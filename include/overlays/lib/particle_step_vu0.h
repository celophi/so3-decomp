#ifndef SO3_OVERLAYS_LIB_PARTICLE_STEP_VU0_H
#define SO3_OVERLAYS_LIB_PARTICLE_STEP_VU0_H

/*
 * The particle step keeps one cell in VU0 while it integrates it: position in vf1, velocity in vf2 (w counts down
 * to the secondary emission), acceleration in vf3, travel in vf4 (xyz distance moved, w age), color in vf6 and its
 * velocity and acceleration in vf7 and vf8. The pass setup leaves the time step in vf5.x, the force-field rate in
 * vf9, zero in vf30, the color ceiling in vf29.x and the grid bounds in vf26/vf27.
 */

/**
 * @brief Load a particle's position into vf1.
 * @param position Aligned position.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_load_position(const void* position)
{
    asm __volatile__("lqc2 $vf1, 0x0(%0)\n" : : "r"(position) : "memory");
}

/**
 * @brief Load a particle's velocity into vf2.
 * @param velocity Aligned velocity.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_load_velocity(const void* velocity)
{
    asm __volatile__("lqc2 $vf2, 0x0(%0)\n" : : "r"(velocity) : "memory");
}

/**
 * @brief Load a particle's acceleration into vf3.
 * @param acceleration Aligned acceleration.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_load_acceleration(const void* acceleration)
{
    asm __volatile__("lqc2 $vf3, 0x0(%0)\n" : : "r"(acceleration) : "memory");
}

/**
 * @brief Load a particle's travel (distance moved, age in w) into vf4.
 * @param travel Aligned travel vector.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_load_travel(const void* travel)
{
    asm __volatile__("lqc2 $vf4, 0x0(%0)\n" : : "r"(travel) : "memory");
}

/**
 * @brief Load a particle's color into vf6.
 * @param color Aligned color.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_load_color(const void* color)
{
    asm __volatile__("lqc2 $vf6, 0x0(%0)\n" : : "r"(color) : "memory");
}

/**
 * @brief Load a particle's color velocity into vf7.
 * @param color_velocity Aligned color velocity.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_load_color_velocity(const void* color_velocity)
{
    asm __volatile__("lqc2 $vf7, 0x0(%0)\n" : : "r"(color_velocity) : "memory");
}

/**
 * @brief Load a particle's color acceleration into vf8.
 * @param color_acceleration Aligned color acceleration.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_load_color_acceleration(const void* color_acceleration)
{
    asm __volatile__("lqc2 $vf8, 0x0(%0)\n" : : "r"(color_acceleration) : "memory");
}

/**
 * @brief Load the force the grid's force field gives at a particle into vf10.
 * @param force Aligned force.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_load_force(const void* force)
{
    asm __volatile__("lqc2 $vf10, 0x0(%0)\n" : : "r"(force) : "memory");
}

/**
 * @brief Load the velocity change a collider gave a particle into vf11.
 * @param bounce Aligned velocity change.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_load_bounce(const void* bounce)
{
    asm __volatile__("lqc2 $vf11, 0x0(%0)\n" : : "r"(bounce) : "memory");
}

/**
 * @brief Step a particle by the time step with the force in vf10: move it, age it, fade and clamp its color and
 *        grow the grid bounds around it.
 * @param next Address to prefetch (0x40 past it).
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_step_with_force(const void* next)
{
    asm __volatile__(
        "pref       0, 0x40(%0)\n"
        "vadda.xyz  $ACC, $vf0, $vf1\n"
        "vmaddx.xyz $vf1, $vf2, $vf5x\n"
        "vadda.xyzw $ACC, $vf30, $vf6\n"
        "vmaddx.xyzw $vf6, $vf7, $vf5x\n"
        "vadda.xyz  $ACC, $vf0, $vf3\n"
        "vmaddx.xyz $vf3, $vf9, $vf5x\n"
        "vadda.xyz  $ACC, $vf0, $vf4\n"
        "vmaddx.xyz $vf4, $vf2, $vf5x\n"
        "vadda.xyz  $ACC, $vf0, $vf2\n"
        "vmaddax.xyz $ACC, $vf10, $vf5x\n"
        "vmaddx.xyz $vf2, $vf3, $vf5x\n"
        "vsubx.w    $vf2, $vf2, $vf5x\n"
        "vmaxx.xyzw $vf6, $vf6, $vf0x\n"
        "vaddx.w    $vf4, $vf4, $vf5x\n"
        "vmulaw.xyzw $ACC, $vf7, $vf0w\n"
        "vmaddx.xyzw $vf7, $vf8, $vf5x\n"
        "vmini.xyz  $vf26, $vf26, $vf1\n"
        "vminix.xyzw $vf6, $vf6, $vf29x\n"
        "vmax.xyz   $vf27, $vf27, $vf1\n"
        :
        : "r"(next)
        : "memory");
}

/**
 * @brief Store the stepped position (vf1).
 * @param output Aligned destination.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_store_position(void* output)
{
    asm __volatile__("sqc2 $vf1, 0x0(%0)\n" : : "r"(output) : "memory");
}

/**
 * @brief Store the stepped velocity (vf2).
 * @param velocity Aligned destination.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_store_velocity(void* velocity)
{
    asm __volatile__("sqc2 $vf2, 0x0(%0)\n" : : "r"(velocity) : "memory");
}

/**
 * @brief Store the stepped color (vf6) into a draw record's second vector.
 * @param output Aligned draw record.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_store_output_color(void* output)
{
    asm __volatile__("sqc2 $vf6, 0x10(%0)\n" : : "r"(output) : "memory");
}

/**
 * @brief Add the collider's velocity change (vf11) to the velocity.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_add_bounce()
{
    asm __volatile__("vadd.xyz $vf2, $vf2, $vf11\n" : : : "memory");
}

/**
 * @brief Store a stepped particle back into its cell.
 * @param travel Aligned travel destination.
 * @param position Aligned position destination.
 * @param velocity Aligned velocity destination.
 * @param acceleration Aligned acceleration destination.
 * @param color Aligned color destination.
 * @param color_velocity Aligned color velocity destination.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_store_state(void* travel, void* position, void* velocity, void* acceleration,
                                            void* color, void* color_velocity)
{
    asm __volatile__(
        "sqc2       $vf4, 0x0(%0)\n"
        "sqc2       $vf1, 0x0(%1)\n"
        "sqc2       $vf2, 0x0(%2)\n"
        "sqc2       $vf3, 0x0(%3)\n"
        "sqc2       $vf6, 0x0(%4)\n"
        "sqc2       $vf7, 0x0(%5)\n"
        :
        : "r"(travel), "r"(position), "r"(velocity), "r"(acceleration), "r"(color), "r"(color_velocity)
        : "memory");
}

/**
 * @brief Store a stepped particle back into its cell and leave its squared travel distance in vf4.x.
 * @param travel Aligned travel destination; also prefetched 0x40 past it.
 * @param position Aligned position destination.
 * @param velocity Aligned velocity destination.
 * @param acceleration Aligned acceleration destination.
 * @param color Aligned color destination.
 * @param color_velocity Aligned color velocity destination.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_store_state_travel_length(void* travel, void* position, void* velocity,
                                                          void* acceleration, void* color, void* color_velocity)
{
    asm __volatile__(
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "sqc2       $vf4, 0x0(%0)\n"
        "vmul.xyz   $vf4, $vf4, $vf4\n"
        "sqc2       $vf1, 0x0(%1)\n"
        "sqc2       $vf2, 0x0(%2)\n"
        "sqc2       $vf3, 0x0(%3)\n"
        "sqc2       $vf6, 0x0(%4)\n"
        "sqc2       $vf7, 0x0(%5)\n"
        "vadday.x   $ACC, $vf4, $vf4y\n"
        "vmaddz.x   $vf4, $vf31, $vf4z\n"
        "pref       0, 0x40(%0)\n"
        :
        : "r"(travel), "r"(position), "r"(velocity), "r"(acceleration), "r"(color), "r"(color_velocity)
        : "memory");
}

/**
 * @brief Store the squared travel distance left in vf4.
 * @param output Aligned destination; the distance is in x.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_store_travel_length(void* output)
{
    asm __volatile__("sqc2 $vf4, 0x0(%0)\n" : : "r"(output) : "memory");
}

/**
 * @brief Transform the position in vf1 by a matrix into vf18.
 * @param matrix Aligned 4x4 matrix rows.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_to_local(const void* matrix)
{
    asm __volatile__(
        "lqc2       $vf8, 0x0(%0)\n"
        "lqc2       $vf9, 0x10(%0)\n"
        "lqc2       $vf10, 0x20(%0)\n"
        "lqc2       $vf11, 0x30(%0)\n"
        "vmulax.xyzw $ACC, $vf8, $vf1x\n"
        "vmadday.xyzw $ACC, $vf9, $vf1y\n"
        "vmaddaz.xyzw $ACC, $vf10, $vf1z\n"
        "vmaddw.xyzw $vf18, $vf11, $vf0w\n"
        :
        : "r"(matrix)
        : "memory");
}

/**
 * @brief Store the local position left in vf18.
 * @param output Aligned destination.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_store_local(void* output)
{
    asm __volatile__("sqc2 $vf18, 0x0(%0)\n" : : "r"(output) : "memory");
}

/**
 * @brief Start a trail from the point in vf1: the scale goes to vf3 and the trail point vf4 starts there.
 * @param scale How far each trail point moves toward the next.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_trail_start(float scale)
{
    asm __volatile__(
        "qmtc2.ni   %0, $vf3\n"
        "vmove.xyzw $vf4, $vf1\n"
        :
        : "r"(scale)
        : "memory");
}

/**
 * @brief Move the trail point toward the next point by the scale, store it there and grow the grid bounds.
 * @param point Aligned next point; replaced with the trail point.
 * @see func_0049DB40 and func_0049E440 in Lib.
 */
