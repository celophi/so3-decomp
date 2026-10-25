#ifndef SO3_OVERLAYS_1067_00_TEXT_001DD3C0_H
#define SO3_OVERLAYS_1067_00_TEXT_001DD3C0_H

#include "types.h"
#include "overlays/lib/vector.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_001FD860.h"
#include "overlays/1067-00/field_list.h"
#include "overlays/1067-00/text_0022DC70.h"

/** Partial object linked into a circular list, with flag and state words. */
typedef struct FieldFlaggedListObject
{
    u8 unk00[8];
    struct FieldFlaggedListObject* next;
    u8 unk0c[0x64];
    s32 unk70;
    s32 unk74;
    u32 unk78;
    void* unk7c;
    u8 unk80[0xC];
    u8 unk8c_0_1 : 2;
    u8 unk8c_2 : 1;
    u8 unk8c_3_7 : 5;
    u8 unk8d[0x17B];
    u32 unk208;
} FieldFlaggedListObject;

#ifdef __cplusplus


/** Root of the FieldListObject hierarchy, with vtable D_150050 in main data. */
class FieldClass150050
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150050()
    {
    }
};

/** Intermediate base with two list links, with vtable D_150060 in main data. */
class FieldClass150060 : public FieldClass150050
{
public:
    /** @brief Clear the link words. */
    FieldClass150060()
    {
        unk04 = 0;
        unk08 = 0;
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass150060()
    {
    }

    FieldClass150060* unk04;
    FieldClass150060* unk08;
};

/**
 * @brief Field object registered with a Lib intrusive list.
 *
 * The owner points to the Lib list subobject, which can sit inside a larger
 * list object. Registration and node updates use the shared list interface.
 */
class FieldListObject : public FieldClass150060
{
public:
    /** @brief Clear the registration flag, state byte and list owner. */
    FieldListObject()
    {
        is_listed = 0;
        unk0f = 0;
        owner = 0;
    }

    /** @brief Detach from the owning list, then destroy the node. */
    virtual ~FieldListObject()
    {
        lib_object_detach_owner(this);
    }

    /**
     * @brief Report the list kind used when registration requests the default.
     *
     * This is separate from list_kind, which records the kind chosen by the
     * owner. An explicit insertion kind or later kind change can differ.
     * @return Three in the base implementation.
     */
    virtual s32 get_default_list_kind();

    /** @brief Delete the object through its virtual destructor. */
    virtual void func_001DD7B0();

    /**
     * @brief Advance this registered object's state.
     *
     * Called during the owning list's update pass. The base does no work;
     * overrides can detach this node or queue it for release.
     */
    virtual void update();

    /** @brief Default handler that performs no work. */
    virtual void func_001DD410();

    /** Kind used by the owning intrusive list. */
    s16 list_kind;

    /** Registration flag set on insertion and cleared on removal. */
    u8 is_listed;

    u8 unk0f;

    /** List subobject that registered this node, or null after detachment. */
    LibClass178DD0* owner;
};

/**
 * Partial base class with two virtual handlers, with vtable D_150000 in main
 * data. Slot 1 is named after its lowest known override (func_001DDB30); its
 * own implementation is func_001DF370.
 */
class FieldClass1DD400
{
public:
    /** @brief Default handler that performs no work. */
    virtual void func_001DD400();

    /**
     * @brief Default handler that performs no work.
     * @param arg Pointer argument; the FieldResourcePreloader state machine passes null and
     *        FieldResourceRequestHandler's override reads its word at offset 0x1C.
     */
    virtual void func_001DDB30(void* arg);
};

/**
 * @brief Coordinate resource loaders registered with the field context.
 *
 * The 140-byte owner has a Lib list base at offset 0x14. Loaders point back to
 * that list through their owner field. Updates snapshot its nodes by list
 * kind, allow entry zero to load and request cancellation from later entries.
 */
class FieldResourceLoaderList : public FieldListObject, public LibClass178DD0
{
public:
    /** @brief Initialize the inherited field node and object list. */
    FieldResourceLoaderList()
    {
    }

    /**
     * @brief Report this object's default list kind.
     * @return The class's default list kind.
     */
    virtual s32 get_default_list_kind();

    /** @brief Dispatch the list's virtual update handler. */
    virtual void update();

    /**
     * @brief Update snapshot entry zero and cancel later entries while the field permits it.
     * Null entries and nodes no longer registered with the list are skipped.
     */
    virtual void update_nodes();

