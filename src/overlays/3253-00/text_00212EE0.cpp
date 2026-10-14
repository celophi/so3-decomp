#include "include_asm.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/3253-00/text_00212EE0.h"

extern "C" void func_4815A0(void);
extern "C" void func_481620(void);

extern "C" u8 D_51E050[];
extern "C" u8 D_158910[];
extern "C" u8 D_158900[];

/** A packed quaternion key: signed Q15 vector components followed by a signed key value. */
struct BattleQuaternionKey
{
    s16 x;
    s16 y;
    s16 z;
    s16 key;
};

/** Observed ownership bit in the native channel flags. */
struct BattleQuaternionFlags
{
    u8 unk0 : 1;
    u8 external_keys : 1;
    u8 unk2 : 6;
};

/** The native low and high mode nibbles share one byte. */
struct BattleQuaternionModes
{
    u8 low : 4;
    u8 high : 4;
};

/** Observed quaternion channel fields; the complete native extent is unknown. */
struct BattleQuaternionTrackFields
{
    void* methods;
    BattleQuaternionKey* keys;
    u8 unk08[8];
    u32 unk10;
    float key_span;
    s16 key_count;
    s16 capacity;
    s16 unk1c;
    s16 unk1e;
    s16 unk20;
    BattleQuaternionModes modes;
    BattleQuaternionFlags flags;
};

/** Partial receiver with a point vector at 0x20 and a one-byte flag at 0x50. */
struct BattlePointFlagFields20
{
    u8 unk00[0x20];
    float x;
    float y;
    float z;
    float w;
    u8 unk30[0x20];
    u8 flag50;
};

/** Point value stored as one native 128-bit slot, with its presence byte. */
struct BattlePointFlagSlot20
{
    u8 pad00[0x20];
    unsigned __int128 value20;
    u8 pad30[0x20];
    u8 flag50;
};

struct BattlePointFlagFields30
{
    u8 pad00[0x30];
    float x;
    float y;
    float z;
    float w;
    u8 pad40[0x10];
    u8 flag50;
};

struct BattlePointFlagSlot30
{
    u8 pad00[0x30];
    unsigned __int128 value30;
    u8 pad40[0x10];
    u8 flag50;
};

struct BattlePointFlagSlot40
{
    u8 pad00[0x40];
    unsigned __int128 value40;
    u8 flag50;
};

struct BattlePointFlagFields40
{
    u8 pad00[0x40];
    float x;
    float y;
    float z;
    u8 pad4C[4];
    u8 flag50;
};

extern "C" void func_4E8EE0(void* vector);

struct BattleVectorSlot20
{
    u8 pad[0x20];
    unsigned __int128 slot;
};

/** Partial receiver with four vector components at offset 0x20. */
struct BattleVectorFields20
{
    u8 unk00[0x20];
    float x;
    float y;
    float z;
    float w;
};

struct BattleGetters38
{
    u8 pad[0x30];
    u32 unk30;
    u8 pad34[4];
    s16 unk38;
};

struct BattleGetters18
{
    u8 pad[0x10];
    u32 unk10;
    u8 pad14[4];
    s16 unk18;
};

struct BattleGetters48
{
    u8 pad[0x40];
    u32 unk40;
    u8 pad44[4];
    s16 unk48;
};

struct BattleFloatFields50
{
    u8 pad[0x4C];
    float unk4c;
    float unk50;
};

struct BattleEntryClear1CView
{
    u8 pad00[0x10];
    u16 unk10;
    u16 unk12;
    u32 unk14;
    u32 unk18;
};

struct BattleWordClearView
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
};

struct BattleResetWord48View
{
    u8 pad00[0x48];
    u32 unk48;
};

struct BattleResetWord4CView
{
    u8 pad00[0x4C];
    u32 unk4c;
};

struct BattleMethodTable4CView
{
    u8 pad00[0x4C];
    const void* methods;
};

struct BattleMethodTable1CView
{
    u8 pad00[0x1C];
    const void* methods;
};

struct BattleHalfwordWordClearView
{
    u8 pad00[4];
    u16 unk04;
    u16 unk06;
    u32 unk08;
    u32 unk0c;
};

struct BattleGetters28
{
    u8 pad[0x20];
    u32 unk20;
    u8 pad24[4];
    s16 unk28;
};

struct BattleStateByte60
{
    u8 pad[0x60];
    u8 unk60;
};

