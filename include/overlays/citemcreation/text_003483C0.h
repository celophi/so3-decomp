#ifndef SO3_OVERLAYS_CITEMCREATION_TEXT_003483C0_H
#define SO3_OVERLAYS_CITEMCREATION_TEXT_003483C0_H

#include "types.h"
#include "overlays/citemcreation/text_003684D0.h"

#ifdef __cplusplus
#include "overlays/citemcreation/text_00358440.h"
#endif

/** Partial owner of four displayed position pairs and their update flags. */
typedef struct ItemCreationFourPositionDisplay
{
    u8 unk00[0x1C];
    float unk1c;
    float unk20;
    u8 unk24[0x1C];
    u8 unk40;
    u8 unk41[0xEF];
    float unk130;
    float unk134;
    u8 unk138[0x1C];
    u8 unk154;
    u8 unk155[0xEF];
    float unk244;
    float unk248;
    u8 unk24c[0x1C];
    u8 unk268;
    u8 unk269[0xEF];
    float unk358;
    float unk35c;
    u8 unk360[0x1C];
    u8 unk37c;
} ItemCreationFourPositionDisplay;

/** Partial owner of the six alternate marker flags and their display. */
typedef struct ItemCreationFlagToggleOwner
{
    u8 unk00[0x15C];
    struct ItemCreationNested* unk15c;
    u8 unk160[0x2C];
    struct ItemCreationNested* unk18c;
    struct ItemCreationNested* unk190;
    struct ItemCreationNested* unk194;
    struct ItemCreationNested* unk198;
    struct ItemCreationNested* unk19c;
    struct ItemCreationNested* unk1a0;
} ItemCreationFlagToggleOwner;

typedef struct ItemCreationOptionDisplay ItemCreationOptionDisplay;
typedef struct ItemCreationOptionTransferOwner ItemCreationOptionTransferOwner;

/** Partial nested object with a flag byte. */
typedef struct ItemCreationFlagNode
{
    u8 unk00[0x3F];
    u8 unk3f;
} ItemCreationFlagNode;

/** Partial color display with its update byte and packed color. */
typedef struct ItemCreationColorDisplay
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[0x57];
    u32 unk94;
} ItemCreationColorDisplay;

/** Partial value display with its update, visibility, and value fields. */
typedef struct ItemCreationValueDisplay
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0xBC];
    u32 unkfc;
} ItemCreationValueDisplay;

/** Partial wrapper containing an optional display marker. */
typedef struct ItemCreationMarkerOwner
{
    u8 unk00[0x30];
    ItemCreationFlagNode* unk30;
} ItemCreationMarkerOwner;

/** Partial owner of nine resource displays and three assigned-item groups. */
typedef struct ItemCreationNineResourceView
{
    u8 unk00[0xA8];
    ItemCreationSelectedDisplayState* unka8;
    u8 unkac[0x30];
    struct FieldResourceDisplay2D5CF0* unkdc[9];
    u8 unk100[9];
    s8 unk109;
    u8 unk10a[2];
    struct FieldObject23CE80* unk10c;
    u8 unk110[0xC];
    ItemCreationMarkerOwner* unk11c[3];
    ItemCreationMarkerOwner* unk128[3];
    ItemCreationColorDisplay* unk134[3];
    ItemCreationColorDisplay* unk140[3];
    ItemCreationColorDisplay* unk14c[3];
    ItemCreationColorDisplay* unk158[3];
    ItemCreationValueDisplay* unk164[3];
    u8 unk170[4];
    ItemCreationFlagNode* unk174[12];
    u8 unk1a4[0x18];
    u8 unk1bc;
} ItemCreationNineResourceView;

/** Partial owner of two direct color displays and their guarded selector. */
typedef struct ItemCreationDirectColorOwner
{
    u8 unk00[0xAC];
    ItemCreationColorDisplay* unkac;
    ItemCreationColorDisplay* unkb0;
    struct FieldState23B3A0* unkb4;
    struct FieldObject23B950* unkb8;
} ItemCreationDirectColorOwner;

/** Partial owner of a two-item color list, selector, and target display. */
typedef struct ItemCreationTwoColorList
{
    u8 unk00[0x2C];
    ItemCreationList unk2c;
    u8 unk30[0x7C];
    struct FieldState23B3A0* unkac;
    struct FieldObject23B950* unkb0;
} ItemCreationTwoColorList;

