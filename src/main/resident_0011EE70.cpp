#include "include_asm.h"
#include "main/resident_0011EE70.h"
#include "main/resident_00101260.h"
#include "sdk/main/libkernl_00121940.h"

enum
{
    GIF_REGISTER_PRIM = 0x0,
    GIF_REGISTER_RGBAQ = 0x1,
    GIF_REGISTER_XYZ2 = 0x5,
    GIF_REGISTER_AD = 0xE
};

enum
{
    GS_REGISTER_PRIM = 0x00,
    GS_REGISTER_TEX0_2 = 0x07,
    GS_REGISTER_ALPHA_1 = 0x42,
    GS_REGISTER_ALPHA_2 = 0x43
};

/** GIF tag for one A+D register write: NLOOP 1, EOP clear, NREG 1. */
#define GIF_TAG_AD_WRITE 0x1000000000000001ULL

/** GIF tag that only ends the transfer: NLOOP 0, EOP set. */
#define GIF_TAG_END 0x8000

/** GIF tag for one packed line: NLOOP 1, register list mode, NREG 4. */
#define GIF_TAG_LINE 0x4400000000000001ULL

/** GIF tag for one packed rectangle: NLOOP 1, register list mode, NREG 6. */
#define GIF_TAG_RECTANGLE 0x6400000000000001ULL

/** GS PRIM: antialiased line drawn with the second drawing context. */
#define GS_PRIM_LINE 0x281

/** GS PRIM: triangle strip drawn with the second drawing context. */
#define GS_PRIM_TRIANGLE_STRIP 0x204

/** GS PRIM alpha blending enable bit. */
#define GS_PRIM_ALPHA_BLEND 0x40

/** Centre of the GS primitive coordinate space, in whole pixels. */
#define GS_COORDINATE_CENTRE 0x800

/** Budget one slot's random bank pick costs. */
#define SOUND_BANK_PICK_COST 300

/** Bank data parts are placed on 2048-byte sector boundaries. */
#define SOUND_BANK_SECTOR_SHIFT 11

extern "C" {
extern u8 D_50CD30[];
extern u8 D_0014FC78[];
extern const ResidentSoundBankVariants* D_001B6424;
extern ResidentDisplayContext* D_001B6650;
extern void* D_001B6640;
extern u8 D_001B65D0;
extern struct FieldPacketQueue* D_001B65DC;

void func_4CE4C0(void* destination, const float* source);
void func_4D72A0(void);
void func_4486A0(void* object);
void func_4D0260(void* list, void* object);
void func_4D0020(void* object);
s32 func_4DC4F0(struct FieldPacketQueue* queue, u32 operation, u32 flags, u32 address, u32 value, void* completion);
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

typedef struct ByteTransitionViewOwnerresident_0011EE70
{
    u8 pad00[0x24];
    u8 unk24;
    u8 unk25;
} ByteTransitionViewOwnerresident_0011EE70;

typedef struct ByteClearOwnerresident_0011EE70
{
    u8 unk00[0x60];
    u8 unk60;
} ByteClearOwnerresident_0011EE70;



typedef struct WordSetterOwnerresident_0011EE70
{
    u8 unk00[0x70];
    u32 unk70;
} WordSetterOwnerresident_0011EE70;



typedef struct WordGetterOwnerresident_0011EE70
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
    u32 unk10;
    u32 unk14;
} WordGetterOwnerresident_0011EE70;

typedef struct ResidentWordAndFlag2B4Ownerresident_0011EE70
{
    u8 pad00[0x2B4];
    u32 unk2B4;
    u32 unk2B8;
    u8 pad2BC[0x7];
    u8 unk2C3;
    u8 unk2C4;
} ResidentWordAndFlag2B4Ownerresident_0011EE70;


typedef struct FlagQuadwordOwnerresident_0011EE70 { u8 unk00[0x20]; unsigned __int128 slots[3]; u8 ready; } FlagQuadwordOwnerresident_0011EE70;