    /** @brief Destroy the Lib list owner and detach the inherited field node. */
    virtual ~FieldResourceLoaderList();

    /** @brief Prepend a node using its default list kind. @param node Node to register. */
    void insert(void* node)
    {
        LibClass178DD0& list = *this;
        void* self = &list;
        list.insert_node_after(self, node, LibClass178DD0::DEFAULT_NODE_KIND);
    }
};

/** Partial 16-byte, 8-byte-aligned FieldClass1DD400 used as the base at offset 0x90 of FieldClass14FE30 (vtable part D_14FE84). */
class FieldClass14FE84 : public FieldClass1DD400
{
public:
    u8 unk04[4];
    u64 unk08;
};

/** Partial class with bases at offsets 0x78 and 0x90 and a Lib member at 0xA0, with vtable D_14FE30 in main data. */
class FieldClass14FE30 : public LibClass178DD0, public FieldListObject, public FieldClass14FE84
{
public:
    static void* operator new(u32 size);

    FieldClass14FE30();

    /** @brief Detach the member at offset 0xA0, then destroy the object. */
    virtual ~FieldClass14FE30();

    /**
     * @brief Release the object's storage through the Lib heap.
     * @param object Storage to release.
     */
    static void operator delete(void* object)
    {
        func_004DB570(object);
    }

    /** @brief Detach the FieldListObject base and queue it on the resident object queue. */
    virtual void func_001DD7B0();

    /**
     * @brief Call func_00227130 for each listed object whose flag bit 1 is set.
     * @param arg Unused interface argument.
     */
    virtual void func_001DDB30(void* arg);

    /**
     * @brief Report this object's default list kind.
     * @return The class's default list kind.
     */
    virtual s32 get_default_list_kind();

    /**
     * @brief Sort the list items by height, then run their per-frame handlers.
     *
     * Items are collected into a temporary array and bubble-sorted from the
     * second entry on by unk464 (type-0x400 objects) or the y component of
     * unk20. Unless the context object at offset 0x8 has a positive float at
     * offset 0x90, live type-0x2 items then run slots 21, 23 and 24; every live
     * item runs slot 13. Nothing happens when bit 7 at context offset 0xDD is set.
     */
    virtual void update_nodes();

    /**
     * @brief Point the context's FieldBattleResourcePreloader at the nearest live type-0x20 list item.
     *
     * Skipped while context flags or the focus object block it. Otherwise runs
     * the per-frame list handler, then finds the type-0x20 item nearest to the
     * context object at offset 0x18 among those with a valid word at offset
     * 0x690. The context's FieldBattleResourcePreloader, created on first use, is updated
     * through set_resource_selection when its settings differ from that item's.
     */
    virtual void update();

    LibTransform unkA0;
};

/**
 * @brief Shared lifecycle for resource loaders registered with the field context.
 *
 * Derived loaders advance reads, release request buffers and schedule their
 * own removal. The 24-byte base keeps the load kind and current state; its
 * vtable at 0x150010 leaves the three lifecycle operations pure virtual.
 */
class FieldResourceLoadTask : public FieldListObject
{
public:
    /** @brief Initialize load kind 5 and the idle request state. */
    FieldResourceLoadTask()
    {
        load_kind = 5;
        request_state = 0;
    }

    /** @brief Destroy the object. */
    virtual ~FieldResourceLoadTask()
    {
    }

    /**
     * @brief Report this object's default list kind.
     * @return The class's default list kind.
     */
    virtual s32 get_default_list_kind();

    /** @brief Detach the object and queue it on the resident object queue. */
    virtual void func_001DD7B0();

    /**
     * @brief Advance resource reads or handle a cancellation request.
     * @param cancel_request One requests cancellation; zero advances loading.
     */
    virtual void update_requests(s32 cancel_request) = 0;

    /**
     * @brief Poll cancellation and release request buffers when cleanup can proceed.
     * @return One if a buffer was present before cleanup, two if a buffer remains pending, otherwise zero.
     */
    virtual s32 poll_request_release() = 0;

    /**
     * @brief Cancel pending reads or queue the loader for removal.
     * @return One after queuing the loader for removal, otherwise zero while reads finish.
     */
    virtual s32 request_removal() = 0;

    /**
     * @brief Read the loader kind used when coordinating resource requests.
     * @return The stored load kind.
     */
    virtual u8 get_load_kind();

    /** @brief Load category used when coordinating other registered loaders. */
    u8 load_kind;

