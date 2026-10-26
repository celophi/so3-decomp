#ifndef SO3_OVERLAYS_CITEM_TEXT_H
#define SO3_OVERLAYS_CITEM_TEXT_H

#include "types.h"

typedef struct ItemRecord ItemRecord;
typedef struct StatusRecord StatusRecord;
typedef struct ItemWindow1844B0 ItemWindow1844B0;
typedef struct Record0034C6A0 Record0034C6A0;
#ifdef __cplusplus
class ItemList184ED8;

typedef ItemList184ED8 Record003540E0;
#else
typedef struct Record003540E0 Record003540E0;
#endif

#ifdef __cplusplus
class ItemList184EC8;

typedef ItemList184EC8 Record003542F0;
#else
typedef struct Record003542F0 Record003542F0;
#endif

#ifdef __cplusplus
class ItemList184EB8;

typedef ItemList184EB8 Record00354740;
#else
typedef struct Record00354740 Record00354740;
#endif

typedef struct ItemWindow1849F0 ItemWindow1849F0;
typedef struct ItemWindow184AF0 ItemWindow184AF0;
typedef struct ItemWindow184BF0 ItemWindow184BF0;
typedef struct ItemWindow184CF0 ItemWindow184CF0;
#ifdef __cplusplus
class ItemListNode;
#else
typedef struct ItemListNode ItemListNode;
#endif
typedef struct ItemListOwner ItemListOwner;

#ifdef __cplusplus
class FieldClass15AE70;
class FieldClass15AD40;

class ItemListWindow1848D0;
#else
typedef struct FieldClass15AE70 FieldClass15AE70;
typedef struct FieldClass15AD40 FieldClass15AD40;

typedef struct ItemListWindow1848D0 ItemListWindow1848D0;
#endif

#ifdef __cplusplus
class CitemCoordinateNode;

/** Sentinel-headed item menu list with its own virtual destructor. */
class ItemList184ED8
{
    public:
        ItemListNode* head;
        u32 count;

        /** @brief Allocate the sentinel and initialize the empty list. */
        ItemList184ED8();

        /** @brief Release the links and sentinel without destroying payloads. */
        virtual ~ItemList184ED8();
};

/** Sentinel-headed item menu list with its own virtual destructor. */
class ItemList184EC8
{
    public:
        ItemListNode* head;
        u32 count;

        /** @brief Allocate the sentinel and initialize the empty list. */
        ItemList184EC8();

        /** @brief Release the links and sentinel without destroying payloads. */
        virtual ~ItemList184EC8();
};

/** Sentinel-headed coordinate list used by the item menu. */
class ItemList184EB8
{
    public:
        CitemCoordinateNode* head;
        u32 count;

        /** @brief Allocate the sentinel and initialize the empty list. */
        ItemList184EB8();

        /** @brief Release the coordinate links and sentinel. */
        virtual ~ItemList184EB8();
};

#endif

/** Two scalar coordinates passed together to the coordinate list. */
typedef struct CitemCoordinate2
{
    float x;
    float y;
#ifdef __cplusplus
    /** @brief Store both coordinates. @param x Horizontal coordinate. @param y Vertical coordinate. */
    CitemCoordinate2(float x, float y) : x(x), y(y) {}
#endif
} CitemCoordinate2;

/** Four float components stored on a 16-byte boundary. */
#ifdef __cplusplus
class Vector4
{
public:
    Vector4& operator=(const Vector4& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
        return *this;
    }

    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16)));
#else
typedef struct Vector4
{
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) Vector4;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Delete the payload-list links and clear the count when the list is nonempty.
 * @param owner List whose sentinel and payloads are retained.
 */
void func_003541F0(Record003540E0* owner);

/**
 * @brief Delete the payload-list links and clear the count when the list is nonempty.
 * @param owner List whose sentinel and payloads are retained.
 */
void func_00354400(Record003542F0* owner);

/**
 * @brief Delete the coordinate-list links and clear the count when the list is nonempty.
 * @param owner List whose sentinel is retained.
 */
void func_003547C0(Record00354740* owner);

/** Comparator returning zero when passed the same node twice. */
typedef s32 (*ItemListComparator)(const ItemListNode* left, const ItemListNode* right, u32 comparison_arg);

/**
 * @brief Sort the list by swapping links while retaining its payloads and sentinel.
 * @param owner List to reorder.
 * @param compare Signed node comparator, returning zero for equal nodes.
 * @param comparison_arg Argument forwarded to each comparator call.
 * @param ascending Nonzero for ascending order, zero for descending order.
 */
void func_00354980(Record003542F0* owner, ItemListComparator compare, u32 comparison_arg, s32 ascending);

/**
 * @brief Compare the low ten-bit definition keys of two list entries.
 * @param left First list node containing an item record.
 * @param right Second list node containing an item record.
 * @param comparison_arg Unused argument supplied by the list sort.
 * @return Signed difference between their definition keys.
 */
s32 func_00351E40(const ItemListNode* left, const ItemListNode* right, u32 comparison_arg);

/**
 * @brief Append a coordinate pair to the selector's sentinel list.
 * @param owner Coordinate list receiver.
 * @param value Coordinate pair to append.
 */
void item_append_selector_coordinate(Record00354740* owner, CitemCoordinate2 value);

