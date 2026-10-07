#ifndef SO3_OVERLAYS_1067_00_DEVELOPMENT_LINE_TARGET_H
#define SO3_OVERLAYS_1067_00_DEVELOPMENT_LINE_TARGET_H

#include "overlays/1067-00/text_002F1B20.h"

#ifdef __cplusplus
/** Common data prefix preceding the target callback table at offset 0x8C. */
struct ItemCreationTargetPrefix : public FieldStateTargets
{
    u8 unk88[4];
};
/** @brief Partial callback interface for a development-line target. */
class ItemCreationClass184EF0 : public ItemCreationTargetPrefix
{
public:
    /** @brief Run the target status callback. @return Callback status. */
    virtual s32 func_slot08();
    /** @brief Run the target update callback. */
    virtual void func_slot0c();
    /** @brief Run the additional target callback. */
    virtual void func_slot10();
};

/** Partial category-one target selected by native MAIN15BB30. */
class FieldClass15BB30 : public ItemCreationClass184EF0
{
public:
    /** @brief Advance this development target. @return Zero or one. */
    virtual s32 func_slot08();
    /** @brief Apply the target result and clear active inventor flags. */
    virtual void func_slot0c();
    /** @brief Clear the target's active inventor flags. */
    virtual void func_slot10();

    u8 unk90[0x320];
    s32 unk3b0;
    u8 unk3b4[0x14];
    u16 unk3c8;
};

/** Development target with an allocation index at offset 0x94. */
class FieldClass15BB50 : public ItemCreationClass184EF0
{
public:
    /** @brief Advance this development target. @return Target status from zero through two. */
    virtual s32 func_slot08();
    /** @brief Apply the target result and clear active inventor flags. */
    virtual void func_slot0c();
    /** @brief Clear the target's active inventor flags. */
    virtual void func_slot10();

    u8 unk90[4];
    s16 unk94;
    u8 unk96[0x22];
};
/** Development target with an allocation index at offset 0xE0. */
class FieldClass15BB70 : public ItemCreationClass184EF0
{
public:
    /** @brief Advance this development target. @return Target status from zero through two. */
    virtual s32 func_slot08();
    /** @brief Apply the target result and clear active inventor flags. */
    virtual void func_slot0c();
    /** @brief Clear the target's active inventor flags. */
    virtual void func_slot10();

    u8 unk90[0x50];
    s16 unke0;
    u8 unke2[0x26];
};
#endif

#endif
