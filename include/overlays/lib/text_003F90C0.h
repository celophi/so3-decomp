#ifndef SO3_OVERLAYS_LIB_TEXT_003F90C0_H
#define SO3_OVERLAYS_LIB_TEXT_003F90C0_H

#include "types.h"

/** Checksum-protected 0xC4-byte character statistics record. */
typedef struct LibCharacterRecord
{
    s16 character_id;

    /** Selects the clamping rules used by the stat setters. */
    s16 stat_limit_type;

    s16 encoded_level;
    s16 encoded_base_level;
    s32 encoded_flags;
    s32 encoded_experience;
    s32 encoded_base_hp;
    s32 encoded_max_hp;
    s32 encoded_hp;
    s32 encoded_base_mp;
    s32 encoded_max_mp;
    s32 encoded_mp;
    float unk28;

    /** Fury is stored at sixteen times its displayed amount. */
    float scaled_max_fury;

    float scaled_fury;
    s32 encoded_base_attack;
    s32 encoded_effective_attack;
    s32 encoded_attack;
    s32 encoded_base_defense;
    s32 encoded_effective_defense;
    s32 encoded_defense;
    s32 encoded_base_agility;
    s32 encoded_effective_agility;
    s32 encoded_agility;
    s32 encoded_base_hit;
    s32 encoded_effective_hit;
    s32 encoded_hit;

    /** Validated through the HIT checksum. */
    s32 encoded_base_intelligence;

    s32 encoded_effective_intelligence;
    s32 encoded_intelligence;
    s16 encoded_base_knockback_power;
    s16 encoded_effective_knockback_power;
    s16 encoded_knockback_power;
    s16 encoded_base_knockback_resistance;
    s16 encoded_effective_knockback_resistance;
    s16 encoded_knockback_resistance;
    s16 encoded_base_critical_rate;
    s16 encoded_effective_critical_rate;
    s16 encoded_critical_rate;
    s32 level_checksum;
    s32 flags_experience_checksum;
    s32 hp_checksum;
    s32 mp_checksum;
    s32 attack_checksum;
    s32 defense_checksum;
    s32 agility_checksum;
    s32 hit_checksum;
    s32 knockback_power_checksum;
    s32 checksum_salt;
    s32 critical_rate_checksum;
    s32 knockback_resistance_checksum;
    s32 unkb4[3];
    s32 unkc0;
} LibCharacterRecord;

/** Checksum-protected 0x114-byte character equipment and skill record. */
typedef struct LibCharacterEquipment
{
    s16 encoded_base_luck;
    s16 encoded_effective_luck;
    s16 encoded_luck;
    s16 encoded_base_stamina;
    s16 encoded_effective_stamina;
    s16 encoded_stamina;
    s16 encoded_equipment_slot_count;
    s16 encoded_slot_limit;
    s16 encoded_equipment_ids[4];
    s16 encoded_sp;
    s16 encoded_cp;
    u8 unk1c[4];
    char character_name[24];
    u8 battle_strategy;
    u8 previous_battle_strategy;
    u8 unk3a;
    u8 encoded_anti_attack_aura_mask;
    u8 encoded_status_skill_levels[5];
    u8 encoded_battle_skill_indices[6];
    u8 encoded_tactical_skill_states[7];
    s16 encoded_symbology_mastery[32];
    s16 encoded_battle_skill_mastery[42];

    /** Damage responses in earth, water, fire, wind order. */
    u8 elemental_damage_responses[4];

    u8 attack_element_mask;
    u8 character_resource_variant;
    u32 luck_checksum;
    u32 stamina_checksum;
    u32 equipment_checksum;
    u32 sp_cp_checksum;
    u32 symbology_mastery_checksum;
    u32 battle_skill_mastery_checksum;
    u32 tactical_skill_states_checksum;
    u32 battle_skill_indices_checksum;
    u32 status_skill_levels_checksum;
    u32 checksum_salt;
    u32 unk110;
} LibCharacterEquipment;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Decode effective agility after validating the agility checksum.
 * @param record Character record.
 * @return Effective agility, or zero for an invalid checksum.
 */
s32 func_003FF740(const LibCharacterRecord* record);

/**
 * @brief Decode HIT after validating its checksum.
 * @param record Character record.
 * @return HIT, or zero for an invalid checksum.
 */
