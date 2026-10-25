#ifndef SO3_OVERLAYS_1067_00_TEXT_00212560_H
#define SO3_OVERLAYS_1067_00_TEXT_00212560_H

#include "types.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_00200710.h"

/** Script context with an object list, context callbacks and word-count command handlers. */
class FieldClass151D40 : public FieldClass150DC0, public FieldClass1502A0
{
public:
    /** @brief Destroy the object list and inherited script state. */
    virtual ~FieldClass151D40();

    /** @brief Advance the registered script context. */
    virtual void update();

    /** @brief Reset the script command state. */
    virtual void func_00217AD0();

    /** @brief Select a command and event packet. @param offset Script byte offset. @param packet Packed event value. */
    virtual void func_0021DC60(u32 offset, u32 packet);

    /**
     * @brief Resolve display coordinates for a keyed field object.
     * @param x Receives the horizontal coordinate.
     * @param y Receives the vertical coordinate.
     * @param key Field object key.
     * @param width Horizontal extent used for clipping.
     * @param height Vertical extent used for clipping.
     */
    virtual void resolve_field_object_display_position(float* x, float* y, s32 key, float width, float height) = 0;

    /**
     * @brief Forward a scalar value to the keyed field object.
     * @param value Integer value forwarded to the object.
     * @param key Field object key.
     * @param amount Value forwarded to the object.
     */
    virtual void set_field_object_value(s32 value, s32 key, float amount) = 0;

    /**
     * @brief Queue a field request with an optional keyed attachment.
     * @param first First request value.
     * @param second Second request value.
     * @param third Third request value.
     * @param fourth Fourth request value.
     * @param key Optional attachment key, or -1.
     * @param enabled Whether to resolve and attach the keyed object.
     * @return Request slot, or -1 if the request could not be queued.
     */
    virtual s32 queue_field_request(s32 first, s32 second, s32 third, s32 fourth, s32 key, u32 enabled) = 0;

    /**
     * @brief Clear one or all field requests and optionally release their attachments.
     * @param index Request slot, or -1 for all slots.
     * @param release Whether to release attached objects.
     */
    virtual void clear_field_requests(s8 index, u32 release) = 0;

    /** @brief Get the interpolated progress value for a request slot. @param index Request slot. @return Progress value, or -1 for a negative slot. */
    virtual s32 get_field_request_progress(s8 index) = 0;

    /** @brief Get the state code for a request slot. @param index Request slot. @return Request state, or -1 for a negative slot. */
    virtual s32 get_field_request_state(s8 index) = 0;

    /** @brief Test whether no field work is pending. @return One when no work is pending, otherwise zero. */
    virtual s32 has_no_pending_field_work();

    /** @brief Refresh character state and its attached field display. */
    virtual void refresh_field_character_state() = 0;

    virtual void func_0020E560() = 0;

    virtual s32 func_0020E4C0() = 0;

    virtual s32 func_slot090(u32 count);

    virtual s32 func_slot094(u32 count);

    virtual s32 func_slot098(u32 count);

    virtual s32 func_slot09C(u32 count);

    virtual s32 func_slot0A0(u32 count);

    virtual s32 func_slot0A4(u32 count);

    virtual s32 func_slot0A8(u32 count);

    virtual s32 func_slot0AC(u32 count);

    virtual s32 func_slot0B0(u32 count);

    virtual s32 func_slot0B4(u32 count);

    virtual s32 func_slot0B8(u32 count);

    virtual s32 func_slot0BC(u32 count);

    virtual s32 func_slot0C0(u32 count);

    virtual s32 func_slot0C4(u32 count);

    virtual s32 func_slot0C8(u32 count);

    virtual s32 func_slot0CC(u32 count);

    virtual s32 func_slot0D0(u32 count);

    virtual s32 func_slot0D4(u32 count);

    virtual s32 func_slot0D8(u32 count);

    virtual s32 func_slot0DC(u32 count);

    virtual s32 func_slot0E0(u32 count);

