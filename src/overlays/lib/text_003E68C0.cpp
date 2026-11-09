#include "include_asm.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"

/** Bounding sphere objects without bounds report: centred on the origin, radius 1000000. */
extern "C" LibVector4 g_default_bounding_sphere;

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

/** @brief Report the list kind used when registration requests the default. @return Three. */
s32 LibListObject::get_default_list_kind()
{
    return 3;
}

/** @brief Default update handler that performs no work. */
void LibListObject::update()
{
}

/** @brief Leave the base intrusive object unchanged. */
void LibListObject::render()
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
s32 LibTransformOwner::get_box_cull_center(void* output)
{
    return 0;
}

/** @brief Test whether the supplied value is negative. @param value Value to test. @param mode Unused mode. @return One if negative, otherwise zero. */
s32 LibTransformOwner::set_fade_alpha(float value, float mode)
{
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
}

/** @brief Return no replacement transform receiver. @return Null. */
LibTransformOwner* LibTransformOwner::clone()
{
    return 0;
}

/** @brief Leave the base transform receiver unchanged. */
void LibTransformOwner::release_clone()
{
}

/** @brief Copy the position and mark the transform dirty. */
void LibOrientedTransform::copy_translation(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&translation, value);
}

/** @brief Copy the position and mark the transform dirty. */
void LibOrientedTransform::set_translation_vector(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&translation, value);
}

/** @brief Set the position and a w component of one, and mark the transform dirty. */
void LibOrientedTransform::set_translation(float x, float y, float z)
{
    transform_dirty = 1;
    translation.x = x;
    translation.y = y;
    translation.z = z;
    translation.w = 1.0f;
}

/** @brief Set all four components of the primary transform vector and mark it dirty. @param x First component. @param y Second component. @param z Third component. @param w Fourth component. */
void LibOrientedTransform::set_orientation_components(float x, float y, float z, float w)
{
    transform_dirty = 1;
    orientation.x = x;
    orientation.y = y;
    orientation.z = z;
    orientation.w = w;
}

/** @brief Copy the primary transform vector and mark it dirty. @param value Source vector. */
void LibOrientedTransform::copy_orientation(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&orientation, value);
}

/** @brief Copy the primary transform vector and mark it dirty. @param value Source vector. */
void LibOrientedTransform::set_orientation(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&orientation, value);
}

/** @brief Convert a rotation into the rotation vector and mark the transform dirty. */
void LibOrientedTransform::convert_rotation(const LibVector4* value)
{
    transform_dirty = 1;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), &value->x);
}

/** @brief Convert a rotation into the rotation vector and mark the transform dirty. */
void LibOrientedTransform::set_rotation_vector(const LibVector4* value)
{
    transform_dirty = 1;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), &value->x);
}

/** @brief Convert three rotation components into the rotation vector and mark the transform dirty. */
void LibOrientedTransform::set_rotation(float x, float y, float z)
{
    transform_dirty = 1;
    LibVector4 value;
    value.x = x;
    value.y = y;
    value.z = z;
    value.w = 1.0f;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), &value.x);
}

/** @brief Copy the secondary transform vector and mark it dirty. @param value Source vector. */
void LibOrientedTransform::copy_scale(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&scale, value);
}

/** @brief Copy the secondary transform vector and mark it dirty. @param value Source vector. */
void LibOrientedTransform::set_scale_vector(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&scale, value);
}

/** @brief Set the secondary transform vector's xyz components and mark it dirty. @param x First component. @param y Second component. @param z Third component. */
void LibOrientedTransform::set_scale(float x, float y, float z)
{
    transform_dirty = 1;
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

void func_003EF030(u8* object)
{
    object[0x64] = 1;
    *(volatile u32*)0x10009020 = *(u32*)(object + 0x9C);
    *(volatile u32*)0x10009010 = *(u32*)(object + 0xA0);
    *(volatile u32*)0x1000E010 = 2;
    *(volatile u32*)0x10009000 = 0x101;
}

/** @brief Finish the transform receiver's packet. @param object Transform owner. */
extern "C" void func_003EF070(LibTransformOwner* object)
{
    lib_finish_packet(object);
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

/** @brief Free the packet storage unless it is borrowed. */
LibPacketBuffer::~LibPacketBuffer()
{
    if (!unk14)
    {
        delete unk04;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", __ct__13LibClipRegionFv);

/** @brief Delete the object through its virtual destructor; null is ignored. */
void LibListObject::destroy()
{
    delete this;
}

/** @brief Store the position components and set the homogeneous component to one. */
void LibPositionTransform::set_translation(float x, float y, float z)
{
    translation.x = x;
    translation.y = y;
    translation.z = z;
    translation.w = 1.0f;
}

/** @brief Copy the position. */
void LibPositionTransform::copy_translation(const LibVector4* value)
{
    copy_vector(&translation, value);
}

/** @brief Copy the position. */
void LibPositionTransform::set_translation_vector(const LibVector4* value)
{
    copy_vector(&translation, value);
}

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
extern "C" void func_003EF910(LibTransformOwner* object)
{
    object->draw_bucket = 9;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF920);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EF960);

/** @brief Default DMA notification hook; does nothing. */
void LibDmaCallbacks::on_packet_notify(u32 value)
{
}

/**
 * @brief Return the default bounding sphere, which encloses everything.
 * @return Sphere centre in xyz, radius in w.
 */
const LibVector4* LibTransformOwner::get_bounding_sphere()
{
    return &g_default_bounding_sphere;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EFAB0);

struct N50Owner94_003E68C0
{
        u8 pad00[0x64];
        u8 active;
        u8 pad65[0x2F];
        ResidentPacket* owner;
};

void func_003EFAF0(N50Owner94_003E68C0* object)
{
    object->active = 1;
    void* adjusted = object;
    if (object != 0)
    {
        adjusted = (u8*)adjusted + 0x90;
    }
    resident_packet_submit(object->owner, adjusted);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003EFB30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F00E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F0150);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F0F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F1160);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F1250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F1330);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F2510);