static inline void vu0_particle_trail_step(void* point)
{
    asm __volatile__(
        "lqc2       $vf2, 0x0(%0)\n"
        "vsub.xyzw  $vf6, $vf2, $vf1\n"
        "vmove.xyzw $vf1, $vf2\n"
        "vadda.xyz  $ACC, $vf0, $vf4\n"
        "vmaddx.xyz $vf4, $vf6, $vf3x\n"
        "sqc2       $vf4, 0x0(%0)\n"
        "vmini.xyz  $vf26, $vf26, $vf4\n"
        "vmax.xyz   $vf27, $vf27, $vf4\n"
        :
        : "r"(point)
        : "memory");
}

/**
 * @brief Load a particle's swirl radii into vf9.
 * @param radius Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_radius(const void* radius)
{
    asm __volatile__("lqc2 $vf9, 0x0(%0)\n" : : "r"(radius) : "memory");
}

/**
 * @brief Load a particle's swirl angles into vf10.
 * @param angle Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_angle(const void* angle)
{
    asm __volatile__("lqc2 $vf10, 0x0(%0)\n" : : "r"(angle) : "memory");
}

/**
 * @brief Load a particle's swirl radius velocity into vf11.
 * @param velocity Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_radius_velocity(const void* velocity)
{
    asm __volatile__("lqc2 $vf11, 0x0(%0)\n" : : "r"(velocity) : "memory");
}

/**
 * @brief Load a particle's swirl radius acceleration into vf12.
 * @param acceleration Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_radius_acceleration(const void* acceleration)
{
    asm __volatile__("lqc2 $vf12, 0x0(%0)\n" : : "r"(acceleration) : "memory");
}

/**
 * @brief Load a particle's swirl angle velocity into vf13.
 * @param velocity Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_angle_velocity(const void* velocity)
{
    asm __volatile__("lqc2 $vf13, 0x0(%0)\n" : : "r"(velocity) : "memory");
}

/**
 * @brief Load a particle's swirl angle acceleration into vf14.
 * @param acceleration Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_angle_acceleration(const void* acceleration)
{
    asm __volatile__("lqc2 $vf14, 0x0(%0)\n" : : "r"(acceleration) : "memory");
}

/**
 * @brief Load the swirl's change in position into vf15.
 * @param delta Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_swirl_delta(const void* delta)
{
    asm __volatile__("lqc2 $vf15, 0x0(%0)\n" : : "r"(delta) : "memory");
}

/**
 * @brief Load the color jitter into vf16.
 * @param offset Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_color_offset(const void* offset)
{
    asm __volatile__("lqc2 $vf16, 0x0(%0)\n" : : "r"(offset) : "memory");
}

/**
 * @brief Load the force the grid's force field gives at a scripted particle into vf17.
 * @param force Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_script_force(const void* force)
{
    asm __volatile__("lqc2 $vf17, 0x0(%0)\n" : : "r"(force) : "memory");
}

/**
 * @brief Load the spin angles into vf1.
 * @param angles Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_spin_angles(const void* angles)
{
    asm __volatile__("lqc2 $vf1, 0x0(%0)\n" : : "r"(angles) : "memory");
}

/**
 * @brief Load the spin rotation into vf2.
 * @param rotation Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_spin_rotation(const void* rotation)
{
    asm __volatile__("lqc2 $vf2, 0x0(%0)\n" : : "r"(rotation) : "memory");
}

/**
 * @brief Load the spin rate into vf3.
 * @param rate Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_spin_rate(const void* rate)
{
    asm __volatile__("lqc2 $vf3, 0x0(%0)\n" : : "r"(rate) : "memory");
}

/**
 * @brief Load the spin offset into vf4.
 * @param offset Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_spin_offset(const void* offset)
{
    asm __volatile__("lqc2 $vf4, 0x0(%0)\n" : : "r"(offset) : "memory");
}

/**
 * @brief Load the previous spun offset into vf6.
 * @param previous Aligned vector.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_load_spin_previous(const void* previous)
{
    asm __volatile__("lqc2 $vf6, 0x0(%0)\n" : : "r"(previous) : "memory");
}

/**
 * @brief Store the stepped swirl radii (vf9).
 * @param radius Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_store_radius(void* radius)
{
    asm __volatile__("sqc2 $vf9, 0x0(%0)\n" : : "r"(radius) : "memory");
}

/**
 * @brief Store the stepped swirl angles (vf10).
 * @param angle Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_store_angle(void* angle)
{
    asm __volatile__("sqc2 $vf10, 0x0(%0)\n" : : "r"(angle) : "memory");
}

/**
 * @brief Store the stepped swirl radius velocity (vf11).
 * @param velocity Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_store_radius_velocity(void* velocity)
{
    asm __volatile__("sqc2 $vf11, 0x0(%0)\n" : : "r"(velocity) : "memory");
}

/**
 * @brief Store the stepped swirl angle velocity (vf13).
 * @param velocity Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_store_angle_velocity(void* velocity)
{
    asm __volatile__("sqc2 $vf13, 0x0(%0)\n" : : "r"(velocity) : "memory");
}

/**
 * @brief Store the swirl's change in position (vf15).
 * @param delta Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_save_swirl_delta(void* delta)
{
    asm __volatile__("sqc2 $vf15, 0x0(%0)\n" : : "r"(delta) : "memory");
}

/**
 * @brief Store the stepped spin angles (vf1).
 * @param angles Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_store_spin_angles(void* angles)
{
    asm __volatile__("sqc2 $vf1, 0x0(%0)\n" : : "r"(angles) : "memory");
}

/**
 * @brief Store the spun offset (vf3).
 * @param offset Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_store_spin_offset(void* offset)
{
    asm __volatile__("sqc2 $vf3, 0x0(%0)\n" : : "r"(offset) : "memory");
}

/**
 * @brief Store the squared travel distance (x) (vf1).
 * @param output Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_store_squared_travel(void* output)
{
    asm __volatile__("sqc2 $vf1, 0x0(%0)\n" : : "r"(output) : "memory");
}

/**
 * @brief Store the stepped travel vector (vf4).
 * @param travel Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_store_travel(void* travel)
{
    asm __volatile__("sqc2 $vf4, 0x0(%0)\n" : : "r"(travel) : "memory");
}

/**
 * @brief Store the stepped acceleration (vf3).
 * @param acceleration Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_store_acceleration(void* acceleration)
{
    asm __volatile__("sqc2 $vf3, 0x0(%0)\n" : : "r"(acceleration) : "memory");
}

/**
 * @brief Store the stepped color (vf6).
 * @param color Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_store_color(void* color)
{
    asm __volatile__("sqc2 $vf6, 0x0(%0)\n" : : "r"(color) : "memory");
}

/**
 * @brief Store the stepped color velocity (vf7).
 * @param velocity Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_store_color_velocity(void* velocity)
{
    asm __volatile__("sqc2 $vf7, 0x0(%0)\n" : : "r"(velocity) : "memory");
}

/**
 * @brief Step the swirl angles and radii by their velocities.
 * @param velocity Unused by the instructions; the original helper still takes the particle's velocity.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_swirl_advance(const void* velocity)
{
    // TODO: The target computes &cell->velocity just before this block and never uses it, which only an asm input
    // does; my guess is the original macro still named the velocity.
    asm __volatile__(
        "vadda.xyz  $ACC, $vf0, $vf9\n"
        "vmaddx.xyz $vf9, $vf11, $vf5x\n"
        "vadda.xyz  $ACC, $vf0, $vf10\n"
        "vmaddx.xyz $vf10, $vf13, $vf5x\n"
        :
        : "r"(velocity)
        : "memory");
}

/**
 * @brief Step the swirl velocities by their accelerations.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_swirl_accelerate()
{
    asm __volatile__(
        "vadda.xyz  $ACC, $vf0, $vf11\n"
        "vmaddx.xyz $vf11, $vf12, $vf5x\n"
        "vadda.xyz  $ACC, $vf0, $vf13\n"
        "vmaddx.xyz $vf13, $vf14, $vf5x\n"
        :
        :
        : "memory");
}

/**
 * @brief Clear the swirl's change in position (vf15).
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_clear_swirl_delta()
{
    asm __volatile__("vmove.xyz $vf15, $vf0\n" : : : "memory");
}

/**
 * @brief Clear the color jitter (vf16).
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_clear_color_offset()
{
    asm __volatile__("vmulx.xyzw $vf16, $vf0, $vf0x\n" : : : "memory");
}

/**
 * @brief Clear the force-field force (vf17).
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_clear_script_force()
{
    asm __volatile__("vmove.xyz $vf17, $vf0\n" : : : "memory");
}

/**
 * @brief Step the spin angles by their rate and turn the offset by the new rotation, leaving the change in vf16.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_spin()
{
    asm __volatile__(
        "vmulaw.xyzw $ACC, $vf1, $vf0w\n"
        "vmaddx.xyzw $vf1, $vf3, $vf5x\n"
        "vmul.xyzw  $vf3, $vf2, $vf4\n"
        "vmula.xyzw $ACC, $vf2, $vf4\n"
        "vmsubw.xyzw $vf16, $vf6, $vf0w\n"
        :
        :
        : "memory");
}

/**
 * @brief Leave the squared travel distance of the travel vector in vf4 in vf1.x.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_squared_travel()
{
    asm __volatile__(
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "vmul.xyz   $vf1, $vf4, $vf4\n"
        "vadday.x   $ACC, $vf1, $vf1y\n"
        "vmaddz.x   $vf1, $vf31, $vf1z\n"
        :
        :
        : "memory");
}

/**
 * @brief Transform a point by a matrix through vf5 and store it; vf5 (the time step) has to be reloaded after.
 * @param point Aligned point.
 * @param matrix Aligned 4x4 matrix rows.
 * @param output Aligned destination.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_point_through(const void* point, const void* matrix, void* output)
{
    asm __volatile__(
        "lqc2       $vf5, 0x0(%0)\n"
        "lqc2       $vf1, 0x0(%1)\n"
        "lqc2       $vf2, 0x10(%1)\n"
        "lqc2       $vf3, 0x20(%1)\n"
        "lqc2       $vf4, 0x30(%1)\n"
        "vmulax.xyzw $ACC, $vf1, $vf5x\n"
        "vmadday.xyzw $ACC, $vf2, $vf5y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf5z\n"
        "vmaddw.xyzw $vf5, $vf4, $vf0w\n"
        "sqc2       $vf5, 0x0(%2)\n"
        :
        : "r"(point), "r"(matrix), "r"(output)
        : "memory");
}

/**
 * @brief Put the time step back into vf5.
 * @param step Time step in seconds.
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_restore_time_step(float step)
{
    asm __volatile__("qmtc2.ni %0, $vf5\n" : : "r"(step) : "memory");
}

/**
 * @brief Step a scripted particle: as vu0_particle_step_with_force, plus the swirl change (vf15) on the position
 *        and travel, the color jitter (vf16) on the color, the acceleration rate from vf18 and the force from vf17.
 * @param next Address to prefetch (0x100 and 0x140 past it).
 * @see func_00445950 and func_0049ED80 in Lib.
 */
