#include "include_asm.h"
#include "main/resident_00101550.h"
#include "main/resident_data.h"
#include "main/func_0011EE00.h"
#include "sdk/main/libc_guess_0013CD50.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/scene.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/model.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/vector_inlines.h"


typedef struct HalfwordSetterOwnertext_0046AE20
{
    u8 unk00[0x6C];
    u16 unk6c;
} HalfwordSetterOwnertext_0046AE20;



typedef struct ByteGetterOwnertext_0046AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e[0x8];
    u8 unk56;
} ByteGetterOwnertext_0046AE20;



typedef struct ByteSetterOwnertext_0046AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u8 unk50[0x4];
    u8 unk54;
    u8 unk55;
    u8 unk56;
} ByteSetterOwnertext_0046AE20;



typedef struct WordSetterOwnertext_0046AE20
{
    u8 unk00[0x48];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x5C];
    u32 unkb0;
    u32 unkb4;
    u32 unkb8;
    u32 unkbc;
} WordSetterOwnertext_0046AE20;



typedef struct WordGetterOwnertext_0046AE20
{
    u8 unk00[0x8];
    u32 unk08;
    u32 unk0c;
    u8 unk10[0x38];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x5C];
    u32 unkb0;
    u32 unkb4;
    u32 unkb8;
    u32 unkbc;
} WordGetterOwnertext_0046AE20;

typedef struct LibFlagState59C
{
    u8 unk00[0x59C];
    u8 unk59c;
    u8 unk59d_0 : 1;
    u8 unk59d_1_7 : 7;
} LibFlagState59C;


typedef struct LibFloatFieldOwner0046AE20
{
    u8 unk00[0x28];
    float unk28;
    u8 unk2c[4];
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
} LibFloatFieldOwner0046AE20;

/** Partial metadata used to filter and name resource entries. */
struct LibEntryMetadata
{
    u16 unk00;
    u16 data_offset;

    /** Negative values link the entry to entry -1 - link of the manager's link_names. */
    s32 link;

    u8 unk08[4];
    s16 child_count;
    u8 state;
    u8 kind;
    u8 unk10[0xC];
    u32 flags;
    u8 unk20[0x64];
    s32 name_checksum;
};

/** Partial inherited transform state shared by the setter's callers. */
typedef struct LibTransformByteState
{
    u8 unk00[0x50];
    u8 transform_dirty;
} LibTransformByteState;

/** Partial receiver with its halfword flags at 0x6A. */
typedef struct LibObjectFlags6A
{
    u8 unk00[0x6A];
    u16 flags;
} LibObjectFlags6A;


typedef struct ByteSourceStateOwnertext_0046AE20 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; const u8* sourceA0; u32 valueA4; } ByteSourceStateOwnertext_0046AE20;
typedef struct TwoWordClearArgStateOwnertext_0046AE20 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; void* unkA0; void* unkA4; } TwoWordClearArgStateOwnertext_0046AE20;
typedef struct FourQuadwordCopyTargetOwnertext_0046AE20
{
    u8 pad00[0x2C];
    u32 unk2C;
    u8 pad30[0x30];
    unsigned __int128 values60[4];
} FourQuadwordCopyTargetOwnertext_0046AE20;
typedef struct FourQuadwordCopySourceOwnertext_0046AE20
{
    u8 pad00[0x150];
    unsigned __int128 values150[4];
} FourQuadwordCopySourceOwnertext_0046AE20;

/** Partial receiver with a byte counter at 0x790. */
typedef struct LibByte790Counter
{
    u8 unk00[0x790];
    u8 unk790;
} LibByte790Counter;

/** Four aligned floats; the C view of a Lib vector. */
typedef struct LibFloat4
{
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) LibFloat4;

/** Partial grid with vtable D_173E70 in main data. */
class LibClass173E70 : public LibClass173A40
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass173E70();

};

/** Partial grid with vtable D_175DE0 in main data. */
class LibClass175DE0 : public LibClass1774E0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass175DE0()
    {
    }

};

/** Partial grid with vtable D_175760 in main data. */
class LibClass175760 : public LibClass175DE0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass175760()
    {
    }
};

/** Partial grid with vtable D_175D10 in main data. */
class LibClass175D10 : public LibClass175DE0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass175D10()
    {
    }
};

/** Partial grid with vtable D_176050 in main data. */
class LibClass176050 : public LibClass177410
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176050()
    {
    }

};

/** Partial grid with vtable D_175900 in main data. */
class LibClass175900 : public LibClass176050
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass175900()
    {
    }
};

/** Partial grid with vtable D_175F80 in main data. */
class LibClass175F80 : public LibClass176050
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass175F80()
    {
    }
};

/** Partial grid with vtable D_175B70 in main data. */
class LibClass175B70 : public LibClass1775B0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass175B70()
    {
    }

};

/** Partial grid with vtable D_175AA0 in main data. */
class LibClass175AA0 : public LibClass175B70
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass175AA0()
    {
    }
};

/** Partial grid with vtable D_1762C0 in main data. */
class LibClass1762C0 : public LibClass177340
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass1762C0()
    {
    }

};

/** Partial grid with vtable D_1761F0 in main data. */
class LibClass1761F0 : public LibClass1762C0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass1761F0()
    {
    }
};

/** Partial grid with vtable D_176530 in main data. */
class LibClass176530 : public LibClass177270
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176530()
    {
    }

};

/** Partial grid with vtable D_176460 in main data. */
class LibClass176460 : public LibClass176530
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176460()
    {
    }
};

/** Partial grid with vtable D_176940 in main data. */
class LibClass176940 : public LibClass1771A0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176940()
    {
    }

};

/** Partial grid with vtable D_1766D0 in main data. */
class LibClass1766D0 : public LibClass176940
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass1766D0()
    {
    }
};

/** Partial grid with vtable D_176870 in main data. */
class LibClass176870 : public LibClass176940
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176870()
    {
    }
};

/** Partial grid with vtable D_173DA0 in main data. */
class LibClass173DA0 : public LibClass173E70
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass173DA0()
    {
    }
};

/** Partial grid with vtable D_176AE0 in main data. */
class LibClass176AE0 : public LibClass173DA0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176AE0()
    {
    }
};

/** Partial grid with vtable D_176C80 in main data. */
class LibClass176C80 : public LibClass173DA0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176C80()
    {
    }
};

/** Partial grid with vtable D_176EF0 in main data. */
class LibClass176EF0 : public LibClass177680
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176EF0()
    {
    }

};

/** Partial grid with vtable D_176E20 in main data. */
class LibClass176E20 : public LibClass176EF0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176E20()
    {
    }
};

/** Partial grid with vtable D_1755C0 in main data. */
class LibClass1755C0 : public LibClass177090
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass1755C0();

};

/** Partial grid with vtable D_175690 in main data. */
class LibClass175690 : public LibClass175760
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass175690();
};

