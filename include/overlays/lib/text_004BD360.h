#ifndef SO3_OVERLAYS_LIB_TEXT_004BD360_H
#define SO3_OVERLAYS_LIB_TEXT_004BD360_H

#include "types.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004CD3A0.h"

/** Opaque Lib text receiver using the main table D_178750. */
typedef struct LibObject178750 LibObject178750;

/** Partial widget receiver using the main table D_178630. */
typedef struct LibClass178630 LibClass178630;

/** Four packed panel colors used by the resident panel API. */
typedef struct LibWidgetColors4C5590
{
    u32 values[4];
} LibWidgetColors4C5590;
/** Container receiver with list and transform interfaces. */
typedef struct LibObject178660 LibObject178660;

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Configure a text slot and its rectangle.
 * @param object Text widget.
 * @param slot Slot index.
 * @param key Resource key.
 * @param flag Slot state flag.
 * @param x Origin x.
 * @param y Origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return Configuration status.
 */
s32 func_004C7FE0(LibObject178750* object, s32 slot, s32 key, u8 flag, float x, float y, float width, float height);
/**
 * @brief Set the text widget's source and resource key.
 * @param object Text widget.
 * @param source Opaque resource source.
 * @param key Resource key.
 * @param flag Resource state flag.
 */
void func_4C6DF0(LibObject178750* object, void* source, u32 key, u8 flag);
/**
 * @brief Attach a widget to the container.
 * @param object Container receiver.
 * @param child Widget to attach.
 */
void func_004C6190(LibObject178660* object, LibClass178600* child);
/**
 * @brief Detach the widget from its associated object.
 * @param object Widget receiver.
 */
void func_004C4A90(LibClass178630* object);

/**
 * @brief Configure the widget mode and rectangle.
 * @param object Widget receiver.
 * @param mode Widget mode.
 * @param x Origin x.
 * @param y Origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @param extra Additional widget component.
 * @return Configuration status.
 */
s32 func_004C5A80(LibClass178630* object, s32 mode, float x, float y, float width, float height, float extra);
/** @brief Set the four packed panel colors. @param object Panel widget. @param colors Four packed colors. */
void func_4C5590(LibClass178630* object, const LibWidgetColors4C5590* colors);
#ifdef __cplusplus
}
#endif

/** Four scalar float bounds returned from the receiver at offset 0xE8. */
typedef struct LibBounds4C69B0
{
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
} LibBounds4C69B0;

/**
 * @brief Set the text widget rectangle.
 * @param object Text widget.
 * @param x Origin x.
 * @param y Origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
#ifdef __cplusplus
extern "C"
#endif
void func_004C7FB0(LibObject178750* object, float x, float y, float width, float height);

#ifdef __cplusplus
/** Virtual intrusive-link root. */
class LibClass171E80
{
public:
    /** @brief Destroy the intrusive-link root. */
    virtual ~LibClass171E80()
    {
    }
};
/** Intrusive list sentinel initialized by the resident list constructor. */
class LibClass171E90 : public LibClass171E80
{
public:
    /** @brief Destroy the list sentinel and its virtual root. */
    virtual ~LibClass171E90()
    {
    }
    LibClass171E90* unk04;
    LibClass171E90* unk08;
};
/** Partial 0x20-byte list receiver with the actual virtual pointer at 0x10. */
class LibClass178A70
{
public:
    LibClass171E90 unk00;
    u32 unk0c;
    /** @brief Initialize the list receiver. */
    LibClass178A70();
    /** @brief Destroy the list receiver. */
    virtual ~LibClass178A70();
    /** @brief Link a node before the first listed node. @param node Node to append. */
    virtual void func_004CA020(void* node);
    /** @brief Link a node after the last listed node. @param node Node to append. */
    virtual void func_004C9FF0(void* node);
    /**
     * @brief Link a node after a list position.
     * @param position Insertion position.
     * @param node Node to insert.
     */
    virtual void func_004C9FC0(void* position, void* node);
    /** @brief Unlink a node and clear its list links. @param node Node to remove. */
    virtual void func_004C9F60(void* node);
    u8 unk14[0xC];
};

/** Partial secondary interface identified by MAIN vtable D_171FF0. */
class LibClass171FF0
{
public:
    /**
     * @brief Run the default DMA notification hook.
     * @param value Notification value.
     */
    virtual void func_003EFA90(u32 value);
    /**
     * @brief Prepare the receiver after a DMA notification.
     * @param value Notification word or packet address.
     */
    virtual void func_003F4410(u32 value);
};

