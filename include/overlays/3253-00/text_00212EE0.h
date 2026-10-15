#ifndef SO3_OVERLAYS_3253_00_TEXT_00212EE0_H
#define SO3_OVERLAYS_3253_00_TEXT_00212EE0_H

#include "types.h"

union LibVector4;
struct BattlePointFlagFields20;
struct BattlePointFlagSlot20;
struct BattlePointFlagFields30;
struct BattlePointFlagSlot30;
struct BattlePointFlagSlot40;
struct BattlePointFlagFields40;
struct BattleQuaternionTrackFields;
struct BattleQuaternionKey;
struct BattleVectorSlot20;
struct BattleVectorFields20;
struct BattleGetters38;
struct BattleGetters18;
struct BattleGetters48;
struct BattleFloatFields50;
struct BattleGetters28;
struct BattleStateByte60;

#ifdef __cplusplus
extern "C" {
void func_00218D40(u8* object, float x, float y, float z);
#endif

/** Install the record's pointer at offset 0x1C, reset it, and return it. */
void* func_0021E540(void* object);
/** Install the record's pointer at offset 0x1C, reset it, and return it. */
void* func_0021E5A0(void* object);
/** Install the record's pointer at offset 0x10, reset it, and return it. */
void* func_0021E600(void* object);

/** Initialize the receiver and install its primary vtable. */
void* func_0021BCD0(void* object);
/** Initialize the receiver and install its primary vtable. */
void* func_0021C260(void* object);
/** Initialize the receiver and install its primary vtable. */
void* func_0021C810(void* object);

/** Forward to the no-argument reset routine. */
void func_0021C9F0(void);

/** Forward to the no-argument reset routine. */
void func_0021CB90(void);

/**
 * @brief Clear all four vector components.
 * @param vector Vector to clear.
 */
void battle_clear_vector4(LibVector4* vector);

/**
 * @brief Test whether a packed quaternion track contains an exact key value.
 * @param object Partial quaternion track receiver.
 * @param key Key value to find.
 * @return One when a key matches exactly; zero otherwise.
 */
s32 battle_has_quaternion_key(const BattleQuaternionTrackFields* object, float key);

/**
 * @brief Use externally owned quaternion keys and record their value span.
 * @param object Quaternion channel receiver.
 * @param count Number of supplied keys.
 * @param keys Caller-owned packed quaternion keys.
 */
void battle_use_external_quaternion_keys(BattleQuaternionTrackFields* object, s32 count, BattleQuaternionKey* keys);

/**
 * @brief Reset the observed quaternion channel state and clear its key pointer.
 * @param object Quaternion channel receiver.
 */
void battle_reset_quaternion_channel(BattleQuaternionTrackFields* object);

/**
 * @brief Set the high quaternion mode nibble and update the native mode flag.
 * @param object Quaternion channel receiver.
 * @param mode Mode value whose low four bits are stored.
 */
void battle_set_quaternion_high_mode(BattleQuaternionTrackFields* object, s32 mode);

/**
 * @brief Set the low quaternion mode nibble and update the native mode flag.
 * @param object Quaternion channel receiver.
 * @param mode Mode value whose low four bits are stored.
 */
void battle_set_quaternion_low_mode(BattleQuaternionTrackFields* object, s32 mode);

/**
 * @brief Return the span of the packed quaternion key values.
 * @param object Partial quaternion track receiver.
 * @return Last key value minus first, or zero when there are fewer than two keys.
 */
float battle_quaternion_key_span(const BattleQuaternionTrackFields* object);

/**
 * @brief Store a point vector and set the receiver's byte at 0x50.
 * @param object Partial point-vector receiver.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void battle_set_point_vector_and_flag(BattlePointFlagFields20* object, float x, float y, float z);

/**
 * @brief Set the receiver's byte at 0x50 and copy a 128-bit value to 0x20.
 * @param object Receiver.
 * @param value Value to copy.
 */
void func_00218C40(BattlePointFlagSlot20* object, const unsigned __int128* value);

/**
 * @brief Set the receiver's byte at 0x50 and write four floats at 0x30.
 * @param object Receiver.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 */
void func_00218C80(BattlePointFlagFields30* object, float x, float y, float z, float w);

/**
 * @brief Set the receiver's byte at 0x50 and pass its vector at 0x30 to the vector helper.
 * @param object Receiver.
 */
void func_00218CE0(BattlePointFlagFields30* object);

/**
 * @brief Set the receiver's byte at 0x50 and pass its vector at 0x30 to the vector helper.
 * @param object Receiver.
 */
void func_00218D10(BattlePointFlagFields30* object);

/**
 * @brief Set the receiver's byte at 0x50 and copy a 128-bit value to 0x30.
 * @param object Receiver.
 * @param value Value to copy.
 */
void func_00218CA0(BattlePointFlagSlot30* object, const unsigned __int128* value);

/**
 * @brief Set the receiver's byte at 0x50 and copy a 128-bit value to 0x30.
 * @param object Receiver.
 * @param value Value to copy.
 */
void func_00218CC0(BattlePointFlagSlot30* object, const unsigned __int128* value);

/**
 * @brief Set the receiver's byte at 0x50 and copy a 128-bit value to 0x40.
 * @param object Receiver.
 * @param value Value to copy.
 */
void func_00218D80(BattlePointFlagSlot40* object, const unsigned __int128* value);

/**
 * @brief Set the receiver's byte at 0x50 and copy a 128-bit value to 0x40.
 * @param object Receiver.
 * @param value Value to copy.
 */
void func_00218DA0(BattlePointFlagSlot40* object, const unsigned __int128* value);

/**
 * @brief Set the receiver's byte at 0x50 and write three floats at 0x40.
 * @param object Receiver.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_00218DC0(BattlePointFlagFields40* object, float x, float y, float z);

/**
 * @brief Test whether a floating-point value is less than zero.
 * @param value Value to test.
 * @return One for a negative value; zero otherwise, including unordered values.
 */
s32 battle_float_is_negative(float value);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00218C20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00218C30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00218DE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00218DF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00218E70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00218E80(void* object);

/**
 * @brief Return the address of the global object at 0x0051E050.
 * @return Address of the global object.
 */
void* func_00218EB0(void);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00218EC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00218ED0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00218EE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00218EF0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00218F00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00218F10(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00218F20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00218FC0(void* object);

/**
 * @brief Return the fixed value 9.
 * @param object Receiver or first argument; unused.
 * @return Always 9.
 */
s32 func_00219250(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00219260(void* object);

/** Build and return a pointer to the four-word stack value. */
void* func_00219280(void);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002192C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002192D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0021CA10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0021CAA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0021CAB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0021CAC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0021CAD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0021CAE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0021CAF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0021FBC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0021FBD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0021FBE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0021FBF0(void* object);

/**
 * @brief Clear the four words at offsets 0x0, 0x4, 0x8, and 0xC.
 * @param object Receiver to update.
 */
void func_0021FC50(void* object);

/**
 * @brief Read the word at receiver offset 0x4.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0021FE20(const void* object);

/**
 * @brief Read the word at receiver offset 0x18.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_00220150(const void* object);

/**
 * @brief Read the signed halfword at receiver offset 0x20.
 * @param object Receiver to inspect.
 * @return Stored signed value.
 */
s32 func_00220160(const void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220170(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220180(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220190(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002201A0(void* object);

/**
 * @brief Return the floating-point value zero.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_002201B0(void* object);

/**
 * @brief Read the word at receiver offset 0x4.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_002201F0(const void* object);

/**
 * @brief Return the receiver address.
 * @param object Receiver to inspect.
 * @return Receiver address.
 */
void* func_00220620(const void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002208D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220910(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220950(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220990(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00220A90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220AD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220B10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220B50(void* object);

/**
 * @brief Return the receiver address.
 * @param object Receiver to inspect.
 * @return Receiver address.
 */
void* func_00220C30(const void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00220E70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220EB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220EF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00220F30(void* object);

/**
 * @brief Return the receiver address.
 * @param object Receiver to inspect.
 * @return Receiver address.
 */
void* func_00221060(const void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00222950(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00222960(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00222970(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00222BC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00222C00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00222C40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00222C80(void* object);

/**
 * @brief Copy a 128-bit value to the receiver's slot.
 * @param object Receiver containing the slot.
 * @param value Value to copy.
 */
void func_00218B50(BattleVectorSlot20* object, const unsigned __int128* value);

/**
 * @brief Copy a 128-bit value to the receiver's slot.
 * @param object Receiver containing the slot.
 * @param value Value to copy.
 */
void func_00218B60(BattleVectorSlot20* object, const unsigned __int128* value);

/**
 * @brief Store three vector components and set the fourth component to one.
 * @param object Receiver containing the vector at offset 0x20.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void battle_set_point_vector(BattleVectorFields20* object, float x, float y, float z);

/**
 * @brief Clear the halfwords at offsets 0x10 and 0x12 and the words at 0x14 and 0x18.
 * @param object Receiver to update.
 */
void func_0021E580(void* object);

/**
 * @brief Clear the halfwords at offsets 0x10 and 0x12 and the words at 0x14 and 0x18.
 * @param object Receiver to update.
 */
void func_0021E5E0(void* object);

/**
 * @brief Clear the halfwords at offsets 0x4 and 0x6 and the words at 0x8 and 0xC.
 * @param object Receiver to update.
 */
void func_0021E640(void* object);

/**
 * @brief Read the receiver's word at offset 0x30.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_0021EA60(const BattleGetters38* object);

/**
 * @brief Read the receiver's signed halfword at offset 0x38.
 * @param object Receiver.
 * @return Stored signed halfword.
 */
s16 func_0021EA70(const BattleGetters38* object);

/**
 * @brief Clear the four words at offsets 0x0, 0x4, 0x8, and 0xC.
 * @param object Receiver to update.
 */
void func_0021F050(void* object);

/**
 * @brief Read the word at receiver offset 0x4.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0021F200(const void* object);

/**
 * @brief Read the receiver's word at offset 0x10.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_0021F530(const BattleGetters18* object);

/**
 * @brief Read the receiver's signed halfword at offset 0x18.
 * @param object Receiver.
 * @return Stored signed halfword.
 */
s16 func_0021F540(const BattleGetters18* object);

/**
 * @brief Return the floating-point value zero.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_0021F550(void* object);

/**
 * @brief Read the word at receiver offset 0x4.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0021F590(const void* object);

/**
 * @brief Read the receiver's word at offset 0x40.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_0021FBA0(const BattleGetters48* object);

/**
 * @brief Read the receiver's signed halfword at offset 0x48.
 * @param object Receiver.
 * @return Stored signed halfword.
 */
s16 func_0021FBB0(const BattleGetters48* object);

/**
 * @brief Read the receiver's word at offset 0x10.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_00222BA0(const BattleGetters18* object);

/**
 * @brief Read the receiver's signed halfword at offset 0x18.
 * @param object Receiver.
 * @return Stored signed halfword.
 */
s16 func_00222BB0(const BattleGetters18* object);

/**
 * @brief Clear the word at offset 0x48 and initialize the receiver state.
 * @param object Receiver to update.
 */
void func_0021D200(void* object);

/**
 * @brief Install the method table at offset 0x4C and return the receiver.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
void* func_0021E450(void* object);

/**
 * @brief Install the method table at offset 0x1C and return the receiver.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
void* func_0021E4D0(void* object);

/**
 * @brief Copy the receiver's float at offset 0x4C to an output.
 * @param object Receiver.
 * @param output Destination for the value.
 */
void func_0021D250(const BattleFloatFields50* object, float* output);

/**
 * @brief Copy the receiver's float at offset 0x50 to an output.
 * @param object Receiver.
 * @param output Destination for the value.
 */
void func_0021E410(const BattleFloatFields50* object, float* output);

/**
 * @brief Clear the four words at offsets 0x0, 0x4, 0x8, and 0xC.
 * @param object Receiver to update.
 */
void func_0021EA80(void* object);

/**
 * @brief Read the word at receiver offset 0x4.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0021EAF0(const void* object);

/**
 * @brief Read the receiver's word at offset 0x20.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_0021EFE0(const BattleGetters28* object);

/**
 * @brief Read the receiver's signed halfword at offset 0x28.
 * @param object Receiver.
 * @return Stored signed halfword.
 */
s16 func_0021EFF0(const BattleGetters28* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to 0.
 * @param object Receiver.
 */
void func_00218E60(BattleStateByte60* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to 0.
 * @param object Receiver.
 */
void func_00219270(BattleStateByte60* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to 9.
 * @param object Receiver.
 */
void func_002192B0(BattleStateByte60* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to 6.
 * @param object Receiver.
 */
void func_002193D0(BattleStateByte60* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to 9.
 * @param object Receiver.
 */
void func_002194D0(BattleStateByte60* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to 9.
 * @param object Receiver.
 */
void func_002194E0(BattleStateByte60* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to 9.
 * @param object Receiver.
 */
void func_002195E0(BattleStateByte60* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to 9.
 * @param object Receiver.
 */
void func_002196E0(BattleStateByte60* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to 9.
 * @param object Receiver.
 */
void func_002197E0(BattleStateByte60* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to 6.
 * @param object Receiver.
 */
void func_002198E0(BattleStateByte60* object);

/**
 * @brief Set the receiver's byte at offset 0x60 to 9.
 * @param object Receiver.
 */
void func_002198F0(BattleStateByte60* object);

#ifdef __cplusplus
/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_0021E9A0(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_0021EF20(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_0021F470(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_0021FAE0(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_00220090(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_00222730(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_00222790(void* object, u8 mode);


/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_0021EA00(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_0021EF80(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_0021F4D0(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_0021FB40(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_002200F0(void* object, u8 mode);


/** Clear the vector at offset 0x90 and update the associated state. */
void func_0021CC40(void* object);
/** Clear the vector at offset 0xB0 and update the associated state. */
void func_0021D570(void* object);
s32 func_0021FC00(void* object, float key);
s32 func_0021F000(void* object, float key);

/** Return the key span between the first and last entries. */
float func_0021F070(void* object);

/** Write the difference between the selected 8-byte entry value and the first value. */
void func_0021D220(const void* object, float* output);

/** Write the difference between the selected 16-byte entry value and the first value. */
void func_0021E420(const void* object, float* output);
float func_002203E0(void* object);
float func_00220800(void* object);
float func_00220DA0(void* object);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_0021FC00(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_00220430(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_00220850(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_00220DF0(void* object, float key);

/** Initialize the object, vtable, and first word, then return it. */
void* func_0021D380(void* receiver);

}
#endif

#endif
