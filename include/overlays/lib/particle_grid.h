#ifndef SO3_OVERLAYS_LIB_PARTICLE_GRID_H
#define SO3_OVERLAYS_LIB_PARTICLE_GRID_H

#include "types.h"

#ifdef __cplusplus
#include "overlays/lib/emission.h"
#include "overlays/lib/grid_bitset.h"
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
/**
 * Root of the grid element classes and the 0x30-byte cell of LibClass173E70, with vtable D_173F48 in main data; its
 * only virtual is the destructor.
 */
class LibClass173F48 : public LibClass173A28
{
public:
    LibClass173F48()
    {
    }

    virtual ~LibClass173F48()
    {
    }

    u8 unk04[0xC];
    LibGridVector4 unk10;
    LibGridVector4 unk20;
};

/** The 64-byte secondary row element, with vtable D_173F38 in main data. */
class LibClass173F38 : public LibClass173F48
{
public:
    LibClass173F38();

    virtual ~LibClass173F38();

    LibGridFrameVector unk30;
};

/** The 0x60-byte common grid cell, with vtable D_174228 in main data. */
class LibClass174228 : public LibClass173F48
{
public:
    LibClass174228()
    {
    }

    virtual ~LibClass174228()
    {
    }

    u8 unk30[0xC];
    float unk3C;
    u8 unk40[0x20];
};

/** 0x80-byte grid cell, with vtable D_174218 in main data. */
class LibClass174218 : public LibClass174228
{
public:
    LibClass174218()
    {
    }

    virtual ~LibClass174218()
    {
    }

    u8 unk60[0x20];
};

/** 0xB0-byte grid cell of LibClass1774E0 with its motion state at 0x80, with vtable D_177168 in main data. */
class LibClass177168 : public LibClass174218, public LibGridFrameMotion
{
public:
    LibClass177168();

    virtual ~LibClass177168();
};

/** 0xF0-byte grid cell, with vtable D_174208 in main data. */
class LibClass174208 : public LibClass174218
{
public:
    LibClass174208()
    {
    }

    virtual ~LibClass174208()
    {
    }

    u8 unk80[0x70];
};

/** 0x120-byte grid cell of LibClass177680, with vtable D_177158 in main data. */
class LibClass177158 : public LibClass174208
{
public:
    LibClass177158();

    virtual ~LibClass177158();

    u8 unkF0[0x30];
};

/** 0x140-byte grid cell of LibClass177750, with vtable D_1741F8 in main data. */
class LibClass1741F8 : public LibClass174208
{
public:
    LibClass1741F8()
    {
    }

    virtual ~LibClass1741F8()
    {
    }

    u8 unkF0[0x50];
};

/** 0x170-byte grid cell of LibClass174240, with vtable D_1741E8 in main data: the element, then its frame motion. */
class LibGridCell170 : public LibClass1741F8, public LibGridFrameMotion
{
public:
    LibGridCell170();

    virtual ~LibGridCell170();
};

/** 0x90-byte grid cell of LibClass177340, with vtable D_177178 in main data. */
class LibClass177178 : public LibClass174228
{
public:
    LibClass177178();

    virtual ~LibClass177178();

    u8 unk60[0x30];
};

/** 0x60-byte grid cell of LibClass1771A0, with vtable D_177188 in main data. */
class LibClass177188 : public LibClass173F48
{
public:
    LibClass177188();

    virtual ~LibClass177188();

    u8 unk30[0x30];
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

        /**
         * @brief Start a pass over the cells for an image model.
         * @param model Image model the pass builds packets for.
         */
        virtual void func_slot0c(void* model) = 0;

        /**
         * @brief Write the next batch's first stream into a scratchpad buffer.
         * @param count Most entries to write.
         * @param buffer Buffer to fill.
         * @param flag Pass flag.
         */
        virtual void func_slot10(s32 count, void* buffer, u8 flag);

        /**
         * @brief Write the next batch's second stream into a scratchpad buffer.
         * @param count Most entries to write.
         * @param buffer Buffer to fill.
         * @param flag Pass flag.
         */
        virtual void func_slot14(s32 count, void* buffer, u8 flag);

