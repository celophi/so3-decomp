#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "sdk/main/libkernl_00121940.h"
#include "sdk/main/libc_guess_00137290.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/1067-00/text_001DED80.h"
#include "overlays/1067-00/text_0022DC70.h"
#include "overlays/1067-00/text_00202240.h"
#include "overlays/1067-00/text_00207AF0.h"
#include "overlays/1067-00/text_002DBC50.h"
#include "overlays/1067-00/text_0021FB80.h"
#include "overlays/1067-00/text_0026EE10.h"
#include "overlays/lib/text_004AB8B0.h"


bool FieldClass154C10::func_00204420()
{
    ResidentContext* context = D_001B6430->context;
    if (!context->unk08->unkf5_5 || context->unkdd.unk7 || context->unkde_1)
    {
        return false;
    }
    return FieldClass150F90::func_00204420();
}

/**
 * @brief Detach the field object, then invoke its removal handler.
 * @param list Unused interface argument.
 * @param object Field object to detach and remove.
 */
void func_001DEDF0(void* list, void* object)
{
    lib_object_detach_owner(object);
    static_cast<FieldListObject*>(object)->func_001DD7B0();
}

FieldFlaggedListObject* func_001DEE30(FieldFlaggedListObject* list, s32 key, u32 mask)
{
    FieldFlaggedListObject* node = list;
    for (;;)
    {
        node = node->next;
        if (!node || list == node)
        {
            break;
        }
        if ((mask & node->unk78) && key == node->unk70)
        {
            return node;
        }
    }
    return 0;
}

void func_001DEE90(FieldFlaggedListObject* list)
{
    FieldFlaggedListObject* node = list;
    for (;;)
    {
        node = node->next;
        if (!node || list == node)
        {
            break;
        }
        if (node->unk78 & 8)
        {
            func_00234000(node);
        }
    }
}

void func_001DEF00(FieldFlaggedListObject* list)
{
    FieldFlaggedListObject* node = list;
    for (;;)
    {
        node = node->next;
        if (!node || list == node)
        {
            break;
        }
        if (node->unk78 & 8)
        {
            func_00233620(node);
        }
    }
}

/**
 * @brief Release listed objects, optionally preserving the focus object and clearing its track.
 * @param list Circular list sentinel; traversal also stops at a null link.
 * @param preserve_focus Nonzero to clear the focus object's track instead of releasing the object.
 */
void func_001DEF70(FieldClass150060* list, s32 preserve_focus)
{
    FieldClass150060* node = list->unk08;
    FieldClass151510* focus = static_cast<FieldClass151510*>(D_001B6430->context->unk18);
    for (;;)
    {
        FieldClass150060* current = node;
        if (!node || list == node)
        {
            break;
        }
        node = node->unk08;
        if (!preserve_focus || focus != current)
        {
            lib_object_detach_owner(current);
            static_cast<FieldListObject*>(current)->func_001DD7B0();
        }
        else if (focus->unk144)
        {
            focus->unk144->func_002DDA70();
        }
    }
}

/** @brief Clear the listed nodes and release both owned tracks. */
void FieldClass15B890::func_002DDA70()
{
    FieldClass15B950::func_002DDA70();
    if (unk90)
    {
        unk90->func_001DF230();
        unk90 = 0;
    }
}
/** @brief Destroy the keyframe object. */
FieldClass177C70::~FieldClass177C70()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", __ct__16FieldClass14FE30Fv);


void FieldClass150090::func_001DF220()
{
}

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF230__16FieldClass150090Fv);


s32 func_001DF2B0(const void* object)
{
    return 0;
}

s32 func_001DF2C0(const void* object)
{
    return 0;
}

s32 func_001DF2D0(const void* object)
{
    return 0;
}

s32 FieldClass150090::func_001DF2E0(s32 index, float* key, float* x, float* y, float* z) const
{
    return 0;
}

void func_001DF2F0(void* object)
{
}

void FieldClass150090::func_001DF300()
{
}

/**
 * @brief Report this object's default list kind.
 * @return Always 3.
 */
s32 FieldResourceLoadTask::get_default_list_kind()
{
    return 3;
}

void FieldResourceLoadTask::func_001DD7B0()
{
    lib_object_detach_owner(this);
    resident_enqueue_object(g_resident_release_queues, this);
}

u8 FieldResourceLoadTask::get_load_kind()
{
    return load_kind;
}

/** @brief Default update handler that performs no work. */
void FieldListObject::update()
{
}

void FieldClass1DD400::func_001DDB30(void* arg)
{
}

s32 FieldPreloadRequest::release_buffer()
{
    read_complete = 0;
    cancel_pending = 0;
    return FieldResourceRequest::release_buffer();
}

