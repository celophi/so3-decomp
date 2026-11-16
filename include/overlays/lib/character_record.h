#ifndef SO3_OVERLAYS_LIB_CHARACTER_RECORD_H
#define SO3_OVERLAYS_LIB_CHARACTER_RECORD_H

#include "types.h"
#include "clamp.h"
#include "overlays/lib/text_003F90C0.h"

/**
 * @brief Checksum the encoded battle skill indices.
 * @param indices Six encoded indices.
 * @return Checksum.
 */
static inline u32 battle_skill_indices_checksum(const u8* indices)
{
    u32 checksum = 0x8D3C43F9;
    s32 entry;

    for (entry = 0; entry < 6; entry++)
    {
        checksum ^= *indices++;
        checksum = checksum * 2 + 0x31;
    }

    return checksum;
}

/**
 * @brief Checksum an array of encoded halfwords.
 * @param data Encoded halfwords.
 * @param size Size of the array in bytes.
 * @return Checksum.
 */
static inline u32 halfwords_checksum(const s16* data, s32 size)
{
    u32 checksum = 0x8D3C43F9;
    s32 entry;

    size /= 2;

    for (entry = 0; entry < size; entry++)
    {
        checksum ^= *data++;
        checksum = checksum * 2 + 0x73;
    }

    return checksum;
}

/**
 * @brief Checksum the encoded tactical skill states.
 * @param states Seven encoded states.
 * @return Checksum.
 */
static inline u32 tactical_skill_states_checksum(const u8* states)
{
    u32 checksum = 0x8D3C43F9;
    s32 entry;

    for (entry = 0; entry < 7; entry++)
    {
        checksum ^= *states++;
        checksum = checksum * 2 + 0x31;
    }

    return checksum;
}

/**
 * @brief Checksum the encoded status skill levels.
 * @param levels Five encoded levels.
 * @return Checksum.
 */
static inline u32 status_skill_levels_checksum(const u8* levels)
{
    u32 checksum = 0x8D3C43F9;

    for (s32 entry = 0; entry < 5; entry++)
    {
        checksum ^= *levels++;
        checksum = checksum * 2 + 0x31;
    }

    return checksum;
}

/**
 * @brief Checksum the encoded luck values.
 * @param equipment Character equipment record.
 * @return Checksum.
 */
static inline u32 luck_checksum(const LibCharacterEquipment* equipment)
{
    return equipment->checksum_salt ^ (equipment->encoded_luck ^ (equipment->encoded_base_luck + equipment->encoded_effective_luck));
}

/**
 * @brief Checksum the encoded stamina values.
 * @param equipment Character equipment record.
 * @return Checksum.
 */
static inline u32 stamina_checksum(const LibCharacterEquipment* equipment)
{
    return equipment->checksum_salt ^ (equipment->encoded_stamina ^ (equipment->encoded_base_stamina + equipment->encoded_effective_stamina));
}

/**
 * @brief Checksum the encoded SP and CP.
 * @param equipment Character equipment record.
 * @return Checksum.
 */
static inline u32 sp_cp_checksum(const LibCharacterEquipment* equipment)
{
    return equipment->checksum_salt ^ (equipment->encoded_sp ^ (equipment->encoded_cp + equipment->checksum_salt));
}

/**
 * @brief Checksum the encoded levels.
 * @param record Character record.
 * @return Checksum.
 */
static inline s32 level_checksum(const LibCharacterRecord* record)
{
    return record->checksum_salt ^ (record->encoded_level ^ (record->encoded_base_level + record->checksum_salt));
}

/**
 * @brief Checksum the encoded flags and experience.
 * @param record Character record.
 * @return Checksum.
 */
static inline s32 flags_experience_checksum(const LibCharacterRecord* record)
{
    return record->checksum_salt ^ (record->encoded_experience ^ (record->encoded_flags + record->checksum_salt));
}

/**
 * @brief Checksum the encoded knockback resistance values.
 * @param record Character record.
 * @return Checksum.
 */
static inline s32 knockback_resistance_checksum(const LibCharacterRecord* record)
{
    return record->checksum_salt
         ^ (record->encoded_knockback_resistance ^ (record->encoded_base_knockback_resistance + record->encoded_effective_knockback_resistance));
}

/**
 * @brief Checksum the encoded knockback power values.
 * @param record Character record.
 * @return Checksum.
 */
