#ifndef SO3_OVERLAYS_CITEM_ITEM_CONTROLLER_H
#define SO3_OVERLAYS_CITEM_ITEM_CONTROLLER_H

#include "types.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/lib/text_004BD360.h"

/** Item menu controller with DMA notification and Field callback interfaces. */
class ItemController : public LibClass171FF0, public FieldClass153E30
{
    public:
        /** @brief Initialize the controller's bases and clear its window and selection state. */
        ItemController();

        /** @brief Release the controller's selection and destroy its bases. */
        virtual ~ItemController();

        /**
         * @brief Allocate and initialize the controller's record selection.
         * @return One when a selection exists and initialization succeeds; otherwise zero.
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

        /** @brief Submit the controller to the resident object queue. */
        virtual void func_001DD7B0();

        /** @brief Release the controller's resources and dispatch its release handler. */
        virtual void func_slot5c();

        /** @brief Return the record selection. @return Current record selection. */
        virtual FieldRecordSelection* selected_records();

        u8 unk38[8];
        FieldRecordSelection* selection;
        u8 unk44[0x70];
        s32 unkb4;
        u32 category;
        u32 unkbc;
};

#endif
