#include "include_asm.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "overlays/lib/light_random.h"
#include "overlays/lib/text_004095C0.h"
#include "clamp.h"
#include "ee.h"
#include "overlays/lib/text_003F90C0.h"
#include "overlays/lib/character_record.h"
#include "overlays/lib/text_0044ABE0.h"
#include "main/system.h"
#include "main/utility.h"

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


extern "C" void func_00409A10(LibCharacterEquipment* equipment);

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

    if (mp > decoded_max_mp(record))
    {
        mp = decoded_max_mp(record);
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

/**
 * @brief Decode current MP, flagging the record when its checksum fails.
 * @param record Character record.
 * @return Current MP, or zero for an invalid checksum.
 */
extern "C" u32 lib_character_get_mp(LibCharacterRecord* record)
{
    u32 first = record->encoded_base_mp;
    u32 salt = record->encoded_max_mp;
    u32 key = character_checksum_salt(record);
    u32 encoded = record->encoded_mp;
    u32 checksum = record->mp_checksum;

    if (checksum != ((first + salt) ^ encoded ^ key))
    {
        u32 flags = record->encoded_flags;
        s32 flag_salt = record->encoded_experience;

        if (record->flags_experience_checksum == ((flags + key) ^ flag_salt ^ key))
        {
            record->encoded_flags = ((flags ^ 0x7DE3F7E3) | 1) ^ 0x7DE3F7E3;
            s32 current_salt = record->encoded_experience;
            record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
        }

        return 0;
    }

    return encoded ^ 0x7DE3F7E3;
}

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

/**
 * @brief Keep only the given flag bits after validating the flags/experience checksum.
 * @param record Character record.
 * @param bits Bits to keep.
 * @return Updated flags, or five for an invalid checksum.
 */
extern "C" u32 lib_character_mask_flags(LibCharacterRecord* record, u32 bits)
{
    if (record->flags_experience_checksum != (((record->encoded_flags + record->checksum_salt) ^ record->encoded_experience) ^ record->checksum_salt))
    {
        return 5;
    }

    u32 value = record->encoded_flags;
    record->encoded_flags = ((value ^ 0x7DE3F7E3) & bits) ^ 0x7DE3F7E3;
    record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ record->encoded_experience) ^ record->checksum_salt;
    return record->encoded_flags ^ 0x7DE3F7E3;
}

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

    if (hp > decoded_max_hp(record))
    {
        hp = decoded_max_hp(record);
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

/**
 * @brief Decode current HP, flagging the record when its checksum fails.
 * @param record Character record.
 * @return Current HP, or zero for an invalid checksum.
 */
extern "C" u32 lib_character_get_hp(LibCharacterRecord* record)
{
    u32 first = record->encoded_base_hp;
    u32 salt = record->encoded_max_hp;
    u32 key = character_checksum_salt(record);
    u32 encoded = record->encoded_hp;
    u32 checksum = record->hp_checksum;

    if (checksum != ((first + salt) ^ encoded ^ key))
    {
        u32 flags = record->encoded_flags;
        s32 flag_salt = record->encoded_experience;

        if (record->flags_experience_checksum == ((flags + key) ^ flag_salt ^ key))
        {
            record->encoded_flags = ((flags ^ 0x7DE3F7E3) | 1) ^ 0x7DE3F7E3;
            s32 current_salt = record->encoded_experience;
            record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ current_salt) ^ record->checksum_salt;
        }

        return 0;
    }

    return encoded ^ 0x7DE3F7E3;
}

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

/**
 * @brief Set flag bits after validating the flags/experience checksum.
 * @param record Character record.
 * @param bits Bits to set.
 * @return Updated flags, or five for an invalid checksum.
 */
extern "C" u32 lib_character_add_flags(LibCharacterRecord* record, u32 bits)
{
    if (record->flags_experience_checksum != (((record->encoded_flags + record->checksum_salt) ^ record->encoded_experience) ^ record->checksum_salt))
    {
        return 5;
    }

    u32 value = record->encoded_flags;
    record->encoded_flags = ((value ^ 0x7DE3F7E3) | bits) ^ 0x7DE3F7E3;
    record->flags_experience_checksum = ((record->encoded_flags + record->checksum_salt) ^ record->encoded_experience) ^ record->checksum_salt;
    return record->encoded_flags ^ 0x7DE3F7E3;
}

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
s32 lib_character_get_effective_agility(const LibCharacterRecord* record)
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

/** Each character's tactical skill levels: the level each of the seven skills comes at (0xFF for never), then a check byte. */
extern "C" u8* D_001B64D4;

/**
 * @brief Decode a tactical skill state after validating the state checksum and the index.
 * @param equipment Character equipment record.
 * @param index State index.
 * @return State, or zero for an invalid checksum or index.
 */
static inline s32 lib_checked_tactical_skill_state(LibCharacterEquipment* equipment, s32 index)
{
    if (equipment->tactical_skill_states_checksum != tactical_skill_states_checksum(equipment->encoded_tactical_skill_states))
    {
        return 0;
    }

    if (index < 0)
    {
        return 0;
    }

    if ((u32)index >= 7)
    {
        return 0;
    }

    return (s8)equipment->encoded_tactical_skill_states[index] ^ 0x77;
}

/**
 * @brief Store a tactical skill state after validating the state checksum and the index.
 * @param equipment Character equipment record.
 * @param index State index.
 * @param state State to store.
 */
static inline void lib_set_checked_tactical_skill_state(LibCharacterEquipment* equipment, s32 index, s32 state)
{
    if (equipment->tactical_skill_states_checksum != tactical_skill_states_checksum(equipment->encoded_tactical_skill_states))
    {
        return;
    }

    if (index < 0)
    {
        return;
    }

    if ((u32)index >= 7)
    {
        return;
    }

    // TODO: The game stores this as a signed byte (-0x78, not 0x88, for state -1); the array may really be s8.
    reinterpret_cast<s8*>(equipment->encoded_tactical_skill_states)[index] = state ^ 0x77;
    equipment->tactical_skill_states_checksum = tactical_skill_states_checksum(equipment->encoded_tactical_skill_states);
}

/**
 * @brief Read the character's level when the encoded levels pass their checksum.
 *
 * Same as lib_character_level, but with a non-const record so the field addresses aren't hoisted out of a loop.
 * @param record Character record.
 * @return Level, or one for a failed checksum.
 */
static inline s32 lib_record_level(LibCharacterRecord* record)
{
    if (record->level_checksum != (record->checksum_salt ^ (record->encoded_level ^ (record->encoded_base_level + record->checksum_salt))))
    {
        return 1;
    }

    return record->encoded_level ^ 0x7E93;
}

/**
 * @brief Learn the first tactical skill the character's level has reached that it doesn't have yet.
 * @param object Unused receiver.
 * @param record Character record.
 * @param equipment Character equipment record.
 * @return The skill's index plus one, or zero when none was learned or the level table fails its check.
 */
extern "C" s32 func_003FFF10(void* object, LibCharacterRecord* record, LibCharacterEquipment* equipment)
{
    u8* levels;
    s32 learned = -1;
    s32 sum = 0;
    levels = D_001B64D4 + (record->character_id - 1) * 8;

    for (s32 i = 0; i < 7; i++)
    {
        if (learned == -1)
        {
            u8 level = *levels;

            if (level != 0xFF && lib_checked_tactical_skill_state(equipment, i) == 0 && lib_record_level(record) >= level)
            {
                learned = i;
            }
        }

        sum += *levels++;
    }

    if (learned != -1 && *levels == ((sum * 99 + 22) & 0xFF))
    {
        if (learned == 2 || learned == 3 || learned == 5 || learned == 6)
        {
            lib_set_checked_tactical_skill_state(equipment, learned, -1);
        }
        else
        {
            lib_set_checked_tactical_skill_state(equipment, learned, 1);
        }

        return learned + 1;
    }

    return 0;
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
        lib_character_add_flags(record, 1);
        return 0;
    }

    mp = lib_character_limit_mp(record, mp);

    if (mp > decoded_max_mp(record))
    {
        mp = decoded_max_mp(record);
    }

    if (mp == 0)
    {
        lib_character_add_flags(record, 1);
    }

    if (mp != 0 && (record->encoded_hp ^ 0x7DE3F7E3) != 0)
    {
        lib_character_mask_flags(record, ~1);
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
        lib_character_add_flags(record, 1);
        return 0;
    }

    hp = lib_character_limit_hp(record, hp);

    if (hp > decoded_max_hp(record))
    {
        hp = decoded_max_hp(record);
    }

    if (hp == 0)
    {
        lib_character_add_flags(record, 1);
    }

    if (hp != 0 && (record->encoded_mp ^ 0x7DE3F7E3) != 0)
    {
        lib_character_mask_flags(record, ~1);
    }

    record->encoded_hp = hp ^ 0x7DE3F7E3;
    record->hp_checksum = record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp));
    return hp;
}

