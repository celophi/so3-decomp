#include "include_asm.h"
#include "overlays/1067-00/text_001E1590.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0012F0F8.h"
#include "overlays/lib/text_00429B00.h"
#include "main/resident_0010A0E0.h"
#include "sdk/main/syscalls_00121940.h"
#include "overlays/1067-00/text_0022DC70.h"
#include "overlays/1067-00/text_002D3BD0.h"
#include "overlays/1067-00/field_runtime.h"

struct FieldGlobal643CState
{
    u8 unk00[0x14];
    FieldClass153E30* unk14;
    u8 unk18;
    u8 unk19;
    u16 unk1a;
};
struct FieldGlobal643CRequest
{
    u8 unk00[0x10];
    FieldGlobal643CState* unk10;
};
extern "C" FieldGlobal643CRequest* D_001B643C;

extern "C" void* D_001B5FC0[];

extern "C" s32 func_0023AEB0(FieldClass1530D0* owner, FieldClass150070* loader);

s32 FieldClass150120::func_001DF3D0()
{
    return 4;
}

void FieldClass150120::func_001DD7B0()
{
    func_0011ED90(D_001B65F4, this);
}

/**
 * @brief Initialize a keyed request and append its new loader to the context list.
 * @param object Request owner.
 * @param key Request key.
 * @param mode Request mode.
 * @return Created loader, or null when allocation fails.
 */
FieldClass1501A0* func_001E15C0(FieldClass150120* object, s32 key, u8 mode)
{
    func_0023AE00(static_cast<FieldClass1530D0*>(D_001B6430->context->unk30), 8);
    object->unk1f = 1;
    object->unk18 = key;
    object->unk1c = 0;
    object->unk1d = mode;
    if (mode == 1)
    {
        object->unk1e = 0;
    }
    else
    {
        object->unk1e = 1;
        object->unk20 = 1;
    }
    object->unk98 = new(0) FieldClass1501A0(object->unk18);
    if (!object->unk98)
    {
        return 0;
    }
    object->unk98->unk20 = static_cast<FieldClass1DD400*>(object);
    static_cast<FieldClass1530D0*>(D_001B6430->context->unk30)->func_004D74F0(object->unk98, (void*)-1);
    return object->unk98;
}

/**
 * @brief Report whether a list traversal has reached a null link.
 * @param node Traversal link to inspect.
 * @return True when the link is null.
 */
static inline bool null_node(const FieldClass150060* node)
{
    if (node)
    {
        return false;
    }
    return true;
}

/**
 * @brief Reuse a listed type-8 loader for the stored key, or create and insert one when absent.
 */
void FieldClass150120::func_001DF360()
{
    FieldClass1530D0* manager = static_cast<FieldClass1530D0*>(D_001B6430->context->unk30);
    FieldClass150060* node = reinterpret_cast<FieldClass150060*>(&static_cast<LibClass178DD0&>(*manager));
    bool found = false;
    if (unk1c != 1 && (unk1c != 0 || unk1d != 1 || unk1e != 1))
    {
        s32 key = unk18;
        if (key > 0 && unk1f == 1)
        {
            for (;;)
            {
                node = node->unk08;
                if (null_node(node) || static_cast<void*>(&static_cast<LibClass178DD0&>(*manager)) == node)
                {
                    break;
                }
                FieldClass1501A0* loader = static_cast<FieldClass1501A0*>(node);
                if (loader->func_001DF350() == 8 && key == loader->unk34)
                {
                    func_004D65C0(loader);
                    manager->insert(loader);
                    found = true;
                    break;
                }
            }
            if (found == false)
            {
                unk9c = new(0) FieldClass1501A0(key);
                if (unk9c)
                {
                    manager->insert(unk9c);
                }
            }
        }
    }
}

/**
 * @brief Handle a completed request buffer in the base receiver.
 * @param buffer Completed buffer; unused.
 * @return Always zero.
 */
s32 FieldClass153E30::func_001E1820(void* buffer)
{
    return 0;
}

/**
 * @brief Test whether an allocation slot is occupied.
 * @param slots Buffer owner.
 * @param index Slot index.
 * @return True when occupied.
 */
static inline bool field_has_allocation(const FieldBufferSlots* slots, u8 index)
{
    return slots->unk14[index] != 0;
}
/**
 * @brief Test whether the resource allocation is attached.
 * @param slots Buffer owner.
 * @return True when attached.
 */
static inline bool field_has_resource(const FieldBufferSlots* slots)
{
    return slots->unk114 != 0;
}
/**
 * @brief Test whether an aligned buffer slot is occupied.
 * @param slots Buffer owner.
 * @param index Slot index.
 * @return True when occupied.
 */
static inline bool field_has_slot_buffer(const FieldBufferSlots* slots, s32 index)
{
    return slots->unk11c[index] != 0;
}
/**
 * @brief Align an allocation address upward to 128 bytes.
 * @param allocation Allocation address.
 * @return Aligned address.
 */
