#ifndef SO3_OVERLAYS_LIB_MODEL_PACKET_H
#define SO3_OVERLAYS_LIB_MODEL_PACKET_H

#include "types.h"
#include "overlays/lib/model.h"
#include "overlays/lib/text_004DD440.h"

#ifdef __cplusplus
/** Screen-to-texture scale of the captured frame (LibClass174840::build_packet); model packets' texture scrolls start from it. */
extern "C" LibVector4 D_00508210[];

/** Texture offset of the captured frame (LibClass174840::build_packet); model packets' texture scrolls start from it. */
extern "C" LibVector4 D_00508220[];

/** Partial view of the model's draw packet at unk220, written through the uncached accelerated segment. */
typedef struct LibModelPacketHeader
{
    u8 unk00[0x20];
    unsigned __int128 light_matrix[4];
    LibMatrix44Value light_transposed;
    unsigned __int128 transform[4];
    unsigned __int128 color;
    s32 white;
    s32 unkf4;
    s32 unkf8;
    s32 light_mode;
    u8 unk100[4];
    s32 unk104;
    u8 unk108[4];
    s32 unk10c;
    u8 unk110[8];
    float unk118;
    s32 unk11c;
    u64 unk120;
    u8 unk128[8];
    u64 test;
    u8 unk138[8];
    unsigned __int128 ambient;
    unsigned __int128 unk150[3];
    LibMatrix44Value unk180;
    unsigned __int128 unk1c0;
    unsigned __int128 unk1d0[8];
    s32 unk250;
    s32 unk254;
    u8 unk258[8];
    unsigned __int128 unk260;
    unsigned __int128 unk270;
    unsigned __int128 unk280;
    u8 unk290[0xC];
    s32 unk29c;
    u8 unk2a0[8];
    s32 unk2a8;
} LibModelPacketHeader;

/**
 * @brief Return the camera's TEST register value with the model's destination alpha test applied.
 * @param model Model.
 * @param camera Camera.
 * @return TEST register value.
 */
static inline u32 lib_model_test_register(const LibColorModel* model, const LibCamera* camera)
{
    u32 test = camera->test;
    u32 date = model->unk59c != 0 ? 0x4000 : 0;
    u32 datm = model->unk59c == 2 ? 0x8000 : 0;

    return datm | (date | (test & ~0xC000));
}
#endif

#endif
