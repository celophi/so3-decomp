#ifndef SO3_OVERLAYS_LIB_PARTICLE_GRID_H
#define SO3_OVERLAYS_LIB_PARTICLE_GRID_H

#include "types.h"

#ifdef __cplusplus
#include "overlays/lib/emission.h"
#endif

/** A vector whose fourth word can hold a frame index. */
typedef union LibGridFrameVector
{
    unsigned __int128 packed;
    float floats[4];

    struct
    {
        float xyz[3];
        s32 frame_index;
    } components;
} LibGridFrameVector;

/** A vector with float and quadword views. */
typedef union LibGridVector4
{
    float floats[4];
    unsigned __int128 packed;
} LibGridVector4;

/** Behaviour when playback reaches the final frame. */
enum LibGridFrameLoopMode
{
    LIB_GRID_FRAME_WRAP = 0,
    LIB_GRID_FRAME_PING_PONG = 1,
    LIB_GRID_FRAME_HOLD_LAST = 2
};

/** Per-cell frame playback state. */
typedef struct LibGridFrameState
{
    s32 reverse;
    s32 frame_index;
    float remaining_time;
    s32 boundary_count;
} LibGridFrameState;

/** An animated vector, its rate, and the cell's frame playback state. */
typedef struct LibGridFrameMotion
{
    LibGridVector4 value;
    LibGridVector4 rate;
    LibGridFrameState frame;
} LibGridFrameMotion;

/** Common grid element base: a cell's position and second vector, and a scale at 0x3C. */
typedef struct LibGridElement40
{
#ifdef __cplusplus
    /**
     * @brief Get the cell position.
     * @return The position vector.
     */
    const LibGridVector4& position() const
    {
        return unk10;
    }

#endif
    void* vtable;
    u8 unk04[0xC];
    LibGridVector4 unk10;
    LibGridVector4 unk20;
    u8 unk30[0xC];
    float unk3C;
} LibGridElement40;

/** 64-byte secondary row element. */
typedef struct LibGridRow40
{
    void* vtable;
    u8 unk04[0xC];
    LibGridVector4 unk10;
    LibGridVector4 unk20;
    LibGridFrameVector unk30;
} LibGridRow40;

#ifdef __cplusplus
/** Bit set of the grid's active cells, with vtable D_173F58 in main data after its data. */
class LibGridBitset
{
public:
    /**
     * @brief Allocate word storage for a bit count.
     * @param count Number of bits.
     */
    LibGridBitset(u32 count)
    {
        bits = 0;
        borrowed = 0;
        resize(count);
    }

    /**
     * @brief Replace the word storage with room for a bit count.
     * @param count Number of bits.
     */
    void resize(u32 count)
    {
        if (!borrowed)
        {
            delete[] bits;
        }
        this->count = count;
        words = (count + 63) >> 6;
        bits = new (0) u64[words];
        borrowed = 0;
    }

    /** @brief Clear every word. */
    void clear()
    {
        s32 total = words;
        for (s32 i = 0; i < total; i++)
        {
            bits[i] = 0;
        }
    }

    s32 count;
    s32 words;
    u64* bits;

    /** Nonzero when bits is borrowed and must not be freed. */
    bool borrowed;

    /** @brief Free the words unless they're borrowed. */
    virtual ~LibGridBitset();
};

/** Root of the grid element classes, with vtable D_173F48 in main data; its only virtual is the destructor. */
class LibClass173F48 : public LibClass173A28
{
public:
    /** @brief Construct the element. */
    LibClass173F48()
    {
    }

    /** @brief Destroy the element. */
    virtual ~LibClass173F48()
    {
    }
};

/** The 64-byte secondary row element, with vtable D_173F38 in main data. */
class LibClass173F38 : public LibClass173F48
{
public:
    /** @brief Construct the element. */
    LibClass173F38();

    /** @brief Destroy the element. */
    virtual ~LibClass173F38();

    u8 unk04[0xC];
    LibGridVector4 unk10;
    LibGridVector4 unk20;
    LibGridFrameVector unk30;
};

/** The 0x60-byte common grid cell, with vtable D_174228 in main data. */
class LibClass174228 : public LibClass173F48
{
public:
    /** @brief Construct the cell. */
    LibClass174228()
    {
    }

