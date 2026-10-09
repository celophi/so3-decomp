#ifndef SO3_OVERLAYS_CMC_TEXT_H
#define SO3_OVERLAYS_CMC_TEXT_H

#include "types.h"

#ifdef __cplusplus
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_001E1590.h"

class CmcClass188EF0;

/** Partial callback controller prefix, with MAIN vtable at 0x18AF20. */
class CmcClass18AF20 : public FieldClass153E30
{
public:
    /** @brief Initialize the callback controller and its retained object pointers. */
    CmcClass18AF20();
    /** @brief Dispatch the requested window action. */
    void dispatch_window_request();
    /** @brief Initialize the linked object. @return One on success, zero on failure. */
    virtual u8 func_00264110();
    /** @brief Destroy the callback controller. */
    virtual ~CmcClass18AF20();
    /** @brief Add this object to the resident queue. */
    virtual void func_001DD7B0();
    /**
     * @brief Bind a completed resource buffer and finish controller setup.
     * @param buffer Completed buffer.
     * @return Setup result, or zero when the buffer is null.
     */
    virtual s32 func_001E1820(void* buffer);
    /** @brief Release the retained resource slot, detach the controller, and queue it. */
    virtual void release_resources();
    s32 resource_slot;
    CmcClass188EF0* linked_object;
    void* unk3c;
    u8 unk40;
    u8 unk41[3];
    FieldClass15AE70* unk44;
    u16 unk48;
    u8 unk4a[2];
    FieldClass15AE70* unk4c;
    u8 unk50;
    u8 unk51;
    u16 unk52;
    u32 unk54;
    FieldClass15AE70* unk58;
    FieldClass15AE70* unk5c;
    FieldClass15AE70* unk60;
    FieldClass15AE70* unk64;
    FieldClass15AE70* unk68;
    FieldClass15AE70* unk6c;
    FieldClass15AE70* unk70;
    FieldClass15AE70* unk74;
    FieldClass15AE70* unk78;
    FieldClass15AE70* unk7c;
    u8 unk80;
};

/** Partial window storage prefix, with MAIN vtable at 0x18AD20. */
class CmcClass18AD20 : public FieldClass15AE70
{
public:
    /** @brief Initialize the window, retained widgets, and animation state. */
    CmcClass18AD20();
    /** @brief Set the window message. @param text_key Message key. */
    virtual void func_slot60(s32 text_key);
    /** @brief Destroy the window. */
    virtual ~CmcClass18AD20();
    /** @brief Update widget state and advance the text rectangle animation. */
    virtual void func_slot5c();
    LibObject178750* unkA8;
    LibObject178750* unkAc;
    LibObject178750* unkB0;
    s32 unkB4;
    s8 unkB8;
    u8 unkB9;
    u8 unkBa;
    u8 unkBb;
    s16 unkBc;
    s8 unkBe;
    u8 unkBf;
    float unkC0;
    float unkC4;
    float unkC8;
    float unkCc;
    ItemCreationClass172870* unkD0;
    u8 unkD4;
};

/** Partial window prefix containing its selection widget, with MAIN vtable at 0x189110. */
class CmcClass189110 : public FieldClass15AE70
{
public:
    /** @brief Run the selection action. @return Window action status. */
    virtual s32 func_slotb0();
    /** @brief Request the controller action and hide the nested display. @return Two. */
    virtual s32 func_slotb4();
    /** @brief Destroy the window. */
    virtual ~CmcClass189110();
    /** @brief Move the child selector backward. */
    virtual void func_slot68();
    /** @brief Move the child selector forward. */
    virtual void func_slot6c();
    CmcClass18AF20* unka8;
    u8 unkac[4];
    FieldClass153130* selector;
};

/** Known root dispatch interface, with MAIN vtable at 0x188ED0. */
class CmcClass188ED0
{
public:
    /** @brief Destroy the root. */
    virtual ~CmcClass188ED0();
};

/** Known intermediate dispatch interface, with MAIN vtable at 0x188EE0. */
class CmcClass188EE0 : public CmcClass188ED0
{
public:
    /** @brief Destroy the intermediate object. */
    virtual ~CmcClass188EE0();
};

