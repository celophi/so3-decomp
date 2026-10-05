#ifndef SO3_OVERLAYS_CITEMCREATION_TEXT_00358440_H
#define SO3_OVERLAYS_CITEMCREATION_TEXT_00358440_H

#include "types.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/citemcreation/text_003684D0.h"
#ifdef __cplusplus
#include "overlays/lib/text_004BD360.h"
#endif

typedef struct ItemCreationCategoryOwner ItemCreationCategoryOwner;
typedef struct ItemCreationCategoryRecord ItemCreationCategoryRecord;
typedef struct ItemCreationIdentifierOwner ItemCreationIdentifierOwner;
struct ItemCreationAllocationRecord;
struct LibObject178660;

/** Partial item display with its decoded halfword and adjacent byte. */
typedef struct ItemCreationAllocationDisplay
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0xBC];
    u16 unkfc;
    u8 unkfe;
} ItemCreationAllocationDisplay;

/** Two nested markers allocated for each checked item display. */
typedef struct ItemCreationAllocationDisplayPair
{
    struct ItemCreationFlagNode* unk00;
    struct ItemCreationFlagNode* unk04;
} ItemCreationAllocationDisplayPair;

/** Partial owner of three checked item displays, marker pairs, and quantity displays. */
typedef struct ItemCreationCheckedAllocationView
{
    u8 unk00[0x10C];
    s16 unk10c;
    u8 unk10e[0xE];
    ItemCreationAllocationDisplay* unk11c[3];
    ItemCreationAllocationDisplayPair unk128[3];
    struct ItemCreationValueDisplay* unk140[3];
} ItemCreationCheckedAllocationView;

/** Partial owner of the value display refreshed from a checked record. */
typedef struct ItemCreationCheckedValueOwner
{
    u8 unk00[0xE4];
    struct ItemCreationValueDisplay* unke4;
} ItemCreationCheckedValueOwner;

/** Partial owner of two value displays refreshed from the current checked record. */
typedef struct ItemCreationTwoCheckedValueOwner
{
    u8 unk00[0xD0];
    struct ItemCreationValueDisplay* unkd0;
    u8 unkd4[4];
    struct ItemCreationValueDisplay* unkd8;
} ItemCreationTwoCheckedValueOwner;

/** Partial panel with paired markers, selected-state codes and value displays. */
typedef struct ItemCreationPanelView
{
    u8 unk00[0x38];
    struct ItemCreationListNode* unk38;
    u8 unk3c[0x6C];
    struct ItemCreationSelectedDisplayState* unka8;
    u8 unkac[0x24];
    u8 unkd0[8];
    u16 unkd8;
    u8 unkda[0xA];
    struct ItemCreationValueDisplay* unke4;
    struct ItemCreationPanelMarker* unke8[9];
    u8 unk10c;
    u8 unk10d;
    u8 unk10e[2];
    u32 unk110[3];
    u8 unk11c[4];
    struct ItemCreationValueDisplay* unk120;
} ItemCreationPanelView;

/** Partial resource view with nine assigned and fourteen available displays. */
typedef struct ItemCreationAvailableResourceView
{
    u8 unk00[0xA8];
    struct ItemCreationIndexedResourceDisplay* unka8[9];
    struct ItemCreationIndexedResourceDisplay* unkcc[14];
    u8 unk104[0x1C];
    struct ItemCreationSelectedDisplayState* unk120;
    u8 unk124;
} ItemCreationAvailableResourceView;

/** Partial owner of two color displays, a selector, and its target display. */
typedef struct ItemCreationTwoColorOwner
{
    u8 unk00[0xB4];
    struct ItemCreationColorDisplay* unkb4[2];
    u8 unkbc[0x10];
    struct FieldState23B3A0* unkcc;
    struct FieldObject23B950* unkd0;
} ItemCreationTwoColorOwner;

