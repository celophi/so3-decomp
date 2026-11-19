#ifndef SO3_EE_H
#define SO3_EE_H

#include "types.h"

/*
 * EE instruction helpers the game wrote inline.
 */

#define UNCACHED_SEGMENT 0x20000000
#define EE_UNCACHED_ACCELERATED 0x30000000
#define EE_SCRATCHPAD 0x70000000
#define DMA_ADDRESS_SCRATCHPAD 0x80000000
#define DMA_TAG_ID_CNT 0x10000000
#define DMA_TAG_ID_NEXT 0x20000000
#define DMA_TAG_ID_REF 0x30000000
#define DMA_TAG_ID_CALL 0x50000000
#define DMA_TAG_ID_END 0x70000000
#define DMA_TAG(qwc, id, address) ((u64)(qwc) | (id) | ((u64)(u32)(address) << 32))

#define DMA_CHCR_DIR_FROM_MEMORY 0x1
#define DMA_CHCR_MODE_CHAIN 0x4
#define DMA_CHCR_TAG_TRANSFER 0x40
#define DMA_CHCR_START 0x100

/** DMA channel 8 (scratchpad to memory) registers, and the DMA status and priority registers. */
#define D8_CHCR ((volatile u32*)0x1000D000)
#define D8_MADR ((volatile u32*)0x1000D010)
#define D8_QWC ((volatile u32*)0x1000D020)
#define D8_SADR ((volatile u32*)0x1000D080)
#define D_STAT ((volatile u32*)0x1000E010)
#define D_PCR ((volatile u32*)0x1000E020)

/** DMA channel 9 (memory to scratchpad) registers. */
#define D9_CHCR ((volatile u32*)0x1000D400)
#define D9_MADR ((volatile u32*)0x1000D410)
#define D9_QWC ((volatile u32*)0x1000D420)
#define D9_SADR ((volatile u32*)0x1000D480)

/** DMA channel 0 (VIF0) registers. */
#define D0_CHCR ((volatile u32*)0x10008000)
#define D0_QWC ((volatile u32*)0x10008020)
#define D0_TADR ((volatile u32*)0x10008030)

/** DMA channel 1 (VIF1) registers. */
#define D1_CHCR ((volatile u32*)0x10009000)
#define D1_MADR ((volatile u32*)0x10009010)
#define D1_QWC ((volatile u32*)0x10009020)
#define D1_TADR ((volatile u32*)0x10009030)

/** DMA channel 3 (IPU to memory) registers. */
#define D3_CHCR ((volatile u32*)0x1000B000)
#define D3_MADR ((volatile u32*)0x1000B010)
#define D3_QWC ((volatile u32*)0x1000B020)

/** DMA channel 4 (memory to IPU) registers. */
#define D4_CHCR ((volatile u32*)0x1000B400)
#define D4_MADR ((volatile u32*)0x1000B410)
#define D4_QWC ((volatile u32*)0x1000B420)
#define D4_TADR ((volatile u32*)0x1000B430)

/** DMA enable registers: reading D_ENABLER and writing D_ENABLEW with D_ENABLE_SUSPEND set holds every channel. */
#define D_ENABLER ((volatile u32*)0x1000F520)
#define D_ENABLEW ((volatile u32*)0x1000F590)
#define D_ENABLE_SUSPEND 0x10000

/** IPU control register; IPU_CTRL_IFC is the input FIFO's quadword count. */
#define IPU_CTRL ((volatile u32*)0x10002010)
#define IPU_CTRL_IFC 0xF0

/** IPU bit pointer: the bit position in the current quadword, FIFO quadword count and FIFO position. */
#define IPU_BP ((volatile u32*)0x10002020)

#define D_STAT_CIS0 0x1
#define D_STAT_CIS1 0x2
#define D_STAT_CIS8 0x100
#define D_STAT_CIS9 0x200
#define D_PCR_CPC8 0x100
#define D_PCR_CPC9 0x200

/** EE timer 0 counter and mode. */
#define TIMER0_COUNT (*(volatile u32*)0x10000000)
#define TIMER0_MODE (*(volatile u32*)0x10000010)

#define TIMER_MODE_CLOCK_HBLANK 0x3
#define TIMER_MODE_COUNT_ENABLE 0x80

/** VIF codes: STCYCL, and UNPACK with its formats and flags. */
#define VIF_STCYCL(cl, wl) (0x01000000 | ((wl) << 8) | (cl))

/** VIF MSCALF: wait for the GIF and the running microprogram, then start the one at address (in doublewords). */
#define VIF_MSCALF(address) (0x15000000 | (address))