/** Partial grid with vtable D_175830 in main data. */
class LibClass175830 : public LibClass175900
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass175830();
};

/** Partial grid with vtable D_1759D0 in main data. */
class LibClass1759D0 : public LibClass175AA0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass1759D0();
};

/** Partial grid with vtable D_175C40 in main data. */
class LibClass175C40 : public LibClass175D10
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass175C40();
};

/** Partial grid with vtable D_175EB0 in main data. */
class LibClass175EB0 : public LibClass175F80
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass175EB0();
};

/** Partial grid with vtable D_176120 in main data. */
class LibClass176120 : public LibClass1761F0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176120();
};

/** Partial grid with vtable D_176390 in main data. */
class LibClass176390 : public LibClass176460
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176390();
};

/** Partial grid with vtable D_176600 in main data. */
class LibClass176600 : public LibClass1766D0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176600();
};

/** Partial grid with vtable D_1767A0 in main data. */
class LibClass1767A0 : public LibClass176870
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass1767A0();
};

/** Partial grid with vtable D_176A10 in main data. */
class LibClass176A10 : public LibClass176AE0
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176A10();
};

/** Partial grid with vtable D_176BB0 in main data. */
class LibClass176BB0 : public LibClass176C80
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176BB0();
};

/** Partial grid with vtable D_176D50 in main data. */
class LibClass176D50 : public LibClass176E20
{
public:
    /** @brief Destroy the grid. */
    virtual ~LibClass176D50();
};

/** Shared object whose reference count is at offset 0x8. */
class LibReferenceCounted
{
public:
    /** @brief Destroy the shared object. */
    virtual ~LibReferenceCounted();

    u8 unk04[4];
    s32 reference_count;
};

/** Partial Lib object with vtable D_1751A0 in main data; it holds one counted reference at offset 0xA80. */
struct LibObject1751A0
{
    u8 unk00[0xA80];
    LibReferenceCounted* reference;
    u8 unkA84[0x58];

    /** Set when the reference came from func_0046B480, which only counts it; releasing it then never deletes it. */
    u8 holds_reference;
};

/** Partial receiver with a flag byte at 0x8D. */
typedef struct LibFlagState8D
{
    u8 unk00[0x8D];
    u8 unk8d_0 : 1;
    u8 unk8d_1 : 1;
    u8 unk8d_2_7 : 6;
} LibFlagState8D;

/** Fixed-capacity list of pointers, with vtable D_175380 in main data; its data comes before the vptr. */
class LibPointerList
{
public:
    s16 capacity;
    s16 count;
    void** items;

    /**
     * @brief Allocate room for a number of pointers.
     * @param size Capacity to allocate.
     */
    LibPointerList(s32 size);

    /** @brief Free the pointer array. */
    virtual ~LibPointerList()
    {
        delete[] items;
    }

    /**
     * @brief Append an item; a full list ignores it.
     * @param item Item to append.
     */
    virtual void append(void* item);

    /**
     * @brief Replace the pointer array with an empty one of a new capacity.
     * @param size Capacity to allocate; stays zero when allocation fails.
     */
    void reserve(s32 size)
    {
        delete[] items;
        items = new (0) void*[size];

        if (items)
        {
            capacity = size;
        }

        count = 0;
    }
};

/** Pointer list with vtable D_175360 in main data. */
class LibClass175360 : public LibPointerList
{
public:
    /** @brief Destroy the list. */
    virtual ~LibClass175360();
};

/** Pointer list with vtable D_175370 in main data. */
class LibClass175370 : public LibPointerList
{
public:
    /** @brief Destroy the list. */
    virtual ~LibClass175370();
};

/** Node of a scene's object list, with vtable D_175390 in main data. */
class LibClass175390 : public LibListSentinel
{
public:
    /** @brief Destroy the node. */
    virtual ~LibClass175390();
};

/** Transform with one extra vector, with vtable D_1753A0 in main data. */
class LibClass1753A0 : public LibTransform
{
public:
    /** @brief Destroy the transform. */
    virtual ~LibClass1753A0();

    /**
     * @brief Copy the extra vector and the transform state.
     * @param source Transform to copy.
     */
    virtual void func_004713F0(const LibClass1753A0* source);

    FieldVec4A unk210;
};

/** Model placed at a target relative to a base position, with vtable D_175430 in main data. */
class LibClass175430 : public LibModel
{
public:
    /** @brief Destroy the model. */
    virtual ~LibClass175430();

    /**
     * @brief Set the target and point the translation from the base position at it.
     * @param x Target x.
     * @param y Target y.
     * @param z Target z.
     */
    virtual void set_translation(float x, float y, float z);

    /**
     * @brief Set the target and point the translation from the base position at it.
     * @param value Target; its w becomes the translation's w.
     */
    virtual void set_translation_vector(const LibVector4* value);

    /**
     * @brief Set the target and point the translation from the base position at it.
     * @param value Target; its w becomes the translation's w.
     */
    virtual void copy_translation(const LibVector4* value);

    /**
     * @brief Return the target.
     * @return Target position.
     */
    virtual FieldVec4B* func_00479100();

    /**
     * @brief Copy the base position, then build this model from another one.
     * @param links Display list the model draws through, or null.
     * @param source Model to copy.
     * @return Nonzero on success.
     */
    virtual s32 func_00471410(LibUpdateList* links, LibClass175430* source);

    /** Position the translation is measured from. */
    FieldVec4B base;

    FieldVec4B target;
};

/** Transform with an optional owned buffer, with vtable D_175530 in main data. */
class LibClass175530 : public LibTransform
{
public:
    /** @brief Free the buffer unless it is borrowed, then destroy the transform. */
    virtual ~LibClass175530();

    u8 unk210[0x40];
    u8* unk250;

    /** Nonzero when unk250 belongs to someone else. */
    u8 unk254;
};

/** Partial fixed-capacity list of key bytes with a parallel array of vectors. */
typedef struct LibKeyedVectorList
{
    u8 unk00[0xB0];
    u8* keys;
    LibFloat4* values;
    u8 unkB8[8];
    s32 capacity;
    s32 count;
} LibKeyedVectorList;

/** Partial object an entry's link points at another manager's entry through. */
typedef struct LibLinkTarget
{
    u8 unk00[0x6C];
    u16 unk6c;
    u8 unk6e[0x19A];
    LibByte790Counter* unk208;
    u8 unk20c[0x624];
    LibByte790Counter* unk830;
    u8 unk834[4];
    LibByte790Counter* unk838;
} LibLinkTarget;

/** Partial kind-10 entry object with a linked object of its own. */
typedef struct LibLinkGroup
{
    u8 unk00[0x3E4];
    LibLinkTarget* object;
    u8 unk3e8[0xB1];
    u8 unk499_0 : 1;
    u8 unk499_1 : 1;
    u8 unk499_2_7 : 6;
} LibLinkGroup;

