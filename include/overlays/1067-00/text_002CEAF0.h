#ifndef SO3_OVERLAYS_1067_00_TEXT_002CEAF0_H
#define SO3_OVERLAYS_1067_00_TEXT_002CEAF0_H

#include "types.h"

/** Runtime window directory containing a deferred-removal list. */
typedef struct FieldWindowRemovalContext FieldWindowRemovalContext;
#ifdef __cplusplus
class FieldClass15AE70;
#else
typedef struct FieldClass15AE70 FieldClass15AE70;
#endif

/** Partial receiver containing 64 allocations and three aligned buffer slots. */
typedef struct FieldBufferSlots
{
    u8 unk00[0x14];
    void* unk14[64];
    void* unk114;
    s32 unk118;
    void* unk11c[3];
    void* unk128[3];
    s32 unk134[3];
    u8 unk140;
} FieldBufferSlots;

/** Partial header of a resource record linked by a byte offset. */
typedef struct FieldResourceRecord
{
    u8 unk00[8];
    u32 unk08;
    u32 next_offset;
} FieldResourceRecord;

typedef struct FieldD1440Object FieldD1440Object;

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Queue a non-null window for removal by the runtime update.
 * @param context Runtime window directory.
 * @param window Window to remove after the current update.
 */
void field_queue_window_removal(FieldWindowRemovalContext* context, FieldClass15AE70* window);

#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 3.
 */
s32 func_002CFE00(FieldClass150070* object);
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 4.
 */
s32 func_002D3BB0(FieldClass150070* object);
#endif

/**
 * @brief Store a byte and flags on an object, then update its 0x88 byte from flag bit 3.
 * @param object Object to update.
 * @param value Byte to store at offset 0x18.
 * @param flags Flags to store at offset 0x1A.
 * @return Always 1.
 */
s32 func_002D1440(FieldD1440Object* object, u8 value, u32 flags);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct ResidentContextObject64;

/** Release the receiver's retained objects and reset its state. */
void func_002D2170(struct ResidentContextObject64* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"

/** Retained field attachment with a context callback. */
class FieldClass15B0E0 : public FieldClass150070, public FieldClass1DD400
{
public:
    static void* operator new(u32 size);

    /** @brief Release storage through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);

    FieldClass15B0E0();

    virtual ~FieldClass15B0E0();

    u8 unk18[0x40];
};
#endif

#endif
