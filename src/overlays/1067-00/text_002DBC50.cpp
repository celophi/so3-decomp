#include "include_asm.h"
#include "boot/resident_data.h"
#include "boot/resident_0010A0E0.h"
#include "overlays/0002-01/text_004CD3A0.h"
#include "overlays/1067-00/text_002DBC50.h"

struct FieldReset2DCA70
{
    u8 unused_00[0x40];
    s32 value_40;
    u8 unused_44[4];
    s16 value_48;
    u8 unused_4a[2];
    s16 value_4c;
    s16 value_4e;
    s16 value_50;
};

struct FieldReset2DCA90
{
    u8 unused_00[0x18];
    s32 value_18;
    u8 unused_1c[4];
    s16 value_20;
    u8 unused_22[2];
    s16 value_24;
    s16 value_26;
    s16 value_28;
};

struct FieldFloatState2DCCF0
{
    u8 unused_00[0x90];
    float value_90;
    s32 value_94;
    float value_98;
    s32 value_9c;
    void* value_a0;
    s32 value_a4;
};

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DBC50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DBDC0);

void* func_002DBFF0(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DC000);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DC3E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DC470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DC4C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DC630);

void func_002DCA40(FieldClass150070* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

void func_002DCA70(FieldReset2DCA70* object)
{
    object->value_48 = 0;
    object->value_4c = -1;
    object->value_40 = 0;
    object->value_4e = -1;
    object->value_50 = -1;
}

void func_002DCA90(FieldReset2DCA90* object)
{
    object->value_20 = 0;
    object->value_24 = -1;
    object->value_18 = 0;
    object->value_26 = -1;
    object->value_28 = -1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DCAB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DCBD0);

void func_002DCCF0(FieldFloatState2DCCF0* object, void* value_a0, s32 value_a4, float value_90, float value_98)
{
    object->value_90 = value_90;
    object->value_98 = value_98 / value_90;
    object->value_9c = 0;
    object->value_94 = 0;
    object->value_a4 = value_a4;
    object->value_a0 = value_a0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DCD20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DCD70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DCEF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DD200);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DD440);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DD5F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DD7B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DD870);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DD990);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DDA70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DDAC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002DBC50", func_002DDB50);