/** Partial kind-1/8 renderable entry object. */
typedef struct LibRenderableEntryObject
{
    u8 unk00[0xF];
    u8 unk0f;
    u8 unk10[0x594];
    u8 unk5a4[0x1F4];
    u8 unk798_0 : 1;
    u8 unk798_1 : 1;
    u8 unk798_2_7 : 6;
} LibRenderableEntryObject;

extern "C"
{
    void func_0047A130(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8);
    void func_004B3D80(void* object, void* handle);
    void func_004A22C0(void* object);
    s32 func_004A9000(void* object);

    void func_0046B480(LibObject1751A0* holder, LibReferenceCounted* reference);
    void func_0046C090(LibEntryManager* manager, void* handle);
    void func_004720F0(LibFloat4* vector);
    LibFloat4* func_00472110(LibFloat4* vector, float value);
    void func_00472570(LibEntryManager* manager, s32 check);
    void func_00472720(LibEntryManager* manager, s32 enable);
    void* func_00472C90(const LibEntryManager* manager, void* handle);
    void* func_00472DA0(const LibEntryManager* manager, void* handle);
    void* func_00473040(LibEntryManager* manager, const char* name);
    void* func_004731A0(const LibEntryManager* manager);
    void func_00473E20(LibEntryManager* manager);
    void func_00478F90(LibFlagState8D* object);
    LibFloat4* func_004790A0(LibFloat4* vector, float x, float y, float z);
    void func_004790D0(unsigned __int128* first, unsigned __int128* second, const unsigned __int128* source);
    LibFloat4* func_004790E0(LibFloat4* vector, float x, float y, float z, float w);
    s32 func_00479C90(const ByteSourceStateOwnertext_0046AE20* object);
    s32 func_00479D30(const ByteSourceStateOwnertext_0046AE20* object);
    void func_00479EF0(LibKeyedVectorList* list, u8 key, const LibFloat4* value);
    void func_00479F50(LibKeyedVectorList* list, u8 key, const LibFloat4* value);
}

/** @brief Destroy the list receiver and its sentinel. */
inline LibListReceiver::~LibListReceiver()
{
}

/**
 * @brief Find the index of the entry that owns a handle.
 * @param manager Runtime entry table and source resource header.
 * @param handle Entry handle to look for.
 * @return Index of the first entry with metadata whose handle matches, or -1.
 */
static inline s32 lib_find_entry_index_inline(const LibEntryManager* manager, void* handle)
{
    s32 found = -1;
    s32 index;

    for (index = 0; index < manager->header->count; index++)
    {
        if (manager->entries[index].metadata != 0 && manager->entries[index].handle == handle)
        {
            found = index;
            break;
        }
    }

    return found;
}

/**
 * @brief Test whether an entry has no source metadata.
 * @param entry Entry to test.
 * @return True when the entry has no metadata.
 */
static inline bool lib_entry_is_empty(const LibManagedEntry* entry)
{
    return !entry->metadata;
}

/**
 * @brief Locate an entry's data after its optional sixteen-byte name.
 * @param manager Manager supplying the resource format flag.
 * @param metadata Source entry metadata.
 * @return Metadata-relative entry data, skipping the name when present.
 */
static inline void* lib_get_entry_data_inline(LibEntryManager* manager, LibEntryMetadata* metadata)
{
    u8* data = (u8*)metadata + metadata->data_offset;

    if (manager->header->flags & LIB_ENTRY_HAS_NAMES)
    {
        data += 0x10;
    }

    return data;
}

/**
 * @brief Read the matrix translation into a position vector.
 * @param result Destination vector.
 * @param object Transform source.
 */
static inline void lib_get_transform_translation(FieldVec4B& result, const LibTransform& object)
{
    result.x = object.transform.m[0][3];
    result.y = object.transform.m[1][3];
    result.z = object.transform.m[2][3];
    result.w = 1.0f;
}

/**
 * @brief Subtract the xyz components of one vector from another.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 * @return The difference, with left's w.
 */
static inline FieldVec4B lib_vector_difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B value(left);
    return value.subtract(right);
}

/**
 * @brief View an aligned matrix row as a vector.
 * @param matrix Source matrix.
 * @param index Row index.
 * @return Read-only row vector.
 */
static inline const FieldVec4A& matrix_row_vector(const LibMatrix44Value& matrix, s32 index)
{
    return *(const FieldVec4A*)matrix.m[index];
}

/**
 * @brief View an aligned matrix row as a writable vector.
 * @param matrix Destination matrix.
 * @param index Row index.
 * @return Writable row vector.
 */
static inline FieldVec4A& matrix_row_vector(LibMatrix44Value& matrix, s32 index)
{
    return *(FieldVec4A*)matrix.m[index];
}

/**
 * @brief Set the translation and mark the transform dirty.
 * @param object Transform.
 * @param x Translation x.
 * @param y Translation y.
 * @param z Translation z.
 */
static inline void lib_set_translation(LibOrientedTransform* object, float x, float y, float z)
{
    object->transform_dirty = 1;
    object->translation.x = x;
    object->translation.y = y;
    object->translation.z = z;
    object->translation.w = 1.0f;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046AE20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B0D0);

/**
 * @brief Release the counted reference the object holds and clear it.
 * @param object Object holding the reference.
 */
void func_0046B3F0(LibObject1751A0* object)
{
    LibReferenceCounted* reference = object->reference;

    if (reference)
    {
        if (object->holds_reference)
        {
            if (reference->reference_count > 0)
            {
                reference->reference_count--;
            }
        }
        else if (reference->reference_count > 0)
        {
            if (--reference->reference_count == 0)
            {
                delete reference;
            }
        }
    }

    object->holds_reference = 0;
    object->reference = 0;
}

/**
 * @brief Hold a reference to a shared object and add to its reference count.
 * @param holder Object that keeps the reference.
 * @param reference Shared object to hold.
 */
void func_0046B480(LibObject1751A0* holder, LibReferenceCounted* reference)
{
    holder->holds_reference = 1;
    holder->reference = reference;
    reference->reference_count++;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B4A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B620);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B7D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B7E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B7F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B810);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046B820);

/** @brief Destroy the look-at transform and its transform base. */
LibLookAtTransform::~LibLookAtTransform()
{
}

/**
 * @brief Copy the look-at target and inherited transform state.
 * @param source Transform to copy; its roll angle is not copied.
 */
void LibLookAtTransform::copy_look_at_state(const LibLookAtTransform* source)
{
    look_at_target = source->look_at_target;
    LibTransform::copy_offset_transform_state(source);
}

