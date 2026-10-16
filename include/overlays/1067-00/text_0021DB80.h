#ifndef SO3_OVERLAYS_1067_00_TEXT_0021DB80_H
#define SO3_OVERLAYS_1067_00_TEXT_0021DB80_H

#include "types.h"

#ifdef __cplusplus
#include "overlays/1067-00/text_001ED7E0.h"
#include "overlays/lib/text_004BD360.h"

/** 0x94-byte field list with its secondary list base at offset 0x14. */
class FieldClass1522C0 : public FieldClass150070, public FieldClass1502A0
{
public:
    /** @brief Allocate through the Lib heap. @param size Allocation size. @return Allocated storage or null. */
    static void* operator new(u32 size);

    /** @brief Release storage through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object)
    {
        func_004DB570(object);
    }

    /** @brief Initialize the inherited node and list. */
    FieldClass1522C0()
    {
        unk90 = 0;
    }

    /** @brief Destroy both list bases. */
    virtual ~FieldClass1522C0();

    /** @brief Report the fixed list kind. @return Three. */
    virtual s32 func_001DF3D0();

    /** @brief Detach this node and queue it for release. */
    virtual void func_001DD7B0();

    /** @brief Advance the list's objects when their update conditions hold. */
    virtual void func_001DF360();

    u8 unk8c[4];

    void* unk90;
};

/** Scene-loader record whose native array stride is 32 bytes. */
class FieldClass152210 : public FieldClass1530C0
{
public:
    /** @brief Initialize the inherited resource-record state. */
    FieldClass152210();
    u8 unk1c[4];
};

/** Resource loader whose 0x3C word is initialized by its native constructor. */
class FieldClass152270 : public FieldClass150750
{
public:
    /** @brief Initialize the scene-resource loader. */
    FieldClass152270();
    /** @brief Release the scene-resource loader. */
    virtual ~FieldClass152270();
    /** @brief Report category2. @return Always2. */
    virtual s32 func_001DF3D0();
    /** @brief Advance the scene-resource state. @param flag Unused inherited argument. */
    virtual void func_001E0A50(s32 flag);
    /** @brief Submit the scene-resource request. */
    virtual void func_001F8CB0();
    /** @brief Advance the scene-resource request. */
    virtual void func_001F98E0();
    /** @brief Release the counted records and their scene-resource registration. */
    virtual void func_001F9050();
    u8 unk34[4];
    s32 unk38;
    void* unk3c;
};

/** Decoder state initialized by resident 0x105770 and consumed by 0x105680. */
struct ResidentDecodeState1C
{
    u32 unk00;
    s32 unk04;
    s32 remaining;
    u8* destination;
    u8* source;
    u8* end;
    u8 kind;
    u8 state;
};

/** 0x64-byte loader created by the script command at 0x1F2B00. */
class FieldClass152220 : public FieldClass152270
{
public:
    /** @brief Initialize the byte-buffer loader. */
    FieldClass152220()
    {
        unk14 = 0;
    }
    /** @brief Release the byte-buffer loader. */
    virtual ~FieldClass152220();
    /** @brief Handle the loader request. @param request Request value. */
    virtual void func_001E0A50(s32 request);
    u8* unk40;
    s32 unk44;
    ResidentDecodeState1C unk48;
};


extern "C" {
#else
typedef struct FieldClass152270 FieldClass152270;
#endif


/**
 * @brief Initialize the loader from the selected scene resource.
 * @param loader Resource loader.
 * @param key Signed scene-resource index.
 */
void func_0021F530(FieldClass152270* loader, s32 key);

typedef struct FieldScriptObject151D40 FieldScriptObject151D40;

/**
 * @brief Copy the current script word to the receiver at offset 0x18.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 0.
 */
s32 func_0021DE20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Copy the current script word only while the guard at 0x424 is set.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return 0 when the word was copied, otherwise 1.
 */
s32 func_0021DE40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Pop a float and two words from the receiver's script stack.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 0.
 */
s32 func_0021DE70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Convert the current unsigned script word to the receiver float at 0x14.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021DEF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_0021E840(void* object);

/**
 * @brief Copy the current script word to the resident halfword at 0xB0.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021E1C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Copy the current script word to the resident halfword at 0xA8.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021E1E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Copy the current script word to the resident halfword at 0xAA.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021E310(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Set or clear resident context bits using two script words.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021E160(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Set the receiver flag at 0x59D and its float at 0x14.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 0.
 */
s32 func_0021DF30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Clear the runtime section's first four packed-flag bytes.
 * @param object Script callback receiver; unused.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021DF60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Write the second script word to the indexed runtime flag selected by the first.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021DFB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Read an indexed runtime flag and apply it to the receiver word at 0x424.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021DFF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Find a node by key and invoke its release handler.
 * @param manager Node-list manager.
 * @param key Key to search.
 * @param unused Unused third argument.
 */
void func_0021F900(void* manager, u32 key, u32 unused);

#ifdef __cplusplus
}
#endif

#endif
