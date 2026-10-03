#ifndef SO3_OVERLAYS_1067_00_TEXT_001E6C50_H
#define SO3_OVERLAYS_1067_00_TEXT_001E6C50_H

#include "types.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/1067-00/text_0023DC90.h"
#include "boot/resident_0011EE70.h"
#include "overlays/0002-01/text_004BD360.h"

/** Partial receiver with three aligned 128-bit slots and a ready byte at offset 0x50. */
typedef struct FieldVectorSlots50
{
    u8 unk00[0x20];
    unsigned __int128 slots[3];
    u8 ready;
} FieldVectorSlots50;

/** Partial receiver with three words at offsets 0x10-0x18 and flag bit 1 at offset 0x66. */
typedef struct FieldStateReset66
{
    u8 unk00[0x10];
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u8 unk1c[0x4A];
    u8 unk66_0 : 1;
    u8 unk66_1 : 1;
    u8 unk66_2_7 : 6;
} FieldStateReset66;

/** Partial circular-list node keyed by the word at offset 0x54. */
typedef struct FieldKeyedListNode54
{
    u8 unk00[8];
    struct FieldKeyedListNode54* next;
    u8 unk0c[0x48];
    u32 unk54;
} FieldKeyedListNode54;

/** Partial receiver with a signed halfword at offset 0x3A. */
typedef struct FieldHalfword3A
{
    u8 unk00[0x3A];
    s16 unk3a;
} FieldHalfword3A;

/** Partial record with a leading pointer, flag byte at offset 0xA and signed halfword at offset 0xE. */
typedef struct FieldPackedRecord0E
{
    void* unk00;
    u8 unk04[6];
    u8 unk0a;
    u8 unk0b[3];
    s16 unk0e;
} FieldPackedRecord0E;

/** Partial object receiving a byte flag at offset 0x3C and a signed count at offset 0xFC. */
typedef struct FieldCountTarget
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[0xBF];
    s32 unkfc;
} FieldCountTarget;

/** Partial receiver holding an optional FieldCountTarget at offset 0x34. */
typedef struct FieldCountOwner34
{
    u8 unk00[0x34];
    FieldCountTarget* unk34;
} FieldCountOwner34;

/** Partial receiver with pointers at offsets 0x80 and 0x448 and a disabling bit 5 at offset 0x8C. */
typedef struct FieldGatedObject448
{
    u8 unk00[0x80];
    void* unk80;
    u8 unk84[8];
    u8 unk8c_0_4 : 5;
    u8 unk8c_5 : 1;
    u8 unk8c_6_7 : 2;
    u8 unk8d[0x3BB];
    void* unk448;
} FieldGatedObject448;

/** Partial receiver with an entry array pointer at offset 4 and entry state at offsets 0x30-0x43. */
typedef struct FieldEntryArrayObject30
{
    u8 unk00[4];
    FieldArrayEntry10* unk04;
    u8 unk08[0x28];
    u32 unk30;
    u8 unk34[4];
    s16 unk38;
    s16 unk3a;
    s16 unk3c;
    s16 unk3e;
    s16 unk40;
    u8 unk42_0_3 : 4;
    u8 unk42_4_7 : 4;
    u8 unk43_0 : 1;
    u8 unk43_1 : 1;
    u8 unk43_2_7 : 6;
} FieldEntryArrayObject30;

#ifdef __cplusplus
/** 16-byte aligned 4x4 float matrix stored as four rows; column 3 of the first three rows holds the translation. */
struct FieldMatrix44
{
    float m[4][4];
} __attribute__((aligned(16)));

/** Partial source record for FieldClass150220: three floats followed by a vector at offset 0x10. */
struct FieldRecord150220
{
    float unk00;
    float unk04;
    float unk08;
    u8 unk0c[4];
    FieldVec4A unk10;
};

/**
 * Partial class derived from FieldClass150070, with vtable D_150220 in boot
 * data. Holds a source record pointer at offset 0x18 and a done flag at bit 0
 * of offset 0x20; slot 8 is pure virtual.
 */
