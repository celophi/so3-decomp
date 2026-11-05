#include "include_asm.h"
#include "vu0.h"
#include "overlays/lib/blend_transform.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/memory_card.h"
#include "overlays/lib/image_capture.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"

#include "sdk/main/libmc_0012BB10.h"
#include "overlays/lib/text_004CD3A0.h"
#include "main/resident_00101260.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_0013CD50.h"

extern "C" {

void func_004486A0(void* object);
void func_00448250(void* object);

typedef struct WordSetterOwnertext_00429B00
{
    u8 unk00[0x24];
    u32 unk24;
    u8 unk28[0x400];
    u32 unk428;
} WordSetterOwnertext_00429B00;



typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x22];
    PackedModePair at22;
} PackedModesOwner;

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00429B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00429BF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00429DF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00429F70);

void func_0042A1B0(void* object);
void func_0042A120(void* object) { func_0042A1B0(object); }

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A1B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A2E0);

/** Set the high packed mode at 0x22 and record whether either mode equals four. */
void func_0042A340(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.highMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

/**
 * @brief Read the word at offset 0x10 in a sequence state.
 * @param state Sequence state to read.
 * @return The stored word.
 */
u32 func_0042A3A0(const LibTextSequenceState* state) {
    return state->unk10;
}

/**
 * @brief Read the signed halfword at offset 0x18 in a sequence state.
 * @param state Sequence state to read.
 * @return The stored count.
 */
s16 func_0042A3B0(const LibTextSequenceState* state) {
    return state->unk18;
}

/**
 * @brief Read the signed halfword at offset 0x1A in a sequence state.
 * @param state Sequence state to read.
 * @return The stored count.
 */
s16 func_0042A3C0(const LibTextSequenceState* state) {
    return state->unk1A;
}

s32 func_0042A3D0(void* object)
{
    return 0;
}

s32 func_0042A3E0(void* object)
{
    return 0;
}

s32 func_0042A3F0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A400);

/**
 * @brief Clear four consecutive words.
 * @param words Pointer to the first word to clear.
 */
void func_0042A460(u32* words) {
    words[0] = 0;
    words[1] = 0;
    words[2] = 0;
    words[3] = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A480);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A4E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A5D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A620);

/**
 * @brief Read the buffer pointer from a sequence state.
 * @param state Sequence state to read.
 * @return The stored buffer pointer.
 */
void* func_0042A6C0(const LibTextSequenceState* state) {
    return state->unk04;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A6D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A770);

/**
 * @brief Default append handler for a channel.
 * @param object Channel object receiving the request.
 * @param value Channel value.
 * @param optional1 Optional second component.
 * @param optional2 Optional third component.
 * @param key Sort value.
 * @return Status.
 */
s32 func_0042A7C0(void* object, const void* value, const void* optional1, const void* optional2, float key) {
    return 0;
}

/**
 * @brief Default set handler for a channel.
 * @param object Channel object receiving the request.
 * @param index Entry index.
 * @param key Sort value.
 * @param value Channel value.
 * @return Status.
 */
s32 func_0042A7D0(void* object, s32 index, float key, const void* value) {
    return 0;
}

/**
 * @brief Default insert handler for a channel.
 * @param object Channel object receiving the request.
 * @param index Entry index.
 * @param key Sort value.
 * @param value Channel value.
 * @return Status.
 */
s32 func_0042A7E0(void* object, s32 index, float key, const void* value) {
    return 0;
}

/**
 * @brief Default channel entry reader.
 * @param object Channel object receiving the request.
 * @param index Entry index.
 * @param key Receives the sort value.
 * @param value Receives the channel value.
 * @return Status.
 */
s32 func_0042A7F0(void* object, s32 index, float* key, void* value) {
    return 0;
}

/**
 * @brief Default channel add handler.
 * @param object Channel object receiving the request.
 * @param value Channel value.
 * @param key Sort value.
 */
void func_0042A800(void* object, const void* value, float key) {
}

/**
 * @brief Perform no work for the default channel handler.
 * @param object Channel object receiving the request.
 */
void func_0042A810(void* object) {
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A820);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A880);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A8B0);

void func_0042A8E0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A8F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042A920);

