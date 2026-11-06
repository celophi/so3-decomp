#include "include_asm.h"
#include "clamp.h"
#include "ee.h"
#include "main/resident_00101260.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_003F90C0.h"

/** One 6-byte character table entry: four values and their checksum. */
typedef struct LibCharacterTableEntry
{
    u8 values[4];
    u16 checksum;
} LibCharacterTableEntry;

/** Experience totals per level, stored at a protected offset. */
class LibExperienceTable
{
public:
    /** @brief Build the totals at a random offset, with a slot that zeroes their sum. */
    LibExperienceTable();

    s32 totals[0x13F];
    u32 encoded_offset;
    u8 unk500[8];
};

extern u8* D_001B64E0;
extern LibCharacterTableEntry* D_001B64E8;

/** Pairs of scaled byte values, ten rows of three. */
extern u8 D_4EC260[10][3][2];

extern "C" s32 func_00456F10(void* flags, s32 bit);
extern "C" void func_00409A10(LibCharacterEquipment* equipment);

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
 * @brief Store MP, limited by type and to the maximum MP, and update the down flag.
 *
 * Flag bit 0 is set when MP or HP is zero and cleared once both are above it.
 * @param record Character record.
 * @param mp MP to store.
 * @return Stored MP, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_mp(LibCharacterRecord* record, s32 mp)
{
    if (record->mp_checksum != (record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp))))
    {
        add_character_flags(record, 1);
        return 0;
    }

    mp = limit_by_type(record, mp, 99999, 99999999);

    if (mp > (record->encoded_max_mp ^ 0x7DE3F7E3))
    {
        mp = record->encoded_max_mp ^ 0x7DE3F7E3;
    }

    if (mp == 0)
    {
        add_character_flags(record, 1);
    }

    if (mp != 0 && (record->encoded_hp ^ 0x7DE3F7E3) != 0)
    {
        remove_character_flags(record, 1);
    }

    record->encoded_mp = mp ^ 0x7DE3F7E3;
    record->mp_checksum = record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp));
    return mp;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F92F0);

/**
 * @brief Limit MP by type to 99999 or 99999999.
 * @param record Character record.
 * @param mp MP to limit.
 * @return Limited MP.
 */
extern "C" s32 lib_character_limit_mp(const LibCharacterRecord* record, s32 mp)
{
    return limit_by_type(record, mp, 99999, 99999999);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F9410);

/**
 * @brief Store HP, limited by type and to the maximum HP, and update the down flag.
 *
 * Flag bit 0 is set when HP or MP is zero and cleared once both are above it.
 * @param record Character record.
 * @param hp HP to store.
 * @return Stored HP, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_hp(LibCharacterRecord* record, s32 hp)
{
    if (record->hp_checksum != (record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp))))
    {
        add_character_flags(record, 1);
        return 0;
    }

    hp = limit_by_type(record, hp, 99999, 99999999);

    if (hp > (record->encoded_max_hp ^ 0x7DE3F7E3))
    {
        hp = record->encoded_max_hp ^ 0x7DE3F7E3;
    }

    if (hp == 0)
    {
        add_character_flags(record, 1);
    }

    if (hp != 0 && (record->encoded_mp ^ 0x7DE3F7E3) != 0)
    {
        remove_character_flags(record, 1);
    }

    record->encoded_hp = hp ^ 0x7DE3F7E3;
    record->hp_checksum = record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp));
    return hp;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F96C0);

/**
 * @brief Limit HP by type to 99999 or 99999999.
 * @param record Character record.
 * @param hp HP to limit.
 * @return Limited HP.
 */
extern "C" s32 lib_character_limit_hp(const LibCharacterRecord* record, s32 hp)
{
    return limit_by_type(record, hp, 99999, 99999999);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F97E0);

/**
 * @brief Store one of three value pairs.
 * @param object Receiver holding two arrays of three words.
 * @param index Pair index, ignored outside zero through two.
 * @param first Value for the first array.
 * @param second Value for the second array.
 */