static inline void* field_aligned_buffer(u8* allocation)
{
    return reinterpret_cast<void*>(((u32)allocation + 0x7F) & ~0x7F);
}
/**
 * @brief Advance along a resource chain and read the selected payload size.
 * @param source Resource pointer advanced while following relative links.
 * @param index Number of links to follow.
 * @return Selected payload size, or zero when the chain ends.
 */
static inline s32 field_resource_size(FieldResourceRecord*& source, s32 index)
{
    for (s32 position = 0; position < index; position++)
    {
        if (!source->next_offset)
        {
            return 0;
        }
        source = reinterpret_cast<FieldResourceRecord*>(reinterpret_cast<u8*>(source) + source->next_offset);
    }
    if (!source)
    {
        return 0;
    }
    return source->unk08;
}

/**
 * @brief Decode a resource after reading its source record address.
 * @param loader Completed record loader.
 * @param allocation Allocation whose aligned address receives the resource.
 * @param index Resource index.
 * @return Decode result.
 */
static inline s32 field_decode_resource(FieldClass150150* loader, u8* allocation, s32 index)
{
    ResidentResourceHeader* source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
    return func_001025A0(D_001B65EC, source, field_aligned_buffer(allocation), index);
}

/**
 * @brief Fill missing resource slots, retrying allocations on the alternate heap.
 * @param loader Completed record loader.
 * @return 1 when loading completes, or 0 when the loader or decoding fails.
 */
s32 FieldClass150120::func_001E1830(FieldClass150150* loader)
{
    if (!loader)
    {
        return 0;
    }
    bool present_1 = field_has_allocation(unk94, 0);
    if (!present_1)
    {
        u8* allocation = func_00102920(D_001B65EC,
            reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 1, 1);
        if (!allocation)
        {
            void* previous_heap = func_00100C80(0);
            allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 1, 1);
            func_00100C80(previous_heap);
        }
        if (!allocation || !field_decode_resource(loader, allocation, 1))
        {
            func_00102A40(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 1);
            field_decode_resource(loader, allocation, 1);
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = func_002D3E40(unk94, allocation, 0);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    bool present_2 = field_has_allocation(unk94, 11);
    if (!present_2)
    {
        u8* allocation = func_00102920(D_001B65EC,
            reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 2, 1);
        if (!allocation)
        {
            void* previous_heap = func_00100C80(0);
            allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 2, 1);
            func_00100C80(previous_heap);
        }
        if (!allocation || !field_decode_resource(loader, allocation, 2))
        {
            func_00102A40(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 2);
            field_decode_resource(loader, allocation, 2);
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = func_002D3E40(unk94, allocation, 11);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    for (s32 slot = 0, index = 3; index < 11; index++, slot++)
    {
        bool present = field_has_allocation(unk94, slot + 1);
        if (!present)
        {
            u8* allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), index, 1);
            if (!allocation)
            {
                void* previous_heap = func_00100C80(0);
                allocation = func_00102920(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), index, 1);
                func_00100C80(previous_heap);
            }
            if (!allocation || !field_decode_resource(loader, allocation, index))
            {
                func_00102A40(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), index);
                field_decode_resource(loader, allocation, index);
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, slot + 1);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    bool present_11 = field_has_allocation(unk94, 12);
    if (!present_11)
    {
        u8* allocation = func_00102920(D_001B65EC,
            reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 11, 1);
        if (!allocation)
        {
            void* previous_heap = func_00100C80(0);
            allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 11, 1);
            func_00100C80(previous_heap);
        }
        if (!allocation || !field_decode_resource(loader, allocation, 11))
        {
            func_00102A40(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 11);
            field_decode_resource(loader, allocation, 11);
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = func_002D3E40(unk94, allocation, 12);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    bool resource_present = field_has_resource(unk94);
    if (!resource_present)
    {
        FieldResourceRecord* source;
        FieldClass1530C0* record = loader->unk1c;
        source = reinterpret_cast<FieldResourceRecord*>(record->rounded_unk04());
        for (s32 position = 0; position < 12; position++)
        {
            if (!source->next_offset)
            {
                return 0;
            }
            source = reinterpret_cast<FieldResourceRecord*>(reinterpret_cast<u8*>(source) + source->next_offset);
        }
        if (!source)
        {
            return 0;
        }
        s32 size = source->unk08;
        u8* allocation = func_00102920(D_001B65EC,
            reinterpret_cast<ResidentResourceHeader*>(record->rounded_unk04()), 12, 1);
        if (!allocation)
        {
            void* previous_heap = func_00100C80(0);
            allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 12, 1);
            func_00100C80(previous_heap);
        }
        if (!allocation || !field_decode_resource(loader, allocation, 12))
        {
            func_00102A40(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 12);
            field_decode_resource(loader, allocation, 12);
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = func_002D3D40(unk94, allocation, size);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    s32 resource_index;
    for (s32 slot = 0; slot < 3; slot++)
    {
        bool present = field_has_slot_buffer(unk94, slot);
        if (!present)
        {
            resource_index = slot + 13;
            FieldResourceRecord* source;
            FieldClass1530C0* record = loader->unk1c;
            source = reinterpret_cast<FieldResourceRecord*>(record->rounded_unk04());
            s32 size = field_resource_size(source, resource_index);
            u8* allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(record->rounded_unk04()), resource_index, 1);
            if (!allocation)
            {
                void* previous_heap = func_00100C80(0);
                allocation = func_00102920(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), resource_index, 1);
                func_00100C80(previous_heap);
            }
            if (!allocation || !field_decode_resource(loader, allocation, resource_index))
            {
                func_00102A40(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), resource_index);
                field_decode_resource(loader, allocation, resource_index);
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3C40(unk94, allocation, size, slot);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    unk94->unk140 = 1;
    s32 index;
    u8* allocation;
    void* previous_heap;
    s32 slot;
    for (slot = 0, index = 16; index < 24; index++, slot++)
    {
        bool present = field_has_allocation(unk94, slot + 49);
        if (!present)
        {
            allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), index, 1);
            if (!allocation)
            {
                previous_heap = func_00100C80(0);
                allocation = func_00102920(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), index, 1);
                func_00100C80(previous_heap);
            }
            if (!allocation || !field_decode_resource(loader, allocation, index))
            {
                func_00102A40(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), index);
                field_decode_resource(loader, allocation, index);
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, slot + 49);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    for (s32 slot = 0; slot < 2; slot++)
    {
        bool present = field_has_allocation(unk94, slot + 9);
        if (!present)
        {
            u8* allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), slot + 24, 1);
            if (!allocation)
            {
                void* previous_heap = func_00100C80(0);
                allocation = func_00102920(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), slot + 24, 1);
                func_00100C80(previous_heap);
            }
            if (!allocation || !field_decode_resource(loader, allocation, slot + 24))
            {
                func_00102A40(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), slot + 24);
                field_decode_resource(loader, allocation, slot + 24);
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, slot + 9);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    for (s32 slot = 0; slot < 2; slot++)
    {
        bool present = field_has_allocation(unk94, slot + 57);
        if (!present)
        {
            u8* allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), slot + 26, 1);
            if (!allocation)
            {
                void* previous_heap = func_00100C80(0);
                allocation = func_00102920(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), slot + 26, 1);
                func_00100C80(previous_heap);
            }
            if (!allocation || !field_decode_resource(loader, allocation, slot + 26))
            {
                func_00102A40(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), slot + 26);
                field_decode_resource(loader, allocation, slot + 26);
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, slot + 57);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    return 1;
}

