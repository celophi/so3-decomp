#ifndef SO3_OVERLAYS_1067_00_TEXT_002D5260_H
#define SO3_OVERLAYS_1067_00_TEXT_002D5260_H

#include "types.h"
#include "overlays/1067-00/text_002D3BD0.h"

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"

class LibObject178660;

/** Resource owner with MAIN vtable at 0x15B200. */
class FieldClass15B200
{
public:
    LibObject178660* unk00;
    float unk04;
    float unk08;
    float unk0c;
    float unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16[2];
    float unk18;
    float unk1c;
    float unk20;
    float unk24;
    u8 unk28;
    u8 unk29[3];
    float unk2c;
    void* unk30;
    /** @brief Initialize the resource owner. @param parent Associated owner. @param flag Initial resource flag. */
    FieldClass15B200(LibObject178660* parent, u8 flag);
    /** @brief Destroy the resource owner. */
    virtual ~FieldClass15B200();
};

struct LibWidgetColors4C5590;

/**
 * @brief Store the owner's bounds and flags, then create its colored child panel.
 * @param object Resource owner; nothing is created when it has no parent.
 * @param first Byte stored at offset 0x14.
 * @param second Byte stored at offset 0x15.
 * @param colors Four packed panel colors.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Panel width.
 * @param height Panel height.
 * @return Zero without a parent.
 */
extern "C" s32 func_002D5290(FieldClass15B200* object, u8 first, u8 second, const LibWidgetColors4C5590* colors,
                             float x, float y, float width, float height);

#endif

/** Partial resource display with its caller-controlled marker byte. */
typedef struct FieldResourceDisplay2D5CF0
{
    u8 unk00[0x3F];
    u8 unk3F;
} FieldResourceDisplay2D5CF0;

/** Partial receiver with a one-bit flag at offset 0x14AC. */
typedef struct FieldFlagState2D7AA0
{
    u8 unk00[0x14AC];
    u8 active : 1;
    u8 other : 7;
} FieldFlagState2D7AA0;

/** Packed source fields in a 0x18-byte table entry. */
typedef struct FieldPackedEntry2D79D0
{
    u64 unk00;
    u64 unk08;
    void* unk10;
    void* unk14;
} FieldPackedEntry2D79D0;

/** Partial receiver containing 32 packed entries and a presence flag. */
typedef struct FieldPackedTable2D79D0
{
    u8 unk00[0x10A8];
    FieldPackedEntry2D79D0 entries[32];
    u8 unk13A8[0x104];
    u8 unk14AC;
} FieldPackedTable2D79D0;

/** Unpacked eight-byte record written by func_002D79D0. */
typedef struct FieldPackedValues2D79D0
{
    u16 unk00;
    u16 unk02;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
} FieldPackedValues2D79D0;

/** One 0x18-byte entry in the receiver's slot table. */
typedef struct FieldSlot2D7A50
{
    void* unk00;
    void* unk04;
    u8 unk08[0x10];
} FieldSlot2D7A50;

/** Partial receiver with 32 entries at offset 0x10B8. */
typedef struct FieldSlotTable2D7A50
{
    u8 unk00[0x10B8];
    FieldSlot2D7A50 entries[32];
} FieldSlotTable2D7A50;

/** Partial state holding two floats and an update flag. */
typedef struct FieldState2D5260
{
    u8 unk00[0x20];
    float unk20;
    float unk24;
    u8 unk28[0x14];
    u8 unk3C;
} FieldState2D5260;

/** Partial owner of the state used by func_002D5260. */
typedef struct FieldObject2D5260
{
    u8 unk00[0x30];
    FieldState2D5260* unk30;
} FieldObject2D5260;

/** Partial receiver with the update flag used by func_002D63F0. */
typedef struct FieldState2D63F0
{
    u8 unk00[0x3C];
    u8 unk3C;
} FieldState2D63F0;

/** Partial receiver whose state is cleared by func_002D6410. */
typedef struct FieldState2D6410
{
    u8 unk00[0xCC];
    s32 unkCC;
    u8 unkD0;
    u8 unkD1[0x37];
    s32 unk108;
    s16 unk10C;
    s16 unk10E;
    u8 unk110;
    u8 unk111;
    u8 unk112;
    u8 unk113;
    u8 unk114;
} FieldState2D6410;

/** Partial receiver with a byte flag at offset 0x3C. */
typedef struct FieldFlagObject2D5CE0
{
    u8 unk00[0x3C];
    u8 unk3C;
} FieldFlagObject2D5CE0;

