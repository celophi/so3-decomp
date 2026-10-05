#ifndef SO3_OVERLAYS_LIB_TEXT_0044ABE0_H
#define SO3_OVERLAYS_LIB_TEXT_0044ABE0_H

#include "types.h"

typedef struct LibDrawState64 LibDrawState64;
#ifdef __cplusplus
extern "C" {
#endif
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

#endif