    virtual s32 func_slot0E4(u32 count);

    virtual s32 func_slot0E8(u32 count);

    virtual s32 func_slot0EC(u32 count);

    virtual s32 func_slot0F0(u32 count);

    virtual s32 func_slot0F4(u32 count);

    virtual s32 func_slot0F8(u32 count);

    virtual s32 func_slot0FC(u32 count);

    virtual s32 func_slot100(u32 count);

    virtual s32 func_slot104(u32 count);

    virtual s32 func_slot108(u32 count);

    virtual s32 func_slot10C(u32 count);

    virtual s32 func_slot110(u32 count);

    virtual s32 func_slot114(u32 count);

    virtual s32 func_slot118(u32 count);

    virtual s32 func_slot11C(u32 count);

    virtual s32 func_slot120(u32 count);

    virtual s32 func_slot124(u32 count);

    virtual s32 func_slot128(u32 count);

    virtual s32 func_slot12C(u32 count);

    virtual s32 func_slot130(u32 count);

    virtual s32 func_slot134(u32 count);

    virtual s32 func_slot138(u32 count);

    virtual s32 func_slot13C(u32 count);

    virtual s32 func_slot140(u32 count);

    virtual s32 func_slot144(u32 count);

    virtual s32 func_slot148(u32 count);

    virtual s32 func_slot14C(u32 count);

    virtual s32 func_slot150(u32 count);

    virtual s32 func_slot154(u32 count);

    virtual s32 func_slot158(u32 count);

    virtual s32 func_slot15C(u32 count);

    virtual s32 func_slot160(u32 count);

    virtual s32 func_slot164(u32 count);

    virtual s32 func_slot168(u32 count);

    virtual s32 func_slot16C(u32 count);

    virtual s32 func_slot170(u32 count);

    virtual s32 func_slot174(u32 count);

    virtual s32 func_slot178(u32 count);

    virtual s32 func_slot17C(u32 count);

    virtual s32 func_slot180(u32 count);

    virtual s32 func_slot184(u32 count);

    virtual s32 func_slot188(u32 count);

    virtual s32 func_slot18C(u32 count);

    virtual s32 func_slot190(u32 count);

    virtual s32 func_slot194(u32 count);

    virtual s32 func_slot198(u32 count);

    virtual s32 func_slot19C(u32 count);

    virtual s32 func_slot1A0(u32 count);

    virtual s32 func_slot1A4(u32 count);

    virtual s32 func_slot1A8(u32 count);

    virtual s32 func_slot1AC(u32 count);

    virtual s32 func_slot1B0(u32 count);

    virtual s32 func_slot1B4(u32 count);

    virtual s32 func_slot1B8(u32 count);

    virtual s32 func_slot1BC(u32 count);

    virtual s32 func_slot1C0(u32 count);

    virtual s32 func_slot1C4(u32 count);

    virtual s32 func_slot1C8(u32 count);

    virtual s32 func_slot1CC(u32 count);

    virtual s32 func_slot1D0(u32 count);

    virtual s32 func_slot1D4(u32 count);

    virtual s32 func_slot1D8(u32 count);

    virtual s32 func_slot1DC(u32 count);

    virtual s32 func_slot1E0(u32 count);

    virtual s32 func_slot1E4(u32 count);

    virtual s32 func_slot1E8(u32 count);

    virtual s32 func_slot1EC(u32 count);

    virtual s32 func_slot1F0(u32 count);

    virtual s32 func_slot1F4(u32 count);

    virtual s32 func_slot1F8(u32 count);

    virtual s32 func_slot1FC(u32 count);

    virtual s32 func_slot200(u32 count);

    virtual s32 func_slot204(u32 count);

    virtual s32 func_slot208(u32 count);

    virtual s32 func_slot20C(u32 count);

    virtual s32 func_slot210(u32 count);

    virtual s32 func_slot214(u32 count);

    virtual s32 func_slot218(u32 count);

    virtual s32 func_slot21C(u32 count);

