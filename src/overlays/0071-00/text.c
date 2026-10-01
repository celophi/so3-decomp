#include "include_asm.h"
#include "overlays/0071-00/text.h"

typedef struct
{
    u8 pad_00[4];
    u32 field_04;
    u8 field_08;
    u8 pad_09;
    u16 field_0a;
    u8 field_0c;
    u8 field_0d;
    u8 pad_0e[2];
    u32 field_10;
    u8 pad_14[0xC];
    u32 field_20;
    u8 pad_24[0x74];
    u32 field_98;
    u32 field_9c;
} ConfigObjectFields;

typedef struct
{
    u8 pad_00[0x24];
    u32 field_24;
} ConfigValue24;

typedef struct
{
    u8 pad_00[0x34];
    u32 field_34;
} ConfigValue34;

typedef struct
{
    u8 pad_00[0x24];
    u32 field_24;
    s8 field_28;
    u8 pad_29[0xF];
    u8 field_38;
} ConfigInputFields;

typedef struct
{
    u8 pad_00[0xAE];
    u8 flag_ae;
    u8 pad_af[0x31];
    float value_e0;
} ConfigDisplay;

typedef struct
{
    u8 pad_00[0xAC];
    ConfigDisplay* display;
} ConfigDisplayOwner;

typedef struct
{
    u8 pad_00[0x3C];
    u8 active;
    u8 pad_3d[0x57];
    u32 color;
} ConfigIcon;

typedef struct ConfigIconNode
{
    ConfigIcon* icon;
    struct ConfigIconNode* next;
} ConfigIconNode;

typedef struct
{
    u8 pad_00[4];
    ConfigIconNode* next;
} ConfigIconList;

typedef struct
{
    u8 pad_00[0x2C];
    ConfigIconList* list;
} ConfigIconOwner;

extern void* func_100AC0(s32 size, s32 flags);
extern void func_2642D0(void* object);
extern u8 D_182170[];

typedef struct
{
    u8 pad_00[0x38];
    void* methods;
} ConfigShell;

extern void func_264230(void* object, s32 flags);
extern void func_2CEAF0(void* object, s32 flags);
extern void func_4618F0(void* object, s32 flags);
extern void func_100B40(void* object);
extern u8 D_181960[];
extern u8 D_181A70[];
extern u8 D_181B70[];
extern u8 D_181C70[];
extern u8 D_181E70[];
extern u8 D_181F70[];
extern u8 D_182070[];
extern u8 D_181A60[];

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003483C0);

void func_00348400(void* object, u8 value)
{
    ((ConfigObjectFields*)object)->field_0c = value;
}

u8 func_00348410(void* object)
{
    return ((ConfigObjectFields*)object)->field_0c;
}

void func_00348420(void* object, u8 value)
{
    ((ConfigObjectFields*)object)->field_08 = value;
}

u8 func_00348430(void* object)
{
    return ((ConfigObjectFields*)object)->field_08;
}

void func_00348440(void* object, u16 value)
{
    ((ConfigObjectFields*)object)->field_0a = value;
}

u16 func_00348450(void* object)
{
    return ((ConfigObjectFields*)object)->field_0a;
}

void func_00348460(void* object, u32 value)
{
    ((ConfigObjectFields*)object)->field_98 = value;
}

u32 func_00348470(void* object)
{
    return ((ConfigObjectFields*)object)->field_98;
}

void func_00348480(void* object, u32 value)
{
    ((ConfigObjectFields*)object)->field_9c = value;
}

u32 func_00348490(void* object)
{
    return ((ConfigObjectFields*)object)->field_9c;
}

void func_003484A0(void* object, u32 value)
{
    ((ConfigObjectFields*)object)->field_04 = value;
}

u32 func_003484B0(void* object)
{
    return ((ConfigObjectFields*)object)->field_04;
}

u32 func_003484C0(void* object)
{
    return ((ConfigObjectFields*)object)->field_10;
}

void func_003484D0(void* object)
{
}