/** @brief Clear the intrusive owner and call the transform release hook. */
void func_0042AA00(LibTransformOwner* object)
{
    object->owner = 0;
    object->LibTransformOwner::destroy();
}

s32 func_0042AA20(void* object)
{
    return 0;
}

s32 func_0042AA30(void* object)
{
    return 128;
}

s32 func_0042AA40(void* object)
{
    return 0;
}

s32 func_0042AA50(void* object)
{
    return 0;
}

void* func_0042AA60(void* object, void* value)
{
    return value;
}

void* func_0042AA70(void* object, void* value)
{
    return value;
}

s32 func_0042AA80(void* object)
{
    return 0;
}

s32 func_0042AA90(void* object)
{
    return 0;
}

/**
 * @brief Test whether the word at offset 0x704 is nonzero.
 * @param object Buffer state to inspect.
 * @return One if the word is nonzero, otherwise zero.
 */
u32 func_0042AAA0(const LibTextBufferState* object) {
    return object->unk704 != 0;
}

/**
 * @brief Return the embedded buffer at byte offset 0x79C.
 * @param object Pointer to the containing object.
 * @return Pointer to the embedded buffer.
 */
u8* func_0042AAB0(LibTextBufferState* object) {
    return object->unk79C;
}

/**
 * @brief Read the byte at offset 0x794 in a buffer state.
 * @param object Buffer state to read.
 * @return The stored byte.
 */
u8 func_0042AAC0(const LibTextBufferState* object) {
    return object->unk794;
}

/**
 * @brief Recompute the RGBA factor from the stored base and modulation factors.
 * @param object Rendering state whose combined factor is updated.
 */
void lib_update_color_factor(LibTextBufferState* object)
{
    vu0_multiply_xyzw(&object->combined_color_factor, &object->base_color_factor, &object->color_modulation);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042AAF0);

/**
 * @brief Access the stored RGBA modulation factor.
 * @param object Rendering state containing the factor.
 * @return Pointer to the packed four-float RGBA factor.
 */
unsigned __int128* lib_get_color_modulation(LibTextBufferState* object)
{
    return &object->color_modulation;
}

/**
 * @brief Store the low byte at 0x210 and set bit 3 at 0x59D.
 * @param object Buffer state containing the value and flag bytes.
 * @param value Value whose low byte is stored.
 */
void func_0042AB30(LibTextBufferState* object, u32 value) {
    object->unk210 = value;
    object->unk59d_3 = 1;
}

}

/**
 * @brief Apply the source blend mode and copy its inherited transform state.
 * @param source Blend transform to copy.
 */
void LibBlendTransform::copy_blend_state(const LibBlendTransform* source)
{
    set_blend_mode(source->blend_mode);
    LibTransform::copy_offset_transform_state(source);
}

/**
 * @brief Store the blend mode.
 * @param mode Blend mode to store.
 */
void LibBlendTransform::set_blend_mode(u8 mode)
{
    blend_mode = mode;
}

extern "C" {

/**
 * @brief Set the bytes at offsets 0x62 and 0x64 in a buffer state.
 * @param object Buffer state to update.
 */
void func_0042ABB0(LibTextBufferState* object) {
    object->unk64 = 0;
    object->unk62 = 1;
}

s32 func_004A4570(void* object);
s32 func_0042ABC0(void* object) { return func_004A4570(object); }

/**
 * @brief Copy a 16-byte value to offset 0x820 in a buffer state.
 * @param object Buffer state to update.
 * @param value 16-byte aligned source value.
 */
void func_0042ABE0(LibTextBufferState* object, const unsigned __int128* value) {
    object->unk820 = *value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042ABF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042AC40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042AC90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042AD80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042ADE0);

/**
 * @brief Copy the byte at offset 0x83C to offset 0x60.
 * @param object Buffer state to update.
 */
void func_0042AE70(LibTextBufferState* object) {
    object->unk60 = object->unk83C;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042AE80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042AEC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042B000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042B110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042C450);

s32 func_0042C5B0(void* object)
{
    return 256;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042C5C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042CC80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042D0B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042D760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042D830);

/** @brief Upload the palette image at D_4EC600. */
void lib_upload_default_palette(void)
{
    func_004D8C20(D_4EC600, 30);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042D970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042D980);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042D990);

