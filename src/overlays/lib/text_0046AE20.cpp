#include "include_asm.h"
#include "overlays/lib/height_grid.h"
#include "main/resident_data.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_0013CD50.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/scene.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/text_0043A920.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/model.h"
#include "overlays/lib/image_model.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/model_entries.h"
#include "overlays/lib/scene_objects.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_0043BD00.h"
#include "main/object_list.h"


typedef struct HalfwordSetterOwnertext_0046AE20
{
    u8 unk00[0x6C];
    u16 unk6c;
} HalfwordSetterOwnertext_0046AE20;



typedef struct ByteGetterOwnertext_0046AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e[0x8];
    u8 unk56;
} ByteGetterOwnertext_0046AE20;



typedef struct ByteSetterOwnertext_0046AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u8 unk50[0x4];
    u8 unk54;
    u8 unk55;
    u8 unk56;
} ByteSetterOwnertext_0046AE20;



typedef struct WordSetterOwnertext_0046AE20
{
    u8 unk00[0x48];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x5C];
    u32 unkb0;
    u32 unkb4;
    u32 unkb8;
    u32 unkbc;
} WordSetterOwnertext_0046AE20;



typedef struct WordGetterOwnertext_0046AE20
{
    u8 unk00[0x8];
    u32 unk08;
    u32 unk0c;
    u8 unk10[0x38];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x5C];
    u32 unkb0;
    u32 unkb4;
    u32 unkb8;
    u32 unkbc;
} WordGetterOwnertext_0046AE20;

typedef struct LibFlagState59C
{
    u8 unk00[0x59C];
    u8 unk59c;
    u8 unk59d_0 : 1;
    u8 unk59d_1_7 : 7;
} LibFlagState59C;


typedef struct LibFloatFieldOwner0046AE20
{
    u8 unk00[0x28];
    float unk28;
    u8 unk2c[4];
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
} LibFloatFieldOwner0046AE20;

/** Partial metadata used to filter and name resource entries. */
struct LibEntryMetadata
{
    u16 unk00;
    u16 data_offset;
    s32 link;
    s32 data_position;
    s16 child_count;
    u8 state;
    u8 kind;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u32 flags;
    float unk20;
    float orientation[4];
    float translation[3];
    float unk40;
    float scale[3];
    u8 unk50[4];
    float offset_rotation[4];
    float offset_translation[3];
    u8 unk70[4];
    float offset_scale[3];
    u8 unk80[4];
    s32 name_checksum;
    u32 layer_mask;
    u8 unk8c;
    u8 unk8d;
    u8 unk8e;
    u8 unk8f;
    u8 unk90;
    u8 unk91;
    u8 unk92;
    u8 unk93;
    float unk94;
    float unk98[4];
    float unka8[3];
    float unkb4;
    float unkb8;
};

/** Partial inherited transform state shared by the setter's callers. */
typedef struct LibTransformByteState
{
    u8 unk00[0x50];
    u8 transform_dirty;
} LibTransformByteState;

/** Partial receiver with its halfword flags at 0x6A. */
typedef struct LibObjectFlags6A
{
    u8 unk00[0x6A];
    u16 flags;
} LibObjectFlags6A;


typedef struct ByteSourceStateOwnertext_0046AE20 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; const u8* sourceA0; u32 valueA4; } ByteSourceStateOwnertext_0046AE20;
typedef struct TwoWordClearArgStateOwnertext_0046AE20 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; void* unkA0; void* unkA4; } TwoWordClearArgStateOwnertext_0046AE20;
typedef struct FourQuadwordCopyTargetOwnertext_0046AE20
{
    u8 pad00[0x2C];
    u32 unk2C;
    u8 pad30[0x30];
    unsigned __int128 values60[4];
} FourQuadwordCopyTargetOwnertext_0046AE20;
typedef struct FourQuadwordCopySourceOwnertext_0046AE20
{
    u8 pad00[0x150];
    unsigned __int128 values150[4];
} FourQuadwordCopySourceOwnertext_0046AE20;

/** Partial receiver with a byte counter at 0x790. */
typedef struct LibByte790Counter
{
    u8 unk00[0x790];
    u8 unk790;
} LibByte790Counter;

/** Four aligned floats; the C view of a Lib vector. */
typedef struct LibFloat4
{
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) LibFloat4;

/** Partial grid emitter with vtable D_175DE0 in main data; slot 0x18 is still pure here. */
class LibClass175DE0 : public LibClass1774E0
{
public:
    /** @brief Start emitting with unit scale, one particle per emission and no emitters. */
    LibClass175DE0()
    {
        unk38 = 1.0f;
        unk44 = 0;
        primary_emitter = 0;
        emission_kind = 0;
        unk4d = 0;
        primary_emission_count = 1;
        secondary_emitter = 0;
        secondary_emission_count = 1;
        unk56 = 0;
        skip_frame_playback = 0;
        unk04 = 1;
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass175DE0()
    {
    }

    virtual void func_slot0C();

    virtual void func_slot20();

    virtual void func_slot28();

    virtual void func_slot2C();

    virtual void func_slot40();

    virtual void func_slot44();

    virtual void func_slot48();

    virtual void func_slot4C(float value);

    virtual void func_slot50();

    virtual void func_slot54();

    virtual void func_slot5C(u8 mode);

    virtual void func_slot60();

    virtual void func_slot64(float value);

    virtual void func_slot68(u8 value);

    virtual void func_slot6C();

    virtual void func_slot70(float value);

    virtual void func_slot74();

    virtual void func_slot78(float value);

    virtual void func_slot7C(u32 value);

    virtual void func_slot80();

    virtual void func_slot84(u8 value);

    virtual void func_slot88(u8 flags);

    virtual void func_slot8C(u32 value);

    virtual void func_slot90();

    virtual void func_slot94(u8 value);

    virtual void func_slot98(float value);

    virtual void func_slot9C(float value);

    virtual void func_slotA0(u8 flags);

    virtual void func_slotA4();

    virtual void func_slotA8();

    virtual void func_slotAC();

    virtual void func_slotB0();

    virtual void func_slotB8();

    virtual void func_slotBC();

    float unk28;
    s32 index;
    float emission_value;
    float unk34;
    float unk38;
    float unk3c;
    float secondary_emission_scale;
    s32 unk44;
    LibClass173990* primary_emitter;
    u8 emission_kind;
    u8 unk4d;
    u8 primary_emission_flags;
    u8 primary_emission_count;
    LibClass173990* secondary_emitter;
    u8 secondary_emission_flags;
    u8 secondary_emission_count;
    u8 unk56;
    u8 skip_frame_playback;
    u8 unk58[0x58];

    /**
     * @brief Set how the grid emits and the value that goes with it.
     * @param kind Emission kind.
     * @param value Emission value.
     */
    void set_emission(u8 kind, float value)
    {
        emission_kind = kind;
        emission_value = value;
    }
};

/** Partial grid with vtable D_175760 in main data. */
class LibClass175760 : public LibClass175DE0
{
public:
    /** @brief Start without either buffer. */
    LibClass175760()
    {
        unkb0 = 0;
        unkb4 = 0;
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass175760()
    {
    }

    virtual void func_slot18();

    void* unkb0;
    void* unkb4;
    u8 unkb8[8];
};

/** Partial grid with vtable D_175D10 in main data. */
class LibClass175D10 : public LibClass175DE0
{
public:
    LibClass175D10()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass175D10()
    {
    }

    virtual void func_slot18();
};

/** Partial grid emitter with vtable D_176050 in main data; slot 0x18 is still pure here. */
class LibClass176050 : public LibClass177410
{
public:
    /** @brief Start emitting with unit scale, one particle per emission and no emitters. */
    LibClass176050()
    {
        unk38 = 1.0f;
        unk44 = 0;
        primary_emitter = 0;
        emission_kind = 0;
        unk4d = 0;
        primary_emission_count = 1;
        secondary_emitter = 0;
        secondary_emission_count = 1;
        unk56 = 0;
        skip_frame_playback = 0;
        unk04 = 1;
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176050()
    {
    }

    virtual void func_slot0C();

    virtual void func_slot20();

    virtual void func_slot28();

    virtual void func_slot2C();

    virtual void func_slot40();

    virtual void func_slot44();

    virtual void func_slot48();

    virtual void func_slot4C(float value);

    virtual void func_slot50();

    virtual void func_slot54();

    virtual void func_slot5C(u8 mode);

    virtual void func_slot60();

    virtual void func_slot64(float value);

    virtual void func_slot68(u8 value);

    virtual void func_slot6C();

    virtual void func_slot70(float value);

    virtual void func_slot74();

    virtual void func_slot78(float value);

    virtual void func_slot7C(u32 value);

    virtual void func_slot80();

    virtual void func_slot84(u8 value);

    virtual void func_slot88(u8 flags);

    virtual void func_slot8C(u32 value);

    virtual void func_slot90();

    virtual void func_slot94(u8 value);

    virtual void func_slot98(float value);

    virtual void func_slot9C(float value);

    virtual void func_slotA0(u8 flags);

    virtual void func_slotA4();

    virtual void func_slotA8();

    virtual void func_slotAC();

    virtual void func_slotB0();

    virtual void func_slotB8();

    virtual void func_slotBC();

    float unk28;
    s32 index;
    float emission_value;
    float unk34;
    float unk38;
    float unk3c;
    float secondary_emission_scale;
    s32 unk44;
    LibClass173990* primary_emitter;
    u8 emission_kind;
    u8 unk4d;
    u8 primary_emission_flags;
    u8 primary_emission_count;
    LibClass173990* secondary_emitter;
    u8 secondary_emission_flags;
    u8 secondary_emission_count;
    u8 unk56;
    u8 skip_frame_playback;
    u8 unk58[0x58];

    /**
     * @brief Set how the grid emits and the value that goes with it.
     * @param kind Emission kind.
     * @param value Emission value.
     */
    void set_emission(u8 kind, float value)
    {
        emission_kind = kind;
        emission_value = value;
    }
};

/** Partial grid with vtable D_175900 in main data. */
class LibClass175900 : public LibClass176050
{
public:
    /** @brief Start without either buffer. */
    LibClass175900()
    {
        unkb0 = 0;
        unkb4 = 0;
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass175900()
    {
    }

    virtual void func_slot18();

    void* unkb0;
    void* unkb4;
    u8 unkb8[8];
};

/** Partial grid with vtable D_175F80 in main data. */
class LibClass175F80 : public LibClass176050
{
public:
    LibClass175F80()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass175F80()
    {
    }

    virtual void func_slot18();
};

/** Partial grid emitter with vtable D_175B70 in main data; slot 0x18 is still pure here. */
class LibClass175B70 : public LibClass1775B0
{
public:
    /** @brief Start emitting with unit scale, one particle per emission and no emitters. */
    LibClass175B70()
    {
        unk38 = 1.0f;
        unk44 = 0;
        primary_emitter = 0;
        emission_kind = 0;
        unk4d = 0;
        primary_emission_count = 1;
        secondary_emitter = 0;
        secondary_emission_count = 1;
        unk56 = 0;
        skip_frame_playback = 0;
        unk04 = 1;
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass175B70()
    {
    }

    virtual void func_slot0C();

    virtual void func_slot20();

    virtual void func_slot28();

    virtual void func_slot2C();

    virtual void func_slot40();

    virtual void func_slot44();

    virtual void func_slot48();

    virtual void func_slot4C(float value);

    virtual void func_slot50();

    virtual void func_slot54();

    virtual void func_slot5C(u8 mode);

    virtual void func_slot60();

    virtual void func_slot64(float value);

    virtual void func_slot68(u8 value);

    virtual void func_slot6C();

    virtual void func_slot70(float value);

    virtual void func_slot74();

    virtual void func_slot78(float value);

    virtual void func_slot7C(u32 value);

    virtual void func_slot80();

    virtual void func_slot84(u8 value);

    virtual void func_slot88(u8 flags);

    virtual void func_slot8C(u32 value);

    virtual void func_slot90();

    virtual void func_slot94(u8 value);

    virtual void func_slot98(float value);

    virtual void func_slot9C(float value);

    virtual void func_slotA0(u8 flags);

    virtual void func_slotA4();

    virtual void func_slotA8();

    virtual void func_slotAC();

    virtual void func_slotB0();

    virtual void func_slotB8();

    virtual void func_slotBC();

    float unk28;
    s32 index;
    float emission_value;
    float unk34;
    float unk38;
    float unk3c;
    float secondary_emission_scale;
    s32 unk44;
    LibClass173990* primary_emitter;
    u8 emission_kind;
    u8 unk4d;
    u8 primary_emission_flags;
    u8 primary_emission_count;
    LibClass173990* secondary_emitter;
    u8 secondary_emission_flags;
    u8 secondary_emission_count;
    u8 unk56;
    u8 skip_frame_playback;
    u8 unk58[0x58];

    /**
     * @brief Set how the grid emits and the value that goes with it.
     * @param kind Emission kind.
     * @param value Emission value.
     */
    void set_emission(u8 kind, float value)
    {
        emission_kind = kind;
        emission_value = value;
    }
};

/** Partial grid with vtable D_175AA0 in main data. */
class LibClass175AA0 : public LibClass175B70
{
public:
    LibClass175AA0()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass175AA0()
    {
    }

    virtual void func_slot18();
};

/** Partial grid emitter with vtable D_1762C0 in main data; slot 0x18 is still pure here. */
class LibClass1762C0 : public LibClass177340
{
public:
    /** @brief Start emitting with unit scale, one particle per emission and no emitters. */
    LibClass1762C0()
    {
        unk38 = 1.0f;
        unk44 = 0;
        primary_emitter = 0;
        emission_kind = 0;
        unk4d = 0;
        primary_emission_count = 1;
        secondary_emitter = 0;
        secondary_emission_count = 1;
        unk56 = 0;
        skip_frame_playback = 0;
        unk04 = 1;
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass1762C0()
    {
    }

    virtual void func_slot0C();

    virtual void func_slot20();

    virtual void func_slot28();

    virtual void func_slot2C();

    virtual void func_slot40();

    virtual void func_slot44();

    virtual void func_slot48();

    virtual void func_slot4C(float value);

    virtual void func_slot50();

    virtual void func_slot54();

    virtual void func_slot5C(u8 mode);

    virtual void func_slot60();

    virtual void func_slot64(float value);

    virtual void func_slot68(u8 value);

    virtual void func_slot6C();

    virtual void func_slot70(float value);

    virtual void func_slot74();

    virtual void func_slot78(float value);

    virtual void func_slot7C(u32 value);

    virtual void func_slot80();

    virtual void func_slot84(u8 value);

    virtual void func_slot88(u8 flags);

    virtual void func_slot8C(u32 value);

    virtual void func_slot90();

    virtual void func_slot94(u8 value);

    virtual void func_slot98(float value);

    virtual void func_slot9C(float value);

    virtual void func_slotA0(u8 flags);

    virtual void func_slotA4();

    virtual void func_slotA8();

    virtual void func_slotAC();

    virtual void func_slotB0();

    virtual void func_slotB8();

    virtual void func_slotBC();

    float unk28;
    s32 index;
    float emission_value;
    float unk34;
    float unk38;
    float unk3c;
    float secondary_emission_scale;
    s32 unk44;
    LibClass173990* primary_emitter;
    u8 emission_kind;
    u8 unk4d;
    u8 primary_emission_flags;
    u8 primary_emission_count;
    LibClass173990* secondary_emitter;
    u8 secondary_emission_flags;
    u8 secondary_emission_count;
    u8 unk56;
    u8 skip_frame_playback;
    u8 unk58[0x58];

    /**
     * @brief Set how the grid emits and the value that goes with it.
     * @param kind Emission kind.
     * @param value Emission value.
     */
    void set_emission(u8 kind, float value)
    {
        emission_kind = kind;
        emission_value = value;
    }
};

/** Partial grid with vtable D_1761F0 in main data. */
class LibClass1761F0 : public LibClass1762C0
{
public:
    LibClass1761F0()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass1761F0()
    {
    }

    virtual void func_slot18();
};

/** Partial grid emitter with vtable D_176530 in main data; slot 0x18 is still pure here. */
class LibClass176530 : public LibClass177270
{
public:
    /** @brief Start emitting with unit scale, one particle per emission and no emitters. */
    LibClass176530()
    {
        unk38 = 1.0f;
        unk44 = 0;
        primary_emitter = 0;
        emission_kind = 0;
        unk4d = 0;
        primary_emission_count = 1;
        secondary_emitter = 0;
        secondary_emission_count = 1;
        unk56 = 0;
        skip_frame_playback = 0;
        unk04 = 1;
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176530()
    {
    }

    virtual void func_slot0C();

    virtual void func_slot20();

    virtual void func_slot28();

    virtual void func_slot2C();

    virtual void func_slot40();

    virtual void func_slot44();

    virtual void func_slot48();

    virtual void func_slot4C(float value);

    virtual void func_slot50();

    virtual void func_slot54();

    virtual void func_slot5C(u8 mode);

    virtual void func_slot60();

    virtual void func_slot64(float value);

    virtual void func_slot68(u8 value);

    virtual void func_slot6C();

    virtual void func_slot70(float value);

    virtual void func_slot74();

    virtual void func_slot78(float value);

    virtual void func_slot7C(u32 value);

    virtual void func_slot80();

    virtual void func_slot84(u8 value);

    virtual void func_slot88(u8 flags);

    virtual void func_slot8C(u32 value);

    virtual void func_slot90();

    virtual void func_slot94(u8 value);

    virtual void func_slot98(float value);

    virtual void func_slot9C(float value);

    virtual void func_slotA0(u8 flags);

    virtual void func_slotA4();

    virtual void func_slotA8();

    virtual void func_slotAC();

    virtual void func_slotB0();

    virtual void func_slotB8();

    virtual void func_slotBC();

    float unk28;
    s32 index;
    float emission_value;
    float unk34;
    float unk38;
    float unk3c;
    float secondary_emission_scale;
    s32 unk44;
    LibClass173990* primary_emitter;
    u8 emission_kind;
    u8 unk4d;
    u8 primary_emission_flags;
    u8 primary_emission_count;
    LibClass173990* secondary_emitter;
    u8 secondary_emission_flags;
    u8 secondary_emission_count;
    u8 unk56;
    u8 skip_frame_playback;
    u8 unk58[0x58];

    /**
     * @brief Set how the grid emits and the value that goes with it.
     * @param kind Emission kind.
     * @param value Emission value.
     */
    void set_emission(u8 kind, float value)
    {
        emission_kind = kind;
        emission_value = value;
    }
};

/** Partial grid with vtable D_176460 in main data. */
class LibClass176460 : public LibClass176530
{
public:
    LibClass176460()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176460()
    {
    }

    virtual void func_slot18();
};

/** Partial grid emitter with vtable D_176940 in main data; slot 0x18 is still pure here. */
class LibClass176940 : public LibClass1771A0
{
public:
    /** @brief Start emitting with unit scale, one particle per emission and no emitters. */
    LibClass176940()
    {
        unk38 = 1.0f;
        unk44 = 0;
        primary_emitter = 0;
        emission_kind = 0;
        unk4d = 0;
        primary_emission_count = 1;
        secondary_emitter = 0;
        secondary_emission_count = 1;
        unk56 = 0;
        skip_frame_playback = 0;
        unk04 = 1;
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176940()
    {
    }

    virtual void func_slot0C();

    virtual void func_slot20();

    virtual void func_slot28();

    virtual void func_slot2C();

    virtual void func_slot40();

    virtual void func_slot44();

    virtual void func_slot48();

    virtual void func_slot4C(float value);

    virtual void func_slot50();

    virtual void func_slot54();

    virtual void func_slot5C(u8 mode);

    virtual void func_slot60();

    virtual void func_slot64(float value);

    virtual void func_slot68(u8 value);

    virtual void func_slot6C();

    virtual void func_slot70(float value);

    virtual void func_slot74();

    virtual void func_slot78(float value);

    virtual void func_slot7C(u32 value);

    virtual void func_slot80();

    virtual void func_slot84(u8 value);

    virtual void func_slot88(u8 flags);

    virtual void func_slot8C(u32 value);

    virtual void func_slot90();

    virtual void func_slot94(u8 value);

    virtual void func_slot98(float value);

    virtual void func_slot9C(float value);

    virtual void func_slotA0(u8 flags);

    virtual void func_slotA4();

    virtual void func_slotA8();

    virtual void func_slotAC();

    virtual void func_slotB0();

    virtual void func_slotB8();

    virtual void func_slotBC();

    float unk28;
    s32 index;
    float emission_value;
    float unk34;
    float unk38;
    float unk3c;
    float secondary_emission_scale;
    s32 unk44;
    LibClass173990* primary_emitter;
    u8 emission_kind;
    u8 unk4d;
    u8 primary_emission_flags;
    u8 primary_emission_count;
    LibClass173990* secondary_emitter;
    u8 secondary_emission_flags;
    u8 secondary_emission_count;
    u8 unk56;
    u8 skip_frame_playback;
    u8 unk58[0x58];

    /**
     * @brief Set how the grid emits and the value that goes with it.
     * @param kind Emission kind.
     * @param value Emission value.
     */
    void set_emission(u8 kind, float value)
    {
        emission_kind = kind;
        emission_value = value;
    }
};

/** Partial grid with vtable D_1766D0 in main data. */
class LibClass1766D0 : public LibClass176940
{
public:
    LibClass1766D0()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass1766D0()
    {
    }

    virtual void func_slot18();
};

/** Partial grid with vtable D_176870 in main data. */
class LibClass176870 : public LibClass176940
{
public:
    LibClass176870()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176870()
    {
    }

    virtual void func_slot18();
};

/** Partial grid with vtable D_176AE0 in main data. */
class LibClass176AE0 : public LibClass173DA0
{
public:
    LibClass176AE0()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176AE0()
    {
    }

    virtual void func_slot18();
};

/** Partial grid with vtable D_176C80 in main data. */
class LibClass176C80 : public LibClass173DA0
{
public:
    LibClass176C80()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176C80()
    {
    }

    virtual void func_slot18();
};

/** Partial grid emitter with vtable D_176EF0 in main data; slot 0x18 is still pure here. */
class LibClass176EF0 : public LibClass177680
{
public:
    /** @brief Start emitting with unit scale, one particle per emission and no emitters. */
    LibClass176EF0()
    {
        unk38 = 1.0f;
        unk44 = 0;
        primary_emitter = 0;
        emission_kind = 0;
        unk4d = 0;
        primary_emission_count = 1;
        secondary_emitter = 0;
        secondary_emission_count = 1;
        unk56 = 0;
        skip_frame_playback = 0;
        unk04 = 1;
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176EF0()
    {
    }

    virtual void func_slot0C();

    virtual void func_slot20();

    virtual void func_slot28();

    virtual void func_slot2C();

    virtual void func_slot40();

    virtual void func_slot44();

    virtual void func_slot48();

    virtual void func_slot4C(float value);

    virtual void func_slot50();

    virtual void func_slot54();

    virtual void func_slot5C(u8 mode);

    virtual void func_slot60();

    virtual void func_slot64(float value);

    virtual void func_slot68(u8 value);

    virtual void func_slot6C();

    virtual void func_slot70(float value);

    virtual void func_slot74();

    virtual void func_slot78(float value);

    virtual void func_slot7C(u32 value);

    virtual void func_slot80();

    virtual void func_slot84(u8 value);

    virtual void func_slot88(u8 flags);

    virtual void func_slot8C(u32 value);

    virtual void func_slot90();

    virtual void func_slot94(u8 value);

    virtual void func_slot98(float value);

    virtual void func_slot9C(float value);

    virtual void func_slotA0(u8 flags);

    virtual void func_slotA4();

    virtual void func_slotA8();

    virtual void func_slotAC();

    virtual void func_slotB0();

    virtual void func_slotB8();

    virtual void func_slotBC();

    float unk28;
    s32 index;
    float emission_value;
    float unk34;
    float unk38;
    float unk3c;
    float secondary_emission_scale;
    s32 unk44;
    LibClass173990* primary_emitter;
    u8 emission_kind;
    u8 unk4d;
    u8 primary_emission_flags;
    u8 primary_emission_count;
    LibClass173990* secondary_emitter;
    u8 secondary_emission_flags;
    u8 secondary_emission_count;
    u8 unk56;
    u8 skip_frame_playback;
    u8 unk58[0x58];

    /**
     * @brief Set how the grid emits and the value that goes with it.
     * @param kind Emission kind.
     * @param value Emission value.
     */
    void set_emission(u8 kind, float value)
    {
        emission_kind = kind;
        emission_value = value;
    }
};

/** Partial grid with vtable D_176E20 in main data. */
class LibClass176E20 : public LibClass176EF0
{
public:
    LibClass176E20()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176E20()
    {
    }

    virtual void func_slot18();
};

/** Partial grid with vtable D_1755C0 in main data. */
class LibClass1755C0 : public LibClass177090
{
public:
    LibClass1755C0()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass1755C0();

};

/** Partial grid with vtable D_175690 in main data. */
class LibClass175690 : public LibClass175760
{
public:
    LibClass175690()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass175690();
};

/** Partial grid with vtable D_175830 in main data. */
class LibClass175830 : public LibClass175900
{
public:
    LibClass175830()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass175830();
};

/** Partial grid with vtable D_1759D0 in main data. */
class LibClass1759D0 : public LibClass175AA0
{
public:
    LibClass1759D0()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass1759D0();
};

/** Partial grid with vtable D_175C40 in main data. */
class LibClass175C40 : public LibClass175D10
{
public:
    LibClass175C40()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass175C40();
};

/** Partial grid with vtable D_175EB0 in main data. */
class LibClass175EB0 : public LibClass175F80
{
public:
    LibClass175EB0()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass175EB0();
};

/** Partial grid with vtable D_176120 in main data. */
class LibClass176120 : public LibClass1761F0
{
public:
    LibClass176120()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176120();
};

/** Partial grid with vtable D_176390 in main data. */
class LibClass176390 : public LibClass176460
{
public:
    LibClass176390()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176390();
};

/** Partial grid with vtable D_176600 in main data. */
class LibClass176600 : public LibClass1766D0
{
public:
    LibClass176600()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176600();
};

/** Partial grid with vtable D_1767A0 in main data. */
class LibClass1767A0 : public LibClass176870
{
public:
    LibClass1767A0()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass1767A0();
};

/** Partial grid with vtable D_176A10 in main data. */
class LibClass176A10 : public LibClass176AE0
{
public:
    LibClass176A10()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176A10();
};

/** Partial grid with vtable D_176BB0 in main data. */
class LibClass176BB0 : public LibClass176C80
{
public:
    LibClass176BB0()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176BB0();
};

/** Partial grid with vtable D_176D50 in main data. */
class LibClass176D50 : public LibClass176E20
{
public:
    LibClass176D50()
    {
    }

    /** @brief Destroy the grid. */
    virtual ~LibClass176D50();
};

/** Partial receiver with a flag byte at 0x8D. */
typedef struct LibFlagState8D
{
    u8 unk00[0x8D];
    u8 unk8d_0 : 1;
    u8 unk8d_1 : 1;
    u8 unk8d_2_7 : 6;
} LibFlagState8D;

/** Fixed-capacity list of pointers, with vtable D_175380 in main data; its data comes before the vptr. */
class LibPointerList
{
public:
    s16 capacity;
    s16 count;
    void** items;

    /**
     * @brief Allocate room for a number of pointers.
     * @param size Capacity to allocate.
     */
    LibPointerList(s32 size);

    /** @brief Free the pointer array. */
    virtual ~LibPointerList()
    {
        delete[] items;
    }

    /**
     * @brief Append an item; a full list ignores it.
     * @param item Item to append.
     */
    virtual void append(void* item);

    /**
     * @brief Replace the pointer array with an empty one of a new capacity.
     * @param size Capacity to allocate; stays zero when allocation fails.
     */
    void reserve(s32 size)
    {
        delete[] items;
        items = new (0) void*[size];

        if (items)
        {
            capacity = size;
        }

        count = 0;
    }
};

/** Pointer list with vtable D_175360 in main data. */
class LibClass175360 : public LibPointerList
{
public:
    LibClass175360(s32 size) : LibPointerList(size)
    {
    }