/**
 * @brief Learn the first symbology the character's level has reached that it doesn't have yet.
 * @param object Unused receiver.
 * @param record Character record.
 * @param equipment Character equipment record.
 * @return The symbology's code, or zero when none was learned or the level list fails its check.
 */
extern "C" s32 func_00400350(void* object, const LibCharacterRecord* record, LibCharacterEquipment* equipment)
{
    LibCodeList* list;
    const u8* level;
    s32 found;
    s32 sum;
    s32 i;
    s32 id;

    found = -1;
    sum = 0;
    id = lib_character_id(record);
    list = &D_001B64CC[id - 1];
    level = &list->entries[0].unk01;

    for (i = 0; i < LIB_CODE_LIST_ENTRY_COUNT; i++, level += 2)
    {
        if (found == -1 && *level != 0xFF)
        {
            if (lib_equipment_symbology_mastery(equipment, i) == 0 && !(lib_character_level(record) < *level))
            {
                found = i;
            }
        }

        sum += *level;
    }

    if (found != -1 && *level == (u8)(sum * 17))
    {
        s32 code = list->entries[found].code;
        func_0040A370(equipment, id, code, 1);
        return code;
    }

    return 0;
}

/**
 * @brief Learn the first battle skill the character's level has reached that it doesn't have yet.
 * @param object Unused receiver.
 * @param record Character record.
 * @param equipment Character equipment record.
 * @return The battle skill's code, or zero when none was learned or the level table fails its check.
 */
extern "C" s32 func_004005C0(void* object, const LibCharacterRecord* record, LibCharacterEquipment* equipment)
{
    LibCodeTable* table;
    const u8* level;
    s32 found;
    s32 sum;
    s32 i;
    s32 id;

    found = -1;
    sum = 0;
    id = lib_character_id(record);
    table = &D_001B64D0[id - 1];
    level = &table->high_codes[0].unk01;

    for (i = 0; i < 42; i++, level += 2)
    {
        if (found == -1 && *level != 0xFF)
        {
            if (lib_equipment_battle_skill_mastery(equipment, i) == 0 && !(lib_character_level(record) < *level))
            {
                found = i;
            }
        }

        sum += *level;
    }

    if (found != -1 && *level == (u8)(sum * 29 + 15))
    {
        s32 code = table->high_codes[found].code;
        func_0040A5C0(equipment, id, code, 1);
        return code;
    }

    return 0;
}

/**
 * @brief Decode the base HP after validating the HP checksum.
 * @param record Character record.
 * @return Base HP, or zero (setting the down flag) for an invalid checksum.
 */
static inline s32 character_base_hp(LibCharacterRecord* record)
{
    if (record->hp_checksum != (record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp))))
    {
        add_character_flags(record, 1);
        return 0;
    }

    return record->encoded_base_hp ^ 0x7DE3F7E3;
}

/**
 * @brief Decode the base MP after validating the MP checksum.
 * @param record Character record.
 * @return Base MP, or zero (setting the down flag) for an invalid checksum.
 */
static inline s32 character_base_mp(LibCharacterRecord* record)
{
    if (record->mp_checksum != (record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp))))
    {
        add_character_flags(record, 1);
        return 0;
    }

    return record->encoded_base_mp ^ 0x7DE3F7E3;
}

/**
 * @brief Store the maximum HP through the out-of-line helpers, lowering the HP to it.
 * @param record Character record.
 * @param max_hp Maximum HP.
 */
static inline void raise_max_hp(LibCharacterRecord* record, s32 max_hp)
{
    if (record->hp_checksum != (record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp))))
    {
        lib_character_add_flags(record, 1);
        return;
    }

    max_hp = lib_character_limit_hp(record, max_hp);

    if (max_hp < 0)
    {
        max_hp = 0;
    }

    record->encoded_max_hp = max_hp ^ 0x7DE3F7E3;
    record->hp_checksum = record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp));

    if (max_hp < (s32)lib_character_get_hp(record))
    {
        lib_character_set_hp(record, max_hp);
    }
}

/**
 * @brief Store the base HP through the out-of-line helpers.
 * @param record Character record.
 * @param base_hp Base HP.
 */
static inline void raise_base_hp(LibCharacterRecord* record, s32 base_hp)
{
    if (record->hp_checksum != (record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp))))
    {
        lib_character_add_flags(record, 1);
        return;
    }

    base_hp = lib_character_limit_hp(record, base_hp);

    if (base_hp < 0)
    {
        base_hp = 0;
    }

    record->encoded_base_hp = base_hp ^ 0x7DE3F7E3;
    record->hp_checksum = record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp));
}

/**
 * @brief Store the maximum MP through the out-of-line helpers, lowering the MP to it.
 * @param record Character record.
 * @param max_mp Maximum MP.
 */
static inline void raise_max_mp(LibCharacterRecord* record, s32 max_mp)
{
    if (record->mp_checksum != (record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp))))
    {
        lib_character_add_flags(record, 1);
        return;
    }

    max_mp = lib_character_limit_mp(record, max_mp);
    record->encoded_max_mp = max_mp ^ 0x7DE3F7E3;
    record->mp_checksum = record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp));

    if (max_mp < (s32)lib_character_get_mp(record))
    {
        lib_character_set_mp(record, max_mp);
    }
}

/**
 * @brief Store the base MP through the out-of-line helpers.
 * @param record Character record.
 * @param base_mp Base MP.
 */
static inline void raise_base_mp(LibCharacterRecord* record, s32 base_mp)
{
    if (record->mp_checksum != (record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp))))
    {
        lib_character_add_flags(record, 1);
        return;
    }

    base_mp = lib_character_limit_mp(record, base_mp);
    record->encoded_base_mp = base_mp ^ 0x7DE3F7E3;
    record->mp_checksum = record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp));
}

/**
 * @brief Decode SP after validating the SP/CP checksum.
 * @param equipment Character equipment record.
 * @return SP, or zero for an invalid checksum.
 */
static inline s32 equipment_sp(const LibCharacterEquipment* equipment)
{
    if (equipment->sp_cp_checksum != (equipment->checksum_salt ^ (equipment->encoded_sp ^ (equipment->encoded_cp + equipment->checksum_salt))))
    {
        return 0;
    }

    return equipment->encoded_sp ^ 0x7E93;
}

/**
 * @brief Decode CP after validating the SP/CP checksum.
 * @param equipment Character equipment record.
 * @return CP, or zero for an invalid checksum.
 */
static inline s32 equipment_cp(const LibCharacterEquipment* equipment)
{
    if (equipment->sp_cp_checksum != (equipment->checksum_salt ^ (equipment->encoded_sp ^ (equipment->encoded_cp + equipment->checksum_salt))))
    {
        return 0;
    }

    return equipment->encoded_cp ^ 0x7E93;
}

/**
 * @brief Store SP, limited to zero through 9999, after validating the SP/CP checksum.
 * @param equipment Character equipment record.
 * @param sp SP to store.
 */
