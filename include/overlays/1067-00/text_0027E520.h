#ifndef SO3_OVERLAYS_1067_00_TEXT_0027E520_H
#define SO3_OVERLAYS_1067_00_TEXT_0027E520_H

#include "types.h"
#ifdef __cplusplus
#include "overlays/1067-00/field_class_154D40.h"
#endif

/** Partial holder of an attached object at offset 0x20, reached through D_001B645C. */
typedef struct FieldHeldObject20
{
    u8 unk00[0x20];
    struct FieldClass150070* unk20;
    u8 unk24[0x22C];
    s32 unk250;
} FieldHeldObject20;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject1559A0
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject1559A0;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject155B80
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject155B80;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject155D90
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject155D90;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject156150
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject156150;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject156400
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject156400;

/** Base callback receivers identified by their installed tables. */
typedef struct FieldObject1564D0 FieldObject1564D0;
typedef struct FieldObject156080 FieldObject156080;

/** Base callback receiver identified by table D_156220. */
typedef struct FieldObject156220 FieldObject156220;

/** Base callback receivers identified by their installed tables. */
typedef struct FieldObject155C50 FieldObject155C50;
typedef struct FieldObject155E60 FieldObject155E60;

typedef struct FieldFloatSourceAF0 FieldFloatSourceAF0;
typedef struct FieldResourceHeader273720 FieldResourceHeader273720;
typedef struct FieldResourceRecord273720 FieldResourceRecord273720;

typedef struct FieldBitset154E80 FieldBitset154E80;






#ifdef __cplusplus
/** Partial FieldClass154E70 with vtable D_1565E0 in main data; its only virtual is the destructor. */
class FieldClass1565E0 : public FieldClass154E70
{
public:
    /** @brief Construct the object. */
    FieldClass1565E0();

    /** @brief Destroy the object. */
    virtual ~FieldClass1565E0();

    u8 unk04[0x7C];
};

/** Partial 96-byte grid element with vtable D_156620 in main data. */
class FieldClass156620 : public FieldClass154E70
{
public:
    /** @brief Start with a random delay from 60 to 120 and cleared state. */
    FieldClass156620();

    /** @brief Destroy the object. */
    virtual ~FieldClass156620();

    u8 unk04[0x2C];
    float unk30;
    u8 unk34[4];
    s32 unk38;
    u8 unk3C[0x14];
    u8 unk50;
    u8 unk51[0xF];
};

/** Partial 128-byte grid element with vtable D_156610 in main data. */
class FieldClass156610 : public FieldClass154E70
{
public:
    /** @brief Start with a unit scale. */
    FieldClass156610();

    /** @brief Destroy the object. */
    virtual ~FieldClass156610();

    u8 unk04[0x5C];
    float unk60;
    u8 unk64[0x1C];
};

/** Partial 112-byte grid element with vtable D_156600 in main data. */
class FieldClass156600 : public FieldClass154E70
{
public:
    /** @brief Start with a cleared word and a unit scale. */
    FieldClass156600();

    /** @brief Destroy the object. */
    virtual ~FieldClass156600();

    u8 unk04[0x5C];
    s32 unk60;
    float unk64;
    u8 unk68[8];
};

/** Partial 80-byte grid element with vtable D_1565F0 in main data. */
class FieldClass1565F0 : public FieldClass154E70
{
public:
    /** @brief Start with a 64.0 extent and the first flag set. */
    FieldClass1565F0();

    /** @brief Destroy the object. */
    virtual ~FieldClass1565F0();

    u8 unk04[0x3C];
    float unk40;
    u8 unk44_0 : 1;
    u8 unk44_1_7 : 7;
    u8 unk45[0xB];
};

/** Partial 112-byte grid element with vtable D_156E80 in main data. */
class FieldClass156E80 : public FieldClass154E70
{
public:
    /** @brief Start with 15.0 extents and both flags clear. */
    FieldClass156E80();

    /** @brief Destroy the object. */
    virtual ~FieldClass156E80();

