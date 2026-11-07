#ifndef SO3_OVERLAYS_LIB_SCENE_H
#define SO3_OVERLAYS_LIB_SCENE_H

#include "types.h"
#include "overlays/lib/counted_list.h"
#include "overlays/lib/text_0046AE20.h"

class LibCameraContext;
class LibCamera;
class LibLightList;
class LibDisplayManager;
class LibRenderer;
class LibUpdateList;

#define LIB_ENTRY_MANAGER_SLOT_COUNT 16

enum
{
    LIB_ENTRY_HAS_NAMES = 1,
    LIB_ENTRY_KIND_LIGHT = 2,
    LIB_ENTRY_KIND_CAMERA = 3,
    LIB_ENTRY_NAME_COMPARE_LENGTH = 16
};

/** Runtime handle and source metadata for one resource entry. */
typedef struct LibManagedEntry
{
    u8 unk00;
    u8 unk01[3];
    u32 unk04;
    void* handle;
    LibEntryMetadata* metadata;
} LibManagedEntry;

/** Resource flags and signed entry count used by table searches. */
typedef struct LibEntryTableHeader
{
    u32 flags;
    s32 count;
} LibEntryTableHeader;

/**
 * Scene built from a scene resource: the runtime table of its entries and the objects made for them, with vtable
 * D_175320 in main data.
 */
class LibScene : public LibListObject
{
public:
    /** @brief Start with no data, entries or slot objects. */
    LibScene();

    /** @brief Release the entries unless the scene keeps them, queue unborrowed data for release, then destroy the list object. */
    virtual ~LibScene();

    /**
     * @brief Create an object of one kind for an entry.
     * @param kind Object kind.
     * @return The new object, or null.
     */
    virtual void* func_00471480(u8 kind);

    /**
     * @brief Create a camera.
     * @param context Resident context the camera starts from.
     * @return The new camera, or null when allocation fails.
     */
    virtual LibCamera* func_00471440(void* context);

    /** @brief Virtual slot 0x24. */
    virtual void* func_0046DE90(void* unk1, void* unk2, void* record);

    /** @brief Virtual slot 0x28. */
    virtual void* func_0046C540(void* record);

    /**
     * @brief Create an object of kind 0x11.
     * @return The new object, or null.
     */
    virtual void* func_0046BA00();

    /** @brief Virtual slot 0x30. */
    virtual void* func_0046C180(void* unk1, void* unk2, void* record);

    /** Decoded scene resource the entries come from. */
    u8* data;

    LibManagedEntry* entries;
    u32 unk1c;
    LibEntryTableHeader* header;
    u8 unk24[0x10];
    void* unk34[LIB_ENTRY_MANAGER_SLOT_COUNT];

    /** Names looked up in the linked manager by entries with a negative link. */
    char (*link_names)[LIB_ENTRY_NAME_COMPARE_LENGTH];

    void* unk78;
    LibEntryManager* linked;
    LibListReceiver unk80;
    s32 cached_entry_index;
    u8 unk98[4];

    /** The data belongs to someone else, so the scene doesn't free it. */
    u8 data_borrowed;

    u8 unk9D;
    u8 unk9E;

    /** Nonzero skips the matching unk34 slot. */
    u8 unk9f[LIB_ENTRY_MANAGER_SLOT_COUNT];
};

/**
 * @brief Create the runtime objects for a loaded scene's entries and hook them up to the display, lists and renderer.
 * @param scene Scene whose data is loaded.
 * @param display Display the scene draws to.
 * @param list Update list the objects join.
 * @param lights Light list (g_light_list) the scene's lights are appended to.
 * @param manager Display manager.
 * @param renderer Renderer.
 * @param flag Boot always passes one.
 */
extern "C" void lib_scene_build_objects(LibScene* scene, LibCameraContext* display, LibUpdateList* list, LibLightList* lights,
                                        LibDisplayManager* manager, LibRenderer* renderer, s32 flag);

#endif