static inline void store_equipment_sp(LibCharacterEquipment* equipment, s32 sp)
{
    if (equipment->sp_cp_checksum == (equipment->checksum_salt ^ (equipment->encoded_sp ^ (equipment->encoded_cp + equipment->checksum_salt))))
    {
        sp = limit_value(sp, 0, 9999);
        equipment->encoded_sp = sp ^ 0x7E93;
        equipment->sp_cp_checksum = sp_cp_checksum(equipment);
    }
}

/**
 * @brief Store CP, limited to zero through fifteen, after validating the SP/CP checksum.
 * @param equipment Character equipment record.
 * @param cp CP to store.
 */
static inline void store_equipment_cp(LibCharacterEquipment* equipment, s32 cp)
{
    if (equipment->sp_cp_checksum == (equipment->checksum_salt ^ (equipment->encoded_sp ^ (equipment->encoded_cp + equipment->checksum_salt))))
    {
        cp = limit_value(cp, 0, 15);
        equipment->encoded_cp = cp ^ 0x7E93;
        equipment->sp_cp_checksum = sp_cp_checksum(equipment);
    }
}

/** Level-up report; func_00400830 adds the SP and CP it gave. */
struct LibLevelUpReport
{
    u8 unk000[0x4FC];
    u32 unk4fc;
    s32 sp_gained;
    s32 cp_gained;
};

extern "C" u8* D_001B64DC;

/**
 * @brief Grow a character's HP, MP, SP and CP for reaching a level, by character type.
 * @param report Level-up report; the SP and CP given are added to it.
 * @param record Character record.
 * @param equipment Character equipment record.
 * @param level New level.
 */
extern "C" void func_00400830(LibLevelUpReport* report, LibCharacterRecord* record, LibCharacterEquipment* equipment, s32 level)
{
    s32 type = record->character_id;
    s32 hp_growth;
    s32 mp_growth;

    // TODO: Both level thresholds are written as an offset compare in the game (level + 1393 < 1433 here and
    // level + 1884 < 1924 for MP); a plain `level < 40` compiles to a different compare.
    if (level + 1393 < 1433)
    {
        if (type == 4 || type == 7)
        {
            hp_growth = (level * 3 + (resident_random_below(5) + 8)) * 2;
        }
        else if (type == 1 || type == 6 || type == 10)
        {
            hp_growth = (level * 3 + (resident_random_below(4) + 5)) * 2;
        }
        else if (type == 5 || type == 8 || type == 9)
        {
            hp_growth = (level * 3 / 2 + (resident_random_below(3) + 7)) * 2;
        }
        else
        {
            hp_growth = (level * 5 / 4 + (resident_random_below(3) + 5)) * 2;
        }
    }
    else
    {
        if (type == 4 || type == 7)
        {
            hp_growth = level * 8 / 5 + (resident_random_below(5) + 19);
        }
        else if (type == 1 || type == 6 || type == 10)
        {
            hp_growth = level * 3 / 2 + (resident_random_below(4) + 2);
        }
        else if (type == 5 || type == 8 || type == 9)
        {
            hp_growth = level * 8 / 6 + (resident_random_below(4) + 10);
        }
        else
        {
            hp_growth = level + resident_random_below(4) + 15;
        }
    }

    raise_max_hp(record, hp_growth + character_max_hp(record));
    raise_base_hp(record, hp_growth + character_base_hp(record));
    lower_hp(record, hp_growth + character_hp(record));

    if (level + 1884 < 1924)
    {
        if (type == 4 || type == 7)
        {
            mp_growth = level / 3 + resident_random_below(2) + 2;
        }
        else if (type == 1 || type == 6 || type == 10)
        {
            mp_growth = level / 3 + resident_random_below(3) + 3;
        }
        else if (type == 5 || type == 8 || type == 9)
        {
            mp_growth = level / 3 + resident_random_below(3) + 4;
        }
        else
        {
            mp_growth = level / 2 + resident_random_below(4) + 8;
        }
    }
    else
    {
        if (type == 4 || type == 7)
        {
            mp_growth = level / 8 + resident_random_below(3) + 1;
        }
        else if (type == 1 || type == 6 || type == 10)
        {
            mp_growth = level / 6 + resident_random_below(4) + 3;
        }
        else if (type == 5 || type == 8 || type == 9)
        {
            mp_growth = level / 5 + resident_random_below(2) + 4;
        }
        else
        {
            mp_growth = level * 2 / 7 + resident_random_below(4) + 4;
        }
    }

    raise_max_mp(record, mp_growth + character_max_mp(record));
    raise_base_mp(record, mp_growth + character_base_mp(record));
    lower_mp(record, mp_growth + character_mp(record));

    // TODO: The game divides three times the level by twelve rather than the level by four.
    s32 sp = level * 3 / 12;
    s32 bonus = sp;

    if (sp >= 3)
    {
        bonus = sp / 2;
        bonus += resident_random_below(3);
    }

    if (level < 40)
    {
        sp = level + (bonus - sp / 3);
    }
    else
    {
        sp = level / 2 + (bonus - sp / 4);
    }

    if (sp <= 0)
    {
        sp = 1;
    }

    s32 current = equipment_sp(equipment);
    store_equipment_sp(equipment, current + sp);
    report->sp_gained += sp;
    const u8* table = D_001B64DC + (type - 1) * 32;
    s32 cp = -1;
    s32 level_sum = 0;
    s32 value_sum = 0;

    for (s32 i = 0; i < 15; i++)
    {
        if (cp == -1 && table[0] != 0xFF && level == table[0])
        {
            cp = table[1];
        }

        level_sum += table[0];
        value_sum += table[1];
        table += 2;
    }

    if (cp == -1 || table[0] != (u8)(level_sum + value_sum * 22 + 7))
    {
        cp = 0;
    }

    report->cp_gained += cp;
    store_equipment_cp(equipment, equipment_cp(equipment) + cp);
}

/**
 * @brief Decode the base attack after validating its checksum.
 * @param record Character record.
 * @return Base attack, or zero for an invalid checksum.
 */
static inline s32 character_base_attack(const LibCharacterRecord* record)
{
    if (record->attack_checksum != (record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack))))
    {
        return 0;
    }

    return record->encoded_base_attack ^ 0x7DE3F7E3;
}

/**
 * @brief Store the base attack, limited by type, after validating its checksum.
 * @param record Character record.
 * @param value Base attack.
 */
static inline void raise_base_attack(LibCharacterRecord* record, s32 value)
{
    if (record->attack_checksum == (record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack))))
    {
        value = limit_by_type(record, value, 9999, 99999);
        record->encoded_base_attack = value ^ 0x7DE3F7E3;
        record->attack_checksum = (record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack)));
    }
}

/**
 * @brief Decode the effective attack after validating its checksum.
 * @param record Character record.
 * @return Effective attack, or zero for an invalid checksum.
 */
static inline s32 character_effective_attack(const LibCharacterRecord* record)
{
    if (record->attack_checksum != (record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack))))
    {
        return 0;
    }

    return record->encoded_effective_attack ^ 0x7DE3F7E3;
}

/**
 * @brief Store the effective attack through the out-of-line helpers, lowering the current value to it.
 * @param record Character record.
 * @param value Effective attack.
 */
static inline void raise_effective_attack(LibCharacterRecord* record, s32 value)
{
    if (record->attack_checksum == (record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack))))
    {
        value = lib_character_limit_attack(record, value);
        record->encoded_effective_attack = value ^ 0x7DE3F7E3;
        record->attack_checksum = (record->checksum_salt ^ (record->encoded_attack ^ (record->encoded_base_attack + record->encoded_effective_attack)));

        if (value < func_003FFE50(record))
        {
            lib_character_set_attack(record, value);
        }
    }
}

/**
 * @brief Decode the base intelligence after validating its checksum.
 * @param record Character record.
 * @return Base intelligence, or zero for an invalid checksum.
 */
