#ifndef SO3_OVERLAYS_LIB_MODEL_ENTRIES_H
#define SO3_OVERLAYS_LIB_MODEL_ENTRIES_H

#include "overlays/lib/model.h"

/** LibShortBitTableHeader with a colour after the records offset; the words start at 0x10. */
struct LibColorBitTableHeader
{
    s16 bit_count;
    s16 unk02;
    s32 records_offset;
    float color[4];
    u32 unk18[2];
    u32 words[1];
};

/** LibColorBitTableHeader whose colour holds texture offsets, a scale and a mapping mode. */
struct LibOffsetBitTableHeader
{
    s16 bit_count;
    s16 unk02;
    s32 records_offset;
    float offset[2];
    float scale;
    s32 mapping;
    u32 unk18[2];
    u32 words[1];
};

/** Record in a resource entry's record list; each starts with its size at 0x8. */
struct LibEntryRecord
{
    u32 unk00[2];
    s32 size;
};

/**
 * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
 * @param entry Resource entry.
 * @param cursor Entry's record cursor.
 * @param index Bit index.
 * @param size Receives the record's size.
 * @return Record, or null.
 */
static inline u8* lib_entry_read_record(LibClass1779F0* entry, u8*& cursor, u32 index, u32* size)
{
    if (entry->unk19 || ((entry->bits.words[index / 32] >> (index % 32)) & 1))
    {
        *size = reinterpret_cast<LibEntryRecord*>(cursor)->size;
        u8* record = cursor;
        cursor += reinterpret_cast<LibEntryRecord*>(cursor)->size;
        return record;
    }

    return 0;
}

/** Bit table at the start of a resource entry's data: one bit per record, then the records at records_offset. */
struct LibBitTableHeader
{
    u32 bit_count;
    s32 unk04;
    s32 records_offset;
    u32 unk0c;
    u32 words[1];
};

/** LibBitTableHeader with a halfword bit count and the records offset in the second word. */
struct LibShortBitTableHeader
{
    s16 bit_count;
    s16 unk02;
    s32 records_offset;
    u32 unk08;
    u32 unk0c;
    u32 words[1];
};

/** LibClass174C90 subclass with vtable D_00174C70 in main data. */
class LibClass174C70 : public LibClass174C90
{
public:
    LibClass174C70();

    virtual ~LibClass174C70();

    /**
     * @brief Fill the record's texture coordinates from the environment map on VU0.
     * @param output Output whose coordinates change.
     * @param index Bit index, which picks the record of vertex indices.
     */
    virtual void func_slot10(LibEntryOutput* output, s32 index);

    /**
     * @brief Return the entry's type code.
     * @return 43.
     */
    virtual s32 func_slot14();

    /**
     * @brief Use a resource's bit table and the records after it, without owning them.
     * @param value Resource data.
     */
    virtual void set_borrowed_data(void* value);

    /**
     * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
     * @param index Bit index.
     * @param size Receives the record's size.
     * @return Record, or null.
     */
    virtual u8* read_record(u32 index, u32* size);

    /**
     * @brief Note whether every bit is set and rewind the records. With a camera, rebuild the rotation from the
     *        root's matrix and move the camera's position into the root's space.
     * @param root Model transform.
     * @return One.
     */
    virtual s32 func_slot1C(LibTransform* root);

    LibBitTableHeader* table;
    u8* records;
    u8* cursor;
    u8 unk3c[4];
    FieldVec4B camera_position;
    LibMatrix44Value rotation;
};

/** LibClass174C90 subclass with vtable D_00174CB0 in main data. */
class LibClass174CB0 : public LibClass174C90
{
public:
    LibClass174CB0();

    virtual ~LibClass174CB0();

    /**
     * @brief Fill the record's texture coordinates from the environment map on VU0, with the table's parameter in
     *        vf29.
     * @param output Output whose coordinates change.
     * @param index Bit index, which picks the record of vertex indices.
     */
    virtual void func_slot10(LibEntryOutput* output, s32 index);

    /**
     * @brief Return the entry's type code.
     * @return 43.
     */
    virtual s32 func_slot14();

    /**
     * @brief Use a resource's bit table and the records after it, without owning them.
     * @param value Resource data.
     */
    virtual void set_borrowed_data(void* value);

    /**
     * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
     * @param index Bit index.
     * @param size Receives the record's size.
     * @return Record, or null.
     */
    virtual u8* read_record(u32 index, u32* size);

    /**
     * @brief Note whether every bit is set and rewind the records. With a camera, rebuild the rotation from the
     *        root's matrix and move the camera's position into the root's space.
     * @param root Model transform.
     * @return One.
     */
    virtual s32 func_slot1C(LibTransform* root);

