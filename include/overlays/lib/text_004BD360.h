#ifndef SO3_OVERLAYS_LIB_TEXT_004BD360_H
#define SO3_OVERLAYS_LIB_TEXT_004BD360_H

#include "types.h"
#include "overlays/lib/animation_binding.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/counted_list.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/vector.h"

typedef struct N54Owner84_004BD360 N54Owner84_004BD360;

/** Opaque Lib text receiver using the main table D_178750. */
typedef struct LibTextWidget LibTextWidget;

struct ResidentResourceHeader;



/** Partial widget receiver using the main table D_178630. */
typedef struct LibPanel LibPanel;

/** Four packed panel colors used by the resident panel API. */
typedef struct LibWidgetColors4C5590
{
    u32 values[4];
} LibWidgetColors4C5590;
/** Container receiver with list and transform interfaces. */
typedef struct LibContainer LibContainer;

#ifdef __cplusplus
extern "C" {
void* func_004C9930(void* receiver);
#endif
/** @brief Store a float in an indexed array slot. @param values Float array. @param index Slot index. @param value Value to store. */
void func_004BD3C0(float* values, s32 index, float value);

/**
 * @brief Copy a vector into the receiver's field at offset 0x10.
 * @param object Receiver to update.
 * @param value Source vector.
 */
void func_004BD360(void* object, const unsigned __int128* value);

/**
 * @brief Copy a vector to the destination and return the destination.
 * @param object Destination vector.
 * @param value Source vector.
 * @return The destination vector.
 */
void* func_004BD4C0(void* object, const unsigned __int128* value);

/**
 * @brief Set the byte at +0x64 to zero and the byte at +0x62 to one.
 * @param object Receiver to update.
 */
void func_004C8530(void* object);

/**
 * @brief Copy a vector into the receiver's field at offset 0x850.
 * @param object Receiver to update.
 * @param value Source vector.
 */
void func_004C94D0(void* object, const unsigned __int128* value);
/** Native panel table stored in MAIN; its contents remain opaque here. */
extern u8 D_178630[];
/** Native text-widget table stored in MAIN; its contents remain opaque here. */
extern u8 D_178750[];

/**
 * @brief Initialize the widget base rectangle and state bytes, and install its native table.
 * @param object Storage for the 0x40-byte widget base.
 * @return The constructed base.
 */
LibWidget* func_004C4960(LibWidget* object);

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
s32 lib_text_init_resource_rectangle(LibTextWidget* object, s32 slot, s32 key, u8 flag, float x, float y, float width, float height);
/**
 * @brief Set the text widget's source and resource key.
 * @param object Text widget.
 * @param slot Resource slot, as returned by lib_load_resource_slot.
 * @param key Resource key.
 * @param flag Resource state flag.
 */
void lib_text_set_resource(LibTextWidget* object, s32 slot, u32 key, u8 flag);
/**
 * @brief Attach a widget to the container.
 * @param object Container receiver.
 * @param child Widget to attach.
 */
void lib_container_attach_widget(LibContainer* object, LibWidget* child);
/**
 * @brief Detach the widget from its associated object.
 * @param object Widget receiver.
 */
void lib_panel_detach(LibPanel* object);

/**
 * @brief Allocate and initialize the panel transform, then set its third component.
 * @param object Panel widget.
 * @param z Third transform component.
 * @return One on successful setup, otherwise zero.
 */
s32 lib_panel_init_transform(LibPanel* object, float z);

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
s32 lib_panel_init_rectangle(LibPanel* object, s32 mode, float x, float y, float width, float height, float extra);
/** @brief Set the four packed panel colors. @param object Panel widget. @param colors Four packed colors. */
void lib_panel_set_colors(LibPanel* object, const LibWidgetColors4C5590* colors);
/** Return the fixed integer value 11. */
s32 func_004C8370(void* object);

/** Return the fixed integer value 1. */
s32 func_004C8380(void* object);

/** Return the fixed integer value 67. */
s32 func_004C96D0(void* object);

/** Return the fixed value 0. */
s32 func_004C3AC0(void* object);

/** Return the fixed value 0. */
s32 func_004C3AD0(void* object);

/** Return the fixed value 0. */
s32 func_004C8360(void* object);

#ifdef __cplusplus
}
#endif


/**
 * @brief Initialize the text widget rectangle and clear its allocation and pending flag.
 * @param object Text widget.
 * @param x Origin x.
 * @param y Origin y.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
#ifdef __cplusplus
extern "C"
#endif
void lib_text_init_rectangle(LibTextWidget* object, float x, float y, float width, float height);

#ifdef __cplusplus
/** Local perspective volume used by visibility tests. */
struct LibProjectionVolume
{
    /** @brief Recompute the derived perspective-volume coefficients. */
    void update_coefficients();

    FieldVec4A origin;
    FieldVec4A x_axis;
    FieldVec4A y_axis;
    FieldVec4A z_axis;
    float near_half_width;
    float near_half_height;
    float near_distance;
    float far_distance;
    float far_near_ratio;
    float unk54;
    float unk58;
};

/** Partial transform and secondary interface, constructed by func_0044B2D0. */
class LibCallbackTransform : public LibClass172000, public LibDmaCallbacks
{
public:
    /** @brief Initialize the transform and callback interface. */
    LibCallbackTransform();
    /** @brief Destroy the transform receiver. */
    virtual ~LibCallbackTransform();
    /** @brief Copy the stored transform state byte into the active state. */
    virtual void set_default_draw_bucket();
    /** @brief Queue the transform receiver for release. */
    virtual void destroy();
    /**
     * @brief Dispatch the transform state flags.
     * @param matrix Unused matrix argument.
     * @param context Unused context argument.
     */
    virtual void build_packet(const void* matrix, void* context);
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
     * @param z Third coordinate.
     * @param second Word value.
     * @param third Second byte value.
     */
    void set_codes_and_z(s32 code, u32 first, float z, u32 second, u32 third);
    void* unk94;
    u8 unk98[8];
    s32 unka0;
    u32 unka4;
    u8 unka8;
    u8 unka9;
    u8 unkaa;
    u8 unkab;
    u8 unkac;
    u8 unkad;

    /** Set when the position or codes change; the packet builder rebuilds the geometry and clears it. */
    u8 geometry_dirty;

    u8 unkaf;
};

/** Shape a morph target blends toward, with the weight range it may use. */
struct LibMorphShape
{
    /** Shape number, such as a mouth shape or zero for closed eyes. */
    s32 id;

    u8 unk04[0x14];
    float min_weight;
    float max_weight;
};