void func_003484E0(void* object)
{
}

void func_003484F0(void* object)
{
}

void func_00348500(void* object)
{
}

void func_00348510(void* object)
{
}

void func_00348520(void* object)
{
}

void func_00348530(void* object)
{
}

void func_00348540(void* object)
{
}

void func_00348550(void* object)
{
}

void func_00348560(void* object)
{
}

void func_00348570(void* object)
{
}

void func_00348580(void* object)
{
}

void func_00348590(void* object)
{
}

void func_003485A0(void* object)
{
}

void func_003485B0(void* object)
{
}

void func_003485C0(void* object)
{
}

void func_003485D0(void* object)
{
}

void func_003485E0(void* object)
{
}

s32 func_003485F0(void* object)
{
    return 0;
}

s32 func_00348600(void* object)
{
    return 0;
}

s32 func_00348610(void* object)
{
    return 0;
}

s32 func_00348620(void* object)
{
    return 0;
}

s32 func_00348630(void* object)
{
    return 0;
}

s32 func_00348640(void* object)
{
    return 0;
}

s32 func_00348650(void* object)
{
    return 0;
}

s32 func_00348660(void* object)
{
    return 0;
}

s32 func_00348670(void* object)
{
    return 0;
}

s32 func_00348680(void* object)
{
    return 0;
}

void func_00348690(void* object)
{
}

void func_003486A0(void* object)
{
}

u8 func_003486B0(void* object)
{
    return ((ConfigObjectFields*)object)->field_0d;
}

void func_003486C0(void* object, u8 value)
{
    ((ConfigObjectFields*)object)->field_0d = value;
}

void func_003486D0(void* object)
{
}

void func_003486E0(void* object, s16 selected)
{
    s32 index = 0;
    ConfigIconNode* node = ((ConfigIconOwner*)object)->list->next;
    if (node != 0)
    {
        do
        {
            ConfigIcon* icon = node->icon;
            if (index == selected)
            {
                icon->color = 0x288080;
                icon->active = 1;
            }
            else
            {
                icon->color = 0x808080;
                icon->active = 1;
            }
            node = node->next;
            index++;
        } while (node != 0);
    }
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00348750);

u32 func_003487B0(void* object)
{
    return ((ConfigObjectFields*)object)->field_20;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003487C0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00348800);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00348840);

void func_003488C0(void* object, u32 value)
{
    ((ConfigObjectFields*)object)->field_20 = value;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003488D0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00348950);

void* func_00348CC0(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181960;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00348D20);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00348E60);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00348FE0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349030);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349070);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003490C0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349110);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349150);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349190);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349230);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349320);

void* func_00349790(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181A70;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

void func_003497F0(void* object)
{
    ConfigDisplay* display = ((ConfigDisplayOwner*)object)->display;
    display->value_e0 = 128.0f;
    display->flag_ae = 1;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349810);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349850);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349890);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003498D0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349910);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349950);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003499F0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00349C70);

void* func_0034A080(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181B70;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034A0E0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034A270);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034A300);

u32 func_0034A420(void* object)
{
    return ((ConfigValue24*)object)->field_24;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034A430);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034A470);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034A4B0);

void* func_0034AC80(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181C70;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034ACE0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034AD30);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034AEC0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034B180);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034B260);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034B340);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034B3D0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034B400);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034B430);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034BA10);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034BB60);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034BD70);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034BF40);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034C140);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034C260);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034C380);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034C600);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034C7C0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034C900);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034CA40);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034CBB0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034CD00);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034D040);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034D180);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034D320);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034D3D0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034D480);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034D510);

u32 func_0034D8A0(void* object)
{
    return ((ConfigValue34*)object)->field_34;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034D8B0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034DB50);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034DDF0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034E090);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034E330);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034E5D0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034EAD0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034EB40);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034EDE0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034F0A0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034F340);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034F5E0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034F880);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034FC70);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_0034FF10);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003501B0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00350270);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00350700);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00350840);