typedef struct FlagFloatQuadOwnerresident_0011EE70 { u8 pad00[0x30]; float values[4]; u8 pad40[0x10]; u8 flag50; } FlagFloatQuadOwnerresident_0011EE70;

typedef struct FlagFloatQuadOffset20Ownerresident_0011EE70
{
    u8 pad00[0x20];
    float values[4];
    u8 pad30[0x20];
    u8 flag50;
} FlagFloatQuadOffset20Ownerresident_0011EE70;

typedef struct FlagFloatTripleOwnerresident_0011EE70 { u8 pad00[0x40]; float values[3]; u8 pad4C[4]; u8 flag50; } FlagFloatTripleOwnerresident_0011EE70;

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

/** @brief Drain both release rings. */
ResidentReleaseQueues::~ResidentReleaseQueues()
{
    vtable = D_0014FC78;
    resident_drain_release_queues(this);
}

/**
 * @brief Initialize both resident release rings as empty.
 * @param queues Release queues to initialize.
 * @return The initialized queues.
 */
ResidentReleaseQueues* resident_initialize_release_queues(ResidentReleaseQueues* queues)
{
    queues->vtable = D_0014FC78;
    queues->allocations.write_index = 1;
    queues->allocations.read_index = 0;
    queues->objects.write_index = 1;
    queues->objects.read_index = 0;
    return queues;
}

/**
 * @brief Append a GIF A+D write of one GS register when the packet has room.
 * @param packet Packet to append to.
 * @param address GS register address.
 * @param data Register value.
 */
void func_0011EF00(ResidentPacket* packet, u64 address, u64 data)
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
void func_0011EF90(ResidentPacket* packet, u64 data)
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
void func_0011F020(ResidentPacket* packet, u64 data)
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
void func_0011F0B0(ResidentPacket* packet, u64 data)
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
void func_0011F140(ResidentPacket* packet, u64 data)
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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F1D0);

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
        offset_x = GS_COORDINATE_CENTRE - D_001B6650->viewport_width / 2;
        offset_y = GS_COORDINATE_CENTRE - D_001B6650->viewport_height / 2;
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
void func_0011F510(ResidentPacket* packet, void* completion)
{
    if (resident_packet_space(packet, 0) != packet->unk0c)
    {
        func_4DC4F0(D_001B65DC, 3, 0, (u32)packet->unk0c & 0x0FFFFFFF, 0, completion);
    }
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F580);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F640);

/**
 * @brief Write a GIF end tag after the pending data without advancing the cursor.
 * @param packet Packet to terminate.
 * @return Quadwords from the pending data's start through the end tag, or zero when nothing is pending.
 */
u32 func_0011F6E0(ResidentPacket* packet)
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
u32 func_0011F760(const void* object)
{
    const u32* words = (const u32*)object;
    return words[3] & 0x0FFFFFFF;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", resident_packet_submit);

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
    packet->unk08 = packet->unk00 + 0x40;
    packet->unk0c = packet->unk08;
}

/**
 * @brief Cancel the bank file reads and forget each slot's variant unless loads are in progress.
 * @param set Sound bank set.
 */
void func_0011F940(ResidentClass14FC90* set)
{
    if (set->loading == 0)
    {
        resident_cancel_resource_requests(func_00101250(resident_get_system()), 0, 0, 6, 0xFFFFFFFF, 0);
        set->variants[0] = -1;
        set->variants[1] = -1;
        set->variants[2] = -1;
        set->loading = 0;
        set->unk24 = 0;
    }
}

/**
 * @brief Move the set state from byte 0x25 to byte 0x24 when set.
 * @param object Object containing the state bytes.
 */
void func_0011F9B0(void* object)
{
    ByteTransitionViewOwnerresident_0011EE70* receiver = (ByteTransitionViewOwnerresident_0011EE70*)object;
    if (receiver->unk25 != 0)
    {
        receiver->unk25 = 0;
        receiver->unk24 = 1;
    }
}

