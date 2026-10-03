#ifndef SO3_OVERLAYS_1070_00_TEXT_00294DA0_H
#define SO3_OVERLAYS_1070_00_TEXT_00294DA0_H

#include "types.h"
#include "overlays/1070-00/text_00213F40.h"
#include "overlays/1070-00/text_00202FB0.h"
#include "overlays/1070-00/text_001F2BB0.h"
#include "overlays/1070-00/text_002A4F10.h"

/** Aligned vector with floating-point and raw-word views. */
typedef union FieldQuad128
{
    unsigned __int128 raw;
    float value[4];
    u32 word[4];
#ifdef __cplusplus
    /** Access the vector's four floating-point components. */
    float* data()
    {
        return value;
    }
    const float* data() const
    {
        return value;
    }
    FieldQuad128& operator=(const FieldQuad128& other)
    {
        raw = other.raw;
        return *this;
    }
#endif
} FieldQuad128;
/** Source record with position and attribute vectors. */
typedef struct FieldHistorySource170
{
    FieldQuad128 unk00;
    FieldQuad128 position;
    FieldQuad128 attributes;
    u8 unk30[0x140];
} FieldHistorySource170;
/** History record with position, attributes, and control words. */
typedef struct FieldHistoryRecord40
{
    FieldQuad128 unk00;
    FieldQuad128 position;
    FieldQuad128 attributes;
    FieldQuad128 control;
} FieldHistoryRecord40;
/** Three-vector output record. */
typedef struct FieldHistoryOutput30
{
    FieldQuad128 position;
    FieldQuad128 attributes;
    FieldQuad128 control;
} FieldHistoryOutput30;
/** Observed receiver prefix for selected-group history output. */
typedef struct FieldHistoryReceiver298CC0
{
    u8 unk00[0xC];
    s32 limit;
    s32 samples;
    FieldHistorySource170* source;
    u32 unk18;
    FieldScaleMask296670* mask;
    FieldHistoryRecord40* history;
    u32 unk24;
    union
    {
        float value;
        u32 bits;
    } unk28;
    s32 index;
    float unk30;
    float decrement;
    u8 unk38[0xC];
    float scale;
    u8 unk48[5];
    u8 mode;
    u8 unk4e[8];
    u8 policy;
} FieldHistoryReceiver298CC0;

/** Source record of size 0x120 with position and attribute vectors. */
typedef struct FieldHistorySource120
{
    FieldQuad128 unk00;
    FieldQuad128 position;
    FieldQuad128 attributes;
    u8 unk30[0xF0];
} FieldHistorySource120;
/** Observed receiver prefix for selected-group history output. */
typedef struct FieldHistoryReceiver29BA70
{
    u8 unk00[0xC];
    s32 limit;
    s32 samples;
    FieldHistorySource120* source;
    u32 unk18;
    FieldScaleMask296670* mask;
    FieldHistoryRecord40* history;
    u32 unk24;
    union
    {
        float value;
        u32 bits;
    } unk28;
    s32 index;
    float unk30;
    float decrement;
    u8 unk38[0xC];
    float scale;
    u8 unk48[5];
    u8 mode;
    u8 unk4e[8];
    u8 policy;
} FieldHistoryReceiver29BA70;

/** Source record of size 0xB0 with position and attribute vectors. */
typedef struct FieldHistorySourceB0
{
    FieldQuad128 unk00;
    FieldQuad128 position;
    FieldQuad128 attributes;
    u8 unk30[0x80];
} FieldHistorySourceB0;
/** Observed receiver prefix for selected-group history output. */
typedef struct FieldHistoryReceiver29ECE0
{
    u8 unk00[0xC];
    s32 limit;
    s32 samples;
    FieldHistorySourceB0* source;
    u32 unk18;
    FieldScaleMask296670* mask;
    FieldHistoryRecord40* history;
    u32 unk24;
    union
    {
        float value;
        u32 bits;
    } unk28;
    s32 index;
    float unk30;
    float decrement;
    u8 unk38[0xC];
    float scale;
    u8 unk48[5];
    u8 mode;
    u8 unk4e[8];
    u8 policy;
} FieldHistoryReceiver29ECE0;

/** Source record of size 0x90 with position and attribute vectors. */
typedef struct FieldHistorySource90
{
    FieldQuad128 unk00;
    FieldQuad128 position;
    FieldQuad128 attributes;
    u8 unk30[0x60];
} FieldHistorySource90;
/** Observed receiver prefix for selected-group history output. */
typedef struct FieldHistoryReceiver2A1FF0
{
    u8 unk00[0xC];
    s32 limit;
    s32 samples;
    FieldHistorySource90* source;
    u32 unk18;
    FieldScaleMask296670* mask;
    FieldHistoryRecord40* history;
    u32 unk24;
    union
    {
        float value;
        u32 bits;
    } unk28;
    s32 index;
    float unk30;
    float decrement;
    u8 unk38[0xC];
    float scale;
    u8 unk48[5];
    u8 mode;
    u8 unk4e[8];
    u8 policy;
} FieldHistoryReceiver2A1FF0;