s32 func_0042D9A0(void* object)
{
    return 34;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042D9B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042DCE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042DFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042E240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042E6E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042E710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042E860);

/**
 * @brief Return the input pointer unchanged.
 * @param object Pointer to return.
 * @return The input pointer.
 */
void* func_0042E9A0(void* object) {
    return object;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042E9B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042EA60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042EAC0);

s32 func_0042EB20(void* object)
{
    return 3;
}

/**
 * @brief Store a word at offset 0x14 and mark the state active at 0x0C.
 * @param state State to update.
 * @param value Word to store.
 */
void func_0042EB30(LibTextValueState* state, u32 value) {
    state->unk14 = value;
    state->unk0C = 1;
}

s32 func_0042EB40(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042EB50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042EBE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042EF30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F0D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F160);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F3E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F420);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042F550);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00430AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00430B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00430CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00430E00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00431020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00431090);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00431680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004316C0);

s32 func_00431720(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00431730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00431770);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004317B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004317F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00431AB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00431E60);

/**
 * @brief Find a slot that can start a file operation: the card library is set up, the slot is open, its card is
 *        ready and its last operation finished.
 * @param card Memory card object.
 * @param slot Slot index.
 * @return The slot's record, or null.
 */
static inline LibMemoryCardSlot* lib_memory_card_idle_slot(LibMemoryCard* card, u32 slot)
{
    LibMemoryCardSlot* record;

    if (!card->initialized || slot >= LIB_MEMORY_CARD_SLOT_COUNT)
    {
        return 0;
    }

    record = &card->slots[slot];

    if (record->card_state != LIB_MEMORY_CARD_STATE_READY)
    {
        return 0;
    }

    if ((record->status & LIB_MEMORY_CARD_STATUS_GROUP_MASK) != LIB_MEMORY_CARD_STATUS_DONE)
    {
        return 0;
    }

    if (!(record->state_flags & LIB_MEMORY_CARD_SLOT_OPEN))
    {
        return 0;
    }

    return record;
}

/**
 * @brief Start an operation: an idle slot takes it as its status, a running one queues it in the busy byte.
 * @param record Slot record.
 * @param operation Operation code.
 */
static inline void lib_memory_card_start_operation(LibMemoryCardSlot* record, u8 operation)
{
    if (record->status == LIB_MEMORY_CARD_STATUS_DONE)
    {
        record->status = operation;
    }
    else
    {
        record->busy = operation;
    }
}

/**
 * @brief Start looking for a file on the card in a slot.
 * @param card Memory card object.
 * @param slot Slot index.
 * @param name File to look for.
 * @param unk7C Stored in the slot at 0x7C.
 * @param unk78 Stored in the slot at 0x78.
 * @param buffer Buffer the probe reads into; it is aligned to 64 bytes first.
 * @return 0 once started, -1 when the slot can't start an operation.
 */
s32 lib_memory_card_probe_file(LibMemoryCard* card, u32 slot, const char* name, s32 unk7C, s32 unk78, u8* buffer)
{
    LibMemoryCardSlot* record = lib_memory_card_idle_slot(card, slot);

    if (!record)
    {
        return -1;
    }

    lib_memory_card_start_operation(record, LIB_MEMORY_CARD_OP_PROBE_FILE);
    record->result = 0;
    record->buffer = reinterpret_cast<u8*>((reinterpret_cast<u32>(buffer) + 63) & ~63);
    record->unk78 = unk78;
    record->unk7C = unk7C;
    strncpy_guess(record->name, name, sizeof(record->name));
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432090);

/**
 * @brief Read the result of a slot's last operation.
 * @param card Memory card object.
 * @param slot Slot index.
 * @param result Receives the result when one is ready; cleared first. May be null.
 * @return 1 with a result, 0 while the slot is busy or its status has no result, -1 when the card library isn't set
 *         up or the slot doesn't exist.
 */