/** Partial view with nine markers and two twelve-marker groups. */
typedef struct ItemCreationNineSlotView
{
    u8 unk00[0xA8];
    struct ItemCreationSelectedDisplayState* unka8;
    struct FieldObject23CEA0* unkac;
    struct FieldObject23CEA0* unkb0;
    struct FieldObject23CEA0* unkb4;
    struct ItemCreationFlagNode* unkb8[9];
    struct ItemCreationFlagNode* unkdc[12];
    struct ItemCreationFlagNode* unk10c[12];
    struct FieldResourceDisplay2D5CF0* unk13c[9];
    u8 unk160[0x30];
    u8 unk190;
    u8 unk191[3];
    struct ItemCreationFlagNode* unk194[3];
    struct ItemCreationFlagNode* unk1a0[3];
    struct ItemCreationFlagNode* unk1ac[3];
    struct ItemCreationColorDisplay* unk1b8[3];
    struct ItemCreationColorDisplay* unk1c4[3];
    struct ItemCreationColorDisplay* unk1d0[3];
    struct ItemCreationColorDisplay* unk1dc[3];
    u8 unk1e8[9];
    u8 unk1f1;
    u8 unk1f2[9];
} ItemCreationNineSlotView;

/** Partial view with three activatable displays and fourteen selection markers. */
typedef struct ItemCreationFourteenSlotView
{
    u8 unk00[0xA8];
    struct ItemCreationSelectedDisplayState* unka8;
    struct FieldObject23CEA0* unkac;
    struct FieldObject23CEA0* unkb0;
    struct FieldObject23CEA0* unkb4;
    struct ItemCreationFlagNode* unkb8[14];
    struct FieldResourceDisplay2D5CF0* unkf0[14];
} ItemCreationFourteenSlotView;

/** Partial state containing three triples of item bytes. */
typedef struct ItemCreationTripleState
{
    u8 unk00[0x1F2];
    u8 unk1f2[3][3];
} ItemCreationTripleState;

/** Partial nested item with two flag bytes and a float setting. */
typedef struct ItemCreationNested
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0x30];
    float unk70;
} ItemCreationNested;

/** Partial owner of six pairs of nested items and optional auxiliary items. */
typedef struct ItemCreationPairOwner
{
    u8 unk00[0xA8];
    ItemCreationNested* unka8;
    ItemCreationNested* unkac;
    u8 unkb0[0x88];
    ItemCreationNested* unk138[6];
    ItemCreationNested* unk150[6];
    u8 unk168[0x24];
    ItemCreationNested* unk18c;
} ItemCreationPairOwner;

#ifdef __cplusplus
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
    virtual void func_slot14();
    virtual void func_slot18();
    virtual void func_slot1c();
    /** @brief Set the nested display byte flag. @param flag Flag value. */
    virtual void func_slot20(u8 flag);
    virtual void func_slot24();
    virtual void func_slot28();
    virtual void func_slot2c();
    virtual void func_slot30();
    virtual void func_slot34();
    virtual void func_slot38();
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
    virtual void func_slot48();
    /** @brief Return the alternate associated window. @return Stored pointer. */
    virtual void* func_slot4c();
    virtual void func_slot50();
    /** @brief Return the stored opaque source pointer. @return Stored pointer. */
    virtual void* func_slot54();
    /** @brief Return the nested display container. @return Stored container. */
    virtual LibObject178660* func_slot58();
    virtual void func_slot5c();
    virtual void func_slot60();
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
    u8 unk04[0xC];
    LibObject178660* unk10;
    u8 unk14[0x18];
    ItemCreationCountedList unk2c;
    u8 unk34[0x40];
    ItemCreationCountedList unk74;
    u8 unk7c[0x1C];
    void* unk98;
    u8 unk9c[0xC];
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
    virtual void func_slot108();
    /**
     * @brief Set the paired display flags and update auxiliary displays.
     * @param value Low byte stored in each paired display flag.
     * @param alternate Auxiliary flag value; its full value selects the height.
     */
    virtual void func_slot10c(u32 value, u32 alternate);
    /** @brief Set the list flag. @param value Flag value to store. */
    virtual void func_slot110(u8 value);
};

