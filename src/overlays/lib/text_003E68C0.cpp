#include "include_asm.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"

extern "C" LibVector4 D_50CD30;
extern "C" void func_0011F770(void* owner, void* object);
extern "C" void func_004D00B0(LibClass178A90* object);

struct LibStateByteB4View
{
    u8 pad00[0x60];
    u8 state60;
    u8 pad61[0x53];
    u8 stateB4;
};

struct LibWordPairView
{
    u32 unk00;
    u32 unk04;
};

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EEB50);

/** @brief Report the fixed kind of this intrusive object. @return Always 3. */
s32 LibClass171EA0::func_003EEBC0()
{
    return 3;
}

/** @brief Leave the base intrusive object unchanged. */
void LibClass171EA0::func_003EEBD0()
{
}

/** @brief Leave the base intrusive object unchanged. */
void LibClass171EA0::func_003EEBE0()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EEBF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EECD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EED40);

extern "C" void func_003EEDE0(void* object)
{
    LibStateByteB4View* state = (LibStateByteB4View*)object;
    state->state60 = state->stateB4;
}

/** Build a four-word stack value and return its address. */
void* func_003EEDF0(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

/** @brief Return the default output-handler result. @param output Unused output object. @return Zero. */
s32 LibClass178A90::func_003EEE20(void* output)
{
    return 0;
}

/** @brief Test whether the supplied value is negative. @param value Value to test. @param mode Unused mode. @return One if negative, otherwise zero. */
s32 LibClass178A90::func_003EEE30(float value, float mode)
{
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
}

/** @brief Return no replacement transform receiver. @return Null. */
LibClass178A90* LibClass178A90::func_003EEE50()
{
    return 0;
}

/** @brief Leave the base transform receiver unchanged. */
void LibClass178A90::func_003EEE60()
{
}

extern "C" void func_003EEE70(LibClass171EF0* object, const LibVector4* value)
{
    object->transform_dirty = 1;
    object->unk20.packed = value->packed;
}

extern "C" void func_003EEE90(LibClass171EF0* object, const LibVector4* value)
{
    object->transform_dirty = 1;
    object->unk20.packed = value->packed;
}

extern "C" void func_003EEEB0(LibClass171EF0* object, float x, float y, float z)
{
    object->transform_dirty = 1;
    object->unk20.components[0] = x;
    object->unk20.components[1] = y;
    object->unk20.components[2] = z;
    object->unk20.components[3] = 1.0f;
}

/** @brief Set all four components of the primary transform vector and mark it dirty. @param x First component. @param y Second component. @param z Third component. @param w Fourth component. */
void LibClass171EF0::func_003EEED0(float x, float y, float z, float w)
{
    transform_dirty = 1;
    unk30.components[0] = x;
    unk30.components[1] = y;
    unk30.components[2] = z;
    unk30.components[3] = w;
}

/** @brief Copy the primary transform vector and mark it dirty. @param value Source vector. */
void LibClass171EF0::func_003EEEF0(const LibVector4* value)
{
    transform_dirty = 1;
    unk30.packed = value->packed;
}

/** @brief Copy the primary transform vector and mark it dirty. @param value Source vector. */
void LibClass171EF0::func_003EEF10(const LibVector4* value)
{
    transform_dirty = 1;
    unk30.packed = value->packed;
}

/** @brief Copy the primary transform vector and mark it dirty. @param object Transform to update. @param value Source vector. */
extern "C" void func_003EEF30(LibClass171EF0* object, const LibVector4* value)
{
    object->transform_dirty = 1;
    func_004CE4C0(object->unk30.components, value->components);
}

/** @brief Copy the primary transform vector and mark it dirty. @param object Transform to update. @param value Source vector. */
extern "C" void func_003EEF60(LibClass171EF0* object, const LibVector4* value)
{
    object->transform_dirty = 1;
    func_004CE4C0(object->unk30.components, value->components);
}

/** @brief Set the primary transform vector's xyz components, set w to one, and mark it dirty. @param object Transform to update. @param x First component. @param y Second component. @param z Third component. */
extern "C" void func_003EEF90(LibClass171EF0* object, float x, float y, float z)
{
    object->transform_dirty = 1;
    LibVector4 value;
    value.components[0] = x;
    value.components[1] = y;
    value.components[2] = z;
    value.components[3] = 1.0f;
    func_004CE4C0(object->unk30.components, value.components);
}

/** @brief Copy the secondary transform vector and mark it dirty. @param value Source vector. */
void LibClass171EF0::func_003EEFD0(const LibVector4* value)
{
    transform_dirty = 1;
    unk40.packed = value->packed;
}

/** @brief Copy the secondary transform vector and mark it dirty. @param value Source vector. */
void LibClass171EF0::func_003EEFF0(const LibVector4* value)
{
    transform_dirty = 1;
    unk40.packed = value->packed;
}

/** @brief Set the secondary transform vector's xyz components and mark it dirty. @param x First component. @param y Second component. @param z Third component. */
void LibClass171EF0::func_003EF010(float x, float y, float z)
{
    transform_dirty = 1;
    unk40.components[0] = x;
    unk40.components[1] = y;
    unk40.components[2] = z;
}

void func_003EF030(u8* object)
{
    object[0x64] = 1;
    *(volatile u32*)0x10009020 = *(u32*)(object + 0x9C);
    *(volatile u32*)0x10009010 = *(u32*)(object + 0xA0);
    *(volatile u32*)0x1000E010 = 2;
    *(volatile u32*)0x10009000 = 0x101;
}

/** @brief Forward the transform receiver to its state-update handler. @param object Transform owner. */
extern "C" void func_003EF070(LibClass178A90* object)
{
    func_004D00B0(object);
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_003EF090(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF0C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF320);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF490);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF740__14LibClass171EA0Fv);