class FieldClass150220 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150220()
    {
    }

    /**
     * @brief Store the source record pointer at offset 0x18.
     * @param source Record to store.
     */
    virtual void func_001E6CF0(FieldRecord150220* source);

    /**
     * @brief Set flag bit 0 at offset 0x20.
     * @param matrix 4x4 matrix used by the overrides; ignored here.
     */
    virtual void func_001E73D0(const FieldMatrix44* matrix);

    /** @brief Clear flag bit 0 at offset 0x20. */
    virtual void func_001E6D00();

    /**
     * @brief Build the object's state from a source record and an optional matrix.
     * @param source Source record, stored at offset 0x18.
     * @param matrix Optional 4x4 matrix.
     * @param scale Scale factor; ignored by FieldClass150250.
     */
    virtual void func_001E6D80(FieldRecord150220* source, const FieldMatrix44* matrix, float scale) = 0;

    u8 unk14[4];
    FieldRecord150220* unk18;
    u8 unk1c[4];
    u8 unk20_0 : 1;
    u8 unk20_1_7 : 7;
};

/** Partial class derived from FieldClass150220, with vtable D_1501F0 in boot data. */
class FieldClass1501F0 : public FieldClass150220
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1501F0();

    /**
     * @brief Unless flag bit 0 at offset 0x20 is set, pass the matrix and transform the vector at offset 0x1C0 into 0x1D0 with func_00433730, then set the flag.
     * @param matrix 4x4 matrix.
     */
    virtual void func_001E73D0(const FieldMatrix44* matrix);

    /**
     * @brief Store the scaled source radius at offset 0x1E0 and, with a matrix, build a pole and three rings
     * of eight points at offset 0x30 on a dome of that radius; set the vector at offset 0x1C0 from the
     * matrix translation (or from the source centre without one) plus the source centre.
     * @param source Source record, stored at offset 0x18; its first float is the radius.
     * @param matrix Optional 4x4 matrix.
     * @param scale Scale applied to the radius stored at offset 0x1E0.
     */
    virtual void func_001E6D80(FieldRecord150220* source, const FieldMatrix44* matrix, float scale);

    u8 unk24[0x19C];
    FieldVec4A unk1c0;
    FieldVec4A unk1d0;
    float unk1e0;
};

/**
 * Partial class derived from FieldClass150220, with vtable D_150250 in boot
 * data. Holds eight corner vectors at offset 0x30, their transformed copies at
 * 0xB0, six vectors at 0x130 built from them, and a centre vector at 0x190
 * with its transformed copy at 0x1A0.
 */
class FieldClass150250 : public FieldClass150220
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150250();

    /**
     * @brief Unless flag bit 0 at offset 0x20 is set, transform the eight vectors at offset 0x30 and the vector at offset 0x190 by the matrix, then set the flag.
     * @param matrix 4x4 matrix.
     */
    virtual void func_001E73D0(const FieldMatrix44* matrix);

    /** @brief Clear flag bit 0 at offset 0x20 and the w component of each vector at offset 0x130. */
    virtual void func_001E6D00();

    /**
     * @brief Return the vector of one face, building it from three transformed corners when its w is zero.
     * @param face Face index, 0 to 5.
     * @return The face's vector at offset 0x130.
     */
    FieldVec4A* func_001E6FC0(s32 face);

    /**
     * @brief Build the eight corner vectors at offset 0x30 from a source record, optionally transformed by a matrix.
     * @param source Source record, stored at offset 0x18.
     * @param matrix Optional 4x4 matrix.
     * @param scale Unused by this class.
     */
    virtual void func_001E6D80(FieldRecord150220* source, const FieldMatrix44* matrix, float scale);

    u8 unk24[0xC];
    FieldVec4A unk30[8];
    FieldVec4A unkb0[8];
    FieldVec4A unk130[6];
    FieldVec4A unk190;
    FieldVec4A unk1a0;
};