static inline s32 knockback_power_checksum(const LibCharacterRecord* record)
{
    return record->checksum_salt ^ (record->encoded_knockback_power ^ (record->encoded_base_knockback_power + record->encoded_effective_knockback_power));
}

/**
 * @brief Checksum the encoded critical rates.
 * @param record Character record.
 * @return Checksum.
 */
static inline s32 critical_rate_checksum(const LibCharacterRecord* record)
{
    return record->checksum_salt ^ (record->encoded_critical_rate ^ (record->encoded_base_critical_rate + record->encoded_effective_critical_rate));
}

/**
 * @brief Checksum the encoded agility values.
 * @param record Character record.
 * @return Checksum.
 */
static inline s32 agility_checksum(const LibCharacterRecord* record)
{
    return record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility));
}

/**
 * @brief Checksum the encoded HIT values; it also protects intelligence.
 * @param record Character record.
 * @return Checksum.
 */
static inline s32 hit_checksum(const LibCharacterRecord* record)
{
    return record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit));
}

/**
 * @brief Checksum the encoded defense values.
 * @param record Character record.
 * @return Checksum.
 */
static inline s32 defense_checksum(const LibCharacterRecord* record)
{
    return record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense));
}

/**
 * @brief Checksum the encoded attack values.
 * @param record Character record.
 * @return Checksum.
 */
static inline s32 attack_checksum(const LibCharacterRecord* record)
{
    return record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack));
}

/** Protected values are limited with this bias added. */
enum
{
    LIMIT_BIAS = 32113
};

/**
 * @brief Limit a value to a range.
 * @param value Value to limit.
 * @param low Lowest allowed value.
 * @param high Highest allowed value.
 * @return Limited value.
 */
static inline s32 limit_value(s32 value, s32 low, s32 high)
{
    value += LIMIT_BIAS;
    value = clamp(value, low + LIMIT_BIAS, high + LIMIT_BIAS);
    value -= LIMIT_BIAS;
    return value;
}

/**
 * @brief Limit a stat to zero through the maximum for the record's limit type.
 * @param record Character record.
 * @param value Value to limit.
 * @param high0 Maximum for limit type zero.
 * @param high1 Maximum for limit type one.
 * @return Limited value, unchanged for other limit types.
 */
static inline s32 limit_by_type(const LibCharacterRecord* record, s32 value, s32 high0, s32 high1)
{
    value += LIMIT_BIAS;

    if (record->stat_limit_type == 0)
    {
        value = clamp(value, LIMIT_BIAS, high0 + LIMIT_BIAS);
    }

    if (record->stat_limit_type == 1)
    {
        value = clamp(value, LIMIT_BIAS, high1 + LIMIT_BIAS);
    }

    value -= LIMIT_BIAS;
    return value;
}

/**
 * @brief Limit a stat by type, only once it's past a threshold.
 *
 * The thresholds are compared with the biased value, so they let almost
 * everything through to the clamp.
 * @param record Character record.
 * @param value Value to limit.
 * @param threshold0 Threshold for limit type zero.
 * @param high0 Maximum for limit type zero.
 * @param threshold1 Threshold for limit type one.
 * @param high1 Maximum for limit type one.
 * @return Limited value.
 */
static inline s32 limit_by_type_above(const LibCharacterRecord* record, s32 value, s32 threshold0, s32 high0, s32 threshold1, s32 high1)
{
    value += LIMIT_BIAS;

    if (record->stat_limit_type == 0 && value > threshold0)
    {
        value = clamp(value, LIMIT_BIAS, high0 + LIMIT_BIAS);
    }

    if (record->stat_limit_type == 1 && value > threshold1)
    {
        value = clamp(value, LIMIT_BIAS, high1 + LIMIT_BIAS);
    }

    value -= LIMIT_BIAS;
    return value;
}

/**
 * @brief Decode luck after validating its checksum.
 * @param equipment Character equipment record.
 * @return Luck, or zero for an invalid checksum.
 */
static inline s32 equipment_luck(const LibCharacterEquipment* equipment)
{
    if (equipment->luck_checksum != (equipment->checksum_salt ^ (equipment->encoded_luck ^ (equipment->encoded_base_luck + equipment->encoded_effective_luck))))
    {
        return 0;
    }

    return equipment->encoded_luck ^ 0x7E93;
}