/** @brief Store the position components and set the homogeneous component to one. */
void LibClass171EC0::func_003EF790(float x, float y, float z)
{
    unk20.components[0] = x;
    unk20.components[1] = y;
    unk20.components[2] = z;
    unk20.components[3] = 1.0f;
}

extern "C" void func_003EF770(LibClass171EC0* object, const LibVector4* value)
{
    object->unk20.packed = value->packed;
}

extern "C" void func_003EF780(LibClass171EC0* object, const LibVector4* value)
{
    object->unk20.packed = value->packed;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF7B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF8A0);

/** @brief Return the fixed value 9. @param object Unused receiver. @return Always 9. */
extern "C" s32 func_003EF900(void* object)
{
    return 9;
}

/** @brief Store state value 9 in the transform's byte at offset 0x60. @param object Transform owner. */
extern "C" void func_003EF910(LibClass178A90* object)
{
    object->unk60 = 9;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF920);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF960);

extern "C" void func_003EFA90(void* object)
{
}

/** @brief Return the shared fallback transform vector. @return Address of D_50CD30. */
const LibVector4* LibClass178A90::func_003EFAA0()
{
    return &D_50CD30;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EFAB0);

struct N50Owner94_003E68C0 { u8 pad00[0x64]; u8 active; u8 pad65[0x2F]; void* owner; };

void func_003EFAF0(N50Owner94_003E68C0* object)
{
    object->active = 1;
    void* adjusted = object;
    if (object != 0)
    {
        adjusted = (u8*)adjusted + 0x90;
    }
    func_0011F770(object->owner, adjusted);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EFB30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F00E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F0150);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F0F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F1160);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F1250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F1330);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F2510);

/** Forward the receiver to func_004D00B0. */
void func_003F2550(LibClass178A90* object)
{
    func_004D00B0(object);
}

/** Queue the DMA submission embedded at offset 0x90 when present. */
s32 func_003F2570(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x90);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F25A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F2CB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F3D70);

extern "C" void func_003F3E60(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x14) = value;
}

extern "C" u32 func_003F3E70(const void* object)
{
    return *(const u32*)((const u8*)object + 0x3C78);
}

extern "C" void func_003F3E80(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x4) = value;
}

extern "C" void func_003F3E90(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x8C) = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F3EA0);

extern "C" void* func_003F3EF0(void* object)
{
    return (u8*)object + 0x3C60;
}

extern "C" void func_003F3F00(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x3C7C) = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F3F10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4070);

extern "C" void* func_003F42A0(void* object)
{
    LibWordPairView* state = (LibWordPairView*)object;
    state->unk04 = 0;
    state->unk00 = 0;
    return object;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F42B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4320);

/** @brief Return the fixed value 9. @param object Unused receiver. @return Always 9. */
extern "C" s32 func_003F4370(void* object)
{
    return 9;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4380);

/** @brief Provide the empty default hook. */
extern "C" void func_003F4410(void)
{
}

/** @brief Clear the transform's first state byte. */
void LibClass178A90::func_003F4420()
{
    unk60 = 0;
}

/** @brief Leave the default transform update hook unchanged. */
void LibClass178A90::func_003EEBE0()
{
}

