#ifndef SO3_OVERLAYS_1067_00_TEXT_0020DA30_H
#define SO3_OVERLAYS_1067_00_TEXT_0020DA30_H

#include "types.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_001E6C50.h"

/** Shape node base identified by MAIN vtable D_1515B0. */
class FieldClass1515B0 : public FieldClass150070
{
public:
    /** @brief Initialize the inherited list node. */
    FieldClass1515B0()
    {
    }
    /** @brief Destroy the shape node. */
    virtual ~FieldClass1515B0()
    {
    }
    /**
     * @brief Bind the descriptor, shape data and starting record index.
     * @param shape Descriptor associated with the node.
     * @param data Shape data supplying the records.
     * @param index Starting record index.
     */
    virtual void func_0020DBC0(FieldShapeOwner18* shape, FieldShapeData10* data, s32 index);
    FieldShapeData10* unk14;
    FieldShapeOwner18* unk18;
    s32 unk1c;
};

/** 0x24-byte specialized shape node, identified by MAIN vtable D_1515E0. */
class FieldClass1515E0 : public FieldClass1515B0
{
public:
    /** @brief Initialize the optional associated list node. */
    FieldClass1515E0()
    {
        unk20 = 0;
    }
    /** @brief Destroy the specialized shape node. */
    virtual ~FieldClass1515E0();
    /**
     * @brief Bind shape data and find the transform's associated kind-seven node.
     * @param shape Descriptor associated with the node.
     * @param data Shape data supplying the records.
     * @param index Starting record index.
     */
    virtual void func_0020DBC0(FieldShapeOwner18* shape, FieldShapeData10* data, s32 index);
    FieldClass150070* unk20;
};
/** Shape node used for descriptors whose kind lies in the range 0x40-0x7E. */
class FieldClass151590 : public FieldClass1515B0
{
public:
    /** @brief Initialize the inherited shape node. */
    FieldClass151590()
    {
    }
    /** @brief Destroy the shape node. */
    virtual ~FieldClass151590();
};

/** Matrix and plane shape node identified by MAIN vtable D_151600. */
class FieldClass151600 : public FieldClass1515B0
{
public:
    /** @brief Initialize the inherited shape node. */
    FieldClass151600()
    {
    }
    /** @brief Destroy the shape node and its inherited list state. */
    virtual ~FieldClass151600();
    /**
     * @brief Bind the descriptor and compute its matrix and plane.
     * @param shape Associated shape descriptor.
     * @param data Shape data supplying the record.
     * @param index Record index.
     */
    virtual void func_0020DBC0(FieldShapeOwner18* shape, FieldShapeData10* data, s32 index);
    LibMatrix44Value unk20;
    FieldVec4A unk60;
};

#endif

struct FieldClass151640;
struct FieldContext26FF70;
struct FieldClass151620;
struct FieldClass150070;
struct FieldClass151570;
struct LibClass178DD0;
struct FieldShapeOwner18;
#ifdef __cplusplus
extern "C" {
#endif
/** @brief Create nodes for range-kind descriptors and mark their records. @param object Shape data and node lists. @param shape First descriptor in the terminated array. */
void func_0020DA30(struct FieldClass151640* object, struct FieldShapeOwner18* shape);
/** @brief Create shape nodes for descriptors. @param object Shape data and destination lists. @param shape First descriptor in the terminated array. */
void func_0020DBD0(struct FieldClass151640* object, struct FieldShapeOwner18* shape);
/** @brief Create shape nodes and optional animation attachments. @param object Shape data and destination lists. @param context Optional animation context. */
void func_0020DDD0(struct FieldClass151640* object, struct FieldContext26FF70* context);
/** @brief Refresh the named transforms of the attached shape entries. @param object Shape data and list owner. */
void func_0020DE80(struct FieldClass151640* object);
/** @brief Move source nodes into the inherited shape list. @param object Destination shape list owner. @param source Source list. */
void func_0020DEF0(struct FieldClass151640* object, struct LibClass178DD0* source);
/** @brief Move the inherited shape nodes into a destination list. @param object Source shape list owner. @param destination Destination list. */
void func_0020DF80(struct FieldClass151640* object, struct LibClass178DD0* destination);
/** @brief Detach and delete an optional shape node. @param object Shape list owner. @param node Node to remove, or null. */
void func_0020E090(struct FieldClass151640* object, struct FieldClass150070* node);
/** @brief Append the shape entry and bind an optional animation attachment. @param object Shape list owner. @param entry Entry to append. @return Created attachment, or null. */
struct FieldClass151570* func_0020E0D0(struct FieldClass151640* object, struct FieldClass151620* entry);
#ifdef __cplusplus
}
#endif

#endif