extern "C" void func_0021F310(void* object);
extern "C" void func_0021FF30(void* object);

typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x22];
    PackedModePair at22;
    u8 unk24[0x6];
    PackedModePair at2a;
    u8 unk2c[0x6];
    PackedModePair at32;
    u8 unk34[0xE];
    PackedModePair at42;
    u8 unk44[0xE];
    PackedModePair at52;
} PackedModesOwner;

typedef struct FloatKeyScanEntry_text_00212EE0_08
{
    float key00;
    u8 unk04[0x4];
} FloatKeyScanEntry_text_00212EE0_08;

typedef struct FloatKeyScanOwner_text_00212EE0_08
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_00212EE0_08* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x6];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_00212EE0_08;

typedef struct FloatKeyScanEntry_text_00212EE0_10
{
    float key00;
    u8 unk04[0x8];
    float key0c;
} FloatKeyScanEntry_text_00212EE0_10;

typedef struct FloatKeyScanOwner_text_00212EE0_10
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_00212EE0_10* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x6];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_00212EE0_10;

typedef struct FloatKeyScanEntry_text_00212EE0_20
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x10];
} FloatKeyScanEntry_text_00212EE0_20;

typedef struct FloatKeyScanOwner_text_00212EE0_20
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_00212EE0_20* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x6];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_00212EE0_20;

typedef struct FloatKeyScanEntry_text_00212EE0_30
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x20];
} FloatKeyScanEntry_text_00212EE0_30;

typedef struct FloatKeyScanOwner_text_00212EE0_30
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_00212EE0_30* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x6];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_00212EE0_30;

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00212EE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00213C00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00213E70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00214790);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002149E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00215130);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00215DC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00216190);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002161D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00216260);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00216A20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00216B60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00217BC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002180F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00218240);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00218510);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00218640);

void func_00218B50(BattleVectorSlot20* object, const unsigned __int128* value)
{
    object->slot = *value;
}

void func_00218B60(BattleVectorSlot20* object, const unsigned __int128* value)
{
    object->slot = *value;
}

void battle_set_point_vector(BattleVectorFields20* object, float x, float y, float z)
{
    object->x = x;
    object->y = y;
    object->z = z;
    object->w = 1.0f;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00218B90);

s32 func_00218C20(void* object)
{
    return 3;
}

void func_00218C30(void* object)
{
}

extern "C" void func_00218C40(BattlePointFlagSlot20* object, const unsigned __int128* value)
{
    object->flag50 = 1;
    object->value20 = *value;
}

void battle_set_point_vector_and_flag(BattlePointFlagFields20* object, float x, float y, float z)
{
    object->flag50 = 1;
    object->x = x;
    object->y = y;
    object->z = z;
    object->w = 1.0f;
}

extern "C" void func_00218C80(BattlePointFlagFields30* object, float x, float y, float z, float w)
{
    object->flag50 = 1;
    object->x = x;
    object->y = y;
    object->z = z;
    object->w = w;
}

extern "C" void func_00218CA0(BattlePointFlagSlot30* object, const unsigned __int128* value)
{
    object->flag50 = 1;
    object->value30 = *value;
}

extern "C" void func_00218CC0(BattlePointFlagSlot30* object, const unsigned __int128* value)
{
    object->flag50 = 1;
    object->value30 = *value;
}

void func_00218CE0(BattlePointFlagFields30* object)
{
    object->flag50 = 1;
    func_4E8EE0(&object->x);
}

void func_00218D10(BattlePointFlagFields30* object)
{
    object->flag50 = 1;
    func_4E8EE0(&object->x);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00218D40);

extern "C" void func_00218D80(BattlePointFlagSlot40* object, const unsigned __int128* value)
{
    object->flag50 = 1;
    object->value40 = *value;
}

extern "C" void func_00218DA0(BattlePointFlagSlot40* object, const unsigned __int128* value)
{
    object->flag50 = 1;
    object->value40 = *value;
}

extern "C" void func_00218DC0(BattlePointFlagFields40* object, float x, float y, float z)
{
    object->flag50 = 1;
    object->x = x;
    object->y = y;
    object->z = z;
}

void func_00218DE0(void* object)
{
}

void func_00218DF0(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00218E00);

void func_00218E60(BattleStateByte60* object)
{
    object->unk60 = 0;
}

void func_00218E70(void* object)
{
}

s32 func_00218E80(void* object)
{
    return 0;
}