static inline s32 character_base_intelligence(const LibCharacterRecord* record)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    return record->encoded_base_intelligence ^ 0x7DE3F7E3;
}

/**
 * @brief Store the base intelligence, limited by type, after validating its checksum.
 * @param record Character record.
 * @param value Base intelligence.
 */
static inline void raise_base_intelligence(LibCharacterRecord* record, s32 value)
{
    if (record->hit_checksum == (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        value = limit_by_type(record, value, 9999, 9999);
        record->encoded_base_intelligence = value ^ 0x7DE3F7E3;
        record->hit_checksum = (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit)));
    }
}

/**
 * @brief Decode the effective intelligence after validating its checksum.
 * @param record Character record.
 * @return Effective intelligence, or zero for an invalid checksum.
 */
static inline s32 character_effective_intelligence(const LibCharacterRecord* record)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    return record->encoded_effective_intelligence ^ 0x7DE3F7E3;
}

/**
 * @brief Store the effective intelligence through the out-of-line helpers, lowering the current value to it.
 * @param record Character record.
 * @param value Effective intelligence.
 */
static inline void raise_effective_intelligence(LibCharacterRecord* record, s32 value)
{
    if (record->hit_checksum == (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        value = lib_character_limit_intelligence(record, value);
        record->encoded_effective_intelligence = value ^ 0x7DE3F7E3;
        record->hit_checksum = (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit)));

        if (value < lib_character_get_intelligence(record))
        {
            lib_character_set_intelligence(record, value);
        }
    }
}

/**
 * @brief Decode the base hit after validating its checksum.
 * @param record Character record.
 * @return Base hit, or zero for an invalid checksum.
 */
static inline s32 character_base_hit(const LibCharacterRecord* record)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    return record->encoded_base_hit ^ 0x7DE3F7E3;
}

/**
 * @brief Store the base hit, limited by type, after validating its checksum.
 * @param record Character record.
 * @param value Base hit.
 */
static inline void raise_base_hit(LibCharacterRecord* record, s32 value)
{
    if (record->hit_checksum == (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        value = limit_by_type(record, value, 9999, 9999);
        record->encoded_base_hit = value ^ 0x7DE3F7E3;
        record->hit_checksum = (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit)));
    }
}

/**
 * @brief Decode the effective hit after validating its checksum.
 * @param record Character record.
 * @return Effective hit, or zero for an invalid checksum.
 */
static inline s32 character_effective_hit(const LibCharacterRecord* record)
{
    if (record->hit_checksum != (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        return 0;
    }

    return record->encoded_effective_hit ^ 0x7DE3F7E3;
}

/**
 * @brief Store the effective hit through the out-of-line helpers, lowering the current value to it.
 * @param record Character record.
 * @param value Effective hit.
 */
static inline void raise_effective_hit(LibCharacterRecord* record, s32 value)
{
    if (record->hit_checksum == (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit))))
    {
        value = lib_character_limit_hit(record, value);
        record->encoded_effective_hit = value ^ 0x7DE3F7E3;
        record->hit_checksum = (record->checksum_salt ^ (record->encoded_hit ^ (record->encoded_base_hit + record->encoded_effective_hit)));

        if (value < func_003FF8F0(record))
        {
            lib_character_set_hit(record, value);
        }
    }
}

/**
 * @brief Decode the base defense after validating its checksum.
 * @param record Character record.
 * @return Base defense, or zero for an invalid checksum.
 */
static inline s32 character_base_defense(const LibCharacterRecord* record)
{
    if (record->defense_checksum != (record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense))))
    {
        return 0;
    }

    return record->encoded_base_defense ^ 0x7DE3F7E3;
}

/**
 * @brief Store the base defense, limited by type, after validating its checksum.
 * @param record Character record.
 * @param value Base defense.
 */
static inline void raise_base_defense(LibCharacterRecord* record, s32 value)
{
    if (record->defense_checksum == (record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense))))
    {
        value = limit_by_type_above(record, value, 9999, 9999, 99999, 99999);
        record->encoded_base_defense = value ^ 0x7DE3F7E3;
        record->defense_checksum = (record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense)));
    }
}

/**
 * @brief Decode the effective defense after validating its checksum.
 * @param record Character record.
 * @return Effective defense, or zero for an invalid checksum.
 */
static inline s32 character_effective_defense(const LibCharacterRecord* record)
{
    if (record->defense_checksum != (record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense))))
    {
        return 0;
    }

    return record->encoded_effective_defense ^ 0x7DE3F7E3;
}

/**
 * @brief Store the effective defense through the out-of-line helpers, lowering the current value to it.
 * @param record Character record.
 * @param value Effective defense.
 */
static inline void raise_effective_defense(LibCharacterRecord* record, s32 value)
{
    if (record->defense_checksum == (record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense))))
    {
        value = lib_character_limit_defense(record, value);
        record->encoded_effective_defense = value ^ 0x7DE3F7E3;
        record->defense_checksum = (record->checksum_salt ^ (record->encoded_defense ^ (record->encoded_base_defense + record->encoded_effective_defense)));

        if (value < func_003FFAC0(record))
        {
            lib_character_set_defense(record, value);
        }
    }
}

/**
 * @brief Decode the base agility after validating its checksum.
 * @param record Character record.
 * @return Base agility, or zero for an invalid checksum.
 */
static inline s32 character_base_agility(const LibCharacterRecord* record)
{
    if (record->agility_checksum != (record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility))))
    {
        return 0;
    }

    return record->encoded_base_agility ^ 0x7DE3F7E3;
}

/**
 * @brief Store the base agility, limited by type, after validating its checksum.
 * @param record Character record.
 * @param value Base agility.
 */
static inline void raise_base_agility(LibCharacterRecord* record, s32 value)
{
    if (record->agility_checksum == (record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility))))
    {
        value = limit_by_type(record, value, 9999, 9999);
        record->encoded_base_agility = value ^ 0x7DE3F7E3;
        record->agility_checksum = (record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility)));
    }
}

/**
 * @brief Store the effective agility through the out-of-line helpers, lowering the current value to it.
 * @param record Character record.
 * @param value Effective agility.
 */
static inline void raise_effective_agility(LibCharacterRecord* record, s32 value)
{
    if (record->agility_checksum == (record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility))))
    {
        value = lib_character_limit_agility(record, value);
        record->encoded_effective_agility = value ^ 0x7DE3F7E3;
        record->agility_checksum = (record->checksum_salt ^ (record->encoded_agility ^ (record->encoded_base_agility + record->encoded_effective_agility)));

        if (value < lib_character_get_effective_agility(record))
        {
            lib_character_set_effective_agility(record, value);
        }
    }
}

/**
 * @brief Decode the base stamina after validating its checksum.
 * @param equipment Character equipment record.
 * @return Base stamina, or zero for an invalid checksum.
 */
static inline s32 equipment_base_stamina(const LibCharacterEquipment* equipment)
{
    if (equipment->stamina_checksum != (equipment->checksum_salt ^ (equipment->encoded_stamina ^ (equipment->encoded_base_stamina + equipment->encoded_effective_stamina))))
    {
        return 0;
    }

    return equipment->encoded_base_stamina ^ 0x7E93;
}

/**
 * @brief Store the base stamina, limited to zero through 9999, after validating its checksum.
 * @param equipment Character equipment record.
 * @param value Base stamina.
 */
static inline void raise_base_stamina(LibCharacterEquipment* equipment, s32 value)
{
    if (equipment->stamina_checksum == (equipment->checksum_salt ^ (equipment->encoded_stamina ^ (equipment->encoded_base_stamina + equipment->encoded_effective_stamina))))
    {
        value = limit_value(value, 0, 9999);
        equipment->encoded_base_stamina = value ^ 0x7E93;
        equipment->stamina_checksum = stamina_checksum(equipment);
    }
}

/**
 * @brief Decode the effective stamina after validating its checksum.
 * @param equipment Character equipment record.
 * @return Effective stamina, or zero for an invalid checksum.
 */