/** Partial owner of a three-item color list, selector, and target display. */
typedef struct ItemCreationThreeColorList
{
    u8 unk00[0x2C];
    ItemCreationList unk2c;
    u8 unk30[0x7C];
    struct FieldState23B3A0* unkac;
    struct FieldObject23B950* unkb0;
} ItemCreationThreeColorList;

/** Partial owner of eight color displays and an optional auxiliary flag. */
typedef struct ItemCreationEightColorOwner
{
    u8 unk00[0x168];
    ItemCreationColorDisplay* unk168[8];
    ItemCreationFlagNode* unk188;
} ItemCreationEightColorOwner;

/** Partial owner of twelve nested flag objects. */
typedef struct ItemCreationFlagGroups
{
    u8 unk00[0x174];
    ItemCreationFlagNode* unk174[12];
} ItemCreationFlagGroups;

/** Partial display containing the position state and its update flags. */
typedef struct ItemCreationTransferDisplay
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0x10];
    float unk50;
    float unk54;
    u8 unk58[0x1D];
    u8 unk75;
} ItemCreationTransferDisplay;

/** Partial owner of the nested flag objects cleared by its reset routine. */
typedef struct ItemCreationFlagResetOwner
{
    u8 unk00[0xDC];
    ItemCreationSelection unkdc;
    u8 unk158[4];
    ItemCreationTransferDisplay* unk15c;
    struct ItemCreationSelection* unk160;
    struct ItemCreationSelectedDisplayState* unk164;
    u8 unk168[4];
    struct ItemCreationTransferDisplay* unk16c;
    u8 unk170[9];
    u8 unk179;
    u8 unk17a[2];
    ItemCreationFlagNode* unk17c[9];
    u8 unk1a0[4];
    ItemCreationFlagNode* unk1a4[3];
    u8 unk1b0;
    u8 unk1b1;
    u8 unk1b2[2];
    ItemCreationFlagNode* unk1b4[9];
    u8 unk1d8[4];
    ItemCreationFlagNode* unk1dc[3];
} ItemCreationFlagResetOwner;

#ifdef __cplusplus
/** Partial virtual interface of the item creation window at 0x185A60. */
class ItemCreationClass185A60 : public FieldClass15AE70
{
public:
    virtual ~ItemCreationClass185A60();
    virtual void func_slotb0();
    virtual void func_slotb4();
    virtual void func_slotb8();
    virtual void func_slotbc();
    virtual void func_slotc0();
    virtual void func_slotc4();
    virtual void func_slotc8();
    virtual void func_slotcc();
    virtual void func_slotd0();
    virtual void func_slotd4();
    virtual void func_slotd8();
    virtual void func_slotdc();
    virtual void func_slote0();
    virtual void func_slote4();
    virtual void func_slote8();
    virtual void func_slotec();
    virtual void func_slotf0();
    virtual s32 func_slotf4(void* associated);
    virtual void func_slotf8(u16 direction);
};

/** Partial virtual interface of the item creation window at 0x185860. */
class ItemCreationClass185860 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185860();
    virtual void func_slotb0();
    virtual void func_slotb4();
    virtual void func_slotb8();
    virtual void func_slotbc();
    virtual void func_slotc0();
    virtual void func_slotc4();
    virtual void func_slotc8();
    virtual void func_slotcc();
    virtual void func_slotd0();
    virtual void func_slotd4();
    virtual void func_slotd8();
    virtual void func_slotdc();
    virtual void func_slote0();
    virtual void func_slote4();
    virtual void func_slote8();
    virtual void func_slotec();
    virtual void func_slotf0();
    virtual s32 func_slotf4(void* associated);
    virtual void func_slotf8(u16 direction);
    /** @brief Forward direction 2 to the window. */
    virtual void func_slot74();
    /** @brief Forward direction 3 to the window. */
    virtual void func_slot70();
};

/** Partial virtual interface of the item creation window at 0x185460. */
class ItemCreationClass185460 : public ItemCreationClass185A60
{
public:
    virtual ~ItemCreationClass185460();
    /** @brief Forward direction 2 to the window. */
    virtual void func_slot74();
    /** @brief Forward direction 4 to the window. */
    virtual void func_slot70();
    /** @brief Forward direction 3 to the window. */
    virtual void func_slot6c();
    /** @brief Forward direction 1 to the window. */
    virtual void func_slot68();
};