/**
 * @brief Report this object's default list kind.
 * @return Always 3.
 */
s32 FieldListObject::get_default_list_kind()
{
    return 3;
}

void FieldResourcePreloader::start_current_read()
{
    FieldPreloadRequest* record = &requests[current_request];
    if (record->buffer_address())
    {
        FieldClass1DD400* owner = this;
        u32 submitted_byte_count = record->byte_capacity;
        resident_queue_resource_request(g_resource_queue, record->file_key, record->buffer_address(), 0x80000000, request_priority, owner, submitted_byte_count, 0, 1);
        u32 byte_count = record->byte_capacity;
        u32 buffer_address = record->buffer_address();
        record->request_address = resident_find_resource_request(g_resource_queue, record->file_key, buffer_address, 0x80000000, byte_count, 0);
        request_state = 1;
        callback_ready = 0;
    }
}

FieldResourcePreloader::~FieldResourcePreloader()
{
    if (requests)
    {
        release_requests();
        delete[] requests;
        requests = 0;
    }
}

s32 FieldResourcePreloader::request_removal()
{
    switch (request_state)
    {
    case 1:
    {
        FieldPreloadRequest* record = requests;
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

void FieldResourcePreloader::release_requests()
{
    s32 i;
    for (i = 0; i < request_capacity; i++)
    {
        FieldPreloadRequest* record = &requests[i];
        record->release_buffer();
    }
}

void FieldResourcePreloader::func_001DDB30(void* arg)
{
    if (!callback_ready)
    {
        FlushCache(0);
        callback_ready = 1;
    }
}

void FieldClass14FEB0::func_001DFAE0()
{
    unk4c = 0.0f;
    FieldClass150090::func_001DFAE0();
}

s32 FieldClass14FEB0::func_001E1470(const float* x, const float* y, const float* z, float key)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return func_001E02C0(x, y, z, key);
}

s32 FieldClass14FEB0::func_001E14A0(s32 index, float key, const float* x, const float* y, const float* z)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return func_001E0220(index, key, x, y, z);
}

s32 FieldClass14FEB0::func_001E14D0(s32 index, float key, const float* x, const float* y, const float* z)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return func_001E0100(index, key, x, y, z);
}

void FieldClass14FEB0::func_001E1500(const float* x, const float* y, const float* z, float key)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    func_001E0080(x, y, z, key);
}

void FieldClass14FEB0::func_001DF300()
{
    float zero = 0.0f;
    func_001E1500(&zero, &zero, &zero, 0.0f);
}

void FieldClass14FEB0::func_001DFA30(float* out) const
{
    *out = unk50;
}

void FieldClass14FEB0::func_001DFA40(float* out) const
{
    FieldArrayEntry10* entries = unk04;
    if (entries)
    {
        *out = entries[unk20 - 1].unk04 - entries[0].unk04;
    }
}

FieldClass150090::~FieldClass150090()
{
    func_001DFD90();
}

void FieldClass150090::func_001DFAE0()
{
    unk04 = 0;
    unk2a_0_3 = 1;
    unk2a_4_7 = 1;
    unk22 = 0;
    unk20 = 0;
    unk24 = -1;
    unk18 = 0;
    unk26 = -1;
    unk28 = -1;
    unk2b_0 = 0;
    unk2b_1 = 0;
}

/**
 * @brief Replace the owned entry array and record its capacity, or zero capacity on failure.
 * @param count Number of entries to allocate.
 */
void FieldClass150090::func_001DFB70(s32 count)
{
    unk2b_1 = 0;
    delete[] unk04;
    unk04 = new(0) FieldArrayEntry10[count];
    unk22 = count;
    if (!unk04)
    {
        unk22 = 0;
    }
}

void FieldClass150090::func_001DFC10(s32 value)
{
    unk2a_0_3 = value;
    unk2b_0 = unk2a_0_3 == 4 || unk2a_4_7 == 4;
}

void FieldClass150090::func_001DFC70(s32 value)
{
    unk2a_4_7 = value;
    unk2b_0 = unk2a_0_3 == 4 || unk2a_4_7 == 4;
}

s32 FieldClass150090::func_001DFCD0() const
{
    return unk18;
}

s16 FieldClass150090::func_001DFCE0() const
{
    return unk20;
}

s16 FieldClass150090::func_001DFCF0() const
{
    return unk22;
}

s32 FieldClass150090::func_001DFD00(const float* x, const float* y, const float* z, float key)
{
    return 0;
}

s32 FieldClass150090::func_001DFD10(s32 index, float key, const float* x, const float* y, const float* z)
{
    return 0;
}