/** Partial group receiver with its scale reference at offset 0xB0. */
typedef struct FieldScaleOwnerB0
{
    u8 unk00[0xC];
    s32 unk0c;
    s32 unk10;
    u8 unk14[8];
    FieldScaleMask296670* unk1c;
    u8 unk20[0xC];
    s32 unk2c;
    u8 unk30[0x80];
    FieldScaleSource296670* unkb0;
} FieldScaleOwnerB0;
/** Partial group receiver with its scale reference at offset 0xC0. */
typedef struct FieldScaleOwnerC0
{
    u8 unk00[0xC];
    s32 unk0c;
    s32 unk10;
    u8 unk14[8];
    FieldScaleMask296670* unk1c;
    u8 unk20[0xC];
    s32 unk2c;
    u8 unk30[0x90];
    FieldScaleSource296670* unkc0;
} FieldScaleOwnerC0;
/** Partial group receiver with its scale reference at offset 0xD0. */
typedef struct FieldScaleOwnerD0
{
    u8 unk00[0xC];
    s32 unk0c;
    s32 unk10;
    u8 unk14[8];
    FieldScaleMask296670* unk1c;
    u8 unk20[0xC];
    s32 unk2c;
    u8 unk30[0xA0];
    FieldScaleSource296670* unkd0;
} FieldScaleOwnerD0;

/** Partial receiver whose value and control flag are updated together. */
typedef struct FieldValueFlagState18
{
    u8 unk00[0x18];
    s32 unk18;
    u8 unk1c[9];
    u8 unk25_0 : 1;
    u8 unk25_1_7 : 7;
} FieldValueFlagState18;

/** Partial receiver containing the countdown at offset 0x50. */
typedef struct FieldDelayState50
{
    u8 unk00[0x50];
    float delay;
} FieldDelayState50;

/** Partial receiver containing the countdown at offset 0x230. */
typedef struct FieldDelayState230
{
    u8 unk00[0x230];
    float delay;
} FieldDelayState230;

/** Partial receiver containing the countdown at offset 0x240. */
typedef struct FieldDelayState240
{
    u8 unk00[0x240];
    float delay;
} FieldDelayState240;

/** Partial receiver holding a secondary-base pointer at offset 0x10. */
typedef struct FieldRetryState295AA0
{
    u8 unk00[0x10];
    FieldReceiverTail21AB20* unk10;
} FieldRetryState295AA0;

/** Partial embedded receiver containing two words with unknown meanings. */
typedef struct FieldInitialWordPair
{
    u32 unk00;
    s32 unk04;
} FieldInitialWordPair;

/** Partial receiver for the 0029B860 field-access family. */
typedef struct FieldState29B860
{
    u8 unk00[0x28];
    float unk28;
    u32 unk2c;
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
    u32 unk48;
    u8 unk4c;
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u32 unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    unsigned __int128 unk60;
    unsigned __int128 unk70;
    unsigned __int128 unk80;
    unsigned __int128 unk90;
    const u8* unka0;
    u32 unka4;
} FieldState29B860;

/** Partial receiver for the 0029EA90 field-access family. */
typedef struct FieldState29EA90
{
    u8 unk00[0x28];
    float unk28;
    u32 unk2c;
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
    u32 unk48;
    u8 unk4c;
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u32 unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    unsigned __int128 unk60;
    unsigned __int128 unk70;
    unsigned __int128 unk80;
    unsigned __int128 unk90;
    const u8* unka0;
    u32 unka4;
} FieldState29EA90;

/** Partial receiver for the 002A1DA0 field-access family. */
typedef struct FieldState2A1DA0
{
    u8 unk00[0x28];
    float unk28;
    u32 unk2c;
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
    u32 unk48;
    u8 unk4c;
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u32 unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    unsigned __int128 unk60;
    unsigned __int128 unk70;
    unsigned __int128 unk80;
    unsigned __int128 unk90;
    const u8* unka0;
    u32 unka4;
} FieldState2A1DA0;

/** Partial source containing four aligned quadword values. */
typedef struct FieldCopySource29BA30
{
    u8 unk00[0x150];
    unsigned __int128 unk150;
    unsigned __int128 unk160;
    unsigned __int128 unk170;
    unsigned __int128 unk180;
} FieldCopySource29BA30;

/** Partial source containing four aligned quadword values. */
typedef struct FieldCopySource29ECA0
{
    u8 unk00[0x150];
    unsigned __int128 unk150;
    unsigned __int128 unk160;
    unsigned __int128 unk170;
    unsigned __int128 unk180;
} FieldCopySource29ECA0;

/** Partial source containing four aligned quadword values. */
typedef struct FieldCopySource2A1FB0
{
    u8 unk00[0x150];
    unsigned __int128 unk150;
    unsigned __int128 unk160;
    unsigned __int128 unk170;
    unsigned __int128 unk180;
} FieldCopySource2A1FB0;

