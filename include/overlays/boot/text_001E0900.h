#ifndef SO3_OVERLAYS_BOOT_TEXT_001E0900_H
#define SO3_OVERLAYS_BOOT_TEXT_001E0900_H

#include "overlays/boot/text_001DD3C0.h"

#define BOOT_TRANSFER_NAME_CAPACITY 64
#define BOOT_TRANSFER_BUFFER_SIZE 1158050
#define BOOT_TRANSFER_FLAG_COUNT 300
#define BOOT_TRANSFER_FLAG_BYTES ((BOOT_TRANSFER_FLAG_COUNT + 7) / 8)

/** @brief Partial layout of the two queried mode words. */
struct BootModePair0910
{
    u8 unk00[0x48];
    s32 unk48;
    u8 unk4C[0xFC];
    s32 unk148;
};

/** Partial 0x58-byte Lib memory card object that runs the two transfer modes; boot calls the Lib constructor. */
class BootModeOwner0910 : public BootClass170E90
{
public:
    /** @brief Initialize the memory card object. */
    BootModeOwner0910();
    BootModePair0910* unk14;
    u8 unk18[8];
    u8 unk20;
    u8 unk21[0x37];
};

enum BootModeFlags0910
{
    BOOT_MODE_0910_FLAG_0 = 0x1,
    BOOT_MODE_0910_FLAG_1 = 0x2
};

/** @brief Stored filename, buffer address, extent, and an unknown word. */
struct BootTransferBuffer0AF0
{
    char* unk00;
    void* unk04;
    u32 unk08;
    u32 unk0C;
};

/** @brief Request record retained by the mode owner's selected entry. */
struct BootTransferRequest0AF0
{
    char* unk00;
    s32 unk04;
    u32 unk08;
    BootTransferBuffer0AF0* unk0C;
};

/**
 * Boot object that reads and writes the BASLUS-20488BTLCOL memory card file through a Lib memory card
 * object, with vtable D_170EB0 in main data. Mode 0 and mode 1 select the two card slots.
 */
class BootClass170EB0 : public BootClass170E90
{
public:
    /** @brief Clear the transfer state, both modes, and the filename. */
    BootClass170EB0();

    /** @brief Destroy the object. */
    virtual ~BootClass170EB0()
    {
    }

    /** @brief Report the list kind used when registration requests the default. @return Two. */
    virtual s32 get_default_list_kind();

    /** @brief Release the transfer buffer and the memory card object, then queue this object for deletion. */
    virtual void destroy();

    /** @brief Advance the memory card state for the current mode. */
    virtual void update();

    /**
     * @brief Query which of the owner's two mode words equal 2.
     * @return Bit 0 for unk48 and bit 1 for unk148; zero when the owner's gate is clear.
     */
    u16 func_001E0910();

    /** @brief Apply transferred flags and header values, copy the payload, and release its buffer. */
    void func_001E0970();

    /** @brief Return the stored signed request result. @return The stored value. */
    s32 func_001E0AD0();

    /** @brief Return the signed 16-bit value at offset 0xDCE. @return The stored value. */
    s16 func_001E0AE0();

    /**
     * @brief Advance the stored two-phase request and update its completion state.
     * @return Narrowed request status, or -1 when the phase is unsupported.
     */
    s16 func_001E0AF0();

    /**
     * @brief Initialize the buffer and request records for a selected transfer mode.
     * @param mode Transfer mode 0 or 1.
     * @param destination Nonnull destination for the transfer.
     * @return 1 when prepared, or 0 for invalid arguments or allocation failure.
     */
    s32 func_001E0C30(u16 mode, void* destination);

    /**
     * @brief Store mode 1 or 2 and reset the state for selector 0.
     * @param mode Mode to store; values other than 1 or 2 have no effect.
     */
    void func_001E0DE0(u8 mode);

    /**
     * @brief Query a mode's byte and reset selector 0 when the reset flag is set.
     * @param mode Mode 0 or 1 to query; other values return zero without a reset.
     * @param kind Select guarded values with 1, or the direct mode byte otherwise.
     * @return The selected byte before any reset.
     */
    u16 func_001E1410(u16 mode, u16 kind);

