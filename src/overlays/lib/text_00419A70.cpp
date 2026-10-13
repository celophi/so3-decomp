#include "include_asm.h"
#include "overlays/lib/text_00419A70.h"

/** Partial list indicator rectangle, drawing storage, flags, and scalar pair. */
struct LibListIndicatorState
{
    u8 unk00[0x18];
    float x;
    float y;
    float width;
    float height;
    u8 unk28[0xC];
    u32 unk34;
    u8 unk38;
    u8 unk39;
    u8 unk3a[6];
    LibStorageBlock0C storage;
    u8 unk4c[4];
    float first;
    float second;
};

/** Partial marker rectangle, drawing storage, flags, and packed colors. */
struct LibMarkerState
{
    u8 unk00[0x18];
    float x;
    float y;
    float width;
    float height;
    u8 unk28[0x11];
    u8 active;
    u8 unk3a[2];
    u8 redraw;
    u8 unk3d[3];
    LibStorageBlock0C storage;
    u8 unk4c[4];
    u32 color;
    u32 dark_color;
};

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00419A70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00419BE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00419C70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00419DE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A0F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A1A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A2F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A540);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A550);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A560);

/**
 * @brief Initialize the list indicator rectangle, scalar pair, and drawing storage.
 * @param object List indicator widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param height Rectangle height.
 * @param first First scalar value.
 * @param second Second scalar value.
 * @return One on success, or zero when storage initialization fails.
 */
s32 lib_list_indicator_init(ItemCreationClass1725D0* object, float x, float y, float height, float first, float second)
{
    LibListIndicatorState* state = reinterpret_cast<LibListIndicatorState*>(object);
    state->x = x;
    state->y = y;
    state->width = 14.0f;
    state->height = height;
    state->first = first;
    state->second = second;
    if (!lib_allocate_drawing_storage(&state->storage, 38))
    {
        return 0;
    }
    state->unk34 = 6;
    state->unk39 = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A9A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041ACF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041AD10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041AD80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041AD90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041ADC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041ADE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041AE30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041AE50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041AE80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041CF80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D0A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D1C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D230);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E880);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E8C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E8E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041EF10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F190);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F1A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F1D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F1F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F230);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F2B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F300);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F320);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F350);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004209C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420A30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420B50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420D00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420D10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420D20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00420F20);

/**
 * @brief Allocate marker drawing storage and initialize its rectangle and colors.
 * @param object Marker widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on success, or zero if storage cannot be allocated.
 */
s32 lib_marker_init_rectangle(ItemCreationClass172870* object, float x, float y, float width, float height)
{
    LibMarkerState* state = reinterpret_cast<LibMarkerState*>(object);
    u32 shade;
    float intensity;
    state->x = x;
    state->y = y;
    state->width = width;
    state->height = height;
    if (!lib_allocate_drawing_storage(&state->storage, 12))
    {
        return 0;
    }
    intensity = 0.9f;
    shade = (u32)(256.0f * intensity);
    state->color = (shade << 16) | (shade << 8) | shade;
    state->redraw = 1;
    state->dark_color = 0x020202;
    state->active = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421450);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004214C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004214D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421D80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00422050);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004220E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00422130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004221A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00422850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00422F70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00423930);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00423970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00423990);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004239C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004245B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424610);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424760);

/** @brief Destroy the list receiver and its embedded sentinel. */
LibClass178A70::~LibClass178A70()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004249C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004249D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424A50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424A60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424A70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424BE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424CE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424F40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425280);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004253A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425490);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004257A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425970);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425B40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425C90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425E10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004260C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004261E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00426370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004264F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00426650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00426C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004284A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004284E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004284F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004288C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004289B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428A50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428AF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428B40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428B90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428C80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428D20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428DC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428E40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428F20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004290A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004291B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004292C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004293D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429480);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004294F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004295B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004295C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004295D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004295E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004295F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429620);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429650);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004296B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004296C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429790);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004297F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004299C0);
