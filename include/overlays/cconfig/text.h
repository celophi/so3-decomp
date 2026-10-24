#ifndef SO3_OVERLAYS_CCONFIG_TEXT_H
#define SO3_OVERLAYS_CCONFIG_TEXT_H

#include "types.h"

typedef struct ConfigList182210 ConfigList182210;
typedef struct ConfigList182200 ConfigList182200;
typedef struct ConfigColorWindow ConfigColorWindow;
typedef struct ConfigOptions ConfigOptions;
typedef struct ConfigGridWindow ConfigGridWindow;
typedef struct ConfigBindingWindow ConfigBindingWindow;
typedef struct ConfigCornerWindow ConfigCornerWindow;
typedef struct ConfigControlReceiver ConfigControlReceiver;
typedef struct ConfigMessageWindow ConfigMessageWindow;
typedef struct ConfigFrameWindow ConfigFrameWindow;
typedef struct ItemCreationClass1725D0 ItemCreationClass1725D0;
typedef struct ItemCreationOptionResourceDisplay ItemCreationOptionResourceDisplay;
typedef struct ConfigPreviewWindow ConfigPreviewWindow;
typedef struct FieldClass15AE70 FieldClass15AE70;

typedef struct ConfigNode
{
    void* value;
    struct ConfigNode* next;
#ifdef __cplusplus
    /** @brief Release the link without destroying its payload. */
    ~ConfigNode()
    {
    }
#endif
} ConfigNode;

typedef struct
{
    ConfigNode* head;
    s32 count;
} ConfigListOwner;

#ifdef __cplusplus
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/lib/text_0045AD10.h"

class ConfigController;

/** Configuration display list with an owned sentinel and a virtual destructor. */
struct ConfigList182210
{
    ConfigNode* head;
    s32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    ConfigList182210();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~ConfigList182210();
};

/** Configuration list with a distinct virtual destructor and an owned sentinel. */
struct ConfigList182200
{
    ConfigNode* head;
    s32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    ConfigList182200();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~ConfigList182200();
};

