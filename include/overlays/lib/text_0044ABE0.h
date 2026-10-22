#ifndef SO3_OVERLAYS_LIB_TEXT_0044ABE0_H
#define SO3_OVERLAYS_LIB_TEXT_0044ABE0_H

#include "types.h"

typedef struct LibDrawState64 LibDrawState64;
typedef struct ItemCreationClass174C40 ItemCreationClass174C40;
typedef struct LibClass174610 LibClass174610;

/** Partial receiver whose byte at offset 0x60 is set by func_0044C050. */
typedef struct LibObjectByte60
{
    u8 unk00[0x60];
    u8 unk60;
} LibObjectByte60;

#ifdef __cplusplus
extern "C" {
void* func_004568A0(void* receiver);
#endif
/** @brief Set the receiver's byte at offset 0x60 to 8. @param object Receiver to update. */
void func_0044C050(LibObjectByte60* object);
/** @brief Set the receiver's byte at offset 0x60 to 8. @param object Receiver to update. */
void func_0044D070(LibObjectByte60* object);
/** @brief Return the address of D_508230. @return The data symbol's address. */
const void* func_0044D080(void);
/** @brief Update the transform and mark the current display ready. @param object Transform receiver. */
void func_0044D0D0(void* object);
/** @brief Return the fixed value 35. @param object Unused receiver. @return Always 35. */
s32 func_00451E20(void* object);
/** @brief Return the fixed value 43. @return Always 43. */
s32 func_004540D0(void);
/** @brief Return the fixed value 10. @return Always 10. */
s32 func_00454730(void);
/** @brief Return the fixed value 43. @return Always 43. */
s32 func_004547B0(void);
/** @brief Return the fixed value 40. @return Always 40. */
s32 func_00456200(void);
/** @brief Return the fixed value 6. @return Always 6. */
s32 func_00456940(void);
/** @brief Return the fixed value 36. @return Always 36. */
s32 func_004569C0(void);
/** @brief Return the fixed value 9. @return Always 9. */
s32 func_0045ABA0(void);
/** @brief Perform no work. @param object Unused receiver. */
void func_0044C060(void* object);
/** @brief Return the address of D_508240. @return The data symbol's address. */
const void* func_0044C070(void);
/** @brief Clear the selected state in the shared lib object. */
void func_0044C080(void);
/** @brief Forward the receiver to the base transform update. @param object Transform receiver. */
void func_0044C0F0(void* object);
/** @brief Forward the receiver to the base transform update. @param object Transform receiver. */
void func_0044D150(void* object);
/** @brief Detach the transform once and mark it released. @param object Transform receiver. */
void func_0044B1C0(LibClass174610* object);

/**
 * @brief Detach the transform receiver from its parent container when attached.
 * @param object Transform receiver to detach.
 */
void func_0044B210(LibClass174610* object);

/**
 * @brief Apply the saved input mode, slot configuration, and input flag.
 * @param settings Saved settings receiver.
 */
void func_004587C0(void* settings);

/**
 * @brief Compute the seeded checksum over a byte range.
 * @param seed Initial checksum seed.
 * @param data Bytes to checksum.
 * @param size Signed byte count.
 * @return Low sixteen bits of the resulting checksum.
 */
u16 func_00457470(u16 seed, const void* data, s32 size);

/**
 * @brief Select the indexed resource and initialize its drawing position.
 * @param object Resource widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param index Resource index.
 * @return Initialization status.
 */
s32 lib_indexed_resource_init(ItemCreationClass174C40* object, float x, float y, s32 index);

/** @brief Initialize resource pointers, drawing scales, colors, and descriptor defaults. @param state State to initialize. */
void lib_draw_state_init(LibDrawState64* state);
#ifdef __cplusplus
}
#endif

/** Drawing state containing resource pointers, scalar coordinates, and descriptor bytes. */
struct LibDrawState64
{
    u32 unk00;
    void* unk04;
    void* unk08;
    u32 unk0c;
    u32 unk10;
    u8 unk14[4];
    float unk18;
    float unk1c;
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
    float unk48;
    float unk4c;
    float unk50;
    u16 unk54;
    u16 unk56;
    u8 unk58;
    u8 unk59;
    u8 unk5a;
    u8 unk5b;
    u8 unk5c[2];
    /** Negative values use the resource record's default descriptor byte. */
    s8 unk5e;
    u8 unk5f;
    u8 unk60;
    u8 unk61[3];
#ifdef __cplusplus
    /** @brief Initialize the drawing state. */
    LibDrawState64()
    {
        lib_draw_state_init(this);
    }
#endif
};

#ifdef __cplusplus
#include "overlays/lib/text_004BD360.h"

/** @brief Clear the intrusive owner and invoke the base transform release. @param object Transform owner to detach. */
extern "C" void func_0044D090(LibClass178A90* object);

