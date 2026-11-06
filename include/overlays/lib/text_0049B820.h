#ifndef SO3_OVERLAYS_LIB_TEXT_0049B820_H
#define SO3_OVERLAYS_LIB_TEXT_0049B820_H

#include "types.h"

#ifdef __cplusplus
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/render_channel.h"
#include "overlays/lib/emission.h"

enum
{
    LIB_LOD_LEVEL_CAPACITY = 8,
    LIB_LOD_OBJECT_CAPACITY = 64
};

/** Partial level-selection controller with primary vtable at 0x177960. */
class LibLodController : public LibTransform
{
public:
    /** @brief Initialize the level-selection controller. */
    LibLodController();
    /** @brief Destroy the controller. */
    virtual ~LibLodController();
    /** @brief Report the controller kind. @return Kind nine. */
    virtual s32 get_default_list_kind();
    /** @brief Select the active object range from the current transformed depth. */
    virtual void update();
    /** @brief Copy level-selection state and inherited transform state. @param source Source controller. */
    virtual void copy_state(const LibLodController* source);

    /**
     * @brief Store and apply an offset to the controller's position.
     * @param offset Position offset.
     */
    void apply_position_offset(const FieldVec4A& offset);

    u8 position_offset_applied;
    u8 unk211[3];
    s32 object_count;
    s32 level_boundaries[LIB_LOD_LEVEL_CAPACITY];
    s32 level_count;
    s32 active_level;
    float range_minimums[LIB_LOD_LEVEL_CAPACITY];
    float range_maximums[LIB_LOD_LEVEL_CAPACITY];
    void* display_manager;
    void* objects[LIB_LOD_OBJECT_CAPACITY];
    u8 unk384[0xC];
    FieldVec4B position_offset;
};

typedef LibLodController LibEntryHandleCollection;

/** Lib object whose update pass draws the renderer's frame, with vtable D_177940 in main data. */
class LibClass177940 : public LibListObject
{
public:
    /** @brief Destroy the object. */
    virtual ~LibClass177940();

    /**
     * @brief Report the list kind used when registration requests the default.
     * @return Thirteen.
     */
    virtual s32 get_default_list_kind();

    /** @brief Draw the renderer's frame and wait for its packets, between two calls on the resident sound. */
    virtual void update();

    /** EE timer 0 count when the frame was drawn. */
    u32 frame_start_time;

    LibRenderer* renderer;
};

/** Partial grid base with vtable D_173A40 in main data. */
class LibClass173A40 : public LibClass173A28
{
    public:
        /** @brief Clear unk08. */
        LibClass173A40()
        {
            unk08 = 0;
        }

        /** @brief Destroy the grid base. */
        virtual ~LibClass173A40()
        {
        }

        virtual void func_slot0C() = 0;

        /** @brief Do nothing (shared by every grid). */
        virtual void func_slot10();

        /** @brief Do nothing (shared by every grid). */
        virtual void func_slot14();

        virtual void func_slot18() = 0;
        virtual void func_slot1C() = 0;
        virtual void func_slot20() = 0;
        virtual void func_slot24() = 0;
        virtual void func_slot28() = 0;
        virtual void func_slot2C() = 0;
        virtual void func_slot30() = 0;
        virtual void func_slot34() = 0;
        virtual void func_slot38() = 0;

        /**
         * @brief Report no selected cell.
         * @return -1.
         */
        virtual s32 func_slot3C();

        virtual void func_slot40() = 0;
        virtual void func_slot44() = 0;
        virtual void func_slot48() = 0;
        virtual void func_slot4C() = 0;
        virtual void func_slot50() = 0;
        virtual void func_slot54() = 0;

        /**
         * @brief Reallocate the grid's storage for a new size.
         * @param rows Cell count.
         * @param columns Secondary elements per cell plus one.
         */
        virtual void resize(s32 rows, s32 columns) = 0;

        virtual void func_slot5C() = 0;
        virtual void func_slot60() = 0;
        virtual void func_slot64() = 0;
        virtual void func_slot68() = 0;
        virtual void func_slot6C() = 0;
        virtual void func_slot70() = 0;
        virtual void func_slot74() = 0;
        virtual void func_slot78() = 0;
        virtual void func_slot7C() = 0;
        virtual void func_slot80() = 0;
        virtual void func_slot84() = 0;
        virtual void func_slot88() = 0;
        virtual void func_slot8C() = 0;
        virtual void func_slot90() = 0;
        virtual void func_slot94() = 0;
        virtual void func_slot98() = 0;
        virtual void func_slot9C() = 0;
        virtual void func_slotA0() = 0;
        virtual void func_slotA4() = 0;
        virtual void func_slotA8() = 0;
        virtual void func_slotAC() = 0;
        virtual void func_slotB0() = 0;