extern "C" void func_003F9860(void* object, s32 index, s32 first, s32 second)
{
    s32* values = (s32*)object;

    if (index >= 0 && index < 3)
    {
        values[index] = first;
        values[index + 3] = second;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", lib_character_recalculate_stats);

/**
 * @brief Store luck, limited to zero through 255 and the effective luck.
 * @param equipment Character equipment record.
 * @param luck Luck to store.
 * @return Stored luck, or zero for an invalid checksum.
 */
extern "C" s32 lib_equipment_set_luck(LibCharacterEquipment* equipment, s32 luck)
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
 * @brief Decode luck after validating its checksum.
 * @param equipment Character equipment record.
 * @return Luck, or zero for an invalid checksum.
 */
s32 func_003FEFA0(const LibCharacterEquipment* equipment)
{
    if (equipment->luck_checksum != (equipment->checksum_salt ^ (equipment->encoded_luck ^ (equipment->encoded_base_luck + equipment->encoded_effective_luck))))
    {
        return 0;
    }

    return equipment->encoded_luck ^ 0x7E93;
}

/**
 * @brief Limit luck to zero through 255.
 * @param equipment Unused equipment record.
 * @param luck Luck to limit.
 * @return Limited luck.
 */
extern "C" s32 lib_equipment_limit_luck(const LibCharacterEquipment* equipment, s32 luck)
{
    return limit_value(luck, 0, 255);
}

/**
 * @brief Store stamina, limited to zero through 9999 and the effective stamina.
 * @param equipment Character equipment record.
 * @param stamina Stamina to store.
 * @return Stored stamina, or zero for an invalid checksum.
 */
extern "C" s32 lib_equipment_set_stamina(LibCharacterEquipment* equipment, s32 stamina)
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
 * @brief Decode stamina after validating its checksum.
 * @param equipment Character equipment record.
 * @return Stamina, or zero for an invalid checksum.
 */
s32 func_003FF0C0(const LibCharacterEquipment* equipment)
{
    if (equipment->stamina_checksum
        != (equipment->checksum_salt ^ (equipment->encoded_stamina ^ (equipment->encoded_base_stamina + equipment->encoded_effective_stamina))))
    {
        return 0;
    }

    return equipment->encoded_stamina ^ 0x7E93;
}

/**
 * @brief Limit stamina to zero through 9999.
 * @param equipment Unused equipment record.
 * @param stamina Stamina to limit.
 * @return Limited stamina.
 */
extern "C" s32 lib_equipment_limit_stamina(const LibCharacterEquipment* equipment, s32 stamina)
{
    return limit_value(stamina, 0, 9999);
}

/**
 * @brief Store the knockback resistance, limited by type to 255 and to the effective resistance.
 * @param record Character record.
 * @param resistance Knockback resistance to store.
 * @return Stored resistance, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_knockback_resistance(LibCharacterRecord* record, s32 resistance)
{
    if (record->knockback_resistance_checksum != (record->checksum_salt ^ (record->encoded_knockback_resistance ^ (record->encoded_base_knockback_resistance + record->encoded_effective_knockback_resistance))))
    {
        return 0;
    }

    resistance = limit_by_type(record, resistance, 255, 255);

    if (resistance > (record->encoded_effective_knockback_resistance ^ 0x7E93))
    {
        resistance = record->encoded_effective_knockback_resistance ^ 0x7E93;
    }

    record->encoded_knockback_resistance = resistance ^ 0x7E93;
    record->knockback_resistance_checksum = knockback_resistance_checksum(record);
    return resistance;
}

/**
 * @brief Decode knockback resistance after validating its checksum.
 * @param record Character record.
 * @return Knockback resistance, or zero for an invalid checksum.
 */
s32 func_003FF210(const LibCharacterRecord* record)
{
    if (record->knockback_resistance_checksum
        != (record->checksum_salt
            ^ (record->encoded_knockback_resistance ^ (record->encoded_base_knockback_resistance + record->encoded_effective_knockback_resistance))))
    {
        return 0;
    }

    return record->encoded_knockback_resistance ^ 0x7E93;
}

/**
 * @brief Limit the knockback resistance by type to 255.
 * @param record Character record.
 * @param resistance Knockback resistance to limit.
 * @return Limited resistance.
 */
extern "C" s32 lib_character_limit_knockback_resistance(const LibCharacterRecord* record, s32 resistance)
{
    return limit_by_type(record, resistance, 255, 255);
}

/**
 * @brief Store the knockback power, limited by type to 255 and to the effective power.
 * @param record Character record.
 * @param power Knockback power to store.
 * @return Stored power, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_knockback_power(LibCharacterRecord* record, s32 power)
{
    if (record->knockback_power_checksum != (record->checksum_salt ^ (record->encoded_knockback_power ^ (record->encoded_base_knockback_power + record->encoded_effective_knockback_power))))
    {
        return 0;
    }

    power = limit_by_type(record, power, 255, 255);

    if (power > (record->encoded_effective_knockback_power ^ 0x7E93))
    {
        power = record->encoded_effective_knockback_power ^ 0x7E93;
    }

    record->encoded_knockback_power = power ^ 0x7E93;
    record->knockback_power_checksum = knockback_power_checksum(record);
    return power;
}

/**
 * @brief Decode knockback power after validating its checksum.
 * @param record Character record.
 * @return Knockback power, or zero for an invalid checksum.
 */
s32 func_003FF3A0(const LibCharacterRecord* record)
{
    if (record->knockback_power_checksum
        != (record->checksum_salt ^ (record->encoded_knockback_power ^ (record->encoded_base_knockback_power + record->encoded_effective_knockback_power))))
    {
        return 0;
    }

    return record->encoded_knockback_power ^ 0x7E93;
}

/**
 * @brief Limit the knockback power by type to 255.
 * @param record Character record.
 * @param power Knockback power to limit.
 * @return Limited power.
 */
extern "C" s32 lib_character_limit_knockback_power(const LibCharacterRecord* record, s32 power)
{
    return limit_by_type(record, power, 255, 255);
}

/**
 * @brief Store the critical rate, limited to zero through 255 and the effective rate.
 * @param record Character record.
 * @param rate Critical rate to store.
 * @return Stored rate, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_critical_rate(LibCharacterRecord* record, s32 rate)
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
 * @brief Decode the critical rate after validating its checksum.
 * @param record Character record.
 * @return Critical rate, or zero for an invalid checksum.
 */
s32 func_003FF500(const LibCharacterRecord* record)
{
    if (record->critical_rate_checksum
        != (record->checksum_salt ^ (record->encoded_critical_rate ^ (record->encoded_base_critical_rate + record->encoded_effective_critical_rate))))
    {
        return 0;
    }

    return record->encoded_critical_rate ^ 0x7E93;
}

/**
 * @brief Limit the critical rate to zero through 255.
 * @param record Unused character record.
 * @param rate Critical rate to limit.
 * @return Limited rate.
 */
extern "C" s32 lib_character_limit_critical_rate(const LibCharacterRecord* record, s32 rate)
{
    return limit_value(rate, 0, 255);
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

    if (agility < func_003FF740(record))
    {
        lib_character_set_effective_agility(record, agility);
    }

    return agility;
}

/**
 * @brief Store the effective agility, limited by type to 9999.
 *
 * It then compares the new value with the effective agility it just stored, so
 * the recursive step never runs.
 * @param record Character record.
 * @param agility Effective agility.
 * @return Stored effective agility, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_effective_agility(LibCharacterRecord* record, s32 agility)
{
    if (record->agility_checksum != (record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility))))
    {
        return 0;
    }

    agility = limit_by_type(record, agility, 9999, 9999);
    record->encoded_effective_agility = agility ^ 0x7DE3F7E3;
    record->agility_checksum = agility_checksum(record);

    if (agility < character_effective_agility(record))
    {
        set_effective_agility_again(record, agility);
    }

    return agility;
}

/**
 * @brief Decode effective agility after validating the agility checksum.
 * @param record Character record.
 * @return Effective agility, or zero for an invalid checksum.
 */
s32 func_003FF740(const LibCharacterRecord* record)
{
    u32 check = record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility));

    if (record->agility_checksum != check)
    {
        return 0;
    }

    return record->encoded_effective_agility ^ 0x7DE3F7E3;
}

/**
 * @brief Limit agility by type to 9999.
 * @param record Character record.
 * @param agility Agility to limit.
 * @return Limited agility.
 */
extern "C" s32 lib_character_limit_agility(const LibCharacterRecord* record, s32 agility)
{
    return limit_by_type(record, agility, 9999, 9999);
}

/**
 * @brief Store HIT, limited by type to 9999 and to the effective HIT.
 * @param record Character record.
 * @param hit HIT to store.
 * @return Stored HIT, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_hit(LibCharacterRecord* record, s32 hit)
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
 * @brief Decode HIT after validating its checksum.
 * @param record Character record.
 * @return HIT, or zero for an invalid checksum.
 */
s32 func_003FF8F0(const LibCharacterRecord* record)
{
    u32 check = record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit));

    if (record->hit_checksum != check)
    {
        return 0;
    }

    return record->encoded_hit ^ 0x7DE3F7E3;
}

/**
 * @brief Limit HIT by type to 9999.
 * @param record Character record.
 * @param hit HIT to limit.
 * @return Limited HIT.
 */
extern "C" s32 lib_character_limit_hit(const LibCharacterRecord* record, s32 hit)
{
    return limit_by_type(record, hit, 9999, 9999);
}

/**
 * @brief Store defense, limited by type to 9999 or 99999 and to the effective defense.
 * @param record Character record.
 * @param defense Defense to store.
 * @return Stored defense, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_defense(LibCharacterRecord* record, s32 defense)
{
    if (record->defense_checksum != (record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense))))
    {
        return 0;
    }

    defense = limit_by_type_above(record, defense, 9999, 9999, 99999, 99999);

    if (defense > (record->encoded_effective_defense ^ 0x7DE3F7E3))
    {
        defense = record->encoded_effective_defense ^ 0x7DE3F7E3;
    }

    record->encoded_defense = defense ^ 0x7DE3F7E3;
    record->defense_checksum = defense_checksum(record);
    return defense;
}

/**
 * @brief Decode defense after validating its checksum.
 * @param record Character record.
 * @return Defense, or zero for an invalid checksum.
 */
s32 func_003FFAC0(const LibCharacterRecord* record)
{
    u32 check = record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense));

    if (record->defense_checksum != check)
    {
        return 0;
    }

    return record->encoded_defense ^ 0x7DE3F7E3;
}

/**
 * @brief Limit defense by type to 9999 or 99999.
 * @param record Character record.
 * @param defense Defense to limit.
 * @return Limited defense.
 */
extern "C" s32 lib_character_limit_defense(const LibCharacterRecord* record, s32 defense)
{
    return limit_by_type_above(record, defense, 9999, 9999, 99999, 99999);
}