    virtual s32 func_slot220(u32 count);

    virtual s32 func_slot224(u32 count);

    virtual s32 func_slot228(u32 count);

    virtual s32 func_slot22C(u32 count);

    virtual s32 func_slot230(u32 count);

    virtual s32 func_slot234(u32 count);

    virtual s32 func_slot238(u32 count);

    virtual s32 func_slot23C(u32 count);

    virtual s32 func_slot240(u32 count);

    virtual s32 func_slot244(u32 count);

    virtual s32 func_slot248(u32 count);

    virtual s32 func_slot24C(u32 count);

    virtual s32 func_slot250(u32 count);

    virtual s32 func_slot254(u32 count);

    virtual s32 func_slot258(u32 count);

    virtual s32 func_slot25C(u32 count);

    virtual s32 func_slot260(u32 count);

    virtual s32 func_slot264(u32 count);

    virtual s32 func_slot268(u32 count);

    virtual s32 func_slot26C(u32 count);

    virtual s32 func_slot270(u32 count);

    virtual s32 func_slot274(u32 count);

    virtual s32 func_slot278(u32 count);

    virtual s32 func_slot27C(u32 count);

    virtual s32 func_slot280(u32 count);

    virtual s32 func_slot284(u32 count);

    virtual s32 func_slot288(u32 count);

    virtual s32 func_slot28C(u32 count);

    virtual s32 func_slot290(u32 count);

    virtual s32 func_slot294(u32 count);

    virtual s32 func_slot298(u32 count);

    virtual s32 func_slot29C(u32 count);

    virtual s32 func_slot2A0(u32 count);

    virtual s32 func_slot2A4(u32 count);

    virtual s32 func_slot2A8(u32 count);

    virtual s32 func_slot2AC(u32 count);

    virtual s32 func_slot2B0(u32 count);

    virtual s32 func_slot2B4(u32 count);

    virtual s32 func_slot2B8(u32 count);

    virtual s32 func_slot2BC(u32 count);

    virtual s32 func_slot2C0(u32 count);

    virtual s32 func_slot2C4(u32 count);

    virtual s32 func_slot2C8(u32 count);

    virtual s32 func_slot2CC(u32 count);

    virtual s32 func_slot2D0(u32 count);

    virtual s32 func_slot2D4(u32 count);

    virtual s32 func_slot2D8(u32 count);

    virtual s32 func_slot2DC(u32 count);

    virtual s32 func_slot2E0(u32 count);

    virtual s32 func_slot2E4(u32 count);

    virtual s32 func_slot2E8(u32 count);

    virtual s32 func_slot2EC(u32 count);

    virtual s32 func_slot2F0(u32 count);

    virtual s32 func_slot2F4(u32 count);

    virtual s32 func_slot2F8(u32 count);

    virtual s32 func_slot2FC(u32 count);

    virtual s32 func_slot300(u32 count);

    virtual s32 func_slot304(u32 count);

    virtual s32 func_slot308(u32 count);

    virtual s32 func_slot30C(u32 count);

    virtual s32 func_slot310(u32 count);

    virtual s32 func_slot314(u32 count);

    virtual s32 func_slot318(u32 count);

    virtual s32 func_slot31C(u32 count);

    virtual s32 func_slot320(u32 count);

    virtual s32 func_slot324(u32 count);

    virtual s32 func_slot328(u32 count);

    virtual s32 func_slot32C(u32 count);

    virtual s32 func_slot330(u32 count);

    virtual s32 func_slot334(u32 count);

    virtual s32 func_slot338(u32 count);

    virtual s32 func_slot33C(u32 count);

    virtual s32 func_slot340(u32 count);

    virtual s32 func_slot344(u32 count);

    virtual s32 func_slot348(u32 count);

    virtual s32 func_slot34C(u32 count);

    virtual s32 func_slot350(u32 count);

    virtual s32 func_slot354(u32 count);

    virtual s32 func_slot358(u32 count);

    virtual s32 func_slot35C(u32 count);

