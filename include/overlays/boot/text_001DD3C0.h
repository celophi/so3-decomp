#ifndef SO3_OVERLAYS_BOOT_TEXT_001DD3C0_H
#define SO3_OVERLAYS_BOOT_TEXT_001DD3C0_H

#include "types.h"

typedef struct Record001E94E0 Record001E94E0;

#define BOOT_TRANSFER_NAME_CAPACITY 64
#define BOOT_TRANSFER_FLAG_COUNT 300
#define BOOT_TRANSFER_FLAG_BYTES ((BOOT_TRANSFER_FLAG_COUNT + 7) / 8)

/** @brief Four aligned floating-point vector components. */
typedef struct BootVector4DDAA0
{
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) BootVector4DDAA0;

/** @brief Matrix storage containing four aligned four-component vectors. */
typedef struct BootMatrix92D0
{
    BootVector4DDAA0 vectors[4];
} BootMatrix92D0;

/** @brief Partial layout of the vector product's two inputs and result. */
typedef struct BootVectorStateDDAA0
{
    u8 unk00[0x560];
    BootVector4DDAA0 unk560;
    BootVector4DDAA0 unk570;
    BootVector4DDAA0 unk580;
} BootVectorStateDDAA0;

/** @brief Partial layout of the two queried mode words. */
typedef struct BootModePair0910
{
    u8 unk00[0x48];
    s32 unk48;
    u8 unk4C[0xFC];
    s32 unk148;
} BootModePair0910;

/** @brief Partial mode owner with a byte gating access to its mode words. */
typedef struct BootModeOwner0910
{
    u8 unk00[0x14];
    BootModePair0910* unk14;
    u8 unk18[8];
    u8 unk20;
} BootModeOwner0910;

enum BootModeFlags0910
{
    BOOT_MODE_0910_FLAG_0 = 0x1,
    BOOT_MODE_0910_FLAG_1 = 0x2
};

/** @brief Stored filename, buffer address, extent, and an unknown word. */
typedef struct BootTransferBuffer0AF0
{
    char* unk00;
    void* unk04;
    u32 unk08;
    u32 unk0C;
} BootTransferBuffer0AF0;

/** @brief Request record retained by the mode owner's selected entry. */
typedef struct BootTransferRequest0AF0
{
    char* unk00;
    s32 unk04;
    u32 unk08;
    BootTransferBuffer0AF0* unk0C;
} BootTransferRequest0AF0;

/** @brief Partial resource storage for transferred flag bits and header values. */
typedef struct BootResourceBits0970
{
    u8 unk00[8];
    u8* unk08;
    u8 unk0C[8];
    u32 unk14;
    u8 unk18[8];
} BootResourceBits0970;

/** @brief Partial selected resource containing the transferred flag storage. */
typedef struct BootResource0970
{
    u8 unk00[0x18C];
    u8 unk18C;
    u8 unk18D[0x1B];
    BootResourceBits0970 unk1A8;
} BootResource0970;

/** @brief Partial state layout for the two selectable reset modes. */
typedef struct BootState1E1A40
{
    u8 unk00[0x14];
    BootModeOwner0910* unk14;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    u8 unk1E;
    u8 unk1F;
    u32 unk20;
    u8 unk24[4];
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    char unk2E[BOOT_TRANSFER_NAME_CAPACITY];
    u8 unk6E[0xCC6];
    u8 unkD34;
    u8 unkD35[2];
    u8 unkD37[2];
    u8 unkD39[0x87];
    s16 unkDC0;
    u8 unkDC2[2];
    void* unkDC4;
    void* unkDC8;
    s16 unkDCC;
    s16 unkDCE;
    s32 unkDD0;
    BootTransferBuffer0AF0 unkDD4;
    BootTransferRequest0AF0 unkDE4;
    BootResource0970* unkDF4;
    u8 unkDF8;
    u8 unkDF9;
    u8 unkDFA[2];
    s32 unkDFC[2];
    s32 unkE04[2];
} BootState1E1A40;

/** @brief Partial receiver containing its matrix, cleanup gate, and attachment. */
typedef struct BootCleanupState8D80
{
    u8 unk00[0x50];
    u8 unk50;
    u8 unk51[0x3F];
    BootMatrix92D0 unk90;
    u8 unkD0[0x4D0];
    u8 unk5A0;
    u8 unk5A1[0x93];
    void* unk634;
} BootCleanupState8D80;

