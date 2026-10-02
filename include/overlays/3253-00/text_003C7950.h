#ifndef SO3_OVERLAYS_3253_00_TEXT_003C7950_H
#define SO3_OVERLAYS_3253_00_TEXT_003C7950_H

#include "types.h"

/** Partial Battle record-array interface with fields at offsets 0x0C-0x20. */
struct BattleArrayAccess
{
    u8 unk00[0xC];
    u32 unk0c;
    s32 unk10;
    u8* unk14;
    u32 unk18;
    u32 unk1c;
    u8* unk20;
};

/** Partial object with adjacent words at offsets 0xB0 and 0xB4. */
struct BattlePairedWords
{
    u8 unk00[0xB0];
    u32 unkB0;
    u32 unkB4;
};

/** Partial receiver with two pointers and a state byte at offset 0x50. */
struct BattleLinkState
{
    u8 unk00[0x48];
    u8* unk48;
    void* unk4c;
    u8 unk50;
};

/** Partial receiver with a state byte at offset 0x60. */
struct BattleState60
{
    u8 unk00[0x60];
    u8 unk60;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C7B50(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_003C7B60(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003C9970(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_003C9980(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CCE60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCE70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCE90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCEA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCEB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCEC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCED0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCEE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCEF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CCF00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCF10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCF20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCF30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CCF40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCF50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCF60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCF70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCF80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCF90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CCFA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCFB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CCFC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCFD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CCFF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD000(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD010(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD020(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD030(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD040(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD060(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD070(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD090(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD0A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD0B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD0C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD0D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD0E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD0F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD100(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD110(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD120(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD130(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD140(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD150(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD160(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD170(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD180(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD190(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD1A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD1B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD1C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD1D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD1F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD200(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD210(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD220(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD230(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD240(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD260(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD270(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD290(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD2A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD2B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD2C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD2D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD2E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD2F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD300(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD310(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD320(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD330(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD340(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD350(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD360(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD370(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD380(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD390(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD3A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD3B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD3C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD3D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD3F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD400(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD410(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD420(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD430(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD440(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD460(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD470(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD490(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD4A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD4B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD4C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD4D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD4E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD4F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD500(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD510(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD520(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD530(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD550(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD580(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD590(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD5A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD5B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD5C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD5D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD5F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD600(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD610(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD620(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD630(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD640(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD660(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD670(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD690(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD6A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD6B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD6C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD6D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD6E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD6F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD700(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD710(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD720(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD730(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD740(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD750(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD760(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD770(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD780(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD790(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD7A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD7B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD7C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD7D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD7F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD800(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD810(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD820(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD830(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD840(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD860(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD870(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD890(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD8A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD8B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD8C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD8D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD8E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD8F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD900(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD910(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD920(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD930(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD940(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD950(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD960(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD970(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD980(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD990(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD9A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD9B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CD9C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD9D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CD9F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDA00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDA10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDA20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDA30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDA40(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDA60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDA70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDA90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDAA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDAB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDAC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDAD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDAE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDAF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDB00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDB10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDB20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDB30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDB40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDB50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDB60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDB70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDB80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDB90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDBA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDBB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDBC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDBD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDBF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDC00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDC10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDC20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDC30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDC40(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDC60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDC70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDC90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDCA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDCB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDCC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDCD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDCE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDCF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDD00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDD10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDD20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDD30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDD40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDD50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDD60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDD70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDD80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDD90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDDA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDDB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDDC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDDD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDDF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDE00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDE10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDE20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003CDE30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003CDE40(void* object);

/**
 * @brief Return the fixed value 35.
 * @param object Receiver or first argument; unused.
 * @return Always 35.
 */
s32 func_003CE570(void* object);

/**
 * @brief Return the fixed value 35.
 * @param object Receiver or first argument; unused.
 * @return Always 35.
 */
s32 func_003CE690(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003CE7C0(void* object);

/**
 * @brief Return the fixed value 35.
 * @param object Receiver or first argument; unused.
 * @return Always 35.
 */
s32 func_003CEF20(void* object);

/**
 * @brief Return the fixed value 35.
 * @param object Receiver or first argument; unused.
 * @return Always 35.
 */
s32 func_003CF690(void* object);

/**
 * @brief Return the fixed value 35.
 * @param object Receiver or first argument; unused.
 * @return Always 35.
 */
s32 func_003CFDD0(void* object);

/**
 * @brief Return the fixed value 35.
 * @param object Receiver or first argument; unused.
 * @return Always 35.
 */
s32 func_003CFEF0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003D0670(void* object);


/**
 * @brief Store both words at offsets 0xB0 and 0xB4.
 * @param object Receiver.
 * @param first First word.
 * @param second Second word.
 */
void func_003C7950(BattlePairedWords* object, u32 first, u32 second);

/**
 * @brief Clear both words at offsets 0xB0 and 0xB4.
 * @param object Receiver.
 */
void func_003C7960(BattlePairedWords* object);

/**
 * @brief Return 100.
 * @param object Receiver.
 * @return 100.0f.
 */
float func_003CCE80(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CCFE0(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CD050(void* object);

/**
 * @brief Return 100.
 * @param object Receiver.
 * @return 100.0f.
 */
float func_003CD080(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CD1E0(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CD250(void* object);

/**
 * @brief Return 100.
 * @param object Receiver.
 * @return 100.0f.
 */
float func_003CD280(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CD3E0(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CD450(void* object);

/**
 * @brief Return 100.
 * @param object Receiver.
 * @return 100.0f.
 */
float func_003CD480(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CD5E0(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CD650(void* object);

/**
 * @brief Return 100.
 * @param object Receiver.
 * @return 100.0f.
 */
float func_003CD680(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CD7E0(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CD850(void* object);

/**
 * @brief Return 100.
 * @param object Receiver.
 * @return 100.0f.
 */
float func_003CD880(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CD9E0(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CDA50(void* object);

/**
 * @brief Return 100.
 * @param object Receiver.
 * @return 100.0f.
 */
float func_003CDA80(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CDBE0(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CDC50(void* object);

/**
 * @brief Return 100.
 * @param object Receiver.
 * @return 100.0f.
 */
float func_003CDC80(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CDDE0(void* object);

/**
 * @brief Return zero.
 * @param object Receiver.
 * @return 0.0f.
 */
float func_003CDE50(void* object);

/**
 * @brief Find a record in the array at offset 0x14.
 * @param object Receiver.
 * @param index Record index.
 * @return Selected record address.
 */
u8* func_003CE510(const BattleArrayAccess* object, s32 index);

/**
 * @brief Find a record in the two-dimensional array at offset 0x20.
 * @param object Receiver.
 * @param row Row index.
 * @param column Column index.
 * @return Selected record address.
 */
u8* func_003CE530(const BattleArrayAccess* object, s32 row, s32 column);

/**
 * @brief Read the word at offset 0x0C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CE550(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CE560(const BattleArrayAccess* object);

/**
 * @brief Find a record in the array at offset 0x14.
 * @param object Receiver.
 * @param index Record index.
 * @return Selected record address.
 */
u8* func_003CE620(const BattleArrayAccess* object, s32 index);

/**
 * @brief Find a record in the two-dimensional array at offset 0x20.
 * @param object Receiver.
 * @param row Row index.
 * @param column Column index.
 * @return Selected record address.
 */
u8* func_003CE640(const BattleArrayAccess* object, s32 row, s32 column);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CE660(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x0C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CE670(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CE680(const BattleArrayAccess* object);

/**
 * @brief Check whether the record pointer at offset 0x14 is set.
 * @param object Receiver.
 * @return True when the pointer is nonnull.
 */
bool func_003CE6A0(const BattleArrayAccess* object);

/**
 * @brief Find a record in the array at offset 0x14.
 * @param object Receiver.
 * @param index Record index.
 * @return Selected record address.
 */
u8* func_003CE750(const BattleArrayAccess* object, s32 index);

/**
 * @brief Find a record in the two-dimensional array at offset 0x20.
 * @param object Receiver.
 * @param row Row index.
 * @param column Column index.
 * @return Selected record address.
 */
u8* func_003CE770(const BattleArrayAccess* object, s32 row, s32 column);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CE790(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x0C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CE7A0(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CE7B0(const BattleArrayAccess* object);

/**
 * @brief Find a record in the array at offset 0x14.
 * @param object Receiver.
 * @param index Record index.
 * @return Selected record address.
 */
u8* func_003CEEC0(const BattleArrayAccess* object, s32 index);

/**
 * @brief Find a record in the two-dimensional array at offset 0x20.
 * @param object Receiver.
 * @param row Row index.
 * @param column Column index.
 * @return Selected record address.
 */
u8* func_003CEEE0(const BattleArrayAccess* object, s32 row, s32 column);

/**
 * @brief Read the word at offset 0x0C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CEF00(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CEF10(const BattleArrayAccess* object);

/**
 * @brief Find a record in the array at offset 0x14.
 * @param object Receiver.
 * @param index Record index.
 * @return Selected record address.
 */
u8* func_003CF620(const BattleArrayAccess* object, s32 index);

/**
 * @brief Find a record in the two-dimensional array at offset 0x20.
 * @param object Receiver.
 * @param row Row index.
 * @param column Column index.
 * @return Selected record address.
 */
u8* func_003CF640(const BattleArrayAccess* object, s32 row, s32 column);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CF660(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x0C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CF670(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CF680(const BattleArrayAccess* object);

/**
 * @brief Find a record in the array at offset 0x14.
 * @param object Receiver.
 * @param index Record index.
 * @return Selected record address.
 */
u8* func_003CFD80(const BattleArrayAccess* object, s32 index);

/**
 * @brief Find a record in the two-dimensional array at offset 0x20.
 * @param object Receiver.
 * @param row Row index.
 * @param column Column index.
 * @return Selected record address.
 */
u8* func_003CFD90(const BattleArrayAccess* object, s32 row, s32 column);

/**
 * @brief Read the word at offset 0x0C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CFDB0(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CFDC0(const BattleArrayAccess* object);

/**
 * @brief Find a record in the array at offset 0x14.
 * @param object Receiver.
 * @param index Record index.
 * @return Selected record address.
 */
u8* func_003CFE80(const BattleArrayAccess* object, s32 index);

/**
 * @brief Find a record in the two-dimensional array at offset 0x20.
 * @param object Receiver.
 * @param row Row index.
 * @param column Column index.
 * @return Selected record address.
 */
u8* func_003CFEA0(const BattleArrayAccess* object, s32 row, s32 column);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CFEC0(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x0C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CFED0(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003CFEE0(const BattleArrayAccess* object);

/**
 * @brief Check whether the record pointer at offset 0x14 is set.
 * @param object Receiver.
 * @return True when the pointer is nonnull.
 */
bool func_003CFF00(const BattleArrayAccess* object);

/**
 * @brief Find a record in the array at offset 0x14.
 * @param object Receiver.
 * @param index Record index.
 * @return Selected record address.
 */
u8* func_003D0600(const BattleArrayAccess* object, s32 index);

/**
 * @brief Find a record in the two-dimensional array at offset 0x20.
 * @param object Receiver.
 * @param row Row index.
 * @param column Column index.
 * @return Selected record address.
 */
u8* func_003D0620(const BattleArrayAccess* object, s32 row, s32 column);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003D0640(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x0C.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003D0650(const BattleArrayAccess* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_003D0660(const BattleArrayAccess* object);

/**
 * @brief Return one.
 * @param object Receiver.
 * @return 1.0f.
 */
float func_003D39F0(void* object);

/**
 * @brief Return one.
 * @param object Receiver.
 * @return 1.0f.
 */
float func_003D3A00(void* object);

/**
 * @brief Return one.
 * @param object Receiver.
 * @return 1.0f.
 */
float func_003D3A10(void* object);

/**
 * @brief Return one.
 * @param object Receiver.
 * @return 1.0f.
 */
float func_003D3A20(void* object);

/**
 * @brief Return one.
 * @param object Receiver.
 * @return 1.0f.
 */
float func_003D3A30(void* object);

/**
 * @brief Return one.
 * @param object Receiver.
 * @return 1.0f.
 */
float func_003D3A40(void* object);

/**
 * @brief Return one.
 * @param object Receiver.
 * @return 1.0f.
 */
float func_003D3A50(void* object);

/**
 * @brief Return one.
 * @param object Receiver.
 * @return 1.0f.
 */
float func_003D3A60(void* object);


/**
 * @brief Store two pointers and check whether the first points to byte 1.
 * @param object Receiver to update.
 * @param first First pointer.
 * @param second Second pointer.
 */
void func_003CB8F0(BattleLinkState* object, u8* first, void* second);

/**
 * @brief Store two pointers and check whether the first points to byte 1.
 * @param object Receiver to update.
 * @param first First pointer.
 * @param second Second pointer.
 */
void func_003CC010(BattleLinkState* object, u8* first, void* second);

/**
 * @brief Store two pointers and check whether the first points to byte 1.
 * @param object Receiver to update.
 * @param first First pointer.
 * @param second Second pointer.
 */
void func_003CC730(BattleLinkState* object, u8* first, void* second);

/**
 * @brief Store two pointers and check whether the first points to byte 1.
 * @param object Receiver to update.
 * @param first First pointer.
 * @param second Second pointer.
 */
void func_003CCE10(BattleLinkState* object, u8* first, void* second);

/**
 * @brief Clear both pointers and set the state byte from a flag.
 * @param object Receiver to update.
 * @param flag Nonzero sets the state byte to 1.
 */
void func_003CB910(BattleLinkState* object, s32 flag);

/**
 * @brief Clear both pointers and set the state byte from a flag.
 * @param object Receiver to update.
 * @param flag Nonzero sets the state byte to 1.
 */
void func_003CC030(BattleLinkState* object, s32 flag);

/**
 * @brief Clear both pointers and set the state byte from a flag.
 * @param object Receiver to update.
 * @param flag Nonzero sets the state byte to 1.
 */
void func_003CC750(BattleLinkState* object, s32 flag);

/**
 * @brief Clear both pointers and set the state byte from a flag.
 * @param object Receiver to update.
 * @param flag Nonzero sets the state byte to 1.
 */
void func_003CCE30(BattleLinkState* object, s32 flag);

/**
 * @brief Set the byte at offset 0x60 to 9.
 * @param object Receiver to update.
 */
void func_003D6CC0(BattleState60* object);

#ifdef __cplusplus
}
#endif

#endif