void* func_003510A0(void* object, s32 flags)
{
    if (object != 0)
    {
        ((ConfigShell*)object)->methods = D_181A60;
        func_4618F0(object, -1);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00351100);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003512E0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003514E0);

void* func_003515B0(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181E70;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00351610);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003516B0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00351820);

void* func_00351BD0(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181F70;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00351C30);

void* func_00351F70(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_182070;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00351FD0);

void func_003520B0(void* object)
{
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003520C0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00352110);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00352130);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00352330);

s32 func_003523F0(void* object)
{
    return 1;
}

void* func_00352400(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_182170;
        func_264230(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

ConfigControl* func_00352460(ConfigControl* object)
{
    func_2642D0(object);
    object->methods = D_182170;
    object->field_34 = 0;
    object->field_38 = 0;
    object->field_40 = 0;
    return object;
}

void func_003524A0(void* object)
{
}

s32 func_003524B0(void* object)
{
    return 0;
}

s32 func_003524C0(void* object)
{
    return 0;
}

void func_003524D0(void* object)
{
}

void func_003524E0(void* object)
{
}

void func_003524F0(void* object)
{
}

s32 func_00352500(void* object)
{
    return 4;
}

u8 func_00352510(void* object)
{
    return ((ConfigInputFields*)object)->field_38;
}

void func_00352520(void* object, u32 value)
{
    ((ConfigInputFields*)object)->field_24 = value;
}

void func_00352530(void* object, s8 value)
{
    ((ConfigInputFields*)object)->field_28 = value;
}

s8 func_00352540(void* object)
{
    return ((ConfigInputFields*)object)->field_28;
}

s32 func_00352550(void* object)
{
    return 0;
}

s32 func_00352560(void* object)
{
    return 0;
}

void func_00352570(void* object)
{
}

s32 func_00352580(void* object)
{
    return 0;
}

void func_00352590(void* object)
{
}

void func_003525A0(void* object)
{
}

void func_003525B0(void* object)
{
}

s32 func_003525C0(void* object)
{
    return 0;
}

s32 func_003525D0(void* object)
{
    return 0;
}

s32 func_003525E0(void* object)
{
    return 0;
}

void func_003525F0(void* object)
{
}

void func_00352600(ConfigListOwner* list, void* value)
{
    ConfigNode* node = func_100AC0(8, 0);
    if (node != 0)
    {
        ConfigNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

ConfigNode* func_00352690(ConfigListOwner* owner, s32 index)
{
    ConfigNode* node = owner->head->next;
    s32 i;
    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003526D0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00352750);

void func_003527D0(ConfigListOwner* list, void* value)
{
    ConfigNode* node = func_100AC0(8, 0);
    if (node != 0)
    {
        ConfigNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00352860);

ConfigNode* func_003528E0(ConfigListOwner* owner, s32 index)
{
    ConfigNode* node = owner->head->next;
    s32 i;
    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

void func_00352920(ConfigListOwner* list, void* value)
{
    ConfigNode* node = func_100AC0(8, 0);
    if (node != 0)
    {
        ConfigNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

ConfigNode* func_003529B0(ConfigListOwner* owner, s32 index)
{
    ConfigNode* node = owner->head->next;
    s32 i;
    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_003529F0);

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00352A70);

void func_00352AF0(ConfigListOwner* list, void* value)
{
    ConfigNode* node = func_100AC0(8, 0);
    if (node != 0)
    {
        ConfigNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/0071-00/asm/nonmatchings/text", func_00352B80);

ConfigNode* func_00352C00(ConfigListOwner* owner, s32 index)
{
    ConfigNode* node = owner->head->next;
    s32 i;
    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

void func_00352C40(ConfigListOwner* list, void* value)
{
    ConfigNode* node = func_100AC0(8, 0);
    if (node != 0)
    {
        ConfigNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

void func_00352CD0(ConfigListOwner* list, void* value)
{
    ConfigNode* node = func_100AC0(8, 0);
    if (node != 0)
    {
        ConfigNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}
