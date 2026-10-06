#ifndef SO3_OVERLAYS_CITEMCREATION_TEXT_003483C0_H
#define SO3_OVERLAYS_CITEMCREATION_TEXT_003483C0_H

#include "types.h"
#include "overlays/citemcreation/text_003684D0.h"

#ifdef __cplusplus
#include "overlays/citemcreation/text_00358440.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/1067-00/text_002D5260.h"
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

#ifdef __cplusplus
class ItemCreationClass185D60;
class ItemCreationClass186670;
#else
struct ItemCreationClass185D60;
#endif
/** Resource window with native primary vtable at 0x186770 and extent 0x1C4. */
typedef struct ItemCreationClass186770
#ifdef __cplusplus
    : public FieldClass15AE70
#endif
{
#ifdef __cplusplus
    /** @brief Initialize the resource window and its owned arrays. */
    ItemCreationClass186770();
    /** @brief Destroy the resource window and its Field base. */
    virtual ~ItemCreationClass186770();
    /** @brief Open the selected resource group. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Reopen the associated window. @return Action status. */
    virtual s32 func_slotb4();
    /** @brief Reopen the option window. @return Action status. */
    virtual s32 func_slotb8();
    /** @brief Refresh the active resource window. */
    virtual void func_slot5c();
    /** @brief Move the resource column in direction zero. */
    virtual void func_slot68();
    /** @brief Move the resource column in direction one. */
    virtual void func_slot6c();
    /** @brief Create the resource grid and displays. @param associated Associated window. @return Initialization status. */
    virtual s32 func_slotf4(void* associated);
#else
    u8 unk00[0xA8];
#endif
    ItemCreationSelectedDisplayState* unka8;
    struct FieldClass15B200* unkac[12];
    struct FieldResourceDisplay2D5CF0* unkdc[9];
    u8 unk100[9];
    s8 unk109;
    u8 unk10a[2];
    struct FieldObject23CEA0* unk10c;
    struct ItemCreationClass186670* unk110;
    struct ItemCreationClass186070* unk114;
    struct ItemCreationClass185B60* unk118;
    struct FieldClass15B200* unk11c[3];
    struct FieldClass15B200* unk128[3];
    ItemCreationColorDisplay* unk134[3];
    ItemCreationColorDisplay* unk140[3];
    ItemCreationColorDisplay* unk14c[3];
    ItemCreationColorDisplay* unk158[3];
    ItemCreationValueDisplay* unk164[3];
    u8 unk170[4];
    struct ItemCreationOptionResourceDisplay* unk174[12];
    u8 unk1a4[0x18];
    u8 unk1bc;
    struct ItemCreationClass185D60* unk1c0;
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
    u8 unk58[0x18];
    float unk70;
    u8 unk74;
    u8 unk75;
} ItemCreationTransferDisplay;

/** Partial owner of the nested flag objects cleared by its reset routine. */
typedef struct ItemCreationFlagResetOwner
{
    u8 unk00[0xDC];
    ItemCreationSelection unkdc;
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
    /** @brief Initialize the selection and display pointers. */
    ItemCreationClass185A60()
    {
        unka8 = 0;
        for (s32 index = 0; index < 12; index++)
        {
            unkac[index] = 0;
        }
        unk15c = 0;
        unkdc.func_slot0c();
    }
    /** @brief Destroy the selection state and window base. */
    virtual ~ItemCreationClass185A60()
    {
    }
    /** @brief Apply the current selection. @return Selection result code. */
    virtual s32 func_slotb0();
    /** @brief Reset the current selection. @return Selection result code. */
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
    virtual s32 func_slotf4(void* associated);
    virtual void func_slotf8(u16 direction);
    ItemCreationSelectedDisplayState* unka8;
    void* unkac[12];
    ItemCreationSelection unkdc;
    ItemCreationTransferDisplay* unk15c;
    /**
     * @brief Create and attach the selection transfer display.
     * @param x Horizontal coordinate.
     * @param y Vertical coordinate.
     * @return Whether the display was created.
     */
    s32 create_selection_display_status(float x, float y);
};

