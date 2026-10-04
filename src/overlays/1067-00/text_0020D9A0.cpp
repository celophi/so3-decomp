#include "include_asm.h"
#include "overlays/1067-00/text_0020D9A0.h"
#include "overlays/1067-00/text_00207AF0.h"
#include "overlays/1067-00/text_0026EE10.h"
#include "main/resident_data.h"
#include "main/resident_0012F0F8.h"
#include "overlays/lib/text_0046AE20.h"

/** @brief Test the descriptor terminal flag. @param shape Descriptor to test. @return Whether the array ends here. */
static inline bool field_owner_is_last(const FieldShapeOwner18* shape)
{
    if (shape->unk0a & 0x20)
    {
        return true;
    }
    return false;
}


/**
 * @brief Create range-kind nodes for descriptors and mark their associated records.
 * @param object Receiver supplying shape data and the destination list.
 * @param shape First descriptor in the terminated descriptor array.
 */
extern "C" void func_0020DA30(FieldClass151640* object, FieldShapeOwner18* shape)
{
    FieldShapeRecord20* records = ((FieldShapeData10*)object->FieldClass1515D0::unk00)->unk0c;
    for (;; shape++)
    {
        s32 index = shape->unk0e;
        if (shape->unk0b >= 0x40 && shape->unk0b < 0x7F && shape->unk04 && index != -1)
        {
            FieldClass151590* node = new (0) FieldClass151590;
            node->func_0020DBC0(shape, (FieldShapeData10*)object->FieldClass1515D0::unk00, index);
            object->unk178.func_004D74F0(node, (void*)-1);
            for (;; index++)
            {
                records[index].unk0c_4 = 1;
                if (records[index].unk0c_5)
                {
                    break;
                }
            }
        }
        if (shape->unk00)
        {
            func_0020DA30(object, shape->unk00);
        }
        if (field_owner_is_last(shape))
        {
            break;
        }
    }
}

/**
 * @brief Bind the descriptor, shape data and starting record index.
 * @param shape Descriptor associated with the node.
 * @param data Shape data supplying the records.
 * @param index Starting record index.
 */
