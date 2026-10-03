#ifndef SO3_OVERLAYS_1067_00_TEXT_001E1590_H
#define SO3_OVERLAYS_1067_00_TEXT_001E1590_H

#include "types.h"
#include "overlays/1067-00/text_001DED80.h"

/** Partial receiver with a word at offset 0x30 and a byte at offset 0x34. */
typedef struct FieldWordByte30
{
    u8 unk00[0x30];
    u32 unk30;
    u8 unk34;
} FieldWordByte30;

/** Partial 28-byte record reset by func_001E5690 and func_001E5AD0. */
typedef struct FieldSlotRecord1C
{
    u8 unk00[4];
    u32 unk04;
    u8 unk08_0 : 1;
    u8 unk08_1_7 : 7;
    u8 unk09[3];
    s32 unk0c;
    u32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16_0 : 1;
    u8 unk16_1 : 1;
    u8 unk16_2 : 1;
    u8 unk16_3_7 : 5;
    u8 unk17[5];
} FieldSlotRecord1C;

/** Partial receiver owning a counted array of 28-byte records at offset 0x1C. */
typedef struct FieldSlotRecordOwner1C
{
    u8 unk00[0x14];
    u8 unk14;
    u8 unk15[7];
    FieldSlotRecord1C* unk1c;
    u32 unk20;
    s32 unk24;
    u8 unk28[5];
    u8 unk2d;
    u8 unk2e;
    u8 unk2f;
    u8 unk30[8];
    s32 unk38;
    s32 unk3c;
} FieldSlotRecordOwner1C;

#ifdef __cplusplus
/** Partial class with a FieldClass1DD400 base at offset 0x14, with vtable D_150120 in main data. */
class FieldClass150120 : public FieldClass150070, public FieldClass1DD400
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150120();

    /**
     * @brief Report the fixed value 4 for this class.
     * @return Always 4.
     */
    virtual s32 func_001DF3D0();

    /** @brief Queue the object on the resident object queue without detaching it. */
    virtual void func_001DD7B0();

    /** @brief FieldClass1DD400 slot 1 override. */
    virtual void func_001DDB30(void* arg);

    u8 unk18[0x2C];
    u8* unk44[10];
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001E1820(const void* object);

/**
 * @brief Store the word at offset 0x30 and the byte at offset 0x34.
 * @param object Receiver to update.
 * @param word Word to store.
 * @param value Byte to store.
 */
void func_001E5020(FieldWordByte30* object, u32 word, u8 value);

/**
 * @brief Reset every 28-byte record in the counted array at offset 0x1C, then clear the word at offset 0x20 and the bytes at offsets 0x2D-0x2F, and set the byte at offset 0x14 to 8, the word at 0x38 to 2 and the word at 0x3C to -1.
 * @param object Receiver owning the records; the loop is skipped when the array pointer is null.
 */
void func_001E5690(FieldSlotRecordOwner1C* object);

/**
 * @brief Reset every 28-byte record in the counted array at offset 0x1C, then clear the word at offset 0x20 and the bytes at offsets 0x2D-0x2F.
 * @param object Receiver owning the records; the loop is skipped when the array pointer is null.
 */
void func_001E5AD0(FieldSlotRecordOwner1C* object);

#ifdef __cplusplus
}
#endif

#endif
