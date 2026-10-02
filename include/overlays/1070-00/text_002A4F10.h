#ifndef SO3_OVERLAYS_1070_00_TEXT_002A4F10_H
#define SO3_OVERLAYS_1070_00_TEXT_002A4F10_H

#include "overlays/1070-00/text_00284BF0.h"

/** Partial resource list entry with its size, keys and observed flag byte. */
typedef struct FieldResourceListEntry
{
    FieldListNode link;
    u8 unk0c[8];
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u32 unk20;
    u8 unk24[0x1C];
    s32 unk40;
    u8 unk44[5];
    u8 unk49_0 : 1;
    u8 unk49_1 : 1;
    u8 unk49_2 : 1;
    u8 unk49_3 : 1;
    u8 unk49_4_7 : 4;
} FieldResourceListEntry;

/** Partial resource-list owner with an embedded sentinel. */
typedef struct FieldResourceList14
{
    u8 unk00[0x14];
    FieldListNode unk14;
} FieldResourceList14;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Find the size selected by a resource entry's flag.
 * @param object Resource list to search.
 * @param kind Resource kind to match.
 * @param key Resource key to match.
 * @return The selected size, or zero when no matching entry exists.
 */
u32 func_002B3140(FieldResourceList14* object, u32 kind, u32 key);

/**
 * @brief Count flagged resource entries matching either of two kind and key conditions.
 * @param object Resource list to search.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 * @return Number of flagged entries with a matching kind and key.
 */
