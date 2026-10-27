#include "include_asm.h"
#include "overlays/boot/text_001E0900.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_00101550.h"
#include "sdk/main/libc_0013C6D0.h"
#include "sdk/main/libc_0013CA60.h"
#include "vu0.h"
#include "ee.h"
#include "overlays/lib/vector_inlines.h"

#define TIMER0_COUNT (*(volatile u32*)0x10000000)

extern "C" {
extern BootClass170F20* D_001B65AC;
u16 func_457470(u16 seed, const void* data, s32 size);
void func_10DA70(BootSound1B65F8* sound, s32 mode);
void func_11E030(BootInputRoot9670* root, s32 slot, s32 enabled);
s32 func_4656B0(BootRuntime1B657C* runtime, void* data);
void func_11E210(BootInputRoot9670* root, s32 first, s32 second, s32 third);
extern void* D_001B65F4;
void func_11ED90(void* queue, void* object);
extern void* D_001B663C;
extern void* D_001B65E0;
extern struct BootRender6618* D_001B6618;
extern BootResident6658* D_001B6658;
void func_4E09B0(BootDimensionsACD0* display, s32 mode);
void func_4E0BC0(BootDimensionsACD0* display, s32 index, float first, float second, s32 mask);
void func_4DD440(BootDimensionsACD0* display, s32 index, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 width, s32 height);
void func_4DF890(BootDimensionsACD0* display, s32 index, s32 width, s32 height, s32 depth, s32 mode);
void func_4E03C0(BootDimensionsACD0* display, s32 index, s32 width, s32 height);
void func_4DF6E0(BootDimensionsACD0* display, s32 red, s32 green, s32 blue, s32 alpha);
void func_4DE250(BootDimensionsACD0* display, s32 index, s32 x, s32 y, s32 width, s32 height);
void func_4DCFA0(BootDimensionsACD0* display);
void func_4DCC10(void* object, void* value);
void func_4D78F0(void* object);
void func_42D940(void);
void func_11DEE0(BootInputRoot9670* root, void* object, s32 enabled);
void func_4DCEA0(BootDimensionsACD0* display, s32 first, s32 second);
void func_101040(void* settings, s32 widescreen);
extern struct BootDisplayLinks661C* D_001B661C;
extern BootDimensionsACD0* D_001B6650;
extern BootDimensionsACD0* D_001B6520;
extern struct BootDisplay6624* D_001B6624;
extern u8 D_001B6420;
extern BootTrackPool<BootClass177F70>* D_001B6664;
extern BootTrackPool<BootClass1714D0>* D_001B6668;
extern BootTrackPool<BootClass177EE0>* D_001B666C;
extern BootTrackPool<BootClass177C70>* D_001B6670;
extern void* D_001B6674;
extern void* D_001B6678;
extern void* D_001B667C;
extern void* D_001B6680;
s32 func_001ED7B0(void* pool, s32 count);
s32 func_001EDD60(void* pool, s32 count);
s32 func_001EE250(void* pool, s32 count);
s32 func_001EE760(void* pool, s32 count);
void func_001ED610(BootTrackPool<BootClass177C70>* pool);
void func_001EDBC0(void* pool);
void func_001EE0C0(void* pool);
void func_001EE5C0(void* pool);
void func_001EEAE0(void* pool);
void func_4C5B60(s32 first, s32 second);
void func_4E14B0(BootProjectionACD0* projection, BootDimensionsACD0* display);
u32 func_113930(BootResident113E40* heap, u32 size);
s32 func_115430(BootResident1B65E4* object);
s32 func_465B20(BootRuntime1B657C* runtime, BootClass178A90* object);
void lib_container_attach_widget(BootClass178660* object, BootClass170E90* child);
void func_100F60(void* root);
void* func_1012C0(void* root);
s32 func_11D9A0(void* clock_source, struct BootClock* clock);
u32 func_10CE00(void);
void* func_101250(void* root);
void func_45A5D0(void);
void func_45A770(void);
void func_433680(void);
void func_4E33B0(void);
void func_11ECD0(void* queue);
void func_4D8970(void);
void func_121890(BootDimensionsACD0* display);
void func_4E3830(BootDimensionsACD0* display, u32 first, s32 second, s32 third, s32 fourth, s32 fifth, s32 sixth);
void func_4D8A80(struct BootScreenRect* rect, u32 color);
void func_4DD830(BootDimensionsACD0* display, s32 frame, void* queue);
extern void* D_001B65DC;
void func_4D8AC0(void);
void func_4D76C0(void* object, u16 x, u16 y);
void func_4D4BE0(void* object);
void func_11F770(void* owner, s32 flags);
u32 func_4DCFF0(BootDimensionsACD0* display, s32 frame);
s32 func_11DF00(BootInputRoot9670* root);
extern float D_001B6688;
extern float D_001B6690;
s32 func_10CAA0(s32 upper);
s32 func_10CC40(s32 lower, s32 upper);
void func_1010D0(void* root, s32 value, s32 flag);
void func_001FA620(BootImage* object, void* image, s32 mode);
void func_001F9FC0(BootImage* object, s32 first, s32 second, s32 width, s32 height, u32 color, s32 third);
extern const struct BootLabelOffsets D_205170;
s32 func_115270(BootResident1B65E4* object);
void func_419A70(BootClass172500* player, s32 first, s32 second);
void func_41A210(BootClass172500* player);
const struct BootTextExtent* func_4C69B0(BootClass178750* text);
extern const struct BootCaption D_205190[];
void func_112400(void* request, s32 sound, s32 first, s32 second, s32 volume, s32 pan, s32 third);
BootClass170F30* func_473940(BootClass170E90* models, const char* name);
void func_4CC2D0(BootVector4DDAA0* output, float angle);
void func_4CBD20(BootMatrix92D0* output, const BootVector4DDAA0* position, const FieldVec4B* target, float roll);
void func_4CBAC0(BootVector4DDAA0* output, const BootMatrix92D0* matrix);
void func_4CD810(FieldVec4B* output, const BootVector4DDAA0* axis_angle);
BootClass178A90* func_473530(BootClass170E90* models, const char* name);
void* func_473390(BootClass170E90* models, const char* name);
s32 func_4B4550(BootClass178220* animation, float frame, s32 mode);
void func_4DA2F0(void* object, const BootVector4DDAA0* offset, s32 first, s32 second, s32 third, float value);
extern const char D_2059E0[];
extern const char D_2059E8[];
extern const char D_205A28[];
extern const char D_205A38[];
extern const char D_205A48[];
extern const char D_205A58[];
extern const char D_205A68[];
void func_4DAFE0(BootClass178F30* manager, BootDimensionsACD0* display, bool enabled, bool first_flag, bool second_flag, s32 level, u32 mask);
extern u8 D_001B6190[5];
extern u8 D_001B6195;
extern const s16 D_205140[];
extern const char D_205AF8[];
extern const char D_205B00[];
extern const char D_205B08[];
extern const char D_205B18[];
void func_112990(void* request, s32 sound, s32 first, s32 second, s32 third);
void func_10DAA0(BootSound1B65F8* sound, s32 mode);
void func_10DA30(BootSound1B65F8* sound);
void func_10DB10(BootSound1B65F8* sound, s32 value);
void func_10EA70(BootSound1B65F8* sound, BootClass178A90* listener, float first, float second);
void func_10EA90(BootSound1B65F8* sound, s32 speaker, float angle);
s32 func_110920(BootSound1B65F8* sound, s32 handle, s32 flag);
s32 func_111C50(BootSound1B65F8* sound, s32 id, BootClass178A90* emitter, s32 first, s32 volume, s32 second);
s32 func_110C10(BootSound1B65F8* sound, s32 handle);
u32 func_10E310(BootSound1B65F8* sound, s32 handle, float time);
void func_10F000(void* request, s32 first, s32 second);
s32 func_103640(void* queue, s32 id, s32 first, s32 second, s32 third, s32 fourth);
void func_103B20(void* queue, s32 id, s32 first, s32 second, s32 third, s32 fourth);
void func_121FE0(s32 value);
void func_11E020(BootInputRoot9670* root, s32 slot, s32 enabled);
void func_11E320(BootInputRoot9670* root, s32 slot, s32* first, s32* second, s32* third, s32* fourth);
void func_467570(BootClass175070* object, s32 first, s32 second, s32 third, float x, float y, float z);
void lib_text_set_resource(BootClass178750* object, s32 source, s32 key, u8 flag);
void func_479190(BootClass175320* scene, void* data);
void func_474010(BootClass175320* scene, BootDimensionsACD0* display, BootClass178DD0* list, struct BootDisplay6624* state, BootClass178F30* manager, struct BootDisplayLinks661C* links, s32 flag);
BootClass170F30* func_472EB0(BootClass170E90* models, BootClass170F30* model);
void* func_473680(BootClass170E90* models, const char* name);
void func_4BF100(BootClass178220* animation, BootClass170E90* models, void* optional);
void func_4BDB50(BootClass178220* animation, BootClass178370* target, const char* name);
void func_4B3DE0(BootClass178220* animation, BootClass178370* target);
void func_4C96E0(struct BootMorphTarget* target, float weight);
void func_4E24D0(void* display);
void func_4D5870(void* display);
}

/** One timed caption of the opening movie; the list ends with a frame of -1. */
struct BootCaption
{
    /** Movie frame the caption is centred on. */
    s16 frame;
    /** Screen corner, or zero for the centre. */
    s16 anchor;
    /** Nonzero for a message, zero for a picture from the third resource block. */
    s16 is_text;
    /** Picture x, or the message key. */
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};

/** Partial extent returned by the text measurement. */
struct BootTextExtent
{
    float unk00;
    float unk04;
    float width;
    float height;
};

/** Horizontal offsets of the six option labels. */
struct BootLabelOffsets
{
    s32 values[6];
};

/** Clock bytes filled by the resident clock query. */
struct BootClock
{
    u8 status;
    u8 second;
    u8 minute;
    u8 hour;
    u8 unk04[4];
};

/** Screen rectangle passed to the clear-colour setup. */
struct BootScreenRect
{
    s32 x;
    s32 y;
    s32 width;
    s32 height;
};

/** Partial resident render state D_001B6618. */
struct BootRender6618
{
    u8 unk00[0xC];
    u32 clear_color;
    u8 unk10[0x10];
    void* packet;
};

/** Partial resident root whose word at 0x15CC0 points to the status byte. */
struct BootResidentRoot15CC0
{
    u8 unk00[0x15CC0];
    u8* status;
};

/** Partial resident display state D_001B6624 that points back at the display manager. */
struct BootDisplay6624
{
    u8 unk00[0x360];
    BootClass178F30* manager;
};

/** Partial resident object whose display pointer is at offset 0x8C. */
struct BootDisplayUser8C
{
    u8 unk00[0x8C];
    BootDimensionsACD0* display;
};

/** Partial resident object whose display pointer is at offset 0x94. */
struct BootDisplayUser94
{
    u8 unk00[0x94];
    BootDimensionsACD0* display;
};

/** Partial resident object whose display pointer is at offset 0x128. */
struct BootDisplayUser128
{
    u8 unk00[0x128];
    BootDimensionsACD0* display;
};

/** Partial resident manager D_001B661C and the objects that draw through the display. */
struct BootDisplayLinks661C : public BootClass178DD0
{
    u8 unk14[0x406C];
    BootDisplayUser8C* unk4080;
    void* unk4084;
    BootDimensionsACD0* unk4088;
    u8 unk408C[0x42];
    u8 unk40CE;
    u8 unk40CF[0x389];
    BootDisplayUser94* unk4458;
    u8 unk445C[4];
    BootDisplayUser94* unk4460;
    BootDisplayUser94* unk4464;
    BootDisplayUser94* unk4468;
    BootDisplayUser128* unk446C;
};

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
 * @brief Read a byte of the extra protected block when the block passes its checksum.
 * @param settings System settings.
 * @param data Start of the extra protected block.
 * @param value Byte to read.
 * @return Stored byte, or zero when the checksum fails.
 */
