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
    /** Button mask that confirms a selection. */
    u16 unk00;
    /** Button mask that cancels or skips. */
    u16 unk02;
    u8 unk04[0x188];
    /** Nonzero for the 16:9 screen layout. */
    u8 widescreen;
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
    struct BootInputStatus9670* input;
    u8 unk10[4];
    /** Boot's message bank. */
    s32 messages;
    u8 unk18[0xC];
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
 * @brief Clear six consecutive words starting at offset 0x20.
 * @param object Record to clear.
 */
void func_001E9650(u32* object);

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

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "overlays/lib/text_0045AD10.h"

/** @brief Detach an object from its owner. @param object Intrusive receiver. */
extern "C" void lib_object_detach_owner(void* object);

class BootClass178660;
class BootClass179150;
class BootClass170F30;
extern "C" s32 lib_container_init(BootClass178660* object, s32 code, float x, float y, s32 first, float z, s32 second);
extern "C" s32 lib_text_init_resource_rectangle(void* object, s32 slot, s32 key, u8 flag, float x, float y, float width, float height);
extern "C" void func_4E32F0(BootClass179150* object);

/** Boot's copy of the virtual intrusive-link root, with vtable D_170E70 in main data. */
class BootClass170E70
{
public:
    /** @brief Destroy the intrusive-link root. */
    virtual ~BootClass170E70()
    {
    }
};

/** Boot's copy of the intrusive list sentinel, with vtable D_170E80 in main data. */
class BootClass170E80 : public BootClass170E70
{
public:
    /** @brief Clear the intrusive links. */
    BootClass170E80() : previous(0), next(0)
    {
    }
    /** @brief Destroy the list sentinel and its virtual root. */
    virtual ~BootClass170E80()
    {
    }
    BootClass170E80* previous;
    BootClass170E80* next;
};

/** Boot's copy of the 0x14-byte owned list object, with vtable D_170E90 in main data. */
class BootClass170E90 : public BootClass170E80
{
public:
    /** @brief Clear the object flags and its owner after initializing the links. */
    BootClass170E90() : is_listed(0), unk0f(0), owner(0)
    {
    }
    /** @brief Detach from the owner, then destroy the intrusive links. */
    virtual ~BootClass170E90()
    {
        lib_object_detach_owner(this);
    }
    /** @brief Report the list kind used when registration requests the default. @return Three in the base implementation. */
    virtual s32 get_default_list_kind();
    /** @brief Delete the object through its virtual destructor; null is ignored. */
    virtual void destroy();
    /** @brief Advance this registered object's state; the owning list's update pass calls it. */
    virtual void update();
    /** @brief Virtual slot 4; the base implementation does nothing. */
    virtual void func_001DD4C0();
    s16 list_kind;
    u8 is_listed;
    u8 unk0f;
    void* owner;
};

/** Boot's copy of the position transform, with vtable D_170D60 in main data. */
class BootClass170D60 : public BootClass170E90
{
public:
    /** @brief Destroy the transform. */
    virtual ~BootClass170D60()
    {
    }
    /**
     * @brief Set the position and a w component of one.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void func_001E0520(float x, float y, float z);
    /** @brief Copy the position. @param value Source vector. */
    virtual void func_001E0510(const BootVector4DDAA0* value);
    /** @brief Copy the position. @param value Source vector. */
    virtual void func_001E0500(const BootVector4DDAA0* value);
    u8 unk14[0xC];
    BootVector4DDAA0 unk20;
};