        /**
         * @brief Copy another grid's settings, resizing this grid to match.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source) = 0;

        virtual void func_slotB8() = 0;
        virtual void func_slotBC() = 0;
        virtual void func_slotC0() = 0;
        virtual void func_slotC4() = 0;
        virtual void func_slotC8() = 0;
        virtual void func_slotCC() = 0;

        u8 unk04;
        u32 unk08;
        s32 unk0c;
        s32 unk10;
        void* unk14;
        void* unk18;
        void* unk1c;
        void* unk20;
        void* unk24;
};

/** Partial grid with vtable D_1771A0 in main data. */
class LibClass1771A0 : public LibClass173A40
{
    public:
        /** @brief Start with no storage. */
        LibClass1771A0();

        /** @brief Release the grid's storage. */
        virtual ~LibClass1771A0();

        /**
         * @brief Copy another grid's size and resize this grid to match.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);
};

/** Partial grid with vtable D_177270 in main data. */
class LibClass177270 : public LibClass173A40
{
    public:
        /** @brief Start with no storage. */
        LibClass177270();

        /** @brief Release the grid's storage. */
        virtual ~LibClass177270();

        /**
         * @brief Copy another grid's size and resize this grid to match.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);
};

/** Partial grid with vtable D_177340 in main data. */
class LibClass177340 : public LibClass173A40
{
    public:
        /** @brief Start with no storage. */
        LibClass177340();

        /** @brief Release the grid's storage. */
        virtual ~LibClass177340();

        /**
         * @brief Copy another grid's size and resize this grid to match.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);
};

/** Partial grid with vtable D_177410 in main data. */
class LibClass177410 : public LibClass173A40
{
    public:
        /** @brief Start with no storage. */
        LibClass177410();

        /** @brief Release the grid's storage. */
        virtual ~LibClass177410();

        /**
         * @brief Copy another grid's size and resize this grid to match.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);
};

/** Partial grid with vtable D_1774E0 in main data. */
class LibClass1774E0 : public LibClass173A40
{
    public:
        /** @brief Start with no storage. */
        LibClass1774E0();

        /** @brief Release the grid's storage. */
        virtual ~LibClass1774E0();

        /**
         * @brief Copy another grid's size and resize this grid to match.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);
};

/** Partial grid with vtable D_1775B0 in main data. */
class LibClass1775B0 : public LibClass173A40
{
    public:
        /** @brief Start with no storage. */
        LibClass1775B0();

        /** @brief Release the grid's storage. */
        virtual ~LibClass1775B0();

        /**
         * @brief Copy another grid's size and resize this grid to match.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);
};

/** Partial grid with vtable D_177680 in main data. */
class LibClass177680 : public LibClass173A40
{
    public:
        /** @brief Start with no storage. */
        LibClass177680();

        /** @brief Release the grid's storage. */
        virtual ~LibClass177680();

        /**
         * @brief Copy another grid's size and resize this grid to match.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);
};

/** Partial grid with vtable D_177750 in main data. */
class LibClass177750 : public LibClass173A40
{
    public:
        /** @brief Start with no storage. */
        LibClass177750();

        /** @brief Release the grid's storage. */
        virtual ~LibClass177750();

        /**
         * @brief Copy another grid's size and resize this grid to match.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);
};

/** Partial grid with vtable D_174240 in main data. */
class LibClass174240 : public LibClass173A40
{
    public:
        /** @brief Start with no storage. */
        LibClass174240();

        /** @brief Release the grid's storage. */
        virtual ~LibClass174240();

        /**
         * @brief Copy another grid's size and resize this grid to match.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);
};

/** Partial grid that drives linked emitters, with vtable D_176FC0 in main data. */
class LibClass176FC0 : public LibClass177750
{
    public:
        /** @brief Start with default emission settings. */
        LibClass176FC0()
        {
            unk38 = 1.0f;
            unk44 = 0;
            unk48 = 0;
            unk4c = 0;
            unk4d = 0;
            unk4f = 1;
            unk50 = 0;
            unk55 = 1;
            unk56 = 0;
            unk57 = 0;
            unk04 = 1;
        }

        /** @brief Destroy the grid. */
        virtual ~LibClass176FC0();

        /**
         * @brief Copy another grid's size and emission settings.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);

        float unk28;
        u32 unk2c;
        float unk30;
        float unk34;
        float unk38;
        float unk3c;
        u8 unk40[4];
        u32 unk44;

        /** Primary linked emitter. */
        LibClass173990* unk48;

        u8 unk4c;
        u8 unk4d;
        u8 unk4e;
        u8 unk4f;
        u32 unk50;
        u8 unk54;
        u8 unk55;
        u8 unk56;
        u8 unk57;
        u8 unk58[8];
        LibVector4 unk60[4];
        u32 unka0;
        u32 unka4;
        u8 unka8[8];
};

/** Partial LibClass176FC0 with vtable D_177090 in main data. */
class LibClass177090 : public LibClass176FC0
{
    public:
        /** @brief Start with no storage. */
        LibClass177090();