/** Configuration options window and its thirty-one owned display lists. */
struct ConfigOptions : public FieldClass15AE70
{
    /** @brief Initialize the options window and its owned lists. */
    ConfigOptions();
    /** @brief Release the owned display lists and the window base. */
    virtual ~ConfigOptions();
    /** @brief Refresh the bindings while this window is active. */
    virtual void func_slot5c();
    /** @brief Refresh the moving selection marker and update the window message. */
    virtual void func_slot64();
    /** @brief Forward to the previous-option hook. */
    virtual void func_slot68();
    /** @brief Forward to the next-option hook. */
    virtual void func_slot6c();
    /** @brief Move the selection to the previous available option. */
    virtual void func_slota0();
    /** @brief Move the selection to the next available option. */
    virtual void func_slota4();
    /** @brief Apply option control mask 0x80. */
    virtual void func_slota8();
    /** @brief Apply option control mask 0x20. */
    virtual void func_slotac();
    /**
     * @brief Confirm the button or window-color row: open its editor, or restore the defaults when the row offers that.
     * @return One after opening an editor or restoring defaults, otherwise zero.
     */
    virtual u8 func_slotb0();
    /**
     * @brief Leave the options: close at once when the menu runtime asks for it, otherwise open the end-configuration prompt.
     * @return Zero without a menu runtime, otherwise two.
     */
    virtual u8 func_slotb4();
    /** @brief Create the option displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    ConfigController* controller;
    LibClass175030* scroll;
    bool unkb0;
    u8 selected;
    u8 unkb2;
    u8 unkb3;
    u16 last_index;
    u16 unkb6;
    s32 unkb8;
    float positions[14];
    ItemCreationOptionResourceDisplay* unkf4;
    s32 unkf8;
    s32 unkfc;
    u8 unk100;
    u8 unk101;
    u8 unk102[2];
    float unk104;
    float unk108;
    float unk10c;
    float unk110;
    ConfigList182200 list;
    ConfigList182200 list0_first;
    ConfigList182210 list0_second;
    ConfigList182200 list1_first;
    ConfigList182210 list1_second;
    ConfigList182200 list2_first;
    ConfigList182210 list2_second;
    ConfigList182200 list3_first;
    ConfigList182210 list3_second;
    ConfigList182200 list4_first;
    ConfigList182210 list4_second;
    ConfigList182200 list5_first;
    ConfigList182210 list5_second;
    ConfigList182200 list6_first;
    ConfigList182210 list6_second;
    ConfigList182200 list7_first;
    ConfigList182210 list7_second;
    ConfigList182200 list8_first;
    ConfigList182210 list8_second;
    ConfigList182200 list9_first;
    ConfigList182210 list9_second;
    ConfigList182200 list10_first;
    ConfigList182210 list10_second;
    ConfigList182200 list11_first;
    ConfigList182210 list11_second;
    ConfigList182200 list12_first;
    ConfigList182210 list12_second;
    ConfigList182200 list13_first;
    ConfigList182210 list13_second;
    ConfigList182200 list14_first;
    ConfigList182210 list14_second;
    u8 unk288;
    u8 unk289[3];
    ItemCreationClass1725D0* unk28c;
    float unk290;
    float unk294;
    float unk298;
    float unk29c;
    float unk2a0;
};

extern "C" {
#endif

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034FC70(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034F880(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034F5E0(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034F340(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034FF10(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034F0A0(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034EDE0(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034EB40(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034E5D0(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034E330(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034E090(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034DDF0(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034DB50(ConfigOptions* object, u32 associated);

/**
 * @brief Create the option row displays.
 * @param object Configuration options window.
 * @param associated Full resource source word.
 * @return One after creation, or zero without an associated resource.
 */
s32 func_0034D8B0(ConfigOptions* object, u32 associated);

/**
 * @brief Color the option rows, distinguishing the selected row and disabled row twelve.
 * @param object Configuration options window.
 * @param selected Selected row index.
 */
void func_0034B180(ConfigOptions* object, u16 selected);

/**
 * @brief Refresh the selected row's option markers and resource display level.
 * @param object Configuration options window.
 * @param row Option row to refresh.
 */
void func_0034B430(ConfigOptions* object, u16 row);

/**
 * @brief Update option row four's setting and choice colors.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034BA10(ConfigOptions* object, u16 input);

/**
 * @brief Toggle the protected mode and update option row thirteen's choice colors.
 * @param object Configuration options window.
 * @param input Control mask supplied by the row dispatcher.
 */
void func_0034BB60(ConfigOptions* object, u16 input);

/**
 * @brief Update option row twelve's setting and choice colors when the feature is enabled.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034BD70(ConfigOptions* object, u16 input);

/**
 * @brief Switch the screen aspect ratio between 4:3 and 16:9, recolor its two choices, and update the preview and camera.
 * @param object Configuration options window.
 * @param input Control mask for the row (0x80 or 0x20).
 */
void func_0034BF40(ConfigOptions* object, u16 input);

/**
 * @brief Update option row ten's message key and choice colors.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034C140(ConfigOptions* object, u16 input);

/**
 * @brief Update option row nine's message key and choice colors.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034C260(ConfigOptions* object, u16 input);

/**
 * @brief Update option row 6's stored flag and choice colors.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034C7C0(ConfigOptions* object, u16 input);

/**
 * @brief Update option row 5's stored flag and choice colors.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034C900(ConfigOptions* object, u16 input);

/**
 * @brief Update option row 2's stored flag and choice colors.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034CBB0(ConfigOptions* object, u16 input);

/**
 * @brief Update option row 0's stored flag and choice colors.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034D040(ConfigOptions* object, u16 input);

/**
 * @brief Update option row three's two-bit mode and choice colors.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034CA40(ConfigOptions* object, u16 input);

/**
 * @brief Update option row seven's input flag, effect, and choice colors.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034C600(ConfigOptions* object, u16 input);

/**
 * @brief Cycle option row eight's input mode and refresh its choice colors.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034C380(ConfigOptions* object, u16 input);

/**
 * @brief Cycle option row one's two-bit mode and refresh its choice colors.
 * @param object Configuration options window.
 * @param input Control mask for the row.
 */
void func_0034CD00(ConfigOptions* object, u16 input);

/**
 * @brief Advance the active options-list movement and update its indicator.
 * @param object Configuration options window.
 */
void func_0034AD30(ConfigOptions* object);

/**
 * @brief Update row highlights while the selector window is active.
 * @param object Configuration selector window.
 */
void func_00348750(ConfigGridWindow* object);

/**
 * @brief Pass direction code 1 to the option grid.
 * @param object Configuration selector window.
 */
void func_003487C0(ConfigGridWindow* object);

/**
 * @brief Pass direction code 0 to the option grid.
 * @param object Configuration selector window.
 */
void func_00348800(ConfigGridWindow* object);

/**
 * @brief Create the end-configuration prompt with its panel, Yes and No labels, and two-row grid.
 * @param object End-configuration confirmation window.
 * @param associated Full resource source word.
 * @param x Horizontal window position.
 * @param y Vertical window position.
 * @param code Base window initializer code.
 * @return One after creation, or zero when the panel, a label, or the grid is absent.
 */
s32 func_00348950(ConfigGridWindow* object, u32 associated, float x, float y, s32 code);

/**
 * @brief Pass direction code 1 to the color component grid.
 * @param object Window-color editor.
 */
void func_00349110(ConfigColorWindow* object);

/**
 * @brief Refresh the component numbers and preview, and show the edited color on its corner of the selector frame.
 * @param object Window-color editor.
 */
void func_00348D20(ConfigColorWindow* object);

/**
 * @brief Pass direction code 0 to the color component grid.
 * @param object Window-color editor.
 */
void func_00349150(ConfigColorWindow* object);

/**
 * @brief Store the edited color in its corner of the window colors, repaint the frame, and close the editor.
 * @param object Window-color editor.
 * @return One after closing.
 */
u8 func_00349230(ConfigColorWindow* object);

/**
 * @brief Create the color editor's preview panel, component labels, number widgets, and grid, starting from the corner's stored color.
 * @param object Window-color editor.
 * @param associated Full resource source word.
 * @param x Horizontal window position.
 * @param y Vertical window position.
 * @return One after creation, or zero when a display or the grid is absent or no corner is set.
 */
s32 func_00349320(ConfigColorWindow* object, u32 associated, float x, float y);

/**
 * @brief Check whether the corner selector is the active window; no work follows the check.
 * @param object Window-color corner selector.
 */
void func_00349810(ConfigCornerWindow* object);

/**
 * @brief Pass direction code 2 to the corner grid.
 * @param object Window-color corner selector.
 */
void func_00349850(ConfigCornerWindow* object);

/**
 * @brief Pass direction code 3 to the corner grid.
 * @param object Window-color corner selector.
 */
void func_00349890(ConfigCornerWindow* object);

/**
 * @brief Pass direction code 1 to the corner grid.
 * @param object Window-color corner selector.
 */
void func_003498D0(ConfigCornerWindow* object);

/**
 * @brief Pass direction code 0 to the corner grid.
 * @param object Window-color corner selector.
 */
void func_00349910(ConfigCornerWindow* object);

/**
 * @brief Open the color editor for the selected corner, placed beside that corner.
 * @param object Window-color corner selector.
 * @return One after the editor is registered, or zero when it cannot be allocated.
 */
u8 func_003499F0(ConfigCornerWindow* object);

/**
 * @brief Create the corner selector's panels, four corner labels, and two-by-two grid.
 * @param object Window-color corner selector.
 * @param associated Full resource source word.
 * @return One after creation, or zero when a panel, label, or the grid is absent.
 */
s32 func_00349C70(ConfigCornerWindow* object, u32 associated);

/**
 * @brief Pass direction code 1 to the binding grid.
 * @param object Button binding selector.
 */
void func_0034A430(ConfigBindingWindow* object);

/**
 * @brief Pass direction code 0 to the binding grid.
 * @param object Button binding selector.
 */
void func_0034A470(ConfigBindingWindow* object);

/**
 * @brief Create the button binding table: the current button names, the function rows, the headings, the grid, and the hint line.
 * @param object Button binding selector.
 * @param associated Full resource source word.
 * @return One after creation, or zero when the panel, a label, or the grid is absent.
 */
s32 func_0034A4B0(ConfigBindingWindow* object, u32 associated);

/**
 * @brief Create and register the preview, message, frame, and options windows.
 * @param object Configuration controller.
 * @return One after the windows are registered.
 */
s32 func_00352130(ConfigController* object);

/**
 * @brief Create the help bar: its labels, clipped scrolling text, and the first help message.
 * @param object Configuration help window.
 * @param associated Full resource source word; zero leaves the window empty.
 * @return One after creation, or zero when the source word or a display is missing.
 */
s32 func_00351820(ConfigMessageWindow* object, u32 associated);

/**
 * @brief Hold the help text for 120 frames, then scroll it left and wrap it; at each wrap the two alternating hints swap.
 * @param object Configuration help window.
 */
void func_003516B0(ConfigMessageWindow* object);

/**
 * @brief Move the option selection, refresh its message, and scroll the list between its two pages.
 * @param object Configuration options window to update.
 * @param direction Zero to move up, or one to move down.
 * @param amount Number of rows to move; only its low byte is used.
 */
void func_0034AEC0(ConfigOptions* object, u16 direction, s32 amount);

/**
 * @brief Dispatch the option control mask to the selected row.
 * @param object Configuration options window to update.
 * @param index Option row index.
 * @param bits Control bits passed to the row handler.
 */
void func_0034D180(ConfigOptions* object, u32 index, u16 bits);

/**
 * @brief Pick the button assignment row message from the current bindings.
 * @param object Configuration options window.
 * @return 0x1FBB when all eight buttons keep their defaults, otherwise 0x1FBC.
 */
s32 func_003501B0(ConfigOptions* object);

/**
 * @brief Resolve the message key that describes an option row's current setting.
 * @param object Configuration options window; rows 9 and 10 cache their keys in it.
 * @param selected Option row, 0 through 13.
 * @return Message key, or zero for rows out of range or unavailable.
 */
s32 func_00350270(ConfigOptions* object, u16 selected);

/**
 * @brief Release the nodes after the sentinel without destroying their payloads.
 * @param object List receiver containing the sentinel and node count.
 */
void func_00352860(ConfigList182210* object);

/**
 * @brief Release the nodes after the sentinel without destroying their payloads.
 * @param object List receiver containing the sentinel and node count.
 */
void func_00352B80(ConfigList182200* object);

/**
 * @brief Submit the configuration receiver to the resident object queue.
 * @param object Receiver to submit.
 */
void func_00352110(void* object);

/**
 * @brief Add to one color component, clamp it to 0..255, and copy the color to all four preview corners.
 * @param object Window-color editor.
 * @param index Component: 0 red, 1 green, 2 blue; other values only refresh the preview.
 * @param delta Amount added to the component.
 */
void func_00348E60(ConfigColorWindow* object, s16 index, s32 delta);

/**
 * @brief Increase the selected color component by five when the selector is active.
 * @param object Color controls to update.
 */
void func_00348FE0(ConfigColorWindow* object);

/**
 * @brief Increase the selected color component by one when the selector is active.
 * @param object Color controls to update.
 */
void func_00349030(ConfigColorWindow* object);

/**
 * @brief Decrease the selected color component by five when the selector is active.
 * @param object Color controls to update.
 */
void func_00349070(ConfigColorWindow* object);

/**
 * @brief Decrease the selected color component by one when the selector is active.
 * @param object Color controls to update.
 */
void func_003490C0(ConfigColorWindow* object);



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
void func_003520B0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003523F0(void* object);


/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003524B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003524C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003524D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003524E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003524F0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00352500(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00352550(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00352560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00352570(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00352580(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00352590(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003525A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003525B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003525C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003525D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003525E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003525F0(void* object);

/**
 * @brief Set the value at object offset 0xC.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00348400(void* object, u8 value);

/**
 * @brief Read the value at object offset 0xC.
 * @param object Object to read.
 * @return Value stored at offset 0xC.
 */
u8 func_00348410(void* object);

/**
 * @brief Set the value at object offset 0x8.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00348420(void* object, u8 value);

/**
 * @brief Read the value at object offset 0x8.
 * @param object Object to read.
 * @return Value stored at offset 0x8.
 */
u8 func_00348430(void* object);

/**
 * @brief Set the value at object offset 0xA.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00348440(void* object, u16 value);

/**
 * @brief Read the value at object offset 0xA.
 * @param object Object to read.
 * @return Value stored at offset 0xA.
 */
u16 func_00348450(void* object);

/**
 * @brief Set the value at object offset 0x9C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00348480(void* object, u32 value);

/**
 * @brief Read the value at object offset 0x9C.
 * @param object Object to read.
 * @return Value stored at offset 0x9C.
 */
u32 func_00348490(void* object);

/**
 * @brief Set the value at object offset 0x4.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_003484A0(void* object, u32 value);

/**
 * @brief Read the value at object offset 0x4.
 * @param object Object to read.
 * @return Value stored at offset 0x4.
 */
u32 func_003484B0(void* object);

/**
 * @brief Read the value at object offset 0x10.
 * @param object Object to read.
 * @return Value stored at offset 0x10.
 */
u32 func_003484C0(void* object);

/**
 * @brief Read the value at object offset 0xD.
 * @param object Object to read.
 * @return Value stored at offset 0xD.
 */
u8 func_003486B0(void* object);

/**
 * @brief Set the value at object offset 0xD.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_003486C0(void* object, u8 value);

/**
 * @brief Read the value at object offset 0x20.
 * @param object Object to read.
 * @return Value stored at offset 0x20.
 */
u32 func_003487B0(void* object);

/**
 * @brief Set the value at object offset 0x20.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_003488C0(void* object, u32 value);

/**
 * @brief Read the value at object offset 0x24.
 * @param object Object to read.
 * @return Value stored at offset 0x24.
 */
u32 func_0034A420(void* object);

/**
 * @brief Read the value at object offset 0x34.
 * @param object Object to read.
 * @return Value stored at offset 0x34.
 */
u32 func_0034D8A0(void* object);

/**
 * @brief Read the value at object offset 0x38.
 * @param object Object to read.
 * @return Value stored at offset 0x38.
 */
u8 func_00352510(void* object);

/**
 * @brief Set the value at object offset 0x24.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00352520(void* object, u32 value);

/**
 * @brief Set the value at object offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00352530(void* object, s8 value);

/**
 * @brief Read the value at object offset 0x28.
 * @param object Object to read.
 * @return Value stored at offset 0x28.
 */
s8 func_00352540(void* object);

/**
 * @brief Set a nested display value and flag.
 * @param object Holder of the display state.
 */
void func_003497F0(void* object);

/**
 * @brief Mark each icon active and color the selected one differently.
 * @param object Holder of the icon list.
 * @param selected Index of the icon to color differently.
 */
void func_003486E0(void* object, s16 selected);

/**
 * @brief Find a node by index in the linked list.
 * @param owner Holder of the list head.
 * @param index Zero-based index to find.
 * @return The node at index, or null if the list ends first.
 */
ConfigNode* func_00352690(ConfigListOwner* owner, s32 index);

/**
 * @brief Find a node by index in the linked list.
 * @param owner Holder of the list head.
 * @param index Zero-based index to find.
 * @return The node at index, or null if the list ends first.
 */
ConfigNode* func_003528E0(ConfigListOwner* owner, s32 index);

/**
 * @brief Find a node by index in the linked list.
 * @param owner Holder of the list head.
 * @param index Zero-based index to find.
 * @return The node at index, or null if the list ends first.
 */
ConfigNode* func_003529B0(ConfigListOwner* owner, s32 index);

/**
 * @brief Find a node by index in the linked list.
 * @param owner Holder of the list head.
 * @param index Zero-based index to find.
 * @return The node at index, or null if the list ends first.
 */
ConfigNode* func_00352C00(ConfigListOwner* owner, s32 index);









/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_00352600(ConfigListOwner* list, void* value);

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_003527D0(ConfigListOwner* list, void* value);

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_00352920(ConfigListOwner* list, void* value);

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_00352AF0(ConfigListOwner* list, void* value);

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_00352C40(ConfigListOwner* list, void* value);

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_00352CD0(ConfigListOwner* list, void* value);



/**
 * @brief Cancel the active configuration selector.
 * @param object Configuration selector window.
 * @return Callback result indicating that input was handled.
 */
s32 func_00348840(FieldClass15AE70* object);

/**
 * @brief Cancel the selector and refresh its parent window.
 * @param object Configuration selector window.
 * @return Callback result indicating that input was handled.
 */
s32 func_00349190(FieldClass15AE70* object);

/**
 * @brief Cancel the selector and refresh its parent window.
 * @param object Configuration selector window.
 * @return Callback result indicating that input was handled.
 */
s32 func_00349950(FieldClass15AE70* object);

/**
 * @brief Apply input to the active binding selector and refresh moved entries.
 * @param object Binding selector window.
 */
void func_0034A0E0(ConfigBindingWindow* object);

/**
 * @brief Swap the selected binding with the entry containing the supplied code.
 * @param object Binding selector window.
 * @param value Word containing the existing binding code to select.
 */
void func_0034A270(ConfigBindingWindow* object, u32 value);

/**
 * @brief Save the four binding codes and refresh the associated window.
 * @param object Binding selector window.
 */
void func_0034A300(ConfigBindingWindow* object);

/**
 * @brief Apply the selected configuration row or dismiss its window.
 * @param object Configuration grid window.
 * @return One when dismissed, or two when the selected row was handled.
 */
s32 func_003488D0(ConfigGridWindow* object);

/**
 * @brief Release the resource slot, detach the receiver, and invoke its release handler.
 * @param object Configuration callback receiver.
 */
void func_003520C0(ConfigControlReceiver* object);

/**
 * @brief Create and attach the configuration window's panel.
 * @param object Configuration panel window.
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 func_003514E0(ConfigFrameWindow* object, u32 associated);

/**
 * @brief Load a completed resource and finish configuration receiver setup.
 * @param object Configuration callback receiver.
 * @param buffer Completed resource buffer, or null.
 * @return Zero without a buffer, otherwise the receiver setup result.
 */
s32 func_00352330(ConfigControlReceiver* object, void* buffer);

/**
 * @brief Create and attach the configuration preview's resource widgets.
 * @param object Configuration preview window.
 * @param associated Full resource source word.
 * @return Always one after initialization.
 */
s32 func_00351C30(ConfigPreviewWindow* object, u32 associated);

/**
 * @brief Update the configuration preview origin, position, and scale from the saved display flag.
 * @param object Configuration controller holding the preview window.
 */
void func_00351FD0(ConfigController* object);

/**
 * @brief Update an in-range message key and the window's special message state.
 * @param object Configuration text window.
 * @param key Message key in the range 0x1FA4 through 0x1FC7.
 */
void func_00351610(ConfigMessageWindow* object, s32 key);

#ifdef __cplusplus
}
#endif

#endif
