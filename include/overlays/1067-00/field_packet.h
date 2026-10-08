#ifndef SO3_OVERLAYS_1067_00_FIELD_PACKET_H
#define SO3_OVERLAYS_1067_00_FIELD_PACKET_H

#include "types.h"
#include "main/resident_0011EE70.h"

#ifdef __cplusplus
/** GS packet buffer with vtable D_1525F0 in main data; its data comes before the vptr. */
class FieldClass1525F0 : public ResidentPacket
{
public:
    /** @brief Release the packet storage unless it is borrowed. */
    virtual ~FieldClass1525F0();
};
#endif

#endif