/** Partial virtual interface of the item creation window at 0x185860. */
class ItemCreationClass185860 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185860()
    {
    }
    /**
     * @brief Select the active view and apply its selected option.
     * @return Always one.
     */
    virtual s32 func_slotb0();
    /**
     * @brief Clear the selected option and restore the active view.
     * @return Always two.
     */
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
    virtual s32 func_slotf4(void* associated);
    /**
     * @brief Dispatch a grid direction and refresh the selected option markers.
     * @param direction Direction code.
     */
    virtual void func_slotf8(s32 direction);
    /** @brief Forward direction 2 to the window. */
    virtual void func_slot74();
    /** @brief Forward direction 3 to the window. */
    virtual void func_slot70();
    u8 unka8;
    u8 unka9;
    u8 unkaa[2];
    struct ItemCreationOptionResourceDisplay* unkac[6];
    ItemCreationSelectedDisplayState* unkc4;
    struct FieldObject23CEA0* unkc8;
    ItemCreationFlagResetOwner* unkcc;
};

/** Partial option window derived from the interface at 0x185860. */
class ItemCreationClass185660 : public ItemCreationClass185860
{
public:
    /** @brief Destroy the option window and its base. */
    virtual ~ItemCreationClass185660();
    /** @brief Apply the selected option and refresh its associated window. @return Always one. */
    virtual s32 func_slotb0();
    /** @brief Reset the option and restore its associated selection display. @return Always two. */
    virtual s32 func_slotb4();
    /**
     * @brief Set up the option window and recover its associated display.
     * @param associated Object associated with the window.
     * @return Zero when no option state is attached, or one after setup.
     */
    virtual s32 func_slotf4(void* associated);
    /**
     * @brief Dispatch a grid direction and refresh the selected option markers.
     * @param direction Direction code.
     */
    virtual void func_slotf8(s32 direction);
};

/** Partial option window derived from the interface at 0x185860. */
class ItemCreationClass185760 : public ItemCreationClass185860
{
public:
    /** @brief Destroy the option window and its base. */
    virtual ~ItemCreationClass185760();
    /** @brief Apply the selected option and refresh its associated window. @return Always one. */
    virtual s32 func_slotb0();
    /** @brief Reset the option and restore its associated selection display. @return Always two. */
    virtual s32 func_slotb4();
    /**
     * @brief Set up the option window and recover its associated display.
     * @param associated Object associated with the window.
     * @return Zero when no option state is attached, or one after setup.
     */
    virtual s32 func_slotf4(void* associated);
    /**
     * @brief Dispatch a grid direction and refresh the selected option markers.
     * @param direction Direction code.
     */
    virtual void func_slotf8(s32 direction);
};

/** Partial virtual interface of the item creation window at 0x185460. */
class ItemCreationClass185460 : public ItemCreationClass185A60
{
public:
    /** @brief Initialize the selection window and its display pointers. */
    ItemCreationClass185460();
    /** @brief Destroy the selection window through its base. */
    virtual ~ItemCreationClass185460();
    /** @brief Forward direction 2 to the window. */
    virtual void func_slot74();
    /** @brief Forward direction 4 to the window. */
    virtual void func_slot70();
    /** @brief Forward direction 3 to the window. */
    virtual void func_slot6c();
    /** @brief Forward direction 1 to the window. */
    virtual void func_slot68();
    ItemCreationSelection* unk160;
    u32 unk164;
    u32 unk168[9];
    u32 unk18c;
    u32 unk190;
    u32 unk194;
    u32 unk198;
    u32 unk19c;
    u32 unk1a0;
    u32 unk1a4;
};

