#include "include_asm.h"
#include "overlays/1067-00/text_001E1590.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "sdk/main/libkernl_00121940.h"
#include "sdk/main/libc_guess_00137290.h"
#include "overlays/lib/text_00429B00.h"
#include "main/resident_0010A0E0.h"
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


/**
 * @brief Report this object's default list kind.
 * @return Always 4.
 */
s32 FieldResourceRequestHandler::get_default_list_kind()
{
    return 4;
}

void FieldResourceRequestHandler::func_001DD7B0()
{
    resident_enqueue_object(g_resident_release_queues, this);
}

/**
 * @brief Cancel listed kind-eight loaders, initialize the request, and append its new loader.
 * @param handler Request handler receiving completion.
 * @param file_key File key to request.
 * @param mode One decodes into the shared buffer first; other values retain the completed loader.
 * @return Created loader, or null when allocation fails.
 */
FieldKeyedResourceLoader* field_start_keyed_resource_request(FieldResourceRequestHandler* handler, s32 file_key, u8 mode)
{
    field_request_loader_removal(static_cast<FieldResourceLoaderList*>(D_001B6430->context->unk30), 8);
    handler->notification_pending = 1;
    handler->file_key = file_key;
    handler->unk1c = 0;
    handler->request_mode = mode;

    if (mode == 1)
    {
        handler->unk1e = 0;
    }
    else
    {
        handler->unk1e = 1;
        handler->unk20 = 1;
    }

    handler->request_loader = new(0) FieldKeyedResourceLoader(handler->file_key);

    if (!handler->request_loader)
    {
        return 0;
    }

    handler->request_loader->completion_callback = static_cast<FieldClass1DD400*>(handler);
    static_cast<FieldResourceLoaderList*>(D_001B6430->context->unk30)->append_node(handler->request_loader, -1);
    return handler->request_loader;
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
void FieldResourceRequestHandler::update()
{
    FieldResourceLoaderList* manager = static_cast<FieldResourceLoaderList*>(D_001B6430->context->unk30);
    FieldClass150060* node = reinterpret_cast<FieldClass150060*>(&static_cast<LibClass178DD0&>(*manager));
    bool found = false;
    if (unk1c != 1 && (unk1c != 0 || request_mode != 1 || unk1e != 1))
    {
        s32 key = file_key;
        if (key > 0 && notification_pending == 1)
        {
            for (;;)
            {
                node = node->unk08;
                if (null_node(node) || static_cast<void*>(&static_cast<LibClass178DD0&>(*manager)) == node)
                {
                    break;
                }
                FieldKeyedResourceLoader* loader = static_cast<FieldKeyedResourceLoader*>(node);
                if (loader->get_load_kind() == 8 && key == loader->file_key)
                {
                    lib_object_detach_owner(loader);
                    manager->insert(loader);
                    found = true;
                    break;
                }
            }
            if (found == false)
            {
                unk9c = new(0) FieldKeyedResourceLoader(key);
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
s32 FieldClass153E30::on_resource_loaded(void* buffer)
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
    return slots->allocations[index] != 0;
}
/**
 * @brief Test whether the resource allocation is attached.
 * @param slots Buffer owner.
 * @return True when attached.
 */
static inline bool field_has_resource(const FieldBufferSlots* slots)
{
    return slots->block_chain_allocation != 0;
}
/**
 * @brief Test whether an aligned buffer slot is occupied.
 * @param slots Buffer owner.
 * @param index Slot index.
 * @return True when occupied.
 */
static inline bool field_has_slot_buffer(const FieldBufferSlots* slots, s32 index)
{
    return slots->buffer_allocations[index] != 0;
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
static inline s32 field_decode_resource(FieldResourceLoader* loader, u8* allocation, s32 index)
{
    ResidentResourceHeader* source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
    return resident_decode_resource_block(g_resident_resource_decoder, source, field_aligned_buffer(allocation), index);
}

/**
 * @brief Fill missing resource slots, retrying allocations on the alternate heap.
 * @param loader Completed record loader.
 * @return 1 when loading completes, or 0 when the loader or decoding fails.
 */
s32 FieldResourceRequestHandler::func_001E1830(FieldResourceLoader* loader)
{
    if (!loader)
    {
        return 0;
    }
    bool present_1 = field_has_allocation(buffer_slots, 0);
    if (!present_1)
    {
        u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
            reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 1, 1);
        if (!allocation)
        {
            void* previous_heap = resident_exchange_allocation_heap(0);
            allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 1, 1);
            resident_exchange_allocation_heap(previous_heap);
        }
        if (!allocation || !field_decode_resource(loader, allocation, 1))
        {
            resident_find_resource_block(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 1);
            field_decode_resource(loader, allocation, 1);
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = field_attach_allocation(buffer_slots, allocation, 0);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    bool present_2 = field_has_allocation(buffer_slots, 11);
    if (!present_2)
    {
        u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
            reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 2, 1);
        if (!allocation)
        {
            void* previous_heap = resident_exchange_allocation_heap(0);
            allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 2, 1);
            resident_exchange_allocation_heap(previous_heap);
        }
        if (!allocation || !field_decode_resource(loader, allocation, 2))
        {
            resident_find_resource_block(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 2);
            field_decode_resource(loader, allocation, 2);
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = field_attach_allocation(buffer_slots, allocation, 11);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    for (s32 slot = 0, index = 3; index < 11; index++, slot++)
    {
        bool present = field_has_allocation(buffer_slots, slot + 1);
        if (!present)
        {
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), index, 1);
            if (!allocation)
            {
                void* previous_heap = resident_exchange_allocation_heap(0);
                allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), index, 1);
                resident_exchange_allocation_heap(previous_heap);
            }
            if (!allocation || !field_decode_resource(loader, allocation, index))
            {
                resident_find_resource_block(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), index);
                field_decode_resource(loader, allocation, index);
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, slot + 1);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    bool present_11 = field_has_allocation(buffer_slots, 12);
    if (!present_11)
    {
        u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
            reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 11, 1);
        if (!allocation)
        {
            void* previous_heap = resident_exchange_allocation_heap(0);
            allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 11, 1);
            resident_exchange_allocation_heap(previous_heap);
        }
        if (!allocation || !field_decode_resource(loader, allocation, 11))
        {
            resident_find_resource_block(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 11);
            field_decode_resource(loader, allocation, 11);
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = field_attach_allocation(buffer_slots, allocation, 12);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    bool resource_present = field_has_resource(buffer_slots);
    if (!resource_present)
    {
        FieldResourceRecord* source;
        FieldResourceRequest* record = loader->requests;
        source = reinterpret_cast<FieldResourceRecord*>(record->buffer_address());
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
        u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
            reinterpret_cast<ResidentResourceHeader*>(record->buffer_address()), 12, 1);
        if (!allocation)
        {
            void* previous_heap = resident_exchange_allocation_heap(0);
            allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 12, 1);
            resident_exchange_allocation_heap(previous_heap);
        }
        if (!allocation || !field_decode_resource(loader, allocation, 12))
        {
            resident_find_resource_block(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 12);
            field_decode_resource(loader, allocation, 12);
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = field_attach_resource_chain(buffer_slots, allocation, size);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    s32 resource_index;
    for (s32 slot = 0; slot < 3; slot++)
    {
        bool present = field_has_slot_buffer(buffer_slots, slot);
        if (!present)
        {
            resource_index = slot + 13;
            FieldResourceRecord* source;
            FieldResourceRequest* record = loader->requests;
            source = reinterpret_cast<FieldResourceRecord*>(record->buffer_address());
            s32 size = field_resource_size(source, resource_index);
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(record->buffer_address()), resource_index, 1);
            if (!allocation)
            {
                void* previous_heap = resident_exchange_allocation_heap(0);
                allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), resource_index, 1);
                resident_exchange_allocation_heap(previous_heap);
            }
            if (!allocation || !field_decode_resource(loader, allocation, resource_index))
            {
                resident_find_resource_block(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), resource_index);
                field_decode_resource(loader, allocation, resource_index);
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_buffer_slot(buffer_slots, allocation, size, slot);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    buffer_slots->unk140 = 1;
    s32 index;
    u8* allocation;
    void* previous_heap;
    s32 slot;
    for (slot = 0, index = 16; index < 24; index++, slot++)
    {
        bool present = field_has_allocation(buffer_slots, slot + 49);
        if (!present)
        {
            allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), index, 1);
            if (!allocation)
            {
                previous_heap = resident_exchange_allocation_heap(0);
                allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), index, 1);
                resident_exchange_allocation_heap(previous_heap);
            }
            if (!allocation || !field_decode_resource(loader, allocation, index))
            {
                resident_find_resource_block(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), index);
                field_decode_resource(loader, allocation, index);
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, slot + 49);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    for (s32 slot = 0; slot < 2; slot++)
    {
        bool present = field_has_allocation(buffer_slots, slot + 9);
        if (!present)
        {
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), slot + 24, 1);
            if (!allocation)
            {
                void* previous_heap = resident_exchange_allocation_heap(0);
                allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), slot + 24, 1);
                resident_exchange_allocation_heap(previous_heap);
            }
            if (!allocation || !field_decode_resource(loader, allocation, slot + 24))
            {
                resident_find_resource_block(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), slot + 24);
                field_decode_resource(loader, allocation, slot + 24);
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, slot + 9);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    for (s32 slot = 0; slot < 2; slot++)
    {
        bool present = field_has_allocation(buffer_slots, slot + 57);
        if (!present)
        {
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), slot + 26, 1);
            if (!allocation)
            {
                void* previous_heap = resident_exchange_allocation_heap(0);
                allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), slot + 26, 1);
                resident_exchange_allocation_heap(previous_heap);
            }
            if (!allocation || !field_decode_resource(loader, allocation, slot + 26))
            {
                resident_find_resource_block(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), slot + 26);
                field_decode_resource(loader, allocation, slot + 26);
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, slot + 57);
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
s32 FieldResourceRequestHandler::func_001E2E40(FieldResourceLoader* loader)
{
    if (!loader)
    {
        return 0;
    }
    {
        bool present = field_has_allocation(buffer_slots, 0);
        if (!present)
        {
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 1, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
            if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), 1))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, 0);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    {
        bool present = field_has_allocation(buffer_slots, 11);
        if (!present)
        {
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 2, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
            if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), 2))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, 11);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    {
        bool present = field_has_allocation(buffer_slots, 13);
        if (!present)
        {
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 3, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
            if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), 3))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, 13);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    bool resource_present = field_has_resource(buffer_slots);
    if (!resource_present)
    {
        FieldResourceRecord* source;
        FieldResourceRequest* record = loader->requests;
        source = reinterpret_cast<FieldResourceRecord*>(record->buffer_address());
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
        u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
            reinterpret_cast<ResidentResourceHeader*>(record->buffer_address()), 4, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
        if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), 4))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = field_attach_resource_chain(buffer_slots, allocation, size);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    for (s32 slot = 0; slot < 38; slot++)
    {
        u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
            reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), slot + 5, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
        if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), slot + 5))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = field_attach_allocation(buffer_slots, allocation, (u8)(slot + 21));
        if (!attached)
        {
            delete[] allocation;
        }
    }
    {
        bool present = field_has_allocation(buffer_slots, 14);
        if (!present)
        {
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 43, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
            if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), 43))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, 14);
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
s32 FieldResourceRequestHandler::func_001E3580(FieldResourceLoader* loader)
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
            bool present = field_has_allocation(buffer_slots, index + 15);
            if (!present)
            {
                u16 resource_index = index + 1;
                u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), resource_index, 1);
                ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
                if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), resource_index))
                {
                    if (allocation)
                    {
                        delete allocation;
                    }
                    return 0;
                }
                u8 attached = field_attach_allocation(buffer_slots, allocation, index + 15);
                if (!attached)
                {
                    delete[] allocation;
                }
            }
        }
        else
        {
            s32 slot = secondary_index + 59;
            bool present = field_has_allocation(buffer_slots, slot);
            if (!present)
            {
                u16 resource_index = index + 1;
                u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                    reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), resource_index, 1);
                ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
                if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), resource_index))
                {
                    if (allocation)
                    {
                        delete allocation;
                    }
                    return 0;
                }
                u8 attached = field_attach_allocation(buffer_slots, allocation, slot);
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
        bool present = field_has_allocation(buffer_slots, index + 23);
        if (!present)
        {
            u16 resource_index = index + 11;
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), resource_index, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
            if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), resource_index))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, index + 23);
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
s32 FieldResourceRequestHandler::func_001E39A0(FieldResourceLoader* loader)
{
    if (!loader)
    {
        return 0;
    }
    bool present = field_has_allocation(buffer_slots, 11);
    if (!present)
    {
        u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 1, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
        if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), 1))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = field_attach_allocation(buffer_slots, allocation, 11);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    for (s32 slot = 0; slot < 8; slot++)
    {
        bool present = field_has_allocation(buffer_slots, slot + 1);
        if (!present)
        {
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), slot + 2, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
            if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), slot + 2))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, slot + 1);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    bool resource_present = field_has_resource(buffer_slots);
    if (!resource_present)
    {
        FieldResourceRecord* source;
        FieldResourceRequest* record = loader->requests;
        source = reinterpret_cast<FieldResourceRecord*>(record->buffer_address());
        s32 size = field_resource_size(source, 10);
        u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(record->buffer_address()), 10, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
        if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), 10))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = field_attach_resource_chain(buffer_slots, allocation, size);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    s32 index;
    for (s32 slot = 0; slot < 3; slot++)
    {
        bool present = field_has_slot_buffer(buffer_slots, slot);
        if (!present)
        {
            index = slot + 11;
            FieldResourceRecord* source;
            FieldResourceRequest* record = loader->requests;
            source = reinterpret_cast<FieldResourceRecord*>(record->buffer_address());
            s32 size = field_resource_size(source, index);
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(record->buffer_address()), index, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
            if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), index))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_buffer_slot(buffer_slots, allocation, size, slot);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    buffer_slots->unk140 = 1;
    for (s32 slot = 0; slot < 2; slot++)
    {
        bool present = field_has_allocation(buffer_slots, slot + 9);
        if (!present)
        {
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), slot + 14, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
            if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), slot + 14))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, slot + 9);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    for (s32 slot = 0; slot < 10; slot++)
    {
        bool present = field_has_allocation(buffer_slots, slot + 49);
        if (!present)
        {
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), slot + 16, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
            if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), slot + 16))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, slot + 49);
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
s32 FieldResourceRequestHandler::func_001E4220(FieldResourceLoader* loader)
{
    if (!loader)
    {
        return 0;
    }
    bool present = field_has_allocation(buffer_slots, 0);
    if (!present)
    {
        u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
            reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 1, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
        if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), 1))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = field_attach_allocation(buffer_slots, allocation, 0);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    bool second_present = field_has_allocation(buffer_slots, 11);
    if (!second_present)
    {
        u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
            reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), 2, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
        if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), 2))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = field_attach_allocation(buffer_slots, allocation, 11);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    for (s32 slot = 0, index = 3; index < 11; index++, slot++)
    {
        bool present = field_has_allocation(buffer_slots, slot + 1);
        if (!present)
        {
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), index, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
            if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), index))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, slot + 1);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    bool resource_present = field_has_resource(buffer_slots);
    if (!resource_present)
    {
        FieldResourceRecord* source;
        FieldResourceRequest* record = loader->requests;
        source = reinterpret_cast<FieldResourceRecord*>(record->buffer_address());
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
        u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
            reinterpret_cast<ResidentResourceHeader*>(record->buffer_address()), 11, 1);
        ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
        if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), 11))
        {
            if (allocation)
            {
                delete allocation;
            }
            return 0;
        }
        u8 attached = field_attach_resource_chain(buffer_slots, allocation, size);
        if (!attached)
        {
            delete[] allocation;
        }
    }
    for (s32 slot = 0; slot < 2; slot++)
    {
        bool present = field_has_allocation(buffer_slots, slot + 9);
        if (!present)
        {
            s32 index = slot + 12;
            u8* allocation = resident_allocate_decode_buffer(g_resident_resource_decoder,
                reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address()), index, 1);
            ResidentResourceHeader* decoded_source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
            if (!resident_decode_resource_block(g_resident_resource_decoder, decoded_source, field_aligned_buffer(allocation), index))
            {
                if (allocation)
                {
                    delete allocation;
                }
                return 0;
            }
            u8 attached = field_attach_allocation(buffer_slots, allocation, slot + 9);
            if (!attached)
            {
                delete[] allocation;
            }
        }
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", decode_request_resources__27FieldResourceRequestHandlerFP19FieldResourceLoader);