/** Return the unsigned byte at receiver offset 0x25. */
u8 func_0011F9D0(void* object)
{
    const ByteTransitionViewOwnerresident_0011EE70* receiver = (const ByteTransitionViewOwnerresident_0011EE70*)object;
    return receiver->unk25;
}

/**
 * @brief Play a voice resource, from an emitter when one is given.
 * @param object Sound bank set; unused.
 * @param resource Voice resource.
 * @param emitter Object the voice follows, or null.
 * @param value Value forwarded to the voice request.
 * @param volume Volume, 0x7F for full.
 * @param low Value forwarded to the voice request.
 * @return Slot identifier of the voice.
 */
s32 func_0011F9E0(void* object, s32 resource, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low)
{
    ResidentSound* sound = func_00101270(resident_get_system());

    if (emitter == 0)
    {
        return func_00111EF0(sound, resource, value, volume, 0x40, low);
    }

    return resident_sound_play_voice(sound, resource, emitter, value, volume, low);
}

/**
 * @brief Play sound data the caller supplies, from an emitter when one is given.
 * @param object Sound bank set; unused.
 * @param buffer Sound data to play.
 * @param emitter Object the sound follows, or null.
 * @param value Value forwarded to the sound request.
 * @param volume Volume, 0x7F for full.
 * @param low Value forwarded to the sound request.
 * @param owns_buffer Nonzero to free the buffer when the sound ends.
 * @return Slot identifier of the sound.
 */
s32 func_0011FA80(void* object, u8* buffer, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low, s32 owns_buffer)
{
    ResidentSound* sound = func_00101270(resident_get_system());

    if (emitter == 0)
    {
        return func_00111A90(sound, buffer, value, volume, 0x40, low, owns_buffer);
    }

    return func_00111860(sound, buffer, emitter, value, volume, low, owns_buffer);
}

/**
 * @brief Play a sound from a slot's bank, from an emitter when one is given.
 * @param set Sound bank set.
 * @param slot Bank slot.
 * @param id Sound number within the bank.
 * @param emitter Object the sound follows, or null.
 * @param arg4 Value forwarded to the sound request.
 * @param arg5 Value forwarded to the sound request.
 * @param arg6 Value forwarded to the sound request.
 * @return Slot identifier of the sound, or -1 when the slot has no bank loaded.
 */
s32 func_0011FB40(ResidentClass14FC90* set, s32 slot, s32 id, ResidentSoundEmitter* emitter, s32 arg4, s32 arg5, s32 arg6)
{
    ResidentSound* sound;

    if (set->variants[slot] < 0)
    {
        return -1;
    }

    sound = func_00101270(resident_get_system());

    if (emitter == 0)
    {
        return resident_sound_play(sound, id, slot * 2 + 1, arg4, arg5, 0x40, arg6);
    }

    return func_00112160(sound, id, emitter, slot * 2 + 1, arg4, arg5, arg6);
}

/**
 * @brief Advance the bank loads by one step each frame while loads are in progress.
 * @param set Sound bank set.
 */