/** Partial scalar state reached through the 002D6A40 object. */
typedef struct FieldScalarState2D6A40
{
    u8 unk00[0xCB];
    u8 unkCB;
    u8 unkCC[2];
    u8 unkCE;
    u8 unkCF[0x11];
    float unkE0;
} FieldScalarState2D6A40;

/** Partial scalar state reached through the 002D8020 object. */
typedef struct FieldScalarState2D8020
{
    u8 unk00[0xCB];
    u8 unkCB;
    u8 unkCC[2];
    u8 unkCE;
    u8 unkCF[0x11];
    float unkE0;
} FieldScalarState2D8020;

/** Partial receiver with a byte at offset 0x60. */
typedef struct FieldState2D82F0
{
    u8 unk00[0x60];
    u8 unk60;
} FieldState2D82F0;

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Replace non-null resource pointers and a nonzero index, then mark the display for refresh.
 * @param object Resource display to update.
 * @param allocation Allocation pointer, or null to retain the current pointer.
 * @param record Resource record, or null to retain the current record.
 * @param index Nonzero value whose low byte replaces the current resource index.
 */
void func_002D5CF0(FieldResourceDisplay2D5CF0* object, void* allocation, FieldResourceRecord* record, u32 index);

/**
 * @brief Set the receiver's active bit and run its imported update routine.
 * @param object Receiver to update.
 */
void func_002D7AA0(FieldFlagState2D7AA0* object);

/**
 * @brief Unpack one table entry when the receiver's presence flag is set.
 * @param object Receiver containing the packed entries.
 * @param index Entry index to read.
 * @param output Eight-byte destination for the unpacked fields.
 * @return One when data is available, otherwise zero.
 */
s32 func_002D79D0(FieldPackedTable2D79D0* object, s32 index, FieldPackedValues2D79D0* output);

/**
 * @brief Store two pointers in the first empty slot.
 * @param object Receiver containing the slot table.
 * @param first First pointer to store.
 * @param second Second pointer to store.
 * @return Slot index, or -1 when the table is full.
 */
s32 func_002D7A50(FieldSlotTable2D7A50* object, void* first, void* second);

/**
 * @brief Store two floats and mark the attached state updated when present.
 * @param object Owner of the optional state.
 * @param first First float to store.
 * @param second Second float to store.
 */
void func_002D5260(FieldObject2D5260* object, float first, float second);

/**
 * @brief Mark the receiver updated and run its imported update routine.
 * @param object Receiver to update.
 */
void func_002D63F0(FieldState2D63F0* object);

/**
 * @brief Clear the known fields in this receiver's state.
 * @param object Receiver to reset.
 */
void func_002D6410(FieldState2D6410* object);

/**
 * @brief Set the resource record and its displayed position.
 * @param object Resource display to update.
 * @param record Resource record to display.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @return One on success, or zero when allocation fails.
 */
s32 func_002D6440(FieldState2D6410* object, FieldResourceRecord* record, float x, float y);

/**
 * @brief Set the receiver's byte at offset 0x3C.
 * @param object Receiver to update.
 */
void func_002D5CE0(FieldFlagObject2D5CE0* object);

/**
 * @brief Store a byte in the receiver's scalar state.
 * @param object Receiver to update.
 * @param value Byte to store.
 */
void func_002D6AD0(FieldScalarState2D6A40* object, u8 value);

/**
 * @brief Store a float and mark it present.
 * @param object Receiver to update.
 * @param value Float to store.
 */
void func_002D6AE0(FieldScalarState2D6A40* object, float value);

/**
 * @brief Return the default float value.
 * @param object Receiver to query.
 * @return Always zero.
 */
float func_002D8000(void* object);

/**
 * @brief Store a byte in the receiver's scalar state.
 * @param object Receiver to update.
 * @param value Byte to store.
 */
void func_002D80E0(FieldScalarState2D8020* object, u8 value);

/**
 * @brief Store a float and mark it present.
 * @param object Receiver to update.
 * @param value Float to store.
 */
void func_002D80F0(FieldScalarState2D8020* object, float value);

/**
 * @brief Set the receiver's byte at offset 0x60 to 9.
 * @param object Receiver to update.
 */
void func_002D82F0(FieldState2D82F0* object);

#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 5.
 */
s32 func_002D82E0(FieldClass150070* object);
#endif

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D6A20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D6A30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D79C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D7FE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D7FF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D8010(void* object);

#ifdef __cplusplus
}
#endif

#endif