/** Boot's copy of the position, rotation and scale transform, with vtable D_170D90 in main data. */
class BootClass170D90 : public BootClass170D60
{
public:
    /** @brief Initialize the transform; boot calls the Lib copy of this constructor. */
    BootClass170D90();
    /** @brief Destroy the transform. */
    virtual ~BootClass170D90()
    {
    }
    /**
     * @brief Set the position and a w component of one, and mark the transform dirty.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void func_001E0520(float x, float y, float z);
    /** @brief Copy the position and mark the transform dirty. @param value Source vector. */
    virtual void func_001E0510(const BootVector4DDAA0* value);
    /** @brief Copy the position and mark the transform dirty. @param value Source vector. */
    virtual void func_001E0500(const BootVector4DDAA0* value);
    /**
     * @brief Convert three rotation components into the rotation vector and mark the transform dirty.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void func_001E06F0(float x, float y, float z);
    /** @brief Convert a rotation into the rotation vector and mark the transform dirty. @param value Source rotation. */
    virtual void func_001E06C0(const BootVector4DDAA0* value);
    /** @brief Convert a rotation into the rotation vector and mark the transform dirty. @param value Source rotation. */
    virtual void func_001E0690(const BootVector4DDAA0* value);
    /** @brief Copy the rotation vector and mark the transform dirty. @param value Source vector. */
    virtual void func_001E0670(const BootVector4DDAA0* value);
    /** @brief Copy the rotation vector and mark the transform dirty. @param value Source vector. */
    virtual void func_001E0650(const BootVector4DDAA0* value);
    /**
     * @brief Set all four rotation components and mark the transform dirty.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     * @param w Fourth component.
     */
    virtual void func_001E0630(float x, float y, float z, float w);
    /**
     * @brief Set the scale's xyz components and mark the transform dirty.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void func_001DDED0(float x, float y, float z);
    /** @brief Copy the scale vector and mark the transform dirty. @param value Source vector. */
    virtual void func_001E0750(const BootVector4DDAA0* value);
    /** @brief Copy the scale vector and mark the transform dirty. @param value Source vector. */
    virtual void func_001E0730(const BootVector4DDAA0* value);
    BootVector4DDAA0 unk30;
    BootVector4DDAA0 unk40;
    /** Nonzero when the transformation matrices need rebuilding. */
    u8 transform_dirty;
    u8 unk51;
};

extern "C" u32 D_001B65BC;
extern "C" u8 D_001B65C0;

/** Boot's view of the transform owner with the shared vtable D_178A90 in main data. */
class BootClass178A90 : public BootClass170D90
{
public:
    /** @brief Initialize the owner's state bytes and tracking words. */
    BootClass178A90();
    /** @brief Remove this object's mask from the resident flags, then destroy the transform. */
    virtual ~BootClass178A90()
    {
        u32 mask = ~unk8c;
        u32 previous = D_001B65BC;
        unk8c &= mask;
        D_001B65BC &= mask;
        if (previous != D_001B65BC)
        {
            D_001B65C0 = 1;
        }
    }
    /** @brief Virtual slot 4; the owner's implementation does nothing. */
    virtual void func_001DD4C0();
    /** @brief Detach and queue the owner; boot uses the Lib implementation. */
    virtual void destroy();
    /** @brief Clear the byte at offset 0x60. */
    virtual void func_001E0860();
    /** @brief Default output handler. @param output Opaque output object. @return Zero. */
    virtual s32 func_001E0880(void* output);
    /**
     * @brief Test the supplied value.
     * @param value Value to test.
     * @param mode Additional mode used by derived implementations.
     * @return Whether the value is negative.
     */
    virtual bool func_001E0890(float value, float mode);
    /** @brief Return the shared fallback vector. @return Vector pointer. */
    virtual const BootVector4DDAA0* func_001E08B0();
    /**
     * @brief Default matrix handler; does nothing.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void func_001E08C0(const void* matrix, void* context);
    /** @brief Mark the matrix state ready; boot uses the Lib implementation. */
    virtual void update_transform_matrix();
    /** @brief Read the stored transformation matrix; boot uses the Lib implementation. @return Matrix pointer. */
    virtual const void* get_transform_matrix();
    /** @brief Copy the source transformation state; boot uses the Lib implementation. @param source Transform source. */
    virtual void func_004CFFA0(const BootClass178A90* source);
    /** @brief Produce a transformation receiver. @return Null. */
    virtual BootClass178A90* func_001E08D0();
    /** @brief Default hook; does nothing. */
    virtual void func_001E08E0();
    /** @brief Store the halfword at offset 0x6A. @param value Value to store. */
    void func_001DFE30(u16 value);
    /** @brief Store the halfword at offset 0x6C. @param value Value to store. */
    void func_001DFE40(u16 value);
    u8 unk60;
    u8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    u8 unk65;
    u8 unk66;
    u8 unk67;
    u8 unk68;
    u8 unk69;
    u16 unk6a;
    u16 unk6c;
    u8 unk6e[0x12];
    void* unk80;
    u8 unk84[4];
    u32 unk88;
    u32 unk8c;
};

/** Boot's copy of the transform subclass between D_178A90 and D_174610, with vtable D_170DE0 in main data. */
class BootClass170DE0 : public BootClass178A90
{
public:
    /** @brief Destroy the transform subclass. */
    virtual ~BootClass170DE0()
    {
    }
};

