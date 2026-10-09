#ifndef SO3_OVERLAYS_1067_00_TEXT_0022B490_H
#define SO3_OVERLAYS_1067_00_TEXT_0022B490_H

#include "types.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_001E6C50.h"
#include "sdk/main/libc_guess_0013A4C0.h"

/** Command retaining a byte setting, a float and the current context mode. */
class FieldClass152C90 : public FieldClass150440
{
public:
    /** @brief Initialize the actor setting command. @param setting Byte setting to apply. @param value Scalar passed to the actor. */
    FieldClass152C90(u8 setting, float value);
    /** @brief Destroy the command node. */
    virtual ~FieldClass152C90();
    /** @brief Apply the actor setting when ready. @return One on completion, zero while waiting. */
    virtual s32 func_0022D800();
    u8 unk1c;
    u8 unk1d[3];
    float unk20;
    u8 unk24_0 : 1;
    u8 unk24_1_7 : 7;
};

/** Queued command copying a 16-byte resource key and one enable bit. */
class FieldClass1526C0 : public FieldClass150440
{
public:
    /**
     * @brief Copy the resource key and initialize the setting.
     * @param enable Setting to apply.
     * @param words Resource key bytes.
     */
    FieldClass1526C0(bool enable, const u32* words)
    {
        unk18 = 0x100EC;
        unk2d_0 = enable;
        func_0013A4C0(unk1c, words, sizeof(unk1c));
        unk2c = 0;
    }
    /** @brief Destroy the command. */
    virtual ~FieldClass1526C0();
    /** @brief Apply the resource setting. @return Whether the command completed. */
    virtual s32 func_0022B850();
    u8 unk1c[16];
    u8 unk2c;
    u8 unk2d_0 : 1;
    u8 unk2d_1_7 : 7;
};

/** Queued command storing a word for the selected target. */
class FieldClass152770 : public FieldClass150440
{
public:
    /** @brief Store the target word. @param value Word to apply. */
    FieldClass152770(u32 value)
    {
        unk18 = 0x100E1;
        unk1c = value;
    }
    /** @brief Destroy the command. */
    virtual ~FieldClass152770();
    /** @brief Apply the stored word. @return Always one. */
    virtual s32 func_0022B8F0();
    u32 unk1c;
};

/** Queued command storing a float for the selected target. */
class FieldClass152790 : public FieldClass150440
{
public:
    /** @brief Store the target float. @param value Float to apply. */
    FieldClass152790(float value)
    {
        unk18 = 0x100E0;
        unk1c = value;
    }
    /** @brief Destroy the command. */
    virtual ~FieldClass152790();
    /** @brief Apply the stored float. @return Always one. */
    virtual s32 func_0022B920();
    float unk1c;
};

#endif

struct FieldCallback22BEC0;
struct FieldCallback22B8F0;
struct FieldCallback22B920;
struct FieldCallback22BC30;
struct FieldCallback22BC90;
struct FieldCallback22BCE0;
struct FieldCallback22BDD0;
struct FieldCallback22BDF0;
struct FieldCallback22D4A0;
struct FieldObject22B790;
struct FieldObject22B740;
struct FieldCallback22C9E0;
struct FieldCallback22CA10;
struct FieldCallback22C7D0;
struct FieldCallback22C860;
struct FieldFlagCallback22D110;
struct FieldCallback22D150;
struct FieldCallback22D180;
struct FieldCallback22D680;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Detach the object and add it to the resident object queue.
 * @param object Object to detach and queue.
 */
void func_0022B550(void* object);

/**
 * @brief Forward a callback word to the attached target.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022B8F0(struct FieldCallback22B8F0* object);

/**
 * @brief Forward a callback float to the attached target.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022B920(struct FieldCallback22B920* object);

/**
 * @brief Forward the callback word to the attached entry selector.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022B990(struct FieldCallback22B8F0* object);

/**
 * @brief Create the object attached to the callback target.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022BE10(struct FieldCallback22B8F0* object);

/**
 * @brief Forward the callback word to the attached selector.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022BC30(struct FieldCallback22BC30* object);

/**
 * @brief Copy the callback value into an attached node and update its child if below the limit.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022BC90(struct FieldCallback22BC90* object);

/**
 * @brief Forward five callback floats when an attached node exists.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022BCE0(struct FieldCallback22BCE0* object);

/**
 * @brief Apply the callback values to the selected resident entry.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022BEC0(struct FieldCallback22BEC0* object);

/**
 * @brief Apply a callback word to the selected resident entry.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022BF00(struct FieldCallback22BEC0* object);

/**
 * @brief Store the callback value at target offset 0x580.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022BDD0(struct FieldCallback22BDD0* object);

/**
 * @brief Store the callback value at target offset 0x57C.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022BDF0(struct FieldCallback22BDF0* object);

/**
 * @brief Store the callback value at target offset 0x1FC.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022D4A0(struct FieldCallback22D4A0* object);

/**
 * @brief Reset the receiver fields and store two bytes and two floats.
 * @param object Receiver to initialize.
 * @param first Byte stored at +0x1C.
 * @param second Byte stored at +0x1D and optionally +0x1E.
 * @param x Float stored at +0x20.
 * @param y Float stored at +0x28.
 */
