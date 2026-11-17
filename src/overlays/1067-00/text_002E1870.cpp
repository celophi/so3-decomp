#include "include_asm.h"
#include "clamp.h"
#include "overlays/1067-00/text_002E1870.h"
#include "overlays/1067-00/field_runtime.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/lib/character_record.h"
#include "main/utility.h"

extern "C" {

extern void func_002F30A0(FieldCountedList* list, void* value);


/** Partial attached state with two status words. */
typedef struct FieldAttached148
{
    u8 pad[0x48];
    u32 value48;
    u8 pad4C[0xFC];
    u32 value148;
} FieldAttached148;

/** Partial active holder of the attached state. */
typedef struct FieldInner20
{
    u8 pad[0x14];
    FieldAttached148* attached;
    u8 pad18[8];
    u8 active20;
} FieldInner20;

struct FieldOuter14
{
    u8 pad[0x14];
    FieldInner20* inner;
};

// Packed-record checksum; repeated-load code generation remains unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E1870);

// Rolling checksum; loop scheduling remains unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E18E0);

// Large dispatcher; needs callback and runtime-record interfaces.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E19D0);

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

s32 func_002E80A0(const FieldCheckedWordsState1870* object)
{
    u32 check = object->unkA8 ^ (object->unk60 ^ (object->unk58 + object->unk5C));

    if (object->unkA0 != check)
    {
        return 0;
    }

    return object->unk60 ^ 0x7DE3F7E3;
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

s32 func_002E8270(const FieldCheckedWordsState1870* object)
{
    u32 check = object->unkA8 ^ (object->unk48 ^ (object->unk40 + object->unk44));

    if (object->unk98 != check)
    {
        return 0;
    }

    return object->unk48 ^ 0x7DE3F7E3;
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

s32 func_002E8440(const FieldCheckedWordsState1870* object)
{
    u32 check = object->unkA8 ^ (object->unk60 ^ (object->unk58 + object->unk5C));

    if (object->unkA0 != check)
    {
        return 0;
    }

    return object->unk6C ^ 0x7DE3F7E3;
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

s32 func_002E8600(const FieldCheckedWordsState1870* object)
{
    u32 check = object->unkA8 ^ (object->unk3C ^ (object->unk34 + object->unk38));

    if (object->unk94 != check)
    {
        return 0;
    }

    return object->unk3C ^ 0x7DE3F7E3;
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

// Checked-value getter; failure-path register allocation remains unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E88F0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8BC0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8D00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8DA0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8EE0);

s32 func_002ECF70(FieldObject15B9A0* object)
{
    return 4;
}

u8 func_002ECF80(FieldObject15B9A0* object)
{
    return object->unk68;
}

s16 func_002ECF90(FieldObject15B9A0* object, s32 index)
{
    return object->unk5E[index];
}

void func_002ECFA0(FieldObject15B9A0* object, s16 index)
{
    object->unk64 = index;
    object->unk5E[object->unk64] = -1;
    object->unk5C[object->unk64] = 0;
    object->unk80 = 0;
    object->unk84 = 0;
    object->unk68 = 0;
}

u16 func_002ECFE0(const FieldOuter14* object)
{
    FieldAttached148* attached;
    u16 flags;

    if (!object->inner->active20)
    {
        return 0;
    }

    attached = object->inner->attached;
    flags = 0;

    if (attached->value48 == 2)
    {
        flags |= 1;
    }

    if (attached->value148 == 2)
    {
        flags |= 2;
    }

    return flags;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002ED040);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002ED130);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002ED240);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002ED8D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDB20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDC90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDD20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDDB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDEC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDFA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDFD0);

u16 func_002EE9B0(const FieldObject2EDFD0* object)
{
    return object->unk1050;
}

s32 func_002EE9C0(FieldObject2EDFD0* object, void* value)
{
    if (value == 0)
    {
        return 0;
    }

    object->unk1254 = value;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EE9E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EEB30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EEC90);

u8 func_002EED90(const FieldObject2EDFD0* object)
{
    return object->unk121E;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EEDA0);

void func_002EEE00(FieldObject2EDFD0* object, void* value)
{
    func_002F30A0((FieldCountedList*)((u8*)object + 0x104C), value);
}

void func_002EEE20(FieldObject2EDFD0* object, s16 value, u8 flag)
{
    object->unk105E = value;
    object->unk1060 = flag;
}

void* func_002EEE30(void* object, s32 index)
{
    ResidentSystem* system;
    FieldRuntimeSections* sections;
    u8* base;
    system = resident_get_system();
    sections = (FieldRuntimeSections*)resident_get_entry_table(system);
    base = (u8*)resident_find_entry(sections, 4);
    return base + 0xC6B0 + (index - 1) * 24;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EEE90);

FieldTransfer2EDFD0* func_002EF000(FieldObject2EDFD0* object)
{
    return &object->unkFF8;
}

void func_002EF010(FieldObject2EDFD0* object, s16 value)
{
    if (value > 50)
    {
        object->unk105A = 50;
    }

    object->unk105A = value;
}

s32 func_002EF030(FieldObject2EDFD0* object, s16 index)
{
    if (index < 0 || index > object->unk105A)
    {
        return 0;
    }

    object->unk1058 = index;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EF070);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EF2B0);

// Header validation; inline comparison and result handling remain unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EF520);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EF6B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EFFF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F0190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F0750);

// Header validation; inline comparison register allocation remains unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F0D90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F0EF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F11F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F17F0);
}
