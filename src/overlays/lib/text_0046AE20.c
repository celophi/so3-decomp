#include "include_asm.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_0049B820.h"

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
    u8 unk04[8];
    s16 child_count;
    u8 state;
    u8 kind;
    u8 unk10[0xC];
    u32 flags;
    u8 unk20[0x64];
    s32 name_checksum;
};

/** Runtime handle and source metadata for one resource entry. */
typedef struct LibManagedEntry
{
    u8 unk00;
    u8 unk01[3];
    u32 unk04;
    void* handle;
    LibEntryMetadata* metadata;
} LibManagedEntry;

/** Resource flags and signed entry count used by table searches. */
typedef struct LibEntryTableHeader
{
    u32 flags;
    s32 count;
} LibEntryTableHeader;

/** Partial view of the manager's runtime table and resource header. */
struct LibEntryManager
{
    u8 unk00[0x18];
    LibManagedEntry* entries;
    u32 unk1c;
    LibEntryTableHeader* header;
    u8 unk24[0x70];
    s32 cached_entry_index;
};

/** Partial inherited transform state shared by the setter's callers. */
typedef struct LibTransformByteState
{
    u8 unk00[0x50];
    u8 transform_dirty;
} LibTransformByteState;

enum
{
    LIB_ENTRY_HAS_NAMES = 1,
    LIB_ENTRY_KIND_LIGHT = 2,
    LIB_ENTRY_KIND_CAMERA = 3,
    LIB_ENTRY_NAME_COMPARE_LENGTH = 16
};

/** Partial receiver with its halfword flags at 0x6A. */
typedef struct LibObjectFlags6A
{
    u8 unk00[0x6A];
    u16 flags;
} LibObjectFlags6A;


INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046AE20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B0D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B3F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B480);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B4A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B620);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B7D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B7E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B7F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B810);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B820);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004D0090__16FieldClass175290Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046BA00);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046C080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046C090);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046C180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046C320);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046C390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046C3F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046C540);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046D780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046D7F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046D860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046D8D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046D930);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046D9A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DA00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DA70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DAD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DB40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DBA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DC10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DC70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DCE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DD50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DDB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DE20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DE90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046F910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004713C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004713F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00471410);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00471440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00471480);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004720F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472100);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004721B0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472220);

/**
 * @brief Add bits to the object's flags.
 * @param object Receiver.
 * @param flags Flag bits to add.
 */
void lib_object_add_flags(void* object, u16 flags)
{
    LibObjectFlags6A* state = object;
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
    u8* data = (u8*)metadata + metadata->data_offset;
    if (manager->header->flags & LIB_ENTRY_HAS_NAMES)
    {
        data += 0x10;
    }
    return data;
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004728A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472A00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472B40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472BB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472C90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472DA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472FD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004731A0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473530);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473D50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473DC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473E20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00474010);

/** Return the word at receiver offset 0x8. */
u32 func_00478F70(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk08;
}

/** Return the word at receiver offset 0xC. */
u32 func_00478F80(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk0c;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00478F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00478FB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00478FE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479010);

/** @brief Copy one aligned 16-byte value. @param output Destination value. @param input Source value. */
void func_00479090(void* output, const void* input)
{
    *(unsigned __int128*)output = *(const unsigned __int128*)input;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004790A0);

/**
 * @brief Set the inherited transform dirty flag.
 * @param object Transform receiver.
 * @param value Dirty flag to store.
 */
void lib_transform_set_dirty(void* object, u8 value)
{
    ((LibTransformByteState*)object)->transform_dirty = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004790D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004790E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479100);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479160);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479190);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004791F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004792A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004793A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479490);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004795D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004796A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004797E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004798D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479950);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479960);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004799E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004799F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479A70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479AF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479B80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479C00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479C10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479C90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479CB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479D50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479DE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479E60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479E70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479EF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479FB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479FC0);

/** Store the word at receiver offset 0xB8. */
void func_00479FD0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unkb8 = value;
}

/** Return the word at receiver offset 0xB8. */
u32 func_00479FE0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unkb8;
}

/** Store the word at receiver offset 0xBC. */
void func_00479FF0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unkbc = value;
}

/** Return the word at receiver offset 0xBC. */
u32 func_0047A000(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unkbc;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A040);

/** Store the word at receiver offset 0xB0. */
void func_0047A070(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unkb0 = value;
}

/** Return the word at receiver offset 0xB0. */
u32 func_0047A080(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unkb0;
}

/** Store the word at receiver offset 0xB4. */
void func_0047A090(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unkb4 = value;
}

/** Return the word at receiver offset 0xB4. */
u32 func_0047A0A0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unkb4;
}

/** Store the word at receiver offset 0xB0. */
void func_0047A0B0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unkb0 = value;
}

/** Return the word at receiver offset 0xB0. */
u32 func_0047A0C0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unkb0;
}

/** Store the word at receiver offset 0xB4. */
void func_0047A0D0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unkb4 = value;
}

/** Return the word at receiver offset 0xB4. */
u32 func_0047A0E0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unkb4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A0F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A100);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A120);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A540);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A640(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A650(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047A660(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047A670(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047A680(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A690(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047A6A0(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047A6B0(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A6C0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047A6D0(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047A6E0(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047A6F0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047A700(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047A710(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047A720(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047A730(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047A740(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047A750(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A760(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047A770(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A780(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk40 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A790);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A7D0);

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A800(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk38 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A810);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047ACA0);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADA0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADB0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047ADC0(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047ADD0(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047ADE0(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADF0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047AE00(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047AE10(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk56;
}
