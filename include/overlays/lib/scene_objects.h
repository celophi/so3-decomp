#ifndef SO3_OVERLAYS_LIB_SCENE_OBJECTS_H
#define SO3_OVERLAYS_LIB_SCENE_OBJECTS_H

#include "overlays/lib/model.h"

/** LibClass1734B0 entry of type 34 with two element arrays, with vtable D_173490 in main data. */
class LibClass173490 : public LibClass1734B0
{
public:
    /** @brief Start with no entry arrays. */
    LibClass173490();

    /** @brief Free both entry arrays, then destroy the entry. */
    virtual ~LibClass173490();

    virtual void set_borrowed_data(void* value);

    /**
     * @brief Copy each vertex's cell element into the output, or, when unk4c is clear, the output's values back
     *        into the cells and set unk4d.
     * @param output Output to fill or read.
     * @param index Bit index, which picks the record of cell indices.
     */
    virtual void func_slot10(LibEntryOutput* output, s32 index);

    /**
     * @brief Return the entry's type code.
     * @return 34.
     */
    virtual s32 func_slot14();

    /**
     * @brief Return the record at the cursor and move past it; the size is given in halfwords and rounded up to 16 bytes.
     * @param index Bit index; unused.
     * @param size Size in halfwords; receives the size in bytes.
     * @return Record.
     */
    virtual u8* read_record(u32 index, u32* size);

    /**
     * @brief Run one step of the ripple grid on VU0: drop a random ripple when enabled, spread the heights into the
     *        velocities (only on masked cells unless the grid is unmasked), then move the masked heights. Rewind the
     *        records; while the grid is idle only rewind them.
     * @param root Model transform the grid belongs to.
     * @return One.
     */
    virtual s32 func_slot1C(LibTransform* root);

    /** @brief Clear both element arrays and the two flags. */
    void clear_entries();

    u32* unk30;
    u32* unk34;
    u32 unk38;
    LibTransform* unk3c;
    LibClass173490Entry* unk40;
    LibClass173490Entry* unk44;
    u32* unk48;
    u8 unk4c;
    u8 unk4d;
};

/**
 * Light: a LibTransform with a kind byte that the scene's models are lit by, with vtable D_1736C0 in main data.
 * Lib's object factory builds the five kinds below with inline constructors.
 */
class LibClass1736C0 : public LibTransform
{
public:
    /** @brief Start as kind zero. */
    LibClass1736C0()
    {
        kind = 0;
    }

    virtual ~LibClass1736C0()
    {
    }

    /**
     * @brief Slot 0x84: bring the light into a view's space.
     * @param matrix View matrix.
     * @param rotation View matrix with its rows normalised, for directions.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation) = 0;

    /**
     * @brief Slot 0x88: work out the light reaching a point.
     * @param point Point being lit.
     * @param normal Normal at the point.
     * @return Light vector; stored in the light.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal) = 0;

    u8 kind;
};

/** Point light of type 0x703, with vtable D_173750 in main data. */
class LibClass173750 : public LibClass1736C0
{
public:
    /** @brief Start as a type-0x703 light of kind one. */
    LibClass173750()
    {
        type_id = 0x703;
        kind = 1;
    }

    /**
     * @brief Transform the light's position into the view's space.
     * @param matrix View matrix.
     * @param rotation Unused.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation);

    /**
     * @brief Work out the vector from a point to the light, falling off with distance.
     * @param point Point being lit.
     * @param normal Unused.
     * @return Light vector at unk220.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal);

    LibVector4 unk220;
    LibVector4 unk230;
    LibVector4 view_position;
};

/** Light of type 0x702 that scales normals, with vtable D_1737E0 in main data. */
class LibClass1737E0 : public LibClass1736C0
{
public:
    /** @brief Start as a type-0x702 light of kind two. */
    LibClass1737E0()
    {
        type_id = 0x702;
        unk230.w = -1.0f;
        kind = 2;
    }

    /**
     * @brief Do nothing; this light doesn't depend on the view.
     * @param matrix Unused.
     * @param rotation Unused.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation)
    {
    }

    /**
     * @brief Scale a normal by the light's factors.
     * @param point Unused.
     * @param normal Normal at the point.
     * @return Light vector at unk220.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal);

    LibVector4 unk220;
    LibVector4 unk230;
};

/** Light of type 0x704 with a position, a radius and two directions, with vtable D_173630 in main data. */
class LibClass173630 : public LibClass1736C0
{
public:
    /** @brief Start as a type-0x704 light of kind one. */
    LibClass173630()
    {
        type_id = 0x704;
        kind = 1;
    }

    virtual ~LibClass173630();

    /**
     * @brief Bring the position and both directions into the view's space.
     * @param matrix View matrix.
     * @param rotation View matrix with its rows normalised.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation);

    /**
     * @brief Give a random vector from the view-space directions for points close enough to the light's axis.
     * @param point Point being lit.
     * @param normal Unused.
     * @return Light vector at unk290; zero for points out of reach.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal);

    LibVector4 view_position;
    LibVector4 unk230;
    LibVector4 unk240;
    LibVector4 axis;
    LibVector4 unk260;
    LibVector4 unk270;
    LibVector4 unk280;
    LibVector4 unk290;
    float radius;
};

/** Light of type 0x701 that gives a random vector between two directions, with vtable D_173870 in main data. */
class LibClass173870 : public LibClass1736C0
{
public:
    /** @brief Start as a type-0x701 light of kind four. */
    LibClass173870()
    {
        type_id = 0x701;
        kind = 4;
    }

