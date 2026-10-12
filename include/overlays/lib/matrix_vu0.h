#ifndef SO3_OVERLAYS_LIB_MATRIX_VU0_H
#define SO3_OVERLAYS_LIB_MATRIX_VU0_H

/**
 * @brief Negate the source translation transformed by the destination rotation.
 * @param output Aligned matrix containing the transposed rotation; receives row 3.
 * @param input Aligned source matrix with translation in row 3.
 */
static inline void vu0_inverse_translation(void* output, const void* input)
{
    asm __volatile__(
        "lqc2       $vf31, 0x30(%0)\n"
        "lqc2       $vf28, 0x00(%1)\n"
        "lqc2       $vf29, 0x10(%1)\n"
        "lqc2       $vf30, 0x20(%1)\n"
        "vsubw.x    $vf27, $vf0, $vf0w\n"
        "vmulax.xyz $ACC, $vf28, $vf31x\n"
        "vmadday.xyz $ACC, $vf29, $vf31y\n"
        "vmaddz.xyz $vf31, $vf30, $vf31z\n"
        "vmulx.xyz  $vf31, $vf31, $vf27x\n"
        "sqc2       $vf31, 0x30(%1)\n"
        :
        : "r"(input), "r"(output)
        : "memory");
}

/** @brief Load four aligned rows and begin collecting absolute component maxima. @param input Aligned source matrix. */
static inline void vu0_inverse_load(const void* input)
{
    asm __volatile__(
        "lqc2 $vf20, 0x00(%0)\n"
        "lqc2 $vf21, 0x10(%0)\n"
        "lqc2 $vf22, 0x20(%0)\n"
        "lqc2 $vf23, 0x30(%0)\n"
        "vmulx.xyzw $vf28, $vf0, $vf0x\n"
        "vabs.xyzw $vf24, $vf20\n"
        "vabs.xyzw $vf25, $vf21\n"
        "vabs.xyzw $vf26, $vf22\n"
        "vabs.xyzw $vf27, $vf23\n"
        "vmax.xyzw $vf28, $vf24, $vf28\n"
        :
        : "r"(input)
        : "memory");
}

/** @brief Accumulate the absolute components of row 1 into the maxima. */
static inline void vu0_inverse_maximum_row1()
{
    asm __volatile__(
        "vmax.xyzw $vf28, $vf25, $vf28\n"
        :
        :
        : "memory");
}

/** @brief Accumulate the absolute components of row 2 into the maxima. */
static inline void vu0_inverse_maximum_row2()
{
    asm __volatile__(
        "vmax.xyzw $vf28, $vf26, $vf28\n"
        :
        :
        : "memory");
}

/** @brief Accumulate the absolute components of row 3 into the maxima. */
static inline void vu0_inverse_maximum_row3()
{
    asm __volatile__(
        "vmax.xyzw $vf28, $vf27, $vf28\n"
        :
        :
        : "memory");
}

/** @brief Start the reciprocal of the first component maximum. */
static inline void vu0_inverse_divide_x()
{
    asm __volatile__(
        "vdiv $Q, $vf0w, $vf28x\n"
        :
        :
        : "memory");
}

/** @brief Normalize row 0 and start the reciprocal for row 1. */
static inline void vu0_inverse_scale_row0()
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyzw $vf24, $vf24, $Q\n"
        "vnop\n"
        "vnop\n"
        "vdiv $Q, $vf0w, $vf28y\n"
        :
        :
        : "memory");
}

/** @brief Normalize row 1 and start the reciprocal for row 2. */
static inline void vu0_inverse_scale_row1()
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyzw $vf25, $vf25, $Q\n"
        "vnop\n"
        "vnop\n"
        "vdiv $Q, $vf0w, $vf28z\n"
        :
        :
        : "memory");
}

