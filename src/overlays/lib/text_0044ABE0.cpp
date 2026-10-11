#include "include_asm.h"
#include "overlays/lib/text_0044ABE0.h"
#include "main/resident_data.h"

/** Partial indexed-resource fields at CC and D0. */
typedef struct LibIndexedResourceState
{
    u8 pad00[0xCC];
    s32 current;
    s32 selected;
} LibIndexedResourceState;
extern "C" s32 func_00461860(LibStorageBlock0C* storage, s32 count);
extern "C" s32 func_00464EF0(FieldRuntime* runtime, s32 index);
extern "C" s32 func_00467800(ItemCreationClass174C40* object, s32 resource, s32 first, s32 second, s32 third, s32 fourth, float x, float y);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044ABE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044ACF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044AD80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044AE70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044AFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B100);

/**
 * @brief Set transform codes and the third coordinate while preserving x and y.
 * @param code Transform code.
 * @param first First byte value.
 * @param z Third coordinate.
 * @param second Word value.
 * @param third Second byte value.
 */
void LibClass174610::set_codes_and_z(s32 code, u32 first, float z, u32 second, u32 third)
{
    if (code != 0)
    {
        z = (float)(code * 16);
        first = 9;
        second = 0xFFFFFE - code * 16;
    }
    unka0 = code;
    unka8 = first;
    unka4 = second;
    if (code >= 13 && code < 21)
    {
        third = 255 - (code - 13);
    }
    unka9 = third;
    LibClass171EC0::func_003EF790(unk20.components[0], unk20.components[1], z);
    unkae = 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B190);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B1C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B240);

/** @brief Initialize transform flags and drawing modes after the base receivers. */
LibClass174610::LibClass174610()
{
    unk6a |= 0x400;
    unk94 = 0;
    unkaf = 0;
    unkae = 1;
    unkad = 1;
    unkac = 1;
    unkab = 1;
    unkaa = 2;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B350);

/**
 * @brief Initialize a widget that restores the runtime clipping bounds.
 * @param object Clipping widget.
 * @param code Retained initialization argument; this routine does not use it.
 * @return True when the six-entry drawing storage was allocated.
 */
extern "C" bool lib_scissor_init_reset(ItemCreationClass1746A0* object, s32 code)
{
    object->unk50 = 1;
    object->unk3c = 1;
    bool success;
    if (!func_00461860(&object->unk40, 6))
    {
        success = false;
    }
    else
    {
        object->unk39 = 1;
        success = true;
    }
    return success;
}

/**
 * @brief Initialize a widget that sets a clipping rectangle.
 * @param object Clipping widget.
 * @param x Rectangle's horizontal position.
 * @param y Rectangle's vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return True when the six-entry drawing storage was allocated.
 */
extern "C" bool lib_scissor_init_rectangle(ItemCreationClass1746A0* object, float x, float y, float width, float height)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;
    object->unk18.unk08 = width;
    object->unk18.unk0c = height;
    object->unk50 = 0;
    object->unk3c = 1;
    bool success;
    if (!func_00461860(&object->unk40, 6))
    {
        success = false;
    }
    else
    {
        object->unk39 = 1;
        success = true;
    }
    return success;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B5E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B6A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044B9E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044BCC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044BDF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044BEE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044BF50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044BF60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044C050);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044C060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044C070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044C080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044C0A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044C0F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044C110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044C140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044CE10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044CF30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D090);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D0B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D0C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D0D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D100);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D150);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D1D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044D9C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E430);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E4D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E560);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044E5F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044ED10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044ED80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044EE40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044EE90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044FC90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044FD30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044FDA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044FF80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0044FFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004517B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004519F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451A60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451AD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451B20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451B60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451B90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451C00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451E20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00451E30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004526A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452CD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452DC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452F00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00452FA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453080);

/**
 * @brief Select the indexed resource and initialize its drawing position.
 * @param object Resource widget.
 * @param index Resource index.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return Initialization status.
 */
extern "C" s32 lib_indexed_resource_init(ItemCreationClass174C40* object, s32 index, float x, float y)
{
    LibIndexedResourceState* state = (LibIndexedResourceState*)object;
    state->selected = index;
    state->current = index;
    return func_00467800(object, func_00464EF0(D_001B657C, state->current) + 0x22, 0, 0, 0, 0, x, y);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453150);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004535B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453EC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453F30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00453F70);

/**
 * @brief Initialize resource pointers, drawing scales, colors, and descriptor defaults.
 * @param state State to initialize.
 */
extern "C" void lib_draw_state_init(LibDrawState64* state)
{
    state->unk04 = 0;
    state->unk00 = 0;
    state->unk08 = 0;
    state->unk18 = state->unk1c = 0.0f;
    state->unk20 = state->unk24 = 0.0f;
    state->unk28 = state->unk2c = 0.0f;
    state->unk30 = state->unk34 = 1.0f;
    state->unk38 = state->unk3c = 0.0f;
    state->unk40 = 0.0f;
    state->unk44 = state->unk48 = state->unk4c = state->unk50 = 128.0f;
    state->unk5e = -1;
    state->unk5f = 0;
    state->unk60 = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004540D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004540E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454300);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004545C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004546D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454740);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004547B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004547C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004549F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454A50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454CB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454D40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454DC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454E30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00454E90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00455040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004550F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00455150);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00455450);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00455AD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00455BD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00455DF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00455EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004560A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456190);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456300);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456690);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004568A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004568E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456950);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004569C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004569D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456A90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456AF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456B90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456CF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456D60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456E60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456F10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00456FE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004570C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457190);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457470);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004577A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457980);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00457B20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00458110);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00458700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004587C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004588E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_004595C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00459990);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00459CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_00459FB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0045A2C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0045A5D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0045A770);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0045ABA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0044ABE0", func_0045ABB0);