    /** @brief Destroy the list. */
    virtual ~LibClass175360();

    u8 unk0c[4];
    LibClass173490Entry unk10;
    u8 unk20[0x10];
};

/** Pointer list with vtable D_175370 in main data. */
class LibClass175370 : public LibPointerList
{
public:
    LibClass175370(s32 size) : LibPointerList(size)
    {
    }

    /** @brief Destroy the list. */
    virtual ~LibClass175370();

    u8 unk0c[4];
};

/** Node of a scene's object list, with vtable D_175390 in main data. */
class LibClass175390 : public LibListSentinel
{
public:
    LibClass175390(void* owner, LibPointerList* items, s32 kind) : owner(owner), items(items), kind(kind)
    {
    }

    /** @brief Destroy the node. */
    virtual ~LibClass175390();

    void* owner;
    LibPointerList* items;
    s32 kind;
};

/** Transform with one extra vector, with vtable D_1753A0 in main data. */
class LibClass1753A0 : public LibTransform
{
public:
    LibClass1753A0()
    {
    }

    /** @brief Destroy the transform. */
    virtual ~LibClass1753A0();

    /**
     * @brief Copy the extra vector and the transform state.
     * @param source Transform to copy.
     */
    virtual void func_004713F0(const LibClass1753A0* source);

    FieldVec4A unk210;
};

/** Model placed at a target relative to a base position, with vtable D_175430 in main data. */
class LibClass175430 : public LibModel
{
public:
    /** @brief Start with the base at the origin. */
    LibClass175430()
    {
        base = FieldVec4B(0.0f, 0.0f, 0.0f, 0.0f);
    }

    /** @brief Destroy the model. */
    virtual ~LibClass175430();

    /**
     * @brief Set the target and point the translation from the base position at it.
     * @param x Target x.
     * @param y Target y.
     * @param z Target z.
     */
    virtual void set_translation(float x, float y, float z);

    /**
     * @brief Set the target and point the translation from the base position at it.
     * @param value Target; its w becomes the translation's w.
     */
    virtual void set_translation_vector(const LibVector4* value);

    /**
     * @brief Set the target and point the translation from the base position at it.
     * @param value Target; its w becomes the translation's w.
     */
    virtual void copy_translation(const LibVector4* value);

    /**
     * @brief Return the target.
     * @return Target position.
     */
    virtual FieldVec4B* func_00479100();

    /**
     * @brief Copy the base position, then build this model from another one.
     * @param links Display list the model draws through, or null.
     * @param source Model to copy.
     * @return Nonzero on success.
     */
    virtual s32 func_00471410(LibUpdateList* links, LibClass175430* source);