/** Known linked-object virtual prefix, with MAIN vtable at 0x188EF0. */
class CmcClass188EF0 : public CmcClass188EE0
{
public:
    /** @brief Destroy the linked object. */
    virtual ~CmcClass188EF0();
    /** @brief Return the object type value. @return Three. */
    virtual s32 func_00348400();
    /** @brief Destroy this object through its virtual destructor. */
    virtual void func_00358F90();
};

/** Partial eight-byte root, with MAIN vtable D_188DA0. */
class CmcClass188DA0
{
public:
    /** @brief Initialize the root dispatch pointer. */
    CmcClass188DA0()
    {
    }
    /** @brief Destroy the root. */
    virtual ~CmcClass188DA0()
    {
    }
    /**
     * @brief Set the row widget byte flags.
     * @param unused Unused owner argument.
     * @param value Byte flag value.
     */
    virtual void func_003591A0(void* unused, u8 value) = 0;
    /**
     * @brief Refresh the row widgets.
     * @param owner Containing list owner.
     * @param index Signed row index.
     */
    virtual void refresh_row(void* owner, s32 index) = 0;
    /**
     * @brief Position the row widgets.
     * @param owner Containing list owner.
     * @param x Horizontal position.
     * @param y Vertical position.
     */
    virtual void position_row(void* owner, float x, float y) = 0;
    /**
     * @brief Return zero as a floating-point value.
     * @return Zero.
     */
    virtual float func_00358F80()
    {
        return 0.0f;
    }
    u8 unk04;
    u8 unk05;
    u8 pad06[2];
};

/** D10-byte owner of a panel, text widgets, and five numeric widgets. */
class CmcClass189900 : public CmcClass188DA0
{
public:
    /** @brief Initialize the embedded widgets and root state. */
    CmcClass189900();
    /** @brief Destroy the embedded widgets. */
    virtual ~CmcClass189900();
    /**
     * @brief Set the row widget byte flags.
     * @param unused Unused owner argument.
     * @param value Byte flag value.
     */
    virtual void func_003591A0(void* unused, u8 value);
    /**
     * @brief Refresh the row widgets.
     * @param owner Containing list owner.
     * @param index Signed row index.
     */
    virtual void refresh_row(void* owner, s32 index);
    /**
     * @brief Position the row widgets.
     * @param owner Containing list owner.
     * @param x Horizontal position.
     * @param y Vertical position.
     */
    virtual void position_row(void* owner, float x, float y);
    LibClass178630 panel;
    LibObject178750 first_text;
    LibObject175140 string_widget;
    LibObject178750 second_text;
    LibObject174F20 numbers[5];
    LibObject178750 array_text[2];
    LibObject178750 third_text;
    LibObject178750 fourth_text;
};

/** Partial 0xB0-byte window interface, with MAIN vtable at 0x189920. */
class CmcClass189920 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~CmcClass189920();
    /**
     * @brief Restore the parent window, queue this window, and set the alternate window text key.
     * @return One.
     */
    virtual s32 func_slotb0();
    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual s32 func_slotb4();
    u8 unka8[8];
};

/** Partial 0xA8-byte window interface, with MAIN vtable at 0x189A20. */
class CmcClass189A20 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~CmcClass189A20();
    /**
     * @brief Restore the parent window, queue this window, and set the alternate window text key.
     * @return One.
     */
    virtual s32 func_slotb0();
    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual s32 func_slotb4();
};

/** Partial 0xA8-byte window interface, with MAIN vtable at 0x189F20. */
class CmcClass189F20 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~CmcClass189F20();
    /**
     * @brief Restore the parent window, queue this window, and set the alternate window text key.
     * @return One.
     */
    virtual s32 func_slotb0();
    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual s32 func_slotb4();
};

/** Partial 0xA8-byte window interface, with MAIN vtable at 0x18A020. */
class CmcClass18A020 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~CmcClass18A020();
    /**
     * @brief Restore the parent window, queue this window, and set the alternate window text key.
     * @return One.
     */
    virtual s32 func_slotb0();
    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual s32 func_slotb4();
};

