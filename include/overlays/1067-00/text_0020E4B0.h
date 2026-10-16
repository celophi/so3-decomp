#ifndef SO3_OVERLAYS_1067_00_TEXT_0020E4B0_H
#define SO3_OVERLAYS_1067_00_TEXT_0020E4B0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ResidentContextObject38;

/**
 * @brief Configure the Field effect's byte parameters and scalar values.
 * @param state Field context owning the effect.
 * @param flag First parameter, stored as a byte.
 * @param amount Second parameter, stored as a byte.
 * @param value First scalar value.
 * @param duration Second scalar value.
 */
void func_0020F110(struct ResidentContextObject38* state, u32 flag, u32 amount, float value, float duration);

/**
 * @brief Find the script's coordinate record and copy its position and condition words.
 * @param state Script owner.
 * @param offset Byte offset into the script, rounded down to a word boundary.
 * @param position Receives three coordinates converted from signed integers.
 * @param word Receives the record's first word.
 * @param packed Receives its packed condition flags.
 * @return One when a coordinate record is found, otherwise zero.
 */
s32 func_0020EF90(struct ResidentContextObject38* state, u32 offset, float* position, u32* word, u32* packed);

/**
 * @brief Return the current frame time step.
 * @param object Unused receiver.
 * @return Frame time step.
 */
float func_0020E4B0(void* object);

/**
 * @brief Return whether the current field context has a nonzero word at offset 0x50.
 * @param object Receiver or first argument; unused.
 * @return Nonzero if the context word is nonzero.
 */
s32 func_0020E4C0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0020E4E0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0020E4F0(void* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "overlays/1067-00/text_00212560.h"

/** Character-name provider for field message and display code. */
class FieldCharacterNames
{
public:
    /** @brief Get a stored character name. @param index One-based character slot. @return Stored name. */
    virtual char* get_character_name(s32 index) = 0;
};

/** Partial field script object exposing context callbacks and character-name lookup. */
class FieldClass1516A0 : public FieldClass151D40, public FieldCharacterNames
{
public:
    FieldClass1516A0();

    virtual ~FieldClass1516A0();

    virtual void resolve_field_object_display_position(float* first, float* second, s32 identifier, float x, float z);

    virtual void set_field_object_value(s32 event, s32 identifier, float value);

    virtual s32 queue_field_request(s32 first, s32 second, s32 third, s32 fourth, s32 identifier, u32 flag);

    virtual void clear_field_requests(s8 index, u32 release);

    virtual s32 get_field_request_progress(s8 index);

    virtual s32 get_field_request_state(s8 index);

    virtual s32 has_no_pending_field_work();

    virtual void refresh_field_character_state();

    virtual void func_0020E560();

    virtual s32 func_0020E4C0();

    virtual char* get_character_name(s32 index);

    u8 unk5a4[0x6C];
};
#endif

#ifdef __cplusplus
extern "C"
{
    void func_0020F230(FieldClass1516A0* object, u32 first, u32 second, u32 third, s8 mode, u32 fifth, u32 sixth, float x, float y, float z);
}
#endif

#endif