static inline s32 equipment_effective_stamina(const LibCharacterEquipment* equipment)
{
    if (equipment->stamina_checksum != (equipment->checksum_salt ^ (equipment->encoded_stamina ^ (equipment->encoded_base_stamina + equipment->encoded_effective_stamina))))
    {
        return 0;
    }

    return equipment->encoded_effective_stamina ^ 0x7E93;
}

/**
 * @brief Store the effective stamina through the out-of-line helpers, lowering the stamina to it.
 * @param equipment Character equipment record.
 * @param value Effective stamina.
 */
static inline void raise_effective_stamina(LibCharacterEquipment* equipment, s32 value)
{
    if (equipment->stamina_checksum == (equipment->checksum_salt ^ (equipment->encoded_stamina ^ (equipment->encoded_base_stamina + equipment->encoded_effective_stamina))))
    {
        equipment->encoded_effective_stamina = lib_equipment_limit_stamina(equipment, value) ^ 0x7E93;

        if (func_003FF0C0(equipment) > (equipment->encoded_effective_stamina ^ 0x7E93))
        {
            lib_equipment_set_stamina(equipment, equipment->encoded_effective_stamina ^ 0x7E93);
        }

        equipment->stamina_checksum = stamina_checksum(equipment);
    }
}

/**
 * @brief Read the character's base level when the encoded levels pass their checksum.
 * @param record Character record.
 * @return Base level, or one for a failed checksum.
 */
static inline s32 lib_character_base_level(const LibCharacterRecord* record)
{
    if (record->level_checksum != (record->checksum_salt ^ (record->encoded_level ^ (record->encoded_base_level + record->checksum_salt))))
    {
        return 1;
    }

    return record->encoded_base_level ^ 0x7E93;
}

/**
 * @brief Store the level, limited to zero through 255, after validating the level checksum.
 * @param record Character record.
 * @param level Level.
 */
static inline void store_character_level(LibCharacterRecord* record, s32 level)
{
    if (record->level_checksum == (record->checksum_salt ^ (record->encoded_level ^ (record->encoded_base_level + record->checksum_salt))))
    {
        level = limit_value(level, 0, 255);
        record->encoded_level = level ^ 0x7E93;
        record->level_checksum = level_checksum(record);
    }
}

/**
 * @brief Store the base level, limited to zero through 255, after validating the level checksum.
 * @param record Character record.
 * @param level Base level.
 */
static inline void store_character_base_level(LibCharacterRecord* record, s32 level)
{
    if (record->level_checksum == (record->checksum_salt ^ (record->encoded_level ^ (record->encoded_base_level + record->checksum_salt))))
    {
        level = limit_value(level, 0, 255);
        record->encoded_base_level = level ^ 0x7E93;
        record->level_checksum = level_checksum(record);
    }
}

/**
 * @brief Decode the experience after validating the flags/experience checksum.
 * @param record Character record.
 * @return Experience, or zero for an invalid checksum.
 */
static inline s32 character_experience(const LibCharacterRecord* record)
{
    if (record->flags_experience_checksum != (record->checksum_salt ^ (record->encoded_experience ^ (record->encoded_flags + record->checksum_salt))))
    {
        return 0;
    }

    return record->encoded_experience ^ 0x7DE3F7E3;
}

extern "C" u8* D_001B64C0;

/**
 * @brief Level a character up while its experience reaches the next threshold: HP and MP every pass of a full level
 *        up, then attack, intelligence, hit, defense, stamina and agility by the type's growth row.
 * @param report Level-up report; its SP and CP totals are cleared first.
 * @param record Character record.
 * @param equipment Character equipment record.
 * @return Number of levels gained.
 */
extern "C" s32 func_00401780(LibLevelUpReport* report, LibCharacterRecord* record, LibCharacterEquipment* equipment)
{
    report->sp_gained = 0;
    report->cp_gained = 0;

    // TODO: The game writes every level-255 test as an offset compare like this one.
    if (lib_record_level(record) + 0x1AF == 0x2AE || lib_character_base_level(record) + 0x18F == 0x28E)
    {
        return 0;
    }

    s32 sum = 0;

    for (s32 i = 0; i < 0x13F; i++)
    {
        sum += reinterpret_cast<s32*>(report)[i];
    }

    s32 count;

    if (sum != 0)
    {
        count = resident_random_range(4, 8) + 1;

        if (count > 6)
        {
            return 0;
        }
    }
    else
    {
        count = 3;
    }

    s32 bonus = count / 3;
    s32 levels = 0;
    s32* thresholds = reinterpret_cast<s32*>(report) + (report->unk4fc ^ 0x400013B);
    s32 type = record->character_id - 1;
    u8* row = D_001B64C0 + type * 13;

    while (character_experience(record) >= thresholds[lib_record_level(record) - 1])
    {
        if (lib_record_level(record) + 0x279 == 0x378 || lib_character_base_level(record) + 0x13F == 0x23E)
        {
            break;
        }

        levels++;

        if (count == 3)
        {
            func_00400830(report, record, equipment, lib_record_level(record) + 1);
        }

        s32 row_sum = 0;
        s32 i;

        for (i = 0; i < 12; i++)
        {
            row_sum += row[i];
        }

        if ((u8)(row_sum - (type + 0x24)) != row[i])
        {
            bonus = resident_random_below(5);
        }

        for (s32 stat = 0; stat < 6; stat++)
        {
            s32 growth = row[stat * 2 + 1] + resident_random_below(row[stat * 2]);

            switch (stat)
            {
            case 0:
                if (count != 3)
                {
                    growth = (D_001B65B8 = 1664525L * D_001B65B8 + 1013904223L) % 6 - 3;
                }

                raise_base_attack(record, growth + character_base_attack(record));
                raise_effective_attack(record, growth + character_effective_attack(record));
                break;
            case 1:
                if (count == 3)
                {
                    raise_base_intelligence(record, growth + character_base_intelligence(record));
                    raise_effective_intelligence(record, growth + character_effective_intelligence(record));
                }

                break;
            case 2:
                if (count < 3)
                {
                    growth = resident_random_range(-3, 2);
                }

                raise_base_hit(record, growth + character_base_hit(record));
                raise_effective_hit(record, growth + character_effective_hit(record));
                break;
            case 3:
                if (bonus == 1)
                {
                    raise_base_defense(record, growth + character_base_defense(record));
                    raise_effective_defense(record, growth + character_effective_defense(record));
                }

                break;
            case 4:
                if (bonus != 1)
                {
                    growth = resident_random_range(-2, 1);
                }

                raise_base_stamina(equipment, growth + equipment_base_stamina(equipment));
                raise_effective_stamina(equipment, growth + equipment_effective_stamina(equipment));
                break;
            case 5:
                if (bonus == 1)
                {
                    raise_base_agility(record, growth + character_base_agility(record));
                    raise_effective_agility(record, growth + character_effective_agility(record));
                }

                break;
            }
        }

        store_character_level(record, lib_record_level(record) + 1);
        store_character_base_level(record, lib_character_base_level(record) + 1);
    }

    return levels;
}

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

/**
 * @brief Checksum an array of halfwords.
 * @param object Unused receiver.
 * @param data Halfwords to checksum.
 * @param size Size of the array in bytes.
 * @return Checksum.
 */
extern "C" u32 func_00405530(void* object, const s16* data, s32 size)
{
    return halfwords_checksum(data, size);
}

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

/**
 * @brief Store the flags after validating the flags/experience checksum.
 * @param record Character record.
 * @param flags Flags to store.
 * @return Stored flags, or five for an invalid checksum.
 */
extern "C" s32 func_00407640(LibCharacterRecord* record, s32 flags)
{
    if (record->flags_experience_checksum != (record->checksum_salt ^ (record->encoded_experience ^ (record->encoded_flags + record->checksum_salt))))
    {
        return 5;
    }

    record->encoded_flags = flags ^ 0x7DE3F7E3;
    record->flags_experience_checksum = flags_experience_checksum(record);
    return record->encoded_flags ^ 0x7DE3F7E3;
}

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