/** @brief Partial projection object containing its stored floating-point parameters. */
typedef struct BootProjectionACD0
{
    u8 unk00[0x250];
    float unk250;
    u8 unk254[8];
    float unk25C;
    u8 unk260[0x18];
    float unk278;
} BootProjectionACD0;

/** @brief Partial object containing the two signed dimensions used by projection. */
typedef struct BootDimensionsACD0
{
    u8 unk00[0x3C6C];
    s16 unk3C6C;
    s16 unk3C6E;
} BootDimensionsACD0;

/** @brief Partial owner containing the projection pointers and mode state. */
typedef struct BootPointerOwnerACC0
{
    u8 unk00[4];
    BootDimensionsACD0* unk04;
    BootProjectionACD0* unk08;
    u8 unk0C[0x18];
    BootState1E1A40* unk24;
} BootPointerOwnerACC0;

/** @brief Partial resident receiver of the copied pointer. */
typedef struct BootPointerContextACC0
{
    u8 unk00[0x90];
    void* unk90;
} BootPointerContextACC0;

/** @brief Opaque resident input root queried by slot. */
typedef struct BootInputRoot9670 BootInputRoot9670;

/** @brief Partial input receiver containing samples, retained modes, and flags. */
typedef struct BootInputStatus9670
{
    u8 unk00[0x14];
    u8 unk14;
    u8 unk15;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u8 unk1E[2];
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2C;
    s32 unk30;
    s32 unk34;
} BootInputStatus9670;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Refresh input samples and update retained mode values when enabled.
 * @param object Receiver containing the input samples and mode-update gate.
 */
void func_001E9670(BootInputStatus9670* object);

extern BootInputRoot9670* D_001B65F0;
u16 func_11E010(BootInputRoot9670* root, s32 slot);
u16 func_11DFF0(BootInputRoot9670* root, s32 slot);
u16 func_11E000(BootInputRoot9670* root, s32 slot);
u16 func_11DFB0(BootInputRoot9670* root, s32 slot);
void func_11DF90(BootInputRoot9670* root, s32 slot);

/**
 * @brief Copy the owner's stored pointer into the resident context.
 * @param object Owner containing the pointer to bind.
 */
void func_001EACC0(BootPointerOwnerACC0* object);

extern BootPointerContextACC0* D_001B6628;

/**
 * @brief Update projection parameters using the resource mode and stored dimensions.
 * @param object Owner containing the projection object to update.
 */
void func_001EACD0(BootPointerOwnerACC0* object);

extern BootPointerOwnerACC0 D_205E10;
extern BootProjectionACD0* D_001B6654;

/**
 * @brief Detach the gated attached object, then perform the receiver cleanup.
 * @param object Receiver containing the cleanup gate and attached object.
 */
void func_001E8D80(BootCleanupState8D80* object);

void func_4D5C90(void* object);
void func_448250(BootCleanupState8D80* object);

/**
 * @brief Negate the second stored matrix vector, then update the receiver.
 * @param object Receiver containing the matrix and update flag.
 * @param first First opaque argument forwarded to the shared update routine.
 * @param second Second opaque argument forwarded to the shared update routine.
 */
void func_001E92D0(BootCleanupState8D80* object, void* first, void* second);

void func_4A5E60(BootCleanupState8D80* object, void* first, void* second);

/**
 * @brief Multiply the two stored vectors component by component.
 * @param object State containing both inputs and the result vector.
 */
void func_001DDAA0(BootVectorStateDDAA0* object);

/**
 * @brief Query which of the owner's two mode words equal 2.
 * @param object State containing the mode owner.
 * @return Bit 0 for unk48 and bit 1 for unk148; zero when the owner's gate is clear.
 */
u16 func_001E0910(BootState1E1A40* object);

/**
 * @brief Advance the stored two-phase request and update its completion state.
 * @param object State containing the mode owner and request records.
 * @return Narrowed request status, or -1 when the phase is unsupported.
 */
s16 func_001E0AF0(BootState1E1A40* object);

/**
 * @brief Initialize the buffer and request records for a selected transfer mode.
 * @param object State receiving the destination and prepared request records.
 * @param mode Transfer mode 0 or 1.
 * @param destination Nonnull destination for the transfer.
 * @return 1 when prepared, or 0 for invalid arguments or allocation failure.
 */
s32 func_001E0C30(BootState1E1A40* object, u16 mode, void* destination);

