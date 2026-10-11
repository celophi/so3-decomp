#include "include_asm.h"
#include "overlays/lib/text_004BD360.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"

extern "C" s32 func_00461860(LibStorageBlock0C* storage, s32 count);

/** @brief Unlink a container child. @param object Container. @param child Widget to unlink. */
extern "C" void func_004C6120(LibObject178660* object, LibClass178600* child);

/** Partial text resource fields and the inherited redraw flag. */
typedef struct LibTextResourceState
{
    u8 pad00[0x3C];
    u8 redraw;
    u8 pad3d[0xCB];
    u32 source;
    u32 key;
    u8 flag;
    u8 pending;
} LibTextResourceState;

typedef struct LibPanelAssociation
{
    u8 pad00[0x9C];
    LibClass178630* panel;
} LibPanelAssociation;

typedef struct LibPanelAssociationState
{
    u8 pad00[0x60];
    LibPanelAssociation* association;
} LibPanelAssociationState;

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD380);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD3C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD3D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD3E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD3F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD420);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD490);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD4F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD8A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD8F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD990);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BD9D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BDA30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BDAA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BDB50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BDC00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BDC50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BDCB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BDD10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BDE00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BF100);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BFDB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004BFE10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C02C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C0370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", __ct__14LibClass178220Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C0530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C0CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C0F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1460);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C14D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1560);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C16C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C16D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C16E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C16F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C19E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C1F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C21A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C22B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C23C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C24E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C25D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2620);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C26A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C26B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C26E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C26F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2770);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C27C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2A10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2B30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2B70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2BB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2C40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2CD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", __ct__14LibClass178370Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C2F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C30C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3120);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3470);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C34D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C39A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C39F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3A50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3AD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3AE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3AF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3B70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3C00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3D00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3D60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3D70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3D80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3D90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3DC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3E20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3F10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3FB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3FE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C3FF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C40A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C40B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4100);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C41D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4350);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C43E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4470);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C44E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4620);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_003EF740__14LibClass178600Fv);

/** @brief Unlink the widget from its container before detaching its owner. */
LibClass178600::~LibClass178600()
{
    if (container)
    {
        func_004C6120(container, this);
    }
}

/** @brief Initialize the widget rectangle, container reference, and state bytes. */
LibClass178600::LibClass178600()
{
    unk18.unk0c = 0.0f;
    unk18.unk08 = 0.0f;
    unk18.unk04 = 0.0f;
    unk18.unk00 = 0.0f;
    unk38 = 0;
    container = 0;
    unk28 = 128.0f;
    unk2c[1] = 0;
    unk2c[0] = 0;
    unk34 = 0;
    unk39 = 0;
    unk3a = 0;
    unk3d = 1;
    unk3e = 1;
    unk3f = 1;
    unk3b = 0;
    unk3c = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4A00);

extern "C" void lib_panel_detach(LibClass178630* object)
{
    LibPanelAssociationState* state = (LibPanelAssociationState*)object;
    if (state->association != 0)
    {
        state->association->panel = 0;
        state->association = 0;
    }
}

/** Panel transform with its callback interface at 0x90. */
class FieldClass15BA90 : public LibClass178A90, public LibClass171FF0
{
public:
    /** @brief Initialize the panel transform and its callback interface. */
    FieldClass15BA90();
    /** @brief Release the association and destroy the transform. */
    virtual ~FieldClass15BA90();
    /** @brief Set the transform translation. @param x Horizontal component. @param y Vertical component. @param z Third component. */
    virtual void func_003EF790(float x, float y, float z);
    void* unk94;
    u8 unk98[4];
    LibClass178630* panel;
    u8 pending;
    u8 unka1[0xF];
};
extern "C" s32 func_002F99F0(FieldClass15BA90*, LibClass178630*);

