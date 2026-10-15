#ifndef SO3_OVERLAYS_3454_00_TEXT_003906F0_H
#define SO3_OVERLAYS_3454_00_TEXT_003906F0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
void func_00391E20(void* object);
#endif

/** Return bits 0 and 2 when the byte fields at offsets 0x38 and 0x39 are set. */
u32 func_0039A340(const u8* object);

/** Return whether the receiver's word at offset 0x14 is nonzero. */
s32 func_00397FC0(void* receiver);

/** Zero the 16-byte value at the supplied address. */
void func_003980A0(void* object);

/**
 * @brief Initialize the record's leading fields and pointer at offset 0x0C.
 * @param arg0 Record to initialize.
 * @return The initialized record.
 */
void* func_00398230(void* arg0);

/** Return whether the receiver's word at offset 0x14 is nonzero. */
s32 func_0039BFF0(void* receiver);

/**
 * @brief Initialize the record's leading fields and pointer at offset 0x0C.
 * @param arg0 Record to initialize.
 * @return The initialized record.
 */
void* func_0039C290(void* arg0);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00394D60(void* object);

/** Return 3 when the receiver byte at 0x949 is zero, otherwise 9. */
s16 func_00394D70(void* object);

/** Initialize the receiver and optionally register it with the owner. */
void* func_00394D90(void* object, s16 count);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00394E90(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00394EA0(void* object);

/**
 * @brief Return the fixed value 5.
 * @param object Receiver or first argument; unused.
 * @return Always 5.
 */
s32 func_00394EB0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00394EC0(void* object);

/**
 * @brief Call func_003940F0 with the object adjusted backward by 0xD0.
 * @param object Object whose subobject address is adjusted.
 */
void func_00394ED0(void* object);

/** Call func_003B5E00 on the subobject at offset 0xD0 and set byte 0x1AC to 2. */
void func_003940F0(void* object);

/**
 * @brief Return func_00394790's result for the object adjusted by -0xD0.
 * @param object Object whose subobject address is adjusted.
 * @return Result returned by func_00394790.
 */
void* func_00394EE0(void* object);

/**
 * @brief Call func_00393750 with the object adjusted backward by 0x290.
 * @param object Object whose subobject address is adjusted.
 */
void func_00394EF0(void* object);

/**
 * @brief Return func_00393C80's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00393C80.
 * @return Result returned by func_00393C80.
 */
void* func_00394F00(void* object, s16 count);

/**
 * @brief Call func_00393170 with the object adjusted backward by 0x290.
 * @param object Object whose subobject address is adjusted.
 */
void func_00394F10(void* object);

/**
 * @brief Return func_00393300's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00393300.
 * @return Result returned by func_00393300.
 */
void* func_00394F20(void* object, s16 count);

/**
 * @brief Return func_00392CD0's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00392CD0.
 * @return Result returned by func_00392CD0.
 */
void* func_00394F30(void* object, s16 count);

/**
 * @brief Call func_00391E20 with the object adjusted backward by 0x290.
 * @param object Object whose subobject address is adjusted.
 */
void func_00394F40(void* object);

/**
 * @brief Return func_00391FA0's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00391FA0.
 * @return Result returned by func_00391FA0.
 */
void* func_00394F50(void* object, s16 count);

/**
 * @brief Return func_00391CC0's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00391CC0.
 * @return Result returned by func_00391CC0.
 */
void* func_00394F60(void* object, s16 count);

/**
 * @brief Call func_0038F8C0 with the object adjusted backward by 0x290.
 * @param object Object whose subobject address is adjusted.
 */
void func_00394F70(void* object);

/**
 * @brief Return func_003906F0's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_003906F0.
 * @return Result returned by func_003906F0.
 */
void* func_00394F90(void* object, s16 count);

/**
 * @brief Call func_0038DFF0 with the object adjusted backward by 0x290.
 * @param object Object whose subobject address is adjusted.
 */
void func_00394FA0(void* object);

/**
 * @brief Call func_0038C850 with the object adjusted backward by 0xD0.
 * @param object Object whose subobject address is adjusted.
 */
void func_00394FC0(void* object);

/**
 * @brief Return func_0038D570's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_0038D570.
 * @return Result returned by func_0038D570.
 */
void* func_00394FD0(void* object, s16 count);

/**
 * @brief Return func_0038C7B0's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_0038C7B0.
 * @return Result returned by func_0038C7B0.
 */
void* func_00394FE0(void* object, s16 count);

/**
 * @brief Return func_0038BFD0's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_0038BFD0.
 * @return Result returned by func_0038BFD0.
 */
void* func_00394FF0(void* object, s16 count);

/**
 * @brief Return func_0038BFD0's result for the object adjusted backward by 0x460.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_0038BFD0.
 * @return Result returned by func_0038BFD0.
 */
void* func_00395000(void* object, s16 count);

/**
 * @brief Return func_0038ACD0's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_0038ACD0.
 * @return Result returned by func_0038ACD0.
 */
void* func_00395010(void* object, s16 count);

/**
 * @brief Return func_0038ACD0's result for the object adjusted backward by 0x460.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_0038ACD0.
 * @return Result returned by func_0038ACD0.
 */
void* func_00395020(void* object, s16 count);

/**
 * @brief Return func_00389720's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00389720.
 * @return Result returned by func_00389720.
 */
void* func_00395030(void* object, s16 count);

/**
 * @brief Call func_003889F0 with the object adjusted backward by 0x290.
 * @param object Object whose subobject address is adjusted.
 */
void func_00395040(void* object);

/**
 * @brief Return func_00388B30's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00388B30.
 * @return Result returned by func_00388B30.
 */
void* func_00395050(void* object, s16 count);

/**
 * @brief Call func_00387650 with the object adjusted backward by 0xD0.
 * @param object Object whose subobject address is adjusted.
 */
void func_00395060(void* object);

/**
 * @brief Return func_00387A60's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00387A60.
 * @return Result returned by func_00387A60.
 */
void* func_00395070(void* object, s16 count);

/**
 * @brief Call func_00386060 with the object adjusted backward by 0xD0.
 * @param object Object whose subobject address is adjusted.
 */
void func_00395080(void* object);

/**
 * @brief Return func_00385F70's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00385F70.
 * @return Result returned by func_00385F70.
 */
void* func_00395090(void* object, s16 count);

/**
 * @brief Return func_00385F70's result for the object adjusted backward by 0x220.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00385F70.
 * @return Result returned by func_00385F70.
 */
void* func_003950A0(void* object, s16 count);

/**
 * @brief Return func_00384FD0's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00384FD0.
 * @return Result returned by func_00384FD0.
 */
void* func_003950B0(void* object, s16 count);

/**
 * @brief Return func_00384C00's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00384C00.
 * @return Result returned by func_00384C00.
 */
void* func_003950C0(void* object, s16 count);

/**
 * @brief Return func_00383D40's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00383D40.
 * @return Result returned by func_00383D40.
 */
void* func_003950D0(void* object, s16 count);

/**
 * @brief Call func_00382D70 with the object adjusted backward by 0x290.
 * @param object Object whose subobject address is adjusted.
 */
void func_003950E0(void* object);

/**
 * @brief Return func_00383450's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00383450.
 * @return Result returned by func_00383450.
 */
void* func_00395100(void* object, s16 count);

/**
 * @brief Call func_00382A30 with the object adjusted backward by 0x290.
 * @param object Object whose subobject address is adjusted.
 */
void func_00395110(void* object);

/**
 * @brief Return func_00382CD0's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00382CD0.
 * @return Result returned by func_00382CD0.
 */
void* func_00395120(void* object, s16 count);

/**
 * @brief Return func_00382220's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00382220.
 * @return Result returned by func_00382220.
 */
void* func_00395130(void* object, s16 count);

/**
 * @brief Return func_00381CA0's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00381CA0.
 * @return Result returned by func_00381CA0.
 */
void* func_00395140(void* object, s16 count);

/**
 * @brief Call func_00381180 with the object adjusted backward by 0x290.
 * @param object Object whose subobject address is adjusted.
 */
void func_00395150(void* object);

/**
 * @brief Return func_00381450's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00381450.
 * @return Result returned by func_00381450.
 */
void* func_00395160(void* object, s16 count);

/**
 * @brief Call func_0037DC00 with the object adjusted backward by 0x290.
 * @param object Object whose subobject address is adjusted.
 */
void func_00395170(void* object);

/**
 * @brief Return func_0037FD20's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_0037FD20.
 * @return Result returned by func_0037FD20.
 */
void* func_00395180(void* object, s16 count);

/**
 * @brief Return func_003750E0's result for the object adjusted backward by 0xD0.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_003750E0.
 * @return Result returned by func_003750E0.
 */
void* func_00395190(void* object, s16 count);

/**
 * @brief Return func_0026F900's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_0026F900.
 * @return Result returned by func_0026F900.
 */
void* func_003951A0(void* object, s16 count);

/**
 * @brief Return func_00375180's result for the object adjusted backward by 0xD0.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00375180.
 * @return Result returned by func_00375180.
 */
void* func_003951B0(void* object, s16 count);

/**
 * @brief Return func_003752C0's result for the object adjusted backward by 0xD0.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_003752C0.
 * @return Result returned by func_003752C0.
 */
void* func_003951C0(void* object, s16 count);

/**
 * @brief Return func_00375600's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00375600.
 * @return Result returned by func_00375600.
 */
void* func_003951D0(void* object, s16 count);

/**
 * @brief Return func_00375980's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00375980.
 * @return Result returned by func_00375980.
 */
void* func_003951E0(void* object, s16 count);

/**
 * @brief Call func_003766F0 with the adjusted object and source object.
 * @param object Object whose subobject address is adjusted.
 * @param source Object passed to func_003766F0.
 */
void func_003951F0(void* object, void* source);

/**
 * @brief Return func_00397480's result for the object adjusted backward by 0x820.
 * @param object Object whose subobject address is adjusted.
 * @return Result returned by func_00397480.
 */
s32 func_00395200(void* object);

/**
 * @brief Return func_00374BB0's result for the adjusted object and count.
 * @param object Object whose subobject address is adjusted.
 * @param count Count passed to func_00374BB0.
 * @return Result returned by func_00374BB0.
 */
void* func_00395210(void* object, s16 count);

/**
 * @brief Call func_00375F30 with the adjusted object and source object.
 * @param object Object whose subobject address is adjusted.
 * @param source Object passed to func_00375F30.
 */
void func_00395220(void* object, void* source);

/** Return the floating-point value 1.0f. */
float func_00394C70(void* object);


/** Initialize the receiver and optionally register it with the owner. */
void* func_00394CE0(void* object, s16 count);

/** Initialize the receiver and release its optional allocation. */
void* func_00394B70(void* object, s16 count);

/** Initialize the receiver and optionally register it with the owner. */
void* func_00394E00(void* object, s16 count);

/** Return the first pointer argument unchanged. */
void* func_0039C0D0(void* value);

#ifdef __cplusplus
}
#endif

#endif