void func_0022B740(struct FieldObject22B740* object, u8 first, u8 second, float x, float y);

/**
 * @brief Clear three receiver bytes and four receiver words.
 * @param object Receiver to reset.
 */
void func_0022B790(struct FieldObject22B790* object);

/**
 * @brief Forward the callback float and duration to the attached state.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022C860(struct FieldCallback22C860* object);

/**
 * @brief Apply the selected field state, or set a fallback value when it fails.
 * @param object Callback receiver.
 * @return 1 on success; otherwise 0.
 */
s32 func_0022C7D0(struct FieldCallback22C7D0* object);

/**
 * @brief Set the handle value when target flag 0x100 is set.
 * @param object Callback receiver.
 * @return Zero when set; otherwise 1.
 */
s32 func_0022D110(struct FieldFlagCallback22D110* object);

/**
 * @brief Set the handle value when target flag 0x400 is set.
 * @param object Callback receiver.
 * @return Zero when set; otherwise 1.
 */
s32 func_0022CF90(struct FieldFlagCallback22D110* object);

/**
 * @brief Forward three callback floats to the attached target.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022D150(struct FieldCallback22D150* object);

/**
 * @brief Copy a callback byte to an attached child, or set the handle fallback value.
 * @param object Callback receiver.
 * @return 1 when the child exists; otherwise 0.
 */
s32 func_0022D680(struct FieldCallback22D680* object);

/**
 * @brief Forward packed callback options and three floats to an attached node.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022CA10(struct FieldCallback22CA10* object);

/**
 * @brief Apply a field-context entry using the callback word.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022D180(struct FieldCallback22D180* object);

/**
 * @brief Check the selected field-context entry and set a fallback float if active.
 * @param object Callback receiver.
 * @return Zero when active; otherwise 1.
 */
s32 func_0022D1C0(struct FieldCallback22D180* object);

/**
 * @brief Apply a field-context entry using the callback word in an alternate mode.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022D230(struct FieldCallback22D180* object);

/**
 * @brief Store a selected target value, using its current value for -1.
 * @param object Callback receiver.
 * @return Always 1.
 */
s32 func_0022C9E0(struct FieldCallback22C9E0* object);

#ifdef __cplusplus
}
/** Partial FieldClass150440 command with vtable D_1527B0 in main data. */
class FieldClass1527B0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass1527B0();
};

/** Partial FieldClass150440 command with vtable D_1527D0 in main data. */
class FieldClass1527D0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass1527D0();
};

/** Partial FieldClass150440 command with vtable D_152810 in main data. */
class FieldClass152810 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152810();
};

/** Partial FieldClass150440 command with vtable D_152830 in main data. */
class FieldClass152830 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152830();
};

/** Partial FieldClass150440 command with vtable D_152850 in main data. */
class FieldClass152850 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152850();
};

/** Partial FieldClass150440 command with vtable D_152870 in main data. */
class FieldClass152870 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152870();
};

/** Partial FieldClass150440 command with vtable D_152890 in main data. */
class FieldClass152890 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152890();
};

/** Partial FieldClass150440 command with vtable D_1528B0 in main data. */
class FieldClass1528B0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass1528B0();
};

/** Partial FieldClass150440 command with vtable D_1528D0 in main data. */
class FieldClass1528D0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass1528D0();
};

/** Partial FieldClass150440 command with vtable D_1528F0 in main data. */
class FieldClass1528F0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass1528F0();
};

/** Partial FieldClass150440 command with vtable D_152910 in main data. */
class FieldClass152910 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152910();
};

