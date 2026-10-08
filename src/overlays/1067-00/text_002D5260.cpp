#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/1067-00/text_001E6C50.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_0044ABE0.h"


/**
 * @brief Allocate and align the drawing storage when it has no allocation.
 * @param storage Storage to initialize.
 * @param count Count used to calculate the drawing allocation size.
 * @return One on success, or zero when storage is already allocated or allocation fails.
 */
extern "C" s32 func_461860(LibStorageBlock0C* storage, u32 count);

extern "C" void func_4D00B0(FieldFlagState2D7AA0* object);

/** Registry prefix containing the two 32-entry container lists. */
struct FieldRegistry1B66A0
{
    u8 unk00[0x20];
    LibObject178660* unk20[32];
    LibObject178660* unka0[32];
};

extern "C" FieldRegistry1B66A0* D_001B66A0;

/** Partial scalar transition interface; the two callbacks occupy its original table slots. */
class FieldScalarTransition2D6AF0
{
public:
    float unk00;
    float unk04;
    u8 unk08_0 : 1;
    u8 unk08_1 : 1;
    u8 unk08_2 : 1;
    u8 unk08_3 : 1;
    u8 unk08_rest : 4;
    u8 unk09[3];

    /** @brief Store the current scalar in the receiving object. @param value Scalar to store. */
    virtual void func_slot08(float value) = 0;
    /** @brief Store the callback's byte value. @param value Byte to store. */
    virtual void func_slot0c(u8 value) = 0;
};

class ItemCreationClass185030;

/** Partial widget aggregate with grid settings and selection callbacks. */
class LibClass1723F0
{
public:
    u8 unk00[0x90];
    ItemCreationClass1746A0 unk90;
    ItemCreationClass1746A0 unke4;
    ItemCreationClass1725D0 unk138;
    ItemCreationClass175030 unk190;
    u8 unk20c[0xAC];
    u8 unk2b8[8];
    float unk2c0;
    float unk2c4;
    float unk2c8;
    float unk2cc;
    float unk2d0;
    u8 unk2d4[0x24];
    s32 unk2f8;
    float unk2fc;
    s32 unk300;
    s32 unk304;
    s32 unk308;
    s32 unk30c;
    s8 unk310;
    s8 unk311;
    s8 unk312;
    s8 unk313;
    s8 unk314;
    s8 unk315;
    s8 unk316;
    u8 unk317;
    u8 unk318;
    u8 unk319[3];
    /** @brief Update the aggregate index. @param index Requested index. */
    virtual void func_00412C10(s32 index);
    /** @brief Update the aggregate float setting. @param value Requested setting. */
    virtual void func_00412C20(float value);
    /** @brief Read the aggregate float setting. @return Current setting. */
    virtual float func_00412C30();
    /** @brief Refresh the aggregate. */
    virtual void func_00413020();
};
/** Widget container with an object base and a selection aggregate. */
class LibClass172320 : public LibObject178660, public LibClass1723F0
{
public:
    /** @brief Initialize the container and its widget aggregate. */
    LibClass172320();
    /** @brief Destroy the aggregate and object bases. */
    virtual ~LibClass172320();
};
/** Resident owner of 32 interface rows and the collection state. */
class LibClass1721F0 : public LibClass172320
{
public:
    /** @brief Initialize the option container transform code. */
    LibClass1721F0();
    /** @brief Destroy the option row collection. */
    virtual ~LibClass1721F0();
    /** @brief Update row values. @param first First value. @param second Second value. @param third Third value. */
    virtual void func_00412C40(u32 first, u32 second, u32 third);
    /** @brief Create an option row. @param index Row index. @return Created row. */
    virtual ItemCreationClass185030* create_row(s32 index) = 0;
    /** @brief Notify the selected index. @param index Selected index. */
    virtual void notify_index(s32 index);
    /** @brief Notify cancellation. */
    virtual void notify_cancel();
    /** @brief Update the aggregate index. @param index Requested index. */
    virtual void func_00412C10(s32 index);
    /** @brief Update the aggregate float setting. @param value Requested setting. */
    virtual void func_00412C20(float value);
    /** @brief Read the aggregate float setting. @return Current setting. */
    virtual float func_00412C30();
    ItemCreationClass185030* unk410[32];
    float unk490;
    float unk494;
    float unk498;
    float unk49c;
    s32 unk4a0;
    s32 unk4a4;
    u8 unk4a8;
    u8 unk4a9;
    u8 unk4aa;
    u8 unk4ab[5];
};

