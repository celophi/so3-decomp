#ifndef SO3_OVERLAYS_CCONFIG_CONFIG_CONTROLLER_H
#define SO3_OVERLAYS_CCONFIG_CONFIG_CONTROLLER_H

#include "types.h"
#include "overlays/1067-00/text_001E1590.h"

/** Configuration menu controller. Partial: its overrides are still written as free functions. */
class ConfigController : public FieldClass153E30
{
    public:
        /** @brief Initialize the Field receiver base and clear the controller state. */
        ConfigController();

        /** @brief Destroy the controller and its Field receiver base. */
        virtual ~ConfigController();

        u32 resource;
        u8 unk38;
        u8 unk39[7];
        u32 unk40;
};

#endif
