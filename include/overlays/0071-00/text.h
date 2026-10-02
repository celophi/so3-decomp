#ifndef SO3_OVERLAYS_0071_00_TEXT_H
#define SO3_OVERLAYS_0071_00_TEXT_H

#include "types.h"

typedef struct
{
    void* methods;
    u8 pad_04[0x30];
    u32 field_34;
    u8 field_38;
    u8 pad_39[7];
    u32 field_40;
} ConfigControl;

typedef struct ConfigOwnedItem ConfigOwnedItem;

typedef struct ConfigNode
{
    void* value;
    struct ConfigNode* next;
} ConfigNode;

typedef struct
{
    ConfigNode* head;
    s32 count;
} ConfigListOwner;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348500(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348510(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348520(void* object);

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
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003485F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348600(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348610(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348620(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348630(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348640(void* object);

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
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348690(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003520B0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003523F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003524A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003524B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003524C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003524D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003524E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003524F0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00352500(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00352550(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00352560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00352570(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00352580(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00352590(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003525A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003525B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003525C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003525D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003525E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003525F0(void* object);

/**
 * @brief Set the value at object offset 0xC.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00348400(void* object, u8 value);

/**
 * @brief Read the value at object offset 0xC.
 * @param object Object to read.
 * @return Value stored at offset 0xC.
 */
u8 func_00348410(void* object);

/**
 * @brief Set the value at object offset 0x8.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00348420(void* object, u8 value);

/**
 * @brief Read the value at object offset 0x8.
 * @param object Object to read.
 * @return Value stored at offset 0x8.
 */
u8 func_00348430(void* object);

/**
 * @brief Set the value at object offset 0xA.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00348440(void* object, u16 value);

/**
 * @brief Read the value at object offset 0xA.
 * @param object Object to read.
 * @return Value stored at offset 0xA.
 */
u16 func_00348450(void* object);

/**
 * @brief Set the value at object offset 0x98.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00348460(void* object, u32 value);

/**
 * @brief Read the value at object offset 0x98.
 * @param object Object to read.
 * @return Value stored at offset 0x98.
 */
u32 func_00348470(void* object);

/**
 * @brief Set the value at object offset 0x9C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00348480(void* object, u32 value);

/**
 * @brief Read the value at object offset 0x9C.
 * @param object Object to read.
 * @return Value stored at offset 0x9C.
 */
u32 func_00348490(void* object);

/**
 * @brief Set the value at object offset 0x4.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_003484A0(void* object, u32 value);

/**
 * @brief Read the value at object offset 0x4.
 * @param object Object to read.
 * @return Value stored at offset 0x4.
 */
u32 func_003484B0(void* object);

/**
 * @brief Read the value at object offset 0x10.
 * @param object Object to read.
 * @return Value stored at offset 0x10.
 */
u32 func_003484C0(void* object);

/**
 * @brief Read the value at object offset 0xD.
 * @param object Object to read.
 * @return Value stored at offset 0xD.
 */
u8 func_003486B0(void* object);

/**
 * @brief Set the value at object offset 0xD.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_003486C0(void* object, u8 value);

/**
 * @brief Read the value at object offset 0x20.
 * @param object Object to read.
 * @return Value stored at offset 0x20.
 */
u32 func_003487B0(void* object);

/**
 * @brief Set the value at object offset 0x20.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_003488C0(void* object, u32 value);

/**
 * @brief Read the value at object offset 0x24.
 * @param object Object to read.
 * @return Value stored at offset 0x24.
 */
u32 func_0034A420(void* object);

/**
 * @brief Read the value at object offset 0x34.
 * @param object Object to read.
 * @return Value stored at offset 0x34.
 */
u32 func_0034D8A0(void* object);

/**
 * @brief Read the value at object offset 0x38.
 * @param object Object to read.
 * @return Value stored at offset 0x38.
 */
u8 func_00352510(void* object);

/**
 * @brief Set the value at object offset 0x24.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00352520(void* object, u32 value);

/**
 * @brief Set the value at object offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_00352530(void* object, s8 value);

/**
 * @brief Read the value at object offset 0x28.
 * @param object Object to read.
 * @return Value stored at offset 0x28.
 */
s8 func_00352540(void* object);

/**
 * @brief Set a nested display value and flag.
 * @param object Holder of the display state.
 */
void func_003497F0(void* object);

/**
 * @brief Mark each icon active and color the selected one differently.
 * @param object Holder of the icon list.
 * @param selected Index of the icon to color differently.
 */
void func_003486E0(void* object, s16 selected);

/**
 * @brief Initialize the control fields.
 * @param object Control object to initialize.
 * @return The initialized object.
 */
ConfigControl* func_00352460(ConfigControl* object);

/**
 * @brief Find a node by index in the linked list.
 * @param owner Holder of the list head.
 * @param index Zero-based index to find.
 * @return The node at index, or null if the list ends first.
 */
ConfigNode* func_00352690(ConfigListOwner* owner, s32 index);

/**
 * @brief Find a node by index in the linked list.
 * @param owner Holder of the list head.
 * @param index Zero-based index to find.
 * @return The node at index, or null if the list ends first.
 */
ConfigNode* func_003528E0(ConfigListOwner* owner, s32 index);

/**
 * @brief Find a node by index in the linked list.
 * @param owner Holder of the list head.
 * @param index Zero-based index to find.
 * @return The node at index, or null if the list ends first.
 */
ConfigNode* func_003529B0(ConfigListOwner* owner, s32 index);

/**
 * @brief Find a node by index in the linked list.
 * @param owner Holder of the list head.
 * @param index Zero-based index to find.
 * @return The node at index, or null if the list ends first.
 */
ConfigNode* func_00352C00(ConfigListOwner* owner, s32 index);

/**
 * @brief Release an object when requested.
 * @param object Object to release.
 * @param flags Controls whether the object is freed.
 * @return The original object pointer.
 */
void* func_00348CC0(void* object, s32 flags);

/**
 * @brief Release an object when requested.
 * @param object Object to release.
 * @param flags Controls whether the object is freed.
 * @return The original object pointer.
 */
void* func_00349790(void* object, s32 flags);

/**
 * @brief Release an object when requested.
 * @param object Object to release.
 * @param flags Controls whether the object is freed.
 * @return The original object pointer.
 */
void* func_0034A080(void* object, s32 flags);

/**
 * @brief Release an object when requested.
 * @param object Object to release.
 * @param flags Controls whether the object is freed.
 * @return The original object pointer.
 */
void* func_0034AC80(void* object, s32 flags);

/**
 * @brief Release an object when requested.
 * @param object Object to release.
 * @param flags Controls whether the object is freed.
 * @return The original object pointer.
 */
void* func_003515B0(void* object, s32 flags);

/**
 * @brief Release an object when requested.
 * @param object Object to release.
 * @param flags Controls whether the object is freed.
 * @return The original object pointer.
 */
void* func_00351BD0(void* object, s32 flags);

/**
 * @brief Release an object when requested.
 * @param object Object to release.
 * @param flags Controls whether the object is freed.
 * @return The original object pointer.
 */
void* func_00351F70(void* object, s32 flags);

/**
 * @brief Release an object when requested.
 * @param object Object to release.
 * @param flags Controls whether the object is freed.
 * @return The original object pointer.
 */
void* func_003510A0(void* object, s32 flags);

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_00352600(ConfigListOwner* list, void* value);

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_003527D0(ConfigListOwner* list, void* value);

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_00352920(ConfigListOwner* list, void* value);

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_00352AF0(ConfigListOwner* list, void* value);

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_00352C40(ConfigListOwner* list, void* value);

/**
 * @brief Append a value to the linked list.
 * @param list List to update.
 * @param value Value stored in the new node.
 */
void func_00352CD0(ConfigListOwner* list, void* value);

/**
 * @brief Release a control object when requested.
 * @param object Object to release.
 * @param flags Controls whether the object is freed.
 * @return The original object pointer.
 */
void* func_00352400(void* object, s32 flags);

/**
 * @brief Release an embedded member and the object when requested.
 * @param object Object containing the embedded member.
 * @param flags Controls whether the object is freed.
 * @return The original object pointer.
 */
void* func_0034EAD0(void* object, s32 flags);

/**
 * @brief Release the attached item and optionally free the owner.
 * @param object Owner of the attached item.
 * @param flags A positive signed 16-bit value requests freeing the owner.
 * @return The original object pointer.
 */
ConfigOwnedItem* func_00352750(ConfigOwnedItem* object, s32 flags);

/**
 * @brief Release the attached item and optionally free the owner.
 * @param object Owner of the attached item.
 * @param flags A positive signed 16-bit value requests freeing the owner.
 * @return The original object pointer.
 */
ConfigOwnedItem* func_00352A70(ConfigOwnedItem* object, s32 flags);

#ifdef __cplusplus
}
#endif

#endif
