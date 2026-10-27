#ifndef SO3_OVERLAYS_BOOT_TEXT_001E0900_H
#define SO3_OVERLAYS_BOOT_TEXT_001E0900_H

#include "overlays/boot/text_001DD3C0.h"
#include "main/resident_001001E0.h"
#include "overlays/lib/vector.h"

#define BOOT_TRANSFER_NAME_CAPACITY 64
#define BOOT_TRANSFER_BUFFER_SIZE 1158050
#define BOOT_TRANSFER_FLAG_COUNT 300
#define BOOT_TRANSFER_FLAG_BYTES ((BOOT_TRANSFER_FLAG_COUNT + 7) / 8)

/** @brief Partial 0x100-byte record the memory card object keeps per slot. */
struct BootModeSlot0910
{
    u8 unk00[0x48];
    /** Card state; two once the card is ready. */
    s32 unk48;
    /** Free space. */
    s32 unk4C;
    /** Nonzero when the card is formatted. */
    s32 unk50;
    u8 unk54[0xAC];
};

/** Partial 0x58-byte Lib memory card object that runs the two transfer modes; boot calls the Lib constructor. */
class BootModeOwner0910 : public BootClass170E90
{
public:
    /** @brief Initialize the memory card object. */
    BootModeOwner0910();
    BootModeSlot0910* unk14;
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
    s32 unk24;
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
    u8* unkDC4;
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
    BootClass178660* unk34;
    BootClass178750* unk38;
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

extern "C" void func_4BDD10(class BootClass178220* animation);

/** Partial 0x70-byte Lib animation with vtable D_178220 in main data; boot calls the Lib constructor. */
class BootClass178220 : public BootClass170E90
{
public:
    /** @brief Construct an empty animation. */
    BootClass178220();

    /**
     * @brief Release the current channels and resource, then play from borrowed data.
     * @param data Animation data the caller keeps.
     */
    void set_resource(void* data)
    {
        if (entries)
        {
            func_4BDD10(this);
            delete[] entries;
        }
        targets_bound = 0;
        if (!resource_is_borrowed)
        {
            operator delete(resource_data);
        }
        resource_is_borrowed = 1;
        resource_data = data;
    }

    u8 unk14[0x1C];
    void* resource_data;
    u8 unk34[0xC];
    u8* entries;
    u8 unk44[0x24];
    u8 resource_is_borrowed;
    u8 unk69;
    /** Cleared to restart the animation from its first frame. */
    u8 unk6A;
    u8 unk6B[3];
    u8 targets_bound;
    u8 unk6F;
};

/** Partial 0xD0-byte Lib animation target with vtable D_178370 in main data; boot calls the Lib constructor. */
class BootClass178370 : public BootClass170E90
{
public:
    /** @brief Construct an empty target. */
    BootClass178370();
    u8 unk14[0xBC];
};

/** Partial 0xB0-byte Lib scene with vtable D_175320 in main data; boot calls the Lib constructor. */
class BootClass175320 : public BootClass170E90
{
public:
    /** @brief Construct an empty scene. */
    BootClass175320();
    u8 unk14[0x9C];
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

    /** @brief Show the message describing the selected option's value. */
    void show_value_message();

    /**
     * @brief Read the cursor position for the selected row of the current page.
     * @param x Receives the horizontal position.
     * @param y Receives the vertical position; unchanged for an unknown row.
     */
    void func_001E5250(float* x, float* y);

    /** @brief Rebuild the current page's option rows when the page changes, then place and highlight them. */
    void func_001E5510();

    /** @brief Turn the camera to the current angle and roll, then step the camera animation states. */
    void func_001E3FF0();

    /**
     * @brief Read the cursor position for a speaker on the surround page.
     * @param speaker Speaker index.
     * @param x Receives the horizontal position.
     * @param y Receives the vertical position.
     */
    void func_001E4610(s32 speaker, float* x, float* y);

    /** @brief Place the five speaker models around the listener and pulse the selected one. */
    void func_001E4760();

    /** @brief Create the page's images once their textures are loaded, then place and highlight them. */
    void func_001E63B0();