/** @brief Store normalized row 0. @param output Aligned destination matrix. */
static inline void vu0_inverse_store_row0(void* output)
{
    asm __volatile__(
        "sqc2 $vf24, 0x00(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/** @brief Normalize row 2 and start the reciprocal for row 3. */
static inline void vu0_inverse_scale_row2()
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyzw $vf26, $vf26, $Q\n"
        "vnop\n"
        "vnop\n"
        "vdiv $Q, $vf0w, $vf28w\n"
        :
        :
        : "memory");
}

/** @brief Store normalized row 1. @param output Aligned destination matrix. */
static inline void vu0_inverse_store_row1(void* output)
{
    asm __volatile__(
        "sqc2 $vf25, 0x10(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/** @brief Normalize the final row. */
static inline void vu0_inverse_scale_row3()
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyzw $vf27, $vf27, $Q\n"
        :
        :
        : "memory");
}

/** @brief Store normalized rows 2 and 3. @param output Aligned destination matrix. */
static inline void vu0_inverse_store_row2(void* output)
{
    asm __volatile__(
        "sqc2 $vf26, 0x20(%0)\n"
        "sqc2 $vf27, 0x30(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/** @brief Transform translation coordinates by three matrix rows. @param vector Aligned vector whose xyz components are transformed in place. @param matrix Aligned source matrix. */
static inline void vu0_transform_translation(void* vector, const void* matrix)
{
    asm __volatile__(
        "lqc2 $vf1, 0x00(%1)\n"
        "lqc2 $vf2, 0x10(%1)\n"
        "lqc2 $vf3, 0x20(%1)\n"
        "lqc2 $vf4, 0x00(%0)\n"
        "vmulax.xyz $ACC, $vf1, $vf4x\n"
        "vmadday.xyz $ACC, $vf2, $vf4y\n"
        "vmaddz.xyz $vf4, $vf3, $vf4z\n"
        "sqc2 $vf4, 0x00(%0)\n"
        :
        : "r"(vector), "r"(matrix)
        : "memory");
}

/**
 * @brief Multiply two aligned 4x4 matrices.
 * @param output Destination matrix, which may alias either input.
 * @param left Left factor.
 * @param right Right factor.
 */
static inline void vu0_multiply_matrix(void* output, const void* left, const void* right)
{
    asm __volatile__(
        "lqc2 $vf1, 0x00(%0)\n"
        "lqc2 $vf2, 0x10(%0)\n"
        "lqc2 $vf3, 0x20(%0)\n"
        "lqc2 $vf4, 0x30(%0)\n"
        "lqc2 $vf5, 0x00(%1)\n"
        "lqc2 $vf6, 0x10(%1)\n"
        "lqc2 $vf7, 0x20(%1)\n"
        "lqc2 $vf8, 0x30(%1)\n"
        "vmulax.xyzw $ACC, $vf5, $vf1x\n"
        "vmadday.xyzw $ACC, $vf6, $vf1y\n"
        "vmaddaz.xyzw $ACC, $vf7, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf8, $vf1w\n"
        "vmulax.xyzw $ACC, $vf5, $vf2x\n"
        "vmadday.xyzw $ACC, $vf6, $vf2y\n"
        "vmaddaz.xyzw $ACC, $vf7, $vf2z\n"
        "vmaddw.xyzw $vf2, $vf8, $vf2w\n"
        "vmulax.xyzw $ACC, $vf5, $vf3x\n"
        "vmadday.xyzw $ACC, $vf6, $vf3y\n"
        "vmaddaz.xyzw $ACC, $vf7, $vf3z\n"
        "vmaddw.xyzw $vf3, $vf8, $vf3w\n"
        "vmulax.xyzw $ACC, $vf5, $vf4x\n"
        "vmadday.xyzw $ACC, $vf6, $vf4y\n"
        "vmaddaz.xyzw $ACC, $vf7, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf8, $vf4w\n"
        "sqc2 $vf1, 0x00(%2)\n"
        "sqc2 $vf2, 0x10(%2)\n"
        "sqc2 $vf3, 0x20(%2)\n"
        "sqc2 $vf4, 0x30(%2)\n"
        :
        : "r"(left), "r"(right), "r"(output)
        : "memory");
}

#endif
