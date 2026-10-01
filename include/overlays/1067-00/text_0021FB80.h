#ifndef SO3_OVERLAYS_1067_00_TEXT_0021FB80_H
#define SO3_OVERLAYS_1067_00_TEXT_0021FB80_H

#include "types.h"
#include "overlays/1067-00/text_0021DB80.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_00207AF0.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Invoke the receiver's virtual handler at vtable offset 0x20, passing its word at offset 0x74.
 * @param object Receiver of the virtual call.
 */
void func_00227130(void* object);

/**
 * @brief Update a type-0x10 object with a flag.
 * @param object FieldClass152350 receiver.
 * @param flag Value of bit 4 at offset 0x6D2 when called from func_001DD9A0.
 */
void func_00220150(void* object, s32 flag);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * Partial FieldClass151510 with 13 more virtual slots, with vtable D_152430 in
 * boot data. Its constructor (func_00229020) sets type bit 0x2 in unk78.
 * Overrides of earlier slots other than slot 15 are not declared yet.
 */
class FieldClass152430 : public FieldClass151510
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass152430();

    /**
     * @brief Optionally copy a vector to offset 0x20, then update the vectors at offsets 0x170-0x190.
     * @param value Vector to copy, or null to keep the current one.
     */
    virtual void func_00205710(const FieldVec4A* value);

    /** @brief Virtual handler slot 19. */
    virtual void func_00203990();

    /** @brief Virtual handler slot 20. */
    virtual void func_00227840();

    /** @brief Copy the vector at offset 0x20 to offset 0x170 and set offset 0x190 to (0, 0, 0, 1). */
    virtual void func_001DE3D0();

    /** @brief Virtual handler slot 22. */
    virtual void func_002039A0();

    /** @brief Virtual handler slot 23. */
    virtual void func_00227CC0();

    /** @brief Default handler that performs no work. */
    virtual void func_001DE3C0();

    /** @brief Virtual handler slot 25. */
    virtual void func_001FED00();

    /** @brief Virtual handler slot 26. */
    virtual void func_002039B0();

    /** @brief Virtual handler slot 27. */
    virtual void func_00228DD0();

    /**
     * @brief Virtual handler slot 28.
     * @param arg Argument whose meaning is not yet known.
     */
    virtual void func_00226C10(void* arg);

    /** @brief Virtual handler slot 29. */
    virtual void func_002039C0();

    /** @brief Virtual handler slot 30. */
    virtual void func_00203A30();

    /** @brief Virtual handler slot 31. */
    virtual void func_002270D0();

};

/**
 * Partial FieldClass152430 with four more virtual slots, with vtable D_150EB0
 * in boot data. Its constructor (func_002036F0, in text_00202240) sets type
 * bit 0x4 in unk78. It is declared here because it derives from
 * FieldClass152430.
 */
class FieldClass150EB0 : public FieldClass152430
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150EB0();

    /**
     * @brief Virtual handler slot 32.
     * @param arg0 First argument whose meaning is not yet known.
     * @param arg1 Second argument whose meaning is not yet known.
     * @param value Float argument whose meaning is not yet known.
     */
    virtual void func_00202CF0(void* arg0, void* arg1, float value);

    /** @brief Virtual handler slot 33. */
    virtual void func_00203500();

    /**
     * @brief Virtual handler slot 34.
     * @param value Float argument whose meaning is not yet known.
     */
    virtual void func_00202580(float value);

    /**
     * @brief Virtual handler slot 35.
     * @param arg Argument whose meaning is not yet known.
     */
    virtual void func_00200110(void* arg);

    u8 unk210[0x180];
    FieldVec4B unk390;
};

/**
 * Partial FieldClass150EB0 with one more virtual slot, with vtable D_152F00 in
 * boot data. Its constructor (func_00238940, in text_0022DC70) sets type bit
 * 0x8 in unk78. It is declared here because it derives from FieldClass152430.
 */
class FieldClass152F00 : public FieldClass150EB0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass152F00();

    /**
     * @brief Run FieldClass152430's handler, then copy the vector to offset 0x530.
     * @param value Vector to copy.
     */
    virtual void func_00205710(const FieldVec4A* value);

    /** @brief Virtual handler slot 36. */
    virtual void func_002378E0();

    u8 unk3a0[0x190];
    FieldVec4B unk530;
};

/**
 * Partial FieldClass152F00 with vtable D_152350 in boot data. Its constructor
 * (func_00224A00) sets type bit 0x10 in unk78. New virtual slots are not
 * declared yet.
 */
class FieldClass152350 : public FieldClass152F00
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass152350();

    u8 unk540[0x192];
    u8 unk6d2_0_3 : 4;
    u8 unk6d2_4 : 1;
    u8 unk6d2_5_7 : 3;
};
#endif

#endif
