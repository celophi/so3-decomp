#ifndef SO3_OVERLAYS_CITEM_ITEM_CONTROLLER_H
#define SO3_OVERLAYS_CITEM_ITEM_CONTROLLER_H

#include "types.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/1067-00/text_0028E240.h"

class FieldClass15AE70;

struct ItemCreationAllocationRecord;

class ItemWindow184CF0;

class ItemWindow184BF0;

class ItemWindow184AF0;

class ItemListWindow1848D0;

class ItemWindow1844B0;

class ItemWindow1849F0;

/** Local two-slot base interface used by the item menu controller. */
class ItemClass184380
{
    public:
        /** @brief Perform no action. */
        virtual void func_00353A30();

        /** @brief Perform no action. */
        virtual void func_00353A40();
};

/** Item menu controller with a local interface and a Field callback base. */
class ItemController : public ItemClass184380, public FieldClass153E30
{
    public:
        /** @brief Initialize the controller's bases and clear its window and selection state. */
        ItemController();

        /** @brief Remove flagged records when requested and destroy the controller bases. */
        virtual ~ItemController();

        /**
         * @brief Allocate and populate a missing record selection.
         * @return One after creating and populating the selection; otherwise zero.
         */
        virtual u8 func_00264110();

        /**
         * @brief Load the completed menu resource and create the windows.
         * @param buffer Completed resource buffer.
         * @return Window creation result, or zero for a null buffer.
         */
        virtual s32 on_resource_loaded(void* buffer);

        /** @brief Create the menu windows. @return One after setup. */
        virtual s32 init_windows();

        /** @brief Report whether window setup finished. @return Setup flag. */
        virtual u8 windows_ready();

        /** @brief Return the loaded resource slot. @return Resource slot. */
        virtual u32 get_resource_slot();

        /** @brief Report this object's default list kind. @return The class's list kind. */
        virtual s32 get_default_list_kind();

        /** @brief Release the selection and queue the controller's Field receiver. */
        virtual void func_001DD7B0();

        /** @brief Release loaded resources, detach the controller, and queue its receiver. */
        virtual void func_slot5c();

        /** @brief Return the record selection. @return Current record selection. */
        virtual FieldRecordSelection* selected_records();

        u32 resource_slot;
        u8 windows_initialized : 1;
        u8 unk3c_1_7 : 7;
        u8 unk3d[3];
        FieldRecordSelection* selection;
        ItemWindow184CF0* unk44;
        ItemWindow184BF0* unk48;
        ItemWindow184AF0* unk4c;
        ItemListWindow1848D0* unk50;
        ItemWindow1844B0* unk54;
        ItemWindow1849F0* unk58;
        u8 unk5c;
        u8 unk5d;
        u16 unk5e;
        u8 entries[68];
        s32 entry_count;
        u8 unka8;
        u8 remove_flagged_records;
        s16 record_identifiers[5];
        s32 unkb4;
        u32 category;
        ItemCreationAllocationRecord* unkbc;
};

#endif