/** Item creation category list with primary vtable at 0x186B70. */
class ItemCreationClass186B70 : public FieldClass15AD40
{
public:
    /** @brief Release the optional panel and destroy the Field list window. */
    virtual ~ItemCreationClass186B70();
    /** @brief Release the category container and base window contents. */
    virtual void func_slot0c();
    /** @brief Update the category rows and selected item preview. */
    virtual void func_slot5c();
    virtual s32 func_slotb0();
    /** @brief Restore the category display or its parent. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Toggle the selected item preview. @return Always zero. */
    virtual s32 func_slotb8();
    /**
     * @brief Create the category list and item preview displays.
     * @param associated Object associated with the window.
     * @return Always one.
     */
    virtual s32 func_slot104(void* associated);
    /**
     * @brief Set the paired display flags and update auxiliary displays.
     * @param value Low byte stored in each paired display flag.
     * @param alternate Auxiliary flag value; its full value selects the height.
     */
    virtual void func_slot10c(u32 value, u32 alternate);
    /** @brief Set the list flag. @param value Flag value to store. */
    virtual void func_slot110(u8 value);
    /** @brief Refresh the visible record rows. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Position the row displays. @param start Base vertical coordinate. */
    virtual void set_scroll_position(float start);
    struct LibObject172410* unk138[6];
    struct ItemCreationOptionResourceDisplay* unk150[6];
    struct LibObject172440* unk168[8];
    struct ItemCreationClass172870* unk188;
    struct LibClass178630* unk18c;
    LibObject178750* unk190;
    LibObject178750* unk194;
    LibObject178750* unk198;
    u8 unk19c[4];
    LibObject178750* unk1a0;
    LibObject178750* unk1a4;
    struct LibObject172410* unk1a8;
    LibObject178660* unk1ac;
    u8 unk1b0;
    u8 unk1b1[3];
    ItemCreationSelectedDisplayState* unk1b4;
    s32 unk1b8;
    s32 unk1bc;
};

class FieldClass153130;
class FieldClass153170;

/** Item creation selection window with primary vtable at 0x186870. */
class ItemCreationClass186870 : public FieldClass15AE70
{
public:
    /** Destroy the window through Field's window base. */
    virtual ~ItemCreationClass186870();
    /** @brief Apply the selected values. @return Always one. */
    virtual s32 func_slotb0();
    /** @brief Restore the selection display. @return Always two. */
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
    /**
     * @brief Create and attach the selection window displays.
     * @param associated Object associated with the window.
     * @return Always one.
     */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    LibObject178750* unkac;
    LibObject178750* unkb0;
    FieldClass153130* unkb4;
    FieldClass153170* unkb8;
    u8 unkbc;
    u8 unkbd;
    u8 unkbe;
};

/** Three cleared words of an item creation window record. */
typedef struct ItemCreationRecord128
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
} ItemCreationRecord128;

struct LibObject175140;
struct ItemCreationOptionResourceDisplay;

/** Item creation detail window with primary vtable at 0x186970. */
class ItemCreationClass186970 : public FieldClass15AE70
{
public:
    /** @brief Construct the detail window with its displays cleared. */
    ItemCreationClass186970();
    /** @brief Destroy the window through Field's window base. */
    virtual ~ItemCreationClass186970();
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
    /**
     * @brief Create and attach the detail window displays.
     * @param associated Object associated with the window.
     * @return One when the displays are created; zero when no state is attached.
     */
    virtual s32 func_slotf4(void* associated);
    /** @brief Refresh the selected item, text, and detail icons. */
    void func_00358850();
    ItemCreationSelectedDisplayState* unka8;
    ItemCreationOptionResourceDisplay* unkac;
    LibObject175140* unkb0;
    LibObject178750* unkb4;
    LibObject178750* unkb8[9];
    LibObject174F20* unkdc[9];
    u8 unk100;
    u8 unk101;
    u16 unk102;
};