    u8 unk04[0x5C];
    float unk60;
    float unk64;
    u8 unk68[4];
    u8 unk6C_0 : 1;
    u8 unk6C_1 : 1;
    u8 unk6C_2_7 : 6;
    u8 unk6D[3];
};

/** Partial grid of FieldClass156620 cells with vtable D_156710 in main data. */
class FieldClass156710 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass156710();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass156710();

    u8* base14;
    FieldClass156620* unk18;
    FieldBitset154E80* unk1C;
    u8* base20;
    FieldClass154E60* unk24;
};

/** Partial grid of FieldClass156610 cells with vtable D_1567E0 in main data. */
class FieldClass1567E0 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass1567E0();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass1567E0();

    u8* base14;
    FieldClass156610* unk18;
    FieldBitset154E80* unk1C;
    u8* base20;
    FieldClass154E60* unk24;
};

/** Partial grid of FieldClass156600 cells with vtable D_1568B0 in main data. */
class FieldClass1568B0 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass1568B0();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass1568B0();

    u8* base14;
    FieldClass156600* unk18;
    FieldBitset154E80* unk1C;
    u8* base20;
    FieldClass154E60* unk24;
};

/** Partial grid of FieldClass1565F0 cells with vtable D_156980 in main data. */
class FieldClass156980 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass156980();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass156980();

    u8* base14;
    FieldClass1565F0* unk18;
    FieldBitset154E80* unk1C;
    u8* base20;
    FieldClass154E60* unk24;
};

/** Partial grid of FieldClass1565E0 cells with vtable D_156A50 in main data. */
class FieldClass156A50 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass156A50();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass156A50();

    u8* base14;
    FieldClass1565E0* unk18;
    FieldBitset154E80* unk1C;
    u8* base20;
    FieldClass154E60* unk24;
};

/** Partial grid of FieldClass156E80 cells with vtable D_156E90 in main data. */
class FieldClass156E90 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass156E90();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass156E90();

    u8* base14;
    FieldClass156E80* unk18;
    FieldBitset154E80* unk1C;
    u8* base20;
    FieldClass154E60* unk24;
};

/** Partial 128-byte grid element with vtable D_156630 in main data. */
class FieldClass156630 : public FieldClass154E70
{
public:
    /** @brief Start with a unit scale and no flags. */
    FieldClass156630();

    /** @brief Destroy the object. */
    virtual ~FieldClass156630();

    u8 unk04[0x5C];
    float unk60;
    s32 unk64;
    u8 unk68[0x18];
};

/** Partial grid of FieldClass156630 cells with vtable D_156640 in main data. */
class FieldClass156640 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass156640();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass156640();

    u8* base14;
    FieldClass156630* unk18;
    FieldBitset154E80* unk1C;
    u8* base20;
    FieldClass154E60* unk24;
};

/** Partial FieldClass156A50 with vtable D_1559A0 in main data. */
class FieldClass1559A0 : public FieldClass156A50
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1559A0()
    {
    }
};

/** Partial FieldClass156980 with vtable D_155C50 in main data. */
class FieldClass155C50 : public FieldClass156980
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass155C50()
    {
    }
};

/** Partial FieldClass1568B0 with vtable D_155E60 in main data. */
class FieldClass155E60 : public FieldClass1568B0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass155E60()
    {
    }
};

/** Partial FieldClass156640 with vtable D_156080 in main data. */
class FieldClass156080 : public FieldClass156640
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156080()
    {
    }
};

/** Partial FieldClass1567E0 with vtable D_156220 in main data. */
class FieldClass156220 : public FieldClass1567E0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156220()
    {
    }
};

/** Partial FieldClass156710 with vtable D_1564D0 in main data. */
class FieldClass1564D0 : public FieldClass156710
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1564D0()
    {
    }
};

/** Partial FieldClass156E90 with vtable D_156D50 in main data. */
class FieldClass156D50 : public FieldClass156E90
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156D50()
    {
    }
};

