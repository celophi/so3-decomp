#ifndef SO3_OVERLAYS_0002_01_TEXT_004CD3A0_H
#define SO3_OVERLAYS_0002_01_TEXT_004CD3A0_H

#include "types.h"

/** Partial list node; the leading bytes and full object extent are unknown. */
typedef struct LibListNode
{
    u8 unk00[8];
    struct LibListNode* next;
    s16 unk0c;
} LibListNode;

#ifdef __cplusplus
/**
 * Partial Lib base class with its vtable pointer at offset 0x10, with vtable D_178DD0 in boot data.
 * Its twelve virtual slots are declared in vtable order; slots 5-9 keep opaque parameters
 * until their Lib implementations are reconstructed.
 */
class LibClass178DD0
{
public:
    u8 unk00[0xC];
    s32 unk0c;

    /** @brief Destroy the object. */
    virtual ~LibClass178DD0();

    /**
     * @brief Link a node before the list's first node and increment the count at offset 0xC.
     * @param node Node to link.
     */
    virtual void func_004CA020(void* node);

    /**
     * @brief Link a node after the list's last node and increment the count at offset 0xC.
     * @param node Node to link.
     */
    virtual void func_004C9FF0(void* node);

    /**
     * @brief Link a node after another node and increment the count at offset 0xC.
     * @param position Node to link after.
     * @param node Node to link.
     */
    virtual void func_004C9FC0(void* position, void* node);

    /**
     * @brief Unlink a node and decrement the nonzero count at offset 0xC.
     * @param node Node to unlink; the list itself and null are ignored.
     */
    virtual void func_004C9F60(void* node);

    /**
     * @brief Lib virtual slot 5.
     * @param value Opaque argument.
     */
    virtual void func_004D72A0(void* value);

    /** @brief Lib virtual slot 6. */
    virtual void func_004D6730();

    /**
     * @brief Lib virtual slot 7.
     * @param a Opaque first argument.
     * @param b Opaque second argument.
     */
    virtual void func_004D74F0(void* a, void* b);

    /**
     * @brief Lib virtual slot 8.
     * @param a Opaque first argument.
     * @param b Opaque second argument.
     */
    virtual void func_004D7450(void* a, void* b);

    /**
     * @brief Lib virtual slot 9.
     * @param a Opaque first argument.
     * @param b Opaque second argument.
     * @param c Opaque third argument.
     */
    virtual void func_004D73B0(void* a, void* b, void* c);

    /**
     * @brief Store the attached object pointer at offset 0x70.
     * @param attached Object pointer to store.
     */
    virtual void func_004295B0(void* attached);

    /** @brief Default handler that performs no work. */
    virtual void func_004295C0();

    /**
     * @brief Release storage allocated for this class.
     * @param object Storage to release.
     */
    static void operator delete(void* object);

    u8 unk14[0x48];
    s32 unk5c;
    s32 unk60;
    u8 unk64[8];
    void** unk6c;
    u8 unk70[8];
};

/** Partial Lib class used as a member object, with vtable D_178EA0 in boot data. */
class LibClass178EA0
{
public:
    /** @brief Destroy the object. */
    virtual ~LibClass178EA0();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Transform a four-float input into an output vector.
 * @param output Destination vector.
 * @param input Source vector.
 */
void func_004CE4C0(float* output, const float* input);

/**
 * @brief Pass a batch of table entry handles to the manager.
 * @param manager Manager object that receives the entries.
 * @param count Number of entries.
 * @param entries Entry handles.
 */
void func_004D4010(void* manager, s32 count, void** entries);

/**
 * @brief Pass one list item to its virtual handler at vtable offset 0x14.
 * @param list List that owns the item.
 * @param item Item to process.
 */
void func_004D6700(void* list, void* item);

/**
 * @brief Fill an array with the list's items.
 * @param list List whose items are collected.
 * @param items Array that receives the item pointers.
 */
void func_004D6AF0(void* list, void** items);

/**
 * @brief Detach the object from the owner stored at offset 0x10, then clear that pointer.
 * @param object Object to detach; the owner receives it through its virtual handler at vtable offset 0x1C.
 */
void func_004D65C0(void* object);

/**
 * @brief Test whether a list traversal has reached its sentinel.
 * @param sentinel List sentinel.
 * @param node Current node.
 * @return 1 if node is the sentinel, otherwise 0.
 */
s32 func_004D6DC0(const void* sentinel, const void* node);

/**
 * @brief Get the next node in a circular list traversal.
 * @param node Current node or list sentinel.
 * @return Next node, which may be the list sentinel.
 */
LibListNode* func_004D6DD0(const LibListNode* node);

/**
 * @brief Read the signed index used to select a node output counter.
 * @param node Current list node.
 * @return The sign-extended index value.
 */
s32 func_004D6DB0(const LibListNode* node);

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_004D6DE0(void* object);

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_004D99A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004D00A0(void* object);

/**
 * @brief Return the fixed value 16.
 * @param object Receiver or first argument; unused.
 * @return Always 16.
 */
s32 func_004D0160(void* object);

/**
 * @brief Return the fixed value 10.
 * @param object Receiver or first argument; unused.
 * @return Always 10.
 */
s32 func_004D5810(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004D5820(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_004D5D70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004D66F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_004D9B50(void* object);

/**
 * @brief Return the fixed value 8.
 * @param object Receiver or first argument; unused.
 * @return Always 8.
 */
s32 func_004DAFD0(void* object);

#ifdef __cplusplus
}
#endif

#endif
