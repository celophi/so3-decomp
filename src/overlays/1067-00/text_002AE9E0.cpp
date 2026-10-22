#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_001001E0.h"
#include "overlays/1067-00/text_002AE9E0.h"
#include "overlays/1067-00/text_00202240.h"
#include "overlays/1067-00/text_001F9B70.h"
#include "overlays/lib/text_004AB8B0.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/1067-00/text_001DED80.h"
#include "overlays/1067-00/text_0029E9E0.h"
#include "overlays/lib/emission_vu0.h"
#include "overlays/lib/object_registry.h"
#include "overlays/lib/render_buffer.h"
#include "sdk/main/libc_guess_0013A4C0.h"

#include "main/resident_00101260.h"
#include "overlays/1067-00/text_0021FB80.h"
#include "overlays/1067-00/text_00207AF0.h"
#include "overlays/1067-00/text_002D8410.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/1067-00/text_002764D0.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/1067-00/field_runtime.h"
#include "clamp.h"

#include "overlays/1067-00/text_0020E4B0.h"
#include "overlays/1067-00/text_0023DC90.h"
#include "overlays/1067-00/text_0024C4B0.h"
#include "overlays/1067-00/text_002541F0.h"
#include "overlays/1067-00/text_00257750.h"
#include "overlays/1067-00/text_0026EE10.h"
#include "overlays/1067-00/text_0027E520.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "main/resident_0011EE70.h"
#include "sdk/main/libc_guess_0013C948.h"

#include "overlays/1067-00/text_00272360.h"
#include "overlays/1067-00/text_0021DB80.h"

#include "overlays/lib/text_003F90C0.h"
#include "overlays/1067-00/text_00291B80.h"
#include "overlays/1067-00/text_002D3BD0.h"

#define TIMER0_COUNT (*(volatile u32*)0x10000000)
#define TIMER0_MODE (*(volatile u32*)0x10000010)

/** Display interfaces retained by the field display/list manager. */
struct FieldDisplaySlot
{
    u8 unk00[0xAF];

    u8 unkaf;
};

struct FieldDisplayManagerState
{
    u8 unk00[0x4084];

    void* unk4084;

    u8 unk4088[0x3DC];

    FieldDisplaySlot* unk4464;

    FieldDisplaySlot* unk4468;
};

struct FieldDisplayState6624
{
    u8 unk00[0x360];

    void* unk360;
};

extern "C"
{
    extern char g_field_default_name_fayt[];

    extern char g_field_default_name_sophia[];

    extern char g_field_default_name_maria[];

    extern char g_field_default_name_cliff[];

    extern char g_field_default_name_nel[];

    extern char g_field_default_name_albel[];

    extern char g_field_default_name_roger[];

    extern char g_field_default_name_peppita[];

    extern char g_field_default_name_adray[];

    extern char g_field_default_name_mirage[];
}

/** Field variables, flags and character names retained in resource four. */
struct FieldRuntimeState
{
    static void* operator new(u32 size);

    /** @brief Release storage through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);

    /** @brief Clear runtime values and restore the default character names. */
    FieldRuntimeState()
    {
        func_0013A678(unk588, 0, sizeof(unk588));
        func_0013A678(unkC588, 0, sizeof(unkC588));
        func_0013A678(unk04, 0, sizeof(unk04));
        func_0013A678(unkC688, 0, sizeof(unkC688));
        field_clear_flags_5000(reinterpret_cast<FieldRuntimeValues*>(this));
        func_0013A678(variables, 0, sizeof(variables));
        unkC7A0 = 0;
        unkC7E6 = 0;
        unkC7A4 = 0;
        unkC7E0 = 0x7FFF;
        unkC7E2 = 100;
        unkC7E4 = 100;
        func_0013A678(character_names, 0, sizeof(character_names));
        func_0013C948(character_names[0], g_field_default_name_fayt);
        func_0013C948(character_names[1], g_field_default_name_sophia);
        func_0013C948(character_names[2], g_field_default_name_maria);
        func_0013C948(character_names[3], g_field_default_name_cliff);
        func_0013C948(character_names[4], g_field_default_name_nel);
        func_0013C948(character_names[5], g_field_default_name_albel);
        func_0013C948(character_names[6], g_field_default_name_roger);
        func_0013C948(character_names[7], g_field_default_name_peppita);
        func_0013C948(character_names[8], g_field_default_name_adray);
        func_0013C948(character_names[9], g_field_default_name_mirage);
        func_0013A678(unkC7E8, 0, sizeof(unkC7E8));
        func_0013A678(unkCF90, 0, sizeof(unkCF90));
        ResidentCheckedRecord* record = reinterpret_cast<ResidentCheckedRecord*>(resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1));

        if (record != 0)
        {
            field_set_checked_fol(record, 0);
        }
    }

    u32 unk00;

    u8 unk04[0x180];

    u8 flags_5000[4];

    u32 variables[256];

    u8 unk588[0xC000];

    u8 unkC588[0x100];

    u8 unkC688[0x28];

    char character_names[10][24];

    u32 unkC7A0;

    u32 unkC7A4;

    u8 unkC7A8[8];

    FieldVec4B unkC7B0;

    FieldVec4B unkC7C0;

    FieldVec4B unkC7D0;

    s16 unkC7E0;

    s16 unkC7E2;

    s16 unkC7E4;

    u8 unkC7E6;

    u8 unkC7E7;

    u8 unkC7E8[0x7A8];

    u8 unkCF90[0xAC8];

    u8 unkDA58[0x88];
};

/** Eight-byte retained resource-loader command. */
struct FieldLoaderCommand
{
    u32 buffer_address;

    u8 kind;

    u8 option;

    u8 unk06[2];
};

/** Retained field loader commands and their resource buffer. */
struct FieldLoaderState
{
    static void* operator new(u32 size);

    /** @brief Release storage through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);

    /** @brief Clear retained loader commands and reset their data buffer. */
    FieldLoaderState()
    {
        func_0013A678(commands, 0, sizeof(commands));
        func_0013A678(unk7e0, 0, sizeof(unk7e0));
        unk17e0 = 0;
        command_count = 0;
        unk17e4 = 0;
        buffer.func_003F5AC0();
        unk798 = 0;
        state = 0;
        unk17e4 = 0;
    }

    u32 unk00;

    LibClass3F5B80 buffer;

    u32 unk798;

    FieldLoaderCommand commands[8];

    u8 unk7dc[4];

    u8 unk7e0[0x1000];

    u16 unk17e0;

    u8 command_count;

    u8 state;

    u8 unk17e4;

    u8 unk17e5[0xB];
};

extern "C"
{
    extern u32 D_001B6434;

    extern u32 D_001B659C;

    extern u32 D_001B65A8;

    extern u32 D_001B65B4;

    extern ResidentHeap* D_001B6698;

    extern LibClass171EA0* D_001B6640;

    extern FieldDisplayState6624* D_001B6624;

    extern u8 D_001CFA00[];

    extern u8 D_36FA80[];

    extern u8 D_3E6880[];

    extern char g_field_default_camera_name[];

}

template <class T>
static inline void field_release_context_object(T*& object);

template <class T>
static inline void field_detach_release_context_object(T*& object);

template <class T>
static inline void field_release_slot_object(T*& object);
static inline void field_delete_render_buffer(LibDrawBuffer*& buffer);
static inline void field_apply_time_step(ResidentContext* context, float step);

/** Partial fixed pool of tracks with a bitmap of used slots. */
template <class T>
struct FieldTrackPool
{
    s32 count;
    s32 unk04;
    T* items;
    s32 capacity;
    s32 words;
    u64* used;
    bool external;
};

/** Partial field runtime exposing the increment used by its updates. */
struct FieldRuntime
{
    u8 unk00[0x5E8];

    FieldCharacterNames* character_names;

    float rate;
};

/** Prefix of either embedded motion state retained by the context owner. */
struct FieldContextMotion
{
    u8 unk00[8];

    FieldClass15B900* list;
};

/** Partial view of the context's FieldClass152410 and its embedded motion states. */
struct FieldContextOwner14
{
    u8 unk00[0x30];

    FieldContextMotion motion;

    u8 unk3c[0x214];

    FieldContextMotion other_motion;

    u8 unk25c[0xB0];

    FieldListObject* unk30c;

    FieldListObject* unk310;
};

/** Partial view of the FieldClass156B50 retained by the context. */
struct FieldContextOwner20
{
    u8 unk00[0x34];

    u8 unk34_0_3 : 4;

    u8 unk34_4 : 1;

    u8 unk34_5_7 : 3;
};

/** Partial field state whose word at 0x90 is cleared during shutdown. */
struct FieldState6628
{
    u8 unk00[0x90];

    u32 unk90;
};

extern "C" void* D_001B6650;
extern "C" void func_4DCFA0(void* state);
extern "C" FieldTrackPool<FieldClass159130>* D_001B6674;
extern "C" FieldTrackPool<FieldClass159390>* D_001B6668;
extern "C" void func_002B9090(FieldClass1595D0* track);
extern "C" void func_002B87A0(FieldClass159780* track);
extern "C" void func_002B91F0(FieldTrackPool<FieldClass159130>* pool, FieldClass159130* track);
extern "C" void func_002B91A0(FieldTrackPool<FieldClass159390>* pool, FieldClass159390* track);

extern "C" u8 D_001B6518;

extern "C" u8 D_001B65B0;

extern "C" u32 D_001B61B4;

extern "C" u32 D_001B65AC;

extern "C" u32 D_001B651C;

extern "C" u32 D_001B654C;

extern "C" u32 D_001B6548;

extern "C" u8 D_001B6510;

extern "C" u8 D_001B65A0;

extern "C" ResidentDmaQueue* D_001B6610;

extern "C" FieldState6628* D_001B6628;

extern "C" void* D_001B663C;

extern "C" FieldTrackPool<FieldClass177F70>* D_001B6664;

extern "C" FieldTrackPool<FieldClass177C70>* D_001B6670;

extern "C" FieldTrackPool<FieldClass177BE0>* D_001B6678;

extern "C" FieldTrackPool<FieldClass174440>* D_001B667C;

extern "C" FieldTrackPool<FieldClass1730F0>* D_001B6680;

/** Partial receiver with a byte at offset 0x60. */
struct FieldByte60AE9E0
{
    u8 pad[0x60];
    u8 value;
};

/** Partial receiver with a float at offset 0x4C. */
struct FieldFloat4CAE9E0
{
    u8 pad[0x4C];
    float value;
};

