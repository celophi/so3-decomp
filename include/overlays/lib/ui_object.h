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

    /**
     * @brief Set the widget rectangle and mark it for redraw.
     * @param x Left edge.
     * @param y Top edge.
     * @param width Rectangle width.
     * @param height Rectangle height.
     */
    void set_rect(float x, float y, float width, float height)
    {
        unk18.unk00 = x;
        unk18.unk04 = y;
        unk18.unk08 = width;
        unk18.unk0c = height;
        needs_redraw = 1;
    }

    LibContainer* container;
    LibUiRect16 unk18;
    float draw_alpha;
    u64* packet;
    u64* packet_tag;
    u32 unk34;
    u8 unk38;
    u8 unk39;
    u8 unk3a;
    u8 unk3b;
    u8 needs_redraw;
    u8 unk3d;
    u8 unk3e;
    u8 visible;
};
#endif
#endif