s32 lib_memory_card_get_result(LibMemoryCard* card, s32 slot, s32* result)
{
    if (result)
    {
        *result = 0;
    }

    if (!card->initialized || slot >= LIB_MEMORY_CARD_SLOT_COUNT)
    {
        return -1;
    }

    if (card->slots[slot].busy)
    {
        return 0;
    }

    u8 status = card->slots[slot].status;
    if (status != 0 && (status & LIB_MEMORY_CARD_STATUS_GROUP_MASK) != LIB_MEMORY_CARD_STATUS_DONE)
    {
        return 0;
    }

    if (result)
    {
        *result = card->slots[slot].result;
    }

    return 1;
}

/**
 * @brief Start a file transfer on the card in a slot.
 * @param card Memory card object.
 * @param slot Slot index.
 * @param request Files to transfer; the slot keeps the pointer until it finishes.
 * @return 0 once started, -1 when the slot can't start an operation.
 */
s32 lib_memory_card_start_transfer(LibMemoryCard* card, u32 slot, LibCardFileRequest* request)
{
    LibMemoryCardSlot* record = lib_memory_card_idle_slot(card, slot);

    if (!record)
    {
        return -1;
    }

    lib_memory_card_start_operation(record, LIB_MEMORY_CARD_OP_TRANSFER);
    record->result = 0;
    record->unk44 = 0;
    record->request = request;
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004323E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004324D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004325A0);

/**
 * @brief Open a slot that isn't running anything: clear its record and mark it open.
 * @param card Memory card object.
 * @param slot Slot index.
 * @param enabled Low bit goes to bit 4 of the slot's config.
 * @param flags Low two bits go to bits 0-1 of the slot's config.
 */
void lib_memory_card_open_slot(LibMemoryCard* card, s32 slot, u32 enabled, u32 flags)
{
    LibMemoryCardSlot* record;

    if (!card->initialized || slot < 0 || slot >= LIB_MEMORY_CARD_SLOT_COUNT)
    {
        return;
    }

    record = &card->slots[slot];

    if (record->status)
    {
        return;
    }

    memset_guess(record, 0, sizeof(LibMemoryCardSlot));
    record->config = ((enabled & 1) << 4) | (flags & 3);
    record->status = LIB_MEMORY_CARD_STATUS_DONE;
    record->state_flags = LIB_MEMORY_CARD_SLOT_OPEN;
}

/** Store the word at receiver offset 0x24. */
void func_00432710(void* object, u32 value)
{
    WordSetterOwnertext_00429B00* receiver = (WordSetterOwnertext_00429B00*)object;
    receiver->unk24 = value;
}

/** Static storage the card's slot records are carved from: both records plus room to align them. */
extern "C" u8 lib_memory_card_slot_storage[];

/**
 * @brief Set up the card library and the slot records, then add the card to an update list.
 * @param card Memory card object.
 * @param list List to add the card to, or null.
 * @return 1 once set up, 0 when it already was or the card library failed to start.
 */
s32 lib_memory_card_init(LibMemoryCard* card, LibUpdateList* list)
{
    if (card->initialized || sceMcInit() != 0)
    {
        return 0;
    }

    card->slot_storage = lib_memory_card_slot_storage;

    if (!card->slot_storage)
    {
        return 0;
    }

    memset_guess(card->slot_storage, 0, LIB_MEMORY_CARD_SLOT_COUNT * sizeof(LibMemoryCardSlot) + 64);
    card->slots = reinterpret_cast<LibMemoryCardSlot*>((reinterpret_cast<u32>(card->slot_storage) + 63) & ~63);
    card->initialized = 1;
    card->unk1e = 0;

    if (list)
    {
        list->append_node(card, -1);
    }

    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432900);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004329C0);