/** @brief Update the matrix to face the target when one is attached. */
void LibLookAtTransform::update_transform_matrix()
{
    if (look_at_target)
    {
        if (!look_at_target->matrix_ready)
        {
            look_at_target->update_transform_matrix();
        }

        LibTransform::update_transform_matrix();
        matrix_ready = 0;

        FieldVec4B direction;
        FieldVec4B position;
        LibMatrix44Value matrix;
        lib_get_transform_translation(direction, *look_at_target);
        lib_get_transform_translation(position, *this);
        direction = lib_vector_difference(direction, position);
        lib_matrix_look_at(&matrix, &position, &direction, roll_angle);
        matrix.m[0][3] = position.x;
        matrix.m[1][3] = position.y;
        matrix.m[2][3] = position.z;
        matrix_row_vector(transform, 0) = matrix_row_vector(matrix, 0);
        matrix_row_vector(transform, 1) = matrix_row_vector(matrix, 1);
        matrix_row_vector(transform, 2) = matrix_row_vector(matrix, 2);
        matrix_row_vector(transform, 3) = matrix_row_vector(matrix, 3);
    }
    else
    {
        LibTransform::update_transform_matrix();
    }
}

/**
 * @brief Create an object of kind 0x11.
 * @return The new object, or null.
 */
void* LibScene::func_0046BA00()
{
    return func_00471480(0x11);
}

/**
 * @brief Set the primary animation link or register a supplemental link in a binding owner.
 * @param owner Binding owner.
 * @param animation Animation handle; null clears the primary link when mode is zero.
 * @param mode Zero selects the primary link; otherwise it is stored for a new supplemental link.
 */
