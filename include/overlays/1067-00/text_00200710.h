#ifndef SO3_OVERLAYS_1067_00_TEXT_00200710_H
#define SO3_OVERLAYS_1067_00_TEXT_00200710_H

#include "types.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"

/** A word on the script stack, accessed as an integer or a float. */
union FieldScriptStackWord
{
    u32 word;
    float number;
};

/** Script context base containing the stack, variable registers and command flags. */
class FieldClass150DC0 : public FieldListObject
{
public:
    /** @brief Initialize the script base state. */
    FieldClass150DC0();

    /**
     * @brief Report this object's default list kind.
     * @return The class's default list kind.
     */
    virtual s32 get_default_list_kind();

    /** @brief Queue the script object for release. */
    virtual void func_001DD7B0();

    /** @brief Destroy the script state and its inherited node. */
    virtual ~FieldClass150DC0();

    /** @brief Return the context's fixed state value. @return Always one. */
    virtual s32 func_00201520();

    /** @brief Return the current context scale. @return Context scale. */
    virtual float func_00201530();

    float number;
    u32 instruction_index;
    s32 stack_depth;
    FieldScriptStackWord stack[256];
    u32 unk420;
    u32 unk424;
    u32 variables[32];
    float unk4a8[4];
    float unk4b8[4];
    u8 unk4c8_0 : 1;
    u8 unk4c8_1 : 1;
    u8 unk4c8_2_7 : 6;
};

struct FieldClass159010;
struct ResidentContextObject64;
struct FieldObjectSlotOwner;
struct FieldClass154E90;
struct FieldClass154CC0;
struct FieldClass1505F0;
struct FieldClass1522C0;
struct ResidentHeap;

/** Retained field resource containing script state, object lists and context attachments. */
class FieldClass150DB0
{
public:
    u32 unk00;
    FieldClass150DC0 script;
    u8 unk4d0[0x10];
    FieldClass1502A0 lists[6];
    u8 unk7b0[0xC4];
    s32 resource_index;
    void* context14;
    FieldClass14FE30* context04;
    ResidentHeap* context6c;
    FieldClass1522C0* context34;
    FieldClass1505F0* context3c;
    FieldClass154CC0* context4c;
    FieldClass154E90* context54;
    void* context58;

    /** Slot owner retained for reuse by the active field context. */
    FieldObjectSlotOwner* object_slots;

    ResidentContextObject64* context64;
    u32 unk8a0;
    void* context24;
    FieldClass159010* context68;
    void* context28;
    u32 unk8b0;
    ResidentHeap* context74;
    u8 unk8b8[0x38];

    virtual ~FieldClass150DB0();
};

#endif

#include "overlays/1067-00/text_001FF260.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Load the selected character and animation resources.
 * @param object Resource list to process.
 * @param character_key Key of character resources to process.
 * @param animation_key Key of animation resources to process.
 * @param mode Select synchronous loading when nonzero.
 * @return One when loading succeeds and the resident state permits it, otherwise zero.
 */
s32 func_002019C0(FieldResourceList14* object, s32 character_key, s32 animation_key, s32 mode);

/**
 * @brief Release the selected character and animation resources.
 * @param object Resource list to process.
 * @param character_key Key of character resources to process.
 * @param animation_key Key of animation resources to process.
 */
void func_00201870(FieldResourceList14* object, s32 character_key, s32 animation_key);

/**
 * @brief Decrement counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002016F0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Increment counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002017B0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Release the resource entry matching all three keys.
 * @param object Resource list to search.
 * @param first First key.
 * @param second Second key.
 * @param key Third key.
 */
void func_00201D70(FieldResourceList14* object, u32 first, u32 second, u32 key);

/**
 * @brief Find the size selected by a resource entry's flag.
 * @param object Resource list to search.
 * @param kind Resource kind to match.
 * @param key Resource key to match.
 * @return The selected size, or zero when no matching entry exists.
 */
u32 func_00201E20(FieldResourceList14* object, u32 kind, u32 key);

/**
 * @brief Find the data of a resource entry.
 * @param object Resource list to search.
 * @param kind Resource kind to match.
 * @param key Resource key to match.
 * @param mode Lookup option; zero in the known callers.
 * @return The entry's data, or null when no matching entry exists.
 */
void* func_00201EA0(FieldResourceList14* object, u32 kind, u32 key, s32 mode);

/**
 * @brief Detach an object and add it to the resident object queue.
 * @param object Object to detach and queue.
 */
void func_00201560(void* object);


#ifdef __cplusplus
}
#endif

#endif