/** Partial FieldClass1559A0 with vtable D_155A70 in main data. */
class FieldClass155A70 : public FieldClass1559A0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass155A70()
    {
    }
};

/** Partial FieldClass155C50 with vtable D_155B80 in main data. */
class FieldClass155B80 : public FieldClass155C50
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass155B80();
};

/** Partial FieldClass155E60 with vtable D_155D90 in main data. */
class FieldClass155D90 : public FieldClass155E60
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass155D90();
};

/** Partial FieldClass156080 with vtable D_155FB0 in main data. */
class FieldClass155FB0 : public FieldClass156080
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass155FB0()
    {
    }
};

/** Partial FieldClass156220 with vtable D_1562F0 in main data. */
class FieldClass1562F0 : public FieldClass156220
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1562F0()
    {
    }
};

/** Partial FieldClass1564D0 with vtable D_156400 in main data. */
class FieldClass156400 : public FieldClass1564D0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156400();
};

/** Partial FieldClass156D50 with vtable D_156C80 in main data. */
class FieldClass156C80 : public FieldClass156D50
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156C80();
};

/** Partial FieldClass155A70 with vtable D_1558D0 in main data. */
class FieldClass1558D0 : public FieldClass155A70
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1558D0();
};

/** Partial FieldClass1562F0 with vtable D_156150 in main data. */
class FieldClass156150 : public FieldClass1562F0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156150();
};

/** Partial FieldClass155FB0 with vtable D_156B70 in main data. */
class FieldClass156B70 : public FieldClass155FB0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156B70();
};
#else
typedef struct FieldClass156710 FieldClass156710;
typedef struct FieldClass1567E0 FieldClass1567E0;
typedef struct FieldClass1568B0 FieldClass1568B0;
typedef struct FieldClass156980 FieldClass156980;
typedef struct FieldClass156A50 FieldClass156A50;
typedef struct FieldClass156E90 FieldClass156E90;
typedef struct FieldClass156640 FieldClass156640;
#endif

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject156B70
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject156B70;

/** Partial receiver containing its signed iteration count. */
typedef struct FieldObject156C80
{
    u8 unk00[0x28];
    s32 unk28;
} FieldObject156C80;


/** Base callback receiver identified by table D_156D50. */
typedef struct FieldObject156D50 FieldObject156D50;



/** Callback receiver identified by table D_157020. */
typedef struct FieldObject157020 FieldObject157020;

/** Partial receiver containing the state bit at offset 0x30. */
typedef struct FieldObject157040
{
    u8 unk00[0x30];
    u8 unk30_0_5 : 6;
    u8 unk30_6 : 1;
    u8 unk30_7 : 1;
} FieldObject157040;


typedef struct FieldScriptObject151D40 FieldScriptObject151D40;