void func_0011FC20(ResidentClass14FC90* set)
{
    ResidentResourceQueue* queue;
    ResidentSound* sound;
    s32* data;
    u8* part;
    bool finished;

    if (set->loading == 0)
    {
        return;
    }

    queue = func_00101250(resident_get_system());
    sound = func_00101270(resident_get_system());

    if (set->upload_lists == 0)
    {
        if (set->buffer == 0)
        {
            return;
        }

        switch (set->load_step)
        {
            case 0:
                if (set->load_index >= set->load_count)
                {
                    set->loading = 0;
                    delete set->buffer;
                    set->buffer = 0;
                    return;
                }

                resident_queue_resource_request(queue, set->loads[set->load_index].file_key, set->buffer, 6, 0x34BC0, 0,
                                                0, 0, 1);
                set->load_step = 1;
                break;

            case 1:
                if (resident_find_resource_request(queue, set->loads[set->load_index].file_key, (u32)set->buffer, 6,
                                                   0xFFFFFFFF, 0) != 0)
                {
                    break;
                }

                if (func_0010EB90(sound, set->buffer, set->loads[set->load_index].slot * 2 + 1, 0) != 0)
                {
                    set->load_step = 2;
                }

                break;

            case 2:
                func_0010F250(sound, 0);

                if (sound->state == 0)
                {
                    set->variants[set->loads[set->load_index].slot] = set->loads[set->load_index].variant;
                    set->load_step = 0;
                    set->load_index++;
                }

                break;
        }
    }
    else
    {
        finished = false;

        do
        {
            switch (set->load_step)
            {
                case 0:
                    for (;;)
                    {
                        if (set->lists[set->list_index][set->load_index] != 0)
                        {
                            break;
                        }

                        if (++set->load_index < RESIDENT_SOUND_BANK_LIST_COUNT)
                        {
                            continue;
                        }

                        set->first_part = 1;
                        set->load_index = 0;

                        if (++set->list_index < RESIDENT_SOUND_BANK_SLOT_COUNT)
                        {
                            continue;
                        }

                        finished = true;
                        break;
                    }

                    if (set->list_index >= RESIDENT_SOUND_BANK_SLOT_COUNT)
                    {
                        set->loading = 0;
                        return;
                    }

                    set->load_step = 1;
                    set->part_index = 0;
                    break;

                case 1:
                    data = set->lists[set->list_index][set->load_index];

                    if (set->part_index >= data[0])
                    {
                        set->load_step = 0;

                        if (++set->load_index >= RESIDENT_SOUND_BANK_LIST_COUNT)
                        {
                            set->first_part = 1;
                            set->list_index++;
                            set->load_index = 0;
                        }

                        break;
                    }

                    part = (u8*)data
                           + (((ResidentSoundBankPart*)(data + 1))[set->part_index].sector << SOUND_BANK_SECTOR_SHIFT);

                    if (func_0010EB90(sound, part, set->list_index * 2 + 2, !set->first_part) != 0)
                    {
                        set->load_step = 2;
                        set->first_part = 0;
                        set->list_sizes[set->list_index] += func_00105F90(sound->stream, (const SoundFileHeader*)part);
                    }
                    else
                    {
                        finished = true;
                    }

                    break;

                case 2:
                    func_0010F250(sound, 0);

                    if (sound->state == 0)
                    {
                        set->load_step = 1;
                        set->part_index++;
                    }
                    else
                    {
                        finished = true;
                    }

                    break;
            }
        } while (!finished);
    }
}

/**
 * @brief Start uploading the registered data lists unless loads are in progress.
 * @param set Sound bank set.
 */
void func_0011FFD0(ResidentClass14FC90* set)
{
    if (set->loading == 0)
    {
        set->load_index = 0;
        set->list_index = 0;
        set->loading = 1;
        set->upload_lists = 1;
        set->load_step = 0;
        set->first_part = 1;
    }
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120000);

/**
 * @brief Clear every registered data list and its size unless loads are in progress.
 * @param set Sound bank set.
 */
void func_00120050(ResidentClass14FC90* set)
{
    s32 list;
    s32 index;

    if (set->loading == 0)
    {
        for (list = 0; list < RESIDENT_SOUND_BANK_SLOT_COUNT; list++)
        {
            set->list_sizes[list] = 0;

            for (index = 0; index < RESIDENT_SOUND_BANK_LIST_COUNT; index++)
            {
                set->lists[list][index] = 0;
            }
        }
    }
}

/**
 * @brief Queue a load of a randomly picked variant of a slot's bank.
 * @param set Sound bank set.
 * @param index Load to fill.
 * @param slot Slot the variant is for.
 */