/**
 * @brief Store luck, limited to zero through 255 and the effective luck.
 * @param equipment Character equipment record.
 * @param luck Luck to store.
 * @return Stored luck, or zero for an invalid checksum.
 */
static inline s32 set_equipment_luck(LibCharacterEquipment* equipment, s32 luck)
{
    if (equipment->luck_checksum != (equipment->checksum_salt ^ (equipment->encoded_luck ^ (equipment->encoded_base_luck + equipment->encoded_effective_luck))))
    {
        return 0;
    }

    luck = limit_value(luck, 0, 255);

    if (luck > (equipment->encoded_effective_luck ^ 0x7E93))
    {
        luck = equipment->encoded_effective_luck ^ 0x7E93;
    }

    equipment->encoded_luck = luck ^ 0x7E93;
    equipment->luck_checksum = luck_checksum(equipment);
    return luck;
}

/**
 * @brief Decode stamina after validating its checksum.
 * @param equipment Character equipment record.
 * @return Stamina, or zero for an invalid checksum.
 */
static inline s32 equipment_stamina(const LibCharacterEquipment* equipment)
{
    if (equipment->stamina_checksum != (equipment->checksum_salt ^ (equipment->encoded_stamina ^ (equipment->encoded_base_stamina + equipment->encoded_effective_stamina))))
    {
        return 0;
    }

    return equipment->encoded_stamina ^ 0x7E93;
}

/**
 * @brief Store stamina, limited to zero through 9999 and the effective stamina.
 * @param equipment Character equipment record.
 * @param stamina Stamina to store.
 * @return Stored stamina, or zero for an invalid checksum.
 */
static inline s32 set_equipment_stamina(LibCharacterEquipment* equipment, s32 stamina)
{
    if (equipment->stamina_checksum != (equipment->checksum_salt ^ (equipment->encoded_stamina ^ (equipment->encoded_base_stamina + equipment->encoded_effective_stamina))))
    {
        return 0;
    }

    stamina = limit_value(stamina, 0, 9999);

    if (stamina > (equipment->encoded_effective_stamina ^ 0x7E93))
    {
        stamina = equipment->encoded_effective_stamina ^ 0x7E93;
    }

    equipment->encoded_stamina = stamina ^ 0x7E93;
    equipment->stamina_checksum = stamina_checksum(equipment);
    return stamina;
}

/**
 * @brief Decode the knockback resistance after validating its checksum.
 * @param record Character record.
 * @return Knockback resistance, or zero for an invalid checksum.
 */
static inline s32 character_knockback_resistance(const LibCharacterRecord* record)
{
    if (record->knockback_resistance_checksum != (record->checksum_salt ^ (record->encoded_knockback_resistance ^ (record->encoded_base_knockback_resistance + record->encoded_effective_knockback_resistance))))
    {
        return 0;
    }

    return record->encoded_knockback_resistance ^ 0x7E93;
}

/**
 * @brief Decode the knockback power after validating its checksum.
 * @param record Character record.
 * @return Knockback power, or zero for an invalid checksum.
 */
static inline s32 character_knockback_power(const LibCharacterRecord* record)
{
    if (record->knockback_power_checksum != (record->checksum_salt ^ (record->encoded_knockback_power ^ (record->encoded_base_knockback_power + record->encoded_effective_knockback_power))))
    {
        return 0;
    }

    return record->encoded_knockback_power ^ 0x7E93;
}

/**
 * @brief Decode the critical rate after validating its checksum.
 * @param record Character record.
 * @return Critical rate, or zero for an invalid checksum.
 */
static inline s32 character_critical_rate(const LibCharacterRecord* record)
{
    if (record->critical_rate_checksum != (record->checksum_salt ^ (record->encoded_critical_rate ^ (record->encoded_base_critical_rate + record->encoded_effective_critical_rate))))
    {
        return 0;
    }

    return record->encoded_critical_rate ^ 0x7E93;
}

/**
 * @brief Store the critical rate, limited to zero through 255 and the effective rate.
 * @param record Character record.
 * @param rate Critical rate to store.
 * @return Stored rate, or zero for an invalid checksum.
 */