/** Four scalar components stored in a LibVectorUpdateView. */
typedef struct LibFloatVector4
{
    float x;
    float y;
    float z;
    float w;
} LibFloatVector4;

/** Partial state updated by func_0044B190; its caller passes the containing object's +0x20 address. */
typedef struct LibVectorUpdateView
{
    u8 unk00[0x20];
    LibFloatVector4 unk20;
    u8 unk30[0x7E];
    u8 unkAE;
} LibVectorUpdateView;

/** @brief Update x and y, preserve z, set w to one, and mark the state. @param state Partial vector state. @param x Horizontal component. @param y Vertical component. */
extern "C" void func_0044B190(LibVectorUpdateView* state, float x, float y);

/** @brief Queue the receiver's DMA callback interface. @param object Transform receiver. @return Queue insertion result. */
extern "C" s32 func_0044C110(LibClass174610* object);

/** Partial Lib class with vtable D_174C20 in main data; its destructor is func_00452F00. */
class LibClass174C20
{
public:
    /** @brief Destroy the object. */
    virtual ~LibClass174C20();
};

/** Clipping widget with resident vtable at 0x1746A0. */
class ItemCreationClass1746A0 : public LibClass178600
{
public:
    /** @brief Initialize the widget storage and select kind 4. */
    inline ItemCreationClass1746A0();
    /**
     * @brief Initialize clipping rectangle geometry and drawing storage.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param width Drawing width.
     * @param height Drawing height.
     */
    inline ItemCreationClass1746A0(float x, float y, float width, float height);
    /** @brief Initialize storage that restores the runtime clipping bounds. @param code Initialization code passed to the resident routine. */
    inline ItemCreationClass1746A0(s32 code);
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass1746A0();
    /** @brief Write the widget clipping bounds into its drawing packet. */
    virtual void draw();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    u8 unk50;
};

/** Partial widget with resident vtable at 0x175110. */
class ItemCreationClass175110 : public LibClass178600
{
public:
    /** @brief Initialize the owned storage and drawing state for kind 7. */
    ItemCreationClass175110()
    {
        unk38 = 7;
    }
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass175110();
    /** @brief Refresh the resource drawing state. */
    virtual void func_00413D20();
    /** @brief Draw the resource widget. */
    virtual void draw();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    LibDrawState64 unk50;
    void* unkb4;
    u16 unkb8;
    u16 unkba;
    u8 unkbc;
    u8 unkbd;
    u8 unkbe;
    u8 unkbf;
    s32 unkc0;
    u32 unkc4;
    u8 unkc8;
    u8 unkc9;
    u8 unkca[2];
};

/** Resident resource widget with its two resource indices at CC and D0. */
class ItemCreationClass174C40 : public ItemCreationClass175110
{
public:
    /** @brief Initialize the resource widget. */
    ItemCreationClass174C40()
    {
    }
    /** @brief Release the resource widget and destroy its base. */
    virtual ~ItemCreationClass174C40();
    /** @brief Refresh the indexed resource drawing state. */
    virtual void func_00413D20();
    s32 unkcc;
    s32 unkd0;
    /** @brief Set both drawing scales. @param x Horizontal scale. @param y Vertical scale. */
    void set_scale(float x, float y)
    {
        unk50.unk34 = y;
        unk50.unk30 = x;
        unk3c = 1;
    }
};

typedef ItemCreationClass1746A0 LibClass1746A0;
typedef ItemCreationClass175110 LibClass175110;
typedef ItemCreationClass174C40 LibClass174C40;

/** @brief Initialize storage that restores the runtime clipping bounds. @param object Clipping widget. @param code Unused initialization argument. @return True when drawing storage was allocated. */
extern "C" bool lib_scissor_init_reset(ItemCreationClass1746A0* object, s32 code);
/** @brief Initialize clipping rectangle geometry and drawing storage. @param object Clipping widget. @param x Horizontal position. @param y Vertical position. @param width Drawing width. @param height Drawing height. @return True when drawing storage was allocated. */
extern "C" bool lib_scissor_init_rectangle(ItemCreationClass1746A0* object, float x, float y, float width, float height);

/**
 * @brief Initialize clipping rectangle geometry and drawing storage.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Drawing width.
 * @param height Drawing height.
 */
inline ItemCreationClass1746A0::ItemCreationClass1746A0(float x, float y, float width, float height)
{
    unk38 = 4;
    lib_scissor_init_rectangle(this, x, y, width, height);
}
/** @brief Initialize storage that restores the runtime clipping bounds. @param code Initialization code passed to the resident routine. */
inline ItemCreationClass1746A0::ItemCreationClass1746A0(s32 code)
{
    unk38 = 4;
    lib_scissor_init_reset(this, code);
}

#endif

#endif
