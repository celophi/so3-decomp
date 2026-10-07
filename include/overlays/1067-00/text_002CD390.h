#ifndef SO3_OVERLAYS_1067_00_TEXT_002CD390_H
#define SO3_OVERLAYS_1067_00_TEXT_002CD390_H

#include "types.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_002CABC0.h"
#else
typedef struct FieldBytePtr10 FieldBytePtr10;
#endif

typedef struct FieldStateCD390 FieldStateCD390;
/** Field list parameters preceding the callback base. */
typedef struct FieldStateCE420
{
    struct LibClass178600* unk00;
    struct LibClass178600* unk04;
    float unk08;
    float unk0c;
    u8 pad10[0xA];
    u16 unk1a;
    u16 unk1c;
    u8 pad1e[4];
    s16 unk22;
    s16 unk24;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 pad29[2];
    u8 unk2b;
    u32 unk2c;
    u8 pad30[4];
    float unk34;
    float unk38;
    u8 unk3c;
    u8 unk3d[3];
} FieldStateCE420;
typedef struct FieldObjectCE8D0 FieldObjectCE8D0;

/** Sentinel node containing an opaque display payload and the next link. */
typedef struct FieldListNode
{
    void* unk00;
    struct FieldListNode* unk04;
} FieldListNode;

/** Sentinel-based display list with its stored node count. */
typedef struct FieldCountedList
{
    FieldListNode* unk00;
    s32 unk04;
} FieldCountedList;

#ifdef __cplusplus
struct LibObject178660;

/** Partial interface of Field's window base, primary vtable 0x15AE70 (destructor in Field). */
class FieldClass15AE70
{
public:
    /** Construct the window base and its members (out of line in Field). */
    FieldClass15AE70();
    /** Destroy the window base. */
    virtual ~FieldClass15AE70();
    // Placeholder virtuals in their vtable order (byte offset in the name); only
    // their positions are known.
    virtual void func_slot0c();
    /**
     * @brief Create the nested display at the supplied coordinates.
     * @param associated Object associated with the window.
     * @param x Horizontal coordinate.
     * @param y Vertical coordinate.
     * @param code Nested display initializer code.
     * @return One when the nested display and associated object are present, or zero otherwise.
     */
    virtual s32 func_slot10(void* associated, float x, float y, s32 code);
    /**
     * @brief Create the nested container with the supplied modes and coordinates.
     * @param associated Opaque value associated with the window.
     * @param first First container mode.
     * @param second Second container mode.
     * @param third Third container mode.
     * @param x Horizontal coordinate.
     * @param y Vertical coordinate.
     * @param z Third transform coordinate.
     * @return One when the container and associated value are present, or zero otherwise.
     */
    virtual s32 func_slot14(void* associated, s32 first, s32 second, s32 third, float x, float y, float z);
    /**
     * @brief Set display flags on the selected window lists.
     * @param flag Flag word forwarded to grids; its low byte updates other displays.
     * @param list_mask List groups selected by bits 0 through 6.
     */
    virtual void func_slot18(u32 flag, u32 list_mask);
    /** @brief Store the byte state and halfword flags. @param code Byte state code. @param flags Halfword state flags. */
    virtual void func_slot1c(u8 code, u16 flags);
    /** @brief Set the nested display byte flag. @param flag Flag value. */
    virtual void func_slot20(u32 flag);
    /** @brief Store the window control byte. @param value Control value. */
    virtual void func_slot24(u8 value);
    /** @brief Read the window control byte. @return Control value. */
    virtual u8 func_slot28();
    /** @brief Store the byte state code. @param value State code. */
    virtual void func_slot2c(u8 value);
    /** @brief Read the byte state code. @return State code. */
    virtual u8 func_slot30();
    /** @brief Store the halfword state flags. @param value State flags. */
    virtual void func_slot34(u16 value);
    /** @brief Read the halfword state flags. @return State flags. */
    virtual u16 func_slot38();
    virtual void func_slot3c();
    /** @brief Store the associated window pointer. @param associated Pointer to store. */
    virtual void func_slot40(void* associated)
    {
        unk98 = associated;
    }
    /** @brief Return the associated window pointer. @return Stored pointer. */
    virtual void* func_slot44()
    {
        return unk98;
    }
    /** @brief Store the alternate window pointer. @param associated Pointer to store. */
    virtual void func_slot48(void* associated);
    /** @brief Return the alternate associated window. @return Stored pointer. */
    virtual void* func_slot4c();
    /** @brief Store the opaque source word. @param value Word to store. */
    virtual void func_slot50(u32 value);
    /** @brief Return the stored opaque source pointer. @return Stored pointer. */
    virtual void* func_slot54();
    /** @brief Return the nested display container. @return Stored container. */
    virtual LibObject178660* func_slot58();
    virtual void func_slot5c();
    /** @brief Set the window message by signed text key. @param text_key Message key or relative index. */
    virtual void func_slot60(s32 text_key);
    virtual void func_slot64();
    virtual void func_slot68();
    virtual void func_slot6c();
    virtual void func_slot70();
    virtual void func_slot74();
    virtual void func_slot78();
    virtual void func_slot7c();
    virtual void func_slot80();
    virtual void func_slot84();
    virtual void func_slot88();
    virtual void func_slot8c();
    virtual void func_slot90();
    virtual void func_slot94();
    virtual void func_slot98();
    virtual void func_slot9c();
    virtual void func_slota0();
    virtual void func_slota4();
    virtual void func_slota8();
    virtual void func_slotac();
    virtual s32 func_slotb0();
    virtual s32 func_slotb4();
    virtual s32 func_slotb8();
    virtual s32 func_slotbc();
    virtual s32 func_slotc0();
    virtual s32 func_slotc4();
    virtual s32 func_slotc8();
    virtual s32 func_slotcc();
    virtual s32 func_slotd0();
    virtual s32 func_slotd4();
    virtual s32 func_slotd8();
    virtual s32 func_slotdc();
    virtual void func_slote0();
    virtual void func_slote4();
    virtual u8 func_slote8();
    virtual void func_slotec(u8 value);
    virtual void func_slotf0();
    u8 unk04[4];
    u8 unk08;
    u8 unk09;
    u16 unk0a;
    u8 unk0c;
    u8 unk0d[3];
    LibObject178660* unk10;
    u8 unk14[0xC];
    FieldCountedList unk20;
    u8 pad28[4];
    FieldCountedList unk2c;
    u8 unk34[0x40];
    FieldCountedList unk74;
    u8 unk7c[0x10];
    FieldCountedList unk8c;
    u8 unk94[4];
    void* unk98;
    void* unk9c;
    u8 unka0[4];
    float unka4;
};