/** Morph target, one of a face model's children; object_kind is two for a morph target. */
struct LibMorphTarget : public LibListObject
{
    u8 unk14[4];

    /** Set while the target has a nonzero weight. */
    u8 active;

    u8 unk19[0x17];
    LibMorphShape* shape;
    u8 unk34[0xC];

    /** Weight clamped to the shape's range. */
    float clamped_weight;

    u8 unk44[0xC];

    /** Weight last asked for. */
    float weight;

    /** Frames left before an idle target is dropped. */
    s32 idle_frames;
};

extern "C"
{
    /**
     * @brief Set a morph target's weight, clamped to its shape's range, and mark its owner when it becomes active.
     * @param target Morph target.
     * @param weight New weight.
     */
    void lib_morph_target_set_weight(LibMorphTarget* target, float weight);
}

/** Selection cursor: a callback transform with a movement state that slides it between positions; vtable D_175070. */
class LibSelectionCursor : public LibCallbackTransform, public LibMovementState
{
public:
    /** @brief Initialize the cursor transform. */
    LibSelectionCursor()
    {
        type_id = 0x6FF0;
    }

    /** @brief Destroy the cursor. */
    virtual ~LibSelectionCursor();

    /**
     * @brief Finish the cursor's drawing packet.
     * @param value Notification word.
     */
    virtual void on_packet_complete(u32 value);

    /**
     * @brief Reset the translation, set the drawing codes and depth, and place the cursor.
     * @param code Drawing code.
     * @param first First drawing value.
     * @param second Second drawing value.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param z Depth.
     */
    void init(s32 code, u32 first, u32 second, float x, float y, float z);
};

class LibContainer;
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
/**
 * @brief Allocate container drawing storage and initialize its transform.
 * @param object Container receiver.
 * @param code Transform code.
 * @param first First byte value.
 * @param second Word value.
 * @param x First coordinate.
 * @param y Second coordinate.
 * @param z Third coordinate.
 * @return One on success, or zero if storage cannot be allocated.
 */
extern "C" s32 lib_container_init(LibContainer* object, s32 code, float x, float y, s32 first, float z, s32 second);

/** 0xF0-byte container, with a list base and a secondary transform base. */
class LibContainer : public LibListReceiver, public LibCallbackTransform
{
public:
    /** @brief Initialize the container transform state. */
    LibContainer()
    {
        type_id = 0x6FF1;
    }
    /**
     * @brief Initialize the container with its default mode and supplied transform.
     * @param x First transform component.
     * @param y Second transform component.
     * @param z Third transform component.
     */
    LibContainer(float x, float y, float z)
    {
        type_id = 0x6FF1;
        lib_container_init(this, 5, x, y, 0, z, 0);
    }

    /**
     * @brief Initialize the container with its mode and transform.
     * @param code Container mode.
     * @param x Transform x.
     * @param y Transform y.
     * @param z Transform z.
     */
    LibContainer(s32 code, float x, float y, float z)
    {
        type_id = 0x6FF1;
        lib_container_init(this, code, x, y, 0, z, 0);
    }
    /** @brief Destroy the container. */
    virtual ~LibContainer();
    /**
     * @brief Update the container and its widgets.
     * @param first First update flag.
     * @param second Second update flag.
     * @param third Third update flag.
     */
    virtual void func_0044B100(u32 first, u32 second, u32 third);
    /** @brief Prepare the container storage. */
    virtual void render();
    /** @brief Prepare the container transform. @param value Notification value. */
    virtual void on_packet_complete(u32 value);
    /**
     * @brief Run the default container state hook.
     * @param first First update flag.
     * @param second Second update flag.
     * @param third Third update flag.
     */
    virtual void func_00412C40(u32 first, u32 second, u32 third);
    LibStorageBlock0C unkD0;
    u8 unkDC[4];
    float unkE0;
    u8 unkE4[0xC];
};

/** Partial 0x114-byte text widget, with MAIN vtable D_178750. */
struct LibTextWidget : public LibDrawWidget
{
    /** @brief Initialize the text widget with an empty rectangle. */
    LibTextWidget()
    {
        unk38 = 11;
        lib_text_init_rectangle(this, 0.0f, 0.0f, 0.0f, 0.0f);
    }

    /**
     * @brief Initialize the text widget with a resource string and rectangle.
     * @param slot Resource slot.
     * @param key String key.
     * @param flag Text flag.
     * @param x Left edge.
     * @param y Top edge.
     * @param width Width.
     * @param height Height.
     */
    LibTextWidget(s32 slot, s32 key, u8 flag, float x, float y, float width, float height)
    {
        unk38 = 11;
        lib_text_init_resource_rectangle(this, slot, key, flag, x, y, width, height);
    }
    /** @brief Destroy the text widget. */
    virtual ~LibTextWidget();
    /** @brief Refresh the text widget drawing state. */
    virtual void func_00413D20();
    /** @brief Draw the text widget. */
    virtual void draw();
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
    s32 init_resource_rectangle(float x, float y, float width, float height, s32 slot, u32 key, u8 flag);
    LibListObject* unkfc;
    u8 unk100[0x14];
};

