#ifndef SO3_OVERLAYS_CCONFIG_CONFIG_CONTROLLER_H
#define SO3_OVERLAYS_CCONFIG_CONFIG_CONTROLLER_H

#include "types.h"
#include "overlays/1067-00/text_001E1590.h"

struct ConfigFrameWindow;
struct ConfigPreviewWindow;

/** Configuration menu controller. Partial: its overrides are still written as free functions. */
class ConfigController : public FieldClass153E30
{
    public:
        /** @brief Initialize the Field receiver base and clear the controller state. */
        ConfigController();

        /** @brief Create and register the configuration windows. @return One after creation. */
        virtual s32 init_windows();

        /** @brief Destroy the controller and its Field receiver base. */
        virtual ~ConfigController();

        u32 resource;

        /** Set once init_windows has registered the windows. */
        u8 ready;

        u8 unk39[3];
        ConfigFrameWindow* frame_window;
        ConfigPreviewWindow* preview_window;
};

#endif