/** Partial receiver whose word at offset 0xA0 points to a byte flag. */
typedef struct FieldBytePointerA0
{
    u8 unk00[0xA0];
    u8* unka0;
} FieldBytePointerA0;

/** Partial receiver with two parallel arrays sharing a capacity and count. */
typedef struct FieldParallelArrays298B70
{
    u8 unk00[0xB0];
    u8* unkb0;
    unsigned __int128* unkb4;
    u32 unkb8;
    u32 unkbc;
    s32 unkc0;
    s32 unkc4;
} FieldParallelArrays298B70;

/** Partial receiver whose control flag occupies byte 0x34. */
typedef struct FieldFlagState34
{
    u8 unk00[0x15];
    u8 unk15;
    u8 unk16[6];
    FieldEntry1C* unk1c;
    u8 unk20[0x11];
    u8 unk31;
    u8 unk32;
    u8 unk33;
    union
    {
        u8 raw;
        struct
        {
            u8 bit0 : 1;
            u8 bits1_7 : 7;
        } bits;
    } unk34;
} FieldFlagState34;

/** Partial receiver holding an array of FieldEntry1C and its count. */
typedef struct FieldEntryArray295A10
{
    u8 unk00[0x1C];
    FieldEntry1C* unk1c;
    u8 unk20[4];
    s32 unk24;
} FieldEntryArray295A10;

#ifdef __cplusplus
/** Release storage through the external allocator interface. */
extern "C" void func_100CB0(void* storage);

/** Partial data-first receiver with its virtual table at offset 0x90. */
class FieldClass173568
{
public:
    u8 unk00[0xC];
    u8* unk0c;
    u8 unk10[0x80];
    /** Release the buffer's allocation and destroy the receiver. */
    virtual ~FieldClass173568();
};


/** Observed receiver prefix with primary vtable at 0x179470. */
class FieldClass179470 : public FieldClass16AB90
{
public:
    /** Initialize the observed fields and enable control bit 2. */
    FieldClass179470();
    /** Destroy the receiver and release its owned buffers. */
    virtual ~FieldClass179470()
    {
        delete[] unk24;
        func_100CB0(unk28);
        func_100CB0(unk2c);
    }
    s16 unk14;
    s16 unk16;
    u8 unk18[2];
    u8 unk1a;
    u8 unk1b;
    void* unk1c;
    u8 unk20[4];
    FieldClass173568* unk24;
    void* unk28;
    void* unk2c;
    u32 unk30;
    u8 unk34[0xC];
    u32 unk40;
    u32 unk44;
    u32 unk48;
    u32 unk4c;
};

/** Receiver prefix with primary and secondary callback interfaces. */
class FieldClass172110 : public FieldClass16AB90, public FieldClass16AB60
{
public:
    /** Initialize the control fields and clear the context control bit. */
    FieldClass172110();
    /** Destroy the receiver through both of its base interfaces. */
    virtual ~FieldClass172110();
    /** Return the fixed receiver type value 4. */
    virtual s32 func_slot0c();
    /** Delete the receiver through its virtual destructor. */
    virtual void func_slot10();
    /** Update the receiver state. */
    virtual void func_slot14();
    /** Handle a callback through the secondary interface. */
    virtual void func_slot0c(void* value);
    s32 unk18;
    u32 unk1c;
    float unk20;
    u8 unk24;
    u8 unk25_0 : 1;
    u8 unk25_1 : 1;
    u8 unk25_2_7 : 6;
};

/** Partial destruction interface with primary vtable at 0x172170. */
class FieldClass172170 : public FieldClass179470
{
public:
    /** Destroy the receiver and its owned buffers through the primary base. */
    virtual ~FieldClass172170();
};

/** Partial interface of the external base destructor at 0x43EA30. */
class LibReceiver43EA30
{
public:
    /** Destroy the external base receiver. */
    virtual ~LibReceiver43EA30();
};

/** Partial interface of the external base destructor at 0x4A71F0. */
class LibReceiver4A71F0
{
public:
    /** Destroy the external base receiver. */
    virtual ~LibReceiver4A71F0();
    /** Return the receiver type. */
    virtual s32 func_slot0c();
    /** Delete the receiver through its primary interface. */
    virtual void func_slot10();
    /** Update the receiver. */
    virtual void func_slot14();
    /** Invoke its default handler. */
    virtual void func_slot18();
    /** Create a receiver for the selected byte-sized kind. */
    virtual void* func_slot1c(u8 kind);
};

/** Partial callback receiver with primary vtable at 0x173580. */
class FieldClass173580 : public LibReceiver43EA30
{
public:
    /** Destroy the callback receiver through its external base. */
    virtual ~FieldClass173580();
};

/** Partial callback receiver with primary vtable at 0x1735A0. */
class FieldClass1735A0 : public LibReceiver4A71F0
{
public:
    /** Destroy the callback receiver through its external base. */
    virtual ~FieldClass1735A0();
};