extern "C" s32 lib_panel_init_transform(LibClass178630* object, float z)
{
    object->unk60 = new (0) FieldClass15BA90;
    if (object->unk60 == 0)
        return 0;
    if (func_002F99F0((FieldClass15BA90*)object->unk60, object) == 0)
        return 0;
    ((FieldClass15BA90*)object->unk60)->func_003EF790(0.0f, 0.0f, z);
    if (object->unk8c != 0)
    {
        ((FieldClass15BA90*)object->unk60)->pending = 1;
        object->unk8c = 0;
    }
    ((LibClass178DD0*)D_001B661C)->func_004D74F0(object->unk60, -1);
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C4B90);

typedef struct LibPanelColorState
{
    u8 pad00[0x3C];
    u8 redraw;
    u8 pad3d[0x27];
    u32 colors[4];
} LibPanelColorState;

/**
 * @brief Set the four panel colors and mark the panel for redraw.
 * @param object Panel widget.
 * @param colors Packed colors whose low 24 bits are stored.
 */
extern "C" void lib_panel_set_colors(LibClass178630* object, const LibWidgetColors4C5590* colors)
{
    LibPanelColorState* state = (LibPanelColorState*)object;
    state->colors[0] = colors->values[0] & 0xFFFFFF;
    state->colors[1] = colors->values[1] & 0xFFFFFF;
    state->colors[2] = colors->values[2] & 0xFFFFFF;
    state->colors[3] = colors->values[3] & 0xFFFFFF;
    state->redraw = 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C55E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C56E0);

/** Partial resident panel defaults containing the four packed colors. */
struct LibPanelDefaults
{
    u8 pad00[0x10];
    u32 colors[4];
};
struct LibPanelContext
{
    u8 pad00[0x554];
    LibPanelDefaults* defaults;
};
struct LibPanelInitState
{
    u8 pad00[0x64];
    u32 colors[4];
    u8 pad74[0x10];
    float extra;
    u8 unk88;
    u8 unk89;
    u8 mode;
    u8 unk8b;
    u8 pending;
};
/**
 * @brief Allocate panel drawing storage and initialize its rectangle and colors.
 * @param object Panel widget.
 * @param mode Drawing mode, stored as a byte.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @param extra Additional drawing coordinate.
 * @return One on successful setup, or zero if storage cannot be allocated.
 */
extern "C" s32 lib_panel_init_rectangle(LibClass178630* object, s32 mode, float x, float y, float width, float height, float extra)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;
    object->unk18.unk08 = width;
    object->unk18.unk0c = height;
    if (!func_00461860(&object->unk40, 0x44))
    {
        return 0;
    }
    LibPanelDefaults* defaults = ((LibPanelContext*)D_001B657C)->defaults;
    LibPanelInitState* state = (LibPanelInitState*)object;
    state->colors[0] = defaults->colors[0] & 0xFFFFFF;
    state->colors[1] = defaults->colors[1] & 0xFFFFFF;
    state->colors[2] = defaults->colors[2] & 0xFFFFFF;
    state->colors[3] = defaults->colors[3] & 0xFFFFFF;
    object->unk3c = 1;
    object->unk34 = 0;
    state->extra = extra;
    state->mode = mode;
    state->unk88 = 0;
    state->unk8b = 0;
    state->pending = 1;
    object->unk60 = 0;
    object->unk39 = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C5B60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6120);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6150);

typedef struct LibWidgetContainerLink
{
    u8 pad00[0x14];
    LibObject178660* container;
} LibWidgetContainerLink;
extern "C" void func_004CA020(LibObject178660* list, LibClass178600* node);

/**
 * @brief Link the widget into the container and record its owner.
 * @param object Container receiver.
 * @param child Widget to attach.
 */
extern "C" void lib_container_attach_widget(LibObject178660* object, LibClass178600* child)
{
    func_004CA020(object, child);
    ((LibWidgetContainerLink*)child)->container = object;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C61D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C61F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6230);

/**
 * @brief Allocate container drawing storage and initialize its transform.
 * @param object Container receiver.
 * @param code Transform code.
 * @param first First byte value.
 * @param second Word value.
 * @param x First coordinate.
 * @param y Second coordinate.
 * @param z Third coordinate.
 * @return One on success, or zero if storage cannot be allocated.
 */