/**
 * @brief Notify the request receiver when a completed buffer is present.
 * @param object Request owner.
 * @param buffer Completed buffer.
 */
static inline void notify_request_buffer(FieldResourceRequestHandler* object, u8* buffer)
{
    if (buffer)
    {
        FieldClass153E30* receiver = object->receiver;
        receiver->on_resource_loaded(buffer);
        object->notification_pending = 0;
    }
}

/**
 * @brief Pass a completed request buffer to its receiver, then release its loader.
 */
void FieldResourceRequestHandler::deliver_completed_request()
{
    u8* buffer = decode_request_resources(completed_loader);

    if (buffer)
    {
        notify_request_buffer(this, buffer);
        delete[] buffer;
        FieldResourceLoader* loader = completed_loader;

        if (loader)
        {
            lib_object_detach_owner(loader);
            loader->func_001DD7B0();
        }
        FlushCache(0);
    }
}

/**
 * @brief Dispatch a completed request buffer or retain its loader for later processing.
 * @param arg Completed record loader.
 */
void FieldResourceRequestHandler::func_001DDB30(void* arg)
{
    if (request_mode == 1)
    {
        FieldResourceLoader* loader = static_cast<FieldResourceLoader*>(arg);
        ResidentResourceHeader* source = reinterpret_cast<ResidentResourceHeader*>(loader->requests->buffer_address());
        void* destination = D_001B5FC0[0];

        if (destination)
        {
            resident_decode_resource_block(g_resident_resource_decoder, source, destination, 0);
            FlushCache(0);
            func_001011B0(func_10D8E0(), destination, 4, source->decoded_size);
        }

        request_mode = 0;

        if (loader)
        {
            lib_object_detach_owner(loader);
            loader->func_001DD7B0();
        }

        unk20 = 1;
        unk1e = 1;

        if (next_file_key)
        {
            field_start_keyed_resource_request(this, next_file_key, next_request_mode);
        }
    }
    else
    {
        completed_loader = static_cast<FieldResourceLoader*>(arg);
        unk1c = 1;
    }
}

