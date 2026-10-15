#include "include_asm.h"
#include "overlays/lib/text_0046AE20.h"

extern void func_0047A130(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8);
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_0049B820.h"

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

void* func_0046C080(void* value)
{
    return value;
}

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

/** Store the low halfword at receiver offset 0x6C. */
void func_00472100(void* object, u32 value)
{
    HalfwordSetterOwnertext_0046AE20* receiver = object;
    receiver->unk6c = value;
}

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

void func_004790D0(unsigned __int128* first, unsigned __int128* second, const unsigned __int128* source)
{
    unsigned __int128 value = *source;
    *second = value;
    *first = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004790E0);

void* func_00479100(void* object)
{
    return (u8*)object + 0x830;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479110);

void func_00479160(void* object, u8 value)
{
    LibFlagState59C* receiver = (LibFlagState59C*)object;
    receiver->unk59c = value;
    receiver->unk59d_0 = 1;
}

typedef struct LibByte790Counter
{
    u8 unk00[0x790];
    u8 unk790;
} LibByte790Counter;

/** Increment the byte at receiver offset 0x790. */
void func_00479180(void* object)
{
    LibByte790Counter* receiver = (LibByte790Counter*)object;
    receiver->unk790 = (u8)(receiver->unk790 + 1);
}

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

s32 func_00479700(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004797E0);

s32 func_00479840(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004798D0);

s32 func_00479950(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479960);

s32 func_004799E0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004799F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479A70);

s32 func_00479AF0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479B80);

s32 func_00479C00(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479C10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479C90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479CB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479D50);

s32 func_00479DD0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479DE0);

s32 func_00479E60(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479E70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479EF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479F50);

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

void func_0047A010(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8)
{
    u8* state = (u8*)cell;
    state[0x130] = 0;
    state[0x132] = 0;
    state[0x131] = 0;
    state[0x133] = 0;
    func_0047A130(object, cell, row, index, extra4, extra5, extra6, extra7, extra8);
}

extern void func_0047A540(void* object, void* state, void* row);