    /**
     * @brief Apply an event to the selected mode and update its reset and completion flags.
     * @param enabled Process the event when this byte equals 1.
     * @param event Event code or direct byte status to store.
     * @param kind Classify the event with 1, or store its byte status with 2.
     */
    void func_001E1500(u8 enabled, u16 event, u16 kind);

    /**
     * @brief Select an event's byte status and update the current mode's stored status.
     * @param event Event code to classify.
     * @param result Byte receiving the selected status, initially cleared to zero.
     */
    void func_001E17C0(u16 event, u8* result);

    /**
     * @brief Reset the shared state and the fields selected by mode 0 or 1.
     * @param mode Mode to store and reset; other values reset only shared fields.
     */
    void func_001E1A40(s16 mode);

    /**
     * @brief Create the memory card object and prepare the shared transfer buffer.
     * @return 1 when initialized, or 0 when an owner, resource, or buffer is unavailable.
     */
    s32 func_001E1AD0();

    BootModeOwner0910* unk14;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    u8 unk1E;
    u8 unk1F;
    u32 unk20;
    u32 unk24;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    char unk2E[BOOT_TRANSFER_NAME_CAPACITY];
    u8 unk6E[0xCC0];
    u8* unkD30;
    u8 unkD34;
    u8 unkD35[2];
    u8 unkD37[2];
    u8 unkD39[0x80];
    u8* unkDBC;
    s16 unkDC0;
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
    s32 unkDFC[2];
    s32 unkE04[2];
};

/** Partial 0x3C-byte boot object with vtable D_170ED0 in main data. */
class BootClass170ED0 : public BootClass170E90
{
public:
    /** @brief Clear the object's state. */
    BootClass170ED0();

    /** @brief Destroy the object. */
    virtual ~BootClass170ED0();

    /** @brief Advance the object's state. */
    virtual void update();

    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    u8 unk24[8];
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
};

/** Interface with one pure virtual function, with vtable D_170F20 in main data. */
class BootClass170F20
{
public:
    /** @brief Return the interface's value. @return Value. */
    virtual float func_001E9380() = 0;
};

/** Implementation of BootClass170F20 that returns zero, with vtable D_170F10 in main data. */
class BootClass170F10 : public BootClass170F20
{
public:
    /** @brief Return zero. @return Always 0.0f. */
    virtual float func_001E9380()
    {
        return 0.0f;
    }
};

/** Partial boot menu object with vtable D_170EF0 in main data. */
class BootClass170EF0 : public BootClass170E90
{
public:
    /** @brief Load the menu's resources and clear its owned objects. */
    BootClass170EF0();

    /** @brief Release the menu's buffers and owned objects. */
    virtual ~BootClass170EF0();

    /** @brief Report the list kind used when registration requests the default. @return Four. */
    virtual s32 get_default_list_kind();

    /** @brief Advance the menu. */
    virtual void update();

    /** @brief Load the selected option's current value from the settings. */
    void func_001E4B50();

    /** @brief Apply the selected option's value to the settings and the hardware. */
    void func_001E4CE0();

    /**
     * @brief Select the message describing the selected option's value.
     * @return Message key, or zero for an unknown option.
     */
    s32 func_001E5090();

    u8* unk14;
    u8* unk18[5];
    u8* unk2C;
    u8* unk30[8];
    s32 unk50;
    u8 unk54[0x14];
    u8 unk68;
    u8 unk69;
    u8 unk6A;
    u8 unk6B;
    u8 unk6C;
    u8 unk6D;
    u8 unk6E;
    u8 unk6F[0xD];
    s32 unk7C;
    u8 unk80[4];
    BootClass170E90* unk84[21];
    BootClass170E90* unkD8;
    BootClass170E90* unkDC;
    BootClass170E90* unkE0[10];
    BootClass170E90* unk108[6];
    BootClass170E90* unk120[6];
    BootClass170F10 unk138;
    BootClass178660* unk13C;
    BootClass170E90* unk140;
    BootClass170E90* unk144;
};

/** Partial 0x38-byte input object with vtable D_171030 in main data; reads the pad and the memory card state. */
class BootClass171030 : public BootClass170E90
{
public:
    /** @brief Clear the retained values and enable the memory card query. */
    BootClass171030();

