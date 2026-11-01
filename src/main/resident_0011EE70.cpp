#include "include_asm.h"
#include "main/resident_0011EE70.h"
#include "main/resident_00101260.h"
#include "main/resident_data.h"
#include "sdk/main/libkernl_00121940.h"
#include "vu0.h"

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
extern const ResidentVector4 D_50CD30;
extern u8 D_0014FC78[];
extern const ResidentSoundBankVariants* D_001B6424;
extern ResidentDisplayContext* D_001B6650;
extern void* D_001B6640;
extern ResidentObjectList* D_001B6614;
extern u8 D_001B65D0;
extern struct FieldPacketQueue* D_001B65DC;

void func_4CE4C0(ResidentVector4* orientation, const ResidentVector4* rotation);
void func_4486A0(void* object);
void func_4D0260(void* list, void* object);
void func_4D02E0(void* list, void* object);
s32 func_4DC4F0(struct FieldPacketQueue* queue, u32 operation, u32 flags, u32 address, u32 value, void* completion);
bool func_4D7D40(ResidentImageSequenceChannel* channel, ResidentRenderDataRecord* record, bool use_inline);
void func_4CBD20(ResidentMatrix* output, const ResidentVector4* position, const ResidentVector4* direction, float roll);
void func_4CFB20(ResidentMatrix* output, const ResidentMatrix* input, float scale, float width, float height, float x_offset,
                 float y_offset);
void func_4CFC50(ResidentMatrix* output, const ResidentMatrix* input, float scale, float width, float height, float x_offset,
                 float y_offset);
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
 * @brief Replace the image channel with a new one bound to the record, while the object is registered and animated.
 * @param object Object whose channel is rebuilt; it has no channel when binding fails.
 */
static inline void rebuild_image_channel(ResidentClass14FD30* object)
{
    if (object->registered)
    {
        delete object->channel;
        object->channel = 0;

        if (object->animated)
        {
            object->channel = new (0) ResidentImageSequenceChannel;

            if (object->channel)
            {
                if (func_4D7D40(object->channel, &object->record, false))
                {
                    object->channel->unk3c = 0x8000;
                }
                else
                {
                    delete object->channel;
                    object->channel = 0;
                }
            }
        }
    }
}

/**
 * @brief Subtract one vector's xyz from another's, keeping the first vector's w.
 * @param output Difference.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 */
static inline void subtract_xyz(ResidentVector4* output, const ResidentVector4* left, const ResidentVector4* right)
{
    output->x = left->x - right->x;
    output->y = left->y - right->y;
    output->z = left->z - right->z;
    output->w = left->w;
}

/**
 * @brief Test whether a list walk has come back to the list.
 * @param list List sentinel.
 * @param node Current node.
 * @return Whether node is the sentinel.
 */
