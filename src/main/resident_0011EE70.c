#include "include_asm.h"
#include "main/resident_0011EE70.h"

typedef struct ByteGetterOwnerresident_0011EE70
{
    u8 unk00[0x25];
    u8 unk25;
} ByteGetterOwnerresident_0011EE70;



typedef struct WordSetterOwnerresident_0011EE70
{
    u8 unk00[0x70];
    u32 unk70;
} WordSetterOwnerresident_0011EE70;



typedef struct WordGetterOwnerresident_0011EE70
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
    u32 unk10;
    u32 unk14;
} WordGetterOwnerresident_0011EE70;


INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011EE70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011EED0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011EF00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011EF90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F020);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F0B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F140);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F1D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F390);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F510);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F580);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F640);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F6E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F760);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F770);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F830);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F860);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F8A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F940);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F9B0);

/** Return the unsigned byte at receiver offset 0x25. */
u8 func_0011F9D0(void* object)
{
    const ByteGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk25;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F9E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011FA80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011FB40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011FC20);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011FFD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120050);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001200C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120360);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120370);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001203C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120410);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001204B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120560);

/** Return the word at receiver offset 0x14. */
u32 func_001205A0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk14;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001205B0);

/** Return the word at receiver offset 0x10. */
u32 func_001205E0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk10;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001205F0);

/** Return the word at receiver offset 0xC. */
u32 func_00120630(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk0c;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120640);

/** Return the word at receiver offset 0x8. */
u32 func_00120670(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk08;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120680);

/** Return the word at receiver offset 0x4. */
u32 func_001206B0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk04;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001206C0);

/** Return the word at receiver offset 0x0. */
u32 func_001206F0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk00;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120700);

/** Store the word at receiver offset 0x70. */
void func_001207B0(void* object, u32 value)
{
    WordSetterOwnerresident_0011EE70* receiver = object;
    receiver->unk70 = value;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001207C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001207D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001207E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120840);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120A50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120A60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120A70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120BF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120EB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120ED0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120EF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120F20);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120FE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001210B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001212A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001213B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121490);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121520);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121570);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121580);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121590);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001215A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001215B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001215C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001215D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001215E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001215F0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121610);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121620);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121630);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121640);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121650);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121670);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121690);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001216B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001216D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121700);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121730);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121770);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121790);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001217B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001217D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001217E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121800);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121810);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121820);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121830);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121840);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121850);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121860);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121870);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121880);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121890);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001218A0);