/**
 * @brief Store intelligence, limited by type to 9999 and to the effective intelligence.
 * @param record Character record.
 * @param intelligence Intelligence to store.
 * @return Stored intelligence, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_intelligence(LibCharacterRecord* record, s32 intelligence)
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
 * @brief Decode intelligence after validating the HIT checksum.
 * @param record Character record.
 * @return Intelligence, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_get_intelligence(const LibCharacterRecord* record)
{
    u32 check = record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit));

    if (record->hit_checksum != check)
    {
        return 0;
    }

    return record->encoded_intelligence ^ 0x7DE3F7E3;
}

/**
 * @brief Limit intelligence by type to 9999.
 * @param record Character record.
 * @param intelligence Intelligence to limit.
 * @return Limited intelligence.
 */
extern "C" s32 lib_character_limit_intelligence(const LibCharacterRecord* record, s32 intelligence)
{
    return limit_by_type(record, intelligence, 9999, 9999);
}

/**
 * @brief Store attack, limited by type to 9999 or 99999 and to the effective attack.
 * @param record Character record.
 * @param attack Attack to store.
 * @return Stored attack, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_attack(LibCharacterRecord* record, s32 attack)
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
 * @brief Decode attack after validating its checksum.
 * @param record Character record.
 * @return Attack, or zero for an invalid checksum.
 */
s32 func_003FFE50(const LibCharacterRecord* record)
{
    u32 check = record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack));

    if (record->attack_checksum != check)
    {
        return 0;
    }

    return record->encoded_attack ^ 0x7DE3F7E3;
}

/**
 * @brief Limit attack by type to 9999 or 99999.
 * @param record Character record.
 * @param attack Attack to limit.
 * @return Limited attack.
 */
extern "C" s32 lib_character_limit_attack(const LibCharacterRecord* record, s32 attack)
{
    return limit_by_type(record, attack, 9999, 99999);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FFF10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00400350);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004005C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00400830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00401780);

/**
 * @brief Return the experience still needed to reach a level.
 * @param table Experience table.
 * @param level Target level.
 * @param record Character record.
 * @param total Optional destination for the level's experience total.
 * @return Remaining experience, zero below level two, or 999999999 from level 256.
 */
extern "C" s32 func_004028C0(LibExperienceTable* table, s32 level, LibCharacterRecord* record, s32* total)
{
    u8 out_of_range = 0;
    s32 result;
    s32* totals;
    s32 experience;

    // TODO: The level and result look biased like the protected counters (257
    // and 3275); this is the only shape I've found that keeps both biases.
    if (level + 257 < 259)
    {
        result = 3275;
        out_of_range = 1;
    }

    if (level + 257 >= 513)
    {
        out_of_range = 1;
        result = 999999999 + 3275;
    }

    if (out_of_range)
    {
        if (total != 0)
        {
            *total = result - 3275;
        }

        return result - 3275;
    }

    totals = &table->totals[table->encoded_offset ^ 0x400013B];

    if (total != 0)
    {
        *total = totals[level - 2];
    }

    if (record->flags_experience_checksum != (record->checksum_salt ^ (record->encoded_experience ^ (record->encoded_flags + record->checksum_salt))))
    {
        experience = 0;
    }
    else
    {
        experience = record->encoded_experience ^ 0x7DE3F7E3;
    }

    return totals[level - 2] - experience;
}

/**
 * @brief Build the experience totals for levels one through 254.
 *
 * They start at a random offset, and a randomly placed slot after them holds
 * the negated sum of the whole array.
 */
LibExperienceTable::LibExperienceTable()
{
    s32 total = 0;
    s32 offset = resident_random_below(58);
    s32* entry = &totals[offset];

    for (s32 level = 1; level < 255; level++)
    {
        // TODO: This is level < 100 with a bias, like the level checks in
        // func_004028C0; written plainly the bias folds away.
        if (level + 4328 < 4428)
        {
            total += ((level - 1) / 10 + 5) * (level * level + 1);
        }
        else
        {
            total += (level * level + 1) * 15;
        }

        *entry++ = total;
    }

    entry += resident_random_below(4);
    *entry = 0;

    s32 sum = 0;

    for (s32 i = 0; i < 0x13F; i++)
    {
        sum += totals[i];
    }

    *entry = -sum;
    encoded_offset = offset ^ 0x400013B;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00402B30);

/**
 * @brief Store the attack element mask.
 * @param equipment Character equipment record.
 * @param mask Element mask.
 */
void func_00404560(LibCharacterEquipment* equipment, u8 mask)
{
    equipment->attack_element_mask = mask;
}

/**
 * @brief Store one elemental damage response.
 * @param equipment Character equipment record.
 * @param element Element index, ignored outside zero through three.
 * @param response Damage response.
 */
extern "C" void lib_equipment_set_elemental_response(LibCharacterEquipment* equipment, s32 element, u8 response)
{
    if (element < 0 || element >= 4)
    {
        return;
    }

    equipment->elemental_damage_responses[element] = response;
}

/**
 * @brief Store a battle skill mastery, limited to 0 through 9999, after validating the mastery checksum.
 * @param equipment Character equipment record.
 * @param index Skill index, from zero through 41.
 * @param mastery Mastery to store.
 * @return Stored mastery, or -1 for an invalid checksum or index.
 */
extern "C" s32 lib_equipment_set_battle_skill_mastery(LibCharacterEquipment* equipment, s32 index, s32 mastery)
{
    if (equipment->battle_skill_mastery_checksum != halfwords_checksum(equipment->encoded_battle_skill_mastery, sizeof(equipment->encoded_battle_skill_mastery)))
    {
        return -1;
    }

    if (index < 0)
    {
        return -1;
    }

    if ((u32)index >= 42)
    {
        return -1;
    }

    if (mastery < 0)
    {
        mastery = 0;
    }

    if (mastery > 9999)
    {
        mastery = 9999;
    }

    equipment->encoded_battle_skill_mastery[index] = mastery ^ 0x7E93;
    equipment->battle_skill_mastery_checksum = halfwords_checksum(equipment->encoded_battle_skill_mastery, sizeof(equipment->encoded_battle_skill_mastery));
    return mastery;
}

/**
 * @brief Store a symbology mastery, limited to -9999 through 9999, after validating the mastery checksum.
 * @param equipment Character equipment record.
 * @param index Symbology index, from zero through 31.
 * @param mastery Mastery to store.
 * @return Stored mastery, zero for an invalid checksum, or -1 for an invalid index.
 */
extern "C" s32 lib_equipment_set_symbology_mastery(LibCharacterEquipment* equipment, s32 index, s32 mastery)
{
    if (equipment->symbology_mastery_checksum != halfwords_checksum(equipment->encoded_symbology_mastery, sizeof(equipment->encoded_symbology_mastery)))
    {
        return 0;
    }

    if (index < 0)
    {
        return -1;
    }

    if ((u32)index >= 32)
    {
        return -1;
    }

    mastery = limit_value(mastery, -9999, 9999);
    equipment->encoded_symbology_mastery[index] = mastery ^ 0x7E93;
    equipment->symbology_mastery_checksum = halfwords_checksum(equipment->encoded_symbology_mastery, sizeof(equipment->encoded_symbology_mastery));
    return mastery;
}

/**
 * @brief Store a tactical skill state after validating the state checksum.
 * @param equipment Character equipment record.
 * @param index State index, from zero through six.
 * @param state State to store.
 * @return state, zero for an invalid checksum, or -1 for an invalid index.
 */
extern "C" s32 lib_equipment_set_tactical_skill_state(LibCharacterEquipment* equipment, s32 index, s32 state)
{
    if (equipment->tactical_skill_states_checksum != tactical_skill_states_checksum(equipment->encoded_tactical_skill_states))
    {
        return 0;
    }

    if (index < 0)
    {
        return -1;
    }

    if ((u32)index >= 7)
    {
        return -1;
    }

    equipment->encoded_tactical_skill_states[index] = state ^ 0x77;
    equipment->tactical_skill_states_checksum = tactical_skill_states_checksum(equipment->encoded_tactical_skill_states);
    return state;
}