/** Partial transform and secondary interface, constructed by func_0044B2D0. */
class LibClass174610 : public LibClass178A90, public LibClass171FF0
{
public:
    /** @brief Initialize the transform and callback interface. */
    LibClass174610();
    /** @brief Destroy the transform receiver. */
    virtual ~LibClass174610();
    /** @brief Queue the transform receiver for release. */
    virtual void func_003EF740();
    /**
     * @brief Dispatch the transform state flags.
     * @param matrix Unused matrix argument.
     * @param context Unused context argument.
     */
    virtual void func_003F4440(const void* matrix, void* context);
    /**
     * @brief Run the default transform state hook.
     * @param first First state value.
     * @param second Second state value.
     * @param third Third state value.
     */
    virtual void func_0044B100(u32 first, u32 second, u32 third);
    /**
     * @brief Set the transform codes and its third coordinate.
     * @param code Transform code.
     * @param first First byte value.
     * @param second Word value.
     * @param third Second byte value.
     * @param z Third coordinate.
     */
    void func_0044B110(s32 code, u8 first, u32 second, u8 third, float z);
    u8 unk94[0x16];
    u8 unkaa;
    u8 unkab;
    u8 unkac;
    u8 unkad;
    u8 unkae;
    u8 unkaf;
};

/** Managed three-word DMA storage, initialized by clearing its allocation. */
class LibStorageBlock0C
{
public:
    /** @brief Clear the owned allocation. */
    LibStorageBlock0C()
    {
        allocation = 0;
    }
    /** @brief Release the owned allocation. */
    ~LibStorageBlock0C();
    void* allocation;
    void* aligned;
    u32 dma_address;
};

class LibObject178660;
/**
 * @brief Configure the container transform and modes.
 * @param object Container receiver.
 * @param first First mode value.
 * @param second Second mode value.
 * @param third Third mode value.
 * @param x First transform component.
 * @param y Second transform component.
 * @param z Third transform component.
 * @return Configuration status.
 */
extern "C" s32 func_004C6510(LibObject178660* object, s32 first, s32 second, s32 third, float x, float y, float z);

/** 0xF0-byte container, with a list base and a secondary transform base. */
class LibObject178660 : public LibClass178A70, public LibClass174610
{
public:
    /** @brief Initialize the container transform state. */
    LibObject178660()
    {
        unk6c = 0x6FF1;
    }
    /**
     * @brief Initialize the container with its default mode and supplied transform.
     * @param x First transform component.
     * @param y Second transform component.
     * @param z Third transform component.
     */
    LibObject178660(float x, float y, float z)
    {
        unk6c = 0x6FF1;
        func_004C6510(this, 5, 0, 0, x, y, z);
    }
    /** @brief Destroy the container. */
    virtual ~LibObject178660();
    /**
     * @brief Update the container and its widgets.
     * @param first First update flag.
     * @param second Second update flag.
     * @param third Third update flag.
     */
    virtual void func_0044B100(u32 first, u32 second, u32 third);
    /** @brief Prepare the container storage. */
    virtual void func_003EEBE0();
    /** @brief Prepare the container transform. @param value Notification value. */
    virtual void func_003F4410(u32 value);
    /**
     * @brief Run the default container state hook.
     * @param first First update flag.
     * @param second Second update flag.
     * @param third Third update flag.
     */
    virtual void func_00412C40(u32 first, u32 second, u32 third);
    LibStorageBlock0C unkD0;
    u8 unkDC[0x14];
};