/**
 * @brief Emit entries through the primary linked emitter.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
void FieldClass157AF0::emit_primary_entries(const LibVector4* position, const LibVector4* first_offset, const LibVector4* second_offset,
                                            const LibVector4* color_scale)
{
    LibVector4 transformed_position;
    LibVector4 transformed_first;
    LibVector4 transformed_second;
    LibVector4 saved_state[2];
    const LibVector4* position_arg;
    const LibVector4* first_offset_arg;
    const LibVector4* second_offset_arg;
    const LibVector4* color_arg;
    u8 flags = primary_emission_flags;

    if (flags & FIELD_EMISSION_POSITION)
    {
        vu0_transform_emission_point(transform_rows, position, &transformed_position);
        position_arg = &transformed_position;
    }
    else
    {
        position_arg = 0;
    }

    if (flags & FIELD_EMISSION_FIRST_OFFSET)
    {
        vu0_transform_emission_direction(transform_rows, first_offset, &transformed_first);
        first_offset_arg = &transformed_first;
    }
    else
    {
        first_offset_arg = 0;
    }

    if (flags & FIELD_EMISSION_SECOND_OFFSET)
    {
        vu0_transform_emission_direction(transform_rows, second_offset, &transformed_second);
        second_offset_arg = &transformed_second;
    }
    else
    {
        second_offset_arg = 0;
    }

    if (flags & FIELD_EMISSION_COLOR_SCALE)
    {
        color_arg = color_scale;
    }
    else
    {
        color_arg = 0;
    }

    vu0_save_emission_state(saved_state);
    primary_emitter->emit_entries(primary_emission_count, position_arg, first_offset_arg, second_offset_arg, color_arg,
                                         0, 0, 0, 0, 0, 0);
    vu0_reset_emission_state();
    vu0_set_emission_delta(D_001B6690);
    vu0_restore_emission_state(saved_state);
}

/**
 * @brief Emit entries through the secondary linked emitter.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set. Its fourth component receives the grid value after emission.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
void FieldClass157AF0::emit_secondary_entries(const LibVector4* position, LibVector4* first_offset, const LibVector4* second_offset,
                                              const LibVector4* color_scale)
{
    if (secondary_emitter != 0)
    {
        LibVector4 transformed_position;
        LibVector4 transformed_first;
        LibVector4 transformed_second;
        LibVector4 saved_state[2];
        const LibVector4* position_arg;
        const LibVector4* first_offset_arg;
        const LibVector4* second_offset_arg;
        const LibVector4* color_arg;
        u8 flags = secondary_emission_flags;

        if (flags & FIELD_EMISSION_POSITION)
        {
            vu0_transform_emission_point(transform_rows, position, &transformed_position);
            position_arg = &transformed_position;
        }
        else
        {
            position_arg = 0;
        }

        if (flags & FIELD_EMISSION_FIRST_OFFSET)
        {
            vu0_transform_emission_direction(transform_rows, first_offset, &transformed_first);
            first_offset_arg = &transformed_first;
            float scale = secondary_emission_scale;
            transformed_first.components[0] *= scale;
            transformed_first.components[1] *= scale;
            transformed_first.components[2] *= scale;
        }
        else
        {
            first_offset_arg = 0;
        }

        if (flags & FIELD_EMISSION_SECOND_OFFSET)
        {
            vu0_transform_emission_direction(transform_rows, second_offset, &transformed_second);
            second_offset_arg = &transformed_second;
        }
        else
        {
            second_offset_arg = 0;
        }

        if (flags & FIELD_EMISSION_COLOR_SCALE)
        {
            color_arg = color_scale;
        }
        else
        {
            color_arg = 0;
        }

        vu0_save_emission_state(saved_state);
        secondary_emitter->emit_entries(secondary_emission_count, position_arg, first_offset_arg, second_offset_arg, color_arg,
                                               0, 0, 0, 0, 0, 0);
        vu0_reset_emission_state();
        vu0_set_emission_delta(D_001B6690);
        vu0_restore_emission_state(saved_state);
        first_offset->components[3] = unk3C;
    }
}

/**
 * @brief Emit entries through the primary linked emitter.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
void FieldClass157E30::emit_primary_entries(const LibVector4* position, const LibVector4* first_offset, const LibVector4* second_offset,
                                            const LibVector4* color_scale)
{
    LibVector4 transformed_position;
    LibVector4 transformed_first;
    LibVector4 transformed_second;
    LibVector4 saved_state[2];
    const LibVector4* position_arg;
    const LibVector4* first_offset_arg;
    const LibVector4* second_offset_arg;
    const LibVector4* color_arg;
    u8 flags = primary_emission_flags;

    if (flags & FIELD_EMISSION_POSITION)
    {
        vu0_transform_emission_point(transform_rows, position, &transformed_position);
        position_arg = &transformed_position;
    }
    else
    {
        position_arg = 0;
    }

    if (flags & FIELD_EMISSION_FIRST_OFFSET)
    {
        vu0_transform_emission_direction(transform_rows, first_offset, &transformed_first);
        first_offset_arg = &transformed_first;
    }
    else
    {
        first_offset_arg = 0;
    }

    if (flags & FIELD_EMISSION_SECOND_OFFSET)
    {
        vu0_transform_emission_direction(transform_rows, second_offset, &transformed_second);
        second_offset_arg = &transformed_second;
    }
    else
    {
        second_offset_arg = 0;
    }

    if (flags & FIELD_EMISSION_COLOR_SCALE)
    {
        color_arg = color_scale;
    }
    else
    {
        color_arg = 0;
    }

    vu0_save_emission_state(saved_state);
    primary_emitter->emit_entries(primary_emission_count, position_arg, first_offset_arg, second_offset_arg, color_arg,
                                         0, 0, 0, 0, 0, 0);
    vu0_reset_emission_state();
    vu0_set_emission_delta(D_001B6690);
    vu0_restore_emission_state(saved_state);
}

/**
 * @brief Emit entries through the secondary linked emitter.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set. Its fourth component receives the grid value after emission.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
void FieldClass157E30::emit_secondary_entries(const LibVector4* position, LibVector4* first_offset, const LibVector4* second_offset,
                                              const LibVector4* color_scale)
{
    if (secondary_emitter != 0)
    {
        LibVector4 transformed_position;
        LibVector4 transformed_first;
        LibVector4 transformed_second;
        LibVector4 saved_state[2];
        const LibVector4* position_arg;
        const LibVector4* first_offset_arg;
        const LibVector4* second_offset_arg;
        const LibVector4* color_arg;
        u8 flags = secondary_emission_flags;

        if (flags & FIELD_EMISSION_POSITION)
        {
            vu0_transform_emission_point(transform_rows, position, &transformed_position);
            position_arg = &transformed_position;
        }
        else
        {
            position_arg = 0;
        }

        if (flags & FIELD_EMISSION_FIRST_OFFSET)
        {
            vu0_transform_emission_direction(transform_rows, first_offset, &transformed_first);
            first_offset_arg = &transformed_first;
            float scale = secondary_emission_scale;
            transformed_first.components[0] *= scale;
            transformed_first.components[1] *= scale;
            transformed_first.components[2] *= scale;
        }
        else
        {
            first_offset_arg = 0;
        }

        if (flags & FIELD_EMISSION_SECOND_OFFSET)
        {
            vu0_transform_emission_direction(transform_rows, second_offset, &transformed_second);
            second_offset_arg = &transformed_second;
        }
        else
        {
            second_offset_arg = 0;
        }

        if (flags & FIELD_EMISSION_COLOR_SCALE)
        {
            color_arg = color_scale;
        }
        else
        {
            color_arg = 0;
        }

        vu0_save_emission_state(saved_state);
        secondary_emitter->emit_entries(secondary_emission_count, position_arg, first_offset_arg, second_offset_arg, color_arg,
                                               0, 0, 0, 0, 0, 0);
        vu0_reset_emission_state();
        vu0_set_emission_delta(D_001B6690);
        vu0_restore_emission_state(saved_state);
        first_offset->components[3] = unk3C;
    }
}

/**
 * @brief Emit entries through the primary linked emitter.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
void FieldClass158170::emit_primary_entries(const LibVector4* position, const LibVector4* first_offset, const LibVector4* second_offset,
                                            const LibVector4* color_scale)
{
    LibVector4 transformed_position;
    LibVector4 transformed_first;
    LibVector4 transformed_second;
    LibVector4 saved_state[2];
    const LibVector4* position_arg;
    const LibVector4* first_offset_arg;
    const LibVector4* second_offset_arg;
    const LibVector4* color_arg;
    u8 flags = primary_emission_flags;

    if (flags & FIELD_EMISSION_POSITION)
    {
        vu0_transform_emission_point(transform_rows, position, &transformed_position);
        position_arg = &transformed_position;
    }
    else
    {
        position_arg = 0;
    }

    if (flags & FIELD_EMISSION_FIRST_OFFSET)
    {
        vu0_transform_emission_direction(transform_rows, first_offset, &transformed_first);
        first_offset_arg = &transformed_first;
    }
    else
    {
        first_offset_arg = 0;
    }

    if (flags & FIELD_EMISSION_SECOND_OFFSET)
    {
        vu0_transform_emission_direction(transform_rows, second_offset, &transformed_second);
        second_offset_arg = &transformed_second;
    }
    else
    {
        second_offset_arg = 0;
    }

    if (flags & FIELD_EMISSION_COLOR_SCALE)
    {
        color_arg = color_scale;
    }
    else
    {
        color_arg = 0;
    }

    vu0_save_emission_state(saved_state);
    primary_emitter->emit_entries(primary_emission_count, position_arg, first_offset_arg, second_offset_arg, color_arg,
                                         0, 0, 0, 0, 0, 0);
    vu0_reset_emission_state();
    vu0_set_emission_delta(D_001B6690);
    vu0_restore_emission_state(saved_state);
}

/**
 * @brief Emit entries through the secondary linked emitter.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set. Its fourth component receives the grid value after emission.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
void FieldClass158170::emit_secondary_entries(const LibVector4* position, LibVector4* first_offset, const LibVector4* second_offset,
                                              const LibVector4* color_scale)
{
    if (secondary_emitter != 0)
    {
        LibVector4 transformed_position;
        LibVector4 transformed_first;
        LibVector4 transformed_second;
        LibVector4 saved_state[2];
        const LibVector4* position_arg;
        const LibVector4* first_offset_arg;
        const LibVector4* second_offset_arg;
        const LibVector4* color_arg;
        u8 flags = secondary_emission_flags;

        if (flags & FIELD_EMISSION_POSITION)
        {
            vu0_transform_emission_point(transform_rows, position, &transformed_position);
            position_arg = &transformed_position;
        }
        else
        {
            position_arg = 0;
        }

        if (flags & FIELD_EMISSION_FIRST_OFFSET)
        {
            vu0_transform_emission_direction(transform_rows, first_offset, &transformed_first);
            first_offset_arg = &transformed_first;
            float scale = secondary_emission_scale;
            transformed_first.components[0] *= scale;
            transformed_first.components[1] *= scale;
            transformed_first.components[2] *= scale;
        }
        else
        {
            first_offset_arg = 0;
        }

        if (flags & FIELD_EMISSION_SECOND_OFFSET)
        {
            vu0_transform_emission_direction(transform_rows, second_offset, &transformed_second);
            second_offset_arg = &transformed_second;
        }
        else
        {
            second_offset_arg = 0;
        }

        if (flags & FIELD_EMISSION_COLOR_SCALE)
        {
            color_arg = color_scale;
        }
        else
        {
            color_arg = 0;
        }

        vu0_save_emission_state(saved_state);
        secondary_emitter->emit_entries(secondary_emission_count, position_arg, first_offset_arg, second_offset_arg, color_arg,
                                               0, 0, 0, 0, 0, 0);
        vu0_reset_emission_state();
        vu0_set_emission_delta(D_001B6690);
        vu0_restore_emission_state(saved_state);
        first_offset->components[3] = unk3C;
    }
}

FieldClass158DD0::FieldClass158DD0()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk20 = 0;
    unk24 = 0;
}

FieldClass158DD0::~FieldClass158DD0()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

float func_002AF510(FieldObject154D50* object)
{
    return 1.0f;
}

float func_002AF520(FieldObject154D50* object)
{
    return 1.0f;
}

float func_002AF530(FieldObject154D50* object)
{
    return 1.0f;
}

float func_002AF540(FieldObject154D50* object)
{
    return 1.0f;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
extern "C" void func_002AF550(FieldClass158DD0* object, const FieldClass158DD0* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

float func_002AF590(FieldObject154D50* object)
{
    return 1.0f;
}

/**
 * @brief Update a scalar after a delay and report when its update timer expires.
 * @param state Timers, increment, and active-update flag.
 * @param value Scalar receiving the saved increment on each active call.
 * @return True when the active-update timer has expired.
 */
bool field_update_timed_value(FieldTimedValueState* state, float* value)
{
    if (state->updating)
    {
        state->update_remaining -= D_001B6688;

        if (state->update_remaining <= 0.0f)
        {
            return true;
        }

        *value += state->value_step;
    }

    if (!(state->delay_remaining <= 0.0f))
    {
        state->delay_remaining -= D_001B6688;

        if (state->delay_remaining <= 0.0f)
        {
            state->updating = 1;

            if (state->update_remaining != 0.0f)
            {
                state->value_step = *value / state->update_remaining;
            }
            else
            {
                state->update_remaining = 0.0f;
            }
        }
    }

    return false;
}

/**
 * @brief Detach and release an object, then clear the stored pointer.
 * @param object Stored intrusive object pointer.
 */
template <class T>
static inline void field_release_slot_object(T*& object)
{
    if (object != 0)
    {
        lib_object_detach_owner(object);
        object->func_003EF740();
        object = 0;
    }
}

/** @brief Release an object through its native Field node prefix and clear its pointer. @param object Object to release. */
template <class T>
static inline void field_release_context_object(T*& object)
{
    if (object != 0)
    {
        reinterpret_cast<FieldListObject*>(object)->func_001DD7B0();
        object = 0;
    }
}

/** @brief Detach and release an object through its native Field node prefix. @param object Object to detach and release. */
template <class T>
static inline void field_detach_release_context_object(T*& object)
{
    if (object != 0)
    {
        lib_object_detach_owner(object);
        reinterpret_cast<FieldListObject*>(object)->func_001DD7B0();
        object = 0;
    }
}

/**
 * @brief Detach and release every occupied object slot.
 * @param owner Slot owner.
 */
void field_clear_object_slots(FieldObjectSlotOwner* owner)
{
    for (s32 i = 0; i < FieldObjectSlotOwner::SLOT_COUNT; i++)
    {
        if (owner->objects[i] != 0)
        {
            field_release_slot_object(owner->objects[i]);
            owner->pending_removal[i] = 0;
        }
    }
}

/**
 * @brief Register every occupied object slot with the Lib object list.
 * @param owner Slot owner.
 */
void field_register_object_slots(FieldObjectSlotOwner* owner)
{
    for (s32 i = 0; i < FieldObjectSlotOwner::SLOT_COUNT; i++)
    {
        if (owner->objects[i] != 0)
        {
            LibClass178DD0& list = lib_object_list_00507c40;
            list.append_node(owner->objects[i], LibClass178DD0::DEFAULT_NODE_KIND);
        }
    }
}

/**
 * @brief Detach every occupied object slot from its current list.
 *
 * Keep the stored pointers and removal flags for later registration.
 * @param owner Slot owner.
 */
void field_detach_object_slots(FieldObjectSlotOwner* owner)
{
    for (s32 i = 0; i < FieldObjectSlotOwner::SLOT_COUNT; i++)
    {
        if (owner->objects[i] != 0)
        {
            lib_object_detach_owner(owner->objects[i]);
        }
    }
}

/**
 * @brief Mark the first slot containing an object for deferred release.
 *
 * Marking a slot does not detach or release its object.
 * @param owner Slot owner.
 * @param object Object to mark.
 */
void field_request_object_slot_removal(FieldObjectSlotOwner* owner, LibClass171EA0* object)
{
    for (s32 i = 0; i < FieldObjectSlotOwner::SLOT_COUNT; i++)
    {
        if (owner->objects[i] == object)
        {
            owner->pending_removal[i] = 1;
            break;
        }
    }
}

/**
 * @brief Store and register an object in the first vacant slot.
 *
 * A full owner leaves the object with the caller.
 * @param owner Slot owner.
 * @param object Object to store and register.
 * @return True if a vacant slot was found; false when all slots are occupied.
 */
bool field_add_object_slot(FieldObjectSlotOwner* owner, LibClass171EA0* object)
{
    for (s32 i = 0; i < FieldObjectSlotOwner::SLOT_COUNT; i++)
    {
        if (owner->objects[i] == 0)
        {
            owner->objects[i] = object;
            LibClass178DD0& list = lib_object_list_00507c40;
            list.append_node(object, LibClass178DD0::DEFAULT_NODE_KIND);
            owner->pending_removal[i] = 0;
            return true;
        }
    }

    return false;
}

/** @brief Detach and release occupied slots marked for removal. */
void FieldObjectSlotOwner::update()
{
    for (s32 i = 0; i < SLOT_COUNT; i++)
    {
        if (pending_removal[i] != 0 && objects[i] != 0)
        {
            field_release_slot_object(objects[i]);
            pending_removal[i] = 0;
        }
    }
}