/**
 * @brief Test whether a floating-point value is less than zero.
 * @param value Value to test.
 * @return One for a negative value; zero otherwise, including unordered values.
 */
s32 battle_float_is_negative(float value)
{
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
}

void* func_00218EB0(void)
{
    return D_51E050;
}

void func_00218EC0(void* object)
{
}

s32 func_00218ED0(void* object)
{
    return 0;
}

void func_00218EE0(void* object)
{
}

void func_00218EF0(void* object)
{
}

s32 func_00218F00(void* object)
{
    return 1;
}

void func_00218F10(void* object)
{
}

s32 func_00218F20(void* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00218F30);

s32 func_00218FC0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00218FD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219060);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219110);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002191C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219220);

s32 func_00219250(void* object)
{
    return 9;
}

s32 func_00219260(void* object)
{
    return 0;
}

void func_00219270(BattleStateByte60* object)
{
    object->unk60 = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219280);

void func_002192B0(BattleStateByte60* object)
{
    object->unk60 = 9;
}

void func_002192C0(void* object)
{
}

void func_002192D0(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002192E0);

void func_002193D0(BattleStateByte60* object)
{
    object->unk60 = 6;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002193E0);

void func_002194D0(BattleStateByte60* object)
{
    object->unk60 = 9;
}

void func_002194E0(BattleStateByte60* object)
{
    object->unk60 = 9;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002194F0);

void func_002195E0(BattleStateByte60* object)
{
    object->unk60 = 9;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002195F0);

void func_002196E0(BattleStateByte60* object)
{
    object->unk60 = 9;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002196F0);

void func_002197E0(BattleStateByte60* object)
{
    object->unk60 = 9;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002197F0);

void func_002198E0(BattleStateByte60* object)
{
    object->unk60 = 6;
}

void func_002198F0(BattleStateByte60* object)
{
    object->unk60 = 9;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219900);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219960);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219C60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219CE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219D40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219DB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219E10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00219FB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021A010);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021A320);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021A3A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021A400);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021A470);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021A4D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021A670);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021A6D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021A9D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021AA40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021AAA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021AB00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021ACA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021AD00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B010);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B080);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B0E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B140);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B2E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B340);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B650);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B6C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B720);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B780);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B920);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021B980);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021BC70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021BCD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021BD10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021BEA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021BF00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021C200);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021C260);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021C2A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021C440);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021C4A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021C7B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021C810);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021C850);

void func_0021C9F0(void)
{
    func_4815A0();
}

void func_0021CA10(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021CA20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021CA50);

s32 func_0021CAA0(void* object)
{
    return 0;
}

s32 func_0021CAB0(void* object)
{
    return 0;
}

s32 func_0021CAC0(void* object)
{
    return 0;
}

s32 func_0021CAD0(void* object)
{
    return 0;
}

void func_0021CAE0(void* object)
{
}

void func_0021CAF0(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021CB00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021CB60);

void func_0021CB90(void)
{
    func_481620();
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021CBB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021CC10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021CC40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021CC80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D170);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D1E0);

void func_0021D200(void* object)
{
    BattleResetWord48View* state = (BattleResetWord48View*)object;
    state->unk48 = 0;
    func_0021F310(object);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D220);

void func_0021D250(const BattleFloatFields50* object, float* output)
{
    *output = object->unk4c;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D260);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D2B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D300);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D380);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D3C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D460);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D4F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D570);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021D5B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021DD20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021DE00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021DE70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021DF20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021DF90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E000);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E070);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E150);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E190);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E1B0);

extern "C" void func_0021E230(void* object)
{
    BattleResetWord4CView* state = (BattleResetWord4CView*)object;
    state->unk4c = 0;
    func_0021FF30(object);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E250);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E2B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E310);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E370);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E3D0);

void func_0021E410(const BattleFloatFields50* object, float* output)
{
    *output = object->unk50;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E420);

void* func_0021E450(void* object)
{
    BattleMethodTable4CView* state = (BattleMethodTable4CView*)object;
    state->methods = D_158910;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E470);

void* func_0021E4D0(void* object)
{
    BattleMethodTable1CView* state = (BattleMethodTable1CView*)object;
    state->methods = D_158900;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E4F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E540);

void func_0021E580(void* object)
{
    BattleEntryClear1CView* state = (BattleEntryClear1CView*)object;
    state->unk10 = 0;
    state->unk12 = 0;
    state->unk14 = 0;
    state->unk18 = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E5A0);

