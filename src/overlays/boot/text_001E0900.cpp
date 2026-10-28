#include "include_asm.h"
#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/init.h"
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
extern BootTrackPool<BootClass1711D0>* D_001B6674;
extern BootTrackPool<BootClass177BE0>* D_001B6678;
extern BootTrackPool<BootClass174440>* D_001B667C;
extern BootTrackPool<BootClass1730F0>* D_001B6680;
void func_001ED610(BootTrackPool<BootClass177C70>* pool);
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
extern const struct BootCaption g_opening_captions[];
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
extern const char g_root_node_name[];
extern const char g_look_node_name[];
extern const char g_right_speaker_name[];
extern const char g_left_speaker_name[];
extern const char g_rear_left_speaker_name[];
extern const char g_rear_right_speaker_name[];
extern const char g_center_speaker_name[];
void func_4DAFE0(BootClass178F30* manager, BootDimensionsACD0* display, bool enabled, bool first_flag, bool second_flag, s32 level, u32 mask);
extern u8 g_settings_option_counts[5];
extern u8 g_difficulty_option_count;
extern const s16 g_voice_lines[];
extern const char g_empty_name[];
extern const char g_bone_root_name[];
extern const char g_camera_node_name[];
extern const char g_face_model_name[];
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
void func_474010(BootClass175320* scene, BootDimensionsACD0* display, BootClass178DD0* list, struct BootDisplay6624* state, BootClass178F30* manager,
                 struct BootDisplayLinks661C* links, s32 flag);
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

static inline void copy_transfer_name(BootBattleTrophyCard* object, const char* base, const char* suffix);
static inline s32 prepare_transfer_request(BootBattleTrophyCard* object);
static inline void set_resource_bit(BootResourceBits0970* bits, u32 index, s32 enabled);

/**
 * @brief Clear the stored filename and copy the optional base and suffix.
 * @param object State containing the filename buffer.
 * @param base Base filename; a null pointer leaves the buffer unchanged.
 * @param suffix Optional suffix to append after the base.
 */
static inline void copy_transfer_name(BootBattleTrophyCard* object, const char* base, const char* suffix)
{
    s32 index;

    if (base != 0)
    {
        for (index = 0; index < BOOT_TRANSFER_NAME_CAPACITY; index++)
        {
            object->filename[index] = 0;
        }

        func_13C948(object->filename, base);

        if (suffix != 0)
        {
            strcat(object->filename, suffix);
        }
    }
}

/**
 * @brief Clear an allocated buffer and populate its transfer request records.
 * @param object State containing the buffer and filename storage.
 * @return 1 when the records are prepared, or 0 when no buffer is allocated.
 */
static inline s32 prepare_transfer_request(BootBattleTrophyCard* object)
{
    u8 ready;

    if (object->transfer_buffer == 0)
    {
        ready = 0;
    }
    else
    {
        func_13A678(object->transfer_buffer, 0, BOOT_TRANSFER_BUFFER_SIZE);

        if (strlen(D_205100) + 1 <= BOOT_TRANSFER_NAME_CAPACITY)
        {
            copy_transfer_name(object, D_205100, D_205980);
        }

        object->unkDD4.unk00 = object->filename;
        object->unkDD4.unk04 = object->transfer_buffer;
        object->unkDD4.unk08 = BOOT_TRANSFER_BUFFER_SIZE;
        object->unkDD4.unk0C = 0;
        object->unkDE4.unk00 = object->filename;
        object->unkDE4.unk04 = 1;
        object->unkDE4.unk08 = 0;
        object->unkDE4.unk0C = &object->unkDD4;
        ready = 1;
    }

    return ready;
}

/**
 * @brief Read the saved difficulty when the protected settings pass their checksum.
 * @param settings System settings.
 * @return Difficulty, or zero (Earth) when the checksum fails.
 */
static inline u8 settings_difficulty(BootResource0970* settings)
{
    if (settings->checksum != func_457470(settings->key, &settings->unk26, (u8*)&settings->checksum - &settings->unk26))
    {
        return 0;
    }

    return settings->difficulty;
}

/**
 * @brief Save a difficulty and reseal the protected settings, unless their checksum is already broken.
 * @param settings System settings.
 * @param value Difficulty to save.
 */