        /**
         * @brief Finish the next batch in a scratchpad buffer.
         * @param count Most entries to write.
         * @param buffer Buffer to fill.
         * @return Entries written; zero once the cells run out.
         */
        virtual s32 func_slot18(s32 count, void* buffer) = 0;

        /**
         * @brief Return a cell.
         * @param index Cell index.
         * @return The cell.
         */
        virtual LibClass174228* func_slot1c(s32 index) = 0;

        /**
         * @brief Return a value for a cell that image models hand back with it.
         * @param index Cell index.
         * @return The value.
         */
        virtual s32 func_slot20(s32 index) = 0;

        virtual u8* func_slot24(s32 index, s32 flag) = 0;

        virtual void func_slot28() = 0;

        /**
         * @brief Report whether the cells changed since the last update.
         * @return Nonzero when they did.
         */
        virtual s32 func_slot2c() = 0;

        virtual LibGridBitset* func_slot30() = 0;

        /**
         * @brief Report a size the image models scale their packet buffers by.
         * @return The size.
         */
        virtual s32 func_slot34() = 0;

        /**
         * @brief Report a divisor the image models size their packet buffers with.
         * @return The divisor.
         */
        virtual s32 func_slot38() = 0;

        virtual s32 func_slot3c();

        virtual void func_slot40(void* cell, void* records, u8 flag, const LibVector4* velocity, const LibVector4* angles,
                                 const LibVector4* scale, const LibVector4* angle_velocity, const LibVector4* scale_velocity) = 0;

        virtual void func_slot44(void* cell, void* records, u8 flag, const LibVector4* direction) = 0;

        /**
         * @brief Report how far the cells reach past their positions.
         * @return The extra radius.
         */
        virtual float func_slot48() = 0;

        virtual void func_slot4c() = 0;

        /**
         * @brief Take an image model's new image.
         * @param image Image entry.
         * @param pixels Data after the image entry's header.
         */
        virtual void func_slot50(void* image, void* pixels) = 0;

        /**
         * @brief Called with one when an image model clears its image.
         * @param value One.
         */
        virtual void func_slot54(s32 value) = 0;

        /**
         * @brief Reallocate the grid for a cell count and row width.
         * @param cells Number of cells.
         * @param columns Elements per row.
         */
        virtual void resize(s32 cells, s32 columns) = 0;

        virtual void func_slot5c() = 0;

        virtual u8 func_slot60() = 0;

        virtual void func_slot64() = 0;

        virtual void func_slot68() = 0;

        virtual void func_slot6c() = 0;

        virtual void func_slot70() = 0;

        virtual void func_slot74() = 0;

        virtual void func_slot78() = 0;

        virtual void func_slot7c(void* object) = 0;

        virtual s32 func_slot80() = 0;

        virtual void func_slot84() = 0;

        virtual void func_slot88() = 0;

        virtual void func_slot8c(void* object) = 0;

        virtual s32 func_slot90() = 0;

        virtual void func_slot94() = 0;

        virtual void func_slot98() = 0;

        virtual void func_slot9c() = 0;

        virtual void func_slota0(void* value) = 0;

        virtual void func_slota4(void* links) = 0;

        virtual void func_slota8() = 0;

        virtual void func_slotac(void* links) = 0;

        virtual void func_slotb0() = 0;

        virtual void func_slotb4() = 0;

        virtual void func_slotb8(float value) = 0;

        virtual void func_slotbc() = 0;

        /**
         * @brief Report whether the grid is ready for an image model to draw from.
         * @return Nonzero when ready.
         */
        virtual s32 func_slotc0() = 0;

        virtual void func_slotc4() = 0;

        virtual void func_slotc8() = 0;

        virtual void func_slotcc() = 0;

        virtual void func_slotd0() = 0;

        virtual void func_slotd4() = 0;