/**
 * @brief Clear a battle skill index after validating the index checksum.
 * @param equipment Character equipment record.
 * @param index Entry index, from zero through five.
 */
extern "C" void lib_equipment_clear_battle_skill_index(LibCharacterEquipment* equipment, s32 index)
{
    // TODO: Indices from six up get through. This reads index < 0 && index >= 6
    // where the other setters reject either, which looks like a bug in the game.
    if (index < 0 && (u32)index >= 6)
    {
        return;
    }

    if (equipment->battle_skill_indices_checksum != battle_skill_indices_checksum(equipment->encoded_battle_skill_indices))
    {
        return;
    }

    equipment->encoded_battle_skill_indices[index] = 0 ^ 0x77;
    equipment->battle_skill_indices_checksum = battle_skill_indices_checksum(equipment->encoded_battle_skill_indices);
}

/**
 * @brief Store a status skill level, limited to zero through ten, after validating the level checksum.
 * @param equipment Character equipment record.
 * @param index Skill index, from zero through four.
 * @param level Level to store.
 * @return Stored level, zero for an invalid checksum, or -1 for an invalid index.
 */
extern "C" s32 lib_equipment_set_status_skill_level(LibCharacterEquipment* equipment, s32 index, s32 level)
{
    if (equipment->status_skill_levels_checksum != status_skill_levels_checksum(equipment->encoded_status_skill_levels))
    {
        return 0;
    }

    if (index < 0)
    {
        return -1;
    }

    if ((u32)index >= 5)
    {
        return -1;
    }

    level = limit_value(level, 0, 10);
    equipment->encoded_status_skill_levels[index] = level ^ 0x77;
    equipment->status_skill_levels_checksum = status_skill_levels_checksum(equipment->encoded_status_skill_levels);
    return level;
}

/**
 * @brief Store the encoded anti-attack aura mask.
 * @param equipment Character equipment record.
 * @param mask Aura mask.
 * @return mask.
 */
s32 func_00404CA0(LibCharacterEquipment* equipment, s32 mask)
{
    equipment->encoded_anti_attack_aura_mask = (u8)mask ^ 0x77;
    return mask;
}

/**
 * @brief Store the byte at offset 0x3A.
 * @param equipment Character equipment record.
 * @param value Byte value.
 * @return value.
 */
extern "C" s32 func_00404CC0(LibCharacterEquipment* equipment, s32 value)
{
    equipment->unk3a = value;
    return value;
}

/**
 * @brief Store the previous battle strategy.
 * @param equipment Character equipment record.
 * @param strategy Battle strategy.
 * @return strategy.
 */
extern "C" s32 func_00404CD0(LibCharacterEquipment* equipment, s32 strategy)
{
    equipment->previous_battle_strategy = strategy;
    return strategy;
}

/**
 * @brief Store the battle strategy.
 * @param equipment Character equipment record.
 * @param strategy Battle strategy.
 * @return strategy.
 */
extern "C" s32 func_00404CE0(LibCharacterEquipment* equipment, s32 strategy)
{
    equipment->battle_strategy = strategy;
    return strategy;
}

/**
 * @brief Store the encoded base MP.
 * @param record Character record.
 * @param base_mp Base MP.
 * @return base_mp.
 */
extern "C" s32 lib_character_set_base_mp(LibCharacterRecord* record, s32 base_mp)
{
    record->encoded_base_mp = base_mp ^ 0x7DE3F7E3;
    return base_mp;
}

/**
 * @brief Store CP, limited to zero through fifteen, after validating the SP/CP checksum.
 * @param equipment Character equipment record.
 * @param cp CP to store.
 */
extern "C" void lib_equipment_set_cp(LibCharacterEquipment* equipment, s32 cp)
{
    if (equipment->sp_cp_checksum == (equipment->checksum_salt ^ (equipment->encoded_sp ^ (equipment->encoded_cp + equipment->checksum_salt))))
    {
        cp = limit_value(cp, 0, 15);
        equipment->encoded_cp = cp ^ 0x7E93;
        equipment->sp_cp_checksum = sp_cp_checksum(equipment);
    }
}

/**
 * @brief Store SP, limited to zero through 9999, after validating the SP/CP checksum.
 * @param equipment Character equipment record.
 * @param sp SP to store.
 * @return Stored SP, or zero for an invalid checksum.
 */
extern "C" s32 lib_equipment_set_sp(LibCharacterEquipment* equipment, s32 sp)
{
    if (equipment->sp_cp_checksum != (equipment->checksum_salt ^ (equipment->encoded_sp ^ (equipment->encoded_cp + equipment->checksum_salt))))
    {
        return 0;
    }

    sp = limit_value(sp, 0, 9999);
    equipment->encoded_sp = sp ^ 0x7E93;
    equipment->sp_cp_checksum = sp_cp_checksum(equipment);
    return sp;
}

/**
 * @brief Store an equipped item after validating the equipment checksum.
 * @param equipment Character equipment record.
 * @param slot Slot index, from zero through the slot limit.
 * @param item_id Item ID.
 * @return item_id, or zero for an invalid checksum or slot.
 */
extern "C" s32 lib_equipment_set_equipment_id(LibCharacterEquipment* equipment, s32 slot, s32 item_id)
{
    if (equipment->equipment_checksum
        != (equipment->checksum_salt ^ ((equipment->encoded_equipment_ids[1] + equipment->encoded_equipment_ids[2]) ^ (equipment->encoded_equipment_ids[3] + equipment->encoded_equipment_ids[0]))))
    {
        return 0;
    }

    if (slot < 0)
    {
        return 0;
    }

    if (slot > (equipment->encoded_slot_limit ^ 0x7E93))
    {
        return 0;
    }

    equipment->encoded_equipment_ids[slot] = (s16)item_id ^ 0x7E93;
    equipment->equipment_checksum =
        equipment->checksum_salt ^ ((equipment->encoded_equipment_ids[1] + equipment->encoded_equipment_ids[2]) ^ (equipment->encoded_equipment_ids[3] + equipment->encoded_equipment_ids[0]));
    return item_id;
}

/**
 * @brief Store the slot limit, limited to one through four.
 * @param equipment Character equipment record.
 * @param limit Slot limit.
 * @return Stored slot limit.
 */
extern "C" s32 lib_equipment_set_slot_limit(LibCharacterEquipment* equipment, s32 limit)
{
    if (limit <= 0)
    {
        limit = 1;
    }

    if (limit > 4)
    {
        limit = 4;
    }

    equipment->encoded_slot_limit = limit ^ 0x7E93;
    return equipment->encoded_slot_limit ^ 0x7E93;
}

/**
 * @brief Store the equipment slot count, limited to one through four.
 * @param equipment Character equipment record.
 * @param count Slot count.
 * @return Stored slot count.
 */
extern "C" s32 lib_equipment_set_slot_count(LibCharacterEquipment* equipment, s32 count)
{
    if (count <= 0)
    {
        count = 1;
    }

    if (count > 4)
    {
        count = 4;
    }

    equipment->encoded_equipment_slot_count = count ^ 0x7E93;
    return equipment->encoded_equipment_slot_count ^ 0x7E93;
}

/**
 * @brief Store the effective stamina, limited to zero through 9999, and lower the stamina to it.
 * @param equipment Character equipment record.
 * @param stamina Effective stamina.
 * @return Stored effective stamina, or zero for an invalid checksum.
 */