void func_0021E5E0(void* object)
{
    BattleEntryClear1CView* state = (BattleEntryClear1CView*)object;
    state->unk10 = 0;
    state->unk12 = 0;
    state->unk14 = 0;
    state->unk18 = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E600);

void func_0021E640(void* object)
{
    BattleHalfwordWordClearView* state = (BattleHalfwordWordClearView*)object;
    state->unk04 = 0;
    state->unk06 = 0;
    state->unk08 = 0;
    state->unk0c = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E660);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E710);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E760);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E810);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E860);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021E910);

/** Set the low packed mode at 0x42 and record whether either mode equals four. */
void func_0021E9A0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.lowMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Set the high packed mode at 0x42 and record whether either mode equals four. */
void func_0021EA00(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.highMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

u32 func_0021EA60(const BattleGetters38* object)
{
    return object->unk30;
}

s16 func_0021EA70(const BattleGetters38* object)
{
    return object->unk38;
}

void func_0021EA80(void* object)
{
    BattleWordClearView* state = (BattleWordClearView*)object;
    state->unk00 = 0;
    state->unk04 = 0;
    state->unk08 = 0;
    state->unk0c = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021EAA0);

u32 func_0021EAF0(const void* object)
{
    return *(const u32*)((const u8*)object + 0x04);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021EB00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021EB50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021EC30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021ED90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021EE40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021EED0);

/** Set the low packed mode at 0x32 and record whether either mode equals four. */
void func_0021EF20(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at32.lowMode = mode;
    receiver->at32.hasModeFour = receiver->at32.lowMode == 4 || receiver->at32.highMode == 4;
}

/** Set the high packed mode at 0x32 and record whether either mode equals four. */
void func_0021EF80(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at32.highMode = mode;
    receiver->at32.hasModeFour = receiver->at32.lowMode == 4 || receiver->at32.highMode == 4;
}

u32 func_0021EFE0(const BattleGetters28* object)
{
    return object->unk20;
}

s16 func_0021EFF0(const BattleGetters28* object)
{
    return object->unk28;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_0021F000(void* object, float key)
{
    FloatKeyScanOwner_text_00212EE0_10* receiver = static_cast<FloatKeyScanOwner_text_00212EE0_10*>(object);
    s16 count = receiver->count28;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key0c)
        {
            return 1;
        }
    }
    return 0;
}

void func_0021F050(void* object)
{
    BattleWordClearView* state = (BattleWordClearView*)object;
    state->unk00 = 0;
    state->unk04 = 0;
    state->unk08 = 0;
    state->unk0c = 0;
}

/** Return the key span between the first and last entries. */
float func_0021F070(void* object)
{
    const FloatKeyScanOwner_text_00212EE0_10* receiver = static_cast<const FloatKeyScanOwner_text_00212EE0_10*>(object);
    s32 count = receiver->count28;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_00212EE0_10* entries = receiver->entries;
    const FloatKeyScanEntry_text_00212EE0_10* lastEntry = entries + --count;
    float first = entries[0].key0c;
    float last = lastEntry->key0c;
    return last - first;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F0C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F120);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F170);

u32 func_0021F200(const void* object)
{
    return *(const u32*)((const u8*)object + 0x04);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F210);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F260);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F310);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F3A0);

/** Set the low packed mode at 0x22 and record whether either mode equals four. */
void func_0021F470(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.lowMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

/** Set the high packed mode at 0x22 and record whether either mode equals four. */
void func_0021F4D0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.highMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

u32 func_0021F530(const BattleGetters18* object)
{
    return object->unk10;
}

s16 func_0021F540(const BattleGetters18* object)
{
    return object->unk18;
}

float func_0021F550(void* object)
{
    return 0.0f;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F560);

u32 func_0021F590(const void* object)
{
    return *(const u32*)((const u8*)object + 0x04);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F5A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F5F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F6A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F6F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F7E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021F950);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021FA00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021FA90);

