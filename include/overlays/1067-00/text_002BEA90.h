#ifndef SO3_OVERLAYS_1067_00_TEXT_002BEA90_H
#define SO3_OVERLAYS_1067_00_TEXT_002BEA90_H

#include "types.h"

/** Partial receiver layouts defined in the owning source. */
typedef struct FieldTable14 FieldTable14;
typedef struct FieldGrid20 FieldGrid20;
typedef struct FieldWord1C FieldWord1C;
typedef struct FieldWord0C FieldWord0C;
typedef struct FieldWord10 FieldWord10;
typedef struct FieldWord14 FieldWord14;
typedef struct FieldWord28 FieldWord28;
typedef struct FieldInputState FieldInputState;
typedef struct FieldFlags1C FieldFlags1C;
typedef struct FieldBytePtr10 FieldBytePtr10;
typedef struct FieldBitFlags1C FieldBitFlags1C;
typedef struct FieldInputBlock FieldInputBlock;
typedef struct FieldEntry90 FieldEntry90;
typedef struct FieldCollection90 FieldCollection90;
typedef struct FieldCell40 FieldCell40;
typedef struct FieldGrid40 FieldGrid40;
typedef struct FieldSignedWord1C FieldSignedWord1C;
typedef struct FieldSignedWord0C FieldSignedWord0C;
typedef struct FieldSignedWord10 FieldSignedWord10;
typedef struct FieldPointer14 FieldPointer14;
typedef struct FieldState100 FieldState100;
typedef struct FieldFloat2C FieldFloat2C;
typedef struct FieldEntry50 FieldEntry50;
typedef struct FieldCollection50 FieldCollection50;
typedef struct FieldCollection FieldCollection;
typedef struct FieldThing FieldThing;
typedef struct FieldPair FieldPair;
typedef struct FieldMotion FieldMotion;
typedef struct FieldList FieldList;
typedef struct FieldState28 FieldState28;
typedef struct FieldSelector FieldSelector;
typedef struct FieldProgressState FieldProgressState;

#ifdef __cplusplus
#include "overlays/1067-00/field_class_154D40.h"

/** Partial FieldClass154E70 with vtable D_159E40 in main data; its only virtual is the destructor. */
class FieldClass159E40 : public FieldClass154E70
{
public:
    /** @brief Construct the object. */
    FieldClass159E40();

    /** @brief Destroy the object. */
    virtual ~FieldClass159E40();

    u8 unk04[0x8C];
};

/** Partial grid of FieldClass159E40 cells with vtable D_159E50 in main data. */
class FieldClass159E50 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass159E50();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass159E50();

    u8* unk14;
    FieldClass159E40* unk18;
    FieldBitset154E80* unk1C;
    u8* unk20;
    FieldClass154E60* unk24;
};

/** Partial FieldClass159E50 with vtable D_159C30 in main data. */
class FieldClass159C30 : public FieldClass159E50
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass159C30()
    {
    }
};

/** Partial FieldClass159C30 with vtable D_159D00 in main data. */
class FieldClass159D00 : public FieldClass159C30
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass159D00()
    {
    }
};

/** Partial FieldClass159D00 with vtable D_159B60 in main data. */
class FieldClass159B60 : public FieldClass159D00
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass159B60();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear bit 0 of the flag byte at offset 0x1C.
 * @param self Receiver to update.
 */
void func_002BED50(FieldBitFlags1C* self);

/**
 * @brief Store input range and whether its first byte is 1.
 * @param self Receiver to update.
 * @param data Input byte stream.
 * @param count Input count.
 */
void func_002BF3F0(FieldInputBlock* self, const u8* data, s32 count);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF430(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF440(void* object);

/**
 * @brief Return the fixed float value 100.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002BF450(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF460(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF470(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF480(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF490(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF4A0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF4B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF4C0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF4D0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF4E0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF4F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF500(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF510(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF520(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF530(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF540(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF550(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF560(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF570(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF580(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF590(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002BF5A0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF5B0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF5C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF5D0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF5E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF5F0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF600(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002BF610(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF620(void* object);

/**
 * @brief Address an indexed 0x90-byte record.
 * @param self Record collection.
 * @param index Record index.
 * @return Indexed record.
 */
FieldEntry90* func_002BF690(FieldCollection90* self, s32 index);

/**
 * @brief Address an indexed 0x40-byte grid cell.
 * @param self Cell grid.
 * @param row Row index.
 * @param column Column index.
 * @return Indexed cell.
 */
FieldCell40* func_002BF6B0(FieldGrid40* self, s32 row, s32 column);

/**
 * @brief Read the signed word at offset 0x1C.
 * @param self Receiver.
 * @return Stored word.
 */
s32 func_002BF6D0(const FieldSignedWord1C* self);

/**
 * @brief Read the signed word at offset 0x0C.
 * @param self Receiver.
 * @return Stored word.
 */
s32 func_002BF6E0(const FieldSignedWord0C* self);

/**
 * @brief Read the signed word at offset 0x10.
 * @param self Receiver.
 * @return Stored word.
 */
s32 func_002BF6F0(const FieldSignedWord10* self);

/**
 * @brief Return the fixed value 0x20.
 * @param self Receiver of the call.
 * @return Fixed value.
 */
s32 func_002BF700(void* self);

/**
 * @brief Test whether the pointer at offset 0x14 is present.
 * @param self Receiver.
 * @return Whether the pointer is non-null.
 */
bool func_002BF710(const FieldPointer14* self);

/**
 * @brief Return the fixed float value 1.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002BFE60(void* object);

/**
 * @brief Advance a progress value while its mode is active.
 * @param self Receiver to update.
 */
void func_002BFF40(FieldProgressState* self);

/**
 * @brief Clear an inactive state flag or activate once.
 * @param state Receiver to update.
 */
void func_002C0390(FieldState100* state);

#ifdef __cplusplus
}
#endif

#endif