/** Partial 0xB0-byte window interface, with MAIN vtable at 0x18A120. */
class CmcClass18A120 : public FieldClass15AE70
{
public:
    /** @brief Handle the window action. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Destroy the window. */
    virtual ~CmcClass18A120();
    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual s32 func_slotb4();
    u8 unka8[8];
};

/** Partial 0xA8-byte window interface, with MAIN vtable at 0x18A220. */
class CmcClass18A220 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~CmcClass18A220();
    /**
     * @brief Restore the parent window, queue this window, and set the alternate window text key.
     * @return One.
     */
    virtual s32 func_slotb0();
    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual s32 func_slotb4();
};

/** Partial 0xB0-byte window interface, with MAIN vtable at 0x18A320. */
class CmcClass18A320 : public FieldClass15AE70
{
public:
    /** @brief Handle the window action. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Destroy the window. */
    virtual ~CmcClass18A320();
    /**
     * @brief Run the window action when its guard byte is clear.
     * @return Zero when guarded, otherwise one after running the action.
     */
    virtual s32 func_slotb4();
    void* unka8;
    u8 unkac;
    u8 unkad[3];
};

/** Partial 0xA8-byte window interface, with MAIN vtable at 0x18A620. */
class CmcClass18A620 : public FieldClass15AE70
{
public:
    /** @brief Handle the window action. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Destroy the window. */
    virtual ~CmcClass18A620();
    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual s32 func_slotb4();
};

/** Partial 0xB0-byte window interface, with MAIN vtable at 0x18A820. */
class CmcClass18A820 : public FieldClass15AE70
{
public:
    /** @brief Handle the window action. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Destroy the window. */
    virtual ~CmcClass18A820();
    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual s32 func_slotb4();
    u8 unka8[8];
};

/** Partial 0xCC-byte window interface, with MAIN vtable at 0x189C20. */
class CmcClass189C20 : public FieldClass15AE70
{
public:
    /** @brief Destroy the window. */
    virtual ~CmcClass189C20();
    /** @brief Release nested displays and unregister this window. */
    virtual void func_slot0c();
    u8 unka8[0x24];
};

/** Partial 0xB4-byte window interface, with MAIN vtable at 0x18AA20. */
class CmcClass18AA20 : public FieldClass15AE70
{
public:
    /** @brief Update the window state. */
    virtual void func_slot5c();
    /** @brief Destroy the window. */
    virtual ~CmcClass18AA20();
    /**
     * @brief Set display flags on selected lists.
     * @param flag Display flag word.
     * @param list_mask List groups selected by bits 0 through 6.
     */
    virtual void func_slot18(u32 flag, u32 list_mask);
    u8 unka8[0xC];
};

/** Partial 0xAC-byte window interface, with MAIN vtable at 0x18AB20. */
class CmcClass18AB20 : public FieldClass15AE70
{
public:
    /** @brief Handle the window action. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Destroy the window. */
    virtual ~CmcClass18AB20();
    /**
     * @brief Set display flags on selected lists.
     * @param flag Display flag word.
     * @param list_mask List groups selected by bits 0 through 6.
     */
    virtual void func_slot18(u32 flag, u32 list_mask);
    u8 unka8[4];
};

/** Partial 0xC0-byte window interface, with MAIN vtable at 0x18AC20. */
class CmcClass18AC20 : public FieldClass15AE70
{
public:
    /** @brief Update the window state. */
    virtual void func_slot5c();
    /** @brief Destroy the window. */
    virtual ~CmcClass18AC20();
    /**
     * @brief Set list flags and the target display byte flag when the low flag byte is one.
     * @param flag Display flag word.
     * @param list_mask List groups selected by bits 0 through 6.
     */
    virtual void func_slot18(u32 flag, u32 list_mask);
    /**
     * @brief Find the final associated window.
     * @return Last window in the chain, including this window when it has no association.
     */
    virtual void* func_slot3c();
    /**
     * @brief Set the window control byte to one and return status two.
     * @return Two.
     */
    virtual s32 func_slotb4();
    u8 unka8[0x14];
    FieldObject23B950* target_display;
};
#endif