static inline void vu0_particle_step_scripted(const void* next)
{
    asm __volatile__(
        "pref       0, 0x100(%0)\n"
        "vadda.xyz  $ACC, $vf0, $vf1\n"
        "vmaddaw.xyz $ACC, $vf15, $vf0w\n"
        "vmaddx.xyz $vf1, $vf2, $vf5x\n"
        "vadda.xyzw $ACC, $vf30, $vf6\n"
        "vmaddaw.xyzw $ACC, $vf16, $vf0w\n"
        "vmaddx.xyzw $vf6, $vf7, $vf5x\n"
        "vadda.xyz  $ACC, $vf0, $vf3\n"
        "vmaddx.xyz $vf3, $vf18, $vf5x\n"
        "vadda.xyz  $ACC, $vf0, $vf4\n"
        "vmaddaw.xyz $ACC, $vf15, $vf0w\n"
        "vmaddx.xyz $vf4, $vf2, $vf5x\n"
        "vadda.xyz  $ACC, $vf0, $vf2\n"
        "vmaddax.xyz $ACC, $vf17, $vf5x\n"
        "vmaddx.xyz $vf2, $vf3, $vf5x\n"
        "vsubx.w    $vf2, $vf2, $vf5x\n"
        "vmaxx.xyzw $vf6, $vf6, $vf0x\n"
        "vaddx.w    $vf4, $vf4, $vf5x\n"
        "vmulaw.xyzw $ACC, $vf7, $vf0w\n"
        "vmaddx.xyzw $vf7, $vf8, $vf5x\n"
        "vmini.xyz  $vf26, $vf26, $vf1\n"
        "vminix.xyzw $vf6, $vf6, $vf29x\n"
        "vmax.xyz   $vf27, $vf27, $vf1\n"
        "pref       0, 0x140(%0)\n"
        :
        : "r"(next)
        : "memory");
}

#endif