/** Partial virtual interface of the item creation window at 0x185960. */
class ItemCreationClass185960 : public ItemCreationClass185A60
{
public:
    /**
     * @brief Apply the selected option and enable the corresponding option window.
     * @return Zero without a state, three for an unchanged alternate selection, or one otherwise.
     */
    virtual s32 func_slotb0();
    /**
     * @brief Reset the option transfer or return to the primary option window.
     * @return Zero without a selection state, or two otherwise.
     */
    virtual s32 func_slotb4();
    /** @brief Initialize the selection window and its display pointers. */
    ItemCreationClass185960();
    /** @brief Destroy the selection window through its base. */
    virtual ~ItemCreationClass185960();
    /** @brief Forward direction 2 to the window. */
    virtual void func_slot74();
    /** @brief Forward direction 4 to the window. */
    virtual void func_slot70();
    /** @brief Forward direction 3 to the window. */
    virtual void func_slot6c();
    /** @brief Forward direction 1 to the window. */
    virtual void func_slot68();
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelection* unk160;
    ItemCreationSelectedDisplayState* unk164;
    u8 unk168[4];
    ItemCreationTransferDisplay* unk16c;
    u8 unk170;
    u8 unk171[3];
    LibObject178750* unk174;
    u8 unk178;
    u8 unk179;
    u8 unk17a[2];
    LibClass174EF0* unk17c;
    LibClass174EF0* unk180[9];
    LibClass174EF0* unk1a4[3];
    u8 unk1b0;
    u8 unk1b1;
    u8 unk1b2[2];
    LibClass174EF0* unk1b4;
    LibClass174EF0* unk1b8[9];
    LibClass174EF0* unk1dc[3];
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
    ItemCreationSelectedDisplayState* unka8;
    u8 unkac;
    u8 unkad[3];
    LibObject178750* unkb0;
};

/** Window with resident vtable 0x186270 and no storage beyond the Field base. */
class ItemCreationClass186270 : public FieldClass15AE70
{
public:
    /** @brief Initialize the Field window base. */
    ItemCreationClass186270()
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~ItemCreationClass186270();
    /** @brief Return to the associated window. @return Always one. */
    virtual s32 func_slotb0();
    /** @brief Handle the alternate action. @return Action status. */
    virtual s32 func_slotb4();
    /** @brief Create and attach the window display. @param associated Associated object. @return Always one. */
    virtual s32 func_slotf4(void* associated);
};

