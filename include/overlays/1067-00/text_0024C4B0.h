#ifndef SO3_OVERLAYS_1067_00_TEXT_0024C4B0_H
#define SO3_OVERLAYS_1067_00_TEXT_0024C4B0_H

#include "types.h"

typedef struct FieldStatus331 FieldStatus331;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Append an object to the ring buffer at offset 0x220 unless it is full.
 * @param queue Receiver owning the ring buffer.
 * @param object Object to append.
 * @return 1 when the object was appended, 0 when the buffer is full.
 */
s32 func_0024CE10(void* queue, void* object);

typedef struct FieldObject153590 FieldObject153590;

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 8.
 */
s32 func_0024CC30(FieldObject153590* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0024C540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0024D000(void* object);

/**
 * @brief Save the current status byte, set it to 3, clear flag bit 0, and store a value.
 * @param object Receiver containing the status bytes.
 * @param value Value to store at offset 0x333.
 */
void func_0024D440(FieldStatus331* object, u8 value);

#ifdef __cplusplus
}

#include "overlays/1067-00/text_00207AF0.h"

/**
 * Partial 0x140-byte FieldClass154D20 with vtable D_153570 in main data and a
 * FieldClass1515D0 member at offset 0x80. Its constructor is func_0024CB40.
 * Overrides other than slot 3 are not declared yet.
 */
class FieldClass153570 : public FieldClass154D20
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass153570();

    /**
     * @brief Return the FieldClass1515D0 member at offset 0x80.
     * @return The member.
     */
    virtual FieldClass1515D0* func_001DDCD0();

    u8 unk10[0x70];
    FieldClass1515D0 unk80;
    u8 unk90[0xB0];
};
#endif

#endif