/** Set the low packed mode at 0x52 and record whether either mode equals four. */
void func_0021FAE0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.lowMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/** Set the high packed mode at 0x52 and record whether either mode equals four. */
void func_0021FB40(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.highMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

u32 func_0021FBA0(const BattleGetters48* object)
{
    return object->unk40;
}

s16 func_0021FBB0(const BattleGetters48* object)
{
    return object->unk48;
}

s32 func_0021FBC0(void* object)
{
    return 0;
}

s32 func_0021FBD0(void* object)
{
    return 0;
}

s32 func_0021FBE0(void* object)
{
    return 0;
}

void func_0021FBF0(void* object)
{
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_0021FC00(void* object, float key)
{
    FloatKeyScanOwner_text_00212EE0_30* receiver = static_cast<FloatKeyScanOwner_text_00212EE0_30*>(object);
    s16 count = receiver->count48;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key0c)
        {
            return 1;
        }
    }
    return 0;
}

void func_0021FC50(void* object)
{
    BattleWordClearView* state = (BattleWordClearView*)object;
    state->unk00 = 0;
    state->unk04 = 0;
    state->unk08 = 0;
    state->unk0c = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021FC70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021FCC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021FD30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021FD80);

u32 func_0021FE20(const void* object)
{
    return *(const u32*)((const u8*)object + 0x04);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021FE30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021FE80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021FF30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_0021FFC0);

/** Set the low packed mode at 0x2A and record whether either mode equals four. */
void func_00220090(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at2a.lowMode = mode;
    receiver->at2a.hasModeFour = receiver->at2a.lowMode == 4 || receiver->at2a.highMode == 4;
}

/** Set the high packed mode at 0x2A and record whether either mode equals four. */
void func_002200F0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at2a.highMode = mode;
    receiver->at2a.hasModeFour = receiver->at2a.lowMode == 4 || receiver->at2a.highMode == 4;
}

u32 func_00220150(const void* object)
{
    return *(const u32*)((const u8*)object + 0x18);
}

s32 func_00220160(const void* object)
{
    return *(const s16*)((const u8*)object + 0x20);
}

s32 func_00220170(void* object)
{
    return 0;
}

s32 func_00220180(void* object)
{
    return 0;
}

s32 func_00220190(void* object)
{
    return 0;
}

void func_002201A0(void* object)
{
}

float func_002201B0(void* object)
{
    return 0.0f;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002201C0);

u32 func_002201F0(const void* object)
{
    return *(const u32*)((const u8*)object + 0x04);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220200);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220250);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002202A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002202F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220380);

/** Return the key span between the first and last entries. */
float func_002203E0(void* object)
{
    const FloatKeyScanOwner_text_00212EE0_10* receiver = static_cast<const FloatKeyScanOwner_text_00212EE0_10*>(object);
    s32 count = receiver->count20;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_00212EE0_10* entries = receiver->entries;
    const FloatKeyScanEntry_text_00212EE0_10* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_00220430(void* object, float key)
{
    FloatKeyScanOwner_text_00212EE0_10* receiver = static_cast<FloatKeyScanOwner_text_00212EE0_10*>(object);
    s16 count = receiver->count20;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220480);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002204D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220540);

void* func_00220620(const void* object)
{
    return (void*)object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220630);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002206A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220710);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002207A0);

/** Return the key span between the first and last entries. */
float func_00220800(void* object)
{
    const FloatKeyScanOwner_text_00212EE0_08* receiver = static_cast<const FloatKeyScanOwner_text_00212EE0_08*>(object);
    s32 count = receiver->count18;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_00212EE0_08* entries = receiver->entries;
    const FloatKeyScanEntry_text_00212EE0_08* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_00220850(void* object, float key)
{
    FloatKeyScanOwner_text_00212EE0_08* receiver = static_cast<FloatKeyScanOwner_text_00212EE0_08*>(object);
    s16 count = receiver->count18;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002208A0);

void func_002208D0(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002208E0);

s32 func_00220910(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220920);

s32 func_00220950(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220960);

s32 func_00220990(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002209A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002209F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220A60);

void func_00220A90(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220AA0);

s32 func_00220AD0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220AE0);

s32 func_00220B10(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220B20);

s32 func_00220B50(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220B60);

void* func_00220C30(const void* object)
{
    return (void*)object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220C40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220CB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220D40);

/** Return the key span between the first and last entries. */
float func_00220DA0(void* object)
{
    const FloatKeyScanOwner_text_00212EE0_20* receiver = static_cast<const FloatKeyScanOwner_text_00212EE0_20*>(object);
    s32 count = receiver->count38;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_00212EE0_20* entries = receiver->entries;
    const FloatKeyScanEntry_text_00212EE0_20* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_00220DF0(void* object, float key)
{
    FloatKeyScanOwner_text_00212EE0_20* receiver = static_cast<FloatKeyScanOwner_text_00212EE0_20*>(object);
    s16 count = receiver->count38;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220E40);

void func_00220E70(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220E80);

s32 func_00220EB0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220EC0);

