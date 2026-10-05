#ifndef SO3_OVERLAYS_1067_00_TEXT_002764D0_H
#define SO3_OVERLAYS_1067_00_TEXT_002764D0_H

#include "types.h"

#ifdef __cplusplus
#include "main/resident_data.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/1067-00/text_001DD3C0.h"

/**
 * Partial 0x7D8-byte FieldClass14FFB0 with vtable D_155640 in main data
 * (FieldClass1DD400 part at +0x2C). The field context keeps one instance at
 * offset 0x1C; it is created on first use and inserted into the context's
 * offset 0x30 list (FieldClass14FE30::func_001DF360, func_00258AC0).
 */
class FieldClass155640 : public FieldClass14FFB0
{
public:
    /** @brief Reset the records and settings; the settings start unset (-1). */
    FieldClass155640()
    {
        FieldClass14FFB0::func_001DEA80();
        func_001DE8B0(0x1A);
        unk7d6_0 = 0;
        unk7d6_1 = 0;
        unk14 = 2;
        unk7d0 = 0;
        unk7c8 = -1;
        unk7cc = -1;
        unk7d5 = -1;
    }

    /** @brief Clear the field context's pointer to this object, then destroy it. */
    virtual ~FieldClass155640();

    /**
     * @brief Override of FieldClass14FFB0 slot 7.
     * @param flag Value whose meaning is not yet known.
     */
    virtual void func_001E0A50(s32 flag);

    /**
     * @brief Advance to the next pending record, refilling the buffers first when requested.
     *
     * Does nothing unless bit 1 at offset 0x30 is set, and clears it afterwards.
     * In state 1, and unless field_records_blocked() reports a block, toggles
     * the current record's bits; if bit 0 at offset 0x7D6 is set, clears it and
     * refills a temporary LibClass3F5B80 and the member at 0x34 from the
     * settings and the field context's word at offset 0xD0. Then skips records
     * that are finished, already handled or unused and sets state 0, or 5 when
     * none remain.
     */
    virtual void func_001E0F60();

    /** @brief Rebuild the records from the current settings. */
    void func_00279B80();

    /**
     * @brief Rebuild the records from a filled LibClass3F5B80.
     * @param source Filled object to read.
     */
    void func_002797D0(LibClass3F5B80* source);

    /**
     * @brief Store new settings, then rebuild the records through func_00279B80.
     * @param id Setting stored at offset 0x7C8.
     * @param area Setting stored at offset 0x7CC.
     * @param kind Setting stored at offset 0x7D4.
     * @param mode Setting stored at offset 0x7D5.
     * @param flag Stored in bit 1 at offset 0x7D6.
     */
    void func_00279EA0(s32 id, s32 area, u8 kind, s8 mode, bool flag);

    LibClass3F5B80 unk34;
    s32 unk7c8;
    s32 unk7cc;
    s32 unk7d0;
    u8 unk7d4;
    s8 unk7d5;
    u8 unk7d6_0 : 1;
    u8 unk7d6_1 : 1;
    u8 unk7d6_2_7 : 6;
};
#endif

typedef struct FieldFlaggedListObject FieldFlaggedListObject;
typedef struct FieldObject22E680 FieldObject22E680;
typedef struct FieldObject155540 FieldObject155540;
typedef struct FieldObject1557B0 FieldObject1557B0;
typedef struct FieldFloatState28F00 FieldFloatState28F00;
typedef struct FieldEntryOwner293F0 FieldEntryOwner293F0;
typedef struct FieldFlagTable2BB00 FieldFlagTable2BB00;
typedef struct FieldLookupNode2BF70 FieldLookupNode2BF70;
typedef struct FieldLookupList2BF70 FieldLookupList2BF70;
typedef struct FieldFlagState271B0 FieldFlagState271B0;
typedef struct FieldFlagState2B320 FieldFlagState2B320;
typedef struct FieldState2B390 FieldState2B390;
typedef struct FieldState2BAF0 FieldState2BAF0;
typedef struct FieldQword27A9A0 FieldQword27A9A0;
typedef struct FieldState27A9A0 FieldState27A9A0;
typedef struct FieldSource2A550 FieldSource2A550;
typedef struct FieldState2A550 FieldState2A550;
typedef struct FieldState27B2A0 FieldState27B2A0;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Copy the signed field-context byte into the receiver.
 * @param object Receiver to update.
 * @return Always 1.
 */