static inline void settings_set_difficulty(BootResource0970* settings, u8 value)
{
    s32 length = (u8*)&settings->checksum - &settings->unk26;

    if (settings->checksum == func_457470(settings->key, &settings->unk26, length))
    {
        settings->difficulty = value;
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
 * @brief Check whether Universe difficulty is unlocked, trusting the flag only when its checksum passes.
 * @param settings System settings.
 * @return The unlock flag, or zero when the checksum fails.
 */
static inline u8 settings_universe_unlocked(BootResource0970* settings)
{
    u8* data = &settings->unk1A0;

    if (settings->extra_checksum != func_457470(settings->extra_key, data, (u8*)&settings->extra_checksum - data))
    {
        return 0;
    }

    return settings->universe_unlocked;
}

/**
 * @brief Check whether 4D difficulty is unlocked, trusting the flag only when its checksum passes.
 * @param settings System settings.
 * @return The unlock flag, or zero when the checksum fails.
 */
static inline u8 settings_fourth_dimension_unlocked(BootResource0970* settings)
{
    u8* data = &settings->unk1A0;

    if (settings->extra_checksum != func_457470(settings->extra_key, data, (u8*)&settings->extra_checksum - data))
    {
        return 0;
    }

    return settings->fourth_dimension_unlocked;
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

/** @brief Report the list kind used when registration requests the default. @return Two. */
s32 BootBattleTrophyCard::get_default_list_kind()
{
    return 2;
}

/**
 * @brief Report which card slots hold a ready card.
 * @return Bit 0 for slot 1 and bit 1 for slot 2; zero while the card object is busy.
 */
u16 BootBattleTrophyCard::get_ready_slots()
{
    BootModeOwner0910* owner = card;
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

/** @brief Apply transferred flags and header values, copy the payload, and release its buffer. */
void BootBattleTrophyCard::func_001E0970()
{
    u8 saved_bits[BOOT_TRANSFER_FLAG_BYTES];
    s32 index;
    u8* saved;
    BootResourceBits0970* bits;

    if (transfer_buffer != 0)
    {
        saved = (u8*)transfer_buffer + 0x4B4;
        bits = &settings->unk1A8;
        func_13A678(saved_bits, 0, BOOT_TRANSFER_FLAG_BYTES);
        func_13A4C0(saved_bits, saved, BOOT_TRANSFER_FLAG_BYTES);

        for (index = 0; index < BOOT_TRANSFER_FLAG_COUNT; index++)
        {
            set_resource_bit(bits, index, saved_bits[index / 8] & (1 << (index % 8)));
        }

        bits->unk14 = *(u32*)transfer_buffer;
        func_13A4C0(bits->unk18, saved + BOOT_TRANSFER_FLAG_BYTES, 8);
        func_13A4C0(unkDC8, (u8*)transfer_buffer + 0x4E2, 0x11A6C0);

        if (transfer_buffer != 0)
        {
            delete[] transfer_buffer;
            transfer_buffer = 0;
        }
    }
}

/** @brief Return the stored signed request result. @return The stored value. */
s32 BootBattleTrophyCard::func_001E0AD0()
{
    return unkDD0;
}

/** @brief Return the signed 16-bit value at offset 0xDCE. @return The stored value. */
s16 BootBattleTrophyCard::func_001E0AE0()
{
    return unkDCE;
}

/**
 * @brief Advance the stored two-phase request and update its completion state.
 * @return Narrowed request status, or -1 when the phase is unsupported.
 */
s16 BootBattleTrophyCard::func_001E0AF0()
{
    s16 result = -1;

    switch (unkDC0)
    {
    case 0:
        unkDF9 = 1;
        result = func_432310(card, unkDCC, &unkDE4);

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
        result = func_432270(card, unkDCC, &unkDD0);

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

/**
 * @brief Initialize the buffer and request records for a selected transfer mode.
 * @param mode Transfer mode 0 or 1.
 * @param destination Nonnull destination for the transfer.
 * @return 1 when prepared, or 0 for invalid arguments or allocation failure.
 */
s32 BootBattleTrophyCard::func_001E0C30(u16 mode, void* destination)
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
    slot = unkDCC;
    unk1E = 0;

    if (transfer_buffer == 0)
    {
        transfer_buffer = new (0) u8[BOOT_TRANSFER_BUFFER_SIZE];
    }

    ready = prepare_transfer_request(this);

    if (!ready)
    {
        return 0;
    }

    unkDF9 = 0;
    return 1;
}

/**
 * @brief Store mode 1 or 2 and reset the state for selector 0.
 * @param mode Mode to store; values other than 1 or 2 have no effect.
 */
void BootBattleTrophyCard::func_001E0DE0(u8 mode)
{
    if (mode == 1 || mode == 2)
    {
        unkD34 = mode;
        reset_slot(0);
    }
}

/**
 * @brief Drop a pending transfer and go back to waiting for the card.
 * @param object Memory card object.
 */
static inline void cancel_transfer(BootBattleTrophyCard* object)
{
    object->unkDCE = 1;
    object->unkDD0 = -12;
    object->unkDCC = -1;
    object->unkDC0 = -1;
    object->unk1C = 1;
    object->unkDF9 = 0;
    object->unkDF8 = 0;
}

/** @brief Advance the memory card state for the current mode. */
void BootBattleTrophyCard::update()
{
    s32 progress;
    s32 status;
    u8 done;

    if (card != 0 && card->unk20 != 0)
    {
        status = unk1A;

        if (unk1E == 0)
        {
            status = card->unk14[slot].unk48;

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

                unk20 = card->unk14[slot].unk50;

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

                unk24 = card->unk14[slot].unk4C;

                if (unk20 == 0 && unkD34 == 1)
                {
                    unk24 = 8000;
                }

                unkDFC[slot] = unk24;
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

                status = func_431F90(card, slot, filename, 0, 1, unkD30);

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
                status = func_432270(card, slot, &progress);

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

                status = func_431F90(card, slot, filename, 0, 1, unkDBC);

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
                status = func_432270(card, slot, &progress);

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
                        reset_slot(0);
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
static inline u8 state_mode_value(BootBattleTrophyCard* object, u16 mode)
{
    if (mode != 0 && mode != 1)
    {
        return 0;
    }

    return object->unkD37[mode];
}

/**
 * @brief Query a slot's state byte, resetting slot 0 when its reset flag is set.
 * @param mode Slot 0 or 1 to query; other values return zero without a reset.
 * @param kind Select guarded values with 1, or the direct mode byte otherwise.
 * @return The selected byte before any reset.
 */
u16 BootBattleTrophyCard::get_slot_state(u16 mode, u16 kind)
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
        reset_slot(0);
    }

    return value;
}

/**
 * @brief Apply an event to the selected mode and update its reset and completion flags.
 * @param enabled Process the event when this byte equals 1.
 * @param event Event code or direct byte status to store.
 * @param kind Classify the event with 1, or store its byte status with 2.
 */
void BootBattleTrophyCard::func_001E1500(u8 enabled, u16 event, u16 kind)
{
    u8 ready;

    if (enabled == 1)
    {
        if (slot == 1)
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

        if (slot == 0)
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
                        reset_slot(1);
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
                            reset_slot(1);
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
                        reset_slot(1);
                    }
                }
            }
            else if (kind == 2)
            {
                unkD37[0] = event;
                unkD35[0] = 1;
                reset_slot(1);
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

/**
 * @brief Select an event's byte status and update the current mode's stored status.
 * @param event Event code to classify.
 * @param result Byte receiving the selected status, initially cleared to zero.
 */
void BootBattleTrophyCard::func_001E17C0(u16 event, u8* result)
{
    s32 value;

    *result = 0;
    if (unkD34 == 1)
    {
        value = unkDFC[slot];

        switch (event)
        {
        case 15:
            *result = 15;
            break;
        case 2:
            unkE04[slot] = 10;
            break;
        case 16:
            if (unk20 == 0)
            {
                *result = 16;
            }
            else
            {
                unkE04[slot] = 16;
            }

            break;
        case 17:
            unkE04[slot] = 17;
            break;
        case 6:
            if (unkE04[slot] == 17)
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

                *result = unkE04[slot];
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
            if (unkE04[slot] == 17)
            {
                *result = 17;
            }
            else
            {
                if (value < 0 || value > 8000)
                {
                    *result = 15;
                }

                *result = unkE04[slot];
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

/**
 * @brief Select a slot and reset its fields along with the shared state.
 * @param mode Slot 0 or 1 to select; other values reset only the shared state.
 */
void BootBattleTrophyCard::reset_slot(s16 mode)
{
    s32 selected = mode;
    slot = mode;
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

/**
 * @brief Create the memory card object for both slots and prepare the transfer buffer.
 * @return 1 when initialized, or 0 when the card object, settings or buffer is unavailable.
 */
s32 BootBattleTrophyCard::initialize()
{
    BootModeOwner0910* owner;
    u8 ready;

    owner = new (0) BootModeOwner0910;
    card = owner;

    if (card == 0)
    {
        return 0;
    }

    func_432720(card, D_001B6614);
    func_432660(card, 0, 0, 0);
    func_432660(card, 1, 1, 0);
    unk1C = 0;
    reset_slot(0);
    settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);

    if (settings == 0)
    {
        return 0;
    }

    if (transfer_buffer == 0)
    {
        transfer_buffer = new (0) u8[BOOT_TRANSFER_BUFFER_SIZE];
    }

    ready = prepare_transfer_request(this);

    if (!ready)
    {
        return 0;
    }

    return 1;
}

/** @brief Release the transfer buffer and the memory card object, then queue this object for deletion. */
void BootBattleTrophyCard::destroy()
{
    if (transfer_buffer != 0)
    {
        delete[] transfer_buffer;
        transfer_buffer = 0;
    }

    if (card != 0)
    {
        card->destroy();
    }

    func_11ED90(D_001B65F4, this);
}

/** @brief Clear the transfer state, both modes, and the filename. */
BootBattleTrophyCard::BootBattleTrophyCard()
{
    s32 index;
    card = 0;
    unk1C = -1;
    slot = -1;
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
    transfer_buffer = 0;
    unkDCC = -1;
    unkDD0 = -1;
    unkDCE = -1;
    unkDC8 = 0;
    settings = 0;
    unkDF8 = 0;

    for (index = 0; index < BOOT_TRANSFER_NAME_CAPACITY; index++)
    {
        filename[index] = 0;
    }

    unkDF9 = 0;
    unkDFC[0] = -1;
    unkE04[0] = -1;
    unkDFC[1] = -1;
    unkE04[1] = -1;
}

/** @brief Destroy the object. */
BootStartupChecks::~BootStartupChecks()
{
}

/**
 * @brief Hang when the main executable's code no longer matches the copy in the program image.
 */
static inline void check_main_code()
{
    // Uncached cursor; the code it checks starts 0x400000 bytes (0x80000 words) below it.
    u64* code = (u64*)(0x20000000 | 0x500000);
    u64* copy = (u64*)(g_boot_program.image->code_offset + (u32)g_boot_program.image);
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
 * @brief Read the PlayStation BB Unit's state: one when it isn't initialized, two when it's ready.
 * @param resident Resident loader.
 * @return Unit state, or three when the loader has no unit information.
 */
static inline u8 unit_state(BootResident1B65E4* resident)
{
    return resident->unk12184 != 0 ? resident->unk141 : 3;
}

/** @brief Run the memory card, progressive display and BB Unit screens in turn, then start the opening movie. */
void BootStartupChecks::update()
{
    BootResource0970* settings;
    BootInput* input;
    s32 slot1;
    s32 slot2;
    u8 finished;
    u8 again;

    if (func_115430(D_001B65E4) != 0)
    {
        return;
    }

    settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    input = g_boot_program.input;
    slot1 = input->slot1_state;
    slot2 = input->slot2_state;

    if (screen == BOOT_STARTUP_CARD_CHECK)
    {
        switch (step)
        {
        case 0:
            if ((((u32)g_boot_program.message_block + 0x7F) & ~0x7F) != 0)
            {
                check_main_code();
                D_001B657C->message_value = 175;

                if ((u32)(slot1 - 16) <= 1 || (u32)(slot2 - 16) <= 1 || (slot1 == 11 && slot2 == 12) || (slot1 == 11 && slot2 == 14) ||
                    (slot1 == 12 && slot2 == 11) || (slot1 == 12 && slot2 == 12) || (slot1 == 12 && slot2 == 13) || (slot1 == 12 && slot2 == 14) ||
                    (slot1 == 13 && slot2 == 12) || (slot1 == 13 && slot2 == 14) || (slot1 == 14 && slot2 == 11) || (slot1 == 14 && slot2 == 12) ||
                    (slot1 == 14 && slot2 == 13))
                {
                    screen = BOOT_STARTUP_PROGRESSIVE;
                    step = 0;
                    return;
                }

                if (slot1 == 15 && slot2 == 15)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_NO_CARD;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 15 && slot2 == 10)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 15 && slot2 == 11)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 15 && slot2 == 12)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 15 && slot2 == 13)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_NO_TROPHY_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 15 && slot2 == 14)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_NO_SAVE_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 10 && slot2 == 15)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 10 && slot2 == 10)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 10 && slot2 == 11)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 10 && slot2 == 12)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 10 && slot2 == 13)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 10 && slot2 == 14)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_SAVE_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 11 && slot2 == 15)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 11 && slot2 == 10)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 11 && slot2 == 11)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 11 && slot2 == 13)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 12 && slot2 == 15)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 12 && slot2 == 10)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 13 && slot2 == 15)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_NO_TROPHY_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 13 && slot2 == 10)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 13 && slot2 == 11)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 13 && slot2 == 13)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 14 && slot2 == 15)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_NO_SAVE_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 14 && slot2 == 10)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_SAVE_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == 14 && slot2 == 14)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_SAVE_SPACE;
                    step = 1;
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }
            }

            break;
        case 1:
            check_main_code();
            container = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, container);
            text = new (0) BootClass178750(g_boot_program.get_messages(), message, 0, 32.0f, 128.0f, 576.0f, 320.0f);
            lib_container_attach_widget(container, text);
            step = 2;
            break;
        case 2:
        {
            u16 pressed = input->pressed;

            if (pressed & settings->unk00)
            {
                check_main_code();
                screen = BOOT_STARTUP_PROGRESSIVE;
                step = 0;
                text->destroy();
                text = 0;
                container->destroy();
                container = 0;
                func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            }
            else if (pressed & settings->unk02)
            {
                text->destroy();
                text = 0;
                container->destroy();
                container = 0;
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                step = 0;
            }
            else if (shown_slot1 != slot1 || shown_slot2 != slot2)
            {
                text->destroy();
                text = 0;
                container->destroy();
                container = 0;
                input->clear_card_states();
                step = 0;
            }

            break;
        }
        }
    }
    else if (screen == BOOT_STARTUP_PROGRESSIVE)
    {
        finished = 0;

        do
        {
            switch (step)
            {
            case 0:
                again = 0;
                check_main_code();

                if ((input->held & 0x1000) && (input->held & 0x4000))
                {
                    step++;
                    container = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
                    func_465B20(D_001B657C, container);
                }
                else if (++frames >= 30 && (((u32)g_boot_program.message_block + 0x7F) & ~0x7F) != 0)
                {
                    finished = 1;
                }

                break;
            case 1:
                again = 0;

                if ((((u32)g_boot_program.message_block + 0x7F) & ~0x7F) != 0)
                {
                    check_main_code();
                    text = new (0) BootClass178750(g_boot_program.get_messages(), BOOT_MSG_PROGRESSIVE_OFFER, 0, 32.0f, 96.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(container, text);
                    step++;
                }

                break;
            case 2:
                again = 0;
                check_main_code();

                if (input->pressed & settings->unk00)
                {
                    step++;
                    frames = 0;
                    text->destroy();
                    text = 0;
                    func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                    settings->widescreen = BOOT_STARTUP_PROGRESSIVE;
                }
                else if (input->pressed & settings->unk04)
                {
                    step++;
                    frames = 0;
                    text->destroy();
                    text = 0;
                    func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                    settings->widescreen = 0;
                }
                else if (input->pressed & settings->unk02)
                {
                    func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                    finished = 1;
                }

                break;
            case 3:
                again = 0;
                check_main_code();

                if (++frames > 10)
                {
                    g_boot_program.set_progressive(1);
                    frames = 0;
                    step++;
                }

                break;
            case 4:
                again = 0;
                check_main_code();

                if (++frames > 60)
                {
                    step++;

                    if (settings->widescreen)
                    {
                        text = new (0) BootClass178750(g_boot_program.get_messages(), BOOT_MSG_PROGRESSIVE_WIDE_STARTED, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                        text->set_scale(0.75f);
                    }
                    else
                    {
                        text = new (0) BootClass178750(g_boot_program.get_messages(), BOOT_MSG_PROGRESSIVE_NORMAL_STARTED, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                    }

                    lib_container_attach_widget(container, text);
                    frames = 0;
                }

                break;
            case 5:
                again = 0;
                check_main_code();

                if (input->pressed & settings->unk00)
                {
                    finished = 1;
                    func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                }
                else if (++frames > 539 || (input->pressed & settings->unk02))
                {
                    text->destroy();
                    text = 0;
                    step++;
                    frames = 0;
                    func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                }

                break;
            case 6:
                check_main_code();
                again = 0;

                if (++frames > 10)
                {
                    settings->widescreen = 0;
                    g_boot_program.set_progressive(0);
                    step++;
                    frames = 0;
                }

                break;
            case 7:
                check_main_code();
                again = 0;

                if (++frames > 60)
                {
                    step = 1;
                    frames = 0;
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
            step = 0;

            if (text != 0)
            {
                text->destroy();
                text = 0;
            }

            if (container != 0)
            {
                container->destroy();
                container = 0;
            }

            screen = BOOT_STARTUP_UNIT_CHECK;
        }
    }
    else
    {
        finished = 0;

        do
        {
            switch (step)
            {
            case 0:
                again = 0;
                check_main_code();

                if (unit_state(D_001B65E4) != 2)
                {
                    if (unit_state(D_001B65E4) == 1)
                    {
                        step++;
                        container = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
                        func_465B20(D_001B657C, container);
                    }
                    else if (g_boot_program.unit_data_deleted != 0)
                    {
                        step = 3;
                        container = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
                        func_465B20(D_001B657C, container);
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

                if ((((u32)g_boot_program.message_block + 0x7F) & ~0x7F) != 0)
                {
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    text = new (0) BootClass178750(g_boot_program.get_messages(), BOOT_MSG_UNIT_NOT_INITIALIZED, 0, 32.0f, 96.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(container, text);
                    step++;
                }

                break;
            case 2:
                check_main_code();
                again = 0;

                if (input->pressed & settings->unk00)
                {
                    func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                    finished = 1;
                }

                break;
            case 3:
                again = 0;

                if ((((u32)g_boot_program.message_block + 0x7F) & ~0x7F) != 0)
                {
                    func_112400(D_001B65F8, 8, 0, 0, 0x7F, 0x40, 0);
                    text = new (0) BootClass178750(g_boot_program.get_messages(), BOOT_MSG_UNIT_DATA_DELETED, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(container, text);
                    step = 2;
                }

                break;
            default:
                again = 0;
                break;
            }
        } while (again);

        if (finished)
        {
            if (container != 0)
            {
                container->destroy();
                container = 0;
            }

            if (text != 0)
            {
                text->destroy();
                text = 0;
            }

            lib_object_detach_owner(this);
            destroy();
            D_001B6614->append_node(new (0) BootOpeningMovie, -1);
        }
    }
}

/** @brief Start on the memory card check. */
BootStartupChecks::BootStartupChecks()
{
    step = 0;
    frames = 0;
    screen = 0;
    container = 0;
    text = 0;
}

/** @brief Report the list kind used when registration requests the default. @return Four. */
s32 BootNewGameSettings::get_default_list_kind()
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

/** @brief Move the girl to her angle around the listener with her lean, then step her walk animations. */
void BootNewGameSettings::place_girl()
{
    BootVector4DDAA0 position;
    BootVector4DDAA0 angles;
    BootMatrix92D0 matrix;
    FieldVec4B target;
    FieldVec4B rotation;
    FieldVec4B roll;
    BootVector4DDAA0 axis;
    BootVector4DDAA0 offset;
    float angle = girl_angle;
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
    axis.w = girl_lean;
    func_4CD810(&roll, &axis);
    rotation = multiply_rotations(roll, rotation);

    if (turn_speed == 0.0f)
    {
        if (girl_lean > 0.0f)
        {
            girl_lean -= 3.1415927f * D_001B6690;
            girl_lean = ee_max_in_place(0.0f, girl_lean);
        }
        else
        {
            girl_lean += 3.1415927f * D_001B6690;
            girl_lean = ee_min(0.0f, girl_lean);
        }
    }
    else if (turn_speed < 0.0f)
    {
        girl_lean += 9.424778f * D_001B6690;
        girl_lean = ee_min(1.5707964f, girl_lean);
    }
    else
    {
        girl_lean -= 9.424778f * D_001B6690;
        girl_lean = ee_max(-1.5707964f, girl_lean);
    }

    BootClass178A90* root = func_473530(girl_scene, g_root_node_name);
    root->func_001E0510(&position);
    root->func_001E0670((BootVector4DDAA0*)&rotation);

    bool again = true;

    while (again)
    {
        switch (walk_state)
        {
        case 0:
            if (turn_speed != 0.0f)
            {
                animation_frame = 0.0f;
                girl_animations[1]->unk6A = 0;
                walk_state = 1;
            }
            else if (func_4B4550(girl_animations[0], animation_frame, 2) > 0)
            {
                animation_frame = 0.0f;
            }
            else
            {
                again = false;
            }

            break;
        case 1:
            if (func_4B4550(girl_animations[1], animation_frame, 2) > 0)
            {
                if (turn_speed == 0.0f)
                {
                    animation_frame = 0.0f;
                    girl_animations[5]->unk6A = 0;
                    walk_state = 5;
                }
                else
                {
                    animation_frame = 0.0f;
                    girl_animations[2]->unk6A = 0;
                    walk_state = 2;
                }
            }
            else
            {
                again = false;
            }

            break;
        case 2:
            if (func_4B4550(girl_animations[2], animation_frame, 2) > 0)
            {
                if (turn_speed == 0.0f)
                {
                    animation_frame = 0.0f;
                    girl_animations[4]->unk6A = 0;
                    walk_state = 4;
                }
                else
                {
                    animation_frame = 0.0f;
                    girl_animations[3]->unk6A = 0;
                    walk_state = 3;
                }
            }
            else
            {
                again = false;
            }

            break;
        case 3:
            if (func_4B4550(girl_animations[3], animation_frame, 2) > 0)
            {
                if (turn_speed == 0.0f)
                {
                    animation_frame = 0.0f;
                    girl_animations[5]->unk6A = 0;
                    walk_state = 5;
                }
                else
                {
                    animation_frame = 0.0f;
                    girl_animations[2]->unk6A = 0;
                    walk_state = 2;
                }
            }
            else
            {
                again = false;
            }

            break;
        case 4:
            if (func_4B4550(girl_animations[4], animation_frame, 2) > 0)
            {
                girl_animations[0]->unk6A = 0;
                animation_frame = 0.0f;
                walk_state = 0;
            }
            else
            {
                again = false;
            }

            break;
        case 5:
            if (func_4B4550(girl_animations[5], animation_frame, 2) > 0)
            {
                girl_animations[0]->unk6A = 0;
                animation_frame = 0.0f;
                walk_state = 0;
            }
            else
            {
                again = false;
            }

            break;
        }
    }

    switch (walk_state)
    {
    case 0:
    case 4:
    case 5:
        animation_frame += D_001B6688;
        break;
    case 1:
    case 2:
    case 3:
    {
        float step;

        if (turn_speed == 0.0f)
        {
            step = 1.0f;
        }
        else
        {
            step = ee_max(0.5f, abs_float(turn_speed));
        }

        animation_frame += step;
        break;
    }
    }

    void* look = func_473390(girl_scene, g_look_node_name);

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
 * @brief Read the cursor position for a speaker on the speaker setup screen.
 * @param speaker Speaker index.
 * @param x Receives the horizontal position.
 * @param y Receives the vertical position.
 */
void BootNewGameSettings::get_speaker_cursor_position(s32 speaker, float* x, float* y)
{
    BootClass170F30* speakers[4];
    BootVector4DDAA0 position;
    BootVector4DDAA0 screen;
    speakers[0] = func_473940(room_scene, g_right_speaker_name);
    speakers[1] = func_473940(room_scene, g_left_speaker_name);
    speakers[2] = func_473940(room_scene, g_rear_left_speaker_name);
    speakers[3] = func_473940(room_scene, g_rear_right_speaker_name);
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

/** @brief Place the five speaker models around the listener and pulse the one being moved. */
void BootNewGameSettings::place_speakers()
{
    BootClass170F30* speakers[5];
    speakers[0] = func_473940(room_scene, g_right_speaker_name);
    speakers[1] = func_473940(room_scene, g_left_speaker_name);
    speakers[2] = func_473940(room_scene, g_rear_left_speaker_name);
    speakers[3] = func_473940(room_scene, g_rear_right_speaker_name);
    speakers[4] = func_473940(room_scene, g_center_speaker_name);

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

    if (adjusting_speaker != 0)
    {
        for (s32 i = 0; i < 4; i++)
        {
            if (i == selected_speaker)
            {
                BootVector4DDAA0 scale;
                copy_vector(&scale, &speakers[i]->unk560);

                if (adjusting_speaker == 1)
                {
                    scale.x += 2.0f * D_001B6690;
                    scale.y += 2.0f * D_001B6690;
                    scale.z += 2.0f * D_001B6690;

                    if (!(scale.x <= 2.0f))
                    {
                        scale.x = 2.0f;
                        scale.y = 2.0f;
                        scale.z = 2.0f;
                        adjusting_speaker = 2;
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
                        adjusting_speaker = 1;
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

/** @brief Select the option that matches the current page's saved setting. */
void BootNewGameSettings::load_option_value()
{
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);

    switch (page)
    {
    case BOOT_SETTINGS_TV_MODE:
        if (settings->widescreen != 0)
        {
            selection = 1;
        }
        else
        {
            selection = 0;
        }

        break;
    case BOOT_SETTINGS_SOUND:
        switch (D_001B65F8->output_mode)
        {
        case 1:
            selection = 0;
            break;
        case 0:
            selection = 1;
            break;
        case 2:
            selection = 2;
            break;
        case 3:
            selection = 3;
            break;
        }

        break;
    case BOOT_SETTINGS_EVENT_SKIP:
        selection = !settings->event_skip;
        break;
    case BOOT_SETTINGS_VOICE:
        selection = settings->voice_mode;
        break;
    case BOOT_SETTINGS_VIBRATION:
        selection = !settings->vibration;
        break;
    case BOOT_SETTINGS_DIFFICULTY:
        selection = settings_difficulty(settings);
        break;
    }
}

/** @brief Save the selected option for the current page and apply it to the display, sound or pad. */
void BootNewGameSettings::apply_option_value()
{
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);

    switch (page)
    {
    case BOOT_SETTINGS_TV_MODE:
        switch (selection)
        {
        case 0:
            settings->widescreen = 0;
            D_001B6654->unk278 = (1.3333334f * (1.0714285f * (float)g_boot_program.display->unk3C60.height)) / (float)g_boot_program.display->unk3C60.width;
            D_001B6654->unk25C = 1.5707964f;
            g_boot_program.update_projection_aspect();
            break;
        case 1:
            settings->widescreen = 1;
            D_001B6654->unk278 =
                (1.7777778f * ((1.3333334f * (1.0714285f * (float)g_boot_program.display->unk3C60.height)) / (float)g_boot_program.display->unk3C60.width)) /
                1.3333334f;
            D_001B6654->unk25C = 1.8325958f;
            g_boot_program.update_projection_aspect();
            break;
        }

        break;
    case BOOT_SETTINGS_SOUND:
        switch (selection)
        {
        case 0:
            func_10DA70(D_001B65F8, 1);
            settings->sound_output = 0;
            break;
        case 1:
            func_10DA70(D_001B65F8, 0);
            settings->sound_output = 1;
            break;
        case 2:
            func_10DA70(D_001B65F8, 2);
            settings->sound_output = 2;
            break;
        case 3:
            func_10DA70(D_001B65F8, 3);
            settings->sound_output = 3;
            break;
        }

        break;
    case BOOT_SETTINGS_EVENT_SKIP:
        switch (selection)
        {
        case 0:
            settings->event_skip = 1;
            break;
        case 1:
            settings->event_skip = 0;
            break;
        }

        break;
    case BOOT_SETTINGS_VOICE:
        settings->voice_mode = selection;
        break;
    case BOOT_SETTINGS_VIBRATION:
        switch (selection)
        {
        case 0:
            settings->vibration = 1;
            func_11E030(D_001B65F0, 0, 1);
            func_11E210(D_001B65F0, 0, 1, 0x40);
            rumble_frames = 10;
            break;
        case 1:
            settings->vibration = 0;
            func_11E030(D_001B65F0, 0, 0);
            break;
        }

        break;
    case BOOT_SETTINGS_DIFFICULTY:
        settings_set_difficulty(settings, selection);
        break;
    }
}

/**
 * @brief Pick the message that describes the selected option.
 * @return Message key, or zero for an unknown page.
 */
s32 BootNewGameSettings::get_value_message()
{
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);

    switch (page)
    {
    case BOOT_SETTINGS_TV_MODE:
        return selection + BOOT_MSG_TV_NORMAL;
    case BOOT_SETTINGS_SOUND:
        if (selection == 3)
        {
            return BOOT_MSG_SOUND_HEADPHONES;
        }

        return selection + BOOT_MSG_SOUND_MONO;
    case BOOT_SETTINGS_EVENT_SKIP:
        return selection + BOOT_MSG_EVENT_SKIP_ON;
    case BOOT_SETTINGS_VOICE:
        if (selection == 3)
        {
            return BOOT_MSG_VOICE_AUTO;
        }

        return selection + BOOT_MSG_VOICE_SUBTITLES_AND_SOUND;
    case BOOT_SETTINGS_VIBRATION:
        return selection + BOOT_MSG_VIBRATION_ON;
    case BOOT_SETTINGS_DIFFICULTY:
        if (selection == 3)
        {
            if (settings_fourth_dimension_unlocked(settings))
            {
                return BOOT_MSG_FOURTH_DIMENSION;
            }

            return BOOT_MSG_FOURTH_DIMENSION_LOCKED;
        }

        if (settings_universe_unlocked(settings) && selection == 2)
        {
            return BOOT_MSG_UNIVERSE_UNLOCKED;
        }

        return selection + BOOT_MSG_DIFFICULTY_EARTH;
    }

    return 0;
}

/**
 * @brief Read the cursor position for the selected row of the current page.
 * @param x Receives the horizontal position.
 * @param y Receives the vertical position; unchanged for an unknown row.
 */
void BootNewGameSettings::get_cursor_position(float* x, float* y)
{
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);

    *x = 58.0f;
    switch (page)
    {
    case BOOT_SETTINGS_SOUND:
        switch (selection)
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
    case BOOT_SETTINGS_VOICE:
        switch (selection)
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
    case BOOT_SETTINGS_DIFFICULTY:
        if (settings_universe_unlocked(settings))
        {
            switch (selection)
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
            switch (selection)
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
        switch (selection)
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
static inline void set_model_color(BootClass177820* model, float red, float green, float blue, float alpha)
{
    BootVector4DDAA0 color;
    color.x = red;
    color.y = green;
    color.z = blue;
    color.w = alpha;
    copy_vector(&model->unk560, &color);
    model->func_001DDAA0();
}

/** @brief Rebuild the current page's option rows when the page changes, then place and highlight them. */
void BootNewGameSettings::update_option_rows()
{
    BootResource0970* settings;

    if (image_blocks[4] != 0 && on_speaker_setup == 0)
    {
        settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);

        if (shown_page != page)
        {
            shown_page = page;

            for (s32 i = 0; i < 4; i++)
            {
                if (images[16 + i] != 0)
                {
                    lib_object_detach_owner(images[16 + i]);
                    images[16 + i]->destroy();
                    images[16 + i] = 0;
                }

                images[16 + i] = new (0) BootImage;
            }

            switch (page)
            {
            case BOOT_SETTINGS_TV_MODE:
                row_x = -272.0f;
                func_001FA620(images[16], (void*)(((u32)image_blocks[3] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[16], 0, 8, 288, 40, 0x80808080, 0);
                images[16]->unk18->func_001E0520(-272.0f, -142.0f, 0.0f);
                func_001FA620(images[17], (void*)(((u32)image_blocks[3] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[17], 0, 68, 288, 40, 0x80808080, 0);
                images[17]->unk18->func_001E0520(-272.0f, -74.0f, 0.0f);
                break;
            case BOOT_SETTINGS_SOUND:
                row_x = -272.0f;
                func_001FA620(images[16], (void*)(((u32)image_blocks[3] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[16], 0, 106, 288, 40, 0x80808080, 0);
                images[16]->unk18->func_001E0520(-272.0f, -162.0f, 0.0f);
                func_001FA620(images[17], (void*)(((u32)image_blocks[3] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[17], 0, 162, 200, 40, 0x80808080, 0);
                images[17]->unk18->func_001E0520(-272.0f, -126.0f, 0.0f);
                func_001FA620(images[18], (void*)(((u32)image_blocks[3] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[18], 0, 236, 424, 40, 0x80808080, 0);
                images[18]->unk18->func_001E0520(-272.0f, -90.0f, 0.0f);
                func_001FA620(images[19], (void*)(((u32)image_blocks[3] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[19], 224, 168, 237, 38, 0x80808080, 0);
                images[19]->unk18->func_001E0520(-272.0f, -55.0f, 0.0f);
                break;
            case BOOT_SETTINGS_EVENT_SKIP:
                row_x = -272.0f;
                func_001FA620(images[16], (void*)(((u32)image_blocks[3] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[16], 0, 312, 340, 40, 0x80808080, 0);
                images[16]->unk18->func_001E0520(-272.0f, -142.0f, 0.0f);
                func_001FA620(images[17], (void*)(((u32)image_blocks[3] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[17], 0, 368, 340, 40, 0x80808080, 0);
                images[17]->unk18->func_001E0520(-272.0f, -74.0f, 0.0f);
                break;
            case BOOT_SETTINGS_VOICE:
                row_x = -260.0f;
                func_001FA620(images[16], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[16], 0, 0, 340, 40, 0x80808080, 0);
                images[16]->unk18->func_001E0520(-260.0f, -142.0f, 0.0f);
                func_001FA620(images[17], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[17], 0, 55, 340, 40, 0x80808080, 0);
                images[17]->unk18->func_001E0520(-260.0f, -102.0f, 0.0f);
                func_001FA620(images[18], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[18], 0, 110, 340, 40, 0x80808080, 0);
                images[18]->unk18->func_001E0520(-260.0f, -62.0f, 0.0f);
                func_001FA620(images[19], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[19], 0, 416, 500, 40, 0x80808080, 0);
                images[19]->unk18->func_001E0520(-260.0f, -22.0f, 0.0f);
                break;
            case BOOT_SETTINGS_VIBRATION:
                row_x = -254.0f;
                func_001FA620(images[16], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[16], 0, 160, 340, 40, 0x80808080, 0);
                images[16]->unk18->func_001E0520(-272.0f, -142.0f, 0.0f);
                func_001FA620(images[17], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                func_001F9FC0(images[17], 0, 215, 340, 40, 0x80808080, 0);
                images[17]->unk18->func_001E0520(-272.0f, -74.0f, 0.0f);
                break;
            case BOOT_SETTINGS_DIFFICULTY:
                row_x = -260.0f;

                if (!settings_universe_unlocked(settings))
                {
                    func_001FA620(images[16], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                    func_001F9FC0(images[16], 0, 257, 340, 42, 0x80808080, 0);
                    images[16]->unk18->func_001E0520(-260.0f, -142.0f, 0.0f);
                    func_001FA620(images[17], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                    func_001F9FC0(images[17], 0, 313, 340, 42, 0x80808080, 0);
                    images[17]->unk18->func_001E0520(-260.0f, -92.0f, 0.0f);
                    func_001FA620(images[18], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                    func_001F9FC0(images[18], 0, 369, 340, 42, 0x80808080, 0);
                    images[18]->unk18->func_001E0520(-260.0f, -42.0f, 0.0f);
                }
                else
                {
                    func_001FA620(images[16], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                    func_001F9FC0(images[16], 3, 257, 340, 42, 0x80808080, 0);
                    images[16]->unk18->func_001E0520(-260.0f, -142.0f, 0.0f);
                    func_001FA620(images[17], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                    func_001F9FC0(images[17], 3, 313, 340, 42, 0x80808080, 0);
                    images[17]->unk18->func_001E0520(-260.0f, -102.0f, 0.0f);
                    func_001FA620(images[18], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                    func_001F9FC0(images[18], 3, 369, 340, 42, 0x80808080, 0);
                    images[18]->unk18->func_001E0520(-260.0f, -62.0f, 0.0f);
                    func_001FA620(images[19], (void*)(((u32)image_blocks[4] + 0x7F) & ~0x7F), 0);
                    func_001F9FC0(images[19], 0, 466, 340, 42, 0x80808080, 0);
                    images[19]->unk18->func_001E0520(-260.0f, -24.0f, 0.0f);
                }

                break;
            }
        }

        if (settings->widescreen)
        {
            for (s32 i = 0; i < 4; i++)
            {
                if (images[16 + i] != 0 && images[16 + i]->unk18 != 0)
                {
                    BootVector4DDAA0 position;
                    copy_vector(&position, &images[16 + i]->unk18->unk20);
                    position.x = 8.0f + 1.3333334f * row_x;
                    images[16 + i]->unk18->func_001E0510(&position);
                }
            }
        }
        else
        {
            for (s32 i = 0; i < 4; i++)
            {
                if (images[16 + i] != 0 && images[16 + i]->unk18 != 0)
                {
                    BootVector4DDAA0 position;
                    copy_vector(&position, &images[16 + i]->unk18->unk20);
                    position.x = row_x;
                    images[16 + i]->unk18->func_001E0510(&position);
                }
            }
        }

        s32 i;
        BootClass177820* model;
        // TODO: My guess; the original reads the extra block through a pointer formed before the loop.
        u8* extra = &settings->unk1A0;

        for (i = 0; i < 4; i++)
        {
            if (images[16 + i] == 0)
            {
                continue;
            }

            model = images[16 + i]->unk18;

            if (model == 0)
            {
                continue;
            }

            if (i == 2 && page == BOOT_SETTINGS_DIFFICULTY)
            {
                if (!settings_extra_byte(settings, extra, &settings->universe_unlocked))
                {
                    set_model_color(model, 0.5f, 0.5f, 0.5f, 1.0f);
                    continue;
                }
            }

            if (i == 3 && page == BOOT_SETTINGS_DIFFICULTY)
            {
                if (!settings_extra_byte(settings, extra, &settings->fourth_dimension_unlocked))
                {
                    set_model_color(model, 0.5f, 0.5f, 0.5f, 1.0f);
                    continue;
                }
            }

            if (selection == i)
            {
                BootVector4DDAA0 scale;
                copy_vector(&scale, &model->unk560);

                if (highlight_phase == 0)
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
                        highlight_phase = 1;
                    }
                }
                else if (highlight_phase != 0)
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
                        highlight_phase = 0;
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
void BootNewGameSettings::update_page_images()
{
    BootResource0970* settings;
    BootLabelOffsets offsets;

    if (image_blocks[4] == 0)
    {
        return;
    }

    if (images[0] == 0)
    {
        images[0] = new (0) BootImage;
        func_001FA620(images[0], (void*)(((u32)image_blocks[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[0], 0, 1, 0x1E8, 0xDF, 0x80808080, 0);
        images[0]->unk18->func_001E0520(-244.0f, -112.0f, 0.0f);
    }

    if (images[1] == 0)
    {
        images[1] = new (0) BootImage;
        func_001FA620(images[1], (void*)(((u32)image_blocks[1] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[1], 0, 0, 0x280, 0x50, 0x80808080, 0);
        images[1]->unk18->func_001E0520(-320.0f, -216.0f, 0.0f);
    }

    if (images[2] == 0 && on_speaker_setup == 0)
    {
        images[2] = new (0) BootImage;
        func_001FA620(images[2], (void*)(((u32)image_blocks[0] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[2], 0x1A, 0xF5, 0x18, 0x16, 0x80808080, 0);

        for (s32 i = 0; i < 6; i++)
        {
            images[3 + i] = new (0) BootImage;
            func_001FA620(images[3 + i], (void*)(((u32)image_blocks[0] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(images[3 + i], 0x52, 0xF3 + i * 29, 0xEE, 0x1C, 0x80808080, 0);
        }
    }

    if (images[9] == 0)
    {
        for (s32 i = 0; i < 6; i++)
        {
            images[9 + i] = new (0) BootImage;
            func_001FA620(images[9 + i], (void*)(((u32)image_blocks[2] + 0x7F) & ~0x7F), 0);
            func_001F9FC0(images[9 + i], 0, 2 + i * 32, 0x180, 0x20, 0x80808080, 0);
        }
    }

    if (images[15] == 0 && on_speaker_setup == 0)
    {
        images[15] = new (0) BootImage;
        func_001FA620(images[15], (void*)(((u32)image_blocks[2] + 0x7F) & ~0x7F), 0);
        func_001F9FC0(images[15], 0, 0xC2, 0x180, 0x20, 0x80808080, 0);
    }

    settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);

    if (settings->widescreen)
    {
        if (images[1] != 0)
        {
            images[1]->unk18->func_001E0520(-414.66669f, -216.0f, 0.0f);
            images[1]->unk18->func_001DDED0(1.31f, 1.0f, 1.0f);
        }

        for (s32 i = 0; i < 6; i++)
        {
            if (images[3 + i] != 0)
            {
                images[3 + i]->unk18->func_001E0520(160.0f, 30.0f + (float)(i * 29), 0.0f);
            }

            if (images[9 + i] != 0)
            {
                images[9 + i]->unk18->func_001E0520(21.0f, -204.0f, 0.0f);
            }
        }

        if (images[15] != 0)
        {
            images[15]->unk18->func_001E0520(-426.66669f, 170.0f, 0.0f);
        }
    }
    else
    {
        if (images[1] != 0)
        {
            images[1]->unk18->func_001E0520(-320.0f, -216.0f, 0.0f);
            images[1]->unk18->func_001DDED0(1.0f, 1.0f, 1.0f);
        }

        for (s32 i = 0; i < 6; i++)
        {
            if (images[3 + i] != 0)
            {
                images[3 + i]->unk18->func_001E0520(56.0f, 30.0f + (float)(i * 29), 0.0f);
            }

            if (images[9 + i] != 0)
            {
                images[9 + i]->unk18->func_001E0520(-80.0f, -204.0f, 0.0f);
            }
        }

        if (images[15] != 0)
        {
            images[15]->unk18->func_001E0520(-320.0f, 170.0f, 0.0f);
        }
    }

    offsets = D_205170;

    for (s32 i = 0; i < 6; i++)
    {
        if (page == i)
        {
            if (images[3 + i] != 0)
            {
                BootVector4DDAA0 color;
                color.x = 1.0f;
                color.y = 1.0f;
                color.z = 1.0f;
                color.w = 1.0f;
                BootClass177820* model = images[3 + i]->unk18;
                copy_vector(&model->unk560, &color);
                model->func_001DDAA0();
            }

            if (images[2] != 0)
            {
                if (settings->widescreen)
                {
                    images[2]->unk18->func_001E0520(142.0f + 1.3333334f * (float)offsets.values[i], (float)(31.0 + 29.0 * i), 0.0f);
                }
                else
                {
                    images[2]->unk18->func_001E0520(44.0f + (float)offsets.values[i], (float)(31.0 + 29.0 * i), 0.0f);
                }
            }

            if (images[9 + i] != 0)
            {
                images[9 + i]->unk18->unk6a &= ~1;
            }
        }
        else
        {
            if (images[3 + i] != 0)
            {
                BootVector4DDAA0 color;
                color.x = 0.5f;
                color.y = 0.5f;
                color.z = 0.5f;
                color.w = 1.0f;
                BootClass177820* model = images[3 + i]->unk18;
                copy_vector(&model->unk560, &color);
                model->func_001DDAA0();
            }

            if (images[9 + i] != 0)
            {
                images[9 + i]->unk18->unk6a |= 1;
            }
        }
    }

    if (images[15] != 0)
    {
        if (page == BOOT_SETTINGS_DIFFICULTY)
        {
            images[15]->unk18->unk6a |= 1;
        }
        else
        {
            images[15]->unk18->unk6a &= ~1;
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
    BootClass171C00* fade = new (0) BootClass171C00(g_boot_program.display);
    fade->unkd0 = 2.0f;
    D_001B661C->append_node(fade, -1);
}

/** @brief Show the message that describes the selected option. */
inline void BootNewGameSettings::show_value_message()
{
    lib_text_set_resource(description_text, g_boot_program.get_messages(), get_value_message(), 0);
}

/**
 * @brief Test buttons pressed this frame against a mask.
 * @param input Pad input.
 * @param mask Buttons to test.
 * @return Nonzero when any of them was pressed.
 */
static inline s32 button_pressed(BootInput* input, u16 mask)
{
    return input->pressed & mask;
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

/** @brief Run the current page or the speaker setup, then stream the next model block and place the rows. */
void BootNewGameSettings::update()
{
    BootInput* input = g_boot_program.input;
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    u8 extra = settings_extra_byte(settings, &settings->unk1A0, &settings->universe_unlocked);
    g_difficulty_option_count = extra ? 4 : 3;

    switch (stage)
    {
    case BOOT_SETTINGS_STAGE_LOAD:
        if (func_102D00(D_001B65E8) != 0)
        {
            func_112990(D_001B65F8, 0x48, 1, 0, 0);
            func_103E70(D_001B65E8, 0x29, model_data, 1, 0x34BC0, 0, 0, 0, 1);
            func_4DF6E0(g_boot_program.display, 0x49, 0x47, 0x9D, 0x7F);
            D_001B661C->prepend_node(new (0) BootClass179150, -1);
            loaded_image_blocks = 0;
            stage++;
            highlight_phase = 0;
            container = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, container);
            description_text = new (0) BootClass178750(g_boot_program.get_messages(), BOOT_MSG_TV_NORMAL, 1, 32.0f, 272.0f, 344.0f, 224.0f);
            description_text->set_color(0x34130F);
            lib_container_attach_widget(container, description_text);
            load_option_value();
            show_value_message();
            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor = new (0) BootClass175070;
            func_467570(cursor, 1, 0, 0xF42400, x, y, 0.0f);
            func_465B20(D_001B657C, cursor);
            func_10DAA0(D_001B65F8, 2);
        }

        break;
    case BOOT_SETTINGS_STAGE_LOAD_IMAGES:
        image_blocks[loaded_image_blocks] = func_102920(D_001B65EC, image_data, loaded_image_blocks, 1);
        func_1025A0(D_001B65EC, image_data, (void*)(((u32)image_blocks[loaded_image_blocks] + 0x7F) & ~0x7F), loaded_image_blocks);

        if (++loaded_image_blocks >= 5)
        {
            stage++;
            shown_page = 0xFF;
            func_121FE0(0);
        }

        break;
    case BOOT_SETTINGS_STAGE_PAGE:
        if (input->repeated == 0x40 && cursor->unk35)
        {
            selection = (selection + 1) % g_settings_option_counts[page];
            apply_option_value();
            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor->func_00466E40(x, y, 0.05f);
            highlight_phase = 0;
            func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
            show_value_message();
        }

        if (input->repeated == 0x10 && cursor->unk35)
        {
            u8 count = g_settings_option_counts[page];
            selection = (selection + count - 1) % count;
            highlight_phase = 0;
            apply_option_value();
            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor->func_00466E40(x, y, 0.05f);
            func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
            show_value_message();
        }

        if (button_pressed(input, settings->unk00))
        {
            if (selection == 2 && page == BOOT_SETTINGS_DIFFICULTY && !settings_extra_byte(settings, &settings->unk1A0, &settings->universe_unlocked))
            {
                func_112400(D_001B65F8, 3, 0, 0, 0x7F, 0x40, 0);
                break;
            }

            if (selection == 3 && page == BOOT_SETTINGS_DIFFICULTY && !settings_extra_byte(settings, &settings->unk1A0, &settings->fourth_dimension_unlocked))
            {
                func_112400(D_001B65F8, 3, 0, 0, 0x7F, 0x40, 0);
                break;
            }

            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            stage = BOOT_SETTINGS_STAGE_NEXT_PAGE;
        }
        else if (button_pressed(input, settings->unk02))
        {
            if (page == BOOT_SETTINGS_TV_MODE)
            {
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                func_10F000(D_001B65F8, 0x1E, -1);
                stage = BOOT_SETTINGS_STAGE_EXIT;
                break;
            }
            else
            {
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                stage = BOOT_SETTINGS_STAGE_PREVIOUS_PAGE;
            }
        }

        if (button_pressed(input, settings->unk04) && page == BOOT_SETTINGS_SOUND && selection == 2)
        {
            func_112400(D_001B65F8, 4, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            stage = BOOT_SETTINGS_STAGE_ENTER_SPEAKERS;
        }

        break;
    case BOOT_SETTINGS_STAGE_EXIT:
        func_4DF6E0(g_boot_program.display, 0, 0, 0, 0x7F);

        if (func_103640(D_001B65E8, 0x29, 0, 0, -1, 0) != 0)
        {
            func_103B20(D_001B65E8, 0x29, 0, 0, -1, 0);
        }

        for (s32 i = 0; i < 21; i++)
        {
            if (images[i] != 0)
            {
                lib_object_detach_owner(images[i]);
                images[i]->destroy();
                images[i] = 0;
            }
        }

        if (container != 0)
        {
            container->destroy();
            container = 0;
        }

        if (description_text != 0)
        {
            description_text->destroy();
            description_text = 0;
        }

        if (cursor != 0)
        {
            cursor->destroy();
            cursor = 0;
        }

        D_001B6614->append_node(new (0) BootClass171BB0(0), -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    case BOOT_SETTINGS_STAGE_NEXT_PAGE:
        if (++page > BOOT_SETTINGS_DIFFICULTY)
        {
            func_4DF6E0(g_boot_program.display, 0, 0, 0, 0x7F);
            func_10F000(D_001B65F8, 0x1E, -1);
            stage = BOOT_SETTINGS_STAGE_START_GAME;
        }
        else
        {
            load_option_value();
            float x;
            float y;
            get_cursor_position(&x, &y);
            place_cursor(cursor, x, y);
            show_value_message();
            stage = BOOT_SETTINGS_STAGE_PAGE;
        }

        break;
    case BOOT_SETTINGS_STAGE_PREVIOUS_PAGE:
    {
        page--;
        load_option_value();
        float x;
        float y;
        get_cursor_position(&x, &y);
        place_cursor(cursor, x, y);
        show_value_message();
        stage = BOOT_SETTINGS_STAGE_PAGE;
        break;
    }
    case BOOT_SETTINGS_STAGE_ENTER_SPEAKERS:
        on_speaker_setup = 1;
        description_text->destroy();
        description_text = 0;
        stage = BOOT_SETTINGS_STAGE_BUILD_SPEAKERS;

        for (s32 i = 2; i < 9; i++)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
            images[i] = 0;
        }

        images[15]->destroy();
        lib_object_detach_owner(images[15]);
        images[15] = 0;

        for (s32 i = 16; i < 20; i++)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
            images[i] = 0;
        }

        break;
    case BOOT_SETTINGS_STAGE_BUILD_SPEAKERS:
        if (loaded_model_blocks == 8)
        {
            func_11E020(D_001B65F0, 0, 0);
            room_scene = new (0) BootClass175320;
            func_479190(room_scene, (void*)(((u32)model_blocks[0] + 0x7F) & ~0x7F));
            func_474010(room_scene, g_boot_program.display, D_001B6614, D_001B6624, D_001B6628, D_001B661C, 1);
            girl_scene = new (0) BootClass175320;
            func_479190(girl_scene, (void*)(((u32)model_blocks[1] + 0x7F) & ~0x7F));
            func_474010(girl_scene, g_boot_program.display, D_001B6614, D_001B6624, D_001B6628, D_001B661C, 1);
            s32 count = 0;

            for (BootClass170F30* model = func_473940(girl_scene, g_empty_name); model != 0; model = func_472EB0(girl_scene, model))
            {
                if (model->unk6c == 0x100)
                {
                    girl_models[count] = new (0) BootClass170F30;
                    girl_models[count]->func_4A37C0(D_001B661C, model);
                    girl_models[count++]->unk208 = model->unk208;
                }
            }

            for (s32 i = 0; i < 6; i++)
            {
                girl_animations[i] = new (0) BootClass178220;
                girl_animations[i]->set_resource((void*)(((u32)model_blocks[2 + i] + 0x7F) & ~0x7F));
                func_4BF100(girl_animations[i], girl_scene, 0);
                animation_targets[i] = new (0) BootClass178370;
                func_4BDB50(girl_animations[i], animation_targets[i], g_bone_root_name);
                func_4B3DE0(girl_animations[i], animation_targets[i]);
            }

            D_001B661C->prepend_node(new (0) BootClass179150, -1);
            D_001B6628->current_display = func_473680(room_scene, g_camera_node_name);
            girl_angle = 1.5707964f;
            animation_frame = 0.0f;
            turn_speed = 0.0f;
            walk_state = 0;
            girl_lean = 0.0f;
            blink_frame = 0;
            adjusting_speaker = 0;
            func_10EA70(D_001B65F8, func_473530(room_scene, g_root_node_name), 0.0f, 500.0f);
            description_text = new (0) BootClass178750(g_boot_program.get_messages(), BOOT_MSG_SPEAKER_SETUP, 1, 32.0f, 352.0f, 576.0f, 112.0f);
            description_text->set_color(0x34130F);
            lib_container_attach_widget(container, description_text);
            place_girl();
            selected_speaker = 0;
            voice_count = 0;
            place_speakers();
            func_10DB10(D_001B65F8, 10000);
            stage++;
        }

        break;
    case BOOT_SETTINGS_STAGE_SHOW_SPEAKERS:
    {
        float x;
        float y;
        get_speaker_cursor_position(0, &x, &y);
        place_cursor(cursor, x, y);
        stage++;
        voice_line = 0;
        break;
    }
    case BOOT_SETTINGS_STAGE_SPEAKERS:
        if (input->repeated & 0xC0)
        {
            if (adjusting_speaker == 0)
            {
                if (cursor->unk35)
                {
                    selected_speaker = (selected_speaker + 1) & 3;
                    float x;
                    float y;
                    get_speaker_cursor_position(selected_speaker, &x, &y);
                    cursor->func_00466E40(x, y, 0.05f);
                    highlight_phase = 0;
                    func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
                }
            }
            else
            {
                float turned = speaker_angle(D_001B65F8, selected_speaker);
                float angle = turned;
                turned += 1.5707964f * D_001B6690;

                if (turned >= 6.2831855f)
                {
                    turned -= 6.2831855f;
                }

                float upper = speaker_angle(D_001B65F8, (selected_speaker + 1) & 3) - 0.2617994f;
                float lower = 0.2617994f + speaker_angle(D_001B65F8, (selected_speaker - 1) & 3);

                if (angle < turned)
                {
                    if (selected_speaker == 0 && angle <= 1.3089969f && turned > 1.3089969f)
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

                func_10EA90(D_001B65F8, selected_speaker, turned);
                settings->speaker_angles[selected_speaker] = turned;
            }
        }

        if (input->repeated & 0x30)
        {
            if (adjusting_speaker == 0)
            {
                if (cursor->unk35)
                {
                    selected_speaker = (selected_speaker + 3) & 3;
                    float x;
                    float y;
                    get_speaker_cursor_position(selected_speaker, &x, &y);
                    cursor->func_00466E40(x, y, 0.05f);
                    func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
                }
            }
            else
            {
                float turned = speaker_angle(D_001B65F8, selected_speaker);
                float angle = turned;
                turned -= 1.5707964f * D_001B6690;

                if (turned < 0.0f)
                {
                    turned += 6.2831855f;
                }

                float upper = speaker_angle(D_001B65F8, (selected_speaker + 1) & 3) - 0.2617994f;
                float lower = 0.2617994f + speaker_angle(D_001B65F8, (selected_speaker - 1) & 3);

                if (angle > turned)
                {
                    if (selected_speaker == 1 && angle >= 1.8325948f && turned < 1.8325957f)
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

                func_10EA90(D_001B65F8, selected_speaker, turned);
                settings->speaker_angles[selected_speaker] = turned;
            }
        }

        if (button_pressed(input, settings->unk04))
        {
            s32 line = func_10CAA0(9);

            if (voice_count < 12)
            {
                voice_count++;
            }
            else
            {
                line += 9;
            }

            if (voice_line != 0)
            {
                func_110920(D_001B65F8, voice_line, 0);
                voice_line = 0;
            }

            voice_line = func_111C50(D_001B65F8, g_voice_lines[line], func_473530(girl_scene, g_root_node_name), 0, 0x7F, 0);
        }

        if (button_pressed(input, settings->unk00))
        {
            if (adjusting_speaker == 0)
            {
                func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                adjusting_speaker = 1;
                saved_speaker_angle = speaker_angle(D_001B65F8, selected_speaker);
            }
            else
            {
                func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
                adjusting_speaker = 0;
            }
        }

        if (button_pressed(input, settings->unk02))
        {
            if (adjusting_speaker == 0)
            {
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                stage = BOOT_SETTINGS_STAGE_LEAVE_SPEAKERS;
            }
            else
            {
                func_112400(D_001B65F8, 2, 0, 0, 0x7F, 0x40, 0);
                func_10EA90(D_001B65F8, selected_speaker, saved_speaker_angle);
                settings->speaker_angles[selected_speaker] = saved_speaker_angle;
                adjusting_speaker = 0;
                place_speakers();
                float x;
                float y;
                get_speaker_cursor_position(selected_speaker, &x, &y);
                place_cursor(cursor, x, y);
            }
        }

        if ((input->pressed & 9) && adjusting_speaker == 0)
        {
            func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            func_10DA30(D_001B65F8);
            place_speakers();

            for (s32 i = 0; i < 4; i++)
            {
                settings->speaker_angles[i] = speaker_angle(D_001B65F8, i);
            }

            float x;
            float y;
            get_speaker_cursor_position(selected_speaker, &x, &y);
            place_cursor(cursor, x, y);
        }

        if (voice_line != 0)
        {
            BootClass170F30* face = func_473940(girl_scene, g_face_model_name);
            BootClass170E80* end = &face->children;
            BootClass170E80* node = end->next;

            if (func_110C10(D_001B65F8, voice_line) != 0)
            {
                s32 shape;

                switch (func_10E310(D_001B65F8, voice_line, 2.0f))
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
                voice_line = 0;

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

        if (blink_frame == 0 && func_10CE00() < 250)
        {
            blink_frame = 1;
        }

        if (blink_frame != 0)
        {
            BootClass170F30* face = func_473940(girl_scene, g_face_model_name);
            BootClass170E80* end = &face->children;
            BootClass170E80* node = end->next;
            blink_frame++;

            for (; !at_end(end, node); node = node->next)
            {
                BootMorphTarget* target = (BootMorphTarget*)node;

                if (target->unk0f == 2 && *target->shape == 0)
                {
                    if (blink_frame < 5)
                    {
                        func_4C96E0(target, 100.0f);
                    }
                    else
                    {
                        func_4C96E0(target, 0.0f);
                        blink_frame = 0;
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
            turn_speed -= 0.01f * (float)turn;
            turn_speed = ee_max(turn_speed, -1.0f);
            turn_speed = ee_min(turn_speed, 1.0f);

            if (turn == 0)
            {
                if (turn_speed > 0.0f)
                {
                    turn_speed -= 0.1f;

                    if (turn_speed < 0.0f)
                    {
                        turn_speed = 0.0f;
                    }
                }
                else if (turn_speed < 0.0f)
                {
                    turn_speed += 0.1f;

                    if (turn_speed > 0.0f)
                    {
                        turn_speed = 0.0f;
                    }
                }
            }
        }

        girl_angle += 0.017453292f * (0.35f * turn_speed);

        if (girl_angle > 6.2831855f)
        {
            girl_angle -= 6.2831855f;
        }

        if (girl_angle < 0.0f)
        {
            girl_angle += 6.2831855f;
        }

        place_girl();
        place_speakers();

        if (adjusting_speaker != 0)
        {
            float x;
            float y;
            get_speaker_cursor_position(selected_speaker, &x, &y);
            place_cursor(cursor, x, y);
        }

        break;
    case BOOT_SETTINGS_STAGE_LEAVE_SPEAKERS:
    {
        func_11E020(D_001B65F0, 0, 1);

        for (s32 i = 0; i < 6; i++)
        {
            if (girl_animations[i] != 0)
            {
                girl_animations[i]->destroy();
                girl_animations[i] = 0;
            }

            if (animation_targets[i] != 0)
            {
                animation_targets[i]->destroy();
                animation_targets[i] = 0;
            }
        }

        func_10DB10(D_001B65F8, 0x8000);
        room_scene->destroy();
        room_scene = 0;
        girl_scene->destroy();
        girl_scene = 0;
        shown_page = 0xFF;

        for (s32 i = 0; i < 10; i++)
        {
            if (girl_models[i] != 0)
            {
                lib_object_detach_owner(girl_models[i]);
                girl_models[i]->destroy();
                girl_models[i] = 0;
            }
        }

        g_boot_program.select_projection();
        description_text->destroy();
        description_text = new (0) BootClass178750(g_boot_program.get_messages(), BOOT_MSG_TV_NORMAL, 1, 32.0f, 272.0f, 344.0f, 224.0f);
        description_text->set_color(0x34130F);
        lib_container_attach_widget(container, description_text);
        load_option_value();
        show_value_message();
        float x;
        float y;
        get_cursor_position(&x, &y);
        place_cursor(cursor, x, y);
        on_speaker_setup = 0;
        stage = BOOT_SETTINGS_STAGE_PAGE;
        break;
    }
    case BOOT_SETTINGS_STAGE_START_GAME:
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

    if (stage > BOOT_SETTINGS_STAGE_LOAD && func_103640(D_001B65E8, 0x29, 0, 0, -1, 0) == 0 && loaded_model_blocks < 8)
    {
        model_blocks[loaded_model_blocks] = func_102920(D_001B65EC, model_data, loaded_model_blocks, 1);
        func_1025A0(D_001B65EC, model_data, (void*)(((u32)model_blocks[loaded_model_blocks] + 0x7F) & ~0x7F), loaded_model_blocks);
        loaded_model_blocks++;
        func_121FE0(0);
    }

    if (rumble_frames != 0 && --rumble_frames == 0)
    {
        func_11E210(D_001B65F0, 0, 0, 0);
    }

    update_page_images();
    update_option_rows();
}

/** @brief Release the loaded data and owned objects. */
BootNewGameSettings::~BootNewGameSettings()
{
    delete image_data;
    delete model_data;

    for (s32 i = 0; i < 5; i++)
    {
        delete image_blocks[i];
    }

    for (s32 i = 0; i < 8; i++)
    {
        delete model_blocks[i];
    }

    for (s32 i = 0; i < 21; i++)
    {
        if (images[i] != 0)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
        }
    }

    for (s32 i = 0; i < 10; i++)
    {
        if (girl_models[i] != 0)
        {
            lib_object_detach_owner(girl_models[i]);
            girl_models[i]->destroy();
        }
    }

    for (s32 i = 0; i < 6; i++)
    {
        if (girl_animations[i] != 0)
        {
            girl_animations[i]->destroy();
        }

        if (animation_targets[i] != 0)
        {
            animation_targets[i]->destroy();
        }
    }

    if (room_scene != 0)
    {
        room_scene->destroy();
    }

    if (girl_scene != 0)
    {
        girl_scene->destroy();
    }

    if (container != 0)
    {
        container->destroy();
    }

    if (description_text != 0)
    {
        description_text->destroy();
    }

    if (cursor != 0)
    {
        cursor->destroy();
    }

    if (rumble_frames != 0)
    {
        func_11E210(D_001B65F0, 0, 0, 0);
    }

    D_001B65AC = 0;
}

/** @brief Start loading the page images and the speaker setup scenes, and clear the owned objects. */
BootNewGameSettings::BootNewGameSettings()
{
    BootResource0970* resource;
    image_data = func_139700(0x40, func_11C8C0(D_001B65E4, 0x28));
    func_103E70(D_001B65E8, 0x28, image_data, 1, 0x34BC0, 0, 0, 0, 1);
    model_data = func_139700(0x40, func_11C8C0(D_001B65E4, 0x29));
    stage = BOOT_SETTINGS_STAGE_LOAD;

    for (s32 i = 0; i < 5; i++)
    {
        image_blocks[i] = 0;
    }

    for (s32 i = 0; i < 21; i++)
    {
        images[i] = 0;
    }

    for (s32 i = 0; i < 8; i++)
    {
        model_blocks[i] = 0;
    }

    for (s32 i = 0; i < 6; i++)
    {
        girl_animations[i] = 0;
        animation_targets[i] = 0;
    }

    for (s32 i = 0; i < 10; i++)
    {
        girl_models[i] = 0;
    }

    container = 0;
    description_text = 0;
    cursor = 0;
    room_scene = 0;
    girl_scene = 0;
    on_speaker_setup = 0;
    rumble_frames = 0;
    D_001B65AC = &unk138;
    page = 0;
    loaded_model_blocks = 0;
    resource = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);

    switch (D_001B65F8->output_mode)
    {
    case 1:
        resource->sound_output = 0;
        break;
    case 0:
        resource->sound_output = 1;
        break;
    case 2:
        resource->sound_output = 2;
        break;
    case 3:
        resource->sound_output = 3;
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

/** @brief Virtual slot 5. @return Always 0. */
s32 BootInput::func_001E9640()
{
    return 0;
}

/** @brief Forget the memory card states so the next query starts fresh. */
void BootInput::clear_card_states()
{
    slot1_state = 0;
    slot2_state = 0;
    unk28 = 0;
    unk2C = 0;
    slot1_ready = 0;
    slot2_ready = 0;
}

/** @brief Sample the first pad, then keep the latest nonzero state of each memory card slot. */
void BootInput::update()
{
    BootBattleTrophyCard* trophy_card;
    u16 slot1;
    u16 slot2;
    u16 third;
    u16 fourth;
    u16 ready;
    held = func_11E010(D_001B65F0, 0);
    pressed = func_11DFF0(D_001B65F0, 0);
    unk1A = func_11E000(D_001B65F0, 0);
    repeated = func_11DFB0(D_001B65F0, 0);
    func_11DF90(D_001B65F0, 0);
    trophy_card = g_boot_program.trophy_card;

    if (card_query_enabled != 0)
    {
        slot1 = trophy_card->get_slot_state(0, 1);
        slot2 = trophy_card->get_slot_state(1, 1);
        third = trophy_card->get_slot_state(0, 2);
        fourth = trophy_card->get_slot_state(1, 2);
        ready = trophy_card->get_ready_slots();

        if (slot1 != 0)
        {
            slot1_state = slot1;
        }

        if (slot2 != 0)
        {
            slot2_state = slot2;
        }

        if (third != 0)
        {
            unk28 = third;
        }

        if (fourth != 0)
        {
            unk2C = fourth;
        }

        if (ready & 1)
        {
            slot1_ready = 1;
        }
        else
        {
            slot1_ready = 0;
        }

        if (ready & 2)
        {
            slot2_ready = 1;
        }
        else
        {
            slot2_ready = 0;
        }
    }
}

/** @brief Clear the card states and start querying the cards. */
BootInput::BootInput()
{
    slot1_state = 0;
    slot2_state = 0;
    unk28 = 0;
    unk2C = 0;
    slot1_ready = 0;
    slot2_ready = 0;
    card_query_enabled = 1;
}

/** @brief Play the opening movie with its timed captions until it ends or the player skips it. */
void BootOpeningMovie::update()
{
    s32 offset;
    s32 fade;
    s32 is_text;
    s32 x;
    s32 y;
    BootInput* input = g_boot_program.input;
    BootResource0970* settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    s32 width;
    s32 height;
    s32 anchor;

    switch (step)
    {
    case 0:
        if ((input->held & 8) || func_115270(D_001B65E4) != 1)
        {
            step = 3;
            break;
        }

        if ((((u32)g_boot_program.image_block + 0x7F) & ~0x7F) == 0)
        {
            break;
        }

        container = new (0) BootClass178660(9, 0.0f, 0.0f, 0.0f);
        func_465B20(D_001B657C, container);
        func_419A70(player, 12, 1);
        caption = 0;
        caption_phase = 0;
        step++;
        caption_image_loaded = 0;
        break;
    case 1:
        fade = 0;
        offset = player->state->unk80C0 - g_opening_captions[caption].frame;

        if (g_opening_captions[caption].frame == -1)
        {
            step++;
            break;
        }

        if (input->held & 8)
        {
            step = 3;
            D_001B661C->append_node(new (0) BootClass171C00(g_boot_program.display), -1);
        }

        is_text = g_opening_captions[caption].is_text;

        if (offset >= -30 && offset < 0)
        {
            fade = -offset;
            caption_phase = 1;
        }

        if (offset >= 0 && offset < 90)
        {
            fade = offset;
            caption_phase = 2;
        }

        if (offset >= 90 && offset < 120)
        {
            fade = offset - 90;
            caption_phase = 3;
        }

        if (offset >= 120)
        {
            caption_phase = 0;
            caption++;

            if (is_text == 0)
            {
                if (caption_image != 0)
                {
                    caption_image->destroy();
                    caption_image = 0;
                }

                caption_image_loaded = 0;
            }
            else
            {
                caption_text->destroy();
                caption_text = 0;
            }

            if (caption >= 18)
            {
                break;
            }
        }

        if (caption_phase <= 0)
        {
            break;
        }

        if (is_text == 0)
        {
            width = g_opening_captions[caption].width;
            height = g_opening_captions[caption].height;

            if (caption_image_loaded == 0)
            {
                caption_image = new (0) BootImage;
                func_001FA620(caption_image, (void*)(((u32)g_boot_program.image_block + 0x7F) & ~0x7F), 0);
                func_001F9FC0(caption_image, g_opening_captions[caption].x, g_opening_captions[caption].y, width, height, 0x80808080, 0);
                caption_image_loaded = 1;
            }
        }
        else
        {
            if (caption_text == 0)
            {
                if (settings->widescreen)
                {
                    caption_text = new (0) BootClass178750(g_boot_program.captions, g_opening_captions[caption].x, 1, 32.0f, 32.0f, 576.0f, 400.0f);
                    caption_text->set_scale(0.75f);
                }
                else
                {
                    caption_text = new (0) BootClass178750(g_boot_program.captions, g_opening_captions[caption].x, 1, 32.0f, 32.0f, 576.0f, 400.0f);
                }

                lib_container_attach_widget(container, caption_text);
            }

            const BootTextExtent* extent = func_4C69B0(caption_text);
            width = (s32)extent->width;
            height = (s32)extent->height;
        }

        anchor = g_opening_captions[caption].anchor;

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
                caption_text->set_horizontal_align(1);
                caption_text->set_vertical_align(1);
                break;
            case 1:
                caption_text->set_horizontal_align(0);
                caption_text->set_vertical_align(0);
                break;
            case 2:
                caption_text->set_horizontal_align(2);
                caption_text->set_vertical_align(0);
                break;
            case 3:
                caption_text->set_horizontal_align(0);
                caption_text->set_vertical_align(2);
                break;
            case 4:
                caption_text->set_horizontal_align(2);
                caption_text->set_vertical_align(2);
                break;
            }
        }

        if (is_text == 0)
        {
            caption_image->unk18->func_001E0520((float)x - 288.0f, (float)y - 192.0f, 0.0f);

            switch (caption_phase)
            {
            case 1:
            {
                float alpha = (30.0f - (float)fade) / 30.0f;
                caption_image->unk18->unk6a &= ~1;
                BootVector4DDAA0 color;
                color.x = 1.0f;
                color.y = 1.0f;
                color.z = 1.0f;
                color.w = alpha;
                BootClass177820* model = caption_image->unk18;
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
                BootClass177820* model = caption_image->unk18;
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
                BootClass177820* model = caption_image->unk18;
                copy_vector(&model->unk560, &color);
                model->func_001DDAA0();
                break;
            }
            }
        }
        else
        {
            switch (caption_phase)
            {
            case 1:
            case 3:
                caption_text->set_alpha(128.0f * (30.0f - (float)fade) / 30.0f);
                break;
            case 2:
                caption_text->set_alpha(128.0f);
                break;
            }
        }

        break;
    case 2:
        if ((input->held & 8) || !player->unk15E794)
        {
            D_001B661C->append_node(new (0) BootClass171C00(g_boot_program.display), -1);
            step = 3;
        }

        break;
    case 3:
        func_41A210(player);

        if (caption_image != 0)
        {
            caption_image->destroy();
            caption_image = 0;
        }

        if (container != 0)
        {
            container->destroy();
            container = 0;
        }

        if (caption_text != 0)
        {
            caption_text->destroy();
            caption_text = 0;
        }

        if (player != 0)
        {
            player->destroy();
            player = 0;
        }

        step++;
        break;
    case 4:
        lib_object_detach_owner(this);
        destroy();
        D_001B6614->append_node(new (0) BootClass171BB0(-1), -1);
        return;
    }
}

/** @brief Release the caption objects, the player and its heap. */
BootOpeningMovie::~BootOpeningMovie()
{
    if (caption_image != 0)
    {
        caption_image->destroy();
    }

    if (container != 0)
    {
        container->destroy();
    }

    if (caption_text != 0)
    {
        caption_text->destroy();
    }

    if (player != 0)
    {
        player->destroy();
    }

    delete movie_heap;
}

/** @brief Create the movie player in its own heap, set up for 4:3 or widescreen. */
BootOpeningMovie::BootOpeningMovie()
{
    void* heap;
    BootResource0970* resource;
    step = 0;
    movie_heap = new (0) BootResident113E40;
    movie_heap->unk2C = 0x40;
    func_113930(movie_heap, 0x579F2C);
    heap = resident_exchange_allocation_heap(movie_heap);
    player = new (0) BootClass172500(640, 448);
    resident_exchange_allocation_heap(heap);
    player->state->set_scale(1.0f, 1.0f);
    player->state->set_words(0x800, 0x800, 1);
    resource = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);

    if (resource->widescreen != 0)
    {
        player->state->unk80D8 = 1;
        D_001B6654->unk278 =
            (1.7777778f * ((1.3333334f * (1.0714285f * (float)g_boot_program.display->unk3C60.height)) / (float)g_boot_program.display->unk3C60.width)) /
            1.3333334f;
        D_001B6654->unk25C = 1.8325958f;
    }

    container = 0;
    caption_text = 0;
    caption_image = 0;
}

/** @brief Show the popup while the loader reports a BB Unit error, and remove it once the error clears. */
void BootUnitErrorPopup::update()
{
    if (enabled == 0)
    {
        return;
    }

    if (func_115430(D_001B65E4) != 0)
    {
        if (container == 0 && (((u32)program->message_block + 0x7F) & ~0x7F) != 0)
        {
            container = new (0) BootClass178660(8, 0.0f, 0.0f, 0.0f);
            func_465B20(D_001B657C, container);
            panel = new (0) BootClass178630(0, 64.0f, 160.0f, 520.0f, 160.0f, 88.0f);
            lib_container_attach_widget(container, panel);
            text = new (0) BootClass178750(program->messages, BOOT_MSG_UNIT_FIX, 0, 80.0f, 176.0f, 576.0f, 320.0f);
            lib_container_attach_widget(container, text);
        }
    }
    else if (container != 0)
    {
        if (panel != 0)
        {
            panel->destroy();
            panel = 0;
        }

        if (text != 0)
        {
            text->destroy();
            text = 0;
        }

        if (container != 0)
        {
            container->destroy();
            container = 0;
        }
    }
}

/** @brief Destroy the object. */
BootUnitErrorPopup::~BootUnitErrorPopup()
{
}

/** @brief Release the owned objects, then queue this object for deletion. */
void BootUnitErrorPopup::destroy()
{
    if (panel != 0)
    {
        panel->destroy();
        panel = 0;
    }

    if (text != 0)
    {
        text->destroy();
        text = 0;
    }

    if (container != 0)
    {
        container->destroy();
        container = 0;
    }

    func_11ED90(D_001B65F4, this);
}

/**
 * @brief Replace the display and, on a full rebuild, the scratch heap.
 * @param full Nonzero to also recreate the scratch heap and rebind the display.
 */
void BootProgram::rebuild_display(u8 full)
{
    BootDisplayArea3C60* area;
    delete display;
    display = new (0) BootDimensionsACD0;
    func_4E09B0(display, 2);
    func_4E0BC0(display, 1, 1.0f, 2.0f, -1);
    func_4DD440(display, 0, 1, 0, 0, 1, 0, 0, 1, 640, 224);
    func_4DD440(display, 1, 1, 0, 0, 1, 1, 1, 1, 640, 224);
    func_4DF890(display, 0, 640, 224, 2, 0x31);
    func_4E03C0(display, 1, 640, 224);
    func_4DF6E0(display, 0, 0, 0, 0x81);
    area = &display->unk3C60;
    func_4DE250(display, 0, 0, 0, area->width, area->height);
    func_4DE250(display, 1, 0, 0, area->width, area->height);
    func_4DCFA0(display);

    if (full)
    {
        if (D_001B663C != (void*)0x70000000)
        {
            ::operator delete(D_001B663C);
        }

        func_4DCC10(D_001B65E0, display->unk3C78);
        D_001B663C = new (0) BootScratchHeap(0x20000, 0x20);
        func_4D78F0(D_001B6618);
        func_42D940();
        func_11DEE0(D_001B65F0, display, 1);
        D_001B6658->display = display;
    }

    frame = 0;
}

/** @brief Make the boot projection the display manager's current display. */
void BootProgram::select_projection()
{
    D_001B6628->current_display = projection;
}

/** @brief Set the projections' aspect and field of view for the 4:3 or widescreen setting. */
inline void BootProgram::update_projection_aspect()
{
    BootResource0970* resource = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);
    BootDimensionsACD0* dimensions;

    if (resource->widescreen != 0)
    {
        dimensions = g_boot_program.display;
        projection->unk278 = (1.7777778f * ((1.3333334f * (1.0714285f * (float)dimensions->unk3C60.height)) / (float)dimensions->unk3C60.width)) / 1.3333334f;
        projection->unk250 = 0.75f;
        dimensions = g_boot_program.display;
        D_001B6654->unk278 = (1.7777778f * ((1.3333334f * (1.0714285f * (float)dimensions->unk3C60.height)) / (float)dimensions->unk3C60.width)) / 1.3333334f;
        D_001B6654->unk25C = 1.8325958f;
    }
    else
    {
        dimensions = g_boot_program.display;
        projection->unk278 = (1.3333334f * (1.0714285f * (float)dimensions->unk3C60.height)) / (float)dimensions->unk3C60.width;
        projection->unk250 = 1.0f;
        dimensions = g_boot_program.display;
        D_001B6654->unk278 = (1.3333334f * (1.0714285f * (float)dimensions->unk3C60.height)) / (float)dimensions->unk3C60.width;
        D_001B6654->unk25C = 1.5707964f;
    }
}

/**
 * @brief Switch progressive output on or off, then rebuild the display and rebind it everywhere.
 * @param progressive Nonzero for progressive (525p) output.
 */
void BootProgram::set_progressive(u8 progressive)
{
    BootDimensionsACD0* rebuilt;
    BootDisplayLinks661C* links;

    if (progressive)
    {
        func_4DCEA0(display, 0, 0);
        func_101040(func_10D8E0(), 1);
    }
    else
    {
        func_4DCEA0(display, 0, 0);
        func_101040(func_10D8E0(), 0);
    }

    rebuild_display(1);
    rebuilt = display;
    links = D_001B661C;
    links->unk4088 = rebuilt;
    D_001B6650 = rebuilt;

    if (links->unk4080 != 0)
    {
        links->unk4080->display = rebuilt;
    }

    links->unk4458->display = rebuilt;
    links->unk4460->display = rebuilt;
    links->unk4464->display = rebuilt;
    links->unk4468->display = rebuilt;
    links->unk446C->display = rebuilt;
    D_001B6520 = rebuilt;
    update_projection_aspect();
}

/** @brief Decode the next of the program's three resource blocks, then destroy this object after the last. */
void BootResourceLoader::update()
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
            program->message_block = buffer;
            program->messages = func_4656B0(D_001B657C, aligned);
            break;
        case 1:
            program->caption_block = buffer;
            program->captions = func_4656B0(D_001B657C, aligned);
            break;
        case 2:
            program->image_block = buffer;
            break;
        }

        block++;
    }
}

/** @brief Fill the track pools, then create and register the projection. */
void BootProgram::create_pools_and_projection()
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
    projection = new (0) BootProjectionACD0(display);
    func_4E14B0(projection, display);
    projection->func_001E0520(0.0f, 0.0f, -500.0f);
    D_001B6628->append_node(projection, -1);
    D_001B6628->current_display = projection;
    func_4DAFE0(D_001B6628, display, false, true, false, 2, 0xFFFFFF);
    D_001B661C->unk4084 = D_001B6624;
    D_001B6624->manager = D_001B6628;
}

/** @brief Run the boot program. */
void BootProgram::run()
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
    BootResourceLoader* loader;

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

    projection = 0;
    input = 0;
    message_block = 0;
    display = 0;
    image_block = 0;
    trophy_card = 0;
    caption_block = 0;
    unk2C = 0;
    exit_code = 0;
    error_popup = 0;
    image = 0;
    messages = 0;
    captions = 0;
    unit_data_deleted = 0;

    buffer = new (0) u8[func_10CE00() + 0x40];
    size = func_11C8C0(func_1012C0(func_10D8E0()), 3);

    if (size > 0x50000)
    {
        size = 0x50000;
    }

    image = (BootProgramImage*)func_139700(0x40, size);
    func_103E70(func_101250(func_10D8E0()), 3, image, 1, 0x34BC0, 0, size, 0, 1);
    delete[] buffer;

    saved_widescreen = 0xFF;
    fresh = true;

    if (func_101440(func_101290(func_10D8E0()), 1) != 0)
    {
        saved_widescreen = ((BootResource0970*)func_101440(func_101290(func_10D8E0()), 1))->widescreen;
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
    rebuild_display(0);
    func_121890(display);
    func_4E3830(display, 0xA0013BA, 0x20000, 0x20, 0x200, 0, 0);
    rect.x = 0;
    rect.y = 0;
    rect.width = 640;
    rect.height = 224;
    func_4D8A80(&rect, 0xFFFFFF);
    D_001B6618->clear_color = 0xFFFFFF;
    func_11DEE0(D_001B65F0, display, 1);

    while (!func_102D00(D_001B65E8))
    {
    }

    check_main_code();
    func_45A770();
    create_pools_and_projection();
    settings = (BootResource0970*)func_101440(func_101290(func_10D8E0()), 1);

    if (saved_widescreen != 0xFF)
    {
        settings->widescreen = saved_widescreen != 0;
    }

    D_001B657C = new (0) BootRuntime1B657C(640.0f, 480.0f, 0, 0, 1.8f);
    trophy_card = new (0) BootBattleTrophyCard;
    D_001B6614->append_node(trophy_card, -1);
    trophy_card->initialize();
    error_popup = new (0) BootUnitErrorPopup(this);
    D_001B6614->append_node(error_popup, -1);
    input = new (0) BootInput;
    D_001B6614->append_node(input, -1);
    loader = new (0) BootResourceLoader(this);
    D_001B6614->append_node(loader, -1);

    if (fresh)
    {
        D_001B6614->append_node(new (0) BootStartupChecks, -1);
    }
    else
    {
        D_001B6614->append_node(new (0) BootClass171BB0(-1), -1);
    }

    D_001B6420 = 1;
    update_projection_aspect();
    frame = 0;
    D_001B661C->unk40CE = 0;
    D_001B6420 = 1;

    while (exit_code == 0)
    {
        func_4DD830(display, frame++, D_001B65DC);
        func_4D8AC0();
        func_4D76C0(D_001B6618, 16, 16);
        func_4D4BE0(D_001B661C);
        D_001B6614->update_nodes();
        func_11F770(D_001B6618->packet, 0);
        func_11ECD0(D_001B65F4);
        func_4DCFF0(display, frame);

        if (frame > 1)
        {
            func_4DCEA0(display, 1, 0);
        }

        D_001B6688 = (float)func_11DF00(D_001B65F0);
        D_001B6690 = D_001B6688 / 60.0f;
        TIMER0_COUNT = 0;
    }

    D_001B661C->unk40CE = 1;
    func_11ECD0(D_001B65F4);
    g_boot_program.release_resources();
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

    func_1010D0(func_10D8E0(), exit_code, 1);
}

/** @brief Release the track pools and every object, resource and buffer the program owns. */
void BootProgram::release_resources()
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
    delete image;
    image = 0;

    if (error_popup != 0)
    {
        lib_object_detach_owner(error_popup);
        error_popup->destroy();
        error_popup = 0;
    }

    if (messages != 0)
    {
        lib_release_resource_slot(D_001B657C, messages);
    }

    if (captions != 0)
    {
        lib_release_resource_slot(D_001B657C, captions);
    }

    delete D_001B657C;
    D_001B657C = 0;

    if (input != 0)
    {
        lib_object_detach_owner(input);
        input->destroy();
        input = 0;
    }

    if (trophy_card != 0)
    {
        trophy_card->destroy();
        trophy_card = 0;
    }

    projection->destroy();
    projection = 0;
    delete message_block;
    message_block = 0;
    delete caption_block;
    caption_block = 0;
    delete image_block;
    image_block = 0;
    delete display;
    display = 0;
}

/** @brief Release the program's objects, resources, and buffers. */
BootProgram::~BootProgram()
{
    if (input != 0)
    {
        lib_object_detach_owner(input);
        input->destroy();
    }

    if (trophy_card != 0)
    {
        trophy_card->destroy();
    }

    if (projection != 0)
    {
        projection->destroy();
    }

    delete message_block;
    delete caption_block;
    delete image_block;
    delete image;
}

/** @brief Destroy the object. */
BootResourceLoader::~BootResourceLoader()
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

#include "overlays/boot/transform_inlines.h"
