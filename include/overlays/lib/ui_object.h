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
typedef struct LibClass178600 LibClass178600;
#ifdef __cplusplus
/** Partial 0x40-byte widget base, with MAIN vtable D_178600. */
struct LibClass178600 : public LibClass171EA0
{
    /** @brief Initialize the widget rectangle and state bytes. */
    LibClass178600();
    /** @brief Destroy the widget. */
    virtual ~LibClass178600();
    /** @brief Delete the widget through its virtual destructor. */
    virtual void func_003EF740();
    /** @brief Virtual widget slot at 0x1C; its base implementation does no work. */
    virtual void func_00413D20();
    /** @brief Virtual widget slot at 0x20; its base implementation does no work. */
    virtual void func_00462310();
    u8 unk04[0x14];
    LibUiRect16 unk18;
    float unk28;
    u8 unk2c[8];
    u32 unk34;
    u8 unk38;
    u8 unk39;
    u8 unk3a;
    u8 unk3b;
    u8 unk3c;
    u8 unk3d;
    u8 unk3e;
    u8 unk3f;
};
#endif
#endif