extern "C" void func_00402B30(LibCharacterRecord* record, LibCharacterEquipment* equipment);

extern "C" const char D_00501CF0[];
extern "C" const char D_00501CE8[];
extern "C" const char D_00501CE0[];
extern "C" const char D_00501CD8[];
extern "C" const char D_00501CD0[];
extern "C" const char D_00501CC8[];
extern "C" const char D_00501CC0[];
extern "C" const char D_00501CB8[];
extern "C" const char D_00501CB0[];
extern "C" const char D_00501CA8[];

/**
 * @brief Copy a character name.
 * @param name Name buffer.
 * @param text Name.
 */
static inline void copy_character_name(char* name, const char* text)
{
    const char* source = text;
    char* destination = name;

    while ((*destination++ = *source++))
    {
    }
}

/**
 * @brief Clear a character's records to zero under fresh checksum salts, then give a party member its starting
 *        values and name.
 * @param record Character record to fill.
 * @param equipment Character equipment record to fill.
 * @param id Character ID; zero leaves the records cleared.
 */
void func_004076D0(LibCharacterRecord* record, LibCharacterEquipment* equipment, s32 id)
{
    s32 i;

    memset_guess(record, 0, sizeof(LibCharacterRecord));
    record->checksum_salt = resident_next_random_word();
    record->level_checksum = level_checksum(record);
    record->flags_experience_checksum = flags_experience_checksum(record);
    record->hp_checksum = record->checksum_salt ^ (record->encoded_hp ^ (record->encoded_base_hp + record->encoded_max_hp));
    record->mp_checksum = record->checksum_salt ^ (record->encoded_mp ^ (record->encoded_base_mp + record->encoded_max_mp));
    record->attack_checksum = attack_checksum(record);
    record->defense_checksum = defense_checksum(record);
    record->agility_checksum = agility_checksum(record);
    record->hit_checksum = hit_checksum(record);
    record->knockback_power_checksum = knockback_power_checksum(record);
    record->knockback_resistance_checksum = knockback_resistance_checksum(record);
    record->critical_rate_checksum = critical_rate_checksum(record);
    func_004076C0(record, 0);
    func_004076B0(record, 0);
    func_00407640(record, 0);
    lib_character_set_level(record, 0);
    lib_character_set_base_level(record, 0);
    lib_character_set_experience(record, 0);
    lib_character_set_hp(record, 0);
    lib_character_set_max_hp(record, 0);
    func_00407050(record, 0);
    lib_character_set_mp(record, 0);
    lib_character_set_max_mp(record, 0);
    func_00406C60(record, 0);
    lib_character_set_fury(record, 0.0f);
    lib_character_set_max_fury(record, 0.0f);
    func_00406AB0(record, 0.0f);
    lib_character_set_attack(record, 0);
    lib_character_set_effective_attack(record, 0);
    lib_character_set_base_attack(record, 0);
    lib_character_set_defense(record, 0);
    lib_character_set_base_defense(record, 0);
    lib_character_set_effective_defense(record, 0);
    lib_character_set_agility(record, 0);
    lib_character_set_base_agility(record, 0);
    lib_character_set_effective_agility(record, 0);
    lib_character_set_hit(record, 0);
    lib_character_set_base_hit(record, 0);
    lib_character_set_effective_hit(record, 0);
    lib_character_set_intelligence(record, 0);
    lib_character_set_base_intelligence(record, 0);
    lib_character_set_effective_intelligence(record, 0);
    lib_character_set_knockback_power(record, 0);
    lib_character_set_base_knockback_power(record, 0);
    lib_character_set_effective_knockback_power(record, 0);
    lib_character_set_knockback_resistance(record, 0);
    lib_character_set_base_knockback_resistance(record, 0);
    lib_character_set_effective_knockback_resistance(record, 0);
    lib_character_set_critical_rate(record, 0);
    lib_character_set_effective_critical_rate(record, 0);
    lib_character_set_base_critical_rate(record, 0);

    memset_guess(equipment, 0, sizeof(LibCharacterEquipment));
    equipment->checksum_salt = resident_next_random_word();
    equipment->luck_checksum = luck_checksum(equipment);
    equipment->stamina_checksum = stamina_checksum(equipment);
    equipment->equipment_checksum =
        equipment->checksum_salt ^ ((equipment->encoded_equipment_ids[1] + equipment->encoded_equipment_ids[2]) ^ (equipment->encoded_equipment_ids[3] + equipment->encoded_equipment_ids[0]));
    equipment->sp_cp_checksum = sp_cp_checksum(equipment);
    equipment->symbology_mastery_checksum = func_00405530(equipment, equipment->encoded_symbology_mastery, sizeof(equipment->encoded_symbology_mastery));
    equipment->battle_skill_mastery_checksum = func_00405530(equipment, equipment->encoded_battle_skill_mastery, sizeof(equipment->encoded_battle_skill_mastery));
    equipment->tactical_skill_states_checksum = func_00405440(equipment, equipment->encoded_tactical_skill_states, sizeof(equipment->encoded_tactical_skill_states));
    equipment->battle_skill_indices_checksum = func_00405440(equipment, equipment->encoded_battle_skill_indices, sizeof(equipment->encoded_battle_skill_indices));
    equipment->status_skill_levels_checksum = func_00405440(equipment, equipment->encoded_status_skill_levels, sizeof(equipment->encoded_status_skill_levels));
    lib_equipment_set_base_luck(equipment, 0);
    lib_equipment_set_effective_luck(equipment, 0);
    lib_equipment_set_luck(equipment, 0);
    lib_equipment_set_base_stamina(equipment, 0);
    lib_equipment_set_effective_stamina(equipment, 0);
    lib_equipment_set_stamina(equipment, 0);
    lib_equipment_set_slot_count(equipment, 4);
    lib_equipment_set_slot_limit(equipment, 4);

    for (i = 0; i < 4; i++)
    {
        lib_equipment_set_equipment_id(equipment, i, 0);
    }

    lib_equipment_set_sp(equipment, 0);
    lib_equipment_set_cp(equipment, 0);
    // TODO: The game passes the equipment record here; the store lands in its unk1c.
    lib_character_set_base_mp(reinterpret_cast<LibCharacterRecord*>(equipment), 0);

    for (i = 0; i < 24; i++)
    {
        equipment->character_name[i] = 0;
    }

    func_00404CE0(equipment, 0);
    func_00404CD0(equipment, 0);
    func_00404CC0(equipment, 0);
    func_00404CA0(equipment, 0);

    for (i = 0; i < 5; i++)
    {
        lib_equipment_set_status_skill_level(equipment, i, 0);
    }

    for (i = 0; i < 6; i++)
    {
        lib_equipment_clear_battle_skill_index(equipment, i);
    }

    for (i = 0; i < 7; i++)
    {
        lib_equipment_set_tactical_skill_state(equipment, i, 0);
    }

    for (i = 0; i < 32; i++)
    {
        lib_equipment_set_symbology_mastery(equipment, i, 0);
    }

    for (i = 0; i < 42; i++)
    {
        lib_equipment_set_battle_skill_mastery(equipment, i, 0);
    }

    for (i = 0; i < 4; i++)
    {
        lib_equipment_set_elemental_response(equipment, i, 0);
    }

    func_00404560(equipment, 0);
    record->character_id = id;
    record->stat_limit_type = 0;

    if (id > 0)
    {
        func_00402B30(record, equipment);
    }

    switch (id)
    {
    case 1:
        copy_character_name(equipment->character_name, D_00501CF0);
        break;
    case 2:
        copy_character_name(equipment->character_name, D_00501CE8);
        break;
    case 3:
        copy_character_name(equipment->character_name, D_00501CE0);
        break;
    case 4:
        copy_character_name(equipment->character_name, D_00501CD8);
        break;
    case 5:
        copy_character_name(equipment->character_name, D_00501CD0);
        break;
    case 6:
        copy_character_name(equipment->character_name, D_00501CC8);
        break;
    case 7:
        copy_character_name(equipment->character_name, D_00501CC0);
        break;
    case 8:
        copy_character_name(equipment->character_name, D_00501CB8);
        break;
    case 9:
        copy_character_name(equipment->character_name, D_00501CB0);
        break;
    case 10:
        copy_character_name(equipment->character_name, D_00501CA8);
        break;
    }
}

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
    LibFactorCounts* factor_counts;
    u8 mask;
    s32 i;

    resident_find_entry(table, 2);
    equipment = (LibCharacterEquipment*)resident_find_entry(table, 3);
    factor_counts = (LibFactorCounts*)(settings + 0xA8);
    flags = 0;

    if (lib_factor_counted(factor_counts, 0x1C6))
    {
        flags |= 0x1;
    }

    if (lib_factor_counted(factor_counts, 0x1C7))
    {
        flags |= 0x2;
    }

    if (lib_factor_counted(factor_counts, 0x1C8))
    {
        flags |= 0x4;
    }

    if (lib_factor_counted(factor_counts, 0x1C9))
    {
        flags |= 0x8;
    }

    if (lib_factor_counted(factor_counts, 0x1CA))
    {
        flags |= 0x10;
    }

    if (lib_factor_counted(factor_counts, 0x1CB))
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