/** Partial FieldClass150440 command with vtable D_152930 in main data. */
class FieldClass152930 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152930();
};

/** Partial FieldClass150440 command with vtable D_152950 in main data. */
class FieldClass152950 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152950();
};

/** Partial FieldClass150440 command with vtable D_152970 in main data. */
class FieldClass152970 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152970();
};

/** Partial FieldClass150440 command with vtable D_152990 in main data. */
class FieldClass152990 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152990();
};

/** Partial FieldClass150440 command with vtable D_1529B0 in main data. */
class FieldClass1529B0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass1529B0();
};

/** Partial FieldClass150440 command with vtable D_1529D0 in main data. */
class FieldClass1529D0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass1529D0();
};

/** Partial FieldClass150440 command with vtable D_1529F0 in main data. */
class FieldClass1529F0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass1529F0();
};

/** Partial FieldClass150440 command with vtable D_152A10 in main data. */
class FieldClass152A10 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152A10();
};

/** Partial FieldClass150440 command with vtable D_152A30 in main data. */
class FieldClass152A30 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152A30();
};

/** Partial FieldClass150440 command with vtable D_152A50 in main data. */
class FieldClass152A50 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152A50();
};

/** Partial FieldClass150440 command with vtable D_152A70 in main data. */
class FieldClass152A70 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152A70();
};

/** Partial FieldClass150440 command with vtable D_152A90 in main data. */
class FieldClass152A90 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152A90();
};

/** Partial FieldClass150440 command with vtable D_152AB0 in main data. */
class FieldClass152AB0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152AB0();
};

/** Partial FieldClass150440 command with vtable D_152AD0 in main data. */
class FieldClass152AD0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152AD0();
};

/** Partial FieldClass150440 command with vtable D_152AF0 in main data. */
class FieldClass152AF0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152AF0();
};

/** Partial FieldClass150440 command with vtable D_152B10 in main data. */
class FieldClass152B10 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152B10();
};

/** Partial FieldClass150440 command with vtable D_152B30 in main data. */
class FieldClass152B30 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152B30();
};

/** Partial FieldClass150440 command with vtable D_152B50 in main data. */
class FieldClass152B50 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152B50();
};

/** Partial FieldClass150440 command with vtable D_152B70 in main data. */
class FieldClass152B70 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152B70();
};

/** Partial FieldClass150440 command with vtable D_152B90 in main data. */
class FieldClass152B90 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152B90();
};

/** Partial FieldClass150440 command with vtable D_152BB0 in main data. */
class FieldClass152BB0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152BB0();
};

/** Partial FieldClass150440 command with vtable D_152BD0 in main data. */
class FieldClass152BD0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152BD0();
};

/** Partial FieldClass150440 command with vtable D_152BF0 in main data. */
class FieldClass152BF0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152BF0();
};

/** Partial FieldClass150440 command with vtable D_152C10 in main data. */
class FieldClass152C10 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152C10();
};

/** Partial FieldClass150440 command with vtable D_152C30 in main data. */
class FieldClass152C30 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152C30();
};

/** Partial FieldClass150440 command with vtable D_152C50 in main data. */
class FieldClass152C50 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152C50();
};

/** Partial FieldClass150440 command with vtable D_152CB0 in main data. */
class FieldClass152CB0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152CB0();
};

/** Partial FieldClass150440 command with vtable D_152CD0 in main data. */
class FieldClass152CD0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152CD0();
};

/** Partial FieldClass150440 command with vtable D_152CF0 in main data. */
class FieldClass152CF0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152CF0();
};

/** Partial FieldClass150440 command with vtable D_152D10 in main data. */
class FieldClass152D10 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152D10();
};

/** Partial FieldClass150440 command with vtable D_152D30 in main data. */
class FieldClass152D30 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152D30();
};

/** Partial FieldClass150440 command with vtable D_152D50 in main data. */
class FieldClass152D50 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152D50();
};

/** Partial FieldClass150440 command with vtable D_152D70 in main data. */
class FieldClass152D70 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152D70();
};

/** Partial FieldClass150440 command with vtable D_152D90 in main data. */
class FieldClass152D90 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152D90();
};

/** Partial FieldClass150440 command with vtable D_152DB0 in main data. */
class FieldClass152DB0 : public FieldClass150440
{
public:
    /** @brief Destroy the command. */
    virtual ~FieldClass152DB0();
};

#endif

#endif