struct LibClass178600;
struct LibClass178630;
struct LibObject178750;
struct LibObject174F20;
struct ItemCreationOptionResourceDisplay;

/** Partial item creation window with primary vtable at 0x186A70. */
class ItemCreationClass186A70 : public FieldClass15AE70
{
public:
    /** Construct the window with its sixteen words cleared. */
    ItemCreationClass186A70();
    /** Destroy the window through Field's window base. */
    virtual ~ItemCreationClass186A70();
    /** @brief Run the default window action. @return Always one. */
    virtual s32 func_slotb0();
    /** @brief Run the default alternate action. @return Always zero. */
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
    /**
     * @brief Create and attach the resource window displays.
     * @param associated Object associated with the window.
     * @return Always one.
     */
    virtual s32 func_slotf4(void* associated);
    /**
     * @brief Select the visible resource widgets and the panel position.
     * @param mode Resource display mode.
     * @param unused Unused caller state word.
     */
    void func_003598E0(u16 mode, u32 unused);
    LibClass178630* unka8;
    LibObject178750* unkac;
    LibObject178750* unkb0;
    LibObject178750* unkb4;
    LibObject178750* unkb8;
    LibObject178750* unkbc;
    LibObject178750* unkc0;
    LibObject178750* unkc4;
    LibObject178750* unkc8;
    ItemCreationOptionResourceDisplay* unkcc;
    LibObject174F20* unkd0;
    ItemCreationOptionResourceDisplay* unkd4;
    LibObject174F20* unkd8;
    float unkdc;
    float unke0;
    float unke4;
};

class ItemCreationClass1746A0;

/** Mode list with primary table 0x186C90 and its owned counted list. */
class ItemCreationClass186C90 : public FieldClass15AD40
{
public:
    /** @brief Initialize the mode list and retain its selection state. @param state Selection state. */
    ItemCreationClass186C90(ItemCreationSelectedDisplayState* state);
    /** @brief Destroy the mode list and its Field window bases. */
    virtual ~ItemCreationClass186C90();
    /** @brief Refresh the active mode list and selection cursor. */
    virtual void func_slot5c();
    /** @brief Restore the mode window or its parent selection. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Create the mode list widgets and initialize its selection. @param associated Associated source. @return Always one. */
    virtual s32 func_slot104(void* associated);
    /** @brief Refresh the mode list rows. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Position the mode list rows. @param start Base vertical coordinate. */
    virtual void set_scroll_position(float start);
    /** @brief Rebuild the related category list. @param reset Whether to reset the selection. @param mode Category mode. */
    virtual void func_slot11c(u16 reset, u8 mode);
    struct LibClass178600* unk138[12];
    LibObject174F20* unk168[12];
    LibClass178630* unk198;
    ItemCreationClass1746A0* unk19c;
    ItemCreationSelectedDisplayState* unk1a0;
    u32 unk1a4;
    ItemCreationClass187A60 unk1a8;
    u16 unk1b4;
    u8 unk1b6[2];
    u32 unk1b8[24];
    u16 unk218;
    u8 unk21a[6];
};

class FieldClass153130;
class FieldClass153170;