s32 FieldClass150090::func_001DFD20(s32 index, float key, const float* x, const float* y, const float* z)
{
    return 0;
}

void FieldClass150090::func_001DFD30(const float* x, const float* y, const float* z, float key)
{
}

float FieldClass150090::func_001DFD40() const
{
    return 0.0f;
}

void FieldClass150090::func_001DFD50(float key, float* out)
{
    *out = func_001E0380(key);
}

FieldArrayEntry10* FieldClass150090::func_001DFD80() const
{
    return unk04;
}

void FieldClass150090::func_001DFD90()
{
    if (!unk2b_1)
    {
        delete[] unk04;
    }
    unk04 = 0;
}

float FieldClass150090::func_001DFDE0(float value) const
{
    FieldArrayEntry10* entries = unk04;
    s32 last = unk20 - 1;
    float first = entries[0].unk00;
    float span = entries[last].unk00 - first;
    float cycles = (value - first) / span;
    s32 count;
    if (cycles < 0.0f)
    {
        cycles -= 1.0f;
    }
    count = cycles;
    if (count != 0)
    {
        return value - count * span;
    }
    return value;
}

/**
 * @brief Find the first entry with the requested sort value.
 * @param key Sort value to find.
 * @return The entry's first component, or zero when no entry matches.
 */
float FieldClass150090::func_001DFE70(float key)
{
    for (s32 index = 0; index < unk20; index++)
    {
        if (unk04[index].unk00 == key)
        {
            FieldArrayEntry10* entry = unk04 + index;
            return entry->unk04;
        }
    }
    return 0.0f;
}

float FieldClass150090::func_001DFED0() const
{
    s32 last;
    if (unk20 < 2)
    {
        return 0.0f;
    }
    last = unk20 - 1;
    return unk04[last].unk00 - unk04[0].unk00;
}

s32 FieldClass150090::func_001DFF20(float key) const
{
    s16 count = unk20;
    s32 i;
    for (i = 0; i < count; i++)
    {
        if (key == unk04[i].unk00)
        {
            return 1;
        }
    }
    return 0;
}

void FieldClass150090::func_001DFF70(s32 count, FieldArrayEntry10* entries)
{
    s32 last = count - 1;
    unk2b_1 = 1;
    unk04 = entries;
    unk22 = count;
    unk20 = count;
    unk1c = unk04[last].unk00 - unk04[0].unk00;
}

s32 FieldClass14FEB0::func_001DF2E0(s32 index, float* key, float* x, float* y, float* z) const
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= unk22)
    {
        return 0;
    }
    if (key)
    {
        *key = unk04[index].unk00;
    }
    if (x)
    {
        *x = unk04[index].unk04;
    }
    if (y)
    {
        *y = unk04[index].unk08;
    }
    if (z)
    {
        *z = unk04[index].unk0c;
    }
    return 1;
}

void FieldClass14FEB0::func_001E0080(const float* x, const float* y, const float* z, float key)
{
    func_001DFC10(6);
    unk08.unk04 = *x;
    unk08.unk08 = *y;
    unk08.unk0c = *z;
    unk08.unk00 = key;
}

s32 FieldClass14FEB0::func_001E0100(s32 index, float key, const float* x, const float* y, const float* z)
{
    s16 count;
    s32 i;
    if (unk04 == 0)
    {
        return 0;
    }
    count = unk20;
    if (index >= count)
    {
        return 0;
    }
    if (count >= unk22)
    {
        return 0;
    }
    for (i = count; i > index; i--)
    {
        unk04[i] = unk04[i - 1];
    }
    unk04[index].unk04 = *x;
    unk04[index].unk08 = *y;
    unk04[index].unk0c = *z;
    unk04[index].unk00 = key;
    if (index == unk20 - 1)
    {
        unk1c = key - unk04[0].unk00;
    }
    unk20++;
    return 1;
}

s32 FieldClass14FEB0::func_001E0220(s32 index, float key, const float* x, const float* y, const float* z)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (index >= unk22)
    {
        return 0;
    }
    unk04[index].unk04 = *x;
    unk04[index].unk08 = *y;
    unk04[index].unk0c = *z;
    unk04[index].unk00 = key;
    if (index == unk20 - 1)
    {
        unk1c = key - unk04[0].unk00;
    }
    return 1;
}

s32 FieldClass14FEB0::func_001E02C0(const float* x, const float* y, const float* z, float key)
{
    if (unk04 == 0)
    {
        return 0;
    }
    if (unk20 >= unk22)
    {
        return 0;
    }
    unk04[unk20].unk04 = *x;
    unk04[unk20].unk08 = *y;
    unk04[unk20].unk0c = *z;
    unk04[unk20].unk00 = key;
    unk1c = key - unk04[0].unk00;
    unk20++;
    return 1;
}