void lib_animation_register_binding(LibAnimationBindingOwner* owner, void* animation, s32 mode)
{
    if (mode)
    {
        s32 index;

        for (index = 1; index < LIB_ANIMATION_BINDING_CAPACITY; index++)
        {
            if (owner->animation_slots[index] == animation)
            {
                return;
            }
        }

        for (index = 1; index < LIB_ANIMATION_BINDING_CAPACITY; index++)
        {
            if (!owner->animation_slots[index])
            {
                owner->animation_slots[index] = animation;
                owner->animation_modes[index] = mode;
                return;
            }
        }
    }
    else
    {
        owner->animation_slots[0] = animation;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046BAC0);

void* func_0046C080(void* value)
{
    return value;
}

/**
 * @brief Detach a handle from its kind-10 entry and pass it to each enabled slot object.
 * @param manager Runtime entry table and slot objects.
 * @param handle Handle of the entry to detach.
 */
void func_0046C090(LibEntryManager* manager, void* handle)
{
    s32 index;
    s32 slot;

    if (manager->entries == 0)
    {
        return;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        if (manager->entries[index].unk00 == 0 && manager->entries[index].metadata->kind == 10 && manager->entries[index].handle == handle)
        {
            manager->entries[index].handle = 0;

            for (slot = 0; slot < LIB_ENTRY_MANAGER_SLOT_COUNT; slot++)
            {
                if (manager->unk34[slot] != 0 && !manager->unk9f[slot])
                {
                    func_004B3D80(manager->unk34[slot], handle);
                }
            }

            return;
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046C180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046C3F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046C540);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046DE90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0046F910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004713C0);

/**
 * @brief Copy the extra vector and the transform state.
 * @param source Transform to copy.
 */
void LibClass1753A0::func_004713F0(const LibClass1753A0* source)
{
    unk210 = source->unk210;
    LibTransform::copy_offset_transform_state(source);
}

/**
 * @brief Copy the base position, then build this model from another one.
 * @param links Display list the model draws through, or null.
 * @param source Model to copy.
 * @return Nonzero on success.
 */
s32 LibClass175430::func_00471410(LibUpdateList* links, LibClass175430* source)
{
    base = source->base;
    return LibModel::build_from(links, source);
}

/**
 * @brief Create a camera.
 * @param context Resident context the camera starts from.
 * @return The new camera, or null when allocation fails.
 */
LibCamera* LibScene::func_00471440(void* context)
{
    return new (0) LibCamera(context);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00471480);

/**
 * @brief Set a vector to (0, 0, 0, 1).
 * @param vector Vector to set.
 */
void func_004720F0(LibFloat4* vector)
{
    *(unsigned __int128*)vector = 0;
    vector->w = 1.0f;
}

/** Store the low halfword at receiver offset 0x6C. */
void func_00472100(void* object, u32 value)
{
    HalfwordSetterOwnertext_0046AE20* receiver = (HalfwordSetterOwnertext_0046AE20*)object;
    receiver->unk6c = value;
}

/**
 * @brief Set all four components of a vector to one value.
 * @param vector Vector to set.
 * @param value Value for every component.
 * @return The vector.
 */
LibFloat4* func_00472110(LibFloat4* vector, float value)
{
    vector->x = value;
    vector->y = value;
    vector->z = value;
    vector->w = value;
    return vector;
}

/** @brief Initialize the transform without a look-at target or roll. */
LibLookAtTransform::LibLookAtTransform()
{
    look_at_target = 0;
    roll_angle = 0.0f;
}

/**
 * @brief Read one child entry index from an entry's data.
 * @param manager Runtime entry table and source resource header.
 * @param entry_index Index of the parent entry.
 * @param child Position in the parent's child list.
 * @return Entry index of the child.
 */
s32 lib_get_entry_child_index(LibEntryManager* manager, s32 entry_index, s32 child)
{
    s32* children = (s32*)lib_get_entry_data_inline(manager, manager->entries[entry_index].metadata);
    return children[child];
}

/**
 * @brief Get the handle of one child of an entry.
 * @param manager Runtime entry table and source resource header.
 * @param entry_index Index of the parent entry.
 * @param child Position in the parent's child list.
 * @return Handle of the child entry.
 */
void* lib_get_entry_child(LibEntryManager* manager, s32 entry_index, s32 child)
{
    s32* children = (s32*)lib_get_entry_data_inline(manager, manager->entries[entry_index].metadata);
    return manager->entries[children[child]].handle;
}

/**
 * @brief Read the signed child-entry count for an indexed resource entry.
 * @param manager Runtime resource-entry manager.
 * @param index Entry index.
 * @return Signed child-entry count stored in the entry's metadata.
 */
s32 lib_get_entry_child_count(LibEntryManager* manager, s32 index)
{
    return manager->entries[index].metadata->child_count;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472220);

/**
 * @brief Add bits to the object's flags.
 * @param object Receiver.
 * @param flags Flag bits to add.
 */
void lib_object_add_flags(void* object, u16 flags)
{
    LibObjectFlags6A* state = (LibObjectFlags6A*)object;
    state->flags |= flags;
}

/**
 * @brief Locate an entry's data after its optional sixteen-byte name.
 * @param manager Manager supplying the resource format flag.
 * @param metadata Source entry metadata.
 * @return Metadata-relative entry data, skipping the name when present.
 */
void* lib_get_entry_data(LibEntryManager* manager, LibEntryMetadata* metadata)
{
    return lib_get_entry_data_inline(manager, metadata);
}

/**
 * @brief Update eligible renderable entries that pass the metadata flag filter.
 * @param manager Runtime resource-entry manager.
 */
void lib_update_renderable_entries(LibEntryManager* manager)
{
    s32 index;

    for (index = 0; index < manager->header->count; index++)
    {
        LibManagedEntry* entry = &manager->entries[index];
        void* handle = entry->handle;

        if (handle != 0 && entry->unk00 == 0)
        {
            LibEntryMetadata* metadata = entry->metadata;

            if ((metadata->state == 2 || metadata->state == 0) &&
                (metadata->kind == 1 || metadata->kind == 8) &&
                (metadata->flags & 0x4080) == 0)
            {
                func_004A2370(handle);
            }
        }
    }
}

/**
 * @brief Set resource state for eligible renderable entries.
 * @param manager Runtime resource-entry manager.
 */
void func_004724A0(LibEntryManager* manager)
{
    s32 index;

    for (index = 0; index < manager->header->count; index++)
    {
        LibManagedEntry* entry = &manager->entries[index];
        void* handle = entry->handle;

        if (handle != 0 && entry->unk00 == 0)
        {
            LibEntryMetadata* metadata = entry->metadata;

            if ((metadata->state == 2 || metadata->state == 0) &&
                (metadata->kind == 1 || metadata->kind == 8) &&
                (metadata->flags & 0x4080) == 0)
            {
                func_004A29D0(handle);
            }
        }
    }
}

/**
 * @brief Set bit 1 at 0x798 on every eligible renderable entry object.
 * @param manager Runtime resource-entry manager.
 * @param check Nonzero to skip objects whose 0x5A4 member passes func_004A9000.
 */
void func_00472570(LibEntryManager* manager, s32 check)
{
    LibManagedEntry* entry;
    s32 index;
    LibRenderableEntryObject* handle;

    if (manager->entries == 0)
    {
        return;
    }

    if (check)
    {
        for (index = 0; index < manager->header->count; index++)
        {
            entry = &manager->entries[index];
            handle = (LibRenderableEntryObject*)entry->handle;

            if (handle != 0 && entry->unk00 == 0)
            {
                LibEntryMetadata* metadata = entry->metadata;

                if ((metadata->state == 2 || metadata->state == 0) && (metadata->kind == 1 || metadata->kind == 8))
                {
                    if (!func_004A9000(handle->unk5a4))
                    {
                        handle->unk798_1 = 1;
                    }
                }
            }
        }
    }
    else
    {
        // TODO: A second index shadowing the first is the only shape I found that gets this loop's
        // registers right. It reads oddly, so I'd like to find what the original really did.
        s32 index;

        for (index = 0; index < manager->header->count; index++)
        {
            entry = &manager->entries[index];
            handle = (LibRenderableEntryObject*)entry->handle;

            if (handle != 0 && entry->unk00 == 0)
            {
                LibEntryMetadata* metadata = entry->metadata;

                if ((metadata->state == 2 || metadata->state == 0) && (metadata->kind == 1 || metadata->kind == 8))
                {
                    handle->unk798_1 = 1;
                }
            }
        }
    }
}

/**
 * @brief Pass every eligible renderable entry object to func_004A22C0, or clear bit 0 of its byte at 0xF.
 * @param manager Runtime resource-entry manager.
 * @param enable Nonzero to call func_004A22C0; zero to clear the bit.
 */
void func_00472720(LibEntryManager* manager, s32 enable)
{
    LibManagedEntry* entry;
    LibRenderableEntryObject* handle;

    if (manager->entries == 0)
    {
        return;
    }

    if (enable)
    {
        s32 index;

        for (index = 0; index < manager->header->count; index++)
        {
            entry = &manager->entries[index];
            handle = (LibRenderableEntryObject*)entry->handle;

            if (handle != 0 && entry->unk00 == 0)
            {
                LibEntryMetadata* metadata = entry->metadata;

                if ((metadata->state == 2 || metadata->state == 0) && (metadata->kind == 1 || metadata->kind == 8))
                {
                    func_004A22C0(handle);
                }
            }
        }
    }
    else
    {
        s32 index;

        for (index = 0; index < manager->header->count; index++)
        {
            entry = &manager->entries[index];
            handle = (LibRenderableEntryObject*)entry->handle;

            if (handle != 0 && entry->unk00 == 0)
            {
                LibEntryMetadata* metadata = entry->metadata;

                if ((metadata->state == 2 || metadata->state == 0) && (metadata->kind == 1 || metadata->kind == 8))
                {
                    handle->unk0f &= ~1;
                }
            }
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_004728A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00472A00);

/**
 * @brief Copy an entry's name into a buffer.
 * @param manager Runtime entry table and source resource header.
 * @param index Entry index.
 * @param name Buffer of at least seventeen bytes; emptied first.
 * @return name, or null when the resource has no names.
 */
char* lib_copy_entry_name(LibEntryManager* manager, s32 index, char* name)
{
    LibEntryMetadata* metadata;

    name[0] = 0;

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES))
    {
        return 0;
    }

    metadata = manager->entries[index].metadata;
    strncpy_guess(name, (const char*)metadata + metadata->data_offset, LIB_ENTRY_NAME_COMPARE_LENGTH);
    name[LIB_ENTRY_NAME_COMPARE_LENGTH] = 0;
    return name;
}

/**
 * @brief Copy the name of the entry that owns a handle into a buffer.
 * @param manager Runtime entry table and source resource header.
 * @param handle Entry handle to look for.
 * @param name Buffer of at least seventeen bytes; emptied first.
 * @return name, or null when the resource has no names or no entry owns the handle.
 */
char* lib_copy_handle_entry_name(const LibEntryManager* manager, void* handle, char* name)
{
    s32 index;
    const LibEntryMetadata* metadata;

    name[0] = 0;

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES))
    {
        return 0;
    }

    index = lib_find_entry_index_inline(manager, handle);

    if (index < 0)
    {
        return 0;
    }

    metadata = manager->entries[index].metadata;
    strncpy_guess(name, (const char*)metadata + metadata->data_offset, LIB_ENTRY_NAME_COMPARE_LENGTH);
    name[LIB_ENTRY_NAME_COMPARE_LENGTH] = 0;
    return name;
}

/**
 * @brief Find the next kind-5 entry after the entry that owns a handle.
 * @param manager Runtime entry table and source resource header.
 * @param handle Handle of the current entry.
 * @return The next entry of kind 5 that passes the state filter, or null.
 */