/**
 * Partial class with its vtable pointer at offset 0xC, after its data, with
 * vtable D_150320 in boot data. It owns an array of 12-byte entries at offset 4
 * with the count at offset 8.
 */
class FieldClass150320
{
public:
    LibClass178220* unk00;
    void* unk04;
    s32 unk08;

    /** @brief Release the entries, then destroy the object. */
    virtual ~FieldClass150320();

    /** @brief Release each entry's object through the manager at offset 0, then delete the entry array. */
    void func_001E9050();
};

class FieldClass150EB0;

/**
 * Partial 0x70-byte keyed animation node derived from FieldClass150070, with
 * vtable D_150280 in boot data. FieldClass1502E0 keeps a list of them; the
 * node owns two Lib objects and refers back to its FieldClass150EB0 owner.
 */
class FieldClass150280 : public FieldClass150070
{
public:
    /** @brief Construct a node with no key (-1) and mode 2. */
    FieldClass150280();

    /** @brief Release the Lib objects of a loaded node, then destroy it. */
    virtual ~FieldClass150280();

    /**
     * @brief Advance the node's animation by a time step and return its current vector.
     * @param arg Pointer argument passed through by FieldClass1502E0::func_001E81D0; not used here.
     * @param flag8 Flag bit 8 of the list's halfword at offset 0xB4.
     * @param flag9 Flag bit 9 of the list's halfword at offset 0xB4.
     * @param step Time step.
     * @return The node's vector.
     */
    FieldVec4A func_001E78B0(void* arg, bool flag8, bool flag9, float step);

    LibClass178220* unk14;
    LibClass178370* unk18;
    FieldClass150EB0* unk1c;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    float unk2c;
    float unk30;
    float unk34;
    u8 unk38[8];
    FieldVec4A unk40;
    u32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5c;
    float unk60;
    u16 unk64;
    u8 unk66_0 : 1;
    u8 unk66_1 : 1;
    u8 unk66_2 : 1;
    u8 unk66_3 : 1;
    u8 unk66_4 : 1;
    u8 unk66_5 : 1;
    u8 unk66_6 : 1;
    u8 unk66_7 : 1;
    u8 unk67[9];
};

/**
 * Partial Lib list class derived from FieldClass1502A0, with vtable D_1502E0 in
 * boot data. Owns two FieldClass150070 objects at offset 0x80 and a
 * FieldClass150320 at offset 0x90.
 */
class FieldClass1502E0 : public FieldClass1502A0
{
public:
    /** @brief Construct the list and set the parameter block at offsets 0x7C-0xBC to its defaults. */
    FieldClass1502E0();

    /** @brief Delete the owned objects and every listed object, then destroy the list. */
    virtual ~FieldClass1502E0();

    /**
     * @brief Store the key and float parameters, the fixed value 300.0f, the low flag bits at offset 0xB4 and mode 2.
     * @param key Word stored at offset 0x98.
     * @param flags Value merged into the low byte of the halfword at offset 0xB4, preserving its high byte.
     * @param a Float stored at offset 0x9C.
     * @param b Float stored at offset 0xA0.
     * @param c Float stored at offset 0xA8.
     * @param d Float stored at offset 0xB0.
     * @param e Float stored at offset 0xA4.
     */
    void func_001E8E00(u32 key, u16 flags, float a, float b, float c, float d, float e);

    /**
     * @brief Load the 'ANIM' resource for a key into a new list node, unless a node with that key exists.
     * @param key Resource key, stored in the node at offset 0x54.
     * @return 1 when a node was added, otherwise 0.
     */
    s32 func_001E82B0(s32 key);

    /**
     * @brief Advance the selected node and return its vector, or (0, 0, 0, 1) when none applies.
     * @param arg Pointer argument passed through to FieldClass150280::func_001E78B0.
     * @param step Time step.
     * @return The selected node's vector.
     */
    FieldVec4B func_001E81D0(void* arg, float step);

