#ifndef SO3_OVERLAYS_LIB_VECTOR_H
#define SO3_OVERLAYS_LIB_VECTOR_H

#include "types.h"

#ifdef __cplusplus
/**
 * 16-byte aligned four-float vector. Assignment copies all 16 bytes with one
 * 128-bit load and store.
 */
class FieldVec4A
{
public:
    /** @brief Leave the components uninitialized. */
    FieldVec4A()
    {
    }

    /**
     * @brief Copy all four components.
     * @param other Vector to copy.
     */
    FieldVec4A(const FieldVec4A& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
    }

    /**
     * @brief Set the four components.
     * @param px First component.
     * @param py Second component.
     * @param pz Third component.
     * @param pw Fourth component.
     */
    FieldVec4A(float px, float py, float pz, float pw)
    {
        x = px;
        y = py;
        z = pz;
        w = pw;
    }

    /**
     * @brief Copy all four components.
     * @param other Vector to copy.
     * @return This vector.
     */
    FieldVec4A& operator=(const FieldVec4A& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
        return *this;
    }

    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16)));

/**
 * Second 16-byte aligned four-float vector type. It has a copy constructor, and
 * its assignments (from FieldVec4A or FieldVec4B) copy all 16 bytes and return
 * a copy, which leaves a 16-byte stack temporary in the caller.
 */
class FieldVec4B
{
public:
    /** @brief Leave the components uninitialized. */
    inline FieldVec4B();

    /**
     * @brief Copy all four components.
     * @param other Vector to copy.
     */
    FieldVec4B(const FieldVec4B& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
    }

    /**
     * @brief Set the four components.
     * @param px First component.
     * @param py Second component.
     * @param pz Third component.
     * @param pw Fourth component.
     */
    FieldVec4B(float px, float py, float pz, float pw)
    {
        x = px;
        y = py;
        z = pz;
        w = pw;
    }

    /**
     * @brief Copy all four components from a FieldVec4A.
     * @param other Vector to copy.
     */
    FieldVec4B(const FieldVec4A& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
    }

    /**
     * @brief Copy all four components from a FieldVec4A.
     * @param other Vector to copy.
     * @return A copy of this vector.
     */
    /**
     * @brief Copy all four components from a FieldVec4A without returning a copy.
     * @param other Vector to copy.
     */
    void set(const FieldVec4A& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
    }

    FieldVec4B operator=(const FieldVec4A& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
        return *this;
    }

    /**
     * @brief Copy all four components.
     * @param other Vector to copy.
     * @return A copy of this vector.
     */
    FieldVec4B operator=(const FieldVec4B& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
        return *this;
    }

    /**
     * @brief Scale all four components.
     * @param scale Factor to multiply by.
     * @return A copy of this vector.
     */
    FieldVec4B operator*=(float scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
        w *= scale;
        return *this;
    }

    /**
     * @brief Add the first three components of another vector.
     * @param other Vector to add.
     * @return A copy of this vector.
     */
    FieldVec4B add(const FieldVec4A& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    /**
     * @brief Add the first three components of another vector.
     * @param other Vector to add.
     * @return A copy of this vector.
     */
    FieldVec4B operator+=(const FieldVec4A& other)
    {
        add(other);
        return *this;
    }

    /**
     * @brief Subtract the first three components of another vector.
     * @param other Vector to subtract.
     * @return A copy of this vector.
     */
    FieldVec4B subtract(const FieldVec4B& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    /**
     * @brief Subtract the first three components of another vector.
     * @param other Vector to subtract.
     * @return A copy of this vector.
     */
    FieldVec4B operator-=(const FieldVec4B& other)
    {
        subtract(other);
        return *this;
    }

    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16)));
#endif

#endif