#ifdef __cplusplus
extern "C" {
#endif

extern FieldHeldObject20* D_001B645C;

/**
 * @brief Create up to count entries for a value and apply their float setting.
 * @param data Entry owner.
 * @param value Value passed to the entry lookup.
 * @param count Maximum entries to create.
 * @param strength Float setting stored on each created entry.
 */
void func_0027EB80(void* data, void* value, s32 count, float strength);

/**
 * @brief Detach and release the object at offset 0x20 through its virtual handler at vtable offset 0x10, then clear the pointer.
 * @param object Holder of the attached object; nothing happens when the pointer is null.
 */
void func_0027E7D0(FieldHeldObject20* object);

/**
 * @brief Drop one reference and release the attached object when none remain.
 * @param object Holder of the attached object and its reference count.
 */
void func_0027E520(FieldHeldObject20* object);

/**
 * @brief Release the attached object and clear the reference count.
 * @param object Holder of the attached object.
 */
void func_00280AF0(FieldHeldObject20* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_00280620(FieldObject1559A0* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00280630(FieldObject1559A0* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00280640(FieldObject1559A0* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_002808F0(FieldObject155B80* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00280900(FieldObject155B80* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00280910(FieldObject155B80* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_00280BC0(FieldObject155D90* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00280BD0(FieldObject155D90* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00280BE0(FieldObject155D90* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_00280F70(FieldObject156150* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00280F80(FieldObject156150* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00280F90(FieldObject156150* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_002811D0(FieldObject156400* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_002811E0(FieldObject156400* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_002811F0(FieldObject156400* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_002826D0(FieldObject1559A0* object);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_002826E0(FieldObject1559A0* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00282700(FieldObject1559A0* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282750(FieldObject1559A0* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282790(FieldObject1559A0* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00282820(FieldObject1559A0* object, float value);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_00282830(FieldObject1559A0* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_002828A0(FieldObject1559A0* object);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00282860(FieldObject1559A0* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_002828D0(FieldObject155C50* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_002828E0(FieldObject155C50* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00282900(FieldObject155C50* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282950(FieldObject155C50* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282990(FieldObject155C50* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00282A20(FieldObject155C50* object, float value);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_00282A30(FieldObject155C50* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_00282AA0(FieldObject155C50* object);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00282A60(FieldObject155C50* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_00282AD0(FieldObject155E60* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_00282AE0(FieldObject155E60* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00282B00(FieldObject155E60* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282B50(FieldObject155E60* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282B90(FieldObject155E60* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00282C20(FieldObject155E60* object, float value);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_00282C30(FieldObject155E60* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_00282CA0(FieldObject155E60* object);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00282C60(FieldObject155E60* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_00282CD0(FieldObject156220* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_00282CE0(FieldObject156220* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00282D00(FieldObject156220* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282D50(FieldObject156220* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282D90(FieldObject156220* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00282E20(FieldObject156220* object, float value);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_00282E30(FieldObject156220* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_00282EA0(FieldObject156220* object);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00282E60(FieldObject156220* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_00282ED0(FieldObject1564D0* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_00282EE0(FieldObject1564D0* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00282F00(FieldObject1564D0* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282F50(FieldObject1564D0* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00282F90(FieldObject1564D0* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00283020(FieldObject1564D0* object, float value);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_00283030(FieldObject1564D0* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_002830A0(FieldObject1564D0* object);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00283060(FieldObject1564D0* object);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_002830D0(FieldObject156080* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_002830E0(FieldObject156080* object);

/**
 * @brief Leave resource binding unchanged.
 * @param object Callback receiver.
 * @param header Resource descriptor supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00283100(FieldObject156080* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00283150(FieldObject156080* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00283190(FieldObject156080* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00283220(FieldObject156080* object, float value);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_00283230(FieldObject156080* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_002832A0(FieldObject156080* object);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00283260(FieldObject156080* object);

/**
 * @brief Get the address of an element in the 128-byte-stride array.
 * @param object Receiver holding the array base.
 * @param index Element index.
 * @return Address of the indexed element.
 */
void* func_00283320(FieldClass156A50* object, s32 index);

/**
 * @brief Get an address in the receiver's 64-byte-stride grid.
 * @param object Receiver holding the grid width and base.
 * @param row Row index.
 * @param column Column index.
 * @return Address selected by the row and column.
 */
void* func_00283330(FieldClass156A50* object, s32 row, s32 column);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_00283350(FieldClass156A50* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_00283360(FieldClass156A50* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_00283370(FieldClass156A50* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 0x20.
 */
u32 func_00283380(FieldClass156A50* object);

/**
 * @brief Report whether the receiver has an array at offset 0x14.
 * @param object Receiver holding the optional array.
 * @return One when the array exists, otherwise zero.
 */
s32 func_00283390(FieldClass156A50* object);

/**
 * @brief Get the address of an element in the 80-byte-stride array.
 * @param object Receiver holding the array base.
 * @param index Element index.
 * @return Address of the indexed element.
 */
void* func_00283440(FieldClass156980* object, s32 index);

/**
 * @brief Get an address in the receiver's 64-byte-stride grid.
 * @param object Receiver holding the grid width and base.
 * @param row Row index.
 * @param column Column index.
 * @return Address selected by the row and column.
 */
void* func_00283460(FieldClass156980* object, s32 row, s32 column);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_00283480(FieldClass156980* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_00283490(FieldClass156980* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_002834A0(FieldClass156980* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 1.
 */
u32 func_002834B0(FieldClass156980* object);

/**
 * @brief Report whether the receiver has an array at offset 0x14.
 * @param object Receiver holding the optional array.
 * @return One when the array exists, otherwise zero.
 */
s32 func_002834C0(FieldClass156980* object);

/**
 * @brief Get the address of an element in the 112-byte-stride array.
 * @param object Receiver holding the array base.
 * @param index Element index.
 * @return Address of the indexed element.
 */
void* func_00283570(FieldClass1568B0* object, s32 index);

/**
 * @brief Get an address in the receiver's 64-byte-stride grid.
 * @param object Receiver holding the grid width and base.
 * @param row Row index.
 * @param column Column index.
 * @return Address selected by the row and column.
 */
void* func_00283590(FieldClass1568B0* object, s32 row, s32 column);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002835B0(FieldClass1568B0* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_002835C0(FieldClass1568B0* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_002835D0(FieldClass1568B0* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 0x20.
 */
u32 func_002835E0(FieldClass1568B0* object);

/**
 * @brief Report whether the receiver has an array at offset 0x14.
 * @param object Receiver holding the optional array.
 * @return One when the array exists, otherwise zero.
 */
s32 func_002835F0(FieldClass1568B0* object);

/**
 * @brief Get the address of an element in the 128-byte-stride array.
 * @param object Receiver holding the array base.
 * @param index Element index.
 * @return Address of the indexed element.
 */
void* func_002836A0(FieldClass1567E0* object, s32 index);

/**
 * @brief Get an address in the receiver's 64-byte-stride grid.
 * @param object Receiver holding the grid width and base.
 * @param row Row index.
 * @param column Column index.
 * @return Address selected by the row and column.
 */
void* func_002836B0(FieldClass1567E0* object, s32 row, s32 column);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002836D0(FieldClass1567E0* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_002836E0(FieldClass1567E0* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_002836F0(FieldClass1567E0* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 0x20.
 */
u32 func_00283700(FieldClass1567E0* object);

/**
 * @brief Report whether the receiver has an array at offset 0x14.
 * @param object Receiver holding the optional array.
 * @return One when the array exists, otherwise zero.
 */
s32 func_00283710(FieldClass1567E0* object);

/**
 * @brief Get the address of an element in the 96-byte-stride array.
 * @param object Receiver holding the array base.
 * @param index Element index.
 * @return Address of the indexed element.
 */
void* func_002837C0(FieldClass156710* object, s32 index);

/**
 * @brief Get an address in the receiver's 64-byte-stride grid.
 * @param object Receiver holding the grid width and base.
 * @param row Row index.
 * @param column Column index.
 * @return Address selected by the row and column.
 */
void* func_002837E0(FieldClass156710* object, s32 row, s32 column);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_00283800(FieldClass156710* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_00283810(FieldClass156710* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_00283820(FieldClass156710* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 1.
 */
u32 func_00283830(FieldClass156710* object);

/**
 * @brief Report whether the receiver has an array at offset 0x14.
 * @param object Receiver holding the optional array.
 * @return One when the array exists, otherwise zero.
 */
s32 func_00283840(FieldClass156710* object);

/**
 * @brief Get the address of an element in the 128-byte-stride array.
 * @param object Receiver holding the array base.
 * @param index Element index.
 * @return Address of the indexed element.
 */
void* func_002838F0(FieldClass156640* object, s32 index);

/**
 * @brief Get an address in the receiver's 64-byte-stride grid.
 * @param object Receiver holding the grid width and base.
 * @param row Row index.
 * @param column Column index.
 * @return Address selected by the row and column.
 */
void* func_00283900(FieldClass156640* object, s32 row, s32 column);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_00283920(FieldClass156640* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_00283930(FieldClass156640* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_00283940(FieldClass156640* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 0x20.
 */
u32 func_00283950(FieldClass156640* object);

/**
 * @brief Report whether the receiver has an array at offset 0x14.
 * @param object Receiver holding the optional array.
 * @return One when the array exists, otherwise zero.
 */
s32 func_00283960(FieldClass156640* object);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002839B0(FieldClass156640* object, s32 rows, s32 columns);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286400(FieldClass156A50* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286410(FieldClass156980* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286420(FieldClass1568B0* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286430(FieldClass1567E0* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286440(FieldClass156710* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00286450(FieldClass156640* object);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Callback receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00286620(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Callback receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00286880(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Callback receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_00286890(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Complete this script command without changing its receiver.
 * @param object Callback receiver.
 * @param count Number of command operand words.
 * @return One to advance to the following command.
 */
s32 func_002868A0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_00288220(FieldObject156B70* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00288230(FieldObject156B70* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00288240(FieldObject156B70* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 3.
 */
u32 func_00288640(FieldObject156C80* object);

/**
 * @brief Reset the signed iteration count.
 * @param object Callback receiver.
 * @param actor Actor supplied by the dispatcher.
 */
void func_00288650(FieldObject156C80* object, FieldFloatSourceAF0* actor);

/**
 * @brief Return the floating-point limit.
 * @param object Callback receiver.
 * @return Always 2500.0f.
 */
float func_00288660(FieldObject156C80* object);

/**
 * @brief Report the callback's default state.
 * @param object Callback receiver.
 * @return Always one.
 */
s32 func_00288680(FieldObject156C80* object);

/**
 * @brief Perform the default callback without changing the receiver.
 * @param object Callback receiver.
 */
void func_00289450(FieldObject156D50* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_00289460(FieldObject156D50* object);

/**
 * @brief Leave the callback receiver unchanged.
 * @param object Callback receiver.
 */
void func_00289470(FieldObject156D50* object);

/**
 * @brief Handle the resource callback without changing the receiver.
 * @param object Callback receiver.
 * @param resource Resource descriptor supplied by the dispatcher.
 * @param records Resource records supplied by the dispatcher.
 */
void func_00289480(FieldObject156D50* object, FieldResourceHeader273720* resource, FieldResourceRecord273720* records);

/**
 * @brief Get the first default element count.
 * @param object Callback receiver.
 * @return Always zero.
 */
s32 func_002894D0(FieldObject156D50* object);

/**
 * @brief Get the second default element count.
 * @param object Callback receiver.
 * @return Always zero.
 */
s32 func_00289510(FieldObject156D50* object);

/**
 * @brief Handle the floating-point callback without changing the receiver.
 * @param object Callback receiver.
 * @param value Floating-point value supplied by the dispatcher.
 */
void func_002895A0(FieldObject156D50* object, float value);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_002895B0(FieldObject156D50* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 0.0f.
 */
float func_00289620(FieldObject156D50* object);

/**
 * @brief Get the default byte mode.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_002895E0(FieldObject156D50* object);

/**
 * @brief Get the address of an element in the 112-byte-stride array.
 * @param object Receiver holding the array base.
 * @param index Element index.
 * @return Address of the indexed element.
 */
void* func_002896A0(FieldClass156E90* object, s32 index);

/**
 * @brief Get an address in the receiver's 64-byte-stride grid.
 * @param object Receiver holding the grid width and base.
 * @param row Row index.
 * @param column Column index.
 * @return Address selected by the row and column.
 */
void* func_002896C0(FieldClass156E90* object, s32 row, s32 column);

/**
 * @brief Get the associated bitset object.
 * @param object Callback receiver.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002896E0(FieldClass156E90* object);

/**
 * @brief Get the first configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_002896F0(FieldClass156E90* object);

/**
 * @brief Get the second configured dimension.
 * @param object Callback receiver.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_00289700(FieldClass156E90* object);

/**
 * @brief Report the supported operation flags.
 * @param object Callback receiver.
 * @return Always 1.
 */
u32 func_00289710(FieldClass156E90* object);

/**
 * @brief Report whether the receiver has an array at offset 0x14.
 * @param object Receiver holding the optional array.
 * @return One when the array exists, otherwise zero.
 */
s32 func_00289720(FieldClass156E90* object);

/**
 * @brief Return the default floating-point value.
 * @param object Callback receiver.
 * @return Always 1.0f.
 */
float func_00289EB0(FieldClass156E90* object);

/**
 * @brief Report the default signed category.
 * @param object Callback receiver.
 * @return Always 4.
 */
s32 func_0028E130(FieldObject157020* object);

/**
 * @brief Report the default signed category.
 * @param object Callback receiver.
 * @return Always 2.
 */
s32 func_0028E1E0(FieldObject157040* object);

/**
 * @brief Set bit 6 of the receiver state byte.
 * @param object Callback receiver.
 */
void func_0028E1F0(FieldObject157040* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0027F3D0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00280660(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00280930(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00280AE0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00280C00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00280EE0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00280FB0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00281210(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002826C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002826F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282710(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282720(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282730(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282740(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282760(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282770(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282780(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002827A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002827B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002827C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002827D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002827E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002827F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282800(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282810(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282840(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282850(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282870(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282880(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282890(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002828B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002828C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002828F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282910(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282920(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282930(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282940(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282960(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282970(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282980(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002829A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002829B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002829C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002829D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002829E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002829F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282A00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282A10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282A40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282A50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282A70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282A80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282A90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282AB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282AC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282AF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282B80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282BA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282BB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282BC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282BD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282BE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282BF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282C00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282C10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282C40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282C50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282C70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282C80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282C90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282CB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282CC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282CF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282D80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282DA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282DB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282DC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282DD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282DE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282DF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282E00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282E10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282E40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282E50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282E70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282E80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282E90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282EB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282EC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282EF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282F80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282FA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282FB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282FC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282FD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00282FE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00282FF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283000(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00283010(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283040(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283050(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283070(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00283080(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283090(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002830B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002830C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002830F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283110(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283120(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283130(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283140(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283160(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283170(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283180(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002831A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002831B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002831C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002831D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002831E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002831F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283200(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00283210(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283240(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283250(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283270(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00283280(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00283290(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002832B0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00287600(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00288260(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00288450(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002892C0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00289430(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00289440(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289490(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002894A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002894B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002894C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002894E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002894F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289500(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289520(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289530(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289550(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289560(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00289570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289580(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00289590(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002895C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002895D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002895F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00289600(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289610(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00289630(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_0028E090(void* object);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002840B0(FieldClass156710* object, s32 rows, s32 columns);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002847F0(FieldClass1567E0* object, s32 rows, s32 columns);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_00284EE0(FieldClass1568B0* object, s32 rows, s32 columns);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002855F0(FieldClass156980* object, s32 rows, s32 columns);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_00285D10(FieldClass156A50* object, s32 rows, s32 columns);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_00289770(FieldClass156E90* object, s32 rows, s32 columns);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00283970(FieldClass156640* object, const FieldClass156640* other);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00283850(FieldClass156710* object, const FieldClass156710* other);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00283720(FieldClass1567E0* object, const FieldClass1567E0* other);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00283600(FieldClass1568B0* object, const FieldClass1568B0* other);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002834D0(FieldClass156980* object, const FieldClass156980* other);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002833A0(FieldClass156A50* object, const FieldClass156A50* other);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00289730(FieldClass156E90* object, const FieldClass156E90* other);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"

/** Partial Field object with vtable D_156E60 in main data and an owned child at offset 0x40. */
class FieldClass156E60 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass156E60();
    /** @brief Detach and delete the child, then detach this object and queue it for release. */
    virtual void func_001DD7B0();
    u8 unk14[0x2C];
    FieldClass150070* unk40;
};
#endif

#endif