extern "C" s32 lib_equipment_set_effective_stamina(LibCharacterEquipment* equipment, s32 stamina)
{
    if (equipment->stamina_checksum != (equipment->checksum_salt ^ (equipment->encoded_stamina ^ (equipment->encoded_base_stamina + equipment->encoded_effective_stamina))))
    {
        return 0;
    }

    stamina = limit_value(stamina, 0, 9999);
    equipment->encoded_effective_stamina = stamina ^ 0x7E93;

    // The checksum isn't updated until afterwards, so this read and store
    // always see a bad checksum when the effective stamina changed.
    if ((equipment->encoded_effective_stamina ^ 0x7E93) < equipment_stamina(equipment))
    {
        set_equipment_stamina(equipment, equipment->encoded_effective_stamina ^ 0x7E93);
    }

    equipment->stamina_checksum = stamina_checksum(equipment);
    return stamina;
}

/**
 * @brief Store the base stamina, limited to zero through 9999.
 * @param equipment Character equipment record.
 * @param stamina Base stamina.
 * @return Stored base stamina, or zero for an invalid checksum.
 */
extern "C" s32 lib_equipment_set_base_stamina(LibCharacterEquipment* equipment, s32 stamina)
{
    if (equipment->stamina_checksum != (equipment->checksum_salt ^ (equipment->encoded_stamina ^ (equipment->encoded_base_stamina + equipment->encoded_effective_stamina))))
    {
        return 0;
    }

    stamina = limit_value(stamina, 0, 9999);
    equipment->encoded_base_stamina = stamina ^ 0x7E93;
    equipment->stamina_checksum = stamina_checksum(equipment);
    return stamina;
}

/**
 * @brief Store the effective luck, limited to zero through 255, and lower the luck to it.
 * @param equipment Character equipment record.
 * @param luck Effective luck.
 * @return Stored effective luck, or zero for an invalid checksum.
 */
extern "C" s32 lib_equipment_set_effective_luck(LibCharacterEquipment* equipment, s32 luck)
{
    if (equipment->luck_checksum != (equipment->checksum_salt ^ (equipment->encoded_luck ^ (equipment->encoded_base_luck + equipment->encoded_effective_luck))))
    {
        return 0;
    }

    luck = limit_value(luck, 0, 255);
    equipment->encoded_effective_luck = luck ^ 0x7E93;
    equipment->luck_checksum = luck_checksum(equipment);

    if (luck < equipment_luck(equipment))
    {
        set_equipment_luck(equipment, luck);
    }

    return luck;
}

/**
 * @brief Store the base luck, limited to zero through 255.
 * @param equipment Character equipment record.
 * @param luck Base luck.
 * @return Stored base luck, or zero for an invalid checksum.
 */
extern "C" s32 lib_equipment_set_base_luck(LibCharacterEquipment* equipment, s32 luck)
{
    if (equipment->luck_checksum != (equipment->checksum_salt ^ (equipment->encoded_luck ^ (equipment->encoded_base_luck + equipment->encoded_effective_luck))))
    {
        return 0;
    }

    luck = limit_value(luck, 0, 255);
    equipment->encoded_base_luck = luck ^ 0x7E93;
    equipment->luck_checksum = luck_checksum(equipment);
    return luck;
}

/**
 * @brief Checksum a byte array.
 * @param object Unused receiver.
 * @param data Bytes to checksum.
 * @param count Number of bytes.
 * @return Checksum.
 */
extern "C" u32 func_00405440(void* object, const u8* data, s32 count)
{
    u32 checksum = 0x8D3C43F9;
    s32 i;

    for (i = 0; i < count; i++)
    {
        checksum ^= *data++;
        checksum = checksum * 2 + 0x31;
    }

    return checksum;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405530);

/**
 * @brief Store the base critical rate, limited to zero through 255.
 * @param record Character record.
 * @param rate Base critical rate.
 * @return Stored base rate, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_base_critical_rate(LibCharacterRecord* record, s32 rate)
{
    if (record->critical_rate_checksum != (record->checksum_salt ^ (record->encoded_critical_rate ^ (record->encoded_base_critical_rate + record->encoded_effective_critical_rate))))
    {
        return 0;
    }

    rate = limit_value(rate, 0, 255);
    record->encoded_base_critical_rate = rate ^ 0x7E93;
    record->critical_rate_checksum = critical_rate_checksum(record);
    return rate;
}

/**
 * @brief Store the effective critical rate, limited to zero through 255, and lower the critical rate to it.
 * @param record Character record.
 * @param rate Effective critical rate.
 * @return Stored effective rate, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_effective_critical_rate(LibCharacterRecord* record, s32 rate)
{
    if (record->critical_rate_checksum != (record->checksum_salt ^ (record->encoded_critical_rate ^ (record->encoded_base_critical_rate + record->encoded_effective_critical_rate))))
    {
        return 0;
    }

    rate = limit_value(rate, 0, 255);
    record->encoded_effective_critical_rate = rate ^ 0x7E93;
    record->critical_rate_checksum = critical_rate_checksum(record);

    if (rate < character_critical_rate(record))
    {
        set_character_critical_rate(record, rate);
    }

    return rate;
}

// TODO: The effective setters for knockback and defense call the limit
// function where the plain setters (and the HIT, attack and critical rate
// ones) inline it. These helpers are a guess that gives both; I haven't found
// one setter shape that does.

/**
 * @brief Store the knockback resistance through its limit function.
 * @param record Character record.
 * @param resistance Knockback resistance to store.
 * @return Stored resistance, or zero for an invalid checksum.
 */
static inline s32 lower_knockback_resistance(LibCharacterRecord* record, s32 resistance)
{
    if (record->knockback_resistance_checksum != (record->checksum_salt ^ (record->encoded_knockback_resistance ^ (record->encoded_base_knockback_resistance + record->encoded_effective_knockback_resistance))))
    {
        return 0;
    }

    resistance = lib_character_limit_knockback_resistance(record, resistance);

    if (resistance > (record->encoded_effective_knockback_resistance ^ 0x7E93))
    {
        resistance = record->encoded_effective_knockback_resistance ^ 0x7E93;
    }

    record->encoded_knockback_resistance = resistance ^ 0x7E93;
    record->knockback_resistance_checksum = knockback_resistance_checksum(record);
    return resistance;
}

/**
 * @brief Store the knockback power through its limit function.
 * @param record Character record.
 * @param power Knockback power to store.
 * @return Stored power, or zero for an invalid checksum.
 */
static inline s32 lower_knockback_power(LibCharacterRecord* record, s32 power)
{
    if (record->knockback_power_checksum != (record->checksum_salt ^ (record->encoded_knockback_power ^ (record->encoded_base_knockback_power + record->encoded_effective_knockback_power))))
    {
        return 0;
    }

    power = lib_character_limit_knockback_power(record, power);

    if (power > (record->encoded_effective_knockback_power ^ 0x7E93))
    {
        power = record->encoded_effective_knockback_power ^ 0x7E93;
    }

    record->encoded_knockback_power = power ^ 0x7E93;
    record->knockback_power_checksum = knockback_power_checksum(record);
    return power;
}

/**
 * @brief Store defense through its limit function.
 * @param record Character record.
 * @param defense Defense to store.
 * @return Stored defense, or zero for an invalid checksum.
 */
