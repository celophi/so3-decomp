#include "include_asm.h"
#include "overlays/lib/init.h"

/** C view of a LibPacketBuffer: its ResidentPacket fields, then the vtable pointer. */
typedef struct LibPacketBufferStorage
{
    u32 unk00;
    u32 unk04;
    u8 unk08[0xD];
    u8 unk15;
    u8 unk16[2];
    void* vtable;
} LibPacketBufferStorage;

void __construct_array(void* array, void* constructor, void* destructor, u32 size, u32 count);

void __register_global_object(void* object, void* destructor, void* registration);

void __ct__19LibClass173490EntryFv(void);

void __dt__15LibPacketBufferFv(void);

void resident_packet_allocate(void* packet, s32 quadwords);

extern char D_00173F68[];
extern void* D_001B6544;
extern float D_00508230[8];
extern u8 D_00508250[];
extern u8 D_0050A250[];
extern float D_0050CAD0[4];
extern float D_0050CC40[];
extern float D_0050CC50[];
extern float D_0050CC54[];
extern float D_0050CC58[];
extern float D_0050CC5C[];
extern float D_0050CC60[];
extern float D_0050CC64[];
extern float D_0050CC68[];
extern float D_0050CC6C[];
extern float D_0050CC70[];
extern float D_0050CC74[];
extern float D_0050CC78[];
extern float D_0050CC7C[];
extern float D_0050CC80[];
extern float D_0050CC90[];
extern float D_0050CC94[];
extern float D_0050CC98[];
extern float D_0050CC9C[];
extern float D_0050CCA0[];
extern float D_0050CCA4[];
extern float D_0050CCA8[];
extern float D_0050CCAC[];
extern float D_0050CCB0[];
extern float D_0050CCB4[];
extern float D_0050CCB8[];
extern float D_0050CCBC[];
extern float g_default_bounding_sphere[4];
extern s32 D_0050CD40[4];
extern LibPacketBufferStorage D_0050CD60;
extern u8 D_0050CD50[];
extern void* __vt__15LibPacketBuffer[];
extern float D_0050CD80[4];

/** @brief Point D_001B6544 at D_00173F68. */
void func_00507560(void)
{
    D_001B6544 = D_00173F68;
}

/** @brief Set both D_00508230 vectors to the origin with a w of 1e30. */
void func_00507570(void)
{
    D_00508230[0] = 0.0f;
    D_00508230[1] = 0.0f;
    D_00508230[2] = 0.0f;
    D_00508230[3] = 1e30f;
    D_00508230[4] = 0.0f;
    D_00508230[5] = 0.0f;
    D_00508230[6] = 0.0f;
    D_00508230[7] = 1e30f;
}

/** @brief Construct the two 512-entry LibClass173490Entry pools. */
void func_005075C0(void)
{
    __construct_array(D_00508250, __ct__19LibClass173490EntryFv, 0, 0x10, 0x200);
    __construct_array(D_0050A250, __ct__19LibClass173490EntryFv, 0, 0x10, 0x200);
}

void func_00507620(void* object)
{
}

void func_00507630(void* object)
{
}

/** @brief Set D_0050CAD0 to (0, 0, -1, 1). */
void func_00507640(void)
{
    D_0050CAD0[0] = 0.0f;
    D_0050CAD0[1] = 0.0f;
    D_0050CAD0[2] = -1.0f;
    D_0050CAD0[3] = 1.0f;
}

void func_00507670(void* object)
{
}

void func_00507680(void* object)
{
}

/** @brief Fill in Lib's trigonometry constants and polynomial coefficients. */
void func_00507690(void)
{
    D_0050CC40[0] = 3.1415925f;
    D_0050CC40[1] = 1.5707963f;
    D_0050CC40[2] = 7.5497894e-08f;
    D_0050CC40[3] = 0.16666667f;
    D_0050CC50[0] = -0.32556581f;
    D_0050CC54[0] = 0.20121253f;
    D_0050CC58[0] = -0.040055536f;
    D_0050CC5C[0] = 0.000791535f;
    D_0050CC60[0] = 3.479331e-05f;
    D_0050CC64[0] = -2.403395f;
    D_0050CC68[0] = 2.0209458f;
    D_0050CC6C[0] = -0.688284f;
    D_0050CC70[0] = 0.077038154f;
    D_0050CC74[0] = 0.5f;
    D_0050CC78[0] = 2.0f;
    D_0050CC7C[0] = 0.0f;
    D_0050CC80[0] = 3.1415927f;
    D_0050CC80[1] = 0.31830987f;
    D_0050CC80[2] = -0.16666667f;
    D_0050CC80[3] = 0.008333334f;
    D_0050CC90[0] = -0.0001984127f;
    D_0050CC94[0] = 2.7557314e-06f;
    D_0050CC98[0] = 0.0f;
    D_0050CC9C[0] = 0.0f;
    D_0050CCA0[0] = 1.5707964f;
    D_0050CCA4[0] = 0.63661975f;
    D_0050CCA8[0] = 1.5707964f;
    D_0050CCAC[0] = 1.5707964f;
    D_0050CCB0[0] = -2.505076e-08f;
    D_0050CCB4[0] = 1.589691e-10f;
    D_0050CCB8[0] = 0.0f;
    D_0050CCBC[0] = 0.0f;
}

/** @brief Set the default bounding sphere to the origin with a radius of one million. */
void func_00507850(void)
{
    g_default_bounding_sphere[0] = 0.0f;
    g_default_bounding_sphere[1] = 0.0f;
    g_default_bounding_sphere[2] = 0.0f;
    g_default_bounding_sphere[3] = 1000000.0f;
}

/** @brief Clear D_0050CD40. */
void func_00507880(void)
{
    D_0050CD40[3] = 0;
    D_0050CD40[2] = 0;
    D_0050CD40[1] = 0;
    D_0050CD40[0] = 0;
}

/** @brief Construct the 64-quadword LibPacketBuffer D_0050CD60 and register its destructor. */
void func_005078B0(void)
{
    D_0050CD60.vtable = __vt__15LibPacketBuffer;
    D_0050CD60.unk04 = 0;
    D_0050CD60.unk15 = 0;
    resident_packet_allocate(&D_0050CD60, 0x40);
    __register_global_object(&D_0050CD60, __dt__15LibPacketBufferFv, D_0050CD50);
}

void func_00507910(void* object)
{
}

/** @brief Set every component of D_0050CD80 to 100000. */
void func_00507920(void)
{
    D_0050CD80[0] = 100000.0f;
    D_0050CD80[1] = 100000.0f;
    D_0050CD80[2] = 100000.0f;
    D_0050CD80[3] = 100000.0f;
}
