#ifndef SO3_MAIN_RESIDENT_DATA_H
#define SO3_MAIN_RESIDENT_DATA_H

#include "main/resident_001001E0.h"
#include "main/resident_00101550.h"
#include "main/resident_0010A0E0.h"
#include "main/item_category.h"

typedef struct FieldRuntime FieldRuntime;

struct FieldClass150F90;

struct FieldClass150C10;

/** Partial resident resource storage containing the category entries. */
typedef struct ResidentObject1B64F8
{
    u8 unk00[0xEA60];
    ItemCreationCategoryRecord item_types[750];
} ResidentObject1B64F8;
/** Partial view of the section selected by resource key four. */
typedef struct ResidentHudSection1B4
{
    u8 unk00[0x1B0];
    u32 unk1b0;
} ResidentHudSection1B4;

/** Partial object at offset 0x8 of the field context. */
typedef struct ResidentContext08
{
    u8 unk00[0x60];
    /** Unidentified flags; bit zero blocks the registered field-object list update. */
    u8 unk60;
    u8 unk61[0x57];
    s32 unkb8;
    u8 unkbc[0x20];
    /** Selected field object from the context's object array. */
    struct FieldClass150F90* current_object;
    u8 unke0[0x15];
    u8 unkf5_0_2 : 3;
    u8 unkf5_3 : 1;
    u8 unkf5_4 : 1;
    u8 unkf5_5 : 1;
    u8 unkf5_6_7 : 2;
} ResidentContext08;

/** Partial attached receiver reached through the field context at offset 0x44. */
typedef struct ResidentContextObject52
{
    u8 unk00[0x34];
    u32 unk34;
    u32 unk38;
    u32 unk3c;
    u32 unk40;
    u8 unk44[0xE];
    u8 unk52_0 : 1;
    u8 unk52_1_7 : 7;
} ResidentContextObject52;

/** Partial resident object reached through D_001B65E4. */
typedef struct ResidentObject1B65E4
{
    u8 unk00[0x12183];
    u8 unk12183;
} ResidentObject1B65E4;

/** Partial object at offset 0x38 of the field context. */
typedef struct ResidentContextObject38
{
    u8 unk00[0x4C8];
    u8 unk4c8_0 : 1;
    u8 unk4c8_1_7 : 7;
    u8 unk4c9[0x103];
    void* unk5cc;
    void* unk5d0;
} ResidentContextObject38;

/** Flag byte at field context offset 0xDD (a separate member: functions testing two of its bits keep its address). */
typedef struct ResidentContextFlagsDD
{
    u8 unk0 : 1;
    u8 unk1 : 1;
    u8 unk2 : 1;
    u8 time_step_hold_active : 1;
    u8 unk4 : 1;
    u8 unk5 : 1;
    u8 unk6 : 1;
    u8 unk7 : 1;
} ResidentContextFlagsDD;

/** Partial polymorphic object attached to the field context. */
typedef struct ResidentContextAttachment
{
    void* vtable;
    u8 unk04[0x11];
    u8 unk15;
    u8 unk16[0x1E];
    u8 unk34;
} ResidentContextAttachment;

/** Partial object at field context offset 0x58. */
typedef struct ResidentContextObject58
{
    u8 unk00[0x1B4];
    s32 unk1b4;
    u8 unk1b8[4];
    s32 unk1bc;
    u8 unk1c0[8];
    ResidentContextAttachment* unk1c8;
    u8 unk1cc[0x14];
    float unk1e0;
    s32 unk1e4;
    u8 unk1e8[2];
    u8 unk1ea_0_3 : 4;
    u8 unk1ea_4 : 1;
    u8 unk1ea_5_7 : 3;
} ResidentContextObject58;

/** Partial object at field context offset 0x64. */
typedef struct ResidentContextObject64
{
    u8 unk00[0x48];
    void* unk48;
} ResidentContextObject64;

/** Partial input state exposing its unsigned control mask. */
typedef struct ResidentContextInput10
{
    u8 unk00[0x24];
    u16 mask;
} ResidentContextInput10;