/**
 * @brief Create the mode owner and prepare its shared transfer buffer.
 * @param object State receiving the owner, selected resource, and request records.
 * @return 1 when initialized, or 0 when an owner, resource, or buffer is unavailable.
 */
s32 func_001E1AD0(BootState1E1A40* object);

void* func_100AC0(u32 size, s32 flags);
BootModeOwner0910* func_432900(BootModeOwner0910* owner);
s32 func_432720(BootModeOwner0910* owner, void* queue);
void func_432660(BootModeOwner0910* owner, s32 mode, u32 enabled, u32 flags);
extern void* D_001B6614;
void* func_10D8E0(void);
void* func_101290(void* object);
void* func_101440(void* table, s32 selector);

void* func_100B00(u32 size, s32 flags);
void* func_13A678(void* destination, s32 value, u32 size);
char* func_13C948(char* destination, const char* source);
extern const char D_205100[];
extern const char D_205980[];

/**
 * @brief Apply transferred flags and header values, copy the payload, and release its buffer.
 * @param object State containing the buffer, selected resource, and destination.
 */
void func_001E0970(BootState1E1A40* object);
void* func_13A4C0(void* destination, const void* source, u32 size);
void func_100BE0(void* allocation);
s32 func_432310(BootModeOwner0910* owner, u32 mode, BootTransferRequest0AF0* request);
s32 func_432270(BootModeOwner0910* owner, s32 mode, s32* result);

/**
 * @brief Reset the shared state and the fields selected by mode 0 or 1.
 * @param object State receiving the reset.
 * @param mode Mode to store and reset; other values reset only shared fields.
 */
void func_001E1A40(BootState1E1A40* object, s16 mode);

/**
 * @brief Select an event's byte status and update the current mode's stored status.
 * @param object State containing the selected mode and its counters and status.
 * @param event Event code to classify.
 * @param result Byte receiving the selected status, initially cleared to zero.
 */
void func_001E17C0(BootState1E1A40* object, u16 event, u8* result);

/**
 * @brief Apply an event to the selected mode and update its reset and completion flags.
 * @param object State receiving the event and any selected-mode reset.
 * @param enabled Process the event when this byte equals 1.
 * @param event Event code or direct byte status to store.
 * @param kind Classify the event with 1, or store its byte status with 2.
 */
void func_001E1500(BootState1E1A40* object, u8 enabled, u16 event, u16 kind);

/**
 * @brief Store mode 1 or 2 and reset the state for selector 0.
 * @param object State receiving the mode and reset.
 * @param mode Mode to store; values other than 1 or 2 have no effect.
 */
void func_001E0DE0(BootState1E1A40* object, u8 mode);

/**
 * @brief Query a mode's byte and reset selector 0 when the reset flag is set.
 * @param object State containing the mode bytes and reset flag.
 * @param mode Mode 0 or 1 to query; other values return zero without a reset.
 * @param kind Select guarded values with 1, or the direct mode byte otherwise.
 * @return The selected byte before any reset.
 */