/** @brief Leave the default transform output handler unchanged. @param matrix Unused matrix. @param context Unused caller context. */
void LibClass178A90::func_003F4440(const void* matrix, void* context)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4450);

/** @brief Run the default transform-state update. */
extern "C" void func_003F44E0(void* object)
{
    func_0044D0D0(object);
}

extern "C" void func_003F4500(LibClass178A90* object)
{
    object->unk60 = 8;
}

/**
 * @brief Read the cached combined transformation matrix.
 * @return Pointer to the stored matrix; this call does not update it.
 */
const LibMatrix44Value* LibTransform::get_transform_matrix()
{
    return &transform;
}

/**
 * @brief Read the additional local translation.
 * @return Stored translation vector; only xyz is used to build the offset matrix.
 */
const LibVector4* LibTransform::get_offset_translation() const
{
    return &offset_translation;
}

/**
 * @brief Read the additional local rotation.
 * @return Stored quaternion in x, y, z, w order.
 */
const LibVector4* LibTransform::get_offset_rotation() const
{
    return &offset_rotation;
}

/**
 * @brief Read the additional local scale.
 * @return Stored scale vector; only xyz is used to build the offset matrix.
 */
const LibVector4* LibTransform::get_offset_scale() const
{
    return &offset_scale;
}

/** @brief Return the fixed value 14. @param object Receiver or first argument; unused. @return Always 14. */
extern "C" s32 func_003F4550(void* object)
{
    return 14;
}

extern "C" void func_003F4560(LibClass178A90* object)
{
    object->unk60 = 7;
}

/** Build a four-word stack value and return its address. */
void* func_003F4570(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F45A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F45B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F45C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F45D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F45E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F45F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F49E0);

/** @brief Store a byte in one of three backing-buffer slots. @param index Slot index. @param value Byte value. */
void LibClass3F5B80::func_003F4A10(s32 index, u8 value)
{
    if (index <= -1 || index >= 3)
    {
        return;
    }
    buffer->unk67B[index] = value;
}

/** @brief Store a byte in one of three backing-buffer slots. @param index Slot index. @param value Byte value. */
void LibClass3F5B80::func_003F4A50(s32 index, u8 value)
{
    if (index <= -1 || index >= 3)
    {
        return;
    }
    buffer->unk678[index] = value;
}

/** @brief Store a byte in one of three backing-buffer slots. @param index Slot index. @param value Byte value. */
void LibClass3F5B80::func_003F4A90(s32 index, u8 value)
{
    if (index <= -1 || index >= 3)
    {
        return;
    }
    buffer->unk675[index] = value;
}

/** @brief Read an entry's state byte when the index is in range. @param index Entry index. @return The state byte, or zero when the index is invalid. */
u8 LibClass3F5B80::func_003F4AD0(s32 index)
{
    if (index >= 0)
    {
        if (index < 0x1A)
        {
            return buffer->entries[index].unk04;
        }
    }
    return 0;
}

/** @brief Read an entry's first word when the index is in range. @param index Entry index. @return The word, or zero when the index is invalid. */
u32 LibClass3F5B80::func_003F4B10(s32 index)
{
    if (index >= 0)
    {
        if (index < 0x1A)
        {
            return buffer->entries[index].unk00;
        }
    }
    return 0;
}

/** @brief Return an entry's signed 16-bit value when the index is in range. @param index Entry index. @return The entry value, or -1 when the index is invalid. */
s32 LibClass3F5B80::func_003F4B50(s32 index)
{
    if (index >= 0)
    {
        if (index < 0x1A)
        {
            return buffer->entries[index].unk06;
        }
    }
    return -1;
}

/** @brief Store a halfword value in the backing buffer, mapping -1 to 0x37. @param value Value to store. */
void LibClass3F5B80::func_003F4B90(s32 value)
{
    if ((s16)value == -1)
    {
        value = 0x37;
    }
    buffer->unk668 = value;
}

/** @brief Store two values in an entry when the index is in range. @param index Entry index. @param value Word value. @param state Byte value. */
void LibClass3F5B80::func_003F4BC0(s32 index, u32 value, u8 state)
{
    if (index >= 0)
    {
        if (index < 0x1A)
        {
            LibClass3F5B80Entry* entry = &buffer->entries[index];
            entry->unk00 = value;
            entry->unk04 = state;
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4BF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4DE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F5AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F5B80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F5C40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F5C80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F5CC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F5CF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F5D40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F5D70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F5E00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", __dt__14LibBufferOwnerFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F6000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F64A0);