typedef struct CmcDrawParameters CmcDrawParameters;
typedef struct Overlay0072Object00349670 Overlay0072Object00349670;
typedef struct Overlay0072Object00349AB0 Overlay0072Object00349AB0;
typedef struct Overlay0072Object0034A1D0 Overlay0072Object0034A1D0;
typedef struct Overlay0072Object0034A690 Overlay0072Object0034A690;
typedef struct Overlay0072Object0034BB10 Overlay0072Object0034BB10;
typedef struct Overlay0072Object0034CF80 Overlay0072Object0034CF80;
typedef struct Overlay0072Object00359210 Overlay0072Object00359210;
typedef struct Overlay0072Object003594A0 Overlay0072Object003594A0;
typedef struct Overlay0072Object00359600 Overlay0072Object00359600;
typedef struct Overlay0072Object0035AFC0 Overlay0072Object0035AFC0;
typedef struct Overlay0072Object00359C10 Overlay0072Object00359C10;
typedef struct Overlay0072Object00353710 Overlay0072Object00353710;
typedef struct Overlay0072Object00358FE0 Overlay0072Object00358FE0;
typedef struct Overlay0072Object003494F0 Overlay0072Object003494F0;
typedef struct Overlay0072Object00358FC0 Overlay0072Object00358FC0;
typedef struct Overlay0072Object00359000 Overlay0072Object00359000;
typedef struct Overlay0072Object003590E0 Overlay0072Object003590E0;
typedef struct Overlay0072CtorObject0034D0E0 Overlay0072CtorObject0034D0E0;
typedef struct Overlay0072ListNode Overlay0072ListNode;
typedef struct Overlay0072List Overlay0072List;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the drawing parameters to their defaults.
 * @param parameters Drawing parameters to initialize.
 */
