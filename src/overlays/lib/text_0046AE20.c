#include "include_asm.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/text_004CD3A0.h"

/** Partial metadata used to filter and name resource entries. */
typedef struct LibEntryMetadata
{
    u16 unk00;
    u16 name_offset;
    u8 unk04[10];
    u8 state;
    u8 kind;
} LibEntryMetadata;

/** Runtime handle and source metadata for one resource entry. */
typedef struct LibManagedEntry
{
    u32 unk00;
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
};

enum
{
    LIB_ENTRY_ALLOW_NAMED_LOOKUP = 1,
    LIB_ENTRY_KIND_CAMERA = 3,
    LIB_ENTRY_NAME_COMPARE_LENGTH = 16
};

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046BA30);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004723A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004723D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004724A0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473250);

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
    if (!(manager->header->flags & LIB_ENTRY_ALLOW_NAMED_LOOKUP) && !any_name)
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
            if (any_name || lib_compare_bounded_strings(name, (const char*)metadata + metadata->name_offset,
                                                        LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
            {
                return manager->entries[index].handle;
            }
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004737E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473D50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473DC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00473E20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00474010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00478F70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00478F80);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004790C0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479FD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479FE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00479FF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A090);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A0A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A0B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A0C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A0D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A0E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A0F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A100);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A120);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A540);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A690);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A6A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A6B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A6C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A6D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A6E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A6F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A740);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A750);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A770);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A790);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A7D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A810);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047ACA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047ADA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047ADB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047ADC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047ADD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047ADE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047ADF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047AE00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047AE10);