/** Boot's copy of the two-callback DMA interface, with vtable D_170D50 in main data. */
class BootClass170D50
{
public:
    /** @brief Install the interface's vtable. */
    BootClass170D50();
    /** @brief Default DMA notification hook; does nothing. @param value Notification value. */
    virtual void func_001E04E0(u32 value);
    /** @brief Default preparation hook; does nothing. @param value Notification word or packet address. */
    virtual void func_001E04F0(u32 value);
};

/** Boot's view of the transform with callback interface, with the shared vtable D_174610 in main data. */
class BootClass174610 : public BootClass170DE0, public BootClass170D50
{
public:
    /** @brief Initialize the transform and callback interface; boot calls the Lib constructor. */
    BootClass174610();
    /** @brief Destroy the transform receiver. */
    virtual ~BootClass174610()
    {
    }
    /**
     * @brief Run the default transform state hook.
     * @param first First state value.
     * @param second Second state value.
     * @param third Third state value.
     */
    virtual void func_0044B100(u32 first, u32 second, u32 third);
    u8 unk94[0x1A];
    u8 unkae;
    u8 unkaf;
};

/** Boot's view of the 0x14-byte list receiver with the shared vtable D_178A70 in main data. */
class BootClass178A70
{
public:
    BootClass170E80 sentinel;
    u32 node_count;
    /** @brief Initialize the list receiver; boot calls the Lib constructor. */
    BootClass178A70();
    /** @brief Destroy the list receiver. */
    virtual ~BootClass178A70();
    /** @brief Append a node to the end of the list. @param node Node to append. */
    virtual void append(void* node);
    /** @brief Prepend a node to the beginning of the list. @param node Node to prepend. */
    virtual void prepend(void* node);
    /**
     * @brief Link a node after a list position.
     * @param position Insertion position.
     * @param node Node to insert.
     */
    virtual void insert_after(void* position, void* node);
    /** @brief Unlink a node and clear its list links. @param node Node to remove. */
    virtual void unlink(void* node);
};

/** Resident manager list that updates its nodes, with the Lib vtable D_178DD0. */
class BootClass178DD0 : public BootClass178A70
{
public:
    /** @brief Destroy the manager list. */
    virtual ~BootClass178DD0();
    /** @brief Remove a node. @param object Node to remove. */
    virtual void remove_node(void* object);
    /** @brief Update every node. */
    virtual void update_nodes();
    /** @brief Append a node of a kind. @param object Node. @param kind Node kind, or -1 for the node's default. */
    virtual void append_node(void* object, s32 kind);
    /** @brief Prepend a node of a kind. @param object Node. @param kind Node kind, or -1 for the node's default. */
    virtual void prepend_node(void* object, s32 kind);
};

/** Boot's view of the 0xF0-byte container with the Lib vtable D_178660. */
class BootClass178660 : public BootClass178A70, public BootClass174610
{
public:
    /**
     * @brief Initialize the container with its transform.
     * @param x First transform component.
     * @param y Second transform component.
     * @param z Third transform component.
     */
    BootClass178660(float x, float y, float z)
    {
        unk6c = 0x6FF1;
        lib_container_init(this, 9, x, y, 0, z, 0);
    }
    /** @brief Destroy the container. */
    virtual ~BootClass178660();
    LibStorageBlock0C unkd0;
    u8 unkdc[0x14];
};

/** Four words cleared by an out-of-line constructor. */
class BootWordQuad
{
public:
    /** @brief Clear all four words. */
    BootWordQuad();
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
};

/** Partial 0xC0-byte transform with the Lib vtable D_179150. */
class BootClass179150 : public BootClass178A90, public BootClass170D50
{
public:
    /** @brief Initialize the transform's modes and timing. */
    BootClass179150()
    {
        func_4E32F0(this);
        unk94 = 0x80000000;
        unk9c = 0x80000000;
        unk98 = 0;
        unka4 = 30.0f;
        func_001DFE40(0x300);
        unk65 = 1;
        func_001DFE30(0x400);
    }
    /** @brief Destroy the transform. */
    virtual ~BootClass179150();
    u32 unk94;
    u32 unk98;
    u32 unk9c;
    u8 unka0[4];
    float unka4;
    BootWordQuad unka8;
    u8 unkb8[8];
};