/** Partial Field row container with its secondary scalar transition state. */
class FieldClass15B300 : public LibClass1721F0, public FieldScalarTransition2D6AF0
{
public:
    u32 unk4c0;
};

/** Partial Field container with its secondary scalar transition state. */
class FieldClass15B670 : public LibObject178660, public FieldScalarTransition2D6AF0
{
};

/** Six-byte controller record in the resident runtime. */
struct FieldControllerInput6
{
    u16 unk00;
    u16 unk02;
    u16 unk04;
};

/** Partial runtime prefix containing its two controller records. */
struct FieldRuntime
{
    u8 unk00[0x5F0];
    FieldControllerInput6 unk5f0[2];
};

/** @brief Refresh the aggregate's scalar display. @param object Widget aggregate. */
extern "C" void func_413BB0(LibClass1723F0* object);
/** @brief Dispatch a resident request. @param receiver Request receiver. @param arg1 Request kind. @param arg2 Request argument. @param arg3 Request argument. @param arg4 Request argument. @param arg5 Request argument. @param arg6 Request argument. @return Request result. */
extern "C" s32 func_112400(ResidentRequest112400* receiver, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
/** @brief Set the movement target. @param object Movement state. @param x Horizontal coordinate. @param y Vertical coordinate. @param duration Movement duration. */
extern "C" void func_466E40(ItemCreationClass185050* object, float x, float y, float duration);

/** Partial container state with the panel constructed at offset 0x100. */
struct FieldPanelState2D7820 : public LibObject178660
{
    u8 unkf0[0x10];
    LibClass178630 unk100;
    u32 unk190;
};

/**
 * @brief Store two floats and mark the attached state updated when present.
 * @param object Owner of the optional state.
 * @param first First float to store.
 * @param second Second float to store.
 */
void func_002D5260(FieldClass15B200* object, float first, float second)
{
    LibClass178600* state = object->unk30;
    if (state != 0)
    {
        state->unk18.unk08 = first;
        state->unk18.unk0c = second;
        state->unk3c = 1;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D5290);

/** @brief Destroy the resource owner. */
FieldClass15B200::~FieldClass15B200()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D5A40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D5AA0);

/**
 * @brief Set the receiver's byte at offset 0x3C.
 * @param object Receiver to update.
 */
void func_002D5CE0(LibClass178600* object)
{
    object->unk3c = 1;
}

/** Eight-byte resource descriptor copied by the resource drawing widget. */
struct FieldResourceDescriptor8
{
    u16 unk00;
    u16 unk02;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
};

/**
 * @brief Set the resource record and optional descriptor, then request a refresh.
 * @param object Resource drawing widget.
 * @param record Resource record to store.
 * @param descriptor Descriptor to copy, or null to retain the existing descriptor.
 */
static inline void set_resource_record(ItemCreationClass175110* object, FieldResourceRecord* record,
                                      const FieldResourceDescriptor8* descriptor)
{
    object->unkb4 = record;
    if (descriptor != 0)
    {
        object->unkb8 = descriptor->unk00;
        object->unkba = descriptor->unk02;
        object->unkbc = descriptor->unk04;
        object->unkbd = descriptor->unk05;
        object->unkbe = descriptor->unk06;
        object->unkbf = descriptor->unk07;
    }
    object->unkc4 = 0;
    object->unkc9 = 1;
    object->unk3c = 1;
}

/**
 * @brief Replace non-null resource pointers and a nonzero resource index, then request an update.
 * @param allocation Allocation pointer, or null to keep the current pointer.
 * @param record Resource record, or null to keep the current record.
 * @param index Nonzero full word whose low byte replaces the resource index.
 */
void ItemCreationOptionResourceDisplay::func_002D5CF0(void* allocation, FieldResourceRecord* record, u32 index)
{
    if (allocation != 0)
    {
        unkcc = allocation;
    }
    if (record != 0)
    {
        unk108 = record;
    }
    if (index != 0)
    {
        unkd0 = index;
    }
    if (unkcc != 0 && record != 0)
    {
        set_resource_record(this, unk108, reinterpret_cast<const FieldResourceDescriptor8*>(&unk10c));
    }
    unk114 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D5DA0);

/** @brief Mark the resource widget updated and refresh its base drawing state. */
void ItemCreationOptionResourceDisplay::func_00413D20()
{
    unk3c = 1;
    ItemCreationClass175110::func_00413D20();
}

/** @brief Clear the resource pointers, indices and trailing update flags. */
void ItemCreationOptionResourceDisplay::func_002D6410()
{
    unkcc = 0;
    unkd0 = 0;
    unk108 = 0;
    unk10c = 0;
    unk10e = 0;
    unk110 = 0;
    unk111 = 0;
    unk112 = 0;
    unk113 = 0;
    unk114 = 0;
}

/**
 * @brief Initialize the resource drawing storage, record and position.
 * @param record Resource record to display.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @return One on success, or zero if the drawing storage cannot be initialized.
 */
s32 ItemCreationOptionResourceDisplay::func_002D6440(FieldResourceRecord* record, float x, float y)
{
    unk18.unk00 = x;
    unk18.unk04 = y;
    if (func_461860(&unk40, 56) == 0)
    {
        return 0;
    }
    unkc0 = 0;
    unk108 = record;
    unkb4 = record;
    unkb8 = unk10c;
    unkba = unk10e;
    unkbc = unk110;
    unkbd = unk111;
    unkbe = unk112;
    unkbf = unk113;
    unkc9 = 1;
    unk34 = 6;
    unk39 = 1;
    if (unkcc == 0 && record == 0)
    {
        unk3b = 0;
    }
    else
    {
        set_resource_record(this, unk108, reinterpret_cast<const FieldResourceDescriptor8*>(&unk10c));
        unk3b = 1;
    }
    return 1;
}

/** Partial LibClass178600 widget with vtable D_15B210 in main data. */
class FieldClass15B210 : public LibClass178600
{
public:
    /** @brief Release the widget storage and destroy its base. */
    virtual ~FieldClass15B210();
    LibStorageBlock0C unk40;
};

/** @brief Release the widget storage and destroy its base. */
FieldClass15B210::~FieldClass15B210()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D65E0);