static inline bool at_list_end(const ResidentClass14FA30* list, const ResidentClass14FA30* node)
{
    if (list == node)
    {
        return true;
    }

    return false;
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
void func_0011F1D0(ResidentPacket* packet, s32 x0, s32 y0, s32 x1, s32 y1, s32 z, u32 color)
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
        offset_x = GS_COORDINATE_CENTRE - D_001B6650->viewport_width / 2;
        offset_y = GS_COORDINATE_CENTRE - D_001B6650->viewport_height / 2;
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
 */
void ResidentClass14FC90::func_00104770()
{
    ResidentResourceQueue* queue;
    ResidentSound* sound;
    s32* data;
    u8* part;
    bool finished;

    if (loading == 0)
    {
        return;
    }

    queue = func_00101250(resident_get_system());
    sound = func_00101270(resident_get_system());

    if (upload_lists == 0)
    {
        if (buffer == 0)
        {
            return;
        }

        switch (load_step)
        {
            case 0:
                if (load_index >= load_count)
                {
                    loading = 0;
                    delete buffer;
                    buffer = 0;
                    return;
                }

                resident_queue_resource_request(queue, loads[load_index].file_key, buffer, 6, 0x34BC0, 0,
                                                0, 0, 1);
                load_step = 1;
                break;

            case 1:
                if (resident_find_resource_request(queue, loads[load_index].file_key, (u32)buffer, 6,
                                                   0xFFFFFFFF, 0) != 0)
                {
                    break;
                }

                if (func_0010EB90(sound, buffer, loads[load_index].slot * 2 + 1, 0) != 0)
                {
                    load_step = 2;
                }

                break;

            case 2:
                func_0010F250(sound, 0);

                if (sound->state == 0)
                {
                    variants[loads[load_index].slot] = loads[load_index].variant;
                    load_step = 0;
                    load_index++;
                }

                break;
        }
    }
    else
    {
        finished = false;

        do
        {
            switch (load_step)
            {
                case 0:
                    for (;;)
                    {
                        if (lists[list_index][load_index] != 0)
                        {
                            break;
                        }

                        if (++load_index < RESIDENT_SOUND_BANK_LIST_COUNT)
                        {
                            continue;
                        }

                        first_part = 1;
                        load_index = 0;

                        if (++list_index < RESIDENT_SOUND_BANK_SLOT_COUNT)
                        {
                            continue;
                        }

                        finished = true;
                        break;
                    }

                    if (list_index >= RESIDENT_SOUND_BANK_SLOT_COUNT)
                    {
                        loading = 0;
                        return;
                    }

                    load_step = 1;
                    part_index = 0;
                    break;

                case 1:
                    data = lists[list_index][load_index];

                    if (part_index >= data[0])
                    {
                        load_step = 0;

                        if (++load_index >= RESIDENT_SOUND_BANK_LIST_COUNT)
                        {
                            first_part = 1;
                            list_index++;
                            load_index = 0;
                        }

                        break;
                    }

                    part = (u8*)data
                           + (((ResidentSoundBankPart*)(data + 1))[part_index].sector << SOUND_BANK_SECTOR_SHIFT);

                    if (func_0010EB90(sound, part, list_index * 2 + 2, !first_part) != 0)
                    {
                        load_step = 2;
                        first_part = 0;
                        list_sizes[list_index] += func_00105F90(sound->stream, (const SoundFileHeader*)part);
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
                        load_step = 1;
                        part_index++;
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

/**
 * @brief Register bank data in the first free entry of a list unless loads are in progress.
 * @param set Sound bank set.
 * @param list List to add to.
 * @param data Bank data.
 */
void func_00120000(ResidentClass14FC90* set, s32 list, s32* data)
{
    s32 index;

    if (set->loading == 0)
    {
        for (index = 0; index < RESIDENT_SOUND_BANK_LIST_COUNT; index++)
        {
            if (set->lists[list][index] == 0)
            {
                set->lists[list][index] = data;
                return;
            }
        }
    }
}

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

/** @brief Detach the set and free its staging buffer. */
ResidentClass14FC90::~ResidentClass14FC90()
{
    lib_object_detach_owner(this);
    delete buffer;
}

/** @brief Construct an empty set with no banks assigned and register it with the update list. */
ResidentClass14FC90::ResidentClass14FC90() : buffer(0)
{
    s32 slot;

    buffer = 0;

    for (slot = 0; slot < RESIDENT_SOUND_BANK_SLOT_COUNT; slot++)
    {
        banks[slot] = 0;
        variants[slot] = -1;
    }

    loading = 0;
    unk24 = 0;
    D_001B6614->append_node(this, -1);
}

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

/** @brief Destroy the list. */
ResidentClass14FCB0::~ResidentClass14FCB0()
{
}

/**
 * @brief Set the next list in the chain.
 * @param attached List that follows this list.
 */
void ResidentClass14FCB0::func_004295B0(void* attached)
{
    next_list = static_cast<ResidentObjectList*>(attached);
}

/** @brief Do nothing. */
void ResidentClass14FCB0::func_004295C0()
{
}

/**
 * @brief Return the list's kind.
 * @return Nine.
 */
s32 ResidentClass14FCB0::func_00104730()
{
    return 9;
}

/** @brief Unregister the object if it is registered, then detach it and queue it for release. */
void ResidentClass14FD30::func_00104740()
{
    if (registered != 0)
    {
        ResidentClass14FD10& registration = *this;

        func_4486A0(&registration);
        func_4D0260(D_001B6640, static_cast<ResidentClass14FD10*>(this));
        registered = 0;
    }

    ResidentClass14FD30Base::func_00104740();
}

/**
 * @brief Copy another object's settings, record and transform state, and rebuild the image channel when it has one.
 * @param source Object to copy.
 */
void ResidentClass14FD30::copy_state(const ResidentClass14FD30* source)
{
    unk218 = source->unk218;
    unk21c = source->unk21c;
    unk220 = source->unk220;
    unk224 = source->unk224;
    elapsed = source->elapsed;
    hit_mask = source->hit_mask;
    hit_volume = source->hit_volume;
    record.next_offset = source->record.next_offset;
    record.storage_kind = source->record.storage_kind;
    record.index = source->record.index;
    record.key08 = source->record.key08;
    record.key0c = source->record.key0c;
    record.unk10[0] = source->record.unk10[0];
    record.unk10[1] = source->record.unk10[1];
    record.resolved_data = source->record.resolved_data;
    record.unk24[0] = source->record.unk24[0];
    record.unk24[1] = source->record.unk24[1];
    record.unk24[2] = source->record.unk24[2];
    record.unk24[3] = source->record.unk24[3];
    record.data = source->record.data;
    record.unk2c = source->record.unk2c;

    if (source->channel)
    {
        animated = 1;
        rebuild_image_channel(this);
    }

    position_source = source->position_source;
    camera = source->camera;
    faces_target = source->faces_target;
    unk2bd = source->unk2bd;
    unk2be = source->unk2be;
    animated = source->animated;
    registered = source->registered;
    unk2c1 = source->unk2c1;
    shared_image = source->shared_image;
    follow_position = source->follow_position;
    follow_camera = source->follow_camera;
    unk2c5 = source->unk2c5;
    unk2c6 = source->unk2c6;
    unk2c7 = source->unk2c7;
    ResidentClass14FD30Base::copy_offset_transform_state(source);
}

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

/**
 * @brief Find the first object from a start node whose hit box a sphere touches, turning it to face the sphere.
 * @param list Object list to walk.
 * @param mask Bits an object's hit mask must share.
 * @param point Sphere centre in xyz and radius in w.
 * @param start Node to start from, or null for the first; the walk also starts from the first while unk8c is set.
 * @return The object hit, or null.
 */
ResidentClass14FD30* func_00120A70(ResidentClass14FCB0* list, u32 mask, const ResidentVector4* point, ResidentClass14FD30* start)
{
    ResidentClass14FD30* node;

    if (start == 0 || list->unk8c != 0)
    {
        start = static_cast<ResidentClass14FD30*>(list->sentinel.next);
    }

    node = start;

    do
    {
        if (!at_list_end(&list->sentinel, node) && (mask & node->hit_mask) != 0 && (node->registered || node->shared_image))
        {
            ResidentVector4 world;
            ResidentVector4 local;
            ResidentHitBox* box = node->hit_volume;

            world = *point;
            world.w = 1.0f;
            vu0_apply_matrix(&box->inverse_transform, &world, &local);

            const ResidentVector4* extents = &box->half_extents;
            float x = extents->x + point->w;
            float y = extents->y + point->w;
            float z = extents->z + point->w;

            if (local.x >= -x && local.x <= x && local.z >= -z && local.z <= z && local.y >= -y && local.y <= y)
            {
                if (node->faces_target)
                {
                    func_001210B0(node, &world);
                }

                return node;
            }
        }

        node = static_cast<ResidentClass14FD30*>(node->next);
    } while (node != start);

    return 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00104770__19ResidentClass14FCB0Fv);

/**
 * @brief Copy the orientation quaternion.
 * @param value Source quaternion.
 */
void ResidentClass14FD30::set_orientation(const ResidentVector4* value)
{
    transform_dirty = 1;
    orientation = *value;
}

/**
 * @brief Copy the position.
 * @param value Source vector.
 */
void ResidentClass14FD30::set_translation_vector(const ResidentVector4* value)
{
    transform_dirty = 1;
    translation = *value;
}

/**
 * @brief Remove a registered node, and make the next two hit tests start from the first node.
 * @param object Node to remove.
 */
void ResidentClass14FCB0::remove_node(void* object)
{
    unk8c = 2;
    D_001B65D0 |= 1;
    ResidentObjectList::remove_node(object);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120F20);

/**
 * @brief Turn the image animation on or off, rebuilding the image channel while the object is registered.
 * @param object Object to update.
 * @param animated Nonzero to animate the record through an image channel.
 */
void func_00120FE0(ResidentClass14FD30* object, u8 animated)
{
    object->animated = animated;
    rebuild_image_channel(object);
}

/**
 * @brief Update the transform, turning it to face a point when asked to, then build the image's projection matrix.
 * @param object Object to update.
 * @param target Point to face, or null for the plain transform.
 */
void func_001210B0(ResidentClass14FD30* object, const ResidentVector4* target)
{
    ResidentImageHeader* image;
    s32 width;
    s32 height;

    if (object->faces_target && target)
    {
        ResidentVector4 position;
        ResidentVector4 direction;
        ResidentMatrix matrix;

        if (!object->matrix_ready)
        {
            object->update_transform_matrix();
        }

        position.x = object->transform.rows[0].w;
        position.y = object->transform.rows[1].w;
        position.z = object->transform.rows[2].w;
        position.w = 1.0f;
        subtract_xyz(&direction, target, &position);
        func_4CBD20(&matrix, &position, &direction, 0.0f);
        matrix.rows[0].w = position.x;
        matrix.rows[1].w = position.y;
        matrix.rows[2].w = position.z;
        object->transform = matrix;
    }
    else
    {
        object->update_transform_matrix();
    }

    if (object->shared_image)
    {
        image = &static_cast<ResidentDisplayManager*>(D_001B661C)->images[object->shared_image - 1];
    }
    else
    {
        u8* data = object->record.data;
        image = (ResidentImageHeader*)(data + ((u32*)data)[3]);
    }

    width = 1 << image->width_log2;
    height = 1 << image->height_log2;

    if (object->unk2c5)
    {
        func_4CFB20(&object->unk270, &object->transform, object->unk218, width, height, object->unk220, object->unk224);
    }
    else
    {
        func_4CFC50(&object->unk270, &object->transform, object->unk218, width, height, object->unk220, object->unk224);
    }
}

/**
 * @brief Point the record at a resource's data, register the object and rebuild its image channel.
 * @param object Object to update.
 * @param resource Resource whose data follows a 16-byte prefix.
 */
void func_001212A0(ResidentClass14FD30* object, u8* resource)
{
    object->record.data = resource + 0x10;
    object->record.storage_kind = 0;
    object->record.resolved_data = 0;
    FlushCache(0);
    object->record.next_offset = 0;
    object->registered = 1;
    func_4D02E0(D_001B6640, static_cast<ResidentClass14FD10*>(object));
    rebuild_image_channel(object);
}

/** @brief Unregister the object and destroy its image channel. */
ResidentClass14FD30::~ResidentClass14FD30()
{
    if (registered)
    {
        ResidentClass14FD10& registration = *this;

        func_4486A0(&registration);
        func_4D0260(D_001B6640, static_cast<ResidentClass14FD10*>(this));
    }

    delete channel;
}

/** @brief Construct an unregistered object with no channel and the image centred. */
ResidentClass14FD30::ResidentClass14FD30()
{
    unk220 = 0.5f;
    unk224 = 0.5f;
    elapsed = 0.0f;
    unk2bd = 0;
    registered = 0;
    shared_image = 0;
    follow_position = 0;
    follow_camera = 0;
    unk2c5 = 0;
    unk2c6 = 0;
    unk2c7 = 0;
    unk6c = 0xD00;
    channel = 0;
}

/**
 * @brief Return zero.
 * @return Zero.
 */
s32 ResidentClass14FD10::func_00121570()
{
    return 0;
}

/**
 * @brief Read the stored transformation matrix.
 * @return Matrix pointer.
 */
const ResidentMatrix* ResidentClass14FD30::get_transform_matrix()
{
    return &transform;
}

/**
 * @brief Read the additional local translation.
 * @return Stored translation.
 */
const ResidentVector4* ResidentClass14FD30::get_offset_translation() const
{
    return &offset_translation;
}

/**
 * @brief Read the additional local rotation.
 * @return Stored quaternion.
 */
const ResidentVector4* ResidentClass14FD30::get_offset_rotation() const
{
    return &offset_rotation;
}

/**
 * @brief Read the additional local scale.
 * @return Stored scale.
 */
const ResidentVector4* ResidentClass14FD30::get_offset_scale() const
{
    return &offset_scale;
}

/** @brief Draw in the main list (bucket zero). */
void ResidentClass14FD30::set_default_draw_bucket()
{
    draw_bucket = 0;
}

/** @brief Do nothing. */
void ResidentClass14FD30::func_00104780()
{
}

/**
 * @brief Give no centre for Lib's oriented-box visibility test.
 * @param output Unused.
 * @return Zero, so the test is skipped.
 */
s32 ResidentClass14FD30::get_box_cull_center(void* output)
{
    return 0;
}

/**
 * @brief Don't fade near the camera.
 * @param value Distance in front of the camera over the fade range.
 * @param mode Unused.
 * @return Whether the value is negative.
 */
bool ResidentClass14FD30::set_fade_alpha(float value, float mode)
{
    return value < 0.0f;
}

/**
 * @brief Return Lib's shared default bounding sphere.
 * @return Bounding sphere.
 */
const ResidentVector4* ResidentClass14FD30::get_bounding_sphere()
{
    return &D_50CD30;
}

/**
 * @brief Do nothing.
 * @param matrix Unused.
 * @param context Unused.
 */
void ResidentClass14FD30::build_packet(const void* matrix, void* context)
{
}

/**
 * @brief Don't copy this object.
 * @return Null.
 */
ResidentClass14FD30Base* ResidentClass14FD30::clone()
{
    return 0;
}

/** @brief Do nothing; this object has no copies. */
void ResidentClass14FD30::release_clone()
{
}

/**
 * @brief Copy the position.
 * @param value Source vector.
 */
void ResidentClass14FD30::copy_translation(const ResidentVector4* value)
{
    transform_dirty = 1;
    translation = *value;
}

/**
 * @brief Set the position and a w component of one.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void ResidentClass14FD30::set_translation(float x, float y, float z)
{
    transform_dirty = 1;
    translation.x = x;
    translation.y = y;
    translation.z = z;
    translation.w = 1.0f;
}

/**
 * @brief Set all four orientation components.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 */
void ResidentClass14FD30::set_orientation_components(float x, float y, float z, float w)
{
    transform_dirty = 1;
    orientation.x = x;
    orientation.y = y;
    orientation.z = z;
    orientation.w = w;
}

/**
 * @brief Copy the orientation quaternion.
 * @param value Source quaternion.
 */
void ResidentClass14FD30::copy_orientation(const ResidentVector4* value)
{
    transform_dirty = 1;
    orientation = *value;
}

/**
 * @brief Convert a rotation into the orientation.
 * @param value Source rotation.
 */
void ResidentClass14FD30::convert_rotation(const ResidentVector4* value)
{
    transform_dirty = 1;
    func_4CE4C0(&orientation, value);
}

/**
 * @brief Convert a rotation into the orientation.
 * @param value Source rotation.
 */
void ResidentClass14FD30::set_rotation_vector(const ResidentVector4* value)
{
    transform_dirty = 1;
    func_4CE4C0(&orientation, value);
}

/**
 * @brief Convert three rotation components into the orientation.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void ResidentClass14FD30::set_rotation(float x, float y, float z)
{
    ResidentVector4 rotation;

    transform_dirty = 1;
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
    rotation.w = 1.0f;
    func_4CE4C0(&orientation, &rotation);
}

/**
 * @brief Copy the scale.
 * @param value Source vector.
 */
void ResidentClass14FD30::copy_scale(const ResidentVector4* value)
{
    transform_dirty = 1;
    scale = *value;
}

/**
 * @brief Copy the scale.
 * @param value Source vector.
 */
void ResidentClass14FD30::set_scale_vector(const ResidentVector4* value)
{
    transform_dirty = 1;
    scale = *value;
}

/**
 * @brief Set the scale's xyz components.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void ResidentClass14FD30::set_scale(float x, float y, float z)
{
    transform_dirty = 1;
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

/**
 * @brief Return zero.
 * @return Zero.
 */
s32 ResidentClass14FD30::func_001217D0()
{
    return 0;
}

/**
 * @brief Get the record while the object is registered.
 * @return The record, or null.
 */
void* ResidentClass14FD30::func_001217E0()
{
    if (registered != 0)
    {
        return &record;
    }

    return 0;
}
