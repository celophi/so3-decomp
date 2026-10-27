#ifndef SO3_OVERLAYS_BOOT_TEXT_001DD3C0_H
#define SO3_OVERLAYS_BOOT_TEXT_001DD3C0_H

#include "types.h"

/** @brief Four aligned floating-point vector components. */
typedef struct BootVector4DDAA0
{
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) BootVector4DDAA0;

/**
 * @brief Copy all 128 bits of an aligned four-component vector.
 * @param destination Vector receiving the copy.
 * @param source Vector to copy.
 */
static inline void copy_vector(BootVector4DDAA0* destination, const BootVector4DDAA0* source)
{
    *(unsigned __int128*)destination = *(const unsigned __int128*)source;
}

/** @brief Matrix storage containing four aligned four-component vectors. */
typedef struct BootMatrix92D0
{
    BootVector4DDAA0 vectors[4];
} BootMatrix92D0;

/** @brief Partial resource storage for transferred flag bits and header values. */
typedef struct BootResourceBits0970
{
    u8 unk00[8];
    u8* unk08;
    u8 unk0C[8];
    u32 unk14;
    u8 unk18[8];
} BootResourceBits0970;

/** @brief Partial system settings, with option bits and two checksummed blocks. */
typedef struct BootResource0970
{
    /** Button mask that confirms a selection. */
    u16 unk00;
    /** Button mask that cancels or skips. */
    u16 unk02;
    u8 unk04[0x20];
    u8 unk24_low : 2;
    u8 unk24_mid : 2;
    u8 unk24_bit4 : 1;
    u8 unk24_bit5 : 1;
    u8 unk24_bit6 : 1;
    u8 unk24_bit7 : 1;
    u8 unk25_low : 1;
    u8 unk25_bit1 : 1;
    u8 unk25_mode : 2;
    u8 unk25_mid : 2;
    u8 unk25_bit6 : 1;
    u8 unk25_bit7 : 1;
    /** First byte covered by checksum. */
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 unk29[0x7B];
    u16 checksum;
    /** Seed for checksum, replaced on every write. */
    u16 key;
    u8 unkA8[0xE4];
    /** Nonzero for the 16:9 screen layout. */
    u8 widescreen;
    u8 unk18D;
    u8 unk18E;
    u8 unk18F[0x11];
    /** First byte covered by extra_checksum. */
    u8 unk1A0;
    u8 unk1A1;
    u8 unk1A2;
    u8 unk1A3;
    u16 extra_checksum;
    /** Seed for extra_checksum. */
    u16 extra_key;
    BootResourceBits0970 unk1A8;
} BootResource0970;

/** Partial resident memory card and loading state reached through D_001B65E4. */
typedef struct BootResident1B65E4
{
    u8 unk00[0x108];
    u8 unk108;
    u8 unk109[0x32];
    u8 unk13b;
    u8 unk13c[5];
    u8 unk141;
    u8 unk142[0x12041];
    u8 unk12183;
} BootResident1B65E4;

/** Partial resident display runtime reached through D_001B657C. */
typedef struct BootRuntime1B657C
{
    u8 unk00[0x568];
    /** Number the next formatted message prints. */
    u32 message_value;
} BootRuntime1B657C;

/** @brief Partial resident sound object reached through D_001B65F8. */
struct BootSound1B65F8
{
    u8 unk00[0x450];
    /** Output mode the player selected in the options. */
    u8 unk450;
};

/** @brief Partial object containing the two signed dimensions used by projection. */
typedef struct BootDimensionsACD0
{
    u8 unk00[0x3C6C];
    s16 unk3C6C;
    s16 unk3C6E;
} BootDimensionsACD0;

/** @brief Partial resident receiver of the copied pointer. */
typedef struct BootPointerContextACC0
{
    u8 unk00[0x90];
    void* unk90;
} BootPointerContextACC0;

