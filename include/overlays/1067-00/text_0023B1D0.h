#ifndef SO3_OVERLAYS_1067_00_TEXT_0023B1D0_H
#define SO3_OVERLAYS_1067_00_TEXT_0023B1D0_H

#include "types.h"

#ifdef __cplusplus
#include "overlays/lib/text_004BD360.h"
#endif

typedef struct FieldObject23CE80 FieldObject23CE80;
typedef struct FieldObject23CEB0 FieldObject23CEB0;
typedef struct FieldObject23CEA0 FieldObject23CEA0;
typedef FieldObject23CEA0 FieldObject23CB30;
typedef struct FieldObject23BAB0 FieldObject23BAB0;
typedef struct FieldState23B3A0 FieldState23B3A0;
typedef struct FieldObject153270 FieldObject153270;
typedef struct FieldNode23D310 FieldNode23D310;
typedef struct FieldObject23D310 FieldObject23D310;
typedef struct FieldObject23D020 FieldObject23D020;
typedef struct FieldObject23B950 FieldObject23B950;
typedef struct FieldObject23B850 FieldObject23B850;
typedef struct FieldTarget23B850 FieldTarget23B850;
typedef struct FieldObject23C180 FieldObject23C180;
typedef struct FieldObject23B1D0 FieldObject23B1D0;
typedef struct FieldObject23B280 FieldObject23B280;
typedef struct FieldObject23BE00 FieldObject23BE00;

/** Partial selector state containing its control byte and current index. */
struct FieldState23B3A0
{
    u8 unk00[0x75];
    u8 unk75;
    u8 unk76[0x1A];
    u16 unk90;
};

/** Partial storage for the field target display receiver. */
struct FieldObject23B950
{
    void** table;
    u8 unk04[0x24];
    u32 unk28;
    u8 unk2C[0xC];
    u8 state;
    u8 unk39[3];
    u8 flag3C;
    u8 unk3D[2];
    u8 flag3F;
    u32 unk40;
    u8 unk44[0x14];
    void* target;
    u8 unk5C;
};

/** Partial field grid storage used by the position operations. */
struct FieldObject23CE80
{
    u8 unk00[0xAE];
    u8 unkAE;
    u8 unkAF[0x31];
    float unkE0;
    u8 unkE4[0xC];
    u8 width;
    u8 height;
    u8 unkF2[0xA];
    float unkFC;
    float unk100;
    u8 unk104[8];
    s16 count;
};

/** Partial field grid storage used by the position operations. */
struct FieldObject23CEB0
{
    u8 unk00[0xAE];
    u8 unkAE;
    u8 unkAF[0x11];
    float unkC0;
    float unkC4;
    u8 unkC8[0x1D];
    u8 unkE5;
    u8 unkE6[0xA];
    u8 width;
    u8 height;
    u8 unkF2;
    u8 unkF3;
    float unkF4;
    float unkF8;
    float unkFC;
    float unk100;
    float unk104;
    float unk108;
    u8 unk10C[4];
    s16 unk110;
    s16 count;
    s16 unk114;
    s16 unk116;
    u8 unk118;
    u8 unk119;
};

#ifdef __cplusplus
/** Field storage and bounds interface with its virtual pointer at 0x38. */
class FieldClass151C50
{
public:
    LibStorageBlock0C unk00;
    u8 unk0c[4];
    float unk10;
    float unk14;
    float unk18;
    float unk1c;
    float unk20;
    float unk24;
    u8 unk28[8];
    float unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36[2];
    /** @brief Destroy the owned field storage. */
    virtual ~FieldClass151C50();
    /** @brief Run the default field bounds hook. */
    virtual void func_00212450();
};

/** Field-context transform with secondary field storage, using table 0x175070. */
class FieldClass175070 : public LibClass174610, public FieldClass151C50
{
public:
    /** @brief Destroy the field storage and transform bases. */
    virtual ~FieldClass175070();
    /** @brief Prepare the field transform after notification. @param value Notification word. */
    virtual void func_003F4410(u32 value);
};

