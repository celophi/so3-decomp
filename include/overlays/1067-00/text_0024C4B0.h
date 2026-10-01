#ifndef SO3_OVERLAYS_1067_00_TEXT_0024C4B0_H
#define SO3_OVERLAYS_1067_00_TEXT_0024C4B0_H

#include "types.h"

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

#ifdef __cplusplus
}

#include "overlays/1067-00/text_00207AF0.h"

/**
 * Partial 0x140-byte FieldClass154D20 with vtable D_153570 in boot data and a
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
