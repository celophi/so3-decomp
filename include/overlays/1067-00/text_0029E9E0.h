#ifndef SO3_OVERLAYS_1067_00_TEXT_0029E9E0_H
#define SO3_OVERLAYS_1067_00_TEXT_0029E9E0_H

#include "overlays/1067-00/text_00293610.h"
#include "overlays/1067-00/text_00273720.h"
#include "overlays/1067-00/field_class_154D40.h"

typedef struct FieldLinkedObject157F00 FieldLinkedObject157F00;

/** Partial scalar state of the distinct D_157F00 class hierarchy. */
typedef struct FieldObject157F00
{
    u8 unk00[0x28];
    float unk28;
    s32 unk2C;
    float unk30;
    float unk34;
    float unk38;
    float unk3C;
    float unk40;
    float unk44;
    FieldLinkedObject157F00* unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    FieldLinkedObject157F00* unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    FieldVector4 unk60;
    FieldVector4 unk70;
    FieldVector4 unk80;
    FieldVector4 unk90;
    u8* unkA0;
    FieldResourceRecord273720* unkA4;
} FieldObject157F00;

/** Partial FieldClass154E70 with vtable D_158A68 in main data: the common grid element base. */
class FieldClass158A68 : public FieldClass154E70
{
public:
    /** @brief Construct the object. */
    FieldClass158A68()
    {
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass158A68()
    {
    }

    /**
     * @brief Get the cell position.
     * @return The position vector.
     */
    const FieldVector4& position() const
    {
        return unk10;
    }

    u8 unk04[0xC];
    FieldVector4 unk10;
    FieldVector4 unk20;
    u8 unk30[0xC];
    float unk3C;
};

/** Partial FieldClass158A68 with vtable D_158A48 in main data; it adds no fields. */
class FieldClass158A48 : public FieldClass158A68
{
public:
    /** @brief Construct the object. */
    FieldClass158A48()
    {
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass158A48()
    {
    }
};

/** Partial FieldClass158A48 with vtable D_158A28 in main data; it adds no fields. */
class FieldClass158A28 : public FieldClass158A48
{
public:
    /** @brief Construct the object. */
    FieldClass158A28()
    {
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass158A28()
    {
    }
};

/** Partial FieldClass158A28 with vtable D_158A08 in main data; it adds no fields. */
class FieldClass158A08 : public FieldClass158A28
{
public:
    /** @brief Construct the object. */
    FieldClass158A08()
    {
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass158A08()
    {
    }
};

/** Complete 0x90-byte grid element with vtable D_158A58 in main data. */
class FieldClass158A58 : public FieldClass158A68
{
public:
    /** @brief Construct the object. */
    FieldClass158A58();

    /** @brief Destroy the object. */
    virtual ~FieldClass158A58();

    FieldVector4 unk40;
    FieldVector4 unk50;
    u8 unk60[0x30];
};

/** Complete 0xB0-byte grid element with vtable D_158A38 in main data. */
class FieldClass158A38 : public FieldClass158A48
{
public:
    /** @brief Construct the object. */
    FieldClass158A38();

    /** @brief Destroy the object. */
    virtual ~FieldClass158A38();

    u8 unk40[0x70];
};

/** Complete 0x120-byte grid element with vtable D_158A18 in main data. */
class FieldClass158A18 : public FieldClass158A28
{
public:
    /** @brief Construct the object. */
    FieldClass158A18();

    /** @brief Destroy the object. */
    virtual ~FieldClass158A18();

    u8 unk40[0xB0];
    u8 unkF0[0x30];
};

/** Complete 0x170-byte grid element with vtable D_1589F8 in main data. */
class FieldClass1589F8 : public FieldClass158A08
{
public:
    /** @brief Construct the object. */
    FieldClass1589F8();

    /** @brief Destroy the object. */
    virtual ~FieldClass1589F8();

    u8 unk40[0x130];
};

/** Complete 0x60-byte grid element with vtable D_158A78 in main data. */
class FieldClass158A78 : public FieldClass154E70
{
public:
    /** @brief Construct the object. */
    FieldClass158A78();

    /** @brief Destroy the object. */
    virtual ~FieldClass158A78();