/**
 * @brief Evaluate the track with cached interpolation, wrapping and endpoint extrapolation.
 * @param key Sort value.
 * @return Evaluated value; updates the cached value and its scaled change.
 */
float FieldClass14FEB0::func_001E0380(float key)
{
    s32 lower;
    s32 upper;
    float wrapped_key;
    u8 extrapolate;
    float result;
    if (!unk04 || !unk20)
    {
        return 0.0f;
    }
    if (unk24 >= unk22)
    {
        unk24 = 0;
    }
    if (unk20 == 1 && (!(key < unk04[0].unk00) || unk2a_0_3 != 6))
    {
        return unk04[0].unk04;
    }
    extrapolate = 0;
    if (key < unk04[0].unk00 && unk2a_0_3 == 6)
    {
        upper = 0;
        wrapped_key = key;
        lower = -1;
    }
    else
    {
        wrapped_key = func_001E1230(reinterpret_cast<FieldEntryArrayObject*>(this), key);
        if (unk18)
        {
            if (unk2a_0_3 == 0 && unk18 < 0)
            {
                return unk04[0].unk04;
            }
            if (unk2a_4_7 == 0 && unk18 > 0)
            {
                return unk04[unk20 - 1].unk04;
            }
        }
        extrapolate = func_001E1310(reinterpret_cast<FieldEntryArrayObject*>(this), wrapped_key, &lower, &upper);
        if (extrapolate)
        {
            wrapped_key = key;
        }
    }
    if (!extrapolate)
    {
        if (unk26 != lower || unk28 != upper)
        {
            unk26 = lower;
            unk28 = upper;
            FieldArrayEntry10* first = lower >= 0 ? unk04 + lower : &unk08;
            s32 last = unk20 - 1;
            if (upper == last && ((!(key < unk04[0].unk00) && unk2a_4_7 == 2) ||
                                (key < unk04[0].unk00 && unk2a_0_3 == 2)))
            {
                FieldArrayEntry10* entries = unk04;
                unk2c.func_001E11E0(&first->unk04, &first->unk0c, &entries[0].unk04, &entries[0].unk08,
                                   first->unk00, entries[upper].unk00);
            }
            else if (lower < upper)
            {
                FieldArrayEntry10* second = unk04 + upper;
                unk2c.func_001E11E0(&first->unk04, &first->unk0c, &second->unk04, &second->unk08, first->unk00, second->unk00);
            }
            else
            {
                FieldArrayEntry10* second = unk04 + last;
                unk2c.func_001E11E0(&first->unk04, &first->unk0c, &second->unk04, &second->unk08, first->unk00, second->unk00);
            }
        }
        result = func_4B16C0(&unk2c, wrapped_key);
        if (unk18 && ((unk2a_0_3 == 5 && unk18 < 0) || (unk2a_4_7 == 5 && unk18 > 0)))
        {
            float delta = unk04[unk20 - 1].unk04 - unk04[0].unk04;
            result += delta * unk18;
        }
    }
    else if (wrapped_key < key)
    {
        s32 count = unk20;
        FieldArrayEntry10* entries = unk04;
        FieldArrayEntry10* last_entry = entries + (count - 1);
        FieldArrayEntry10* previous_entry = entries + (count - 2);
        float last_key = last_entry->unk00;
        float previous_key = previous_entry->unk00;
        float slope = entries[count - 1].unk08 / (last_key - previous_key);
        result = entries[count - 1].unk04 + slope * (key - last_key);
    }
    else
    {
        FieldArrayEntry10* entries = unk04;
        float first_key = entries[0].unk00;
        result = entries[0].unk04 + (entries[0].unk0c / (entries[1].unk00 - first_key)) * (key - first_key);
    }
    unk50 = D_001B668C * (result - unk4c);
    unk4c = result;
    return result;
}

/**
 * @brief Finish or cancel pending record requests and report their remaining state.
 * @return One when cancelled storage remains, two when requests remain, or zero otherwise.
 */
s32 FieldResourcePreloader::poll_request_release()
{
    s32 result = 0;
    FieldPreloadRequest* records = requests;
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
            FieldPreloadRequest* record = records + i;
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
            FieldPreloadRequest* record = records + i;
            if (record->buffer_address())
            {
                result = 2;
                break;
            }
        }
    }
    return result;
}