/** Partial field grid interface using MAIN table 0x153290. */
struct FieldObject23CEA0 : public FieldClass175070
{
    /** @brief Initialize the grid and its field transform bases. */
    FieldObject23CEA0();
    /**
     * @brief Store the grid dimensions.
     * @param width Column count.
     * @param height Row count.
     */
    void func_0023CE80(u8 width, u8 height);
    /**
     * @brief Store the grid spacing.
     * @param x Horizontal spacing.
     * @param y Vertical spacing.
     */
    void func_0023CE60(float x, float y);
    /**
     * @brief Position a grid entry.
     * @param value Entry index.
     * @param x Horizontal displacement.
     * @param y Vertical displacement.
     * @return Always one.
     */
    s32 func_0023CF50(s16 value, float x, float y);
    /**
     * @brief Dispatch a direction to the grid selection handler.
     * @param direction Signed direction code.
     * @return Selection handler result.
     */
    virtual s16 func_0023CDB0(s16 direction);
    u8 width;
    u8 unkF1;
    u8 unkF2;
    u8 unkF3[0x1D];
    s16 row_count;
    s16 index;
    s16 unk114;
    u8 unk116[3];
    u8 unk119;
    u8 unk11a[0x16];
};
#else
/** Partial field grid flag and selection storage. */
struct FieldObject23CEA0
{
    u8 unk00[0xAD];
    u8 unkAD;
    u8 unkAE;
    u8 unkAF[0x11];
    float unkC0;
    float unkC4;
    u8 unkC8[0x18];
    float unkE0;
    u8 unkE4;
    u8 unkE5;
    u8 unkE6[0xA];
    u8 width;
    u8 unkF1[0x1F];
    s16 row_count;
    s16 index;
    s16 unk114;
};
#endif


/** Linked nodes used by the field coordinate selector. */
struct FieldObject23D310
{
    FieldNode23D310* first;
};