    virtual s32 func_slot360(u32 count);

    virtual s32 func_slot364(u32 count);

    virtual s32 func_slot368(u32 count);

    virtual s32 func_slot36C(u32 count);

    virtual s32 func_slot370(u32 count);

    virtual s32 func_slot374(u32 count);

    virtual s32 func_slot378(u32 count);

    virtual s32 func_slot37C(u32 count);

    virtual s32 func_slot380(u32 count);

    virtual s32 func_slot384(u32 count);

    virtual s32 func_slot388(u32 count);

    virtual s32 func_slot38C(u32 count);

    virtual s32 func_slot390(u32 count);

    virtual s32 func_slot394(u32 count);

    virtual s32 func_slot398(u32 count);

    virtual s32 func_slot39C(u32 count);

    virtual s32 func_slot3A0(u32 count);

    virtual s32 func_slot3A4(u32 count);

    virtual s32 func_slot3A8(u32 count);

    virtual s32 func_slot3AC(u32 count);

    virtual s32 func_slot3B0(u32 count);

    virtual s32 func_slot3B4(u32 count);

    virtual s32 func_slot3B8(u32 count);

    virtual s32 func_slot3BC(u32 count);

    virtual s32 func_slot3C0(u32 count);

    virtual s32 func_slot3C4(u32 count);

    virtual s32 func_slot3C8(u32 count);

    virtual s32 func_slot3CC(u32 count);

    virtual s32 func_slot3D0(u32 count);

    virtual s32 func_slot3D4(u32 count);

    virtual s32 func_slot3D8(u32 count);

    virtual s32 func_slot3DC(u32 count);

    virtual s32 func_slot3E0(u32 count);

    virtual s32 func_slot3E4(u32 count);

    virtual s32 func_slot3E8(u32 count);

    virtual s32 func_slot3EC(u32 count);

    virtual s32 func_slot3F0(u32 count);

    virtual s32 func_slot3F4(u32 count);

    virtual s32 func_slot3F8(u32 count);

    virtual s32 func_slot3FC(u32 count);

    virtual s32 func_slot400(u32 count);

    virtual s32 func_slot404(u32 count);

    virtual s32 func_slot408(u32 count);

    virtual s32 func_slot40C(u32 count);

    virtual s32 func_slot410(u32 count);

    virtual s32 func_slot414(u32 count);

    virtual s32 func_slot418(u32 count);

    virtual s32 func_slot41C(u32 count);

    virtual s32 func_slot420(u32 count);

    virtual s32 func_slot424(u32 count);

    virtual s32 func_slot428(u32 count);

    virtual s32 func_slot42C(u32 count);

    virtual s32 func_slot430(u32 count);

    virtual s32 func_slot434(u32 count);

    virtual s32 func_slot438(u32 count);

    virtual s32 func_slot43C(u32 count);

    virtual s32 func_slot440(u32 count);

    virtual s32 func_slot444(u32 count);

    virtual s32 func_slot448(u32 count);

    virtual s32 func_slot44C(u32 count);

    virtual s32 func_slot450(u32 count);

    virtual s32 func_slot454(u32 count);

    virtual s32 func_slot458(u32 count);

    virtual s32 func_slot45C(u32 count);

    virtual s32 func_slot460(u32 count);

    virtual s32 func_slot464(u32 count);

    virtual s32 func_slot468(u32 count);

    virtual s32 func_slot46C(u32 count);

    virtual s32 func_slot470(u32 count);

    void* script_data;
    const u32* current;
    void* unk54c;
    s32 unk550;
    void* attachments[16];
    void* special;
    u32 previous_instruction_index;
    u8 unk59c;
    u8 unk59d_0 : 1;
    u8 unk59d_1 : 1;
    u8 unk59d_2 : 1;
    u8 unk59d_3 : 1;
    u8 unk59d_4_7 : 4;
    u8 unk59e[2];
};
#endif


typedef struct ResidentContextObject38 ResidentContextObject38;