/** @brief Release every stored object and destroy the intrusive owner base. */
FieldObjectSlotOwner::~FieldObjectSlotOwner()
{
    for (s32 i = 0; i < SLOT_COUNT; i++)
    {
        field_release_slot_object(objects[i]);
    }
}

/** @brief Initialize the intrusive base and clear all slots and removal flags. */
FieldObjectSlotOwner::FieldObjectSlotOwner()
{
    for (s32 i = 0; i < SLOT_COUNT; i++)
    {
        objects[i] = 0;
        pending_removal[i] = 0;
    }
}

/**
 * @brief Delete a rendering buffer and clear its owning pointer.
 * @param buffer Owned rendering buffer, or null.
 */
static inline void field_delete_render_buffer(LibDrawBuffer*& buffer)
{
    delete buffer;
    buffer = 0;
}

/** @brief Release the timed quad records. */
FieldTimedQuadController::~FieldTimedQuadController()
{
    for (s32 i = 0; i < RECORD_COUNT; i++)
    {
        if (records[i] != 0)
        {
            delete records[i];
            records[i] = 0;
        }
    }
}

/**
 * @brief Accept any actor and source for quad generation.
 * @param actor Actor supplying the vertices; unused.
 * @param source Source record associated with the actor; unused.
 * @return Always one.
 */
s32 FieldTimedQuadController::accepts_source(const void* actor, const void* source)
{
    return 1;
}

/** @brief Detach and queue the controller, releasing its rendering resources. */
void FieldTimedQuadController::func_001DD7B0()
{
    lib_object_detach_owner(this);
    resident_enqueue_object(D_001B65F4, this);
    field_release_slot_object(attached_object);

    if (!renderer_external)
    {
        field_delete_render_buffer(renderer);
    }

    renderer = 0;
    renderer_external = 0;
}

/** @brief Release all records and resources, then unset the texture and count. */
void FieldTimedQuadController::func_00272220()
{
    for (s32 i = 0; i < RECORD_COUNT; i++)
    {
        if (records[i] != 0)
        {
            delete records[i];
            records[i] = 0;
        }
    }

    field_release_slot_object(attached_object);

    if (!renderer_external)
    {
        field_delete_render_buffer(renderer);
    }

    renderer = 0;
    renderer_external = 0;
    texture_index = -1;
    record_count = 0;
}

/** @brief Set the low flag bit on the attached transform when present. */
void FieldTimedQuadController::func_00272130()
{
    LibTransform* target = attached_object;
    if (target != 0)
    {
        target->unk6a |= 1;
    }
}