    /**
     * @brief Get the cell position.
     * @return The position vector.
     */
    const FieldVector4& position() const
    {
        return unk10;
    }

    u8 unk04[0xC];
    FieldVector4 unk10;
    FieldVector4 unk20;
    u8 unk30[0xC];
    float unk3C;
    u8 unk40[0x20];
};

/** Partial grid of FieldClass1589F8 cells with vtable D_158DD0 in main data. */
class FieldClass158DD0 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass158DD0();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass158DD0();

    FieldClass1589F8* unk14;
    FieldClass1589F8* unk18;
    FieldBitset154E80* unk1C;
    FieldObject154E60* unk20;
    FieldClass154E60* unk24;
};

/** Partial FieldClass158DD0 with vtable D_158860 in main data. */
class FieldClass158860 : public FieldClass158DD0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158860()
    {
    }

    float unk28;
    s32 unk2C;
    float unk30;
    float unk34;
    float unk38;
    float unk3C;
    float unk40;
    float unk44;
    FieldLinkedObject157F00* unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    FieldLinkedObject157F00* unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    FieldVector4 unk60;
    FieldVector4 unk70;
    FieldVector4 unk80;
    FieldVector4 unk90;
    u8* unkA0;
    FieldResourceRecord273720* unkA4;
};

/** Partial FieldClass158860 with vtable D_158930 in main data; it owns two arrays unless they are borrowed. */
class FieldClass158930 : public FieldClass158860
{
public:
    /** @brief Release the arrays unless they are borrowed. */
    virtual ~FieldClass158930();

    u8* unkB0;
    FieldVec4A* unkB4;
    u8 unkB8[0x11];
    bool unkC9;
};


/** Partial grid of FieldClass158A18 cells with vtable D_158D00 in main data. */
class FieldClass158D00 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass158D00();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass158D00();

    FieldClass158A18* unk14;
    FieldClass158A18* unk18;
    FieldBitset154E80* unk1C;
    FieldObject154E60* unk20;
    FieldClass154E60* unk24;
};

/** Partial grid of FieldClass158A38 cells with vtable D_158C30 in main data. */
class FieldClass158C30 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass158C30();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass158C30();

    FieldClass158A38* unk14;
    FieldClass158A38* unk18;
    FieldBitset154E80* unk1C;
    FieldObject154E60* unk20;
    FieldClass154E60* unk24;
};

/** Partial grid of FieldClass158A58 cells with vtable D_158B60 in main data. */
class FieldClass158B60 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass158B60();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass158B60();

    FieldClass158A58* unk14;
    FieldClass158A58* unk18;
    FieldBitset154E80* unk1C;
    FieldObject154E60* unk20;
    FieldClass154E60* unk24;
};

/** Partial grid of FieldClass158A78 cells with vtable D_158A90 in main data. */
class FieldClass158A90 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass158A90();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass158A90();

    FieldClass158A78* unk14;
    FieldClass158A78* unk18;
    FieldBitset154E80* unk1C;
    FieldObject154E60* unk20;
    FieldClass154E60* unk24;
};

/** Partial FieldClass158D00 with vtable D_157AF0 in main data. */
class FieldClass157AF0 : public FieldClass158D00
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157AF0()
    {
    }

    float unk28;
    s32 unk2C;
    float unk30;
    float unk34;
    float unk38;
    float unk3C;
    float unk40;
    float unk44;
    FieldLinkedObject157F00* unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    FieldLinkedObject157F00* unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    FieldVector4 unk60;
    FieldVector4 unk70;
    FieldVector4 unk80;
    FieldVector4 unk90;
    u8* unkA0;
    FieldResourceRecord273720* unkA4;
};

/** Partial FieldClass158C30 with vtable D_157E30 in main data. */
class FieldClass157E30 : public FieldClass158C30
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157E30()
    {
    }

    float unk28;
    s32 unk2C;
    float unk30;
    float unk34;
    float unk38;
    float unk3C;
    float unk40;
    float unk44;
    FieldLinkedObject157F00* unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    FieldLinkedObject157F00* unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    FieldVector4 unk60;
    FieldVector4 unk70;
    FieldVector4 unk80;
    FieldVector4 unk90;
    u8* unkA0;
    FieldResourceRecord273720* unkA4;
};