u16 func_001E1410(BootState1E1A40* object, u16 mode, u16 kind);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001DD4C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E04E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E04F0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_001E05D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E05E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E0870(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E0880(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E08C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E08D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E08E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E08F0(void* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_001E0900(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_001E3FE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9400(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9410(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9440(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9450(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9490(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9640(void* object);

/**
 * @brief Return the stored signed request result.
 * @param object Object containing the value.
 * @return The stored value.
 */
s32 func_001E0AD0(BootState1E1A40* object);

/**
 * @brief Return the signed 16-bit value at offset 0xDCE.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001E0AE0(BootState1E1A40* object);

/**
 * @brief Return the 8-bit value at offset 0x794.
 * @param object Object containing the value.
 * @return The stored value.
 */
u8 func_001E9480(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_001DD400(void* object);

/**
 * @brief Store the value at offset 0x6A.
 * @param object Object receiving the value.
 * @param value Value to store.
 */
void func_001DFE30(void* object, u16 value);

/**
 * @brief Store the value at offset 0x6C.
 * @param object Object receiving the value.
 * @param value Value to store.
 */
void func_001DFE40(void* object, u16 value);

/**
 * @brief Store the value at offset 0x18.
 * @param object Object receiving the value.
 * @param value Value to store.
 */
void func_001E0250(void* object, u8 value);

/**
 * @brief Clear the byte at offset 0x60.
 * @param object Object containing the byte.
 */
void func_001E0860(void* object);

/**
 * @brief Return the supplied value.
 * @param object Receiver or first argument; unused.
 * @param value Value to return.
 * @return The supplied value.
 */
s32 func_001E9420(void* object, s32 value);

/**
 * @brief Return the supplied value.
 * @param object Receiver or first argument; unused.
 * @param value Value to return.
 * @return The supplied value.
 */
s32 func_001E9430(void* object, s32 value);

/**
 * @brief Return the address of the field at offset 0x79C.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E9470(void* object);

/**
 * @brief Return the address of the field at offset 0x570.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E94D0(void* object);

/**
 * @brief Return the address of the field at offset 0x90.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E9550(void* object);

/**
 * @brief Return the address of the field at offset 0x1D0.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E9560(void* object);

/**
 * @brief Return the address of the field at offset 0x1E0.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E9570(void* object);

/**
 * @brief Return the address of the field at offset 0x1F0.
 * @param object Object containing the field.
 * @return Pointer to the field.
 */
u8* func_001E9580(void* object);

/**
 * @brief Return zero as a float.
 * @param object Receiver or first argument; unused.
 * @return Always 0.0f.
 */
float func_001E9380(void* object);

/**
 * @brief Check whether the word at offset 0x704 is nonzero.
 * @param object Object containing the word.
 * @return One if nonzero, otherwise zero.
 */
s32 func_001E9460(void* object);

/**
 * @brief Mark a record active and set its float values.
 * @param object Record to update.
 * @param first First float value.
 * @param second Second float value.
 * @param third Third float value.
 */
void func_001DD620(u8* object, float first, float second, float third);

/**
 * @brief Mark a record active and set three float values.
 * @param object Record to update.
 * @param first First float value.
 * @param second Second float value.
 * @param third Third float value.
 */
void func_001DDED0(u8* object, float first, float second, float third);

/**
 * @brief Set three float values and a final value of 1.0f.
 * @param object Record to update.
 * @param first First float value.
 * @param second Second float value.
 * @param third Third float value.
 */
void func_001E0520(u8* object, float first, float second, float third);

/**
 * @brief Mark a record active and set four float values.
 * @param object Record to update.
 * @param first First float value.
 * @param second Second float value.
 * @param third Third float value.
 * @param fourth Fourth float value.
 */
void func_001E0630(u8* object, float first, float second, float third, float fourth);

/**
 * @brief Clear the first four words of a record.
 * @param object Record to clear.
 * @return The record pointer.
 */
void* func_001DFE50(u32* object);

/**
 * @brief Initialize a record pointer to the fixed table.
 * @param object Pointer field to initialize.
 * @return The record pointer.
 */
void* func_001DFE70(void** object);

/**
 * @brief Check whether a float is negative.
 * @param object Receiver or first argument; unused.
 * @param value Float to test.
 * @return One if negative, otherwise zero.
 */
s32 func_001E0890(void* object, float value);

/**
 * @brief Return the fixed table address.
 * @param object Receiver or first argument; unused.
 * @return Address of the fixed table.
 */
void* func_001E08B0(void* object);

/**
 * @brief Clear six consecutive words starting at offset 0x20.
 * @param object Record to clear.
 */
void func_001E9650(u32* object);

/**
 * @brief Copy 16 bytes to offset 0x20.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0500(u8* object, const unsigned __int128* value);

/**
 * @brief Copy 16 bytes to offset 0x20.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0510(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x20.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E05F0(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x20.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0610(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x30.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0650(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x30.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0670(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x40.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0730(u8* object, const unsigned __int128* value);

/**
 * @brief Mark a record active and copy 16 bytes to offset 0x40.
 * @param object Destination record.
 * @param value 16-byte value to copy.
 */
void func_001E0750(u8* object, const unsigned __int128* value);

/**
 * @brief Forward to the owner 0x640 bytes before the embedded object.
 * @param object Pointer to the embedded object.
 */
void func_001E9590(u8* object);

/**
 * @brief Forward to the owner 0x640 bytes before the embedded object.
 * @param object Pointer to the embedded object.
 */
void func_001E95A0(u8* object);

/**
 * @brief Set the value byte and active flag.
 * @param object Record to update.
 * @param value Byte to store.
 */
void func_001E94E0(Record001E94E0* object, u8 value);

/**
 * @brief Mark a record active and copy a four-float value into it.
 * @param object Record to update.
 * @param first First float value.
 * @param second Second float value.
 * @param third Third float value.
 */
void func_001E06F0(u8* object, float first, float second, float third);

#ifdef __cplusplus
}
#endif

#endif