#define VIF_FLUSH 0x11000000
#define VIF_DIRECTHL(quadwords) (0x51000000 | (quadwords))
#define VIF_UNPACK(format, num, address) (((num) << 16) | ((format) << 24) | (address))
#define VIF_UNPACK_S_8 0x62
#define VIF_UNPACK_V4_32 0x6C
#define VIF_UNPACK_V4_16 0x6D
#define VIF_UNPACK_V4_8 0x6E
#define VIF_UNPACK_V2_16_MASKED 0x75
#define VIF_UNPACK_UNSIGNED 0x4000
#define VIF_UNPACK_ADD_TOPS 0x8000

/**
 * @brief Return the EE scalar maximum of two floating-point operands.
 * @param left First operand.
 * @param right Second operand.
 * @return Maximum produced by the EE scalar instruction.
 * @see Silent Hill 2/3 (CodeWarrior) has the same one-instruction float_max
 *      (https://github.com/dreamingmoths/memory-of-alessa, include/math.h).
 */
static inline float ee_max(float left, float right)
{
    float result;
    asm __volatile__("max.s %0, %1, %2" : "=f"(result) : "f"(left), "f"(right));
    return result;
}

/**
 * @brief Return the absolute value of a floating-point operand with the EE scalar instruction.
 * @param value Operand.
 * @return Absolute value produced by the EE scalar instruction.
 * @see abs.s in the EE Core Instruction Set Manual; SO3 keeps one whose result is never used (main 0x10E4B0), and
 *      lib 0x456360 keeps its offset wrap loops unrotated, which only an asm statement in the function gives.
 */
static inline float ee_abs(float value)
{
    // TODO: This is asm because the compiler drops an unused abs and rotates loops next to a plain one; check whether
    // the original was asm too.
    float result;
    asm __volatile__("abs.s %0, %1" : "=f"(result) : "f"(value));
    return result;
}

/**
 * @brief Return the EE scalar minimum of two floating-point operands.
 * @param left First operand.
 * @param right Second operand.
 * @return Minimum produced by the EE scalar instruction.
 * @see Silent Hill 2/3 (CodeWarrior) has the same one-instruction float_min
 *      (https://github.com/dreamingmoths/memory-of-alessa, include/math.h).
 */
static inline float ee_min(float left, float right)
{
    float result;
    asm __volatile__("min.s %0, %1, %2" : "=f"(result) : "f"(left), "f"(right));
    return result;
}

#ifdef __cplusplus
/**
 * @brief Return the EE scalar maximum of a value and a float read in place.
 *
 * The same max.s as ee_max, but the second operand is read through the
 * reference rather than copied into a parameter.
 * @param left First operand.
 * @param right Second operand, usually a field.
 * @return Maximum produced by the EE scalar instruction.
 * @see Silent Hill 2/3 (CodeWarrior) has the same one-instruction float_max
 *      (https://github.com/dreamingmoths/memory-of-alessa, include/math.h).
 */
static inline float ee_max_in_place(float left, const float& right)
{
    float result;
    asm __volatile__("max.s %0, %1, %2" : "=f"(result) : "f"(left), "f"(right));
    return result;
}
#endif

/**
 * @brief Request cache prefetch for the supplied address.
 *
 * No memory clobber: pref is only a cache hint and doesn't order loads or
 * stores.
 * @param address Address to prefetch.
 * @see Code Veronica X (CodeWarrior) has the same PREFETCH macro
 *      (https://github.com/AshfordFamily/recvx-decomp,
 *      include/ps2/veronica/prog/macros.h), as does ps2dev gsKit's
 *      GSKIT_PREFETCH (ee/gs/include/gsInit.h).
 */
static inline void ee_prefetch(const void* address)
{
    asm __volatile__("pref 0, 0(%0)" : : "r"(address));
}

/**
 * @brief Prefetch the cache line 0x40 bytes past an address (one pref with an offset).
 * @param address Base address.
 * @see ee_prefetch; Lib's morph loop at 0x4A9600 prefetches two 0x20-byte records ahead this way.
 */
static inline void ee_prefetch_ahead(const void* address)
{
    asm __volatile__("pref 0, 0x40(%0)" : : "r"(address));
}

/**
 * @brief Wait for every earlier load and store to finish (one sync).
 *
 * The game issues this between writing a packet's end tag and handing the
 * packet to DMA, so the tag is in memory before the transfer reads it.
 * @see ps2sdk has the same one-instruction EE_SYNC
 *      (https://github.com/ps2dev/ps2sdk, ee/kernel/include/kernel.h).
 */
static inline void ee_sync(void)
{
    asm __volatile__("sync");
}