/** Partial FieldClass158B60 with vtable D_158170 in main data. */
class FieldClass158170 : public FieldClass158B60
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158170()
    {
    }

    float unk28;
    s32 unk2C;
    float unk30;
    float unk34;
    float unk38;
    float unk3C;
    float unk40;
    float unk44;
    FieldLinkedObject157F00* unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    FieldLinkedObject157F00* unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    FieldVector4 unk60;
    FieldVector4 unk70;
    FieldVector4 unk80;
    FieldVector4 unk90;
    u8* unkA0;
    FieldResourceRecord273720* unkA4;
};

/** Partial FieldClass158A90 with vtable D_158720 in main data. */
class FieldClass158720 : public FieldClass158A90
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158720()
    {
    }

    float unk28;
    s32 unk2C;
    float unk30;
    float unk34;
    float unk38;
    float unk3C;
    float unk40;
    float unk44;
    FieldLinkedObject157F00* unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    FieldLinkedObject157F00* unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    FieldVector4 unk60;
    FieldVector4 unk70;
    FieldVector4 unk80;
    FieldVector4 unk90;
    u8* unkA0;
    FieldResourceRecord273720* unkA4;
};

/** Partial FieldClass157E30 with vtable D_1577B0 in main data. */
class FieldClass1577B0 : public FieldClass157E30
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1577B0()
    {
    }
};

/** Partial FieldClass157AF0 with vtable D_157A20 in main data. */
class FieldClass157A20 : public FieldClass157AF0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157A20()
    {
    }
};

/** Partial FieldClass157E30 with vtable D_157D60 in main data. */
class FieldClass157D60 : public FieldClass157E30
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157D60()
    {
    }
};

/** Partial FieldClass158170 with vtable D_1580A0 in main data. */
class FieldClass1580A0 : public FieldClass158170
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1580A0()
    {
    }
};

/** Partial FieldClass158720 with vtable D_1583E0 in main data. */
class FieldClass1583E0 : public FieldClass158720
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1583E0()
    {
    }
};

/** Partial FieldClass158720 with vtable D_158650 in main data. */
class FieldClass158650 : public FieldClass158720
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158650()
    {
    }
};

/** Partial FieldClass1577B0 with vtable D_1576E0 in main data. */
class FieldClass1576E0 : public FieldClass1577B0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1576E0()
    {
    }
};

/** Partial FieldClass157A20 with vtable D_157950 in main data. */
class FieldClass157950 : public FieldClass157A20
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157950()
    {
    }
};

/** Partial FieldClass157D60 with vtable D_157C90 in main data. */
class FieldClass157C90 : public FieldClass157D60
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157C90()
    {
    }
};

/** Partial FieldClass1580A0 with vtable D_157FD0 in main data. */
class FieldClass157FD0 : public FieldClass1580A0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157FD0()
    {
    }
};

/** Partial FieldClass1583E0 with vtable D_158310 in main data. */
class FieldClass158310 : public FieldClass1583E0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158310()
    {
    }
};

/** Partial FieldClass158650 with vtable D_158580 in main data. */
class FieldClass158580 : public FieldClass158650
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158580()
    {
    }
};

/** Partial FieldClass1576E0 with vtable D_157610 in main data. */
class FieldClass157610 : public FieldClass1576E0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157610();
};

/** Partial FieldClass157950 with vtable D_157880 in main data. */
class FieldClass157880 : public FieldClass157950
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157880();
};

/**
 * Partial FieldClass158930 with vtable D_173F80 in main data (a Lib-region vtable; its destructor
 * slot points to the Lib copy at 0x441600).
 */
class FieldClass173F80 : public FieldClass158930
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass173F80()
    {
    }
};

/** Partial FieldClass173F80 with vtable D_157540 in main data. */
class FieldClass157540 : public FieldClass173F80
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157540();
};

/** Partial FieldClass157C90 with vtable D_157BC0 in main data. */
class FieldClass157BC0 : public FieldClass157C90
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157BC0();
};

/** Partial FieldClass157FD0 with vtable D_157F00 in main data. */
class FieldClass157F00 : public FieldClass157FD0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass157F00();
};

/** Partial FieldClass158310 with vtable D_158240 in main data. */
class FieldClass158240 : public FieldClass158310
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass158240();
};

