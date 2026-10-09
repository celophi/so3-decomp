#ifndef SO3_OVERLAYS_1067_00_TEXT_002CD390_H
#define SO3_OVERLAYS_1067_00_TEXT_002CD390_H

#include "types.h"
#include "main/resident_001001E0.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_002CABC0.h"
#include "overlays/1067-00/text_001DD3C0.h"
#else
typedef struct FieldBytePtr10 FieldBytePtr10;
#endif

#ifdef __cplusplus
class FieldClass15AE70;
#else
typedef struct FieldClass15AE70 FieldClass15AE70;
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
#ifdef __cplusplus

    /** @brief Release the link without destroying its payload. */
    ~FieldListNode()
    {
    }
#endif
} FieldListNode;

/** Sentinel-based display list with its stored node count. */
typedef struct FieldCountedList
{
    FieldListNode* unk00;
    s32 unk04;
} FieldCountedList;

#ifdef __cplusplus
/** Pointer list with vtable D_153EC0 in main data. */
class FieldClass153EC0 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass153EC0();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass153EC0();
};

/** Pointer list with vtable D_154BA0 in main data. */
class FieldClass154BA0 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass154BA0();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass154BA0();
};

/** Pointer list with vtable D_15AF68 in main data. */
class FieldClass15AF68 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15AF68();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15AF68();
};

/** Pointer list with vtable D_15AF78 in main data. */
class FieldClass15AF78 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15AF78();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15AF78();
};

/** Pointer list with vtable D_15AF88 in main data. */
class FieldClass15AF88 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15AF88();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15AF88();
};

/** Pointer list with vtable D_15AF98 in main data. */
class FieldClass15AF98 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15AF98();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15AF98();
};

/** Pointer list with vtable D_15AFA8 in main data. */
class FieldClass15AFA8 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15AFA8();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15AFA8();
};

/** Pointer list with vtable D_15AFB8 in main data. */
class FieldClass15AFB8 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15AFB8();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15AFB8();
};

/** Pointer list with vtable D_15AFC8 in main data. */
class FieldClass15AFC8 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15AFC8();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15AFC8();
};

/** Pointer list with vtable D_15AFD8 in main data. */
class FieldClass15AFD8 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15AFD8();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15AFD8();
};

/** Pointer list with vtable D_15AFE8 in main data. */
class FieldClass15AFE8 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15AFE8();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15AFE8();
};

/** Pointer list with vtable D_15AFF8 in main data. */
class FieldClass15AFF8 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15AFF8();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15AFF8();
};

/** Pointer list with vtable D_15B008 in main data. */
class FieldClass15B008 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15B008();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15B008();
};

/** Pointer list with vtable D_15B9F8 in main data. */
class FieldClass15B9F8 : public FieldCountedList
{
public:
    /** @brief Allocate the sentinel and initialize the empty list. */
    FieldClass15B9F8();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~FieldClass15B9F8();
};

struct LibObject178660;

/** Partial interface of Field's window base, primary vtable 0x15AE70 (destructor in Field). */
class FieldClass15AE70 : public FieldClass150050
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
     * @param associated Full resource source word.
     * @param x Horizontal coordinate.
     * @param y Vertical coordinate.
     * @param code Nested display initializer code.
     * @return One when the nested display is present and the source word is nonzero, or zero otherwise.
     */
    virtual s32 func_slot10(u32 associated, float x, float y, s32 code);
    /**
     * @brief Create the nested container with the supplied modes and coordinates.
     * @param associated Full resource source word.
     * @param first First container mode.
     * @param second Second container mode.
     * @param third Third container mode.
     * @param x Horizontal coordinate.
     * @param y Vertical coordinate.
     * @param z Third transform coordinate.
     * @return One when the container is present and the source word is nonzero, or zero otherwise.
     */
    virtual s32 func_slot14(u32 associated, s32 first, s32 second, s32 third, float x, float y, float z);
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
    /**
     * @brief Return the final window in the associated-window chain.
     * @return Last window, including this window when it has no association.
     */
    virtual void* func_slot3c();
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
    /** @brief Return the stored resource source word. @return Stored word. */
    virtual u32 func_slot54();
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
    u32 unk04;
    u8 unk08;
    u8 unk09;
    u16 unk0a;
    u8 unk0c;
    u8 unk0d;
    u8 unk0e[2];
    LibObject178660* unk10;
    FieldClass15AF68 unk14;
    FieldClass15AF78 unk20;
    FieldClass15AF88 unk2c;
    FieldClass15AF98 unk38;
    FieldClass15AFA8 unk44;
    FieldClass15AFB8 unk50;
    FieldClass15AFC8 unk5c;
    FieldClass15AFD8 unk68;
    FieldClass15AFE8 unk74;
    FieldClass15AFF8 unk80;
    FieldClass15B008 unk8c;
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
    virtual s32 func_slot104(u32 associated);
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
 * @brief Create and configure the window's nested display container.
 * @param object Field window receiver.
 * @param associated Full resource source word.
 * @param first First container configuration value.
 * @param second Second container configuration value.
 * @param third Third container configuration value.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @param z Third coordinate.
 * @return One when the container is present and the source word is nonzero, otherwise zero.
 */
s32 func_002CE760(FieldClass15AE70* object, u32 associated, s32 first, s32 second, s32 third, float x, float y, float z);

/**
 * @brief Create a nested display and initialize it with the resource source word and coordinates.
 * @param object Receiver that owns the nested display.
 * @param associated Full resource source word.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @param code Value forwarded to the nested display initializer.
 * @return One when the nested display is present and the source word is nonzero, or zero otherwise.
 */
s32 func_002CE8D0(FieldObjectCE8D0* object, u32 associated, float x, float y, s32 code);

#ifdef __cplusplus
}
#endif

#endif