/** 0x57C-byte multiline text widget with trailing scroll state. */
struct LibObject174D90 : public LibTextWidget
{
    /** @brief Initialize the multiline text widget with an empty rectangle. */
    LibObject174D90()
    {
        unk38 = 12;
        lib_multiline_text_init_rectangle(this, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    /** @brief Release the multiline allocation and destroy the text widget. */
    virtual ~LibObject174D90();
    /** @brief Advance and refresh the multiline text state. */
    virtual void func_00413D20();
    /** @brief Draw the multiline text widget. */
    virtual void draw();

    /** @brief Hook run when the text restarts; the base implementation does nothing. */
    virtual void func_0045F600();

    /** @brief Hook run at the end of the text; the base implementation does nothing. */
    virtual void func_0045F610();

    /**
     * @brief Hook for a text control code with three values; the base implementation does nothing.
     * @param first First value.
     * @param second Second value.
     * @param third Third value.
     */
    virtual void func_0045F620(s16 first, s16 second, u32 third);

    /**
     * @brief Hook for a text control code with one value; the base implementation does nothing.
     * @param value Control value.
     */
    virtual void func_0045F630(u32 value);

    /**
     * @brief Hook for a text control code with one value; the base implementation does nothing.
     * @param value Control value.
     */
    virtual void func_0045F640(u32 value);

    /** @brief Hook for a text control code; the base implementation does nothing. */
    virtual void func_0045F650();

    /**
     * @brief Configure the multiline text resource, rectangle, and drawing mode.
     * @param x Rectangle origin x.
     * @param y Rectangle origin y.
     * @param width Rectangle width.
     * @param height Rectangle height.
     * @param slot Resource slot index.
     * @param key Resource key.
     * @param mode Drawing mode mask.
     * @param flag Flag whose low byte is stored by the widget.
     * @return One on successful setup, otherwise zero.
     */
    s32 init_multiline_resource_rectangle(float x, float y, float width, float height, s32 slot, s32 key, u32 mode, u32 flag);
    u8 unk114[0x410];
    float unk524;
    float unk528;
    float unk52c;
    u8 unk530[0x34];
    s32 unk564;
    u8 unk568[0x12];
    u8 unk57a;
    u8 unk57b;

    /**
     * @brief Run func_00451B90 on the object at offset 0x564 when the byte at 0x57A is set.
     * @return The func_00451B90 result, or zero.
     */
    s32 func_0045F660();
};

/** 0x90-byte widget, constructed inline over LibWidget. */
struct LibPanel : public LibWidget
{
    /** @brief Initialize widget state and select kind 1. */
    LibPanel()
    {
        unk50.unk0c = 0.0f;
        unk50.unk08 = 0.0f;
        unk50.unk04 = 0.0f;
        unk50.unk00 = 0.0f;
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
    LibPanel(s32 mode, float x, float y, float width, float height, float extra)
    {
        unk50.unk0c = 0.0f;
        unk50.unk08 = 0.0f;
        unk50.unk04 = 0.0f;
        unk50.unk00 = 0.0f;
        unk38 = 1;
        lib_panel_init_rectangle(this, mode, x, y, width, height, extra);
    }
    /** @brief Destroy the widget. */
    virtual ~LibPanel()
    {
        lib_panel_detach(this);
    }
    /** @brief Refresh the panel drawing state. */
    virtual void func_00413D20();
    /** @brief Draw the panel. */
    virtual void draw();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
    LibUiRect16 unk50;
    void* unk60;
    u8 unk64[0x28];
    u8 unk8c;
    u8 unk8d[3];
};

/** How a track evaluates keys outside its first and last keyframes. */
enum
{
    /** Keep the first or last value outside the key span. */
    LIB_TRACK_END_HOLD = 0,

    /** Wrap the key into the stored span. */
    LIB_TRACK_END_CYCLE = 1,

    /** Use the first value at the last segment's endpoint. */
    LIB_TRACK_END_CYCLE_TO_FIRST = 2,

    /** Reflect the key on odd cycles. */
    LIB_TRACK_END_PING_PONG = 3,

    /** Continue evaluating the first or last segment outside the span. */
    LIB_TRACK_END_EXTEND_SEGMENT = 4,

    /** Wrap the key and add the endpoint difference for each cycle. */
    LIB_TRACK_END_OFFSET_CYCLE = 5,

    /** Interpolate from the stored single key before the first array key. */
    LIB_TRACK_END_USE_PRE_START_KEY = 6
};

/** Bookkeeping every track keeps after its key storage: counts, the cached lookup and how it extends past its ends. */
struct LibTrackState
{
    /** Whole key spans the last wrapped key was past the first key; negative before it. */
    s32 cycle_count;

    /** Last key minus first key. */
    float span;

    s16 key_count;
    s16 key_capacity;

    /** Lower key index the last search found; the next search starts there. */
    s16 search_index;

    /** Lower key index the cached segment was built from; -1 after the keys change. */
    s16 segment_lower;

    /** Upper key index the cached segment was built from; -1 after the keys change. */
    s16 segment_upper;

    /** LIB_TRACK_END_* mode applied before the first key. */
    u8 before_mode : 4;

    /** LIB_TRACK_END_* mode applied after the last key. */
    u8 after_mode : 4;

    /** Set when either end extends its first or last keyframe segment. */
    u8 extends_segment : 1;

    /** Set when the keys are bound from outside, so the track doesn't free them. */
    u8 external_keys : 1;

    /** Set while the track belongs to a pool. */
    u8 pooled : 1;

    u8 unk_3_7 : 5;
};

/**
 * Root of Lib's keyframe tracks, with vtable D_173180 in main data. Unlike Boot's copy, the root declares the whole
 * interface, so the float, vector and curve families share it; values travel as untyped pointers.
 */
class LibClass173180
{
public:
    /** @brief Destroy the track. */
    virtual ~LibClass173180()
    {
    }

    /**
     * @brief Allocate storage for the requested keyframe count.
     * @param count Requested keyframe count.
     */
    virtual void allocate_keys(s32 count) = 0;

    /**
     * @brief Bind an external keyframe array.
     * @param count Keyframe count.
     * @param keys External keyframe storage.
     */
    virtual void bind_keys(s32 count, void* keys) = 0;

    /**
     * @brief Set what the track does before its first key.
     * @param mode LibTrackEndMode.
     */
    virtual void set_before_mode(u32 mode) = 0;

    /**
     * @brief Set what the track does after its last key.
     * @param mode LibTrackEndMode.
     */
    virtual void set_after_mode(u32 mode) = 0;

    /**
     * @brief Return how many key spans the last wrapped key was past the first key.
     * @return Signed cycle count.
     */
    virtual s32 get_cycle_count() const = 0;

    /**
     * @brief Append a keyframe; the root ignores it.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent, for curve tracks.
     * @param out_tangent Outgoing tangent, for curve tracks.
     * @param key Sort key.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);

    /**
     * @brief Append a keyframe from an unpacked record; the root ignores it.
     * @param record Keyframe record in the track's own layout.
     */
    virtual void append_key_record(const void* record);

    /**
     * @brief Replace an indexed keyframe; the root ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent, for curve tracks.
     * @param out_tangent Outgoing tangent, for curve tracks.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);

    /**
     * @brief Insert a keyframe at an index; the root ignores it.
     * @param index Keyframe index.
     * @param key Sort key.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent, for curve tracks.
     * @param out_tangent Outgoing tangent, for curve tracks.
     * @return Nonzero when the keyframe was stored.
     */
    virtual s32 insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);

    /**
     * @brief Read an indexed keyframe; the root has none.
     * @param index Keyframe index.
     * @param key Receives the sort key.
     * @param value Receives the value.
     * @param first Receives the first auxiliary value.
     * @param second Receives the second auxiliary value.
     * @return Nonzero when the keyframe is available.
     */
    virtual s32 read_key(s32 index, float* key, void* value, void* first, void* second) const;

    /**
     * @brief Store a single keyframe that applies before the key array; the root ignores it.
     * @param value Keyframe value.
     * @param in_tangent Incoming tangent, for curve tracks.
     * @param out_tangent Outgoing tangent, for curve tracks.
     * @param key Sort key.
     */
    virtual void set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key);

    /** @brief Forget the cached sample; the root has none. */
    virtual void reset_keys();

    /**
     * @brief Test whether the track has a keyframe at a key.
     * @param key Key to find.
     * @return Nonzero when the key exists.
     */
    virtual s32 has_key(float key) const = 0;

    /**
     * @brief Write the difference between the last and first key values.
     * @param output Receives the difference.
     */
    virtual void get_end_delta(void* output) const = 0;

    /**
     * @brief Wrap a key into the stored key range.
     * @param key Key to wrap.
     * @return Wrapped key.
     */
    virtual float wrap_key(float key) const = 0;

    /**
     * @brief Write how fast the value changed at the last sample, per second.
     * @param output Receives the rate.
     */
    virtual void get_value_rate(void* output) const = 0;

    /**
     * @brief Return the span between the first and last keys.
     * @return Key span, or zero when fewer than two keys are stored.
     */
    virtual float get_key_span() const = 0;

    /**
     * @brief Evaluate the track at a key.
     * @param key Evaluation key.
     * @param output Receives the value.
     */
    virtual void evaluate(float key, void* output) = 0;

    /**
     * @brief Return the stored keyframe count.
     * @return Keyframe count.
     */
    virtual s16 get_key_count() const = 0;

    /** @brief Delete the track through its virtual destructor; pooled tracks return to their pool instead. */
    virtual void release();

    /**
     * @brief Return the key storage.
     * @return Key array, or null.
     */
    virtual void* get_keys() = 0;

    /** @brief Clear the key storage, counts, modes and cached indices. */
    virtual void reset_state() = 0;

    /**
     * @brief Return the number of keys the storage can hold.
     * @return Key capacity.
     */
    virtual s16 get_key_capacity() = 0;
};

/** 8-byte key of LibWordTrackBase: a key position followed by a word that holds until the next key. */
struct LibWordTrackKey
{
    /**
     * @brief Copy the key and value.
     * @param other Key to copy.
     * @return This key.
     */
    LibWordTrackKey& operator=(const LibWordTrackKey& other)
    {
        key = other.key;
        value = other.value;
        return *this;
    }

