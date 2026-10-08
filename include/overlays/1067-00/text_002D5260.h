#ifndef SO3_OVERLAYS_1067_00_TEXT_002D5260_H
#define SO3_OVERLAYS_1067_00_TEXT_002D5260_H

#include "types.h"
#include "overlays/lib/ui_object.h"
#include "overlays/1067-00/text_002D3BD0.h"

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/lib/text_0044ABE0.h"

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
    LibClass178600* unk30;
    /** @brief Initialize the resource owner. @param parent Associated owner. @param flag Initial resource flag. */
    FieldClass15B200(LibObject178660* parent, u8 flag);
    /** @brief Destroy the resource owner. */
    virtual ~FieldClass15B200();
};

struct LibWidgetColors4C5590;

/**
 * @brief Store two floats and mark the attached state updated when present.
 * @param object Owner of the optional state.
 * @param first First float to store.
 * @param second Second float to store.
 */
extern "C" void func_002D5260(FieldClass15B200* object, float first, float second);

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

/**
 * @brief Remove the first matching entry from the second registry list and queue the container for release.
 * @param object Container to remove and release.
 */
extern "C" void func_002D70F0(LibObject178660* object);

/**
 * @brief Remove the first matching entry from the first registry list and queue the container for release.
 * @param object Container to remove and release.
 */
extern "C" void func_002D7630(LibObject178660* object);


struct FieldPanelState2D7820;

/**
 * @brief Configure the container transform and panel, then attach the panel and store the supplied value.
 * @param object Container to initialize.
 * @param value Word to store after panel setup succeeds.
 * @param mode Signed byte passed to the container transform setup.
 * @param transform Third transform setup argument.
 * @param x Container horizontal position.
 * @param y Container vertical position.
 * @param width Panel width.
 * @param height Panel height.
 * @return One on panel setup success, otherwise zero.
 */
extern "C" s32 func_002D7820(FieldPanelState2D7820* object, u32 value, s8 mode, s32 transform,
                  float x, float y, float width, float height);

class FieldScalarTransition2D6AF0;

/**
 * @brief Advance the flagged scalar transition and dispatch its updated value.
 * @param object Scalar transition state.
 * @return One when a transition flag is set, otherwise zero.
 */
extern "C" s32 func_002D6AF0(FieldScalarTransition2D6AF0* object);

class FieldClass15B300;
class FieldClass15B670;
class ItemCreationOptionResourceDisplay;
class FieldClass178A90;
class FieldClass15B770;

/**
 * @brief Apply controller input to the row container's selection and scrolling state.
 * @param object Field row container.
 * @return One when its selection or scrolling state changes, otherwise zero.
 */
extern "C" bool func_002D6CB0(FieldClass15B300* object);

#else
typedef struct FieldClass15B300 FieldClass15B300;
typedef struct FieldClass15B670 FieldClass15B670;
typedef struct ItemCreationOptionResourceDisplay ItemCreationOptionResourceDisplay;
typedef struct FieldClass178A90 FieldClass178A90;
typedef struct FieldClass15B770 FieldClass15B770;
#endif

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
void func_002D5CF0(ItemCreationOptionResourceDisplay* object, void* allocation, FieldResourceRecord* record, u32 index);

/**
 * @brief Set the receiver's active bit and run its imported update routine.
 * @param object Receiver to update.
 */
void func_002D7AA0(FieldFlagState2D7AA0* object);

/**
 * @brief Submit prepared packet addresses with the callback attached to the final entry.
 * @param object Packet batch owner.
 */
void func_002D7AD0(FieldClass15B770* object);

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
 * @brief Mark the receiver updated and run its imported update routine.
 * @param object Receiver to update.
 */
void func_002D63F0(ItemCreationOptionResourceDisplay* object);

/**
 * @brief Clear the known fields in this receiver's state.
 * @param object Receiver to reset.
 */
void func_002D6410(ItemCreationOptionResourceDisplay* object);

/**
 * @brief Set the resource record and its displayed position.
 * @param object Resource display to update.
 * @param record Resource record to display.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @return One on success, or zero when allocation fails.
 */
s32 func_002D6440(ItemCreationOptionResourceDisplay* object, FieldResourceRecord* record, float x, float y);

/**
 * @brief Set the receiver's byte at offset 0x3C.
 * @param object Receiver to update.
 */
void func_002D5CE0(LibClass178600* object);

/**
 * @brief Store the row container's transform byte.
 * @param object Field row container.
 * @param value Byte to store.
 */
void func_002D6AD0(FieldClass15B300* object, u8 value);

/**
 * @brief Store a float and mark it present.
 * @param object Receiver to update.
 * @param value Float to store.
 */
void func_002D6AE0(FieldClass15B300* object, float value);

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
void func_002D80E0(FieldClass15B670* object, u8 value);

/**
 * @brief Store a float and mark it present.
 * @param object Receiver to update.
 * @param value Float to store.
 */
void func_002D80F0(FieldClass15B670* object, float value);

/**
 * @brief Set the receiver's byte at offset 0x60 to 9.
 * @param object Receiver to update.
 */
void func_002D82F0(FieldClass178A90* object);

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

/** Field resource widget using resident table 0x15B240. */
struct ItemCreationOptionResourceDisplay : public ItemCreationClass175110
{
    /** @brief Initialize the resource widget and clear its trailing state. */
    ItemCreationOptionResourceDisplay()
    {
        unk124 = 0;
        unk120 = 0;
        unk11c = 0;
        unk118 = 0;
        func_002D6410();
    }
    /**
     * @brief Replace non-null resource pointers and a nonzero resource index, then request an update.
     * @param allocation Allocation pointer, or null to keep the current pointer.
     * @param record Resource record, or null to keep the current record.
     * @param index Nonzero full word whose low byte replaces the resource index.
     */
    void func_002D5CF0(void* allocation, FieldResourceRecord* record, u32 index);
    /** @brief Clear the resource pointers, indices and trailing update flags. */
    void func_002D6410();
    /**
     * @brief Allocate the resource drawing storage and set its record and position.
     * @param record Resource record to display.
     * @param x Horizontal coordinate.
     * @param y Vertical coordinate.
     * @return One on success, or zero if drawing-storage allocation fails.
     */
    s32 func_002D6440(FieldResourceRecord* record, float x, float y);
    /** @brief Destroy the resource widget. */
    virtual ~ItemCreationOptionResourceDisplay();
    /** @brief Refresh the resource widget. */
    virtual void func_00413D20();
    /** @brief Draw the resource widget. */
    virtual void func_00462310();
    void* unkcc;
    u8 unkd0;
    u8 unkd1[0x37];
    FieldResourceRecord* unk108;
    u16 unk10c;
    u16 unk10e;
    u8 unk110;
    u8 unk111;
    u8 unk112;
    u8 unk113;
    u8 unk114;
    u8 unk115[3];
    u32 unk118;
    u32 unk11c;
    u32 unk120;
    u32 unk124;
};
#endif

#endif