static inline void pick_bank_variant(ResidentClass14FC90* set, s32 index, s32 slot)
{
    s32 variant;

    set->loads[index].slot = slot;
    variant = resident_random_below(D_001B6424[set->banks[slot] - 1].count);
    set->loads[index].file_key = D_001B6424[set->banks[slot] - 1].file_keys[variant];
    set->loads[index].variant = variant;
}

/**
 * @brief Pick a variant for each assigned slot without one, then spend the rest of a budget re-picking random slots,
 *        and start loading the picks.
 * @param set Sound bank set.
 * @param budget Budget; each pick costs SOUND_BANK_PICK_COST.
 * @return One when loading started, or zero while loads are in progress, when the budget runs out or when the staging
 *         buffer can't be allocated.
 */
s32 func_001200C0(ResidentClass14FC90* set, s32 budget)
{
    u8 picked[RESIDENT_SOUND_BANK_SLOT_COUNT];
    s32 count;
    s32 slot;
    s32 index;

    if (set->loading != 0)
    {
        return 0;
    }

    count = 0;

    for (slot = 0; slot < RESIDENT_SOUND_BANK_SLOT_COUNT; slot++)
    {
        if (set->banks[slot] != 0)
        {
            if (set->variants[slot] == -1)
            {
                pick_bank_variant(set, count, slot);
                picked[slot] = 1;
                count++;
                budget -= SOUND_BANK_PICK_COST;
            }
            else
            {
                picked[slot] = 0;
            }
        }
    }

    if (budget < 0)
    {
        return 0;
    }

    while (budget > SOUND_BANK_PICK_COST)
    {
        for (index = 0; index < RESIDENT_SOUND_BANK_SLOT_COUNT; index++)
        {
            if (!picked[index] && set->banks[index] != 0)
            {
                break;
            }
        }

        if (index == RESIDENT_SOUND_BANK_SLOT_COUNT)
        {
            break;
        }

        for (index = 0; index < 100; index++)
        {
            slot = resident_random_below(RESIDENT_SOUND_BANK_SLOT_COUNT);

            if (!picked[slot] && set->banks[slot] != 0)
            {
                break;
            }
        }

        if (picked[slot] || set->banks[slot] == 0)
        {
            break;
        }

        pick_bank_variant(set, count, slot);
        picked[slot] = 1;
        count++;
        budget -= SOUND_BANK_PICK_COST;
    }

    delete set->buffer;
    set->buffer = new (0) u8[0x21C00];

    if (set->buffer != 0)
    {
        set->load_count = count;
        set->load_index = 0;
        set->loading = 1;
        set->upload_lists = 0;
        set->load_step = 0;
        return 1;
    }

    return 0;
}

void func_00120360(const void* value)
{
    D_001B6424 = (const ResidentSoundBankVariants*)value;
}

/**
 * @brief Get the budget picking a variant for every assigned slot without one would cost.
 * @param set Sound bank set.
 * @return The pick cost times the number of such slots.
 */
s32 func_00120370(ResidentClass14FC90* set)
{
    s32 cost = 0;
    s32 slot;

    for (slot = 0; slot < RESIDENT_SOUND_BANK_SLOT_COUNT; slot++)
    {
        if (set->banks[slot] != 0 && set->variants[slot] == -1)
        {
            cost += SOUND_BANK_PICK_COST;
        }
    }

    return cost;
}

/**
 * @brief Assign a bank to a slot unless loads are in progress, forgetting its variant when the bank changes.
 * @param set Sound bank set.
 * @param slot Slot to assign.
 * @param bank One-based bank number, or zero for none.
 * @return One when assigned, or zero while loads are in progress.
 */
s32 func_001203C0(ResidentClass14FC90* set, s32 slot, s32 bank)
{
    if (set->loading != 0)
    {
        return 0;
    }

    if (set->banks[slot] != bank)
    {
        set->variants[slot] = -1;
    }

    set->banks[slot] = bank;
    return 1;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120410);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001204B0);

/**
 * @brief Clamp a value to [0, 999999999] and store it at offset 0x14.
 * @param object Object containing the word.
 * @param value Value to store.
 * @return The clamped value.
 */