/** Partial destruction interface with primary vtable at 0x172870. */
class FieldClass172870 : public FieldClass173A80
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172870()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x172BB0. */
class FieldClass172BB0 : public FieldClass1739B0
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172BB0()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x172EF0. */
class FieldClass172EF0 : public FieldClass1738E0
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172EF0()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x1734A0. */
class FieldClass1734A0 : public FieldClass173810
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass1734A0()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x172530. */
class FieldClass172530 : public FieldClass172BB0
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172530()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x172460. */
class FieldClass172460 : public FieldClass172530
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172460()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x1727A0. */
class FieldClass1727A0 : public FieldClass172870
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass1727A0()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x1726D0. */
class FieldClass1726D0 : public FieldClass1727A0
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass1726D0()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x172AE0. */
class FieldClass172AE0 : public FieldClass172BB0
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172AE0()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x172A10. */
class FieldClass172A10 : public FieldClass172AE0
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172A10()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x172E20. */
class FieldClass172E20 : public FieldClass172EF0
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172E20()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x172D50. */
class FieldClass172D50 : public FieldClass172E20
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172D50()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x173160. */
class FieldClass173160 : public FieldClass1734A0
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass173160()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x173090. */
class FieldClass173090 : public FieldClass173160
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass173090()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x1733D0. */
class FieldClass1733D0 : public FieldClass1734A0
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass1733D0()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x173300. */
class FieldClass173300 : public FieldClass1733D0
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass173300()
    {
    }
};

/** Partial destruction interface with primary vtable at 0x172390. */
class FieldClass172390 : public FieldClass172460
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172390();
};

/** Partial destruction interface with primary vtable at 0x172600. */
class FieldClass172600 : public FieldClass1726D0
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172600();
};

/** Partial destruction interface with primary vtable at 0x172940. */
class FieldClass172940 : public FieldClass172A10
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172940();
};

/** Partial destruction interface with primary vtable at 0x172C80. */
class FieldClass172C80 : public FieldClass172D50
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172C80();
};

/** Partial destruction interface with primary vtable at 0x172FC0. */
class FieldClass172FC0 : public FieldClass173090
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass172FC0();
};

/** Partial destruction interface with primary vtable at 0x173230. */
class FieldClass173230 : public FieldClass173300
{
public:
    /** Destroy the receiver through its primary base. */
    virtual ~FieldClass173230();
};

/** Primary receiver prefix, preceding the secondary base at 0x18. */
class FieldRequestHead294DA0
{
public:
    u8 unk00[0x15];
    u8 unk15;
    u8 unk16[2];
};

/** Secondary receiver passed to the asynchronous read interface. */
class FieldRequestObserver294DA0
{
public:
    void* unk00;
};

/** Partial receiver holding the selected read entry and its notification token. */
class FieldRequestState294DA0 : public FieldRequestHead294DA0, public FieldRequestObserver294DA0
{
public:
    FieldEntry1C* unk1c;
    u8 unk20[8];
    s32 unk28;
    s32 unk2c;
    u8 unk30[2];
    u8 unk32;
};

/** Partial entry with a base at offset 0xF0. */
class FieldEntryHead0029E550
{
public:
    u8 unk00[0xF0];
};

class FieldEntryTail0029E550
{
public:
    u8 unk00[0x30];
};

class FieldEntry0029E550 : public FieldEntryHead0029E550, public FieldEntryTail0029E550
{
};

/** Partial receiver holding the entry array at offset 0x14. */
typedef struct FieldEntryOwner0029E550
{
    u8 unk00[0x14];
    FieldEntry0029E550* unk14;
} FieldEntryOwner0029E550;

/** Partial entry with a base at offset 0x80. */
class FieldEntryHead002A1860
{
public:
    u8 unk00[0x80];
};

class FieldEntryTail002A1860
{
public:
    u8 unk00[0x30];
};

class FieldEntry002A1860 : public FieldEntryHead002A1860, public FieldEntryTail002A1860
{
};

/** Partial receiver holding the entry array at offset 0x14. */
typedef struct FieldEntryOwner002A1860
{
    u8 unk00[0x14];
    FieldEntry002A1860* unk14;
} FieldEntryOwner002A1860;

/** Partial entry with a base at offset 0x60. */
class FieldEntryHead002A4AD0
{
public:
    u8 unk00[0x60];
};

class FieldEntryTail002A4AD0
{
public:
    u8 unk00[0x30];
};

class FieldEntry002A4AD0 : public FieldEntryHead002A4AD0, public FieldEntryTail002A4AD0
{
};

/** Partial receiver holding the entry array at offset 0x14. */
typedef struct FieldEntryOwner002A4AD0
{
    u8 unk00[0x14];
    FieldEntry002A4AD0* unk14;
} FieldEntryOwner002A4AD0;

/** Partial first base of FieldEntry29B830, covering offsets 0x00-0x13F. */
class FieldEntryHead29B830
{
public:
    u8 unk00[0x140];
};

/** Partial second base of FieldEntry29B830, placed at offset 0x140. */
class FieldEntryTail29B830
{
public:
    u8 unk00[0x30];
};