void FieldClass1515B0::func_0020DBC0(FieldShapeOwner18* shape, FieldShapeData10* data, s32 index)
{
    unk14 = data;
    unk18 = shape;
    unk1c = index;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020D9A0", func_0020DBD0);

/**
 * @brief Create each kind of shape node and optional animation attachments.
 * @param object Shape resource and destination lists.
 * @param context Optional context supplying the animation manager.
 */
extern "C" void func_0020DDD0(FieldClass151640* object, FieldContext26FF70* context)
{
    if (object->FieldClass1515D0::unk00)
    {
        func_0020DBD0(object, (FieldShapeOwner18*)((FieldShapeData30*)object->FieldClass1515D0::unk00 + 1));
        func_0020DA30(object, (FieldShapeOwner18*)((FieldShapeData30*)object->FieldClass1515D0::unk00 + 1));
        func_0020D810(object, (FieldShapeOwner18*)((FieldShapeData30*)object->FieldClass1515D0::unk00 + 1));
        if (context)
        {
            func_0020D5E0(object, context->unk8c, (FieldShapeOwner18*)((FieldShapeData30*)object->FieldClass1515D0::unk00 + 1));
        }
    }
}

/** @brief Update the attached shape-node list. */
void FieldClass151640::func_0020BDA0()
{
    unk88.func_004D6730();
}

/**
 * @brief Refresh the named transforms of the receiver's attached shape entries.
 * @param object Shape resource containing the entries.
 */
extern "C" void func_0020DE80(FieldClass151640* object)
{
    FieldClass151620* node = (FieldClass151620*)&object->FieldClass1502A0::unk00;
    for (;;)
    {
        node = static_cast<FieldClass151620*>(node->unk08);
        if ((FieldClass151620*)&object->FieldClass1502A0::unk00 == node)
        {
            break;
        }
        func_0013A4C0(node->unk84, node->unk84, 0x11);
        node->shape.unk04 = (LibClass178A90*)func_00473390(((FieldClass150F90*)D_001B6430->context->unk08->unkdc)->unk7c, node->unk84);
    }
}

/**
 * @brief Transfer every node from the source list into the shape resource's inherited list.
 * @param object Shape resource receiving the nodes.
 * @param source List supplying the nodes.
 */
extern "C" void func_0020DEF0(FieldClass151640* object, LibClass178DD0* source)
{
    FieldClass150060* current;
    FieldClass150060* node = ((FieldClass150060*)source)->unk08;
    for (;;)
    {
        current = node;
        if (!node || (FieldClass150060*)source == node)
        {
            break;
        }
        node = node->unk08;
        func_004D65C0(current);
        object->func_004D74F0(current, (void*)-1);
    }
}

/**
 * @brief Transfer every node from the shape resource's inherited list into another list.
 * @param object Shape resource supplying the nodes.
 * @param destination List receiving the nodes.
 */
extern "C" void func_0020DF80(FieldClass151640* object, LibClass178DD0* destination)
{
    FieldClass150060* current;
    FieldClass150060* node = ((FieldClass150060*)object->FieldClass1502A0::unk00)->unk08;
    for (;;)
    {
        current = node;
        if (!node || (FieldClass150060*)object->FieldClass1502A0::unk00 == node)
        {
            break;
        }
        node = node->unk08;
        func_004D65C0(current);
        destination->func_004D74F0(current, (void*)-1);
    }
}

/** @brief Detach and delete the nodes in the inherited shape list. */
void FieldClass151640::func_001DD730()
{
    FieldClass150060* current;
    FieldClass150060* node = ((FieldClass150060*)FieldClass1502A0::unk00)->unk08;
    for (;;)
    {
        current = node;
        if (!node || (FieldClass150060*)FieldClass1502A0::unk00 == node)
        {
            break;
        }
        node = node->unk08;
        func_004D65C0(current);
        static_cast<FieldClass150070*>(current)->func_001DD7B0();
    }
}

/**
 * @brief Detach and delete the optional shape node.
 * @param object Shape resource receiving the request.
 * @param node Node to remove, or null.
 */
extern "C" void func_0020E090(FieldClass151640* object, FieldClass150070* node)
{
    if (node)
    {
        func_004D65C0(node);
        node->func_001DD7B0();
    }
}

/**
 * @brief Append the shape entry and bind its optional animation attachment.
 * @param object Shape resource receiving the entry.
 * @param entry Entry supplying the descriptor and attachment back-pointer.
 * @return Created attachment, or null.
 */
extern "C" FieldClass151570* func_0020E0D0(FieldClass151640* object, FieldClass151620* entry)
{
    object->func_004D74F0(entry, (void*)-1);
    FieldClass151570* attachment = func_0020D5E0(object,
        ((FieldRoot26FF70*)D_001B6430->context->unk08->unkdc)->unkD8->unk8c, &entry->shape);
    if (attachment)
    {
        attachment->unk20 = entry;
        entry->unk80 = attachment;
    }
    return attachment;
}

/** @brief Destroy the range-kind shape node and its inherited list state. */
FieldClass151590::~FieldClass151590()
{
}

/** @brief Destroy the specialized node and its inherited list state. */
FieldClass1515E0::~FieldClass1515E0()
{
}

/** @brief Destroy the matrix and plane shape node and its inherited list state. */
FieldClass151600::~FieldClass151600()
{
}

/** @brief Destroy all shape lists and the inherited resource storage. */
FieldClass151640::~FieldClass151640()
{
    func_001DD730();
    unk88.func_001DD730();
    unk100.func_001DD730();
    unk178.func_001DD730();
    unk1f0.func_001DD730();
}