/** @brief Clear the low flag bit on the attached transform when present. */
void FieldTimedQuadController::func_002721A0()
{
    LibTransform* target = attached_object;
    if (target != 0)
    {
        target->unk6a &= 0xFFFE;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002AFDD0);

/**
 * @brief Add a timed quad in the first free record slot.
 *
 * Leave the count unchanged when the pool is full or allocation fails.
 * @param vertices Four aligned vertices to copy.
 * @param side Low bit selects the quad's texture orientation.
 * @param alpha Initial alpha for the hold and fade intervals.
 */
void FieldTimedQuadController::add_quad(const FieldVector4* vertices, u8 side, u8 alpha)
{
    FieldTimedQuad* record = 0;

    for (s32 i = 0; i < RECORD_COUNT; i++)
    {
        if (records[i] == 0)
        {
            records[i] = new (0) FieldTimedQuad;

            if (records[i] == 0)
            {
                return;
            }

            record = records[i];
            break;
        }
    }

    if (record != 0)
    {
        record->side = side;
        record->base_alpha = alpha;

        for (s32 i = 0; i < 4; i++)
        {
            record->vertices[i] = vertices[i];
        }

        record_count++;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", update__24FieldTimedQuadControllerFv);

/** @brief Initialize the quad pool and rendering state. */
FieldTimedQuadController::FieldTimedQuadController()
{
    unk18 = 5;
    func_0013A678(records, 0, sizeof(records));
    texture_index = -1;
    record_count = 0;
    renderer = 0;
    attached_object = 0;
    renderer_external = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B0A10);

extern "C" void func_002B0A80(FieldByte60AE9E0* object)
{
    object->value = 4;
}

/** @brief Destroy the shutdown sequence. */
FieldShutdownSequence::~FieldShutdownSequence()
{
}

/**
 * @brief Report this object's default list kind.
 * @return Always 9.
 */
s32 FieldShutdownSequence::get_default_list_kind()
{
    return 9;
}

/** @brief Run the next stage, then request exit and remove the node after stage three. */
void FieldShutdownSequence::update()
{
    field_run_shutdown_stage(D_001B6430->context, stage);
    stage++;

    if (stage >= 4)
    {
        D_001B6430->context->exit_requested = 1;
        D_001B6420 = 0;
        lib_object_detach_owner(this);
        func_001DD7B0();
    }
}

bool func_002B0BC0(FieldFlagOwner2B0BC0* object)
{
    FieldFlagTarget2B0BC0* target = object->target;
    if (target == 0)
    {
        return false;
    }
    return target->first || target->second;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B0C00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B0D80);

/**
 * @brief Set display alpha blending, creating or removing its update node as needed.
 *
 * Zero detaches the node and queues its removal. The display blend flag and
 * alpha reset when the queued node is destroyed.
 * @param context Field context retaining the blend node.
 * @param alpha Nonzero alpha enables blending; zero requests removal.
 */
extern "C" void field_set_display_blend(ResidentContext* context, float alpha)
{
    if (alpha == 0.0f)
    {
        if (context->display_blend_node != 0)
        {
            lib_object_detach_owner(context->display_blend_node);
            context->display_blend_node->func_001DD7B0();
            context->display_blend_node = 0;
        }
    }
    else
    {
        if (context->display_blend_node == 0)
        {
            context->display_blend_node = new (0) FieldDisplayBlendNode;
            D_001B6614->append_node(context->display_blend_node, -1);
        }

        context->display_blend_node->alpha = alpha;
        LibDisplayState* state = static_cast<LibDisplayState*>(D_001B6650);
        state->blend_enabled = 1;
        state->blend_alpha = alpha;
    }
}

/** @brief Detach the node and add it to the resident release queue. */
void FieldDisplayBlendNode::func_001DD7B0()
{
    lib_object_detach_owner(this);
    resident_enqueue_object(D_001B65F4, this);
}

/**
 * @brief Release the current update callback and retain its replacement.
 * @param context Field context owning the callback.
 * @param callback Replacement callback, or null.
 */
void field_set_update_callback(ResidentContext* context, FieldClass150C10* callback)
{
    if (context->update_callback != 0)
    {
        context->update_callback->func_001FC370();
        context->update_callback = 0;
    }

    context->update_callback = callback;
}

/**
 * @brief Recalculate the scaled field increments and the runtime update rate.
 * @param context Field context retaining the step and its multiplier.
 * @param step New unscaled increment; ordered values at or below zero retain the current one.
 */
static inline void field_apply_time_step(ResidentContext* context, float step)
{
    if (!(step <= 0.0f))
    {
        context->time_step = step;
    }

    float scaled_step = context->time_step * context->time_scale;
    D_001B6688 = scaled_step;
    D_001B6690 = scaled_step / 60.0f;

    if (D_001B657C != 0)
    {
        D_001B657C->rate = scaled_step;
    }
}

/**
 * @brief Recalculate the scaled field increments and the runtime update rate.
 * @param context Field context retaining the step and its multiplier.
 * @param step New unscaled increment; ordered values at or below zero retain the current one.
 */
void field_update_time_step(ResidentContext* context, float step)
{
    field_apply_time_step(context, step);
}

/**
 * @brief Adjust the update interval after an overrun and retain it briefly.
 * @param context Field context and timing state.
 * @param overrun Positive overrun measure; nonpositive values advance or release the hold.
 */
void field_adjust_time_step(ResidentContext* context, s32 overrun)
{
    if (overrun > 0)
    {
        FieldClass150F90* object = 0;

        if (context->unk08 != 0)
        {
            object = context->unk08->current_object;
        }

        if (!D_001B6430->context->unkde_1 && object != 0 && object->func_00204420())
        {
            if (context->unk08 != 0 && context->unk08->unkf5_5)
            {
                context->unkdd.time_step_hold_active = true;
                context->time_step_hold = 5.0f;
                s32 level = overrun + 1;

                if (level > 3)
                {
                    level = 3;
                }

                context->time_step_level = level;
                field_apply_time_step(context, (float)level);
            }
        }
    }
    else if (context->unkdd.time_step_hold_active)
    {
        context->time_step_hold -= 1.0f;

        if (context->time_step_hold <= 0.0f)
        {
            context->unkdd.time_step_hold_active = 0;
            context->time_step_hold = 0.0f;
        }
    }
    else
    {
        context->time_step_level = 1;
        context->unkA0 = 5.0f;
        field_apply_time_step(context, 1.0f);
    }
}

/**
 * @brief Run field rendering and object updates, then finish shutdown after exit.
 * @param context Field context retaining update, display, and timing state.
 */
void field_run_update_loop(ResidentContext* context)
{
    TIMER0_MODE = 0x83;

    for (; func_0011DF10(D_001B65F0, 0) == 0;)
    {
    }

    func_4DCEA0(D_001B6650, true, false);
    D_001B6420 = 1;

    for (; !context->exit_requested;)
    {
        if (!context->skip_render)
        {
            func_4DD830(D_001B6650, context->render_count, D_001B65DC);
        }
        else
        {
            context->skip_render = 0;
        }

        context->render_count++;

        if (D_001B6618 != 0)
        {
            func_0011F770(D_001B6618->packet, 0);
            func_4D76C0(D_001B6618, 16, 16);
        }

        func_4D8AC0();
        func_4D4BE0(D_001B661C);
        D_001B6614->update_nodes();
        context->update_count++;

        if (context->update_callback != 0)
        {
            context->update_callback->func_001FC020();
        }

        resident_drain_release_queues(D_001B65F4);
        resident_get_runtime_owner();
        s32 overrun = 0;
        void* first_attachment = 0;
        void* second_attachment = 0;

        if (context->unk38 != 0)
        {
            first_attachment = context->unk38->unk5cc;
            second_attachment = context->unk38->unk5d0;
        }

        if (context->wait_skip_count > 0 || first_attachment != 0 || second_attachment != 0)
        {
            if (context->wait_skip_count > 0)
            {
                context->wait_skip_count--;
            }

            if (first_attachment != 0 || second_attachment != 0)
            {
                overrun = 1;
            }
            else
            {
                overrun = 0;
            }

            context->display_field = func_4DCFF0(D_001B6650, context->render_count);
            func_0011DF00(D_001B65F0);
        }
        else
        {
            s32 remaining = context->time_step_level;
            context->display_field = func_4DCFF0(D_001B6650, context->render_count);
            for (s32 retries = 5; retries >= 0; retries--)
            {
                remaining -= func_0011DF00(D_001B65F0);

                if (remaining <= 0)
                {
                    break;
                }

                context->display_field = func_0011DF10(D_001B65F0, 0);
            }

            if (remaining < 0)
            {
                overrun = -remaining;
            }
        }

        field_adjust_time_step(context, overrun);
        TIMER0_COUNT = 0;
    }

    field_run_shutdown_stage(context, 4);
    func_00433AA0();

    if (context->unkdd.unk4)
    {
        func_001010D0(resident_get_runtime_owner(), context->unk7c, 1);
    }

    if (context->unkdd.unk5)
    {
        func_001010D0(resident_get_runtime_owner(), context->unk80, 1);
    }
}

/**
 * @brief Initialize the field context and run its update loop.
 * @param context Field context to initialize and run.
 */
void field_initialize_and_run(ResidentContext* context)
{
    field_initialize_context(context);
    field_run_update_loop(context);
}

/**
 * @brief Release field objects, resources and heaps for one shutdown stage.
 * @param context Field context owning the retained objects.
 * @param stage Shutdown stage; stages zero, one, three and four perform work.
 */
extern "C" void field_run_shutdown_stage(ResidentContext* context, s32 stage)
{
    u8 full_release = context->unkdd.unk5;

    switch (stage)
    {
    case 0:
        func_00428B90(1);
        func_004288C0(1);
        D_001B6518 = 0;
        D_001B65B0 = 0;
        func_00110C60(D_001B65F8);
        static_cast<FieldContextOwner20*>(context->unk20)->unk34_4 = 1;

        if (context->unk1c != 0)
        {
            static_cast<FieldListObject*>(context->unk1c)->func_001DD7B0();
        }

        lib_object_detach_owner(context->object_slots);
        field_detach_object_slots(context->object_slots);
        lib_object_detach_owner(context->unk64);
        reinterpret_cast<FieldClass15B0E0*>(context->unk64)->func_002D2170();
        func_002D9730(static_cast<FieldListObject*>(context->unk28));
        lib_object_detach_owner(context->unk28);
        func_0027C020(context->unk58);
        lib_object_detach_owner(context->unk58);
        lib_object_detach_owner(context->unk34);
        lib_object_detach_owner(context->unk14);
        static_cast<FieldContextOwner14*>(context->unk14)->motion.list->func_002DDA70();
        static_cast<FieldContextOwner14*>(context->unk14)->other_motion.list->func_002DDA70();
        lib_object_detach_owner(context->unk54);
        func_001DEF00(reinterpret_cast<FieldFlaggedListObject*>(context->unk04));
        lib_object_detach_owner(&static_cast<FieldListObject&>(*static_cast<FieldClass14FE30*>(context->unk04)));
        lib_object_detach_owner(context->unk4c);
        field_detach_release_context_object(context->display_blend_node);
        lib_object_detach_owner(context->unk08);

        if (full_release)
        {
            if (context->unk5c != 0)
            {
                ::operator delete(context->unk5c);
                context->unk5c = 0;
            }

            void* directory = resident_get_entry_table(resident_get_runtime_owner());
            void* storage = reinterpret_cast<void*>(resident_find_entry(directory, 6));
            func_00101480(directory, 6);
            FieldClass152F00::operator delete(storage);
            storage = reinterpret_cast<void*>(resident_find_entry(directory, 4));
            func_00101480(directory, 4);
            FieldClass152F00::operator delete(storage);
            FieldClass150DB0* resource = reinterpret_cast<FieldClass150DB0*>(resident_find_entry(directory, 5));

            if (resource != 0)
            {
                func_00101480(directory, 5);
                delete resource;
            }

            LibBufferOwner* buffers = reinterpret_cast<LibBufferOwner*>(resident_find_entry(directory, 7));

            if (buffers != 0)
            {
                func_00101480(directory, 7);
                delete buffers;
            }

            func_0040AF80();
            func_00433680();
            func_003EF8A0();
            func_001DEF70(reinterpret_cast<FieldClass150060*>(context->unk04), 0);

            if (context->unk04 != 0)
            {
                static_cast<FieldClass14FE30*>(context->unk04)->func_001DD7B0();
                context->unk04 = 0;
            }

            static_cast<FieldClass1502A0&>(*context->unk4c).func_001DD730();
            field_release_context_object(context->unk4c);
            field_release_context_object(context->unk34);
            field_release_context_object(context->unk54);
            field_release_context_object(context->unk64);
            delete context->unk74;
            context->unk74 = 0;

            if (context->unk24 != 0)
            {
                static_cast<ResidentClass14FA40*>(context->unk24)->func_00104740();
                context->unk24 = 0;
            }

            field_detach_release_context_object(context->unk28);
            field_release_context_object(context->unk58);
            delete static_cast<FieldClass1505F0*>(context->unk3c);
            context->unk3c = 0;
            field_release_context_object(context->object_slots);
            delete context->unk68;
            context->unk68 = 0;
        }
        break;

    case 1:
        field_detach_release_context_object(context->unk30);
        field_detach_release_context_object(context->unk38);
        field_release_slot_object(context->unk48);
        field_detach_release_context_object(context->unk44);
        field_detach_release_context_object(context->unk2c);
        field_release_context_object(context->unk08);
        break;

    case 3:
        {
            FieldContextOwner14* owner = static_cast<FieldContextOwner14*>(context->unk14);
            field_release_context_object(owner->unk30c);
            field_release_context_object(owner->unk310);
            func_00209640(&owner->motion);

            if (full_release)
            {
                field_release_context_object(context->unk14);
            }
        }
        break;

    case 4:
        field_detach_release_context_object(context->input);
        field_detach_release_context_object(context->unk20);
        func_0011DE00(func_001012D0(resident_get_runtime_owner()), 0, 0);
        func_004DBEE0(D_001B65DC, 0);

        ResidentDmaQueue* dma_queue = D_001B6610;

        for (; dma_queue->busy != 0;)
        {
        }

        D_001B61B4 = 0;
        D_001B65AC = 0;
        D_001B651C = 0;
        D_001B654C = 0;
        D_001B6548 = 0;
        D_001B6628->unk90 = 0;
        field_detach_release_context_object(context->unk40);
        delete reinterpret_cast<LibClass174F50*>(D_001B657C);
        D_001B657C = 0;
        func_002B4620(D_001B6664);
        func_002B4C50(D_001B6668);
        func_002B51F0(reinterpret_cast<FieldTrackPool<FieldClass177EE0>*>(D_001B666C));
        func_002B56D0(D_001B6670);
        func_002B5C80(D_001B6674);
        func_002B6180(D_001B6678);
        func_002B6680(D_001B667C);
        func_002B6BA0(D_001B6680);

        if (!D_001B6430->context->unkdd.unk4)
        {
            func_0011DEE0(D_001B65F0, context->unk0c, 0);
        }

        delete D_001B6430;
        D_001B6430 = 0;
        delete context->unk0c;
        context->unk0c = 0;
        delete D_001B6618;
        D_001B6618 = 0;

        if (full_release)
        {
            if (D_001B663C != reinterpret_cast<void*>(0x70000000))
            {
                ::operator delete(D_001B663C);
            }

            D_001B663C = 0;
            func_003EF860();
            func_0040B1F0();
        }

        delete context->unk78;
        context->unk78 = 0;
        resident_drain_release_queues(D_001B65F4);
        delete static_cast<ResidentHeap*>(context->unk70);
        context->unk70 = 0;
        resident_exchange_allocation_heap(0);

        if (full_release)
        {
            func_004E33B0();
        }

        resident_drain_release_queues(D_001B65F4);

        if (full_release)
        {
            delete static_cast<ResidentHeap*>(context->unk6c);
            context->unk6c = 0;
            D_001B65F8->unk0c = 0;
            func_001106B0(D_001B65F8, 0);
        }

        ResidentCheckedRecord* resource =
            reinterpret_cast<ResidentCheckedRecord*>(resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1));
        resource->unk25_4_5 = 0;
        D_001B6420 = 1;
        D_001B6510 = 0;
        D_001B65A0 = 0;
        break;
    }
}

/** @brief Release the listed objects and destroy the inherited list. */
FieldClass159010::~FieldClass159010()
{
    func_001DD730();
}

/**
 * @brief Initialize field objects, runtime resources and pending restore requests.
 * @param context Field context to initialize.
 */
extern "C" void field_initialize_context(ResidentContext* context)
{
    func_004DBEE0(D_001B65DC, 0);
    D_001B6420 = 0;
    D_001B6434 = 0;
    context->unkdd.unk4 = 0;
    context->unkdd.unk5 = 0;
    context->unkdd.unk6 = 0;
    context->unkdd.time_step_hold_active = 0;
    context->exit_requested = 0;
    context->unkdd.unk7 = 0;
    context->unkde_1 = 0;
    context->unkde_2 = 0;
    context->unkde_3 = 0;
    context->unkde_5 = 0;
    context->skip_render = 0;
    context->unkde_7 = 0;
    context->unkdf_0 = 1;
    context->unkde_4 = 0;
    context->unkdf_1 = 0;
    context->unkdd.unk2 = 0;
    context->unkdd.unk1 = 0;
    context->unkdd.unk0 = 0;
    context->unkdf_2 = 0;
    context->render_count = 0;
    context->update_count = 0;
    context->wait_skip_count = 5;
    context->unkA0 = 5.0f;
    context->time_step_hold = 0.0f;
    context->time_scale = 1.0f;
    context->time_step = 1.0f;
    context->unkd0 = 0;
    context->time_step_level = 1;
    context->update_callback = 0;
    context->display_blend_node = 0;
    context->unk14 = 0;
    context->unk5c = 0;
    context->unk6c = 0;
    context->unk0c = 0;
    context->unk38 = 0;
    D_001B6430 = 0;
    context->unk70 = 0;
    context->unk74 = 0;
    context->unk78 = 0;
    context->unk64 = 0;
    context->unk68 = 0;
    context->unk24 = 0;
    context->unk1c = 0;
    context->unk20 = 0;
    context->unk28 = 0;
    context->unkdc = 1;
    context->unkb2 = -1;
    context->unkb0 = -1;
    context->unka8 = -1;
    context->unkaa = 0;
    D_001B6688 = 1.0f;
    D_001B6690 = 1.0f / 60.0f;
    func_002B4620(D_001B6664);
    func_002B4C50(D_001B6668);
    func_002B51F0(reinterpret_cast<FieldTrackPool<FieldClass177EE0>*>(D_001B666C));
    func_002B56D0(D_001B6670);
    func_002B5C80(D_001B6674);
    func_002B6180(D_001B6678);
    func_002B6680(D_001B667C);
    func_002B6BA0(D_001B6680);
    D_001B65A8 = 0;
    D_001B65A0 = 0;
    D_001B659C = 0;
    delete static_cast<ResidentHeap*>(D_001B6684);
    D_001B6684 = 0;

    if (D_001B663C != reinterpret_cast<void*>(0x70000000))
    {
        ::operator delete(D_001B663C);
    }

    D_001B663C = 0;
    delete D_001B6618;
    D_001B6618 = 0;
    delete reinterpret_cast<LibClass174F50*>(D_001B657C);
    D_001B657C = 0;
    lib_object_detach_owner(D_001B6640);

    if (D_001B6640 != 0)
    {
        D_001B6640->func_003EF740();
        D_001B6640 = 0;
    }

    func_00433AA0();
    resident_exchange_allocation_heap(0);
    func_00114650(D_001CFA00, 1);
    void* directory = resident_get_entry_table(resident_get_runtime_owner());
    FieldClass150DB0* saved = reinterpret_cast<FieldClass150DB0*>(resident_find_entry(directory, 5));
    ResidentCheckedRecord* checked = reinterpret_cast<ResidentCheckedRecord*>(resident_find_entry(directory, 1));

    if (saved == 0)
    {
        func_0011DF80(D_001B65F0);
        context->unk6c = ::new (0) ResidentHeap;
        func_00113930(static_cast<ResidentHeap*>(context->unk6c), 0x40C00);
        void* previous_heap = resident_exchange_allocation_heap(context->unk6c);
        LibBufferOwner* buffers = ::new (0) LibBufferOwner;
        func_0040AFA0();
        func_001014B0(directory, buffers, 7);
        LibResourceRecordC4* output = reinterpret_cast<LibResourceRecordC4*>(resident_find_entry(directory, 2));
        LibResourceRecord114* input = reinterpret_cast<LibResourceRecord114*>(resident_find_entry(directory, 3));
        func_004076D0(&output[0], &input[0], 1);
        func_004076D0(&output[1], &input[1], 0);
        func_004076D0(&output[2], &input[2], 0);
        func_004076D0(&output[3], &input[3], 0);
        func_004076D0(&output[4], &input[4], 0);
        func_004076D0(&output[5], &input[5], 0);
        func_004076D0(&output[6], &input[6], 0);
        func_004076D0(&output[7], &input[7], 0);
        context->unk74 = ::new (0) ResidentHeap;
        func_0040B250();
        func_00291B80();
        resident_exchange_allocation_heap(previous_heap);
    }
    else
    {
        context->unk6c = saved->context6c;
        context->unk74 = saved->context74;
    }

    D_001B6698 = static_cast<ResidentHeap*>(context->unk6c);
    void* previous_heap = resident_exchange_allocation_heap(context->unk6c);
    LibClass178B10* temporary = ::new (0) LibClass178B10(768);
    D_001B6640 = temporary;
    D_001B6614->append_node(temporary, -1);
    resident_exchange_allocation_heap(previous_heap);

    if (saved == 0)
    {
        FieldRuntimeState* state = new FieldRuntimeState;
        func_001014B0(directory, state, 4);
    }

    D_001B65B0 = 1;
    D_001B65B4 = 2;
    previous_heap = resident_exchange_allocation_heap(context->unk6c);
    context->unk70 = ::new (0) ResidentHeap;
    resident_exchange_allocation_heap(previous_heap);
    func_00113930(static_cast<ResidentHeap*>(context->unk70), 0x600000);
    resident_exchange_allocation_heap(context->unk70);
    s32 unused_space = D_3E6880 - D_36FA80;

    if (unused_space > 0x800)
    {
        context->unk78 = ::new (0) ResidentHeap;
        func_001138B0(context->unk78, reinterpret_cast<void*>(reinterpret_cast<u32>(D_36FA80) + 0x200), unused_space - 0x800);
    }

    func_002B41A0(D_001B6664, 900);
    func_002B5390(D_001B6670, 901);
    func_002B6310(D_001B667C, 902);
    func_002B47C0(D_001B6668, 2300);
    func_002B4DF0(reinterpret_cast<FieldTrackPool<FieldClass177EE0>*>(D_001B666C), 2801);
    func_002B5870(D_001B6674, 4702);
    func_002B5E20(D_001B6678, 3703);
    func_002B6820(D_001B6680, 2201);
    func_002B0D80(context, 0, 0x7F000000);
    D_001B6510 = 0;
    D_001B6518 = 0;
    FieldDisplayManagerState* display = static_cast<FieldDisplayManagerState*>(D_001B661C);
    display->unk4084 = D_001B6624;
    D_001B6624->unk360 = D_001B6628;
    static_cast<FieldDisplayManagerState*>(D_001B661C)->unk4464->unkaf = 0;
    static_cast<FieldDisplayManagerState*>(D_001B661C)->unk4468->unkaf = 0;
    FieldDisplaySlot* slot = static_cast<FieldDisplayManagerState*>(D_001B661C)->unk4464;

    if (slot != 0)
    {
        slot->unkaf = 1;
    }

    slot = static_cast<FieldDisplayManagerState*>(D_001B661C)->unk4468;

    if (slot != 0)
    {
        slot->unkaf = 1;
    }

    func_0045F5E0();

    if (saved == 0)
    {
        FieldLoaderState* state = new FieldLoaderState;
        func_001014B0(directory, state, 6);
    }

    FieldInputState* input = ::new (0) FieldInputState;
    context->input = reinterpret_cast<ResidentContextInput10*>(input);
    reinterpret_cast<FieldInputState*>(context->input)->clear(1);
    D_001B6614->append_node(context->input, -1);
    ResidentContextRef* reference = ::new (0) ResidentContextRef;

    if (reference != 0)
    {
        reference->context = context;
        reference->unk04 = reinterpret_cast<ResidentCheckedRecord*>(resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1));
    }

    D_001B6430 = reference;
    context->unk2c = reinterpret_cast<FieldResourceList14*>(::new (0) FieldClass150E10);
    D_001B6614->append_node(context->unk2c, -1);
    context->unk30 = ::new (0) FieldResourceLoaderList;
    D_001B6614->append_node(context->unk30, -1);
    context->unk08 = reinterpret_cast<ResidentContext08*>(::new (0) FieldClass153CD0);
    D_001B6614->append_node(context->unk08, -1);

    if (saved == 0)
    {
        context->unk14 = new FieldClass152410;
    }
    else
    {
        context->unk14 = saved->context14;
    }

    D_001B6614->append_node(context->unk14, -1);
    FieldClass1516A0* script = ::new (0) FieldClass1516A0;
    context->unk38 = reinterpret_cast<ResidentContextObject38*>(script);

    if (saved != 0)
    {
        FieldClass150DC0* destination = reinterpret_cast<FieldClass150DC0*>(context->unk38);
        FieldClass150DC0* source = &saved->script;
        *destination = *source;
        reinterpret_cast<FieldClass150DC0*>(context->unk38)->owner = 0;
    }

    D_001B6614->append_node(context->unk38, -1);
    D_001B657C->character_names = static_cast<FieldCharacterNames*>(reinterpret_cast<FieldClass1516A0*>(context->unk38));

    if (saved == 0)
    {
        context->unk64 = reinterpret_cast<ResidentContextObject64*>(new FieldClass15B0E0);
    }
    else
    {
        context->unk64 = saved->context64;
    }

    D_001B6614->append_node(context->unk64, -1);

    if (saved == 0)
    {
        context->unk04 = new FieldClass14FE30;
    }
    else
    {
        context->unk04 = saved->context04;
    }

    D_001B6614->append_node(static_cast<FieldListObject*>(static_cast<FieldClass14FE30*>(context->unk04)), -1);
    context->unk44 = reinterpret_cast<ResidentContextObject52*>(::new (0) FieldClass1537C0);
    FieldClass1537C0* camera_controller = reinterpret_cast<FieldClass1537C0*>(context->unk44);
    camera_controller->unk51_0 = 0;
    camera_controller->unk20 = 10.0f;
    camera_controller->unk34 = 0;
    camera_controller->unk3c = 0;
    camera_controller->unk51_2 = 0;
    D_001B6614->append_node(context->unk44, -1);

    if (saved == 0)
    {
        context->unk4c = new FieldClass154CC0;
    }
    else
    {
        context->unk4c = saved->context4c;
    }

    D_001B6614->append_node(context->unk4c, -1);

    if (saved == 0)
    {
        context->unk3c = new FieldClass1505F0;
    }
    else
    {
        context->unk3c = saved->context3c;
    }

    if (saved == 0)
    {
        context->unk34 = new FieldClass1522C0;
    }
    else
    {
        context->unk34 = saved->context34;
    }

    D_001B6614->append_node(context->unk34, -1);

    if (saved == 0)
    {
        context->unk58 = reinterpret_cast<ResidentContextObject58*>(new FieldClass1557B0);
    }
    else
    {
        context->unk58 = static_cast<ResidentContextObject58*>(saved->context58);
    }

    D_001B6614->append_node(context->unk58, -1);
    context->unk48 = ::new (0) FieldClass1534B0;
    static_cast<LibClass178DD0*>(D_001B661C)->append_node(context->unk48, -1);
    context->unk40 = ::new (0) FieldClass153590;
    D_001B6614->append_node(context->unk40, -1);
    context->unk20 = ::new (0) FieldClass156B50;
    D_001B6614->append_node(context->unk20, -1);

    if (saved == 0)
    {
        context->object_slots = new FieldObjectSlotOwner;
    }
    else
    {
        context->object_slots = saved->object_slots;
    }

    D_001B6614->append_node(context->object_slots, -1);

    if (saved == 0)
    {
        previous_heap = resident_exchange_allocation_heap(context->unk6c);
        context->unk24 = ::new (0) ResidentClass14FC90;
        resident_exchange_allocation_heap(previous_heap);
    }
    else
    {
        context->unk24 = saved->context24;
    }

    reinterpret_cast<FieldClass1516A0*>(context->unk38)->refresh_field_character_state();
    s32 extra_budget = func_00120370(static_cast<ResidentClass14FC90*>(context->unk24));

    if (extra_budget > 0)
    {
        func_001200C0(static_cast<ResidentClass14FC90*>(context->unk24), extra_budget + 300);
    }

    if (saved == 0)
    {
        context->unk54 = new FieldClass154E90;
    }
    else
    {
        context->unk54 = saved->context54;
    }

    D_001B6614->append_node(context->unk54, -1);

    if (saved == 0)
    {
        context->unk28 = new FieldClass15B800;
    }
    else
    {
        context->unk28 = saved->context28;
    }

    func_002D9F80(static_cast<FieldState2D9F80*>(context->unk28));
    D_001B6614->append_node(context->unk28, -1);

    if (saved == 0)
    {
        context->unk68 = new FieldClass159010;
    }
    else
    {
        context->unk68 = saved->context68;
    }

    FieldVec4A initial;
    initial.x = 0.0f;
    initial.y = -320.0f;
    initial.z = 160.0f;
    static_cast<FieldClass152410*>(context->unk14)->unk40 = initial;
    func_002263B0(static_cast<FieldClass152410*>(context->unk14));

    if (saved == 0)
    {
        context->unk18 = new FieldClass152350;
        static_cast<FieldClass152350*>(context->unk18)->unk74 = 0;
        static_cast<LibClass178DD0*>(static_cast<FieldClass14FE30*>(context->unk04))->append_node(context->unk18, -1);
    }
    else
    {
        context->unk18 = func_001DEE30(reinterpret_cast<FieldFlaggedListObject*>(context->unk04), 0, 0x10);
        func_00204DC0(context->unk18);
    }

    if (saved == 0)
    {
        func_0020F230(reinterpret_cast<FieldClass1516A0*>(context->unk38), 0, 0x80000000, 0, 0, 0, 0, 30.0f, 0.0f, 0.0f);
        void* created = 0;

        s32 mode = checked->unk25_4_5;

        switch (static_cast<u8>(mode))
        {
        case 0:
        {
            FieldClass15BBB0* camera = ::new (0) FieldClass15BBB0;

            FieldVec4A origin(0.0f, 0.0f, 0.0f, 0.0f);
            camera->unk9c0 = 0x57;
            camera->unk9d0 = origin;
            camera->unk9e0 = 0;
            camera->unk9e4 = 0;
            camera->unk9e8 = 0;
            func_0013C948(camera->name, g_field_default_camera_name);
            camera->unk9fd_0 = 1;
            camera->unk9ca = 0;
            static_cast<LibClass178DD0*>(D_001B661C)->append_node(camera, -1);
            break;
        }
        case 1:
            func_00254230(D_001B6430->context->unk44, 7, 2, 0.0f);
            break;
        case 2:
            created = func_00258C90(context->unk08, 0, 1, 1);
            break;
        }

        if (created != 0)
        {
            static_cast<ResidentContextObject52*>(created)->unk40 = 0x4000;
        }
    }
    else
    {
        func_0020F230(reinterpret_cast<FieldClass1516A0*>(context->unk38), 0, 0x80000000, 0x80000000, 0, 0, 0, 0.0f, 0.0f, 0.0f);
        FieldLoaderState* state = reinterpret_cast<FieldLoaderState*>(resident_find_entry(directory, 6));

        switch (state->state)
        {
        case 3:
            state->state = 2;
        case 2:
        {
            FieldContextResourceLoader* loader = new FieldContextResourceLoader;

            if (loader->unk30_0)
            {
                if (loader->requests != 0)
                {
                    delete[] loader->requests;
                }

                loader->requests = new (0) FieldSceneResourceRequest[3];
            }
            else
            {
                previous_heap = resident_exchange_allocation_heap(D_001B6430->context->unk6c);
                if (loader->requests != 0)
                {
                    delete[] loader->requests;
                }

                loader->requests = new (0) FieldSceneResourceRequest[3];
                resident_exchange_allocation_heap(previous_heap);
            }

            loader->request_capacity = 3;
            u8 kinds = 0;
            s32 command_count = state->command_count;

            for (s32 i = 0; i < command_count; i++)
            {
                FieldLoaderCommand* command = &state->commands[i];
                field_append_loaded_resource(loader, command->buffer_address, command->kind, command->option & 1);

                switch (command->kind)
                {
                case 1:
                    kinds |= 1;
                    break;
                case 0:
                    kinds |= 2;
                    break;
                case 2:
                    kinds |= 4;
                    break;
                }
            }

            const u32 present_kinds = kinds;
            s32 added = 0;

            if (!(present_kinds & 2) && (s32)func_0011C8C0(D_001B65E4, D_303CB0[saved->resource_index].file_key) > 0x800)
            {
                field_append_file_request(loader, D_303CB0[saved->resource_index].file_key, 0);
                added++;
            }

            if (!(present_kinds & 1))
            {
                FieldSceneResourceRequest* record = field_append_file_request(loader, D_303CB0[saved->resource_index].file_key + 1, 1);
                added++;
                record->byte_capacity = (D_303CB0[saved->resource_index].byte_count + 0x7FF) & ~0x7FF;
            }

            if (!(present_kinds & 4))
            {
                field_append_file_request(loader, func_002D4B30(saved->resource_index, 0), 2);
                added++;
            }

            loader->completion_callback = static_cast<FieldClass1DD400*>(reinterpret_cast<FieldClass153CD0*>(context->unk08));
            loader->resource_index = saved->resource_index;
            loader->load_auxiliary = 1;

            if (added != 0)
            {
                static_cast<LibClass178DD0&>(*static_cast<FieldResourceLoaderList*>(context->unk30)).append_node(loader, -1);
                return;
            }

            loader->request_state = 1;
            loader->func_001DDB30(0);
            loader->advance_requests();
            loader->finish_requests();
            break;
        }
        }
    }
}

/**
 * @brief Store clamped Fol and refresh its checksum when the saved record is valid.
 * @param record Checked resident record.
 * @param fol Fol value to store, limited to zero through 99,999,999.
 */
extern "C" void field_set_checked_fol(ResidentCheckedRecord* record, s32 fol)
{
    u16 checksum = record->checksum;
    const u8* end = reinterpret_cast<const u8*>(&record->checksum);
    const u8* data = record->unk26;

    if (checksum == func_00457470(record->checksum_seed, data, end - data))
    {
        fol += 40597;
        fol = clamp(fol, 40597, 100040596);
        fol -= 40597;
        record->encoded_fol = fol ^ 0x7CE3C7F7;
        record->checksum_seed = resident_next_random_word();
        end = reinterpret_cast<const u8*>(&record->checksum);
        data = record->unk26;
        record->checksum = func_00457470(record->checksum_seed, data, end - data);
    }
}

/**
 * @brief Clear the 32 runtime flags addressed by script keys starting at 0x5000.
 * @param values Runtime resource section containing the flags.
 */
extern "C" void field_clear_flags_5000(FieldRuntimeValues* values)
{
    func_0013A678(values->flags_5000, 0, sizeof(values->flags_5000));
}

/** @brief Disable display blending and restore the default alpha. */
FieldDisplayBlendNode::~FieldDisplayBlendNode()
{
    LibDisplayState* state = static_cast<LibDisplayState*>(D_001B6650);
    state->blend_enabled = 0;
    state->blend_alpha = 0.5f;
}

/**
 * @brief Report this object's default list kind.
 * @return Always 14.
 */
s32 FieldDisplayBlendNode::get_default_list_kind()
{
    return 14;
}

/** @brief Rebuild the display drawing commands. */
void FieldDisplayBlendNode::update()
{
    func_4DCFA0(D_001B6650);
}

/**
 * @brief Append an already loaded resource when a request slot remains.
 * @param loader Resource loader.
 * @param buffer_address Address of the resource buffer.
 * @param kind Resource kind stored in the request.
 * @param release_buffer Low bit selects whether to free the buffer on release.
 */
extern "C" void field_append_loaded_resource(FieldContextResourceLoader* loader, u32 buffer_address, u8 kind, u32 release_buffer)
{
    if (loader->request_count < loader->request_capacity)
    {
        loader->requests[loader->request_count].reset_request();
        FieldSceneResourceRequest* record = &loader->requests[loader->request_count];
        record->buffer_base = buffer_address;
        record->unk08_0 = 1;
        loader->requests[loader->request_count].unk16_1 = release_buffer;
        loader->requests[loader->request_count].unk16_0 = 1;
        loader->requests[loader->request_count].slot_index = loader->request_count;
        loader->requests[loader->request_count].kind = kind;
        loader->request_count++;
    }
}

#include "overlays/lib/vector_inlines.h"

/** 16-byte keyframe of FieldClass159780; the value's fourth component is its key. */
struct FieldTrackKey159780
{
    /** @brief Leave the value uninitialized. */
    FieldTrackKey159780()
    {
    }

    FieldVec4B value;
};

/** 48-byte vector keyframe of FieldClass1595D0: a FieldClass159780 keyframe and two auxiliary vectors. */
struct FieldTrackKey1595D0 : public FieldTrackKey159780
{
    /** @brief Leave the vectors uninitialized. */
    FieldTrackKey1595D0()
    {
    }

    FieldVec4B first;
    FieldVec4B second;
};

/** 32-byte keyframe of FieldClass159810: a key and a value at offset 0x10. */
struct FieldTrackKey159810
{
    /** @brief Leave the keyframe uninitialized. */
    FieldTrackKey159810();

    float key;
    FieldVec4B value;
};

/** Partial 48-byte keyframe of FieldClass1598A0 with its key first. */
struct FieldTrackKey1598A0
{
    /** @brief Leave the keyframe uninitialized. */
    FieldTrackKey1598A0();

    float key;
    u8 unk04[0x2C];
};

/** Partial 32-byte keyframe of FieldClass159660 with its key first. */
struct FieldTrackKey159660
{
    /** @brief Leave the keyframe uninitialized. */
    FieldTrackKey159660();

    float key;
    u8 unk04[0x1C];
};

/** 8-byte packed keyframe of FieldClass159540: three halfword values and a halfword key. */
struct FieldTrackKey159540
{
    /**
     * @brief Copy the values and key.
     * @param entry Entry to copy.
     * @return This entry.
     */
    FieldTrackKey159540& operator=(const FieldTrackKey159540& entry)
    {
        unk00[0] = entry.unk00[0];
        unk00[1] = entry.unk00[1];
        unk00[2] = entry.unk00[2];
        key = entry.key;
        return *this;
    }

    s16 unk00[3];
    s16 key;
};

/** 8-byte scalar keyframe of FieldClass1596F0: a key followed by its value. */
struct FieldTrackKey1596F0
{
    /**
     * @brief Copy the key and value.
     * @param entry Entry to copy.
     * @return This entry.
     */
    FieldTrackKey1596F0& operator=(const FieldTrackKey1596F0& entry)
    {
        key = entry.key;
        value = entry.value;
        return *this;
    }

    float key;
    float value;
};

/**
 * @brief Subtract the first three components.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 * @return Difference, keeping the left vector's fourth component.
 */
static inline FieldVec4A sequence_difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4A value;
    *(unsigned __int128*)&value = *(const unsigned __int128*)&left;
    value.x -= right.x;
    value.y -= right.y;
    value.z -= right.z;
    return value;
}