    /**
     * @brief Find the listed node with a key.
     * @param key Key compared with each node's word at offset 0x54.
     * @return The first matching node, or null when none matches.
     */
    FieldClass150280* find(s32 key)
    {
        FieldClass150060* list = (FieldClass150060*)unk00;
        FieldClass150060* node = list;
        for (;;)
        {
            node = node->unk08;
            if (list == node)
            {
                break;
            }
            if (key == static_cast<FieldClass150280*>(node)->unk54)
            {
                return static_cast<FieldClass150280*>(node);
            }
        }
        return 0;
    }

    FieldClass150EB0* unk78;
    FieldClass150280* unk7c;
    FieldClass150070* unk80[2];
    u32 unk88;
    u32 unk8c;
    FieldClass150320* unk90;
    s32 unk94;
    u32 unk98;
    float unk9c;
    float unka0;
    float unka4;
    float unka8;
    float unkac;
    float unkb0;
    u16 unkb4;
    u8 unkb6;
    u8 unkb7;
    s32 unkb8;
    u8 unkbc_0 : 1;
    u8 unkbc_1_7 : 7;
};

/**
 * 32-byte shape record. The first 16 bytes are read as a FieldVec4B of half
 * extents, so the flag byte at offset 0xC overlaps its fourth component.
 */
struct FieldShapeRecord20
{
    float unk00;
    float unk04;
    float unk08;
    u8 unk0c_0_3 : 4;
    u8 unk0c_4 : 1;
    u8 unk0c_5 : 1;
    u8 unk0c_6_7 : 2;
    u8 unk0d[3];
    FieldVec4A unk10;
};

/** Partial owner of FieldClass150330 shapes: an object at offset 4, an index at 0xC and a vector at 0x10. */
struct FieldShapeOwner18
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[4];
    s16 unk0c;
    u8 unk0e[2];
    FieldVec4A unk10;
};

/** Two vertex indices of one line segment. */
struct FieldIndexPair
{
    /** @brief Leave the indices uninitialized. */
    FieldIndexPair();

    /**
     * @brief Set both indices.
     * @param from First vertex index.
     * @param to Second vertex index.
     */
    FieldIndexPair(s16 from, s16 to)
    {
        unk00 = from;
        unk02 = to;
    }

    s16 unk00;
    s16 unk02;
};

/** Partial class derived from FieldClass150070, with vtable D_150330 in boot data. */
class FieldClass150330 : public FieldClass150070
{
public:
    /** @brief Clear the words, array pointers and halfwords, and set flag bit 1 at offset 0x3C. */
    FieldClass150330();

    /** @brief Delete the three arrays at offsets 0x24-0x2C, then destroy the object. */
    virtual ~FieldClass150330();

    /** @brief Detach the object and queue it on the resident object queue. */
    virtual void func_001DD7B0();

    /**
     * @brief Append one line segment between two vertices to a packet.
     * @param packet Packet to append to.
     * @param from First vertex.
     * @param to Second vertex.
     * @param color Packed colour, alpha in the top byte.
     */
    void func_001E9690(ResidentPacket* packet, const FieldVec4B* from, const FieldVec4B* to, u32 color);

    /**
     * @brief Set up the shape from its owner and record, build its vertices, and move them to the record's centre.
     * @param owner Owner stored at offset 0x18; its object at offset 4 is stored at offset 0x20.
     * @param record Shape record stored at offset 0x1C; its low four flag bits select the shape.
     * @param color Packed colour stored at offset 0x14.
     * @param flag Stored in flag bit 2 at offset 0x3C; enlarges the shape by 5%.
     */
    void func_001EA2E0(FieldShapeOwner18* owner, FieldShapeRecord20* record, u32 color, s32 flag);

    /**
     * @brief Allocate and build the eight vertices and twelve edges of the box between two corners.
     * @param low Lower corner.
     * @param high Upper corner.
     */
    void func_001E9B80(const FieldVec4B* low, const FieldVec4B* high);