    /** @brief Destroy the cell. */
    virtual ~LibClass174228()
    {
    }

    u8 unk04[0xC];
    LibGridVector4 unk10;
    LibGridVector4 unk20;
    u8 unk30[0xC];
    float unk3C;
    u8 unk40[0x20];
};

/** 0x80-byte grid cell, with vtable D_174218 in main data. */
class LibClass174218 : public LibClass174228
{
public:
    /** @brief Construct the cell. */
    LibClass174218()
    {
    }

    /** @brief Destroy the cell. */
    virtual ~LibClass174218()
    {
    }

    u8 unk60[0x20];
};

/** 0xB0-byte grid cell of LibClass1774E0, with vtable D_177168 in main data. */
class LibClass177168 : public LibClass174218
{
public:
    /** @brief Construct the cell. */
    LibClass177168();

    /** @brief Destroy the cell. */
    virtual ~LibClass177168();

    u8 unk80[0x30];
};

/** 0xF0-byte grid cell, with vtable D_174208 in main data. */
class LibClass174208 : public LibClass174218
{
public:
    /** @brief Construct the cell. */
    LibClass174208()
    {
    }

    /** @brief Destroy the cell. */
    virtual ~LibClass174208()
    {
    }

    u8 unk80[0x70];
};

/** 0x120-byte grid cell of LibClass177680, with vtable D_177158 in main data. */
class LibClass177158 : public LibClass174208
{
public:
    /** @brief Construct the cell. */
    LibClass177158();

    /** @brief Destroy the cell. */
    virtual ~LibClass177158();

    u8 unkF0[0x30];
};

/** 0x140-byte grid cell of LibClass177750, with vtable D_1741F8 in main data. */
class LibClass1741F8 : public LibClass174208
{
public:
    /** @brief Construct the cell. */
    LibClass1741F8()
    {
    }

    /** @brief Destroy the cell. */
    virtual ~LibClass1741F8()
    {
    }

    u8 unkF0[0x50];
};

/** 0x170-byte grid cell of LibClass174240, with vtable D_1741E8 in main data: the element, then its frame motion. */
class LibGridCell170 : public LibClass1741F8, public LibGridFrameMotion
{
public:
    /** @brief Construct the cell. */
    LibGridCell170();

    /** @brief Destroy the cell. */
    virtual ~LibGridCell170();
};

/** 0x90-byte grid cell of LibClass177340, with vtable D_177178 in main data. */
class LibClass177178 : public LibClass174228
{
public:
    /** @brief Construct the cell. */
    LibClass177178();

    /** @brief Destroy the cell. */
    virtual ~LibClass177178();

    u8 unk60[0x30];
};

/** 0x60-byte grid cell of LibClass1771A0, with vtable D_177188 in main data. */
class LibClass177188 : public LibClass173F48
{
public:
    /** @brief Construct the cell. */
    LibClass177188();

    /** @brief Destroy the cell. */
    virtual ~LibClass177188();

    u8 unk04[0x5C];
};
#else
/** Bit set of the grid's active cells. */
typedef struct LibGridBitset
{
    s32 count;
    s32 words;
    u64* bits;
} LibGridBitset;
#endif

/** Output record containing an updated vector and an optional frame index. */
typedef struct LibGridOutputRecord
{
    u8 unk00[0x20];
    LibGridFrameVector frame_vector;
} LibGridOutputRecord;

/** Leading frame count and end behaviour of a grid frame resource. */
typedef struct LibGridFrameHeader
{
    u8 frame_count;
    u8 unk01[2];
    u8 loop_mode;
} LibGridFrameHeader;

/** 0x50-byte frame record with its duration measured in frames. */
typedef struct LibGridFrameRecord
{
    u8 unk00[0xC];
    float duration_frames;
    u8 unk10[0x40];
} LibGridFrameRecord;


#ifdef __cplusplus
/**
 * Root of Lib's particle grids, Lib's copy of the field's grid base. Most slots are filled by the grid classes;
 * only the ones used so far are named.
 */
class LibGridBase
{
    public:
        /** @brief Destroy the grid. */
        virtual ~LibGridBase();