/** Twenty-byte power record of the table at D_001B64BC, indexed by ID minus one. */
struct LibPowerEntry
{
    u32 unk00;
    u16 unk04;
    u16 base;
    u16 intelligence_scale;
    u16 level_scale;
    u8 unk0c;
    u8 unk0d;
    u16 checksum;
    u8 unk10;
    u8 flags;
    u16 unk12;
};

extern "C" LibPowerEntry* D_001B64BC;

/**
 * @brief Look up a power, scale it by level and intelligence and limit it to -99999 through 99999.
 *
 * A record whose checksum fails gives a much smaller power and 0xF3 for unk0d.
 * IDs 3 and 18 scale by level only.
 * @param id One-based power ID, from one through 29.
 * @param mode Zero or one, picking the scale and the flag bit tested.
 * @param level Level, limited to one through ten.
 * @param record Character record supplying intelligence, or null.
 * @param power Receives the power, or null.
 * @param kind Receives the low six flag bits, or null.
 * @param unk10 Receives unk10, or null.
 * @param unk00 Receives unk00, or null.
 * @param unk04 Receives unk04 as a float, or null.
 * @param unk0d Receives unk0d, or 0xF3 for a failed checksum, or null.
 * @param scaled Receives the power scaled by unk12 / 2048, or null.
 * @return 1 when the flag bit for the mode is set, otherwise 0.
 */
extern "C" s32 func_00408200(s32 id, s32 mode, s32 level, const LibCharacterRecord* record, s32* power, s32* kind, s32* unk10, u32* unk00, float* unk04,
                             s32* unk0d, s32* scaled)
{
    LibPowerEntry* entry;
    s32 value;
    s32 intelligence_scale;
    s32 level_scale;
    s32 extra;
    s32 weight;
    s32 scale;
    u16 checksum;
    u8 flags;

    if (id <= 0 || id > 29)
    {
        return 0;
    }

    if (level < 0)
    {
        level = 1;
    }
    else if (level > 10)
    {
        level = 10;
    }

    entry = &D_001B64BC[id - 1];

    if (unk00 != 0)
    {
        *unk00 = entry->unk00;
    }

    weight = entry->unk04;

    if (unk04 != 0)
    {
        *unk04 = weight;
    }

    value = entry->base;
    intelligence_scale = entry->intelligence_scale;
    level_scale = entry->level_scale;
    extra = entry->unk0d;

    checksum = extra + ((value - 500 + weight * 3) + (level_scale - intelligence_scale * 5) - id * 493);

    if (checksum != entry->checksum)
    {
        value /= 128;

        if (record != 0)
        {
            value += (level * level_scale) / 2048 + (intelligence_scale * character_intelligence(record)) / 16000;
        }

        value /= 256;
        extra = 0xF3;
    }
    else if (id == 3 || id == 18)
    {
        value += (level * level_scale) / 128;

        if (mode == 0)
        {
            value = (value * 4) / 5;
        }
    }
    else
    {
        if (mode == 0)
        {
            if (value <= 400)
            {
                intelligence_scale = (intelligence_scale * 24) / 64;
                level_scale = (level_scale * 32) / 64;
            }
            else
            {
                intelligence_scale = (intelligence_scale * 14) / 64;
                level_scale = (level_scale * 24) / 64;
            }
        }

        if (record != 0)
        {
            value += (level * level_scale) / 128 + (intelligence_scale * character_intelligence(record)) / 2048;
        }
    }

    if (unk10 != 0)
    {
        *unk10 = entry->unk10;
    }

    flags = entry->flags;
    scale = entry->unk12;
    value += 773;

    if (value > 100772)
    {
        value = 100772;
    }

    if (value < -99226)
    {
        value = -99226;
    }

    if (power != 0)
    {
        *power = value - 773;
    }

    if (scaled != 0)
    {
        *scaled = ((value - 773) * scale) / 2048;
    }

    if (kind != 0)
    {
        *kind = flags & 0x3F;
    }

    if (unk0d != 0)
    {
        *unk0d = extra;
    }

    if (((flags & 0x40) && mode == 0) || ((flags & 0x80) && mode == 1))
    {
        return 1;
    }

    return 0;
}

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

extern u16* D_001B64E4;

/**
 * @brief Read a value from one of two checksummed ten-halfword records.
 * @param object Unused.
 * @param index Value index, 2 to 10.
 * @param record Record number, 1 or 2.
 * @return The value, or zero for a bad index, record or checksum.
 */
extern "C" s32 func_004086D0(void* object, s32 index, s32 record)
{
    if (index <= 1 || index > 10 || (record != 1 && record != 2))
    {
        return 0;
    }

    u16* entry = D_001B64E4;
    entry += (record - 1) * 10;
    u16 checksum = entry[0];
    s32 value = entry[index - 1];
    u32 sum = 0;

    for (s32 i = 0; i < 9; i++)
    {
        sum += entry[i + 1];
    }

    u16 expected = sum * 6 + record * 0xB4F + 0x9708;

    if (expected != checksum)
    {
        value = 0;
    }

    return value;
}

extern u8* D_001B64B4;

// TODO: The target adds 0xE2 and 0x18 at run time for the bad-checksum result; only a local with propagation off
// keeps the two apart.
#pragma push
#pragma opt_propagation off

/**
 * @brief Read a value from a checksummed ten-byte record.
 * @param record Record number, from one.
 * @param index Value index, 1 to 9.
 * @return The value, -1 for a bad index, or 250 when the record's checksum is wrong.
 */
extern "C" s32 func_004087A0(s32 record, s32 index)
{
    if (index <= 0 || index >= 10)
    {
        return -1;
    }

    s32 base = (record - 1) * 10;
    u32 sum = 0;

    for (s32 i = base + 1; i < base + 10; i++)
    {
        sum += D_001B64B4[i];
    }

    u8 checksum = -(sum + record * 3);
    u8* entry = D_001B64B4 + base;

    if (checksum == entry[0])
    {
        return entry[index];
    }

    s32 bad = 226;
    return bad + 24;
}

#pragma pop

/** Mastery level steps of each battle skill: nine steps, then a check byte. */
extern "C" u8* D_001B64C8;

/** Mastery level steps of each symbology, laid out like D_001B64C8. */
extern "C" u8* D_001B64C4;