static inline s32 set_character_critical_rate(LibCharacterRecord* record, s32 rate)
{
    if (record->critical_rate_checksum != (record->checksum_salt ^ (record->encoded_critical_rate ^ (record->encoded_base_critical_rate + record->encoded_effective_critical_rate))))
    {
        return 0;
    }

    rate = limit_value(rate, 0, 255);

    if (rate > (record->encoded_effective_critical_rate ^ 0x7E93))
    {
        rate = record->encoded_effective_critical_rate ^ 0x7E93;
    }

    record->encoded_critical_rate = rate ^ 0x7E93;
    record->critical_rate_checksum = critical_rate_checksum(record);
    return rate;
}

/**
 * @brief Decode HIT after validating its checksum.
 * @param record Character record.
 * @return HIT, or zero for an invalid checksum.
 */
static inline s32 character_hit(const LibCharacterRecord* record)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    return record->encoded_hit ^ 0x7DE3F7E3;
}

/**
 * @brief Store HIT, limited by type to 9999 and to the effective HIT.
 * @param record Character record.
 * @param hit HIT to store.
 * @return Stored HIT, or zero for an invalid checksum.
 */
static inline s32 set_character_hit(LibCharacterRecord* record, s32 hit)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    hit = limit_by_type(record, hit, 9999, 9999);

    if (hit > (record->encoded_effective_hit ^ 0x7DE3F7E3))
    {
        hit = record->encoded_effective_hit ^ 0x7DE3F7E3;
    }

    record->encoded_hit = hit ^ 0x7DE3F7E3;
    record->hit_checksum = hit_checksum(record);
    return hit;
}

/**
 * @brief Decode intelligence after validating the HIT checksum.
 * @param record Character record.
 * @return Intelligence, or zero for an invalid checksum.
 */
static inline s32 character_intelligence(const LibCharacterRecord* record)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    return record->encoded_intelligence ^ 0x7DE3F7E3;
}

/**
 * @brief Store intelligence, limited by type to 9999 and to the effective intelligence.
 * @param record Character record.
 * @param intelligence Intelligence to store.
 * @return Stored intelligence, or zero for an invalid checksum.
 */
static inline s32 set_character_intelligence(LibCharacterRecord* record, s32 intelligence)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    intelligence = limit_by_type(record, intelligence, 9999, 9999);

    if (intelligence > (record->encoded_effective_intelligence ^ 0x7DE3F7E3))
    {
        intelligence = record->encoded_effective_intelligence ^ 0x7DE3F7E3;
    }

    record->encoded_intelligence = intelligence ^ 0x7DE3F7E3;
    record->hit_checksum = hit_checksum(record);
    return intelligence;
}

/**
 * @brief Decode defense after validating its checksum.
 * @param record Character record.
 * @return Defense, or zero for an invalid checksum.
 */
static inline s32 character_defense(const LibCharacterRecord* record)
{
    if (record->defense_checksum != (record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense))))
    {
        return 0;
    }

    return record->encoded_defense ^ 0x7DE3F7E3;
}

/**
 * @brief Decode attack after validating its checksum.
 * @param record Character record.
 * @return Attack, or zero for an invalid checksum.
 */
static inline s32 character_attack(const LibCharacterRecord* record)
{
    if (record->attack_checksum != (record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack))))
    {
        return 0;
    }

    return record->encoded_attack ^ 0x7DE3F7E3;
}

/**
 * @brief Store attack, limited by type to 9999 or 99999 and to the effective attack.
 * @param record Character record.
 * @param attack Attack to store.
 * @return Stored attack, or zero for an invalid checksum.
 */
static inline s32 set_character_attack(LibCharacterRecord* record, s32 attack)
{
    if (record->attack_checksum != (record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack))))
    {
        return 0;
    }

    attack = limit_by_type(record, attack, 9999, 99999);

    if (attack > (record->encoded_effective_attack ^ 0x7DE3F7E3))
    {
        attack = record->encoded_effective_attack ^ 0x7DE3F7E3;
    }

    record->encoded_attack = attack ^ 0x7DE3F7E3;
    record->attack_checksum = attack_checksum(record);
    return attack;
}

/**
 * @brief Set flag bits after validating the flags/experience checksum.
 * @param record Character record.
 * @param bits Bits to set.
 */
