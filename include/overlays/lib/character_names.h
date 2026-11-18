#ifndef SO3_OVERLAYS_LIB_CHARACTER_NAMES_H
#define SO3_OVERLAYS_LIB_CHARACTER_NAMES_H

#include "types.h"

#ifdef __cplusplus
/** Character-name provider for field message and display code. */
class FieldCharacterNames
{
public:
    /**
     * @brief Get a stored character name.
     * @param index One-based character slot.
     * @return Stored name.
     */
    virtual char* get_character_name(s32 index) = 0;
};
#endif

#endif