/** Per-character mastery level steps of the character-specific battle skills, laid out like D_001B64C8. */
extern "C" u8* D_00507C00[10];

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
extern "C" s32 func_00408850(void* detail, s32 code, s32 index, s32* kind, s32* value, s32* result_index, s32* remainder)
{
    LibCharacterEquipment* equipment = static_cast<LibCharacterEquipment*>(detail);

    if (index < 0 || index >= 42 || code - 1 < 0 || code - 1 >= 10)
    {
        return 0;
    }

    s32 table = code - 1;

    s32 entry;
    s32 mastery;
    u8* steps;

    if (index < 26)
    {
        entry = D_001B64D0->high_codes[index].code;
        mastery = lib_equipment_battle_skill_mastery(equipment, index);
        steps = D_001B64C8 + index * 10;
    }
    else
    {
        // TODO: The game adds the entry offset before the table's; indexing D_001B64D0[table] adds them the other way.
        LibCodeListEntry* codes = &D_001B64D0->high_codes[index];
        entry = codes[table * (sizeof(LibCodeTable) / sizeof(LibCodeListEntry))].code;

        if (entry > 0 && entry < 30)
        {
            s32 position = func_0040AF10(code, entry);
            mastery = lib_equipment_symbology_mastery(equipment, position);
            steps = D_001B64C4 + (entry - 1) * 10;
        }
        else
        {
            mastery = lib_equipment_battle_skill_mastery(equipment, index);
            // TODO: Only a separate index local and the offset added afterwards match here.
            s32 id = code - 1;
            steps = D_00507C00[id];
            steps += (index - 26) * 10;
        }
    }

    if (kind != 0)
    {
        *kind = entry;
    }

    if (entry == 0 || mastery == 0)
    {
        return 0;
    }

    s32 sign;

    if (mastery < 0)
    {
        mastery = -mastery;
        sign = -1;
    }
    else
    {
        sign = 1;
    }

    if (value != 0)
    {
        *value = mastery - 1;
    }

    u8 found = 0;
    s32 total = 0;
    u8 valid = func_00408E20(steps, entry);

    for (s32 i = 0; i < 9; i++)
    {
        total += *steps;

        if (mastery - 1 < total)
        {
            if (result_index != 0)
            {
                *result_index = i + 1;
            }

            if (remainder != 0)
            {
                *remainder = total - (mastery - 1);
            }

            found = 1;
            break;
        }

        steps++;
    }

    if (!found)
    {
        if (result_index != 0)
        {
            *result_index = 10;
        }

        if (remainder != 0)
        {
            *remainder = 0;
        }
    }

    if (!valid)
    {
        if (result_index != 0)
        {
            *result_index = 1;
        }

        if (remainder != 0)
        {
            *remainder = 76;
            *remainder += 13;
        }
    }

    return sign;
}

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

/** Three codes the combined code 0x90 stands for. */
extern "C" u8 D_001B6198[3];

/** Three codes the combined code 0x91 stands for. */
extern "C" u8 D_001B619C[3];

/**
 * @brief Decode a battle skill index after validating the index checksum and the slot.
 * @param equipment Character equipment record.
 * @param slot Entry index, from zero through five.
 * @return The battle skill index plus one, or zero for an invalid checksum or slot.
 */
static inline s32 lib_battle_skill_index(LibCharacterEquipment* equipment, s32 slot)
{
    if (equipment->battle_skill_indices_checksum != battle_skill_indices_checksum(equipment->encoded_battle_skill_indices))
    {
        return 0;
    }

    if (slot < 0)
    {
        return 0;
    }

    if ((u32)slot >= 6)
    {
        return 0;
    }

    return equipment->encoded_battle_skill_indices[slot] ^ 0x77;
}

/**
 * @brief Resolve a symbology entry and its mastery step. Parts of the combined codes 0x90 and 0x91 only count while
 *        the combined symbology is unlearned, or, in mode zero, while it's set in battle skill slot four or five.
 * @param equipment Character equipment record.
 * @param code Code list ID, from one through ten.
 * @param index Entry index, from zero through thirty-one.
 * @param kind Optional destination for the entry's code.
 * @param value Optional destination for the mastery minus one.
 * @param result_index Optional destination for the mastery step, from one through ten.
 * @param remainder Optional destination for the amount left to the next step.
 * @param mode Nonzero to skip the battle skill slot check.
 * @return 1 or -1 by the sign of the mastery, or zero when the entry is unavailable.
 */
extern "C" s32 func_00408EA0(LibCharacterEquipment* equipment, s32 code, s32 index, s32* kind, s32* value, s32* result_index,
                             s32* remainder, s32 mode)
{
    s32 sign = 0;

    if (index < 0 || index >= 32 || code - 1 < 0 || code - 1 >= 10)
    {
        return 0;
    }

    s32 table = code - 1;
    // TODO: The level walk starts from the list pointer itself; a separate &entries[0].unk01 pointer doesn't match.
    const u8* level = reinterpret_cast<const u8*>(&D_001B64CC[table]);
    s32 entry = level[index * 2];
    level++;
    s32 sum = 0;

    for (s32 i = 0; i < LIB_CODE_LIST_ENTRY_COUNT; i++, level += 2)
    {
        sum += *level;
    }

    if (*level != (u8)(sum * 17))
    {
        return 0;
    }

    if (kind != 0)
    {
        *kind = entry;
    }

    s32 mastery = lib_equipment_symbology_mastery(equipment, index);

    if (entry == 0)
    {
        return 0;
    }

    if (mastery <= -1)
    {
        mastery = -mastery;
        sign = -1;
    }
    else if (mastery > 0)
    {
        sign = 1;
    }
    else if (mastery == 0)
    {
        return 0;
    }

    u8 plain = 0;

    if (code - 1 == 1 || code - 1 == 8)
    {
        plain = 1;
    }
    else if (D_001B64CC[table].entries[index].unk01 != 0xFF)
    {
        plain = 1;
    }

    if (!plain)
    {
        for (s32 pass = 0; pass < 2; pass++)
        {
            const u8* parts;
            s32 combined;
            // TODO: Both arms set the part count, which keeps it in a register like the game's.
            s32 count;

            if (pass == 0)
            {
                count = 3;
                parts = D_001B6198;
                combined = 0x90;
            }
            else
            {
                count = 3;
                parts = D_001B619C;
                combined = 0x91;
            }

            for (s32 j = 0; j < count; j++)
            {
                if (entry != parts[j])
                {
                    continue;
                }

                if (lib_equipment_battle_skill_mastery(equipment, func_0040AE00(code, combined)) == 0)
                {
                    sign = 0;
                    continue;
                }

                if (mode != 0)
                {
                    goto resolved;
                }

                s32 saved = sign;
                sign = 0;

                for (s32 slot = 0; slot < 2; slot++)
                {
                    s32 skill = lib_battle_skill_index(equipment, slot + 4);

                    if (skill > 0)
                    {
                        s32 skill_kind;
                        func_00408850(equipment, code, skill - 1, &skill_kind, 0, 0, 0);

                        if (skill_kind == combined)
                        {
                            sign = saved;
                            goto resolved;
                        }
                    }
                }

                goto done;
            }
        }
    }

resolved:
    if (value != 0)
    {
        *value = mastery - 1;
    }

    u8 found = 0;
    u8* steps = D_001B64C4 + (entry - 1) * 10;
    s32 total = 0;

    if (!func_00408E20(steps, entry))
    {
        if (result_index != 0)
        {
            *result_index = 1;
        }

        if (remainder != 0)
        {
            *remainder = 18;
            *remainder += 81;
        }

        goto done;
    }

    for (s32 i = 0; i < 9; i++)
    {
        total += *steps;

        if (mastery - 1 < total)
        {
            if (result_index != 0)
            {
                *result_index = i + 1;
            }

            if (remainder != 0)
            {
                *remainder = total - (mastery - 1);
            }

            found = 1;
            break;
        }

        steps++;
    }

    if (!found)
    {
        if (result_index != 0)
        {
            *result_index = 10;
        }

        if (remainder != 0)
        {
            *remainder = 0;
        }
    }

done:
    return sign;
}