    FieldVec4B base;
    FieldVec4B target;
};

/** Partial fixed-capacity list of key bytes with a parallel array of vectors. */
typedef struct LibKeyedVectorList
{
    u8 unk00[0xB0];
    u8* keys;
    LibFloat4* values;
    u8 unkB8[8];
    s32 capacity;
    s32 count;
} LibKeyedVectorList;

/** Partial object an entry's link points at another manager's entry through. */
typedef struct LibLinkTarget
{
    u8 unk00[0x6C];
    u16 unk6c;
    u8 unk6e[0x19A];
    LibByte790Counter* unk208;
    u8 unk20c[0x624];
    LibByte790Counter* unk830;
    u8 unk834[4];
    LibByte790Counter* unk838;
} LibLinkTarget;

/** Partial kind-10 entry object with a linked object of its own. */
typedef struct LibLinkGroup
{
    u8 unk00[0x3E4];
    LibLinkTarget* object;
    u8 unk3e8[0xB1];
    u8 unk499_0 : 1;
    u8 unk499_1 : 1;
    u8 unk499_2_7 : 6;
} LibLinkGroup;

/** Partial transform record of a scene entry. */
typedef struct LibSceneTransformRecord
{
    u8 unk00[4];
    s32 parent;
    u8 unk08[0xC];
    u32 unk14;
    u8 unk18[0xC];
    float orientation[4];
    float translation[3];
    u8 unk40[4];
    float scale[3];
    u8 unk50[4];
    float offset_rotation[4];
    float offset_translation[3];
    u8 unk70[4];
    float offset_scale[3];
} LibSceneTransformRecord;

/** Partial kind-1/8 renderable entry object. */
typedef struct LibRenderableEntryObject
{
    u8 unk00[0xF];
    u8 unk0f;
    u8 unk10[0x594];
    u8 unk5a4[0x1F4];
    u8 unk798_0 : 1;
    u8 unk798_1 : 1;
    u8 unk798_2_7 : 6;
} LibRenderableEntryObject;

/** One 16-byte value, copied as a quadword. */
typedef struct LibQuadword
{
    unsigned __int128 value;
} LibQuadword;

extern "C"
{
    void func_0047A130(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8);

    void func_004A22C0(void* object);

    s32 func_004A9000(void* object);

    void func_0046B480(LibObject1751A0* holder, LibGridBase* reference);

    /**
     * @brief Attach a source to the emitter, set flag bit 0 of 0x499, clear 0x3F4 and count the emitter as a user.
     * @param object Emitter.
     * @param source Image model to draw from.
     */
    void func_0043ADF0(void* object, s32 value);

    void func_0043B700(void* object, void* source);

    LibRenderDataRecord* func_00448910(u32 first_key, u32 second_key);

    void lib_collect_entry_tree(LibEntryManager* manager, s32 index, LibEntryHandleCollection* collection);

    void func_0046C3F0(LibEntryManager* scene, LibTransform* object, const LibSceneTransformRecord* record);

    void func_00472570(LibEntryManager* manager, s32 check);

    void func_00472720(LibEntryManager* manager, s32 enable);

    void* func_00472C90(const LibEntryManager* manager, void* handle);

    void* func_00472DA0(const LibEntryManager* manager, void* handle);

    void* func_00473040(LibEntryManager* manager, const char* name);

    void* func_004731A0(const LibEntryManager* manager);

    void func_00473E20(LibEntryManager* manager);

    void func_00478F90(LibFlagState8D* object);

    LibFloat4* func_004790A0(LibFloat4* vector, float x, float y, float z);

    LibQuadword func_004790D0(LibQuadword* destination, const LibQuadword* source);

    LibFloat4* func_004790E0(LibFloat4* vector, float x, float y, float z, float w);

    s32 func_00479C90(const ByteSourceStateOwnertext_0046AE20* object);

    s32 func_00479D30(const ByteSourceStateOwnertext_0046AE20* object);

    void func_00479EF0(LibKeyedVectorList* list, u8 key, const LibFloat4* value);

    void func_00479F50(LibKeyedVectorList* list, u8 key, const LibFloat4* value);
}

/** @brief Destroy the list receiver and its sentinel. */
inline LibListReceiver::~LibListReceiver()
{
}

/**
 * @brief Find the index of the entry that owns a handle.
 * @param manager Runtime entry table and source resource header.
 * @param handle Entry handle to look for.
 * @return Index of the first entry with metadata whose handle matches, or -1.
 */
static inline s32 lib_find_entry_index_inline(const LibEntryManager* manager, void* handle)
{
    s32 found = -1;
    s32 index;

    for (index = 0; index < manager->header->count; index++)
    {
        if (manager->entries[index].metadata != 0 && manager->entries[index].handle == handle)
        {
            found = index;
            break;
        }
    }

    return found;
}

/**
 * @brief Test whether an entry has no source metadata.
 * @param entry Entry to test.
 * @return True when the entry has no metadata.
 */
static inline bool lib_entry_is_empty(const LibManagedEntry* entry)
{
    return !entry->metadata;
}

/**
 * @brief Locate an entry's data after its optional sixteen-byte name.
 * @param manager Manager supplying the resource format flag.
 * @param metadata Source entry metadata.
 * @return Metadata-relative entry data, skipping the name when present.
 */
static inline void* lib_get_entry_data_inline(LibEntryManager* manager, LibEntryMetadata* metadata)
{
    u8* data = (u8*)metadata + metadata->data_offset;

    if (manager->header->flags & LIB_ENTRY_HAS_NAMES)
    {
        data += 0x10;
    }

    return data;
}

/**
 * @brief Read the matrix translation into a position vector.
 * @param result Destination vector.
 * @param object Transform source.
 */
static inline void lib_get_transform_translation(FieldVec4B& result, const LibTransform& object)
{
    result.x = object.transform.m[0][3];
    result.y = object.transform.m[1][3];
    result.z = object.transform.m[2][3];
    result.w = 1.0f;
}

/**
 * @brief Subtract the xyz components of one vector from another.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 * @return The difference, with left's w.
 */
static inline FieldVec4B lib_vector_difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B value(left);
    return value.subtract(right);
}

/**
 * @brief View an aligned matrix row as a vector.
 * @param matrix Source matrix.
 * @param index Row index.
 * @return Read-only row vector.
 */
static inline const FieldVec4A& matrix_row_vector(const LibMatrix44Value& matrix, s32 index)
{
    return *(const FieldVec4A*)matrix.m[index];
}

/**
 * @brief View an aligned matrix row as a writable vector.
 * @param matrix Destination matrix.
 * @param index Row index.
 * @return Writable row vector.
 */
static inline FieldVec4A& matrix_row_vector(LibMatrix44Value& matrix, s32 index)
{
    return *(FieldVec4A*)matrix.m[index];
}

/**
 * @brief Set the translation and mark the transform dirty.
 * @param object Transform.
 * @param x Translation x.
 * @param y Translation y.
 * @param z Translation z.
 */
static inline void lib_set_translation(LibOrientedTransform* object, float x, float y, float z)
{
    object->transform_dirty = 1;
    object->translation.x = x;
    object->translation.y = y;
    object->translation.z = z;
    object->translation.w = 1.0f;
}

extern "C" LibImageRegistry* g_image_registry;

/**
 * @brief Point the model at one image of a resource's FISP chunk.
 * @param resource First chunk of the resource.
 * @param index Image index in the FISP chunk; past the count, nothing changes.
 */
void LibObject1751A0::set_image(LibResourceChunkHeader* resource, u32 index)
{
    record.data = reinterpret_cast<u8*>(resource + 1);
    LibResourceChunkHeader* chunk = resource;

    do
    {
        if (chunk->magic == LIB_IMAGE_SET_CHUNK_MAGIC)
        {
            goto found;
        }

        chunk = lib_next_chunk(chunk);
    } while (chunk != 0);

    return;

found:
    LibImageSet* set = reinterpret_cast<LibImageSet*>(chunk + 1);

    if (set->count < index)
    {
        return;
    }

    u32* offsets = set->offsets;
    image = reinterpret_cast<LibImageEntry*>(reinterpret_cast<u8*>(set) + offsets[index]);
    record.storage_kind = 0;
    record.resolved_data = 0;
    setup = image->setup;

    reset_texture_uploads();

    FlushCache(0);

    if (reference)
    {
        reference->func_slot50(image, image->pixels);
    }

    record.next_offset = 0;
    float width = static_cast<u32>(image->width);
    float height = static_cast<u32>(image->height);
    height *= height;
    width *= width;
    width += height;
    diagonal = ee_sqrt(width);
    registered = 1;
    func_004D02E0(g_image_registry, this);
}

/** @brief Size and allocate the packet buffers for the grid, and point the DMA chains at them. */
void LibObject1751A0::allocate_packets()
{
    if (reference != 0 && reference->func_slotc0())
    {
        s32 unit = reference->func_slot38();
        s32 batch = 0x30 / unit;

        switch (kind)
        {
        case 2:
        case 4:
            batch /= 2;
            break;
        case 3:
        case 5:
        case 6:
            batch = 0x12 / unit;
            break;
        }

        batch *= unit;
        delete packet;
        packet = 0;
        delete unka84[0];
        unka84[0] = 0;
        delete unka90[0];
        unka90[0] = 0;
        delete unka8c;
        unka8c = 0;
        s32 batches = (batch + unit * reference->func_slot34() - 1) / batch;
        s32 size = batches * 4 + 0x18;
        unka84[0] = new (0) u8[size * 32];
        unka84[1] = unka84[0] + size * 16;
        unka8c = new (0) u8[0x400];
        s32 qwords = (batches * 0x20u + batch * (batches * 0x30u)) / 16 + 0x12;

        if (!copied)
        {
            packet = new (0) LibImagePacket;
            unka90[0] = new (0) u8[qwords * 32];
            unka90[1] = unka90[0] + qwords * 16;
        }

        if (unka84[0] == 0 || (!copied && unka90[0] == 0) || unka8c == 0 || (!copied && packet == 0))
        {
            delete packet;
            delete unka84[0];
            delete unka90[0];
            delete unka8c;
            packet = 0;
            unka84[0] = 0;
            unka90[0] = 0;
            unka8c = 0;
            return;
        }

        if (packet)
        {
            memset_guess(packet, 0, sizeof(LibImagePacket));
        }

        chains[0].tags[0][0] = DMA_TAG(0, DMA_TAG_ID_CALL, unka8c + 0x40);
        chains[1].tags[0][0] = DMA_TAG(0, DMA_TAG_ID_CALL, unka8c + 0x40);
        chains[0].tags[1][0] = DMA_TAG(0, DMA_TAG_ID_CALL, unka84[0] + 0x40);
        chains[1].tags[1][0] = DMA_TAG(0, DMA_TAG_ID_CALL, unka84[1] + 0x40);
        chains[0].tags[2][0] = DMA_TAG_ID_END;
        chains[1].tags[2][0] = DMA_TAG_ID_END;
        FlushCache(0);
        unkadd = 0;
        next_cell = 0;
    }
}

/**
 * @brief Release the counted reference the object holds and clear it.
 * @param object Object holding the reference.
 */
void func_0046B3F0(LibObject1751A0* object)
{
    object->release_reference();
}

/**
 * @brief Hold a reference to a shared object and add to its reference count.
 * @param holder Object that keeps the reference.
 * @param reference Shared object to hold.
 */
void func_0046B480(LibObject1751A0* holder, LibGridBase* reference)
{
    holder->hold_reference(reference);
}

/** Registry of the image resources in use. */

/** @brief Let go of the shared object, unregister the image and free the buffers. */
LibObject1751A0::~LibObject1751A0()
{
    release_reference();

    if (registered)
    {
        func_004D0260(g_image_registry, this);
    }

    delete packet;
    delete unka84[0];
    delete unka90[0];
    delete unka8c;
}

/** @brief Start without an image, with an open bounding box and two texture upload records. */
LibObject1751A0::LibObject1751A0()
{
    set_type_id(0x400);
    clear_vector(&bounding_sphere);
    bounding_sphere.w = 1.0f;
    bounding_sphere.w = 10000.0f;
    set_vector(&box_min, -10000.0f, -10000.0f, -10000.0f, 0.0f);
    set_vector(&box_max, 10000.0f, 10000.0f, 10000.0f, 0.0f);
    diagonal = 1.0f;
    unkaa4 = 10.0f;
    unka98[0] = -1;
    unka98[1] = -1;
    unkae6 = 0;
    holds_reference = 0;
    reference = 0;
    unka84[0] = 0;
    unka84[1] = 0;
    unka90[0] = 0;
    unka90[1] = 0;
    packet = 0;
    unka8c = 0;
    unkade = 0;
    unkada[0] = 1;
    unkada[1] = 1;
    next_cell = 0;
    unkadf = 0;
    unkabc = 0.0f;
    unkac0 = 1.0f;
    unkae0 = 0;
    image = 0;
    unkae4 = 0;
    registered = 0;
    unkacc = 0;
    user_count = 0;
    phase = 0;
    phase_period = 0;
    unkaa8 = 10.0f;

    s32 i = 0;
    LibVector4* row = draw_packet.unk20.rows;

    do
    {
        set_vector(&row[i], 1e-10f, 1e-10f, 1e-10f, 1e-10f);
    } while (++i < 4);

    unkae3 = 0;
    unkac8 = 0;
    unkaac = 0;
    copied = 0;
    source = 0;
    FlushCache(0);
}

/** @brief Destroy the look-at transform and its transform base. */
LibLookAtTransform::~LibLookAtTransform()
{
}

/**
 * @brief Copy the look-at target and inherited transform state.
 * @param source Transform to copy; its roll angle is not copied.
 */
void LibLookAtTransform::copy_look_at_state(const LibLookAtTransform* source)
{
    look_at_target = source->look_at_target;
    LibTransform::copy_offset_transform_state(source);
}

/** @brief Update the matrix to face the target when one is attached. */
void LibLookAtTransform::update_transform_matrix()
{
    if (look_at_target)
    {
        if (!look_at_target->matrix_ready)
        {
            look_at_target->update_transform_matrix();
        }

        LibTransform::update_transform_matrix();
        matrix_ready = 0;

        FieldVec4B direction;
        FieldVec4B position;
        LibMatrix44Value matrix;
        lib_get_transform_translation(direction, *look_at_target);
        lib_get_transform_translation(position, *this);
        direction = lib_vector_difference(direction, position);
        lib_matrix_look_at(&matrix, &position, &direction, roll_angle);
        matrix.m[0][3] = position.x;
        matrix.m[1][3] = position.y;
        matrix.m[2][3] = position.z;
        matrix_row_vector(transform, 0) = matrix_row_vector(matrix, 0);
        matrix_row_vector(transform, 1) = matrix_row_vector(matrix, 1);
        matrix_row_vector(transform, 2) = matrix_row_vector(matrix, 2);
        matrix_row_vector(transform, 3) = matrix_row_vector(matrix, 3);
    }
    else
    {
        LibTransform::update_transform_matrix();
    }
}

/**
 * @brief Create an object of kind 0x11; the base scene ignores the shape and data.
 * @param shape Emitter shape.
 * @param data Shape data.
 * @return The new object, or null.
 */
void* LibScene::func_0046BA00(u8 shape, void* data)
{
    return func_00471480(0x11);
}

/**
 * @brief Set the primary animation link or register a supplemental link in a binding owner.
 * @param owner Binding owner.
 * @param animation Animation handle; null clears the primary link when mode is zero.
 * @param mode Zero selects the primary link; otherwise it is stored for a new supplemental link.
 */
void lib_animation_register_binding(LibAnimationBindingOwner* owner, void* animation, s32 mode)
{
    if (mode)
    {
        s32 index;

        for (index = 1; index < LIB_ANIMATION_BINDING_CAPACITY; index++)
        {
            if (owner->animation_slots[index] == animation)
            {
                return;
            }
        }

        for (index = 1; index < LIB_ANIMATION_BINDING_CAPACITY; index++)
        {
            if (!owner->animation_slots[index])
            {
                owner->animation_slots[index] = animation;
                owner->animation_modes[index] = mode;
                return;
            }
        }
    }
    else
    {
        owner->animation_slots[0] = animation;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046BAC0);

void* func_0046C080(void* value)
{
    return value;
}

/**
 * @brief Detach a handle from its kind-10 entry and pass it to each enabled slot object.
 * @param manager Runtime entry table and slot objects.
 * @param handle Handle of the entry to detach.
 */
void func_0046C090(LibEntryManager* manager, void* handle)
{
    s32 index;
    s32 slot;

    if (manager->entries == 0)
    {
        return;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        if (manager->entries[index].unk00 == 0 && manager->entries[index].metadata->kind == 10 && manager->entries[index].handle == handle)
        {
            manager->entries[index].handle = 0;

            for (slot = 0; slot < LIB_ENTRY_MANAGER_SLOT_COUNT; slot++)
            {
                if (manager->unk34[slot] != 0 && !manager->unk9f[slot])
                {
                    func_004B3D80(manager->unk34[slot], handle);
                }
            }

            return;
        }
    }
}

/** Partial view of the scene record a particle grid is built from. */
struct LibGridSceneRecord
{
    u32 unk00;
    s32 unk04;
    u32 unk08;
    u32 unk0c;
    s32 unk10;
    s32 image_offset;
    s32 rows;
    u8 columns;
    u8 shape;
    u8 kind;
    u8 unk1f;
    float unk20;
    float unk24;
    void* unk28;
    u8 unk2c;
    u8 unk2d;
    u8 unk2e;
    u8 unk2f;
    u8 unk30[0x1];
    u8 unk31;
    s16 image_slot;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
    float unk48;
    float unk4c;
    float unk50;
    float unk54;
    float unk58;
    u32 unk5c;
    float unk60;
    float unk64;
    u8 emission;
    u8 unk69;
    u8 unk6a;
    u8 unk6b;
    u8 unk6c;
    u8 unk6d;
    u8 unk6e;
    u8 unk6f;
    u8 unk70;
    u8 unk71;
    u8 unk72;
    u8 unk73;
    u8 unk74;
    u8 unk75;
    u8 keyed;
    u8 unk77;
    u8 unk78;
    u8 unk79;
    u8 unk7a;
    u8 unk7b;
    u8 unk7c;
    u8 unk7d;
    u8 unk7e;
    u8 unk7f;
    u8 unk80;
    u8 unk81;
    u8 unk82;
    u8 unk83;
    u8 unk84;
    u8 unk85;
    u8 unk86;
    u8 unk87;
    u8 unk88;
    u8 unk89[0x3];
    float unk8c;
    float unk90;
    float unk94;
    float value;
    float unk9c;
    float unka0;
    float unka4;
    float unka8;
    float unkac;
    float unkb0;
    float unkb4;
    float unkb8;
    float unkbc;
    float unkc0;
    float unkc4;
    float unkc8;
    float unkcc;
    float unkd0;
    float unkd4;
    float unkd8;
    float unkdc;
    float unke0;
    float unke4;
    u8 unke8;
    u8 unke9;
    u8 unkea;
    u8 unkeb;
    float unkec;
    float unkf0;
    float unkf4;
    float unkf8;
    float unkfc;
    float unk100;
    float unk104;
    float unk108;
    float unk10c;
    float unk110;
    float unk114;
    float unk118;
    float unk11c;
    float unk120;
    float unk124;
    float unk128;
    float unk12c;
    float unk130;
    float unk134;
    float unk138;
    u8 unk13c;
    u8 unk13d;
    u8 unk13e;
    u8 unk13f;
    u8 unk140;
    u8 unk141;
    u8 unk142;
    u8 unk143;
    float unk144;
    float unk148;
    float unk14c;
    float unk150;
    float unk154;
    float unk158;
    float unk15c;
    float unk160;
    float unk164;
    float unk168;
    float unk16c;
    float unk170;
    float unk174;
    float unk178;
    float unk17c;
    float unk180;
    float unk184;
    float unk188;
    float unk18c;
    float unk190;
    float unk194;
    float unk198;
    float unk19c;
    float unk1a0;
    float unk1a4;
    u8 unk1a8;
    u8 unk1a9;
    u8 unk1aa;
    u8 unk1ab;
    float unk1ac;
    float unk1b0;
    float unk1b4;
    float unk1b8;
    float unk1bc;
    float unk1c0;
    float unk1c4;
    float unk1c8;
    u8 unk1cc;
    u8 unk1cd;
    u8 unk1ce;
    u8 unk1cf;
    u8 unk1d0;
    u8 unk1d1;
    u8 unk1d2;
    u8 unk1d3;
    u8 unk1d4;
    u8 unk1d5;
    u8 unk1d6;
    u8 unk1d7[0x1];
    float unk1d8;
    float unk1dc;
    float unk1e0;
    float unk1e4;
    float unk1e8;
    float unk1ec;
    float unk1f0;
    float unk1f4;
    float unk1f8;
    float unk1fc;
    float unk200;
    float unk204;
    float unk208;
    float unk20c;
    float unk210;
    float unk214;
    float unk218;
    float unk21c;
    float unk220;
    float unk224;
    float unk228;
    float unk22c;
    float unk230;
    float unk234;
    float unk238;
    float unk23c;
    s16 key_count;
    s16 link_count;
    s32 keys_offset;
    u8 unk248;
    u8 unk249;
    u8 unk24a;
    u8 unk24b;
    u8 unk24c;
    u8 unk24d[3];
    s32 links[1];
};

/** Key of a keyed grid in its scene record: a key byte and a vector. */
struct LibGridSceneKey
{
    u8 key;
    u8 unk01[3];
    float x;
    float y;
    float z;
    float w;
};

/**
 * @brief Create a LibClass176D50 particle grid for a scene record and take its emission settings from the record.
 * @param unk1 Unused.
 * @param unk2 Unused.
 * @param record Scene record.
 * @return The new grid, or null.
 */
void* LibScene::func_0046C180(void* unk1, void* unk2, void* record)
{
    LibGridSceneRecord* source = static_cast<LibGridSceneRecord*>(record);
    LibClass176D50* grid = new (0) LibClass176D50;

    if (grid == 0)
    {
        return 0;
    }

    switch (source->emission)
    {
    case 0:
        grid->set_emission(1, source->value);
        break;
    case 1:
        grid->set_emission(2, source->value * source->value);
        break;
    case 2:
        grid->emission_kind = 3;
        break;
    case 3:
        grid->set_emission(4, source->value);
        break;
    case 4:
        grid->set_emission(5, source->value);
        break;
    case 5:
        grid->set_emission(6, source->value);
        break;
    }

    return grid;
}

/**
 * @brief Set a transform's offset translation (w one) and rebuild its offset matrix.
 * @param object Transform.
 * @param x Translation x.
 * @param y Translation y.
 * @param z Translation z.
 */
static inline void lib_set_offset_translation(LibTransform* object, float x, float y, float z)
{
    object->offset_translation.x = x;
    object->offset_translation.y = y;
    object->offset_translation.z = z;
    object->offset_translation.w = 1.0f;
    lib_rebuild_offset_transform(object);
    object->transform_dirty = 1;
}

/**
 * @brief Set a transform's offset rotation quaternion and rebuild its offset matrix.
 * @param object Transform.
 * @param x Quaternion x.
 * @param y Quaternion y.
 * @param z Quaternion z.
 * @param w Quaternion w.
 */
static inline void lib_set_offset_rotation(LibTransform* object, float x, float y, float z, float w)
{
    object->offset_rotation.x = x;
    object->offset_rotation.y = y;
    object->offset_rotation.z = z;
    object->offset_rotation.w = w;
    lib_rebuild_offset_transform(object);
    object->transform_dirty = 1;
}

/**
 * @brief Set a transform's offset scale and rebuild its offset matrix.
 * @param object Transform.
 * @param x Scale x.
 * @param y Scale y.
 * @param z Scale z.
 */
static inline void lib_set_offset_scale(LibTransform* object, float x, float y, float z)
{
    object->offset_scale.x = x;
    object->offset_scale.y = y;
    object->offset_scale.z = z;
    lib_rebuild_offset_transform(object);
    object->transform_dirty = 1;
}

/**
 * @brief Set a transform up from a scene record: its parent entry, flags, transform and offset transform.
 * @param scene Scene holding the parent entry.
 * @param object Transform to set up.
 * @param record Transform record; a negative parent index leaves the parent alone.
 */
void func_0046C3F0(LibEntryManager* scene, LibTransform* object, const LibSceneTransformRecord* record)
{
    if (record->parent >= 0)
    {
        object->parent_transform = static_cast<LibTransform*>(scene->entries[record->parent].handle);
    }

    object->unk20c = scene->unk9E ? record->unk14 : record->unk14 | 0x1C0;
    object->set_translation(record->translation[0], record->translation[1], record->translation[2]);
    object->set_orientation_components(record->orientation[0], record->orientation[1], record->orientation[2],
                                       record->orientation[3]);
    object->set_scale(record->scale[0], record->scale[1], record->scale[2]);
    lib_set_offset_translation(object, record->offset_translation[0], record->offset_translation[1],
                               record->offset_translation[2]);
    lib_set_offset_rotation(object, record->offset_rotation[0], record->offset_rotation[1], record->offset_rotation[2],
                            record->offset_rotation[3]);
    lib_set_offset_scale(object, record->offset_scale[0], record->offset_scale[1], record->offset_scale[2]);
}

/**
 * @brief Create a particle grid for a scene record: the record's kind and shape pick the grid class, and its
 *        emission settings, or for keyed grids their key list, come from the record.
 * @param record Scene record.
 * @return The new grid, or null.
 */
void* LibScene::func_0046C540(void* record)
{
    LibGridSceneRecord* source = static_cast<LibGridSceneRecord*>(record);
    LibClass173A40* grid = 0;

    switch (source->kind)
    {
    case 0:
        switch (source->shape)
        {
        case 0:
            grid = new (0) LibClass176BB0;

            if (!grid)
            {
                return 0;
            }

            break;
        case 1:
            grid = new (0) LibClass173CD0;

            if (!grid)
            {
                return 0;
            }

            break;
        case 2:
            grid = new (0) LibClass176A10;

            if (!grid)
            {
                return 0;
            }

            break;
        case 3:
        case 5:
        case 6:
            grid = new (0) LibClass1767A0;

            if (!grid)
            {
                return 0;
            }

            break;
        case 4:
            grid = new (0) LibClass176600;

            if (!grid)
            {
                return 0;
            }

            break;
        }

        break;
    case 1:
        switch (source->shape)
        {
        case 0:
        case 1:
        case 2:
        {
            LibClass176390* emitter = new (0) LibClass176390;
            grid = emitter;

            if (!emitter)
            {
                return 0;
            }

            switch (source->emission)
            {
            case 0:
                emitter->set_emission(1, source->value);
                break;
            case 1:
                emitter->set_emission(2, source->value * source->value);
                break;
            case 4:
                emitter->set_emission(5, source->value);
                break;
            case 5:
                emitter->set_emission(6, source->value);
                break;
            }

            break;
        }
        case 3:
        case 4:
        case 5:
        case 6:
        {
            LibClass176120* emitter = new (0) LibClass176120;
            grid = emitter;

            if (!emitter)
            {
                return 0;
            }

            switch (source->emission)
            {
            case 0:
                emitter->set_emission(1, source->value);
                break;
            case 1:
                emitter->set_emission(2, source->value * source->value);
                break;
            case 3:
                emitter->set_emission(4, source->value);
                break;
            case 4:
                emitter->set_emission(5, source->value);
                break;
            case 5:
                emitter->set_emission(6, source->value);
                break;
            }

            break;
        }
        }

        break;
    case 2:
        switch (source->shape)
        {
        case 0:
        case 1:
        case 2:
        {
            LibClass175EB0* emitter = new (0) LibClass175EB0;
            grid = emitter;

            if (!emitter)
            {
                return 0;
            }

            switch (source->emission)
            {
            case 0:
                emitter->set_emission(1, source->value);
                break;
            case 1:
                emitter->set_emission(2, source->value * source->value);
                break;
            case 2:
                emitter->emission_kind = 3;
                break;
            case 4:
                emitter->set_emission(5, source->value);
                break;
            case 5:
                emitter->set_emission(6, source->value);
                break;
            }

            break;
        }
        case 3:
        case 4:
        case 5:
        case 6:
        {
            LibClass175C40* emitter = new (0) LibClass175C40;
            grid = emitter;

            if (!emitter)
            {
                return 0;
            }

            switch (source->emission)
            {
            case 0:
                emitter->set_emission(1, source->value);
                break;
            case 1:
                emitter->set_emission(2, source->value * source->value);
                break;
            case 2:
                emitter->emission_kind = 3;
                break;
            case 3:
                emitter->set_emission(4, source->value);
                break;
            case 4:
                emitter->set_emission(5, source->value);
                break;
            case 5:
                emitter->set_emission(6, source->value);
                break;
            }

            break;
        }
        }

        break;
    case 3:
        switch (source->shape)
        {
        case 0:
        case 1:
        case 2:
        {
            LibClass1759D0* emitter = new (0) LibClass1759D0;
            grid = emitter;

            if (!emitter)
            {
                return 0;
            }

            switch (source->emission)
            {
            case 0:
                emitter->set_emission(1, source->value);
                break;
            case 1:
                emitter->set_emission(2, source->value * source->value);
                break;
            case 2:
                emitter->emission_kind = 3;
                break;
            case 4:
                emitter->set_emission(5, source->value);
                break;
            case 5:
                emitter->set_emission(6, source->value);
                break;
            }

            break;
        }
        case 3:
        case 4:
        case 5:
        case 6:
        {
            LibClass176D50* emitter = new (0) LibClass176D50;
            grid = emitter;

            if (!emitter)
            {
                return 0;
            }

            switch (source->emission)
            {
            case 0:
                emitter->set_emission(1, source->value);
                break;
            case 1:
                emitter->set_emission(2, source->value * source->value);
                break;
            case 2:
                emitter->emission_kind = 3;
                break;
            case 3:
                emitter->set_emission(4, source->value);
                break;
            case 4:
                emitter->set_emission(5, source->value);
                break;
            case 5:
                emitter->set_emission(6, source->value);
                break;
            }

            break;
        }
        }

        break;
    case 4:
        switch (source->shape)
        {
        case 0:
        case 1:
        case 2:
        {
            LibClass175830* emitter = new (0) LibClass175830;
            grid = emitter;

            if (!emitter)
            {
                return 0;
            }

            switch (source->emission)
            {
            case 0:
                emitter->set_emission(1, source->value);
                break;
            case 1:
                emitter->set_emission(2, source->value * source->value);
                break;
            case 2:
                emitter->emission_kind = 3;
                break;
            case 4:
                emitter->set_emission(5, source->value);
                break;
            case 5:
                emitter->set_emission(6, source->value);
                break;
            }

            break;
        }
        case 3:
        case 4:
        case 5:
        case 6:
        {
            LibClass175690* emitter = new (0) LibClass175690;
            grid = emitter;

            if (!emitter)
            {
                return 0;
            }

            switch (source->emission)
            {
            case 0:
                emitter->set_emission(1, source->value);
                break;
            case 1:
                emitter->set_emission(2, source->value * source->value);
                break;
            case 2:
                emitter->emission_kind = 3;
                break;
            case 3:
                emitter->set_emission(4, source->value);
                break;
            case 4:
                emitter->set_emission(5, source->value);
                break;
            case 5:
                emitter->set_emission(6, source->value);
                break;
            }

            break;
        }
        }

        break;
    case 5:
        switch (source->shape)
        {
        case 0:
        case 1:
        case 2:
        {
            LibClass1755C0* list = new (0) LibClass1755C0;
            grid = list;

            if (!list)
            {
                return 0;
            }

            list->set_emission(1, source->value);

            if (source->keyed)
            {
                list->unkc8 = 1;
            }

            LibGridSceneKey* key = reinterpret_cast<LibGridSceneKey*>(reinterpret_cast<u8*>(source) + source->keys_offset);
            s32 count = source->key_count;
            list->unkc9 = 0;
            list->unkb0 = new (0) u8[count];
            list->unkb4 = new (0) LibClass173490Entry[count];
            list->unkc0 = count;
            list->unkc4 = 0;

            for (s32 i = 0; i < count; i++)
            {
                func_00479F50(reinterpret_cast<LibKeyedVectorList*>(list), key->key,
                              reinterpret_cast<const LibFloat4*>(&FieldVec4A(key->x, key->y, key->z, key->w)));
                key++;
            }

            break;
        }
        case 3:
        case 4:
        case 5:
        case 6:
        {
            LibClass173F80* list = new (0) LibClass173F80;
            grid = list;

            if (!list)
            {
                return 0;
            }

            list->set_emission(1, source->value);

            if (source->keyed)
            {
                list->unkc8 = 1;
            }

            LibGridSceneKey* key = reinterpret_cast<LibGridSceneKey*>(reinterpret_cast<u8*>(source) + source->keys_offset);
            s32 count = source->key_count;
            list->unkc9 = 0;
            list->unkb0 = new (0) u8[count];
            list->unkb4 = new (0) LibClass173490Entry[count];
            list->unkc0 = count;
            list->unkc4 = 0;

            for (s32 i = 0; i < count; i++)
            {
                func_00479EF0(reinterpret_cast<LibKeyedVectorList*>(list), key->key,
                              reinterpret_cast<const LibFloat4*>(&FieldVec4A(key->x, key->y, key->z, key->w)));
                key++;
            }

            break;
        }
        }

        break;
    case 6:
        grid = static_cast<LibClass173A40*>(func_0046C180(reinterpret_cast<void*>(source->shape), source->unk28, record));
        break;
    }

    return grid;
}

/**
 * @brief View a vector as the quadword the emitter setters take.
 * @param vector Vector to pass.
 * @return The vector's 16 bytes.
 */
static inline const unsigned __int128* as_quadword(const FieldVec4A& vector)
{
    return reinterpret_cast<const unsigned __int128*>(&vector);
}

/**
 * @brief Create a particle emitter for a scene record: unless the record says otherwise, also a grid and an image
 *        object that draws it, then copy the record's grid, image and emitter settings across.
 * @param unk1 Update list the image object joins.
 * @param unk2 Update list the emitter joins.
 * @param record Scene record.
 * @return The new emitter, or null.
 */
void* LibScene::func_0046DE90(void* unk1, void* unk2, void* record)
{
    LibGridSceneRecord* source = static_cast<LibGridSceneRecord*>(record);

    if (source->unk1ce != 6)
    {
        return 0;
    }

    LibClass173990* emitter;

    if (source->kind == 6)
    {
        emitter = static_cast<LibClass173990*>(func_0046BA00(source->shape, source->unk28));
    }
    else
    {
        emitter = static_cast<LibClass173990*>(func_00471480(0x11));
    }

    if (!emitter)
    {
        return 0;
    }

    LibObject1751A0* object = 0;

    if (!source->unk31)
    {
        object = static_cast<LibObject1751A0*>(func_00471480(0x12));

        if (!object)
        {
            emitter->destroy();
            return 0;
        }

        LibClass173A40* grid = static_cast<LibClass173A40*>(func_0046C540(record));

        if (!grid)
        {
            emitter->destroy();
            object->destroy();
            return 0;
        }

        func_0046B480(object, reinterpret_cast<LibGridBase*>(grid));
        grid->resize(source->rows, source->columns);
        grid->func_slot4C(source->unk20);

        switch (source->unk2d)
        {
        case 0:
            grid->func_slot5C(0);
            break;
        case 1:
            grid->func_slot5C(1);
            break;
        case 2:
            grid->func_slot5C(2);
            break;
        case 3:
            grid->func_slot5C(3);
            break;
        }

        grid->func_slot64(source->unk34);

        if (source->columns > 1)
        {
            grid->func_slot68(source->unk1d5);
            grid->func_slot70(source->unk64);
        }

        grid->func_slot78(source->unk24);

        if (source->unk6f)
        {
            grid->func_slot7C(source->unk00);
            grid->func_slot84(source->unk70);
            grid->func_slot88((source->unk71 ? 1 : 0) | (source->unk72 ? 2 : 0) | (source->unk73 ? 4 : 0) |
                              (source->unk74 ? 8 : 0));
        }
        else
        {
            grid->func_slot7C(0);
        }

        if (source->unk81)
        {
            grid->func_slot8C(source->unk0c);
            grid->func_slot94(source->unk82);
            grid->func_slot98(source->unk90);
            grid->func_slot9C(source->unk94);
            grid->func_slotA0((source->unk83 ? 1 : 0) | (source->unk84 ? 2 : 0) | (source->unk85 ? 4 : 0) |
                              (source->unk86 ? 8 : 0));
        }
        else
        {
            grid->func_slot8C(0);
        }

        if ((source->shape > 2 && source->shape < 5) || source->shape == 6)
        {
            if (source->image_offset)
            {
                LibRenderDataRecord* entry =
                    reinterpret_cast<LibRenderDataRecord*>(reinterpret_cast<u8*>(source) + source->image_offset);

                if (entry->storage_kind == 1)
                {
                    LibRenderDataRecord* shared = func_00448910(entry->key08, entry->key0c);

                    if (shared)
                    {
                        object->set_image(shared->data ? reinterpret_cast<LibResourceChunkHeader*>(
                                                             static_cast<u8*>(shared->data) - 0x10)
                                                       : reinterpret_cast<LibResourceChunkHeader*>(shared + 1),
                                          source->image_slot);
                    }
                }
                else if (entry->storage_kind == 4)
                {
                    object->set_image(reinterpret_cast<LibResourceChunkHeader*>(reinterpret_cast<u8*>(entry) +
                                                                                 entry->data_offset - 0x10),
                                      source->image_slot);
                }
                else
                {
                    object->set_image(reinterpret_cast<LibResourceChunkHeader*>(entry + 1), source->image_slot);
                }
            }
        }
        else if (source->shape == 5)
        {
            object->clear_image();
        }

        object->set_primitive(source->shape, source->unk2e ? true : false, source->unk2f, source->unk58);

        if (source->unk6d)
        {
            float value = source->unka0;
            object->unkadf = 1;
            object->unkabc = value;
        }

        if (source->unk6e)
        {
            object->unkae0 = source->unk6e;
        }

        func_0043B700(emitter, object);
        object->light_mask = source->unk5c;

        if (source->unk6c)
        {
            float value = source->unk9c;
            object->unkae6 = 1;
            object->unkac4 = value;
        }

        float radius = ee_max_in_place(source->unkac, source->unkb0);
        radius = ee_max(source->unkb4, radius);
        object->unkaa8 = radius;
        static_cast<LibUpdateList*>(unk1)->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
    }
    else
    {
        emitter->unk49b_0 = 1;
    }

    if (source->unk78)
    {
        func_00435190(emitter, source->unk08);
        func_004351A0(emitter, 1, source->unk79,
                      (source->unk7a ? 1 : 0) | (source->unk7b ? 2 : 0) | (source->unk7c ? 4 : 0) |
                          (source->unk7d ? 8 : 0) | (source->unk7e ? 0x10 : 0) | (source->unk7f ? 0x20 : 0) |
                          (source->unk80 ? 0x40 : 0));
    }

    emitter->unk3ec = source->unka4;
    emitter->unk3f0 = source->unka8;

    if (source->unk1cf)
    {
        func_004352B0(emitter, 1, source->unk208, source->unk20c);
        emitter->unk3e8 = reinterpret_cast<u32>(this);
    }

    if (source->unk1d0 || source->unk1d1)
    {
        func_00435270(emitter, source->unk1d0 ? true : false, source->unk1d1 ? true : false, source->unk1d2, source->unk210);

        if (source->unk1d3)
        {
            func_004351D0(emitter, 1, source->unk214, source->unk218);
        }
    }

    switch (source->unk75)
    {
    case 0:
        func_0043AFC0(emitter);
        break;
    case 1:
        func_0043AFA0(emitter, as_quadword(FieldVec4A(source->unkac, source->unkb0, source->unkb4, 1.0f)), source->unkb8);
        break;
    case 2:
        func_0043AF80(emitter, as_quadword(FieldVec4A(source->unkac, source->unkb0, source->unkb4, 1.0f)), source->unkb8);
        break;
    case 3:
        func_0043AF60(emitter, as_quadword(FieldVec4A(source->unkac, source->unkb0, source->unkb4, 1.0f)), source->unkb8);
        break;
    case 4:
        func_0043AF20(emitter, as_quadword(FieldVec4A(source->unkac, source->unkb0, source->unkb4, 1.0f)), source->unkb8);
        break;
    case 5:
        func_0043AF40(emitter, source->unkac, source->unkb4, source->unkb8);
        break;
    case 6:
        func_0043AF00(emitter, as_quadword(FieldVec4A(source->unkac, source->unkb0, source->unkb4, 1.0f)), source->unkb8);
        break;
    case 7:
        func_0043AEE0(emitter, as_quadword(FieldVec4A(source->unkac, source->unkb0, source->unkb4, 1.0f)), source->unkb8);
        break;
    case 8:
        func_0043AEC0(emitter, as_quadword(FieldVec4A(source->unkac, source->unkb0, source->unkb4, 1.0f)), source->unkb8);
        break;
    case 9:
        func_0043AEA0(emitter, as_quadword(FieldVec4A(source->unkac, source->unkb0, source->unkb4, 1.0f)), source->unkb8);
        break;
    case 10:
        func_0043AE80(emitter, as_quadword(FieldVec4A(source->unkac, source->unkb0, source->unkb4, 1.0f)), source->unkb8);
        break;
    case 11:
        func_0043AE20(emitter, as_quadword(FieldVec4A(source->unkac, source->unkb0, source->unkb4, 1.0f)), 0, source->unk1d4 != 0, source->unke4,
                      source->unkb8);
        break;
    }

    if (source->kind > 0)
    {
        switch (source->unke9)
        {
        case 0:
            func_0043ADE0(emitter, as_quadword(FieldVec4A(source->unkec, source->unkf0, source->unkf4, 1.0f)));
            break;
        case 1:
            func_0043ADC0(emitter, as_quadword(FieldVec4A(source->unkec, source->unkf0, source->unkf4, 1.0f)),
                          as_quadword(FieldVec4A(source->unkf8, source->unkfc, source->unk100, 1.0f)));
            break;
        case 2:
            func_0043ADA0(emitter, as_quadword(FieldVec4A(source->unkec, source->unkf0, source->unkf4, source->unkfc)));
            break;
        case 3:
            func_0043AD80(emitter, source->unk104, source->unk108);
            break;
        case 4:
            func_0043AD60(emitter, source->unk104, source->unk108, source->unk10c);
            break;
        case 5:
            func_0043AD40(emitter, source->unk104, source->unk108);
            break;
        case 6:
            func_0043AD20(emitter, as_quadword(FieldVec4A(source->unkec, source->unkf0, source->unkf4, source->unkfc)));
            break;
        case 7:
            func_0043AD00(emitter, source->unk104, source->unk108, source->unk10c, source->unkf0, source->unkfc);
            break;
        }

        switch (source->unk140)
        {
        case 0:
            func_0043ACF0(emitter, as_quadword(FieldVec4A(source->unk144, source->unk148, source->unk14c, 1.0f)));
            break;
        case 1:
            func_0043ACD0(emitter, as_quadword(FieldVec4A(source->unk144, source->unk148, source->unk14c, 1.0f)),
                          as_quadword(FieldVec4A(source->unk150, source->unk154, source->unk158, 1.0f)));
            break;
        case 2:
            func_0043ACB0(emitter, as_quadword(FieldVec4A(source->unk15c, source->unk15c, source->unk15c, source->unk15c)));
            break;
        }

        if (source->unk13c)
        {
            emitter->unk49b_1 = 1;
        }

        if (source->unk13f)
        {
            emitter->unk49b_2 = 1;
        }

        if (source->unk13e)
        {
            emitter->unk49b_3 = 1;
        }

        if (source->unk87)
        {
            float value = source->unk8c;
            emitter->unk49c_5 = 1;
            emitter->unk438 = value;
        }

        if (source->unk13d)
        {
            float value = source->unk138;
            emitter->unk49b_4 = 1;
            emitter->unk3fc = value;
        }

        if (source->unk88)
        {
            emitter->unk49c_6 = 1;
        }
    }

    switch (source->unk143)
    {
    case 0:
        func_0043ACA0(emitter, as_quadword(FieldVec4A(source->unk188, source->unk18c, source->unk190, source->unk194)));
        break;
    case 1:
        func_0043AC80(emitter, as_quadword(FieldVec4A(source->unk188, source->unk18c, source->unk190, source->unk194)),
                      as_quadword(FieldVec4A(source->unk198, source->unk19c, source->unk1a0, source->unk1a4)));
        break;
    case 2:
        func_0043AC60(emitter, as_quadword(FieldVec4A(source->unk188, source->unk18c, source->unk190, source->unk194)),
                      as_quadword(FieldVec4A(source->unk198, source->unk19c, source->unk1a0, source->unk1a4)));
        break;
    }

    if (source->kind > 1)
    {
        switch (source->unk1cc)
        {
        case 0:
            func_0043AC50(emitter, as_quadword(FieldVec4A(source->unk1d8, source->unk1dc, source->unk1e0, source->unk1e4)));
            break;
        case 1:
            func_0043AC30(emitter, as_quadword(FieldVec4A(source->unk1d8, source->unk1dc, source->unk1e0, source->unk1e4)),
                          as_quadword(FieldVec4A(source->unk1e8, source->unk1ec, source->unk1f0, source->unk1f4)));
            break;
        case 2:
            func_0043AC10(emitter, as_quadword(FieldVec4A(source->unk1d8, source->unk1dc, source->unk1e0, source->unk1e4)),
                          as_quadword(FieldVec4A(source->unk1e8, source->unk1ec, source->unk1f0, source->unk1f4)));
            break;
        }

        switch (source->unk1cd)
        {
        case 0:
            func_0043AC00(emitter, as_quadword(FieldVec4A(source->unk1f8, source->unk1fc, source->unk200, source->unk204)));
            break;
        case 1:
            func_0043ABE0(emitter, as_quadword(FieldVec4A(source->unk1f8, source->unk1fc, source->unk200, source->unk204)));
            break;
        }
    }

    if (source->unk2d == 0 || source->unk2d == 2)
    {
        emitter->entry_count = 0;
        delete[] emitter->entries;
        emitter->entries = 0;
    }
    else
    {
        s32 count = source->columns - 1;
        delete[] emitter->entries;
        emitter->entries = new (0) LibClass173490Entry[count];

        if (emitter->entries)
        {
            emitter->entry_count = count;
        }
        else
        {
            emitter->entry_count = 0;
        }

        for (s32 i = 0; i < source->columns - 1; i++)
        {
            float x = source->unk38 + ((1.0f + i) * (source->unk48 - source->unk38)) / (u32)source->columns;
            float y = source->unk3c + ((1.0f + i) * (source->unk4c - source->unk3c)) / (u32)source->columns;
            float z = source->unk40 + ((1.0f + i) * (source->unk50 - source->unk40)) / (u32)source->columns;
            float w = source->unk44 + ((1.0f + i) * (source->unk54 - source->unk44)) / (u32)source->columns;
            emitter->set_entry(i, &LibClass173490Entry(x, y, z, w));
        }
    }

    if (source->kind > 2 && source->keyed)
    {
        switch (source->unk77)
        {
        case 0:
            func_0043ABD0(emitter, source->unkbc, source->unkc0);
            break;
        case 1:
            func_0043ABB0(emitter, source->unkbc, source->unkc0, source->unkc4, source->unkc8);
            break;
        }

        switch (source->unke8)
        {
        case 0:
            func_0043ABA0(emitter, as_quadword(FieldVec4A(source->unkcc, source->unkd0, source->unkd4, 1.0f)));
            break;
        case 1:
            func_0043AB80(emitter, as_quadword(FieldVec4A(source->unkcc, source->unkd0, source->unkd4, 1.0f)),
                          as_quadword(FieldVec4A(source->unkd8, source->unkdc, source->unke0, 1.0f)));
            break;
        }

        switch (source->unkea)
        {
        case 0:
            func_0043AB70(emitter, source->unk110, source->unk114);
            break;
        case 1:
            func_0043AB50(emitter, source->unk110, source->unk114, source->unk118, source->unk11c);
            break;
        }

        switch (source->unkeb)
        {
        case 0:
            func_0043AB40(emitter, as_quadword(FieldVec4A(source->unk120, source->unk124, source->unk128, 1.0f)));
            break;
        case 1:
            func_0043AB20(emitter, as_quadword(FieldVec4A(source->unk120, source->unk124, source->unk128, 1.0f)),
                          as_quadword(FieldVec4A(source->unk12c, source->unk130, source->unk134, 1.0f)));
            break;
        }

        switch (source->unk141)
        {
        case 0:
            func_0043AB10(emitter, source->unk160, source->unk164);
            break;
        case 1:
            func_0043AAF0(emitter, source->unk160, source->unk164, source->unk168, source->unk16c);
            break;
        }

        switch (source->unk142)
        {
        case 0:
            func_0043AAE0(emitter, as_quadword(FieldVec4A(source->unk170, source->unk174, source->unk178, 1.0f)));
            break;
        case 1:
            func_0043AAC0(emitter, as_quadword(FieldVec4A(source->unk170, source->unk174, source->unk178, 1.0f)),
                          as_quadword(FieldVec4A(source->unk17c, source->unk180, source->unk184, 1.0f)));
            break;
        }
    }

    u8 c = source->unk24a;
    u8 b = source->unk249;
    u8 a = source->unk248;
    emitter->unk494 = a;
    emitter->unk495 = b;
    emitter->unk496 = c;

    if (source->shape == 3 || source->shape == 5 || source->shape == 6)
    {
        switch (source->unk1a8)
        {
        case 0:
            func_0043AAB0(emitter, source->unk1ac);
            break;
        case 1:
            func_0043AA90(emitter, source->unk1ac, source->unk1b0);
            break;
        }

        switch (source->unk1a9)
        {
        case 0:
            func_0043AA80(emitter, source->unk1b4);
            break;
        case 1:
            func_0043AA60(emitter, source->unk1b4, source->unk1b8);
            break;
        }

        switch (source->unk1aa)
        {
        case 0:
            func_0043AA50(emitter, as_quadword(FieldVec4A(source->unk1bc, source->unk1bc, source->unk1bc, source->unk1bc)));
            break;
        case 1:
            func_0043AA30(emitter, as_quadword(FieldVec4A(source->unk1bc, source->unk1bc, source->unk1bc, source->unk1bc)),
                          as_quadword(FieldVec4A(source->unk1c0, source->unk1c0, source->unk1c0, source->unk1c0)));
            break;
        case 2:
            func_0043AA10(emitter, as_quadword(FieldVec4A(source->unk1bc, source->unk1bc, source->unk1bc, source->unk1bc)),
                          as_quadword(FieldVec4A(source->unk1c0, source->unk1c0, source->unk1c0, source->unk1c0)));
            break;
        }

        switch (source->unk1ab)
        {
        case 0:
            func_0043AA00(emitter, as_quadword(FieldVec4A(source->unk1c4, source->unk1c4, source->unk1c4, source->unk1c4)));
            break;
        case 1:
            func_0043A9E0(emitter, as_quadword(FieldVec4A(source->unk1c4, source->unk1c4, source->unk1c4, source->unk1c4)),
                          as_quadword(FieldVec4A(source->unk1c8, source->unk1c8, source->unk1c8, source->unk1c8)));
            break;
        case 2:
            func_0043A9C0(emitter, as_quadword(FieldVec4A(source->unk1c4, source->unk1c4, source->unk1c4, source->unk1c4)),
                          as_quadword(FieldVec4A(source->unk1c8, source->unk1c8, source->unk1c8, source->unk1c8)));
            break;
        }

        if (source->shape == 5)
        {
            switch (source->unk1d6)
            {
            case 0:
                func_0043A9B0(emitter, source->unk21c);
                break;
            case 1:
                func_0043A990(emitter, source->unk21c, source->unk220);
                break;
            }

            if (object)
            {
                float scale = source->unk224;
                object->unka70[0] = scale;
                object->unka70[1] = scale;
                object->set_unka70_zw(source->unk228, source->unk22c);
            }
        }
        else if (source->shape == 6)
        {
            switch (source->unk24b)
            {
            case 0:
                func_0043A980(emitter, source->unk230);
                break;
            case 1:
                func_0043A960(emitter, source->unk230, source->unk234);
                break;
            }

            switch (source->unk24c)
            {
            case 0:
                func_0043A950(emitter, source->unk238);
                break;
            case 1:
                func_0043A930(emitter, source->unk238, source->unk23c);
                break;
            }
        }
    }

    if (source->unk6b)
    {
        emitter->unk499_1 = 1;
    }

    if (source->unk1f)
    {
        float value = source->unk60;
        emitter->unk49a = source->unk1f;
        emitter->unk434 = value;
    }

    static_cast<LibUpdateList*>(unk2)->append_node(emitter, LibUpdateList::DEFAULT_NODE_KIND);
    return emitter;
}

/** Link-system resource header; the node, link and shape records follow at 0x18. */
typedef struct LibLinkSystemRecord
{
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
    s16 node_count;
    s16 link_count;
    s16 shape_count;
    u8 unk16;
    u8 has_unk30;
    u32 entries[1];
} LibLinkSystemRecord;

extern "C" void func_0046BAC0(LibScene* scene, LibClass173050* owner, LibLinkSystemRecord* record);

extern LibResidentUpdateList* D_001B6660;

/** Kind-31 entry data: an occluder rectangle's half extents and a flag. */
struct LibSceneOccluderRecord
{
    float half_width;
    float half_depth;
    u8 unk08;
};

/** Kind-0 ray of a ray list: a fan of four colors out to two widths. */
struct LibSceneFanRayRecord
{
    s32 kind;
    float axis_offset;
    float alpha;
    u32 colors[4];
    float inner_radius;
    float widths[2];
};

/** Kind-1 ray of a ray list: four bands between five colors. */
struct LibSceneBandRayRecord
{
    s32 kind;
    float axis_offset;
    float alpha;
    u32 colors[5];
    float inner_radius;
    float widths[4];
};

/** Kind-2 ray of a ray list: a ring. */
struct LibSceneRingRayRecord
{
    s32 kind;
    float axis_offset;
    float alpha;
    u32 color;
    s32 segments;
    float inner_radius;
    float width;
};

/** Kind-3 ray of a ray list: spokes from a centre color to an edge color. */
struct LibSceneSpokeRayRecord
{
    s32 kind;
    float axis_offset;
    float alpha;
    u32 centre_color;
    u32 edge_color;
    s32 unk14;
    s32 unk18;
    float unk1c;
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
    float unk30;
    float unk34;
};

/** An entry's data in a scene's resource: after the 16-byte header of the 128-byte aligned resource. */
#define LIB_SCENE_ENTRY_DATA(scene, metadata) \
    (reinterpret_cast<u8*>((reinterpret_cast<u32>((scene)->data) + 127) & ~127) + (metadata)->data_position + 0x10)

/** Kind-22 entry data: the ray list header, then the ray records. */
struct LibSceneRayListRecord
{
    u8 unk00[4];
    u32 unk04;
    float unk08;
    u16 ray_count;
    u8 unk0e;
    u8 unk0f;
};

/**
 * @brief Give a renderable its layer from an entry's layer mask: bit 0 set keeps the other bits as the mask, otherwise
 *        the lowest set bit is the layer and the rest stays the mask.
 * @param object Renderable.
 * @param mask Layer mask from the entry's metadata.
 */
static inline void lib_scene_set_layer_mask(LibTransform* object, u32 mask)
{
    if (mask & 1)
    {
        object->unk88 = mask >> 1;
    }
    else if (mask != 0)
    {
        u32 bits = mask >> 1;
        u32 rest = bits;

        for (s32 layer = 1; bits != 0; layer++)
        {
            if (bits & 1)
            {
                object->layer = layer;
                rest &= ~(1 << (layer - 1));
                object->unk88 = rest;
                break;
            }

            bits >>= 1;
        }
    }
}

/**
 * @brief Give a renderable its layer from an entry's layer mask, and the layer's display manager with it.
 * @param scene Scene whose renderer holds the layers.
 * @param object Renderable.
 * @param mask Layer mask from the entry's metadata.
 */
static inline void lib_scene_set_layer_and_manager(LibScene* scene, LibTransform* object, u32 mask)
{
    if (mask & 1)
    {
        object->unk88 = mask >> 1;
    }
    else if (mask != 0)
    {
        u32 bits = mask >> 1;
        u32 rest = bits;

        for (s32 layer = 1; bits != 0; layer++)
        {
            if (bits & 1)
            {
                object->layer = layer;
                rest &= ~(1 << (layer - 1));
                object->unk88 = rest;
                object->display_manager = scene->renderer->layers[layer - 1].display_manager;
                break;
            }

            bits >>= 1;
        }
    }
}

/**
 * @brief Make a scene that shares another scene's data: copy its lists and tables, then make each entry's object
 *        again, copying the source scene's object where there is one, and hook them up the way the source's were.
 * @param scene Scene to fill.
 * @param source Scene to copy.
 * @param with_transforms Nonzero also copies the entries of kind 9 (plain transforms).
 * @return 1 when every object copied cleanly, 0 when one didn't or an allocation failed.
 */
extern "C" bool func_0046F910(LibScene* scene, LibScene* source, u8 with_transforms)
{
    u32* cursor;
    bool result;
    LibClass173380* lod_parent = 0;

    scene->renderer = source->renderer;
    result = true;
    scene->update_list = source->update_list;
    scene->light_list = source->light_list;
    scene->display_manager = source->display_manager;
    scene->unk1c = source->unk1c;
    scene->data_borrowed = 1;
    scene->header = source->header;
    scene->data = source->data;
    cursor = reinterpret_cast<u32*>(scene->unk1c);

    while (*reinterpret_cast<s32*>(cursor) != 1)
    {
        u32 type = *cursor++;

        switch (type)
        {
            case 2:
                cursor += 2;
                break;
            case 4:
                cursor += 8;
                break;
            case 3:
            {
                scene->entries = new (0) LibManagedEntry[scene->header->count];

                if (!scene->entries)
                {
                    return 0;
                }

                for (s32 i = 0; i < scene->header->count; i++)
                {
                    LibEntryMetadata* metadata = reinterpret_cast<LibEntryMetadata*>(cursor);
                    scene->entries[i].unk00 = 0;
                    scene->entries[i].handle = 0;
                    scene->entries[i].unk04 = 0;
                    scene->entries[i].metadata = metadata;
                    cursor = reinterpret_cast<u32*>(reinterpret_cast<u8*>(cursor) + *reinterpret_cast<u16*>(cursor));

                    switch (metadata->state)
                    {
                        case 1:
                            switch (metadata->kind)
                            {
                                case 4:
                                {
                                    scene->entries[i].handle = scene->func_00471480(0);
                                    LibTransform* object = static_cast<LibTransform*>(scene->entries[i].handle);

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    object->copy_offset_transform_state(static_cast<LibTransform*>(source->entries[i].handle));

                                    if (metadata->link >= 0)
                                    {
                                        static_cast<LibTransform*>(scene->entries[i].handle)->parent_transform =
                                            static_cast<LibTransform*>(scene->entries[metadata->link].handle);
                                    }

                                    static_cast<LibTransform*>(scene->entries[i].handle)->object_kind |= 1;
                                    scene->update_list->append_node(scene->entries[i].handle, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 7:
                                {
                                    LibLodController* object = static_cast<LibLodController*>(scene->func_00471480(1));
                                    scene->entries[i].handle = object;

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    static_cast<LibLodController*>(scene->entries[i].handle)
                                        ->copy_offset_transform_state(static_cast<LibTransform*>(source->entries[i].handle));

                                    if (metadata->link >= 0)
                                    {
                                        object->parent_transform = static_cast<LibTransform*>(scene->entries[metadata->link].handle);
                                    }

                                    scene->display_manager->append_node(scene->entries[i].handle, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                            }

                            break;
                        case 3:
                        {
                            scene->entries[i].handle = scene->func_00471480(0x30);
                            LibTransform* object = static_cast<LibTransform*>(scene->entries[i].handle);

                            if (!object)
                            {
                                return 0;
                            }

                            object->parent_transform = 0;
                            static_cast<LibTransform*>(scene->entries[i].handle)->unk20c = 0;
                            static_cast<LibTransform*>(scene->entries[i].handle)->object_kind |= 1;
                            scene->update_list->append_node(scene->entries[i].handle, LibUpdateList::DEFAULT_NODE_KIND);
                            break;
                        }
                        case 0:
                        case 2:
                            switch (metadata->kind)
                            {
                                case 1:
                                {
                                    LibModel* object;

                                    if (metadata->flags & 0x4080)
                                    {
                                        LibModel* original = static_cast<LibModel*>(source->entries[i].handle);

                                        if (original->type_id == 0x110)
                                        {
                                            LibClass1788B0* model = static_cast<LibClass1788B0*>(scene->func_00471480(8));
                                            object = model;

                                            if (!object)
                                            {
                                                return 0;
                                            }

                                            if (!model->func_004C8720(scene->renderer, static_cast<LibClass1788B0*>(source->entries[i].handle)))
                                            {
                                                result = false;
                                            }
                                        }
                                        else
                                        {
                                            object = static_cast<LibModel*>(scene->func_00471480(0x2C));

                                            if (!object)
                                            {
                                                return 0;
                                            }

                                            if (static_cast<LibClass173380*>(original)->unk838)
                                            {
                                                if (!static_cast<LibClass173380*>(object)->build_from(0, static_cast<LibClass173380*>(original)))
                                                {
                                                    result = false;
                                                }

                                                if (lod_parent)
                                                {
                                                    lod_parent->objects.append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                                    static_cast<LibClass173380*>(object)->unk838 = 1;
                                                }
                                            }
                                            else
                                            {
                                                if (!static_cast<LibClass173380*>(object)->build_from(scene->renderer, static_cast<LibClass173380*>(original)))
                                                {
                                                    result = false;
                                                }

                                                lod_parent = static_cast<LibClass173380*>(object);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        object = static_cast<LibModel*>(scene->func_00471480(2));

                                        if (!object)
                                        {
                                            return 0;
                                        }

                                        if (!object->build_from(scene->renderer, static_cast<LibModel*>(source->entries[i].handle)))
                                        {
                                            result = false;
                                        }
                                    }

                                    lib_scene_set_layer_mask(object, metadata->layer_mask);
                                    scene->entries[i].handle = object;

                                    if (metadata->link >= 0)
                                    {
                                        object->parent_transform = static_cast<LibTransform*>(scene->entries[metadata->link].handle);
                                    }

                                    break;
                                }
                                case 8:
                                {
                                    LibClass175430* model = static_cast<LibClass175430*>(scene->func_00471480(0xE));

                                    if (!model)
                                    {
                                        return 0;
                                    }

                                    if (!model->func_00471410(scene->renderer, static_cast<LibClass175430*>(source->entries[i].handle)))
                                    {
                                        result = false;
                                    }

                                    scene->entries[i].handle = model;

                                    if (metadata->link >= 0)
                                    {
                                        model->parent_transform = static_cast<LibTransform*>(scene->entries[metadata->link].handle);
                                    }

                                    lib_scene_set_layer_and_manager(scene, model, metadata->layer_mask);
                                    break;
                                }
                                case 9:
                                    if (with_transforms)
                                    {
                                        scene->entries[i].handle = scene->func_00471480(0);
                                        LibTransform* object = static_cast<LibTransform*>(scene->entries[i].handle);

                                        if (!object)
                                        {
                                            return 0;
                                        }

                                        object->copy_offset_transform_state(static_cast<LibTransform*>(source->entries[i].handle));

                                        if (metadata->link >= 0)
                                        {
                                            static_cast<LibTransform*>(scene->entries[i].handle)->parent_transform =
                                                static_cast<LibTransform*>(scene->entries[metadata->link].handle);
                                        }

                                        static_cast<LibTransform*>(scene->entries[i].handle)->object_kind |= 1;
                                        scene->update_list->append_node(scene->entries[i].handle, LibUpdateList::DEFAULT_NODE_KIND);
                                    }

                                    break;
                                case 10:
                                {
                                    u8* data = LIB_SCENE_ENTRY_DATA(scene, metadata);
                                    LibClass173990* emitter = static_cast<LibClass173990*>(scene->func_00471480(0x11));
                                    scene->entries[i].handle = emitter;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    emitter->copy_state(static_cast<LibClass173990*>(source->entries[i].handle));

                                    if (metadata->link >= 0)
                                    {
                                        emitter->parent_transform = static_cast<LibTransform*>(scene->entries[metadata->link].handle);
                                    }

                                    scene->update_list->append_node(emitter, LibUpdateList::DEFAULT_NODE_KIND);
                                    LibObject1751A0* image = static_cast<LibObject1751A0*>(scene->func_00471480(0x12));

                                    if (!image)
                                    {
                                        return 0;
                                    }

                                    image->copy_image_state(emitter->source);
                                    scene->renderer->append_node(image, LibUpdateList::DEFAULT_NODE_KIND);
                                    func_0043B700(emitter, image);
                                    lib_scene_set_layer_and_manager(scene, image, metadata->layer_mask);
                                    LibClass173A40* grid = static_cast<LibClass173A40*>(scene->func_0046C540(data));

                                    if (!grid)
                                    {
                                        return 0;
                                    }

                                    grid->copy_settings(reinterpret_cast<LibClass173A40*>(image->reference));
                                    func_0046B480(image, reinterpret_cast<LibGridBase*>(grid));
                                    break;
                                }
                                case 20:
                                {
                                    u32* data = reinterpret_cast<u32*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    ResidentImageObject* image = static_cast<ResidentImageObject*>(scene->func_00471480(0x1C));
                                    scene->entries[i].handle = image;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    image->copy_state(static_cast<ResidentImageObject*>(source->entries[i].handle));

                                    if (metadata->link >= 0)
                                    {
                                        static_cast<ResidentImageObject*>(scene->entries[i].handle)->parent_transform =
                                            static_cast<ResidentImageObjectBase*>(scene->entries[metadata->link].handle);
                                    }

                                    image->hit_volume = reinterpret_cast<ResidentHitBox*>(*data);
                                    resident_image_object_rebuild_hit_box(image);
                                    D_001B6660->append_node(image, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 21:
                                {
                                    LibClass1753A0* object = static_cast<LibClass1753A0*>(scene->func_00471480(0x1D));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    object->func_004713F0(static_cast<LibClass1753A0*>(source->entries[i].handle));

                                    if (metadata->link >= 0)
                                    {
                                        static_cast<LibTransform*>(scene->entries[i].handle)->parent_transform =
                                            static_cast<LibTransform*>(scene->entries[metadata->link].handle);
                                    }

                                    break;
                                }
                                case 22:
                                {
                                    LibSceneRayListRecord* data = reinterpret_cast<LibSceneRayListRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172960* rays = static_cast<LibClass172960*>(scene->func_00471480(0x1E));
                                    scene->entries[i].handle = rays;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    LibClass1728A0* capture = static_cast<LibClass1728A0*>(scene->func_00471480(0x1F));

                                    if (!capture)
                                    {
                                        return 0;
                                    }

                                    func_004214C0(capture, rays, scene->display_manager);
                                    scene->update_list->append_node(capture, LibUpdateList::DEFAULT_NODE_KIND);
                                    rays->unk240 = capture;
                                    rays->unk23d = 1;
                                    u8* record = reinterpret_cast<u8*>(data + 1);
                                    rays->unk230 = data->unk04;
                                    rays->unk22c = data->unk08;
                                    rays->unk23c = data->unk0e != 0;
                                    rays->unk23e = !data->unk0f;
                                    LibClass1728C0* ray;

                                    for (s32 k = 0; k < data->ray_count; k++)
                                    {
                                        switch (*reinterpret_cast<s32*>(record))
                                        {
                                            case 0:
                                            {
                                                LibSceneFanRayRecord* source_ray = reinterpret_cast<LibSceneFanRayRecord*>(record);
                                                LibClass172940* fan = static_cast<LibClass172940*>(scene->func_00471480(0x20));

                                                if (!fan)
                                                {
                                                    return 0;
                                                }

                                                ray = fan;
                                                fan->set_colors(source_ray->colors[0], source_ray->colors[1], source_ray->colors[2],
                                                                source_ray->colors[3]);
                                                fan->inner_radius = source_ray->inner_radius;
                                                fan->set_widths(source_ray->widths[0], source_ray->widths[1]);

                                                fan->axis_offset = source_ray->axis_offset;
                                                fan->alpha = source_ray->alpha;
                                                record += sizeof(LibSceneFanRayRecord);
                                                break;
                                            }
                                            case 1:
                                            {
                                                LibSceneBandRayRecord* source_ray = reinterpret_cast<LibSceneBandRayRecord*>(record);
                                                LibClass172920* band = static_cast<LibClass172920*>(scene->func_00471480(0x21));

                                                if (!band)
                                                {
                                                    return 0;
                                                }

                                                ray = band;
                                                band->set_colors(source_ray->colors[0], source_ray->colors[1], source_ray->colors[2],
                                                                 source_ray->colors[3], source_ray->colors[4]);
                                                band->inner_radius = source_ray->inner_radius;
                                                band->set_widths(source_ray->widths[0], source_ray->widths[1], source_ray->widths[2],
                                                                 source_ray->widths[3]);
                                                band->axis_offset = source_ray->axis_offset;
                                                band->alpha = source_ray->alpha;
                                                record += sizeof(LibSceneBandRayRecord);
                                                break;
                                            }
                                            case 2:
                                            {
                                                LibSceneRingRayRecord* source_ray = reinterpret_cast<LibSceneRingRayRecord*>(record);
                                                LibClass172900* ring = static_cast<LibClass172900*>(scene->func_00471480(0x22));

                                                if (!ring)
                                                {
                                                    return 0;
                                                }

                                                ray = ring;
                                                ring->color = source_ray->color;
                                                ring->inner_radius = source_ray->inner_radius;
                                                ring->width = source_ray->width;
                                                ring->segments = source_ray->segments;
                                                ring->axis_offset = source_ray->axis_offset;
                                                ring->alpha = source_ray->alpha;
                                                record += sizeof(LibSceneRingRayRecord);
                                                break;
                                            }
                                            case 3:
                                            {
                                                LibSceneSpokeRayRecord* source_ray = reinterpret_cast<LibSceneSpokeRayRecord*>(record);
                                                LibClass1728E0* spokes = static_cast<LibClass1728E0*>(scene->func_00471480(0x23));

                                                if (!spokes)
                                                {
                                                    return 0;
                                                }

                                                ray = spokes;
                                                spokes->set_colors(source_ray->centre_color, source_ray->edge_color);
                                                spokes->unk1c = source_ray->unk14;
                                                spokes->unk20 = source_ray->unk18;
                                                spokes->unk3c = source_ray->unk34;
                                                spokes->set_first_length(source_ray->unk1c, source_ray->unk20, source_ray->unk24);
                                                spokes->set_second_length(source_ray->unk28, source_ray->unk2c, source_ray->unk30);
                                                spokes->axis_offset = source_ray->axis_offset;
                                                spokes->alpha = source_ray->alpha;
                                                func_00421D80(spokes);
                                                record += sizeof(LibSceneSpokeRayRecord);
                                                break;
                                            }
                                        }

                                        rays->append(ray);
                                    }

                                    func_0046C3F0(scene, rays, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    rays->allocate_packet();
                                    scene->renderer->append_node(rays, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 23:
                                {
                                    LibLinkSystemRecord* data = reinterpret_cast<LibLinkSystemRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass173050* links = static_cast<LibClass173050*>(scene->func_00471480(0x24));
                                    scene->entries[i].handle = links;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    links->unk20 = data->unk00;
                                    s32 count = data->node_count;
                                    delete[] links->unk24;
                                    links->unk24 = new (0) LibClass173070[count];
                                    links->node_count = count;

                                    if (!links->unk24)
                                    {
                                        links->node_count = 0;
                                    }

                                    copy_vector(reinterpret_cast<LibVector4*>(&links->unk40),
                                                reinterpret_cast<const LibVector4*>(&LibClass173490Entry(data->unk04, data->unk08, data->unk0c, 1.0f)));
                                    scene->update_list->append_node(links, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 24:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172FC0* shape = static_cast<LibClass172FC0*>(scene->func_00471480(0x25));
                                    scene->entries[i].handle = shape;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    copy_vector(&shape->local_point, reinterpret_cast<const LibVector4*>(&LibClass173490Entry(0.0f, 0.0f, 0.0f, 1.0f)));
                                    copy_vector(&shape->local_axis, reinterpret_cast<const LibVector4*>(&LibClass173490Entry(0.0f, -data[1], 0.0f, 1.0f)));
                                    shape->unk214 = data[2];
                                    shape->unk220 = data[0];
                                    func_0046C3F0(scene, shape, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    scene->update_list->append_node(shape, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 25:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172F30* shape = static_cast<LibClass172F30*>(scene->func_00471480(0x26));
                                    scene->entries[i].handle = shape;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    shape->unk214 = data[1];
                                    shape->unk220 = data[0];
                                    func_0046C3F0(scene, shape, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    scene->update_list->append_node(shape, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 26:
                                {
                                    LibClass172EA0* shape = static_cast<LibClass172EA0*>(scene->func_00471480(0x27));
                                    scene->entries[i].handle = shape;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    func_0046C3F0(scene, shape, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    scene->update_list->append_node(shape, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 27:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172C60* shape = static_cast<LibClass172C60*>(scene->func_00471480(0x28));
                                    scene->entries[i].handle = shape;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    shape->set_parameters(data[0], data[1], data[2], data[3]);
                                    func_0046C3F0(scene, shape, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    D_507C40.append_node(shape, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 28:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172B40* shape = static_cast<LibClass172B40*>(scene->func_00471480(0x29));
                                    scene->entries[i].handle = shape;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    shape->set_parameters(data[0], data[1], data[2]);
                                    func_0046C3F0(scene, shape, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    D_507C40.append_node(shape, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 29:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172CF0* shape = static_cast<LibClass172CF0*>(scene->func_00471480(0x2A));
                                    scene->entries[i].handle = shape;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    shape->set_parameters(data[0], data[1]);
                                    func_0046C3F0(scene, shape, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    D_507C40.append_node(shape, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 30:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172E10* shape = static_cast<LibClass172E10*>(scene->func_00471480(0x2B));
                                    scene->entries[i].handle = shape;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    copy_vector(&shape->extent, reinterpret_cast<const LibVector4*>(&LibClass173490Entry(data[1], data[3], data[2], 1.0f)));
                                    func_0046C3F0(scene, shape, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    scene->update_list->append_node(shape, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 31:
                                {
                                    LibSceneOccluderRecord* data = reinterpret_cast<LibSceneOccluderRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass1734D0* occluder = static_cast<LibClass1734D0*>(scene->func_00471480(0x2D));
                                    scene->entries[i].handle = occluder;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    occluder->half_width = data->half_width;
                                    occluder->half_depth = data->half_depth;
                                    occluder->unk21c = data->unk08 != 0;
                                    func_00431020(occluder);
                                    func_0046C3F0(scene, occluder, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    scene->renderer->unk40d8.append_node(occluder, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 32:
                                {
                                    LibClass172D80* shape = static_cast<LibClass172D80*>(scene->func_00471480(0x2F));
                                    scene->entries[i].handle = shape;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    func_0046C3F0(scene, shape, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    scene->update_list->append_node(shape, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                            }

                            break;
                    }
                }

                break;
            }
            case 5:
                cursor = reinterpret_cast<u32*>(reinterpret_cast<u32>(cursor) + 4 + *cursor * 0x10);
                break;
            case 6:
                cursor += 0x40;
                break;
            case 7:
                cursor += 1;
                break;
            case 8:
                cursor += 5;
                break;
            case 9:
                cursor += 5;
                break;
            case 10:
                cursor += 1;
                break;
        }
    }

    for (s32 i = 0; i < scene->header->count; i++)
    {
        LibManagedEntry* entry = &scene->entries[i];
        LibEntryMetadata* metadata = entry->metadata;

        switch (metadata->kind)
        {
            case 7:
            {
                s32 count = metadata->child_count;
                LibLodController* controller;
                s32 k;
                s32* children = static_cast<s32*>(lib_get_entry_data_inline(scene, metadata));
                controller = static_cast<LibLodController*>(entry->handle);

                for (k = 0; k < count; k++)
                {
                    controller->level_boundaries[k] = controller->object_count;
                    lib_collect_entry_tree(scene, children[k], controller);
                }

                controller->level_boundaries[k] = controller->object_count;
                break;
            }
            case 20:
            {
                ResidentImageObject* image = static_cast<ResidentImageObject*>(entry->handle);

                if (image->hit_volume)
                {
                    image->hit_volume = static_cast<ResidentHitBox*>(scene->entries[reinterpret_cast<s32>(image->hit_volume)].handle);
                }

                break;
            }
            case 23:
                func_0046BAC0(scene, static_cast<LibClass173050*>(entry->handle),
                              reinterpret_cast<LibLinkSystemRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata)));
                break;
        }
    }

    func_00473E20(scene);

    for (s32 i = 0; i < scene->header->count; i++)
    {
        LibManagedEntry* entry = &scene->entries[i];
        LibEntryMetadata* metadata = entry->metadata;

        if (metadata && (metadata->state == 2 || metadata->state == 0))
        {
            u8 kind = metadata->kind;

            if (kind >= 24)
            {
                if (kind == 24 || kind == 25)
                {
                    if (!static_cast<LibClass172AB0*>(entry->handle)->unk210)
                    {
                        func_00428D20(static_cast<LibListObject*>(entry->handle), 0);
                    }
                }
                else if (kind == 26 || kind == 30 || kind == 32)
                {
                    if (!static_cast<LibClass172AB0*>(entry->handle)->unk210)
                    {
                        func_00428A50(static_cast<LibListObject*>(entry->handle), 0);
                    }
                }
            }
        }
    }

    for (s32 i = 0; i < scene->header->count; i++)
    {
        LibManagedEntry* entry = &scene->entries[i];

        if (entry->metadata)
        {
            u32 mask = entry->metadata->layer_mask;

            if (mask != 0 && !(mask & 1))
            {
                LibTransform* object = static_cast<LibTransform*>(entry->handle);

                if (object->layer)
                {
                    object->display_manager = scene->renderer->layers[object->layer - 1].display_manager;
                }
            }
        }
    }

    return result;
}

/** @brief Clear the link table and its counts. */
LibClass173070::LibClass173070()
{
    unk08 = 0;
    links = 0;
    link_count = 0;
    unk20 = 0;
}

/**
 * @brief Copy the extra vector and the transform state.
 * @param source Transform to copy.
 */
void LibClass1753A0::func_004713F0(const LibClass1753A0* source)
{
    unk210 = source->unk210;
    LibTransform::copy_offset_transform_state(source);
}

/**
 * @brief Copy the base position, then build this model from another one.
 * @param links Display list the model draws through, or null.
 * @param source Model to copy.
 * @return Nonzero on success.
 */
s32 LibClass175430::func_00471410(LibUpdateList* links, LibClass175430* source)
{
    base = source->base;
    return LibModel::build_from(links, source);
}

/**
 * @brief Create a camera.
 * @param context Resident context the camera starts from.
 * @return The new camera, or null when allocation fails.
 */
LibCamera* LibScene::func_00471440(void* context)
{
    return new (0) LibCamera(context);
}

/**
 * @brief Create an object of one kind for an entry.
 * @param kind Object kind.
 * @return The new object, or null.
 */
void* LibScene::func_00471480(u8 kind)
{
    switch (kind)
    {
    case 0:
        return new (0) LibTransform;
    case 1:
        return new (0) LibLodController;
    case 2:
        return new (0) LibModel;
    case 3:
        return new (0) LibResourceBuffer;
    case 4:
        return new (0) LibLight;
    case 6:
        return new (0) LibClass175530;
    case 7:
        return new (0) LibClass177A80;
    case 8:
        return new (0) LibClass1788B0;
    case 9:
        return new (0) LibClass1789C0;
    case 10:
        return new (0) LibClass174C70;
    case 11:
        return new (0) LibClass174CB0;
    case 12:
        return new (0) LibClass174D10;
    case 13:
        return new (0) LibClass174D50;
    case 14:
        return new (0) LibClass175430;
    case 15:
        return new (0) LibClass173C40;
    case 16:
        return new (0) LibClass173B10;
    case 17:
        return new (0) LibClass173990;
    case 18:
        return new (0) LibObject1751A0;
    case 19:
        return new (0) LibClass173870;
    case 20:
        return new (0) LibClass173900;
    case 21:
        return new (0) LibClass1737E0;
    case 22:
        return new (0) LibClass173750;
    case 23:
        return new (0) LibClass173630;
    case 24:
        return new (0) LibClass174B70;
    case 25:
        return new (0) LibClass174AC0;
    case 26:
        return new (0) LibClass174970;
    case 27:
        return new (0) LibClass174C20;
    case 28:
        return new (0) ResidentImageObject;
    case 29:
        return new (0) LibClass1753A0;
    case 30:
        return new (0) LibClass172960;
    case 31:
        return new (0) LibClass1728A0;
    case 32:
        return new (0) LibClass172940;
    case 33:
        return new (0) LibClass172920;
    case 34:
        return new (0) LibClass172900;
    case 35:
        return new (0) LibClass1728E0;
    case 36:
        return new (0) LibClass173050;
    case 37:
        return new (0) LibClass172FC0;
    case 38:
        return new (0) LibClass172F30;
    case 39:
        return new (0) LibClass172EA0;
    case 40:
        return new (0) LibClass172C60;
    case 41:
        return new (0) LibClass172B40;
    case 42:
        return new (0) LibClass172CF0;
    case 43:
        return new (0) LibClass172E10;
    case 44:
        return new (0) LibClass173380;
    case 45:
        return new (0) LibClass1734D0;
    case 46:
        return new (0) LibClass173490;
    case 47:
        return new (0) LibClass172D80;
    case 48:
        return new (0) LibTransform;
    }

    return 0;
}

/** @brief Set the vector to (0, 0, 0, 1). */
inline void LibClass173490Entry::set_identity()
{
    *(unsigned __int128*)this = 0;
    w = 1.0f;
}

/**
 * @brief Set the light's transform type ID.
 * @param type Type ID.
 */
inline void LibLight::set_light_type(u32 type)
{
    type_id = type;
}

/**
 * @brief Set all four components to one value.
 * @param value Value for every component.
 */
inline LibClass173490Entry::LibClass173490Entry(float value)
{
    x = value;
    y = value;
    z = value;
    w = value;
}

/** @brief Initialize the transform without a look-at target or roll. */
LibLookAtTransform::LibLookAtTransform()
{
    look_at_target = 0;
    roll_angle = 0.0f;
}

/**
 * @brief Read one child entry index from an entry's data.
 * @param manager Runtime entry table and source resource header.
 * @param entry_index Index of the parent entry.
 * @param child Position in the parent's child list.
 * @return Entry index of the child.
 */
s32 lib_get_entry_child_index(LibEntryManager* manager, s32 entry_index, s32 child)
{
    s32* children = (s32*)lib_get_entry_data_inline(manager, manager->entries[entry_index].metadata);
    return children[child];
}

/**
 * @brief Get the handle of one child of an entry.
 * @param manager Runtime entry table and source resource header.
 * @param entry_index Index of the parent entry.
 * @param child Position in the parent's child list.
 * @return Handle of the child entry.
 */
void* lib_get_entry_child(LibEntryManager* manager, s32 entry_index, s32 child)
{
    s32* children = (s32*)lib_get_entry_data_inline(manager, manager->entries[entry_index].metadata);
    return manager->entries[children[child]].handle;
}

/**
 * @brief Read the signed child-entry count for an indexed resource entry.
 * @param manager Runtime resource-entry manager.
 * @param index Entry index.
 * @return Signed child-entry count stored in the entry's metadata.
 */
s32 lib_get_entry_child_count(LibEntryManager* manager, s32 index)
{
    return manager->entries[index].metadata->child_count;
}

/**
 * @brief Flag an entry and the entries below it (draw flag 0x8) and add their handles to a collection.
 * @param manager Scene holding the entries.
 * @param index Entry to start from; an entry with unk00 set is skipped with everything below it.
 * @param collection Collection that receives the handles.
 */
void lib_collect_entry_tree(LibEntryManager* manager, s32 index, LibEntryHandleCollection* collection)
{
    LibManagedEntry* entry = &manager->entries[index];

    if (entry->unk00 == 0)
    {
        static_cast<LibTransformOwner*>(entry->handle)->draw_flags |= LIB_DRAW_FLAG_0008;
        lib_append_entry_handle(collection, manager->entries[index].handle);
        LibEntryMetadata* metadata = manager->entries[index].metadata;
        s32 count = metadata->child_count;
        s32 i;
        s32* children = static_cast<s32*>(lib_get_entry_data_inline(manager, metadata));

        for (i = 0; i < count; i++)
        {
            s32 child = children[i];

            if (manager->entries[child].unk00 == 0)
            {
                lib_object_add_flags(manager->entries[child].handle, LIB_DRAW_FLAG_0008);
                lib_append_entry_handle(collection, manager->entries[child].handle);
                s32 child_count = manager->entries[child].metadata->child_count;
                s32* grandchildren = static_cast<s32*>(lib_get_entry_data(manager, manager->entries[child].metadata));

                for (s32 j = 0; j < child_count; j++)
                {
                    lib_collect_entry_tree(manager, grandchildren[j], collection);
                }
            }
        }
    }
}

/**
 * @brief Add bits to the object's flags.
 * @param object Receiver.
 * @param flags Flag bits to add.
 */
void lib_object_add_flags(void* object, u16 flags)
{
    LibObjectFlags6A* state = (LibObjectFlags6A*)object;
    state->flags |= flags;
}

/**
 * @brief Locate an entry's data after its optional sixteen-byte name.
 * @param manager Manager supplying the resource format flag.
 * @param metadata Source entry metadata.
 * @return Metadata-relative entry data, skipping the name when present.
 */
void* lib_get_entry_data(LibEntryManager* manager, LibEntryMetadata* metadata)
{
    return lib_get_entry_data_inline(manager, metadata);
}

/**
 * @brief Update eligible renderable entries that pass the metadata flag filter.
 * @param manager Runtime resource-entry manager.
 */
void lib_update_renderable_entries(LibEntryManager* manager)
{
    s32 index;

    for (index = 0; index < manager->header->count; index++)
    {
        LibManagedEntry* entry = &manager->entries[index];
        void* handle = entry->handle;

        if (handle != 0 && entry->unk00 == 0)
        {
            LibEntryMetadata* metadata = entry->metadata;

            if ((metadata->state == 2 || metadata->state == 0) &&
                (metadata->kind == 1 || metadata->kind == 8) &&
                (metadata->flags & 0x4080) == 0)
            {
                func_004A2370(handle);
            }
        }
    }
}

/**
 * @brief Set resource state for eligible renderable entries.
 * @param manager Runtime resource-entry manager.
 */
void func_004724A0(LibEntryManager* manager)
{
    s32 index;

    for (index = 0; index < manager->header->count; index++)
    {
        LibManagedEntry* entry = &manager->entries[index];
        void* handle = entry->handle;

        if (handle != 0 && entry->unk00 == 0)
        {
            LibEntryMetadata* metadata = entry->metadata;

            if ((metadata->state == 2 || metadata->state == 0) &&
                (metadata->kind == 1 || metadata->kind == 8) &&
                (metadata->flags & 0x4080) == 0)
            {
                func_004A29D0(handle);
            }
        }
    }
}

/**
 * @brief Set bit 1 at 0x798 on every eligible renderable entry object.
 * @param manager Runtime resource-entry manager.
 * @param check Nonzero to skip objects whose 0x5A4 member passes func_004A9000.
 */
void func_00472570(LibEntryManager* manager, s32 check)
{
    LibManagedEntry* entry;
    s32 index;
    LibRenderableEntryObject* handle;

    if (manager->entries == 0)
    {
        return;
    }

    if (check)
    {
        for (index = 0; index < manager->header->count; index++)
        {
            entry = &manager->entries[index];
            handle = (LibRenderableEntryObject*)entry->handle;

            if (handle != 0 && entry->unk00 == 0)
            {
                LibEntryMetadata* metadata = entry->metadata;

                if ((metadata->state == 2 || metadata->state == 0) && (metadata->kind == 1 || metadata->kind == 8))
                {
                    if (!func_004A9000(handle->unk5a4))
                    {
                        handle->unk798_1 = 1;
                    }
                }
            }
        }
    }
    else
    {
        // TODO: A second index shadowing the first is the only shape I found that gets this loop's
        // registers right. It reads oddly, so I'd like to find what the original really did.
        s32 index;

        for (index = 0; index < manager->header->count; index++)
        {
            entry = &manager->entries[index];
            handle = (LibRenderableEntryObject*)entry->handle;

            if (handle != 0 && entry->unk00 == 0)
            {
                LibEntryMetadata* metadata = entry->metadata;

                if ((metadata->state == 2 || metadata->state == 0) && (metadata->kind == 1 || metadata->kind == 8))
                {
                    handle->unk798_1 = 1;
                }
            }
        }
    }
}

/**
 * @brief Pass every eligible renderable entry object to func_004A22C0, or clear bit 0 of its byte at 0xF.
 * @param manager Runtime resource-entry manager.
 * @param enable Nonzero to call func_004A22C0; zero to clear the bit.
 */
void func_00472720(LibEntryManager* manager, s32 enable)
{
    LibManagedEntry* entry;
    LibRenderableEntryObject* handle;

    if (manager->entries == 0)
    {
        return;
    }

    if (enable)
    {
        s32 index;

        for (index = 0; index < manager->header->count; index++)
        {
            entry = &manager->entries[index];
            handle = (LibRenderableEntryObject*)entry->handle;

            if (handle != 0 && entry->unk00 == 0)
            {
                LibEntryMetadata* metadata = entry->metadata;

                if ((metadata->state == 2 || metadata->state == 0) && (metadata->kind == 1 || metadata->kind == 8))
                {
                    func_004A22C0(handle);
                }
            }
        }
    }
    else
    {
        s32 index;

        for (index = 0; index < manager->header->count; index++)
        {
            entry = &manager->entries[index];
            handle = (LibRenderableEntryObject*)entry->handle;

            if (handle != 0 && entry->unk00 == 0)
            {
                LibEntryMetadata* metadata = entry->metadata;

                if ((metadata->state == 2 || metadata->state == 0) && (metadata->kind == 1 || metadata->kind == 8))
                {
                    handle->unk0f &= ~1;
                }
            }
        }
    }
}

/**
 * @brief Turn fogging on or off for the scene's models and its emitters' image models.
 * @param manager Scene.
 * @param enabled Nonzero for fog.
 * @param check Nonzero to skip entries with metadata flag 0x4.
 */
void func_004728A0(LibEntryManager* manager, u8 enabled, s32 check)
{
    if (manager->entries == 0)
    {
        return;
    }

    for (s32 index = 0; index < manager->header->count; index++)
    {
        LibManagedEntry* entry = &manager->entries[index];
        void* handle = entry->handle;

        if (handle != 0 && entry->unk00 == 0)
        {
            LibEntryMetadata* metadata = entry->metadata;

            if (metadata->state == 2 || metadata->state == 0)
            {
                if (metadata->kind == 1 || metadata->kind == 8)
                {
                    if (!check || !(metadata->flags & 4))
                    {
                        static_cast<LibColorModel*>(handle)->set_fog_enabled(enabled);
                    }
                }
                else if (metadata->kind == 10)
                {
                    if (!check || !(metadata->flags & 4))
                    {
                        LibClass173990* emitter = static_cast<LibClass173990*>(handle);

                        if (emitter && !emitter->unk49b_0)
                        {
                            emitter->source->set_fog_enabled(enabled);
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief Add draw flags to an object.
 * @param object Object (LibTransformOwner).
 * @param flags Flags to add.
 */
static inline void lib_add_draw_flags(void* object, u16 flags)
{
    static_cast<LibTransformOwner*>(object)->set_draw_flags(static_cast<LibTransformOwner*>(object)->get_draw_flags() | flags);
}

/**
 * @brief Remove draw flags from an object.
 * @param object Object (LibTransformOwner).
 * @param flags Flags to remove.
 */
static inline void lib_remove_draw_flags(void* object, u16 flags)
{
    static_cast<LibTransformOwner*>(object)->set_draw_flags(static_cast<LibTransformOwner*>(object)->get_draw_flags() & ~flags);
}

/**
 * @brief Add draw flags to an emitter's image model, unless the emitter has none.
 * @param emitter Emitter, or null.
 * @param flags Flags to add.
 */
static inline void lib_emitter_add_draw_flags(LibClass173990* emitter, u16 flags)
{
    if (emitter && !emitter->unk49b_0)
    {
        lib_add_draw_flags(emitter->source, flags);
    }
}

/**
 * @brief Remove draw flags from an emitter's image model, unless the emitter has none.
 * @param emitter Emitter, or null.
 * @param flags Flags to remove.
 */
static inline void lib_emitter_remove_draw_flags(LibClass173990* emitter, u16 flags)
{
    if (emitter && !emitter->unk49b_0)
    {
        lib_remove_draw_flags(emitter->source, flags);
    }
}

/**
 * @brief Hide or show every loaded, active entry of a scene, except kind 0x17; emitters (kind 10) pass it to their
 *        image model.
 * @param scene Scene whose entries change.
 * @param hidden Nonzero to hide, zero to show.
 */
extern "C" void func_00472A00(LibEntryManager* scene, s32 hidden)
{
    s32 index;

    if (scene->entries == 0)
    {
        return;
    }

    for (index = 0; index < scene->header->count; index++)
    {
        void* handle;
        LibManagedEntry* entry = &scene->entries[index];

        handle = entry->handle;

        if (handle != 0 && entry->unk00 == 0)
        {
            LibEntryMetadata* metadata = entry->metadata;

            if ((metadata->state == 2 || metadata->state == 0) && metadata->kind != 0x17)
            {
                if (hidden)
                {
                    if (metadata->kind == 10)
                    {
                        lib_emitter_add_draw_flags(static_cast<LibClass173990*>(handle), LIB_DRAW_HIDDEN);
                    }
                    else
                    {
                        lib_add_draw_flags(scene->entries[index].handle, LIB_DRAW_HIDDEN);
                    }
                }
                else
                {
                    if (metadata->kind == 10)
                    {
                        lib_emitter_remove_draw_flags(static_cast<LibClass173990*>(handle), LIB_DRAW_HIDDEN);
                    }
                    else
                    {
                        lib_remove_draw_flags(scene->entries[index].handle, LIB_DRAW_HIDDEN);
                    }
                }
            }
        }
    }
}

/**
 * @brief Copy an entry's name into a buffer.
 * @param manager Runtime entry table and source resource header.
 * @param index Entry index.
 * @param name Buffer of at least seventeen bytes; emptied first.
 * @return name, or null when the resource has no names.
 */
char* lib_copy_entry_name(LibEntryManager* manager, s32 index, char* name)
{
    LibEntryMetadata* metadata;

    name[0] = 0;

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES))
    {
        return 0;
    }

    metadata = manager->entries[index].metadata;
    strncpy_guess(name, (const char*)metadata + metadata->data_offset, LIB_ENTRY_NAME_COMPARE_LENGTH);
    name[LIB_ENTRY_NAME_COMPARE_LENGTH] = 0;
    return name;
}

/**
 * @brief Copy the name of the entry that owns a handle into a buffer.
 * @param manager Runtime entry table and source resource header.
 * @param handle Entry handle to look for.
 * @param name Buffer of at least seventeen bytes; emptied first.
 * @return name, or null when the resource has no names or no entry owns the handle.
 */
char* lib_copy_handle_entry_name(const LibEntryManager* manager, void* handle, char* name)
{
    s32 index;
    const LibEntryMetadata* metadata;

    name[0] = 0;

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES))
    {
        return 0;
    }

    index = lib_find_entry_index_inline(manager, handle);

    if (index < 0)
    {
        return 0;
    }

    metadata = manager->entries[index].metadata;
    strncpy_guess(name, (const char*)metadata + metadata->data_offset, LIB_ENTRY_NAME_COMPARE_LENGTH);
    name[LIB_ENTRY_NAME_COMPARE_LENGTH] = 0;
    return name;
}

/**
 * @brief Find the next kind-5 entry after the entry that owns a handle.
 * @param manager Runtime entry table and source resource header.
 * @param handle Handle of the current entry.
 * @return The next entry of kind 5 that passes the state filter, or null.
 */
void* func_00472C90(const LibEntryManager* manager, void* handle)
{
    s32 found;
    s32 index;

    if (manager->entries == 0)
    {
        return 0;
    }

    found = lib_find_entry_index_inline(manager, handle);

    if (found >= 0)
    {
        index = found;

        for (;;)
        {
            index++;

            if (index >= manager->header->count || index == found)
            {
                break;
            }

            if (manager->entries[index].metadata != 0 && (manager->entries[index].metadata->state == 2 || manager->entries[index].metadata->state == 0) &&
                manager->entries[index].metadata->kind == 5)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find the next kind-10 entry after the entry that owns a handle.
 * @param manager Runtime entry table and source resource header.
 * @param handle Handle of the current entry.
 * @return The next entry of kind 10 that passes the state filter, or null.
 */
void* func_00472DA0(const LibEntryManager* manager, void* handle)
{
    s32 found;
    s32 index;

    if (manager->entries == 0)
    {
        return 0;
    }

    found = lib_find_entry_index_inline(manager, handle);

    if (found >= 0)
    {
        index = found;

        for (;;)
        {
            index++;

            if (index >= manager->header->count || index == found)
            {
                break;
            }

            if (manager->entries[index].metadata != 0 && (manager->entries[index].metadata->state == 2 || manager->entries[index].metadata->state == 0) &&
                manager->entries[index].metadata->kind == 10)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find the next renderable entry after the entry that owns a handle.
 * @param manager Runtime entry table and source resource header.
 * @param handle Handle of the current entry, as returned by lib_find_renderable_entry.
 * @return The next entry of kind 1 or 8 that passes the state filter, or null.
 */
void* lib_find_next_renderable_entry(const LibEntryManager* manager, void* handle)
{
    s32 found;
    s32 index;

    if (manager->entries == 0)
    {
        return 0;
    }

    found = lib_find_entry_index_inline(manager, handle);

    if (found >= 0)
    {
        index = found;

        for (;;)
        {
            index++;

            if (index >= manager->header->count || index == found)
            {
                break;
            }

            if (manager->entries[index].metadata != 0 && (manager->entries[index].metadata->state == 2 || manager->entries[index].metadata->state == 0) &&
                (manager->entries[index].metadata->kind == 1 || manager->entries[index].metadata->kind == 8))
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find the index of the entry that owns a handle.
 * @param manager Runtime entry table and source resource header.
 * @param handle Entry handle to look for.
 * @return Index of the first entry with metadata whose handle matches, or -1.
 */
s32 lib_find_entry_index(const LibEntryManager* manager, void* handle)
{
    return lib_find_entry_index_inline(manager, handle);
}

/**
 * @brief Find a kind-10 entry whose metadata passes the state and name filters.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching handle, or null.
 */
void* func_00473040(LibEntryManager* manager, const char* name)
{
    u8 any_name = 0;
    s32 index;

    if (name == 0 || name[0] == 0)
    {
        any_name = 1;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES) && !any_name)
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && (metadata->state == 2 || metadata->state == 0) &&
            metadata->kind == 10)
        {
            if (any_name || lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset,
                                                        LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find the first kind-5 entry that passes the state filter.
 * @param manager Runtime entry table and source resource header.
 * @return The first matching handle, or null.
 */
void* func_004731A0(const LibEntryManager* manager)
{
    s32 index;

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        if (manager->entries[index].metadata != 0 && (manager->entries[index].metadata->state == 2 || manager->entries[index].metadata->state == 0) &&
            manager->entries[index].metadata->kind == 5)
        {
            return manager->entries[index].handle;
        }
    }

    return 0;
}

/**
 * @brief Find a named entry by searching circularly from the last successful index.
 * @param manager Runtime entry table and source metadata.
 * @param name Entry name; null returns no entry.
 * @param checksum Precomputed signed-byte name sum, or zero to calculate it from up to sixteen characters.
 * @return Matching entry handle, or null.
 */
void* lib_find_named_entry_cached(LibEntryManager* manager, const char* name, s32 checksum)
{
    s32 index;
    s32 scanned;

    if (!name)
    {
        return 0;
    }

    if (!checksum)
    {
        s32 name_index;

        for (name_index = 0; name_index < LIB_ENTRY_NAME_COMPARE_LENGTH; name_index++)
        {
            s32 byte = (s8)name[name_index];

            if (!byte)
            {
                break;
            }

            checksum += byte;
        }
    }

    index = manager->cached_entry_index;

    for (scanned = 0; scanned < manager->header->count; scanned++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata && checksum == metadata->name_checksum &&
            lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset, LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
        {
            manager->cached_entry_index = index;
            return manager->entries[index].handle;
        }

        index++;

        if (index >= manager->header->count)
        {
            index = 0;
        }
    }

    return 0;
}

/**
 * @brief Find an entry by name.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null to take the first entry with metadata.
 * @return Handle of the first entry whose name checksum and name match, or null.
 */
void* lib_find_named_entry(const LibEntryManager* manager, const char* name)
{
    s32 checksum;
    s32 name_index;
    s32 index;
    s32 first;

    if (name == 0)
    {
        for (first = 0; first < manager->header->count; first++)
        {
            if (!lib_entry_is_empty(&manager->entries[first]))
            {
                return manager->entries[first].handle;
            }
        }

        return 0;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES))
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    checksum = 0;

    for (name_index = 0; name_index < LIB_ENTRY_NAME_COMPARE_LENGTH; name_index++)
    {
        s32 byte = (s8)name[name_index];

        if (!byte)
        {
            break;
        }

        checksum += byte;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        const LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && checksum == metadata->name_checksum &&
            lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset, LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
        {
            return manager->entries[index].handle;
        }
    }

    return 0;
}

/**
 * @brief Find a transform entry (metadata state 1 or 3) by name.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching transform handle, or null.
 */
void* lib_find_transform_entry(LibEntryManager* manager, const char* name)
{
    u8 any_name = 0;
    s32 index;

    if (name == 0 || name[0] == 0)
    {
        any_name = 1;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES) && !any_name)
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && (metadata->state == 1 || metadata->state == 3))
        {
            if (any_name || lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset, LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find a camera entry whose metadata passes the state and name filters.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching camera handle, or null.
 */
void* lib_find_camera_entry(LibEntryManager* manager, const char* name)
{
    u8 any_name = 0;
    s32 index;

    if (name == 0 || name[0] == 0)
    {
        any_name = 1;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES) && !any_name)
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && (metadata->state == 2 || metadata->state == 0) &&
            metadata->kind == LIB_ENTRY_KIND_CAMERA)
        {
            if (any_name || lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset,
                                                        LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find a light entry whose metadata passes the state and name filters.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching light handle, or null.
 */
void* lib_find_light_entry(LibEntryManager* manager, const char* name)
{
    u8 any_name = 0;
    s32 index;

    if (name == 0 || name[0] == 0)
    {
        any_name = 1;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES) && !any_name)
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && (metadata->state == 2 || metadata->state == 0) &&
            metadata->kind == LIB_ENTRY_KIND_LIGHT)
        {
            if (any_name || lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset,
                                                        LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find a renderable entry of kind 1 or 8 whose metadata passes the state and name filters.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching renderable handle, or null.
 */
void* lib_find_renderable_entry(LibEntryManager* manager, const char* name)
{
    u8 any_name = 0;
    s32 index;

    if (name == 0 || name[0] == 0)
    {
        any_name = 1;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES) && !any_name)
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && (metadata->state == 2 || metadata->state == 0) &&
            (metadata->kind == 1 || metadata->kind == 8))
        {
            if (any_name || lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset,
                                                        LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Let go of an emitter's image model, queueing its grid when nothing else uses it, then destroy the emitter.
 * @param emitter Emitter, or null.
 */
static inline void lib_scene_release_emitter(LibClass173990* emitter)
{
    if (emitter)
    {
        LibObject1751A0* source = emitter->source;

        if (source)
        {
            LibGridBase* grid = source->reference;
            func_0046B3F0(source);

            if (grid && grid->user_count == 0)
            {
                resident_enqueue_object(g_resident_release_queues, grid);
            }
        }

        emitter->destroy();
    }
}

/**
 * @brief Release the scene's entries (detach and free what they created).
 * @param scene Scene.
 */
void lib_scene_release_entries(LibEntryManager* scene)
{
    if (scene->entries == 0)
    {
        return;
    }

    for (s32 index = 0; index < scene->header->count; index++)
    {
        LibManagedEntry* entry = &scene->entries[index];

        switch (entry->unk00)
        {
        case 1:
            if (entry->handle)
            {
                resident_enqueue_object(g_resident_release_queues, entry->handle);
            }

            break;
        }
    }

    for (s32 index = 0; index < scene->header->count; index++)
    {
        LibManagedEntry* entry = &scene->entries[index];

        switch (entry->unk00)
        {
        case 0:
            u8 kind = entry->metadata->kind;

            if (kind == 10)
            {
                LibClass173990* emitter = static_cast<LibClass173990*>(entry->handle);

                if (emitter)
                {
                    lib_scene_release_emitter(emitter);
                }
            }
            else if (kind == 0x17)
            {
                if (entry->handle)
                {
                    lib_object_detach_owner(entry->handle);
                    static_cast<LibListObject*>(scene->entries[index].handle)->destroy();
                }
            }
            else if (entry->handle)
            {
                static_cast<LibListObject*>(entry->handle)->destroy();
            }

            break;
        }
    }

    LibClass175390* node = static_cast<LibClass175390*>(scene->unk80.sentinel.next);

    for (;;)
    {
        if (&scene->unk80.sentinel == node)
        {
            break;
        }

        LibClass175390* next = static_cast<LibClass175390*>(node->next);
        scene->unk80.unlink(node);
        delete node->items;
        delete node;
        node = next;
    }

    delete[] scene->entries;
    scene->entries = 0;

    for (s32 slot = 0; slot < LIB_ENTRY_MANAGER_SLOT_COUNT; slot++)
    {
        LibAnimation* animation = scene->unk34[slot];

        if (animation)
        {
            if (scene->unk9f[slot])
            {
                animation->secondary_binding_owner = 0;
                lib_animation_clear_targets_by_kind(animation, 8);
            }
            else
            {
                animation->primary_binding_owner = 0;
                lib_animation_clear_targets(animation);
            }

            scene->unk34[slot] = 0;
        }
    }
}

/** @brief Destroy the node. */
LibClass175390::~LibClass175390()
{
}

/**
 * @brief Point each linked entry's objects at the entries they name in the linked manager.
 * @param manager Runtime entry table with its link names and linked manager.
 */
void func_00473E20(LibEntryManager* manager)
{
    s32 count;
    s32 index;

    if (manager->link_count != 0 && manager->linked != 0)
    {
        count = manager->header->count;

        for (index = 0; index < count; index++)
        {
            LibManagedEntry* entry = &manager->entries[index];

            if (entry->unk00 == 0)
            {
                s32 link = entry->metadata->link;

                if (link < 0 && entry->handle != 0)
                {
                    LibByte790Counter* target = (LibByte790Counter*)lib_find_named_entry_cached(manager->linked, manager->link_names[-1 - link], 0);

                    if (target)
                    {
                        switch (manager->entries[index].metadata->kind)
                        {
                        case 23:
                            break;

                        case 1:
                            if (manager->entries[index].metadata->flags & 0x80)
                            {
                                LibLinkTarget* object = (LibLinkTarget*)manager->entries[index].handle;

                                if (object->unk6c == 0x110)
                                {
                                    object->unk838 = target;
                                    target->unk790++;
                                }
                                else
                                {
                                    object->unk830 = target;
                                    target->unk790++;
                                }
                            }

                            if (manager->entries[index].metadata->flags & 0x4000)
                            {
                                ((LibLinkTarget*)manager->entries[index].handle)->unk830 = target;
                                target->unk790++;
                            }

                            ((LibLinkTarget*)manager->entries[index].handle)->unk208 = target;
                            break;

                        case 10:
                        {
                            LibLinkGroup* group = (LibLinkGroup*)manager->entries[index].handle;

                            if (group->object && group->unk499_1)
                            {
                                group->object->unk208 = target;
                            }
                        }

                        /* fall through */

                        default:
                            ((LibLinkTarget*)manager->entries[index].handle)->unk208 = target;
                            break;
                        }
                    }
                    else
                    {
                        ((LibLinkTarget*)manager->entries[index].handle)->unk208 = 0;
                    }
                }
            }
        }
    }
}

/** Scene chunk of type 4: the ambient colour, camera defaults and the format word. */
struct LibSceneSettingsChunk
{
    float ambient[3];
    u8 unk0c;
    u8 unk0d;
    u8 unk0e;
    u8 unk0f;
    u32 unk10;
    s32 unk14;
    s32 unk18;
    u32 format;
};

/** Scene chunks of types 8 and 9: one renderer fog record. */
struct LibSceneFogChunk
{
    float unk00;
    float unk04;
    s32 unk08;
    u8 unk0c;
    u8 unk0d;
    u8 unk0e;
    u8 unk0f;
    u8 unk10;
};

/** Kind-7 entry data: LOD level count and ranges. */
struct LibSceneLodRecord
{
    s32 level_count;
    float minimums[8];
    float maximums[8];
};

/** Kind-20 entry data: a resident image object's hit settings. */
struct LibSceneImageObjectRecord
{
    u32 hit_volume;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
    float unk10;
    float unk14;
    float unk18;
    float unk1c;
    u32 hit_mask;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    u8 animated;
    u8 faces_target;
    u8 unk29;
    u8 unk2a;
    u8 unk2b;
    u8 unk2c;
    u8 unk2d;
    u8 unk2e;
};

/** Kind-18 entry data: a sampled sprite. */
struct LibSceneSpriteRecord
{
    u8 unk00;
    u8 rows;
    u8 columns;
    u8 unk03;
    u8 blend_mode;
    float position[3];
    float values[3];
    float unk20;
    float unk24;
    float first_color[4];
    float second_color[4];
    float unk48;
    float unk4c;
};

/** Kind-19 entry data: a waving image grid. */
struct LibSceneGridImageRecord
{
    u8 columns;
    u8 rows;
    u8 unk02;
    u8 blend_mode;
    float amplitude;
    float frequency;
    float phase;
    float unk10[3];
    float half_width;
    float half_height;
    float color[4];
    float unk34;
    float unk38;
};

/** Pack four 0..2 colour channels into an RGBA word. */
#define LIB_SCENE_PACK_COLOR(c)                                                                                        \
    ((s32)(128.0f * (c)[0]) | ((s32)(128.0f * (c)[1]) << 8) | ((s32)(128.0f * (c)[2]) << 16) |                      \
     ((s32)(128.0f * (c)[3]) << 24))

/** Set an entry object's effect draw flags from the entry flags and move it to the given list kind for each. */
#define LIB_SCENE_SET_EFFECT_KINDS(scene, i, metadata, kind)                                                         \
    if ((metadata)->flags & 0x10)                                                                                    \
    {                                                                                                                \
        static_cast<LibTransform*>((scene)->entries[i].handle)->draw_flags |= 0x80;                                 \
        lib_object_set_list_kind(static_cast<LibListObject*>((scene)->entries[i].handle), kind);                     \
    }                                                                                                                \
    if ((metadata)->flags & 0x20)                                                                                    \
    {                                                                                                                \
        static_cast<LibTransform*>((scene)->entries[i].handle)->draw_flags |= 0x100;                                \
        lib_object_set_list_kind(static_cast<LibListObject*>((scene)->entries[i].handle), kind);                     \
    }                                                                                                                \
    if ((metadata)->flags & 0x40)                                                                                    \
    {                                                                                                                \
        static_cast<LibTransform*>((scene)->entries[i].handle)->draw_flags |= 0x200;                                \
        lib_object_set_list_kind(static_cast<LibListObject*>((scene)->entries[i].handle), kind);                     \
    }

/**
 * @brief Copy a fog chunk into a renderer pass.
 * @param pass Pass to set.
 * @param fog Fog chunk.
 */
static inline void lib_scene_read_fog(LibRendererPass* pass, const LibSceneFogChunk* fog)
{
    pass->unka0 = fog->unk00;
    pass->unka4 = fog->unk04;
    pass->unka8 = fog->unk08;
    pass->unkac = fog->unk0c;
    pass->unkad = fog->unk0d;
    pass->unkaf = fog->unk0f != 0;
    pass->unkae = fog->unk10 != 0;
}

/** Set a model entry's fog bits, effect draw flags and list kinds from the entry flags. */
#define LIB_SCENE_SET_MODEL_FLAGS(scene, i, metadata, model)                                                         \
    if (D_001B6550)                                                                                                  \
    {                                                                                                                \
        (model)->unk59d_1 = !((metadata)->flags & 0x2000);                                                           \
        (model)->unk59d_0 = 1;                                                                                       \
    }                                                                                                                \
    if ((metadata)->flags & 2)                                                                                       \
    {                                                                                                                \
        static_cast<LibTransform*>((scene)->entries[i].handle)->draw_flags |= 4;                                     \
        lib_object_set_list_kind(static_cast<LibTransform*>((scene)->entries[i].handle), 9);                         \
    }                                                                                                                \
    LIB_SCENE_SET_EFFECT_KINDS(scene, i, metadata, 9)                                                                \
    if ((metadata)->flags & 8)                                                                                       \
    {                                                                                                                \
        static_cast<LibTransform*>((scene)->entries[i].handle)->draw_flags |= 0x20;                                  \
    }                                                                                                                \
    if ((D_001B6594 || ((metadata)->flags & 0x100)) && !D_001B6550)                                                  \
    {                                                                                                                \
        (model)->unk59d_1 = 1;                                                                                       \
        (model)->unk59d_0 = 1;                                                                                       \
    }                                                                                                                \
    if ((metadata)->flags & 0x200)                                                                                   \
    {                                                                                                                \
        (model)->unk797_5 = 1;                                                                                       \
    }                                                                                                                \
    if ((metadata)->flags & 0x400)                                                                                   \
    {                                                                                                                \
        (model)->unk59c = 2;                                                                                         \
        (model)->unk59d_0 = 1;                                                                                       \
    }

/** Kind-2 entry data: a light. */
struct LibSceneLightRecord
{
    u8 type;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    u32 target;
    float color[3];
    float intensity;
    float cone_angle;
    float unk1c;
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
    float unk30;
    u32 mask;
    u8 unk38;
    u8 unk39;
    u8 unk3a;
    u8 unk3b;
    float unk3c;
    u8 unk40;
    u8 unk41;
    u8 unk42;
};

/** Kind-3 entry data: a camera. */
struct LibSceneCameraRecord
{
    float fov;
    u32 target;
    float near_clip;
    float far_clip;
    float unk10;
    u32 unk14;
};

/**
 * @brief Set a light's colour, leaving its intensity.
 * @param light Light to update.
 * @param red Red.
 * @param green Green.
 * @param blue Blue.
 */
static inline void lib_light_set_color(LibLight* light, float red, float green, float blue)
{
    light->color.x = red;
    light->color.y = green;
    light->color.z = blue;
}

/**
 * @brief Recompute a light's attenuation term from its range.
 * @param light Light to update.
 */
static inline void lib_light_update_attenuation(LibLight* light)
{
    switch (light->unk28b)
    {
        case 0:
        case 1:
            light->unk280 = light->unk268 / light->unk27c;
            break;
        case 2:
            light->unk280 = (light->unk268 * light->unk268) / (light->unk27c * light->unk27c);
            break;
    }
}

/** Chunk-6 record: a scene camera to put on one of the renderer's layers. */
struct LibSceneCameraSlot
{
    s32 index;
    u8 unk04;
    u8 type;
    u8 unk06[2];
};

/**
 * @brief Set a transform's offset translation (w one), rebuild its offset matrix and mark it dirty.
 * @param object Transform.
 * @param x Translation x.
 * @param y Translation y.
 * @param z Translation z.
 */
static inline void lib_scene_set_offset_translation(LibTransform* object, float x, float y, float z)
{
    object->offset_translation.x = x;
    object->offset_translation.y = y;
    object->offset_translation.z = z;
    object->offset_translation.w = 1.0f;
    lib_rebuild_offset_transform(object);
    lib_transform_set_dirty(object, 1);
}

/**
 * @brief Set a transform's offset rotation quaternion, rebuild its offset matrix and mark it dirty.
 * @param object Transform.
 * @param x Quaternion x.
 * @param y Quaternion y.
 * @param z Quaternion z.
 * @param w Quaternion w.
 */
static inline void lib_scene_set_offset_rotation(LibTransform* object, float x, float y, float z, float w)
{
    object->offset_rotation.x = x;
    object->offset_rotation.y = y;
    object->offset_rotation.z = z;
    object->offset_rotation.w = w;
    lib_rebuild_offset_transform(object);
    lib_transform_set_dirty(object, 1);
}

/**
 * @brief Set a transform's offset scale, rebuild its offset matrix and mark it dirty.
 * @param object Transform.
 * @param x Scale x.
 * @param y Scale y.
 * @param z Scale z.
 */
static inline void lib_scene_set_offset_scale(LibTransform* object, float x, float y, float z)
{
    object->offset_scale.x = x;
    object->offset_scale.y = y;
    object->offset_scale.z = z;
    lib_rebuild_offset_transform(object);
    lib_transform_set_dirty(object, 1);
}

/**
 * @brief Set a light's two cached cone terms.
 * @param light Light to update.
 * @param inner Squared cosine of the inner half-angle.
 * @param reciprocal Reciprocal of the falloff range.
 */
static inline void lib_light_set_cone_terms(LibLight* light, float inner, float reciprocal)
{
    light->unk26c = inner;
    light->unk270 = reciprocal;
}

/**
 * @brief Set the four components of a vector.
 * @param vector Vector to set.
 * @param x X.
 * @param y Y.
 * @param z Z.
 * @param w W.
 */
static inline void lib_vector_set(FieldVec4B* vector, float x, float y, float z, float w)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
    vector->w = w;
}

/**
 * @brief Set a camera's near and far clip depths.
 * @param camera Camera.
 * @param near_clip Near depth.
 * @param far_clip Far depth.
 */
static inline void lib_camera_set_clip_depths(LibCamera* camera, float near_clip, float far_clip)
{
    camera->screen_min.z = near_clip;
    camera->screen_max.z = far_clip;
}

/**
 * @brief Set a bouncing object's flag and radius.
 * @param object Object.
 * @param flag Flag.
 * @param radius Radius.
 */
static inline void lib_scene_set_bounce(LibClass173C40* object, u8 flag, float radius)
{
    object->unk222[0] = flag;
    object->radius = radius;
}

/**
 * @brief Set the first two components of a vector.
 * @param vector Vector.
 * @param x X.
 * @param y Y.
 */
static inline void lib_vector_set_xy(LibVector4* vector, float x, float y)
{
    vector->x = x;
    vector->y = y;
}

/**
 * @brief Set a sampled sprite's sizes, colours and blend mode.
 * @param sprite Sprite.
 * @param size Size.
 * @param extent Extent, also its cull radius.
 * @param first_color First colour.
 * @param second_color Second colour.
 * @param alpha ALPHA register value.
 */
static inline void lib_sprite_set_style(LibClass174AC0* sprite, float size, float extent, u32 first_color, u32 second_color,
                                        u32 alpha)
{
    sprite->unk284 = size;
    sprite->unk288 = extent;
    sprite->first_color = first_color;
    sprite->second_color = second_color;
    sprite->alpha = alpha;
    sprite->unk248 = extent;
}

/**
 * @brief Set a grid's row wave.
 * @param grid Grid.
 * @param amplitude Amplitude.
 * @param frequency Frequency.
 * @param phase Phase in turns.
 */
static inline void lib_grid_set_row_wave(LibClass174970* grid, float amplitude, float frequency, float phase)
{
    grid->row_amplitude = amplitude;
    grid->row_frequency = frequency;
    grid->row_phase = phase;
}

/**
 * @brief Set a grid's column wave.
 * @param grid Grid.
 * @param amplitude Amplitude.
 * @param frequency Frequency.
 * @param phase Phase in turns.
 */
static inline void lib_grid_set_column_wave(LibClass174970* grid, float amplitude, float frequency, float phase)
{
    grid->column_amplitude = amplitude;
    grid->column_frequency = frequency;
    grid->column_phase = phase;
}

/**
 * @brief Centre a grid on its origin with the given half extents.
 * @param grid Grid.
 * @param half_width Half the width.
 * @param half_height Half the height.
 */
static inline void lib_grid_set_extent(LibClass174970* grid, float half_width, float half_height)
{
    grid->left = -half_width;
    grid->top = -half_height;
    grid->width = 2.0f * half_width;
    grid->height = 2.0f * half_height;
}

/**
 * @brief Set a sprite's fade start and end distances.
 * @param sprite Sprite.
 * @param start Fade start.
 * @param end Fade end.
 */
static inline void lib_sprite_set_fade(LibClass1748D0* sprite, float start, float end)
{
    sprite->unk24c = start;
    sprite->unk250 = end;
}

/**
 * @brief Pack four 0..2 colour channels into an RGBA word.
 * @param color Channels.
 * @return The packed colour.
 */
static inline u32 lib_scene_pack_color(const float* color)
{
    return (s32)(128.0f * color[0]) | ((s32)(128.0f * color[1]) << 8) | ((s32)(128.0f * color[2]) << 16) |
           ((s32)(128.0f * color[3]) << 24);
}

/**
 * @brief Set a grid's colour and blend mode.
 * @param grid Grid.
 * @param color Packed colour.
 * @param alpha ALPHA register value.
 */
static inline void lib_grid_set_color(LibClass174970* grid, u32 color, u32 alpha)
{
    grid->unk298 = color;
    grid->alpha = alpha;
}

/**
 * @brief Set an image object's anchor and mark its transform dirty.
 * @param object Image object.
 * @param x Anchor x.
 * @param y Anchor y.
 */
static inline void lib_image_object_set_anchor(ResidentImageObject* object, float x, float y)
{
    object->unk220 = x;
    object->unk224 = y;
    lib_transform_set_dirty(object, 1);
}

/**
 * @brief Set a box shape's half extents.
 * @param object Shape.
 * @param x Half extent along x.
 * @param z Half extent along z.
 */
static inline void lib_shape_set_extent(LibClass172D80* object, float x, float z)
{
    object->extent_x = x;
    object->extent_z = z;
}

/**
 * @brief Return whether a model's child list has a payload buffer for a set.
 * @param children Child list.
 * @param set Payload set.
 * @return Nonzero when the buffer exists.
 */
static inline u8 lib_model_children_have_payload(LibClass177A20* children, s32 set)
{
    return children->payload_buffers[set] != 0;
}

/**
 * @brief Make a camera follow an anchor.
 * @param camera Camera.
 * @param anchor Transform to follow.
 */
static inline void lib_camera_follow(LibCamera* camera, LibTransform* anchor)
{
    camera->mode = 1;
    camera->anchor = anchor;
}

/**
 * @brief Set a light list's ambient colour, clamping negative channels to zero.
 * @param lights Light list.
 * @param red Red.
 * @param green Green.
 * @param blue Blue.
 */
static inline void lib_light_list_set_ambient(LibLightList* lights, float red, float green, float blue)
{
    if (red < 0.0f)
    {
        red = 0.0f;
    }

    if (green < 0.0f)
    {
        green = 0.0f;
    }

    if (blue < 0.0f)
    {
        blue = 0.0f;
    }

    lights->unk310.x = red;
    lights->unk310.y = green;
    lights->unk310.z = blue;
}

/**
 * @brief Set a skinned model's unk864 and unk868.
 * @param model Model.
 * @param first unk864.
 * @param second unk868.
 */
static inline void lib_skinned_set_unk864(LibClass1788B0* model, float first, float second)
{
    model->unk864 = first;
    model->unk868 = second;
}

/**
 * @brief Point a scene at the link name table in its object block.
 * @param scene Scene.
 * @param cursor Chunk data: the name count, then the 16-byte names.
 * @return The data after the table.
 */
static inline u32* lib_scene_read_links(LibScene* scene, u32* cursor)
{
    scene->link_count = *cursor++;
    scene->link_names = reinterpret_cast<char(*)[LIB_ENTRY_NAME_COMPARE_LENGTH]>(cursor);
    return cursor + scene->link_count * 4;
}

#define LIB_SCENE_SHAPE_MAGIC 0x4CF139D0

extern "C" u8 D_001B658C;
extern "C" u8 D_001B6590;
extern "C" u8 D_001B6594;
extern "C" LibListObject* D_001B6598;

// TODO: The game expands only the inline calls written directly in this function; the vector, dirty-flag and list
// node helpers those call stay out-of-line copies. Inline depth 1 gives exactly that, but I don't know what the
// original did.
#pragma push
#pragma inline_depth(1)
extern "C" s32 lib_scene_build_objects(LibScene* scene, LibCameraContext* display, LibUpdateList* list, LibLightList* lights,
                                        LibDisplayManager* manager, LibRenderer* renderer, u8 flag)
{
    FieldVec4B quaternion;
    u32* cursor;
    LibSceneSettingsChunk* settings;
    LibSceneCameraSlot* camera_table;
    LibClass173380* lod_parent;
    bool allow_lod_parents;

    if (!scene->data)
    {
        return 0;
    }

    u8* block = reinterpret_cast<u8*>((reinterpret_cast<u32>(scene->data) + 127) & ~127);

    for (;;)
    {
        if (*reinterpret_cast<u32*>(block) == 0x535346)
        {
            break;
        }

        u32 next = reinterpret_cast<u32*>(block)[3];
        block = next == 0 ? 0 : block + next;

        if (!block)
        {
            return 0;
        }
    }

    scene->renderer = renderer;
    settings = 0;
    scene->update_list = list;
    camera_table = 0;
    scene->light_list = lights;
    lod_parent = 0;
    scene->display_manager = manager;
    allow_lod_parents = 0;
    scene->link_names = 0;
    scene->link_count = 0;
    scene->unk1c = reinterpret_cast<u32>(block + 0x10);
    cursor = reinterpret_cast<u32*>(scene->unk1c);

    while (*reinterpret_cast<s32*>(cursor) != 1)
    {
        u32 type = *cursor++;

        switch (type)
        {
            case 2:
                scene->header = reinterpret_cast<LibEntryTableHeader*>(cursor);
                cursor += 2;
                break;
            case 4:
            {
                settings = reinterpret_cast<LibSceneSettingsChunk*>(cursor);
                cursor += 8;
                lib_light_list_set_ambient(lights, settings->ambient[0], settings->ambient[1], settings->ambient[2]);

                if ((settings->format & 0xFF) != 10)
                {
                    return 0;
                }

                if (((s32)(settings->format & 0xFF00) >> 8) == 1)
                {
                    scene->unk9E = 1;
                }

                break;
            }
            case 3:
            {
                scene->entries = new (0) LibManagedEntry[scene->header->count];

                if (!scene->entries)
                {
                    return 0;
                }

                for (s32 i = 0; i < scene->header->count; i++)
                {
                    LibEntryMetadata* metadata = reinterpret_cast<LibEntryMetadata*>(cursor);
                    scene->entries[i].unk00 = 0;
                    scene->entries[i].handle = 0;
                    scene->entries[i].unk04 = 0;
                    scene->entries[i].metadata = metadata;
                    cursor = reinterpret_cast<u32*>(reinterpret_cast<u8*>(cursor) + *reinterpret_cast<u16*>(cursor));

                    switch (metadata->state)
                    {
                        case 1:
                            switch (metadata->kind)
                            {
                                case 4:
                                {
                                    scene->entries[i].handle = scene->func_00471480(0);
                                    LibTransform* object = static_cast<LibTransform*>(scene->entries[i].handle);

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    object->object_kind |= 1;
                                    func_0046C3F0(scene, static_cast<LibTransform*>(scene->entries[i].handle),
                                                  reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(scene->entries[i].handle, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 7:
                                {
                                    LibLodController* controller = static_cast<LibLodController*>(scene->func_00471480(1));
                                    scene->entries[i].handle = controller;

                                    if (!controller)
                                    {
                                        return 0;
                                    }

                                    LibSceneLodRecord* data = reinterpret_cast<LibSceneLodRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    func_0046C3F0(scene, controller, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    controller->display_manager = manager;
                                    controller->level_count = data->level_count;

                                    for (s32 k = 0; k < data->level_count; k++)
                                    {
                                        controller->range_minimums[k] = data->minimums[k];
                                        controller->range_maximums[k] = data->maximums[k];
                                    }

                                    manager->append_node(scene->entries[i].handle, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                            }

                            break;
                        case 3:
                        {
                            scene->entries[i].handle = scene->func_00471480(0x30);
                            LibTransform* object = static_cast<LibTransform*>(scene->entries[i].handle);

                            if (!object)
                            {
                                return 0;
                            }

                            object->parent_transform = 0;
                            static_cast<LibTransform*>(scene->entries[i].handle)->unk20c = 0;
                            static_cast<LibTransform*>(scene->entries[i].handle)->object_kind |= 1;
                            list->append_node(scene->entries[i].handle, LibUpdateList::DEFAULT_NODE_KIND);
                            break;
                        }
                        case 0:
                        case 2:
                            switch (metadata->kind)
                            {
                                case 1:
                                {
                                    LibModel* model;

                                    if (metadata->flags & 0x4080)
                                    {
                                        if (!D_001B658C && !(metadata->flags & 0x4000))
                                        {
                                            LibClass1788B0* skinned = static_cast<LibClass1788B0*>(scene->func_00471480(8));
                                            model = skinned;

                                            if (!model)
                                            {
                                                return 0;
                                            }

                                            if (metadata->link >= 0)
                                            {
                                                LibModel* parent = static_cast<LibModel*>(scene->entries[metadata->link].handle);
                                                skinned->unk838 = parent;
                                                func_00479180(parent);
                                            }

                                            skinned->unk820 = metadata->unk8c != 0;
                                            func_00479160(skinned, skinned->unk820 ? 2 : 0);
                                            skinned->unk821 = metadata->unk8d != 0;
                                            skinned->unk822 = metadata->unk90 != 0;
                                            skinned->unk825 = metadata->unk8e;
                                            skinned->unk823 = metadata->unk8f;
                                            skinned->sphere_radius_scale = metadata->unk94;
                                            FieldVec4B vector(metadata->unk98[0], metadata->unk98[1], metadata->unk98[2], metadata->unk98[3]);
                                            func_004C94D0(skinned, reinterpret_cast<const unsigned __int128*>(&vector));
                                            skinned->unk82c = metadata->unkb4;
                                            skinned->unk830 = metadata->unkb8;
                                            skinned->unk860 = metadata->unka8[0];
                                            lib_skinned_set_unk864(skinned, metadata->unka8[1], metadata->unka8[2]);
                                            skinned->unk59d_1 = 0;
                                            skinned->unk59d_0 = 1;
                                        }
                                        else
                                        {
                                            LibClass173380* lod = static_cast<LibClass173380*>(scene->func_00471480(0x2C));
                                            model = lod;

                                            if (!model)
                                            {
                                                return 0;
                                            }

                                            if (metadata->link >= 0)
                                            {
                                                LibModel* parent = static_cast<LibModel*>(scene->entries[metadata->link].handle);
                                                lod->unk830 = parent;
                                                func_00479180(parent);
                                            }

                                            lod->unk836 = metadata->unk8d != 0;
                                            lod->unk837 = metadata->unk90 != 0;
                                            lod->unk835 = metadata->unk8e;
                                            lod->unk834 = metadata->unk8f;
                                            lod->unk848 = metadata->unk94;
                                            FieldVec4B vector(metadata->unk98[0], metadata->unk98[1], metadata->unk98[2], metadata->unk98[3]);
                                            func_0042ABE0(lod, reinterpret_cast<LibVector4*>(&vector));
                                            lod->unk854 = metadata->unkb4;
                                            lod->unk858 = metadata->unkb8;
                                            lod->unk85c = metadata->unk91 | (metadata->unk92 << 8) | (metadata->unk93 << 16);
                                        }
                                    }
                                    else
                                    {
                                        model = static_cast<LibModel*>(scene->func_00471480(2));

                                        if (!model)
                                        {
                                            return 0;
                                        }
                                    }

                                    scene->entries[i].handle = model;
                                    u8 owns_buffer = 0;

                                    if (!metadata->unk18)
                                    {
                                        scene->entries[i].unk04 = reinterpret_cast<u32>(scene->func_00471480(3));

                                        if (!scene->entries[i].unk04)
                                        {
                                            return 0;
                                        }

                                        model->attach_draw_buffer(reinterpret_cast<LibDrawBuffer*>(scene->entries[i].unk04));
                                        model->borrow_mesh(reinterpret_cast<u8*>((reinterpret_cast<u32>(scene->data) + 127) & ~127) +
                                                           metadata->data_position);
                                        owns_buffer = 1;
                                    }

                                    if (metadata->flags & 0x4080)
                                    {
                                        if ((D_001B6590 || allow_lod_parents) && (D_001B658C || (metadata->flags & 0x4000)))
                                        {
                                            if (lod_parent)
                                            {
                                                lod_parent->objects.append_node(model, LibUpdateList::DEFAULT_NODE_KIND);
                                                static_cast<LibClass173380*>(model)->unk838 = 1;
                                            }
                                            else
                                            {
                                                if (D_001B6598)
                                                {
                                                    renderer->insert_node_after(D_001B6598, model, LibUpdateList::DEFAULT_NODE_KIND);
                                                }
                                                else
                                                {
                                                    renderer->append_node(model, LibUpdateList::DEFAULT_NODE_KIND);
                                                }

                                                lod_parent = static_cast<LibClass173380*>(model);
                                            }
                                        }
                                        else if (D_001B6598)
                                        {
                                            renderer->insert_node_after(D_001B6598, model, LibUpdateList::DEFAULT_NODE_KIND);
                                        }
                                        else
                                        {
                                            renderer->append_node(model, LibUpdateList::DEFAULT_NODE_KIND);
                                        }
                                    }
                                    else
                                    {
                                        renderer->append_node(model, LibUpdateList::DEFAULT_NODE_KIND);
                                    }

                                    static_cast<LibTransform*>(scene->entries[i].handle)->draw_flags = (metadata->flags & 1) ? 2 : 0;
                                    static_cast<LibTransform*>(scene->entries[i].handle)->draw_flags |= (metadata->flags & 0x800) ? 0x800 : 0;
                                    static_cast<LibTransform*>(scene->entries[i].handle)->draw_flags |= (metadata->flags & 0x8000) ? 0x4000 : 0;
                                    static_cast<LibTransform*>(scene->entries[i].handle)->draw_flags |= (metadata->flags & 0x1000) ? 0x1000 : 0;
                                    LIB_SCENE_SET_MODEL_FLAGS(scene, i, metadata, model)
                                    lib_scene_set_layer_mask(model, metadata->layer_mask);
                                    func_004DA050(model, metadata->unk20);
                                    model->light_mask = metadata->unk10;
                                    func_0046C3F0(scene, model, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    model->create_render_channels();

                                    if (flag && owns_buffer)
                                    {
                                        model->build_packets();
                                    }

                                    break;
                                }
                                case 8:
                                {
                                    LibClass175430* model = static_cast<LibClass175430*>(scene->func_00471480(0xE));

                                    if (!model)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].handle = model;
                                    u8 owns_buffer = 0;

                                    if (!metadata->unk18)
                                    {
                                        scene->entries[i].unk04 = reinterpret_cast<u32>(scene->func_00471480(3));

                                        if (!scene->entries[i].unk04)
                                        {
                                            return 0;
                                        }

                                        model->attach_draw_buffer(reinterpret_cast<LibDrawBuffer*>(scene->entries[i].unk04));
                                        model->borrow_mesh(reinterpret_cast<u8*>((reinterpret_cast<u32>(scene->data) + 127) & ~127) +
                                                           metadata->data_position);
                                        owns_buffer = 1;
                                    }

                                    renderer->append_node(model, LibUpdateList::DEFAULT_NODE_KIND);
                                    static_cast<LibTransform*>(scene->entries[i].handle)->draw_flags = (metadata->flags & 1) ? 2 : 0;
                                    static_cast<LibTransform*>(scene->entries[i].handle)->draw_flags |= (metadata->flags & 0x800) ? 0x800 : 0;
                                    static_cast<LibTransform*>(scene->entries[i].handle)->draw_flags |= (metadata->flags & 0x1000) ? 0x1000 : 0;
                                    static_cast<LibTransform*>(scene->entries[i].handle)->draw_flags |= (metadata->flags & 0x8000) ? 0x4000 : 0;
                                    LIB_SCENE_SET_MODEL_FLAGS(scene, i, metadata, model)
                                    lib_scene_set_layer_mask(model, metadata->layer_mask);
                                    model->set_translation(metadata->translation[0], metadata->translation[1], metadata->translation[2]);

                                    if (metadata->link >= 0)
                                    {
                                        LibLodController* controller = static_cast<LibLodController*>(scene->entries[metadata->link].handle);

                                        if (!controller->position_offset_applied)
                                        {
                                            controller->apply_position_offset(*reinterpret_cast<FieldVec4A*>(model->func_00479100()));
                                        }
                                    }

                                    LibFloat4 vector;
                                    func_004790D0(reinterpret_cast<LibQuadword*>(&model->base),
                                                  reinterpret_cast<LibQuadword*>(func_004790E0(&vector, metadata->translation[0], metadata->translation[1],
                                                                                               metadata->translation[2], metadata->unk40)));
                                    func_0046C3F0(scene, model, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    func_004DA050(model, metadata->unk20);
                                    model->light_mask = metadata->unk10;
                                    model->create_render_channels();

                                    if (owns_buffer)
                                    {
                                        model->build_packets();
                                    }

                                    break;
                                }
                                case 2:
                                {
                                    LibSceneLightRecord* data = reinterpret_cast<LibSceneLightRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibLight* light = static_cast<LibLight*>(scene->func_00471480(4));

                                    if (!light)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].handle = light;
                                    u32 shadow = 0;

                                    if (data->unk3b)
                                    {
                                        shadow = 4;
                                    }

                                    switch (data->type)
                                    {
                                        case 0:
                                            light->kind = shadow;
                                            break;
                                        case 1:
                                            light->kind = shadow | 1;
                                            break;
                                        case 2:
                                            light->kind = shadow | 2;
                                            break;
                                    }

                                    u32 target = data->target;
                                    light->look_at_target = reinterpret_cast<LibTransform*>(target);

                                    if (target)
                                    {
                                        light->roll_angle = metadata->orientation[0];
                                    }

                                    lib_light_set_color(light, data->color[0], data->color[1], data->color[2]);
                                    light->color.w = data->intensity;
                                    light->mask = data->mask;
                                    light->cone_angle = data->cone_angle;
                                    func_004C9BA0(light);
                                    light->unk288 = data->unk01;
                                    light->unk289 = data->unk02;
                                    light->unk28a = data->unk03;
                                    light->unk28b = data->unk38;
                                    lib_light_update_attenuation(light);
                                    light->unk268 = data->unk20;
                                    lib_light_update_attenuation(light);
                                    light->unk274 = data->unk2c;
                                    light->cone_angle = data->cone_angle;
                                    func_004C9BA0(light);
                                    light->unk278 = data->unk1c;
                                    func_004C9BA0(light);
                                    lib_light_set_cone_terms(light, data->unk24, data->unk28);
                                    light->unk28c = data->unk39;
                                    light->unk28d = data->unk3a;
                                    light->unk27c = data->unk30;
                                    lib_light_update_attenuation(light);
                                    light->unk284 = data->unk3c;
                                    light->unk28e = data->unk40;
                                    light->unk290 = data->unk41 != 0;
                                    light->unk291 = data->unk42 != 0;
                                    light->set_translation(metadata->translation[0], metadata->translation[1], metadata->translation[2]);
                                    light->set_orientation_components(metadata->orientation[0], metadata->orientation[1],
                                                                      metadata->orientation[2], metadata->orientation[3]);
                                    lib_scene_set_offset_translation(light, metadata->offset_translation[0], metadata->offset_translation[1],
                                                                     metadata->offset_translation[2]);
                                    lib_scene_set_offset_rotation(light, metadata->offset_rotation[0], metadata->offset_rotation[1],
                                                                  metadata->offset_rotation[2], metadata->offset_rotation[3]);
                                    light->unk20c = scene->unk9E ? metadata->unk14 : metadata->unk14 | 0x1C0;

                                    if (metadata->link >= 0)
                                    {
                                        light->parent_transform = static_cast<LibTransform*>(scene->entries[metadata->link].handle);
                                    }

                                    lights->append_node(light, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 3:
                                {
                                    LibSceneCameraRecord* data = reinterpret_cast<LibSceneCameraRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibCamera* camera = scene->func_00471440(display);

                                    if (!camera)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].handle = camera;

                                    if (manager->current_display)
                                    {
                                        camera->copy_view_and_fog(static_cast<LibCamera*>(manager->current_display));
                                    }

                                    if (data->unk14)
                                    {
                                        camera->unk3d2 = 0;
                                        lib_camera_set_clip_depths(camera, data->near_clip, data->far_clip);
                                    }

                                    camera->unk270 = data->unk10;
                                    u32 target = data->target;
                                    camera->look_at_target = reinterpret_cast<LibTransform*>(target);

                                    if (target)
                                    {
                                        camera->roll_angle = metadata->orientation[0];
                                    }

                                    camera->horizontal_fov = data->fov;
                                    camera->set_translation(metadata->translation[0], metadata->translation[1], metadata->translation[2]);
                                    lib_vector_set(&quaternion, metadata->orientation[0], metadata->orientation[1], metadata->orientation[2],
                                                   metadata->orientation[3]);
                                    FieldVec4B orientation = func_004CD570(quaternion);
                                    camera->copy_orientation(reinterpret_cast<LibVector4*>(&orientation));
                                    camera->set_scale(metadata->scale[0], metadata->scale[1], metadata->scale[2]);
                                    lib_scene_set_offset_translation(camera, metadata->offset_translation[0], metadata->offset_translation[1],
                                                                     metadata->offset_translation[2]);
                                    lib_scene_set_offset_rotation(camera, metadata->offset_rotation[0], metadata->offset_rotation[1],
                                                                  metadata->offset_rotation[2], metadata->offset_rotation[3]);
                                    lib_scene_set_offset_scale(camera, metadata->offset_scale[0], metadata->offset_scale[1], metadata->offset_scale[2]);
                                    camera->unk20c = scene->unk9E ? metadata->unk14 : metadata->unk14 | 0x1C0;

                                    if (metadata->link >= 0)
                                    {
                                        camera->parent_transform = static_cast<LibTransform*>(scene->entries[metadata->link].handle);
                                    }

                                    if (settings && settings->unk0c)
                                    {
                                        camera->set_fog(settings->unk10, (float)(u32)settings->unk0d, (float)(u32)settings->unk0e,
                                                        (float)settings->unk14, (float)settings->unk18);
                                        camera->fog_enabled = 1;
                                    }

                                    manager->append_node(camera, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 5:
                                {
                                    u8* data = LIB_SCENE_ENTRY_DATA(scene, metadata);
                                    LibClass175530* object = static_cast<LibClass175530*>(scene->func_00471480(6));

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].handle = object;
                                    object->grid = reinterpret_cast<LibHeightGrid*>(data);
                                    object->grid_is_borrowed = 1;
                                    object->unk20c = scene->unk9E ? metadata->unk14 : metadata->unk14 | 0x1C0;

                                    if (metadata->link >= 0)
                                    {
                                        object->parent_transform = static_cast<LibTransform*>(scene->entries[metadata->link].handle);
                                    }

                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 6:
                                case 9:
                                {
                                    scene->entries[i].handle = scene->func_00471480(0);
                                    LibTransform* object = static_cast<LibTransform*>(scene->entries[i].handle);

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    object->object_kind |= 1;
                                    func_0046C3F0(scene, static_cast<LibTransform*>(scene->entries[i].handle),
                                                  reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(scene->entries[i].handle, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 10:
                                {
                                    u8* data = LIB_SCENE_ENTRY_DATA(scene, metadata);
                                    scene->entries[i].handle = scene->func_0046DE90(renderer, list, data);

                                    if (scene->entries[i].handle)
                                    {
                                        func_0046C3F0(scene, static_cast<LibTransform*>(scene->entries[i].handle),
                                                      reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                        LIB_SCENE_SET_EFFECT_KINDS(scene, i, metadata, 9)

                                        if (metadata->flags & 8)
                                        {
                                            static_cast<LibTransform*>(scene->entries[i].handle)->draw_flags |= 0x20;
                                        }

                                        if (data[0x2C])
                                        {
                                            static_cast<LibTransform*>(scene->entries[i].handle)->draw_flags |= 4;
                                        }

                                        LibObject1751A0* image = static_cast<LibClass173990*>(scene->entries[i].handle)->source;

                                        if (image)
                                        {
                                            image->draw_flags = (metadata->flags & 1) ? 2 : 0;
                                            image->draw_flags |= (metadata->flags & 0x800) ? 0x800 : 0;
                                            image->draw_flags |= (metadata->flags & 0x1000) ? 0x1000 : 0;
                                            image->draw_flags |= (metadata->flags & 0x8000) ? 0x4000 : 0;

                                            if (D_001B6550)
                                            {
                                                image->unk59d_1 = !(metadata->flags & 0x2000);
                                                image->unk59d_0 = 1;
                                            }

                                            if (static_cast<LibClass173990*>(scene->entries[i].handle)->unk499_1 && metadata->link >= 0)
                                            {
                                                image->parent_transform = static_cast<LibTransform*>(scene->entries[metadata->link].handle);
                                            }

                                            image->unk20c = scene->unk9E ? metadata->unk14 : metadata->unk14 | 0x1C0;
                                            lib_scene_set_layer_mask(image, metadata->layer_mask);
                                            image->set_translation(metadata->translation[0], metadata->translation[1], metadata->translation[2]);
                                            image->set_orientation_components(metadata->orientation[0], metadata->orientation[1],
                                                                              metadata->orientation[2], metadata->orientation[3]);
                                            image->set_scale(metadata->scale[0], metadata->scale[1], metadata->scale[2]);
                                            lib_scene_set_offset_translation(image, metadata->offset_translation[0], metadata->offset_translation[1],
                                                                             metadata->offset_translation[2]);
                                            lib_scene_set_offset_rotation(image, metadata->offset_rotation[0], metadata->offset_rotation[1],
                                                                          metadata->offset_rotation[2], metadata->offset_rotation[3]);
                                            lib_scene_set_offset_scale(image, metadata->offset_scale[0], metadata->offset_scale[1], metadata->offset_scale[2]);

                                            if (metadata->flags & 0x10)
                                            {
                                                image->draw_flags |= 0x80;
                                                lib_object_set_list_kind(image, 0xA);
                                            }

                                            if (metadata->flags & 0x20)
                                            {
                                                image->draw_flags |= 0x100;
                                                lib_object_set_list_kind(image, 0xA);
                                            }

                                            if (metadata->flags & 0x40)
                                            {
                                                image->draw_flags |= 0x200;
                                                lib_object_set_list_kind(image, 0xA);
                                            }

                                            if (metadata->flags & 8)
                                            {
                                                image->draw_flags |= 0x20;
                                            }
                                        }
                                    }

                                    break;
                                }
                                case 11:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass173C40* object = static_cast<LibClass173C40*>(scene->func_00471480(0xF));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    LibFloat4 vector;
                                    object->unk214 = data[2];
                                    object->unk210 = data[3];
                                    func_00479090(&object->half_width, func_004790A0(&vector, data[0], 0.0f, data[1]));
                                    lib_scene_set_bounce(object, reinterpret_cast<u8*>(data)[0x10] != 0, data[5]);
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 12:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass173B10* object = static_cast<LibClass173B10*>(scene->func_00471480(0x10));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    object->unk214 = data[1];
                                    object->unk210 = data[2];
                                    object->radius = data[0];
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 13:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass173870* object = static_cast<LibClass173870*>(scene->func_00471480(0x13));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    LibFloat4 first;
                                    LibFloat4 second;
                                    LibFloat4* direction = func_004790A0(&second, data[3], data[4], data[5]);
                                    func_00479090(&object->unk220, func_004790A0(&first, data[0], data[1], data[2]));
                                    func_00479090(&object->unk240, direction);
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 14:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass173900* object = static_cast<LibClass173900*>(scene->func_00471480(0x14));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    LibFloat4 vector;
                                    func_00479090(&object->unk220, func_004790A0(&vector, data[0], data[1], data[2]));
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 15:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass1737E0* object = static_cast<LibClass1737E0*>(scene->func_00471480(0x15));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    lib_vector_set_xy(&object->unk230, data[0], data[1]);
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 16:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass173750* object = static_cast<LibClass173750*>(scene->func_00471480(0x16));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    object->unk230.x = 6.6725903e-07f * data[0];
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 17:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass173630* object = static_cast<LibClass173630*>(scene->func_00471480(0x17));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    float extra = data[6];
                                    LibFloat4 first;
                                    LibFloat4 second;
                                    LibFloat4* direction = func_004790A0(&second, data[3], data[4], data[5]);
                                    func_00479090(&object->unk230, func_004790A0(&first, data[0], data[1], data[2]));
                                    func_00479090(&object->unk260, direction);
                                    object->radius = extra;
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 18:
                                {
                                    LibSceneSpriteRecord* data = reinterpret_cast<LibSceneSpriteRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass174AC0* sprite;

                                    if (!data->unk00)
                                    {
                                        void* object = scene->func_00471480(0x18);
                                        scene->entries[i].handle = object;

                                        if (!scene->entries[i].handle)
                                        {
                                            return 0;
                                        }

                                        sprite = static_cast<LibClass174AC0*>(object);
                                    }
                                    else
                                    {
                                        void* object = scene->func_00471480(0x19);
                                        scene->entries[i].handle = object;

                                        if (!scene->entries[i].handle)
                                        {
                                            return 0;
                                        }

                                        sprite = static_cast<LibClass174AC0*>(object);
                                    }

                                    sprite->draw_flags = (metadata->flags & 1) ? 2 : 0;
                                    sprite->draw_flags |= (metadata->flags & 0x8000) ? 0x4000 : 0;
                                    sprite->func_0044FDA0(data->columns, data->rows);
                                    u32 first_color = LIB_SCENE_PACK_COLOR(data->first_color);
                                    u32 second_color = LIB_SCENE_PACK_COLOR(data->second_color);
                                    FieldVec4B position(data->position[0], data->position[1], data->position[2], 1.0f);
                                    sprite->func_00451AD0(&position.x);
                                    FieldVec4B values(data->values[0], data->values[1], data->values[2], 1.0f);
                                    sprite->func_00451B20(&values.x);
                                    lib_sprite_set_style(sprite, data->unk20, data->unk24, first_color, second_color, D_004ED320[data->blend_mode]);

                                    if (data->unk03)
                                    {
                                        sprite->unk244 = 1;
                                    }

                                    if (!(data->unk48 <= 0.0f) && !(data->unk4c <= 0.0f))
                                    {
                                        lib_sprite_set_fade(sprite, data->unk48, data->unk4c);
                                    }

                                    LIB_SCENE_SET_EFFECT_KINDS(scene, i, metadata, 9)
                                    func_0046C3F0(scene, sprite, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    renderer->append_node(sprite, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 19:
                                {
                                    LibSceneGridImageRecord* data = reinterpret_cast<LibSceneGridImageRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass174970* grid = static_cast<LibClass174970*>(scene->func_00471480(0x1A));
                                    scene->entries[i].handle = grid;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    grid->set_grid_size(data->columns, data->rows);
                                    grid->draw_flags = (metadata->flags & 1) ? 2 : 0;
                                    grid->draw_flags |= (metadata->flags & 0x8000) ? 0x4000 : 0;
                                    u32 color = lib_scene_pack_color(data->color);
                                    lib_grid_set_row_wave(grid, data->amplitude, data->frequency, 3.1415927f * (2.0f * data->phase));
                                    lib_grid_set_column_wave(grid, data->amplitude, data->frequency, 3.1415927f * (2.0f * data->phase));
                                    lib_grid_set_extent(grid, data->half_width, data->half_height);
                                    lib_grid_set_color(grid, color, D_004ED320[data->blend_mode]);

                                    if (data->unk02)
                                    {
                                        grid->unk244 = 1;
                                    }

                                    if (!(data->unk34 <= 0.0f) && !(data->unk38 <= 0.0f))
                                    {
                                        lib_sprite_set_fade(grid, data->unk34, data->unk38);
                                    }

                                    LIB_SCENE_SET_EFFECT_KINDS(scene, i, metadata, 9)
                                    func_0046C3F0(scene, grid, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    renderer->append_node(grid, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 20:
                                {
                                    LibSceneImageObjectRecord* data = reinterpret_cast<LibSceneImageObjectRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    ResidentImageObject* object = static_cast<ResidentImageObject*>(scene->func_00471480(0x1C));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    object->unk218 = data->unk10;
                                    object->unk21c = data->unk14;
                                    object->hit_mask = data->hit_mask;
                                    object->unk2be = data->unk26;
                                    resident_image_object_set_animated(object, data->animated != 0);
                                    object->hit_volume = reinterpret_cast<ResidentHitBox*>(data->hit_volume);
                                    resident_image_object_set_unk2b4(object, data->unk2b != 0, data->unk04);
                                    resident_image_object_set_unk2b8(object, data->unk2c != 0, data->unk08);
                                    object->unk2c1 = data->unk24;
                                    object->faces_target = data->faces_target != 0;
                                    object->unk2c5 = data->unk29 != 0;
                                    object->unk2c6 = data->unk2d != 0;
                                    lib_image_object_set_anchor(object, 0.5f + data->unk18, 0.5f + data->unk1c);
                                    object->unk2c7 = data->unk2e != 0;
                                    func_0046C3F0(scene, reinterpret_cast<LibTransform*>(object), reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    D_001B6660->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 21:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass1753A0* object = static_cast<LibClass1753A0*>(scene->func_00471480(0x1D));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    LibFloat4 vector;
                                    func_00479090(&object->unk210, func_004790A0(&vector, data[0], data[1], data[2]));
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                                                        break;
                                }
                                case 22:
                                {
                                    LibSceneRayListRecord* data = reinterpret_cast<LibSceneRayListRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172960* rays = static_cast<LibClass172960*>(scene->func_00471480(0x1E));
                                    scene->entries[i].handle = rays;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    LibClass1728A0* capture = static_cast<LibClass1728A0*>(scene->func_00471480(0x1F));

                                    if (!capture)
                                    {
                                        return 0;
                                    }

                                    func_004214C0(capture, rays, manager);
                                    list->append_node(capture, LibUpdateList::DEFAULT_NODE_KIND);
                                    rays->unk240 = capture;
                                    rays->unk23d = 1;
                                    u8* record = reinterpret_cast<u8*>(data + 1);
                                    rays->unk230 = data->unk04;
                                    rays->unk22c = data->unk08;
                                    rays->unk23c = data->unk0e != 0;
                                    rays->unk23e = !data->unk0f;
                                    LibClass1728C0* ray;

                                    for (s32 k = 0; k < data->ray_count; k++)
                                    {
                                        switch (*reinterpret_cast<s32*>(record))
                                        {
                                            case 0:
                                            {
                                                LibSceneFanRayRecord* source_ray = reinterpret_cast<LibSceneFanRayRecord*>(record);
                                                LibClass172940* fan = static_cast<LibClass172940*>(scene->func_00471480(0x20));

                                                if (!fan)
                                                {
                                                    return 0;
                                                }

                                                ray = fan;
                                                fan->set_colors(source_ray->colors[0], source_ray->colors[1], source_ray->colors[2],
                                                                source_ray->colors[3]);
                                                fan->inner_radius = source_ray->inner_radius;
                                                fan->set_widths(source_ray->widths[0], source_ray->widths[1]);

                                                fan->axis_offset = source_ray->axis_offset;
                                                fan->alpha = source_ray->alpha;
                                                record += sizeof(LibSceneFanRayRecord);
                                                break;
                                            }
                                            case 1:
                                            {
                                                LibSceneBandRayRecord* source_ray = reinterpret_cast<LibSceneBandRayRecord*>(record);
                                                LibClass172920* band = static_cast<LibClass172920*>(scene->func_00471480(0x21));

                                                if (!band)
                                                {
                                                    return 0;
                                                }

                                                ray = band;
                                                band->set_colors(source_ray->colors[0], source_ray->colors[1], source_ray->colors[2],
                                                                 source_ray->colors[3], source_ray->colors[4]);
                                                band->inner_radius = source_ray->inner_radius;
                                                band->set_widths(source_ray->widths[0], source_ray->widths[1], source_ray->widths[2],
                                                                 source_ray->widths[3]);
                                                band->axis_offset = source_ray->axis_offset;
                                                band->alpha = source_ray->alpha;
                                                record += sizeof(LibSceneBandRayRecord);
                                                break;
                                            }
                                            case 2:
                                            {
                                                LibSceneRingRayRecord* source_ray = reinterpret_cast<LibSceneRingRayRecord*>(record);
                                                LibClass172900* ring = static_cast<LibClass172900*>(scene->func_00471480(0x22));

                                                if (!ring)
                                                {
                                                    return 0;
                                                }

                                                ray = ring;
                                                ring->color = source_ray->color;
                                                ring->inner_radius = source_ray->inner_radius;
                                                ring->width = source_ray->width;
                                                ring->segments = source_ray->segments;
                                                ring->axis_offset = source_ray->axis_offset;
                                                ring->alpha = source_ray->alpha;
                                                record += sizeof(LibSceneRingRayRecord);
                                                break;
                                            }
                                            case 3:
                                            {
                                                LibSceneSpokeRayRecord* source_ray = reinterpret_cast<LibSceneSpokeRayRecord*>(record);
                                                LibClass1728E0* spokes = static_cast<LibClass1728E0*>(scene->func_00471480(0x23));

                                                if (!spokes)
                                                {
                                                    return 0;
                                                }

                                                ray = spokes;
                                                spokes->set_colors(source_ray->centre_color, source_ray->edge_color);
                                                spokes->unk1c = source_ray->unk14;
                                                spokes->unk20 = source_ray->unk18;
                                                spokes->unk3c = source_ray->unk34;
                                                spokes->set_first_length(source_ray->unk1c, source_ray->unk20, source_ray->unk24);
                                                spokes->set_second_length(source_ray->unk28, source_ray->unk2c, source_ray->unk30);
                                                spokes->axis_offset = source_ray->axis_offset;
                                                spokes->alpha = source_ray->alpha;
                                                func_00421D80(spokes);
                                                record += sizeof(LibSceneSpokeRayRecord);
                                                break;
                                            }
                                        }

                                        rays->append(ray);
                                    }

                                    func_0046C3F0(scene, rays, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    rays->allocate_packet();
                                    renderer->append_node(rays, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 23:
                                {
                                    LibLinkSystemRecord* data = reinterpret_cast<LibLinkSystemRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass173050* object = static_cast<LibClass173050*>(scene->func_00471480(0x24));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    object->unk20 = data->unk00;
                                    s32 count = data->node_count;
                                    delete[] object->unk24;
                                    object->unk24 = new (0) LibClass173070[count];
                                    object->node_count = count;

                                    if (!object->unk24)
                                    {
                                        object->node_count = 0;
                                    }

                                    LibFloat4 vector;
                                    func_00479090(&object->unk40, func_004790A0(&vector, data->unk04, data->unk08, data->unk0c));

                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 24:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172FC0* object = static_cast<LibClass172FC0*>(scene->func_00471480(0x25));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    LibFloat4 point;
                                    LibFloat4 axis;
                                    func_00479090(&object->local_point, func_004790E0(&point, 0.0f, 0.0f, 0.0f, 1.0f));
                                    func_00479090(&object->local_axis, func_004790E0(&axis, 0.0f, -data[1], 0.0f, 1.0f));
                                    object->unk214 = data[2];
                                    object->unk220 = data[0];
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 25:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172F30* object = static_cast<LibClass172F30*>(scene->func_00471480(0x26));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    object->unk214 = data[1];
                                    object->unk220 = data[0];
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 26:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172EA0* object = static_cast<LibClass172EA0*>(scene->func_00471480(0x27));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    if (*reinterpret_cast<u32*>(data) == LIB_SCENE_SHAPE_MAGIC)
                                    {
                                        object->unk214 = data[1];
                                    }

                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 27:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172C60* object = static_cast<LibClass172C60*>(scene->func_00471480(0x28));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    object->set_parameters(data[0], data[1], data[2], data[3]);
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    D_507C40.append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 28:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172B40* object = static_cast<LibClass172B40*>(scene->func_00471480(0x29));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    object->set_parameters(data[0], data[1], data[2]);
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    D_507C40.append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 29:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172CF0* object = static_cast<LibClass172CF0*>(scene->func_00471480(0x2A));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    object->set_parameters(data[0], data[1]);
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    D_507C40.append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 30:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172E10* object = static_cast<LibClass172E10*>(scene->func_00471480(0x2B));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    if (*reinterpret_cast<u32*>(data) == LIB_SCENE_SHAPE_MAGIC)
                                    {
                                        LibFloat4 extent;
                                        object->unk214 = data[4];
                                        func_00479090(&object->extent, func_004790A0(&extent, data[1], data[3], data[2]));
                                    }
                                    else
                                    {
                                        LibFloat4 extent;
                                        func_00479090(&object->extent, func_004790A0(&extent, data[0], data[2], data[1]));
                                    }

                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 31:
                                {
                                    LibSceneOccluderRecord* data = reinterpret_cast<LibSceneOccluderRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass1734D0* object = static_cast<LibClass1734D0*>(scene->func_00471480(0x2D));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    object->half_width = data->half_width;
                                    object->half_depth = data->half_depth;
                                    object->unk21c = data->unk08 != 0;
                                    func_00431020(object);
                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    renderer->unk40d8.append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 32:
                                {
                                    float* data = reinterpret_cast<float*>(LIB_SCENE_ENTRY_DATA(scene, metadata));
                                    LibClass172D80* object = static_cast<LibClass172D80*>(scene->func_00471480(0x2F));
                                    scene->entries[i].handle = object;

                                    if (!scene->entries[i].handle)
                                    {
                                        return 0;
                                    }

                                    if (*reinterpret_cast<u32*>(data) == LIB_SCENE_SHAPE_MAGIC)
                                    {
                                        object->unk214 = data[1];
                                        lib_shape_set_extent(object, data[2], data[3]);
                                    }

                                    func_0046C3F0(scene, object, reinterpret_cast<const LibSceneTransformRecord*>(metadata));
                                    list->append_node(object, LibUpdateList::DEFAULT_NODE_KIND);
                                    break;
                                }
                                case 0x40:
                                {
                                    LibClass1779F0* object = static_cast<LibClass1779F0*>(scene->func_00471480(7));

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].unk00 = 1;
                                    scene->entries[i].handle = object;
                                    object->set_borrowed_data(reinterpret_cast<u8*>((reinterpret_cast<u32>(scene->data) + 127) & ~127) +
                                                              metadata->data_position);

                                    if (metadata->link >= 0)
                                    {
                                        LibModel* parent = static_cast<LibModel*>(scene->entries[metadata->link].handle);

                                        object->attach(parent, list);

                                        if (flag || parent->type_id == 0x101)
                                        {
                                            LibClass177A20* children = &parent->children;

                                            if (!lib_model_children_have_payload(children, parent->children.payload_set) &&
                                                !static_cast<LibClass177A80*>(object)->header->has_second_set)
                                            {
                                                children->allocate_payload(1);
                                                parent->children.allocate_payload(0);
                                            }
                                        }
                                    }

                                    break;
                                }
                                case 0x41:
                                {
                                    LibClass1779F0* object = static_cast<LibClass1779F0*>(scene->func_00471480(9));

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].unk00 = 1;
                                    scene->entries[i].handle = object;
                                    object->set_borrowed_data(reinterpret_cast<u8*>((reinterpret_cast<u32>(scene->data) + 127) & ~127) +
                                                              metadata->data_position);

                                    if (metadata->link >= 0)
                                    {
                                        LibModel* parent = static_cast<LibModel*>(scene->entries[metadata->link].handle);

                                        object->attach(parent, list);

                                        if (flag || parent->type_id == 0x101)
                                        {
                                            LibClass177A20* children = &parent->children;

                                            if (!lib_model_children_have_payload(children, parent->children.payload_set))
                                            {
                                                children->allocate_payload(1);
                                                parent->children.allocate_payload(0);
                                            }
                                        }
                                    }

                                    break;
                                }
                                case 0x42:
                                {
                                    LibClass1779F0* object = static_cast<LibClass1779F0*>(scene->func_00471480(0xA));

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].unk00 = 1;
                                    scene->entries[i].handle = object;
                                    object->set_borrowed_data(reinterpret_cast<u8*>((reinterpret_cast<u32>(scene->data) + 127) & ~127) +
                                                              metadata->data_position);

                                    if (metadata->link >= 0)
                                    {
                                        LibModel* parent = static_cast<LibModel*>(scene->entries[metadata->link].handle);

                                        object->attach(parent, list);

                                        if (flag || parent->type_id == 0x101)
                                        {
                                            LibClass177A20* children = &parent->children;

                                            if (!lib_model_children_have_payload(children, parent->children.payload_set))
                                            {
                                                children->allocate_payload(1);
                                                parent->children.allocate_payload(0);
                                            }
                                        }
                                    }

                                    break;
                                }
                                case 0x43:
                                {
                                    LibClass1779F0* object = static_cast<LibClass1779F0*>(scene->func_00471480(0xB));

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].unk00 = 1;
                                    scene->entries[i].handle = object;
                                    object->set_borrowed_data(reinterpret_cast<u8*>((reinterpret_cast<u32>(scene->data) + 127) & ~127) +
                                                              metadata->data_position);

                                    if (metadata->link >= 0)
                                    {
                                        LibModel* parent = static_cast<LibModel*>(scene->entries[metadata->link].handle);

                                        object->attach(parent, list);

                                        if (flag || parent->type_id == 0x101)
                                        {
                                            LibClass177A20* children = &parent->children;

                                            if (!lib_model_children_have_payload(children, parent->children.payload_set))
                                            {
                                                children->allocate_payload(1);
                                                parent->children.allocate_payload(0);
                                            }
                                        }
                                    }

                                    break;
                                }
                                case 0x44:
                                {
                                    LibClass1779F0* object = static_cast<LibClass1779F0*>(scene->func_00471480(0xC));

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].unk00 = 1;
                                    scene->entries[i].handle = object;
                                    object->set_borrowed_data(reinterpret_cast<u8*>((reinterpret_cast<u32>(scene->data) + 127) & ~127) +
                                                              metadata->data_position);

                                    if (metadata->link >= 0)
                                    {
                                        LibModel* parent = static_cast<LibModel*>(scene->entries[metadata->link].handle);

                                        object->attach(parent, list);

                                        if (flag || parent->type_id == 0x101)
                                        {
                                            LibClass177A20* children = &parent->children;

                                            if (!lib_model_children_have_payload(children, parent->children.payload_set))
                                            {
                                                children->allocate_payload(1);
                                                parent->children.allocate_payload(0);
                                            }
                                        }
                                    }

                                    break;
                                }
                                case 0x45:
                                {
                                    LibClass1779F0* object = static_cast<LibClass1779F0*>(scene->func_00471480(0xD));

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].unk00 = 1;
                                    scene->entries[i].handle = object;
                                    object->set_borrowed_data(reinterpret_cast<u8*>((reinterpret_cast<u32>(scene->data) + 127) & ~127) +
                                                              metadata->data_position);

                                    if (metadata->link >= 0)
                                    {
                                        LibModel* parent = static_cast<LibModel*>(scene->entries[metadata->link].handle);

                                        object->attach(parent, list);

                                        if (flag || parent->type_id == 0x101)
                                        {
                                            LibClass177A20* children = &parent->children;

                                            if (!lib_model_children_have_payload(children, parent->children.payload_set))
                                            {
                                                children->allocate_payload(1);
                                                parent->children.allocate_payload(0);
                                            }
                                        }
                                    }

                                    break;
                                }
                                case 0x46:
                                {
                                    LibClass1779F0* object = static_cast<LibClass1779F0*>(scene->func_00471480(0x1B));

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].unk00 = 1;
                                    scene->entries[i].handle = object;
                                    object->set_borrowed_data(reinterpret_cast<u8*>((reinterpret_cast<u32>(scene->data) + 127) & ~127) +
                                                              metadata->data_position);

                                    if (metadata->link >= 0)
                                    {
                                        LibModel* parent = static_cast<LibModel*>(scene->entries[metadata->link].handle);

                                        object->attach(parent, list);

                                        if (flag || parent->type_id == 0x101)
                                        {
                                            LibClass177A20* children = &parent->children;

                                            if (!lib_model_children_have_payload(children, parent->children.payload_set))
                                            {
                                                children->allocate_payload(1);
                                                parent->children.allocate_payload(0);
                                            }
                                        }
                                    }

                                    break;
                                }
                                case 0x47:
                                {
                                    LibClass1779F0* object = static_cast<LibClass1779F0*>(scene->func_00471480(0x2E));

                                    if (!object)
                                    {
                                        return 0;
                                    }

                                    scene->entries[i].unk00 = 1;
                                    scene->entries[i].handle = object;
                                    object->set_borrowed_data(reinterpret_cast<u8*>((reinterpret_cast<u32>(scene->data) + 127) & ~127) +
                                                              metadata->data_position);

                                    if (metadata->link >= 0)
                                    {
                                        LibModel* parent = static_cast<LibModel*>(scene->entries[metadata->link].handle);

                                        object->attach(parent, list);

                                        if (flag || parent->type_id == 0x101)
                                        {
                                            LibClass177A20* children = &parent->children;

                                            if (!lib_model_children_have_payload(children, parent->children.payload_set))
                                            {
                                                children->allocate_payload(1);
                                                parent->children.allocate_payload(0);
                                            }
                                        }
                                    }

                                    break;
                                }
                            }

                            break;
                    }
                }

                break;
            }
            case 5:
            {
                cursor = lib_scene_read_links(scene, cursor);
                break;
            }
            case 6:
                camera_table = reinterpret_cast<LibSceneCameraSlot*>(cursor);
                cursor += 0x40;
                break;
            case 7:
                renderer->unk4458->unk9d = *cursor++;
                break;
            case 11:
                renderer->unk40cd = *cursor++ != 0;
                break;
            case 8:
            {
                LibSceneFogChunk* fog = reinterpret_cast<LibSceneFogChunk*>(cursor);
                cursor += 5;
                lib_scene_read_fog(renderer->unk4464, fog);
                break;
            }
            case 9:
            {
                LibSceneFogChunk* fog = reinterpret_cast<LibSceneFogChunk*>(cursor);
                cursor += 5;
                lib_scene_read_fog(renderer->unk4468, fog);
                break;
            }
            case 10:
                allow_lod_parents = *cursor++ ? true : false;
                break;
        }
    }

    for (s32 i = 0; i < scene->header->count; i++)
    {
        LibManagedEntry* entry = &scene->entries[i];
        LibEntryMetadata* metadata = entry->metadata;

        switch (metadata->kind)
        {
            case 1:
            case 8:
                if (metadata->unk18)
                {
                    LibManagedEntry* source = &scene->entries[scene->entries[i].metadata->unk18];
                    LibModel* shared = static_cast<LibModel*>(source->handle);
                    static_cast<LibModel*>(scene->entries[i].handle)->set_resource(reinterpret_cast<LibResourceBuffer*>(source->unk04));

                    LibClass177A20* children = &shared->children;

                    if (children->node_count)
                    {
                        children->unk88 = 2;
                    }

                    if (shared->get_render_channels()->node_count)
                    {
                        shared->draw_flags |= 0x2000;
                    }

                    if (flag)
                    {
                        static_cast<LibModel*>(scene->entries[i].handle)->build_packets();
                        static_cast<LibModel*>(scene->entries[i].handle)->unk791 = 1;
                    }
                    else if (static_cast<LibModel*>(scene->entries[i].handle)->type_id == 0x101)
                    {
                        static_cast<LibModel*>(scene->entries[i].handle)->build_packets();
                    }
                }

                break;
            case 2:
            case 3:
            {
                LibLookAtTransform* object = static_cast<LibLookAtTransform*>(entry->handle);

                if (object->look_at_target)
                {
                    object->look_at_target = static_cast<LibTransform*>(scene->entries[reinterpret_cast<s32>(object->look_at_target)].handle);
                }

                break;
            }
            case 7:
            {
                s32 count = metadata->child_count;
                LibLodController* controller;
                s32 k;
                s32* children = static_cast<s32*>(lib_get_entry_data(scene, metadata));
                controller = static_cast<LibLodController*>(scene->entries[i].handle);

                for (k = 0; k < count; k++)
                {
                    controller->level_boundaries[k] = controller->object_count;
                    lib_collect_entry_tree(scene, children[k], controller);
                }

                controller->level_boundaries[k] = controller->object_count;
                break;
            }
            case 10:
            {
                LibClass173990* emitter = static_cast<LibClass173990*>(entry->handle);

                if (!emitter)
                {
                    break;
                }

                LibGridSceneRecord* data = reinterpret_cast<LibGridSceneRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata));

                if ((s32)emitter->unk428 > 0)
                {
                    func_00435190(emitter, reinterpret_cast<u32>(scene->entries[emitter->unk428].handle));
                }

                if (data->unk10 > 0)
                {
                    func_0043ADF0(emitter, reinterpret_cast<s32>(scene->entries[data->unk10].handle));
                }

                s32 index = data->unk04;

                if (emitter->unk49b_0)
                {
                    LibClass173990* source = static_cast<LibClass173990*>(scene->entries[index].handle);

                    if (source)
                    {
                        func_0043B700(emitter, source->source);
                    }
                }
                else
                {
                    LibGridBase* grid = emitter->source->reference;
                    index = grid->func_slot80();

                    if (index > 0)
                    {
                        grid->func_slot7c(scene->entries[index].handle);
                    }

                    index = grid->func_slot90();

                    if (index > 0)
                    {
                        grid->func_slot8c(scene->entries[index].handle);
                    }

                    if (data->unk6a && data->link_count > 0)
                    {
                        s32* indices = data->links;
                        LibClass175370* links = new (0) LibClass175370(data->link_count);
                        LibClass175390* node = new (0) LibClass175390(emitter, links, 1);

                        if (!node || !links)
                        {
                            break;
                        }

                        scene->unk80.append(node);
                        grid->func_slotac(links);

                        for (s32 k = 0; k < data->link_count; k++)
                        {
                            LibTransform* object = static_cast<LibTransform*>(scene->entries[indices[k]].handle);

                            if (object && ((u32)object->type_id >> 8) == 6)
                            {
                                links->append(object);
                            }
                        }
                    }

                    if (data->unk69 && data->link_count > 0)
                    {
                        s32* indices = data->links;
                        LibClass175360* links = new (0) LibClass175360(data->link_count);
                        LibClass175390* node = new (0) LibClass175390(emitter, links, 2);

                        if (!node || !links)
                        {
                            break;
                        }

                        scene->unk80.append(node);
                        grid->func_slota4(links);

                        for (s32 k = 0; k < data->link_count; k++)
                        {
                            LibTransform* object = static_cast<LibTransform*>(scene->entries[indices[k]].handle);

                            if (object && ((u32)object->type_id >> 8) == 7)
                            {
                                links->append(object);
                            }
                        }
                    }
                }

                break;
            }
            case 20:
            {
                ResidentImageObject* object = static_cast<ResidentImageObject*>(entry->handle);

                if (object->hit_volume)
                {
                    object->hit_volume = static_cast<ResidentHitBox*>(scene->entries[reinterpret_cast<s32>(object->hit_volume)].handle);
                }

                LibSceneImageObjectRecord* data = reinterpret_cast<LibSceneImageObjectRecord*>(LIB_SCENE_ENTRY_DATA(scene, scene->entries[i].metadata));

                if (data->unk2b && object->position_source)
                {
                    object->position_source =
                        static_cast<ResidentImageObjectBase*>(scene->entries[reinterpret_cast<s32>(object->position_source)].handle);
                }

                if (data->unk2c && object->camera)
                {
                    object->camera = static_cast<ResidentImageObjectBase*>(scene->entries[reinterpret_cast<s32>(object->camera)].handle);
                }

                if (data->unk0c)
                {
                    LibRenderDataRecord* resource = reinterpret_cast<LibRenderDataRecord*>(reinterpret_cast<u8*>(data) + data->unk0c);

                    if (data->unk2a)
                    {
                        object->shared_image = data->unk2a;
                    }
                    else if (resource->storage_kind == 1)
                    {
                        LibRenderDataRecord* shared = func_00448910(resource->key08, resource->key0c);

                        if (shared)
                        {
                            resident_image_object_attach(object, shared->data ? static_cast<u8*>(shared->data) - 0x10
                                                                              : reinterpret_cast<u8*>(shared + 1));
                        }
                    }
                    else
                    {
                        resident_image_object_attach(object, reinterpret_cast<u8*>(resource + 1));
                    }
                }

                resident_image_object_rebuild_hit_box(object);
                break;
            }
            case 23:
                func_0046BAC0(scene, static_cast<LibClass173050*>(entry->handle),
                              reinterpret_cast<LibLinkSystemRecord*>(LIB_SCENE_ENTRY_DATA(scene, metadata)));
                break;
            case 0x40:
            {
                LibClass177A80* object = static_cast<LibClass177A80*>(entry->handle);

                s32 count = object->header->matrix_count;

                for (s32 k = 0; k < count; k++)
                {
                    object->unk3c[k] = reinterpret_cast<u32>(scene->entries[reinterpret_cast<s32*>(object->unk38)[k]].handle);
                }

                if (object->header->has_second_set)
                {
                    object->listed = 0;
                    func_00478F90(reinterpret_cast<LibFlagState8D*>(object->list));
                    LibModel* model = object->list->model;
                    model->unk638 = reinterpret_cast<u32>(object);
                    model->unk59d_0 = 1;
                }

                break;
            }
        }
    }

    func_00473E20(scene);

    if (camera_table)
    {
        for (s32 k = 1; k <= 32; k++, camera_table++)
        {
            if (camera_table->index)
            {
                switch (camera_table->type)
                {
                    case 0:
                    {
                        LibCamera* camera = static_cast<LibCamera*>(scene->entries[camera_table->index].handle);
                        lib_object_detach_owner(camera);
                        camera->unk3d1 = 1;
                        LibClass178F30* layer = &renderer->unk4470[k - 1];
                        layer->append_node(camera, LibUpdateList::DEFAULT_NODE_KIND);
                        layer->current_display = camera;
                        func_004D08D0(renderer, k, 1 << (camera_table->unk04 + 6), reinterpret_cast<LibDisplayManager*>(layer));
                        break;
                    }
                    case 1:
                    {
                        LibCamera* camera = renderer->cameras[k - 1];
                        lib_object_detach_owner(camera);
                        LibClass178F30* layer = &renderer->unk4470[k - 1];
                        lib_camera_follow(camera, static_cast<LibTransform*>(scene->entries[camera_table->index].handle));
                        layer->append_node(camera, LibUpdateList::DEFAULT_NODE_KIND);
                        layer->current_display = camera;
                        func_004D08D0(renderer, k, 1 << (camera_table->unk04 + 6), reinterpret_cast<LibDisplayManager*>(layer));
                        break;
                    }
                }
            }
        }
    }

    for (s32 i = 0; i < scene->header->count; i++)
    {
        LibManagedEntry* entry = &scene->entries[i];

        if (entry->metadata)
        {
            u32 mask = entry->metadata->layer_mask;

            if (mask != 0 && !(mask & 1))
            {
                LibTransform* object = static_cast<LibTransform*>(entry->handle);

                if (object->layer)
                {
                    object->display_manager = renderer->layers[object->layer - 1].display_manager;
                }
            }
        }
    }

    for (s32 i = 0; i < scene->header->count; i++)
    {
        LibManagedEntry* entry = &scene->entries[i];
        LibEntryMetadata* metadata = entry->metadata;

        if (metadata && (metadata->state == 2 || metadata->state == 0))
        {
            u8 kind = metadata->kind;

            if (kind >= 24)
            {
                if (kind == 24 || kind == 25)
                {
                    if (!static_cast<LibClass172AB0*>(entry->handle)->unk210)
                    {
                        func_00428D20(static_cast<LibListObject*>(entry->handle), 0);
                    }
                }
                else if (kind == 26 || kind == 30 || kind == 32)
                {
                    if (!static_cast<LibClass172AB0*>(entry->handle)->unk210)
                    {
                        func_00428A50(static_cast<LibListObject*>(entry->handle), 0);
                    }
                }
            }
        }
    }

    if (settings)
    {
        scene->unk98 = settings->unk10;

        if (settings->unk0c)
        {
            LibCamera* camera = static_cast<LibCamera*>(manager->current_display);

            if (camera)
            {
                camera->set_fog(settings->unk10, (float)(u32)settings->unk0d, (float)(u32)settings->unk0e,
                                (float)settings->unk14, (float)settings->unk18);
                display->set_clear_color(settings->unk10 & 0xFF, (settings->unk10 >> 8) & 0xFF,
                                         (settings->unk10 >> 16) & 0xFF, 0x7F);
                camera->fog_enabled = 1;
            }

            func_004728A0(scene, 1, 1);
        }
    }

    if (lod_parent && lod_parent->objects.get_node_count())
    {
        LibClass173380* first = reinterpret_cast<LibClass173380*>(func_00478F70(&lod_parent->objects));
        lod_parent->unk83a = 0;
        first->unk839 = 1;
    }

    return 1;
}
#pragma pop

/** Return the word at receiver offset 0x8. */
u32 func_00478F70(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unk08;
}

/**
 * @brief Return how many nodes the list holds.
 * @return Node count.
 */
u32 LibListReceiver::get_node_count() const
{
    return node_count;
}

/**
 * @brief Set bit 1 of the flag byte at receiver offset 0x8D.
 * @param object Receiver.
 */
void func_00478F90(LibFlagState8D* object)
{
    object->unk8d_1 = 1;
}

/**
 * @brief Append an item; a full list ignores it.
 * @param item Item to append.
 */
void LibPointerList::append(void* item)
{
    if (count < capacity)
    {
        items[count++] = item;
    }
}


/**
 * @brief Allocate room for a number of pointers.
 * @param size Capacity to allocate.
 */
LibPointerList::LibPointerList(s32 size)
{
    items = 0;
    capacity = 0;
    reserve(size);
}

/**
 * @brief Copy one aligned 16-byte value.
 * @param output Destination value.
 * @param input Source value.
 */
void func_00479090(void* output, const void* input)
{
    *(unsigned __int128*)output = *(const unsigned __int128*)input;
}

/**
 * @brief Set a vector to (x, y, z, 1).
 * @param vector Vector to set.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @return The vector.
 */
LibFloat4* func_004790A0(LibFloat4* vector, float x, float y, float z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
    vector->w = 1.0f;
    return vector;
}

/**
 * @brief Set the inherited transform dirty flag.
 * @param object Transform receiver.
 * @param value Dirty flag to store.
 */
void lib_transform_set_dirty(void* object, u8 value)
{
    ((LibTransformByteState*)object)->transform_dirty = value;
}

LibQuadword func_004790D0(LibQuadword* destination, const LibQuadword* source)
{
    return *destination = *source;
}

/**
 * @brief Set the four components of a vector.
 * @param vector Vector to set.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 * @return The vector.
 */
LibFloat4* func_004790E0(LibFloat4* vector, float x, float y, float z, float w)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
    vector->w = w;
    return vector;
}

/**
 * @brief Return the target.
 * @return Target position.
 */
FieldVec4B* LibClass175430::func_00479100()
{
    return &target;
}

/**
 * @brief Set the target and point the translation from the base position at it.
 * @param x Target x.
 * @param y Target y.
 * @param z Target z.
 */
void LibClass175430::set_translation(float x, float y, float z)
{
    target.x = x;
    target.y = y;
    target.z = z;
    lib_set_translation(this, x - base.x, y - base.y, z - base.z);
}

void func_00479160(void* object, u8 value)
{
    LibFlagState59C* receiver = (LibFlagState59C*)object;
    receiver->unk59c = value;
    receiver->unk59d_0 = 1;
}

/** Increment the byte at receiver offset 0x790. */
void func_00479180(void* object)
{
    LibByte790Counter* receiver = (LibByte790Counter*)object;
    receiver->unk790 = (u8)(receiver->unk790 + 1);
}

/**
 * @brief Release the scene's entries unless it keeps them, then free its data unless it's borrowed.
 * @param scene Scene.
 */
static inline void lib_scene_release_data(LibEntryManager* scene)
{
    if (!scene->unk9D)
    {
        lib_scene_release_entries(scene);
    }

    if (!scene->data_borrowed)
    {
        delete scene->data;
    }
}

/**
 * @brief Replace the scene's data with already decoded data it doesn't own.
 * @param scene Scene.
 * @param data Decoded scene resource.
 */
void lib_scene_use_data(LibEntryManager* scene, u8* data)
{
    lib_scene_release_data(scene);
    scene->data_borrowed = 1;
    scene->data = data;
}

/**
 * @brief Replace the scene's data by decoding a scene resource into a buffer the scene owns.
 * @param scene Scene.
 * @param source Compressed scene resource.
 */
void lib_scene_load_data(LibEntryManager* scene, ResidentResourceHeader* source)
{
    u8* buffer;

    lib_scene_release_data(scene);
    scene->data_borrowed = 0;
    buffer = resident_allocate_decode_buffer(g_resident_resource_decoder, source, 0, 1);

    if (buffer)
    {
        resident_decode_resource_block(g_resident_resource_decoder, source, (void*)RESIDENT_ALIGN_RESOURCE(buffer), 0);
        scene->data = buffer;
    }
}

/** @brief Release the entries unless the scene keeps them, queue unborrowed data for release, then destroy the list object. */
LibScene::~LibScene()
{
    if (!unk9D)
    {
        lib_scene_release_entries(this);
    }

    if (!data_borrowed)
    {
        resident_queue_allocation_release(g_resident_release_queues, data);
    }
}

/** @brief Start with no data, entries or slot objects. */
LibScene::LibScene()
{
    s32 slot;

    data = 0;
    entries = 0;
    data_borrowed = 0;
    cached_entry_index = 0;
    unk9D = 0;

    for (slot = 0; slot < LIB_ENTRY_MANAGER_SLOT_COUNT; slot++)
    {
        unk34[slot] = 0;
        unk9f[slot] = 0;
    }

    linked = 0;
    unk9E = 0;
}

/** @brief Destroy the list. */
LibClass175360::~LibClass175360()
{
}

/** @brief Destroy the list. */
LibClass175370::~LibClass175370()
{
}

/** @brief Destroy the transform. */
LibClass1753A0::~LibClass1753A0()
{
}

/** @brief Destroy the model. */
LibClass175430::~LibClass175430()
{
}

/**
 * @brief Set the target and point the translation from the base position at it.
 * @param value Target; its w becomes the translation's w.
 */
void LibClass175430::copy_translation(const LibVector4* value)
{
    target = *reinterpret_cast<const FieldVec4B*>(value);

    LibVector4 offset;
    offset.x = value->x - base.x;
    offset.y = value->y - base.y;
    offset.z = value->z - base.z;
    offset.w = value->w;
    transform_dirty = 1;
    copy_vector(&translation, &offset);
}

/**
 * @brief Set the target and point the translation from the base position at it.
 * @param value Target; its w becomes the translation's w.
 */
void LibClass175430::set_translation_vector(const LibVector4* value)
{
    LibVector4 offset;
    offset.x = value->x - base.x;
    offset.y = value->y - base.y;
    offset.z = value->z - base.z;
    offset.w = value->w;
    target = *reinterpret_cast<const FieldVec4B*>(value);
    transform_dirty = 1;
    copy_vector(&translation, &offset);
}


/** @brief Free the grid unless it is borrowed, then destroy the transform. */
LibClass175530::~LibClass175530()
{
    if (!grid_is_borrowed)
    {
        delete grid;
    }
}

/** @brief Destroy the grid. */
LibClass1755C0::~LibClass1755C0()
{
}

s32 func_00479840(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass175690::~LibClass175690()
{
}

/** @brief Destroy the grid. */
LibClass175830::~LibClass175830()
{
}

s32 func_00479950(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass1759D0::~LibClass1759D0()
{
}

s32 func_004799E0(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass175C40::~LibClass175C40()
{
}

/** @brief Destroy the grid. */
LibClass175EB0::~LibClass175EB0()
{
}

s32 func_00479AF0(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass176120::~LibClass176120()
{
}

/** @brief Destroy the grid. */
LibClass176390::~LibClass176390()
{
}

s32 func_00479C00(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass176600::~LibClass176600()
{
}

/**
 * @brief Test whether the source byte at receiver offset 0xA0 isn't 1.
 * @param object Receiver.
 * @return Nonzero unless the source byte is 1.
 */
s32 func_00479C90(const ByteSourceStateOwnertext_0046AE20* object)
{
    return *object->sourceA0 != 1;
}

/** @brief Destroy the grid. */
LibClass1767A0::~LibClass1767A0()
{
}

/**
 * @brief Test whether the source byte at receiver offset 0xA0 isn't 1.
 * @param object Receiver.
 * @return Nonzero unless the source byte is 1.
 */
s32 func_00479D30(const ByteSourceStateOwnertext_0046AE20* object)
{
    return *object->sourceA0 != 1;
}

/** @brief Destroy the grid. */
LibClass176A10::~LibClass176A10()
{
}

s32 func_00479DD0(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass176BB0::~LibClass176BB0()
{
}

s32 func_00479E60(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass176D50::~LibClass176D50()
{
}

/**
 * @brief Append a key and an optional value to a fixed-capacity keyed list; full lists ignore it.
 * @param list List to append to.
 * @param key Key byte.
 * @param value Value to copy, or null to leave the slot's value unchanged.
 */
void func_00479EF0(LibKeyedVectorList* list, u8 key, const LibFloat4* value)
{
    if (list->count < list->capacity)
    {
        list->keys[list->count] = key;

        if (value)
        {
            *(unsigned __int128*)&list->values[list->count] = *(const unsigned __int128*)value;
        }

        list->count++;
    }
}

/**
 * @brief Append a key and an optional value to a fixed-capacity keyed list; full lists ignore it.
 * @param list List to append to.
 * @param key Key byte.
 * @param value Value to copy, or null to leave the slot's value unchanged.
 */
void func_00479F50(LibKeyedVectorList* list, u8 key, const LibFloat4* value)
{
    if (list->count < list->capacity)
    {
        list->keys[list->count] = key;

        if (value)
        {
            *(unsigned __int128*)&list->values[list->count] = *(const unsigned __int128*)value;
        }

        list->count++;
    }
}

void func_00479FB0(void* object)
{
}

s32 func_00479FC0(void* object)
{
    return 1;
}

/** Store the word at receiver offset 0xB8. */
void func_00479FD0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = (WordSetterOwnertext_0046AE20*)object;
    receiver->unkb8 = value;
}

/** Return the word at receiver offset 0xB8. */
u32 func_00479FE0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unkb8;
}

/** Store the word at receiver offset 0xBC. */
void func_00479FF0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = (WordSetterOwnertext_0046AE20*)object;
    receiver->unkbc = value;
}

/** Return the word at receiver offset 0xBC. */
u32 func_0047A000(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unkbc;
}

void func_0047A010(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8)
{
    u8* state = (u8*)cell;
    state[0x130] = 0;
    state[0x132] = 0;
    state[0x131] = 0;
    state[0x133] = 0;
    func_0047A130(object, cell, row, index, extra4, extra5, extra6, extra7, extra8);
}