    float key;
    u32 value;
};

/** Key storage and bookkeeping for tracks of 32-bit words (vtable D_1782E0 in main data); keys aren't stored at this level. */
class LibWordTrackBase : public LibClass173180
{
public:
    /** @brief Construct the track. */
    LibWordTrackBase();

    /** @brief Release the key storage. */
    virtual ~LibWordTrackBase();

    virtual void allocate_keys(s32 count);
    virtual void bind_keys(s32 count, void* keys);
    virtual void set_before_mode(u32 mode);
    virtual void set_after_mode(u32 mode);
    virtual s32 get_cycle_count() const;
    virtual s32 append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual void set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 has_key(float key) const;
    virtual float wrap_key(float key) const;
    virtual float get_key_span() const;
    virtual void evaluate(float key, void* output);
    virtual s16 get_key_count() const;
    virtual void* get_keys();
    virtual void reset_state();
    virtual s16 get_key_capacity();

    /**
     * @brief Append a key; the base ignores it.
     * @param value Key value.
     * @param in_tangent Unused incoming tangent.
     * @param out_tangent Unused outgoing tangent.
     * @param key Key position.
     * @return Nonzero when the key was stored.
     */
    virtual s32 on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);

    /**
     * @brief Replace an indexed key; the base ignores it.
     * @param index Key index.
     * @param key Key position.
     * @param value Key value.
     * @return Nonzero when the key was stored.
     */
    virtual s32 on_replace_key(s32 index, float key, const void* value);

    /**
     * @brief Insert a key before an index; the base ignores it.
     * @param index Key index.
     * @param key Key position.
     * @param value Key value.
     * @return Nonzero when the key was stored.
     */
    virtual s32 on_insert_key(s32 index, float key, const void* value);

    /**
     * @brief Store the single key; the base ignores it.
     * @param value Key value.
     * @param key Key position.
     */
    virtual void on_set_single_key(const void* value, float key);

    /**
     * @brief Return the value the track settles on.
     * @return Zero in the base.
     */
    virtual u32 get_last_value();

    /**
     * @brief Return the value of the key at a position.
     * @param key Key position.
     * @return Key value, or zero when no key is there.
     */
    virtual u32 find_key_value(float key);

    /**
     * @brief Sample the track.
     * @param key Key position.
     * @return Track value.
     */
    virtual u32 sample(float key) = 0;

    /** @brief Delete the key storage unless it is external, and clear the key pointer. */
    void free_keys();

    /**
     * @brief Wrap a key across the span and store its signed cycle count.
     * @param key Key position.
     * @return Wrapped key, reflected on odd ping-pong cycles.
     */
    float update_cycle_count(float key);

    /**
     * @brief Find the keys around a position, starting from the cached search index.
     * @param key Key position.
     * @param lower Receives the lower key index.
     * @param upper Receives the upper key index.
     * @return One when an end mode extends the first or last segment, otherwise zero.
     */
    u8 find_surrounding_keys(float key, s32* lower, s32* upper);

    LibWordTrackKey* key_array;

    /** Single key, used before key storage exists. */
    LibWordTrackKey single_key;

    LibTrackState state;
};

/** Word track that stores its keys in the array (vtable D_178250 in main data). */
class LibWordKeyTrack : public LibWordTrackBase
{
public:
    /** @brief Destroy the track. */
    virtual ~LibWordKeyTrack()
    {
    }

    virtual s32 read_key(s32 index, float* key, void* value, void* first, void* second) const;
    virtual s32 on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 on_replace_key(s32 index, float key, const void* value);
    virtual s32 on_insert_key(s32 index, float key, const void* value);
    virtual void on_set_single_key(const void* value, float key);
};

/** 0x24-byte word track that holds each key's value until the next key (vtable D_178570 in main data). */
class LibWordTrack : public LibWordKeyTrack
{
public:
    /** @brief Destroy the track. */
    virtual ~LibWordTrack();

    virtual void get_end_delta(void* output) const;
    virtual void get_value_rate(void* output) const;
    virtual u32 get_last_value();
    virtual u32 sample(float key);
};