/** Partial LibClass178EA0 with vtable D_15B270 in main data. */
class FieldClass15B270 : public LibClass178EA0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15B270();
};

/** @brief Destroy the object. */
FieldClass15B270::~FieldClass15B270()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D66C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D68F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D69A0);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D6A20(void* object)
{
}

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D6A30(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D6A40);

/**
 * @brief Store the row container's transform byte.
 * @param object Field row container.
 * @param value Byte to store.
 */
void func_002D6AD0(FieldClass15B300* object, u8 value)
{
    object->unkab = value;
}

/**
 * @brief Store a float and mark it present.
 * @param object Receiver to update.
 * @param value Float to store.
 */
void func_002D6AE0(FieldClass15B300* object, float value)
{
    object->unkE0 = value;
    object->unkae = 1;
}

/**
 * @brief Advance the flagged scalar transition and dispatch its updated value.
 * @param object Scalar transition state.
 * @return One when a transition flag is set, otherwise zero.
 */
s32 func_002D6AF0(FieldScalarTransition2D6AF0* object)
{
    if (object->unk08_0)
    {
        object->unk00 -= 16.0f * D_001B6688;
        if (object->unk00 <= object->unk04)
        {
            object->unk00 = object->unk04;
            object->unk08_0 = 0;
            if (object->unk04 == 0.0f)
            {
                object->func_slot0c(0);
            }
        }
        object->func_slot08(object->unk00);
        return 1;
    }
    if (object->unk08_1)
    {
        object->unk00 += 16.0f * D_001B6688;
        if (!(object->unk00 < 128.0f))
        {
            object->unk00 = 128.0f;
            object->unk08_1 = 0;
        }
        object->func_slot08(object->unk00);
        return 1;
    }
    if (object->unk08_2)
    {
        object->unk00 -= 16.0f * D_001B6688;
        if (object->unk00 <= 0.0f)
        {
            object->unk00 = 0.0f;
            object->unk08_3 = 1;
        }
        object->func_slot08(object->unk00);
        return 1;
    }
    return 0;
}

/**
 * @brief Apply controller input to the row container's selection and scrolling state.
 * @param object Field row container.
 * @return One when its selection or scrolling state changes, otherwise zero.
 */
