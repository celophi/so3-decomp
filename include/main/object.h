#ifndef SO3_MAIN_OBJECT_H
#define SO3_MAIN_OBJECT_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"

#ifndef __cplusplus
typedef struct ResidentLink ResidentLink;
typedef struct ResidentListSentinel ResidentListSentinel;
typedef struct ResidentListObject ResidentListObject;
#endif

#ifdef __cplusplus
extern "C" {
/**
 * @brief Detach a resident object from its owner; Lib implements this.
 * @param object Object to detach.
 */
void lib_object_detach_owner(void* object);
}

/** Resident object root with vtable at 0x14FA20. */
class ResidentLink
{
public:
    virtual ~ResidentLink()
    {
    }
};

/** Partial resident intrusive node with vtable at 0x14FA30. */
class ResidentListSentinel : public ResidentLink
{
public:
    /** @brief Construct an unlinked node. */
    ResidentListSentinel() : previous(0), next(0)
    {
    }

    virtual ~ResidentListSentinel()
    {
    }

    ResidentListSentinel* previous;
    ResidentListSentinel* next;
};

/** Partial resident object interface with vtable at 0x14FA40. */
class ResidentListObject : public ResidentListSentinel
{
public:
    /** @brief Construct an object with no owner. */
    ResidentListObject() : unk0e(0), unk0f(0), owner(0)
    {
    }

    /** @brief Detach the object from its owner. */
    virtual ~ResidentListObject()
    {
        lib_object_detach_owner(this);
    }

    /**
     * @brief Return the object's kind.
     * @return Object kind.
     */
    virtual s32 get_default_list_kind();

    /** @brief Destroy the object through its virtual destructor. */
    virtual void destroy();

    /** @brief Update the object; its list calls this once a frame. */
    virtual void update();

    virtual void render();

    s16 list_kind;
    u8 unk0e;
    u8 unk0f;
    void* owner;
};
#endif

#endif
