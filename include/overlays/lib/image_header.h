#ifndef SO3_OVERLAYS_LIB_IMAGE_HEADER_H
#define SO3_OVERLAYS_LIB_IMAGE_HEADER_H

#include "types.h"

#define LIB_IMAGE_SWIZZLED 0x2000

/** Header of a FIS image; the image block sits image_offset bytes after it. */
struct LibImageHeader
{
    u16 flags;
    u16 unk02;
    char name[4];
    s32 id;
    u32 image_offset;
    s32 palette_size;
    u32 palette_offset;
    u16 palette_format;
};

/** GS transfer packet in front of an image's palette, with the colours after it. */
struct LibImagePalette
{
    u8 unk00[0x20];
    u64 bitbltbuf;
    u8 unk28[0x18];
    u64 trxreg;
    u8 unk48[0x38];
    u32 colors[1];
};

/** Block of a FIS image that holds its size; the width and height are powers of two. */
struct LibImageInfo
{
    u16 width;
    u16 height;
    u32 data_size;
    u32 pixel_offset;
    u16 texture_code;
    u8 width_log2;
    u8 height_log2;
};

#endif
