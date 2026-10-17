#ifndef SO3_OVERLAYS_LIB_PALETTE_BLEND_CHANNEL_H
#define SO3_OVERLAYS_LIB_PALETTE_BLEND_CHANNEL_H

#include "overlays/lib/render_channel.h"
#include "overlays/lib/text_003E68C0.h"

class LibResourceBuffer;
struct LibImageDataHeader;

/** Channel that blends selected palette entries between two borrowed RGBA arrays. */
class LibPaletteBlendChannel : public LibRenderChannel
{
public:
    /** @brief Flush the data cache and initialize an empty palette blend. */
    LibPaletteBlendChannel();

    /** @brief Destroy the channel; its palette, source colors and indices are borrowed. */
    virtual ~LibPaletteBlendChannel();

    /**
     * @brief Blend the selected palette entries using the stored weight.
     *
     * Components are truncated to integers and packed into bytes without clamping.
     */
    virtual void update();

    /**
     * @brief Bind the selected image from the source resource.
     *
     * A nonempty record list with no matching selector reports success and keeps
     * the previous target. Failed lookups also leave that target unchanged.
     * @return False for a missing resource, empty record list or unsupported matching storage kind; true otherwise.
     */
    bool load_resource();

    const LibVector4* start_colors;

    const LibVector4* end_colors;

    const u8* palette_indices;

    LibImageDataHeader* target;

    LibResourceBuffer* resource;

    /** Weight of end_colors; start_colors uses 1 - blend. */
    float blend;

    s16 entry_count;
};

#endif
