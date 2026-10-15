#ifndef SO3_OVERLAYS_LIB_TEXT_0046AE20_H
#define SO3_OVERLAYS_LIB_TEXT_0046AE20_H

#include "types.h"
#include "overlays/lib/animation_binding.h"

typedef struct LibObject1751A0 LibObject1751A0;
/** Opaque owner of the runtime resource-entry table. */
typedef struct LibEntryManager LibEntryManager;
/** Opaque metadata for one resource entry. */
typedef struct LibEntryMetadata LibEntryMetadata;

#ifdef __cplusplus
extern "C" {
#endif

void func_0047A010(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8);

/** Return the mapped entry at the indexed 0x120-byte record's offset 0xF0. */
void* func_0047A860(const void* object, s32 index);
/** Clear four state bytes before updating the row through the owner. */
void func_0047A040(void* object, u8* state, void* row);

/**
 * @brief Release the grid reference held by the linked Lib object.
 * @param object Linked object holding the grid.
 */
void func_0046B3F0(LibObject1751A0* object);

/**
 * @brief Find a camera entry matching its name and state filters.
 * @param object Manager supplying the entry table.
 * @param name Entry name; null or empty accepts any name.
 * @return Matching entry handle, or null.
 */
void* lib_find_camera_entry(LibEntryManager* object, const char* name);

/**
 * @brief Find a light entry whose metadata passes the state and name filters.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching light handle, or null.
 */
void* lib_find_light_entry(LibEntryManager* manager, const char* name);

/**
 * @brief Find a named entry by searching circularly from the last successful index.
 * @param manager Runtime entry table and source metadata.
 * @param name Entry name; null returns no entry.
 * @param checksum Precomputed signed-byte name sum, or zero to calculate it from up to sixteen characters.
 * @return Matching entry handle, or null.
 */
void* lib_find_named_entry_cached(LibEntryManager* manager, const char* name, s32 checksum);

/**
 * @brief Add bits to the object's flags.
 * @param object Receiver.
 * @param flags Flag bits to add.
 */
void lib_object_add_flags(void* object, u16 flags);

/**
 * @brief Read the signed child-entry count for an indexed resource entry.
 * @param manager Runtime resource-entry manager.
 * @param index Entry index.
 * @return Signed child-entry count stored in the entry's metadata.
 */
s32 lib_get_entry_child_count(LibEntryManager* manager, s32 index);

/**
 * @brief Set resource state for eligible renderable entries.
 * @param manager Runtime resource-entry manager.
 */
void func_004724A0(LibEntryManager* manager);

/**
 * @brief Locate an entry's data after its optional sixteen-byte name.
 * @param manager Manager supplying the resource format flag.
 * @param metadata Source entry metadata.
 * @return Metadata-relative entry data, skipping the name when present.
 */
void* lib_get_entry_data(LibEntryManager* manager, LibEntryMetadata* metadata);

/**
 * @brief Update eligible renderable entries that pass the metadata flag filter.
 * @param manager Runtime resource-entry manager.
 */
void lib_update_renderable_entries(LibEntryManager* manager);

/**
 * @brief Update each active entry of the object's table with a boolean setting and an option flag.
 * @param object Object whose entry table is updated.
 * @param enable Boolean setting forwarded to each entry.
 * @param option Nonzero to select the alternate update path.
 */
void func_004728A0(void* object, s32 enable, s32 option);

/**
 * @brief Return the handle of the next table entry after entry that passes the entry state filter.
 * @param object Object whose entry table is searched.
 * @param entry Handle of the current entry.
 * @return The next entry's handle, or null if there is none.
 */
void* func_00472EB0(void* object, void* entry);

/**
 * @brief Find a renderable entry of kind 1 or 8 whose metadata passes the state and name filters.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching renderable handle, or null.
 */
void* lib_find_renderable_entry(LibEntryManager* manager, const char* name);

/**
 * @brief Find a named table entry.
 * @param object Object whose table is searched.
 * @param name Name to search; null selects the first entry with metadata.
 * @return Matching entry handle, or null.
 */
void* func_00473390(void* object, const char* name);

/** @brief Copy one aligned 16-byte value. @param output Destination value. @param input Source value. */
void func_00479090(void* output, const void* input);
/**
 * @brief Set the inherited transform dirty flag.
 * @param object Transform receiver.
 * @param value Dirty flag to store.
 */
void lib_transform_set_dirty(void* object, u8 value);

/**
 * @brief Set the primary animation link or register a supplemental link in a binding owner.
 * @param owner Binding owner.
 * @param animation Animation handle; null clears the primary link when mode is zero.
 * @param mode Zero selects the primary link; otherwise it is stored for a new supplemental link.
 */
void lib_animation_register_binding(LibAnimationBindingOwner* owner, void* animation, s32 mode);



/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A640(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A650(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A690(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A6C0(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A760(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A780(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A800(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADA0(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADB0(void* object, float value);

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADF0(void* object, float value);


/** Return the float member at receiver offset 0x30. */
float func_0047A660(void* object);

/** Return the float member at receiver offset 0x44. */
float func_0047A6D0(void* object);

/** Return the float member at receiver offset 0x28. */
float func_0047A6E0(void* object);

/** Return the float member at receiver offset 0x30. */
float func_0047ADC0(void* object);

/** Return the word at receiver offset 0x8. */
u32 func_00478F70(const void* object);
/** Return the word at receiver offset 0xC. */
u32 func_00478F80(const void* object);
/** Return the word at receiver offset 0xB8. */
u32 func_00479FE0(const void* object);
/** Return the word at receiver offset 0xBC. */
u32 func_0047A000(const void* object);
/** Return the word at receiver offset 0xB0. */
u32 func_0047A080(const void* object);
/** Return the word at receiver offset 0xB4. */
u32 func_0047A0A0(const void* object);
/** Return the word at receiver offset 0xB0. */
u32 func_0047A0C0(const void* object);
/** Return the word at receiver offset 0xB4. */
u32 func_0047A0E0(const void* object);
/** Return the word at receiver offset 0x48. */
u32 func_0047A700(const void* object);
/** Return the word at receiver offset 0x50. */
u32 func_0047A740(const void* object);


/** Store the word at receiver offset 0xB8. */
void func_00479FD0(void* object, u32 value);

/** Store the word at receiver offset 0xBC. */
void func_00479FF0(void* object, u32 value);

/** Store the word at receiver offset 0xB0. */
void func_0047A070(void* object, u32 value);

/** Store the word at receiver offset 0xB4. */
void func_0047A090(void* object, u32 value);

/** Store the word at receiver offset 0xB0. */
void func_0047A0B0(void* object, u32 value);

/** Store the word at receiver offset 0xB4. */
void func_0047A0D0(void* object, u32 value);

/** Store the word at receiver offset 0x48. */
void func_0047A6F0(void* object, u32 value);

/** Store the word at receiver offset 0x50. */
void func_0047A730(void* object, u32 value);


/** Store the byte at receiver offset 0x4D. */
void func_0047A670(void* object, u8 value);

/** Store the byte at receiver offset 0x56. */
void func_0047A6A0(void* object, u8 value);

/** Store the byte at receiver offset 0x4F. */
void func_0047A710(void* object, u8 value);

/** Store the byte at receiver offset 0x4E. */
void func_0047A720(void* object, u8 value);

/** Store the byte at receiver offset 0x55. */
void func_0047A750(void* object, u8 value);

/** Store the byte at receiver offset 0x54. */
void func_0047A770(void* object, u8 value);

/** Store the byte at receiver offset 0x4D. */
void func_0047ADD0(void* object, u8 value);

/** Store the byte at receiver offset 0x56. */
void func_0047AE00(void* object, u8 value);


/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047A680(const void* object);

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047A6B0(const void* object);

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047ADE0(const void* object);

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047AE10(const void* object);


/** Store the low halfword at receiver offset 0x6C. */
void func_00472100(void* object, u32 value);

/** Return the fixed integer value 1. */
s32 func_00479FC0(void* object);

/** Return the fixed integer value 1. */
s32 func_0047A850(void* object);

/** Return the fixed value 0. */
s32 func_00479700(void* object);

/** Return the fixed value 0. */
s32 func_00479840(void* object);

/** Return the fixed value 0. */
s32 func_00479950(void* object);

/** Return the fixed value 0. */
s32 func_004799E0(void* object);

/** Return the fixed value 0. */
s32 func_00479AF0(void* object);

/** Return the fixed value 0. */
s32 func_00479C00(void* object);

/** Return the fixed value 0. */
s32 func_00479DD0(void* object);

/** Return the fixed value 0. */
s32 func_00479E60(void* object);

/** Return the fixed value 0. */
s32 func_0047A0F0(void* object);

/** Return the fixed value 0. */
s32 func_0047A100(void* object);

/** Return the fixed value 0. */
s32 func_0047A110(void* object);

/** Return the fixed value 0. */
s32 func_0047A120(void* object);

void func_00479FB0(void* object);
void func_0047A840(void* object);

/** Return the first pointer argument unchanged. */
void* func_0046C080(void* value);

#ifdef __cplusplus
/** Store a byte source and word, then set state 0x57 from the source byte. */
void func_0047A790(void* object, const u8* source, u32 value);

/** Clear two pointer fields and set the byte at receiver offset 0x57 from enabled. */
void func_0047A7D0(void* object, s32 enabled);

/** Clear the word at receiver offset 0x2C and copy four aligned values from the source. */
void func_0047A810(void* object, const void* source);

}
#endif

/** Return the receiver address at byte offset 0x830. */
void* func_00479100(void* object);

/** Store a byte at 0x59C and set bit 0 of the byte at 0x59D. */
void func_00479160(void* object, u8 value);

#ifdef __cplusplus
extern "C" {
#endif
/** @brief Increment the byte at receiver offset 0x790. @param object Receiver containing the counter byte. */
void func_00479180(void* object);
#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
/** Partial Lib class with vtable D_175320 in main data; its destructor is func_004792A0. */
class LibClass175320
{
public:
    /** @brief Destroy the object. */
    virtual ~LibClass175320();
};
#endif

#endif