#ifdef __cplusplus
extern "C" {
#endif

extern BootPointerContextACC0* D_001B6628;

extern class BootProjectionACD0* D_001B6654;

void* func_10D8E0(void);
void* func_101290(void* object);
void* func_101440(void* table, s32 selector);
void* func_13A678(void* destination, s32 value, u32 size);
void func_100BE0(void* allocation);
extern BootRuntime1B657C* D_001B657C;
u8* func_102920(void* decoder, u8* source, s32 index, s32 aligned);
s32 func_1025A0(void* decoder, u8* source, void* destination, s32 index);
s32 func_102D00(void* queue);
extern BootResident1B65E4* D_001B65E4;
extern void* D_001B65E8;
extern void* D_001B65F4;
extern struct BootSound1B65F8* D_001B65F8;
u32 func_11C8C0(void* table, s32 id);
u8* func_139700(u32 alignment, u32 size);
void func_103E70(void* queue, s32 id, void* destination, s32 first, u32 size, s32 second, s32 third, s32 fourth, s32 fifth);

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
extern "C" void func_4D5C90(void* object);

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

/** Partial 0x880-byte Lib projection object; boot calls the Lib constructor. */
class BootProjectionACD0 : public BootClass170E90
{
public:
    u8 unk14[0x23C];
    float unk250;
    u8 unk254[8];
    float unk25C;
    u8 unk260[0x18];
    float unk278;
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

/** Boot's view of the Lib model base that adds a matrix and three vectors, with the Lib vtable D_172080. */
class BootClass172080 : public BootClass178A90
{
public:
    /** @brief Destroy the model base; boot uses the Lib implementation. */
    virtual ~BootClass172080();
    /** @brief Rebuild the transformation matrix; boot uses the Lib implementation. */
    virtual void update_transform_matrix();
    /** @brief Read the transformation matrix. @return The matrix. */
    virtual const void* get_transform_matrix()
    {
        return &unk90;
    }
    /** @brief Read the first stored vector. @return Vector at offset 0x1D0. */
    virtual const BootVector4DDAA0* func_001E9560() const
    {
        return &unk1D0;
    }
    /** @brief Read the second stored vector. @return Vector at offset 0x1E0. */
    virtual const BootVector4DDAA0* func_001E9570() const
    {
        return &unk1E0;
    }
    /** @brief Read the third stored vector. @return Vector at offset 0x1F0. */
    virtual const BootVector4DDAA0* func_001E9580() const
    {
        return &unk1F0;
    }
    /** @brief Copy another model's state; boot uses the Lib implementation. @param source Model to copy. */
    virtual void func_4D9F40(const BootClass172080* source);
    BootMatrix92D0 unk90;
    u8 unkD0[0x100];
    BootVector4DDAA0 unk1D0;
    BootVector4DDAA0 unk1E0;
    BootVector4DDAA0 unk1F0;
    u8 unk200[0x10];
    u8 unk210;
};

/** Boot's view of the Lib model with color factors, with the Lib vtable D_174310. */
class BootClass174310 : public BootClass172080
{
public:
    /** @brief Destroy the model; boot uses the Lib implementation. */
    virtual ~BootClass174310();
    /** @brief Detach and queue the model; boot uses the Lib implementation. */
    virtual void destroy();
    /**
     * @brief Store the byte at offset 0x210 and set its flag.
     * @param value Byte to store.
     */
    virtual void func_001E94E0(u8 value)
    {
        unk210 = value;
        unk59d_3 = 1;
    }
    /**
     * @brief Copy another model's byte at offset 0x210 and its Lib state.
     * @param source Model to copy.
     */
    virtual void func_001E9500(const BootClass174310* source)
    {
        func_001E94E0(source->unk210);
        BootClass172080::func_4D9F40(source);
    }
    /** @brief Store the component product of the two input vectors. */
    virtual void func_001DDAA0();
    /**
     * @brief Store the color modulation, then recompute the combined color factor.
     * @param key Caller's key; unused here.
     * @param modulation Color modulation to store.
     */
    virtual void func_001E94A0(s32 key, const BootVector4DDAA0* modulation)
    {
        copy_vector(&unk570, modulation);
        func_001DDAA0();
    }
    /** @brief Read the color modulation. @return Vector at offset 0x570. */
    virtual const BootVector4DDAA0* func_001E94D0() const
    {
        return &unk570;
    }
    /** @brief Virtual slot 0x98; boot uses the Lib implementation. */
    virtual void func_slot98();
    /** @brief Virtual slot 0x9C; boot uses the Lib implementation. */
    virtual void func_448180();
    u8 unk220[0x340];
    BootVector4DDAA0 unk560;
    BootVector4DDAA0 unk570;
    BootVector4DDAA0 unk580;
    u8 unk590[0xD];
    u8 unk59d_0_2 : 3;
    u8 unk59d_3 : 1;
    u8 unk59d_4_7 : 4;
    u8 unk59e[2];
    u8 unk5a0;
    u8 unk5a1[0x93];
    void* unk634;
    u8 unk638[8];
};

/** Boot's view of the Lib model base that adds five more slots; no vtable of its own appears in main data. */
class BootClass177820Primary : public BootClass174310
{
public:
    /** @brief Destroy the model; boot uses the Lib implementation. */
    virtual ~BootClass177820Primary();
    /** @brief Virtual slot 0xA0; boot uses the Lib implementation. */
    virtual void func_4A3F50();
    /** @brief Virtual slot 0xA4; boot uses the Lib implementation. */
    virtual void func_4A3EC0();
    /** @brief Virtual slot 0xA8; boot uses the Lib implementation. */
    virtual void func_4A3E50();
    /** @brief Virtual slot 0xAC. @return Nonzero when set. */
    virtual s32 func_001E9460();
    /** @brief Virtual slot 0xB0. @return Byte pointer. */
    virtual u8* func_001E9470();
};

/** Boot's view of the Lib model's second base at offset 0x640. */
class BootClass177820Secondary
{
public:
    /** @brief First secondary slot. */
    virtual void func_4A4510();
    /** @brief Second secondary slot. */
    virtual void func_4A4550();
};

/** Boot's view of the Lib model with vtable D_177820; boot calls its Lib destructor. */
class BootClass177820 : public BootClass177820Primary, public BootClass177820Secondary
{
public:
    /** @brief Destroy the model; boot uses the Lib implementation. */
    virtual ~BootClass177820();
    /** @brief Detach the attached object when the gate is set, then destroy the model through its base. */
    virtual void destroy()
    {
        if (unk5a0 != 0 && unk634 != 0)
        {
            func_4D5C90(unk634);
        }
        BootClass174310::destroy();
    }
    /** @brief Advance the model; boot uses the Lib implementation. */
    virtual void update();
    /** @brief Virtual slot 4; boot uses the Lib implementation. */
    virtual void func_001DD4C0();
    /** @brief Boot uses the Lib implementation. */
    virtual void func_001E0860();
    /** @brief Boot uses the Lib implementation. @param output Opaque output object. @return Lib result. */
    virtual s32 func_001E0880(void* output);
    /** @brief Boot uses the Lib implementation. @param value Value to test. @param mode Mode. @return Lib result. */
    virtual bool func_001E0890(float value, float mode);
    /** @brief Boot uses the Lib implementation. @return Vector pointer. */
    virtual const BootVector4DDAA0* func_001E08B0();
    /**
     * @brief Apply a matrix; boot uses the Lib implementation.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void func_001E08C0(const void* matrix, void* context);
    /** @brief Boot uses the Lib implementation. @return Transformation receiver. */
    virtual BootClass178A90* func_001E08D0();
    /** @brief Boot uses the Lib implementation. */
    virtual void func_001E08E0();
    /** @brief Virtual slot 0x98; boot uses the Lib implementation. */
    virtual void func_slot98();
    /** @brief Check whether the word at offset 0x704 is nonzero. @return One if nonzero, otherwise zero. */
    virtual s32 func_001E9460()
    {
        return unk704 != 0;
    }
    /** @brief Return the address of the bytes at offset 0x79C. @return Pointer to the bytes. */
    virtual u8* func_001E9470()
    {
        return unk79c;
    }
    /** @brief Return zero. @return Always 0. */
    virtual s32 func_001E9400()
    {
        return 0;
    }
    /** @brief Return zero. @return Always 0. */
    virtual s32 func_001E9410()
    {
        return 0;
    }
    /** @brief Return the supplied value. @param value Value to return. @return The supplied value. */
    virtual s32 func_001E9420(s32 value)
    {
        return value;
    }
    /** @brief Return the supplied value. @param value Value to return. @return The supplied value. */
    virtual s32 func_001E9430(s32 value)
    {
        return value;
    }
    /** @brief Return zero. @return Always 0. */
    virtual s32 func_001E9440()
    {
        return 0;
    }
    /** @brief Return zero. @return Always 0. */
    virtual s32 func_001E9450()
    {
        return 0;
    }
    /** @brief First secondary slot; boot uses the Lib implementation. */
    virtual void func_4A4510();
    /** @brief Second secondary slot; boot uses the Lib implementation. */
    virtual void func_4A4550();
    /** @brief Return the byte at offset 0x794. @return The stored byte. */
    virtual u8 func_001E9480()
    {
        return unk794;
    }
    /** @brief Boot uses the Lib implementation. */
    virtual void func_4A37C0();
    /** @brief Boot uses the Lib implementation. */
    virtual void func_4A7E80();
    /** @brief Boot uses the Lib implementation. */
    virtual void func_4A4ED0();
    /** @brief Return zero. @return Always 0. */
    virtual s32 func_001E9490()
    {
        return 0;
    }
    u8 unk644[0xC0];
    u32 unk704;
    u8 unk708[0x8C];
    u8 unk794;
    u8 unk795[7];
    u8 unk79c[0x84];
    BootVector4DDAA0 unk820;
    u8 unk830[0x10];
};

/** Partial model object with vtable D_170F30 in main data. */
class BootClass170F30 : public BootClass177820
{
public:
    /** @brief Destroy the model object. */
    virtual ~BootClass170F30();
    /**
     * @brief Negate the matrix's second vector, then apply the matrix through the Lib model.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void func_001E08C0(const void* matrix, void* context);
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
    /** @brief Release the owned objects, then queue this object for deletion. */
    virtual void destroy();
    /** @brief Advance the object's state. */
    virtual void update();
    /** @brief Store the byte at offset 0x18. @param value Byte to store. */
    virtual void func_001E0250(u8 value);
    u8 unk14[4];
    u8 unk18;
    u8 unk19[3];
    BootClass178660* unk1C;
    BootClass170E90* unk20;
    BootClass170E90* unk24;
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