    /**
     * @brief Turn both directions into the view's space and halve the second.
     * @param matrix Unused.
     * @param rotation View matrix with its rows normalised.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation);

    /**
     * @brief Pick a random vector from the view-space directions.
     * @param point Unused.
     * @param normal Unused.
     * @return Light vector at unk270.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal);

    LibVector4 unk220;
    LibVector4 unk230;
    LibVector4 unk240;
    LibVector4 unk250;
    LibVector4 unk260;
    LibVector4 unk270;
};

/** Directional light of type 0x700, with vtable D_173900 in main data. */
class LibClass173900 : public LibClass1736C0
{
public:
    /** @brief Start as a type-0x700 light. */
    LibClass173900()
    {
        type_id = 0x700;
    }

    /**
     * @brief Turn the direction into the view's space.
     * @param matrix Unused.
     * @param rotation View matrix with its rows normalised.
     */
    virtual void func_slot84(const LibMatrix44Value* matrix, const LibMatrix44Value* rotation);

    /**
     * @brief Give the view-space direction, the same for every point.
     * @param point Unused.
     * @param normal Unused.
     * @return Direction at unk230.
     */
    virtual const LibVector4* func_slot88(const LibVector4* point, const LibVector4* normal)
    {
        return &unk230;
    }

    LibVector4 unk220;
    LibVector4 unk230;
};

/**
 * LibTransform of type 0x1100, with vtable D_1734D0 in main data: a rectangle in its local xz plane, given by its half
 * extents; I think these are occluders.
 */
class LibClass1734D0 : public LibTransform
{
public:
    /** @brief Construct the transform. */
    LibClass1734D0();

    float half_width;
    float half_depth;
    float depth;
    u8 unk21c;
    u8 unk21d[3];
    LibVector4 corners[4];
};

/**
 * @brief Work out the four corners of the rectangle from its half extents, in the xz plane at y zero.
 * @param object Rectangle; the corners' w is left alone.
 */
extern "C" void func_00431020(LibClass1734D0* object);

/** Model with three owned list objects, with vtables D_1788B0 and D_178964 in main data. */
class LibClass1788B0 : public LibModel
{
public:
    /** @brief Construct the model with its defaults. */
    LibClass1788B0();

    /** @brief Destroy the owned list objects, then the model. */
    virtual ~LibClass1788B0()
    {
        for (s32 i = 0; i < 3; i++)
        {
            if (unk83c[i] != 0)
            {
                unk83c[i]->destroy();
                unk83c[i] = 0;
            }
        }
    }

    /**
     * @brief Report no box-culling centre.
     * @param output Unused.
     * @return Zero.
     */
    virtual s32 get_box_cull_center(void* output);

    /** @brief Destroy the model's attachments, then the model. */
    virtual void destroy();

    /** @brief Draw the model. */
    virtual void render();

    virtual const LibVector4* get_bounding_sphere();

    virtual void build_packet(const void* matrix, void* context);

    virtual LibTransformOwner* clone();

    /**
     * @brief Return the before packet's size.
     * @return Eleven.
     */
    virtual s32 get_before_packet_size();

    /**
     * @brief Return the after packet's size.
     * @return One.
     */
    virtual s32 get_after_packet_size();

    virtual s32 build_before_packet(s32 block, s32 address);

    /**
     * @brief Chain the model's after block in with a DMA reference, unless the model has a display manager or
     *        D_001B65B0 is clear.
     * @param block Block address (uncached).
     * @param address Address of the model's draw packet.
     * @return End of what was written.
     */
    virtual s32 build_after_packet(s32 block, s32 address);

    /**
     * @brief Build from another model of this class, sharing its owner.
     * @param links Update list for the new model.
     * @param source Model to copy.
     * @return Nonzero on success.
     */
    virtual s32 func_004C8720(LibUpdateList* links, LibClass1788B0* source);

    /**
     * @brief Build from a model of the source class, sharing its owner.
     * @param links Update list for the new model.
     * @param source Model to copy.
     * @return Nonzero on success.
     */
    virtual s32 func_004C8680(LibUpdateList* links, LibClass173380* source);

    /**
     * @brief Virtual slot 0x100.
     * @param index Index.
     * @param matrix Matrix.
     * @param context Context.
     * @param scale Scale.
     */
    virtual void func_004C8860(s32 index, void* matrix, void* context, float scale);

    /**
     * @brief Set the two values at 0x864.
     * @param first Value at 0x864.
     * @param second Value at 0x868.
     */
    void set_unk864(float first, float second)
    {
        unk864 = first;
        unk868 = second;
    }

    u8 unk820;
    u8 unk821;
    u8 unk822;
    u8 unk823;
    u8 unk824;
    u8 unk825;
    u8 unk826;
    u8 unk827;
    float sphere_radius_scale;
    float unk82c;
    float unk830;
    float unk834;
    LibModel* unk838;
    LibTransformOwner* unk83c[3];
    u8 unk848[8];
    FieldVec4B unk850;
    float unk860;
    float unk864;
    float unk868;
    u8 unk86c[4];
};

#endif