void cmc_initialize_drawing_parameters(CmcDrawParameters* parameters);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00348400(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348410(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348420(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0034BB00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0034BD60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0034BD70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003540E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003585A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00359140(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00359180(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359190(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003591B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003591C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003591E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359200(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359290(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003592A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003592B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003592C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003592D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003592E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003592F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359300(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359310(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359320(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359330(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359340(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359350(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359360(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359370(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359380(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359390(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003593A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003593B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003593C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003593D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003593E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003593F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00359400(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00359410(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00359420(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00359430(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00359440(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00359450(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00359460(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00359470(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359480(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359490(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003594C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003594D0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00359630(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359670(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00359680(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359690(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003596A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003596B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003596C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003596D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003596E0(void* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_00359960(void* object);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
s32 func_00349670(Overlay0072Object00349670* object);

/**
 * @brief Set a field on this object.
 * @param object Object to update.
 * @param value New field value.
 */
void func_00349AB0(Overlay0072Object00349AB0* object, u8 value);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
u8 func_0034A1D0(Overlay0072Object0034A1D0* object);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
s32 func_0034A1E0(Overlay0072Object0034A1D0* object);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
s32 func_0034A690(Overlay0072Object0034A690* object);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
s32 func_0034BB10(Overlay0072Object0034BB10* object);

/**
 * @brief Set a field on this object.
 * @param object Object to update.
 * @param value New field value.
 */
void func_0034BB20(Overlay0072Object0034BB10* object, s32 value);

/**
 * @brief Set a field on this object.
 * @param object Object to update.
 * @param value New field value.
 */
void func_0034BB30(Overlay0072Object0034BB10* object, s32 value);

/**
 * @brief Set a field on this object.
 * @param object Object to update.
 * @param value New field value.
 */
void func_0034CF80(Overlay0072Object0034CF80* object, u16 value);

/**
 * @brief Set a field on this object.
 * @param object Object to update.
 * @param value New field value.
 */
void func_00359210(Overlay0072Object00359210* object, u8 value);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
u8 func_00359220(Overlay0072Object00359210* object);

/**
 * @brief Set a field on this object.
 * @param object Object to update.
 * @param value New field value.
 */
void func_00359230(Overlay0072Object00359210* object, u16 value);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
u16 func_00359240(Overlay0072Object00359210* object);

/**
 * @brief Set a field on this object.
 * @param object Object to update.
 * @param value New field value.
 */
void func_00359250(Overlay0072Object00359210* object, s32 value);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
s32 func_00359260(Overlay0072Object00359210* object);

/**
 * @brief Set a field on this object.
 * @param object Object to update.
 * @param value New field value.
 */
void func_00359270(Overlay0072Object00359210* object, s32 value);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
s32 func_00359280(Overlay0072Object00359210* object);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
u8 func_003594A0(Overlay0072Object003594A0* object);

/**
 * @brief Set a field on this object.
 * @param object Object to update.
 * @param value New field value.
 */
void func_003594B0(Overlay0072Object003594A0* object, u8 value);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
s32 func_00359600(Overlay0072Object00359600* object);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
u8 func_00359610(Overlay0072Object00359600* object);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
s32 func_00359620(Overlay0072Object00359600* object);

/**
 * @brief Set a field on this object.
 * @param object Object to update.
 * @param value New field value.
 */
void func_00359640(Overlay0072Object00359600* object, s32 value);

/**
 * @brief Set a field on this object.
 * @param object Object to update.
 * @param value New field value.
 */
void func_00359650(Overlay0072Object00359600* object, u8 value);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
s8 func_00359660(Overlay0072Object00359600* object);

/**
 * @brief Return a field from this object.
 * @param object Object to read.
 * @return The field value.
 */
s16 func_0035AFC0(Overlay0072Object0035AFC0* object);

/**
 * @brief Return zero as a floating-point value.
 * @param object Receiver or first argument; unused.
 * @return Zero.
 */
float func_003591D0(void* object);

/**
 * @brief Copy one byte field into another.
 * @param object Object to update.
 */
void func_003591F0(Overlay0072Object00359210* object);

/**
 * @brief Read a byte from the referenced object.
 * @param object Object holding the reference.
 * @return The referenced byte.
 */
u8 func_00359C10(Overlay0072Object00359C10* object);

/**
 * @brief Test whether a floating-point value is negative.
 * @param value Value to test.
 * @return 1 if negative, otherwise 0.
 */
s32 func_00359150(float value);

/**
 * @brief Reset several fields on this object.
 * @param object Object to reset.
 * @param value Value to store in the first short field.
 */
void func_0035AF60(Overlay0072Object0035AFC0* object, s16 value);

/**
 * @brief Read the selected record's field at 0x50.
 * @param object Object holding the selected record index.
 * @return Field value.
 */
s32 func_0035AF80(Overlay0072Object0035AFC0* object);

/**
 * @brief Read the selected record's field at 0x4C.
 * @param object Object holding the selected record index.
 * @return Field value.
 */
s32 func_0035AFA0(Overlay0072Object0035AFC0* object);

/**
 * @brief Read a record's field at 0x48.
 * @param object Object holding the record array.
 * @param index Record index.
 * @return Field value.
 */
s32 func_0035AFD0(Overlay0072Object0035AFC0* object, s16 index);

/**
 * @brief Update two byte fields and clear the current index for value 1.
 * @param object Object to update.
 * @param value New state value.
 * @param other New companion value.
 */
void func_0035ADA0(Overlay0072Object0035AFC0* object, u8 value, u8 other);

/**
 * @brief Store three floating-point values and mark them active.
 * @param object Object to update.
 * @param x First value.
 * @param y Second value.
 * @param z Third value.
 */
void func_00359120(Overlay0072Object00359210* object, float x, float y, float z);

/**
 * @brief Store four floating-point values and mark them active.
 * @param object Object to update.
 * @param x First value.
 * @param y Second value.
 * @param z Third value.
 * @param w Fourth value.
 */
void func_00358FE0(Overlay0072Object00358FE0* object, float x, float y, float z, float w);

/**
 * @brief Store three floating-point values and a fixed fourth component.
 * @param object Object to update.
 * @param x First value.
 * @param y Second value.
 * @param z Third value.
 */
void func_00353710(Overlay0072Object00353710* object, float x, float y, float z);

/**
 * @brief Return the address of D_50CD30.
 * @param object Receiver or first argument; unused.
 * @return Address of D_50CD30.
 */
u8* func_00359170(void* object);

/**
 * @brief Return a positive field value or zero.
 * @param object Object holding the referenced field.
 * @return Field value if positive, otherwise zero.
 */
s32 func_00359C20(Overlay0072Object00359C10* object);

/**
 * @brief Copy a 128-bit value into this object and mark it active.
 * @param object Object to update.
 * @param value Value to copy.
 */
void func_003494F0(Overlay0072Object003494F0* object, const unsigned __int128* value);

/**
 * @brief Copy a 128-bit value into this object and mark it active.
 * @param object Object to update.
 * @param value Value to copy.
 */
void func_00358FC0(Overlay0072Object00358FC0* object, const unsigned __int128* value);

/**
 * @brief Copy a 128-bit value into this object and mark it active.
 * @param object Object to update.
 * @param value Value to copy.
 */
void func_00359000(Overlay0072Object00359000* object, const unsigned __int128* value);

/**
 * @brief Copy a 128-bit value into this object and mark it active.
 * @param object Object to update.
 * @param value Value to copy.
 */
void func_00359020(Overlay0072Object00359000* object, const unsigned __int128* value);

/**
 * @brief Copy a 128-bit value into this object and mark it active.
 * @param object Object to update.
 * @param value Value to copy.
 */
void func_003590E0(Overlay0072Object003590E0* object, const unsigned __int128* value);

/**
 * @brief Copy a 128-bit value into this object and mark it active.
 * @param object Object to update.
 * @param value Value to copy.
 */
void func_00359100(Overlay0072Object003590E0* object, const unsigned __int128* value);

/**
 * @brief Initialize the object and set state 6.
 * @param object Object to initialize.
 * @return The initialized object.
 */
Overlay0072CtorObject0034D0E0* func_0034D0E0(Overlay0072CtorObject0034D0E0* object);

/**
 * @brief Initialize the object and set state 5.
 * @param object Object to initialize.
 * @return The initialized object.
 */
Overlay0072CtorObject0034D0E0* func_0034D120(Overlay0072CtorObject0034D0E0* object);

/**
 * @brief Initialize the object and set state 3.
 * @param object Object to initialize.
 * @return The initialized object.
 */
Overlay0072CtorObject0034D0E0* func_0034D230(Overlay0072CtorObject0034D0E0* object);

/**
 * @brief Initialize the object and set state 4.
 * @param object Object to initialize.
 * @return The initialized object.
 */
Overlay0072CtorObject0034D0E0* func_0034D270(Overlay0072CtorObject0034D0E0* object);

/**
 * @brief Set the same value in several byte fields.
 * @param object Object to update.
 * @param unused Second argument; unused.
 * @param value Value for each field.
 */
void func_0034D880(u8* object, void* unused, u8 value);

/**
 * @brief Append a value to the list when allocation succeeds.
 * @param list List to extend.
 * @param value Value to append.
 */
void func_003596F0(Overlay0072List* list, void* value);

/**
 * @brief Append a value to the list when allocation succeeds.
 * @param list List to extend.
 * @param value Value to append.
 */
void func_00359780(Overlay0072List* list, void* value);

/**
 * @brief Find the list node at the given index.
 * @param list List to search.
 * @param index Zero-based index after the head node.
 * @return Matching node, or null if the chain ends early.
 */
Overlay0072ListNode* func_00359810(Overlay0072List* list, s32 index);

/**
 * @brief Append a value to the list when allocation succeeds.
 * @param list List to extend.
 * @param value Value to append.
 */
void func_00359850(Overlay0072List* list, void* value);

#ifdef __cplusplus
}
#endif

#endif