/** Partial FieldClass158580 with vtable D_1584B0 in main data. */
class FieldClass1584B0 : public FieldClass158580
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1584B0();
};


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store the floating-point value at offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF30(FieldObject157BC0* object, float value);

/**
 * @brief Store the floating-point value at offset 0x30.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF40(FieldObject157BC0* object, float value);

/**
 * @brief Read the floating-point value at offset 0x30.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_0029EF50(FieldObject157BC0* object);

/**
 * @brief Store the byte state at offset 0x4D.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF60(FieldObject157BC0* object, u8 value);

/**
 * @brief Read the byte state at offset 0x4D.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_0029EF70(FieldObject157BC0* object);

/**
 * @brief Store the floating-point value at offset 0x34.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF80(FieldObject157BC0* object, float value);

/**
 * @brief Store the byte state at offset 0x56.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF90(FieldObject157BC0* object, u8 value);

/**
 * @brief Read the byte state at offset 0x56.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_0029EFA0(FieldObject157BC0* object);

/**
 * @brief Store the floating-point value at offset 0x44.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EFB0(FieldObject157BC0* object, float value);

/**
 * @brief Read the floating-point value at offset 0x44.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_0029EFC0(FieldObject157BC0* object);

/**
 * @brief Read the floating-point value at offset 0x28.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_0029EFD0(FieldObject157BC0* object);

/**
 * @brief Store the linked object at offset 0x48.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EFE0(FieldObject157BC0* object, FieldLinkedObject157BC0* value);

/**
 * @brief Read the linked object at offset 0x48.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157BC0* func_0029EFF0(FieldObject157BC0* object);

/**
 * @brief Store the byte state at offset 0x4F.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F000(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the byte state at offset 0x4E.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F010(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the linked object at offset 0x50.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F020(FieldObject157BC0* object, FieldLinkedObject157BC0* value);

/**
 * @brief Read the linked object at offset 0x50.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157BC0* func_0029F030(FieldObject157BC0* object);

/**
 * @brief Store the byte state at offset 0x55.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F040(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x3C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F050(FieldObject157BC0* object, float value);

/**
 * @brief Store the byte state at offset 0x54.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F060(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x40.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F070(FieldObject157BC0* object, float value);

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F0F0(FieldObject157BC0* object, float value);

/**
 * @brief Store the floating-point value at offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21A0(FieldObject157F00* object, float value);

/**
 * @brief Store the floating-point value at offset 0x30.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21B0(FieldObject157F00* object, float value);

/**
 * @brief Read the floating-point value at offset 0x30.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A21C0(FieldObject157F00* object);

/**
 * @brief Store the byte state at offset 0x4D.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21D0(FieldObject157F00* object, u8 value);

/**
 * @brief Read the byte state at offset 0x4D.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A21E0(FieldObject157F00* object);

/**
 * @brief Store the floating-point value at offset 0x34.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21F0(FieldObject157F00* object, float value);

/**
 * @brief Store the byte state at offset 0x56.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2200(FieldObject157F00* object, u8 value);

/**
 * @brief Read the byte state at offset 0x56.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A2210(FieldObject157F00* object);

/**
 * @brief Store the floating-point value at offset 0x44.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2220(FieldObject157F00* object, float value);

/**
 * @brief Read the floating-point value at offset 0x44.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A2230(FieldObject157F00* object);

/**
 * @brief Read the floating-point value at offset 0x28.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A2240(FieldObject157F00* object);

/**
 * @brief Store the linked object at offset 0x48.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2250(FieldObject157F00* object, FieldLinkedObject157F00* value);

/**
 * @brief Read the linked object at offset 0x48.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157F00* func_002A2260(FieldObject157F00* object);

/**
 * @brief Store the byte state at offset 0x4F.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2270(FieldObject157F00* object, u8 value);

/**
 * @brief Store the byte state at offset 0x4E.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2280(FieldObject157F00* object, u8 value);

/**
 * @brief Store the linked object at offset 0x50.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2290(FieldObject157F00* object, FieldLinkedObject157F00* value);

/**
 * @brief Read the linked object at offset 0x50.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157F00* func_002A22A0(FieldObject157F00* object);

/**
 * @brief Store the byte state at offset 0x55.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22B0(FieldObject157F00* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x3C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22C0(FieldObject157F00* object, float value);

/**
 * @brief Store the byte state at offset 0x54.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22D0(FieldObject157F00* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x40.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22E0(FieldObject157F00* object, float value);

/**
 * @brief Enable the default callback predicate for this receiver.
 * @param object Receiver to query.
 * @return Always true.
 */
