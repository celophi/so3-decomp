#ifndef SO3_OVERLAYS_1067_00_TEXT_001E1590_H
#define SO3_OVERLAYS_1067_00_TEXT_001E1590_H

#include "types.h"
#include "overlays/1067-00/text_001DED80.h"

/** Partial receiver with a word at offset 0x30 and a byte at offset 0x34. */
typedef struct FieldWordByte30
{
    u8 unk00[0x30];
    u32 unk30;
    u8 unk34;
} FieldWordByte30;

/** Partial 28-byte record reset by func_001E5690 and func_001E5AD0. */
typedef struct FieldSlotRecord1C
{
    u8 unk00[4];
    u32 unk04;
    u8 unk08_0 : 1;
    u8 unk08_1_7 : 7;
    u8 unk09[3];
    s32 unk0c;
    u32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16_0 : 1;
    u8 unk16_1 : 1;
    u8 unk16_2 : 1;
    u8 unk16_3_7 : 5;
    u8 unk17[5];
} FieldSlotRecord1C;

/** Partial receiver owning a counted array of 28-byte records at offset 0x1C. */
typedef struct FieldSlotRecordOwner1C
{
    u8 unk00[0x14];
    u8 unk14;
    u8 unk15[7];
    FieldSlotRecord1C* unk1c;
    u32 unk20;
    s32 unk24;
    u8 unk28[5];
    u8 unk2d;
    u8 unk2e;
    u8 unk2f;
    u8 unk30[8];
    s32 unk38;
    s32 unk3c;
} FieldSlotRecordOwner1C;

#ifdef __cplusplus
/** Partial record loader with vtable D_150150 and a secondary interface at offset 0x18. */
class FieldClass150150 : public FieldClass150010, public FieldClass1DD400
{
public:
    /**
     * @brief Initialize the record state, allocation flags, and request span.
     */
    FieldClass150150()
    {
        unk2c = 0x80;
        unk24 = 0;
        unk28 = 0x34BC0;
        unk1c = 0;
        unk30_1 = 0;
        unk30_0 = 0;
        func_001E5AD0();
    }

    /**
     * @brief Destroy the record loader.
     */
    virtual ~FieldClass150150();
    /**
     * @brief Advance record requests according to the supplied flag.
     * @param flag Request flag.
     */
    virtual void func_001E0A50(s32 flag);
    /**
     * @brief Finish pending record requests.
     * @return Record request status.
     */
    virtual s32 func_001E07A0();
    /**
     * @brief Advance the record release state.
     * @return Record release status.
     */
    virtual s32 func_001DF640();
    /**
     * @brief Start the request for the current record when its rounded size is nonzero.
     */
    virtual void func_001E5BA0();

    /**
     * @brief Start or advance the request for the current record.
     */
    virtual void func_001E5D20();

    /**
     * @brief Reset every record and clear the active request state.
     */
    virtual void func_001E5AD0();

    /**
     * @brief Release every record in the counted array.
     */
    virtual void func_001E68D0();

    /**
     * @brief Process the secondary interface's record request.
     * @param arg Request argument.
     */
    virtual void func_001DDB30(void* arg);

    FieldClass1530C0* unk1c;
    FieldClass1DD400* unk20;
    s32 unk24;
    s32 unk28;
    u8 unk2c;
    u8 unk2d;
    u8 unk2e;
    u8 unk2f;
    u8 unk30_0 : 1;
    u8 unk30_1 : 1;
    u8 unk30_2_7 : 6;
    u8 unk31[3];
};
/** Keyed record loader with vtable D_1501A0; its complete allocation is 0x48 bytes. */
class FieldClass1501A0 : public FieldClass150150
{
public:
    /**
     * @brief Initialize a loader for the requested key.
     * @param key Request key.
     */
    FieldClass1501A0(s32 key);
    /**
     * @brief Destroy the keyed loader.
     */
    virtual ~FieldClass1501A0();

    /**
     * @brief Queue the loader on the resident object queue without detaching it.
     */
    virtual void func_001DD7B0();
    /**
     * @brief Flush the cache once for this loader.
     * @param arg Unused secondary-interface argument.
     */
    virtual void func_001DDB30(void* arg);

    /**
     * @brief Advance the keyed loader's record requests.
     * @param flag Request flag.
     */
    virtual void func_001E0A50(s32 flag);

    /**
     * @brief Advance the keyed loader's current request.
     */
    virtual void func_001E5D20();

    /**
     * @brief Reset the keyed loader and its request limit.
     */
    virtual void func_001E5AD0();

    s32 unk34;
    s32 unk38;
    s32 unk3c;
    void* unk40;
    u8 unk44;
    u8 unk45[3];
};

struct FieldBufferSlots;