        u8 unk04;
        s32 user_count;
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
        float secondary_emission_scale;
        float unk44;
        LibClass173990* primary_emitter;
        u8 unk4C;
        u8 unk4D;
        u8 primary_emission_flags;
        u8 primary_emission_count;
        LibClass173990* secondary_emitter;
        u8 secondary_emission_flags;
        u8 secondary_emission_count;
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

/** Grid emitter with two more words at 0xB0 that its settings copy carries over. */
class LibGridEmitterB0 : public LibGridEmitter
{
    public:
        void* unkb0;
        void* unkb4;
};
#endif

#ifdef __cplusplus
/** Grid receiver the frame-vector updater at 0x48E550 reads: 0x447500's layout over LibClass177168 cells. */
typedef struct LibGridReceiver48E550
{
    u8 unk00[0xC];
    s32 cell_count;
    s32 columns;
    LibClass177168* cells;
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
} LibGridReceiver48E550;
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

#ifdef __cplusplus
/** Collider the grids' kind-6 particles test against: the first virtual reports a hit. */
class LibGridCollider
{
public:
    /**
     * @brief Test a particle.
     * @param transform Grid's transform.
     * @param position Particle position.
     * @param color Particle color.
     * @param travel Particle travel vector.
     * @param limit Grid's limit value.
     * @return Whether the particle hit.
     */
    virtual bool collide(const LibVector4* transform, const void* position, const void* color, const void* travel,
                         float limit) = 0;
};

extern "C" LibGridCollider* D_001B6540;

/** Ground the particle scripts measure heights against: the first virtual gives the height under a point. */
class LibGridGround
{
public:
    /**
     * @brief Measure the ground height under a point.
     * @param point Point, in the grid's space.
     * @param unused Always null here.
     * @return Ground height.
     */
    virtual float height(const LibVector4* point, void* unused) = 0;
};

extern "C" LibGridGround* D_001B654C;

/** Draw record a particle step writes per grid column. */
struct LibGridParticleOutput20
{
    LibGridVector4 position;
    LibGridVector4 color;
    LibGridVector4 unk20;
};

/** A scripted particle: the element part of a grid cell as the particle scripts use it. */
struct LibGridParticleCell
{
    u8 unk00[0x10];
    LibGridVector4 position;
    LibGridVector4 color;
    LibGridVector4 velocity;
    LibGridVector4 acceleration;
    LibGridVector4 travel;
    LibGridVector4 color_velocity;
    LibGridVector4 color_acceleration;
    LibGridVector4 angle;
    LibGridVector4 angle_velocity;
    LibGridVector4 angle_acceleration;
    LibGridVector4 radius;
    LibGridVector4 radius_velocity;
    LibGridVector4 radius_acceleration;
    LibGridVector4 swirl;
    LibGridVector4 unkf0;
    LibGridVector4 unk100;
    LibGridVector4 unk110;
    LibGridVector4 unk120;
    u8 script_pc;
    u8 flags;
    u8 color_mode;
    u8 wait_mode;
    float wait_value;
};

/**
 * @brief Zero a grid vector through a cleared local.
 * @param output Vector to clear.
 */
static inline void lib_grid_clear_vector(LibGridVector4* output)
{
    LibVector4 zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    zero.w = 0.0f;
    const LibVector4* value = &zero;
    output->packed = *(unsigned __int128*)value;
}

// TODO: Only here for the collide call's colour argument. Written as &cell->color the argument moves are
// issued in the wrong order.
/**
 * @brief Get a scripted particle's colour vector.
 * @param cell Particle.
 * @return The particle's colour.
 */
static inline LibGridVector4* lib_grid_particle_color(LibGridParticleCell* cell)
{
    return &cell->color;
}

struct LibColliderList;

/**
 * @brief Run a moving point through every collider in a list.
 * @param list Colliders to test.
 * @param previous Position before the step.
 * @param position Position after the step.
 * @param velocity Velocity over the step.
 * @param out_velocity Receives the velocity change.
 * @param out_position Receives the corrected position.
 * @return Whether any collider was hit.
 */
extern "C" bool func_0043CBF0(LibColliderList* list, const LibVector4* previous, const LibVector4* position,
                              const LibVector4* velocity, LibVector4* out_velocity, LibVector4* out_position);
#endif

#endif