s32 func_00276BE0(FieldFlagState271B0* object);

/**
 * @brief Set the first flag on the object attached to the field context.
 * @param object Callback receiver; unused.
 * @return Always 1.
 */
s32 func_00276DF0(void* object);

/**
 * @brief Update bit 1 of the receiver's flag byte from its stored word.
 * @param object Receiver to update.
 * @return Always 1.
 */
s32 func_002771B0(FieldFlagState271B0* object);

/**
 * @brief Set the resident flag from the low bit of the receiver's word.
 * @param object Receiver supplying the word.
 * @return Always 1.
 */
s32 func_00277610(FieldFlagState271B0* object);

/**
 * @brief Set a float immediately or start a timed change toward it.
 * @param object Receiver with current and target float values.
 * @param target Value to store or move toward.
 * @param duration Time divisor; zero stores the value immediately.
 */
void func_00278F00(FieldFloatState28F00* object, float target, float duration);

/**
 * @brief Apply or clear a field state using the selected list node and callback data.
 * @param state Receiver holding the current field state.
 * @param node Selected list node, or null to clear the current state.
 * @param data Sixteen bytes copied into the active state.
 * @return Nonzero when the state operation succeeds.
 */
s32 func_00278D90(void* state, FieldFlaggedListObject* node, const void* data);

/**
 * @brief Clear bit 0 in inactive entries of a 26-entry array.
 * @param object Receiver holding the entry array.
 */
void func_002793F0(FieldEntryOwner293F0* object);

/**
 * @brief Store caller values, copy or clear 16 bytes, and reset two flags.
 * @param object Receiver to initialize.
 * @param value14 Word stored at offset 0x14.
 * @param source Source for the word stored at offset 0x54.
 * @param data Optional 16-byte source; null clears the destination.
 * @param value18 Word stored at offset 0x18.
 * @param value28 Word stored at offset 0x28.
 * @param value2c Word stored at offset 0x2C.
 * @param value30 Word stored at offset 0x30.
 */
void func_0027A550(FieldState2A550* object, u32 value14, const FieldSource2A550* source,
                   const void* data, u32 value18, u32 value28, u32 value2c, u32 value30);

/**
 * @brief Store caller values, copy or clear 16 bytes, and reset two flags.
 * @param object Receiver to initialize.
 * @param value14 Word stored at offset 0x14.
 * @param value50 Word stored at offset 0x50.
 * @param data Optional 16-byte source; null clears the destination.
 * @param value18 Word stored at offset 0x18.
 * @param value28 Word stored at offset 0x28.
 * @param value2c Word stored at offset 0x2C.
 * @param value30 Word stored at offset 0x30.
 */
void func_0027A6F0(FieldState2A550* object, u32 value14, u32 value50,
                   const void* data, u32 value18, u32 value28, u32 value2c, u32 value30);

/**
 * @brief Clear two receiver flags and set its state word to -3.
 * @param object Receiver to update.
 */
void func_0027A3E0(FieldFlagState2B320* object);

/**
 * @brief Clear two receiver flags and set its state word to -3.
 * @param object Receiver to update.
 */
void func_0027A6B0(FieldFlagState2B320* object);

/**
 * @brief Detach the receiver and add it to the resident object queue.
 * @param object Receiver to detach and queue.
 */
void func_002782A0(void* object);

/**
 * @brief Detach the receiver and add it to the resident object queue.
 * @param object Receiver to detach and queue.
 */
void func_002782D0(void* object);

/**
 * @brief Clear the receiver's attached state and update its flags.
 * @param object Receiver to reset.
 */