/** 0x170-byte array element; func_0029B830 converts it to its base at 0x140. */
class FieldEntry29B830 : public FieldEntryHead29B830, public FieldEntryTail29B830
{
};

/** Partial receiver holding an array of FieldEntry29B830 at offset 0x14. */
typedef struct FieldEntryOwner29B830
{
    u8 unk00[0x14];
    FieldEntry29B830* unk14;
} FieldEntryOwner29B830;
#endif

#ifdef __cplusplus
extern "C" {

/**
 * @brief Request kind 0x11 through the receiver's creation interface.
 * @param object Receiver that creates the requested object.
 */
void func_00298B40(LibReceiver4A71F0* object);
#endif

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
void func_00298CC0(FieldHistoryReceiver298CC0* object, s32 capacity, FieldHistoryOutput30* output, u32 stamp);

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
void func_0029BA70(FieldHistoryReceiver29BA70* object, s32 capacity, FieldHistoryOutput30* output, u32 stamp);

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
void func_0029ECE0(FieldHistoryReceiver29ECE0* object, s32 capacity, FieldHistoryOutput30* output, u32 stamp);

/**
 * @brief Copy selected group histories and extend the caller's VU0 bounds.
 * @param object Receiver containing selection masks, source records, and histories.
 * @param capacity Output-record count at which processing stops before the next group.
 * @param output Destination array of three-vector records.
 * @param stamp Nonzero to copy the receiver's raw word at 0x28 into control records.
 */
void func_002A1FF0(FieldHistoryReceiver2A1FF0* object, s32 capacity, FieldHistoryOutput30* output, u32 stamp);

/**
 * @brief Scale two float components in each entry of selected groups.
 * @param source Reference to the scale receiver; a null receiver skips the update.
 * @param entries Entry buffer to update.
 * @param count Number of entries requested.
 * @param first First group flag index.
 * @param group_size Number of entries in each selected group.
 * @param limit End of the group flag range.
 * @param flags Group bitmask array.
 */
void func_00296670(FieldScaleSource296670** source, FieldScaleEntry296670* entries, s32 count, s32 first, s32 group_size, s32 limit, const u64* flags);

/**
 * @brief Initialize the particle arrays using the default heap, then restore the heap.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_00298180(void* object, s32 count, s32 group_size);

/**
 * @brief Initialize the particle arrays using the default heap, then restore the heap.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_002982E0(void* object, s32 count, s32 group_size);

/**
 * @brief Initialize the particle arrays using the default heap, then restore the heap.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_00298440(void* object, s32 count, s32 group_size);

/**
 * @brief Initialize the particle arrays using the default heap, then restore the heap.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_002985A0(void* object, s32 count, s32 group_size);

/**
 * @brief Initialize the particle arrays using the default heap, then restore the heap.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_00298700(void* object, s32 count, s32 group_size);

/**
 * @brief Initialize the particle arrays using the default heap, then restore the heap.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_00298860(void* object, s32 count, s32 group_size);

/**
 * @brief Initialize the particle arrays using the default heap, then restore the heap.
 * @param object Receiver whose arrays are initialized.
 * @param count Number of groups.
 * @param group_size Number of entries per group.
 */
void func_002989E0(void* object, s32 count, s32 group_size);

/**
 * @brief Update the particle buffer and scale entries in its selected groups.
 * @param object Receiver containing the group mask and scale reference.
 * @param count Number of entries to update.
 * @param entries Entry buffer.
 */
void func_00298120(FieldScaleOwnerD0* object, s32 count, FieldScaleEntry296670* entries);

/**
 * @brief Update the particle buffer and scale entries in its selected groups.
 * @param object Receiver containing the group mask and scale reference.
 * @param count Number of entries to update.
 * @param entries Entry buffer.
 */
void func_00298280(FieldScaleOwnerC0* object, s32 count, FieldScaleEntry296670* entries);

/**
 * @brief Update the particle buffer and scale entries in its selected groups.
 * @param object Receiver containing the group mask and scale reference.
 * @param count Number of entries to update.
 * @param entries Entry buffer.
 */
void func_002983E0(FieldScaleOwnerB0* object, s32 count, FieldScaleEntry296670* entries);

/**
 * @brief Update the particle buffer and scale entries in its selected groups.
 * @param object Receiver containing the group mask and scale reference.
 * @param count Number of entries to update.
 * @param entries Entry buffer.
 */
void func_00298540(FieldScaleOwnerB0* object, s32 count, FieldScaleEntry296670* entries);

/**
 * @brief Update the particle buffer and scale entries in its selected groups.
 * @param object Receiver containing the group mask and scale reference.
 * @param count Number of entries to update.
 * @param entries Entry buffer.
 */
void func_002986A0(FieldScaleOwnerB0* object, s32 count, FieldScaleEntry296670* entries);

/**
 * @brief Update the particle buffer and scale entries in its selected groups.
 * @param object Receiver containing the group mask and scale reference.
 * @param count Number of entries to update.
 * @param entries Entry buffer.
 */
void func_00298800(FieldScaleOwnerB0* object, s32 count, FieldScaleEntry296670* entries);

/**
 * @brief Update the particle buffer and scale entries in its selected groups.
 * @param object Receiver containing the group mask and scale reference.
 * @param count Number of entries to update.
 * @param entries Entry buffer.
 */
void func_00298980(FieldScaleOwnerB0* object, s32 count, FieldScaleEntry296670* entries);


/**
 * @brief Store the value, clear the receiver flag, and set context flag 6.
 * @param object Receiver containing the value and control flag.
 * @param value Value to store.
 */
void func_00296190(FieldValueFlagState18* object, s32 value);

/**
 * @brief Dispatch the update with the fixed time step when its control byte is set.
 * @param object Receiver forwarded to the update.
 * @param context Context forwarded to the update.
 * @return Byte result of the dispatched update.
 */
u8 func_00296620(void* object, void* context);

/**
 * @brief Advance the countdown and dispatch its active update.
 * @param object Receiver containing the countdown.
 */
void func_00296580(FieldDelayState50* object);

/**
 * @brief Set the low control bit at byte 0x34.
 * @param object Receiver whose flag is set.
 */
void func_00295A80(FieldFlagState34* object);

/**
 * @brief Test whether the referenced byte differs from 1.
 * @param object Receiver holding the byte pointer.
 * @return One if the byte differs from 1, otherwise zero.
 */
s32 func_00298A50(FieldBytePointerA0* object);

/**
 * @brief Return the fixed value 35.
 * @param object Receiver; unused.
 * @return Always 35.
 */
s32 func_00298AD0(void* object);

/**
 * @brief Set the unkb8 word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_00298C20(FieldParallelArrays298B70* object, u32 value);

/**
 * @brief Read the unkb8 word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_00298C30(FieldParallelArrays298B70* object);

/**
 * @brief Set the unkbc word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_00298C40(FieldParallelArrays298B70* object, u32 value);

/**
 * @brief Read the unkbc word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_00298C50(FieldParallelArrays298B70* object);

/**
 * @brief Set the unkb0 reference.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_00298C60(FieldParallelArrays298B70* object, u8* value);

/**
 * @brief Read the unkb0 reference.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8* func_00298C70(FieldParallelArrays298B70* object);

/**
 * @brief Set the unkb4 reference.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_00298C80(FieldParallelArrays298B70* object, unsigned __int128* value);

/**
 * @brief Read the unkb4 reference.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
unsigned __int128* func_00298C90(FieldParallelArrays298B70* object);

#ifdef __cplusplus
/**
 * @brief Submit the selected read entry and register its state notification.
 * @param object Receiver holding the entry array and selected entry index.
 */
void func_00294DA0(FieldRequestState294DA0* object);
#endif


/**
 * @brief Consume the control bit and advance past marked entries.
 * @param object Receiver holding entry indices and state.
 */
void func_00294FE0(FieldFlagState34* object);

/**
 * @brief Return the secondary base of an array entry.
 * @param object Receiver holding the entry array.
 * @param index Entry index.
 * @return The entry's secondary base, or null if its address is null.
 */
FieldEntryTail0029E550* func_0029E550(FieldEntryOwner0029E550* object, s32 index);

/**
 * @brief Return the secondary base of an array entry.
 * @param object Receiver holding the entry array.
 * @param index Entry index.
 * @return The entry's secondary base, or null if its address is null.
 */
FieldEntryTail002A1860* func_002A1860(FieldEntryOwner002A1860* object, s32 index);

/**
 * @brief Return the secondary base of an array entry.
 * @param object Receiver holding the entry array.
 * @param index Entry index.
 * @return The entry's secondary base, or null if its address is null.
 */
FieldEntryTail002A4AD0* func_002A4AD0(FieldEntryOwner002A4AD0* object, s32 index);


/**
 * @brief Initialize the two observed words of an embedded receiver.
 * @param object Embedded receiver to initialize.
 * @return The supplied receiver.
 */
FieldInitialWordPair* func_00297E10(FieldInitialWordPair* object);

/**
 * @brief Advance the countdown and invoke func_424F20 when it has elapsed.
 * @param object Receiver containing the countdown at offset 0x230.
 */
void func_00297F40(FieldDelayState230* object);

/**
 * @brief Advance the countdown and invoke func_425100 when it has elapsed.
 * @param object Receiver containing the countdown at offset 0x240.
 */
void func_00298030(FieldDelayState240* object);

/**
 * @brief Try an operation up to eight times while the receiver permits retries.
 * @param object Receiver holding the retry target's secondary base.
 * @param value Opaque value forwarded to the selected operation.
 * @param mode Nonzero selects func_45FF30; zero selects func_460280.
 * @return First nonzero operation result, or zero after retries stop.
 */
s32 func_00295AA0(FieldRetryState295AA0* object, u32 value, s32 mode);

/**
 * @brief Run func_0021A970 on each entry in the unk1c array.
 * @param object Receiver holding the array and its unk24 count.
 */
void func_00295A10(FieldEntryArray295A10* object);


/**
 * @brief Return the fixed value 5.
 * @param object Receiver or first argument; unused.
 * @return Always 5.
 */
s32 func_00296570(void* object);

/**
 * @brief Test whether the byte pointed to by offset 0xA0 differs from 1.
 * @param object Receiver holding the byte pointer.
 * @return 1 if the byte isn't 1, otherwise 0.
 */
s32 func_002988D0(FieldBytePointerA0* object);

/**
 * @brief Append a byte and an optional quadword to the parallel arrays.
 * @param object Receiver whose unkc4 count is checked against its unkc0 capacity.
 * @param value Byte stored in the unkb0 array.
 * @param data Quadword copied into the unkb4 array, or null to leave that entry unchanged.
 *
 * When the arrays are full, this reports an error through func_115C20 with the
 * "progparticles.h" string instead and leaves the count unchanged.
 */
void func_00298B70(FieldParallelArrays298B70* object, u8 value, const unsigned __int128* data);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00298C00(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00298C10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00298CA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00298CB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029BA60(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0029E540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029EC60(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0029EC70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029EC80(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0029EC90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029ECD0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002A1850(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A1F70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A1F80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A1F90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A1FA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A1FE0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002A4AC0(void* object);

#ifdef __cplusplus
/**
 * @brief Return the base at offset 0x140 of an array entry.
 * @param object Receiver holding the entry array.
 * @param index Entry index.
 * @return The entry's FieldEntryTail29B830 base, or null if the entry address is null.
 */
FieldEntryTail29B830* func_0029B830(FieldEntryOwner29B830* object, s32 index);
#endif

/**
 * @brief Set the unk28 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B860(FieldState29B860* object, float value);

/**
 * @brief Set the unk30 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B870(FieldState29B860* object, float value);

/**
 * @brief Read the unk30 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029B880(FieldState29B860* object);

/**
 * @brief Set the unk4d stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B890(FieldState29B860* object, u8 value);

/**
 * @brief Read the unk4d stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_0029B8A0(FieldState29B860* object);

/**
 * @brief Set the unk34 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B8B0(FieldState29B860* object, float value);

/**
 * @brief Set the unk56 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B8C0(FieldState29B860* object, u8 value);

/**
 * @brief Read the unk56 stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_0029B8D0(FieldState29B860* object);

/**
 * @brief Set the unk44 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B8E0(FieldState29B860* object, float value);

/**
 * @brief Read the unk44 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029B8F0(FieldState29B860* object);

/**
 * @brief Read the unk28 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029B900(FieldState29B860* object);

/**
 * @brief Set the unk48 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B910(FieldState29B860* object, u32 value);

/**
 * @brief Read the unk48 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_0029B920(FieldState29B860* object);

/**
 * @brief Set the unk4f stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B930(FieldState29B860* object, u8 value);

/**
 * @brief Set the unk4e stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B940(FieldState29B860* object, u8 value);

/**
 * @brief Set the unk50 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B950(FieldState29B860* object, u32 value);

/**
 * @brief Read the unk50 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_0029B960(FieldState29B860* object);

/**
 * @brief Set the unk55 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B970(FieldState29B860* object, u8 value);

/**
 * @brief Set the unk3c float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B980(FieldState29B860* object, float value);

/**
 * @brief Set the unk54 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B990(FieldState29B860* object, u8 value);

/**
 * @brief Set the unk40 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029B9A0(FieldState29B860* object, float value);

/**
 * @brief Set the unk38 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029BA20(FieldState29B860* object, float value);

/**
 * @brief Set the unk28 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EA90(FieldState29EA90* object, float value);

/**
 * @brief Set the unk30 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EAA0(FieldState29EA90* object, float value);

/**
 * @brief Read the unk30 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029EAB0(FieldState29EA90* object);

/**
 * @brief Set the unk4d stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EAC0(FieldState29EA90* object, u8 value);

/**
 * @brief Read the unk4d stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_0029EAD0(FieldState29EA90* object);

/**
 * @brief Set the unk34 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EAE0(FieldState29EA90* object, float value);

/**
 * @brief Set the unk56 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EAF0(FieldState29EA90* object, u8 value);

/**
 * @brief Read the unk56 stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_0029EB00(FieldState29EA90* object);

/**
 * @brief Set the unk44 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EB10(FieldState29EA90* object, float value);

/**
 * @brief Read the unk44 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029EB20(FieldState29EA90* object);

/**
 * @brief Read the unk28 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_0029EB30(FieldState29EA90* object);

/**
 * @brief Set the unk48 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EB40(FieldState29EA90* object, u32 value);

/**
 * @brief Read the unk48 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_0029EB50(FieldState29EA90* object);

/**
 * @brief Set the unk4f stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EB60(FieldState29EA90* object, u8 value);

/**
 * @brief Set the unk4e stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EB70(FieldState29EA90* object, u8 value);

/**
 * @brief Set the unk50 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EB80(FieldState29EA90* object, u32 value);

/**
 * @brief Read the unk50 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_0029EB90(FieldState29EA90* object);

/**
 * @brief Set the unk55 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EBA0(FieldState29EA90* object, u8 value);

/**
 * @brief Set the unk3c float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EBB0(FieldState29EA90* object, float value);

/**
 * @brief Set the unk54 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EBC0(FieldState29EA90* object, u8 value);

/**
 * @brief Set the unk40 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EBD0(FieldState29EA90* object, float value);

/**
 * @brief Set the unk38 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_0029EC50(FieldState29EA90* object, float value);

/**
 * @brief Set the unk28 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1DA0(FieldState2A1DA0* object, float value);

/**
 * @brief Set the unk30 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1DB0(FieldState2A1DA0* object, float value);

/**
 * @brief Read the unk30 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_002A1DC0(FieldState2A1DA0* object);

/**
 * @brief Set the unk4d stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1DD0(FieldState2A1DA0* object, u8 value);

/**
 * @brief Read the unk4d stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_002A1DE0(FieldState2A1DA0* object);

/**
 * @brief Set the unk34 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1DF0(FieldState2A1DA0* object, float value);

/**
 * @brief Set the unk56 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E00(FieldState2A1DA0* object, u8 value);

/**
 * @brief Read the unk56 stored byte.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u8 func_002A1E10(FieldState2A1DA0* object);

/**
 * @brief Set the unk44 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E20(FieldState2A1DA0* object, float value);

/**
 * @brief Read the unk44 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_002A1E30(FieldState2A1DA0* object);

/**
 * @brief Read the unk28 float value.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
float func_002A1E40(FieldState2A1DA0* object);

/**
 * @brief Set the unk48 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E50(FieldState2A1DA0* object, u32 value);

/**
 * @brief Read the unk48 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_002A1E60(FieldState2A1DA0* object);

/**
 * @brief Set the unk4f stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E70(FieldState2A1DA0* object, u8 value);

/**
 * @brief Set the unk4e stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E80(FieldState2A1DA0* object, u8 value);

/**
 * @brief Set the unk50 stored word.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1E90(FieldState2A1DA0* object, u32 value);

/**
 * @brief Read the unk50 stored word.
 * @param object Receiver containing the field.
 * @return Stored field value.
 */
u32 func_002A1EA0(FieldState2A1DA0* object);

/**
 * @brief Set the unk55 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1EB0(FieldState2A1DA0* object, u8 value);

/**
 * @brief Set the unk3c float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1EC0(FieldState2A1DA0* object, float value);

/**
 * @brief Set the unk54 stored byte.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1ED0(FieldState2A1DA0* object, u8 value);

/**
 * @brief Set the unk40 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1EE0(FieldState2A1DA0* object, float value);

/**
 * @brief Set the unk38 float value.
 * @param object Receiver containing the field.
 * @param value Value to store.
 */
void func_002A1F60(FieldState2A1DA0* object, float value);

/**
 * @brief Clear the stored data and set the control byte.
 * @param object Receiver to update.
 * @param value Nonzero to set the control byte.
 */
void func_0029B9F0(FieldState29B860* object, s32 value);

/**
 * @brief Store the data reference and derive its control byte.
 * @param object Receiver to update.
 * @param data Data whose first byte selects the control value.
 * @param value Word associated with the data reference.
 */
void func_0029B9B0(FieldState29B860* object, const u8* data, u32 value);

/**
 * @brief Clear the stored data and set the control byte.
 * @param object Receiver to update.
 * @param value Nonzero to set the control byte.
 */
void func_0029EC20(FieldState29EA90* object, s32 value);

/**
 * @brief Store the data reference and derive its control byte.
 * @param object Receiver to update.
 * @param data Data whose first byte selects the control value.
 * @param value Word associated with the data reference.
 */
void func_0029EBE0(FieldState29EA90* object, const u8* data, u32 value);

/**
 * @brief Clear the stored data and set the control byte.
 * @param object Receiver to update.
 * @param value Nonzero to set the control byte.
 */
void func_002A1F30(FieldState2A1DA0* object, s32 value);

/**
 * @brief Store the data reference and derive its control byte.
 * @param object Receiver to update.
 * @param data Data whose first byte selects the control value.
 * @param value Word associated with the data reference.
 */
void func_002A1EF0(FieldState2A1DA0* object, const u8* data, u32 value);

/**
 * @brief Clear the stored word and copy four aligned quadwords.
 * @param object Receiver to update.
 * @param source Source of the quadword values.
 */
void func_0029BA30(FieldState29B860* object, const FieldCopySource29BA30* source);

/**
 * @brief Clear the stored word and copy four aligned quadwords.
 * @param object Receiver to update.
 * @param source Source of the quadword values.
 */
void func_0029ECA0(FieldState29EA90* object, const FieldCopySource29ECA0* source);

/**
 * @brief Clear the stored word and copy four aligned quadwords.
 * @param object Receiver to update.
 * @param source Source of the quadword values.
 */
void func_002A1FB0(FieldState2A1DA0* object, const FieldCopySource2A1FB0* source);

#ifdef __cplusplus
}
#endif

#endif