/**
 * @brief Decode and attach the resource buffers assigned to this loader kind.
 * @param loader Completed record loader.
 * @return One when the required resources have been processed, otherwise zero.
 */
s32 FieldClass150120::func_001E2E40(FieldClass150150* loader)
{
    if (!loader)
    {
        return 0;
    }
    {
        bool present = field_has_allocation(unk94, 0);
        if (!present)
        {
            u8* allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 1, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
            if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), 1))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, 0);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    {
        bool present = field_has_allocation(unk94, 11);
        if (!present)
        {
            u8* allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 2, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
            if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), 2))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, 11);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    {
        bool present = field_has_allocation(unk94, 13);
        if (!present)
        {
            u8* allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 3, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
            if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), 3))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, 13);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    bool resource_present = field_has_resource(unk94);
    if (!resource_present)
    {
        FieldResourceRecord* source;
        FieldClass1530C0* record = loader->unk1c;
        source = reinterpret_cast<FieldResourceRecord*>(record->rounded_unk04());
        for (s32 position = 0; position < 4; position++)
        {
            if (!source->next_offset)
            {
                return 0;
            }
            source = reinterpret_cast<FieldResourceRecord*>(reinterpret_cast<u8*>(source) + source->next_offset);
        }
        if (!source)
        {
            return 0;
        }
        s32 size = source->unk08;
        u8* allocation = func_00102920(D_001B65EC,
            reinterpret_cast<ResidentResourceHeader*>(record->rounded_unk04()), 4, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
        if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), 4))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = func_002D3D40(unk94, allocation, size);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    for (s32 slot = 0; slot < 38; slot++)
    {
        u8* allocation = func_00102920(D_001B65EC,
            reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), slot + 5, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
        if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), slot + 5))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = func_002D3E40(unk94, allocation, (u8)(slot + 21));
        if (!attached)
        {
            delete[] allocation;
        }
    }
    {
        bool present = field_has_allocation(unk94, 14);
        if (!present)
        {
            u8* allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 43, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
            if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), 43))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, 14);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    return 1;
}

/**
 * @brief Attach decoded resources to the remaining allocation slots.
 * @param loader Completed record loader.
 * @return 1 when loading completes, or 0 when the loader or decoding fails.
 */