/** Partial 0xA8-byte window with resident vtable at 0x186370. */
class ItemCreationClass186370 : public FieldClass15AE70
{
public:
    /** @brief Initialize the Field window base. */
    ItemCreationClass186370()
    {
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass186370();
    /** @brief Handle the window action. @return Handler status. */
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
     * @brief Create and attach the window display.
     * @param associated Object associated with the window.
     * @return Setup status.
     */
    virtual s32 func_slotf4(void* associated);
};

struct LibObject172410;
struct LibObject174F20;
struct LibObject172440;
class ItemCreationClass172870;

/** Field window with resident vtable at 0x186070. */
class ItemCreationClass186070 : public FieldClass15AE70
{
public:
    /** @brief Release the container and base window contents. */
    virtual void func_slot0c();
    /** @brief Initialize the window and keep its selection state. @param object Selection state. */
    ItemCreationClass186070(ItemCreationSelectedDisplayState* object);
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass186070();
    /** @brief Handle the window action. @return Handler status. */
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
     * @brief Create and attach the window display.
     * @param associated Object associated with the window.
     * @return Setup status.
     */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    LibObject178750* unkac;
    LibObject172410* unkb0;
    LibObject174F20* unkb4;
    ItemCreationClass172870* unkb8;
    LibObject178750* unkbc;
    LibObject178750* unkc0;
    LibObject172440* unkc4[8];
    LibObject178750* unke4;
    LibObject178660* unke8;
    u8 unkec;
    u8 unked;
    u16 unkee;
    u16 unkf0;
    u8 unkf2[2];
    u32 unkf4;
    LibClass178630* unkf8;
};

/** Partial Field window interface with resident vtable at 0x186470. */
class ItemCreationClass186470 : public FieldClass15AE70
{
public:
    /** @brief Initialize the window through its Field base. */
    ItemCreationClass186470()
    {
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass186470();
    /** @brief Handle the window action. @return Handler status. */
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
     * @brief Create and attach the window display.
     * @param associated Object associated with the window.
     * @return Setup status.
     */
    virtual s32 func_slotf4(void* associated);
    LibObject178750* unka8;
};

/** Partial Field window interface with resident vtable at 0x186570. */
class ItemCreationClass186570 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass186570();
    /** @brief Handle the window action. @return Handler status. */
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
     * @brief Create and attach the window display.
     * @param associated Object associated with the window.
     * @return Setup status.
     */
    virtual s32 func_slotf4(void* associated);
    LibObject178750* unka8;
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
    /** @brief Apply the selected result action. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Restore the third row and associated resource window. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Create the result action displays. @param associated Text source. @return Always one. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    FieldClass153130* unkac;
    FieldClass153170* unkb0;
};

class ItemCreationClass185F60;

/** Option window with primary vtable at 0x185E60. */
class ItemCreationClass185E60 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass185E60();
    /** @brief Update the option window and its active container. */
    virtual void func_slot5c();
    /** @brief Create the option window widgets. @param associated Associated source. @return Always one. */
    virtual s32 func_slotf4(void* associated);
    u8 unka8[0x10];
    ItemCreationClass185F60* unkb8;
    u8 unkbc;
    u8 unkbd[0x1F];
};

/** 0xB8-byte item creation window with primary vtable at 0x186670. */
class ItemCreationClass186670 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemCreationClass186670();
    /** @brief Apply the selected action. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Restore the associated resource window. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Create the option displays. @param associated Associated source. @return Always one. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    FieldClass153130* unkac;
    FieldClass153170* unkb0;
    LibObject178750* unkb4;
};

/** Partial widget with resident vtable at 0x172870. */
class ItemCreationClass172870 : public LibClass178600
{
public:
    /** @brief Initialize the widget storage and select kind 6. */
    inline ItemCreationClass172870();
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass172870();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    u32 unk50;
    u32 unk54;
};

/** Partial widget with resident vtable at 0x172600. */
class ItemCreationClass172600 : public LibClass178600
{
public:
    /** @brief Initialize the widget storage and select kind 5. */
    ItemCreationClass172600();
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass172600();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    float unk50;
};

/** Partial widget with resident vtable at 0x1725D0. */
class ItemCreationClass1725D0 : public LibClass178600
{
public:
    /** @brief Initialize the widget storage and select kind 3. */
    inline ItemCreationClass1725D0();
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass1725D0();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    float unk50;
    float unk54;
};

/** Partial widget with resident vtable at 0x1746A0. */
class ItemCreationClass1746A0 : public LibClass178600
{
public:
    /** @brief Initialize the widget storage and select kind 4. */
    inline ItemCreationClass1746A0();
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass1746A0();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    u8 unk50;
};

/** Partial widget with resident vtable at 0x175110. */
class ItemCreationClass175110 : public LibClass178600
{
public:
    /** @brief Initialize the owned storage and drawing state for kind 7. */
    ItemCreationClass175110()
    {
        unk38 = 7;
    }
    /** @brief Release the widget storage and destroy its base. */
    virtual ~ItemCreationClass175110();
    /** @brief Refresh the resource drawing state. */
    virtual void func_00413D20();
    /** @brief Draw the resource widget. */
    virtual void func_00462310();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    LibDrawState64 unk50;
    void* unkb4;
    u16 unkb8;
    u16 unkba;
    u8 unkbc;
    u8 unkbd;
    u8 unkbe;
    u8 unkbf;
    s32 unkc0;
    u32 unkc4;
    u8 unkc8;
    u8 unkc9;
    u8 unkca[2];
};

/** Field resource widget using resident table 0x15B240. */
struct ItemCreationOptionResourceDisplay : public ItemCreationClass175110
{
    /** @brief Initialize the resource widget and clear its trailing state. */
    ItemCreationOptionResourceDisplay()
    {
        unk124 = 0;
        unk120 = 0;
        unk11c = 0;
        unk118 = 0;
        ::func_002D6410(static_cast<FieldState2D6410*>(static_cast<void*>(this)));
    }
    /** @brief Destroy the resource widget. */
    virtual ~ItemCreationOptionResourceDisplay();
    /** @brief Refresh the resource widget. */
    virtual void func_00413D20();
    /** @brief Draw the resource widget. */
    virtual void func_00462310();
    void* unkcc;
    u8 unkd0;
    u8 unkd1[0x37];
    FieldResourceRecord* unk108;
    u16 unk10c;
    u16 unk10e;
    u8 unk110;
    u8 unk111;
    u8 unk112;
    u8 unk113;
    u8 unk114;
    u8 unk115[3];
    u32 unk118;
    u32 unk11c;
    u32 unk120;
    u32 unk124;
};


class LibClass1721F0;

/** Option row callback interface with resident vtable at 0x185030. */
class ItemCreationClass185030
{
public:
    /** @brief Destroy the option row interface. */
    virtual ~ItemCreationClass185030()
    {
    }
    /** @brief Update the row flag. @param source Row owner. @param value Current flag. */
    virtual void func_slot0c(LibClass1721F0* source, u8 value) = 0;
    /** @brief Update the row index. @param source Row owner. @param index Current index. */
    virtual void func_slot10(LibClass1721F0* source, s32 index) = 0;
    /** @brief Update the row position. @param source Row owner. @param x Horizontal setting. @param y Vertical setting. */
    virtual void func_slot14(LibClass1721F0* source, float x, float y) = 0;
    /** @brief Read the row float setting. @return Current setting. */
    virtual float func_slot18();
};

/** Four embedded text widgets behind the common row callback interface. */
class ItemCreationClass186050 : public ItemCreationClass185030
{
public:
    /** @brief Initialize the four text widgets. */
    ItemCreationClass186050()
    {
    }
    /** @brief Destroy the four text widgets and row interface. */
    virtual ~ItemCreationClass186050();
    /** @brief Update the row flag. @param source Row owner. @param value Current flag. */
    virtual void func_slot0c(LibClass1721F0* source, u8 value);
    /** @brief Update the row index. @param source Row owner. @param index Current index. */
    virtual void func_slot10(LibClass1721F0* source, s32 index);
    /** @brief Update the row position. @param source Row owner. @param x Horizontal setting. @param y Vertical setting. */
    virtual void func_slot14(LibClass1721F0* source, float x, float y);
    LibObject178750 unk04;
    LibObject178750 unk118;
    LibObject178750 unk22c;
    LibObject178750 unk340;
};

/** 0x3C-byte storage receiver, with its dispatch pointer after the stored state. */
class ItemCreationClass185050
{
public:
    LibStorageBlock0C unk00;
    u8 unk0c[4];
    float unk10;
    float unk14;
    float unk18;
    float unk1c;
    float unk20;
    float unk24;
    u8 unk28[8];
    float unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36[2];