/** Second word-track base with the same layout and code as LibWordTrackBase (vtable D_1784E0 in main data). */
class LibClass1784E0 : public LibClass173180
{
public:
    /** @brief Construct the track. */
    LibClass1784E0();

    /** @brief Release the key storage. */
    virtual ~LibClass1784E0();

    virtual void allocate_keys(s32 count);
    virtual void bind_keys(s32 count, void* keys);
    virtual void set_before_mode(u32 mode);
    virtual void set_after_mode(u32 mode);
    virtual s32 get_cycle_count() const;
    virtual s32 append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual s32 insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent);
    virtual void set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 has_key(float key) const;
    virtual float wrap_key(float key) const;
    virtual float get_key_span() const;
    virtual void evaluate(float key, void* output);
    virtual s16 get_key_count() const;
    virtual void* get_keys();
    virtual void reset_state();
    virtual s16 get_key_capacity();

    /**
     * @brief Append a key; the base ignores it.
     * @param value Key value.
     * @param in_tangent Unused incoming tangent.
     * @param out_tangent Unused outgoing tangent.
     * @param key Key position.
     * @return Nonzero when the key was stored.
     */
    virtual s32 on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);

    /**
     * @brief Replace an indexed key; the base ignores it.
     * @param index Key index.
     * @param key Key position.
     * @param value Key value.
     * @return Nonzero when the key was stored.
     */
    virtual s32 on_replace_key(s32 index, float key, const void* value);

    /**
     * @brief Insert a key before an index; the base ignores it.
     * @param index Key index.
     * @param key Key position.
     * @param value Key value.
     * @return Nonzero when the key was stored.
     */
    virtual s32 on_insert_key(s32 index, float key, const void* value);

    /**
     * @brief Store the single key; the base ignores it.
     * @param value Key value.
     * @param key Key position.
     */
    virtual void on_set_single_key(const void* value, float key);

    /**
     * @brief Return the value the track settles on.
     * @return Zero in the base.
     */
    virtual u32 get_last_value();

    /**
     * @brief Return the value of the key at a position.
     * @param key Key position.
     * @return Key value, or zero when no key is there.
     */
    virtual u32 find_key_value(float key);

    /**
     * @brief Sample the track.
     * @param key Key position.
     * @return Track value.
     */
    virtual u32 sample(float key) = 0;

    /** @brief Delete the key storage unless it is external, and clear the key pointer. */
    void free_keys();

    /**
     * @brief Wrap a key across the span and store its signed cycle count.
     * @param key Key position.
     * @return Wrapped key, reflected on odd ping-pong cycles.
     */
    float update_cycle_count(float key);

    /**
     * @brief Find the keys around a position, starting from the cached search index.
     * @param key Key position.
     * @param lower Receives the lower key index.
     * @param upper Receives the upper key index.
     * @return One when an end mode extends the first or last segment, otherwise zero.
     */
    u8 find_surrounding_keys(float key, s32* lower, s32* upper);

    LibWordTrackKey* key_array;

    /** Single key, used before key storage exists. */
    LibWordTrackKey single_key;

    LibTrackState state;
};

/** LibClass1784E0 that stores its keys in the array (vtable D_178450 in main data). */
class LibClass178450 : public LibClass1784E0
{
public:
    /** @brief Destroy the track. */
    virtual ~LibClass178450()
    {
    }

    virtual s32 read_key(s32 index, float* key, void* value, void* first, void* second) const;
    virtual s32 on_append_key(const void* value, const void* in_tangent, const void* out_tangent, float key);
    virtual s32 on_replace_key(s32 index, float key, const void* value);
    virtual s32 on_insert_key(s32 index, float key, const void* value);
    virtual void on_set_single_key(const void* value, float key);
};

/** 0x2C-byte LibClass178450 whose sample is always zero (vtable D_1783C0 in main data). */
class LibClass1783C0 : public LibClass178450
{
public:
    /** @brief Construct the track with both trailing words cleared. */
    LibClass1783C0();

    /** @brief Destroy the track. */
    virtual ~LibClass1783C0();

    virtual void get_end_delta(void* output) const;
    virtual void get_value_rate(void* output) const;
    virtual u32 get_last_value();
    virtual u32 sample(float key);

    u32 unk24;
    u32 unk28;
};

/** 20-byte animation entry with a channel, target word and state name. */
struct LibAnimationEntry14
{
    s16 type;
    u8 kind;
    u8 flags;
    LibClass173180* channel;
    void* target;
    u8 unk0c[4];
    const char* state_name;
};

class LibAnimation;
extern "C" void lib_animation_release_channels(LibAnimation* object);

/**
 * Partial 0x70-byte Lib animation object, with vtable D_178220 in main data.
 * It holds a data block at offset 0x30 (owned unless the byte at 0x68 is set)
 * and an array at offset 0x40.
 */
class LibAnimation : public LibListObject
{
public:
    /** @brief Construct an empty object. */
    LibAnimation();

    /** @brief Detach the animation, free its resource when owned and release its channels and bindings. */
    virtual ~LibAnimation();

    /** @brief Apply the frame the animation follows, once a frame has elapsed. */
    virtual void update();

    /**
     * @brief Mark or clear the skip flag of every populated entry bound to a target.
     * @param target Bound target to match.
     * @param skip Nonzero to skip the target's entries, zero to apply them again.
     */
    void set_target_skipped(const void* target, s32 skip);

    /** @brief Stop following a frame and leave the update list. */
    void stop();

    /**
     * @brief Follow a frame and join an update list.
     * @param list Update list to join.
     * @param frame Frame to apply on each update.
     */
    void play(LibUpdateList* list, float* frame);

    /**
     * @brief Release the current channels and resource, then play from borrowed data.
     * @param data Animation data the caller keeps.
     */
    void set_resource(void* data)
    {
        if (entries)
        {
            lib_animation_release_channels(this);
            delete[] entries;
        }
        targets_bound = 0;
        if (!resource_is_borrowed)
        {
            operator delete(resource_data);
        }
        resource_is_borrowed = 1;
        resource_data = data;
    }


    u8 unk14[0x1C];
    void* resource_data;
    u8 unk34[4];
    s32 entry_count;
    u8 unk3c[4];
    LibAnimationEntry14* entries;

    /** Frame applied by update(), or null when the animation isn't playing. */
    float* frame;

    u32 unk48;
    u8 unk4c[4];
    LibAnimationEntry14* cached_entry;
    u8 unk54[4];
    LibAnimationBindingOwner* primary_binding_owner;
    LibAnimationBindingOwner* secondary_binding_owner;