/** Forward the receiver to lib_finish_packet. */
void func_003F2550(LibTransformOwner* object)
{
    lib_finish_packet(object);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", __dt__14LibClass172000Fv);

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

/** @brief Default preparation hook; does nothing. */
void LibDmaCallbacks::on_packet_complete(u32 value)
{
}

/** @brief Clear the transform's first state byte. */
void LibTransformOwner::set_default_draw_bucket()
{
    draw_bucket = 0;
}

/** @brief Leave the default transform update hook unchanged. */
void LibTransformOwner::render()
{
}

/** @brief Leave the default transform output handler unchanged. @param matrix Unused matrix. @param context Unused caller context. */
void LibTransformOwner::build_packet(const void* matrix, void* context)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F4450);

/** @brief Run the default transform-state update. */
extern "C" void func_003F44E0(void* object)
{
    func_0044D0D0(object);
}

extern "C" void func_003F4500(LibTransformOwner* object)
{
    object->draw_bucket = 8;
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

extern "C" void func_003F4560(LibTransformOwner* object)
{
    object->draw_bucket = 7;
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

/**
 * @brief Read the checked word.
 * @return The word, or zero when its two copies disagree.
 */
u32 LibProtectedValues::get_checked_word()
{
    LibProtectedRecord* values = record();

    if (values->word == (values->check ^ (LIB_PROTECTED_WORD_KEY ^ LIB_PROTECTED_CHECK_KEY)))
    {
        return values->word ^ LIB_PROTECTED_WORD_KEY;
    }

    return 0;
}

/**
 * @brief Store the checked word and its check copy.
 * @param value Word to store.
 */
void LibProtectedValues::set_checked_word(u32 value)
{
    LibProtectedRecord* values = record();
    values->word = value ^ LIB_PROTECTED_WORD_KEY;
    values->check = value ^ LIB_PROTECTED_CHECK_KEY;
}

/**
 * @brief Read the small value.
 * @return The value, 0 to LIB_PROTECTED_SMALL_MAX.
 */
s32 LibProtectedValues::get_small_value()
{
    return (record()->small_value ^ LIB_PROTECTED_SMALL_KEY) - LIB_PROTECTED_SMALL_BIAS;
}

/**
 * @brief Store the small value, clamped to 0 to LIB_PROTECTED_SMALL_MAX.
 * @param value Value to store.
 */
void LibProtectedValues::set_small_value(s32 value)
{
    value += LIB_PROTECTED_SMALL_BIAS;

    if (value > LIB_PROTECTED_SMALL_BIAS + LIB_PROTECTED_SMALL_MAX)
    {
        value = LIB_PROTECTED_SMALL_BIAS + LIB_PROTECTED_SMALL_MAX;
    }
    else if (value < LIB_PROTECTED_SMALL_BIAS)
    {
        value = LIB_PROTECTED_SMALL_BIAS;
    }

    record()->small_value = value ^ LIB_PROTECTED_SMALL_KEY;
}

/**
 * @brief Read the large value.
 * @return The value, 0 to LIB_PROTECTED_LARGE_MAX.
 */
s32 LibProtectedValues::get_large_value()
{
    LibProtectedRecord* values = record();
    return (values->large_value ^ values->large_key) - LIB_PROTECTED_LARGE_BIAS;
}

/**
 * @brief Store the large value, clamped to 0 to LIB_PROTECTED_LARGE_MAX, under a fresh random key.
 * @param value Value to store.
 */
void LibProtectedValues::set_large_value(s32 value)
{
    value += LIB_PROTECTED_LARGE_BIAS;

    if (value > LIB_PROTECTED_LARGE_BIAS + LIB_PROTECTED_LARGE_MAX)
    {
        value = LIB_PROTECTED_LARGE_BIAS + LIB_PROTECTED_LARGE_MAX;
    }
    else if (value < LIB_PROTECTED_LARGE_BIAS)
    {
        value = LIB_PROTECTED_LARGE_BIAS;
    }

    LibProtectedRecord* values = record();
    u32 key = (resident_next_random_word() & 0xFFFF) + LIB_PROTECTED_LARGE_KEY_BASE;
    values->large_key = key;
    values->large_value = value ^ key;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", reset__18LibProtectedValuesFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", __dt__14LibBufferOwnerFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F6000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003E68C0", func_003F64A0);