s32 func_00220EF0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220F00);

s32 func_00220F30(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220F40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00220F90);

void* func_00221060(const void* object)
{
    return (void*)object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221070);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002210E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221150);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002211C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221280);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221300);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221420);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002214C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221580);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002219A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221A30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221B70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221BD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221C50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221D50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221DE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221E70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221ED0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00221FD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00222030);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002220B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002221B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00222240);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002222E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00222330);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002226D0);

/** Set the low packed mode at 0x42 and record whether either mode equals four. */
void func_00222730(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.lowMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Set the low packed mode at 0x52 and record whether either mode equals four. */
void func_00222790(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.lowMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/**
 * @brief Set the low quaternion mode nibble and update the native mode flag.
 * @param object Quaternion channel receiver.
 * @param mode Mode value whose low four bits are stored.
 */
void battle_set_quaternion_low_mode(BattleQuaternionTrackFields* object, s32 mode)
{
    object->modes.low = mode;
    object->flags.unk0 = object->modes.low == 4 || object->modes.high == 4;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00222850);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_002228D0);

void func_00222950(void* object)
{
}

void func_00222960(void* object)
{
}

void func_00222970(void* object)
{
}

/**
 * @brief Reset the observed quaternion channel state and clear its key pointer.
 * @param object Quaternion channel receiver.
 */
void battle_reset_quaternion_channel(BattleQuaternionTrackFields* object)
{
    object->keys = 0;
    object->modes.low = 1;
    object->modes.high = 1;
    object->capacity = 0;
    object->key_count = 0;
    object->unk1c = -1;
    object->unk10 = 0;
    object->unk1e = -1;
    object->unk20 = -1;
    object->flags.unk0 = 0;
    object->flags.external_keys = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00222A10);

/** @brief Use the caller's quaternion keys and record their span. */
void battle_use_external_quaternion_keys(BattleQuaternionTrackFields* object, s32 count, BattleQuaternionKey* keys)
{
    s32 last_index = count - 1;
    object->flags.external_keys = 1;
    object->keys = keys;
    object->capacity = count;
    object->key_count = count;
    const BattleQuaternionKey* last_key = object->keys + last_index;
    object->key_span = (float)last_key->key - (float)object->keys[0].key;
}

/**
 * @brief Set the high quaternion mode nibble and update the native mode flag.
 * @param object Quaternion channel receiver.
 * @param mode Mode value whose low four bits are stored.
 */
void battle_set_quaternion_high_mode(BattleQuaternionTrackFields* object, s32 mode)
{
    object->modes.high = mode;
    object->flags.unk0 = object->modes.low == 4 || object->modes.high == 4;
}

u32 func_00222BA0(const BattleGetters18* object)
{
    return object->unk10;
}

s16 func_00222BB0(const BattleGetters18* object)
{
    return object->unk18;
}

s32 func_00222BC0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00222BD0);

s32 func_00222C00(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00222C10);

s32 func_00222C40(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00222C50);

void func_00222C80(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00222C90);

/** @brief Test whether a packed quaternion track contains an exact key value. */
s32 battle_has_quaternion_key(const BattleQuaternionTrackFields* object, float key)
{
    const BattleQuaternionKey* cursor;
    s32 index = 0;
    s32 key_count = object->key_count;
    if (index < key_count)
    {
        cursor = object->keys;
        do
        {
            if (key == (float)cursor->key)
            {
                return 1;
            }
            ++index;
            ++cursor;
        } while (index < key_count);
    }
    return 0;
}

/** @brief Clear all four vector components. @param vector Vector to clear. */
void battle_clear_vector4(LibVector4* vector)
{
    vector->components[0] = 0.0f;
    vector->components[1] = 0.0f;
    vector->components[2] = 0.0f;
    vector->components[3] = 0.0f;
}

/** @brief Return the difference between the last and first packed quaternion key values. */
float battle_quaternion_key_span(const BattleQuaternionTrackFields* object)
{
    if (object->key_count < 2)
    {
        return 0.0f;
    }
    s32 last_index = object->key_count - 1;
    const BattleQuaternionKey* last_key = object->keys + last_index;
    return (float)last_key->key - (float)object->keys[0].key;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00222DA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00212EE0", func_00222E90);