/**
 * @brief Store the file key and mode for the request that follows direct-buffer decoding.
 * @param handler Request handler retaining the next request.
 * @param file_key Next file key; zero leaves no request queued.
 * @param mode Mode passed to the next keyed request.
 */
void field_set_next_resource_request(FieldResourceRequestHandler* handler, u32 file_key, u8 mode)
{
    handler->next_file_key = file_key;
    handler->next_request_mode = mode;
}

/** @brief Release the owned buffers and destroy the request handler. */
FieldResourceRequestHandler::~FieldResourceRequestHandler()
{
    s32 i;

    for (i = 0; i < 10; i++)
    {
        if (owned_buffers[i])
        {
            delete[] owned_buffers[i];
            owned_buffers[i] = 0;
        }
    }
}

/**
 * @brief Set the key to -1 and clear the request state, parallel arrays, and loader pointers.
 */
FieldResourceRequestHandler::FieldResourceRequestHandler()
{
    file_key = -1;
    request_mode = 0;
    unk1c = 0;
    unk1e = 0;
    notification_pending = 0;
    unk20 = 0;
    unk24 = 0;
    unk28 = 0;
    receiver = 0;
    unk38 = 0;
    completed_loader = 0;
    next_file_key = 0;
    next_request_mode = 0;
    unk40 = 0;

    for (s32 index = 0; index < 10; index++)
    {
        owned_buffers[index] = 0;
        unk6c[index] = 0;
    }
    buffer_slots = 0;
    request_loader = 0;
    unk9c = 0;
}

