#include "include_asm.h"
#include "main/resident_00101550.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_001001E0.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"

struct ResidentPointer90
{
    u8 unk00[0x90];
    void* unk90;
};

struct ResidentPointer100
{
    u8 unk00[0x100];
    void* unk100;
};

struct ResidentSignedByteBC
{
    u8 unk00[0xBC];
    s8 unkBC;
};

void func_00101550(void* object)
{
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00101560);

/**
 * @brief Decode an LZ payload with 16-bit literals and word offsets.
 * @param decoder Resident decoder; unused.
 * @param source Compressed word stream, without its block header.
 * @param destination Output word buffer.
 * @return One when a token with zero distance ends the stream.
 */
INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_decode_lz_words);

/**
 * @brief Decode an LZ payload with byte literals, back references, and runs of repeated bytes.
 * @param decoder Resident decoder; unused.
 * @param source Compressed byte stream, without its block header.
 * @param destination Output byte buffer.
 * @param decoded_size Output byte count at which decoding stops.
 * @return One after decoding.
 */
INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_decode_lz_runs);

/**
 * @brief Decode an LZ payload with byte literals and back references.
 * @param decoder Resident decoder; unused.
 * @param source Compressed byte stream, without its block header.
 * @param destination Output byte buffer.
 * @return One when a token with zero distance ends the stream.
 */
INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_decode_lz_bytes);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00102340);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_decode_resource_block);

/**
 * @brief Allocate an output buffer for the selected compression block.
 *
 * Aligned allocations use the selected heap when one is set. Otherwise allocation
 * uses the default C allocator.
 *
 * @param decoder Resident decoder; unused.
 * @param source First block header.
 * @param index Links to follow; nonpositive values select the first block.
 * @param aligned Nonzero reserves space for aligning the payload to 128 bytes.
 * @return Allocation base, or null when the block or storage is unavailable.
 */
extern "C" u8* resident_allocate_decode_buffer(ResidentDecodeObject* decoder, ResidentResourceHeader* source,
                                             s32 index, s32 aligned)
{
    if (aligned && g_allocation_heap != 0)
    {
        for (s32 block_index = 0; block_index < index; block_index++)
        {
            u32 next_offset = source->next_offset;

            if (next_offset == 0)
            {
                return 0;
            }

            source = reinterpret_cast<ResidentResourceHeader*>(reinterpret_cast<u8*>(source) + next_offset);
        }

        u8* allocation = static_cast<u8*>(resident_heap_allocate(g_allocation_heap, source->decoded_size + 128));
        u32 padding = 128 - ((u32)allocation & 127);

        return static_cast<u8*>(resident_heap_resize(allocation, source->decoded_size + padding));
    }

    for (s32 block_index = 0; block_index < index; block_index++)
    {
        u32 next_offset = source->next_offset;

        if (next_offset == 0)
        {
            return 0;
        }

        source = reinterpret_cast<ResidentResourceHeader*>(reinterpret_cast<u8*>(source) + next_offset);
    }

    if (aligned)
    {
        u8* allocation = static_cast<u8*>(malloc_guess(source->decoded_size + 128));
        u32 padding = 128 - ((u32)allocation & 127);

        return static_cast<u8*>(func_0013B858(allocation, source->decoded_size + padding));
    }

    return static_cast<u8*>(malloc_guess(source->decoded_size));
}

/**
 * @brief Find a compression block by following its relative links.
 * @param decoder Resident decoder; unused.
 * @param source First block header.
 * @param index Links to follow; nonpositive values select the first block.
 * @return Selected header, or null when the chain ends.
 */
extern "C" ResidentResourceHeader* resident_find_resource_block(ResidentDecodeObject* decoder,
                                                              ResidentResourceHeader* source, s32 index)
{
    for (s32 block_index = 0; block_index < index; block_index++)
    {
        u32 next_offset = source->next_offset;

        if (next_offset == 0)
        {
            return 0;
        }

        source = reinterpret_cast<ResidentResourceHeader*>(reinterpret_cast<u8*>(source) + next_offset);
    }

    return source;
}

void func_00102A90(void* object)
{
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_update_resource_queue);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00102AE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00102B30);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00102C90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00102D00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00102D50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001031C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001034E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00103510);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00103580);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_find_resource_request);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001037E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00103AE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_cancel_resource_requests);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_queue_resource_request);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001041C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00104370);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001043F0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", __dt__21ResidentResourceQueueFv);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001044F0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00104600);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00104680);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001046E0);

s32 func_00104730(void* object)
{
    return 3;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00104740);

void func_00104770(void* object)
{
}

void func_00104780(void* object)
{
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00104790);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00104C90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105210);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105680);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105770);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001058C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105A20);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105AE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105BF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105DD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105F90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105FB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001060C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00106160);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00106240);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001065B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00106640);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001066D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00106780);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001068C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00106A50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00107020);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001070B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001071A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00107230);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00107250);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00107420);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00107530);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00107730);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00107940);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00107B10);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00107B60);

void func_00107D90(void* receiver, void* value)
{
    ResidentPointer90* object = (ResidentPointer90*)receiver;
    func_0010A080(object->unk90, (const s32*)value);
}

void func_00107DB0(void* receiver, void* argument)
{
    ResidentPointer90* object = (ResidentPointer90*)receiver;
    func_0010A0B0(object->unk90, (const s32*)argument);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00107DD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00108000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00108220);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00108430);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00108640);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00108800);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00108A00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00108C40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00108E10);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", __dt__19ResidentSoundStreamFv);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001093E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109510);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109800);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109BE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109C80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109CB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109D50);

void func_00109F20(void* receiver)
{
    ResidentPointer100* object = (ResidentPointer100*)receiver;
    func_00109510(object->unk100);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109F40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109FB0);

s8 func_00109FD0(const void* object)
{
    const ResidentSignedByteBC* receiver = (const ResidentSignedByteBC*)object;
    return receiver->unkBC;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109FE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_0010A000);
