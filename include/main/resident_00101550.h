#ifndef SO3_MAIN_RESIDENT_00101550_H
#define SO3_MAIN_RESIDENT_00101550_H

#include "types.h"

#ifdef __cplusplus
/** Resident object root with vtable at 0x14FA20. */
class ResidentClass14FA20
{
public:
    /** @brief Destroy the resident root. */
    virtual ~ResidentClass14FA20();
};

/** Partial resident intrusive node with vtable at 0x14FA30. */
class ResidentClass14FA30 : public ResidentClass14FA20
{
public:
    /** @brief Destroy the intrusive node. */
    virtual ~ResidentClass14FA30();

    ResidentClass14FA30* previous;

    ResidentClass14FA30* next;
};

/** Partial resident object interface with vtable at 0x14FA40. */
class ResidentClass14FA40 : public ResidentClass14FA30
{
public:
    /** @brief Destroy the resident object. */
    virtual ~ResidentClass14FA40();

    /** @brief Return the object's kind. @return Object kind. */
    virtual s32 func_00104730();

    /** @brief Queue the object for release. */
    virtual void func_00104740();

    s16 list_kind;

    u8 unk0e;

    u8 unk0f;

    void* owner;
};
#endif

/** Dispatch table whose complete layout is not yet known. */
typedef struct ResidentDispatchTable ResidentDispatchTable;

/** Partial prefix of an object registered with the resident dispatcher. */
typedef struct ResidentRegisteredObject
{
    const ResidentDispatchTable* dispatch;
} ResidentRegisteredObject;

/** Partial resident object reached through D_001B65E8. */
typedef struct ResidentObject1B65E8
{
    u8 unk00[0x30];
    u8 unk30;
} ResidentObject1B65E8;

/** Opaque resident decoder used by the resource loading helpers. */
typedef struct ResidentDecodeObject ResidentDecodeObject;

/** Partial resource header containing a payload size and relative link. */
typedef struct ResidentResourceHeader
{
    u8 unk00[8];
    u32 unk08;
    u32 next_offset;
} ResidentResourceHeader;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Run the object's two update steps until the second reports no more work.
 * @param object Object to update.
 * @return Nonzero while the object is still busy.
 */
s32 func_00102AA0(ResidentObject1B65E8* object);

/**
 * @brief Submit a request to the object at D_001B65E8.
 * @param object Receiving object.
 * @param key First request word.
 * @param size Request size.
 * @param mask Third request word.
 * @param word Fourth request word.
 * @param mode Fifth request word.
 * @return Request result; meaning not yet known.
 */
s32 func_00103640(ResidentObject1B65E8* object, s32 key, u32 size, u32 mask, u32 word, s32 mode);

/**
 * @brief Submit the alternative request form to the object at D_001B65E8.
 * @param object Receiving object.
 * @param key First request word.
 * @param size Request size.
 * @param mask Third request word.
 * @param word Fourth request word.
 * @param mode Fifth request word.
 * @return Request result; meaning not yet known.
 */
s32 func_00103B20(ResidentObject1B65E8* object, s32 key, u32 size, u32 mask, u32 word, s32 mode);

/**
 * @brief Submit a resident request with an owner and two extra words; meaning not yet known.
 * @param object Resident object D_001B65E8.
 * @param key First request word.
 * @param size Second request word.
 * @param mask Third request word.
 * @param value Fourth request word.
 * @param owner Owner passed through to the request.
 * @param word Sixth request word.
 * @param mode Seventh request word.
 * @param flag Eighth request word.
 * @return Request result; meaning not yet known.
 */
s32 func_00103E70(ResidentObject1B65E8* object, s32 key, u32 size, u32 mask, s32 value, void* owner, u32 word, s32 mode,
                  s32 flag);

/**
 * @brief Initialize the dispatch pointer and register the object.
 * @param object Object to register.
 * @return The registered object.
 */
ResidentRegisteredObject* func_00101560(ResidentRegisteredObject* object);

/** Resident resource decoder. */
extern ResidentDecodeObject* D_001B65EC;

/**
 * @brief Decode or copy the selected resource into a destination buffer.
 * @param decoder Resident decoder.
 * @param source Resource header.
 * @param destination Destination buffer.
 * @param index Resource index.
 * @return Decode result.
 */
s32 func_001025A0(ResidentDecodeObject* decoder, ResidentResourceHeader* source, void* destination, s32 index);

/**
 * @brief Allocate storage for the selected resource.
 * @param decoder Resident decoder.
 * @param source Resource header.
 * @param index Resource index.
 * @param aligned Allocation alignment mode.
 * @return Allocated byte buffer, or null when allocation fails.
 */
u8* func_00102920(ResidentDecodeObject* decoder, ResidentResourceHeader* source, s32 index, s32 aligned);

/**
 * @brief Find a resource header by following its relative links.
 * @param decoder Resident decoder; unused.
 * @param source First resource header.
 * @param index Number of links to follow.
 * @return Selected header, or null when the chain ends.
 */
ResidentResourceHeader* func_00102A40(ResidentDecodeObject* decoder, ResidentResourceHeader* source, s32 index);

/** Return the fixed integer value 3. */
s32 func_00104730(void* object);

void func_00101550(void* object);
void func_00102A90(void* object);
void func_00104770(void* object);
void func_00104780(void* object);

/**
 * @brief Pass the pointer at offset 0x90 to the resident helper.
 * @param receiver Object containing the pointer.
 * @param argument Input pointer forwarded to the resident helper.
 */
void func_00107D90(void* receiver, void* argument);

/**
 * @brief Pass the pointer at offset 0x90 to the alternate resident helper.
 * @param receiver Object containing the pointer.
 * @param argument Input pointer forwarded to the resident helper.
 */
void func_00107DB0(void* receiver, void* argument);

/**
 * @brief Run the resident helper with an object and four word arguments.
 * @param object Input object.
 * @param arg1 First input word.
 * @param arg2 Second input word.
 * @param arg3 Third input word.
 * @param arg4 Fourth input word.
 */
void func_00108C40(void* object, u32 arg1, u32 arg2, u32 arg3, u32 arg4);

/** Run the resident object helper with four word arguments. */
s32 func_00107B10(void* object, u32 arg1, u32 arg2, u32 arg3, u32 arg4);

/**
 * @brief Pass the pointer at offset 0x100 to the resident helper.
 * @param receiver Object containing the pointer.
 */
void func_00109F20(void* receiver);

/** Return the signed byte at receiver offset 0xBC. */
s8 func_00109FD0(const void* object);

/**
 * @brief Set the receiver flag when the input value is positive.
 * @param object Receiver whose field at offset 0xB0 is set.
 * @param value Input value to check and return.
 * @return The positive input value, or zero.
 */
s32 func_0010A080(void* object, const s32* value);

/** @brief Apply the resident helper to the supplied object and flag. @param object Helper receiver. @param flag Helper flag. */
void func_001071A0(void* object, s32 flag);

/**
 * @brief Set two receiver flags when the input value is positive.
 * @param object Receiver whose fields at offsets 0xAC and 0x110 are set.
 * @param value Input value to check and return.
 * @return The positive input value, or zero.
 */
s32 func_0010A0B0(void* object, const s32* value);

/** @brief Process the supplied resident object. @param object Input object. */
void func_00109510(void* object);

#ifdef __cplusplus
}
#endif

#endif