    /** @brief Initialize the storage and clear its three scalar pairs. */
    ItemCreationClass185050()
    {
        unk14 = 0.0f;
        unk10 = 0.0f;
        unk1c = 0.0f;
        unk18 = 0.0f;
        unk24 = 0.0f;
        unk20 = 0.0f;
    }
    /** @brief Release the owned storage. */
    virtual ~ItemCreationClass185050()
    {
    }
    virtual void func_slot0c();
};

/** Partial kind-9 widget with a storage base at offset 0x40. */
class ItemCreationClass175030 : public LibClass178600, public ItemCreationClass185050
{
public:
    /** @brief Initialize the widget and select kind 9. */
    inline ItemCreationClass175030();
    /** @brief Destroy the storage base and widget base. */
    virtual ~ItemCreationClass175030();
};

/** Kind-2 widget over the 0x90-byte resident widget base. */
class ItemCreationClass184F30 : public LibClass178630
{
public:
    /** @brief Initialize the widget and select kind 2. */
    ItemCreationClass184F30();
    /** @brief Destroy the resident widget base. */
    virtual ~ItemCreationClass184F30();
};

/** Seven-widget aggregate with its dispatch pointer after the stored state. */
class ItemCreationClass1723F0
{
public:
    ItemCreationClass184F30 unk00;
    ItemCreationClass1746A0 unk90;
    ItemCreationClass1746A0 unke4;
    ItemCreationClass1725D0 unk138;
    ItemCreationClass175030 unk190;
    ItemCreationClass172600 unk20c;
    ItemCreationClass172870 unk260;
    u8 unk2b8[0x64];
    /** @brief Initialize the seven embedded widgets. */
    ItemCreationClass1723F0()
    {
    }
    /** @brief Destroy the seven embedded widgets. */
    ~ItemCreationClass1723F0()
    {
    }
    /** @brief Handle the aggregate selection. @param index Selected index. */
    virtual void func_00412C10(s32 index);
    /** @brief Run the second aggregate state hook. */
    virtual void func_00412C20();
    /** @brief Read the aggregate value. @return Aggregate value. */
    virtual float func_00412C30();
    /** @brief Update the aggregate widgets and selection state. */
    virtual void func_00413020();
};

/** Container with its seven-widget aggregate as a second base. */
class ItemCreationClass184F60 : public LibObject178660, public ItemCreationClass1723F0
{
public:
    /** @brief Initialize the container and its widget aggregate. */
    ItemCreationClass184F60();
    /** @brief Destroy the widget aggregate and container. */
    virtual ~ItemCreationClass184F60();
};

/** Window with MAIN vtable 0x186170 and no storage beyond the Field base. */
class ItemCreationClass186170 : public FieldClass15AE70
{
public:
    /** @brief Initialize the Field window base. */
    ItemCreationClass186170()
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~ItemCreationClass186170();
    /** @brief Handle the return action. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Handle the alternate action. @return Action status. */
    virtual s32 func_slotb4();
    /** @brief Set up the window. @param associated Associated object. @return Setup status. */
    virtual s32 func_slotf4(void* associated);
};

extern "C" {
#endif

/**
 * @brief Refresh the selected item's child window displays.
 * @param object Child window receiver.
 */
void func_00352DE0(struct ItemCreationClass186070* object);

/**
 * @brief Create the resource displays for the twelve-option selection grid.
 * @param object Window owning the selection and resource displays.
 * @return Always one.
 */
s32 func_0034FA70(struct ItemCreationClass185A60* object);

/**
 * @brief Select the result window's text resource for its mode.
 * @param object Result window.
 * @param mode Mode to store; zero through two select a resource.
 */
void func_003500D0(struct ItemCreationClass185B60* object, u8 mode);

/**
 * @brief Restore the associated window and dispatch the result state.
 * @param object Result window.
 * @return Always one.
 */
s32 func_0034FE00(struct ItemCreationClass185B60* object);

/**
 * @brief Restore the associated window and dispatch the result state.
 * @param object Result window.
 * @return Always one.
 */
s32 func_0034FF70(struct ItemCreationClass185B60* object);

/**
 * @brief Create and attach the result window's display widgets.
 * @param object Result window.
 * @param associated Object associated with the window.
 * @return Always one.
 */
s32 func_003501B0(struct ItemCreationClass185B60* object, void* associated);

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
 * @brief Return the selection state's associated pointer.
 * @param object Selection state.
 * @return Stored pointer.
 */
void* func_0034FF60(ItemCreationSelectedDisplayState* object);

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