/** @brief Return a FieldClass1595D0 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey1595D0* entry_1595D0(const FieldSequenceState40* object, s32 index)
{
    return &static_cast<const FieldTrackKey1595D0*>(object->unk04)[index];
}

/** @brief Return a FieldClass159780 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey159780* entry_159780(const FieldSequenceState20* object, s32 index)
{
    return &static_cast<const FieldTrackKey159780*>(object->unk04)[index];
}

/** @brief Return a FieldClass159810 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey159810* entry_159810(const FieldSequenceState30* object, s32 index)
{
    return &static_cast<const FieldTrackKey159810*>(object->unk04)[index];
}

/** @brief Return a FieldClass1598A0 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey1598A0* entry_1598A0(const FieldSequenceState40* object, s32 index)
{
    return &static_cast<const FieldTrackKey1598A0*>(object->unk04)[index];
}

/** @brief Return a FieldClass159660 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey159660* entry_159660(const FieldSequenceState30* object, s32 index)
{
    return &static_cast<const FieldTrackKey159660*>(object->unk04)[index];
}

/** @brief Return a FieldClass159540 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey159540* entry_159540(const FieldSequenceState10* object, s32 index)
{
    return &static_cast<const FieldTrackKey159540*>(object->unk04)[index];
}

/** @brief Return a FieldClass159540 keyframe's key. @param object Sequence receiver. @param index Entry index. @return Key as a float. */
static inline float key_159540(const FieldSequenceState10* object, s32 index)
{
    return entry_159540(object, index)->key;
}