/** Partial FieldClass150070 receiver with MAIN vtable 0x153E30. */
class FieldClass153E30 : public FieldClass150070
{
public:
    /**
     * @brief Destroy the callback receiver.
     */
    virtual ~FieldClass153E30();
    /**
     * @brief Release the callback receiver through its virtual handler.
     */
    virtual void func_001DD7B0();
    /**
     * @brief Report the receiver state.
     * @return Receiver state byte.
     */
    virtual u8 func_00264110();
    /**
     * @brief Handle a supplied object; remaining contract is unresolved.
     * @param value Supplied object.
     * @return Handler result.
     */
    virtual s32 func_00263FD0(void* value);
    /**
     * @brief Handle a supplied object; remaining contract is unresolved.
     * @param value Supplied object.
     * @return Handler result.
     */
    virtual s32 func_00263F50(void* value);
    /**
     * @brief Report the handler state.
     * @return Handler result.
     */
    virtual s32 func_00264080();
    /**
     * @brief Store the pointer at offset 0x20.
     * @param value Pointer to store.
     */
    virtual void func_00263C70(void* value);
    /**
     * @brief Get the pointer at offset 0x20.
     * @return Stored pointer.
     */
    virtual void* func_00261150();
    /**
     * @brief Store the pointer at offset 0x24.
     * @param value Pointer to store.
     */
    virtual void func_00263C80(void* value);
    /**
     * @brief Get the pointer at offset 0x24.
     * @return Stored pointer.
     */
    virtual void* func_00263C90();
    /**
     * @brief Store the byte at offset 0x28.
     * @param value Byte to store.
     */
    virtual void func_00263CA0(s8 value);
    /**
     * @brief Get the signed byte at offset 0x28.
     * @return Stored byte.
     */
    virtual s8 func_00263CB0();
    /**
     * @brief Handle an optional pointer.
     * @param value Supplied pointer.
     * @return Handler pointer.
     */
    virtual void* func_00263CC0(void* value);
    /**
     * @brief Update the callback receiver.
     */
    virtual void func_00263E90();
    /**
     * @brief Report the receiver flag.
     * @return Receiver flag.
     */
    virtual u8 func_00261D20();
    /**
     * @brief Handle a completed request buffer.
     * @param buffer Completed buffer.
     * @return Zero in the base implementation.
     */
    virtual u8 func_001E1820(void* buffer);
};

/** Partial class with a FieldClass1DD400 base at offset 0x14, with vtable D_150120 in main data. */
class FieldClass150120 : public FieldClass150070, public FieldClass1DD400
{
public:
    /**
     * @brief Decode and attach the resource group selected for this loader.
     * @param loader Completed record loader.
     * @return Resource loading result.
     */
    s32 func_001E1830(FieldClass150150* loader);

    /**
     * @brief Attach additional resources from a completed record loader.
     * @param loader Completed record loader.
     * @return Resource attachment result.
     */
    s32 func_001E3580(FieldClass150150* loader);

    /**
     * @brief Attach resource buffers from a completed record loader.
     * @param loader Completed record loader.
     * @return Resource attachment result.
     */
    s32 func_001E2E40(FieldClass150150* loader);

    /**
     * @brief Fill the aligned resource slots from a completed record loader.
     * @param loader Completed record loader.
     * @return Resource loading result.
     */
    s32 func_001E39A0(FieldClass150150* loader);

    /**
     * @brief Attach decoded resources from a completed loader to the buffer slots.
     * @param loader Completed record loader.
     * @return Attachment result.
     */
    s32 func_001E4220(FieldClass150150* loader);

    /**
     * @brief Complete the stored loader and release its temporary request buffer.
     */
    void func_001E4E50();
    /**
     * @brief Decode the supplied loader into a temporary request buffer.
     * @param loader Completed record loader.
     * @return Temporary byte buffer, or null when unavailable.
     */
    u8* func_001E48A0(FieldClass150150* loader);


    /**
     * @brief Clear the request state, parallel arrays, and loader pointers.
     */
    FieldClass150120();

    /**
     * @brief Destroy the object.
     */
    virtual ~FieldClass150120();

    /**
     * @brief Report the fixed value 4 for this class.
     * @return Always 4.
     */
    virtual s32 func_001DF3D0();

    /**
     * @brief Queue the object on the resident object queue without detaching it.
     */
    virtual void func_001DD7B0();

    /**
     * @brief Reuse a matching keyed loader or create and append one when needed.
     */
    virtual void func_001DF360();

    /**
     * @brief FieldClass1DD400 slot 1 override.
     */
    virtual void func_001DDB30(void* arg);

    s32 unk18;
    u8 unk1c;
    u8 unk1d;
    u8 unk1e;
    u8 unk1f;
    u8 unk20;
    u8 unk21[3];
    u32 unk24;
    u8 unk28;
    u8 unk29[3];
    FieldClass153E30* unk2c;
    u32 unk30;
    u8 unk34;
    u8 unk35[3];
    u32 unk38;
    FieldClass150150* unk3c;
    u32 unk40;
    u8* unk44[10];
    u32 unk6c[10];
    FieldBufferSlots* unk94;
    FieldClass1501A0* unk98;
    FieldClass1501A0* unk9c;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
/**
 * @brief Allocate aligned storage, retrying while the owner permits it.
 * @param owner Loader whose owner pointer identifies its context list.
 * @param size Requested size in bytes.
 * @param mode Allocator selection.
 * @return Allocated storage, or null when allocation fails or retries stop.
 */
void* func_001E6B40(FieldClass150070* owner, u32 size, s32 mode);

/**
 * @brief Find or prepare a record slot for the supplied request key.
 * @param object Record loader.
 * @param key Request key.
 * @param mode Record request mode.
 * @return Selected record slot, or null when none is available.
 */
FieldClass1530C0* func_001E69A0(FieldClass150150* object, s32 key, u8 mode);

/**
 * @brief Initialize a keyed request, create its loader, and append it to the context list.
 * @param object Request owner.
 * @param key Request key.
 * @param mode Request mode.
 * @return Created loader, or null when allocation fails.
 */
FieldClass1501A0* func_001E15C0(FieldClass150120* object, s32 key, u8 mode);
#endif

/**
 * @brief Store the word at offset 0x30 and the byte at offset 0x34.
 * @param object Receiver to update.
 * @param word Word to store.
 * @param value Byte to store.
 */
void func_001E5020(FieldWordByte30* object, u32 word, u8 value);

#ifdef __cplusplus
}
#endif

#endif