/**
 * @brief Finish an interrupt handler (sync, then ei).
 *
 * Every interrupt and SIF command handler in the game ends with this pair
 * before it returns, as a workaround for an EE kernel bug.
 * @see ps2sdk has the same pair as ExitHandler
 *      (https://github.com/ps2dev/ps2sdk, ee/kernel/include/kernel.h).
 */
static inline void ee_exit_handler(void)
{
    asm __volatile__("sync\nei");
}

#define EE_STATUS_EIE 0x10000

/**
 * @brief Read the COP0 Status register (one mfc0).
 * @return The Status register.
 * @see ps2sdk reads it the same way with get_mips_cop_reg(0, COP0_REG_Status)
 *      (https://github.com/ps2dev/ps2sdk, common/include/mipscopaccess.h).
 */
static inline u32 ee_get_status(void)
{
    // The game clears it before the read; one request wrapper keeps that dead move.
    u32 status = 0;
    asm __volatile__("mfc0 %0, $12" : "=r"(status));
    return status;
}

/**
 * @brief Pack the low halfword of each word of two quadwords into one quadword with the EE's PPACH instruction.
 * @param high Quadword whose halfwords fill the upper half of the result.
 * @param low Quadword whose halfwords fill the lower half of the result.
 * @return The packed quadword.
 * @see EE Core Instruction Set Manual (PPACH); SO3's stream copy at main 0x109800 is the one user.
 */
static inline unsigned __int128 ee_pack_halfwords(unsigned __int128 high, unsigned __int128 low)
{
    // TODO: This is asm because the compiler has no way to write PPACH; check whether the original was asm too.
    unsigned __int128 result;
    asm __volatile__("ppach %0, %1, %2" : "=r"(result) : "r"(high), "r"(low));
    return result;
}

/**
 * @brief Transpose a 16-byte-aligned 4x4 matrix of words with the EE's 128-bit MMI instructions.
 *
 * The registers are fixed ($t0-$t7) because every copy in the game uses the
 * same ones: about 115 functions across main, lib, 1067-00, 1070-00, 3253-00
 * and 3454-00 have this exact sequence.
 * @param out Aligned destination matrix.
 * @param in Aligned source matrix.
 * @see EE Core Instruction Set Manual (PEXTLW, PEXTUW, PCPYLD, PCPYUD, LQ, SQ).
 */
static inline void ee_transpose_matrix(void* out, const void* in)
{
    asm __volatile__("lq       $8, 0x0(%1)\n"
                     "lq       $9, 0x10(%1)\n"
                     "lq       $10, 0x20(%1)\n"
                     "lq       $11, 0x30(%1)\n"
                     "pextlw   $12, $9, $8\n"
                     "pextuw   $13, $9, $8\n"
                     "pextlw   $14, $11, $10\n"
                     "pextuw   $15, $11, $10\n"
                     "pcpyld   $8, $14, $12\n"
                     "pcpyud   $9, $12, $14\n"
                     "pcpyld   $10, $15, $13\n"
                     "pcpyud   $11, $13, $15\n"
                     "sq       $8, 0x0(%0)\n"
                     "sq       $9, 0x10(%0)\n"
                     "sq       $10, 0x20(%0)\n"
                     "sq       $11, 0x30(%0)\n"
                     :
                     : "r"(out), "r"(in)
                     : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

/*
 * My guess is the game wanted branchless selects that weren't at the mercy of
 * bad branch prediction, and the compiler only sometimes turns a ?: into
 * movn/movz on its own. Being volatile also stops the compiler's later cleanup
 * in the same block, which is why the target keeps an `andi 0xFF` after each
 * later compare. TODO: come back to this if a better explanation turns up.
 */

/**
 * @brief Return replacement if condition is non-zero, otherwise value (one movn).
 * @param value Value kept when condition is zero.
 * @param replacement Value used when condition is non-zero.
 * @param condition Selector.
 * @return The selected value.
 * @see https://decomp.me/scratch/e8lkP
 */
static inline s32 ee_movn(s32 value, s32 replacement, s32 condition)
{
    asm __volatile__("movn %0, %1, %2" : "+r"(value) : "r"(replacement), "r"(condition));
    return value;
}

/**
 * @brief Return replacement if condition is zero, otherwise value (one movz).
 * @param value Value kept when condition is non-zero.
 * @param replacement Value used when condition is zero.
 * @param condition Selector.
 * @return The selected value.
 * @see https://decomp.me/scratch/e8lkP
 */
static inline s32 ee_movz(s32 value, s32 replacement, s32 condition)
{
    asm __volatile__("movz %0, %1, %2" : "+r"(value) : "r"(replacement), "r"(condition));
    return value;
}

#endif