/** Partial virtual interface of the item creation window at 0x185960. */
class ItemCreationClass185960 : public ItemCreationClass185A60
{
public:
    virtual ~ItemCreationClass185960();
    /** @brief Forward direction 2 to the window. */
    virtual void func_slot74();
    /** @brief Forward direction 4 to the window. */
    virtual void func_slot70();
    /** @brief Forward direction 3 to the window. */
    virtual void func_slot6c();
    /** @brief Forward direction 1 to the window. */
    virtual void func_slot68();
};

/** Partial item creation window with primary vtable at 0x185060. */
class ItemCreationClass185060 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185060();
};

/** Partial item creation window with primary vtable at 0x185160. */
class ItemCreationClass185160 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185160();
};

/** Partial item creation window with primary vtable at 0x185260. */
class ItemCreationClass185260 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185260();
};

/** Partial item creation window with primary vtable at 0x185360. */
class ItemCreationClass185360 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185360();
};

/** Partial item creation window with primary vtable at 0x185560. */
class ItemCreationClass185560 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185560();
};

/** Partial item creation window with primary vtable at 0x185B60. */
class ItemCreationClass185B60 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185B60();
};

/** Partial item creation window with primary vtable at 0x185C60. */
class ItemCreationClass185C60 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185C60();
};

/** Partial item creation window with primary vtable at 0x185D60. */
class ItemCreationClass185D60 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185D60();
};

/** Partial item creation window with primary vtable at 0x185E60. */
class ItemCreationClass185E60 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185E60();
};

/** Partial item creation window with primary vtable at 0x186670. */
class ItemCreationClass186670 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass186670();
};