    /** Compared with each entry's target; the frame is truncated to a whole number when they match. */
    void* unk60;

    float unk64;
    u8 resource_is_borrowed;

    /** Set while the animation is in an update list. */
    u8 playing;

    /** Set once a frame has been applied; cleared to restart, which applies the restart-only entries again. */
    u8 started;

    u8 unk6b;

    /** Whether the last update applied a nonzero status. */
    u8 unk6c;

    u8 unk6d;
    u8 targets_bound;
    u8 unk6f;
};

/** 0xD0-byte transform that animation channels drive, with vtable D_178370 in main data. It keeps how far each part moved at its last update. */
class LibAnimationTarget : public LibOrientedTransform
{
public:
    /** @brief Construct an empty object. */
    LibAnimationTarget();

    /** @brief Destroy the target. */
    virtual ~LibAnimationTarget();

    /**
     * @brief Set the position, w of one, and keep its change from the previous position.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_translation(float x, float y, float z);

    /**
     * @brief Copy the position and keep its change from the previous position.
     * @param value New position.
     */
    virtual void set_translation_vector(const LibVector4* value);

    /**
     * @brief Copy the position and keep its change from the previous position.
     * @param value New position.
     */
    virtual void copy_translation(const LibVector4* value);

    /**
     * @brief Copy the rotation and keep the rotation from the previous one.
     * @param value New rotation quaternion.
     */
    virtual void set_orientation(const LibVector4* value);

    /**
     * @brief Copy the rotation and keep the rotation from the previous one.
     * @param value New rotation quaternion.
     */
    virtual void copy_orientation(const LibVector4* value);

    /**
     * @brief Set the rotation and keep the rotation from the previous one.
     * @param x First quaternion component.
     * @param y Second quaternion component.
     * @param z Third quaternion component.
     * @param w Fourth quaternion component.
     */
    virtual void set_orientation_components(float x, float y, float z, float w);

    /**
     * @brief Set the scale's xyz and keep its change from the previous scale.
     * @param x First component.
     * @param y Second component.
     * @param z Third component.
     */
    virtual void set_scale(float x, float y, float z);

    /**
     * @brief Copy the scale and keep its change from the previous scale.
     * @param value New scale.
     */
    virtual void set_scale_vector(const LibVector4* value);

    /**
     * @brief Copy the scale and keep its change from the previous scale.
     * @param value New scale.
     */
    virtual void copy_scale(const LibVector4* value);

    /** Position change at the last update, once a position has been set. */
    FieldVec4B translation_delta;

    /** Rotation from the previous rotation to the current one, once a rotation has been set. */
    FieldVec4B orientation_delta;

    /** Scale change at the last update, once a scale has been set. */
    FieldVec4B scale_delta;

    /** Translation read from the target's translation channels by lib_animation_read_channel_pose. */
    FieldVec4B channel_translation;

    /** Rotation quaternion read from the target's rotation channels. */
    FieldVec4B channel_rotation;

    /** Scale read from the target's scale channels. */
    FieldVec4B channel_scale;

    /** Set once a position has been set, so later updates keep a change. */
    u8 has_translation;

    /** Set once a rotation has been set. */
    u8 has_orientation;

    /** Set once a scale has been set. */
    u8 has_scale;

    u8 unkc3[0xD];
};