static inline s32 lower_defense(LibCharacterRecord* record, s32 defense)
{
    if (record->defense_checksum != (record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense))))
    {
        return 0;
    }

    defense = lib_character_limit_defense(record, defense);

    if (defense > (record->encoded_effective_defense ^ 0x7DE3F7E3))
    {
        defense = record->encoded_effective_defense ^ 0x7DE3F7E3;
    }

    record->encoded_defense = defense ^ 0x7DE3F7E3;
    record->defense_checksum = defense_checksum(record);
    return defense;
}

/**
 * @brief Store the effective knockback resistance, limited by type to 255, and lower the resistance to it.
 * @param record Character record.
 * @param resistance Effective knockback resistance.
 * @return Stored effective resistance, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_effective_knockback_resistance(LibCharacterRecord* record, s32 resistance)
{
    if (record->knockback_resistance_checksum != (record->checksum_salt ^ (record->encoded_knockback_resistance ^ (record->encoded_base_knockback_resistance + record->encoded_effective_knockback_resistance))))
    {
        return 0;
    }

    resistance = limit_by_type(record, resistance, 255, 255);
    record->encoded_effective_knockback_resistance = resistance ^ 0x7E93;
    record->knockback_resistance_checksum = knockback_resistance_checksum(record);

    if (resistance < character_knockback_resistance(record))
    {
        lower_knockback_resistance(record, resistance);
    }

    return resistance;
}

/**
 * @brief Store the base knockback resistance, limited by type to 255.
 * @param record Character record.
 * @param resistance Base knockback resistance.
 * @return Stored base resistance, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_base_knockback_resistance(LibCharacterRecord* record, s32 resistance)
{
    if (record->knockback_resistance_checksum != (record->checksum_salt ^ (record->encoded_knockback_resistance ^ (record->encoded_base_knockback_resistance + record->encoded_effective_knockback_resistance))))
    {
        return 0;
    }

    resistance = limit_by_type(record, resistance, 255, 255);
    record->encoded_base_knockback_resistance = resistance ^ 0x7E93;
    record->knockback_resistance_checksum = knockback_resistance_checksum(record);
    return resistance;
}

/**
 * @brief Store the effective knockback power, limited by type to 255, and lower the power to it.
 * @param record Character record.
 * @param power Effective knockback power.
 * @return Stored effective power, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_effective_knockback_power(LibCharacterRecord* record, s32 power)
{
    if (record->knockback_power_checksum != (record->checksum_salt ^ (record->encoded_knockback_power ^ (record->encoded_base_knockback_power + record->encoded_effective_knockback_power))))
    {
        return 0;
    }

    power = limit_by_type(record, power, 255, 255);
    record->encoded_effective_knockback_power = power ^ 0x7E93;
    record->knockback_power_checksum = knockback_power_checksum(record);

    if (power < character_knockback_power(record))
    {
        lower_knockback_power(record, power);
    }

    return power;
}

/**
 * @brief Store the base knockback power, limited by type to 255.
 * @param record Character record.
 * @param power Base knockback power.
 * @return Stored base power, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_base_knockback_power(LibCharacterRecord* record, s32 power)
{
    if (record->knockback_power_checksum != (record->checksum_salt ^ (record->encoded_knockback_power ^ (record->encoded_base_knockback_power + record->encoded_effective_knockback_power))))
    {
        return 0;
    }

    power = limit_by_type(record, power, 255, 255);
    record->encoded_base_knockback_power = power ^ 0x7E93;
    record->knockback_power_checksum = knockback_power_checksum(record);
    return power;
}

/**
 * @brief Store the effective intelligence, limited by type to 9999, and lower the intelligence to it.
 * @param record Character record.
 * @param intelligence Effective intelligence.
 * @return Stored effective intelligence, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_effective_intelligence(LibCharacterRecord* record, s32 intelligence)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    intelligence = limit_by_type(record, intelligence, 9999, 9999);
    record->encoded_effective_intelligence = intelligence ^ 0x7DE3F7E3;
    record->hit_checksum = hit_checksum(record);

    if (intelligence < character_intelligence(record))
    {
        set_character_intelligence(record, intelligence);
    }

    return intelligence;
}

/**
 * @brief Store the base intelligence, limited by type to 9999.
 * @param record Character record.
 * @param intelligence Base intelligence.
 * @return Stored base intelligence, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_base_intelligence(LibCharacterRecord* record, s32 intelligence)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    intelligence = limit_by_type(record, intelligence, 9999, 9999);
    record->encoded_base_intelligence = intelligence ^ 0x7DE3F7E3;
    record->hit_checksum = hit_checksum(record);
    return intelligence;
}

/**
 * @brief Store the effective HIT, limited by type to 9999, and lower the HIT to it.
 * @param record Character record.
 * @param hit Effective HIT.
 * @return Stored effective HIT, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_effective_hit(LibCharacterRecord* record, s32 hit)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    hit = limit_by_type(record, hit, 9999, 9999);
    record->encoded_effective_hit = hit ^ 0x7DE3F7E3;
    record->hit_checksum = hit_checksum(record);

    if (hit < character_hit(record))
    {
        set_character_hit(record, hit);
    }

    return hit;
}

/**
 * @brief Store the base HIT, limited by type to 9999.
 * @param record Character record.
 * @param hit Base HIT.
 * @return Stored base HIT, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_base_hit(LibCharacterRecord* record, s32 hit)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    hit = limit_by_type(record, hit, 9999, 9999);
    record->encoded_base_hit = hit ^ 0x7DE3F7E3;
    record->hit_checksum = hit_checksum(record);
    return hit;
}

/**
 * @brief Store the base agility, limited by type to 9999.
 * @param record Character record.
 * @param agility Base agility.
 * @return Stored base agility, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_base_agility(LibCharacterRecord* record, s32 agility)
{
    if (record->agility_checksum != (record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility))))
    {
        return 0;
    }

    agility = limit_by_type(record, agility, 9999, 9999);
    record->encoded_base_agility = agility ^ 0x7DE3F7E3;
    record->agility_checksum = agility_checksum(record);
    return agility;
}

/**
 * @brief Store agility, limited by type to 9999 and to the effective agility.
 * @param record Character record.
 * @param agility Agility to store.
 * @return Stored agility, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_agility(LibCharacterRecord* record, s32 agility)
{
    if (record->agility_checksum != (record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility))))
    {
        return 0;
    }

    agility = limit_by_type(record, agility, 9999, 9999);

    if (agility > (record->encoded_effective_agility ^ 0x7DE3F7E3))
    {
        agility = record->encoded_effective_agility ^ 0x7DE3F7E3;
    }

    record->encoded_agility = agility ^ 0x7DE3F7E3;
    record->agility_checksum = agility_checksum(record);
    return agility;
}

/**
 * @brief Store the effective defense, limited by type to 9999 or 99999, and lower the defense to it.
 * @param record Character record.
 * @param defense Effective defense.
 * @return Stored effective defense, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_effective_defense(LibCharacterRecord* record, s32 defense)
{
    if (record->defense_checksum != (record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense))))
    {
        return 0;
    }

    defense = limit_by_type_above(record, defense, 9999, 9999, 99999, 99999);
    record->encoded_effective_defense = defense ^ 0x7DE3F7E3;
    record->defense_checksum = defense_checksum(record);

    if (defense < character_defense(record))
    {
        lower_defense(record, defense);
    }

    return defense;
}

/**
 * @brief Store the base defense, limited by type to 9999 or 99999.
 * @param record Character record.
 * @param defense Base defense.
 * @return Stored base defense, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_base_defense(LibCharacterRecord* record, s32 defense)
{
    if (record->defense_checksum != (record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense))))
    {
        return 0;
    }

    defense = limit_by_type_above(record, defense, 9999, 9999, 99999, 99999);
    record->encoded_base_defense = defense ^ 0x7DE3F7E3;
    record->defense_checksum = defense_checksum(record);
    return defense;
}

/**
 * @brief Store the base attack, limited by type to 9999 or 99999.
 * @param record Character record.
 * @param attack Base attack.
 * @return Stored base attack, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_base_attack(LibCharacterRecord* record, s32 attack)
{
    if (record->attack_checksum != (record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack))))
    {
        return 0;
    }

    attack = limit_by_type(record, attack, 9999, 99999);
    record->encoded_base_attack = attack ^ 0x7DE3F7E3;
    record->attack_checksum = attack_checksum(record);
    return attack;
}

/**
 * @brief Store the effective attack, limited by type to 9999 or 99999, and lower the attack to it.
 * @param record Character record.
 * @param attack Effective attack.
 * @return Stored effective attack, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_effective_attack(LibCharacterRecord* record, s32 attack)
{
    if (record->attack_checksum != (record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack))))
    {
        return 0;
    }

    attack = limit_by_type(record, attack, 9999, 99999);
    record->encoded_effective_attack = attack ^ 0x7DE3F7E3;
    record->attack_checksum = attack_checksum(record);

    if (attack < character_attack(record))
    {
        set_character_attack(record, attack);
    }

    return attack;
}

/**
 * @brief Store the value at offset 0x28, limited to zero through one hundred.
 * @param record Character record.
 * @param value Displayed value.
 * @return Stored value.
 */