    /**
     * @brief Build the vertices and segments of a round shape.
     * @param radius Shape radius.
     */
    void func_001E9EA0(float radius);

    u32 unk14;
    FieldShapeOwner18* unk18;
    FieldShapeRecord20* unk1c;
    void* unk20;
    FieldVec4B* unk24;
    FieldVec4B* unk28;
    FieldIndexPair* unk2c;
    float unk30;
    u8 unk34[4];
    s16 unk38;
    s16 unk3a;
    u8 unk3c_0 : 1;
    u8 unk3c_1 : 1;
    u8 unk3c_2 : 1;
    s8 unk3c_3_5 : 3;
    u8 unk3c_6_7 : 2;
};

/**
 * Partial class derived from FieldClass150070, with vtable D_150440 in boot
 * data. Its storage is released through the Lib heap.
 */
class FieldClass150440 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150440()
    {
    }

    /**
     * @brief Release the object's storage through the Lib heap.
     * @param object Storage to release.
     */
    static void operator delete(void* object)
    {
        func_004DB570(object);
    }
};

/** Partial class derived from FieldClass150440, with vtable D_150420 in boot data. */
class FieldClass150420 : public FieldClass150440
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150420();
};

/**
 * Partial 0x50-byte class derived from FieldClass150070, with vtable D_1504F0
 * in boot data. At most one exists at a time, in D_001B6428.
 */
class FieldClass1504F0 : public FieldClass150070
{
public:
    /** @brief Construct the object with its state cleared. */
    FieldClass1504F0();

    /**
     * @brief Release the Lib slot at offset 0x3C and the object at offset 0x40, reset the target's
     * state flags (resetting its scale first unless flag bit 0 or 1 is set), then destroy the object.
     */
    virtual ~FieldClass1504F0();

    FieldObject24B6B0* unk14;
    void* unk18;
    u8 unk1c[0x20];
    s32 unk3c;
    FieldClass150070* unk40;
    u8 unk44[8];
    u8 unk4c;
    u8 unk4d_0 : 1;
    u8 unk4d_1 : 1;
    u8 unk4d_2 : 1;
    u8 unk4d_3_7 : 5;
    u8 unk4e[2];
};

/** The current FieldClass1504F0, or null. */
extern "C" FieldClass1504F0* D_001B6428;

/** Partial class derived from FieldClass150070, with vtable D_150460 in boot data. */
class FieldClass150460 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150460()
    {
    }
};

/** Partial class derived from FieldClass150460, with vtable D_150490 in boot data. */
class FieldClass150490 : public FieldClass150460
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150490()
    {
    }

    /**
     * @brief Add the object's GS register writes to a packet; this class adds none.
     * @param packet Packet to append to.
     */
    virtual void func_001EAC90(ResidentPacket* packet)
    {
    }
};

/**
 * Partial class derived from FieldClass150490, with vtable D_1504C0 in boot
 * data. Owns a list of FieldClass150070 objects at offset 0x38.
 */
class FieldClass1504C0 : public FieldClass150490
{
public:
    /** @brief Detach and delete every object in the list at offset 0x38, then destroy the object. */
    virtual ~FieldClass1504C0();

    /** @brief Detach the object and queue it on the resident object queue. */
    virtual void func_001DD7B0();

    /** @brief Advance the counter at offset 0xC0, then call func_001EA730 when the pointer at offset 0x30 and flag bit 1 at offset 0xC4 are set. */
    virtual void func_001DF360();

    /** @brief Update the object; func_001DF360 calls it after advancing the counter when the gating flags are set. */
    void func_001EA730();

    /**
     * @brief When the pointer at offset 0x30 and flag bit 1 at offset 0xC4 are set, set the packet's byte at
     * offset 0x15 and wrap func_001EAA10's output in GS register writes.
     * @param packet Packet to append to.
     */
    virtual void func_001EAC90(ResidentPacket* packet);