// Some units include this header inside an extern "C" block, where these overloads wouldn't be allowed.
extern "C++"
{
/**
 * @brief Copy a vector into a FieldVec4B as one 128-bit value, like copy_vector does for LibVector4.
 * @param destination Vector receiving the copy.
 * @param source Vector to copy.
 */
static inline void copy_vector(FieldVec4B* destination, const LibVector4* source)
{
    *(unsigned __int128*)destination = *(const unsigned __int128*)source;
}

/**
 * @brief Copy a FieldVec4B into a vector as one 128-bit value.
 * @param destination Vector receiving the copy.
 * @param source Vector to copy.
 */
static inline void copy_vector(LibVector4* destination, const FieldVec4B* source)
{
    *(unsigned __int128*)destination = *(const unsigned __int128*)source;
}

/**
 * @brief Zero all four components of a FieldVec4B with one 128-bit store.
 * @param vector Vector to clear.
 */
static inline void clear_vector(FieldVec4B* vector)
{
    *(unsigned __int128*)vector = 0;
}
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
/**
 * @brief Extract quaternion components from a rotation matrix.
 * @param output Destination quaternion.
 * @param input Source matrix.
 */
void lib_matrix_to_quaternion(FieldVec4B* output, const LibMatrix44Value* input);

/**
 * @brief Build a matrix at a position that looks along a direction.
 * @param output Destination matrix.
 * @param position Eye position.
 * @param direction Direction to face.
 * @param roll Roll angle in radians.
 */
void lib_matrix_look_at(LibMatrix44Value* output, const FieldVec4B* position, const FieldVec4B* direction, float roll);

/**
 * @brief Evaluate the native three-angle trigonometric approximation and retain its result in VU0 vf13.
 * @param output Aligned destination for the result, inferred to contain sine values in x, y, and z.
 * @param x First angle in radians.
 * @param y Second angle in radians.
 * @param z Third angle in radians.
 */
void func_004CA090(FieldVec4A* output, float x, float y, float z);

/**
 * @brief Start the native three-angle trigonometric approximation, leaving its result in VU0 vf13.
 *
 * The caller must wait for VU0 before consuming the result.
 * @param x First angle in radians.
 * @param y Second angle in radians.
 * @param z Third angle in radians.
 */
void func_004CD2C0(float x, float y, float z);

/**
 * @brief Evaluate the clamped arc-cosine approximation.
 * @param value Cosine argument.
 * @return Approximated angle in radians.
 */
float func_004CD010(float value);

/**
 * @brief Compute the VU0 sine and cosine approximations for an angle.
 * @param output Aligned vector receiving cosine in z and sine in w; x and y retain shared polynomial coefficients.
 * @param angle Angle in radians.
 */
void lib_compute_sine_cosine_pair(LibVector4* output, float angle);

/**
 * @brief Compute degree-nine VU0 sine and cosine approximations.
 * @param output Aligned vector receiving cosine in z and sine in w; x and y retain shared polynomial coefficients.
 * @param angle Angle in radians.
 */
void lib_compute_sine_cosine_pair_degree9(LibVector4* output, float angle);


/**
 * @brief Extract a quaternion after mapping each matrix row from (x, y, z) to (x, -z, y).
 * @param source Source matrix.
 * @param output Destination quaternion.
 */
void func_004CCCF0(const LibMatrix44Value* source, FieldVec4B* output);

/**
 * @brief Evaluate the degree-six Taylor polynomial for exp(value).
 * @param value Polynomial argument.
 * @return Polynomial approximation to exp(value).
 */
float func_004CCD90(float value);

/** Entry kinds of a target's pose channels; the axis kinds keep one component per channel. */
enum
{
    LIB_ANIMATION_KIND_TRANSLATION = 0,
    LIB_ANIMATION_KIND_ROTATION = 1,
    LIB_ANIMATION_KIND_SCALE = 2,
    LIB_ANIMATION_KIND_TRANSLATION_AXIS = 3,
    LIB_ANIMATION_KIND_ROTATION_AXIS = 4,
    LIB_ANIMATION_KIND_SCALE_AXIS = 5
};

enum
{
    LIB_ANIMATION_AXIS_COUNT = 3,

    /** Entry flag: lib_animation_apply_frame leaves the entry alone. */
    LIB_ANIMATION_ENTRY_SKIP = 0x10,

    /** Low nibble of an entry's flags: the axis of a per-axis channel, zero for a whole vector. */
    LIB_ANIMATION_ENTRY_AXIS_MASK = 0xF
};

/**
 * @brief Find the channel bound to a target with the requested kind and axis, and cache its entry.
 * @param object Animation object.
 * @param target Bound target to match.
 * @param kind Entry kind.
 * @param axis Axis to match against the entry flags' low nibble.
 * @return Matching channel, or null.
 */
static inline LibClass173180* lib_animation_find_channel_inline(LibAnimation* object, const void* target, u8 kind, u8 axis)
{
    if (!object->entries)
    {
        return 0;
    }

    s32 count = object->entry_count;

    for (s32 i = 0; i < count; i++)
    {
        if (object->entries[i].channel && object->entries[i].target == target && kind == object->entries[i].kind &&
            axis == (object->entries[i].flags & LIB_ANIMATION_ENTRY_AXIS_MASK))
        {
            object->cached_entry = &object->entries[i];
            return object->cached_entry->channel;
        }
    }

    object->cached_entry = 0;
    return 0;
}

/**
 * @brief Find the channel bound to a target with the requested kind and axis, and cache its entry.
 * @param object Animation object.
 * @param target Bound target to match.
 * @param kind Entry kind.
 * @param axis Axis to match against the entry flags' low nibble.
 * @return Matching channel, or null.
 */
LibClass173180* lib_animation_find_channel(LibAnimation* object, const void* target, u8 kind, u8 axis);

/**
 * @brief Prepare a transition between animation objects.
 * @param object Destination animation.
 * @param target Bound target.
 * @param previous Previous animation.
 * @param duration Transition duration.
 * @return Destination frame selected by the transition.
 */
float func_004BDE00(LibAnimation* object, void* target, LibAnimation* previous, float duration);

/**
 * @brief Make the animation's channels from its resource and bind each record to the scene entry it names.
 * @param object Animation object.
 * @param scene Scene whose entries the records name.
 * @param slots Optional slot source for entries without a scene target.
 * @return One when bound, or zero when the animation has no resource.
 */
s32 lib_animation_bind_channels(LibAnimation* object, void* scene, void* slots);

/**
 * @brief Bind populated animation entries whose state names match over up to sixteen characters.
 * @param object Animation object.
 * @param target Vector state to bind.
 * @param name State name to match.
 */
void lib_animation_bind_state(LibAnimation* object, LibAnimationTarget* target, const char* name);

/**
 * @brief Normalize the vector state delta in place.
 * @param object Vector state.
 */
void func_004C2CD0(LibAnimationTarget* object);

/**
 * @brief Read and cache an indexed animation channel matching the entry's low flag nibble.
 * @param object Animation object.
 * @param index Entry index; the caller supplies a valid array index.
 * @param nibble Flag value to match against the entry's low nibble.
 * @return Matching channel, or null.
 */
LibClass173180* lib_animation_channel_at(LibAnimation* object, s32 index, u8 nibble);

/**
 * @brief Replace an animation entry's channel and descriptor when its index is below the entry count.
 * @param object Animation object.
 * @param index Entry index; only the upper bound is checked.
 * @param channel Replacement channel.
 * @param kind Entry kind.
 * @param type Entry type.
 * @param flags Entry flags.
 */
void lib_animation_set_entry_channel(LibAnimation* object, s32 index, LibClass173180* channel, u8 kind, s16 type, u8 flags);

/**
 * @brief Clear populated animation entries' targets and mark their bindings incomplete.
 * @param object Animation object.
 */
void lib_animation_clear_targets(LibAnimation* object);

/**
 * @brief Clear targets for populated animation entries of the requested kind.
 * @param object Animation object.
 * @param kind Entry kind to clear.
 */
void lib_animation_clear_targets_by_kind(LibAnimation* object, u8 kind);

/**
 * @brief Clear populated animation entries referencing a particular target.
 * @param object Animation object.
 * @param target Bound target to remove.
 */
void lib_animation_clear_matching_target(LibAnimation* object, const void* target);

/**
 * @brief Replace the animation data with a decoded resource buffer.
 * @param object Animation object.
 * @param source Resource header to decode.
 */
void lib_animation_load_resource(LibAnimation* object, struct ResidentResourceHeader* source);
#endif

/**
 * @brief Rebuild the receiver's data and return its scalar bounds.
 * @param object Lib text receiver to rebuild.
 * @return Bounds at offset 0xE8, or null when rebuilding fails.
 */
LibTextExtent* lib_text_measure_bounds(LibTextWidget* object);

#ifdef __cplusplus
/**
 * @brief Delete populated channels and unregister their binding-owner links.
 * @param object Animation object.
 */
void lib_animation_release_channels(LibAnimation* object);
#endif

/**
 * @brief Bind a LibAnimation to a second object.
 * @param object Object to update.
 * @param target Object to bind; FieldClass150EB0 passes its object at offset 0x7C.
 * @return Binding status.
 */
s32 func_004BFE10(void* object, void* target);

/**
 * @brief Evaluate the degree-thirteen VU0 cosine approximation.
 * @param angle Angle in radians.
 * @return Approximated cosine.
 */
float lib_cosine(float angle);

/**
 * @brief Evaluate the degree-nine VU0 cosine approximation.
 * @param angle Angle in radians.
 * @return Approximated cosine.
 */
float lib_cosine_degree9(float angle);

/**
 * @brief Evaluate the degree-thirteen VU0 sine approximation.
 * @param angle Angle in radians.
 * @return Approximated sine.
 */
float lib_sine(float angle);

/**
 * @brief Compute the fog mapping offset + reciprocal_scale / z for perspective fog.
 * @param offset Receives the constant fog coefficient.
 * @param reciprocal_scale Receives the reciprocal-distance fog coefficient.
 * @param far_factor Fog factor at the far distance.
 * @param near_factor Fog factor at the near distance.
 * @param near_plane Near-plane distance; must differ from far_plane.
 * @param far_plane Far-plane distance.
 */
void lib_compute_perspective_fog_coefficients(float* offset, float* reciprocal_scale, float far_factor, float near_factor,
                                              float near_plane, float far_plane);

/**
 * @brief Evaluate the degree-nine VU0 sine approximation.
 * @param angle Angle in radians.
 * @return Approximated sine.
 */
float lib_sine_degree9(float angle);

#ifdef __cplusplus
/**
 * @brief Compute dot(point - origin, direction) over the xyz components.
 * @param point Aligned point vector.
 * @param direction Aligned vector supplying the dot-product coefficients.
 * @param origin Aligned vector subtracted from point.
 * @return The xyz dot product.
 */
float lib_dot_point_offset(const LibVector4* point, const LibVector4* direction, const LibVector4* origin);

/**
 * @brief Compute the inverse-rotated positive z direction of a unit quaternion.
 * @param quaternion Unit quaternion to evaluate.
 * @param output Vector receiving the direction in xyz and 1 in w.
 */
void lib_quaternion_inverse_z_direction(const FieldVec4B* quaternion, FieldVec4A* output);

/**
 * @brief Build a quaternion from an origin-to-target direction and supplied z rotation.
 * @param output Four-float quaternion destination.
 * @param target Target position measured from the origin.
 * @param z_angle Rotation about z in radians.
 */
void lib_quaternion_from_direction_xz(float* output, const LibVector4* target, float z_angle);

/**
 * @brief Build a directional shadow projection onto a plane.
 * @param output Projection matrix destination.
 * @param direction Projection direction; its xyz dot product with the plane normal must be nonzero.
 * @param plane Plane equation coefficients (normal.x, normal.y, normal.z, offset).
 */
void lib_build_directional_shadow_matrix(LibMatrix44Value* output, const FieldVec4A* direction, const FieldVec4A* plane);

/**
 * @brief Build the homogeneous shadow matrix dot(light, plane) * I - light * plane transpose.
 * @param output Projection matrix destination.
 * @param light Homogeneous light vector; w distinguishes a point from a direction.
 * @param plane Plane equation coefficients (normal.x, normal.y, normal.z, offset).
 */
void lib_build_projective_shadow_matrix(LibMatrix44Value* output, const FieldVec4A* light, const FieldVec4A* plane);
#endif




/** Return the receiver address at byte offset 0x10. */
const void* func_004BD370(const void* object);

/** Return the receiver address at byte offset 0x570. */
const void* func_004BD3D0(const void* object);

/** Return the receiver address at byte offset 0x40. */
const void* func_004BD4A0(const void* object);

/** Return the receiver address at byte offset 0x20. */
const void* func_004BD4B0(const void* object);

/** Forward the receiver to func_004A4570 and return its queue result. */
s32 func_004C8510(void* object);


#ifdef __cplusplus
void func_004C3AE0(void* object);
void func_004C3AF0(void* object);

void func_004C4500(void* object);
void func_004C4510(void* object);


/** Clear the vector at offset 0xB0 and update the associated state. */
void func_004C2B30(void* object);

/** Set the active byte and notify the embedded receiver. */
void func_004C61F0(N54Owner84_004BD360* object);

/**
 * @brief Load the shared font, upload its textures and store it in the resident entry table.
 * @param chunks Loaded chunk list, or null to read archive resources 8 and 9.
 * @param source Loaded texture block; read from the archive when chunks is null.
 * @return One when the font is loaded, or zero when an allocation or decode fails.
 */
s32 lib_load_shared_font(struct LibFontChunk* chunks, struct ResidentResourceHeader* source);

}
#endif

