#ifndef SO3_OVERLAYS_LIB_TEXT_0044ABE0_H
#define SO3_OVERLAYS_LIB_TEXT_0044ABE0_H

#include "types.h"

typedef struct LibDrawState64 LibDrawState64;
#ifdef __cplusplus
extern "C" {
#endif
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

/** @brief Initialize the drawing state. @param state State to initialize. */
void func_453FF0(LibDrawState64* state);
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
    u8 unk5e;
    u8 unk5f;
    u8 unk60;
    u8 unk61[3];
#ifdef __cplusplus
    /** @brief Initialize the drawing state. */
    LibDrawState64()
    {
        func_453FF0(this);
    }
#endif
};

#ifdef __cplusplus
#include "overlays/lib/text_004BD360.h"

/** Partial widget with resident vtable at 0x1746A0. */
class ItemCreationClass1746A0 : public LibClass178600
{
public:
    /** @brief Initialize the widget storage and select kind 4. */
    inline ItemCreationClass1746A0();
    /**
     * @brief Initialize frame geometry and storage.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param width Drawing width.
     * @param height Drawing height.
     */
    inline ItemCreationClass1746A0(float x, float y, float width, float height);
    /** @brief Initialize enabled frame storage. @param code Initialization code passed to the resident routine. */
    inline ItemCreationClass1746A0(s32 code);
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass1746A0();
    /** @brief Draw the frame widget. */
    virtual void func_00462310();
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
    virtual void func_00462310();
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
/** @brief Initialize the indexed resource drawing state. @param object Resource widget. @param index Resource index. @param x Horizontal position. @param y Vertical position. @return Initialization status. */
extern "C" s32 func_4530E0(ItemCreationClass174C40* object, s32 index, float x, float y);

typedef ItemCreationClass1746A0 LibClass1746A0;
typedef ItemCreationClass175110 LibClass175110;
typedef ItemCreationClass174C40 LibClass174C40;

/** @brief Initialize enabled frame storage. @param object Frame widget. @param code Initialization code. @return Initialization status. */
extern "C" s32 func_44B510(ItemCreationClass1746A0* object, s32 code);
/** @brief Initialize frame geometry and storage. @param object Frame widget. @param x Horizontal position. @param y Vertical position. @param width Drawing width. @param height Drawing height. @return Initialization status. */
extern "C" s32 func_44B570(ItemCreationClass1746A0* object, float x, float y, float width, float height);

/**
 * @brief Initialize frame geometry and storage.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Drawing width.
 * @param height Drawing height.
 */
inline ItemCreationClass1746A0::ItemCreationClass1746A0(float x, float y, float width, float height)
{
    unk38 = 4;
    func_44B570(this, x, y, width, height);
}
/** @brief Initialize enabled frame storage. @param code Initialization code passed to the resident routine. */
inline ItemCreationClass1746A0::ItemCreationClass1746A0(s32 code)
{
    unk38 = 4;
    func_44B510(this, code);
}

#endif

#endif