        /** @brief Free the storage unless it's borrowed, then destroy the grid. */
        virtual ~LibClass177090();

        /**
         * @brief Copy another grid's size, emission settings and storage settings.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);

        void* unkb0;
        void* unkb4;
        void* unkb8;
        void* unkbc;
        u32 unkc0;
        u32 unkc4;
        u8 unkc8;

        /** Nonzero when unkb0 and unkb4 are borrowed and must not be freed. */
        u8 unkc9;

        u8 unkca[6];
};

/** Partial grid that drives linked emitters, with vtable D_174050 in main data. */
class LibClass174050 : public LibClass174240
{
    public:
        /** @brief Start with default emission settings. */
        LibClass174050()
        {
            unk38 = 1.0f;
            unk44 = 0;
            unk48 = 0;
            unk4c = 0;
            unk4d = 0;
            unk4f = 1;
            unk50 = 0;
            unk55 = 1;
            unk56 = 0;
            unk57 = 0;
            unk04 = 1;
        }

        /** @brief Destroy the grid. */
        virtual ~LibClass174050();

        /**
         * @brief Copy another grid's size and emission settings.
         * @param source Grid to copy.
         */
        virtual void copy_settings(const LibClass173A40* source);

        float unk28;
        u32 unk2c;
        float unk30;
        float unk34;
        float unk38;
        float unk3c;
        u8 unk40[4];
        u32 unk44;

        /** Primary linked emitter. */
        LibClass173990* unk48;

        u8 unk4c;
        u8 unk4d;
        u8 unk4e;
        u8 unk4f;
        u32 unk50;
        u8 unk54;
        u8 unk55;
        u8 unk56;
        u8 unk57;
        u8 unk58[8];
        LibVector4 unk60[4];
        u32 unka0;
        u32 unka4;
        u8 unka8[8];
};

/** Partial LibClass174050 with vtable D_174120 in main data. */
class LibClass174120 : public LibClass174050
{
    public:
        /** @brief Start with no storage. */
        LibClass174120();

        /** @brief Free the storage unless it's borrowed, then destroy the grid. */
        virtual ~LibClass174120();

        void* unkb0;
        void* unkb4;
        void* unkb8;
        void* unkbc;
        u32 unkc0;
        u32 unkc4;
        u8 unkc8;

        /** Nonzero when unkb0 and unkb4 are borrowed and must not be freed. */
        u8 unkc9;

        u8 unkca[6];
};
#else
/** Opaque level-selection controller used by the C handle-collection interface. */
typedef struct LibLodController LibEntryHandleCollection;
#endif

#ifdef __cplusplus
extern "C" {
void func_004A4510(void* receiver);
#endif

/** Return the mapped entry after the indexed 0x140-byte record. */
void* func_004A08C0(const void* object, s32 index);

/**
 * @brief Append a handle when the collection has fewer than sixty-four entries.
 * @param collection Destination collection.
 * @param object Handle to append.
 */
void lib_append_entry_handle(LibEntryHandleCollection* collection, void* object);

/**
 * @brief Update the renderable object's resource buffers and state flags.
 * @param object Renderable object.
 */
void func_004A2370(void* object);

/**
 * @brief Set renderable resource state when its buffers are eligible.
 * @param object Renderable receiver.
 * @return One when state was applied, or zero when the request was skipped.
 */
s32 func_004A29D0(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2200(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2210(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2220(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2230(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2240(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2250(void* object);

/** Return the floating-point value 1.0f. */
float func_004A2260(void* object);

/** Return the floating-point value 1.0f. */
float func_004A22B0(void* object);

/** Return the fixed integer value 1. */
s32 func_004A08B0(void* object);

/** Return the fixed integer value 11. */
s32 func_004A8FF0(void* object);

/** Return the fixed value 0. */
s32 func_004A0C50(void* object);

/** Return the fixed value 0. */
s32 func_004A0C70(void* object);

/** Return the fixed value 0. */
s32 func_004AA410(void* object);

void func_004A08A0(void* object);
void func_004A0C40(void* object);
void func_004A0C60(void* object);
void func_004A9220(void* object);
void func_004A9230(void* object);

/** Clear the word at receiver offset 0x2C and copy four aligned values from the source. */
void func_004A06B0(void* object, const void* source);

/** Queue the receiver's DMA submission object and return its queue result. */
s32 func_004A4570(void* object);

/**
 * @brief Queue the object's receiver for deferred destruction.
 * @param object Object containing the receiver at offset 0x14, or null.
 */
void lib_queue_object_release(void* object);

/** Forward the receiver to lib_finish_packet. */
void func_004A4550(void* object);

#ifdef __cplusplus
}
#endif

#endif