s32 func_003FF8F0(const LibCharacterRecord* record);

/**
 * @brief Decode defense after validating its checksum.
 * @param record Character record.
 * @return Defense, or zero for an invalid checksum.
 */
s32 func_003FFAC0(const LibCharacterRecord* record);

/**
 * @brief Decode attack after validating its checksum.
 * @param record Character record.
 * @return Attack, or zero for an invalid checksum.
 */
s32 func_003FFE50(const LibCharacterRecord* record);

/**
 * @brief Decode luck after validating its checksum.
 * @param equipment Character equipment record.
 * @return Luck, or zero for an invalid checksum.
 */
s32 func_003FEFA0(const LibCharacterEquipment* equipment);

/**
 * @brief Decode stamina after validating its checksum.
 * @param equipment Character equipment record.
 * @return Stamina, or zero for an invalid checksum.
 */
s32 func_003FF0C0(const LibCharacterEquipment* equipment);

/**
 * @brief Decode knockback resistance after validating its checksum.
 * @param record Character record.
 * @return Knockback resistance, or zero for an invalid checksum.
 */
s32 func_003FF210(const LibCharacterRecord* record);

/**
 * @brief Decode knockback power after validating its checksum.
 * @param record Character record.
 * @return Knockback power, or zero for an invalid checksum.
 */
s32 func_003FF3A0(const LibCharacterRecord* record);

/**
 * @brief Decode the critical rate after validating its checksum.
 * @param record Character record.
 * @return Critical rate, or zero for an invalid checksum.
 */
s32 func_003FF500(const LibCharacterRecord* record);

/**
 * @brief Read the selected pair of scaled byte values from the Lib table.
 * @param index Signed table row, defaulting to zero outside zero through nine.
 * @param component Pair within the row, defaulting to zero outside zero through two.
 * @param first Optional destination for the first value.
 * @param second Optional destination for the second value.
 */
void func_00408600(s32 index, s32 component, float* first, float* second);

/**
 * @brief Resolve a detail entry and return its selected values.
 * @param detail Opaque detail record.
 * @param code Signed record code, from one through ten.
 * @param index Signed entry index, from zero through thirty-one.
 * @param kind Optional destination for the entry kind.
 * @param value Optional destination for the entry value.
 * @param result_index Optional destination for the result index.
 * @param remainder Optional destination for the remaining value.
 * @param mode Full-word lookup mode.
 * @return Lookup result, or zero for invalid code or index.
 */
s32 func_408EA0(void* detail, s32 code, s32 index, s32* kind, s32* value, s32* result_index, s32* remainder, s32 mode);

/**
 * @brief Resolve a protected detail entry and return its selected values.
 * @param detail Detail record containing the encoded entry arrays.
 * @param code Signed record code, from one through ten.
 * @param index Signed entry index, from zero through forty-one.
 * @param kind Optional destination for the entry kind.
 * @param value Optional destination for the entry value.
 * @param result_index Optional destination for the result index.
 * @param remainder Optional destination for the remaining value.
 * @return Signed lookup result, or zero when the entry is unavailable.
 */
s32 func_00408850(void* detail, s32 code, s32 index, s32* kind, s32* value, s32* result_index, s32* remainder);

/**
 * @brief Store the attack element mask.
 * @param equipment Character equipment record.
 * @param mask Element mask.
 */
void func_00404560(LibCharacterEquipment* equipment, u8 mask);

/**
 * @brief Store the encoded anti-attack aura mask.
 * @param equipment Character equipment record.
 * @param mask Aura mask.
 * @return mask.
 */
s32 func_00404CA0(LibCharacterEquipment* equipment, s32 mask);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
struct LibResourceRecordC4
{
    u8 data[0xC4];

#ifdef __cplusplus
    /**
     * @brief Copy a record.
     * @param other Record to copy.
     * @return This record.
     */
    LibResourceRecordC4& operator=(const LibResourceRecordC4& other);
#endif
};

struct LibResourceRecord114
{
    u8 data[0x114];

#ifdef __cplusplus
    /**
     * @brief Copy a record.
     * @param other Record to copy.
     * @return This record.
     */
    LibResourceRecord114& operator=(const LibResourceRecord114& other);
#endif
};


extern "C"
{
    void func_004076D0(LibResourceRecordC4* output, LibResourceRecord114* input, s32 flag);
}
#endif

#endif