    u8* unk14;
    u8* unk18[5];
    u8* unk2C;
    u8* unk30[8];
    s32 unk50;
    /** Camera angle around the listener. */
    float unk54;
    /** Turn input; zero when idle. */
    float unk58;
    /** Time in the current camera animation. */
    float unk5C;
    /** Camera roll, eased toward the turn direction. */
    float unk60;
    /** Selected speaker's angle before adjusting it, restored on cancel. */
    float unk64;
    u8 unk68;
    u8 unk69;
    u8 unk6A;
    u8 unk6B;
    u8 unk6C;
    u8 unk6D;
    u8 unk6E;
    /** Selected speaker on the surround page. */
    u8 unk6F;
    u8 unk70;
    u8 unk71;
    /** Selected speaker pulse: zero off, one growing, two shrinking. */
    u8 unk72;
    u8 unk73;
    /** Voice line the face lip-syncs to, or zero. */
    s32 unk74;
    /** Blink frame counter, zero while the eyes are open. */
    s32 unk78;
    s32 unk7C;
    /** Horizontal position of the current page's rows. */
    float unk80;
    BootImage* unk84[21];
    BootClass175320* unkD8;
    BootClass175320* unkDC;
    BootClass170F30* unkE0[10];
    /** Camera animations, one per state of unk70. */
    BootClass178220* unk108[6];
    BootClass178370* unk120[6];
    BootClass170F10 unk138;
    BootClass178660* unk13C;
    BootClass178750* unk140;
    BootClass175070* unk144;
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

/** Partial movie decoder state reached through the player. */
struct BootMovieState15E700
{
    /**
     * @brief Store the two scale words at offset 0x80C4.
     * @param first First scale.
     * @param second Second scale.
     */
    void set_scale(float first, float second)
    {
        unk80C4 = first;
        unk80C8 = second;
    }

    /**
     * @brief Store the three words at offset 0x80AC.
     * @param first First word.
     * @param second Second word.
     * @param third Third word.
     */
    void set_words(s32 first, s32 second, s32 third)
    {
        unk80AC = first;
        unk80B0 = second;
        unk80B4 = third;
    }

    u8 unk00[0x80AC];
    s32 unk80AC;
    s32 unk80B0;
    s32 unk80B4;
    u8 unk80B8[8];
    /** Frame being shown. */
    s32 unk80C0;
    float unk80C4;
    float unk80C8;
    u8 unk80CC[0xC];
    u8 unk80D8;
};

/** Partial 0x15E7C0-byte Lib movie player with vtable D_172500 in main data; boot calls the Lib constructor. */
class BootClass172500 : public BootClass170E90
{
public:
    /**
     * @brief Initialize the player and its decoder for a frame size.
     * @param width Frame width.
     * @param height Frame height.
     */
    BootClass172500(s32 width, s32 height);
    /** @brief Destroy the player. */
    virtual ~BootClass172500();
    u8 unk14[0x15E6EC];
    BootMovieState15E700* state;
    u8 unk15E704[0x90];
    /** Nonzero while the movie plays. */
    u8 unk15E794;
    u8 unk15E795[0x2B];
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

    /** Step: start, captions, wait for the end, stop, hand over. */
    s32 unk14;
    /** Caption being shown. */
    s32 unk18;
    /** Caption phase: zero none, one fading in, two shown, three fading out. */
    s32 unk1C;
    /** Nonzero once the caption image exists. */
    u8 unk20;
    u8 unk21[3];
    BootResident113E40* unk24;
    BootClass172500* unk28;
    BootImage* unk2C;
    BootClass178660* unk30;
    BootClass178750* unk34;
};

/** Partial 0x20-byte boot object with vtable D_171090 in main data. */
class BootClass171090 : public BootClass170E90
{
public:
    /**
     * @brief Start loading the program's resource 0x26.
     * @param owner Program that receives the decoded blocks.
     */
    BootClass171090(class BootClass1710B0* owner)
    {
        data = func_139700(0x40, func_11C8C0(D_001B65E4, 0x26));
        func_103E70(D_001B65E8, 0x26, data, 1, 0x34BC0, 0, 0, 0, 1);
        program = owner;
        block = 0;
    }

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

    /**
     * @brief Replace the display and, on a full rebuild, the scratch heap.
     * @param full Nonzero to also recreate the scratch heap and rebind the display.
     */
    void func_001EAA40(u8 full);

    /**
     * @brief Switch the widescreen setting, rebuild the display and rebind it everywhere.
     * @param widescreen Nonzero for the widescreen projection.
     */
    void func_001EAE80(u8 widescreen);

