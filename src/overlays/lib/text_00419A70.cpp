#include "include_asm.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"

extern "C" void func_004D00B0(void* object);

typedef struct WordSetterOwnertext_00419A70
{
    u8 unk00[0x70];
    u32 unk70;
} WordSetterOwnertext_00419A70;



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

/** Partial receiver view with an observed byte at offset 0x60. */
typedef struct LibReceiverByte60
{
    u8 unk00[0x60];
    u8 unk60;
} LibReceiverByte60;

/** Partial receiver with two pointer fields at offsets 0x14 and 0x18. */
typedef struct LibReceiverPointerPair14
{
    u8 unk00[0x14];
    void* unk14;
    void* unk18;
} LibReceiverPointerPair14;

typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x22];
    PackedModePair at22;
} PackedModesOwner;

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00419A70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00419BE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00419C70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00419DE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A0F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A130);

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_0041A170(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A1A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041A2F0);

void func_0041A530(void* object)
{
}

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

void func_0041AD80(void* object)
{
    ((LibReceiverByte60*)object)->unk60 = 7;
}

/** Build a four-word stack value and return its address. */
void* func_0041AD90(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

/** @brief Clear the intrusive owner and call the transform release hook. */
extern "C" void func_0041ADC0(LibClass178A90* object)
{
    object->owner = 0;
    object->LibClass178A90::func_003EF740();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041ADE0);

/** Forward the receiver to func_004D00B0. */
void func_0041AE30(void* object)
{
    func_004D00B0(object);
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_0041AE50(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041AE80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041CF80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D0A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D1C0);

/** Forward the receiver to func_004D00B0. */
void func_0041D210(void* object)
{
    func_004D00B0(object);
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_0041D230(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041D260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E760);

void func_0041E880(u8* object)
{
    object[0x64] = 1;
    *(volatile u32*)0x10009020 = *(u32*)(object + 0x9C);
    *(volatile u32*)0x10009010 = *(u32*)(object + 0xA0);
    *(volatile u32*)0x1000E010 = 2;
    *(volatile u32*)0x10009000 = 0x101;
}

/** Forward the receiver to func_004D00B0. */
void func_0041E8C0(void* object)
{
    func_004D00B0(object);
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_0041E8E0(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041E910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041EF10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F030);

void func_0041F130(void* object)
{
    ((LibReceiverByte60*)object)->unk60 = 7;
}

/** Build a four-word stack value and return its address. */
void* func_0041F140(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

/** @brief Clear the intrusive owner and call the transform release hook. */
extern "C" void func_0041F170(LibClass178A90* object)
{
    object->owner = 0;
    object->LibClass178A90::func_003EF740();
}

void func_0041F190(void* object)
{
    ((LibReceiverByte60*)object)->unk60 = 7;
}

/** Build a four-word stack value and return its address. */
void* func_0041F1A0(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

/** @brief Clear the intrusive owner and call the transform release hook. */
extern "C" void func_0041F1D0(LibClass178A90* object)
{
    object->owner = 0;
    object->LibClass178A90::func_003EF740();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F1F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F230);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F240);

void func_0041F250(void* object)
{
    ((LibReceiverByte60*)object)->unk60 = 7;
}

/** Build a four-word stack value and return its address. */
void* func_0041F260(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

/** @brief Clear the intrusive owner and call the transform release hook. */
extern "C" void func_0041F290(LibClass178A90* object)
{
    object->owner = 0;
    object->LibClass178A90::func_003EF740();
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_0041F2B0);

/** Forward the receiver to func_004D00B0. */
void func_0041F300(void* object)
{
    func_004D00B0(object);
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_0041F320(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

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

s32 func_00421240(void* object)
{
    return 16;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00421450);

void func_004214C0(void* object, void* first, void* second)
{
    LibReceiverPointerPair14* state = (LibReceiverPointerPair14*)object;
    state->unk14 = first;
    state->unk18 = second;
}

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

void func_00423930(u8* object)
{
    object[0x64] = 1;
    *(volatile u32*)0x10009020 = *(u32*)(object + 0x234);
    *(volatile u32*)0x10009010 = *(u32*)(object + 0x238);
    *(volatile u32*)0x1000E010 = 2;
    *(volatile u32*)0x10009000 = 0x101;
}

/** Forward the receiver to func_004D00B0. */
void func_00423970(void* object)
{
    func_004D00B0(object);
}

/** Queue the DMA submission embedded at offset 0x210 when present. */
s32 func_00423990(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x210);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

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

s32 func_004249C0(void* object)
{
    return 398;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004249D0);

s32 func_00424A50(void* object)
{
    return 230;
}

void func_00424A60(void* object)
{
    ((LibReceiverByte60*)object)->unk60 = 9;
}

/** Build a four-word stack value and return its address. */
void* func_00424A70(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AC0);

s32 func_00424AD0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424AE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424BE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424CE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00424F40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00425250);

void func_00425280(void* object)
{
}

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

struct SmallConditionalInput04
{
    u8 unk00[4];
    float unk04;
};

extern "C" s32 func_004284A0(void* object, const void* value, float* zero_output, float* small_output)
{
    const SmallConditionalInput04* state = (const SmallConditionalInput04*)value;
    if (!(state->unk04 <= 0.0f))
    {
        *zero_output = 0.0f;
        *small_output = 0.05f;
        return 1;
    }
    return 0;
}

s32 func_004284E0(void* object)
{
    return 0;
}

s32 func_004284F0(void* object)
{
    return 0;
}

void func_00428500(void* object)
{
}

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

s32 func_00428DC0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428DD0);

s32 func_00428E40(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428F20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00428F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004290A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004291B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004292C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004293D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429480);

s32 func_004294F0(void* object)
{
    return 5;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429500);

/** Store the word at receiver offset 0x70. */
void func_004295B0(void* object, u32 value)
{
    WordSetterOwnertext_00419A70* receiver = static_cast<WordSetterOwnertext_00419A70*>(object);
    receiver->unk70 = value;
}

void func_004295C0(void* object)
{
}

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

/** Set the low packed mode at 0x22 and record whether either mode equals four. */
void func_004297F0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.lowMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

void func_00429850(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_00429860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_00419A70", func_004299C0);