/** Coordinate selection state and its currently selected node index. */
struct FieldObject23B1D0
{
    u8 unk00[0x3C];
    u8 flag3C;
    u8 unk3D[3];
    u8 point40[0x10];
    float x;
    float y;
    u8 unk58[0x1D];
    u8 flag75;
    u8 unk76[6];
    FieldObject23D310 nodes;
    u8 unk80[8];
    s32 selected;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Select a node and either copy or apply its coordinates.
 * @param object Receiver with the node list.
 * @param index Number of links to follow and value stored on success.
 * @param direct Copy coordinates directly when nonzero; otherwise apply them through the field helper.
 * @return One when a node is found, otherwise zero.
 */
s32 func_0023B1D0(FieldObject23B1D0* object, s32 index, s32 direct);

/**
 * @brief Set the unsigned count and update position from the receiver's grid values.
 * @param object Receiver to update.
 * @param count Count stored at offset 0x90.
 */
void func_0023B280(FieldObject23B280* object, u16 count);

/**
 * @brief Clear the unsigned count and update position from the receiver's grid values.
 * @param object Receiver to update.
 */
void func_0023B310(FieldObject23B280* object);

/**
 * @brief Refresh the display receiver's position from its target.
 * @param object Display receiver to update.
 */
void func_0023B780(FieldObject23B950* object);

/**
 * @brief Store a target and refresh the display receiver's position.
 * @param object Display receiver to update.
 * @param target Target supplying the position, or null.
 */
void func_0023B7E0(FieldObject23B950* object, FieldTarget23B850* target);

/**
 * @brief Set a target and pass its position to the field helper.
 * @param object Receiver that stores the target.
 * @param target Target with the position to pass, or null for zero values.
 * @param color Packed color passed to the final helper.
 */
void func_0023B850(FieldObject23B850* object, FieldTarget23B850* target, u32 color);

/**
 * @brief Set the display target, stored float values, and packed color.
 * @param object Display receiver to update.
 * @param target Grid target, or null to allocate one.
 * @param color Packed color passed to the field helper.
 * @param first First float stored in the receiver.
 * @param second Second float stored in the receiver.
 * @param third Positive third float used by the field helper.
 * @param fourth Fourth float stored in the receiver.
 * @return Zero for a nonpositive third float, otherwise one.
 */
s32 func_0023BB20(FieldObject23BE00* object, FieldObject23CEB0* target, u32 color, float first, float second, float third, float fourth);

/**
 * @brief Initialize the display receiver's method table and target state.
 * @param object Receiver to initialize.
 * @return Original receiver pointer.
 */
FieldObject23BE00* func_0023BE00(FieldObject23BE00* object);

/**
 * @brief Detach an object and add it to the resident queue.
 * @param object Object to detach and queue.
 */
void func_0023BF50(void* object);

/**
 * @brief Initialize the receiver's table and state fields after its base initializer.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
FieldObject23B950* func_0023B950(FieldObject23B950* object);

/**
 * @brief Position the display using its grid target, signed index, and supplied size.
 * @param object Display receiver holding the grid target and position values.
 * @param index Signed cell index; negative values leave the display unchanged.
 * @param size Positive size stored in the display and used for its position.
 * @return One when updated; zero for no target, a nonpositive size, or a negative index.
 */
s32 func_0023B9B0(FieldObject23BE00* object, s16 index, float size);

/**
 * @brief Restore three table pointers, call base cleanup, and optionally delete the receiver.
 * @param object Receiver to release, or null.
 * @param flags Signed deletion flag.
 * @return The original receiver pointer.
 */
FieldObject23C180* func_0023C180(FieldObject23C180* object, s16 flags);

/**
 * @brief Clear the receiver state, initialize its resident data, and attach it to the field runtime.
 * @param object Receiver to initialize.
 * @param first_float First value forwarded to the resident initializer.
 * @param second_float Second value forwarded to the resident initializer.
 */
void func_0023D020(FieldObject23D020* object, float first_float, float second_float);

/**
 * @brief Store three floats and update receiver state when a target exists and the third float is nonzero.
 * @param object Receiver to update.
 * @param x First float.
 * @param y Second float.
 * @param z Third float.
 * @return One when updated, otherwise zero.
 */
s32 func_0023BAB0(FieldObject23BAB0* object, float x, float y, float z);

/**
 * @brief Set the total from the current index, row count, and width.
 * @param object Receiver to update.
 */
void func_0023CB30(FieldObject23CB30* object);
/**
 * @brief Refresh field grid coordinates from the current index.
 * @param object Grid receiver to update.
 */
void func_0023C7B0(FieldObject23CEA0* object);

/**
 * @brief Set the grid selection index and update its coordinates.
 * @param object Grid marker.
 * @param index Selection index.
 */
void func_0023C550(FieldObject23CEA0* object, u8 index);

/**
 * @brief Store two floats at receiver offsets 0xFC and 0x100.
 * @param object Receiver to update.
 * @param first Value stored at 0xFC.
 * @param second Value stored at 0x100.
 */
void func_0023CE60(FieldObject23CE80* object, float first, float second);

/**
 * @brief Store two floats at receiver offsets 0xF4 and 0xF8.
 * @param object Receiver to update.
 * @param first Value stored at 0xF4.
 * @param second Value stored at 0xF8.
 */
void func_0023CE70(FieldObject23CEB0* object, float first, float second);

/**
 * @brief Update position from the signed count and width.
 * @param object Receiver to update.
 * @return Always 1.
 */
s32 func_0023CEE0(FieldObject23CEB0* object);

/**
 * @brief Apply position offsets, optionally update the count, then refresh position.
 * @param object Receiver to update.
 * @param value New signed count when positive.
 * @param first_delta First position offset.
 * @param second_delta Second position offset.
 * @return Always 1.
 */
s32 func_0023CF50(FieldObject23CEB0* object, s16 value, float first_delta, float second_delta);

/**
 * @brief Store a byte at receiver offset 0xAD.
 * @param object Receiver to update.
 * @param value Byte to store.
 */
void func_0023CEA0(FieldObject23CEA0* object, u8 value);

/**
 * @brief Store two byte dimensions and their product minus one.
 * @param object Receiver to update.
 * @param width First byte value.
 * @param height Second byte value.
 */
void func_0023CE80(FieldObject23CE80* object, u8 width, u8 height);

/**
 * @brief Store two floats in both state pairs and set two state bytes.
 * @param object Receiver to update.
 * @param first Value stored at offsets 0xF4 and 0xC0.
 * @param second Value stored at offsets 0xF8 and 0xC4.
 * @return Always 1.
 */
s32 func_0023CEB0(FieldObject23CEB0* object, float first, float second);

/**
 * @brief Advance through a receiver's linked nodes.
 * @param object Receiver holding the first node.
 * @param count Additional next links to follow from the first node's next pointer.
 * @return The reached node, or null if the list ends early.
 */
FieldNode23D310* func_0023D310(FieldObject23D310* object, s32 count);

/**
 * @brief Read the unsigned halfword at offset 0x90.
 * @param object Receiver.
 * @return The current unsigned halfword.
 */
u16 func_0023B3A0(FieldState23B3A0* object);

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 4.
 */
s32 func_0023D2B0(FieldObject153270* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0023D2A0(void* object);

#ifdef __cplusplus
}
#endif

#endif