    /** @brief Fill the track pools, then create and register the projection. */
    void func_001EB210();

    /** @brief Release the track pools and every object, resource and buffer the program owns. */
    void func_001EBCF0();

    BootDimensionsACD0* unk04;
    BootProjectionACD0* unk08;
    BootClass171030* input;
    u8* unk10;
    /** Boot's message bank. */
    /** @brief Read the message bank handle. @return Bank handle. */
    s32 get_messages() const
    {
        return messages;
    }

    s32 messages;
    u8* unk18;
    s32 unk1C;
    u8* unk20;
    BootClass170EB0* unk24;
    BootClass170E90* unk28;
    s32 unk2C;
    /** Nonzero once the boot program should end; passed on to the resident runtime. */
    s32 unk30;
    /** Widescreen setting read from the saved settings, or 0xFF when there were none. */
    u8 unk34;
    u8 unk35[3];
    /** Frame counter. */
    s32 unk38;
    u8 unk3C;
    u8 unk3D[3];
    u8* unk40;
};

/** Partial resident object D_001B6658 that holds the current display. */
struct BootResident6658
{
    u8 unk00[4];
    BootDimensionsACD0* display;
};

/** 0x2910-byte Lib heap that may sit at the start of scratchpad memory. */
class BootScratchHeap
{
public:
    /**
     * @brief Create the heap.
     * @param size Heap size in bytes.
     * @param count Block count.
     */
    BootScratchHeap(s32 size, s32 count);

    /**
     * @brief Allocate the heap object through the resident allocator.
     * @param size Object size in bytes.
     * @param heap Heap selector.
     * @return The allocated storage.
     */
    static void* operator new(u32 size, s32 heap)
    {
        return ::operator new(size, heap);
    }

    /**
     * @brief Release the storage when construction fails, unless it is the scratchpad.
     * @param object Storage to release.
     * @param heap Heap selector passed to operator new.
     */
    static void operator delete(void* object, s32 heap)
    {
        if (object != (void*)0x70000000)
        {
            ::operator delete(object);
        }
    }

    u8 unk00[0x2910];
};

/** Shared keyframe sequence fields with packed modes and the pooled flag. */
struct BootSequenceTail
{
    s32 unk00;
    /** Last key minus first key. */
    float span;
    s16 unk08;
    s16 unk0a;
    s16 unk0c;
    s16 unk0e;
    s16 unk10;
    u8 unk12_0_3 : 4;
    u8 unk12_4_7 : 4;
    u8 unk13_0 : 1;
    u8 unk13_1 : 1;
    /** Set while the track belongs to a pool. */
    u8 pooled : 1;
    u8 unk13_3_7 : 5;
};

/** Fixed pool of tracks with a bitmap of used slots. */
template <class T>
struct BootTrackPool
{
    /**
     * @brief Allocate the tracks, mark them pooled and clear the used bitmap.
     * @param count Number of tracks.
     * @return One on success, or zero when the tracks could not be allocated.
     */
    s32 init(s32 count)
    {
        s32 index;
        s32 word_count;
        s32 word;
        items = new (0) T[count];
        if (items == 0)
        {
            return 0;
        }
        for (index = 0; index < count; index++)
        {
            items[index].state.pooled = true;
        }
        if (!external)
        {
            delete[] used;
        }
        capacity = count;
        words = (u32)(count + 63) >> 6;
        used = new (0) u64[words];
        external = false;
        this->count = count;
        unk04 = 0;
        word_count = words;
        for (word = 0; word < word_count; word++)
        {
            used[word] = 0;
        }
        return 1;
    }

    /** @brief Release every track in the pool and its storage. */
    void release()
    {
        s32 track_count = count;
        s32 index;
        for (index = 0; index < track_count; index++)
        {
            items[index].state.pooled = false;
        }
        delete[] items;
        if (!external)
        {
            delete[] used;
            used = 0;
        }
        items = 0;
        count = 0;
    }