/** Partial field context reached through D_001B6430. */
typedef struct ResidentContext
{
    u8 unk00[4];
    void* unk04;
    ResidentContext08* unk08;
    struct LibDisplayState* unk0c;
    ResidentContextInput10* input;
    void* unk14;
    void* unk18;
    void* unk1c;
    void* unk20;
    void* unk24;
    void* unk28;
    struct FieldResourceList14* unk2c;
    void* unk30;
    void* unk34;
    ResidentContextObject38* unk38;
    void* unk3c;
    void* unk40;
    ResidentContextObject52* unk44;
    struct LibClass171EA0* unk48;
    struct FieldClass154CC0* unk4c;

    /** Node that rebuilds drawing commands while display blending is active. */
    struct FieldDisplayBlendNode* display_blend_node;

    struct FieldListObject* unk54;
    ResidentContextObject58* unk58;
    void* unk5c;

    /** Slot owner whose objects can be detached and registered again. */
    struct FieldObjectSlotOwner* object_slots;

    ResidentContextObject64* unk64;
    struct FieldClass1502A0* unk68;
    void* unk6c;
    void* unk70;
    struct ResidentHeap* unk74;
    struct ResidentHeap* unk78;
    void* unk7c;
    void* unk80;

    /** Optional receiver updated by the field loop. */
    struct FieldClass150C10* update_callback;

    /** Render iteration passed to the display-buffer functions. */
    s32 render_count;

    /** Display field returned by the resident synchronization functions. */
    u32 display_field;

    /** Number of completed object-list updates. */
    s32 update_count;

    /** Integer interval used when waiting for the next field update. */
    s32 time_step_level;

    /** Unscaled increment retained when the update argument is nonpositive. */
    float time_step;

    /** Remaining updates before the current time-step level can reset. */
    float time_step_hold;

    float unkA0;

    /** Multiplier applied to the retained time step. */
    float time_scale;

    s16 unka8;
    s16 unkaa;
    u8 unkac[4];
    s16 unkb0;
    s16 unkb2;
    u8 unkb4[0x1C];
    u32 unkd0;
    u32 unkd4;

    /** Remaining updates that skip the normal interval wait. */
    s32 wait_skip_count;

    s8 unkdc;
    ResidentContextFlagsDD unkdd;
    u8 exit_requested : 1;
    u8 unkde_1 : 1;
    u8 unkde_2 : 1;
    u8 unkde_3 : 1;
    u8 unkde_4 : 1;
    u8 unkde_5 : 1;
    u8 skip_render : 1;
    u8 unkde_7 : 1;
    u8 unkdf_0 : 1;
    u8 unkdf_1 : 1;
    u8 unkdf_2 : 1;
    u8 unkdf_3_7 : 5;
} ResidentContext;

/** Partial resident record containing condition masks and checked Fol. */
typedef struct ResidentCheckedRecord
{
    u16 unk00;
    u16 unk02;
    u16 unk04;
    u16 unk06;
    u8 unk08[0x1D];
    u8 unk25_0_3 : 4;
    u8 unk25_4_5 : 2;
    u8 unk25_6_7 : 2;
    u8 unk26[0xE];
    /** Fol XOR-encoded with 0x7CE3C7F7. */
    u32 encoded_fol;
    u8 unk38[0x6C];
    /** Checksum of the 126 bytes beginning at offset 0x26. */
    u16 checksum;
    /** Random seed used to calculate the checksum. */
    u16 checksum_seed;
} ResidentCheckedRecord;

/** Partial holder of the current field context and its condition masks. */
typedef struct ResidentContextRef
{
    ResidentContext* context;
    ResidentCheckedRecord* unk04;
} ResidentContextRef;

#ifdef __cplusplus
extern "C" {
#endif

extern const ResidentDispatchTable D_159070;
extern ResidentObject1B65E4* D_001B65E4;
extern ResidentResourceQueue* D_001B65E8;
/** Resident input root supplying per-slot samples and retained flags. */
extern struct BootInputRoot9670* D_001B65F0;
extern ResidentReleaseQueues* D_001B65F4;
extern ResidentRequest112400* D_001B65F8;
extern ResidentContextRef* D_001B6430;
extern FieldRuntime* D_001B657C;
extern u8 D_001B6448;
extern void* D_001B644C;
extern void* D_001B6450;
extern void* D_001B6458;
extern void* D_001B661C;
extern void* D_001B6684;
extern float D_001B6688;
extern float D_001B6690;

extern u8 D_001B6420;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * @brief Report whether record processing must wait for the resident objects.
 *
 * Shared by FieldResourcePreloader::advance_requests and its FieldBattleResourcePreloader override.
 * @return True when the byte at offset 0x12183 of D_001B65E4 is set,
 *         resident_update_resource_queue(D_001B65E8) reports pending cancellation, or
 *         the byte at offset 0x30
 *         of D_001B65E8 is set.
 */
static inline bool field_records_blocked()
{
    if (D_001B65E4->unk12183 || resident_update_resource_queue(D_001B65E8) || D_001B65E8->unk30)
    {
        return true;
    }
    return false;
}
#endif

#endif
