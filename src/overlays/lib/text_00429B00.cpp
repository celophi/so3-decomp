#include "include_asm.h"
#include "vu0.h"
#include "overlays/lib/blend_transform.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/text_004CD3A0.h"
#include "sdk/main/libc_guess_00137290.h"

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
void func_0042AA00(LibClass178A90* object)
{
    object->owner = 0;
    object->LibClass178A90::func_003EF740();
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
    LibTransform::copy_transform_state(source);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_0042D940);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00431F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432090);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432310);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004323E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004324D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004325A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432660);

/** Store the word at receiver offset 0x24. */
void func_00432710(void* object, u32 value)
{
    WordSetterOwnertext_00429B00* receiver = (WordSetterOwnertext_00429B00*)object;
    receiver->unk24 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432900);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004329C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432A50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00432A80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004332F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433340);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004333A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433480);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433580);

void func_00433650(void* object)
{
    u8* bytes = (u8*)object;
    bytes[0x60] = bytes[0x94];
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004336E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433790);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433880);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_004339F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00429B00", func_00433AA0);

void* func_00433BE0(u32 alignment, u32 size) { return func_00139700(alignment, size); }

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
