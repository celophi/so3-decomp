#ifndef SO3_OVERLAYS_1067_00_TEXT_002764D0_H
#define SO3_OVERLAYS_1067_00_TEXT_002764D0_H

#include "types.h"

#ifdef __cplusplus
#include "main/resident_data.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/1067-00/field_class_1553b0.h"

/**
 * @brief Prepare the battle overlay, archive and selected resources while in the field.
 *
 * The field context owns one 0x7D8-byte preloader and lists it with the other
 * resource loaders. Its 26 requests follow resource_plan; the first buffer
 * holds resources 0xD7E and 0xD7F for the battle transition.
 */
class FieldBattleResourcePreloader : public FieldResourcePreloader
{
public:
    /** @brief Allocate 26 request records and initialize the preload state and selection sentinels. */
    FieldBattleResourcePreloader()
    {
        FieldResourcePreloader::reset_requests();
        allocate_requests(0x1A);
        refresh_pending = 0;
        include_optional_resource = 0;
        load_kind = 2;
        start_delay = 0;
        unk7c8 = -1;
        unk7cc = -1;
        unk7d5 = -1;
    }

    /** @brief Clear the field context's pointer to this object, then destroy it. */
    virtual ~FieldBattleResourcePreloader();

    /**
     * @brief Start pending battle reads when the field state and available memory permit.
     * @param flag One to request cancellation, zero to continue loading.
     */
    virtual void update_requests(s32 flag);

    /**
     * @brief Mark the current read complete and advance to the next pending request.
     *
     * Waits for callback_ready and any field resource block to clear. A pending
     * cancellation clears the request's completion flag. A pending refresh
     * reconciles the records against the new selection before advancing.
     */
    virtual void advance_requests();

    /** @brief Rebuild the resource selection and cancel reads whose file keys changed. */
    void rebuild_requests();

    /**
     * @brief Reconcile request records with the supplied resource plan.
     * @param source Plan whose file keys replace the current selection.
     */
    void reconcile_requests(LibClass3F5B80* source);

    /**
     * @brief Store the resource selection and rebuild its requests.
     * @param id Setting stored at offset 0x7C8.
     * @param area Setting stored at offset 0x7CC.
     * @param kind Setting stored at offset 0x7D4.
     * @param mode Setting stored at offset 0x7D5.
     * @param flag Whether to include the optional resource in slot 2.
     */
    void set_resource_selection(s32 id, s32 area, u8 kind, s8 mode, bool flag);

    LibClass3F5B80 resource_plan;
    s32 unk7c8;
    s32 unk7cc;
    s32 start_delay;
    u8 unk7d4;
    s8 unk7d5;
    u8 refresh_pending : 1;
    u8 include_optional_resource : 1;
    u8 unk7d6_2_7 : 6;
};
#endif

typedef struct FieldFlaggedListObject FieldFlaggedListObject;
typedef struct FieldObject22E680
{
    u8 unk00[0x24];
    s32 unk24;
    u8 unk28[0x24];
    u8 unk4c_0 : 1;
    u8 unk4c_1 : 1;
    u8 unk4c_2 : 1;
    u8 unk4c_3 : 1;
    u8 unk4c_4 : 1;
    u8 unk4c_5 : 1;
    u8 unk4c_6 : 1;
    u8 unk4c_7 : 1;
    u8 unk4d[3];
    void* unk50;
    u8 unk54[0xC];
    u8 unk60;
} FieldObject22E680;
typedef struct FieldObject155540 FieldObject155540;
typedef struct FieldObject1557B0 FieldObject1557B0;
typedef struct FieldFloatState28F00 FieldFloatState28F00;
typedef struct FieldEntryOwner293F0 FieldEntryOwner293F0;
typedef struct FieldFlagTable2BB00 FieldFlagTable2BB00;
typedef struct FieldLookupNode2BF70 FieldLookupNode2BF70;
typedef struct FieldLookupList2BF70 FieldLookupList2BF70;
typedef struct FieldFlagState271B0 FieldFlagState271B0;
typedef struct FieldFlagState2B320 FieldFlagState2B320;
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
void func_0027B390(ResidentContextObject58* object, u32 value, s32 force);

/**
 * @brief Set the context's two signed script values.
 * @param object Field-context object to update.
 * @param first First signed value.
 * @param second Second signed value.
 */
void func_0027B3D0(void* object, s32 first, s32 second);

/**
 * @brief Test the state byte of the receiver's attached object.
 * @param object Field-context object to inspect.
 * @return One when the attachment exists and its byte at +0x15 is 5.
 */
s32 func_0027B710(ResidentContextObject58* object);

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
 * @brief Release and clear the receiver's attached object.
 * @param object Receiver holding the attachment.
 */
void func_0027B740(ResidentContextObject58* object);

/**
 * @brief Process an indexed operation on the field-context object.
 * @param object Field-context object to update.
 * @param index Operation index.
 */
void func_0027B7D0(ResidentContextObject58* object, u32 index);

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

/**
 * @brief Apply the stored context identifier using the supplied transition value.
 * @param object Field-context object containing the identifier.
 * @param value Second transition value.
 */
void func_0027CB20(ResidentContextObject58* object, s32 value);

#ifdef __cplusplus
}

/** Partial FieldClass1553B0 object with vtable D_155610 in main data. */
class FieldClass155610 : public FieldClass1553B0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass155610();

    /** @brief Update the controller. */
    virtual void update();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct ResidentContextObject58;

/** Run the shutdown hook on each object in the retained list. */
void func_0027C020(struct ResidentContextObject58* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"

/** Retained field object list. */
class FieldClass1557B0 : public FieldListObject, public FieldClass1502A0
{
public:
    static void* operator new(u32 size);

    /** @brief Release storage through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);

    FieldClass1557B0();

    virtual ~FieldClass1557B0();

    u8 unk8c[0x160];
};
#endif

#endif