    LibShortBitTableHeader* table;
    u8* records;
    u8* cursor;
    u8 unk3c[4];
    FieldVec4B camera_position;
    LibMatrix44Value rotation;
};

/** LibClass174C90 subclass with vtable D_00174D10 in main data. */
class LibClass174D10 : public LibClass174C90
{
public:
    /** @brief Start as an entry of kind 5 with blend mode 0. */
    LibClass174D10();

    virtual ~LibClass174D10();

    /**
     * @brief Scroll the record's texture coordinates by the offsets on VU0.
     * @param output Output whose coordinates change.
     * @param index Bit index, which picks the record of coordinate indices.
     */
    virtual void func_slot10(LibEntryOutput* output, s32 index);

    /**
     * @brief Return the entry's type code.
     * @return 40.
     */
    virtual s32 func_slot14();

    /**
     * @brief Use a resource's bit table, records and two offsets without owning them.
     * @param value Resource data.
     */
    virtual void set_borrowed_data(void* value);

    /**
     * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
     * @param index Bit index.
     * @param size Receives the record's size.
     * @return Record, or null.
     */
    virtual u8* read_record(u32 index, u32* size);

    /**
     * @brief Note whether every bit is set; in mapping mode 2 scroll the offsets by the camera's reflection off the
     *        model, otherwise count the blend mode down. Rewind the records.
     * @param root Model transform; unused.
     * @return Zero on the step the countdown ends, otherwise one.
     */
    virtual s32 func_slot1C(LibTransform* root);

    /**
     * @brief Pick the blend mode: offsets other than zero mark the owning list the first time; zero offsets use
     *        mode 2 once the list was marked.
     */
    void update_blend_mode()
    {
        if (offset_u != 0.0f || offset_v != 0.0f)
        {
            if (blend_mode == 0)
            {
                if (unk18 != 1 && list != 0)
                {
                    list->unk8d_1 = 1;
                }

                unk18 = 1;
                blend_mode = 0;
            }
        }
        else if (unk18)
        {
            blend_mode = 2;
        }
    }

    /**
     * @brief Set the first offset and refresh the blend mode.
     * @param value Offset.
     */
    void set_offset_u(float value)
    {
        offset_u = value;
        update_blend_mode();
    }

    /**
     * @brief Set the second offset and refresh the blend mode.
     * @param value Offset.
     */
    void set_offset_v(float value)
    {
        offset_v = value;
        update_blend_mode();
    }

    LibOffsetBitTableHeader* table;
    u8* records;
    u8* cursor;
    u8 unk3c[4];
    float offset_u;
    float offset_v;
    u8 unk48[8];
    s32 blend_mode;
    u8 unk54[0xC];
};

/** LibClass1779F0 subclass with vtable D_00174D30 in main data; only its destructors are known. */
class LibClass174D30 : public LibClass1779F0
{
public:
    /** @brief Start unattached, with unk0e set to two. */
    LibClass174D30();

    virtual ~LibClass174D30()
    {
    }

    /**
     * @brief Return the entry's type code.
     * @return Six.
     */
    virtual s32 func_slot14();
};

/** LibClass174D30 subclass with vtable D_00174D50 in main data. */
class LibClass174D50 : public LibClass174D30
{
public:
    /** @brief Start as an entry of kind 6 with a white colour. */
    LibClass174D50();

    virtual ~LibClass174D50();

    /**
     * @brief Tint the record's vertex colors by the entry's color on VU0.
     * @param output Output whose colors change.
     * @param index Bit index, which picks the record of color indices.
     */
    virtual void func_slot10(LibEntryOutput* output, s32 index);

    /**
     * @brief Return the entry's type code.
     * @return 36.
     */
    virtual s32 func_slot14();

    /**
     * @brief Use a resource's bit table, records and colour without owning them; a colour other than white
     *        marks the owning list.
     * @param value Resource data.
     */
    virtual void set_borrowed_data(void* value);

    /**
     * @brief Return the record at the cursor and move past it, when the entry is complete or has bit `index`.
     * @param index Bit index.
     * @param size Receives the record's size.
     * @return Record, or null.
     */
    virtual u8* read_record(u32 index, u32* size);

    /**
     * @brief Note whether every bit is set, count the blend mode down and rewind the records.
     * @param root Model transform; unused.
     * @return Zero on the step the countdown ends, otherwise one.
     */
    virtual s32 func_slot1C(LibTransform* root);

    LibColorBitTableHeader* table;
    u8* records;
    u8* cursor;
    u8 unk3c[4];
    FieldVec4B color;
    s32 blend_mode;
};

#endif