s32 func_002B2950(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Decrement counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002B29F0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Increment counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002B2AB0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Write the float field at offset 0x28.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5010(u8* object, float value);

/**
 * @brief Write the float field at offset 0x30.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5020(u8* object, float value);

/**
 * @brief Read the float field at offset 0x30.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A5030(u8* object);

/**
 * @brief Write the u8 field at offset 0x4D.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5040(u8* object, u8 value);

/**
 * @brief Read the u8 field at offset 0x4D.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_002A5050(u8* object);

/**
 * @brief Write the float field at offset 0x34.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5060(u8* object, float value);

/**
 * @brief Write the u8 field at offset 0x56.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5070(u8* object, u8 value);

/**
 * @brief Read the u8 field at offset 0x56.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_002A5080(u8* object);

/**
 * @brief Write the float field at offset 0x44.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5090(u8* object, float value);

/**
 * @brief Read the float field at offset 0x44.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A50A0(u8* object);

/**
 * @brief Read the float field at offset 0x28.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A50B0(u8* object);

/**
 * @brief Write the u32 field at offset 0x48.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A50C0(u8* object, u32 value);

/**
 * @brief Read the u32 field at offset 0x48.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A50D0(u8* object);

/**
 * @brief Write the u8 field at offset 0x4F.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A50E0(u8* object, u8 value);

/**
 * @brief Write the u8 field at offset 0x4E.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A50F0(u8* object, u8 value);

/**
 * @brief Write the u32 field at offset 0x50.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5100(u8* object, u32 value);

/**
 * @brief Read the u32 field at offset 0x50.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A5110(u8* object);

/**
 * @brief Write the u8 field at offset 0x55.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5120(u8* object, u8 value);

/**
 * @brief Write the float field at offset 0x3C.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5130(u8* object, float value);

/**
 * @brief Write the u8 field at offset 0x54.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5140(u8* object, u8 value);

/**
 * @brief Write the float field at offset 0x40.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A5150(u8* object, float value);

/**
 * @brief Write the float field at offset 0x38.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A51D0(u8* object, float value);

/**
 * @brief Write the float field at offset 0x28.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8280(u8* object, float value);

/**
 * @brief Write the float field at offset 0x30.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8290(u8* object, float value);

/**
 * @brief Read the float field at offset 0x30.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A82A0(u8* object);

/**
 * @brief Write the u8 field at offset 0x4D.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A82B0(u8* object, u8 value);

/**
 * @brief Read the u8 field at offset 0x4D.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_002A82C0(u8* object);

/**
 * @brief Write the float field at offset 0x34.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A82D0(u8* object, float value);

/**
 * @brief Write the u8 field at offset 0x56.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A82E0(u8* object, u8 value);

/**
 * @brief Read the u8 field at offset 0x56.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_002A82F0(u8* object);

/**
 * @brief Write the float field at offset 0x44.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8300(u8* object, float value);

/**
 * @brief Read the float field at offset 0x44.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A8310(u8* object);

/**
 * @brief Read the float field at offset 0x28.
 * @param object Object containing the field.
 * @return Field value.
 */
float func_002A8320(u8* object);

/**
 * @brief Write the u32 field at offset 0x48.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8330(u8* object, u32 value);

/**
 * @brief Read the u32 field at offset 0x48.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A8340(u8* object);

/**
 * @brief Write the u8 field at offset 0x4F.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8350(u8* object, u8 value);

/**
 * @brief Write the u8 field at offset 0x4E.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8360(u8* object, u8 value);

/**
 * @brief Write the u32 field at offset 0x50.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8370(u8* object, u32 value);

/**
 * @brief Read the u32 field at offset 0x50.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A8380(u8* object);

/**
 * @brief Write the u8 field at offset 0x55.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8390(u8* object, u8 value);

/**
 * @brief Write the float field at offset 0x3C.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A83A0(u8* object, float value);

/**
 * @brief Write the u8 field at offset 0x54.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A83B0(u8* object, u8 value);

/**
 * @brief Write the float field at offset 0x40.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A83C0(u8* object, float value);

/**
 * @brief Write the float field at offset 0x38.
 * @param object Object containing the field.
 * @param value Value to write.
 */
void func_002A8440(u8* object, float value);

/**
 * @brief Clear two counters and set the enabled byte.
 * @param object Object containing the fields.
 * @param enabled Whether to set the enabled byte.
 */
void func_002A51A0(u8* object, u32 enabled);

/**
 * @brief Clear two counters and set the enabled byte.
 * @param object Object containing the fields.
 * @param enabled Whether to set the enabled byte.
 */
void func_002A8410(u8* object, u32 enabled);

/**
 * @brief Return the fixed value 1.0f.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_002B2680(void* object);

/**
 * @brief Return the fixed value 1.0f.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_002B2690(void* object);

/**
 * @brief Return the fixed value 1.0f.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_002B26A0(void* object);

/**
 * @brief Return the fixed value 1.0f.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_002B26B0(void* object);

/**
 * @brief Return the fixed value 1.0f.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0f.
 */
float func_002B2700(void* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A84D0(u8* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A84E0(u8* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A84F0(u8* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A85C0(u8* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A85D0(u8* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A85E0(u8* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A86B0(u8* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A86C0(u8* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A86D0(u8* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A87A0(u8* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A87B0(u8* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A87C0(u8* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A8890(u8* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A88A0(u8* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_002A88B0(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the field.
 * @return One if the word is nonzero, otherwise zero.
 */
s32 func_002A8510(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the field.
 * @return One if the word is nonzero, otherwise zero.
 */
s32 func_002A8600(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the field.
 * @return One if the word is nonzero, otherwise zero.
 */
s32 func_002A86F0(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the field.
 * @return One if the word is nonzero, otherwise zero.
 */
s32 func_002A87E0(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the field.
 * @return One if the word is nonzero, otherwise zero.
 */
s32 func_002A88D0(u8* object);

/**
 * @brief Return an entry address using a stride of 368 bytes.
 * @param object Object holding the entry pointer at offset 0x14.
 * @param index Entry index.
 * @return Address of the indexed entry.
 */
u8* func_002A8490(u8* object, s32 index);

/**
 * @brief Return an entry address using a stride of 288 bytes.
 * @param object Object holding the entry pointer at offset 0x14.
 * @param index Entry index.
 * @return Address of the indexed entry.
 */
u8* func_002A8580(u8* object, s32 index);

/**
 * @brief Return an entry address using a stride of 176 bytes.
 * @param object Object holding the entry pointer at offset 0x14.
 * @param index Entry index.
 * @return Address of the indexed entry.
 */
u8* func_002A8670(u8* object, s32 index);

/**
 * @brief Return an entry address using a stride of 144 bytes.
 * @param object Object holding the entry pointer at offset 0x14.
 * @param index Entry index.
 * @return Address of the indexed entry.
 */
u8* func_002A8760(u8* object, s32 index);

/**
 * @brief Return an entry address using a stride of 96 bytes.
 * @param object Object holding the entry pointer at offset 0x14.
 * @param index Entry index.
 * @return Address of the indexed entry.
 */
u8* func_002A8850(u8* object, s32 index);

/**
 * @brief Return an entry address from row and column indices.
 * @param object Object holding the row width and entry pointer.
 * @param row Row index.
 * @param column Column index.
 * @return Address of the selected 64-byte entry.
 */
u8* func_002A84B0(u8* object, s32 row, s32 column);

/**
 * @brief Return an entry address from row and column indices.
 * @param object Object holding the row width and entry pointer.
 * @param row Row index.
 * @param column Column index.
 * @return Address of the selected 64-byte entry.
 */
u8* func_002A85A0(u8* object, s32 row, s32 column);

/**
 * @brief Return an entry address from row and column indices.
 * @param object Object holding the row width and entry pointer.
 * @param row Row index.
 * @param column Column index.
 * @return Address of the selected 64-byte entry.
 */
u8* func_002A8690(u8* object, s32 row, s32 column);

/**
 * @brief Return an entry address from row and column indices.
 * @param object Object holding the row width and entry pointer.
 * @param row Row index.
 * @param column Column index.
 * @return Address of the selected 64-byte entry.
 */
u8* func_002A8780(u8* object, s32 row, s32 column);

/**
 * @brief Return an entry address from row and column indices.
 * @param object Object holding the row width and entry pointer.
 * @param row Row index.
 * @param column Column index.
 * @return Address of the selected 64-byte entry.
 */
u8* func_002A8870(u8* object, s32 row, s32 column);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A51E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A51F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A5200(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A5210(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A5250(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002A7D30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A8450(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A8460(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A8470(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A8480(void* object);

/**
 * @brief Return the fixed value 63.
 * @param object Receiver or first argument; unused.
 * @return Always 63.
 */
s32 func_002A8500(void* object);

/**
 * @brief Return the fixed value 47.
 * @param object Receiver or first argument; unused.
 * @return Always 47.
 */
s32 func_002A85F0(void* object);

/**
 * @brief Return the fixed value 39.
 * @param object Receiver or first argument; unused.
 * @return Always 39.
 */
s32 func_002A86E0(void* object);

/**
 * @brief Return the fixed value 35.
 * @param object Receiver or first argument; unused.
 * @return Always 35.
 */
s32 func_002A87D0(void* object);

/**
 * @brief Return the fixed value 33.
 * @param object Receiver or first argument; unused.
 * @return Always 33.
 */
s32 func_002A88C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B0AB0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002B0AC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B1B10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B1B20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B1B30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002B1B40(void* object);

/**
 * @brief Return the fixed value 12.
 * @param object Receiver or first argument; unused.
 * @return Always 12.
 */
s32 func_002B3440(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002B3640(void* object);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_002B4520(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4530(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B4810(void* object);

#ifdef __cplusplus
}
#endif

#endif