/**
 * @brief Initialize a record and its embedded part.
 * @param record Record to initialize.
 * @param flag Cleanup flag.
 * @return The record.
 */
Record0034C6A0* func_0034C6A0(Record0034C6A0* record, s16 flag);

/**
 * @brief Append a payload to the list when node allocation succeeds.
 * @param owner List with a sentinel head and element count.
 * @param value Payload stored in the new node.
 */
void item_append_list_value(Record003540E0* owner, void* value);

/**
 * @brief Append a payload to the list when node allocation succeeds.
 * @param owner List with a sentinel head and element count.
 * @param value Payload stored in the new node.
 */
void func_00354370(ItemListOwner* owner, void* value);

/**
 * @brief Follow links from the node after the head.
 * @param owner List owner to search.
 * @param index Number of links to follow.
 * @return Reached node, or null if the chain ends first.
 */
ItemListNode* func_00354480(ItemListOwner* owner, s32 index);

/**
 * @brief Append a payload to the list when node allocation succeeds.
 * @param owner List with a sentinel head and element count.
 * @param value Payload stored in the new node.
 */
void func_003544C0(ItemListOwner* owner, void* value);

/**
 * @brief Append a payload to the list when node allocation succeeds.
 * @param owner List with a sentinel head and element count.
 * @param value Payload stored in the new node.
 */
void func_00354550(ItemListOwner* owner, void* value);

/**
 * @brief Follow links from the node after the head.
 * @param owner List owner to search.
 * @param index Number of links to follow.
 * @return Reached node, or null if the chain ends first.
 */
ItemListNode* func_003545E0(ItemListOwner* owner, s32 index);

/**
 * @brief Append a payload to the list when node allocation succeeds.
 * @param owner List with a sentinel head and element count.
 * @param value Payload stored in the new node.
 */
void func_00354620(ItemListOwner* owner, void* value);

/**
 * @brief Append a payload to the list when node allocation succeeds.
 * @param owner List with a sentinel head and element count.
 * @param value Payload stored in the new node.
 */
void func_003546B0(ItemListOwner* owner, void* value);

/**
 * @brief Store the word field at 0x24.
 * @param state Status record to update.
 * @param value Value to store.
 */
void func_00353F70(StatusRecord* state, u32 value);

/**
 * @brief Read the word field at 0x24.
 * @param state Status record to read.
 * @return Current field value.
 */
u32 func_00353F80(StatusRecord* state);

/**
 * @brief Store the signed byte field at 0x28.
 * @param state Status record to update.
 * @param value Value to store.
 */
void func_00353F90(StatusRecord* state, s8 value);

/**
 * @brief Read the signed byte field at 0x28.
 * @param state Status record to read.
 * @return Current field value.
 */
s8 func_00353FA0(StatusRecord* state);

/**
 * @brief Store the byte field at 0xC.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_00348460(ItemRecord* item, u8 value);

/**
 * @brief Read the byte field at 0xC.
 * @param item Item record to read.
 * @return Current field value.
 */
u8 func_00348470(ItemRecord* item);

/**
 * @brief Store the byte field at 0x8.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_00348480(ItemRecord* item, u8 value);

/**
 * @brief Read the byte field at 0x8.
 * @param item Item record to read.
 * @return Current field value.
 */
u8 func_00348490(ItemRecord* item);

/**
 * @brief Store the halfword field at 0xA.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_003484A0(ItemRecord* item, u16 value);

/**
 * @brief Read the halfword field at 0xA.
 * @param item Item record to read.
 * @return Current field value.
 */
u16 func_003484B0(ItemRecord* item);

/**
 * @brief Store the word field at 0x9C.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_003484E0(ItemRecord* item, u32 value);

/**
 * @brief Read the word field at 0x9C.
 * @param item Item record to read.
 * @return Current field value.
 */
u32 func_003484F0(ItemRecord* item);

/**
 * @brief Store the word field at 0x4.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_00348500(ItemRecord* item, u32 value);

/**
 * @brief Read the word field at 0x4.
 * @param item Item record to read.
 * @return Current field value.
 */
u32 func_00348510(ItemRecord* item);

/**
 * @brief Read the word field at 0x10.
 * @param item Item record to read.
 * @return Current field value.
 */
u32 func_00348520(ItemRecord* item);

/**
 * @brief Read the byte field at 0xD.
 * @param item Item record to read.
 * @return Current field value.
 */
u8 func_00348710(ItemRecord* item);

/**
 * @brief Store the byte field at 0xD.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_00348720(ItemRecord* item, u8 value);

/**
 * @brief Read the word field at 0x20.
 * @param item Item record to read.
 * @return Current field value.
 */
u32 func_003487B0(ItemRecord* item);

/**
 * @brief Store the word field at 0x20.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_003489F0(ItemRecord* item, u32 value);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348530(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348550(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348580(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348590(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348600(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348610(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348620(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348630(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348640(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348650(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348660(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348670(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348680(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348690(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348700(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348730(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353EA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353EB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353EC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00353ED0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00353EE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00353FB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00353FC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353FD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353FE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353FF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00354000(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00354010(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00354020(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00354030(void* object);

#ifdef __cplusplus
}
#endif

#endif