s32 FieldClass150120::func_001E3580(FieldClass150150* loader)
{
    if (!loader)
    {
        return 0;
    }
    u16 secondary_index = 0;
    for (s32 index = 0; index < 10; index++)
    {
        if (index < 8)
        {
            bool present = field_has_allocation(unk94, index + 15);
            if (!present)
            {
                u16 resource_index = index + 1;
                u8* allocation = func_00102920(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), resource_index, 1);
                ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
                if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), resource_index))
                {
                    if (allocation)
                    {
                        delete allocation;
                    }
                    return 0;
                }
                u8 attached = func_002D3E40(unk94, allocation, index + 15);
                if (!attached)
                {
                    delete[] allocation;
                }
            }
        }
        else
        {
            s32 slot = secondary_index + 59;
            bool present = field_has_allocation(unk94, slot);
            if (!present)
            {
                u16 resource_index = index + 1;
                u8* allocation = func_00102920(D_001B65EC,
                    reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), resource_index, 1);
                ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
                if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), resource_index))
                {
                    if (allocation)
                    {
                        delete allocation;
                    }
                    return 0;
                }
                u8 attached = func_002D3E40(unk94, allocation, slot);
                secondary_index++;
                if (!attached)
                {
                    delete[] allocation;
                }
            }
        }
    }
    for (s32 index = 0; index < 2; index++)
    {
        bool present = field_has_allocation(unk94, index + 23);
        if (!present)
        {
            u16 resource_index = index + 11;
            u8* allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), resource_index, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
            if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), resource_index))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, index + 23);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    return 1;
}

/**
 * @brief Decode missing resource allocations into the owner's buffer slots.
 * @param loader Completed record loader.
 * @return One after processing the resource slots, or zero on decode failure.
 */
s32 FieldClass150120::func_001E39A0(FieldClass150150* loader)
{
    if (!loader)
    {
        return 0;
    }
    bool present = field_has_allocation(unk94, 11);
    if (!present)
    {
        u8* allocation = func_00102920(D_001B65EC, reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 1, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
        if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), 1))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = func_002D3E40(unk94, allocation, 11);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    for (s32 slot = 0; slot < 8; slot++)
    {
        bool present = field_has_allocation(unk94, slot + 1);
        if (!present)
        {
            u8* allocation = func_00102920(D_001B65EC, reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), slot + 2, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
            if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), slot + 2))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, slot + 1);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    bool resource_present = field_has_resource(unk94);
    if (!resource_present)
    {
        FieldResourceRecord* source;
        FieldClass1530C0* record = loader->unk1c;
        source = reinterpret_cast<FieldResourceRecord*>(record->rounded_unk04());
        s32 size = field_resource_size(source, 10);
        u8* allocation = func_00102920(D_001B65EC, reinterpret_cast<ResidentResourceHeader*>(record->rounded_unk04()), 10, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
        if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), 10))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = func_002D3D40(unk94, allocation, size);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    s32 index;
    for (s32 slot = 0; slot < 3; slot++)
    {
        bool present = field_has_slot_buffer(unk94, slot);
        if (!present)
        {
            index = slot + 11;
            FieldResourceRecord* source;
            FieldClass1530C0* record = loader->unk1c;
            source = reinterpret_cast<FieldResourceRecord*>(record->rounded_unk04());
            s32 size = field_resource_size(source, index);
            u8* allocation = func_00102920(D_001B65EC, reinterpret_cast<ResidentResourceHeader*>(record->rounded_unk04()), index, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
            if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), index))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3C40(unk94, allocation, size, slot);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    unk94->unk140 = 1;
    for (s32 slot = 0; slot < 2; slot++)
    {
        bool present = field_has_allocation(unk94, slot + 9);
        if (!present)
        {
            u8* allocation = func_00102920(D_001B65EC, reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), slot + 14, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
            if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), slot + 14))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, slot + 9);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    for (s32 slot = 0; slot < 10; slot++)
    {
        bool present = field_has_allocation(unk94, slot + 49);
        if (!present)
        {
            u8* allocation = func_00102920(D_001B65EC, reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), slot + 16, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
            if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), slot + 16))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, slot + 49);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    return 1;
}

/**
 * @brief Decode and attach missing resource buffers from a completed record loader.
 * @param loader Completed record loader.
 * @return One when the required buffers are available, otherwise zero.
 */