    /**
     * @brief Append the object's own GS data to a packet.
     * @param packet Packet to append to.
     */
    void func_001EAA10(ResidentPacket* packet);

    u8 unk14[0x1C];
    void* unk30;
    u8 unk34[4];
    LibClass178DD0 unk38;
    u8 unkb0[0x10];
    s32 unkc0;
    u8 unkc4_0 : 1;
    u8 unkc4_1 : 1;
    u8 unkc4_2 : 1;
    u8 unkc4_3 : 1;
    u8 unkc4_4 : 1;
    u8 unkc4_5_7 : 3;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mark the receiver ready and copy a 128-bit value into slot 0.
 * @param object Receiver containing the slots.
 * @param value Value to copy.
 */
void func_001E7E90(FieldVectorSlots50* object, const unsigned __int128* value);

/**
 * @brief Mark the receiver ready and copy a 128-bit value into slot 2.
 * @param object Receiver containing the slots.
 * @param value Value to copy.
 */
void func_001E7EB0(FieldVectorSlots50* object, const unsigned __int128* value);

/**
 * @brief Mark the receiver ready and copy a 128-bit value into slot 1.
 * @param object Receiver containing the slots.
 * @param value Value to copy.
 */
void func_001E7ED0(FieldVectorSlots50* object, const unsigned __int128* value);

/**
 * @brief Clear the words at offsets 0x10-0x18 and flag bit 1 at offset 0x66.
 * @param object Receiver to reset.
 */
void func_001E7560(FieldStateReset66* object);

/**
 * @brief Find a node whose word at offset 0x54 matches the key, stopping on return to the list head.
 * @param list Head of a circular list; its links are assumed nonnull.
 * @param key Value compared with the word at offset 0x54.
 * @return The first matching node, or null if none matches.
 */
FieldKeyedListNode54* func_001E8490(FieldKeyedListNode54* list, u32 key);

/**
 * @brief Read the signed halfword at offset 0x3A.
 * @param object Receiver to inspect.
 * @return The stored halfword.
 */
s16 func_001E9380(const FieldHalfword3A* object);

/**
 * @brief Test bit 5 of the flag byte at offset 0xA.
 * @param record Record to inspect.
 * @return 1 when the bit is set, otherwise 0.
 */
s32 func_001EB2C0(const FieldPackedRecord0E* record);

/**
 * @brief Read the leading pointer.
 * @param record Record to inspect.
 * @return The stored pointer.
 */
void* func_001EB2D0(const FieldPackedRecord0E* record);

/**
 * @brief Read the signed halfword at offset 0xE.
 * @param record Record to inspect.
 * @return The stored halfword.
 */
s16 func_001EB2E0(const FieldPackedRecord0E* record);

/**
 * @brief Store a count and set the byte flag in the optional target at offset 0x34.
 * @param object Receiver holding the target.
 * @param count Signed count stored at the target's offset 0xFC.
 */
void func_001EB690(FieldCountOwner34* object, s32 count);

/**
 * @brief Test that both pointers at offsets 0x80 and 0x448 are set and bit 5 at offset 0x8C is clear.
 * @param object Receiver to inspect.
 * @return 1 when all conditions hold, otherwise 0.
 */
s32 func_001ECF10(const FieldGatedObject448* object);

/**
 * @brief Clear the entry array pointer, counters and flags, and set both nibbles and the three halfword indices to their initial values.
 * @param object Receiver to reset.
 */
void func_001E94F0(FieldEntryArrayObject30* object);

/**
 * @brief Create the FieldClass1504F0 instance and insert it into D_001B6614.
 *
 * When flag is set and bit 3 of the field context byte at offset 0xDE is clear,
 * the bit is written clear and nothing is created. Nothing is created while an
 * instance exists.
 * @param flag Stored in flag bit 2 at offset 0x4D of the new object.
 * @return 1 when an object was created and inserted, otherwise 0.
 */
s32 func_001E95B0(s32 flag);

#ifdef __cplusplus
}
#endif

#endif