/** @brief Return a FieldClass1596F0 keyframe. @param object Sequence receiver. @param index Entry index. @return Entry. */
static inline const FieldTrackKey1596F0* entry_1596F0(const FieldSequenceState10* object, s32 index)
{
    return &static_cast<const FieldTrackKey1596F0*>(object->unk04)[index];
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B41A0(FieldTrackPool<FieldClass177F70>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass177F70[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass177F70::~FieldClass177F70()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __ct__16FieldClass177F70Fv);



/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B4620(FieldTrackPool<FieldClass177F70>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B47C0(FieldTrackPool<FieldClass159390>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass159390[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass159390::~FieldClass159390()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __ct__16FieldClass159390Fv);



/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B4C50(FieldTrackPool<FieldClass159390>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B4DF0(FieldTrackPool<FieldClass177EE0>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass177EE0[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass177EE0::~FieldClass177EE0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __ct__16FieldClass177EE0Fv);


/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B51F0(FieldTrackPool<FieldClass177EE0>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B5390(FieldTrackPool<FieldClass177C70>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass177C70[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].unk2b_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __ct__16FieldClass177C70Fv);

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B56D0(FieldTrackPool<FieldClass177C70>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].unk2b_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B5870(FieldTrackPool<FieldClass159130>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass159130[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass159130::~FieldClass159130()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __ct__16FieldClass159130Fv);


/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B5C80(FieldTrackPool<FieldClass159130>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B5E20(FieldTrackPool<FieldClass177BE0>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass177BE0[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass177BE0::~FieldClass177BE0()
{
}

FieldClass177BE0::FieldClass177BE0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B6180);

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B6310(FieldTrackPool<FieldClass174440>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass174440[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass174440::~FieldClass174440()
{
}

FieldClass174440::FieldClass174440()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B6680(FieldTrackPool<FieldClass174440>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

/**
 * @brief Allocate the pool's tracks, mark them pooled and clear the used bitmap.
 * @param pool Pool to fill.
 * @param count Number of tracks.
 * @return One on success, or zero when the tracks could not be allocated.
 */
extern "C" s32 func_002B6820(FieldTrackPool<FieldClass1730F0>* pool, s32 count)
{
    s32 index;
    s32 words;
    s32 word;
    pool->items = new (0) FieldClass1730F0[count];
    if (pool->items == 0)
    {
        return 0;
    }
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = true;
    }
    if (!pool->external)
    {
        delete[] pool->used;
    }
    pool->capacity = count;
    pool->words = (u32)(count + 63) >> 6;
    pool->used = new (0) u64[pool->words];
    pool->external = false;
    pool->count = count;
    pool->unk04 = 0;
    words = pool->words;
    for (word = 0; word < words; word++)
    {
        pool->used[word] = 0;
    }
    return 1;
}

FieldClass1730F0::~FieldClass1730F0()
{
}

FieldClass1730F0::FieldClass1730F0()
{
}

/**
 * @brief Release every track in the pool and its storage.
 * @param pool Pool to clear.
 */
extern "C" void func_002B6BA0(FieldTrackPool<FieldClass1730F0>* pool)
{
    s32 count = pool->count;
    s32 index;
    for (index = 0; index < count; index++)
    {
        pool->items[index].state.unk13_2 = false;
    }
    delete[] pool->items;
    if (!pool->external)
    {
        delete[] pool->used;
        pool->used = 0;
    }
    pool->items = 0;
    pool->count = 0;
}

extern "C" void func_4B1640(void* object);

/** @brief Forward the object to func_4B1640. @param object Object to forward. */
extern "C" void func_002B6D40(void* object)
{
    func_4B1640(object);
}

void FieldClass159130::func_001DF230()
{
    if (this != 0)
    {
        if (state.unk13_2)
        {
            func_slot94();
        }
        else
        {
            delete this;
        }
    }
}

void FieldClass159130::func_slot94()
{
    func_002B9090(this);
    func_002B91F0(D_001B6674, this);
}

float FieldClass1591D0::func_002B6DF0(float key)
{
    return func_4B16C0(this, key);
}

void FieldClass159390::func_001DF230()
{
    if (this != 0)
    {
        if (state.unk13_2)
        {
            func_slot84();
        }
        else
        {
            delete this;
        }
    }
}

void FieldClass159390::func_slot84()
{
    func_002B87A0(this);
    func_002B91A0(D_001B6668, this);
}

void FieldClass159300::func_002B83C0()
{
    unk90 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    FieldClass159780::func_002B83C0();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B6EE0);

void FieldClass159300::func_002B73D0(FieldVec4B* output) const
{
    if (unk04 != 0)
    {
        *output = sequence_difference(static_cast<const FieldTrackKey159780*>(unk04)[state.unk08 - 1].value, static_cast<const FieldTrackKey159780*>(unk04)[0].value);
    }
}

void func_002B7440(FieldSequenceVectorA0* object, FieldVec4B* output)
{
    *output = object->unkA0;
}

void FieldClass1594B0::func_002B8860()
{
    unk48 = 0;
    FieldClass1596F0::func_002B8860();
}

void func_002B7480(FieldSampleOwner2B7480* object, float* output)
{
    float* values = object->values;
    if (values != 0)
    {
        *output = values[2 * object->index - 1] - values[1];
    }
}

extern "C" void func_002B74B0(const FieldFloat4CAE9E0* object, float* output)
{
    *output = object->value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B74C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B7510);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B7560);

FieldClass159980::FieldClass159980()
{
    unk00 = 0;
}

s32 FieldClass159270::func_002B9900(const FieldVec4A* value, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (state.unk08 >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey159780*>(unk04)[state.unk08].value = *value;
    static_cast<FieldTrackKey159780*>(unk04)[state.unk08].value.w = key;
    state.span = key - static_cast<FieldTrackKey159780*>(unk04)[0].value.w;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

s32 FieldClass159270::func_002B98C0(s32 index, float key, const FieldVec4A* value)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey159780*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey159780*>(unk04)[index].value.w = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey159780*>(unk04)[0].value.w;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    return 1;
}

s32 FieldClass159270::func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    if (key)
    {
        *key = static_cast<const FieldTrackKey159780*>(unk04)[index].value.w;
    }
    if (value)
    {
        *value = static_cast<const FieldTrackKey159780*>(unk04)[index].value;
    }
    return 1;
}

void FieldClass159090::func_002B8C50()
{
    unkB0 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    FieldClass1595D0::func_002B8C50();
}

s32 FieldClass159090::func_002B7810(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (state.unk08 >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey1595D0*>(unk04)[state.unk08].value = *value;
    static_cast<FieldTrackKey1595D0*>(unk04)[state.unk08].first = *first;
    static_cast<FieldTrackKey1595D0*>(unk04)[state.unk08].second = *second;
    static_cast<FieldTrackKey1595D0*>(unk04)[state.unk08].value.w = key;
    state.span = key - static_cast<FieldTrackKey1595D0*>(unk04)[0].value.w;
    state.unk08++;
    return 1;
}

/**
 * @brief Return a vector, or a zeroed fallback when it is missing.
 * @param vector Optional vector.
 * @param zero Storage for the zero vector.
 * @return The vector, or zero after clearing it.
 */
static inline const FieldVec4A* track_vector(const FieldVec4A* vector, FieldVec4A* zero)
{
    if (!vector)
    {
        zero->x = 0.0f;
        zero->y = 0.0f;
        zero->z = 0.0f;
        zero->w = 0.0f;
        return zero;
    }
    return vector;
}

s32 FieldClass159090::func_002BB970(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return func_002B7810(value, first, second, key);
}

s32 FieldClass159090::func_002B7960(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey1595D0*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].first = *first;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].second = *second;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].value.w = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey1595D0*>(unk04)[0].value.w;
    }
    return 1;
}

s32 FieldClass159090::func_002BB9A0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return func_002B7960(index, key, value, first, second);
}

s32 FieldClass159090::func_002BB9D0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    return func_002B9F50(index, key, value, first, second);
}

void FieldClass159090::func_002BBA00(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    second = track_vector(second, &zero_second);
    first = track_vector(first, &zero_first);
    func_002B9EC0(value, first, second, key);
}

s32 FieldClass159090::func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    if (key)
    {
        *key = static_cast<const FieldTrackKey1595D0*>(unk04)[index].value.w;
    }
    if (value)
    {
        *value = static_cast<const FieldTrackKey1595D0*>(unk04)[index].value;
    }
    if (first)
    {
        *first = static_cast<const FieldTrackKey1595D0*>(unk04)[index].first;
    }
    if (second)
    {
        *second = static_cast<const FieldTrackKey1595D0*>(unk04)[index].second;
    }
    return 1;
}

void FieldClass159090::func_001DF300()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    func_002BBA00(&zero, &zero, &zero, 0.0f);
}

void func_002B7C80(FieldSequenceVectorC0* object, FieldVec4B* output)
{
    *output = object->unkC0;
}

/**
 * @brief Return the difference between the endpoint vectors.
 * @param object Sequence receiver.
 * @param output Receives the difference; unchanged when there are no entries.
 */
extern "C" void func_002B7CA0(const FieldSequenceState40* object, FieldVec4B* output)
{
    if (object->unk04 != 0)
    {
        *output = sequence_difference(entry_1595D0(object, object->state.unk08 - 1)->value, entry_1595D0(object, 0)->value);
    }
}

FieldClass159970::FieldClass159970()
{
}

FieldClass159960::FieldClass159960()
{
}

FieldClass159950::FieldClass159950()
{
    func_002B7DA0();
}

void FieldClass159950::func_002B7DA0()
{
    unk10 = 0;
    unk12 = 0;
    unk14 = 0;
    unk18 = 0;
}

FieldClass159940::FieldClass159940()
{
    func_002B7E00();
}

void FieldClass159940::func_002B7E00()
{
    unk10 = 0;
    unk12 = 0;
    unk14 = 0;
    unk18 = 0;
}

FieldClass159930::FieldClass159930()
{
    func_002B7E60();
}

void FieldClass159930::func_002B7E60()
{
    unk04 = 0;
    unk06 = 0;
    unk08 = 0;
    unk0c = 0;
}

extern "C" void func_002B7EF0(FieldClass1598A0* track);

FieldClass1598A0::~FieldClass1598A0()
{
    func_002B7EF0(this);
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B7EF0(FieldClass1598A0* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey1598A0*>(track->unk04);
    }
    track->unk04 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", __dt__16FieldClass159810Fv);

void FieldClass159810::func_002B7FB0(s32 mode)
{
    state.unk12_0_3 = mode;
    state.unk13_0 = state.unk12_0_3 == 4 || state.unk12_4_7 == 4;
}

void FieldClass159810::func_002B8010(s32 mode)
{
    state.unk12_4_7 = mode;
    state.unk13_0 = state.unk12_0_3 == 4 || state.unk12_4_7 == 4;
}

s32 func_002B8070(FieldSequenceState30* object)
{
    return object->state.unk00;
}

s16 func_002B8080(FieldSequenceState30* object)
{
    return object->state.unk08;
}

void func_002B8090(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass159810::func_002B80B0(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

void* func_002B8100(FieldSequenceState30* object)
{
    return object->unk04;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B8110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B81F0);

extern "C" void func_002B87A0(FieldClass159780* track);

FieldClass159780::~FieldClass159780()
{
    func_002B87A0(this);
}

void FieldClass159780::func_002B83C0()
{
    unk04 = 0;
    state.unk12_0_3 = 1;
    state.unk12_4_7 = 1;
    state.unk0a = 0;
    state.unk08 = 0;
    state.unk0c = -1;
    state.unk00 = 0;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk13_0 = 0;
    state.unk13_1 = 0;
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002B8450(FieldSequenceState20* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_159780(object, count - 1)->value.w - entry_159780(object, 0)->value.w;
}

void func_002B84A0(FieldSequenceState20* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

void func_002B8500(FieldSequenceState20* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002B8560(FieldSequenceState20* object)
{
    return object->state.unk00;
}

s16 func_002B8570(FieldSequenceState20* object)
{
    return object->state.unk08;
}

s16 func_002B8580(FieldSequenceState20* object)
{
    return object->state.unk0a;
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002B8590(const FieldSequenceState20* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_159780(object, index)->value.w)
        {
            return 1;
        }
    }
    return 0;
}

void func_002B85E0(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002B8600(const FieldSequenceState20* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_159780(object, object->state.unk08 - 1)->value.w - entry_159780(object, 0)->value.w;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B8650);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass159780::func_002B86B0(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002B8700(const FieldSequenceState20* object, float key)
{
    float first = entry_159780(object, 0)->value.w;
    float range = entry_159780(object, object->state.unk08 - 1)->value.w - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

void* func_002B8790(FieldSequenceState20* object)
{
    return object->unk04;
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B87A0(FieldClass159780* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey159780*>(track->unk04);
    }
    track->unk04 = 0;
}

extern "C" void func_002B8AD0(FieldClass1596F0* track);

FieldClass1596F0::~FieldClass1596F0()
{
    func_002B8AD0(this);
}

void FieldClass1596F0::func_002B8860()
{
    unk04 = 0;
    state.unk12_0_3 = 1;
    state.unk12_4_7 = 1;
    state.unk0a = 0;
    state.unk08 = 0;
    state.unk0c = -1;
    state.unk00 = 0;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk13_0 = 0;
    state.unk13_1 = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002B88F0(FieldSequenceState10* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey1596F0*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey1596F0[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}

void func_002B8990(FieldSequenceState10* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

void func_002B89F0(FieldSequenceState10* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002B8A50(FieldSequenceState10* object)
{
    return object->state.unk00;
}

s16 func_002B8A60(FieldSequenceState10* object)
{
    return object->state.unk08;
}

s16 func_002B8A70(FieldSequenceState10* object)
{
    return object->state.unk0a;
}

extern "C" float func_002B8A80(FieldSequenceState10* object)
{
    return 0.0f;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void FieldClass1596F0::func_002B8A90(float key, float* output) const
{
    *output = func_slot80(key);
}

void* func_002B8AC0(FieldSequenceState10* object)
{
    return object->unk04;
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B8AD0(FieldClass1596F0* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey1596F0*>(track->unk04);
    }
    track->unk04 = 0;
}

extern "C" void func_002B8B90(FieldClass159660* track);

FieldClass159660::~FieldClass159660()
{
    func_002B8B90(this);
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B8B90(FieldClass159660* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey159660*>(track->unk04);
    }
    track->unk04 = 0;
}

FieldClass1595D0::~FieldClass1595D0()
{
    func_002B9090(this);
}

void FieldClass1595D0::func_002B8C50()
{
    unk04 = 0;
    state.unk12_0_3 = 1;
    state.unk12_4_7 = 1;
    state.unk0a = 0;
    state.unk08 = 0;
    state.unk0c = -1;
    state.unk00 = 0;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk13_0 = 0;
    state.unk13_1 = 0;
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002B8CE0(FieldSequenceState40* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_1595D0(object, count - 1)->value.w - entry_1595D0(object, 0)->value.w;
}

void func_002B8D30(FieldSequenceState40* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

void func_002B8D90(FieldSequenceState40* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002B8DF0(FieldSequenceState40* object)
{
    return object->state.unk00;
}

s16 func_002B8E00(FieldSequenceState40* object)
{
    return object->state.unk08;
}

s16 func_002B8E10(FieldSequenceState40* object)
{
    return object->state.unk0a;
}

s32 func_002B8E20(void* object)
{
    return 0;
}

s32 func_002B8E30(void* object)
{
    return 0;
}

s32 func_002B8E40(void* object)
{
    return 0;
}

void func_002B8E50(void* object)
{
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002B8E60(const FieldSequenceState40* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_1595D0(object, index)->value.w)
        {
            return 1;
        }
    }
    return 0;
}

void func_002B8EB0(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002B8ED0(const FieldSequenceState40* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_1595D0(object, object->state.unk08 - 1)->value.w - entry_1595D0(object, 0)->value.w;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B8F20);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass1595D0::func_002B8F90(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002B8FE0(const FieldSequenceState40* object, float key)
{
    float first = entry_1595D0(object, 0)->value.w;
    float range = entry_1595D0(object, object->state.unk08 - 1)->value.w - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

void* func_002B9080(FieldSequenceState40* object)
{
    return object->unk04;
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B9090(FieldClass1595D0* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey1595D0*>(track->unk04);
    }
    track->unk04 = 0;
}

extern "C" void func_002B9150(FieldClass159540* track);

FieldClass159540::~FieldClass159540()
{
    func_002B9150(this);
}

/**
 * @brief Release owned keyframe storage and clear the keyframe pointer.
 * @param track Track whose storage is released; external storage is left alone.
 */
extern "C" void func_002B9150(FieldClass159540* track)
{
    if (!track->state.unk13_1)
    {
        delete[] static_cast<FieldTrackKey159540*>(track->unk04);
    }
    track->unk04 = 0;
}

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
extern "C" void func_002B91A0(FieldTrackPool<FieldClass159390>* pool, FieldClass159390* track)
{
    u32 index = ((u32)track - (u32)pool->items) / ((u32)&pool->items[1] - (u32)pool->items);
    pool->used[index >> 6] &= ~((u64)1 << (index & 0x3F));
}

/**
 * @brief Mark a track's pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
extern "C" void func_002B91F0(FieldTrackPool<FieldClass159130>* pool, FieldClass159130* track)
{
    u32 index = ((u32)track - (u32)pool->items) / ((u32)&pool->items[1] - (u32)pool->items);
    pool->used[index >> 6] &= ~((u64)1 << (index & 0x3F));
}

FieldClass159540::FieldClass159540()
{
    state.unk13_2 = false;
    func_002BBA30();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B92B0);

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002B9320(FieldSequenceState40* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey1595D0*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey1595D0[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}


FieldClass1595D0::FieldClass1595D0()
{
    state.unk13_2 = false;
    func_002B8C50();
}

FieldClass159660::FieldClass159660()
{
    state.unk13_2 = false;
    func_002BB620();
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002B94C0(const FieldSequenceState10* object, float key)
{
    float first = entry_1596F0(object, 0)->key;
    float range = entry_1596F0(object, object->state.unk08 - 1)->key - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B9550);

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002B95B0(const FieldSequenceState10* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_1596F0(object, object->state.unk08 - 1)->key - entry_1596F0(object, 0)->key;
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002B9600(const FieldSequenceState10* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_1596F0(object, index)->key)
        {
            return 1;
        }
    }
    return 0;
}

/** @brief Forward a keyframe with a key to slot 0x74. */
extern "C" void func_002B9650(FieldClass1596F0* object, const float* value, float key)
{
    object->func_002B9680(value, key);
}

void func_002B9680(void* object)
{
}

/** @brief Forward an indexed keyframe insertion to slot 0x70. */
extern "C" s32 func_002B9690(FieldClass1596F0* object, s32 index, float key, const float* value)
{
    return object->func_002B96C0(index, key, value);
}

s32 func_002B96C0(void* object)
{
    return 0;
}

/** @brief Forward an indexed keyframe replacement to slot 0x6C. */
extern "C" s32 func_002B96D0(FieldClass1596F0* object, s32 index, float key, const float* value)
{
    return object->func_002B9700(index, key, value);
}

s32 func_002B9700(void* object)
{
    return 0;
}

/** @brief Forward a keyframe with a key to slot 0x68. */
extern "C" s32 func_002B9710(FieldClass1596F0* object, const float* value, float key)
{
    return object->func_002B9740(value, key);
}

s32 func_002B9740(void* object)
{
    return 0;
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002B9750(FieldSequenceState10* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_1596F0(object, count - 1)->key - entry_1596F0(object, 0)->key;
}

FieldClass1596F0::FieldClass1596F0()
{
    state.unk13_2 = false;
    func_002B8860();
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002B9810(FieldClass159780* object, const FieldVec4A* value, float key)
{
    object->func_002B9840(value, key);
}

void func_002B9840(void* object)
{
}

/** @brief Forward an indexed vector insertion to slot 0x70. */
extern "C" s32 func_002B9850(FieldClass159780* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_002B9880(index, key, value);
}

s32 func_002B9880(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector replacement to slot 0x6C. */
extern "C" s32 func_002B9890(FieldClass159780* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_002B98C0(index, key, value);
}

s32 func_002B98C0(void* object)
{
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002B98D0(FieldClass159780* object, const FieldVec4A* value, float key)
{
    return object->func_002B9900(value, key);
}

s32 func_002B9900(void* object)
{
    return 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002B9910(FieldSequenceState20* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey159780*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey159780[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}


FieldClass159780::FieldClass159780()
{
    state.unk13_2 = false;
    func_002B83C0();
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002B9A40(const FieldSequenceState30* object, float key)
{
    float first = entry_159810(object, 0)->key;
    float range = entry_159810(object, object->state.unk08 - 1)->key - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002B9AD0);

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002B9B30(const FieldSequenceState30* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_159810(object, object->state.unk08 - 1)->key - entry_159810(object, 0)->key;
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002B9B80(const FieldSequenceState30* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_159810(object, index)->key)
        {
            return 1;
        }
    }
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002B9BD0(FieldClass159810* object, const FieldVec4A* value, float key)
{
    object->func_002B9C00(value, key);
}

void func_002B9C00(void* object)
{
}

/** @brief Forward an indexed vector insertion to slot 0x70. */
extern "C" s32 func_002B9C10(FieldClass159810* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_002B9C40(index, key, value);
}

s32 func_002B9C40(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector replacement to slot 0x6C. */
extern "C" s32 func_002B9C50(FieldClass159810* object, s32 index, float key, const FieldVec4A* value)
{
    return object->func_002B9C80(index, key, value);
}

s32 func_002B9C80(void* object)
{
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002B9C90(FieldClass159810* object, const FieldVec4A* value, float key)
{
    return object->func_002B9CC0(value, key);
}

s32 func_002B9CC0(void* object)
{
    return 0;
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002B9CD0(FieldSequenceState30* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_159810(object, count - 1)->key - entry_159810(object, 0)->key;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002B9D20(FieldSequenceState30* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey159810*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey159810[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}

FieldTrackKey159810::FieldTrackKey159810()
{
}

FieldClass159810::FieldClass159810()
{
    state.unk13_2 = false;
    func_001E94F0();
}

FieldClass1598A0::FieldClass1598A0()
{
    state.unk13_2 = false;
    func_002BAE90();
}

void FieldClass159090::func_002B9EC0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    func_002B8D30(6);
    unk10 = *value;
    unk20 = *first;
    unk30 = *second;
    unk10.w = key;
}

s32 FieldClass159090::func_002B9F50(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    s32 count;
    s32 i;
    if (unk04 == 0)
    {
        return 0;
    }
    count = state.unk08;
    if (index >= count)
    {
        return 0;
    }
    if (count >= state.unk0a)
    {
        return 0;
    }
    for (i = count; i > index; i--)
    {
        static_cast<FieldTrackKey1595D0*>(unk04)[i] = static_cast<FieldTrackKey1595D0*>(unk04)[i - 1];
    }
    static_cast<FieldTrackKey1595D0*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].first = *first;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].second = *second;
    static_cast<FieldTrackKey1595D0*>(unk04)[index].value.w = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey1595D0*>(unk04)[0].value.w;
    }
    state.unk08++;
    return 1;
}

void FieldClass159420::func_002B9680(const float* value, float key)
{
    func_002B8990(6);
    unk0c = *value;
    unk08 = key;
}

s32 FieldClass159420::func_001DF2E0(s32 index, float* key, float* value, float* first, float* second) const
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    if (key)
    {
        *key = static_cast<const FieldTrackKey1596F0*>(unk04)[index].key;
    }
    if (value)
    {
        const FieldTrackKey1596F0* entries = static_cast<const FieldTrackKey1596F0*>(unk04);
        *value = entries[index].value;
    }
    return 1;
}

s32 FieldClass159420::func_002B96C0(s32 index, float key, const float* value)
{
    s32 count;
    s32 i;
    if (unk04 == 0)
    {
        return 0;
    }
    count = state.unk08;
    if (index >= count)
    {
        return 0;
    }
    if (count >= state.unk0a)
    {
        return 0;
    }
    for (i = count; i > index; i--)
    {
        static_cast<FieldTrackKey1596F0*>(unk04)[i] = static_cast<FieldTrackKey1596F0*>(unk04)[i - 1];
    }
    FieldTrackKey1596F0* entries = static_cast<FieldTrackKey1596F0*>(unk04);
    entries[index].value = *value;
    static_cast<FieldTrackKey1596F0*>(unk04)[index].key = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey1596F0*>(unk04)[0].key;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

s32 FieldClass159420::func_002B9700(s32 index, float key, const float* value)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    FieldTrackKey1596F0* entries = static_cast<FieldTrackKey1596F0*>(unk04);
    entries[index].value = *value;
    static_cast<FieldTrackKey1596F0*>(unk04)[index].key = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey1596F0*>(unk04)[0].key;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    return 1;
}

s32 FieldClass159420::func_002B9740(const float* value, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (state.unk08 >= state.unk0a)
    {
        return 0;
    }
    FieldTrackKey1596F0* entries = static_cast<FieldTrackKey1596F0*>(unk04);
    entries[state.unk08].value = *value;
    static_cast<FieldTrackKey1596F0*>(unk04)[state.unk08].key = key;
    state.span = key - static_cast<FieldTrackKey1596F0*>(unk04)[0].key;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

void FieldClass159270::func_002B9840(const FieldVec4A* value, float key)
{
    func_002B84A0(6);
    unk10 = *value;
    unk10.w = key;
}

s32 FieldClass159270::func_002B9880(s32 index, float key, const FieldVec4A* value)
{
    s32 count;
    s32 i;
    if (unk04 == 0)
    {
        return 0;
    }
    count = state.unk08;
    if (index >= count)
    {
        return 0;
    }
    if (count >= state.unk0a)
    {
        return 0;
    }
    for (i = count; i > index; i--)
    {
        static_cast<FieldTrackKey159780*>(unk04)[i] = static_cast<FieldTrackKey159780*>(unk04)[i - 1];
    }
    static_cast<FieldTrackKey159780*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey159780*>(unk04)[index].value.w = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey159780*>(unk04)[0].value.w;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

void FieldClass1591E0::func_002B9C00(const FieldVec4A* value, float key)
{
    func_002B7FB0(6);
    unk20 = *value;
    unk10 = key;
}

s32 FieldClass1591E0::func_001DF2E0(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    if (key)
    {
        *key = static_cast<const FieldTrackKey159810*>(unk04)[index].key;
    }
    if (value)
    {
        *value = static_cast<const FieldTrackKey159810*>(unk04)[index].value;
    }
    return 1;
}

s32 FieldClass1591E0::func_002B9C40(s32 index, float key, const FieldVec4A* value)
{
    s32 count;
    s32 i;
    if (unk04 == 0)
    {
        return 0;
    }
    count = state.unk08;
    if (index >= count)
    {
        return 0;
    }
    if (count >= state.unk0a)
    {
        return 0;
    }
    for (i = count; i > index; i--)
    {
        static_cast<FieldTrackKey159810*>(unk04)[i] = static_cast<FieldTrackKey159810*>(unk04)[i - 1];
    }
    static_cast<FieldTrackKey159810*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey159810*>(unk04)[index].key = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey159810*>(unk04)[0].key;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

s32 FieldClass1591E0::func_002B9C80(s32 index, float key, const FieldVec4A* value)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey159810*>(unk04)[index].value = *value;
    static_cast<FieldTrackKey159810*>(unk04)[index].key = key;
    if (index == state.unk08 - 1)
    {
        state.span = key - static_cast<FieldTrackKey159810*>(unk04)[0].key;
    }
    state.unk0e = -1;
    state.unk10 = -1;
    return 1;
}

s32 FieldClass1591E0::func_002B9CC0(const FieldVec4A* value, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (state.unk08 >= state.unk0a)
    {
        return 0;
    }
    static_cast<FieldTrackKey159810*>(unk04)[state.unk08].value = *value;
    static_cast<FieldTrackKey159810*>(unk04)[state.unk08].key = key;
    state.span = key - static_cast<FieldTrackKey159810*>(unk04)[0].key;
    state.unk0e = -1;
    state.unk10 = -1;
    state.unk08++;
    return 1;
}

void FieldClass1594B0::func_001DF300()
{
    float zero = 0.0f;
    func_002B9680(&zero, 0.0f);
    func_002B8990(1);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BA850);

void FieldClass159300::func_001DF300()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    func_002B9840(&zero, 0.0f);
    func_002B84A0(1);
}

void func_002BAC40(FieldSequenceState10* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

void FieldClass159660::func_002BACA0(s32 mode)
{
    state.unk12_0_3 = mode;
    state.unk13_0 = state.unk12_0_3 == 4 || state.unk12_4_7 == 4;
}

void func_002BAD00(FieldSequenceState40* object, u8 mode)
{
    object->state.unk12_0_3 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BAD60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BADE0);

void FieldClass159950::func_002BAE60()
{
}

void FieldClass159940::func_002BAE70()
{
}

void FieldClass159930::func_002BAE80()
{
}

void func_002BAE90(FieldSequenceState40* object)
{
    object->unk04 = 0;
    object->state.unk12_0_3 = 1;
    object->state.unk12_4_7 = 1;
    object->state.unk0a = 0;
    object->state.unk08 = 0;
    object->state.unk0c = -1;
    object->state.unk00 = 0;
    object->state.unk0e = -1;
    object->state.unk10 = -1;
    object->state.unk13_0 = 0;
    object->state.unk13_1 = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002BAF20(FieldSequenceState40* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey1598A0*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey1598A0[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002BAFD0(FieldSequenceState40* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_1598A0(object, count - 1)->key - entry_1598A0(object, 0)->key;
}

void func_002BB020(FieldSequenceState40* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002BB080(FieldSequenceState40* object)
{
    return object->state.unk00;
}

s16 func_002BB090(FieldSequenceState40* object)
{
    return object->state.unk08;
}

s16 func_002BB0A0(FieldSequenceState40* object)
{
    return object->state.unk0a;
}

s32 func_002BB0B0(void* object)
{
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002BB0C0(FieldClass1598A0* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_002BB0B0(value, first, second, key);
}

s32 func_002BB0F0(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector replacement to slot 0x6C. */
extern "C" s32 func_002BB100(FieldClass1598A0* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BB0F0(index, key, value, first, second);
}

s32 func_002BB130(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector insertion to slot 0x70. */
extern "C" s32 func_002BB140(FieldClass1598A0* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BB130(index, key, value, first, second);
}

void func_002BB170(void* object)
{
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002BB180(FieldClass1598A0* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_002BB170(value, first, second, key);
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002BB1B0(const FieldSequenceState40* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_1598A0(object, index)->key)
        {
            return 1;
        }
    }
    return 0;
}

void func_002BB200(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002BB220(const FieldSequenceState40* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_1598A0(object, object->state.unk08 - 1)->key - entry_1598A0(object, 0)->key;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BB270);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass1598A0::func_002BB2E0(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002BB330(const FieldSequenceState40* object, float key)
{
    float first = entry_1598A0(object, 0)->key;
    float range = entry_1598A0(object, object->state.unk08 - 1)->key - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

void* func_002BB3D0(FieldSequenceState40* object)
{
    return object->unk04;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BB3E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BB4C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BB620);

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002BB6B0(FieldSequenceState30* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey159660*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey159660[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}

void FieldClass159660::func_002BB760(s32 mode)
{
    state.unk12_4_7 = mode;
    state.unk13_0 = state.unk12_0_3 == 4 || state.unk12_4_7 == 4;
}

s32 func_002BB7C0(FieldSequenceState30* object)
{
    return object->state.unk00;
}

s16 func_002BB7D0(FieldSequenceState30* object)
{
    return object->state.unk08;
}

s16 func_002BB7E0(FieldSequenceState30* object)
{
    return object->state.unk0a;
}

s32 func_002BB7F0(void* object)
{
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002BB800(FieldClass159660* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_002BB7F0(value, first, second, key);
}

s32 func_002BB830(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector replacement to slot 0x6C. */
extern "C" s32 func_002BB840(FieldClass159660* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BB830(index, key, value, first, second);
}

s32 func_002BB870(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector insertion to slot 0x70. */
extern "C" s32 func_002BB880(FieldClass159660* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BB870(index, key, value, first, second);
}

void func_002BB8B0(void* object)
{
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002BB8C0(FieldClass159660* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_002BB8B0(value, first, second, key);
}

void func_002BB8F0(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass159660::func_002BB910(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

void* func_002BB960(FieldSequenceState30* object)
{
    return object->unk04;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002BB970(FieldClass1595D0* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_002B8E20(value, first, second, key);
}

/** @brief Forward an indexed vector set with a key to slot 0x6C. */
extern "C" s32 func_002BB9A0(FieldClass1595D0* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002B8E30(index, key, value, first, second);
}

/** @brief Forward an indexed vector set with a key to slot 0x70. */
extern "C" s32 func_002BB9D0(FieldClass1595D0* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002B8E40(index, key, value, first, second);
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002BBA00(FieldClass1595D0* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_002B8E50(value, first, second, key);
}

void func_002BBA30(FieldSequenceState10* object)
{
    object->unk04 = 0;
    object->state.unk12_0_3 = 1;
    object->state.unk12_4_7 = 1;
    object->state.unk0a = 0;
    object->state.unk08 = 0;
    object->state.unk0c = -1;
    object->state.unk00 = 0;
    object->state.unk0e = -1;
    object->state.unk10 = -1;
    object->state.unk13_0 = 0;
    object->state.unk13_1 = 0;
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param object Sequence receiver.
 * @param count Requested keyframe count.
 */
extern "C" void func_002BBAC0(FieldSequenceState10* object, s32 count)
{
    object->state.unk13_1 = 0;
    delete[] static_cast<FieldTrackKey159540*>(object->unk04);
    object->unk04 = new (0) FieldTrackKey159540[count];
    object->state.unk0a = count;
    if (!object->unk04)
    {
        object->state.unk0a = 0;
    }
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002BBB60(FieldSequenceState10* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = key_159540(object, count - 1) - key_159540(object, 0);
}

void func_002BBBC0(FieldSequenceState10* object, u8 mode)
{
    object->state.unk12_4_7 = mode;
    object->state.unk13_0 = object->state.unk12_0_3 == 4 || object->state.unk12_4_7 == 4;
}

s32 func_002BBC20(FieldSequenceState10* object)
{
    return object->state.unk00;
}

s16 func_002BBC30(FieldSequenceState10* object)
{
    return object->state.unk08;
}

s16 func_002BBC40(FieldSequenceState10* object)
{
    return object->state.unk0a;
}

s32 func_002BBC50(void* object)
{
    return 0;
}

/** @brief Forward a vector set with a key to slot 0x68. */
extern "C" s32 func_002BBC60(FieldClass159540* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return object->func_002BBC50(value, first, second, key);
}

s32 func_002BBC90(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector replacement to slot 0x6C. */
extern "C" s32 func_002BBCA0(FieldClass159540* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BBC90(index, key, value, first, second);
}

s32 func_002BBCD0(void* object)
{
    return 0;
}

/** @brief Forward an indexed vector insertion to slot 0x70. */
extern "C" s32 func_002BBCE0(FieldClass159540* object, s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return object->func_002BBCD0(index, key, value, first, second);
}

void func_002BBD10(void* object)
{
}

/** @brief Forward a vector set with a key to slot 0x74. */
extern "C" void func_002BBD20(FieldClass159540* object, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    object->func_002BBD10(value, first, second, key);
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002BBD50(const FieldSequenceState10* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == key_159540(object, index))
        {
            return 1;
        }
    }
    return 0;
}

void func_002BBDB0(FieldResetWords00* object)
{
    object->words[0] = 0;
    object->words[1] = 0;
    object->words[2] = 0;
    object->words[3] = 0;
}

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002BBDD0(const FieldSequenceState10* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return key_159540(object, object->state.unk08 - 1) - key_159540(object, 0);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BBE30);

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated vector.
 */
void FieldClass159540::func_002BBF20(float key, FieldVec4B* output) const
{
    *output = func_slot80(key);
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002BBF70(const FieldSequenceState10* object, float key)
{
    float first = key_159540(object, 0);
    float range = key_159540(object, object->state.unk08 - 1) - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

void* func_002BC010(FieldSequenceState10* object)
{
    return object->unk04;
}

/**
 * @brief Wrap a key into the stored key range.
 * @param object Sequence receiver.
 * @param key Key to wrap.
 * @return The key less a whole number of key spans.
 */
extern "C" float func_002BC020(const FieldSequenceState30* object, float key)
{
    float first = entry_159660(object, 0)->key;
    float range = entry_159660(object, object->state.unk08 - 1)->key - first;
    float position = (key - first) / range;
    s32 spans;
    if (position < 0.0f)
    {
        position -= 1.0f;
    }
    spans = (s32)position;
    if (spans != 0)
    {
        return key - spans * range;
    }
    return key;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC0B0);

/**
 * @brief Return the span between the first and last keys.
 * @param object Sequence receiver.
 * @return Last key minus first key, or zero with fewer than two entries.
 */
extern "C" float func_002BC110(const FieldSequenceState30* object)
{
    if (object->state.unk08 < 2)
    {
        return 0.0f;
    }
    return entry_159660(object, object->state.unk08 - 1)->key - entry_159660(object, 0)->key;
}

/**
 * @brief Test whether the track contains the supplied key.
 * @param object Sequence receiver.
 * @param key Key to find.
 * @return One when the key exists, otherwise zero.
 */
extern "C" s32 func_002BC160(const FieldSequenceState30* object, float key)
{
    s16 count = object->state.unk08;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == entry_159660(object, index)->key)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Bind an external keyframe array.
 * @param object Sequence receiver.
 * @param count Keyframe count.
 * @param entries External keyframe storage.
 */
extern "C" void func_002BC1B0(FieldSequenceState30* object, s32 count, void* entries)
{
    object->state.unk13_1 = 1;
    object->unk04 = entries;
    object->state.unk0a = count;
    object->state.unk08 = count;
    object->state.span = entry_159660(object, count - 1)->key - entry_159660(object, 0)->key;
}

FieldTrackKey159660::FieldTrackKey159660()
{
}

FieldTrackKey1598A0::FieldTrackKey1598A0()
{
}

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 14.
 */
s32 func_002BC220(FieldListObject* object)
{
    return 14;
}

void func_002BC230(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC240);

void func_002BC260(void* object)
{
}

void func_002BC270(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC280);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC370);

FieldClass159A70::~FieldClass159A70()
{
    if (unk08 != 0)
    {
        delete unk08;
        unk08 = 0;
    }
}

FieldClass159A70::FieldClass159A70()
{
    unk00 = 0;
    unk1c = 0;
    unk20 = 0;
    unk24 = 0;
    unk28 = 0;
    unk18 = 0;
    unk16 = 0;
    unk14 = 0;
    unk04 = 0;
    unk08 = 0;
    unk0c = 96.0f;
    unk10 = 5.0f;
}

void FieldClass159A70::func_002BC4F0(u32 first, u32 depth, float value)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002AE9E0", func_002BC500);