/** Partial 0xF0-byte selection cursor with the Lib vtable D_175070. */
class BootClass175070 : public BootClass174610, public ItemCreationClass185050
{
public:
    /** @brief Initialize the cursor transform. */
    BootClass175070()
    {
        unk6c = 0x6FF0;
    }
    /** @brief Destroy the cursor. */
    virtual ~BootClass175070();
};

/** Boot's view of the Lib drawing widget with vtable D_174EF0. */
class BootClass174EF0 : public BootClass170E90
{
public:
    /** @brief Initialize the widget; boot calls the Lib constructor. */
    BootClass174EF0();
    /** @brief Destroy the widget. */
    virtual ~BootClass174EF0();
    /** @brief Set the draw color and mark the widget visible. @param color Packed color. */
    void set_color(u32 color)
    {
        unk98 = color;
        unk3c = 1;
    }
    u8 unk14[0x24];
    u8 unk38;
    u8 unk39[3];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0x58];
    u32 unk98;
    u8 unk9c[0x78];
};

/** Boot's view of the 0x114-byte Lib text widget with vtable D_178750. */
class BootClass178750 : public BootClass174EF0
{
public:
    /**
     * @brief Initialize the text widget with a resource string and rectangle.
     * @param slot Resource slot.
     * @param key Resource key.
     * @param x Origin x.
     * @param y Origin y.
     * @param width Rectangle width.
     * @param height Rectangle height.
     */
    BootClass178750(s32 slot, s32 key, float x, float y, float width, float height)
    {
        unk38 = 11;
        lib_text_init_resource_rectangle(this, slot, key, 1, x, y, width, height);
    }
    /** @brief Destroy the text widget. */
    virtual ~BootClass178750();
};

/** Partial 0xE0-byte screen fade with vtable D_171C00 in main data. */
class BootClass171C00 : public BootClass178A90, public BootClass170D50
{
public:
    /** @brief Initialize the fade for the display. @param display Display dimensions. */
    BootClass171C00(BootDimensionsACD0* display);
    u8 unk94[0x3C];
    float unkd0;
    u8 unkd4[0xC];
};

/** Partial 0x3C-byte list object with vtable D_171BB0 in main data. */
class BootClass171BB0 : public BootClass170E90
{
public:
    /** @brief Initialize the object. @param mode Start mode. */
    BootClass171BB0(s32 mode);
    u8 unk14[0x28];
};

/** Partial 0x2C-byte progress bar with vtable D_171BD0 in main data; driven with a done/total pair. */
class BootProgressBar : public BootClass170E90
{
public:
    /** @brief Initialize the progress bar. */
    BootProgressBar();
    u8 unk14[4];
    BootClass170F30* unk18;
    u8 unk1c[0x10];
};

/** Partial model object with vtable D_170F30 in main data. */
class BootClass170F30 : public BootClass178A90
{
public:
    /** @brief Destroy the model object. */
    virtual ~BootClass170F30();
    /** @brief Virtual slot 0x74. */
    virtual void func_slot74();
    /** @brief Virtual slot 0x78. */
    virtual void func_slot78();
    /** @brief Virtual slot 0x7C. */
    virtual void func_slot7c();
    /** @brief Virtual slot 0x80. */
    virtual void func_slot80();
    /** @brief Virtual slot 0x84. */
    virtual void func_slot84();
    /** @brief Virtual slot 0x88. */
    virtual void func_slot88();
    /** @brief Store the component product of the two input vectors. */
    virtual void func_001DDAA0();
    u8 unk90[0x4D0];
    BootVector4DDAA0 unk560;
    BootVector4DDAA0 unk570;
    BootVector4DDAA0 unk580;
};

/** Partial 0x30-byte image object with vtable D_171C90 in main data, drawn from a decoded FIS image. */
class BootImage : public BootClass170E90
{
public:
    /** @brief Clear the object's model and state bytes. */
    BootImage();
    u8 unk14[4];
    BootClass170F30* unk18;
    u8 unk1c[0x10];
    u8 unk2c;
    u8 unk2d;
    u8 unk2e;
};

/** Partial list object with vtable D_171070 in main data. */
class BootClass171070 : public BootClass170E90
{
public:
    /** @brief Destroy the object. */
    virtual ~BootClass171070();
    /** @brief Store the byte at offset 0x18. @param value Byte to store. */
    virtual void func_001E0250(u8 value);
    u8 unk14[4];
    u8 unk18;
};

