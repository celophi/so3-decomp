#ifndef SO3_MAIN_LZ_COPY_H
#define SO3_MAIN_LZ_COPY_H

#include "types.h"

// TODO: These are asm because I could not get the compiler to copy this way; check whether the original was asm.

/**
 * @brief Copy three bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_3(u8* destination, const u8* source)
{
    asm __volatile__("lb $8, 0(%1)\n"
                     "lb $9, 1(%1)\n"
                     "lb $10, 2(%1)\n"
                     "sb $8, 0(%0)\n"
                     "sb $9, 1(%0)\n"
                     "sb $10, 2(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy four bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_4(u8* destination, const u8* source)
{
    asm __volatile__("lwl $8, 3(%1)\n"
                     "lwr $8, 0(%1)\n"
                     "swl $8, 3(%0)\n"
                     "swr $8, 0(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy five bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_5(u8* destination, const u8* source)
{
    asm __volatile__("lwl $8, 3(%1)\n"
                     "lwr $8, 0(%1)\n"
                     "lb $9, 4(%1)\n"
                     "swl $8, 3(%0)\n"
                     "swr $8, 0(%0)\n"
                     "sb $9, 4(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy six bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_6(u8* destination, const u8* source)
{
    asm __volatile__("lwl $8, 3(%1)\n"
                     "lwr $8, 0(%1)\n"
                     "lb $9, 4(%1)\n"
                     "lb $10, 5(%1)\n"
                     "swl $8, 3(%0)\n"
                     "swr $8, 0(%0)\n"
                     "sb $9, 4(%0)\n"
                     "sb $10, 5(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy seven bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_7(u8* destination, const u8* source)
{
    asm __volatile__("lwl $8, 3(%1)\n"
                     "lwr $8, 0(%1)\n"
                     "lb $9, 4(%1)\n"
                     "lb $10, 5(%1)\n"
                     "lb $11, 6(%1)\n"
                     "swl $8, 3(%0)\n"
                     "swr $8, 0(%0)\n"
                     "sb $9, 4(%0)\n"
                     "sb $10, 5(%0)\n"
                     "sb $11, 6(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy eight bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_8(u8* destination, const u8* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy nine bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_9(u8* destination, const u8* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "lb $9, 8(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sb $9, 8(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy ten bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_10(u8* destination, const u8* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "lb $9, 8(%1)\n"
                     "lb $10, 9(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sb $9, 8(%0)\n"
                     "sb $10, 9(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy eleven bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_11(u8* destination, const u8* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "lb $9, 8(%1)\n"
                     "lb $10, 9(%1)\n"
                     "lb $11, 10(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sb $9, 8(%0)\n"
                     "sb $10, 9(%0)\n"
                     "sb $11, 10(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy twelve bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_12(u8* destination, const u8* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "lwl $9, 11(%1)\n"
                     "lwr $9, 8(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "swl $9, 11(%0)\n"
                     "swr $9, 8(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy thirteen bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_13(u8* destination, const u8* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "lwl $9, 11(%1)\n"
                     "lwr $9, 8(%1)\n"
                     "lb $10, 12(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "swl $9, 11(%0)\n"
                     "swr $9, 8(%0)\n"
                     "sb $10, 12(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy fourteen bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_14(u8* destination, const u8* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "lwl $9, 11(%1)\n"
                     "lwr $9, 8(%1)\n"
                     "lb $10, 12(%1)\n"
                     "lb $11, 13(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "swl $9, 11(%0)\n"
                     "swr $9, 8(%0)\n"
                     "sb $10, 12(%0)\n"
                     "sb $11, 13(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy fifteen bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_15(u8* destination, const u8* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "lwl $9, 11(%1)\n"
                     "lwr $9, 8(%1)\n"
                     "lb $10, 12(%1)\n"
                     "lb $11, 13(%1)\n"
                     "lb $12, 14(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "swl $9, 11(%0)\n"
                     "swr $9, 8(%0)\n"
                     "sb $10, 12(%0)\n"
                     "sb $11, 13(%0)\n"
                     "sb $12, 14(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy sixteen bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_16(u8* destination, const u8* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy seventeen bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_17(u8* destination, const u8* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "lb $10, 16(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)\n"
                     "sb $10, 16(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy eighteen bytes, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_bytes_18(u8* destination, const u8* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "lb $10, 16(%1)\n"
                     "lb $11, 17(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)\n"
                     "sb $10, 16(%0)\n"
                     "sb $11, 17(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy two halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_2(u16* destination, const u16* source)
{
    asm __volatile__("lh $8, 0(%1)\n"
                     "lh $9, 2(%1)\n"
                     "sh $8, 0(%0)\n"
                     "sh $9, 2(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy three halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_3(u16* destination, const u16* source)
{
    asm __volatile__("lh $8, 0(%1)\n"
                     "lh $9, 2(%1)\n"
                     "lh $10, 4(%1)\n"
                     "sh $8, 0(%0)\n"
                     "sh $9, 2(%0)\n"
                     "sh $10, 4(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy four halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_4(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy five halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_5(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "lh $9, 8(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sh $9, 8(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy six halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_6(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "lh $9, 8(%1)\n"
                     "lh $10, 10(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sh $9, 8(%0)\n"
                     "sh $10, 10(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy seven halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_7(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "lh $9, 8(%1)\n"
                     "lh $10, 10(%1)\n"
                     "lh $11, 12(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sh $9, 8(%0)\n"
                     "sh $10, 10(%0)\n"
                     "sh $11, 12(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy eight halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_8(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy nine halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_9(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "lh $10, 16(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)\n"
                     "sh $10, 16(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy ten halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_10(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "lh $10, 16(%1)\n"
                     "lh $11, 18(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)\n"
                     "sh $10, 16(%0)\n"
                     "sh $11, 18(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy eleven halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_11(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "lh $10, 16(%1)\n"
                     "lh $11, 18(%1)\n"
                     "lh $12, 20(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)\n"
                     "sh $10, 16(%0)\n"
                     "sh $11, 18(%0)\n"
                     "sh $12, 20(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy twelve halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_12(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "ldl $10, 23(%1)\n"
                     "ldr $10, 16(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)\n"
                     "sdl $10, 23(%0)\n"
                     "sdr $10, 16(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy thirteen halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_13(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "ldl $10, 23(%1)\n"
                     "ldr $10, 16(%1)\n"
                     "lh $11, 24(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)\n"
                     "sdl $10, 23(%0)\n"
                     "sdr $10, 16(%0)\n"
                     "sh $11, 24(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy fourteen halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_14(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "ldl $10, 23(%1)\n"
                     "ldr $10, 16(%1)\n"
                     "lh $11, 24(%1)\n"
                     "lh $12, 26(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)\n"
                     "sdl $10, 23(%0)\n"
                     "sdr $10, 16(%0)\n"
                     "sh $11, 24(%0)\n"
                     "sh $12, 26(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy fifteen halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_15(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "ldl $10, 23(%1)\n"
                     "ldr $10, 16(%1)\n"
                     "lh $11, 24(%1)\n"
                     "lh $12, 26(%1)\n"
                     "lh $13, 28(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)\n"
                     "sdl $10, 23(%0)\n"
                     "sdr $10, 16(%0)\n"
                     "sh $11, 24(%0)\n"
                     "sh $12, 26(%0)\n"
                     "sh $13, 28(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy sixteen halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_16(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "ldl $10, 23(%1)\n"
                     "ldr $10, 16(%1)\n"
                     "ldl $11, 31(%1)\n"
                     "ldr $11, 24(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)\n"
                     "sdl $10, 23(%0)\n"
                     "sdr $10, 16(%0)\n"
                     "sdl $11, 31(%0)\n"
                     "sdr $11, 24(%0)" : : "r"(destination), "r"(source));
}

/**
 * @brief Copy seventeen halfwords, loading them all into $t0 and up before storing any.
 * @param destination Where the block goes.
 * @param source Where the block comes from; it can be at any distance behind the destination.
 * @see EE Core Instruction Set Manual (LDL, LDR, SDL, SDR, LWL, LWR); the six LZ decoders in main.
 */
static inline void lz_copy_halfwords_17(u16* destination, const u16* source)
{
    asm __volatile__("ldl $8, 7(%1)\n"
                     "ldr $8, 0(%1)\n"
                     "ldl $9, 15(%1)\n"
                     "ldr $9, 8(%1)\n"
                     "ldl $10, 23(%1)\n"
                     "ldr $10, 16(%1)\n"
                     "ldl $11, 31(%1)\n"
                     "ldr $11, 24(%1)\n"
                     "lh $12, 32(%1)\n"
                     "sdl $8, 7(%0)\n"
                     "sdr $8, 0(%0)\n"
                     "sdl $9, 15(%0)\n"
                     "sdr $9, 8(%0)\n"
                     "sdl $10, 23(%0)\n"
                     "sdr $10, 16(%0)\n"
                     "sdl $11, 31(%0)\n"
                     "sdr $11, 24(%0)\n"
                     "sh $12, 32(%0)" : : "r"(destination), "r"(source));
}

#endif