    s32 count;
    s32 unk04;
    T* items;
    s32 capacity;
    s32 words;
    u64* used;
    bool external;
};

/** Track record with vtable D_171B00 in main data; its data comes before the vptr. */
class BootClass171B00
{
public:
    /** @brief Reset the record. */
    BootClass171B00();
    u32 unk00;
    u16 unk04;
    u16 unk06;
    u32 unk08;
    u32 unk0C;
    // Virtual slot 8; only its position is known.
    virtual void func_001F4970();
};

/** BootClass171B00 with vtable D_171B30 in main data. */
class BootClass171B30 : public BootClass171B00
{
public:
    /** @brief Reset the record and clear its first word. */
    BootClass171B30();
    // Virtual slots 0xC (pure) and 0x10; only their positions are known.
    virtual void func_slot0c() = 0;
    virtual void func_001F48D0();
};

/** 0x24-byte BootClass171B30 with the Lib vtable D_178200. */
class BootClass178200 : public BootClass171B30
{
public:
    // Lib implementation of the pure slot; only its position is known.
    virtual void func_slot0c();
    u8 unk14[0x10];
};

/** Vector record with vtable D_171B10 in main data; its data comes before the vptr. */
class BootClass171B10
{
public:
    /** @brief Reset the record. */
    BootClass171B10();
    FieldVec4B unk00;
    u16 unk10;
    u16 unk12;
    u32 unk14;
    u32 unk18;
    // Virtual slot 8; only its position is known.
    virtual void func_001F4960();
};

/** BootClass171B10 with vtable D_171B50 in main data. */
class BootClass171B50 : public BootClass171B10
{
public:
    /** @brief Reset the record and clear its vector. */
    BootClass171B50();
    // Virtual slots 0xC (pure) and 0x10; only their positions are known.
    virtual void func_slot0c() = 0;
    virtual void func_001F0560();
};

/** 0x20-byte BootClass171B50 with the Lib vtable D_1781E0. */
class BootClass1781E0 : public BootClass171B50
{
public:
    // Lib implementation of the pure slot; only its position is known.
    virtual void func_slot0c();
};

/** Vector record with vtable D_171B20 in main data; its data comes before the vptr. */
class BootClass171B20
{
public:
    /** @brief Reset the record. */
    BootClass171B20();
    FieldVec4B unk00;
    u16 unk10;
    u16 unk12;
    u32 unk14;
    u32 unk18;
    // Virtual slot 8; only its position is known.
    virtual void func_001F4950();
};

/** BootClass171B20 with vtable D_171B70 in main data. */
class BootClass171B70 : public BootClass171B20
{
public:
    /** @brief Reset the record and clear its vector. */
    BootClass171B70();
    // Virtual slots 0xC (pure) and 0x10; only their positions are known.
    virtual void func_slot0c() = 0;
    virtual void func_001F4850();
};

/** 0x20-byte BootClass171B70 with the Lib vtable D_1781C0. */
class BootClass1781C0 : public BootClass171B70
{
public:
    // Lib implementation of the pure slot; only its position is known.
    virtual void func_slot0c();
};

/** Scalar range with vtable D_171B88 in main data; its data comes before the vptr. */
class BootClass171B88
{
public:
    /** @brief Install the vtable; the range is left unset. */
    BootClass171B88();
    float unk00;
    float unk04;
    float unk08;
    float unk0C;
    float unk10;
    float unk14;
    float unk18;
    // Virtual slot 8 sets the range; only its position is known.
    virtual void func_001EFE50();
};

/** 0x20-byte BootClass171B88 with vtable D_171270 in main data. */
class BootClass171270 : public BootClass171B88
{
public:
    // Virtual slot 0xC; only its position is known.
    virtual void func_001EEE20();
};

/** Partial keyframe track with vtable D_1717A0 in main data; its constructor and destructor are out of line. */
class BootClass1717A0
{
public:
    /** @brief Construct the track. */
    BootClass1717A0();
    /** @brief Destroy the track. */
    virtual ~BootClass1717A0();
    void* unk04;
    u8 unk08[8];
    BootSequenceTail state;
};

/** Partial BootClass1717A0 with vtable D_171560 in main data. */
class BootClass171560 : public BootClass1717A0
{
public:
    /** @brief Destroy the track. */
    virtual ~BootClass171560()
    {
    }
};

/** Partial BootClass171560 with vtable D_1715F0 in main data. */
class BootClass1715F0 : public BootClass171560
{
public:
    /** @brief Destroy the track. */
    virtual ~BootClass1715F0()
    {
    }
    BootClass178200 unk24;
    s32 unk48;
    float unk4c;
};

/** 0x50-byte pooled track with the Lib vtable D_177F70. */
class BootClass177F70 : public BootClass1715F0
{
public:
    /** @brief Construct the track. */
    BootClass177F70();
    /** @brief Destroy the track. */
    virtual ~BootClass177F70();
};

/** Partial keyframe track with vtable D_171830 in main data; its constructor and destructor are out of line. */
class BootClass171830
{
public:
    /** @brief Construct the track. */
    BootClass171830();
    /** @brief Destroy the track. */
    virtual ~BootClass171830();
    void* unk04;
    u8 unk08[0x18];
    BootSequenceTail state;
};

/** Partial BootClass171830 with vtable D_1713B0 in main data. */
class BootClass1713B0 : public BootClass171830
{
public:
    /** @brief Destroy the track. */
    virtual ~BootClass1713B0()
    {
    }
    u8 unk34[0xC];
};

/** Partial BootClass1713B0 with vtable D_171440 in main data. */
class BootClass171440 : public BootClass1713B0
{
public:
    /** @brief Destroy the track. */
    virtual ~BootClass171440()
    {
    }
    BootClass1781E0 unk40;
    u8 unk60[0x50];
};

/** 0xB0-byte pooled track with vtable D_1714D0 in main data. */
class BootClass1714D0 : public BootClass171440
{
public:
    /** @brief Construct the track. */
    BootClass1714D0();
    /** @brief Destroy the track. */
    virtual ~BootClass1714D0();
};

/** Partial keyframe track with vtable D_1718C0 in main data; its constructor and destructor are out of line. */
class BootClass1718C0
{
public:
    /** @brief Construct the track. */
    BootClass1718C0();
    /** @brief Destroy the track. */
    virtual ~BootClass1718C0();
    void* unk04;
    u8 unk08[0x28];
    BootSequenceTail state;
};

/** Partial BootClass1718C0 with vtable D_171320 in main data. */
class BootClass171320 : public BootClass1718C0
{
public:
    /** @brief Destroy the track. */
    virtual ~BootClass171320()
    {
    }
    u8 unk44[0xC];
};

/** 0xC0-byte pooled track with the Lib vtable D_177EE0. */
class BootClass177EE0 : public BootClass171320
{
public:
    /** @brief Construct the track. */
    BootClass177EE0();
    /** @brief Destroy the track. */
    virtual ~BootClass177EE0();
    BootClass1781C0 unk50;
    u8 unk70[0x50];
};

/** Partial keyframe track with vtable D_171950 in main data; its constructor and destructor are out of line. */
class BootClass171950
{
public:
    /** @brief Construct the track. */
    BootClass171950();
    /** @brief Destroy the track. */
    virtual ~BootClass171950();
    void* unk04;
    u8 unk08[0x10];
    BootSequenceTail state;
};

/** Partial BootClass171950 with vtable D_171280 in main data. */
class BootClass171280 : public BootClass171950
{
public:
    /** @brief Destroy the track. */
    virtual ~BootClass171280()
    {
    }
    BootClass171270 unk2C;
    u8 unk4C[8];
};

/** 0x54-byte pooled track with the Lib vtable D_177C70. */
class BootClass177C70 : public BootClass171280
{
public:
    /** @brief Construct the track. */
    BootClass177C70();
    /** @brief Destroy the track. */
    virtual ~BootClass177C70();
};

extern "C" {
s32 func_001EC010(BootTrackPool<BootClass177F70>* pool, s32 count);
void func_001EC490(BootTrackPool<BootClass177F70>* pool);
s32 func_001EC630(BootTrackPool<BootClass1714D0>* pool, s32 count);
void func_001ECAC0(BootTrackPool<BootClass1714D0>* pool);
s32 func_001ECC60(BootTrackPool<BootClass177EE0>* pool, s32 count);
void func_001ED060(BootTrackPool<BootClass177EE0>* pool);
s32 func_001ED200(BootTrackPool<BootClass177C70>* pool, s32 count);
}

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
extern BootClass178DD0* D_001B6614;
void* func_100B00(u32 size, s32 flags);
char* func_13C948(char* destination, const char* source);
void* func_13A4C0(void* destination, const void* source, u32 size);
extern const char D_205100[];
extern const char D_205980[];
extern const char D_205988[];
s32 func_431F90(BootModeOwner0910* owner, s32 slot, char* name, s32 first, s32 second, u8* buffer);
}

#endif