/**
 * @brief Queue the loader on the resident object queue without detaching it.
 */
void FieldKeyedResourceLoader::func_001DD7B0()
{
    resident_enqueue_object(g_resident_release_queues, this);
}

/**
 * @brief Allocate storage for the next keyed request and advance its loader state.
 * @param cancel_request One requests cancellation; zero advances reads.
 */
void FieldKeyedResourceLoader::update_requests(s32 cancel_request)
{
    advance_requests();

    if (request_state == 0)
    {
        if (cancel_request == 0 && !field_records_blocked())
        {
            if (current_request == 0)
            {
                if (start_delay)
                {
                    start_delay--;
                    return;
                }
                u8 state = D_001B643C->unk10->unk18;

                if (state == 12 || state == 7)
                {
                    FieldResourceLoaderList* manager = static_cast<FieldResourceLoaderList*>(D_001B6430->context->unk30);
                    FieldClass150060* node = reinterpret_cast<FieldClass150060*>(&manager->sentinel);
                    u8 busy = 0;

                    for (;;)
                    {
                        node = node->unk08;

                        if (reinterpret_cast<FieldClass150060*>(&manager->sentinel) == node)
                        {
                            break;
                        }
                        FieldResourceLoadTask* loader = static_cast<FieldResourceLoadTask*>(node);

                        if (this != loader && (loader->get_load_kind() == 1 || loader->get_load_kind() == 2) && loader->poll_request_release() == 1)
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
            u32 allocation_size = requests[current_request].byte_capacity + 0x80;
            buffer_allocation = malloc_guess(allocation_size + 0x7D000);

            if (buffer_allocation)
            {
                free_guess(buffer_allocation);
                buffer_allocation = new(0) u8[(allocation_size + 0x7FF) & ~0x7FF];
            }
            else
            {
                FieldResourceLoaderList* manager = static_cast<FieldResourceLoaderList*>(D_001B6430->context->unk30);
                FieldClass150060* node = reinterpret_cast<FieldClass150060*>(&manager->sentinel);
                u8 busy = 0;

                for (;;)
                {
                    node = node->unk08;

                    if (reinterpret_cast<FieldClass150060*>(&manager->sentinel) == node)
                    {
                        break;
                    }
                    FieldResourceLoadTask* loader = static_cast<FieldResourceLoadTask*>(node);

                    if (this != loader && (loader->get_load_kind() == 1 || loader->get_load_kind() == 2))
                    {
                        if (loader->poll_request_release() == 1)
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
            FieldResourceRequest* record = &requests[current_request];
            record->buffer_base = (u32)buffer_allocation;
            record->unk08_0 = 0;
            start_current_read();
        }
    }
    else
    {
        FieldResourceLoader::update_requests(cancel_request);
    }
}

/**
 * @brief Advance a completed keyed request and notify its owner when the batch finishes.
 */
void FieldKeyedResourceLoader::advance_requests()
{
    if (!completion_ready)
    {
        return;
    }

    if (request_state == 1)
    {
        if (field_records_blocked())
        {
            return;
        }

        for (; current_request < request_count; )
        {
            current_request++;

            if (!requests[current_request].unk16_0)
            {
                break;
            }
        }

        if (current_request >= request_count)
        {
            request_state = 5;

            if (completion_callback)
            {
                completion_callback->func_001DDB30(this);
            }
        }
        else
        {
            request_state = 0;
        }
    }

    completion_ready = 0;
}

/**
 * @brief Flush the cache once for this loader.
 * @param arg Unused secondary-interface argument.
 */
void FieldKeyedResourceLoader::func_001DDB30(void* arg)
{
    if (!completion_ready)
    {
        FlushCache(0);
        completion_ready = 1;
    }
}

/**
 * @brief Reset request slots, restore the start delay, and clear the initial slot index.
 * Existing buffer addresses are cleared without freeing their storage.
 */
void FieldKeyedResourceLoader::reset_requests()
{
    s32 i;

    if (requests)
    {
        for (i = 0; i < request_capacity; i++)
        {
            FieldResourceRequest* record = &requests[i];
            record->file_key = -1;
            record->buffer_base = 0;
            record->request_address = 0;
            record->unk16_0 = 0;
            record->unk16_1 = 1;
            record->unk08_0 = 0;
            record->unk16_2 = 0;
            record->slot_index = 0;
            record->kind = 0;
        }
    }

    completion_callback = 0;
    unk2f = 0;
    request_count = 0;
    current_request = 0;
    load_kind = 8;
    unk2f = 0;
    start_delay = 2;
    initial_request_slot = -1;
}

/**
 * @brief Detach the keyed loader, then destroy its record-loader base.
 */
FieldKeyedResourceLoader::~FieldKeyedResourceLoader()
{
    lib_object_detach_owner(this);
}

/**
 * @brief Create the keyed loader's record array and prepare its first record.
 * @param key Request key.
 */
FieldKeyedResourceLoader::FieldKeyedResourceLoader(s32 key)
{
    reset_requests();

    if (unk30_0)
    {
        if (requests)
        {
            delete[] requests;
        }

        requests = new(0) FieldResourceRequest[50];
    }
    else
    {
        void* heap = resident_exchange_allocation_heap(D_001B6430->context->unk6c);

        if (requests)
        {
            delete[] requests;
        }

        requests = new(0) FieldResourceRequest[50];
        resident_exchange_allocation_heap(heap);
    }
    request_capacity = 50;
    file_key = key;
    FieldResourceRequest* record = field_append_resource_request(this, file_key, 0);
    initial_request_slot = record->slot_index;
    resident_get_resource_size(g_resource_archive, file_key);
    u32 aligned_size = (resident_get_resource_size(g_resource_archive, file_key) + 0x7FF) & ~0x7FF;
    record->set_capacity(aligned_size);
}

/**
 * @brief Reset request slots, counts, and the completion callback.
 * Existing buffer addresses are cleared without freeing their storage.
 */
void FieldResourceLoader::reset_requests()
{
    s32 i;

    if (requests)
    {
        for (i = 0; i < request_capacity; i++)
        {
            FieldResourceRequest* record = &requests[i];
            record->file_key = -1;
            record->buffer_base = 0;
            record->request_address = 0;
            record->unk16_0 = 0;
            record->unk16_1 = 1;
            record->unk08_0 = 0;
            record->unk16_2 = 0;
            record->slot_index = 0;
            record->kind = 0;
        }
    }

    completion_callback = 0;
    unk2f = 0;
    request_count = 0;
    current_request = 0;
}

/**
 * @brief Start the request for the current counted record.
 */
void FieldResourceLoader::start_current_read()
{
    FieldResourceRequest* record = &requests[current_request];

    if (record->buffer_address())
    {
        FieldClass1DD400* owner = this;
        u32 submitted_byte_count = record->byte_capacity;
        resident_queue_resource_request(g_resource_queue, record->file_key, (void*)record->buffer_address(), 0x80000000, request_priority, owner, submitted_byte_count, 0, 1);
        u32 byte_count = record->byte_capacity;
        u32 buffer_address = record->buffer_address();
        record->request_address = resident_find_resource_request(g_resource_queue, record->file_key, buffer_address, 0x80000000, byte_count, 0);
        request_state = 1;
        callback_ready = 0;
    }
}

/**
 * @brief Advance the current record request after its pending operation finishes.
 */
void FieldResourceLoader::advance_requests()
{
    if (!callback_ready)
    {
        return;
    }

    if (request_state == 1)
    {
        if (field_records_blocked())
        {
            return;
        }
        FieldResourceRequest* record = &requests[current_request];
        u32 byte_count = record->byte_capacity;
        u32 buffer_address = record->buffer_address();

        if (resident_find_resource_request(g_resource_queue, record->file_key, buffer_address, 0x80000000, byte_count, 0))
        {
            return;
        }

        for (; current_request < request_count; )
        {
            current_request++;

            if (!requests[current_request].unk16_0)
            {
                break;
            }
        }

        if (current_request >= request_count)
        {
            request_state = 5;
        }
        else
        {
            request_state = 0;
        }
    }

    callback_ready = 0;
}

/**
 * @brief Release record storage and destroy the owned array.
 */
FieldResourceLoader::~FieldResourceLoader()
{
    if (requests)
    {
        release_requests();
        delete[] requests;
        requests = 0;
    }
}

/**
 * @brief Advance record requests or handle a requested cancellation.
 * @param cancel_request One requests cancellation; zero advances reads.
 */
void FieldResourceLoader::update_requests(s32 cancel_request)
{
    switch (request_state)
    {
    case 0:
        if (!cancel_request && requests)
        {
            FlushCache(0);
            FieldResourceRequest* record = &requests[current_request];
            void* result = field_allocate_request_buffer(this, (record->byte_capacity + 0x7FF) & ~0x7FF, 1);

            if (result)
            {
                record->buffer_base = (u32)result;
                record->unk08_0 = 0;
                start_current_read();
            }
        }

        break;
    case 1:
        if (cancel_request == 1)
        {
            for (s32 i = 0; i < request_count; i++)
            {
                FieldResourceRequest* record = &requests[i];
                u32 byte_count = record->byte_capacity;
                u32 buffer_address = record->buffer_address();
                resident_cancel_resource_requests(g_resource_queue, record->file_key, buffer_address, 0x80000000, byte_count, 0);
            }

            request_state = 9;
        }
        else
        {
            FieldResourceRequest* record = &requests[current_request];
            u32 byte_count = record->byte_capacity;
            u32 buffer_address = record->buffer_address();

            if (!resident_find_resource_request(g_resource_queue, record->file_key, buffer_address, 0x80000000, byte_count, 0) && !field_records_blocked())
            {
                func_001DDB30(0);
            }
        }

        break;
    case 9:
        if (!cancel_request)
        {
            start_current_read();
        }

        break;
    case 10:
    {
        bool done = true;
        FieldResourceRequest* records = requests;

        for (s32 i = 0; i < request_count; i++)
        {
            FieldResourceRequest* record = &records[i];
            u32 byte_count = record->byte_capacity;
            u32 buffer_address = record->buffer_address();
            record->request_address = resident_find_resource_request(g_resource_queue, record->file_key, buffer_address, 0x80000000, byte_count, 0);

            if (record->request_address)
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
            for (s32 i = 0; i < request_capacity; i++, records++)
            {
                records->release_buffer();
            }

            current_request = 0;
            request_state = 0;
        }

        break;
    }
    case 7:
    {
        bool done = true;
        FieldResourceRequest* record = requests;

        for (s32 i = 0; i < request_count; i++, record++)
        {
            u32 byte_count = record->byte_capacity;
            u32 buffer_address = record->buffer_address();
            record->request_address = resident_find_resource_request(g_resource_queue, record->file_key, buffer_address, 0x80000000, byte_count, 0);

            if (record->request_address)
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
    advance_requests();
}

/**
 * @brief Finish or cancel pending record requests and report their remaining state.
 * @return One when cancelled storage remains, two when requests remain, or zero otherwise.
 */
s32 FieldResourceLoader::poll_request_release()
{
    s32 result = 0;
    FieldResourceRequest* records = requests;

    switch (request_state)
    {
    case 1:
    {
        for (s32 i = 0; i < request_count; i++)
        {
            const FieldResourceRequest* record = records + i;

            if (!record->unk08_0)
            {
                u32 byte_count = record->byte_capacity;
                u32 buffer_address = record->buffer_address();
                resident_cancel_resource_requests(g_resource_queue, record->file_key, buffer_address, 0x80000000, byte_count, 0);
            }
        }

        request_state = 10;
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
        for (s32 i = 0; i < request_count; i++)
        {
            FieldResourceRequest* record = records + i;

            if (record->buffer_address())
            {
                result = 1;
                break;
            }
        }

        for (s32 i = 0; i < request_capacity; i++)
        {
            records[i].release_buffer();
        }

        request_state = 0;
        current_request = 0;
        break;
    }
    }

    if (result != 1)
    {
        for (s32 i = 0; i < request_count; i++)
        {
            FieldResourceRequest* record = records + i;

            if (record->buffer_address())
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
s32 FieldResourceLoader::request_removal()
{
    switch (request_state)
    {
    case 1:
    {
        FieldResourceRequest* record = requests;

        for (s32 i = 0; i < request_count; i++, record++)
        {
            const FieldResourceRequest* entry = record;

            if (!entry->unk08_0)
            {
                u32 byte_count = entry->byte_capacity;
                u32 buffer_address = entry->buffer_address();
                resident_cancel_resource_requests(g_resource_queue, entry->file_key, buffer_address, 0x80000000, byte_count, 0);
            }
        }

        request_state = 7;
        break;
    }
    case 9:
    case 10:
        request_state = 7;
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
void FieldResourceLoader::release_requests()
{
    for (s32 index = 0; index < request_capacity; index++)
    {
        requests[index].release_buffer();
    }
}

/**
 * @brief Mark a record request as ready to advance.
 * @param arg Callback argument; unused.
 */
void FieldResourceLoader::func_001DDB30(void* arg)
{
    if (!callback_ready)
    {
        FlushCache(0);
        callback_ready = 1;
    }
}

/**
 * @brief Append a file-backed resource request when a slot remains.
 * @param loader Loader owning the request array.
 * @param file_key File key used to look up the resource size.
 * @param kind Resource kind stored in the request.
 * @return Appended request, or null when the array is full.
 */
extern "C" FieldResourceRequest* field_append_resource_request(FieldResourceLoader* loader, s32 file_key, u8 kind)
{
    if (loader->request_count >= loader->request_capacity)
    {
        return 0;
    }
    FieldResourceRequest* record = loader->requests + loader->request_count;
    record->file_key = -1;
    record->buffer_base = 0;
    record->request_address = 0;
    record->unk16_0 = 0;
    record->unk16_1 = 1;
    record->unk08_0 = 0;
    record->unk16_2 = 0;
    record->slot_index = 0;
    record->kind = 0;
    loader->requests[loader->request_count].file_key = file_key;
    loader->requests[loader->request_count].set_capacity(resident_get_resource_size(g_resource_archive, loader->requests[loader->request_count].file_key));
    loader->requests[loader->request_count].slot_index = loader->request_count;
    loader->requests[loader->request_count].kind = kind;
    loader->request_count++;
    return loader->requests + (loader->request_count - 1);
}

/**
 * @brief Allocate a 128-byte-aligned buffer, retrying after other loaders release storage.
 * @param loader Loader attached to the resource list.
 * @param size Requested buffer size in bytes.
 * @param mode Nonzero for the library allocator, zero for the resident allocator.
 * @return Allocated buffer, or null when allocation or recovery fails after at most eight attempts.
 */
void* field_allocate_request_buffer(FieldListObject* loader, u32 size, s32 mode)
{
    FieldResourceLoaderList* manager = static_cast<FieldResourceLoaderList*>(loader->owner);
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
            result = memalign_guess(0x80, size);
        }
        if (result)
        {
            return result;
        }
        if (manager->node_count == 1 || !field_reclaim_loader_buffers(manager, loader))
        {
            break;
        }
    }
    return 0;
}

// Compiler-generated this-adjustment thunk; needs recovered classes.