    /** @brief Destroy the object. */
    virtual ~BootClass171030()
    {
    }

    /** @brief Refresh input samples and update retained mode values when enabled. */
    virtual void update();

    /** @brief Virtual slot 5. @return Always 0. */
    virtual s32 func_001E9640();

    /** @brief Clear the retained memory card values and flags. */
    void func_001E9650();

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
};

/** Partial 0x58-byte resident object whose vtable pointer follows its data; boot calls the resident constructor. */
class BootResident113E40
{
public:
    /** @brief Initialize the object. */
    BootResident113E40();
    u8 unk00[0x2C];
    s32 unk2C;
    u8 unk30[0x24];

    /** @brief Destroy the object. */
    virtual ~BootResident113E40();
};

/** Partial 0x38-byte boot object with vtable D_171050 in main data. */
class BootClass171050 : public BootClass170E90
{
public:
    /** @brief Create the object's resources. */
    BootClass171050();

    /** @brief Release the owned objects. */
    virtual ~BootClass171050();

    /** @brief Advance the object's state. */
    virtual void update();

    u8 unk14[0x10];
    BootResident113E40* unk24;
    BootClass170E90* unk28;
    BootClass170E90* unk2C;
    BootClass178660* unk30;
    BootClass170E90* unk34;
};

/** Partial 0x20-byte boot object with vtable D_171090 in main data. */
class BootClass171090 : public BootClass170E90
{
public:
    /** @brief Destroy the object. */
    virtual ~BootClass171090();

    /** @brief Decode the next of the program's three resource blocks, then destroy this object after the last. */
    virtual void update();

    class BootClass1710B0* program;
    /** Loaded resource whose blocks are decoded. */
    u8* data;
    /** Next block to decode. */
    s32 block;
};

/** Resident program object base, with vtable D_14F9F0 in main data; the constructor registers the object. */
class BootResidentProgram
{
public:
    /** @brief Register the object as the running program. */
    BootResidentProgram();

    /** @brief Run the program; the base implementation is resident. */
    virtual void run();
};

/** Opaque resident input root queried by slot. */
struct BootInputRoot9670;

/** Boot program object D_205E10, with vtable D_1710B0 in main data. */
class BootClass1710B0 : public BootResidentProgram
{
public:
    /** @brief Run the boot program. */
    virtual void run();

    /** @brief Release the program's objects, resources, and buffers. */
    virtual ~BootClass1710B0();

    /** @brief Copy the projection object into the resident context. */
    void func_001EACC0();

    /** @brief Update projection parameters using the resource mode and stored dimensions. */
    void func_001EACD0();

    BootDimensionsACD0* unk04;
    BootProjectionACD0* unk08;
    BootClass171030* input;
    u8* unk10;
    /** Boot's message bank. */
    s32 messages;
    u8* unk18;
    s32 unk1C;
    u8* unk20;
    BootClass170EB0* unk24;
    BootClass170E90* unk28;
    u8 unk2C[0x14];
    u8* unk40;
};

extern "C" {
extern BootClass1710B0 D_205E10;
extern BootInputRoot9670* D_001B65F0;
u16 func_11E010(BootInputRoot9670* root, s32 slot);
u16 func_11DFF0(BootInputRoot9670* root, s32 slot);
u16 func_11E000(BootInputRoot9670* root, s32 slot);
u16 func_11DFB0(BootInputRoot9670* root, s32 slot);
void func_11DF90(BootInputRoot9670* root, s32 slot);
void* func_100AC0(u32 size, s32 flags);
s32 func_432720(BootModeOwner0910* owner, void* queue);
void func_432660(BootModeOwner0910* owner, s32 mode, u32 enabled, u32 flags);
s32 func_432310(BootModeOwner0910* owner, u32 mode, BootTransferRequest0AF0* request);
s32 func_432270(BootModeOwner0910* owner, s32 mode, s32* result);
extern void* D_001B6614;
void* func_100B00(u32 size, s32 flags);
char* func_13C948(char* destination, const char* source);
void* func_13A4C0(void* destination, const void* source, u32 size);
extern const char D_205100[];
extern const char D_205980[];
}

#endif