        virtual void func_slot0c() = 0;
        virtual void func_slot10();
        virtual void func_slot14();
        virtual void func_slot18() = 0;
        virtual void func_slot1c() = 0;
        virtual void func_slot20() = 0;
        virtual void func_slot24() = 0;
        virtual void func_slot28() = 0;
        virtual void func_slot2c() = 0;
        virtual LibGridBitset* func_slot30() = 0;
        virtual void func_slot34() = 0;
        virtual void func_slot38() = 0;
        virtual s32 func_slot3c();
        virtual void func_slot40() = 0;
        virtual void func_slot44() = 0;
        virtual void func_slot48() = 0;
        virtual void func_slot4c() = 0;
        virtual void func_slot50() = 0;
        virtual void func_slot54() = 0;

        /**
         * @brief Reallocate the grid for a cell count and row width.
         * @param cells Number of cells.
         * @param columns Elements per row.
         */
        virtual void resize(s32 cells, s32 columns) = 0;

        u8 unk04;
        s32 unk08;
        s32 cell_count;
        s32 columns;
};

/** Settings every Lib particle grid emitter shares; the cell and row arrays' element types vary by grid. */
class LibGridEmitter : public LibGridBase
{
    public:
        void* cells;
        void* unk18;
        LibGridBitset* active;
        LibGridRow40* rows;
        void* unk24;
        float unk28;
        s32 index;
        float unk30;
        float unk34;
        float unk38;
        float unk3C;
        float unk40;
        float unk44;
        void* unk48;
        u8 unk4C;
        u8 unk4D;
        u8 unk4E;
        u8 unk4F;
        void* unk50;
        u8 unk54;
        u8 unk55;
        u8 unk56;
        u8 skip_frame_playback;
        u8 unk58[8];
        LibGridVector4 unk60;
        LibGridVector4 unk70;
        LibGridVector4 unk80;
        LibGridVector4 unk90;
        LibGridFrameHeader* frame_header;
        LibGridFrameRecord* frame_records;
};
#endif

#ifdef __cplusplus
/** Grid receiver the frame-vector updater at 0x447500 reads; the same layout as the field's grid emitters. */
typedef struct LibGridReceiver447500
{
    u8 unk00[0xC];
    s32 cell_count;
    s32 columns;
    LibGridCell170* cells;
    u32 unk18;
    LibGridBitset* active;
    LibGridRow40* rows;
    u32 unk24;
    float unk28;
    s32 index;
    float unk30;
    u8 unk34[0x18];
    u8 unk4C;
    u8 unk4D[0xA];
    u8 skip_frame_playback;
    u8 unk58[0x48];
    LibGridFrameHeader* frame_header;
    LibGridFrameRecord* frame_records;
} LibGridReceiver447500;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00494AE0(LibGridEmitter* object, const LibGridEmitter* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00491820(LibGridEmitter* object, const LibGridEmitter* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_0048E480(LibGridEmitter* object, const LibGridEmitter* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_0048B300(LibGridEmitter* object, const LibGridEmitter* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00488040(LibGridEmitter* object, const LibGridEmitter* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00484D80(LibGridEmitter* object, const LibGridEmitter* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00481AC0(LibGridEmitter* object, const LibGridEmitter* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_00447090(LibGridEmitter* object, const LibGridEmitter* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_0043E220(LibGridEmitter* object, const LibGridEmitter* other);

/**
 * @brief Fill a row of secondary elements from a cell, or from an explicit vector.
 * @param object Grid owning the row.
 * @param cell Cell whose vectors are copied.
 * @param row First secondary element of the row.
 * @param index Unused.
 * @param source Vector copied to each element, or null to use the cell's position.
 */
void func_00444BF0(LibGridEmitter* object, LibGridElement40* cell, LibGridRow40* row, s32 index, const LibGridVector4* source);

/**
 * @brief Advance active cells' frame vectors and playback state into an output batch.
 * @param object Grid owning the cells and frame resource.
 * @param capacity Output-entry budget, counted in steps of the grid column count.
 * @param output Output records, with each cell written at the start of its row.
 * @param preserve_row_vector Nonzero to retain the saved xyz components in the first secondary element.
 */
void func_00447500(LibGridReceiver447500* object, s32 capacity, LibGridOutputRecord* output, s32 preserve_row_vector);

#ifdef __cplusplus
}
#endif

#endif
