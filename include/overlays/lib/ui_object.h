#ifndef SO3_LIB_UI_OBJECT_H
#define SO3_LIB_UI_OBJECT_H
#include "types.h"
#include "overlays/lib/text_003E68C0.h"
/** Four ordinary scalar components of a widget rectangle. */
typedef struct LibUiRect16
{
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
} LibUiRect16;
typedef struct LibWidget LibWidget;
#ifdef __cplusplus
struct LibContainer;
/** Partial 0x40-byte widget base, with MAIN vtable D_178600. */
struct LibWidget : public LibListObject
{
    /** @brief Initialize the widget rectangle and state bytes. */
    LibWidget();
    /** @brief Destroy the widget. */
    virtual ~LibWidget();
    /** @brief Delete the widget through its virtual destructor. */
    virtual void destroy();
    /** @brief Virtual widget slot at 0x1C; its base implementation does no work. */
    virtual void func_00413D20();
    /** @brief Draw the widget; the base implementation does no work. */
    virtual void draw();
    LibContainer* container;
    LibUiRect16 unk18;
    float draw_alpha;

    /** Start of the widget's drawing packet. */
    u64* packet;

    /** DMA tag that ends the drawing packet. */
    u64* packet_tag;

    u32 unk34;
    u8 unk38;
    u8 unk39;
    u8 unk3a;
    u8 unk3b;
    /** Nonzero when the widget needs redrawing. */
    u8 needs_redraw;

    u8 unk3d;
    u8 unk3e;
    u8 visible;
};
#endif
#endif