static inline void add_character_flags(LibCharacterRecord* record, s32 bits)
{
    if (record->flags_experience_checksum == (record->checksum_salt ^ (record->encoded_experience ^ (record->encoded_flags + record->checksum_salt))))
    {
        record->encoded_flags = ((record->encoded_flags ^ 0x7DE3F7E3) | bits) ^ 0x7DE3F7E3;
        record->flags_experience_checksum = flags_experience_checksum(record);
    }
}

/**
 * @brief Clear flag bits after validating the flags/experience checksum.
 * @param record Character record.
 * @param bits Bits to clear.
 */
static inline void remove_character_flags(LibCharacterRecord* record, s32 bits)
{
    if (record->flags_experience_checksum == (record->checksum_salt ^ (record->encoded_experience ^ (record->encoded_flags + record->checksum_salt))))
    {
        record->encoded_flags = ((record->encoded_flags ^ 0x7DE3F7E3) & ~bits) ^ 0x7DE3F7E3;
        record->flags_experience_checksum = flags_experience_checksum(record);
    }
}

/**
 * @brief Limit a fury amount to zero through one hundred.
 * @param amount Displayed amount.
 * @return Limited amount.
 */
static inline float clamp_fury(float amount)
{
    amount *= 16.0f;
    amount = ee_max(amount, 0.0f);
    amount = ee_min(amount, 1600.0f);
    amount *= 0.0625f;
    return amount;
}

/**
 * @brief Decode the displayed fury.
 * @param record Character record.
 * @return Fury.
 */
static inline float character_fury(const LibCharacterRecord* record)
{
    return 0.0625f * record->scaled_fury;
}

/**
 * @brief Decode the displayed maximum fury.
 * @param record Character record.
 * @return Maximum fury.
 */
static inline float character_max_fury(const LibCharacterRecord* record)
{
    return 0.0625f * record->scaled_max_fury;
}

/**
 * @brief Store fury, limited to zero through the maximum.
 * @param record Character record.
 * @param fury Displayed fury.
 * @return Stored fury.
 */
static inline float set_character_fury(LibCharacterRecord* record, float fury)
{
    fury = clamp_fury(fury);

    if (!(fury <= character_max_fury(record)))
    {
        fury = character_max_fury(record);
    }

    record->scaled_fury = 16.0f * fury;
    return fury;
}

/**
 * @brief Decode the maximum MP without checking it.
 * @param record Character record.
 * @return Maximum MP.
 */
static inline s32 decoded_max_mp(const LibCharacterRecord* record)
{
    return record->encoded_max_mp ^ 0x7DE3F7E3;
}

/**
 * @brief Decode the maximum HP without checking it.
 * @param record Character record.
 * @return Maximum HP.
 */
static inline s32 decoded_max_hp(const LibCharacterRecord* record)
{
    return record->encoded_max_hp ^ 0x7DE3F7E3;
}

/**
 * @brief Read the record's checksum salt.
 * @param record Character record.
 * @return The salt.
 */
static inline u32 character_checksum_salt(const LibCharacterRecord* record)
{
    return record->checksum_salt;
}

/**
 * @brief Decode the effective agility after validating the agility checksum.
 * @param record Character record.
 * @return Effective agility, or zero for an invalid checksum.
 */
static inline s32 character_effective_agility(const LibCharacterRecord* record)
{
    if (record->agility_checksum != (record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility))))
    {
        return 0;
    }

    return record->encoded_effective_agility ^ 0x7DE3F7E3;
}

extern "C" s32 lib_character_set_effective_agility(LibCharacterRecord* record, s32 agility);
extern "C" s32 lib_character_limit_agility(const LibCharacterRecord* record, s32 agility);

// TODO: The target has this function inlined into itself once, with the
// nested limit, read and recursive call left out of line. This helper is a
// guess at that copy.

/**
 * @brief Store the effective agility through its limit function, then recurse.
 * @param record Character record.
 * @param agility Effective agility.
 * @return Stored effective agility, or zero for an invalid checksum.
 */
static inline s32 set_effective_agility_again(LibCharacterRecord* record, s32 agility)
{
    if (record->agility_checksum != (record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility))))
    {
        return 0;
    }

    agility = lib_character_limit_agility(record, agility);
    record->encoded_effective_agility = agility ^ 0x7DE3F7E3;
    record->agility_checksum = agility_checksum(record);

    if (agility < lib_character_get_effective_agility(record))
    {
        lib_character_set_effective_agility(record, agility);
    }

    return agility;
}

#endif
