#ifndef SO3_OVERLAYS_1067_00_TEXT_0021FB80_H
#define SO3_OVERLAYS_1067_00_TEXT_0021FB80_H

#include "types.h"
struct FieldClass151510;
struct FieldVec4B;
#ifdef __cplusplus
#include "overlays/1067-00/text_002DBC50.h"
#endif
#include "overlays/1067-00/text_0021DB80.h"
#include "overlays/1067-00/text_002607B0.h"

/** Partial resident state with a scalar at offset 0x5FC and flags at offsets 0x6D2-0x6D3. */
typedef struct FieldObject220150
{
    u8 unk00[0x5FC];
    float value;
    u8 unk600[0xD2];
    u8 unk6D2_0_5 : 6;
    u8 unk6D2_6 : 1;
    u8 unk6D2_7 : 1;
    u8 unk6D3_0 : 1;
    u8 unk6D3_1 : 1;
    u8 unk6D3_2 : 1;
    u8 unk6D3_3_7 : 5;
} FieldObject220150;

#ifdef __cplusplus
#include "overlays/1067-00/text_00207AF0.h"
#endif

#ifdef __cplusplus
/** Partial 0xA0-byte list owner with a scalar track and table D_15B890. */
class FieldClass15B890 : public FieldClass15B950
{
public:
    /** @brief Allocate through the Lib heap. @param size Allocation size. @return Allocated storage or null. */
    static void* operator new(u32 size);
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
    /** @brief Clear the scalar track and record array and set the default scale. */
    FieldClass15B890()
    {
        unk90 = 0;
        unk94 = 1.0f;
        unk9e_0 = 0;
        unk98 = 0;
    }

    u8 unk8c[4];
    FieldClass150090* unk90;
    float unk94;
    void* unk98;
    s16 unk9c;
    u8 unk9e_0 : 1;
    u8 unk9e_1_7 : 7;
    u8 unk9f;

    /** @brief Release the scalar track and record array, then destroy the list. */
    virtual ~FieldClass15B890();

    /** @brief Clear the listed nodes and release both owned tracks. */
    virtual void func_002DDA70();
};
#endif