/** Field list callback base with a parameter prefix and two update hooks. */
class FieldClass15AE60 : public FieldStateCE420
{
public:
    /** @brief Refresh the visible record rows. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Position the row displays. @param start Base vertical coordinate. */
    virtual void set_scroll_position(float start);
    u8 unk44[4];
    LibClass178600* unk48[12];
    u8 unk78[0xC];
    u8 unk84;
    u8 unk85;
    u8 unk86[2];
    s32 unk88;
    u8 unk8c;
    u8 unk8d[3];
};

/** Field list window with its callback base at offset 0xA8. */
class FieldClass15AD40 : public FieldClass15AE70, public FieldClass15AE60
{
public:
    FieldClass15AD40();
    virtual ~FieldClass15AD40();
    virtual s32 func_slot104(void* associated);
    /** @brief Refresh the list for a category. @param category Category byte supplied by the associated state. */
    virtual void func_slot108(u8 category);
    /**
     * @brief Set the paired display flags and update auxiliary displays.
     * @param value Low byte stored in each paired display flag.
     * @param alternate Auxiliary flag value; its full value selects the height.
     */
    virtual void func_slot10c(u32 value, u32 alternate);
    /** @brief Set the list flag. @param value Flag value to store. */
    virtual void func_slot110(u8 value);
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the float at offset 0x14 to one when the state bit is set.
 * @param object Receiver containing the float and state bit.
 * @return Zero when the bit was set; one otherwise.
 */
s32 func_002CD390(FieldStateCD390* object);

/** @brief Perform no action. @param object Receiver; unused. */
void func_002CD780(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CD790(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CD7A0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CD7B0(void* object);

/**
 * @brief Store two byte values and two halfwords, copy the current floats, and clear related state.
 * @param object Receiver to update.
 * @param first First byte value.
 * @param second Value whose low byte is stored.
 * @param third First halfword value.
 * @param fourth Second halfword value.
 */
void func_002CE420(FieldStateCE420* object, u8 first, u32 second, u16 third, u16 fourth);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
int func_002CD9E0(void* object);

/**
 * @brief Store a byte in the selected object when present.
 * @param object Receiver containing the selected object.
 * @param value Value whose low byte is stored.
 */
void func_002CE510(FieldBytePtr10* object, u32 value);

/**
 * @brief Create a nested display and initialize it with the associated object and coordinates.
 * @param object Receiver that owns the nested display.
 * @param associated Associated object forwarded to the receiver's handler.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @param code Value forwarded to the nested display initializer.
 * @return One when the nested display and associated object are present, or zero otherwise.
 */
s32 func_002CE8D0(FieldObjectCE8D0* object, void* associated, float x, float y, s32 code);

#ifdef __cplusplus
}
#endif

#endif