/** Header for the script data block whose word at +8 points to its records. */
typedef struct FieldScriptData217590
{
    u8 unk00[8];
    u32 unk08;
} FieldScriptData217590;

/** Script command state shared by field callback handlers. */
typedef struct FieldScriptObject151D40
{
    u8 unk00[0x14];
    float unk14;
    u8 unk18[0x40C];
    u32 unk424;
    u32 unk428[40];
    unsigned char unk4C8_0 : 1;
    unsigned char unk4C8_1 : 7;
    u8 unk4C9[0x7B];
    FieldScriptData217590* unk544;
    const u32* unk548;
} FieldScriptObject151D40;
typedef struct FieldObject217CE0 FieldObject217CE0;

/** A 16-byte script-resource record with a signed key and opaque payload. */
typedef struct FieldScriptRecord217590
{
    s32 unk00;
    u8 unk04[12];
} FieldScriptRecord217590;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Test the resident state for a key.
 * @param object Resident state receiver.
 * @param key Key tested after conversion to a halfword.
 * @return Nonzero when the key is set.
 */
s32 func_00217600(ResidentContextObject38* object, s32 key);

/**
 * @brief Set a byte on each attached object in the receiver's pointer array.
 * @param object Receiver holding 16 slots and one extra attachment.
 * @param value Byte to store on each non-null attachment.
 */
void func_00217CE0(FieldObject217CE0* object, u8 value);

/**
 * @brief Set the low flag bit from the low bit of the command value.
 * @param object Script receiver to update.
 * @param value Command value supplying the flag bit.
 */
void func_002125C0(FieldScriptObject151D40* object, u32 value);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002127C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002127D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212A50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212A60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212A70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212A80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212A90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AD0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212AF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B00(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B10(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212B90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BD0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212BF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C00(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C10(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212C90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CD0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212CF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D00(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D10(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212D90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DD0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212DF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E00(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E10(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212E90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212EA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212EB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212EC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212ED0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212EE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212EF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F00(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F10(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F50(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F80(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212F90(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FA0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FC0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FD0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FE0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00212FF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213000(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213010(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213020(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213030(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213040(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213050(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213060(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213070(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213080(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213090(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002130A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002130B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002130C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Copy the first command word to the global word.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002130D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002130F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213100(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213110(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213120(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213130(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213140(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213150(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213160(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213170(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213180(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213190(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002131F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213200(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213210(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213220(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213230(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213240(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213250(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213260(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213270(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213280(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213290(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002132F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213300(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213310(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213320(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213330(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213340(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213350(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213360(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213370(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213380(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213390(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002133F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213400(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213410(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213420(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213430(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213440(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213450(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213460(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213470(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213480(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213490(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002134F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213500(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213510(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213520(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213530(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213540(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213550(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213560(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213570(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213580(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213590(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002135F0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213600(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213610(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213620(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213630(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213640(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213650(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213660(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213670(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213680(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00213690(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002136A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002136B0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002136C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Script command receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002136D0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Find a record in the script resource's sentinel-terminated table.
 * @param object Script receiver containing the resource header.
 * @param key Record key to find, or -1 to return the first record.
 * @return Matching record, or null when the table is absent or the key is missing.
 */
FieldScriptRecord217590* func_00217590(FieldScriptObject151D40* object, s32 key);

/**
 * @brief Write a script variable word or packed runtime flag.
 * @param object Script receiver containing local variable words.
 * @param key Encoded storage selector and index, or 0xFFFF for the current word.
 * @param value Value to write; packed flags use its truth value.
 */
void func_00217780(FieldScriptObject151D40* object, s32 key, u32 value);

/**
 * @brief Read a script variable word or a packed runtime flag.
 * @param object Script receiver containing local variable words.
 * @param key Encoded storage selector and index, or 0xFFFF for the current word.
 * @return Stored word or normalized flag value; zero for an unknown selector.
 */
u32 func_00217920(FieldScriptObject151D40* object, s32 key);

#ifdef __cplusplus
}
#endif

#endif