void func_0027ABF0(FieldObject22E680* object);

/**
 * @brief Store five words and two aligned 16-byte values.
 * @param object Receiver to update.
 * @param value14 Word stored at offset 0x14.
 * @param first First aligned value.
 * @param second Second aligned value.
 * @param value18 Word stored at offset 0x18.
 * @param value28 Word stored at offset 0x28.
 * @param value2c Word stored at offset 0x2C.
 * @param value30 Word stored at offset 0x30.
 */
void func_0027A9A0(FieldState27A9A0* object, u32 value14,
                   const FieldQword27A9A0* first, const FieldQword27A9A0* second,
                   u32 value18, u32 value28, u32 value2c, u32 value30);

/**
 * @brief Store six words in the receiver.
 * @param object Receiver to update.
 * @param value14 Word stored at offset 0x14.
 * @param value18 Word stored at offset 0x18.
 * @param value28 Word stored at offset 0x28.
 * @param value34 Word stored at offset 0x34.
 * @param value2c Word stored at offset 0x2C.
 * @param value30 Word stored at offset 0x30.
 */
void func_0027B2A0(FieldState27B2A0* object, u32 value14, u32 value18,
                   u32 value28, u32 value34, u32 value2c, u32 value30);

/**
 * @brief Clear bit 3 of the receiver's flag byte and set its state word to -3.
 * @param object Receiver to update.
 */
void func_0027B320(FieldFlagState2B320* object);

/**
 * @brief Update a stored word and set its change flag when needed.
 * @param object Receiver to update.
 * @param value Word to store.
 * @param force Also update when the stored word already equals value.
 */
void func_0027B390(FieldState2B390* object, u32 value, s32 force);

/**
 * @brief Store a word and mark the receiver ready.
 * @param object Receiver to update.
 * @param value Word to store.
 * @param unused Third argument; unused.
 */
void func_0027BAF0(FieldState2BAF0* object, u32 value, s32 unused);

/**
 * @brief Set bit 0 or bit 3 of the receiver's flag byte from bit 5.
 * @param object Receiver whose flag byte is updated.
 */
void func_0027C080(FieldFlagState2B320* object);

/**
 * @brief Return the selected entry's flag category.
 * @param object Receiver holding the entry array.
 * @param index Signed entry index.
 * @return 1 for bit 2, 2 for bit 0, or 0 otherwise.
 */
s32 func_0027BB00(FieldFlagTable2BB00* object, s8 index);

/**
 * @brief Update the selected entry with four caller values.
 * @param context Resident entry collection.
 * @param id Selected entry identifier.
 * @param first First value to store.
 * @param mode Mode value to store.
 * @param second Second value to store.
 * @param third Third value to store.
 */
void func_0027C0D0(void* context, s32 id, u32 first, u32 mode, u32 second, u32 third);

/**
 * @brief Update the selected entry with one caller value.
 * @param context Resident entry collection.
 * @param id Selected entry identifier.
 * @param extra Additional caller value.
 */
void func_0027C130(void* context, s32 id, u32 extra);

/**
 * @brief Find a list node by its stored key.
 * @param object Receiver holding the sentinel list.
 * @param key Word compared with each node's value at offset 0x14.
 * @return Matching node, or null when the list ends.
 */
FieldLookupNode2BF70* func_0027BF70(FieldLookupList2BF70* object, u32 key);

/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 4.
 */
s32 func_00278300(FieldObject155540* object);

/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 2.
 */
s32 func_0027D320(FieldObject1557B0* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00277320(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00277630(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00277640(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00277CA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00278950(void* object);

/**
 * @brief Change the receiver's identifier and update its transition state.
 * @param object Receiver containing the current identifier.
 * @param identifier New signed identifier; -2 selects the special transition.
 * @param first First transition value.
 * @param second Second transition value.
 * @return Zero when the identifier is unchanged, or one after a change.
 */
s32 func_0027CB50(void* object, s32 identifier, s32 first, s32 second);

#ifdef __cplusplus
}
#endif

#endif