bool func_002D6CB0(FieldClass15B300* object)
{
    bool changed = false;
    s32 selection = object->unk312;
    s32 row_step = 0;
    u16 buttons = D_001B657C->unk5f0[object->unk315].unk04;
    s32 page_step = 0;
    if (buttons & 0x10)
    {
        if (selection < object->unk310)
        {
            row_step--;
        }
        else
        {
            selection -= object->unk310;
        }
    }
    else if (buttons & 0x40)
    {
        if (selection >= object->unk310 * (object->unk311 - 1))
        {
            row_step++;
        }
        else
        {
            selection += object->unk310;
        }
    }
    else if (buttons & 0x80)
    {
        if (object->unk310 > 1)
        {
            if (selection == 0)
            {
                selection = object->unk310 - 1;
                row_step--;
            }
            else
            {
                selection--;
            }
        }
    }
    else if (buttons & 0x20)
    {
        if (object->unk310 > 1)
        {
            if (selection == object->unk310 * object->unk311 - 1)
            {
                row_step++;
                selection = object->unk310 * (object->unk311 - 1);
            }
            else
            {
                selection++;
            }
        }
    }
    else if (buttons & 0x400)
    {
        if (object->unk304 > 0)
        {
            page_step--;
        }
        else
        {
            selection %= object->unk310;
        }
    }
    else if (buttons & 0x800)
    {
        if (object->unk304 < object->unk300)
        {
            page_step++;
        }
        else
        {
            selection = selection % object->unk310 + object->unk310 * (object->unk311 - 1);
        }
    }
    if (object->unk4c0 & 1)
    {
        bool wrapped = false;
        if (row_step < 0 && object->unk304 <= 0)
        {
            object->unk304 = object->unk300;
            selection = selection % object->unk310 + object->unk310 * (object->unk311 - 1);
            wrapped = true;
        }
        else if (row_step > 0 && object->unk304 >= object->unk300)
        {
            object->unk304 = 0;
            wrapped = true;
            selection %= object->unk310;
        }
        if (wrapped)
        {
            object->func_00412C10(object->unk304);
            func_413BB0(&static_cast<LibClass1723F0&>(*object));
            changed = true;
        }
    }
    if (selection != object->unk312)
    {
        object->unk312 = selection;
        float duration;
        if (row_step != 0)
        {
            duration = object->unk2c8 / 60.0f;
        }
        else
        {
            duration = 0.05f;
        }
        func_466E40(&object->unk190,
                     object->unk2cc + object->unk2c0 * (selection % object->unk310),
                     object->unk2d0 + object->unk2c4 * (selection / object->unk310), duration);
        changed = true;
    }
    if ((row_step < 0 && object->unk304 > 0) || (row_step > 0 && object->unk304 < object->unk300))
    {
        object->unk313 = row_step;
        object->unk314 = 1;
        changed = true;
    }
    if (page_step != 0)
    {
        if (page_step < 0)
        {
            object->unk304 -= object->unk311;
            if (object->unk304 < 0)
            {
                object->unk304 = 0;
            }
        }
        else
        {
            object->unk304 += object->unk311;
            if (object->unk304 > object->unk300)
            {
                object->unk304 = object->unk300;
            }
        }
        object->func_00412C10(object->unk304);
        func_413BB0(&static_cast<LibClass1723F0&>(*object));
        changed = true;
    }
    if (changed)
    {
        func_112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
    }
    return changed;
}

/**
 * @brief Remove the first matching entry from the second registry list and queue the container for release.
 * @param object Container to remove and release.
 */
void func_002D70F0(LibObject178660* object)
{
    FieldRegistry1B66A0* registry = D_001B66A0;
    if (registry != 0)
    {
        for (s32 i = 0; i < 32; i++)
        {
            if (registry->unka0[i] == object)
            {
                registry->unka0[i] = 0;
                break;
            }
        }
    }
    object->LibClass174610::func_003EF740();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7150);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D72B0);

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass1725D0::~ItemCreationClass1725D0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7500);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7540);

/**
 * @brief Remove the first matching entry from the first registry list and queue the container for release.
 * @param object Container to remove and release.
 */
void func_002D7630(LibObject178660* object)
{
    FieldRegistry1B66A0* registry = D_001B66A0;
    if (registry != 0)
    {
        for (s32 i = 0; i < 32; i++)
        {
            if (registry->unk20[i] == object)
            {
                registry->unk20[i] = 0;
                break;
            }
        }
    }
    object->LibClass174610::func_003EF740();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7690);

/**
 * @brief Configure the container transform and panel, then attach the panel and store the supplied value.
 * @param object Container to initialize.
 * @param value Word to store after panel setup succeeds.
 * @param mode Signed byte passed to the container transform setup.
 * @param transform Third transform setup argument.
 * @param x Container horizontal position.
 * @param y Container vertical position.
 * @param width Panel width.
 * @param height Panel height.
 * @return One on panel setup success, otherwise zero.
 */
s32 func_002D7820(FieldPanelState2D7820* object, u32 value, s8 mode, s32 transform,
                  float x, float y, float width, float height)
{
    func_004C6510(object, mode, 9, transform, x, y, 0.0f);
    object->unk6c = 0x400E;
    if (func_004C5A80(&object->unk100, 0, 0.0f, 0.0f, width, height, 88.0f) == 0)
    {
        return 0;
    }
    object->unk100.unk3d = 1;
    func_004C6190(object, &object->unk100);
    object->unk190 = value;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D78E0);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D79C0(void* object)
{
}