extern "C" {
#endif

/**
 * @brief Transfer the selected option into its list display and refresh the option markers.
 * @param object Owner of the six-slot option list, valid selected index, and marker display.
 */
void func_0034CE00(ItemCreationOptionTransferOwner* object);

/**
 * @brief Refresh the nine resource displays and count their active entries.
 * @param object Owner of the selected resource values and displays.
 */
void func_00356160(ItemCreationNineResourceView* object);

/**
 * @brief Refresh the three assigned-item groups and their selector grid.
 * @param object Owner of the group displays and selected item values.
 */
void func_00356FD0(ItemCreationNineResourceView* object);

/**
 * @brief Advance an enabled selector and refresh its two displays and target.
 * @param object Owner of the displays, selector, and target display.
 */
void func_00358240(ItemCreationDirectColorOwner* object);

/**
 * @brief Move an enabled selector backward and refresh its two displays and target.
 * @param object Owner of the displays, selector, and target display.
 */
void func_00358340(ItemCreationDirectColorOwner* object);

/**
 * @brief Advance the selector and refresh the colors and target of the two-item list.
 * @param object Owner of the item list, selector, and target display.
 */
void func_00355670(ItemCreationTwoColorList* object);

/**
 * @brief Move the selector backward and refresh the colors and target of the two-item list.
 * @param object Owner of the item list, selector, and target display.
 */
void func_00355740(ItemCreationTwoColorList* object);

/**
 * @brief Advance the selector and refresh the colors and target of the three-item list.
 * @param object Owner of the item list, selector, and target display.
 */
void func_00350E00(ItemCreationThreeColorList* object);

/**
 * @brief Move the selector backward and refresh the colors and target of the three-item list.
 * @param object Owner of the item list, selector, and target display.
 */
void func_00350ED0(ItemCreationThreeColorList* object);

/**
 * @brief Position the four item displays relative to a shared origin.
 * @param object Owner of the four position pairs and update flags.
 * @param x Horizontal origin.
 * @param y Vertical position for all four displays.
 */
void func_00352B00(ItemCreationFourPositionDisplay* object, float x, float y);

/**
 * @brief Set alternate marker flags and update their associated display setting.
 * @param object Owner of the optional marker and display objects.
 * @param mode Zero or one selects the marker group; other values leave the state unchanged.
 */
void func_0034A670(ItemCreationFlagToggleOwner* object, u8 mode);

/**
 * @brief Dim eight displays, then brighten those selected by an item's resident flags.
 * @param object Owner of the eight optional displays and auxiliary flag.
 * @param selected Item from one through twelve; other values leave the displays dim.
 */
void func_0034A7A0(ItemCreationEightColorOwner* object, u8 selected);

/**
 * @brief Rebuild and refresh the option list selected by the transfer state.
 * @param object Owner of the selection and transfer state.
 * @param option Option to display, or 0xFF to use the current selection.
 */
void func_0034D980(ItemCreationFlagResetOwner* object, u8 option);

/**
 * @brief Move the transfer display and refresh its selected option markers and list.
 * @param object Owner of the selection and optional transfer display.
 * @param direction Direction used to advance the embedded selection.
 */
void func_0034E4D0(ItemCreationFlagResetOwner* object, u16 direction);

/**
 * @brief Move the optional transfer display using the embedded selection.
 * @param object Owner of the selection and optional transfer display.
 * @param direction Direction used to advance the embedded selection.
 */
void func_0034F9B0(ItemCreationFlagResetOwner* object, u16 direction);

/**
 * @brief Initialize the view display at its fixed coordinates and report success.
 * @param object View that owns the display.
 * @param associated Associated object forwarded to the field initializer.
 * @return Always one.
 */
s32 func_0034FD50(ItemCreationFlagResetOwner* object, void* associated);

/**
 * @brief Refresh an option display from its current option list.
 * @param object Option display to refresh.
 */
void func_0034D340(ItemCreationOptionDisplay* object);

/**
 * @brief Refresh the option markers for the selected option.
 * @param object Owner of the option markers.
 * @param option Selected option byte.
 */
void func_0034DB00(ItemCreationFlagResetOwner* object, u8 option);

/**
 * @brief Clear all twelve nested flags and enable the selected group of four.
 * @param object Owner of the optional nested objects.
 * @param group Group to enable, from zero through two; other values leave all flags clear.
 */
void func_00356780(ItemCreationFlagGroups* object, u16 group);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348500(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348510(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348520(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348530(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348550(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348580(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348590(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003485F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348600(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348610(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348620(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348630(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348640(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348650(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348660(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348670(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348680(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348690(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00350DE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00350DF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351C30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351C40(void* object);

/**
 * @brief Write the byte at offset 0xC.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348400(void* object, u8 value);

/**
 * @brief Read the byte at offset 0xC.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_00348410(void* object);

/**
 * @brief Write the byte at offset 0x8.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348420(void* object, u8 value);

/**
 * @brief Read the byte at offset 0x8.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_00348430(void* object);

/**
 * @brief Write the halfword at offset 0xA.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348440(void* object, u16 value);

/**
 * @brief Read the halfword at offset 0xA.
 * @param object Object containing the field.
 * @return Field value.
 */
u16 func_00348450(void* object);

/**
 * @brief Write the word at offset 0x98.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348460(void* object, u32 value);

/**
 * @brief Read the word at offset 0x98.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_00348470(void* object);

/**
 * @brief Write the word at offset 0x9C.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348480(void* object, u32 value);

/**
 * @brief Read the word at offset 0x9C.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_00348490(void* object);

/**
 * @brief Write the word at offset 0x4.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003484A0(void* object, u32 value);

/**
 * @brief Read the word at offset 0x4.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_003484B0(void* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_003484C0(void* object);

/**
 * @brief Read the byte at offset 0xD.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_003486B0(void* object);

/**
 * @brief Write the byte at offset 0xD.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003486C0(void* object, u8 value);

/**
 * @brief Read the word at offset 0x20.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_003486E0(void* object);

/**
 * @brief Write the word at offset 0x20.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003486F0(void* object, u32 value);

/**
 * @brief Read the word at offset 0x34.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_0034FF60(void* object);

/**
 * @brief Write the halfword at offset 0x6C.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003527C0(void* object, u16 value);

/**
 * @brief Write the same byte to four object slots.
 * @param object Object to update.
 * @param unused Unused argument.
 * @param value Value to store or test.
 */
void func_00352DC0(u8* object, u32 unused, u8 value);

/**
 * @brief Clear the flag byte in 24 nested objects.
 * @param object Object holding the nested pointers.
 */
void func_0034DA30(ItemCreationFlagResetOwner* object);

#ifdef __cplusplus
}
#endif

#endif