bool func_0029E9E0(FieldObject157BC0* object);

/**
 * @brief Enable the default callback predicate for this receiver.
 * @param object Receiver to query.
 * @return Always true.
 */
bool func_002A1C50(FieldObject157F00* object);

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2360(FieldObject157F00* object, float value);

/**
 * @brief Report the default enabled callback state.
 * @param object Object being queried.
 * @return Always true.
 */
bool func_002A4EC0(FieldObject158240* object);

/**
 * @brief Store the floating-point value at offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5410(FieldObject158240* object, float value);

/**
 * @brief Store the floating-point value at offset 0x30.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5420(FieldObject158240* object, float value);

/**
 * @brief Read the floating-point value at offset 0x30.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A5430(FieldObject158240* object);

/**
 * @brief Store the byte state at offset 0x4D.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5440(FieldObject158240* object, u8 value);

/**
 * @brief Read the byte state at offset 0x4D.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A5450(FieldObject158240* object);

/**
 * @brief Store the floating-point value at offset 0x34.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5460(FieldObject158240* object, float value);

/**
 * @brief Store the byte state at offset 0x56.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5470(FieldObject158240* object, u8 value);

/**
 * @brief Read the byte state at offset 0x56.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A5480(FieldObject158240* object);

/**
 * @brief Store the floating-point value at offset 0x44.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5490(FieldObject158240* object, float value);

/**
 * @brief Read the floating-point value at offset 0x44.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A54A0(FieldObject158240* object);

/**
 * @brief Read the floating-point value at offset 0x28.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A54B0(FieldObject158240* object);

/**
 * @brief Store the byte state at offset 0x4F.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A54E0(FieldObject158240* object, u8 value);

/**
 * @brief Store the byte state at offset 0x4E.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A54F0(FieldObject158240* object, u8 value);

/**
 * @brief Store the byte state at offset 0x55.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5520(FieldObject158240* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x3C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5530(FieldObject158240* object, float value);

/**
 * @brief Store the byte state at offset 0x54.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5540(FieldObject158240* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x40.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5550(FieldObject158240* object, float value);

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A55D0(FieldObject158240* object, float value);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset154E80* func_002A5660(FieldClass158DD0* object);

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5670(FieldClass158DD0* object);

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5680(FieldClass158DD0* object);

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5690(FieldClass158DD0* object);

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A56A0(FieldClass158DD0* object);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset154E80* func_002A5750(FieldClass158D00* object);

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5760(FieldClass158D00* object);

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5770(FieldClass158D00* object);

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5780(FieldClass158D00* object);

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5790(FieldClass158D00* object);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset154E80* func_002A5840(FieldClass158C30* object);

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5850(FieldClass158C30* object);

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5860(FieldClass158C30* object);

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5870(FieldClass158C30* object);

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5880(FieldClass158C30* object);

/**
 * @brief Get an indexed primary array element.
 * @param object Object to query.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldClass158A58* func_002A58F0(FieldClass158B60* object, s32 index);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002A5930(FieldClass158B60* object);

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5940(FieldClass158B60* object);

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5950(FieldClass158B60* object);

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5960(FieldClass158B60* object);

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5970(FieldClass158B60* object);

/**
 * @brief Get an indexed primary array element.
 * @param object Object to query.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldClass158A78* func_002A59E0(FieldClass158A90* object, s32 index);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002A5A20(FieldClass158A90* object);

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5A30(FieldClass158A90* object);

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5A40(FieldClass158A90* object);

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5A50(FieldClass158A90* object);

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5A60(FieldClass158A90* object);

/**
 * @brief Report the default enabled callback state.
 * @param object Object to query.
 * @return Always true.
 */