extern "C" float func_00406AB0(LibCharacterRecord* record, float value)
{
    value = clamp_fury(value);
    record->unk28 = 16.0f * value;
    return value;
}

/**
 * @brief Store the maximum fury and lower the current fury to it.
 * @param record Character record.
 * @param max_fury Displayed maximum fury.
 * @return Stored maximum fury.
 */
extern "C" float lib_character_set_max_fury(LibCharacterRecord* record, float max_fury)
{
    max_fury = clamp_fury(max_fury);
    record->scaled_max_fury = 16.0f * max_fury;

    if (!(character_fury(record) <= max_fury))
    {
        set_character_fury(record, max_fury);
    }

    return max_fury;
}

/**
 * @brief Store fury, limited to zero through the maximum.
 * @param record Character record.
 * @param fury Displayed fury.
 * @return Stored fury.
 */
extern "C" float lib_character_set_fury(LibCharacterRecord* record, float fury)
{
    return set_character_fury(record, fury);
}

/**
 * @brief Store the base MP, limited by type to 99999 or 99999999.
 * @param record Character record.
 * @param base_mp Base MP.
 * @return Stored base MP, or zero (setting the down flag) for an invalid checksum.
 */
extern "C" s32 func_00406C60(LibCharacterRecord* record, s32 base_mp)
{
    if (record->mp_checksum != (record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp))))
    {
        add_character_flags(record, 1);
        return 0;
    }

    base_mp = limit_by_type(record, base_mp, 99999, 99999999);
    record->encoded_base_mp = base_mp ^ 0x7DE3F7E3;
    record->mp_checksum = record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp));
    return base_mp;
}

/**
 * @brief Decode MP after validating its checksum.
 * @param record Character record.
 * @return MP, or zero (setting the down flag) for an invalid checksum.
 */
static inline s32 character_mp(LibCharacterRecord* record)
{
    if (record->mp_checksum != (record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp))))
    {
        add_character_flags(record, 1);
        return 0;
    }

    return record->encoded_mp ^ 0x7DE3F7E3;
}

/**
 * @brief Decode HP after validating its checksum.
 * @param record Character record.
 * @return HP, or zero (setting the down flag) for an invalid checksum.
 */
static inline s32 character_hp(LibCharacterRecord* record)
{
    if (record->hp_checksum != (record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp))))
    {
        add_character_flags(record, 1);
        return 0;
    }

    return record->encoded_hp ^ 0x7DE3F7E3;
}

extern "C" s32 func_003F9410(LibCharacterRecord* record, s32 mask);
extern "C" s32 func_003F97E0(LibCharacterRecord* record, s32 bits);

// TODO: The maximum HP/MP setters have the HP/MP setter inlined with its
// helpers called out of line, like the knockback and defense ones. These
// copies are a guess at that.

/**
 * @brief Store MP through the out-of-line limit and flag functions.
 * @param record Character record.
 * @param mp MP to store.
 * @return Stored MP, or zero for an invalid checksum.
 */
static inline s32 lower_mp(LibCharacterRecord* record, s32 mp)
{
    if (record->mp_checksum != (record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp))))
    {
        func_003F97E0(record, 1);
        return 0;
    }

    mp = lib_character_limit_mp(record, mp);

    if (mp > (record->encoded_max_mp ^ 0x7DE3F7E3))
    {
        mp = record->encoded_max_mp ^ 0x7DE3F7E3;
    }

    if (mp == 0)
    {
        func_003F97E0(record, 1);
    }

    if (mp != 0 && (record->encoded_hp ^ 0x7DE3F7E3) != 0)
    {
        func_003F9410(record, ~1);
    }

    record->encoded_mp = mp ^ 0x7DE3F7E3;
    record->mp_checksum = record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp));
    return mp;
}

/**
 * @brief Store HP through the out-of-line limit and flag functions.
 * @param record Character record.
 * @param hp HP to store.
 * @return Stored HP, or zero for an invalid checksum.
 */
static inline s32 lower_hp(LibCharacterRecord* record, s32 hp)
{
    if (record->hp_checksum != (record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp))))
    {
        func_003F97E0(record, 1);
        return 0;
    }

    hp = lib_character_limit_hp(record, hp);

    if (hp > (record->encoded_max_hp ^ 0x7DE3F7E3))
    {
        hp = record->encoded_max_hp ^ 0x7DE3F7E3;
    }

    if (hp == 0)
    {
        func_003F97E0(record, 1);
    }

    if (hp != 0 && (record->encoded_mp ^ 0x7DE3F7E3) != 0)
    {
        func_003F9410(record, ~1);
    }

    record->encoded_hp = hp ^ 0x7DE3F7E3;
    record->hp_checksum = record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp));
    return hp;
}

/**
 * @brief Store the maximum MP, limited by type, and lower the MP to it.
 * @param record Character record.
 * @param max_mp Maximum MP.
 * @return Stored maximum MP, or zero (setting the down flag) for an invalid checksum.
 */
extern "C" s32 lib_character_set_max_mp(LibCharacterRecord* record, s32 max_mp)
{
    if (record->mp_checksum != (record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp))))
    {
        add_character_flags(record, 1);
        return 0;
    }

    max_mp = limit_by_type(record, max_mp, 99999, 99999999);
    record->encoded_max_mp = max_mp ^ 0x7DE3F7E3;
    record->mp_checksum = record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp));

    if (max_mp < character_mp(record))
    {
        lower_mp(record, max_mp);
    }

    return max_mp;
}

/**
 * @brief Store the base HP, limited by type to 99999 or 99999999.
 * @param record Character record.
 * @param base_hp Base HP.
 * @return Stored base HP, or zero (setting the down flag) for an invalid checksum.
 */
extern "C" s32 func_00407050(LibCharacterRecord* record, s32 base_hp)
{
    if (record->hp_checksum != (record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp))))
    {
        add_character_flags(record, 1);
        return 0;
    }

    base_hp = limit_by_type(record, base_hp, 99999, 99999999);

    if (base_hp < 0)
    {
        base_hp = 0;
    }

    record->encoded_base_hp = base_hp ^ 0x7DE3F7E3;
    record->hp_checksum = record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp));
    return base_hp;
}

