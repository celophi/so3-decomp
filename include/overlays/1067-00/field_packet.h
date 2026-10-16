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

/** Partial packet drawer whose packet precedes its native virtual pointer. */
typedef struct FieldPacketDrawer
{
    u8 unk00[0x20];

    struct FieldClass1525F0* packet;

#ifdef __cplusplus
    /** @brief Release the drawer's packet storage. */
    virtual ~FieldPacketDrawer();
#endif
} FieldPacketDrawer;

typedef struct FieldPacketQueue FieldPacketQueue;

#ifdef __cplusplus
extern "C" {
#endif

extern FieldPacketDrawer* D_001B6618;

extern FieldPacketQueue* D_001B65DC;

#ifdef __cplusplus
}
#endif

#endif