    /**
     * @brief Current loading, cancellation or removal state.
     *
     * Common states are 0 for idle, 1 for reading and 5 for completion.
     * Decoder subclasses also use this byte for their processing stages.
     */
    u8 request_state;
};

/**
 * @brief Resource request with completion and cancellation flags for preloading.
 *
 * The 32-byte record retains the base's vtable pointer at offset 0x18.
 */
class FieldPreloadRequest : public FieldResourceRequest
{
public:
    /** @brief Initialize a request with neither completion nor cancellation pending. */
    FieldPreloadRequest();

    /**
     * @brief Clear the preload flags and release the request's buffer.
     * @return The base request's release result.
     */
    virtual s32 release_buffer();

    u8 read_complete : 1;
    u8 cancel_pending : 1;
    u8 unk1c_2_7 : 6;
    u8 unk1d[3];
};

/**
 * @brief Preload a counted array of resources through the resident request queue.
 *
 * The 52-byte object has its completion callback base at offset 0x18.
 * Its primary vtable is at 0x14FFB0; the callback part follows at 0x14FFDC.
 */
class FieldResourcePreloader : public FieldResourceLoadTask, public FieldClass1DD400
{
public:
    /** @brief Clear the record array and state, set the defaults, then reset the records. */
    FieldResourcePreloader();

    /** @brief Free the record array, then destroy the object. */
    virtual ~FieldResourcePreloader();

    /**
     * @brief Advance resource reads or wait for their cancellation and cleanup.
     * @param flag One to request cancellation, zero to continue loading.
     */
    virtual void update_requests(s32 flag);

    /**
     * @brief Poll cancellation and release the requests when cleanup can proceed.
     *
     * State 1 releases every record not flagged by bit 0 at its offset 0x08 and moves to
     * state 10. State 10 only reports. State 9 waits while field_records_blocked() reports
     * a block; otherwise, like any other state, it notes whether a record still has a
     * nonzero buffer address, releases all request_capacity records,
     * and resets the state and current request index.
     * @return 1 if that scan found such a record, otherwise 2 if a record still has a
     *         nonzero buffer address, otherwise 0.
     */
    virtual s32 poll_request_release();

    /**
     * @brief Cancel pending reads or queue the preloader for removal.
     *
     * State 1 cancels reads for records that do not borrow their buffers and
     * enters state 7. States 9 and 10 also enter state 7. That state waits for
     * update_requests to finish the reads and queue removal; other states
     * queue the object immediately through func_001DD7B0.
     * @return One after queuing the preloader for removal, otherwise zero.
     */
    virtual s32 request_removal();

    /**
     * @brief Queue a read into the current request's buffer.
     *
     * A missing buffer leaves the request unchanged. Otherwise keeps the resident
     * queue slot in request_address, enters state 1 and clears callback_ready.
     */
    virtual void start_current_read();

    /** @brief Advance past the completed read and skip requests marked as finished. */
    virtual void advance_requests();

    /** @brief Reset the request records, counts and current index without freeing buffers. */
    virtual void reset_requests();

    /** @brief Release the buffer of every allocated request record. */
    virtual void release_requests();

    /**
     * @brief Flush the cache and mark the current read ready for completion handling.
     * @param arg Unused callback argument.
     */
    virtual void func_001DDB30(void* arg);

    /**
     * @brief Replace the record array with count newly constructed records.
     * @param count Number of records to allocate.
     */
    void allocate_requests(s32 count);

