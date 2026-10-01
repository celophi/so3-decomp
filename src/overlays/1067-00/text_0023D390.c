#include "include_asm.h"
#include "overlays/1067-00/text_0023D390.h"


void func_0023D390(void* object)
{
}

void func_0023D3A0(void* object)
{
}

void func_0023D3B0(void* object)
{
}

void func_0023D3C0(FieldFlags4B5* object, u8 value)
{
    object->bit0 = value;
}

void func_0023D3E0(FieldFlags8C* object, u32 value, u32 enable)
{
    if (enable != 0)
    {
        object->bit5 = value ? 0 : 1;
    }
}

void func_0023D420(FieldVectorSlot20* object, const unsigned __int128* value)
{
    if (value != 0)
    {
        object->value = *value;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023D390", func_0023D440);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023D390", func_0023D5D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023D390", func_0023D680);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023D390", func_0023D750);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023D390", func_0023D830);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0023D390", func_0023DB10);