/**
 * @brief Store the maximum HP, limited by type and at least zero, and lower the HP to it.
 * @param record Character record.
 * @param max_hp Maximum HP.
 * @return Stored maximum HP, or zero (setting the down flag) for an invalid checksum.
 */
extern "C" s32 lib_character_set_max_hp(LibCharacterRecord* record, s32 max_hp)
{
    if (record->hp_checksum != (record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp))))
    {
        add_character_flags(record, 1);
        return 0;
    }

    max_hp = limit_by_type(record, max_hp, 99999, 99999999);

    if (max_hp < 0)
    {
        max_hp = 0;
    }

    record->encoded_max_hp = max_hp ^ 0x7DE3F7E3;
    record->hp_checksum = record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp));

    if (max_hp < character_hp(record))
    {
        lower_hp(record, max_hp);
    }

    return max_hp;
}

/**
 * @brief Store the experience, limited to zero through 999999999.
 * @param record Character record.
 * @param experience Experience to store.
 * @return Stored experience, or zero for an invalid checksum.
 */
extern "C" s32 lib_character_set_experience(LibCharacterRecord* record, s32 experience)
{
    if (record->flags_experience_checksum != (record->checksum_salt ^ (record->encoded_experience ^ (record->encoded_flags + record->checksum_salt))))
    {
        return 0;
    }

    experience = limit_value(experience, 0, 999999999);
    record->encoded_experience = experience ^ 0x7DE3F7E3;
    record->flags_experience_checksum = flags_experience_checksum(record);
    return experience;
}

/**
 * @brief Store the base level, limited to zero through 255.
 * @param record Character record.
 * @param level Base level.
 * @return Stored base level, or one for an invalid checksum.
 */
extern "C" s32 lib_character_set_base_level(LibCharacterRecord* record, s32 level)
{
    if (record->level_checksum != (record->checksum_salt ^ (record->encoded_level ^ (record->encoded_base_level + record->checksum_salt))))
    {
        return 1;
    }

    level = limit_value(level, 0, 255);
    record->encoded_base_level = level ^ 0x7E93;
    record->level_checksum = level_checksum(record);
    return level;
}

/**
 * @brief Store the level, limited to zero through 255.
 * @param record Character record.
 * @param level Level to store.
 * @return Stored level, or one for an invalid checksum.
 */
extern "C" s32 lib_character_set_level(LibCharacterRecord* record, s32 level)
{
    if (record->level_checksum != (record->checksum_salt ^ (record->encoded_level ^ (record->encoded_base_level + record->checksum_salt))))
    {
        return 1;
    }

    level = limit_value(level, 0, 255);
    record->encoded_level = level ^ 0x7E93;
    record->level_checksum = level_checksum(record);
    return level;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00407640);

/**
 * @brief Store the stat limit type.
 * @param record Character record.
 * @param type Limit type.
 * @return Stored limit type.
 */
extern "C" s16 func_004076B0(LibCharacterRecord* record, s16 type)
{
    record->stat_limit_type = type;
    return record->stat_limit_type;
}

/**
 * @brief Store the character ID.
 * @param record Character record.
 * @param id Character ID.
 * @return Stored character ID.
 */
extern "C" s16 func_004076C0(LibCharacterRecord* record, s16 id)
{
    record->character_id = id;
    return record->character_id;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004076D0);

/**
 * @brief Read one of a character's four table values after validating its checksum.
 * @param record Character record, or null.
 * @param index One-based value index, limited to one through four.
 * @return Table value, or 16 without a record, for limit type one, or for an invalid checksum.
 */
extern "C" u8 func_00407FC0(const LibCharacterRecord* record, s32 index)
{
    LibCharacterTableEntry* entry;
    s32 sum;
    s32 i;
    u16 check;

    if (record == 0)
    {
        return 16;
    }

    if (record->stat_limit_type == 1)
    {
        return 16;
    }

    entry = &D_001B64E8[record->character_id - 1];
    sum = 0;

    for (i = 0; i < 4; i++)
    {
        sum += entry->values[i];
    }

    check = sum * (record->character_id * 14) - record->character_id * 7 + 2974;

    if (check != entry->checksum)
    {
        return 16;
    }

    index--;

    if (index <= -1)
    {
        index = 0;
    }
    else if (index >= 4)
    {
        index = 3;
    }

    return entry->values[index];
}

/** Set each party member's aura bits from story flags 0x1C6 through 0x1CB. */
extern "C" void func_00408090(void)
{
    ResidentEntryTable* table = resident_get_entry_table(resident_get_system());
    u8* settings = (u8*)resident_find_entry(table, 1);
    LibCharacterEquipment* equipment;
    s32 flags;
    u8* event_flags;
    u8 mask;
    s32 i;

    resident_find_entry(table, 2);
    equipment = (LibCharacterEquipment*)resident_find_entry(table, 3);
    event_flags = settings + 0xA8;
    flags = 0;

    if (func_00456F10(event_flags, 0x1C6))
    {
        flags |= 0x1;
    }

    if (func_00456F10(event_flags, 0x1C7))
    {
        flags |= 0x2;
    }

    if (func_00456F10(event_flags, 0x1C8))
    {
        flags |= 0x4;
    }

    if (func_00456F10(event_flags, 0x1C9))
    {
        flags |= 0x8;
    }

    if (func_00456F10(event_flags, 0x1CA))
    {
        flags |= 0x10;
    }

    if (func_00456F10(event_flags, 0x1CB))
    {
        flags |= 0x20;
    }

    mask = flags;

    for (i = 0; i < 8; i++)
    {
        equipment->encoded_anti_attack_aura_mask = ((equipment->encoded_anti_attack_aura_mask ^ 0x77) | mask) ^ 0x77;
        func_00409A10(equipment);
        equipment++;
    }
}

/**
 * @brief Read a byte from the table at D_001B64E0.
 * @param id One-based entry ID, from one through 703.
 * @return Entry byte, or zero for an invalid ID.
 */
extern "C" u8 func_004081D0(s32 id)
{
    if (id <= 0 || id > 0x2BF)
    {
        return 0;
    }

    return D_001B64E0[id - 1];
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00408200);

/**
 * @brief Read the selected pair of scaled byte values from the Lib table.
 * @param index Signed table row, defaulting to zero outside zero through nine.
 * @param component Pair within the row, defaulting to zero outside zero through two.
 * @param first Optional destination for the first value.
 * @param second Optional destination for the second value.
 */
void func_00408600(s32 index, s32 component, float* first, float* second)
{
    if (index < 0 || index >= 10)
    {
        index = 0;
    }

    if (component < 0 || component >= 3)
    {
        component = 0;
    }

    if (first != 0)
    {
        *first = D_4EC260[index][component][0] * 40;
    }

    if (second != 0)
    {
        *second = D_4EC260[index][component][1] * 40;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004086D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004087A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00408850);

/**
 * @brief Validate a nine-byte block against the checksum byte after it.
 * @param data Nine bytes followed by their checksum.
 * @param seed Value mixed into the sum.
 * @return One when the checksum matches, otherwise zero.
 */
extern "C" s32 func_00408E20(u8* data, s32 seed)
{
    s32 sum = 0;
    s32 i;

    for (i = 0; i < 9; i++)
    {
        sum += *data++;
    }

    if (seed >= 129)
    {
        sum -= seed * 9;
    }
    else
    {
        sum += seed * 9;
    }

    if (*data != (u8)sum)
    {
        return 0;
    }

    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00408EA0);