/** Partial 0x114-byte text widget, with MAIN vtable D_178750. */
struct LibObject178750 : public LibClass174EF0
{
    /** @brief Initialize the text widget with an empty rectangle. */
    LibObject178750()
    {
        unk38 = 11;
        func_004C7FB0(this, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    /** @brief Destroy the text widget. */
    virtual ~LibObject178750();
    /**
     * @brief Configure a text slot and its rectangle.
     * @param x Origin x.
     * @param y Origin y.
     * @param width Rectangle width.
     * @param height Rectangle height.
     * @param slot Slot index.
     * @param key Resource key.
     * @param flag Slot state flag.
     * @return Configuration status.
     */
    s32 func_004C7FE0(float x, float y, float width, float height, s32 slot, s32 key, u8 flag);
    u8 unkfc[0x18];
};


/** 0x90-byte widget, constructed inline over LibClass178600. */
struct LibClass178630 : public LibClass178600
{
    /** @brief Initialize widget state and select kind 1. */
    LibClass178630()
    {
        unk5c = 0;
        unk58 = 0;
        unk54 = 0;
        unk50 = 0;
        unk38 = 1;
        unk60 = 0;
    }
    /**
     * @brief Initialize widget state and drawing dimensions.
     * @param mode Drawing mode.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param width Drawing width.
     * @param height Drawing height.
     * @param extra Extra drawing coordinate.
     */
    LibClass178630(s32 mode, float x, float y, float width, float height, float extra)
    {
        unk5c = 0;
        unk58 = 0;
        unk54 = 0;
        unk50 = 0;
        unk38 = 1;
        func_004C5A80(this, mode, x, y, width, height, extra);
    }
    /** @brief Destroy the widget. */
    virtual ~LibClass178630()
    {
        func_004C4A90(this);
    }
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    u32 unk50;
    u32 unk54;
    u32 unk58;
    u32 unk5c;
    void* unk60;
    u8 unk64[0x2C];
};

/** Partial Lib keyframe channel interface, with root vtable D_173180 and known derived table D_1782E0. */
class LibClass173180
{
public:
    /**
     * @brief Destroy the channel.
     */
    virtual ~LibClass173180();
    /**
     * @brief Allocate channel entries.
     * @param count Entry count.
     */
    virtual void func_004C1560(s32 count) = 0;
    /**
     * @brief Use external channel entries.
     * @param count Entry count.
     * @param entries External entries.
     */
    virtual void func_004C2770(s32 count, void* entries) = 0;
    /**
     * @brief Store the low mode nibble.
     * @param mode Mode value.
     */
    virtual void func_004C1600(s32 mode) = 0;
    /**
     * @brief Store the high mode nibble.
     * @param mode Mode value.
     */
    virtual void func_004C1660(s32 mode) = 0;
    /**
     * @brief Read the channel word at offset 0x10.
     * @return Stored word.
     */
    virtual u32 func_004BD490() = 0;
    /**
     * @brief Default append handler.
     * @param value Channel value.
     * @param optional1 Optional second component.
     * @param optional2 Optional third component.
     * @param key Sort value.
     * @return Status.
     */
    virtual s32 func_0042A7C0(const void* value, const void* optional1, const void* optional2, float key);
    /**
     * @brief Slot 0x24 is an empty default handler; its argument contract remains unresolved.
     */
    virtual void func_00429850(...);
    /**
     * @brief Default set handler.
     * @param index Entry index.
     * @param key Sort value.
     * @param value Channel value.
     * @return Status.
     */
    virtual s32 func_0042A7D0(s32 index, float key, const void* value);
    /**
     * @brief Default insert handler.
     * @param index Entry index.
     * @param key Sort value.
     * @param value Channel value.
     * @return Status.
     */
    virtual s32 func_0042A7E0(s32 index, float key, const void* value);
    /**
     * @brief Read one channel entry.
     * @param index Entry index.
     * @param key Receives the sort value.
     * @param value Receives the channel value.
     * @return Status.
     */
    virtual s32 func_0042A7F0(s32 index, float* key, void* value);
    /**
     * @brief Default add handler.
     * @param value Channel value.
     * @param key Sort value.
     */
    virtual void func_0042A800(const void* value, float key);
    /**
     * @brief Perform no work.
     */
    virtual void func_0042A810();
    /**
     * @brief Test whether an entry has the requested key.
     * @param key Sort value.
     * @return One when present, otherwise zero.
     */
    virtual s32 func_004C2620(float key) = 0;
    /**
     * @brief Write a channel value.
     * @param output Receives a value whose width depends on the channel.
     */
    virtual void func_004C4500(void* output) = 0;
    /**
     * @brief Wrap a key into the channel range.
     * @param key Sort value.
     * @return Wrapped key.
     */
    virtual float func_004C24E0(float key) = 0;
    /**
     * @brief Write a channel value.
     * @param output Receives a value whose width depends on the channel.
     */
    virtual void func_004C4510(void* output) = 0;
    /**
     * @brief Read the channel key span.
     * @return Difference between last and first key.
     */
    virtual float func_004C25D0() = 0;
    /**
     * @brief Evaluate the channel.
     * @param key Sort value.
     * @param output Receives the channel value.
     */
    virtual void func_004C16F0(float key, void* output) = 0;
    /** @brief Read the channel state. @return Stored state. */
    virtual s16 func_004C16C0() = 0;
    /** @brief Delete the channel through its virtual destructor. */
    virtual void func_0042A820();
    /** @brief Read the current channel entry. @return Entry pointer. */
    virtual void* func_004C1720() = 0;
    /** @brief Reset the channel state. */
    virtual void func_004C14D0() = 0;
    /** @brief Read the channel entry count. @return Entry count. */
    virtual s16 func_004C16D0() = 0;
};

/** 20-byte animation entry with a channel, target word and state name. */
struct LibAnimationEntry14
{
    s16 unk00;
    u8 unk02;
    u8 unk03;
    LibClass173180* unk04;
    void* unk08;
    u8 unk0c[4];
    const char* unk10;
};

/**
 * Partial 0x70-byte Lib animation object, with vtable D_178220 in main data.
 * It holds a data block at offset 0x30 (owned unless the byte at 0x68 is set)
 * and an array at offset 0x40.
 */
class LibClass178220 : public LibClass171EA0
{
public:
    /** @brief Construct an empty object. */
    LibClass178220();

    u8 unk04[0x2C];
    void* unk30;
    u8 unk34[4];
    s32 unk38;
    u8 unk3c[4];
    LibAnimationEntry14* unk40;
    u8 unk44[0xC];
    LibAnimationEntry14* unk50;
    u8 unk54[0x10];
    float unk64;
    u8 unk68;
    u8 unk69;
    u8 unk6a;
    u8 unk6b[3];
    u8 unk6e;
    u8 unk6f;
};

/** Partial 0xD0-byte Lib object, with vtable D_178370 in main data. */
class LibClass178370 : public LibClass171EF0
{
public:
    /** @brief Construct an empty object. */
    LibClass178370();

    /**
     * @brief Store the three scalar components of the vector state.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void func_003EF790(float x, float y, float z);

    /**
     * @brief Store a vector and update the vector state delta.
     * @param value New vector.
     */
    virtual void func_003EF780(const LibVector4* value);

    LibVector4 unk60;
    LibVector4 unk70;
    LibVector4 unk80;
    LibVector4 unk90;
    LibVector4 unka0;
    LibVector4 unkb0;
    u8 unkc0;
    u8 unkc1;
    u8 unkc2;
    u8 unkc3[0xD];
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
/**
 * @brief Find an animation channel by key and kind.
 * @param object Animation object.
 * @param key Entry key.
 * @param kind Entry kind.
 * @param flags Low flag bits to match.
 * @return Matching channel, or null.
 */
LibClass173180* func_004BDAA0(LibClass178220* object, u32 key, u8 kind, u8 flags);

/**
 * @brief Prepare a transition between animation objects.
 * @param object Destination animation.
 * @param target Bound target.
 * @param previous Previous animation.
 * @param duration Transition duration.
 * @return Destination frame selected by the transition.
 */
float func_004BDE00(LibClass178220* object, void* target, LibClass178220* previous, float duration);

/**
 * @brief Bind the animation object to a target.
 * @param object Animation object.
 * @param target Target object.
 * @param optional Optional object passed to the binder.
 * @return Binding status.
 */
s32 func_004BF100(LibClass178220* object, void* target, void* optional);

/**
 * @brief Bind a named animation state.
 * @param object Animation object.
 * @param target Vector state.
 * @param name State name.
 */
void func_004BDB50(LibClass178220* object, LibClass178370* target, const char* name);

/**
 * @brief Normalize the vector state delta in place.
 * @param object Vector state.
 */
void func_004C2CD0(LibClass178370* object);

/**
 * @brief Look up an indexed animation channel and cache its entry.
 * @param object Animation object.
 * @param index Entry index.
 * @param nibble Entry option nibble.
 * @return Channel, or null when no entry matches.
 */
LibClass173180* func_004BDA30(LibClass178220* object, s32 index, u8 nibble);

/**
 * @brief Replace an animation entry's channel and descriptor.
 * @param object Animation object.
 * @param index Entry index.
 * @param channel Replacement channel.
 * @param kind Entry kind.
 * @param type Entry type.
 * @param flags Entry flags.
 */
void func_004BD9D0(LibClass178220* object, s32 index, LibClass173180* channel, u8 kind, s16 type, u8 flags);
#endif

/**
 * @brief Rebuild the receiver's data and return its scalar bounds.
 * @param object Lib text receiver to rebuild.
 * @return Bounds at offset 0xE8, or null when rebuilding fails.
 */
LibBounds4C69B0* func_004C69B0(LibObject178750* object);

/**
 * @brief Release the data a LibClass178220 builds from its block at offset 0x40.
 * @param object Object to update.
 */
void func_004BDD10(void* object);

/**
 * @brief Bind a LibClass178220 to a second object.
 * @param object Object to update.
 * @param target Object to bind; FieldClass150EB0 passes its object at offset 0x7C.
 * @return Binding status.
 */
s32 func_004BFE10(void* object, void* target);

/**
 * @brief Evaluate a VU0 polynomial approximation of a trigonometric function.
 *
 * Inferred to be the cosine: Field's ring builder uses it for the height of a
 * point measured from the pole.
 * @param angle Angle in radians.
 * @return The approximated value.
 */
float func_004CC3E0(float angle);

/** @brief Evaluate the VU0 sine approximation. @param angle Angle in radians. @return Approximated sine. */
float func_004CC5B0(float angle);

/**
 * @brief Evaluate a VU0 polynomial approximation of a trigonometric function.
 *
 * Inferred to be the sine, the partner of func_004CC3E0.
 * @param angle Angle in radians.
 * @return The approximated value.
 */
float func_004CC690(float angle);

#ifdef __cplusplus
}
#endif

#endif