#ifdef __cplusplus
class LibMessageWindow;

/** Multiline text of a message window, passing its control codes on to the window. MAIN vtable at 0x174EB0. */
class LibMessageWindowText : public LibObject174D90
{
public:
    /** @brief Destroy the text. */
    virtual ~LibMessageWindowText();

    /** @brief Flag the restart for the window. */
    virtual void func_0045F600();

    /** @brief Flag the end of the text for the window. */
    virtual void func_0045F610();

    /**
     * @brief Pass a three-value control code to the window.
     * @param first First value.
     * @param second Second value.
     * @param third Third value.
     */
    virtual void func_0045F620(s16 first, s16 second, u32 third);

    /**
     * @brief Pass a one-value control code to the window.
     * @param value Control value.
     */
    virtual void func_0045F630(u32 value);

    /**
     * @brief Pass a one-value control code to the window and set its flag byte at 0x1064.
     * @param value Control value.
     */
    virtual void func_0045F640(u32 value);

    /** @brief Flag a control code for the window and set its flag byte at 0x1064. */
    virtual void func_0045F650();

    /** Window the text belongs to. */
    LibMessageWindow* owner;
};

/** Partial message window: a container holding a panel, two clipping widgets and its multiline text. MAIN vtable at 0x174DD0. */
class LibMessageWindow : public LibContainer
{
public:
    /** @brief Destroy the window and its widgets. */
    virtual ~LibMessageWindow();

    /**
     * @brief Advance from state 4 or 6 to the next state.
     * @return One when the state advanced, otherwise zero.
     */
    s32 func_00461B60();

    /**
     * @brief In state 4 or 6, load new text into the window and go back to state 2.
     * @param source Resource source word.
     * @param key Text resource key.
     * @param mode Drawing mode; its bits 16 and 18 are kept from the current mode.
     * @param flag Resource state flag.
     * @return One when the text was loaded, otherwise zero.
     */
    s32 func_00461BA0(u32 source, s32 key, u32 mode, u32 flag);

    u8 unkf0[0x9D0];
    LibMessageWindowText text;
    u32 source;
    s32 key;
    u32 mode;
    s32 state;
    u32 unk1050;
    s16 unk1054;
    s16 unk1056;
    u32 unk1058;
    u8 unk105c;
    u8 unk105d;
    u8 unk105e;
    u8 unk105f;
    u8 unk1060;
    u8 unk1061;
    u8 unk1062;
    u8 unk1063;
    u8 unk1064;
};
#endif

#endif