s32 func_00120560(void* object, s32 value)
{
    WordGetterOwnerresident_0011EE70* receiver = (WordGetterOwnerresident_0011EE70*)object;
    if (value < 0)
    {
        value = 0;
    }
    if (value > 999999999)
    {
        value = 999999999;
    }
    receiver->unk14 = value;
    return value;
}

/** Return the word at receiver offset 0x14. */
u32 func_001205A0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = (const WordGetterOwnerresident_0011EE70*)object;
    return receiver->unk14;
}

s32 func_001205B0(void* object, s32 value)
{
    WordGetterOwnerresident_0011EE70* receiver = (WordGetterOwnerresident_0011EE70*)object;
    if (value < 0)
    {
        value = 0;
    }
    if (value > 100)
    {
        value = 100;
    }
    receiver->unk10 = value;
    return value;
}

/** Return the word at receiver offset 0x10. */
u32 func_001205E0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = (const WordGetterOwnerresident_0011EE70*)object;
    return receiver->unk10;
}

/**
 * @brief Clamp a value to [0, 99999999] and store it at offset 0xC.
 * @param object Object containing the word.
 * @param value Value to store.
 * @return The clamped value.
 */
s32 func_001205F0(void* object, s32 value)
{
    WordGetterOwnerresident_0011EE70* receiver = (WordGetterOwnerresident_0011EE70*)object;
    if (value < 0)
    {
        value = 0;
    }
    if (value > 99999999)
    {
        value = 99999999;
    }
    receiver->unk0c = value;
    return value;
}

/** Return the word at receiver offset 0xC. */
u32 func_00120630(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = (const WordGetterOwnerresident_0011EE70*)object;
    return receiver->unk0c;
}

s32 func_00120640(void* object, s32 value)
{
    WordGetterOwnerresident_0011EE70* receiver = (WordGetterOwnerresident_0011EE70*)object;
    if (value < 0)
    {
        value = 0;
    }
    if (value > 255)
    {
        value = 255;
    }
    receiver->unk08 = value;
    return value;
}

/** Return the word at receiver offset 0x8. */
u32 func_00120670(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = (const WordGetterOwnerresident_0011EE70*)object;
    return receiver->unk08;
}

s32 func_00120680(void* object, s32 value)
{
    WordGetterOwnerresident_0011EE70* receiver = (WordGetterOwnerresident_0011EE70*)object;
    if (value < 0)
    {
        value = 0;
    }
    if (value > 999)
    {
        value = 999;
    }
    receiver->unk04 = value;
    return value;
}

/** Return the word at receiver offset 0x4. */
u32 func_001206B0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = (const WordGetterOwnerresident_0011EE70*)object;
    return receiver->unk04;
}

s32 func_001206C0(void* object, s32 value)
{
    WordGetterOwnerresident_0011EE70* receiver = (WordGetterOwnerresident_0011EE70*)object;
    if (value < 0)
    {
        value = 0;
    }
    if (value > 9999)
    {
        value = 9999;
    }
    receiver->unk00 = value;
    return value;
}

/** Return the word at receiver offset 0x0. */
u32 func_001206F0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = (const WordGetterOwnerresident_0011EE70*)object;
    return receiver->unk00;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120700);

/** Store the word at receiver offset 0x70. */
void func_001207B0(void* object, u32 value)
{
    WordSetterOwnerresident_0011EE70* receiver = (WordSetterOwnerresident_0011EE70*)object;
    receiver->unk70 = value;
}

void func_001207C0(void* object)
{
}

s32 func_001207D0(void* object)
{
    return 9;
}

/**
 * @brief Unregister the object if it is registered, then detach it and queue it for release.
 * @param object Object to release.
 */