/** Partial item creation window with primary vtable at 0x186DB0. */
class ItemCreationClass186DB0 : public FieldClass15AE70
{
public:
    /** Construct the window, keeping the supplied object. */
    ItemCreationClass186DB0(void* object);
    /** Destroy the window through Field's window base. */
    virtual ~ItemCreationClass186DB0();
    /** @brief Refresh the previous mode selection. */
    virtual void func_slot68();
    /** @brief Refresh the next mode selection. */
    virtual void func_slot6c();
    /** @brief Open the related list. @return Zero for an inactive selector; otherwise one. */
    virtual s32 func_slotb0();
    /** @brief Restore the prior item pair and parent window. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Create the mode display widgets. @param associated Associated parent. @return Setup status. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    FieldClass153130* unkac;
    FieldClass153170* unkb0;
    u16 unkb4;
    u8 unkb6[2];
    u32 unkb8;
    LibClass178630* unkbc;
    LibClass178630* unkc0;
    LibClass178630* unkc4;
    LibObject178750* unkc8[6];
    ItemCreationOptionResourceDisplay* unke0[6];
    LibObject178750* unkf8;
    float unkfc[4];
    s16 unk10c;
    u8 unk10e[2];
    LibObject178750* unk110[3];
    LibObject172410* unk11c[3];
    LibObject178750* unk128[6];
    LibObject174F20* unk140[3];
    u8 unk14c;
    u8 unk14d[3];
    ItemCreationClass186C90* unk150;
};

struct ItemCreationTwoColorReturnParent;

/** Two-choice item creation window with primary vtable at 0x186EB0. */
class ItemCreationClass186EB0 : public FieldClass15AE70
{
public:
    /** Construct the window, keeping the supplied object. */
    ItemCreationClass186EB0(void* object);
    /** Destroy the window through Field's window base. */
    virtual ~ItemCreationClass186EB0();
    /** @brief Reset the choices and return to the parent when enabled. @return Always two. */
    virtual s32 func_slotb4();
    /**
     * @brief Create the two choice displays and their selection widgets.
     * @param associated Object associated with the window.
     * @return Zero without a parent, otherwise one.
     */
    virtual s32 func_slotf4(void* associated);
    ItemCreationTwoColorReturnParent* unka8;
    u8 unkac;
    u8 unkad[0x3];
    LibClass178630* unkb0;
    LibObject178750* unkb4[2];
    float unkbc;
    float unkc0;
    float unkc4;
    float unkc8;
    FieldClass153130* unkcc;
    FieldClass153170* unkd0;
    u8 unkd4;
    u8 unkd5[0x3];
    void* unkd8;
    ItemCreationClass186DB0* unkdc;
    FieldClass15AE70* unke0;
};

/** Eight-choice item creation window with primary vtable at 0x186FB0. */
class ItemCreationClass186FB0 : public FieldClass15AE70
{
public:
    /** Construct the window, keeping the supplied object. */
    ItemCreationClass186FB0(void* object);
    /** Destroy the window through Field's window base. */
    virtual ~ItemCreationClass186FB0();
    /** @brief Refresh the option display for the first selection direction. */
    virtual void func_slot6c();
    /** @brief Refresh the option display for the second selection direction. */
    virtual void func_slot68();
    /** @brief Reset the option selection and handle the return mode. @return Always two. */
    virtual s32 func_slotb4();
    /**
     * @brief Create eight option displays and their selection widgets.
     * @param associated Object associated with the window.
     * @return Zero without a parent, otherwise one.
     */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    ItemCreationTwoColorReturnParent* unkac;
    LibClass178630* unkb0;
    LibObject178750* unkb4[8];
    FieldClass153130* unkd4;
    FieldClass153170* unkd8;
    u8 unkdc;
    u8 unkdd[0xB];
    u16 unke8;
};

/** Partial item creation window with primary vtable at 0x1874B0. */
class ItemCreationClass1874B0 : public FieldClass15AE70
{
public:
    /** Destroy the window through Field's window base. */
    virtual ~ItemCreationClass1874B0();
};

/** Partial item creation window with primary vtable at 0x1875B0. */
class ItemCreationClass1875B0 : public FieldClass15AE70
{
public:
    /** Destroy the window through Field's window base. */
    virtual ~ItemCreationClass1875B0();
};

/** Partial item creation window with primary vtable at 0x1870B0. */
class ItemCreationClass1870B0 : public FieldClass15AE70
{
public:
    /** Destroy the window through Field's window base. */
    virtual ~ItemCreationClass1870B0();
    /** Call the virtual at 0xa0. */
    virtual void func_slot68();
    /** Call the virtual at 0xa4. */
    virtual void func_slot6c();
    /** Call the virtual at 0xa8. */
    virtual void func_slot70();
    /** Call the virtual at 0xac. */
    virtual void func_slot74();
};

/** Partial item creation window with primary vtable at 0x1872B0. */
class ItemCreationClass1872B0 : public FieldClass15AE70
{
public:
    /** Construct the window with its fields and arrays cleared. */
    ItemCreationClass1872B0();
    /** Destroy the window through Field's window base. */
    virtual ~ItemCreationClass1872B0();
    u32 unka8;
    u8 unkac;
    u8 unkad[3];
    u32 unkb0[8];
    u8 unkd0[8];
    u16 unkd8;
    u8 unkda[2];
    u32 unkdc;
    u32 unke0;
    u32 unke4;
    u32 unke8[9];
    u8 unk10c;
    u8 unk10d;
    u8 unk10e[0xE];
    u32 unk11c;
    u32 unk120;
};

/** Partial item creation window with primary vtable at 0x1873B0. */
class ItemCreationClass1873B0 : public FieldClass15AE70
{
public:
    /** Construct the window with its arrays and records cleared. */
    ItemCreationClass1873B0();
    /** Destroy the window and the object it owns. */
    virtual ~ItemCreationClass1873B0();
    u32 unka8[9];
    u32 unkcc[14];
    u32 unk104[7];
    u32 unk120;
    u8 unk124;
    u8 unk125;
    u8 unk126[2];
    ItemCreationRecord128 unk128[3];
};

/** Partial item creation window with primary vtable at 0x1871B0. */
class ItemCreationClass1871B0 : public FieldClass15AE70
{
public:
    /** Destroy the window through Field's window base. */
    virtual ~ItemCreationClass1871B0();
    /** Call the virtual at 0xa0. */
    virtual void func_slot68();
    /** Call the virtual at 0xa4. */
    virtual void func_slot6c();
    /** Call the virtual at 0xa8. */
    virtual void func_slot70();
    /** Call the virtual at 0xac. */
    virtual void func_slot74();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Update a checked item display and its quantity, or hide the displays for an empty item.
 * @param object Owner of the checked item and quantity displays.
 * @param value Signed item index; zero hides the displays.
 * @param quantity Quantity to display, or -1 to hide its display.
 * @param index Index of the display to update.
 */
void func_0035E150(ItemCreationCheckedAllocationView* object, s16 value, s32 quantity, s8 index);

/**
 * @brief Display the checked record's decoded value, or zero for an invalid checksum.
 * @param object Owner of the optional value display.
 */
void func_00366CB0(ItemCreationCheckedValueOwner* object);

/**
 * @brief Refresh each optional display from the checked resident value.
 * @param object Owner of the two optional value displays.
 */
void func_00359C80(ItemCreationTwoCheckedValueOwner* object);

/**
 * @brief Update panel marker visibility and values from the selected state.
 * @param object Panel associated with the selected state.
 */
void func_00366050(ItemCreationPanelView* object);

/**
 * @brief Refresh the available and assigned resource displays from the selected state.
 * @param object Resource view with an optional associated selected state.
 */
void func_00366F10(ItemCreationAvailableResourceView* object);

/**
 * @brief Advance the selector and refresh the colors and target of two item displays.
 * @param object Owner of the item displays, selector, and target display.
 */
void func_0035F710(ItemCreationTwoColorOwner* object);

/**
 * @brief Move the selector backward and refresh the colors and target of two item displays.
 * @param object Owner of the item displays, selector, and target display.
 */
void func_0035F7F0(ItemCreationTwoColorOwner* object);

/**
 * @brief Refresh the assigned-group markers, colors, and the two group grids.
 * @param object Nine-slot view containing three assigned-group displays.
 */
void func_00363D20(ItemCreationNineSlotView* object);

/**
 * @brief Refresh the nine item-resource displays and their assigned-item codes.
 * @param object View containing the item-resource displays and selection state.
 */
void func_003614B0(ItemCreationNineSlotView* object);

/**
 * @brief Refresh the fourteen item-resource displays and their marker bytes.
 * @param object View containing the item-resource displays and selection state.
 */
void func_00364D20(ItemCreationFourteenSlotView* object);

/**
 * @brief Activate the selected display and refresh its markers, or deactivate the displays and clear their markers.
 * @param object View containing nine markers and two twelve-marker groups.
 * @param mode One activates the selected display; zero deactivates displays; other values do nothing.
 */
void func_00360E60(ItemCreationNineSlotView* object, u16 mode);

/**
 * @brief Clear the view markers and mark the group selected by the current display index.
 * @param object View containing the markers and selected display.
 */
void func_00361220(ItemCreationNineSlotView* object);

/**
 * @brief Activate a selected display and its marker, or deactivate the current displays and markers.
 * @param object View containing the displays and fourteen selection markers.
 * @param mode One activates the selected display; zero deactivates the current displays; other values do nothing.
 */
void func_00364090(ItemCreationFourteenSlotView* object, u16 mode);

/**
 * @brief Report whether any byte in a selected item triple is nonzero.
 * @param object State containing the three item triples.
 * @param index Triple index, zero through two; other values report zero.
 * @return One when a byte in the selected triple is nonzero, or zero otherwise.
 */
u8 func_003623C0(ItemCreationTripleState* object, u8 index);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035AF70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035AF80(void* object);

/**
 * @brief Confirm the active slot and update its alternate field display.
 * @param object Fourteen-slot view linked to the selection state.
 * @return 1 when the active selection was processed, or 0 when unavailable.
 */
u8 func_003644F0(ItemCreationFourteenSlotView* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003641F0(void* object);

/**
 * @brief Test whether a category is rejected by the selected mode or has no accepted records.
 * @param object Category display containing its selected state and mode.
 * @param category Category entry containing the zero-based catalog index.
 * @return One when its catalog fields fail the mode test or no collected record passes it; otherwise zero.
 */
u8 func_0035CAD0(ItemCreationCategoryOwner* object, const ItemCreationCategoryRecord* category);



/**
 * @brief Update object state using a selected value.
 * @param object Object to update.
 * @param value Selected value.
 */
void func_0035FCA0(u8* object, u16 value);

/**
 * @brief Read the word at offset 0x24.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_00366040(void* object);

/**
 * @brief Set a nested object's value and select its float setting.
 * @param object Object holding the nested pointer.
 * @param unused Unused second argument.
 * @param value Value to write at offset 0x3F; selects the float setting.
 */
void func_0035C4D0(u8* object, void* unused, u32 value);

/**
 * @brief Set the nested object's float value and active flag if present.
 * @param object Object holding the nested pointer.
 */
void func_0035E2D0(u8* object);

/** @brief Resize the mode list and rebuild its category rows. @param object Mode list. @param mode Compact display mode. */
void func_0035D0C0(ItemCreationClass186C90* object, s32 mode);

#ifdef __cplusplus
/**
 * @brief Test whether a record is empty, rejected by the selected mode, or already assigned.
 * @param object Owner of the selected mode and assigned identifier pairs.
 * @param record Packed item record to test; null is accepted as an empty record.
 * @return True for an empty record, a failed mode predicate, or an assigned identifier.
 */
bool func_0035B310(ItemCreationIdentifierOwner* object, const struct ItemCreationAllocationRecord* record);
#endif

#ifdef __cplusplus
}
#endif

#endif