void FieldResourcePreloader::update_requests(s32 flag)
{
    switch (request_state)
    {
    case 0:
        if (!flag && requests)
        {
            FlushCache(0);
            FieldPreloadRequest* record = &requests[current_request];
            void* buffer = field_allocate_preload_buffer(this, (record->byte_capacity + 0x7FF) & ~0x7FF, 1);
            if (buffer)
            {
                record->buffer_base = (u32)buffer;
                record->unk08_0 = 0;
                start_current_read();
            }
        }
        break;
    case 1:
        if (flag == 1)
        {
            for (s32 i = 0; i < request_count; i++)
            {
                FieldPreloadRequest* record = &requests[i];
                u32 byte_count = record->byte_capacity;
                u32 buffer_address = record->buffer_address();
                resident_cancel_resource_requests(g_resource_queue, record->file_key, buffer_address, 0x80000000, byte_count, 0);
            }
            request_state = 9;
        }
        else
        {
            FieldPreloadRequest* record = &requests[current_request];
            u32 byte_count = record->byte_capacity;
            u32 buffer_address = record->buffer_address();
            if (!resident_find_resource_request(g_resource_queue, record->file_key, buffer_address, 0x80000000, byte_count, 0) && !field_records_blocked())
            {
                func_001DDB30(0);
            }
        }
        break;
    case 9:
        if (!flag)
        {
            start_current_read();
        }
        break;
    case 10:
    {
        bool done = true;
        FieldPreloadRequest* records = requests;
        for (s32 i = 0; i < request_count; i++)
        {
            FieldPreloadRequest* record = &records[i];
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
        FieldPreloadRequest* record = requests;
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

void FieldResourcePreloader::advance_requests()
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
        FieldPreloadRequest* record = &requests[current_request];
        u32 byte_count = record->byte_capacity;
        u32 buffer_address = record->buffer_address();
        if (resident_find_resource_request(g_resource_queue, record->file_key, buffer_address, 0x80000000, byte_count, 0))
        {
            return;
        }
        for (; current_request < request_count;)
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
 * @brief Allocate a 128-byte-aligned buffer, retrying after other listed loaders release storage.
 * @param loader Loader attached to the resource list.
 * @param size Requested buffer size in bytes.
 * @param mode Nonzero for the library allocator, zero for the resident allocator.
 * @return Allocated buffer, or null when allocation or recovery fails after at most eight attempts.
 */
void* field_allocate_preload_buffer(FieldListObject* loader, u32 size, s32 mode)
{
    FieldResourceLoaderList* manager = static_cast<FieldResourceLoaderList*>(loader->owner);
    for (s32 attempt = 0; attempt < 8; attempt++)
    {
        void* result;
        if (mode)
        {
            func_00433AA0();
            result = func_00433880(size, 128);
        }
        else
        {
            result = memalign_guess(128, size);
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

void FieldClass159960::func_001E11E0(const float* a, const float* b, const float* c, const float* d, float start, float end)
{
    unk00 = *a;
    unk10 = start;
    unk08 = *b;
    unk04 = *c;
    unk14 = end;
    unk0c = *d;
    unk18 = end - start;
    if (unk18 == 0.0f)
    {
        unk18 = 1.0f;
    }
}

float func_001E1230(FieldEntryArrayObject* object, float key)
{
    float first = object->unk04[0].unk00;
    float cycles = (key - first) / object->unk1c;
    if (key < first)
    {
        cycles -= 1.0f;
    }
    object->unk18 = cycles;
    if (object->unk18 != 0)
    {
        float result = key - object->unk18 * object->unk1c;
        if ((object->unk2a_0_3 == 3 && object->unk18 < 0) || (object->unk2a_4_7 == 3 && object->unk18 > 0))
        {
            s32 index = object->unk20 - 1;
            float last = object->unk04[index].unk00;
            if (object->unk18 & 1)
            {
                result = first + (last - result);
            }
        }
        return result;
    }
    return key;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1310);

s32 FieldClass150090::func_001E1470(const float* x, const float* y, const float* z, float key)
{
    return func_001DFD00(x, y, z, key);
}

s32 FieldClass150090::func_001E14A0(s32 index, float key, const float* x, const float* y, const float* z)
{
    return func_001DFD10(index, key, x, y, z);
}

s32 FieldClass150090::func_001E14D0(s32 index, float key, const float* x, const float* y, const float* z)
{
    return func_001DFD20(index, key, x, y, z);
}

void FieldClass150090::func_001E1500(const float* x, const float* y, const float* z, float key)
{
    func_001DFD30(x, y, z, key);
}


/** @brief Forward the node update from the field-list secondary base. */
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1540);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1550);

/** @brief Forward the default-kind query from the field-node subobject. */
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1560);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1570);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1580);