bool func_002AD9D0(FieldObject158860* object);

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldClass1589F8* func_002A5620(FieldClass158DD0* object, s32 index);

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5640(FieldClass158DD0* object, s32 row, s32 column);

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldClass158A18* func_002A5710(FieldClass158D00* object, s32 index);

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5730(FieldClass158D00* object, s32 row, s32 column);

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldClass158A38* func_002A5800(FieldClass158C30* object, s32 index);

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5820(FieldClass158C30* object, s32 row, s32 column);

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5910(FieldClass158B60* object, s32 row, s32 column);

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5A00(FieldClass158A90* object, s32 row, s32 column);

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_0029F080(FieldObject157BC0* object, u8* header, FieldResourceRecord273720* records);

/**
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_0029F140(FieldObject157BC0* object, const FieldVectorSource150* source);

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_002A22F0(FieldObject157F00* object, u8* header, FieldResourceRecord273720* records);

/**
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_002A23B0(FieldObject157F00* object, const FieldVectorSource150* source);

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_002A5560(FieldObject158240* object, u8* header, FieldResourceRecord273720* records);

/**
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_002AD830(FieldObject158860* object, const FieldVectorSource150* source);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029F100(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0029F110(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029F120(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0029F130(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029F170(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A2370(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A2380(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A2390(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A23A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A23E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A55E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A55F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A5600(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A5610(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002AD9C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002AE9A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002AE9B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002AE9C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002AE9D0(void* object);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002A5A70(FieldClass158A90* object, s32 rows, s32 columns);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002A6170(FieldClass158B60* object, s32 rows, s32 columns);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002A6910(FieldClass158C30* object, s32 rows, s32 columns);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002A70D0(FieldClass158D00* object, s32 rows, s32 columns);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_002A78C0(FieldClass158DD0* object, s32 rows, s32 columns);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002AD860(FieldClass158A90* object, const FieldClass158A90* other);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002AD8A0(FieldClass158B60* object, const FieldClass158B60* other);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002AD8E0(FieldClass158C30* object, const FieldClass158C30* other);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_002AD920(FieldClass158D00* object, const FieldClass158D00* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_002A8000(FieldClass158720* object, const FieldClass158720* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_002A87F0(FieldClass158170* object, const FieldClass158170* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_002A8FE0(FieldClass157E30* object, const FieldClass157E30* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_002A9810(FieldClass157AF0* object, const FieldClass157AF0* other);

/**
 * @brief Copy another grid's size and settings, reallocating this grid to match.
 * @param object Grid to update.
 * @param other Grid to copy.
 */
void func_002AD760(FieldClass158860* object, const FieldClass158860* other);

/**
 * @brief Fill a row of secondary elements from a cell (or an explicit vector).
 * @param object Grid owning the row.
 * @param cell Cell whose vectors are copied.
 * @param row First secondary element of the row.
 * @param index Unused.
 * @param source Vector copied to each element, or null to use the cell's.
 */
void func_0029EE30(FieldClass157E30* object, FieldClass158A38* cell, FieldClass154E60* row, s32 index, const FieldVector4* source);

/**
 * @brief Fill a row of secondary elements from a cell (or an explicit vector).
 * @param object Grid owning the row.
 * @param cell Cell whose vectors are copied.
 * @param row First secondary element of the row.
 * @param index Unused.
 * @param source Vector copied to each element, or null to use the cell's.
 */
void func_002A20A0(FieldClass158170* object, FieldClass158A58* cell, FieldClass154E60* row, s32 index, const FieldVector4* source);

/**
 * @brief Fill a row of secondary elements from a cell (or an explicit vector).
 * @param object Grid owning the row.
 * @param cell Cell whose vectors are copied.
 * @param row First secondary element of the row.
 * @param index Unused.
 * @param source Vector copied to each element, or null to use the cell's.
 */
void func_002A5310(FieldClass158720* object, FieldClass158A78* cell, FieldClass154E60* row, s32 index, const FieldVector4* source);

/**
 * @brief Fill a row of secondary elements from a cell (or an explicit vector).
 * @param object Grid owning the row.
 * @param cell Cell whose vectors are copied.
 * @param row First secondary element of the row.
 * @param index Unused.
 * @param source Vector copied to each element, or null to use the cell's.
 */
void func_002ADDF0(FieldClass158860* object, FieldClass1589F8* cell, FieldClass154E60* row, s32 index, const FieldVector4* source);

#ifdef __cplusplus
}
#endif
#endif