/**
 * @brief Unpack one table entry when the receiver's presence flag is set.
 * @param object Receiver containing the packed entries.
 * @param index Entry index to read.
 * @param output Eight-byte destination for the unpacked fields.
 * @return One when data is available, otherwise zero.
 */
s32 func_002D79D0(FieldPackedTable2D79D0* object, s32 index, FieldPackedValues2D79D0* output)
{
    if ((object->unk14AC & 1) == 0)
    {
        return 0;
    }
    u64 first = object->entries[index].unk00;
    u64 second = object->entries[index].unk08;
    output->unk04 = (first >> 14) & 0x3F;
    output->unk05 = (first >> 20) & 0x3F;
    output->unk06 = (first >> 26) & 0xF;
    output->unk07 = (first >> 30) & 0xF;
    output->unk00 = first & 0x3FFF;
    output->unk02 = (second >> 37) & 0x3FFF;
    return 1;
}

/**
 * @brief Store two pointers in the first empty slot.
 * @param object Receiver containing the slot table.
 * @param first First pointer to store.
 * @param second Second pointer to store.
 * @return Slot index, or -1 when the table is full.
 */
s32 func_002D7A50(FieldSlotTable2D7A50* object, void* first, void* second)
{
    for (s32 index = 0; index < 32; index++)
    {
        if (object->entries[index].unk00 == 0)
        {
            object->entries[index].unk00 = first;
            object->entries[index].unk04 = second;
            return index;
        }
    }
    return -1;
}

/**
 * @brief Set the receiver's active bit and run its imported update routine.
 * @param object Receiver to update.
 */
void func_002D7AA0(FieldFlagState2D7AA0* object)
{
    object->active = 1;
    func_4D00B0(object);
}

/** Partial packet batch with the Field transform and completion callback bases. */
class FieldClass15B770 : public FieldClass1503A0, public FieldClass1DD400
{
public:
    u8 unk94[0x1314];
    u32 packet_addresses[64];
    s32 packet_count;
    u8 unk14ac[4];
};

struct FieldPacketQueue;
extern "C" FieldPacketQueue* D_001B65DC;

/**
 * @brief Append a packet address and optional completion context to the queue.
 * @param queue Packet queue.
 * @param operation Queue operation value.
 * @param flags Entry flags.
 * @param address Packet hardware address.
 * @param value Additional entry value.
 * @param completion Optional completion context.
 * @return One when queued, or zero when the queue is full.
 */
extern "C" s32 func_4DC4F0(FieldPacketQueue* queue, u32 operation, u32 flags,
                          u32 address, u32 value, void* completion);

/**
 * @brief Submit prepared packet addresses with the callback attached to the final entry.
 * @param object Packet batch owner.
 */
void func_002D7AD0(FieldClass15B770* object)
{
    object->unk60[4] = 1;
    for (s32 index = 0; index < object->packet_count; index++)
    {
        FieldClass1DD400* completion = index == object->packet_count - 1 ?
            static_cast<FieldClass1DD400*>(object) : 0;
        func_4DC4F0(D_001B65DC, 3, 0, object->packet_addresses[index], 0, completion);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7B80);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D7FE0(void* object)
{
}

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D7FF0(void* object)
{
}

/**
 * @brief Return the default float value.
 * @param object Receiver to query.
 * @return Always zero.
 */
float func_002D8000(void* object)
{
    return 0.0f;
}

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D8010(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8020);

/**
 * @brief Store a byte in the receiver's scalar state.
 * @param object Receiver to update.
 * @param value Byte to store.
 */
void func_002D80E0(FieldClass15B670* object, u8 value)
{
    object->unkab = value;
}

/**
 * @brief Store a float and mark it present.
 * @param object Receiver to update.
 * @param value Float to store.
 */
void func_002D80F0(FieldClass15B670* object, float value)
{
    object->unkE0 = value;
    object->unkae = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8100);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8180);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 5.
 */
s32 func_002D82E0(FieldClass150070* object)
{
    return 5;
}

/**
 * @brief Set the receiver's byte at offset 0x60 to 9.
 * @param object Receiver to update.
 */
void func_002D82F0(FieldClass178A90* object)
{
    object->unk60[0] = 9;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8300);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8320);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8350);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8370);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8380);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8390);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8400);