void func_001207E0(ResidentClass14FD30* object)
{
    if (object->registered != 0)
    {
        ResidentClass14FD10& registration = *object;

        func_4486A0(&registration);
        func_4D0260(D_001B6640, static_cast<ResidentClass14FD10*>(object));
        object->registered = 0;
    }

    func_4D0020(object);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120840);

void func_00120A50(void* object, u8 flag, u32 value)
{
    ResidentWordAndFlag2B4Ownerresident_0011EE70* receiver = (ResidentWordAndFlag2B4Ownerresident_0011EE70*)object;
    receiver->unk2C4 = flag;
    receiver->unk2B8 = value;
}

void func_00120A60(void* object, u8 flag, u32 value)
{
    ResidentWordAndFlag2B4Ownerresident_0011EE70* receiver = (ResidentWordAndFlag2B4Ownerresident_0011EE70*)object;
    receiver->unk2C3 = flag;
    receiver->unk2B4 = value;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120A70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120BF0);

void func_00120EB0(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnerresident_0011EE70* receiver = (FlagQuadwordOwnerresident_0011EE70*)object;
    receiver->ready = 1;
    receiver->slots[1] = *value;
}

void func_00120ED0(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnerresident_0011EE70* receiver = (FlagQuadwordOwnerresident_0011EE70*)object;
    receiver->ready = 1;
    receiver->slots[0] = *value;
}

/**
 * @brief Set the word at offset 0x8C to 2, set bit 0 of the shared flag byte D_001B65D0 and call func_4D72A0.
 * @param object Object containing the word.
 */
void func_00120EF0(void* object)
{
    u8* bytes = (u8*)object;

    *(u32*)(bytes + 0x8C) = 2;
    D_001B65D0 |= 1;
    func_4D72A0();
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120F20);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120FE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001210B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001212A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001213B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121490);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121520);

s32 func_00121570(void* object)
{
    return 0;
}

void* func_00121580(void* object)
{
    return (u8*)object + 0x90;
}

void* func_00121590(void* object)
{
    return (u8*)object + 0x1D0;
}

void* func_001215A0(void* object)
{
    return (u8*)object + 0x1E0;
}

void* func_001215B0(void* object)
{
    return (u8*)object + 0x1F0;
}

void func_001215C0(void* object)
{
    ByteClearOwnerresident_0011EE70* receiver = (ByteClearOwnerresident_0011EE70*)object;
    receiver->unk60 = 0;
}

void func_001215D0(void* object)
{
}

s32 func_001215E0(void* object)
{
    return 0;
}

s32 func_001215F0(float value)
{
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
}

const void* func_00121610(void)
{
    return D_50CD30;
}

void func_00121620(void* object)
{
}

s32 func_00121630(void* object)
{
    return 0;
}

void func_00121640(void* object)
{
}

void func_00121650(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnerresident_0011EE70* receiver = (FlagQuadwordOwnerresident_0011EE70*)object;
    receiver->ready = 1;
    receiver->slots[0] = *value;
}

/**
 * @brief Store three components and set the fourth to 1.0 at offset 0x20.
 * @param object Object containing the vector and flag.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_00121670(void* object, float x, float y, float z)
{
    FlagFloatQuadOffset20Ownerresident_0011EE70* receiver = (FlagFloatQuadOffset20Ownerresident_0011EE70*)object;
    receiver->flag50 = 1;
    receiver->values[0] = x;
    receiver->values[1] = y;
    receiver->values[2] = z;
    receiver->values[3] = 1.0f;
}

void func_00121690(void* object, float x, float y, float z, float w)
{
    FlagFloatQuadOwnerresident_0011EE70* receiver = (FlagFloatQuadOwnerresident_0011EE70*)object;
    receiver->flag50 = 1;
    receiver->values[0] = x;
    receiver->values[1] = y;
    receiver->values[2] = z;
    receiver->values[3] = w;
}

void func_001216B0(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnerresident_0011EE70* receiver = (FlagQuadwordOwnerresident_0011EE70*)object;
    receiver->ready = 1;
    receiver->slots[1] = *value;
}