/** @brief Mark the packet being stored as done and finish the capture. */
void LibImageCapture::on_store_complete()
{
    stored[storing] = 1;
    lib_finish_packet(this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432A80);

/**
 * @brief Let the store thread know the store packet's transfer is over.
 * @param channel DMA channel number.
 */
void LibImageCapture::complete_dma(u32 channel)
{
    func_001140F0(g_vif1_dma_queue);
    iSignalSema(D_005081D0.semaphore);
}

/**
 * @brief Hand the packet being stored to the store thread and wake it.
 * @param channel DMA channel number.
 */
void LibImageCapture::submit_dma(u32 channel)
{
    dma_pending = 1;
    u8 index = storing;
    void* destination = destinations[index];
    D_005081D0.packet = reinterpret_cast<GsStoreImage*>(reinterpret_cast<u32>(&packets[index]) | UNCACHED_SEGMENT);
    D_005081D0.destination = destination;
    D_005081D0.capture = this;

    if (!func_00114DD0(&D_005081D0))
    {
        D_005081D0.wake_failed = 1;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004332F0);

/** @brief Queue the capture's DMA, or hand it to the packet queue when unk65 is set. */
void LibImageCapture::render()
{
    if (!unk65)
    {
        func_00114100(g_vif1_dma_queue, this);
    }
    else
    {
        func_004DC4F0(D_001B65DC, 6, 0, this, 0, 0);
    }
}

/**
 * @brief Queue a copy of a VRAM rectangle into memory, in the next of the capture's two store packets.
 * @param capture Capture object.
 * @param destination Memory the pixels are copied to.
 * @param base_pointer Source buffer address in 64-word blocks.
 * @param buffer_width Source buffer width in 64-pixel units.
 * @param pixel_format Source pixel format.
 * @param x Left edge of the rectangle.
 * @param y Top edge of the rectangle.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
void lib_image_capture_store(LibImageCapture* capture, void* destination, s16 base_pointer, s16 buffer_width,
                             s16 pixel_format, s16 x, s16 y, s16 width, s16 height)
{
    capture->current ^= 1;
    sceGsSetDefStoreImage(reinterpret_cast<GsStoreImage*>(reinterpret_cast<u32>(&capture->packets[capture->current]) | UNCACHED_SEGMENT),
                          base_pointer, buffer_width, pixel_format, x, y, width, height);
    capture->destinations[capture->current] = destination;
    capture->stored[capture->current] = 0;
    capture->pending = 1;
}

/**
 * @brief Pick the waiting packet to store, if there is one.
 * @param matrix Matrix supplied by the caller; unused.
 * @param context Opaque caller context; unused.
 */
void LibImageCapture::build_packet(const void* matrix, void* context)
{
    if (!pending)
    {
        unk63 = 0;
        return;
    }

    storing = current;
    unk63 = 1;
    pending = 0;
}

/** @brief Destroy the capture. */
LibImageCapture::~LibImageCapture()
{
}

/** @brief Construct the capture. */
LibImageCapture::LibImageCapture()
{
    set_type_id(0x1200);
    default_draw_bucket = 9;
    current = 0;
    pending = 0;
    unk65 = 0;
    set_draw_flags(draw_flags | LIB_DRAW_FLAG_0400);
    FlushCache(0);
}

/** @brief Use the capture's own draw bucket. */
void LibImageCapture::set_default_draw_bucket()
{
    draw_bucket = default_draw_bucket;
}

/** @brief Free the shared font (archive resources 8 and 9) and remove it from the entry table. */
void lib_release_shared_font(void)
{
    ResidentEntryTable* table = resident_get_entry_table(resident_get_system());
    void* font = (void*)resident_find_entry(table, LIB_ENTRY_SHARED_FONT);
    resident_remove_entry(table, LIB_ENTRY_SHARED_FONT);
    free_guess(font);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004336E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433790);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433880);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004339F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433AA0);

void* func_00433BE0(u32 alignment, u32 size) { return memalign(alignment, size); }

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433C00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433C70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433EF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004341F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434300);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434330);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004344D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004348E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004349D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434CE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434D40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434DB0);

void func_00434E20(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434E30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434EA0);

void* func_00434F10(void* object)
{
    return (u8*)object + 0x230;
}

s32 func_00434F20(void* object)
{
    return 6;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434F30);

void func_00434FA0(void* object)
{
    func_004486A0((u8*)object + 0x5A4);
    func_00448250(object);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00434FD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00435020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00435070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004350C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00435110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00435150);

/** Store the word at receiver offset 0x428. */
void func_00435190(void* object, u32 value)
{
    WordSetterOwnertext_00429B00* receiver = (WordSetterOwnertext_00429B00*)object;
    receiver->unk428 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004351A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004351D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00435270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004352B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004352E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00435840);

}