extern "C" s32 lib_container_init(LibObject178660* object, s32 code, float x, float y, s32 first, float z, s32 second)
{
    if (!func_00461860(&object->unkD0, 12))
    {
        return 0;
    }
    object->LibClass171EC0::func_003EF790(x, y, 0.0f);
    object->set_codes_and_z(code, first, z, second, 0);
    object->unkE0 = 128.0f;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C65E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C67C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6910);

typedef struct LibTextBoundsState
{
    u8 pad00[0x70];
    void* drawing;
    u8 pad74[0x40];
    u32 count;
    u8 padb8[0x30];
    LibBounds4C69B0 bounds;
    u8 padf8[0x10];
    u32 source;
    u32 key;
    u8 flag;
    u8 pending;
} LibTextBoundsState;
extern "C" s32 func_004C7D40(LibObject178750* object, u32 source, u32 key, u8 flag);
extern "C" void* func_100B00(u32 size, s32 flags);
extern "C" void func_004C74E0(LibObject178750* object);

/**
 * @brief Refresh the text layout and return its measured bounds.
 * @param object Text widget.
 * @return Stored bounds, or null when resource loading or allocation fails.
 */
extern "C" LibBounds4C69B0* lib_text_measure_bounds(LibObject178750* object)
{
    LibTextBoundsState* state = (LibTextBoundsState*)object;
    if (state->pending)
    {
        if (!func_004C7D40(object, state->source, state->key, state->flag))
        {
            return 0;
        }
    }
    state->drawing = func_100B00(state->count * 32, 0);
    if (!state->drawing)
    {
        return 0;
    }
    func_004C74E0(object);
    delete[] (u8*)state->drawing;
    return &state->bounds;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6A40);

extern "C" void lib_text_set_resource(LibObject178750* object, u32 source, u32 key, u8 flag)
{
    LibTextResourceState* state = (LibTextResourceState*)object;
    state->source = source;
    state->key = key;
    state->flag = flag;
    state->pending = 1;
    state->redraw = 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6E10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C6F30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C7010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C71E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C7290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C74E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C79C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C7D00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C7D40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C7F80);

typedef struct LibTextRectangleState
{
    u8 pad00[0xF8];
    u8 flag;
    u8 padf9[3];
    void* allocation;
    u8 pad100[0x11];
    u8 pending;
} LibTextRectangleState;
extern "C" void func_00464870(LibObject178750* object, float x, float y, float width, float height);
/**
 * @brief Initialize the text rectangle and clear its allocation and pending flag.
 * @param object Text widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
extern "C" void lib_text_init_rectangle(LibObject178750* object, float x, float y, float width, float height)
{
    LibTextRectangleState* state = (LibTextRectangleState*)object;
    func_00464870(object, x, y, width, height);
    state->allocation = 0;
    state->pending = 0;
}

/**
 * @brief Initialize the text rectangle and immediately load its resource.
 * @param object Text widget.
 * @param slot Resource source word.
 * @param key Text resource key.
 * @param flag Text slot state flag.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return Resource initialization status.
 */
extern "C" s32 lib_text_init_resource_rectangle(LibObject178750* object, s32 slot, s32 key, u8 flag, float x, float y, float width, float height)
{
    LibTextRectangleState* state = (LibTextRectangleState*)object;
    state->flag = flag;
    func_00464870(object, x, y, width, height);
    state->allocation = 0;
    state->pending = 0;
    return func_004C7D40(object, slot, key, 0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C80E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C81B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8280);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8380);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C83E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8540);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C85D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8810);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C8F80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C94D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C94E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C95A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C96D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C96E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C97A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C98E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9930);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C99E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9BA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9D80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9E80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9F00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004C9FF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CA020);

/** @brief Initialize an empty intrusive list whose sentinel links point to itself. */
LibClass178A70::LibClass178A70()
{
    unk0c = 0;
    unk00.previous = &unk00;
    unk00.next = &unk00;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CA090);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CA180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CA270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CAB20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CBA70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CBAC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CBD20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC1A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC2D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC3E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC4D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC5B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC690);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC7A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CC950);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CCA70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CCBE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CCC50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CCCA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CCCF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CCD90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CCE10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CCEE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CD010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004BD360", func_004CD2C0);