/** Message keys in boot's English message bank (resource 38, block 0). */
enum BootMessage
{
    BOOT_MSG_INSTALL_CONFIRM = 0x1E,
    BOOT_MSG_OVERWRITE_CONFIRM = 0x1F,
    BOOT_MSG_NOT_ENOUGH_SPACE = 0x20,
    BOOT_MSG_ERROR = 0x21,
    BOOT_MSG_UNIT_ERROR = 0x22,
    BOOT_MSG_INSTALLING = 0x23,
    BOOT_MSG_PERCENT = 0x24,
    BOOT_MSG_ABORT_CONFIRM = 0x25,
    BOOT_MSG_INSTALL_COMPLETE = 0x26,
    /** First of the eight battle-system tips shown while installing. */
    BOOT_MSG_FIRST_TIP = 0x28
};

/** Resources the installer loads. */
enum BootInstallResource
{
    /** Two images: the screen sprite sheet and its banner. */
    BOOT_RES_SCREEN_IMAGES = 0x2A,
    /** SYSTEM.CNF, icon.sys and the icon written to the BB Unit partition. */
    BOOT_RES_SYSTEM_FILES = 0x2D,
    /** PlayStation BB Navigator icons and title file. */
    BOOT_RES_NAVIGATOR_FILES = 0x2E,
    /** The eight images shown with the battle-system tips. */
    BOOT_RES_TIP_IMAGES = 0x2F,
    BOOT_RES_SOUND = 0x427
};

/**
 * Boot screen that offers to install the game on the PlayStation BB Unit (hard disk), with vtable D_170D30
 * in main data. It asks yes/no, checks the unit and its free space, writes the partition files while
 * showing a progress bar and battle-system tips, then hands over to the next boot stage.
 */
class BootInstaller : public BootClass170E90
{
public:
    /** @brief Allocate the boot buffers and clear the owned objects. */
    BootInstaller();
    /** @brief Release the owned objects and buffers. */
    virtual ~BootInstaller();
    /** @brief Report the list kind used when registration requests the default. @return Four. */
    virtual s32 get_default_list_kind();
    /** @brief Advance the install sequence: load the screen, ask, check the BB Unit, install, then hand over. */
    virtual void update();
    /**
     * @brief Replace the tip image with block @p index of the tip image resource.
     * @param index Tip image to decode.
     */
    void show_tip_image(s32 index);
    /** @brief Create the yes/no choice images and pulse the selected one; release them once installing starts. */
    void update_choice_images();
    /** @brief Create the four screen images once, then place them for the 4:3 or widescreen layout. */
    void place_screen_images();
    u8* screen_image_data;
    u8* sound_data;
    u8* screen_image_buffers[2];
    u8* system_file_data;
    u8* navigator_file_data;
    u8* system_file_buffers[3];
    u8* navigator_file_buffers[3];
    u8* install_buffer;
    BootImage* images[20];
    BootProgressBar* progress_bar;
    BootImage* tip_image;
    u8* tip_image_buffer;
    u8* tip_image_data;
    /** Current step of the install sequence. */
    s32 step;
    /** Step taken when the player answers no or cancels. */
    s32 no_step;
    /** Step taken when the player answers yes. */
    s32 yes_step;
    u8 selection;
    u8 screen_images_loaded;
    u8 sound_started;
    u8 exiting;
    /** Nonzero while the selected choice image grows back to full size. */
    u8 choice_growing;
    u8 unkb9[3];
    u8* unkbc;
    /** Install size used as the progress denominator. */
    s32 install_total;
    /** Next tip to show. */
    s32 tip_index;
    /** Progress percentage at which the next tip is shown. */
    s32 next_tip_percent;
    s32 menu_frames;
    s32 wait_frames;
    /** 0x200-byte buffer the resident install code fills with the icon.sys header. */
    u8* icon_header;
    BootClass178660* container;
    BootClass178750* message_text;
    BootClass178750* progress_text;
    BootClass178750* tip_text;
    BootClass175070* cursor;
};

/** Partial boot globals; the first word is the object whose byte at offset 0x18 the boot object sets. */
typedef struct BootGlobals205E38
{
    BootClass171070* unk00;
    u8 unk04[0x18];
} BootGlobals205E38;

extern "C" BootGlobals205E38 D_205E38;
#endif

#endif