#ifdef __cplusplus
extern "C" {

/**
 * @brief Update the field context object after a release.
 * @param object Field context object.
 */
void func_00226340(void* object);
/** @brief Set two bounds and optionally select a named entry. @param object Context receiver. @param name Optional entry name. @param first First bound. @param second Second bound. */
void func_00225150(void* object, const char* name, float first, float second);

/** @brief Create or update the attached range object. @param object Context receiver. @param value Range selection. @param duration Transition duration. */
void func_00225550(void* object, u32 value, float duration);

#endif

/**
 * @brief Store four floats in an aligned vector.
 * @param vector Vector to update.
 * @param first First component.
 * @param second Second component.
 * @param third Third component.
 * @param fourth Fourth component.
 * @return The supplied vector.
 */
FieldVector2624* func_00221430(FieldVector2624* vector, float first, float second, float third, float fourth);

/** @brief Return the receiver's heading. @param object Field receiver. @return Heading in radians. */
float func_002273B0(struct FieldClass151510* object);

/** @brief Apply a vector with the supplied scale. @param object Field receiver. @param vector Vector to apply. @param scale Application scale. */
void func_00227740(struct FieldClass151510* object, const struct FieldVec4B* vector, float scale);

/**
 * @brief Invoke the receiver's virtual handler at vtable offset 0x20, passing its word at offset 0x74.
 * @param object Receiver of the virtual call.
 */
void func_00227130(void* object);

/**
 * @brief Apply an aligned vector to the field receiver using the supplied float.
 * @param object Receiver to update.
 * @param vector Aligned vector to copy.
 * @param scale Float used by the update.
 */
void func_002274F0(void* object, const FieldVector2624* vector, float scale);

/**
 * @brief Build a four-float value, pass it through the library helper, and copy it to output.
 * @param unused0 Unused first argument.
 * @param unused1 Unused second argument.
 * @param output Destination for the four floats.
 */
void func_002276F0(void* unused0, void* unused1, float* output);

/**
 * @brief Set two state bits and a float when the receiver allows the update.
 * @param object Receiver with state bytes at offsets 0x6D2 and 0x6D3.
 * @param flag Value stored in bit 7 at offset 0x6D2.
 */
void func_00220150(void* object, s32 flag);

typedef struct FieldObject228E0 FieldObject228E0;
typedef struct FieldObject224E50 FieldObject224E50;
typedef struct FieldObject29250 FieldObject29250;
typedef struct FieldObject2B440 FieldObject2B440;

/**
 * @brief Initialize the receiver and poll it until the helper returns nonzero.
 * @param object Receiver to initialize and poll.
 */
void func_002227F0(void* object);

/**
 * @brief Set state from the current resident table record.
 * @param object Receiver whose state byte is updated.
 */
void func_002228E0(FieldObject228E0* object);

typedef struct FieldObject22CC0 FieldObject22CC0;

/**
 * @brief Process the receiver when its field flag is clear and context data is present.
 * @param object Receiver to process.
 * @return Helper result, or zero when the receiver is ineligible.
 */
s32 func_00222CC0(FieldObject22CC0* object);

/**
 * @brief Copy the receiver byte at offset 0xF0 to offset 0x60.
 * @param object Receiver to update.
 */
void func_00229250(FieldObject29250* object);

/**
 * @brief Clear the resident owner's link when it points to this object.
 * @param object Object to detach from the owner.
 */
void func_00229310(void* object);

/**
 * @brief Copy the receiver byte at offset 0x94 to offset 0x60.
 * @param object Receiver to update.
 */
void func_0022B440(FieldObject2B440* object);

/**
 * @brief Detach an object and queue it for removal.
 * @param object Object to remove.
 */
void func_00224CE0(void* object);

/**
 * @brief Clear eight receiver words from offsets 0x14 through 0x30.
 * @param object Receiver to reset.
 */
void func_00224E50(FieldObject224E50* object);

/**
 * @brief Copy a 17-byte operand record and select the resident receiver.
 * @param object Receiver selected by the resident state.
 * @param source Packed operand record to retain.
 * @param flags Flags retained with the record.
 * @return Always one.
 */
s32 func_00225790(void* object, const void* source, u32 flags);

/**
 * @brief Update the actor heading, optionally interpolating it.
 * @param actor Actor whose orientation to update.
 * @param heading Heading in radians.
 * @param duration Interpolation duration; zero updates immediately.
 */
void func_00227610(struct FieldClass151510* actor, float heading, float duration);

typedef struct FieldObject152320 FieldObject152320;

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 14.
 */
s32 func_0021FC10(FieldObject152320* object);

typedef struct FieldObject152410 FieldObject152410;

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 2.
 */
s32 func_00224FC0(FieldObject152410* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00224C30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00224CD0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00229240(void* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * Partial FieldClass151510 with 13 more virtual slots, with vtable D_152430 in
 * main data. Its constructor sets type bit 0x2 in unk78.
 * Overrides of earlier slots other than slots 9 and 15 are not declared yet.
 */
class FieldClass152430 : public FieldClass151510
{
public:
    /** @brief Initialize the actor fields and its embedded command list. */
    FieldClass152430();

    /** @brief Destroy the object. */
    virtual ~FieldClass152430();

    /**
     * @brief Test the inherited gate while flag bit 5 at offset 0x8C is clear.
     * @return True when both conditions pass.
     */
    virtual bool func_00204420();

    /**
     * @brief Optionally copy a vector to offset 0x20, then update the vectors at offsets 0x170-0x190.
     * @param value Vector to copy, or null to keep the current one.
     */
    virtual void func_00205710(const FieldVec4A* value);

    /** @brief Return the default result for slot 19. @return Always zero. */
    virtual s32 func_00203990();

    /** @brief Virtual handler slot 20. */
    virtual void func_00227840();

    /** @brief Copy the vector at offset 0x20 to offset 0x170 and set offset 0x190 to (0, 0, 0, 1). */
    virtual void func_001DE3D0();

    /** @brief Virtual handler slot 22. */
    virtual void func_002039A0();

    /** @brief Virtual handler slot 23. */
    virtual void func_00227CC0();

    /** @brief Default handler that performs no work. */
    virtual void func_001DE3C0();

    /** @brief Virtual handler slot 25. */
    virtual void func_001FED00();

    /** @brief Default scalar-setting handler. @param setting Setting to ignore. @param value Scalar to ignore. */
    virtual void func_002039B0(u8 setting, float value);

    /** @brief Virtual handler slot 27. */
    virtual void func_00228DD0();

    /**
     * @brief Virtual handler slot 28.
     * @param flags Flag word; bit 0 and the remaining bits select different updates.
     */
    virtual void func_00226C10(u32 flags);

    /**
     * @brief Test whether the actor is moving.
     * @return True when the vector at offset 0x180 is nonzero.
     */
    virtual bool func_002039C0() const;

    /** @brief Virtual handler slot 30. */
    virtual void func_00203A30();

    /** @brief Virtual handler slot 31. */
    virtual void func_002270D0();

    u8 unk210[0xD0];
    u8 unk2e0;
    s8 unk2e1;
    u8 unk2e2_0 : 1;
    u8 unk2e2_1_7 : 7;
};

/** Actor command list retaining its owning receiver. */
class FieldClass152E50 : public FieldClass152FA0
{
public:
    /** @brief Destroy the command list. */
    virtual ~FieldClass152E50();

    FieldClass152430* unk7c;
};

/** Partial base actor; the native constructor is 0x0024E420. */
class FieldClass1535B0 : public FieldClass152430
{
public:
    /** @brief Allocate through the Lib heap. @param size Allocation size. @return Storage or null. */
    static void* operator new(u32 size);
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
    /** @brief Initialize the inherited actor and named-object state. */
    FieldClass1535B0();
    /** @brief Destroy the named-object state and inherited actor. */
    virtual ~FieldClass1535B0();
    /** @brief Bind a named resident object and copy its transform. @param name Object name. @return One when found, zero otherwise. */
    s32 func_0024D1C0(const char* name);
    u8 unk2f0[0x44];
    u8 unk334_0_1 : 2;
    u8 unk334_2 : 1;
    u8 unk334_3_7 : 5;
};

/** 0x3D0-byte actor derived from the native 0x340-byte base. */
class FieldClass155580 : public FieldClass1535B0
{
public:
    /** @brief Allocate through the Lib heap. @param size Allocation size. @return Storage or null. */
    static void* operator new(u32 size);
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
    /** @brief Set the actor category and clear its transition state. */
    FieldClass155580()
    {
        unk78 |= 0x1000;
        unk348 = 0.0f;
        unk3a4 = 0;
        unk3c0 = 0;
        unk3c4 = 0;
        unk3a0 = 0;
        unk3b0 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
        unk350_0 = 0;
        unk350_1 = 0;
    }
    /** @brief Destroy the inherited named actor. */
    virtual ~FieldClass155580();
    float unk340;
    float unk344;
    float unk348;
    float unk34c;
    u8 unk350_0 : 1;
    u8 unk350_1 : 1;
    u8 unk350_2_7 : 6;
    u8 unk351[0x4F];
    void* unk3a0;
    void* unk3a4;
    u8 unk3a8[8];
    FieldVec4A unk3b0;
    void* unk3c0;
    void* unk3c4;
};

/** Partial Field object with vtable D_152410 in main data and an owned child at offset 0x300. */
class FieldClass152410 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass152410();
    /** @brief Detach and delete the child, then detach this object and queue it for release. */
    virtual void func_001DD7B0();
    u8 unk14[0x2EC];
    FieldClass150070* unk300;
};

/** 0x300-byte actor whose scalar track is retained at offset 0x144. */
class FieldClass1570D0 : public FieldClass152430
{
public:
    /** @brief Allocate through the Lib heap. @param size Allocation size. @return Allocated storage or null. */
    static void* operator new(u32 size);
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
    /** @brief Set the actor flags and create its scalar track. */
    FieldClass1570D0()
    {
        unk78 |= 0x2000;
        unk204 |= 0x2 | 0x4 | 0x8;
        unk144 = new FieldClass15B890;
        unk2f0 = 0;
        unk2e0 = 1;
    }
    /** @brief Destroy the actor and its inherited state. */
    virtual ~FieldClass1570D0();
    /**
     * @brief Report the stored moving flag.
     * @return Flag at offset 0x2F0.
     */
    virtual bool func_002039C0() const;
    bool unk2f0;
};

class FieldClass1502E0;

/**
 * Partial FieldClass152430 with four more virtual slots, with vtable D_150EB0
 * in main data. Its constructor (func_002036F0, in text_00202240) sets type
 * bit 0x4 in unk78. It is declared here because it derives from
 * FieldClass152430.
 */
class FieldClass150EB0 : public FieldClass152430
{
public:
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
    /** @brief Destroy the object. */
    virtual ~FieldClass150EB0();

    /**
     * @brief Virtual handler slot 32.
     * @param arg0 First argument whose meaning is not yet known.
     * @param arg1 Second argument whose meaning is not yet known.
     * @param value Float argument whose meaning is not yet known.
     */
    virtual void func_00202CF0(void* arg0, void* arg1, float value);

    /** @brief Virtual handler slot 33. */
    virtual void func_00203500();

    /** @brief Reset actor state using its selected resource key. */
    virtual void func_00202580();

    /**
     * @brief Virtual handler slot 35.
     * @param arg Argument whose meaning is not yet known.
     */
    virtual void func_00200110(void* arg);

    u8 unk2f0[0x20];
    FieldClass150280 unk310;
    u8 unk380[4];
    FieldClass1502A0* unk384;
    u8 unk388[8];
    FieldVec4B unk390;
    FieldClass1502E0* unk3a0;
    u8 unk3a4[8];
    s32 unk3ac;
    s32 unk3b0;
    u32 unk3b4;
    u8 unk3b8[8];
};

/**
 * Partial FieldClass150EB0 with one more virtual slot, with vtable D_152F00 in
 * main data. Its constructor (func_00238940, in text_0022DC70) sets type bit
 * 0x8 in unk78. It is declared here because it derives from FieldClass152430.
 */
class FieldClass152F00 : public FieldClass150EB0
{
public:
    /** @brief Allocate through the Lib heap. @param size Allocation size. @return Storage or null. */
    static void* operator new(u32 size);
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
    /** @brief Initialize the inherited actor and its resource state. */
    FieldClass152F00();
    /** @brief Destroy the object. */
    virtual ~FieldClass152F00();

    /**
     * @brief Run FieldClass152430's handler, then copy the vector to offset 0x530.
     * @param value Vector to copy.
     */
    virtual void func_00205710(const FieldVec4A* value);

    /** @brief Virtual handler slot 36. */
    virtual void func_002378E0();

    u8 unk3c0[0x30];
    FieldClass1502A0 unk3f0;
    u8 unk468[0xC8];
    FieldVec4B unk530;
    u8 unk540[0x48];
    void* unk588;
    u8 unk58c[0x41];
    u8 unk5cd_0_1 : 2;
    u8 unk5cd_2 : 1;
    u8 unk5cd_3 : 1;
    u8 unk5cd_4 : 1;
    u8 unk5cd_5_7 : 3;
};

/**
 * Partial FieldClass152430 with vtable D_153330 in main data. Its constructor
 * (func_00249000, in text_0023DC90) sets type bit 0x400 in unk78. Its seven
 * new virtual slots (32-38) are not declared yet.
 */
class FieldClass153330 : public FieldClass152430
{
public:
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
    /** @brief Destroy the object. */
    virtual ~FieldClass153330();

    /**
     * @brief Virtual handler slot 32.
     * @param arg0 First argument whose meaning is not yet known.
     * @param arg1 Second argument whose meaning is not yet known.
     * @param arg2 Third argument whose meaning is not yet known.
     * @param value Float argument whose meaning is not yet known.
     */
    virtual void func_002485B0(void* arg0, void* arg1, void* arg2, float value);

    /** @brief Default handler that performs no work. */
    virtual void func_0023D390();

    /** @brief Default handler that performs no work. */
    virtual void func_0023D3A0();

    /** @brief Default handler that performs no work. */
    virtual void func_0023D3B0();

    /** @brief Virtual handler slot 36. */
    virtual void func_00247940();

    /**
     * @brief Virtual handler slot 37.
     * @param flag Value whose meaning is not yet known; func_001DD860 passes 1.
     */
    virtual void func_0023DE90(s32 flag);

    /**
     * @brief Virtual handler slot 38.
     * @param arg Argument whose meaning is not yet known.
     */
    virtual void func_0023D3C0(void* arg);

    u8 unk2f0[0xE0];
    FieldClass1502A0 unk3d0;
    u8 unk448[0x1C];
    float unk464;
    u8 unk468[0x4D];
    u8 unk4b5;
    u8 unk4b6;
    u8 unk4b7;
    u8* unk4b8;
};

/**
 * Partial 0x6A0-byte FieldClass152F00 with vtable D_152FE0 in main data. Its
 * constructor is inlined in the factory func_001F87F0, which sets type bit 0x20
 * through func_001F8A70. Overrides and new virtual slots are not declared yet.
 */
class FieldClass152FE0 : public FieldClass152F00
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass152FE0();

    u8 unk5d0[0x80];
    FieldVec4A unk650;
    FieldVec4A unk660;
    FieldVec4A unk670;
    float unk680;
    u32 unk684;
    u32 unk688;
    u8 unk68c[4];
    s32 unk690;
    s32 unk694;
    u8 unk698[4];
    u8 unk69c;
    u8 unk69d;
    u8 unk69e;
    u8 unk69f_0 : 1;
    u8 unk69f_1 : 1;
    u8 unk69f_2 : 1;
    u8 unk69f_3_7 : 5;
};

/**
 * Partial FieldClass152F00 with vtable D_152350 in main data. Its constructor
 * (func_00224A00) sets type bit 0x10 in unk78. New virtual slots are not
 * declared yet.
 */
class FieldClass152350 : public FieldClass152F00
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass152350();

    u8 unk5d0[0x68];
    float unk638;
    u8 unk63c[0x96];
    u8 unk6d2_0_3 : 4;
    u8 unk6d2_4 : 1;
    u8 unk6d2_5_7 : 3;
};
#endif

#endif
