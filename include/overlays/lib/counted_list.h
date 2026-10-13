#ifndef SO3_OVERLAYS_LIB_COUNTED_LIST_H
#define SO3_OVERLAYS_LIB_COUNTED_LIST_H

#include "overlays/lib/text_003E68C0.h"

#ifdef __cplusplus
/** 0x14-byte list receiver with the virtual pointer after its sentinel and count. */
class LibClass178A70
{
public:
    LibClass171E90 sentinel;
    u32 node_count;
    /** @brief Initialize the list receiver. */
    LibClass178A70();
    /** @brief Destroy the list receiver. */
    virtual ~LibClass178A70();
    /** @brief Append a node to the end of the list. @param node Node to append. */
    virtual void append(void* node);
    /** @brief Prepend a node to the beginning of the list. @param node Node to prepend. */
    virtual void prepend(void* node);
    /**
     * @brief Link a node after a list position.
     * @param position Insertion position.
     * @param node Node to insert.
     */
    virtual void insert_after(void* position, void* node);
    /** @brief Unlink a node and clear its list links. @param node Node to remove. */
    virtual void unlink(void* node);
};

#endif

#endif