s32 FieldClass150120::func_001E4220(FieldClass150150* loader)
{
    if (!loader)
    {
        return 0;
    }
    bool present = field_has_allocation(unk94, 0);
    if (!present)
    {
        u8* allocation = func_00102920(D_001B65EC,
            reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 1, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
        if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), 1))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = func_002D3E40(unk94, allocation, 0);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    bool second_present = field_has_allocation(unk94, 11);
    if (!second_present)
    {
        u8* allocation = func_00102920(D_001B65EC,
            reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), 2, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
        if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), 2))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = func_002D3E40(unk94, allocation, 11);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    for (s32 slot = 0, index = 3; index < 11; index++, slot++)
    {
        bool present = field_has_allocation(unk94, slot + 1);
        if (!present)
        {
            u8* allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), index, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
            if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), index))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, slot + 1);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    bool resource_present = field_has_resource(unk94);
    if (!resource_present)
    {
        FieldResourceRecord* source;
        FieldClass1530C0* record = loader->unk1c;
        source = reinterpret_cast<FieldResourceRecord*>(record->rounded_unk04());
        for (s32 position = 0; position < 11; position++)
        {
            if (!source->next_offset)
            {
                return 0;
            }
            source = reinterpret_cast<FieldResourceRecord*>(reinterpret_cast<u8*>(source) + source->next_offset);
        }
        if (!source)
        {
            return 0;
        }
        s32 size = source->unk08;
        u8* allocation = func_00102920(D_001B65EC,
            reinterpret_cast<ResidentResourceHeader*>(record->rounded_unk04()), 11, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
        if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), 11))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = func_002D3D40(unk94, allocation, size);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    for (s32 slot = 0; slot < 2; slot++)
    {
        bool present = field_has_allocation(unk94, slot + 9);
        if (!present)
        {
            s32 index = slot + 12;
            u8* allocation = func_00102920(D_001B65EC,
                reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04()), index, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
            if (!func_001025A0(D_001B65EC, decoded_source, field_aligned_buffer(allocation), index))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = func_002D3E40(unk94, allocation, slot + 9);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E48A0__16FieldClass150120FP16FieldClass150150);

/**
 * @brief Notify the request receiver when a completed buffer is present.
 * @param object Request owner.
 * @param buffer Completed buffer.
 */
static inline void notify_request_buffer(FieldClass150120* object, u8* buffer)
{
    if (buffer)
    {
        FieldClass153E30* receiver = object->unk2c;
        receiver->func_001E1820(buffer);
        object->unk1f = 0;
    }
}

/**
 * @brief Pass a completed request buffer to its receiver, then release its loader.
 */
void FieldClass150120::func_001E4E50()
{
    u8* buffer = func_001E48A0(unk3c);
    if (buffer)
    {
        notify_request_buffer(this, buffer);
        delete[] buffer;
        FieldClass150150* loader = unk3c;
        if (loader)
        {
            func_004D65C0(loader);
            loader->func_001DD7B0();
        }
        func_00121FE0(0);
    }
}

/**
 * @brief Dispatch a completed request buffer or retain its loader for later processing.
 * @param arg Completed record loader.
 */
void FieldClass150120::func_001DDB30(void* arg)
{
    if (unk1d == 1)
    {
        FieldClass150150* loader = static_cast<FieldClass150150*>(arg);
        ResidentResourceHeader* source = reinterpret_cast<ResidentResourceHeader*>(loader->unk1c->rounded_unk04());
        void* destination = D_001B5FC0[0];
        if (destination)
        {
            func_001025A0(D_001B65EC, source, destination, 0);
            func_00121FE0(0);
            func_001011B0(func_10D8E0(), destination, 4, source->unk08);
        }
        unk1d = 0;
        if (loader)
        {
            func_004D65C0(loader);
            loader->func_001DD7B0();
        }
        unk20 = 1;
        unk1e = 1;
        if (unk30)
        {
            func_001E15C0(this, unk30, unk34);
        }
    }
    else
    {
        unk3c = static_cast<FieldClass150150*>(arg);
        unk1c = 1;
    }
}

void func_001E5020(FieldWordByte30* object, u32 word, u8 value)
{
    object->unk30 = word;
    object->unk34 = value;
}

FieldClass150120::~FieldClass150120()
{
    s32 i;
    for (i = 0; i < 10; i++)
    {
        if (unk44[i])
        {
            delete[] unk44[i];
            unk44[i] = 0;
        }
    }
}

/**
 * @brief Set the key to -1 and clear the request state, parallel arrays, and loader pointers.
 */
FieldClass150120::FieldClass150120()
{
    unk18 = -1;
    unk1d = 0;
    unk1c = 0;
    unk1e = 0;
    unk1f = 0;
    unk20 = 0;
    unk24 = 0;
    unk28 = 0;
    unk2c = 0;
    unk38 = 0;
    unk3c = 0;
    unk30 = 0;
    unk34 = 0;
    unk40 = 0;
    for (s32 index = 0; index < 10; index++)
    {
        unk44[index] = 0;
        unk6c[index] = 0;
    }
    unk94 = 0;
    unk98 = 0;
    unk9c = 0;
}

/**
 * @brief Queue the loader on the resident object queue without detaching it.
 */
void FieldClass1501A0::func_001DD7B0()
{
    func_0011ED90(D_001B65F4, this);
}

/**
 * @brief Allocate storage for the next keyed request and advance its loader state.
 * @param flag Request control flag.
 */
void FieldClass1501A0::func_001E0A50(s32 flag)
{
    func_001E5D20();
    if (unk15 == 0)
    {
        if (flag == 0 && !field_records_blocked())
        {
            if (unk2e == 0)
            {
                if (unk38)
                {
                    unk38--;
                    return;
                }
                u8 state = D_001B643C->unk10->unk18;
                if (state == 12 || state == 7)
                {
                    FieldClass1530D0* manager = static_cast<FieldClass1530D0*>(D_001B6430->context->unk30);
                    FieldClass150060* node = (FieldClass150060*)manager->LibClass178DD0::unk00;
                    u8 busy = 0;
                    for (;;)
                    {
                        node = node->unk08;
                        if ((FieldClass150060*)manager->LibClass178DD0::unk00 == node)
                        {
                            break;
                        }
                        FieldClass150010* loader = static_cast<FieldClass150010*>(node);
                        if (this != loader && (loader->func_001DF350() == 1 || loader->func_001DF350() == 2) && loader->func_001E07A0() == 1)
                        {
                            busy = 1;
                        }
                    }
                    if (busy)
                    {
                        return;
                    }
                }
            }
            u32 size = unk1c[unk2e].unk00 + 0x80;
            unk40 = func_00139900(size + 0x7D000);
            if (unk40)
            {
                func_00139928(unk40);
                unk40 = new(0) u8[(size + 0x7FF) & ~0x7FF];
            }
            else
            {
                FieldClass1530D0* manager = static_cast<FieldClass1530D0*>(D_001B6430->context->unk30);
                FieldClass150060* node = (FieldClass150060*)manager->LibClass178DD0::unk00;
                u8 busy = 0;
                for (;;)
                {
                    node = node->unk08;
                    if ((FieldClass150060*)manager->LibClass178DD0::unk00 == node)
                    {
                        break;
                    }
                    FieldClass150010* loader = static_cast<FieldClass150010*>(node);
                    if (this != loader && (loader->func_001DF350() == 1 || loader->func_001DF350() == 2))
                    {
                        if (loader->func_001E07A0() == 1)
                        {
                            busy = 1;
                        }
                        if (busy)
                        {
                            return;
                        }
                    }
                }
            }
            FieldClass1530C0* record = &unk1c[unk2e];
            record->unk04 = (u32)unk40;
            record->unk08_0 = 0;
            func_001E5BA0();
        }
    }
    else
    {
        FieldClass150150::func_001E0A50(flag);
    }
}

/**
 * @brief Advance a completed keyed request and notify its owner when the batch finishes.
 */
void FieldClass1501A0::func_001E5D20()
{
    if (!unk44)
    {
        return;
    }
    if (unk15 == 1)
    {
        if (field_records_blocked())
        {
            return;
        }
        while (unk2e < unk2d)
        {
            unk2e++;
            if (!unk1c[unk2e].unk16_0)
            {
                break;
            }
        }
        if (unk2e >= unk2d)
        {
            unk15 = 5;
            if (unk20)
            {
                unk20->func_001DDB30(this);
            }
        }
        else
        {
            unk15 = 0;
        }
    }
    unk44 = 0;
}

/**
 * @brief Flush the cache once for this loader.
 * @param arg Unused secondary-interface argument.
 */
void FieldClass1501A0::func_001DDB30(void* arg)
{
    if (!unk44)
    {
        func_00121FE0(0);
        unk44 = 1;
    }
}

void FieldClass1501A0::func_001E5AD0()
{
    s32 i;
    if (unk1c)
    {
        for (i = 0; i < unk24; i++)
        {
            FieldClass1530C0* record = &unk1c[i];
            record->unk0c = -1;
            record->unk04 = 0;
            record->unk10 = 0;
            record->unk16_0 = 0;
            record->unk16_1 = 1;
            record->unk08_0 = 0;
            record->unk16_2 = 0;
            record->unk14 = 0;
            record->unk15 = 0;
        }
    }
    unk20 = 0;
    unk2f = 0;
    unk2d = 0;
    unk2e = 0;
    unk14 = 8;
    unk2f = 0;
    unk38 = 2;
    unk3c = -1;
}

/**
 * @brief Detach the keyed loader, then destroy its record-loader base.
 */
FieldClass1501A0::~FieldClass1501A0()
{
    func_004D65C0(this);
}

/**
 * @brief Create the keyed loader's record array and prepare its first record.
 * @param key Request key.
 */
FieldClass1501A0::FieldClass1501A0(s32 key)
{
    func_001E5AD0();
    if (unk30_0)
    {
        if (unk1c)
        {
            delete[] unk1c;
        }
        unk1c = new(0) FieldClass1530C0[50];
    }
    else
    {
        void* heap = func_00100C80(D_001B6430->context->unk6c);
        if (unk1c)
        {
            delete[] unk1c;
        }
        unk1c = new(0) FieldClass1530C0[50];
        func_00100C80(heap);
    }
    unk24 = 50;
    unk34 = key;
    FieldClass1530C0* record = func_001E69A0(this, unk34, 0);
    unk3c = record->unk14;
    func_0011C8C0(D_001B65E4, unk34);
    u32 aligned_size = (func_0011C8C0(D_001B65E4, unk34) + 0x7FF) & ~0x7FF;
    record->set_capacity(aligned_size);
}

void FieldClass150150::func_001E5AD0()
{
    s32 i;
    if (unk1c)
    {
        for (i = 0; i < unk24; i++)
        {
            FieldClass1530C0* record = &unk1c[i];
            record->unk0c = -1;
            record->unk04 = 0;
            record->unk10 = 0;
            record->unk16_0 = 0;
            record->unk16_1 = 1;
            record->unk08_0 = 0;
            record->unk16_2 = 0;
            record->unk14 = 0;
            record->unk15 = 0;
        }
    }
    unk20 = 0;
    unk2f = 0;
    unk2d = 0;
    unk2e = 0;
}

/**
 * @brief Start the request for the current counted record.
 */
void FieldClass150150::func_001E5BA0()
{
    FieldClass1530C0* record = &unk1c[unk2e];
    if (record->rounded_unk04())
    {
        FieldClass1DD400* owner = this;
        u32 first = record->unk00;
        func_00103E70(D_001B65E8, record->unk0c, record->rounded_unk04(), 0x80000000, unk28, owner, first, 0, 1);
        u32 word = record->unk00;
        u32 size = record->rounded_unk04();
        record->unk10 = func_00103640(D_001B65E8, record->unk0c, size, 0x80000000, word, 0);
        unk15 = 1;
        unk30_1 = 0;
    }
}

/**
 * @brief Advance the current record request after its pending operation finishes.
 */
void FieldClass150150::func_001E5D20()
{
    if (!unk30_1)
    {
        return;
    }
    if (unk15 == 1)
    {
        if (field_records_blocked())
        {
            return;
        }
        FieldClass1530C0* record = &unk1c[unk2e];
        u32 word = record->unk00;
        u32 size = record->rounded_unk04();
        if (func_00103640(D_001B65E8, record->unk0c, size, 0x80000000, word, 0))
        {
            return;
        }
        while (unk2e < unk2d)
        {
            unk2e++;
            if (!unk1c[unk2e].unk16_0)
            {
                break;
            }
        }
        if (unk2e >= unk2d)
        {
            unk15 = 5;
        }
        else
        {
            unk15 = 0;
        }
    }
    unk30_1 = 0;
}

/**
 * @brief Release record storage and destroy the owned array.
 */
FieldClass150150::~FieldClass150150()
{
    if (unk1c)
    {
        func_001E68D0();
        delete[] unk1c;
        unk1c = 0;
    }
}

/**
 * @brief Advance record requests or handle a requested cancellation.
 * @param flag Request control flag.
 */
void FieldClass150150::func_001E0A50(s32 flag)
{
    switch (unk15)
    {
    case 0:
        if (!flag && unk1c)
        {
            func_00121FE0(0);
            FieldClass1530C0* record = &unk1c[unk2e];
            void* result = func_001E6B40(this, (record->unk00 + 0x7FF) & ~0x7FF, 1);
            if (result)
            {
                record->unk04 = (u32)result;
                record->unk08_0 = 0;
                func_001E5BA0();
            }
        }
        break;
    case 1:
        if (flag == 1)
        {
            for (s32 i = 0; i < unk2d; i++)
            {
                FieldClass1530C0* record = &unk1c[i];
                u32 word = record->unk00;
                u32 size = record->rounded_unk04();
                func_00103B20(D_001B65E8, record->unk0c, size, 0x80000000, word, 0);
            }
            unk15 = 9;
        }
        else
        {
            FieldClass1530C0* record = &unk1c[unk2e];
            u32 word = record->unk00;
            u32 size = record->rounded_unk04();
            if (!func_00103640(D_001B65E8, record->unk0c, size, 0x80000000, word, 0) && !field_records_blocked())
            {
                func_001DDB30(0);
            }
        }
        break;
    case 9:
        if (!flag)
        {
            func_001E5BA0();
        }
        break;
    case 10:
    {
        bool done = true;
        FieldClass1530C0* records = unk1c;
        for (s32 i = 0; i < unk2d; i++)
        {
            FieldClass1530C0* record = &records[i];
            u32 word = record->unk00;
            u32 size = record->rounded_unk04();
            record->unk10 = func_00103640(D_001B65E8, record->unk0c, size, 0x80000000, word, 0);
            if (record->unk10)
            {
                done = false;
            }
        }
        if (field_records_blocked())
        {
            done = false;
        }
        if (done)
        {
            for (s32 i = 0; i < unk24; i++, records++)
            {
                records->func_0023AD00();
            }
            unk2e = 0;
            unk15 = 0;
        }
        break;
    }
    case 7:
    {
        bool done = true;
        FieldClass1530C0* record = unk1c;
        for (s32 i = 0; i < unk2d; i++, record++)
        {
            u32 word = record->unk00;
            u32 size = record->rounded_unk04();
            record->unk10 = func_00103640(D_001B65E8, record->unk0c, size, 0x80000000, word, 0);
            if (record->unk10)
            {
                done = false;
            }
        }
        if (field_records_blocked())
        {
            done = false;
        }
        if (done)
        {
            func_001DD7B0();
        }
        break;
    }
    }
    func_001E5D20();
}

/**
 * @brief Finish or cancel pending record requests and report their remaining state.
 * @return One when cancelled storage remains, two when requests remain, or zero otherwise.
 */
s32 FieldClass150150::func_001E07A0()
{
    s32 result = 0;
    FieldClass1530C0* records = unk1c;
    switch (unk15)
    {
    case 1:
    {
        for (s32 i = 0; i < unk2d; i++)
        {
            const FieldClass1530C0* record = records + i;
            if (!record->unk08_0)
            {
                u32 word = record->unk00;
                u32 size = record->rounded_unk04();
                func_00103B20(D_001B65E8, record->unk0c, size, 0x80000000, word, 0);
            }
        }
        unk15 = 10;
        break;
    }
    case 10:
        break;
    case 9:
        if (field_records_blocked())
        {
            break;
        }
    default:
    {
        for (s32 i = 0; i < unk2d; i++)
        {
            FieldClass1530C0* record = records + i;
            if (record->rounded_unk04())
            {
                result = 1;
                break;
            }
        }
        for (s32 i = 0; i < unk24; i++)
        {
            records[i].func_0023AD00();
        }
        unk15 = 0;
        unk2e = 0;
        break;
    }
    }
    if (result != 1)
    {
        for (s32 i = 0; i < unk2d; i++)
        {
            FieldClass1530C0* record = records + i;
            if (record->rounded_unk04())
            {
                result = 2;
                break;
            }
        }
    }
    return result;
}

/**
 * @brief Advance the loader record release state.
 * @return One after releasing the loader, otherwise zero.
 */
s32 FieldClass150150::func_001DF640()
{
    switch (unk15)
    {
    case 1:
    {
        FieldClass1530C0* record = unk1c;
        for (s32 i = 0; i < unk2d; i++, record++)
        {
            const FieldClass1530C0* entry = record;
            if (!entry->unk08_0)
            {
                u32 word = entry->unk00;
                u32 size = entry->rounded_unk04();
                func_00103B20(D_001B65E8, entry->unk0c, size, 0x80000000, word, 0);
            }
        }
        unk15 = 7;
        break;
    }
    case 9:
    case 10:
        unk15 = 7;
        break;
    case 7:
        break;
    default:
        func_001DD7B0();
        return 1;
    }
    return 0;
}

/**
 * @brief Release each record in the loader's array.
 */
void FieldClass150150::func_001E68D0()
{
    for (s32 index = 0; index < unk24; index++)
    {
        unk1c[index].func_0023AD00();
    }
}

/**
 * @brief Mark a record request as ready to advance.
 * @param arg Callback argument; unused.
 */
void FieldClass150150::func_001DDB30(void* arg)
{
    if (!unk30_1)
    {
        func_00121FE0(0);
        unk30_1 = 1;
    }
}

/**
 * @brief Initialize and append the next record for the requested key and mode.
 * @param object Loader owning the record array and append index.
 * @param key Key identifying the requested resident resource.
 * @param mode Request mode to store in the record.
 * @return Appended record, or null when the record array is full.
 */
extern "C" FieldClass1530C0* func_001E69A0(FieldClass150150* object, s32 key, u8 mode)
{
    if (object->unk2d >= object->unk24)
    {
        return 0;
    }
    FieldClass1530C0* record = object->unk1c + object->unk2d;
    record->unk0c = -1;
    record->unk04 = 0;
    record->unk10 = 0;
    record->unk16_0 = 0;
    record->unk16_1 = 1;
    record->unk08_0 = 0;
    record->unk16_2 = 0;
    record->unk14 = 0;
    record->unk15 = 0;
    object->unk1c[object->unk2d].unk0c = key;
    object->unk1c[object->unk2d].set_capacity(func_0011C8C0(D_001B65E4, object->unk1c[object->unk2d].unk0c));
    object->unk1c[object->unk2d].unk14 = object->unk2d;
    object->unk1c[object->unk2d].unk15 = mode;
    object->unk2d++;
    return object->unk1c + (object->unk2d - 1);
}

/**
 * @brief Allocate an aligned buffer with up to eight recovery attempts.
 * @param owner Loader attached to the resource list.
 * @param size Requested buffer size in bytes.
 * @param mode Nonzero for the library allocator, zero for the resident allocator.
 * @return Allocated buffer, or null when allocation or recovery fails.
 */
void* func_001E6B40(FieldClass150070* owner, u32 size, s32 mode)
{
    FieldClass1530D0* manager = static_cast<FieldClass1530D0*>(static_cast<LibClass178DD0*>(owner->unk10));
    for (s32 attempt = 0; attempt < 8; attempt++)
    {
        void* result;
        if (mode)
        {
            func_00433AA0();
            result = func_00433880(size, 0x80);
        }
        else
        {
            result = func_00139700(0x80, size);
        }
        if (result)
        {
            return result;
        }
        if (manager->LibClass178DD0::unk0c == 1 || !func_0023AEB0(manager, owner))
        {
            break;
        }
    }
    return 0;
}

// Compiler-generated this-adjustment thunk; needs recovered classes.