void* func_00472C90(const LibEntryManager* manager, void* handle)
{
    s32 found;
    s32 index;

    if (manager->entries == 0)
    {
        return 0;
    }

    found = lib_find_entry_index_inline(manager, handle);

    if (found >= 0)
    {
        index = found;

        for (;;)
        {
            index++;

            if (index >= manager->header->count || index == found)
            {
                break;
            }

            if (manager->entries[index].metadata != 0 && (manager->entries[index].metadata->state == 2 || manager->entries[index].metadata->state == 0) &&
                manager->entries[index].metadata->kind == 5)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find the next kind-10 entry after the entry that owns a handle.
 * @param manager Runtime entry table and source resource header.
 * @param handle Handle of the current entry.
 * @return The next entry of kind 10 that passes the state filter, or null.
 */
void* func_00472DA0(const LibEntryManager* manager, void* handle)
{
    s32 found;
    s32 index;

    if (manager->entries == 0)
    {
        return 0;
    }

    found = lib_find_entry_index_inline(manager, handle);

    if (found >= 0)
    {
        index = found;

        for (;;)
        {
            index++;

            if (index >= manager->header->count || index == found)
            {
                break;
            }

            if (manager->entries[index].metadata != 0 && (manager->entries[index].metadata->state == 2 || manager->entries[index].metadata->state == 0) &&
                manager->entries[index].metadata->kind == 10)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find the next renderable entry after the entry that owns a handle.
 * @param manager Runtime entry table and source resource header.
 * @param handle Handle of the current entry, as returned by lib_find_renderable_entry.
 * @return The next entry of kind 1 or 8 that passes the state filter, or null.
 */
void* lib_find_next_renderable_entry(const LibEntryManager* manager, void* handle)
{
    s32 found;
    s32 index;

    if (manager->entries == 0)
    {
        return 0;
    }

    found = lib_find_entry_index_inline(manager, handle);

    if (found >= 0)
    {
        index = found;

        for (;;)
        {
            index++;

            if (index >= manager->header->count || index == found)
            {
                break;
            }

            if (manager->entries[index].metadata != 0 && (manager->entries[index].metadata->state == 2 || manager->entries[index].metadata->state == 0) &&
                (manager->entries[index].metadata->kind == 1 || manager->entries[index].metadata->kind == 8))
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find the index of the entry that owns a handle.
 * @param manager Runtime entry table and source resource header.
 * @param handle Entry handle to look for.
 * @return Index of the first entry with metadata whose handle matches, or -1.
 */
s32 lib_find_entry_index(const LibEntryManager* manager, void* handle)
{
    return lib_find_entry_index_inline(manager, handle);
}

/**
 * @brief Find a kind-10 entry whose metadata passes the state and name filters.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching handle, or null.
 */
void* func_00473040(LibEntryManager* manager, const char* name)
{
    u8 any_name = 0;
    s32 index;

    if (name == 0 || name[0] == 0)
    {
        any_name = 1;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES) && !any_name)
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && (metadata->state == 2 || metadata->state == 0) &&
            metadata->kind == 10)
        {
            if (any_name || lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset,
                                                        LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find the first kind-5 entry that passes the state filter.
 * @param manager Runtime entry table and source resource header.
 * @return The first matching handle, or null.
 */
void* func_004731A0(const LibEntryManager* manager)
{
    s32 index;

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        if (manager->entries[index].metadata != 0 && (manager->entries[index].metadata->state == 2 || manager->entries[index].metadata->state == 0) &&
            manager->entries[index].metadata->kind == 5)
        {
            return manager->entries[index].handle;
        }
    }

    return 0;
}

/**
 * @brief Find a named entry by searching circularly from the last successful index.
 * @param manager Runtime entry table and source metadata.
 * @param name Entry name; null returns no entry.
 * @param checksum Precomputed signed-byte name sum, or zero to calculate it from up to sixteen characters.
 * @return Matching entry handle, or null.
 */
void* lib_find_named_entry_cached(LibEntryManager* manager, const char* name, s32 checksum)
{
    s32 index;
    s32 scanned;

    if (!name)
    {
        return 0;
    }

    if (!checksum)
    {
        s32 name_index;

        for (name_index = 0; name_index < LIB_ENTRY_NAME_COMPARE_LENGTH; name_index++)
        {
            s32 byte = (s8)name[name_index];

            if (!byte)
            {
                break;
            }

            checksum += byte;
        }
    }

    index = manager->cached_entry_index;

    for (scanned = 0; scanned < manager->header->count; scanned++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata && checksum == metadata->name_checksum &&
            lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset, LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
        {
            manager->cached_entry_index = index;
            return manager->entries[index].handle;
        }

        index++;

        if (index >= manager->header->count)
        {
            index = 0;
        }
    }

    return 0;
}

/**
 * @brief Find an entry by name.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null to take the first entry with metadata.
 * @return Handle of the first entry whose name checksum and name match, or null.
 */
void* lib_find_named_entry(const LibEntryManager* manager, const char* name)
{
    s32 checksum;
    s32 name_index;
    s32 index;
    s32 first;

    if (name == 0)
    {
        for (first = 0; first < manager->header->count; first++)
        {
            if (!lib_entry_is_empty(&manager->entries[first]))
            {
                return manager->entries[first].handle;
            }
        }

        return 0;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES))
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    checksum = 0;

    for (name_index = 0; name_index < LIB_ENTRY_NAME_COMPARE_LENGTH; name_index++)
    {
        s32 byte = (s8)name[name_index];

        if (!byte)
        {
            break;
        }

        checksum += byte;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        const LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && checksum == metadata->name_checksum &&
            lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset, LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
        {
            return manager->entries[index].handle;
        }
    }

    return 0;
}

/**
 * @brief Find a transform entry (metadata state 1 or 3) by name.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching transform handle, or null.
 */
void* lib_find_transform_entry(LibEntryManager* manager, const char* name)
{
    u8 any_name = 0;
    s32 index;

    if (name == 0 || name[0] == 0)
    {
        any_name = 1;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES) && !any_name)
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && (metadata->state == 1 || metadata->state == 3))
        {
            if (any_name || lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset, LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find a camera entry whose metadata passes the state and name filters.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching camera handle, or null.
 */
void* lib_find_camera_entry(LibEntryManager* manager, const char* name)
{
    u8 any_name = 0;
    s32 index;

    if (name == 0 || name[0] == 0)
    {
        any_name = 1;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES) && !any_name)
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && (metadata->state == 2 || metadata->state == 0) &&
            metadata->kind == LIB_ENTRY_KIND_CAMERA)
        {
            if (any_name || lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset,
                                                        LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find a light entry whose metadata passes the state and name filters.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching light handle, or null.
 */
void* lib_find_light_entry(LibEntryManager* manager, const char* name)
{
    u8 any_name = 0;
    s32 index;

    if (name == 0 || name[0] == 0)
    {
        any_name = 1;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES) && !any_name)
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && (metadata->state == 2 || metadata->state == 0) &&
            metadata->kind == LIB_ENTRY_KIND_LIGHT)
        {
            if (any_name || lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset,
                                                        LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

/**
 * @brief Find a renderable entry of kind 1 or 8 whose metadata passes the state and name filters.
 * @param manager Runtime entry table and source resource header.
 * @param name Name to compare, or null or empty to accept any name.
 * @return The first matching renderable handle, or null.
 */
void* lib_find_renderable_entry(LibEntryManager* manager, const char* name)
{
    u8 any_name = 0;
    s32 index;

    if (name == 0 || name[0] == 0)
    {
        any_name = 1;
    }

    if (!(manager->header->flags & LIB_ENTRY_HAS_NAMES) && !any_name)
    {
        return 0;
    }

    if (manager->entries == 0)
    {
        return 0;
    }

    for (index = 0; index < manager->header->count; index++)
    {
        LibEntryMetadata* metadata = manager->entries[index].metadata;

        if (metadata != 0 && (metadata->state == 2 || metadata->state == 0) &&
            (metadata->kind == 1 || metadata->kind == 8))
        {
            if (any_name || lib_compare_bounded_strings(name, (const char*)metadata + metadata->data_offset,
                                                        LIB_ENTRY_NAME_COMPARE_LENGTH) == 0)
            {
                return manager->entries[index].handle;
            }
        }
    }

    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", lib_scene_release_entries);

/** @brief Destroy the node. */
LibClass175390::~LibClass175390()
{
}

/**
 * @brief Point each linked entry's objects at the entries they name in the linked manager.
 * @param manager Runtime entry table with its link names and linked manager.
 */
void func_00473E20(LibEntryManager* manager)
{
    s32 count;
    s32 index;

    if (manager->unk78 != 0 && manager->linked != 0)
    {
        count = manager->header->count;

        for (index = 0; index < count; index++)
        {
            LibManagedEntry* entry = &manager->entries[index];

            if (entry->unk00 == 0)
            {
                s32 link = entry->metadata->link;

                if (link < 0 && entry->handle != 0)
                {
                    LibByte790Counter* target = (LibByte790Counter*)lib_find_named_entry_cached(manager->linked, manager->link_names[-1 - link], 0);

                    if (target)
                    {
                        switch (manager->entries[index].metadata->kind)
                        {
                        case 23:
                            break;

                        case 1:
                            if (manager->entries[index].metadata->flags & 0x80)
                            {
                                LibLinkTarget* object = (LibLinkTarget*)manager->entries[index].handle;

                                if (object->unk6c == 0x110)
                                {
                                    object->unk838 = target;
                                    target->unk790++;
                                }
                                else
                                {
                                    object->unk830 = target;
                                    target->unk790++;
                                }
                            }

                            if (manager->entries[index].metadata->flags & 0x4000)
                            {
                                ((LibLinkTarget*)manager->entries[index].handle)->unk830 = target;
                                target->unk790++;
                            }

                            ((LibLinkTarget*)manager->entries[index].handle)->unk208 = target;
                            break;

                        case 10:
                        {
                            LibLinkGroup* group = (LibLinkGroup*)manager->entries[index].handle;

                            if (group->object && group->unk499_1)
                            {
                                group->object->unk208 = target;
                            }
                        }
                        /* fall through */

                        default:
                            ((LibLinkTarget*)manager->entries[index].handle)->unk208 = target;
                            break;
                        }
                    }
                    else
                    {
                        ((LibLinkTarget*)manager->entries[index].handle)->unk208 = 0;
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", lib_scene_build_objects);

/** Return the word at receiver offset 0x8. */
u32 func_00478F70(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unk08;
}

/** Return the word at receiver offset 0xC. */
u32 func_00478F80(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unk0c;
}

/**
 * @brief Set bit 1 of the flag byte at receiver offset 0x8D.
 * @param object Receiver.
 */
void func_00478F90(LibFlagState8D* object)
{
    object->unk8d_1 = 1;
}

/**
 * @brief Append an item; a full list ignores it.
 * @param item Item to append.
 */
void LibPointerList::append(void* item)
{
    if (count < capacity)
    {
        items[count++] = item;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_00478FE0);

/**
 * @brief Allocate room for a number of pointers.
 * @param size Capacity to allocate.
 */
LibPointerList::LibPointerList(s32 size)
{
    items = 0;
    capacity = 0;
    reserve(size);
}

/** @brief Copy one aligned 16-byte value. @param output Destination value. @param input Source value. */
void func_00479090(void* output, const void* input)
{
    *(unsigned __int128*)output = *(const unsigned __int128*)input;
}

/**
 * @brief Set a vector to (x, y, z, 1).
 * @param vector Vector to set.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @return The vector.
 */
LibFloat4* func_004790A0(LibFloat4* vector, float x, float y, float z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
    vector->w = 1.0f;
    return vector;
}

/**
 * @brief Set the inherited transform dirty flag.
 * @param object Transform receiver.
 * @param value Dirty flag to store.
 */
void lib_transform_set_dirty(void* object, u8 value)
{
    ((LibTransformByteState*)object)->transform_dirty = value;
}

void func_004790D0(unsigned __int128* first, unsigned __int128* second, const unsigned __int128* source)
{
    unsigned __int128 value = *source;
    *second = value;
    *first = value;
}

/**
 * @brief Set the four components of a vector.
 * @param vector Vector to set.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 * @return The vector.
 */
LibFloat4* func_004790E0(LibFloat4* vector, float x, float y, float z, float w)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
    vector->w = w;
    return vector;
}

/**
 * @brief Return the target.
 * @return Target position.
 */
FieldVec4B* LibClass175430::func_00479100()
{
    return &target;
}

/**
 * @brief Set the target and point the translation from the base position at it.
 * @param x Target x.
 * @param y Target y.
 * @param z Target z.
 */
void LibClass175430::set_translation(float x, float y, float z)
{
    target.x = x;
    target.y = y;
    target.z = z;
    lib_set_translation(this, x - base.x, y - base.y, z - base.z);
}

void func_00479160(void* object, u8 value)
{
    LibFlagState59C* receiver = (LibFlagState59C*)object;
    receiver->unk59c = value;
    receiver->unk59d_0 = 1;
}

/** Increment the byte at receiver offset 0x790. */
void func_00479180(void* object)
{
    LibByte790Counter* receiver = (LibByte790Counter*)object;
    receiver->unk790 = (u8)(receiver->unk790 + 1);
}

/**
 * @brief Release the scene's entries unless it keeps them, then free its data unless it's borrowed.
 * @param scene Scene.
 */
static inline void lib_scene_release_data(LibEntryManager* scene)
{
    if (!scene->unk9D)
    {
        lib_scene_release_entries(scene);
    }

    if (!scene->data_borrowed)
    {
        delete scene->data;
    }
}

/**
 * @brief Replace the scene's data with already decoded data it doesn't own.
 * @param scene Scene.
 * @param data Decoded scene resource.
 */
void lib_scene_use_data(LibEntryManager* scene, u8* data)
{
    lib_scene_release_data(scene);
    scene->data_borrowed = 1;
    scene->data = data;
}

/**
 * @brief Replace the scene's data by decoding a scene resource into a buffer the scene owns.
 * @param scene Scene.
 * @param source Compressed scene resource.
 */
void lib_scene_load_data(LibEntryManager* scene, ResidentResourceHeader* source)
{
    u8* buffer;

    lib_scene_release_data(scene);
    scene->data_borrowed = 0;
    buffer = resident_allocate_decode_buffer(g_resident_resource_decoder, source, 0, 1);

    if (buffer)
    {
        resident_decode_resource_block(g_resident_resource_decoder, source, (void*)RESIDENT_ALIGN_RESOURCE(buffer), 0);
        scene->data = buffer;
    }
}

/** @brief Release the entries unless the scene keeps them, queue unborrowed data for release, then destroy the list object. */
LibScene::~LibScene()
{
    if (!unk9D)
    {
        lib_scene_release_entries(this);
    }

    if (!data_borrowed)
    {
        resident_queue_allocation_release(g_resident_release_queues, data);
    }
}

/** @brief Start with no data, entries or slot objects. */
LibScene::LibScene()
{
    s32 slot;

    data = 0;
    entries = 0;
    data_borrowed = 0;
    cached_entry_index = 0;
    unk9D = 0;

    for (slot = 0; slot < LIB_ENTRY_MANAGER_SLOT_COUNT; slot++)
    {
        unk34[slot] = 0;
        unk9f[slot] = 0;
    }

    linked = 0;
    unk9E = 0;
}

/** @brief Destroy the list. */
LibClass175360::~LibClass175360()
{
}

/** @brief Destroy the list. */
LibClass175370::~LibClass175370()
{
}

/** @brief Destroy the transform. */
LibClass1753A0::~LibClass1753A0()
{
}

/** @brief Destroy the model. */
LibClass175430::~LibClass175430()
{
}

/**
 * @brief Set the target and point the translation from the base position at it.
 * @param value Target; its w becomes the translation's w.
 */
void LibClass175430::copy_translation(const LibVector4* value)
{
    target = *reinterpret_cast<const FieldVec4B*>(value);

    LibVector4 offset;
    offset.x = value->x - base.x;
    offset.y = value->y - base.y;
    offset.z = value->z - base.z;
    offset.w = value->w;
    transform_dirty = 1;
    copy_vector(&translation, &offset);
}

/**
 * @brief Set the target and point the translation from the base position at it.
 * @param value Target; its w becomes the translation's w.
 */
void LibClass175430::set_translation_vector(const LibVector4* value)
{
    LibVector4 offset;
    offset.x = value->x - base.x;
    offset.y = value->y - base.y;
    offset.z = value->z - base.z;
    offset.w = value->w;
    target = *reinterpret_cast<const FieldVec4B*>(value);
    transform_dirty = 1;
    copy_vector(&translation, &offset);
}


/** @brief Free the buffer unless it is borrowed, then destroy the transform. */
LibClass175530::~LibClass175530()
{
    if (!unk254)
    {
        delete unk250;
    }
}

/** @brief Destroy the grid. */
LibClass1755C0::~LibClass1755C0()
{
}

s32 func_00479840(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass175690::~LibClass175690()
{
}

/** @brief Destroy the grid. */
LibClass175830::~LibClass175830()
{
}

s32 func_00479950(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass1759D0::~LibClass1759D0()
{
}

s32 func_004799E0(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass175C40::~LibClass175C40()
{
}

/** @brief Destroy the grid. */
LibClass175EB0::~LibClass175EB0()
{
}

s32 func_00479AF0(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass176120::~LibClass176120()
{
}

/** @brief Destroy the grid. */
LibClass176390::~LibClass176390()
{
}

s32 func_00479C00(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass176600::~LibClass176600()
{
}

/**
 * @brief Test whether the source byte at receiver offset 0xA0 isn't 1.
 * @param object Receiver.
 * @return Nonzero unless the source byte is 1.
 */
s32 func_00479C90(const ByteSourceStateOwnertext_0046AE20* object)
{
    return *object->sourceA0 != 1;
}

/** @brief Destroy the grid. */
LibClass1767A0::~LibClass1767A0()
{
}

/**
 * @brief Test whether the source byte at receiver offset 0xA0 isn't 1.
 * @param object Receiver.
 * @return Nonzero unless the source byte is 1.
 */
s32 func_00479D30(const ByteSourceStateOwnertext_0046AE20* object)
{
    return *object->sourceA0 != 1;
}

/** @brief Destroy the grid. */
LibClass176A10::~LibClass176A10()
{
}

s32 func_00479DD0(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass176BB0::~LibClass176BB0()
{
}

s32 func_00479E60(void* object)
{
    return 0;
}

/** @brief Destroy the grid. */
LibClass176D50::~LibClass176D50()
{
}

/**
 * @brief Append a key and an optional value to a fixed-capacity keyed list; full lists ignore it.
 * @param list List to append to.
 * @param key Key byte.
 * @param value Value to copy, or null to leave the slot's value unchanged.
 */
void func_00479EF0(LibKeyedVectorList* list, u8 key, const LibFloat4* value)
{
    if (list->count < list->capacity)
    {
        list->keys[list->count] = key;

        if (value)
        {
            *(unsigned __int128*)&list->values[list->count] = *(const unsigned __int128*)value;
        }

        list->count++;
    }
}

/**
 * @brief Append a key and an optional value to a fixed-capacity keyed list; full lists ignore it.
 * @param list List to append to.
 * @param key Key byte.
 * @param value Value to copy, or null to leave the slot's value unchanged.
 */
void func_00479F50(LibKeyedVectorList* list, u8 key, const LibFloat4* value)
{
    if (list->count < list->capacity)
    {
        list->keys[list->count] = key;

        if (value)
        {
            *(unsigned __int128*)&list->values[list->count] = *(const unsigned __int128*)value;
        }

        list->count++;
    }
}

void func_00479FB0(void* object)
{
}

s32 func_00479FC0(void* object)
{
    return 1;
}

/** Store the word at receiver offset 0xB8. */
void func_00479FD0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = (WordSetterOwnertext_0046AE20*)object;
    receiver->unkb8 = value;
}

/** Return the word at receiver offset 0xB8. */
u32 func_00479FE0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unkb8;
}

/** Store the word at receiver offset 0xBC. */
void func_00479FF0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = (WordSetterOwnertext_0046AE20*)object;
    receiver->unkbc = value;
}

/** Return the word at receiver offset 0xBC. */
u32 func_0047A000(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = (const WordGetterOwnertext_0046AE20*)object;
    return receiver->unkbc;
}

void func_0047A010(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8)
{
    u8* state = (u8*)cell;
    state[0x130] = 0;
    state[0x132] = 0;
    state[0x131] = 0;
    state[0x133] = 0;
    func_0047A130(object, cell, row, index, extra4, extra5, extra6, extra7, extra8);
}