static inline u8 settings_extra_byte(BootResource0970* settings, u8* data, u8* value)
{
    if (settings->extra_checksum != func_457470(settings->extra_key, data, (u8*)&settings->extra_checksum - data))
    {
        return 0;
    }
    return *value;
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
    BootModeSlot0910* modes;
    u16 flags;

    if (owner->unk20 == 0)
    {
        return 0;
    }

    modes = owner->unk14;
    flags = 0;
    if (modes[0].unk48 == 2)
    {
        flags |= BOOT_MODE_0910_FLAG_0;
    }
    if (modes[1].unk48 == 2)
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
            delete[] unkDC4;
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
        unkDC4 = new (0) u8[BOOT_TRANSFER_BUFFER_SIZE];
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

/**
 * @brief Drop a pending transfer and go back to waiting for the card.
 * @param object Memory card object.
 */
static inline void cancel_transfer(BootClass170EB0* object)
{
    object->unkDCE = 1;
    object->unkDD0 = -12;
    object->unkDCC = -1;
    object->unkDC0 = -1;
    object->unk1C = 1;
    object->unkDF9 = 0;
    object->unkDF8 = 0;
}

/** @brief Follow the selected card's state and step the save-data checks. */
void BootClass170EB0::update()
{
    s32 progress;
    s32 status;
    u8 done;

    if (unk14 != 0 && unk14->unk20 != 0)
    {
        status = unk1A;
        if (unk1E == 0)
        {
            status = unk14->unk14[unk18].unk48;
            if (status != unk1A)
            {
                unk1A = status;
                unk1C = 1;
                unkDCE = -1;
                if (unkDF9 != 0)
                {
                    cancel_transfer(this);
                }
                return;
            }
        }

        progress = 0;
        done = 0;
        for (;;)
        {
            if (done)
            {
                break;
            }
            switch (unk1C)
            {
            case 0:
                done = 1;
                break;
            case 1:
                if (status != 2)
                {
                    if (unkDF8 == 0)
                    {
                        func_001E1500(1, 15, 1);
                    }
                    else
                    {
                        cancel_transfer(this);
                    }
                    return;
                }

                unk20 = unk14->unk14[unk18].unk50;
                if (unk20 == 0)
                {
                    if (unkD34 == 1)
                    {
                        func_001E1500(1, 16, 1);
                    }
                    else
                    {
                        func_001E1500(1, 16, unkD34);
                    }
                    return;
                }

                unk24 = unk14->unk14[unk18].unk4C;
                if (unk20 == 0 && unkD34 == 1)
                {
                    unk24 = 8000;
                }
                unkDFC[unk18] = unk24;
                unk1C = 2;
                if (unk24 < 175)
                {
                    unk2D = 1;
                }
                break;
            case 2:
                if (strlen(D_205100) + 1 <= BOOT_TRANSFER_NAME_CAPACITY)
                {
                    copy_transfer_name(this, D_205100, D_205988);
                }
                status = func_431F90(unk14, unk18, unk2E, 0, 1, unkD30);
                if (status == -1)
                {
                    done = 1;
                }
                else
                {
                    unk1C = 3;
                }
                break;
            case 3:
                status = func_432270(unk14, unk18, &progress);
                if (status != 0 && status == 1)
                {
                    if (progress == 0)
                    {
                        if (unk2D != 0)
                        {
                            func_001E1500(1, 2, 1);
                        }
                        else
                        {
                            func_001E1500(1, 16, 1);
                        }
                    }
                    else if (progress > 0)
                    {
                        func_001E1500(1, 17, 1);
                    }
                    else
                    {
                        func_001E1500(1, 0, 1);
                    }
                }

                if (unkD34 == 1)
                {
                    if (status == 1)
                    {
                        unk1C = 4;
                    }
                    else
                    {
                        done = 1;
                    }
                }
                else if (status == 1)
                {
                    unk1C = 4;
                }
                else
                {
                    done = 1;
                }
                break;
            case 4:
                if (strlen(D_205100) + 1 <= BOOT_TRANSFER_NAME_CAPACITY)
                {
                    copy_transfer_name(this, D_205100, D_205980);
                }
                status = func_431F90(unk14, unk18, unk2E, 0, 1, unkDBC);
                if (status == -1)
                {
                    done = 1;
                }
                else
                {
                    unk1C = 5;
                }
                break;
            case 5:
                status = func_432270(unk14, unk18, &progress);
                if (status != 0 && status == 1)
                {
                    if (progress == 0)
                    {
                        if (unkD34 == 1)
                        {
                            func_001E1500(1, 6, 1);
                        }
                        else
                        {
                            func_001E1500(1, 6, 2);
                        }
                    }
                    else if (progress > 0)
                    {
                        if (unkD34 == 1)
                        {
                            func_001E1500(1, 5, 1);
                        }
                        else if (unkDF8 != 0)
                        {
                            unk1C = 8;
                            unkDCE = -1;
                        }
                        else
                        {
                            func_001E1500(1, 5, 2);
                        }
                    }
                    else if (unkD34 == 1)
                    {
                        func_001E1500(1, 15, 1);
                    }
                    else
                    {
                        func_001E1500(1, 0, 1);
                        func_001E1A40(0);
                    }
                }
                done = 1;
                break;
            case 8:
                func_001E0AF0();
                done = 1;
                break;
            default:
                done = 1;
                break;
            }
        }
    }
}

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
        unkDC4 = new (0) u8[BOOT_TRANSFER_BUFFER_SIZE];
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
        delete[] unkDC4;
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

/**
 * @brief Hang when the main executable's code no longer matches the copy in the program image.
 */
static inline void check_main_code()
{
    // Uncached cursor; the code it checks starts 0x400000 bytes (0x80000 words) below it.
    u64* code = (u64*)(0x20000000 | 0x500000);
    u64* copy = (u64*)(D_205E38.image->code_offset + (u32)D_205E38.image);
    s32 index;
    for (index = 0; index < 0x8760; index++, code++, copy++)
    {
        if (code[-0x80000] != *copy)
        {
            BootResidentRoot15CC0* root = (BootResidentRoot15CC0*)func_10D8E0();
            *root->status = 0x67;
            for (;;)
            {
            }
        }
    }
}

/**
 * @brief Read the disc state, or three when the resident loader has no disc information.
 * @return Disc state.
 */
static inline u8 disc_state(BootResident1B65E4* resident)
{
    return resident->unk12184 != 0 ? resident->unk141 : 3;
}

/** @brief Check the controllers, then run the widescreen and disc status screens before the opening movie. */
void BootClass170ED0::update()
{
    BootResource0970* settings;
    BootClass171030* input;
    s32 first;
    s32 second;
    u8 finished;
    u8 again;

    if (func_115430(D_001B65E4) != 0)
    {
        return;
    }

    settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    input = D_205E10.input;
    first = input->unk20;
    second = input->unk24;
    if (unk1C == 0)
    {
        switch (unk14)
        {
        case 0:
            if ((((u32)D_205E10.unk10 + 0x7F) & ~0x7F) != 0)
            {
                check_main_code();
                D_001B657C->message_value = 175;
                if ((u32)(first - 16) <= 1 || (u32)(second - 16) <= 1 || (first == 11 && second == 12) ||
                    (first == 11 && second == 14) || (first == 12 && second == 11) || (first == 12 && second == 12) ||
                    (first == 12 && second == 13) || (first == 12 && second == 14) || (first == 13 && second == 12) ||
                    (first == 13 && second == 14) || (first == 14 && second == 11) || (first == 14 && second == 12) ||
                    (first == 14 && second == 13))
                {
                    unk1C = 1;
                    unk14 = 0;
                    return;
                }
                    if (first == 15 && second == 15)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2000;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 15 && second == 10)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2002;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 15 && second == 11)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2002;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 15 && second == 12)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2002;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 15 && second == 13)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2006;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 15 && second == 14)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2009;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 10 && second == 15)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2001;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 10 && second == 10)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2003;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 10 && second == 11)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2003;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 10 && second == 12)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2003;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 10 && second == 13)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2007;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 10 && second == 14)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2010;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 11 && second == 15)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2001;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 11 && second == 10)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2003;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 11 && second == 11)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2003;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 11 && second == 13)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2007;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 12 && second == 15)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2001;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 12 && second == 10)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2003;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 13 && second == 15)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2005;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 13 && second == 10)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2007;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 13 && second == 11)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2007;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 13 && second == 13)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2007;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 14 && second == 15)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2008;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 14 && second == 10)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2010;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
                    if (first == 14 && second == 14)
                    {
                        unk2C = first;
                        unk30 = second;
                        unk20 = 2010;
                        unk14 = 1;
                        func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                        return;
                    }
            }
            break;
        case 1:
            check_main_code();
            unk34 = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, unk34);
            unk38 = new (0) BootClass178750(D_205E10.get_messages(), unk20, 0, 32.0f, 128.0f, 576.0f, 320.0f);
            lib_container_attach_widget(unk34, unk38);
            unk14 = 2;
            break;
        case 2:
        {
            u16 pressed = input->unk18;
            if (pressed & settings->unk00)
            {
                check_main_code();
                unk1C = 1;
                unk14 = 0;
                unk38->destroy();
                unk38 = 0;
                unk34->destroy();
                unk34 = 0;
                func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            }
            else if (pressed & settings->unk02)
            {
                unk38->destroy();
                unk38 = 0;
                unk34->destroy();
                unk34 = 0;
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                unk14 = 0;
            }
            else if (unk2C != first || unk30 != second)
            {
                unk38->destroy();
                unk38 = 0;
                unk34->destroy();
                unk34 = 0;
                input->func_001E9650();
                unk14 = 0;
            }
            break;
        }
        }
    }
    else if (unk1C == 1)
    {
        finished = 0;
        do
        {
            switch (unk14)
            {
            case 0:
                again = 0;
                check_main_code();
                if ((input->unk16 & 0x1000) && (input->unk16 & 0x4000))
                {
                    unk14++;
                    unk34 = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
                    func_465B20(D_001B657C, unk34);
                }
                else if (++unk18 >= 30 && (((u32)D_205E10.unk10 + 0x7F) & ~0x7F) != 0)
                {
                    finished = 1;
                }
                break;
            case 1:
                again = 0;
                if ((((u32)D_205E10.unk10 + 0x7F) & ~0x7F) != 0)
                {
                    check_main_code();
                    unk38 = new (0) BootClass178750(D_205E10.get_messages(), 1, 0, 32.0f, 96.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(unk34, unk38);
                    unk14++;
                }
                break;
            case 2:
                again = 0;
                check_main_code();
                if (input->unk18 & settings->unk00)
                {
                    unk14++;
                    unk18 = 0;
                    unk38->destroy();
                    unk38 = 0;
                    func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                    settings->widescreen = 1;
                }
                else if (input->unk18 & settings->unk04)
                {
                    unk14++;
                    unk18 = 0;
                    unk38->destroy();
                    unk38 = 0;
                    func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                    settings->widescreen = 0;
                }
                else if (input->unk18 & settings->unk02)
                {
                    func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                    finished = 1;
                }
                break;
            case 3:
                again = 0;
                check_main_code();
                if (++unk18 > 10)
                {
                    D_205E10.func_001EAE80(1);
                    unk18 = 0;
                    unk14++;
                }
                break;
            case 4:
                again = 0;
                check_main_code();
                if (++unk18 > 60)
                {
                    unk14++;
                    if (settings->widescreen)
                    {
                        unk38 = new (0) BootClass178750(D_205E10.get_messages(), 2, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                        unk38->set_scale(0.75f);
                    }
                    else
                    {
                        unk38 = new (0) BootClass178750(D_205E10.get_messages(), 7, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                    }
                    lib_container_attach_widget(unk34, unk38);
                    unk18 = 0;
                }
                break;
            case 5:
                again = 0;
                check_main_code();
                if (input->unk18 & settings->unk00)
                {
                    finished = 1;
                    func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                }
                else if (++unk18 > 539 || (input->unk18 & settings->unk02))
                {
                    unk38->destroy();
                    unk38 = 0;
                    unk14++;
                    unk18 = 0;
                    func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                }
                break;
            case 6:
                check_main_code();
                again = 0;
                if (++unk18 > 10)
                {
                    settings->widescreen = 0;
                    D_205E10.func_001EAE80(0);
                    unk14++;
                    unk18 = 0;
                }
                break;
            case 7:
                check_main_code();
                again = 0;
                if (++unk18 > 60)
                {
                    unk14 = 1;
                    unk18 = 0;
                }
                break;
            default:
                check_main_code();
                again = 0;
                break;
            }
        } while (again);

        if (finished)
        {
            unk14 = 0;
            if (unk38 != 0)
            {
                unk38->destroy();
                unk38 = 0;
            }
            if (unk34 != 0)
            {
                unk34->destroy();
                unk34 = 0;
            }
            unk1C = 2;
        }
    }
    else
    {
        finished = 0;
        do
        {
            switch (unk14)
            {
            case 0:
                again = 0;
                check_main_code();
                if (disc_state(D_001B65E4) != 2)
                {
                    if (disc_state(D_001B65E4) == 1)
                    {
                        unk14++;
                        unk34 = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
                        func_465B20(D_001B657C, unk34);
                    }
                    else if (D_205E38.unk14 != 0)
                    {
                        unk14 = 3;
                        unk34 = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
                        func_465B20(D_001B657C, unk34);
                    }
                    else
                    {
                        finished = 1;
                    }
                }
                break;
            case 1:
                again = 0;
                check_main_code();
                if ((((u32)D_205E10.unk10 + 0x7F) & ~0x7F) != 0)
                {
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    unk38 = new (0) BootClass178750(D_205E10.get_messages(), 8, 0, 32.0f, 96.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(unk34, unk38);
                    unk14++;
                }
                break;
            case 2:
                check_main_code();
                again = 0;
                if (input->unk18 & settings->unk00)
                {
                    func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                    finished = 1;
                }
                break;
            case 3:
                again = 0;
                if ((((u32)D_205E10.unk10 + 0x7F) & ~0x7F) != 0)
                {
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    unk38 = new (0) BootClass178750(D_205E10.get_messages(), 0x33, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(unk34, unk38);
                    unk14 = 2;
                }
                break;
            default:
                again = 0;
                break;
            }
        } while (again);

        if (finished)
        {
            if (unk34 != 0)
            {
                unk34->destroy();
                unk34 = 0;
            }
            if (unk38 != 0)
            {
                unk38->destroy();
                unk38 = 0;
            }
            lib_object_detach_owner(this);
            destroy();
            D_001B6614->append_node(new (0) BootClass171050, -1);
        }
    }
}

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

/**
 * @brief Multiply the first three components of a vector by another vector's.
 * @param vector Vector to scale.
 * @param scale Per-component factors; w is unused.
 * @return The scaled vector.
 */
static inline FieldVec4B scale_components(const FieldVec4A& vector, const BootVector4DDAA0& scale)
{
    FieldVec4B result = vector;
    result.x *= scale.x;
    result.y *= scale.y;
    result.z *= scale.z;
    return result;
}

/**
 * @brief Combine two rotations.
 * @param left Rotation applied second.
 * @param right Rotation applied first.
 * @return The product left * right.
 */
static inline FieldVec4B multiply_rotations(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B result;
    result.x = left.w * right.x + right.w * left.x + left.y * right.z - left.z * right.y;
    result.y = left.w * right.y + right.w * left.y + left.z * right.x - left.x * right.z;
    result.z = left.w * right.z + right.w * left.z + left.x * right.y - left.y * right.x;
    result.w = left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z;
    return result;
}

/**
 * @brief Return the absolute value of a float (one abs.s).
 * @param value Value to convert.
 * @return Absolute value.
 */
static inline float abs_float(float value)
{
    return __s_abs(value);
}

void BootClass170EF0::func_001E3FF0()
{
    BootVector4DDAA0 position;
    BootVector4DDAA0 angles;
    BootMatrix92D0 matrix;
    FieldVec4B target;
    FieldVec4B rotation;
    FieldVec4B roll;
    BootVector4DDAA0 axis;
    BootVector4DDAA0 offset;
    float angle = unk54;
    func_4CC2D0(&angles, angle);
    position.x = 300.0f * angles.z;
    position.z = 300.0f * angles.w;
    position.y = 0.0f;
    position.w = 1.0f;
    target = scale_components(FieldVec4A(-1.0f, -1.0f, -1.0f, -1.0f), position);
    func_4CBD20(&matrix, &position, &target, 0.0f);
    func_4CBAC0((BootVector4DDAA0*)&rotation, &matrix);
    axis.x = 0.0f;
    axis.y = 1.0f;
    axis.z = 0.0f;
    axis.w = unk60;
    func_4CD810(&roll, &axis);
    rotation = multiply_rotations(roll, rotation);

    if (unk58 == 0.0f)
    {
        if (unk60 > 0.0f)
        {
            unk60 -= 3.1415927f * D_001B6690;
            unk60 = ee_max_in_place(0.0f, unk60);
        }
        else
        {
            unk60 += 3.1415927f * D_001B6690;
            unk60 = ee_min(0.0f, unk60);
        }
    }
    else if (unk58 < 0.0f)
    {
        unk60 += 9.424778f * D_001B6690;
        unk60 = ee_min(1.5707964f, unk60);
    }
    else
    {
        unk60 -= 9.424778f * D_001B6690;
        unk60 = ee_max(-1.5707964f, unk60);
    }

    BootClass178A90* root = func_473530(unkDC, D_2059E0);
    root->func_001E0510(&position);
    root->func_001E0670((BootVector4DDAA0*)&rotation);

    bool again = true;
    while (again)
    {
        switch (unk70)
        {
        case 0:
            if (unk58 != 0.0f)
            {
                unk5C = 0.0f;
                unk108[1]->unk6A = 0;
                unk70 = 1;
            }
            else if (func_4B4550(unk108[0], unk5C, 2) > 0)
            {
                unk5C = 0.0f;
            }
            else
            {
                again = false;
            }
            break;
        case 1:
            if (func_4B4550(unk108[1], unk5C, 2) > 0)
            {
                if (unk58 == 0.0f)
                {
                    unk5C = 0.0f;
                    unk108[5]->unk6A = 0;
                    unk70 = 5;
                }
                else
                {
                    unk5C = 0.0f;
                    unk108[2]->unk6A = 0;
                    unk70 = 2;
                }
            }
            else
            {
                again = false;
            }
            break;
        case 2:
            if (func_4B4550(unk108[2], unk5C, 2) > 0)
            {
                if (unk58 == 0.0f)
                {
                    unk5C = 0.0f;
                    unk108[4]->unk6A = 0;
                    unk70 = 4;
                }
                else
                {
                    unk5C = 0.0f;
                    unk108[3]->unk6A = 0;
                    unk70 = 3;
                }
            }
            else
            {
                again = false;
            }
            break;
        case 3:
            if (func_4B4550(unk108[3], unk5C, 2) > 0)
            {
                if (unk58 == 0.0f)
                {
                    unk5C = 0.0f;
                    unk108[5]->unk6A = 0;
                    unk70 = 5;
                }
                else
                {
                    unk5C = 0.0f;
                    unk108[2]->unk6A = 0;
                    unk70 = 2;
                }
            }
            else
            {
                again = false;
            }
            break;
        case 4:
            if (func_4B4550(unk108[4], unk5C, 2) > 0)
            {
                unk108[0]->unk6A = 0;
                unk5C = 0.0f;
                unk70 = 0;
            }
            else
            {
                again = false;
            }
            break;
        case 5:
            if (func_4B4550(unk108[5], unk5C, 2) > 0)
            {
                unk108[0]->unk6A = 0;
                unk5C = 0.0f;
                unk70 = 0;
            }
            else
            {
                again = false;
            }
            break;
        }
    }

    switch (unk70)
    {
    case 0:
    case 4:
    case 5:
        unk5C += D_001B6688;
        break;
    case 1:
    case 2:
    case 3:
    {
        float step;
        if (unk58 == 0.0f)
        {
            step = 1.0f;
        }
        else
        {
            step = ee_max(0.5f, abs_float(unk58));
        }
        unk5C += step;
        break;
    }
    }

    void* look = func_473390(unkDC, D_2059E8);
    if (look != 0)
    {
        offset.x = 0.0f;
        offset.y = -160.0f;
        offset.z = 0.0f;
        offset.w = 1.0f;
        func_4DA2F0(look, &offset, 1, 4, 0, 0.5f);
    }
}

/**
 * @brief Read the cursor position for a speaker on the surround page.
 * @param speaker Speaker index.
 * @param x Receives the horizontal position.
 * @param y Receives the vertical position.
 */
void BootClass170EF0::func_001E4610(s32 speaker, float* x, float* y)
{
    BootClass170F30* speakers[4];
    BootVector4DDAA0 position;
    BootVector4DDAA0 screen;
    speakers[0] = func_473940(unkD8, D_205A28);
    speakers[1] = func_473940(unkD8, D_205A38);
    speakers[2] = func_473940(unkD8, D_205A48);
    speakers[3] = func_473940(unkD8, D_205A58);
    speakers[speaker]->update_transform_matrix();
    BootClass170F30* model = speakers[speaker];
    position.x = model->unk90.vectors[0].w;
    position.y = model->unk90.vectors[1].w;
    position.z = model->unk90.vectors[2].w;
    position.w = 1.0f;
    BootClass178F30* manager = D_001B6628;
    func_4E24D0(manager->current_display);
    func_4D5870(D_001B6628->current_display);
    vu0_wait_microprogram();
    vu0_start_microprogram_vf5(&position);
    vu0_wait_microprogram();
    vu0_read_vf6(&screen);
    *x = screen.x - 1728.0f;
    *y = screen.y - 1824.0f;
}

/**
 * @brief Give a speaker model an even color modulation and recompute its combined color.
 * @param model Speaker model.
 * @param shade Red, green and blue factor; alpha is one.
 */
static inline void set_speaker_color(BootClass170F30* const& model, float shade)
{
    BootVector4DDAA0 color;
    color.x = shade;
    color.y = shade;
    color.z = shade;
    color.w = 1.0f;
    BootClass170F30* speaker = model;
    copy_vector(&speaker->unk560, &color);
    speaker->func_001DDAA0();
}

void BootClass170EF0::func_001E4760()
{
    BootClass170F30* speakers[5];
    speakers[0] = func_473940(unkD8, D_205A28);
    speakers[1] = func_473940(unkD8, D_205A38);
    speakers[2] = func_473940(unkD8, D_205A48);
    speakers[3] = func_473940(unkD8, D_205A58);
    speakers[4] = func_473940(unkD8, D_205A68);

    for (s32 i = 0; i < 5; i++)
    {
        BootVector4DDAA0 position;
        BootVector4DDAA0 angles;
        BootMatrix92D0 matrix;
        FieldVec4B target;
        BootVector4DDAA0 rotation;
        func_4CC2D0(&angles, i < 4 ? D_001B65F8->speaker_angles[i] : 1.5707964f);
        position.x = 250.0f * angles.z;
        position.z = 250.0f * angles.w;
        position.y = 0.0f;
        position.w = 1.0f;
        speakers[i]->func_001E0510(&position);
        target = scale_components(FieldVec4A(-1.0f, -1.0f, -1.0f, -1.0f), position);
        func_4CBD20(&matrix, &position, &target, 0.0f);
        func_4CBAC0(&rotation, &matrix);
        speakers[i]->func_001E0670(&rotation);
    }

    if (unk72 != 0)
    {
        for (s32 i = 0; i < 4; i++)
        {
            if (i == unk6F)
            {
                BootVector4DDAA0 scale;
                copy_vector(&scale, &speakers[i]->unk560);
                if (unk72 == 1)
                {
                    scale.x += 2.0f * D_001B6690;
                    scale.y += 2.0f * D_001B6690;
                    scale.z += 2.0f * D_001B6690;
                    if (!(scale.x <= 2.0f))
                    {
                        scale.x = 2.0f;
                        scale.y = 2.0f;
                        scale.z = 2.0f;
                        unk72 = 2;
                    }
                }
                else
                {
                    scale.x -= 2.0f * D_001B6690;
                    scale.y -= 2.0f * D_001B6690;
                    scale.z -= 2.0f * D_001B6690;
                    if (scale.x < 1.0f)
                    {
                        scale.x = 1.0f;
                        scale.y = 1.0f;
                        scale.z = 1.0f;
                        unk72 = 1;
                    }
                }
                BootClass170F30* model = speakers[i];
                copy_vector(&model->unk560, &scale);
                model->func_001DDAA0();
            }
            else
            {
                set_speaker_color(speakers[i], 1.0f);
            }
        }
    }
    else
    {
        for (s32 i = 0; i < 4; i++)
        {
            set_speaker_color(speakers[i], 1.0f);
        }
    }
}

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
            D_001B6654->unk278 = (1.3333334f * (1.0714285f * (float)D_205E10.unk04->unk3C60.height)) / (float)D_205E10.unk04->unk3C60.width;
            D_001B6654->unk25C = 1.5707964f;
            D_205E10.func_001EACD0();
            break;
        case 1:
            settings->widescreen = 1;
            D_001B6654->unk278 =
                (1.7777778f * ((1.3333334f * (1.0714285f * (float)D_205E10.unk04->unk3C60.height)) / (float)D_205E10.unk04->unk3C60.width)) /
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

void BootClass170EF0::func_001E5250(float* x, float* y)
{
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    *x = 58.0f;
    switch (unk68)
    {
    case 1:
        switch (unk6A)
        {
        case 0:
            *y = 90.0f;
            return;
        case 1:
            *y = 126.0f;
            return;
        case 2:
            *y = 160.0f;
            return;
        case 3:
            *y = 194.0f;
            return;
        }
        break;
    case 3:
        switch (unk6A)
        {
        case 0:
            *y = 108.0f;
            return;
        case 1:
            *y = 148.0f;
            return;
        case 2:
            *y = 188.0f;
            return;
        case 3:
            *y = 228.0f;
            return;
        }
        break;
    case 5:
        if (settings_extra_1a1(settings))
        {
            switch (unk6A)
            {
            case 0:
                *y = 108.0f;
                return;
            case 1:
                *y = 148.0f;
                return;
            case 2:
                *y = 188.0f;
                return;
            case 3:
                *y = 228.0f;
                return;
            }
        }
        else
        {
            switch (unk6A)
            {
            case 0:
                *y = 108.0f;
                return;
            case 1:
                *y = 158.0f;
                return;
            case 2:
                *y = 208.0f;
                return;
            }
        }
        break;
    default:
        switch (unk6A)
        {
        case 0:
            *y = 108.0f;
            return;
        case 1:
            *y = 176.0f;
            return;
        }
        break;
    }
}

/**
 * @brief Store a model's color modulation and recompute its combined color.
 * @param model Model to update.
 * @param red Red factor.
 * @param green Green factor.
 * @param blue Blue factor.
 * @param alpha Alpha factor.
 */
static inline void set_model_color(BootClass170F30* model, float red, float green, float blue, float alpha)
{
    BootVector4DDAA0 color;
    color.x = red;
    color.y = green;
    color.z = blue;
    color.w = alpha;
    copy_vector(&model->unk560, &color);
    model->func_001DDAA0();
}

void BootClass170EF0::func_001E5510()
{
    BootResource0970* settings;

    if (unk18[4] != 0 && unk6D == 0)
    {
        settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
        if (unk69 != unk68)
        {
            unk69 = unk68;
            for (s32 i = 0; i < 4; i++)
            {
                if (unk84[16 + i] != 0)
                {
                    lib_object_detach_owner(unk84[16 + i]);
                    unk84[16 + i]->destroy();
                    unk84[16 + i] = 0;
                }
                unk84[16 + i] = new (0) BootImage;
            }

            switch (unk68)
            {
        case 0:
            unk80 = -272.0f;
            func_001FA620(unk84[16], (void*)(((u32)unk18[3] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[16], 0, 8, 288, 40, 0x80808080, 0);
            unk84[16]->unk18->func_001E0520(-272.0f, -142.0f, 0.0f);
            func_001FA620(unk84[17], (void*)(((u32)unk18[3] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[17], 0, 68, 288, 40, 0x80808080, 0);
            unk84[17]->unk18->func_001E0520(-272.0f, -74.0f, 0.0f);
            break;
        case 1:
            unk80 = -272.0f;
            func_001FA620(unk84[16], (void*)(((u32)unk18[3] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[16], 0, 106, 288, 40, 0x80808080, 0);
            unk84[16]->unk18->func_001E0520(-272.0f, -162.0f, 0.0f);
            func_001FA620(unk84[17], (void*)(((u32)unk18[3] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[17], 0, 162, 200, 40, 0x80808080, 0);
            unk84[17]->unk18->func_001E0520(-272.0f, -126.0f, 0.0f);
            func_001FA620(unk84[18], (void*)(((u32)unk18[3] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[18], 0, 236, 424, 40, 0x80808080, 0);
            unk84[18]->unk18->func_001E0520(-272.0f, -90.0f, 0.0f);
            func_001FA620(unk84[19], (void*)(((u32)unk18[3] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[19], 224, 168, 237, 38, 0x80808080, 0);
            unk84[19]->unk18->func_001E0520(-272.0f, -55.0f, 0.0f);
            break;
        case 2:
            unk80 = -272.0f;
            func_001FA620(unk84[16], (void*)(((u32)unk18[3] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[16], 0, 312, 340, 40, 0x80808080, 0);
            unk84[16]->unk18->func_001E0520(-272.0f, -142.0f, 0.0f);
            func_001FA620(unk84[17], (void*)(((u32)unk18[3] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[17], 0, 368, 340, 40, 0x80808080, 0);
            unk84[17]->unk18->func_001E0520(-272.0f, -74.0f, 0.0f);
            break;
        case 3:
            unk80 = -260.0f;
            func_001FA620(unk84[16], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[16], 0, 0, 340, 40, 0x80808080, 0);
            unk84[16]->unk18->func_001E0520(-260.0f, -142.0f, 0.0f);
            func_001FA620(unk84[17], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[17], 0, 55, 340, 40, 0x80808080, 0);
            unk84[17]->unk18->func_001E0520(-260.0f, -102.0f, 0.0f);
            func_001FA620(unk84[18], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[18], 0, 110, 340, 40, 0x80808080, 0);
            unk84[18]->unk18->func_001E0520(-260.0f, -62.0f, 0.0f);
            func_001FA620(unk84[19], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[19], 0, 416, 500, 40, 0x80808080, 0);
            unk84[19]->unk18->func_001E0520(-260.0f, -22.0f, 0.0f);
            break;
        case 4:
            unk80 = -254.0f;
            func_001FA620(unk84[16], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[16], 0, 160, 340, 40, 0x80808080, 0);
            unk84[16]->unk18->func_001E0520(-272.0f, -142.0f, 0.0f);
            func_001FA620(unk84[17], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[17], 0, 215, 340, 40, 0x80808080, 0);
            unk84[17]->unk18->func_001E0520(-272.0f, -74.0f, 0.0f);
            break;
        case 5:
            unk80 = -260.0f;
            if (!settings_extra_1a1(settings))
            {
                func_001FA620(unk84[16], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(unk84[16], 0, 257, 340, 42, 0x80808080, 0);
                unk84[16]->unk18->func_001E0520(-260.0f, -142.0f, 0.0f);
                func_001FA620(unk84[17], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(unk84[17], 0, 313, 340, 42, 0x80808080, 0);
                unk84[17]->unk18->func_001E0520(-260.0f, -92.0f, 0.0f);
                func_001FA620(unk84[18], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(unk84[18], 0, 369, 340, 42, 0x80808080, 0);
                unk84[18]->unk18->func_001E0520(-260.0f, -42.0f, 0.0f);
            }
            else
            {
                func_001FA620(unk84[16], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(unk84[16], 3, 257, 340, 42, 0x80808080, 0);
                unk84[16]->unk18->func_001E0520(-260.0f, -142.0f, 0.0f);
                func_001FA620(unk84[17], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(unk84[17], 3, 313, 340, 42, 0x80808080, 0);
                unk84[17]->unk18->func_001E0520(-260.0f, -102.0f, 0.0f);
                func_001FA620(unk84[18], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(unk84[18], 3, 369, 340, 42, 0x80808080, 0);
                unk84[18]->unk18->func_001E0520(-260.0f, -62.0f, 0.0f);
                func_001FA620(unk84[19], (void*)(((u32)unk18[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(unk84[19], 0, 466, 340, 42, 0x80808080, 0);
                unk84[19]->unk18->func_001E0520(-260.0f, -24.0f, 0.0f);
            }
            break;
            }
        }

        if (settings->widescreen)
        {
            for (s32 i = 0; i < 4; i++)
            {
                if (unk84[16 + i] != 0 && unk84[16 + i]->unk18 != 0)
                {
                    BootVector4DDAA0 position;
                    copy_vector(&position, &unk84[16 + i]->unk18->unk20);
                    position.x = 8.0f + 1.3333334f * unk80;
                    unk84[16 + i]->unk18->func_001E0510(&position);
                }
            }
        }
        else
        {
            for (s32 i = 0; i < 4; i++)
            {
                if (unk84[16 + i] != 0 && unk84[16 + i]->unk18 != 0)
                {
                    BootVector4DDAA0 position;
                    copy_vector(&position, &unk84[16 + i]->unk18->unk20);
                    position.x = unk80;
                    unk84[16 + i]->unk18->func_001E0510(&position);
                }
            }
        }

        s32 i;
        BootClass170F30* model;
        // TODO: My guess; the original reads the extra block through a pointer formed before the loop.
        u8* extra = &settings->unk1A0;
        for (i = 0; i < 4; i++)
        {
            if (unk84[16 + i] == 0)
            {
                continue;
            }
            model = unk84[16 + i]->unk18;
            if (model == 0)
            {
                continue;
            }
            if (i == 2 && unk68 == 5)
            {
                if (!settings_extra_byte(settings, extra, &settings->unk1A1))
                {
                    set_model_color(model, 0.5f, 0.5f, 0.5f, 1.0f);
                    continue;
                }
            }
            if (i == 3 && unk68 == 5)
            {
                if (!settings_extra_byte(settings, extra, &settings->unk1A2))
                {
                    set_model_color(model, 0.5f, 0.5f, 0.5f, 1.0f);
                    continue;
                }
            }
            if (unk6A == i)
            {
                BootVector4DDAA0 scale;
                copy_vector(&scale, &model->unk560);
                if (unk6C == 0)
                {
                    scale.x -= 0.01f * D_001B6688;
                    scale.y -= 0.005f * D_001B6688;
                    if (scale.y < 0.5f)
                    {
                        scale.y = 0.5f;
                    }
                    if (scale.x < 0.5f)
                    {
                        scale.x = 0.5f;
                        unk6C = 1;
                    }
                }
                else if (unk6C != 0)
                {
                    scale.x += 0.01f * D_001B6688;
                    scale.y += 0.005f * D_001B6688;
                    if (!(scale.y <= 1.0f))
                    {
                        scale.y = 1.0f;
                    }
                    if (!(scale.x <= 1.0f))
                    {
                        scale.x = 1.0f;
                        unk6C = 0;
                    }
                }
                copy_vector(&model->unk560, &scale);
                model->func_001DDAA0();
            }
            else
            {
                set_model_color(model, 1.0f, 1.0f, 1.0f, 1.0f);
            }
        }
    }
}

// TODO: Only matches with this off to the end of the file; find the real cause.
#pragma opt_pulloutconstants off
/** @brief Create the page's images once their textures are loaded, then place and highlight them. */
void BootClass170EF0::func_001E63B0()
{
    BootResource0970* settings;
    BootLabelOffsets offsets;

    if (unk18[4] == 0)
    {
        return;
    }

    if (unk84[0] == 0)
    {
        unk84[0] = new (0) BootImage;
        func_001FA620(unk84[0], (void*)(((u32)unk18[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(unk84[0], 0, 1, 0x1E8, 0xDF, 0x80808080, 0);
        unk84[0]->unk18->func_001E0520(-244.0f, -112.0f, 0.0f);
    }

    if (unk84[1] == 0)
    {
        unk84[1] = new (0) BootImage;
        func_001FA620(unk84[1], (void*)(((u32)unk18[1] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(unk84[1], 0, 0, 0x280, 0x50, 0x80808080, 0);
        unk84[1]->unk18->func_001E0520(-320.0f, -216.0f, 0.0f);
    }

    if (unk84[2] == 0 && unk6D == 0)
    {
        unk84[2] = new (0) BootImage;
        func_001FA620(unk84[2], (void*)(((u32)unk18[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(unk84[2], 0x1A, 0xF5, 0x18, 0x16, 0x80808080, 0);
        for (s32 i = 0; i < 6; i++)
        {
            unk84[3 + i] = new (0) BootImage;
            func_001FA620(unk84[3 + i], (void*)(((u32)unk18[0] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[3 + i], 0x52, 0xF3 + i * 29, 0xEE, 0x1C, 0x80808080, 0);
        }
    }

    if (unk84[9] == 0)
    {
        for (s32 i = 0; i < 6; i++)
        {
            unk84[9 + i] = new (0) BootImage;
            func_001FA620(unk84[9 + i], (void*)(((u32)unk18[2] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(unk84[9 + i], 0, 2 + i * 32, 0x180, 0x20, 0x80808080, 0);
        }
    }

    if (unk84[15] == 0 && unk6D == 0)
    {
        unk84[15] = new (0) BootImage;
        func_001FA620(unk84[15], (void*)(((u32)unk18[2] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(unk84[15], 0, 0xC2, 0x180, 0x20, 0x80808080, 0);
    }

    settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    if (settings->widescreen)
    {
        if (unk84[1] != 0)
        {
            unk84[1]->unk18->func_001E0520(-414.66669f, -216.0f, 0.0f);
            unk84[1]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }
        for (s32 i = 0; i < 6; i++)
        {
            if (unk84[3 + i] != 0)
            {
                unk84[3 + i]->unk18->func_001E0520(160.0f, 30.0f + (float)(i * 29), 0.0f);
            }
            if (unk84[9 + i] != 0)
            {
                unk84[9 + i]->unk18->func_001E0520(21.0f, -204.0f, 0.0f);
            }
        }
        if (unk84[15] != 0)
        {
            unk84[15]->unk18->func_001E0520(-426.66669f, 170.0f, 0.0f);
        }
    }
    else
    {
        if (unk84[1] != 0)
        {
            unk84[1]->unk18->func_001E0520(-320.0f, -216.0f, 0.0f);
            unk84[1]->unk18->func_001DDED0(1.0f, 1.0f, 1.0f);
        }
        for (s32 i = 0; i < 6; i++)
        {
            if (unk84[3 + i] != 0)
            {
                unk84[3 + i]->unk18->func_001E0520(56.0f, 30.0f + (float)(i * 29), 0.0f);
            }
            if (unk84[9 + i] != 0)
            {
                unk84[9 + i]->unk18->func_001E0520(-80.0f, -204.0f, 0.0f);
            }
        }
        if (unk84[15] != 0)
        {
            unk84[15]->unk18->func_001E0520(-320.0f, 170.0f, 0.0f);
        }
    }

    offsets = D_205170;
    for (s32 i = 0; i < 6; i++)
    {
        if (unk68 == i)
        {
            if (unk84[3 + i] != 0)
            {
                BootVector4DDAA0 color;
                color.x = 1.0f;
                color.y = 1.0f;
                color.z = 1.0f;
                color.w = 1.0f;
                BootClass170F30* model = unk84[3 + i]->unk18;
                copy_vector(&model->unk560, &color);
                model->func_001DDAA0();
            }
            if (unk84[2] != 0)
            {
                if (settings->widescreen)
                {
                    unk84[2]->unk18->func_001E0520(142.0f + 1.3333334f * (float)offsets.values[i],
                        (float)(31.0 + 29.0 * i), 0.0f);
                }
                else
                {
                    unk84[2]->unk18->func_001E0520(44.0f + (float)offsets.values[i], (float)(31.0 + 29.0 * i), 0.0f);
                }
            }
            if (unk84[9 + i] != 0)
            {
                unk84[9 + i]->unk18->unk6a &= ~1;
            }
        }
        else
        {
            if (unk84[3 + i] != 0)
            {
                BootVector4DDAA0 color;
                color.x = 0.5f;
                color.y = 0.5f;
                color.z = 0.5f;
                color.w = 1.0f;
                BootClass170F30* model = unk84[3 + i]->unk18;
                copy_vector(&model->unk560, &color);
                model->func_001DDAA0();
            }
            if (unk84[9 + i] != 0)
            {
                unk84[9 + i]->unk18->unk6a |= 1;
            }
        }
    }

    if (unk84[15] != 0)
    {
        if (unk68 == 5)
        {
            unk84[15]->unk18->unk6a |= 1;
        }
        else
        {
            unk84[15]->unk18->unk6a &= ~1;
        }
    }
}

/** Partial Lib morph target, one of a face model's children; unk0f is two for a morph target. */
struct BootMorphTarget : public BootClass170E90
{
    u8 unk14[0x1C];
    /** Shape the target draws, such as a mouth shape or zero for closed eyes. */
    s32* shape;
};

/** @brief Queue a fade-out over the current screen. */
static inline void queue_fade()
{
    BootClass171C00* fade = new (0) BootClass171C00(D_205E10.unk04);
    fade->unkd0 = 2.0f;
    D_001B661C->append_node(fade, -1);
}

/** @brief Show the message describing the selected option's value. */
inline void BootClass170EF0::show_value_message()
{
    lib_text_set_resource(unk140, D_205E10.get_messages(), func_001E5090(), 0);
}

/**
 * @brief Test buttons pressed this frame against a mask.
 * @param input Pad input.
 * @param mask Buttons to test.
 * @return Nonzero when any of them was pressed.
 */
static inline s32 button_pressed(BootClass171030* input, u16 mask)
{
    return input->unk18 & mask;
}

/**
 * @brief Move the cursor straight to a position.
 * @param cursor Cursor to move.
 * @param x Horizontal position.
 * @param y Vertical position.
 */
static inline void place_cursor(BootClass175070* cursor, float x, float y)
{
    ItemCreationClass185050& motion = *cursor;
    motion.unk10 = x;
    motion.unk14 = y;
    motion.unk35 = 1;
    cursor->unkae = 1;
}

/**
 * @brief Test whether a list walk has come back to the list.
 * @param list List sentinel.
 * @param node Current node.
 * @return Whether node is the sentinel.
 */
static inline bool at_end(const BootClass170E80* list, const BootClass170E80* node)
{
    if (list == node)
    {
        return true;
    }
    return false;
}

/**
 * @brief Read a surround speaker's current angle.
 * @param sound Sound system.
 * @param speaker Speaker index.
 * @return Angle in radians.
 */
static inline float speaker_angle(BootSound1B65F8* sound, s32 speaker)
{
    return sound->speaker_angles[speaker];
}

/** @brief Run the options menu: load it, take input on each page and the surround page, then close it. */
void BootClass170EF0::update()
{
    BootClass171030* input = D_205E10.input;
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    u8 extra = settings_extra_byte(settings, &settings->unk1A0, &settings->unk1A1);
    D_001B6195 = extra ? 4 : 3;
    switch (unk50)
    {
    case 0:
        if (func_102D00(D_001B65E8) != 0)
        {
            func_112990(D_001B65F8, 0x48, 1, 0, 0);
            func_103E70(D_001B65E8, 0x29, unk2C, 1, 0x34BC0, 0, 0, 0, 1);
            func_4DF6E0(D_205E10.unk04, 0x49, 0x47, 0x9D, 0x7F);
            D_001B661C->prepend_node(new (0) BootClass179150, -1);
            unk6B = 0;
            unk50++;
            unk6C = 0;
            unk13C = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, unk13C);
            unk140 = new (0) BootClass178750(D_205E10.get_messages(), 10, 1, 32.0f, 272.0f, 344.0f, 224.0f);
            unk140->set_color(0x34130F);
            lib_container_attach_widget(unk13C, unk140);
            func_001E4B50();
            show_value_message();
            float x;
            float y;
            func_001E5250(&x, &y);
            unk144 = new (0) BootClass175070;
            func_467570(unk144, 1, 0, 0xF42400, x, y, 0.0f);
            func_465B20(D_001B657C, unk144);
            func_10DAA0(D_001B65F8, 2);
        }
        break;
    case 1:
        unk18[unk6B] = func_102920(D_001B65EC, unk14, unk6B, 1);
        func_1025A0(D_001B65EC, unk14, (void*)(((u32)unk18[unk6B] + 0x7F) & ~0x7F), unk6B);
        if (++unk6B >= 5)
        {
            unk50++;
            unk69 = 0xFF;
            func_121FE0(0);
        }
        break;
    case 2:
        if (input->unk1C == 0x40 && unk144->unk35)
        {
            unk6A = (unk6A + 1) % D_001B6190[unk68];
            func_001E4CE0();
            float x;
            float y;
            func_001E5250(&x, &y);
            unk144->func_00466E40(x, y, 0.05f);
            unk6C = 0;
            func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
            show_value_message();
        }
        if (input->unk1C == 0x10 && unk144->unk35)
        {
            u8 count = D_001B6190[unk68];
            unk6A = (unk6A + count - 1) % count;
            unk6C = 0;
            func_001E4CE0();
            float x;
            float y;
            func_001E5250(&x, &y);
            unk144->func_00466E40(x, y, 0.05f);
            func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
            show_value_message();
        }
        if (button_pressed(input, settings->unk00))
        {
            if (unk6A == 2 && unk68 == 5 && !settings_extra_byte(settings, &settings->unk1A0, &settings->unk1A1))
            {
                func_112400(D_001B65F8, 3, 0, 0, 0x7F, 0x40, 0);
                break;
            }
            if (unk6A == 3 && unk68 == 5 && !settings_extra_byte(settings, &settings->unk1A0, &settings->unk1A2))
            {
                func_112400(D_001B65F8, 3, 0, 0, 0x7F, 0x40, 0);
                break;
            }
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            unk50 = 4;
        }
        else if (button_pressed(input, settings->unk02))
        {
            if (unk68 == 0)
            {
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                func_10F000(D_001B65F8, 0x1E, -1);
                unk50 = 3;
                break;
            }
            else
            {
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                unk50 = 5;
            }
        }
        if (button_pressed(input, settings->unk04) && unk68 == 1 && unk6A == 2)
        {
            func_112400(D_001B65F8, 4, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            unk50 = 6;
        }
        break;
    case 3:
        func_4DF6E0(D_205E10.unk04, 0, 0, 0, 0x7F);
        if (func_103640(D_001B65E8, 0x29, 0, 0, -1, 0) != 0)
        {
            func_103B20(D_001B65E8, 0x29, 0, 0, -1, 0);
        }
        for (s32 i = 0; i < 21; i++)
        {
            if (unk84[i] != 0)
            {
                lib_object_detach_owner(unk84[i]);
                unk84[i]->destroy();
                unk84[i] = 0;
            }
        }
        if (unk13C != 0)
        {
            unk13C->destroy();
            unk13C = 0;
        }
        if (unk140 != 0)
        {
            unk140->destroy();
            unk140 = 0;
        }
        if (unk144 != 0)
        {
            unk144->destroy();
            unk144 = 0;
        }
        D_001B6614->append_node(new (0) BootClass171BB0(0), -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    case 4:
        if (++unk68 > 5)
        {
            func_4DF6E0(D_205E10.unk04, 0, 0, 0, 0x7F);
            func_10F000(D_001B65F8, 0x1E, -1);
            unk50 = 11;
        }
        else
        {
            func_001E4B50();
            float x;
            float y;
            func_001E5250(&x, &y);
            place_cursor(unk144, x, y);
            show_value_message();
            unk50 = 2;
        }
        break;
    case 5:
    {
        unk68--;
        func_001E4B50();
        float x;
        float y;
        func_001E5250(&x, &y);
        place_cursor(unk144, x, y);
        show_value_message();
        unk50 = 2;
        break;
    }
    case 6:
        unk6D = 1;
        unk140->destroy();
        unk140 = 0;
        unk50 = 7;
        for (s32 i = 2; i < 9; i++)
        {
            lib_object_detach_owner(unk84[i]);
            unk84[i]->destroy();
            unk84[i] = 0;
        }
        unk84[15]->destroy();
        lib_object_detach_owner(unk84[15]);
        unk84[15] = 0;
        for (s32 i = 16; i < 20; i++)
        {
            lib_object_detach_owner(unk84[i]);
            unk84[i]->destroy();
            unk84[i] = 0;
        }
        break;
    case 7:
        if (unk6E == 8)
        {
            func_11E020(D_001B65F0, 0, 0);
            unkD8 = new (0) BootClass175320;
            func_479190(unkD8, (void*)(((u32)unk30[0] + 0x7F) & ~0x7F));
            func_474010(unkD8, D_205E10.unk04, D_001B6614, D_001B6624, D_001B6628, D_001B661C, 1);
            unkDC = new (0) BootClass175320;
            func_479190(unkDC, (void*)(((u32)unk30[1] + 0x7F) & ~0x7F));
            func_474010(unkDC, D_205E10.unk04, D_001B6614, D_001B6624, D_001B6628, D_001B661C, 1);
            s32 count = 0;
            for (BootClass170F30* model = func_473940(unkDC, D_205AF8); model != 0; model = func_472EB0(unkDC, model))
            {
                if (model->unk6c == 0x100)
                {
                    unkE0[count] = new (0) BootClass170F30;
                    unkE0[count]->func_4A37C0(D_001B661C, model);
                    unkE0[count++]->unk208 = model->unk208;
                }
            }
            for (s32 i = 0; i < 6; i++)
            {
                unk108[i] = new (0) BootClass178220;
                unk108[i]->set_resource((void*)(((u32)unk30[2 + i] + 0x7F) & ~0x7F));
                func_4BF100(unk108[i], unkDC, 0);
                unk120[i] = new (0) BootClass178370;
                func_4BDB50(unk108[i], unk120[i], D_205B00);
                func_4B3DE0(unk108[i], unk120[i]);
            }
            D_001B661C->prepend_node(new (0) BootClass179150, -1);
            D_001B6628->current_display = func_473680(unkD8, D_205B08);
            unk54 = 1.5707964f;
            unk5C = 0.0f;
            unk58 = 0.0f;
            unk70 = 0;
            unk60 = 0.0f;
            unk78 = 0;
            unk72 = 0;
            func_10EA70(D_001B65F8, func_473530(unkD8, D_2059E0), 0.0f, 500.0f);
            unk140 = new (0) BootClass178750(D_205E10.get_messages(), 15, 1, 32.0f, 352.0f, 576.0f, 112.0f);
            unk140->set_color(0x34130F);
            lib_container_attach_widget(unk13C, unk140);
            func_001E3FF0();
            unk6F = 0;
            unk71 = 0;
            func_001E4760();
            func_10DB10(D_001B65F8, 10000);
            unk50++;
        }
        break;
    case 8:
    {
        float x;
        float y;
        func_001E4610(0, &x, &y);
        place_cursor(unk144, x, y);
        unk50++;
        unk74 = 0;
        break;
    }
    case 9:
        if (input->unk1C & 0xC0)
        {
            if (unk72 == 0)
            {
                if (unk144->unk35)
                {
                    unk6F = (unk6F + 1) & 3;
                    float x;
                    float y;
                    func_001E4610(unk6F, &x, &y);
                    unk144->func_00466E40(x, y, 0.05f);
                    unk6C = 0;
                    func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
                }
            }
            else
            {
                float turned = speaker_angle(D_001B65F8, unk6F);
                float angle = turned;
                turned += 1.5707964f * D_001B6690;
                if (turned >= 6.2831855f)
                {
                    turned -= 6.2831855f;
                }
                float upper = speaker_angle(D_001B65F8, (unk6F + 1) & 3) - 0.2617994f;
                float lower = 0.2617994f + speaker_angle(D_001B65F8, (unk6F - 1) & 3);
                if (angle < turned)
                {
                    if (unk6F == 0 && angle <= 1.3089969f && turned > 1.3089969f)
                    {
                        turned = 1.3089969f;
                    }
                    if (upper - angle >= -0.000001f && turned > upper)
                    {
                        turned = upper;
                    }
                    if (angle - lower >= -0.000001f && turned < lower)
                    {
                        turned = lower;
                    }
                }
                func_10EA90(D_001B65F8, unk6F, turned);
                settings->speaker_angles[unk6F] = turned;
            }
        }
        if (input->unk1C & 0x30)
        {
            if (unk72 == 0)
            {
                if (unk144->unk35)
                {
                    unk6F = (unk6F + 3) & 3;
                    float x;
                    float y;
                    func_001E4610(unk6F, &x, &y);
                    unk144->func_00466E40(x, y, 0.05f);
                    func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
                }
            }
            else
            {
                float turned = speaker_angle(D_001B65F8, unk6F);
                float angle = turned;
                turned -= 1.5707964f * D_001B6690;
                if (turned < 0.0f)
                {
                    turned += 6.2831855f;
                }
                float upper = speaker_angle(D_001B65F8, (unk6F + 1) & 3) - 0.2617994f;
                float lower = 0.2617994f + speaker_angle(D_001B65F8, (unk6F - 1) & 3);
                if (angle > turned)
                {
                    if (unk6F == 1 && angle >= 1.8325948f && turned < 1.8325957f)
                    {
                        turned = 1.8325957f;
                    }
                    if (upper - angle >= -0.000001f && turned > upper)
                    {
                        turned = upper;
                    }
                    if (angle - lower >= -0.000001f && turned < lower)
                    {
                        turned = lower;
                    }
                }
                func_10EA90(D_001B65F8, unk6F, turned);
                settings->speaker_angles[unk6F] = turned;
            }
        }
        if (button_pressed(input, settings->unk04))
        {
            s32 line = func_10CAA0(9);
            if (unk71 < 12)
            {
                unk71++;
            }
            else
            {
                line += 9;
            }
            if (unk74 != 0)
            {
                func_110920(D_001B65F8, unk74, 0);
                unk74 = 0;
            }
            unk74 = func_111C50(D_001B65F8, D_205140[line], func_473530(unkDC, D_2059E0), 0, 0x7F, 0);
        }
        if (button_pressed(input, settings->unk00))
        {
            if (unk72 == 0)
            {
                func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                unk72 = 1;
                unk64 = speaker_angle(D_001B65F8, unk6F);
            }
            else
            {
                func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                unk72 = 0;
            }
        }
        if (button_pressed(input, settings->unk02))
        {
            if (unk72 == 0)
            {
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                unk50 = 10;
            }
            else
            {
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                func_10EA90(D_001B65F8, unk6F, unk64);
                settings->speaker_angles[unk6F] = unk64;
                unk72 = 0;
                func_001E4760();
                float x;
                float y;
                func_001E4610(unk6F, &x, &y);
                place_cursor(unk144, x, y);
            }
        }
        if ((input->unk18 & 9) && unk72 == 0)
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            func_10DA30(D_001B65F8);
            func_001E4760();
            for (s32 i = 0; i < 4; i++)
            {
                settings->speaker_angles[i] = speaker_angle(D_001B65F8, i);
            }
            float x;
            float y;
            func_001E4610(unk6F, &x, &y);
            place_cursor(unk144, x, y);
        }
        if (unk74 != 0)
        {
            BootClass170F30* face = func_473940(unkDC, D_205B18);
            BootClass170E80* end = &face->children;
            BootClass170E80* node = end->next;
            if (func_110C10(D_001B65F8, unk74) != 0)
            {
                s32 shape;
                switch (func_10E310(D_001B65F8, unk74, 2.0f))
                {
                case 0:
                    shape = -1;
                    break;
                case 1:
                    shape = 1;
                    break;
                case 2:
                    shape = 2;
                    break;
                case 3:
                    shape = 3;
                    break;
                case 4:
                    shape = 1;
                    break;
                case 5:
                    shape = 4;
                    break;
                case 6:
                    shape = -1;
                    break;
                case 7:
                    shape = -1;
                    break;
                }
                for (; !at_end(end, node); node = node->next)
                {
                    BootMorphTarget* target = (BootMorphTarget*)node;
                    if (target->unk0f == 2)
                    {
                        if (shape == *target->shape)
                        {
                            func_4C96E0(target, 100.0f);
                        }
                        else
                        {
                            func_4C96E0(target, 0.0f);
                        }
                    }
                }
            }
            else
            {
                unk74 = 0;
                for (; !at_end(end, node); node = node->next)
                {
                    BootMorphTarget* target = (BootMorphTarget*)node;
                    if (target->unk0f == 2)
                    {
                        func_4C96E0(target, 0.0f);
                    }
                }
            }
        }
        if (unk78 == 0 && func_10CE00() < 250)
        {
            unk78 = 1;
        }
        if (unk78 != 0)
        {
            BootClass170F30* face = func_473940(unkDC, D_205B18);
            BootClass170E80* end = &face->children;
            BootClass170E80* node = end->next;
            unk78++;
            for (; !at_end(end, node); node = node->next)
            {
                BootMorphTarget* target = (BootMorphTarget*)node;
                if (target->unk0f == 2 && *target->shape == 0)
                {
                    if (unk78 < 5)
                    {
                        func_4C96E0(target, 100.0f);
                    }
                    else
                    {
                        func_4C96E0(target, 0.0f);
                        unk78 = 0;
                    }
                    break;
                }
            }
        }
        {
            s32 first;
            s32 second;
            s32 turn;
            s32 fourth;
            func_11E320(D_001B65F0, 0, &first, &second, &turn, &fourth);
            unk58 -= 0.01f * (float)turn;
            unk58 = ee_max(unk58, -1.0f);
            unk58 = ee_min(unk58, 1.0f);
            if (turn == 0)
            {
                if (unk58 > 0.0f)
                {
                    unk58 -= 0.1f;
                    if (unk58 < 0.0f)
                    {
                        unk58 = 0.0f;
                    }
                }
                else if (unk58 < 0.0f)
                {
                    unk58 += 0.1f;
                    if (unk58 > 0.0f)
                    {
                        unk58 = 0.0f;
                    }
                }
            }
        }
        unk54 += 0.017453292f * (0.35f * unk58);
        if (unk54 > 6.2831855f)
        {
            unk54 -= 6.2831855f;
        }
        if (unk54 < 0.0f)
        {
            unk54 += 6.2831855f;
        }
        func_001E3FF0();
        func_001E4760();
        if (unk72 != 0)
        {
            float x;
            float y;
            func_001E4610(unk6F, &x, &y);
            place_cursor(unk144, x, y);
        }
        break;
    case 10:
    {
        func_11E020(D_001B65F0, 0, 1);
        for (s32 i = 0; i < 6; i++)
        {
            if (unk108[i] != 0)
            {
                unk108[i]->destroy();
                unk108[i] = 0;
            }
            if (unk120[i] != 0)
            {
                unk120[i]->destroy();
                unk120[i] = 0;
            }
        }
        func_10DB10(D_001B65F8, 0x8000);
        unkD8->destroy();
        unkD8 = 0;
        unkDC->destroy();
        unkDC = 0;
        unk69 = 0xFF;
        for (s32 i = 0; i < 10; i++)
        {
            if (unkE0[i] != 0)
            {
                lib_object_detach_owner(unkE0[i]);
                unkE0[i]->destroy();
                unkE0[i] = 0;
            }
        }
        D_205E10.func_001EACC0();
        unk140->destroy();
        unk140 = new (0) BootClass178750(D_205E10.get_messages(), 10, 1, 32.0f, 272.0f, 344.0f, 224.0f);
        unk140->set_color(0x34130F);
        lib_container_attach_widget(unk13C, unk140);
        func_001E4B50();
        show_value_message();
        float x;
        float y;
        func_001E5250(&x, &y);
        place_cursor(unk144, x, y);
        unk6D = 0;
        unk50 = 2;
        break;
    }
    case 11:
        if (func_103640(D_001B65E8, 0x29, 0, 0, -1, 0) != 0)
        {
            func_103B20(D_001B65E8, 0x29, 0, 0, -1, 0);
        }
        settings->unk25_mid = 0;
        D_001B6614->append_node(new (0) BootClass171CB0, -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    }

    if (unk50 > 0 && func_103640(D_001B65E8, 0x29, 0, 0, -1, 0) == 0 && unk6E < 8)
    {
        unk30[unk6E] = func_102920(D_001B65EC, unk2C, unk6E, 1);
        func_1025A0(D_001B65EC, unk2C, (void*)(((u32)unk30[unk6E] + 0x7F) & ~0x7F), unk6E);
        unk6E++;
        func_121FE0(0);
    }
    if (unk7C != 0 && --unk7C == 0)
    {
        func_11E210(D_001B65F0, 0, 0, 0);
    }
    func_001E63B0();
    func_001E5510();
}

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

/** @brief Play the opening movie with its timed captions until it ends or the player skips it. */
void BootClass171050::update()
{
    s32 offset;
    s32 fade;
    s32 is_text;
    s32 x;
    s32 y;
    BootClass171030* input = D_205E10.input;
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    s32 width;
    s32 height;
    s32 anchor;

    switch (unk14)
    {
    case 0:
        if ((input->unk16 & 8) || func_115270(D_001B65E4) != 1)
        {
            unk14 = 3;
            break;
        }
        if ((((u32)D_205E10.unk20 + 0x7F) & ~0x7F) == 0)
        {
            break;
        }
        unk30 = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
        func_465B20(D_001B657C, unk30);
        func_419A70(unk28, 12, 1);
        unk18 = 0;
        unk1C = 0;
        unk14++;
        unk20 = 0;
        break;
    case 1:
        fade = 0;
        offset = unk28->state->unk80C0 - D_205190[unk18].frame;
        if (D_205190[unk18].frame == -1)
        {
            unk14++;
            break;
        }
        if (input->unk16 & 8)
        {
            unk14 = 3;
            D_001B661C->append_node(new (0) BootClass171C00(D_205E10.unk04), -1);
        }

        is_text = D_205190[unk18].is_text;
        if (offset >= -30 && offset < 0)
        {
            fade = -offset;
            unk1C = 1;
        }
        if (offset >= 0 && offset < 90)
        {
            fade = offset;
            unk1C = 2;
        }
        if (offset >= 90 && offset < 120)
        {
            fade = offset - 90;
            unk1C = 3;
        }
        if (offset >= 120)
        {
            unk1C = 0;
            unk18++;
            if (is_text == 0)
            {
                if (unk2C != 0)
                {
                    unk2C->destroy();
                    unk2C = 0;
                }
                unk20 = 0;
            }
            else
            {
                unk34->destroy();
                unk34 = 0;
            }
            if (unk18 >= 18)
            {
                break;
            }
        }

        if (unk1C <= 0)
        {
            break;
        }

        if (is_text == 0)
        {
            width = D_205190[unk18].width;
            height = D_205190[unk18].height;
            if (unk20 == 0)
            {
                unk2C = new (0) BootImage;
                func_001FA620(unk2C, (void*)(((u32)D_205E10.unk20 + 0x7F) & ~0x7F), 0);
                func_001F9FC0(unk2C, D_205190[unk18].x, D_205190[unk18].y, width, height, 0x80808080, 0);
                unk20 = 1;
            }
        }
        else
        {
            if (unk34 == 0)
            {
                if (settings->widescreen)
                {
                    unk34 = new (0) BootClass178750(D_205E10.unk1C, D_205190[unk18].x, 1, 32.0f, 32.0f, 576.0f, 400.0f);
                    unk34->set_scale(0.75f);
                }
                else
                {
                    unk34 = new (0) BootClass178750(D_205E10.unk1C, D_205190[unk18].x, 1, 32.0f, 32.0f, 576.0f, 400.0f);
                }
                lib_container_attach_widget(unk30, unk34);
            }
            const BootTextExtent* extent = func_4C69B0(unk34);
            width = (s32)extent->width;
            height = (s32)extent->height;
        }

        anchor = D_205190[unk18].anchor;
        if (is_text == 0)
        {
            switch (anchor)
            {
            case 0:
                x = 288 - width / 2;
                y = 192 - height / 2;
                break;
            case 1:
                x = 0;
                y = 0;
                break;
            case 2:
                x = 576 - width;
                y = 0;
                break;
            case 3:
                x = 0;
                y = 384 - height;
                break;
            case 4:
                x = 576 - width;
                y = 384 - height;
                break;
            }
        }
        else
        {
            switch (anchor)
            {
            case 0:
                unk34->set_horizontal_align(1);
                unk34->set_vertical_align(1);
                break;
            case 1:
                unk34->set_horizontal_align(0);
                unk34->set_vertical_align(0);
                break;
            case 2:
                unk34->set_horizontal_align(2);
                unk34->set_vertical_align(0);
                break;
            case 3:
                unk34->set_horizontal_align(0);
                unk34->set_vertical_align(2);
                break;
            case 4:
                unk34->set_horizontal_align(2);
                unk34->set_vertical_align(2);
                break;
            }
        }

        if (is_text == 0)
        {
            unk2C->unk18->func_001E0520((float)x - 288.0f, (float)y - 192.0f, 0.0f);
            switch (unk1C)
            {
            case 1:
            {
                float alpha = (30.0f - (float)fade) / 30.0f;
                unk2C->unk18->unk6a &= ~1;
                BootVector4DDAA0 color;
                color.x = 1.0f;
                color.y = 1.0f;
                color.z = 1.0f;
                color.w = alpha;
                BootClass170F30* model = unk2C->unk18;
                copy_vector(&model->unk560, &color);
                model->func_001DDAA0();
                break;
            }
            case 2:
            {
                BootVector4DDAA0 color;
                color.x = 1.0f;
                color.y = 1.0f;
                color.z = 1.0f;
                color.w = 1.0f;
                BootClass170F30* model = unk2C->unk18;
                copy_vector(&model->unk560, &color);
                model->func_001DDAA0();
                break;
            }
            case 3:
            {
                BootVector4DDAA0 color;
                color.x = 1.0f;
                color.y = 1.0f;
                color.z = 1.0f;
                color.w = (30.0f - (float)fade) / 30.0f;
                BootClass170F30* model = unk2C->unk18;
                copy_vector(&model->unk560, &color);
                model->func_001DDAA0();
                break;
            }
            }
        }
        else
        {
            switch (unk1C)
            {
            case 1:
            case 3:
                unk34->set_alpha(128.0f * (30.0f - (float)fade) / 30.0f);
                break;
            case 2:
                unk34->set_alpha(128.0f);
                break;
            }
        }
        break;
    case 2:
        if ((input->unk16 & 8) || !unk28->unk15E794)
        {
            D_001B661C->append_node(new (0) BootClass171C00(D_205E10.unk04), -1);
            unk14 = 3;
        }
        break;
    case 3:
        func_41A210(unk28);
        if (unk2C != 0)
        {
            unk2C->destroy();
            unk2C = 0;
        }
        if (unk30 != 0)
        {
            unk30->destroy();
            unk30 = 0;
        }
        if (unk34 != 0)
        {
            unk34->destroy();
            unk34 = 0;
        }
        if (unk28 != 0)
        {
            unk28->destroy();
            unk28 = 0;
        }
        unk14++;
        break;
    case 4:
        lib_object_detach_owner(this);
        destroy();
        D_001B6614->append_node(new (0) BootClass171BB0(-1), -1);
        return;
    }
}

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

BootClass171050::BootClass171050()
{
    void* heap;
    BootResource0970* resource;
    unk14 = 0;
    unk24 = new (0) BootResident113E40;
    unk24->unk2C = 0x40;
    func_113930(unk24, 0x579F2C);
    heap = resident_exchange_allocation_heap(unk24);
    unk28 = new (0) BootClass172500(640, 448);
    resident_exchange_allocation_heap(heap);
    unk28->state->set_scale(1.0f, 1.0f);
    unk28->state->set_words(0x800, 0x800, 1);
    resource = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    if (resource->widescreen != 0)
    {
        unk28->state->unk80D8 = 1;
        D_001B6654->unk278 =
            (1.7777778f * ((1.3333334f * (1.0714285f * (float)D_205E10.unk04->unk3C60.height)) /
                (float)D_205E10.unk04->unk3C60.width)) / 1.3333334f;
        D_001B6654->unk25C = 1.8325958f;
    }
    unk30 = 0;
    unk34 = 0;
    unk2C = 0;
}

/** @brief Show the waiting popup while the resident loader is busy, and remove it once it is idle. */
void BootClass171070::update()
{
    if (unk18 == 0)
    {
        return;
    }

    if (func_115430(D_001B65E4) != 0)
    {
        if (unk1C == 0 && (((u32)program->unk10 + 0x7F) & ~0x7F) != 0)
        {
            unk1C = new (0) BootClass178660(8, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, unk1C);
            unk24 = new (0) BootClass178630(0, 64.0f, 160.0f, 520.0f, 160.0f, 88.0f);
            lib_container_attach_widget(unk1C, unk24);
            unk20 = new (0) BootClass178750(program->messages, 0x32, 0, 80.0f, 176.0f, 576.0f, 320.0f);
            lib_container_attach_widget(unk1C, unk20);
        }
    }
    else if (unk1C != 0)
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
    }
}

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

void BootClass1710B0::func_001EAA40(u8 full)
{
    BootDisplayArea3C60* area;
    delete unk04;
    unk04 = new (0) BootDimensionsACD0;
    func_4E09B0(unk04, 2);
    func_4E0BC0(unk04, 1, 1.0f, 2.0f, -1);
    func_4DD440(unk04, 0, 1, 0, 0, 1, 0, 0, 1, 640, 224);
    func_4DD440(unk04, 1, 1, 0, 0, 1, 1, 1, 1, 640, 224);
    func_4DF890(unk04, 0, 640, 224, 2, 0x31);
    func_4E03C0(unk04, 1, 640, 224);
    func_4DF6E0(unk04, 0, 0, 0, 0x81);
    area = &unk04->unk3C60;
    func_4DE250(unk04, 0, 0, 0, area->width, area->height);
    func_4DE250(unk04, 1, 0, 0, area->width, area->height);
    func_4DCFA0(unk04);
    if (full)
    {
        if (D_001B663C != (void*)0x70000000)
        {
            ::operator delete(D_001B663C);
        }
        func_4DCC10(D_001B65E0, unk04->unk3C78);
        D_001B663C = new (0) BootScratchHeap(0x20000, 0x20);
        func_4D78F0(D_001B6618);
        func_42D940();
        func_11DEE0(D_001B65F0, unk04, 1);
        D_001B6658->display = unk04;
    }
    unk38 = 0;
}

/**
 * @brief Copy the owner's stored pointer into the resident context.
 * @param object Owner containing the pointer to bind.
 */
void BootClass1710B0::func_001EACC0()
{
    D_001B6628->current_display = unk08;
}

/**
 * @brief Update projection parameters using the resource mode and stored dimensions.
 * @param object Owner containing the projection object to update.
 */
inline void BootClass1710B0::func_001EACD0()
{
    BootResource0970* resource = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    BootDimensionsACD0* dimensions;
    if (resource->widescreen != 0)
    {
        dimensions = D_205E10.unk04;
        unk08->unk278 =
            (1.7777778f * ((1.3333334f * (1.0714285f * (float)dimensions->unk3C60.height)) /
                (float)dimensions->unk3C60.width)) / 1.3333334f;
        unk08->unk250 = 0.75f;
        dimensions = D_205E10.unk04;
        D_001B6654->unk278 =
            (1.7777778f * ((1.3333334f * (1.0714285f * (float)dimensions->unk3C60.height)) /
                (float)dimensions->unk3C60.width)) / 1.3333334f;
        D_001B6654->unk25C = 1.8325958f;
    }
    else
    {
        dimensions = D_205E10.unk04;
        unk08->unk278 =
            (1.3333334f * (1.0714285f * (float)dimensions->unk3C60.height)) /
                (float)dimensions->unk3C60.width;
        unk08->unk250 = 1.0f;
        dimensions = D_205E10.unk04;
        D_001B6654->unk278 =
            (1.3333334f * (1.0714285f * (float)dimensions->unk3C60.height)) /
                (float)dimensions->unk3C60.width;
        D_001B6654->unk25C = 1.5707964f;
    }
}

void BootClass1710B0::func_001EAE80(u8 widescreen)
{
    BootDimensionsACD0* display;
    BootDisplayLinks661C* links;
    if (widescreen)
    {
        func_4DCEA0(unk04, 0, 0);
        func_101040(func_10D8E0(), 1);
    }
    else
    {
        func_4DCEA0(unk04, 0, 0);
        func_101040(func_10D8E0(), 0);
    }
    func_001EAA40(1);
    display = unk04;
    links = D_001B661C;
    links->unk4088 = display;
    D_001B6650 = display;
    if (links->unk4080 != 0)
    {
        links->unk4080->display = display;
    }
    links->unk4458->display = display;
    links->unk4460->display = display;
    links->unk4464->display = display;
    links->unk4468->display = display;
    links->unk446C->display = display;
    D_001B6520 = display;
    func_001EACD0();
}

/** @brief Decode the next of the program's three resource blocks, then destroy this object after the last. */
void BootClass171090::update()
{
    u8* buffer;
    u8* aligned;
    if (func_102D00(D_001B65E8) != 0)
    {
        if (block >= 3)
        {
            delete[] data;
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

void BootClass1710B0::func_001EB210()
{
    func_4C5B60(0, 0);
    func_001EC010(D_001B6664, 500);
    func_001EC630(D_001B6668, 500);
    func_001ECC60(D_001B666C, 500);
    func_001ED200(D_001B6670, 2000);
    func_001ED7B0(D_001B6674, 2000);
    func_001EDD60(D_001B6678, 2000);
    func_001EE250(D_001B667C, 1000);
    func_001EE760(D_001B6680, 1000);
    unk08 = new (0) BootProjectionACD0(unk04);
    func_4E14B0(unk08, unk04);
    unk08->func_001E0520(0.0f, 0.0f, -500.0f);
    D_001B6628->append_node(unk08, -1);
    D_001B6628->current_display = unk08;
    func_4DAFE0(D_001B6628, unk04, false, true, false, 2, 0xFFFFFF);
    D_001B661C->unk4084 = D_001B6624;
    D_001B6624->manager = D_001B6628;
}

/** @brief Run the boot program: set up the display and objects, run the frame loop, then shut down. */
void BootClass1710B0::run()
{
    BootClock clock;
    BootScreenRect rect;
    u8* buffer;
    s32 size;
    s32 count;
    s32 index;
    bool fresh;
    s32 previous;
    BootResource0970* settings;
    BootClass171090* loader;

    if (((BootResidentRoot15CC0*)func_10D8E0())->status == 0)
    {
        func_100F60(func_10D8E0());
    }

    func_11D9A0(func_1012C0(func_10D8E0()), &clock);
    count = (u8)(TIMER0_COUNT + (clock.hour + (clock.second + clock.minute)));
    for (index = 0; index < count; index++)
    {
        resident_next_random_word();
    }

    unk08 = 0;
    input = 0;
    unk10 = 0;
    unk04 = 0;
    unk20 = 0;
    unk24 = 0;
    unk18 = 0;
    unk2C = 0;
    unk30 = 0;
    unk28 = 0;
    unk40 = 0;
    messages = 0;
    unk1C = 0;
    unk3C = 0;

    buffer = new (0) u8[func_10CE00() + 0x40];
    size = func_11C8C0(func_1012C0(func_10D8E0()), 3);
    if (size > 0x50000)
    {
        size = 0x50000;
    }
    unk40 = func_139700(0x40, size);
    func_103E70(func_101250(func_10D8E0()), 3, unk40, 1, 0x34BC0, 0, size, 0, 1);
    delete[] buffer;

    unk34 = 0xFF;
    fresh = true;
    if (func_101440(func_101290(func_10D8E0()), 1) != 0)
    {
        unk34 = ((BootResource0970*)func_101440(func_101290(func_10D8E0()), 1))->widescreen;
        func_45A5D0();
        fresh = false;
    }

    if (D_001B6614 != 0)
    {
        func_433680();
        func_4E33B0();
        func_11ECD0(D_001B65F4);
        func_11ECD0(D_001B65F4);
    }

    func_4D8970();
    func_001EAA40(0);
    func_121890(unk04);
    func_4E3830(unk04, 0xA0013BA, 0x20000, 0x20, 0x200, 0, 0);
    rect.x = 0;
    rect.y = 0;
    rect.width = 640;
    rect.height = 224;
    func_4D8A80(&rect, 0xFFFFFF);
    D_001B6618->clear_color = 0xFFFFFF;
    func_11DEE0(D_001B65F0, unk04, 1);

    while (!func_102D00(D_001B65E8))
    {
    }

    check_main_code();
    func_45A770();
    func_001EB210();
    settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    if (unk34 != 0xFF)
    {
        settings->widescreen = unk34 != 0;
    }

    D_001B657C = new (0) BootRuntime1B657C(640.0f, 480.0f, 0, 0, 1.8f);
    unk24 = new (0) BootClass170EB0;
    D_001B6614->append_node(unk24, -1);
    unk24->func_001E1AD0();
    unk28 = new (0) BootClass171070(this);
    D_001B6614->append_node(unk28, -1);
    input = new (0) BootClass171030;
    D_001B6614->append_node(input, -1);
    loader = new (0) BootClass171090(this);
    D_001B6614->append_node(loader, -1);
    if (fresh)
    {
        D_001B6614->append_node(new (0) BootClass170ED0, -1);
    }
    else
    {
        D_001B6614->append_node(new (0) BootClass171BB0(-1), -1);
    }

    D_001B6420 = 1;
    func_001EACD0();
    unk38 = 0;
    D_001B661C->unk40CE = 0;
    D_001B6420 = 1;
    while (unk30 == 0)
    {
        func_4DD830(unk04, unk38++, D_001B65DC);
        func_4D8AC0();
        func_4D76C0(D_001B6618, 16, 16);
        func_4D4BE0(D_001B661C);
        D_001B6614->update_nodes();
        func_11F770(D_001B6618->packet, 0);
        func_11ECD0(D_001B65F4);
        func_4DCFF0(unk04, unk38);
        if (unk38 > 1)
        {
            func_4DCEA0(unk04, 1, 0);
        }
        D_001B6688 = (float)func_11DF00(D_001B65F0);
        D_001B6690 = D_001B6688 / 60.0f;
        TIMER0_COUNT = 0;
    }

    D_001B661C->unk40CE = 1;
    func_11ECD0(D_001B65F4);
    D_205E10.func_001EBCF0();
    func_11ECD0(D_001B65F4);
    func_11ECD0(D_001B65F4);

    previous = resident_next_random_word();
    while (previous == resident_next_random_word())
    {
    }
    previous = func_10CE00();
    while (previous == func_10CE00())
    {
    }
    previous = func_10CAA0(1000);
    while (previous == func_10CAA0(1000))
    {
    }
    previous = func_10CC40(0, 1000);
    while (previous == func_10CC40(0, 1000))
    {
    }

    func_1010D0(func_10D8E0(), unk30, 1);
}

void BootClass1710B0::func_001EBCF0()
{
    func_11DEE0(D_001B65F0, 0, 0);
    D_001B6420 = 0;
    func_001EC490(D_001B6664);
    func_001ECAC0(D_001B6668);
    func_001ED060(D_001B666C);
    func_001ED610(D_001B6670);
    func_001EDBC0(D_001B6674);
    func_001EE0C0(D_001B6678);
    func_001EE5C0(D_001B667C);
    func_001EEAE0(D_001B6680);
    delete unk40;
    unk40 = 0;
    if (unk28 != 0)
    {
        lib_object_detach_owner(unk28);
        unk28->destroy();
        unk28 = 0;
    }
    if (messages != 0)
    {
        lib_release_resource_slot(D_001B657C, messages);
    }
    if (unk1C != 0)
    {
        lib_release_resource_slot(D_001B657C, unk1C);
    }
    delete D_001B657C;
    D_001B657C = 0;
    if (input != 0)
    {
        lib_object_detach_owner(input);
        input->destroy();
        input = 0;
    }
    if (unk24 != 0)
    {
        unk24->destroy();
        unk24 = 0;
    }
    unk08->destroy();
    unk08 = 0;
    delete unk10;
    unk10 = 0;
    delete unk18;
    unk18 = 0;
    delete unk20;
    unk20 = 0;
    delete unk04;
    unk04 = 0;
}

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

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
s32 func_001EC010(BootTrackPool<BootClass177F70>* pool, s32 count)
{
    return pool->init(count);
}

BootClass177F70::~BootClass177F70()
{
}

BootClass177F70::BootClass177F70()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
void func_001EC490(BootTrackPool<BootClass177F70>* pool)
{
    pool->release();
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
s32 func_001EC630(BootTrackPool<BootClass1714D0>* pool, s32 count)
{
    return pool->init(count);
}

BootClass1714D0::~BootClass1714D0()
{
}

BootClass1714D0::BootClass1714D0()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
void func_001ECAC0(BootTrackPool<BootClass1714D0>* pool)
{
    pool->release();
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
s32 func_001ECC60(BootTrackPool<BootClass177EE0>* pool, s32 count)
{
    return pool->init(count);
}

BootClass177EE0::~BootClass177EE0()
{
}

BootClass177EE0::BootClass177EE0()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
void func_001ED060(BootTrackPool<BootClass177EE0>* pool)
{
    pool->release();
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
s32 func_001ED200(BootTrackPool<BootClass177C70>* pool, s32 count)
{
    return pool->init(count);
}