    FieldPreloadRequest* requests;
    u32 unk20;
    s32 request_capacity;
    s32 request_priority;
    u8 unk2c;
    u8 request_count;
    u8 current_request;
    u8 unk2f;
    u8 unk30_0 : 1;
    u8 callback_ready : 1;
    u8 unk30_2_7 : 6;
};

/**
 * @brief Pass the table entries of each listed type-0x8 object to the D_001B661C manager.
 *
 * Objects whose func_00204420 check fails or that have no table at offset 0x7C
 * are skipped. At most 32 entries are collected per object.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
extern "C" void func_001DD5E0(FieldClass150060* list);

/**
 * @brief Run each listed object's type-specific update.
 *
 * Type-0x400 objects run slot 37 with 1; type-0x20000 objects are detached and
 * released; type-0x20 objects without an object at offset 0x148 copy the vector
 * at offset 0x670 through slot 15. Afterwards the D_001B645C holder, if any,
 * releases its attached object and clears its word at offset 0x250.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
extern "C" void func_001DD860(FieldClass150060* list);
#endif

#ifdef __cplusplus
class FieldClass151510;

/**
 * @brief Update the type-0x2 and type-0x20000 objects in a list through slots 12 and 14.
 *
 * Objects whose word at offset 0x70 has its sign bit set are skipped. With mode
 * 2 or more, each object's own bits 5 and 6 at offset 0x8C select the settings
 * and type-0x10 objects are also passed to func_00220150; otherwise mode and arg
 * are passed to slot 12.
 * @param list Head of a circular object list.
 * @param mode Setting passed to slot 12, or 2 or more to use each object's own settings.
 * @param arg Update argument passed to slot 12 when mode is below 2.
 */
extern "C" void func_001DD9A0(FieldClass150060* list, s8 mode, s32 arg);

/**
 * @brief Test the listed type-0x1 objects other than self with func_0045BD20.
 *
 * Objects with type bit 0x10000 but not 0x200, failing func_00204420, with bit 3
 * at offset 0x204 set, or without an object at offset 0xA8 are skipped.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param self Object to skip; nothing is tested when bit 22 at its offset 0x204 is set.
 * @param arg0 First argument passed to func_0045BD20.
 * @param arg1 Second argument passed to func_0045BD20.
 * @return 1 when a test succeeds, otherwise 0.
 */
extern "C" s32 func_001DDBA0(FieldClass150060* list, FieldClass151510* self, void* arg0, void* arg1);

/**
 * Partial list head reached through a listed object's owner pointer at offset
 * 0x10, recording the last object found by func_001DDD30.
 */
class FieldListOwner94 : public FieldClass150060
{
public:
    u8 unk0c[0x88];
    FieldClass150060* unk94;
};

/**
 * @brief Find the first listed type-0x1 object whose shape passes func_0045F5A0 against the target's shape.
 *
 * Objects equal to the target, with type bit 0x10000 but not 0x200, type-0x10
 * objects with a positive float at offset 0x638, objects failing
 * func_00204420, with bit 3 at offset 0x204 set, or without an object at offset
 * 0xA8 are skipped. When the target is a type-0x20 object with bit 0 at offset
 * 0x69F set, type-0x10 objects are skipped; type-0x20 objects are skipped when
 * their own bit 0 at offset 0x69F is set or the target is a type-0x10 object
 * with a positive float at offset 0x638.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param target In: object whose shape is tested; nothing is tested when bit 22 at its offset 0x204 is set. Out: the object found.
 * @return True when an object is found; it is also stored at the list's offset 0x94.
 */
extern "C" bool func_001DDD30(FieldListOwner94* list, FieldClass151510** target);

/** Resident Lib list that many Field objects insert themselves into. */
extern "C" LibClass178DD0* D_001B6614;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Call func_002379A0 with a nonzero flag for each listed object whose flag bit 3 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DD570(FieldFlaggedListObject* list);

/**
 * @brief Clear the word at offset 0x208 for each listed object whose flag bit 1 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DD6E0(FieldFlaggedListObject* list);

/**
 * @brief Find a listed object with a matching key, bit 2 at offset 0x8C clear and a nonnull pointer at offset 0x7C.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param key Value compared with the word at offset 0x74.
 * @return The first matching object, or null if none matches.
 */
FieldFlaggedListObject* func_001DDF50(FieldFlaggedListObject* list, s32 key);

/**
 * @brief Update the table of every listed object that has one at offset 0x7C.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param flag Nonzero to enable the setting passed to func_004728A0.
 */
void func_001DE400(FieldFlaggedListObject* list, s32 flag);

/**
 * @brief Append listed objects to the field context's queue, all of them or only those with a nonzero word at offset 0x70.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param only_keyed Nonzero to skip objects whose word at offset 0x70 is zero.
 */
void func_001DE470(FieldFlaggedListObject* list, s32 only_keyed);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/** Registered field object list. */
class FieldClass150E10 : public FieldListObject, public LibClass178DD0
{
public:
    /** @brief Initialize the inherited field node and object list. */
    FieldClass150E10()
    {
    }

    virtual ~FieldClass150E10();

    /**
     * @brief Report this object's default list kind.
     * @return The class's default list kind.
     */
    virtual s32 get_default_list_kind();

    virtual void func_001DD7B0();

    /** @brief Update inherited nodes when the field context permits it. */
    virtual void update();
};
#endif

#endif
