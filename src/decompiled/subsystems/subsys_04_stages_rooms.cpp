// ============================================================================
// P.N.03 (GPNE08) Full-ISA Zero-Truncation Static Recompilation Unit: subsys_04_stages_rooms.cpp
// Functions in this translation unit: 182
// ============================================================================
#include "pn03_ppc_context.hpp"
#include "pn03_symbols.hpp"
#include "pn03_all_forwards.hpp"

namespace pn03::recomp {

// [0x800A79E4] cObj00::FREE_ON(unsigned long) (obj00.obj, 9 insns / 0x24 bytes)
void cObj00__FREE_ON_800A79E4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A79E4 */ ctx.rlwinm(11, 4, 29u, 3u, 29u, false); // rlwinm r11, r4, 29, 3, 29
    /* 0x800A79E8 */ ctx.r[3] = ctx.r[3] + (1212); // addi r3, r3, 1212
    /* 0x800A79EC */ ctx.r[9] = mem.read_u32(ctx.r[11] + ctx.r[3]); // lwzx r9, r11, r3
    /* 0x800A79F0 */ ctx.rlwinm(4, 4, 0u, 27u, 31u, false); // rlwinm r4, r4, 0, 27, 31
    /* 0x800A79F4 */ ctx.r[0] = 0x80000000u; // lis r0, 0x8000
    /* 0x800A79F8 */ ctx.r[0] = (ctx.r[4] & 32u) ? 0u : (ctx.r[0] >> (ctx.r[4] & 31u)); // srw r0, r0, r4
    /* 0x800A79FC */ ctx.r[9] = ctx.r[9] | ctx.r[0]; // or r9, r9, r0
    /* 0x800A7A00 */ mem.write_u32(ctx.r[11] + ctx.r[3], ctx.r[9]); // stwx r9, r11, r3
    /* 0x800A7A04 */ return; // blr
}

// [0x800A7A08] cObj00::FREE_OFF(unsigned long) (obj00.obj, 9 insns / 0x24 bytes)
void cObj00__FREE_OFF_800A7A08(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7A08 */ ctx.rlwinm(11, 4, 29u, 3u, 29u, false); // rlwinm r11, r4, 29, 3, 29
    /* 0x800A7A0C */ ctx.r[3] = ctx.r[3] + (1212); // addi r3, r3, 1212
    /* 0x800A7A10 */ ctx.r[9] = mem.read_u32(ctx.r[11] + ctx.r[3]); // lwzx r9, r11, r3
    /* 0x800A7A14 */ ctx.rlwinm(4, 4, 0u, 27u, 31u, false); // rlwinm r4, r4, 0, 27, 31
    /* 0x800A7A18 */ ctx.r[0] = 0x80000000u; // lis r0, 0x8000
    /* 0x800A7A1C */ ctx.r[0] = (ctx.r[4] & 32u) ? 0u : (ctx.r[0] >> (ctx.r[4] & 31u)); // srw r0, r0, r4
    /* 0x800A7A20 */ ctx.r[0] = ctx.r[9] & ~ctx.r[0]; // andc r0, r9, r0
    /* 0x800A7A24 */ mem.write_u32(ctx.r[11] + ctx.r[3], ctx.r[0]); // stwx r0, r11, r3
    /* 0x800A7A28 */ return; // blr
}

// [0x800A7A2C] cObj00::FREE_CK(unsigned long) (obj00.obj, 8 insns / 0x20 bytes)
void cObj00__FREE_CK_800A7A2C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7A2C */ ctx.r[3] = ctx.r[3] + (1212); // addi r3, r3, 1212
    /* 0x800A7A30 */ ctx.rlwinm(9, 4, 29u, 3u, 29u, false); // rlwinm r9, r4, 29, 3, 29
    /* 0x800A7A34 */ ctx.r[0] = mem.read_u32(ctx.r[9] + ctx.r[3]); // lwzx r0, r9, r3
    /* 0x800A7A38 */ ctx.rlwinm(4, 4, 0u, 27u, 31u, false); // rlwinm r4, r4, 0, 27, 31
    /* 0x800A7A3C */ ctx.r[3] = 0x80000000u; // lis r3, 0x8000
    /* 0x800A7A40 */ ctx.r[3] = (ctx.r[4] & 32u) ? 0u : (ctx.r[3] >> (ctx.r[4] & 31u)); // srw r3, r3, r4
    /* 0x800A7A44 */ ctx.r[3] = ctx.r[0] & ctx.r[3]; // and r3, r0, r3
    /* 0x800A7A48 */ return; // blr
}

// [0x800A7A4C] cObj00::cObj00(void) (obj00.obj, 21 insns / 0x54 bytes)
void cObj00__cObj00_800A7A4C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7A4C */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800A7A50 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A7A54 */ ctx.stmw(mem, 30, ctx.r[1] + (8)); // stmw r30, 8(r1)
    /* 0x800A7A58 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800A7A5C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800A7A60 */ cObj__cObj_80074A98(ctx, mem); // bl 0x80074A98 <cObj::cObj(void)>
    /* 0x800A7A64 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A7A68 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800A7A6C */ ctx.r[9] = ctx.r[9] + (-15432); // addi r9, r9, -15432 -> cObj00 virtual table
    /* 0x800A7A70 */ mem.write_u32(ctx.r[30] + (1228), ctx.r[0]); // stw r0, 1228(r30)
    /* 0x800A7A74 */ mem.write_u32(ctx.r[30] + (1208), ctx.r[9]); // stw r9, 1208(r30)
    /* 0x800A7A78 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A7A7C */ mem.write_u32(ctx.r[30] + (1212), ctx.r[0]); // stw r0, 1212(r30)
    /* 0x800A7A80 */ mem.write_u32(ctx.r[30] + (1216), ctx.r[0]); // stw r0, 1216(r30)
    /* 0x800A7A84 */ mem.write_u32(ctx.r[30] + (1220), ctx.r[0]); // stw r0, 1220(r30)
    /* 0x800A7A88 */ mem.write_u32(ctx.r[30] + (1224), ctx.r[0]); // stw r0, 1224(r30)
    /* 0x800A7A8C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800A7A90 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A7A94 */ ctx.lmw(mem, 30, ctx.r[1] + (8)); // lmw r30, 8(r1)
    /* 0x800A7A98 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800A7A9C */ return; // blr
}

// [0x800A7AA0] cObj00::Main(void) (obj00.obj, 101 insns / 0x194 bytes)
void cObj00__Main_800A7AA0(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7AA0 */ ctx.r[1] += (-32); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -32(r1)
    /* 0x800A7AA4 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A7AA8 */ ctx.stmw(mem, 30, ctx.r[1] + (24)); // stmw r30, 24(r1)
    /* 0x800A7AAC */ mem.write_u32(ctx.r[1] + (36), ctx.r[0]); // stw r0, 36(r1)
    /* 0x800A7AB0 */ ctx.r[31] = ctx.r[3]; // mr r31, r3
    /* 0x800A7AB4 */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800A7AB8 */ cObj00__FREE_CK_800A7A2C(ctx, mem); // bl 0x800A7A2C <cObj00::FREE_CK(unsigned long)>
    /* 0x800A7ABC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800A7AC0 */ if (ctx.eval_bc(12, 2)) goto loc_800A7AFC; // bc 12, 2, 0x800A7AFC
    /* 0x800A7AC4 */ ctx.r[5] = mem.read_u32(ctx.r[31] + (1216)); // lwz r5, 1216(r31)
    /* 0x800A7AC8 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7ACC */ ctx.r[8] = mem.read_u16(ctx.r[31] + (1222)); // lhz r8, 1222(r31)
    /* 0x800A7AD0 */ ctx.r[4] = ctx.r[31] + (380); // addi r4, r31, 380
    /* 0x800A7AD4 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800A7AD8 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800A7ADC */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800A7AE0 */ MotionSetCore_800A1E20(ctx, mem); // bl 0x800A1E20 <MotionSetCore(cEm *, _MOTION_INFO *, void *, void *, unsigned char, unsigned short, unsigned short)>
    /* 0x800A7AE4 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7AE8 */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800A7AEC */ cObj00__FREE_OFF_800A7A08(ctx, mem); // bl 0x800A7A08 <cObj00::FREE_OFF(unsigned long)>
    /* 0x800A7AF0 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7AF4 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800A7AF8 */ cObj00__FREE_ON_800A79E4(ctx, mem); // bl 0x800A79E4 <cObj00::FREE_ON(unsigned long)>
loc_800A7AFC:;
    /* 0x800A7AFC */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7B00 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800A7B04 */ cObj00__FREE_CK_800A7A2C(ctx, mem); // bl 0x800A7A2C <cObj00::FREE_CK(unsigned long)>
    /* 0x800A7B08 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800A7B0C */ if (ctx.eval_bc(12, 2)) goto loc_800A7B28; // bc 12, 2, 0x800A7B28
    /* 0x800A7B10 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A7B14 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A7B18 */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-15444)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15444(r9) [0x8016C3AC]
    /* 0x800A7B1C */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7B20 */ ctx.f[2] = mem.read_f32(ctx.r[11] + (-15440)); ctx.ps0[2] = static_cast<float>(ctx.f[2]); // lfs f2, -15440(r11) [0x8016C3B0]
    /* 0x800A7B24 */ MotionMove_800A2434(ctx, mem); // bl 0x800A2434 <MotionMove(cEm *, float, float)>
loc_800A7B28:;
    /* 0x800A7B28 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7B2C */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800A7B30 */ cObj00__FREE_CK_800A7A2C(ctx, mem); // bl 0x800A7A2C <cObj00::FREE_CK(unsigned long)>
    /* 0x800A7B34 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800A7B38 */ if (ctx.eval_bc(4, 2)) goto loc_800A7BB8; // bc 4, 2, 0x800A7BB8
    /* 0x800A7B3C */ ctx.f[0] = mem.read_f32(ctx.r[31] + (204)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 204(r31)
    /* 0x800A7B40 */ ctx.r[9] = ctx.r[31] + (204); // addi r9, r31, 204
    /* 0x800A7B44 */ ctx.r[30] = ctx.r[1] + (8); // addi r30, r1, 8
    /* 0x800A7B48 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7B4C */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800A7B50 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A7B54 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A7B58 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A7B5C */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A7B60 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800A7B64 */ RotMatrix_8009E1D0(ctx, mem); // bl 0x8009E1D0 <RotMatrix(float (*)[3], cVec &)>
    /* 0x800A7B68 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r31)
    /* 0x800A7B6C */ ctx.r[9] = ctx.r[31] + (192); // addi r9, r31, 192
    /* 0x800A7B70 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7B74 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A7B78 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800A7B7C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A7B80 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A7B84 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A7B88 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800A7B8C */ TransMatrix_8009E1B4(ctx, mem); // bl 0x8009E1B4 <TransMatrix(float (*)[3], cVec &)>
    /* 0x800A7B90 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (216)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 216(r31)
    /* 0x800A7B94 */ ctx.r[9] = ctx.r[31] + (216); // addi r9, r31, 216
    /* 0x800A7B98 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A7B9C */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7BA0 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800A7BA4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A7BA8 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A7BAC */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A7BB0 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800A7BB4 */ ScaleMatrix_8009E168(ctx, mem); // bl 0x8009E168 <ScaleMatrix(float (*)[3], cVec &)>
loc_800A7BB8:;
    /* 0x800A7BB8 */ ctx.r[3] = mem.read_u32(ctx.r[31] + (1224)); // lwz r3, 1224(r31)
    /* 0x800A7BBC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800A7BC0 */ if (ctx.eval_bc(12, 2)) goto loc_800A7BE4; // bc 12, 2, 0x800A7BE4
    /* 0x800A7BC4 */ ctx.r[3] = mem.read_u32(ctx.r[3] + (240)); // lwz r3, 240(r3)
    /* 0x800A7BC8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800A7BCC */ if (ctx.eval_bc(12, 2)) goto loc_800A7BE4; // bc 12, 2, 0x800A7BE4
    /* 0x800A7BD0 */ ctx.r[4] = mem.read_u32(ctx.r[31] + (1228)); // lwz r4, 1228(r31)
    /* 0x800A7BD4 */ GetPartsAddr_800A0BD4(ctx, mem); // bl 0x800A0BD4 <GetPartsAddr(PARTS *, unsigned long)>
    /* 0x800A7BD8 */ ctx.r[4] = ctx.r[31]; // mr r4, r31
    /* 0x800A7BDC */ ctx.r[5] = ctx.r[31]; // mr r5, r31
    /* 0x800A7BE0 */ ctx.call_indirect(0x80100470u, mem); // bl 0x80100470 <PSMTXConcat>
loc_800A7BE4:;
    /* 0x800A7BE4 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7BE8 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800A7BEC */ cObj00__FREE_CK_800A7A2C(ctx, mem); // bl 0x800A7A2C <cObj00::FREE_CK(unsigned long)>
    /* 0x800A7BF0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800A7BF4 */ if (ctx.eval_bc(4, 2)) goto loc_800A7C18; // bc 4, 2, 0x800A7C18
    /* 0x800A7BF8 */ ctx.r[3] = mem.read_u32(ctx.r[31] + (240)); // lwz r3, 240(r31)
    /* 0x800A7BFC */ ModelMatCalc_800A0BF4(ctx, mem); // bl 0x800A0BF4 <ModelMatCalc(PARTS *)>
    /* 0x800A7C00 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A7C04 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A7C08 */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-15444)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15444(r9) [0x8016C3AC]
    /* 0x800A7C0C */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7C10 */ ctx.f[2] = mem.read_f32(ctx.r[11] + (-15440)); ctx.ps0[2] = static_cast<float>(ctx.f[2]); // lfs f2, -15440(r11) [0x8016C3B0]
    /* 0x800A7C14 */ InverseKinematics_800999AC(ctx, mem); // bl 0x800999AC <InverseKinematics(cEm *, float, float)>
loc_800A7C18:;
    /* 0x800A7C18 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7C1C */ PartsWorldCalc_800A0E5C(ctx, mem); // bl 0x800A0E5C <PartsWorldCalc(cEm *)>
    /* 0x800A7C20 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (36)); // lwz r0, 36(r1)
    /* 0x800A7C24 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A7C28 */ ctx.lmw(mem, 30, ctx.r[1] + (24)); // lmw r30, 24(r1)
    /* 0x800A7C2C */ ctx.r[1] = ctx.r[1] + (32); // addi r1, r1, 32
    /* 0x800A7C30 */ return; // blr
}

// [0x800A7C34] cObj00::Release(void) (obj00.obj, 8 insns / 0x20 bytes)
void cObj00__Release_800A7C34(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7C34 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800A7C38 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A7C3C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800A7C40 */ PushObj_800749C8(ctx, mem); // bl 0x800749C8 <PushObj(cObj *)>
    /* 0x800A7C44 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800A7C48 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A7C4C */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800A7C50 */ return; // blr
}

// [0x800A7C54] cObj00::MotSetObj00(void *, unsigned long) (obj00.obj, 12 insns / 0x30 bytes)
void cObj00__MotSetObj00_800A7C54(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7C54 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800A7C58 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A7C5C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800A7C60 */ ctx.r[9] = ctx.r[3]; // mr r9, r3
    /* 0x800A7C64 */ mem.write_u32(ctx.r[9] + (1216), ctx.r[4]); // stw r4, 1216(r9)
    /* 0x800A7C68 */ mem.write_u32(ctx.r[9] + (1220), ctx.r[5]); // stw r5, 1220(r9)
    /* 0x800A7C6C */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800A7C70 */ cObj00__FREE_ON_800A79E4(ctx, mem); // bl 0x800A79E4 <cObj00::FREE_ON(unsigned long)>
    /* 0x800A7C74 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800A7C78 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A7C7C */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800A7C80 */ return; // blr
}

// [0x800A7C84] cObj00::OyaSetObj00(cEm *, unsigned long) (obj00.obj, 3 insns / 0xC bytes)
void cObj00__OyaSetObj00_800A7C84(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7C84 */ mem.write_u32(ctx.r[3] + (1228), ctx.r[5]); // stw r5, 1228(r3)
    /* 0x800A7C88 */ mem.write_u32(ctx.r[3] + (1224), ctx.r[4]); // stw r4, 1224(r3)
    /* 0x800A7C8C */ return; // blr
}

// [0x800A7C90] SetObj00(unsigned long, unsigned long, cVec &, cVec &) (obj00.obj, 53 insns / 0xD4 bytes)
void SetObj00_800A7C90(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7C90 */ ctx.r[1] += (-32); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -32(r1)
    /* 0x800A7C94 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A7C98 */ ctx.stmw(mem, 27, ctx.r[1] + (12)); // stmw r27, 12(r1)
    /* 0x800A7C9C */ mem.write_u32(ctx.r[1] + (36), ctx.r[0]); // stw r0, 36(r1)
    /* 0x800A7CA0 */ ctx.r[29] = ctx.r[3]; // mr r29, r3
    /* 0x800A7CA4 */ ctx.r[28] = ctx.r[4]; // mr r28, r4
    /* 0x800A7CA8 */ ctx.r[30] = ctx.r[5]; // mr r30, r5
    /* 0x800A7CAC */ ctx.r[27] = ctx.r[6]; // mr r27, r6
    /* 0x800A7CB0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A7CB4 */ PullObj_80074784(ctx, mem); // bl 0x80074784 <PullObj(long)>
    /* 0x800A7CB8 */ ctx.r[31] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // mr r31, r3
    /* 0x800A7CBC */ if (ctx.eval_bc(12, 2)) goto loc_800A7D4C; // bc 12, 2, 0x800A7D4C
    /* 0x800A7CC0 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800A7CC4 */ ctx.r[5] = ctx.r[28]; // mr r5, r28
    /* 0x800A7CC8 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7CCC */ cObj__ModelInit_80074D30(ctx, mem); // bl 0x80074D30 <cObj::ModelInit(unsigned long, unsigned long)>
    /* 0x800A7CD0 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (244)); // lwz r0, 244(r31)
    /* 0x800A7CD4 */ ctx.r[4] = 0x80170000u; // lis r4, 0x8017
    /* 0x800A7CD8 */ ctx.r[4] = ctx.r[4] + (10500); // addi r4, r4, 10500 -> Obj_at_light
    /* 0x800A7CDC */ ctx.r[3] = ctx.r[31] + (312); // addi r3, r31, 312
    /* 0x800A7CE0 */ ctx.rlwinm(0, 0, 0u, 30u, 27u, false); // rlwinm r0, r0, 0, 30, 27
    /* 0x800A7CE4 */ ctx.r[5] = 0x00000004u; // li r5, 4
    /* 0x800A7CE8 */ mem.write_u32(ctx.r[31] + (244), ctx.r[0]); // stw r0, 244(r31)
    /* 0x800A7CEC */ LightInfoInit_8009AF88(ctx, mem); // bl 0x8009AF88 <LightInfoInit(tagLIGHT_INFO *, tagATARI_INFO *, unsigned char)>
    /* 0x800A7CF0 */ ctx.r[11] = mem.read_u32(ctx.r[30] + (0)); // lwz r11, 0(r30)
    /* 0x800A7CF4 */ ctx.r[9] = ctx.r[31] + (192); // addi r9, r31, 192
    /* 0x800A7CF8 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (8)); // lwz r0, 8(r30)
    /* 0x800A7CFC */ ctx.r[8] = ctx.r[31] + (268); // addi r8, r31, 268
    /* 0x800A7D00 */ ctx.r[10] = mem.read_u32(ctx.r[30] + (4)); // lwz r10, 4(r30)
    /* 0x800A7D04 */ ctx.r[7] = ctx.r[31] + (204); // addi r7, r31, 204
    /* 0x800A7D08 */ mem.write_u32(ctx.r[31] + (192), ctx.r[11]); // stw r11, 192(r31)
    /* 0x800A7D0C */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7D10 */ mem.write_u32(ctx.r[9] + (8), ctx.r[0]); // stw r0, 8(r9)
    /* 0x800A7D14 */ mem.write_u32(ctx.r[9] + (4), ctx.r[10]); // stw r10, 4(r9)
    /* 0x800A7D18 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (0)); // lwz r0, 0(r30)
    /* 0x800A7D1C */ ctx.r[9] = mem.read_u32(ctx.r[30] + (8)); // lwz r9, 8(r30)
    /* 0x800A7D20 */ ctx.r[11] = mem.read_u32(ctx.r[30] + (4)); // lwz r11, 4(r30)
    /* 0x800A7D24 */ mem.write_u32(ctx.r[31] + (268), ctx.r[0]); // stw r0, 268(r31)
    /* 0x800A7D28 */ mem.write_u32(ctx.r[8] + (8), ctx.r[9]); // stw r9, 8(r8)
    /* 0x800A7D2C */ mem.write_u32(ctx.r[8] + (4), ctx.r[11]); // stw r11, 4(r8)
    /* 0x800A7D30 */ ctx.r[0] = mem.read_u32(ctx.r[27] + (0)); // lwz r0, 0(r27)
    /* 0x800A7D34 */ ctx.r[9] = mem.read_u32(ctx.r[27] + (8)); // lwz r9, 8(r27)
    /* 0x800A7D38 */ ctx.r[11] = mem.read_u32(ctx.r[27] + (4)); // lwz r11, 4(r27)
    /* 0x800A7D3C */ mem.write_u32(ctx.r[31] + (204), ctx.r[0]); // stw r0, 204(r31)
    /* 0x800A7D40 */ mem.write_u32(ctx.r[7] + (8), ctx.r[9]); // stw r9, 8(r7)
    /* 0x800A7D44 */ mem.write_u32(ctx.r[7] + (4), ctx.r[11]); // stw r11, 4(r7)
    /* 0x800A7D48 */ goto loc_800A7D50; // b 0x800A7D50 <sub_800A7D50>
loc_800A7D4C:;
    /* 0x800A7D4C */ ctx.r[3] = 0x00000000u; // li r3, 0
loc_800A7D50:;
    /* 0x800A7D50 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (36)); // lwz r0, 36(r1)
    /* 0x800A7D54 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A7D58 */ ctx.lmw(mem, 27, ctx.r[1] + (12)); // lmw r27, 12(r1)
    /* 0x800A7D5C */ ctx.r[1] = ctx.r[1] + (32); // addi r1, r1, 32
    /* 0x800A7D60 */ return; // blr
}

// [0x800A7D64] cObj00::~cObj00(void) (obj00.obj, 8 insns / 0x20 bytes)
void cObj00_dtor_cObj00_800A7D64(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7D64 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800A7D68 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A7D6C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800A7D70 */ cObj_dtor_cObj_80074AD8(ctx, mem); // bl 0x80074AD8 <cObj::~cObj(void)>
    /* 0x800A7D74 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800A7D78 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A7D7C */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800A7D80 */ return; // blr
}

// [0x800A7D84] cObj00::Initialize(void) (obj00.obj, 1 insns / 0x4 bytes)
void cObj00__Initialize_800A7D84(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7D84 */ return; // blr
}

// [0x800A7D88] cObj02::Main(void) (obj02.obj, 63 insns / 0xFC bytes)
void cObj02__Main_800A7D88(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7D88 */ ctx.r[1] += (-32); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -32(r1)
    /* 0x800A7D8C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A7D90 */ ctx.stmw(mem, 30, ctx.r[1] + (24)); // stmw r30, 24(r1)
    /* 0x800A7D94 */ mem.write_u32(ctx.r[1] + (36), ctx.r[0]); // stw r0, 36(r1)
    /* 0x800A7D98 */ ctx.r[31] = ctx.r[3]; // mr r31, r3
    /* 0x800A7D9C */ ctx.r[0] = mem.read_u32(ctx.r[31] + (1212)); // lwz r0, 1212(r31)
    /* 0x800A7DA0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 2); // cmpwi cr0, r0, 2
    /* 0x800A7DA4 */ if (ctx.eval_bc(12, 2)) goto loc_800A7DD0; // bc 12, 2, 0x800A7DD0
    /* 0x800A7DA8 */ if (ctx.eval_bc(12, 1)) goto loc_800A7DB8; // bc 12, 1, 0x800A7DB8
    /* 0x800A7DAC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 1); // cmpwi cr0, r0, 1
    /* 0x800A7DB0 */ if (ctx.eval_bc(12, 2)) goto loc_800A7DC4; // bc 12, 2, 0x800A7DC4
    /* 0x800A7DB4 */ goto loc_800A7DE4; // b 0x800A7DE4 <sub_800A7DE4>
loc_800A7DB8:;
    /* 0x800A7DB8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 3); // cmpwi cr0, r0, 3
    /* 0x800A7DBC */ if (ctx.eval_bc(12, 2)) goto loc_800A7DDC; // bc 12, 2, 0x800A7DDC
    /* 0x800A7DC0 */ goto loc_800A7DE4; // b 0x800A7DE4 <sub_800A7DE4>
loc_800A7DC4:;
    /* 0x800A7DC4 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7DC8 */ cObj02__swing_rot_800A7EB4(ctx, mem); // bl 0x800A7EB4 <cObj02::swing_rot(void)>
    /* 0x800A7DCC */ goto loc_800A7DE4; // b 0x800A7DE4 <sub_800A7DE4>
loc_800A7DD0:;
    /* 0x800A7DD0 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7DD4 */ cObj02__swing_pos_800A7F4C(ctx, mem); // bl 0x800A7F4C <cObj02::swing_pos(void)>
    /* 0x800A7DD8 */ goto loc_800A7DE4; // b 0x800A7DE4 <sub_800A7DE4>
loc_800A7DDC:;
    /* 0x800A7DDC */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7DE0 */ cObj02__rotate_800A7E84(ctx, mem); // bl 0x800A7E84 <cObj02::rotate(void)>
loc_800A7DE4:;
    /* 0x800A7DE4 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (204)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 204(r31)
    /* 0x800A7DE8 */ ctx.r[9] = ctx.r[31] + (204); // addi r9, r31, 204
    /* 0x800A7DEC */ ctx.r[30] = ctx.r[1] + (8); // addi r30, r1, 8
    /* 0x800A7DF0 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7DF4 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800A7DF8 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A7DFC */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A7E00 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A7E04 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A7E08 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800A7E0C */ RotMatrix_8009E1D0(ctx, mem); // bl 0x8009E1D0 <RotMatrix(float (*)[3], cVec &)>
    /* 0x800A7E10 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r31)
    /* 0x800A7E14 */ ctx.r[9] = ctx.r[31] + (192); // addi r9, r31, 192
    /* 0x800A7E18 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7E1C */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A7E20 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800A7E24 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A7E28 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A7E2C */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A7E30 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800A7E34 */ TransMatrix_8009E1B4(ctx, mem); // bl 0x8009E1B4 <TransMatrix(float (*)[3], cVec &)>
    /* 0x800A7E38 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (216)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 216(r31)
    /* 0x800A7E3C */ ctx.r[9] = ctx.r[31] + (216); // addi r9, r31, 216
    /* 0x800A7E40 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A7E44 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7E48 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800A7E4C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A7E50 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A7E54 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A7E58 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800A7E5C */ ScaleMatrix_8009E168(ctx, mem); // bl 0x8009E168 <ScaleMatrix(float (*)[3], cVec &)>
    /* 0x800A7E60 */ ctx.r[3] = mem.read_u32(ctx.r[31] + (240)); // lwz r3, 240(r31)
    /* 0x800A7E64 */ ModelMatCalc_800A0BF4(ctx, mem); // bl 0x800A0BF4 <ModelMatCalc(PARTS *)>
    /* 0x800A7E68 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A7E6C */ PartsWorldCalc_800A0E5C(ctx, mem); // bl 0x800A0E5C <PartsWorldCalc(cEm *)>
    /* 0x800A7E70 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (36)); // lwz r0, 36(r1)
    /* 0x800A7E74 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A7E78 */ ctx.lmw(mem, 30, ctx.r[1] + (24)); // lmw r30, 24(r1)
    /* 0x800A7E7C */ ctx.r[1] = ctx.r[1] + (32); // addi r1, r1, 32
    /* 0x800A7E80 */ return; // blr
}

// [0x800A7E84] cObj02::rotate(void) (obj02.obj, 12 insns / 0x30 bytes)
void cObj02__rotate_800A7E84(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7E84 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800A7E88 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A7E8C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800A7E90 */ ctx.r[0] = ctx.r[3] + (204); // addi r0, r3, 204
    /* 0x800A7E94 */ ctx.r[4] = ctx.r[3] + (1240); // addi r4, r3, 1240
    /* 0x800A7E98 */ ctx.r[3] = ctx.r[0]; // mr r3, r0
    /* 0x800A7E9C */ ctx.r[5] = ctx.r[3]; // mr r5, r3
    /* 0x800A7EA0 */ ctx.call_indirect(0x801038F4u, mem); // bl 0x801038F4 <PSVECAdd>
    /* 0x800A7EA4 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800A7EA8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A7EAC */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800A7EB0 */ return; // blr
}

// [0x800A7EB4] cObj02::swing_rot(void) (obj02.obj, 38 insns / 0x98 bytes)
void cObj02__swing_rot_800A7EB4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7EB4 */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800A7EB8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A7EBC */ ctx.stmw(mem, 30, ctx.r[1] + (8)); // stmw r30, 8(r1)
    /* 0x800A7EC0 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800A7EC4 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800A7EC8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A7ECC */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-15324)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -15324(r9) [0x8016C424]
    /* 0x800A7ED0 */ ctx.f[1] = mem.read_f32(ctx.r[30] + (1216)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 1216(r30)
    /* 0x800A7ED4 */ ctx.f[12] = mem.read_f32(ctx.r[30] + (1276)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 1276(r30)
    /* 0x800A7ED8 */ ctx.f[1] = static_cast<float>(ctx.f[1] + ctx.f[13]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fadds f1, f1, f13
    /* 0x800A7EDC */ ctx.f[0] = mem.read_f32(ctx.r[30] + (1252)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1252(r30)
    /* 0x800A7EE0 */ mem.write_f32(ctx.r[30] + (1216), static_cast<float>(ctx.f[1])); // stfs f1, 1216(r30)
    /* 0x800A7EE4 */ ctx.f[1] = static_cast<float>(ctx.f[12] * ctx.f[1] + ctx.f[0]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmadds f1, f12, f1, f0
    /* 0x800A7EE8 */ ctx.call_indirect(0x800E46B4u, mem); // bl 0x800E46B4 <sinf>
    /* 0x800A7EEC */ ctx.f[0] = mem.read_f32(ctx.r[30] + (1264)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1264(r30)
    /* 0x800A7EF0 */ ctx.f[12] = mem.read_f32(ctx.r[30] + (1280)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 1280(r30)
    /* 0x800A7EF4 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f1
    /* 0x800A7EF8 */ ctx.f[13] = mem.read_f32(ctx.r[30] + (1216)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 1216(r30)
    /* 0x800A7EFC */ ctx.f[1] = mem.read_f32(ctx.r[30] + (1256)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 1256(r30)
    /* 0x800A7F00 */ mem.write_f32(ctx.r[30] + (204), static_cast<float>(ctx.f[0])); // stfs f0, 204(r30)
    /* 0x800A7F04 */ ctx.f[1] = static_cast<float>(ctx.f[12] * ctx.f[13] + ctx.f[1]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmadds f1, f12, f13, f1
    /* 0x800A7F08 */ ctx.call_indirect(0x800E46B4u, mem); // bl 0x800E46B4 <sinf>
    /* 0x800A7F0C */ ctx.f[0] = mem.read_f32(ctx.r[30] + (1268)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1268(r30)
    /* 0x800A7F10 */ ctx.f[12] = mem.read_f32(ctx.r[30] + (1284)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 1284(r30)
    /* 0x800A7F14 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f1
    /* 0x800A7F18 */ ctx.f[13] = mem.read_f32(ctx.r[30] + (1216)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 1216(r30)
    /* 0x800A7F1C */ ctx.f[1] = mem.read_f32(ctx.r[30] + (1260)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 1260(r30)
    /* 0x800A7F20 */ mem.write_f32(ctx.r[30] + (208), static_cast<float>(ctx.f[0])); // stfs f0, 208(r30)
    /* 0x800A7F24 */ ctx.f[1] = static_cast<float>(ctx.f[12] * ctx.f[13] + ctx.f[1]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmadds f1, f12, f13, f1
    /* 0x800A7F28 */ ctx.call_indirect(0x800E46B4u, mem); // bl 0x800E46B4 <sinf>
    /* 0x800A7F2C */ ctx.f[0] = mem.read_f32(ctx.r[30] + (1272)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1272(r30)
    /* 0x800A7F30 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f1
    /* 0x800A7F34 */ mem.write_f32(ctx.r[30] + (212), static_cast<float>(ctx.f[0])); // stfs f0, 212(r30)
    /* 0x800A7F38 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800A7F3C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A7F40 */ ctx.lmw(mem, 30, ctx.r[1] + (8)); // lmw r30, 8(r1)
    /* 0x800A7F44 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800A7F48 */ return; // blr
}

// [0x800A7F4C] cObj02::swing_pos(void) (obj02.obj, 86 insns / 0x158 bytes)
void cObj02__swing_pos_800A7F4C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A7F4C */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800A7F50 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A7F54 */ mem.write_u32(ctx.r[1] + (12), ctx.r[31]); // stw r31, 12(r1)
    /* 0x800A7F58 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800A7F5C */ ctx.r[31] = ctx.r[3]; // mr r31, r3
    /* 0x800A7F60 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (248)); // lbz r0, 248(r31)
    /* 0x800A7F64 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800A7F68 */ if (ctx.eval_bc(4, 2)) goto loc_800A7F94; // bc 4, 2, 0x800A7F94
    /* 0x800A7F6C */ ctx.f[0] = mem.read_f32(ctx.r[31] + (192)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 192(r31)
    /* 0x800A7F70 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800A7F74 */ mem.write_u8(ctx.r[31] + (248), static_cast<uint8_t>(ctx.r[0])); // stb r0, 248(r31)
    /* 0x800A7F78 */ ctx.r[11] = ctx.r[31] + (192); // addi r11, r31, 192
    /* 0x800A7F7C */ mem.write_f32(ctx.r[31] + (1228), static_cast<float>(ctx.f[0])); // stfs f0, 1228(r31)
    /* 0x800A7F80 */ ctx.r[9] = ctx.r[31] + (1228); // addi r9, r31, 1228
    /* 0x800A7F84 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r11)
    /* 0x800A7F88 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r9)
    /* 0x800A7F8C */ ctx.f[13] = mem.read_f32(ctx.r[11] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r11)
    /* 0x800A7F90 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r9)
loc_800A7F94:;
    /* 0x800A7F94 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A7F98 */ ctx.f[11] = mem.read_f32(ctx.r[31] + (1216)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 1216(r31)
    /* 0x800A7F9C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-15320)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -15320(r9) [0x8016C428]
    /* 0x800A7FA0 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (1220)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 1220(r31)
    /* 0x800A7FA4 */ ctx.f[12] = mem.read_f32(ctx.r[31] + (1224)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 1224(r31)
    /* 0x800A7FA8 */ ctx.f[11] = static_cast<float>(ctx.f[11] + ctx.f[0]); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // fadds f11, f11, f0
    /* 0x800A7FAC */ ctx.f[10] = mem.read_f32(ctx.r[31] + (1276)); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // lfs f10, 1276(r31)
    /* 0x800A7FB0 */ ctx.f[13] = static_cast<float>(ctx.f[13] + ctx.f[0]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // fadds f13, f13, f0
    /* 0x800A7FB4 */ ctx.f[1] = mem.read_f32(ctx.r[31] + (1252)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 1252(r31)
    /* 0x800A7FB8 */ ctx.f[12] = static_cast<float>(ctx.f[12] + ctx.f[0]); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // fadds f12, f12, f0
    /* 0x800A7FBC */ mem.write_f32(ctx.r[31] + (1220), static_cast<float>(ctx.f[13])); // stfs f13, 1220(r31)
    /* 0x800A7FC0 */ ctx.f[1] = static_cast<float>(ctx.f[10] * ctx.f[11] + ctx.f[1]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmadds f1, f10, f11, f1
    /* 0x800A7FC4 */ mem.write_f32(ctx.r[31] + (1224), static_cast<float>(ctx.f[12])); // stfs f12, 1224(r31)
    /* 0x800A7FC8 */ mem.write_f32(ctx.r[31] + (1216), static_cast<float>(ctx.f[11])); // stfs f11, 1216(r31)
    /* 0x800A7FCC */ ctx.call_indirect(0x800E46B4u, mem); // bl 0x800E46B4 <sinf>
    /* 0x800A7FD0 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (1228)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 1228(r31)
    /* 0x800A7FD4 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (1264)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1264(r31)
    /* 0x800A7FD8 */ ctx.f[11] = mem.read_f32(ctx.r[31] + (1280)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 1280(r31)
    /* 0x800A7FDC */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A7FE0 */ ctx.f[12] = mem.read_f32(ctx.r[31] + (1220)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 1220(r31)
    /* 0x800A7FE4 */ ctx.f[1] = mem.read_f32(ctx.r[31] + (1256)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 1256(r31)
    /* 0x800A7FE8 */ mem.write_f32(ctx.r[31] + (192), static_cast<float>(ctx.f[0])); // stfs f0, 192(r31)
    /* 0x800A7FEC */ ctx.f[1] = static_cast<float>(ctx.f[11] * ctx.f[12] + ctx.f[1]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmadds f1, f11, f12, f1
    /* 0x800A7FF0 */ ctx.call_indirect(0x800E46B4u, mem); // bl 0x800E46B4 <sinf>
    /* 0x800A7FF4 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (1232)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 1232(r31)
    /* 0x800A7FF8 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (1268)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1268(r31)
    /* 0x800A7FFC */ ctx.f[11] = mem.read_f32(ctx.r[31] + (1284)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 1284(r31)
    /* 0x800A8000 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A8004 */ ctx.f[12] = mem.read_f32(ctx.r[31] + (1224)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 1224(r31)
    /* 0x800A8008 */ ctx.f[1] = mem.read_f32(ctx.r[31] + (1260)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 1260(r31)
    /* 0x800A800C */ mem.write_f32(ctx.r[31] + (196), static_cast<float>(ctx.f[0])); // stfs f0, 196(r31)
    /* 0x800A8010 */ ctx.f[1] = static_cast<float>(ctx.f[11] * ctx.f[12] + ctx.f[1]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmadds f1, f11, f12, f1
    /* 0x800A8014 */ ctx.call_indirect(0x800E46B4u, mem); // bl 0x800E46B4 <sinf>
    /* 0x800A8018 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (1272)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 1272(r31)
    /* 0x800A801C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8020 */ ctx.f[12] = mem.read_f32(ctx.r[31] + (1236)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 1236(r31)
    /* 0x800A8024 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (1276)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1276(r31)
    /* 0x800A8028 */ ctx.f[11] = mem.read_f32(ctx.r[31] + (1216)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 1216(r31)
    /* 0x800A802C */ ctx.f[13] = static_cast<float>(ctx.f[13] * ctx.f[1] + ctx.f[12]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // fmadds f13, f13, f1, f12
    /* 0x800A8030 */ ctx.f[10] = mem.read_f32(ctx.r[9] + (-15316)); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // lfs f10, -15316(r9) [0x8016C42C]
    /* 0x800A8034 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f11
    /* 0x800A8038 */ mem.write_f32(ctx.r[31] + (200), static_cast<float>(ctx.f[13])); // stfs f13, 200(r31)
    /* 0x800A803C */ ctx.cmp_f64(0, ctx.f[0], ctx.f[10]); // fcmpu cr0, f0, f10
    /* 0x800A8040 */ if (ctx.eval_bc(4, 1)) goto loc_800A8050; // bc 4, 1, 0x800A8050
    /* 0x800A8044 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8048 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-15312)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -15312(r9) [0x8016C430]
    /* 0x800A804C */ mem.write_f32(ctx.r[31] + (1216), static_cast<float>(ctx.f[0])); // stfs f0, 1216(r31)
loc_800A8050:;
    /* 0x800A8050 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (1280)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1280(r31)
    /* 0x800A8054 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (1220)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 1220(r31)
    /* 0x800A8058 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f13
    /* 0x800A805C */ ctx.cmp_f64(0, ctx.f[0], ctx.f[10]); // fcmpu cr0, f0, f10
    /* 0x800A8060 */ if (ctx.eval_bc(4, 1)) goto loc_800A8070; // bc 4, 1, 0x800A8070
    /* 0x800A8064 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8068 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-15312)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -15312(r9) [0x8016C430]
    /* 0x800A806C */ mem.write_f32(ctx.r[31] + (1220), static_cast<float>(ctx.f[0])); // stfs f0, 1220(r31)
loc_800A8070:;
    /* 0x800A8070 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (1284)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1284(r31)
    /* 0x800A8074 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (1224)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 1224(r31)
    /* 0x800A8078 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f13
    /* 0x800A807C */ ctx.cmp_f64(0, ctx.f[0], ctx.f[10]); // fcmpu cr0, f0, f10
    /* 0x800A8080 */ if (ctx.eval_bc(4, 1)) goto loc_800A8090; // bc 4, 1, 0x800A8090
    /* 0x800A8084 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8088 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-15312)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -15312(r9) [0x8016C430]
    /* 0x800A808C */ mem.write_f32(ctx.r[31] + (1224), static_cast<float>(ctx.f[0])); // stfs f0, 1224(r31)
loc_800A8090:;
    /* 0x800A8090 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800A8094 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A8098 */ ctx.r[31] = mem.read_u32(ctx.r[1] + (12)); // lwz r31, 12(r1)
    /* 0x800A809C */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800A80A0 */ return; // blr
}

// [0x800A80A4] cObj02::Release(void) (obj02.obj, 8 insns / 0x20 bytes)
void cObj02__Release_800A80A4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A80A4 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800A80A8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A80AC */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800A80B0 */ PushObj_800749C8(ctx, mem); // bl 0x800749C8 <PushObj(cObj *)>
    /* 0x800A80B4 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800A80B8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A80BC */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800A80C0 */ return; // blr
}

// [0x800A80C4] cObj02::clip(void) const (obj02.obj, 6 insns / 0x18 bytes)
void cObj02__clip_800A80C4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A80C4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A80C8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (296)); // lwz r0, 296(r9)
    /* 0x800A80CC */ ctx.r[9] = ctx.r[0] & 0x08000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x0800
    /* 0x800A80D0 */ ctx.r[3] = ctx.pack_cr(); // mfcr r3
    /* 0x800A80D4 */ ctx.rlwinm(3, 3, 3u, 31u, 31u, false); // rlwinm r3, r3, 3, 31, 31
    /* 0x800A80D8 */ return; // blr
}

// [0x800A80DC] cObj02::renderRegistration(void) (obj02.obj, 23 insns / 0x5C bytes)
void cObj02__renderRegistration_800A80DC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A80DC */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800A80E0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A80E4 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800A80E8 */ ctx.r[0] = mem.read_u8(ctx.r[3] + (295)); // lbz r0, 295(r3)
    /* 0x800A80EC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 5); // cmpwi cr0, r0, 5
    /* 0x800A80F0 */ if (ctx.eval_bc(4, 2)) goto loc_800A8110; // bc 4, 2, 0x800A8110
    /* 0x800A80F4 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A80F8 */ ctx.r[5] = 0x800E0000u; // lis r5, 0x800E
    /* 0x800A80FC */ ctx.r[3] = mem.read_u16(ctx.r[3] + (1290)); // lhz r3, 1290(r3)
    /* 0x800A8100 */ ctx.r[5] = ctx.r[5] + (-25172); // addi r5, r5, -25172 -> ModelRender(void *)
    /* 0x800A8104 */ ctx.r[6] = mem.read_u16(ctx.r[4] + (1292)); // lhz r6, 1292(r4)
    /* 0x800A8108 */ AddOtDirect_800DCC40(ctx, mem); // bl 0x800DCC40 <AddOtDirect(unsigned short, void *, void (*)(void *), unsigned short)>
    /* 0x800A810C */ goto loc_800A8128; // b 0x800A8128 <sub_800A8128>
loc_800A8110:;
    /* 0x800A8110 */ ctx.r[5] = 0x800E0000u; // lis r5, 0x800E
    /* 0x800A8114 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A8118 */ ctx.r[5] = ctx.r[5] + (-25172); // addi r5, r5, -25172 -> ModelRender(void *)
    /* 0x800A811C */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800A8120 */ ctx.r[6] = 0x00000001u; // li r6, 1
    /* 0x800A8124 */ AddOtDirect_800DCC40(ctx, mem); // bl 0x800DCC40 <AddOtDirect(unsigned short, void *, void (*)(void *), unsigned short)>
loc_800A8128:;
    /* 0x800A8128 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800A812C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A8130 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800A8134 */ return; // blr
}

// [0x800A8138] cObj02::~cObj02(void) (obj02.obj, 8 insns / 0x20 bytes)
void cObj02_dtor_cObj02_800A8138(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A8138 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800A813C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A8140 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800A8144 */ cObj_dtor_cObj_80074AD8(ctx, mem); // bl 0x80074AD8 <cObj::~cObj(void)>
    /* 0x800A8148 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800A814C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A8150 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800A8154 */ return; // blr
}

// [0x800A8158] cObj02::Initialize(void) (obj02.obj, 1 insns / 0x4 bytes)
void cObj02__Initialize_800A8158(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A8158 */ return; // blr
}

// [0x800A815C] cObj02::setOt(OT_TYPE, long) (obj02.obj, 3 insns / 0xC bytes)
void cObj02__setOt_800A815C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A815C */ mem.write_u16(ctx.r[3] + (1292), static_cast<uint16_t>(ctx.r[5])); // sth r5, 1292(r3)
    /* 0x800A8160 */ mem.write_u32(ctx.r[3] + (1288), ctx.r[4]); // stw r4, 1288(r3)
    /* 0x800A8164 */ return; // blr
}

// [0x800A8168] cObj02::cObj02(void) (obj02.obj, 43 insns / 0xAC bytes)
void cObj02__cObj02_800A8168(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A8168 */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800A816C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A8170 */ ctx.stmw(mem, 30, ctx.r[1] + (8)); // stmw r30, 8(r1)
    /* 0x800A8174 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800A8178 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800A817C */ cObj__cObj_80074A98(ctx, mem); // bl 0x80074A98 <cObj::cObj(void)>
    /* 0x800A8180 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A8184 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8188 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-15208)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -15208(r11) [0x8016C498]
    /* 0x800A818C */ ctx.r[9] = ctx.r[9] + (-15304); // addi r9, r9, -15304 -> cObj02 virtual table
    /* 0x800A8190 */ mem.write_u32(ctx.r[30] + (1208), ctx.r[9]); // stw r9, 1208(r30)
    /* 0x800A8194 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800A8198 */ mem.write_u32(ctx.r[30] + (1212), ctx.r[0]); // stw r0, 1212(r30)
    /* 0x800A819C */ ctx.r[9] = ctx.r[30] + (1216); // addi r9, r30, 1216
    /* 0x800A81A0 */ mem.write_f32(ctx.r[30] + (1216), static_cast<float>(ctx.f[0])); // stfs f0, 1216(r30)
    /* 0x800A81A4 */ ctx.r[11] = ctx.r[30] + (1228); // addi r11, r30, 1228
    /* 0x800A81A8 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
    /* 0x800A81AC */ ctx.r[10] = ctx.r[30] + (1240); // addi r10, r30, 1240
    /* 0x800A81B0 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r9)
    /* 0x800A81B4 */ ctx.r[8] = ctx.r[30] + (1252); // addi r8, r30, 1252
    /* 0x800A81B8 */ mem.write_f32(ctx.r[30] + (1228), static_cast<float>(ctx.f[0])); // stfs f0, 1228(r30)
    /* 0x800A81BC */ ctx.r[9] = ctx.r[30] + (1264); // addi r9, r30, 1264
    /* 0x800A81C0 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800A81C4 */ ctx.r[7] = ctx.r[30] + (1276); // addi r7, r30, 1276
    /* 0x800A81C8 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800A81CC */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A81D0 */ mem.write_f32(ctx.r[30] + (1240), static_cast<float>(ctx.f[0])); // stfs f0, 1240(r30)
    /* 0x800A81D4 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800A81D8 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800A81DC */ mem.write_f32(ctx.r[30] + (1252), static_cast<float>(ctx.f[0])); // stfs f0, 1252(r30)
    /* 0x800A81E0 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r8)
    /* 0x800A81E4 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800A81E8 */ mem.write_f32(ctx.r[30] + (1264), static_cast<float>(ctx.f[0])); // stfs f0, 1264(r30)
    /* 0x800A81EC */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
    /* 0x800A81F0 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r9)
    /* 0x800A81F4 */ mem.write_f32(ctx.r[30] + (1276), static_cast<float>(ctx.f[0])); // stfs f0, 1276(r30)
    /* 0x800A81F8 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r7)
    /* 0x800A81FC */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800A8200 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800A8204 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A8208 */ ctx.lmw(mem, 30, ctx.r[1] + (8)); // lmw r30, 8(r1)
    /* 0x800A820C */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800A8210 */ return; // blr
}

// [0x800A8214] cObj02::load(void *) (obj02.obj, 43 insns / 0xAC bytes)
void cObj02__load_800A8214(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A8214 */ ctx.r[9] = ctx.r[3] + (1240); // addi r9, r3, 1240
    /* 0x800A8218 */ ctx.r[0] = ctx.r[4] + (12); // addi r0, r4, 12
    /* 0x800A821C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), static_cast<int32_t>(ctx.r[4])); // cmpw cr0, r9, r4
    /* 0x800A8220 */ if (ctx.eval_bc(12, 2)) goto loc_800A823C; // bc 12, 2, 0x800A823C
    /* 0x800A8224 */ ctx.f[0] = mem.read_f32(ctx.r[4] + (0)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 0(r4)
    /* 0x800A8228 */ mem.write_f32(ctx.r[3] + (1240), static_cast<float>(ctx.f[0])); // stfs f0, 1240(r3)
    /* 0x800A822C */ ctx.f[13] = mem.read_f32(ctx.r[4] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r4)
    /* 0x800A8230 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r9)
    /* 0x800A8234 */ ctx.f[0] = mem.read_f32(ctx.r[4] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r4)
    /* 0x800A8238 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
loc_800A823C:;
    /* 0x800A823C */ ctx.r[11] = ctx.r[0]; // mr r11, r0
    /* 0x800A8240 */ ctx.r[9] = ctx.r[3] + (1252); // addi r9, r3, 1252
    /* 0x800A8244 */ ctx.r[0] = ctx.r[4] + (24); // addi r0, r4, 24
    /* 0x800A8248 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), static_cast<int32_t>(ctx.r[11])); // cmpw cr0, r9, r11
    /* 0x800A824C */ if (ctx.eval_bc(12, 2)) goto loc_800A8268; // bc 12, 2, 0x800A8268
    /* 0x800A8250 */ ctx.f[0] = mem.read_f32(ctx.r[4] + (12)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 12(r4)
    /* 0x800A8254 */ mem.write_f32(ctx.r[3] + (1252), static_cast<float>(ctx.f[0])); // stfs f0, 1252(r3)
    /* 0x800A8258 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r11)
    /* 0x800A825C */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r9)
    /* 0x800A8260 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r11)
    /* 0x800A8264 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
loc_800A8268:;
    /* 0x800A8268 */ ctx.r[11] = ctx.r[0]; // mr r11, r0
    /* 0x800A826C */ ctx.r[9] = ctx.r[3] + (1276); // addi r9, r3, 1276
    /* 0x800A8270 */ ctx.r[0] = ctx.r[4] + (36); // addi r0, r4, 36
    /* 0x800A8274 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), static_cast<int32_t>(ctx.r[11])); // cmpw cr0, r9, r11
    /* 0x800A8278 */ if (ctx.eval_bc(12, 2)) goto loc_800A8294; // bc 12, 2, 0x800A8294
    /* 0x800A827C */ ctx.f[0] = mem.read_f32(ctx.r[4] + (24)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 24(r4)
    /* 0x800A8280 */ mem.write_f32(ctx.r[3] + (1276), static_cast<float>(ctx.f[0])); // stfs f0, 1276(r3)
    /* 0x800A8284 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r11)
    /* 0x800A8288 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r9)
    /* 0x800A828C */ ctx.f[0] = mem.read_f32(ctx.r[11] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r11)
    /* 0x800A8290 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
loc_800A8294:;
    /* 0x800A8294 */ ctx.r[11] = ctx.r[0]; // mr r11, r0
    /* 0x800A8298 */ ctx.r[9] = ctx.r[3] + (1264); // addi r9, r3, 1264
    /* 0x800A829C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), static_cast<int32_t>(ctx.r[11])); // cmpw cr0, r9, r11
    /* 0x800A82A0 */ if (ctx.eval_bc(12, 2)) return; // bclr 12, 2
    /* 0x800A82A4 */ ctx.f[0] = mem.read_f32(ctx.r[4] + (36)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 36(r4)
    /* 0x800A82A8 */ mem.write_f32(ctx.r[3] + (1264), static_cast<float>(ctx.f[0])); // stfs f0, 1264(r3)
    /* 0x800A82AC */ ctx.f[13] = mem.read_f32(ctx.r[11] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r11)
    /* 0x800A82B0 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r9)
    /* 0x800A82B4 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r11)
    /* 0x800A82B8 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
    /* 0x800A82BC */ return; // blr
}

// [0x800A82C0] cObj02::setMoveType(OBJ02_TYPE) (obj02.obj, 4 insns / 0x10 bytes)
void cObj02__setMoveType_800A82C0(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A82C0 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800A82C4 */ mem.write_u32(ctx.r[3] + (1212), ctx.r[4]); // stw r4, 1212(r3)
    /* 0x800A82C8 */ mem.write_u8(ctx.r[3] + (248), static_cast<uint8_t>(ctx.r[0])); // stb r0, 248(r3)
    /* 0x800A82CC */ return; // blr
}

// [0x800A82D0] cObj05::Main(void) (obj05.obj, 193 insns / 0x304 bytes)
void cObj05__Main_800A82D0(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A82D0 */ ctx.r[1] += (-48); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -48(r1)
    /* 0x800A82D4 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A82D8 */ ctx.stmw(mem, 28, ctx.r[1] + (32)); // stmw r28, 32(r1)
    /* 0x800A82DC */ mem.write_u32(ctx.r[1] + (52), ctx.r[0]); // stw r0, 52(r1)
    /* 0x800A82E0 */ ctx.r[29] = ctx.r[3]; // mr r29, r3
    /* 0x800A82E4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A82E8 */ ctx.r[31] = ctx.r[29] + (1224); // addi r31, r29, 1224
    /* 0x800A82EC */ ctx.r[4] = mem.read_u32(ctx.r[31] + (120)); // lwz r4, 120(r31)
    /* 0x800A82F0 */ ctx.r[9] = ctx.r[9] + (756); // addi r9, r9, 756
    /* 0x800A82F4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[4]), static_cast<int32_t>(ctx.r[9])); // cmpw cr0, r4, r9
    /* 0x800A82F8 */ if (ctx.eval_bc(12, 2)) goto loc_800A8328; // bc 12, 2, 0x800A8328
    /* 0x800A82FC */ ctx.r[9] = mem.read_u8(ctx.r[31] + (124)); // lbz r9, 124(r31)
    /* 0x800A8300 */ ctx.rlwinm(0, 9, 0u, 24u, 31u, false); // rlwinm r0, r9, 0, 24, 31
    /* 0x800A8304 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 255); // cmpwi cr0, r0, 255
    /* 0x800A8308 */ if (ctx.eval_bc(12, 2)) goto loc_800A8328; // bc 12, 2, 0x800A8328
    /* 0x800A830C */ ctx.r[0] = mem.read_u16(ctx.r[31] + (114)); // lhz r0, 114(r31)
    /* 0x800A8310 */ ctx.cmp_u32(0, ctx.r[9], ctx.r[0]); // cmplw cr0, r9, r0
    /* 0x800A8314 */ if (ctx.eval_bc(12, 1)) goto loc_800A8328; // bc 12, 1, 0x800A8328
    /* 0x800A8318 */ cObj05__Efm05RotMatrix_800A8E2C(ctx, mem); // bl 0x800A8E2C <cObj05::Efm05RotMatrix(float (*)[2][3])>
    /* 0x800A831C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A8320 */ ctx.r[9] = ctx.r[9] + (756); // addi r9, r9, 756
    /* 0x800A8324 */ mem.write_u32(ctx.r[31] + (120), ctx.r[9]); // stw r9, 120(r31)
loc_800A8328:;
    /* 0x800A8328 */ ctx.r[9] = mem.read_u16(ctx.r[31] + (108)); // lhz r9, 108(r31)
    /* 0x800A832C */ ctx.r[0] = mem.read_u16(ctx.r[31] + (114)); // lhz r0, 114(r31)
    /* 0x800A8330 */ ctx.cmp_u32(0, ctx.r[9], ctx.r[0]); // cmplw cr0, r9, r0
    /* 0x800A8334 */ if (ctx.eval_bc(12, 1)) goto loc_800A838C; // bc 12, 1, 0x800A838C
    /* 0x800A8338 */ ctx.r[11] = mem.read_u32(ctx.r[29] + (192)); // lwz r11, 192(r29)
    /* 0x800A833C */ ctx.r[9] = ctx.r[29] + (192); // addi r9, r29, 192
    /* 0x800A8340 */ ctx.r[10] = mem.read_u32(ctx.r[9] + (4)); // lwz r10, 4(r9)
    /* 0x800A8344 */ ctx.r[3] = ctx.r[9]; // mr r3, r9
    /* 0x800A8348 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (8)); // lwz r0, 8(r9)
    /* 0x800A834C */ ctx.r[30] = ctx.r[29] + (256); // addi r30, r29, 256
    /* 0x800A8350 */ mem.write_u32(ctx.r[29] + (268), ctx.r[11]); // stw r11, 268(r29)
    /* 0x800A8354 */ ctx.r[9] = ctx.r[29] + (268); // addi r9, r29, 268
    /* 0x800A8358 */ ctx.r[5] = ctx.r[3]; // mr r5, r3
    /* 0x800A835C */ mem.write_u32(ctx.r[9] + (8), ctx.r[0]); // stw r0, 8(r9)
    /* 0x800A8360 */ mem.write_u32(ctx.r[9] + (4), ctx.r[10]); // stw r10, 4(r9)
    /* 0x800A8364 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A8368 */ ctx.call_indirect(0x801038F4u, mem); // bl 0x801038F4 <PSVECAdd>
    /* 0x800A836C */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A8370 */ ctx.r[4] = ctx.r[31] + (20); // addi r4, r31, 20
    /* 0x800A8374 */ ctx.r[5] = ctx.r[30]; // mr r5, r30
    /* 0x800A8378 */ ctx.call_indirect(0x801038F4u, mem); // bl 0x801038F4 <PSVECAdd>
    /* 0x800A837C */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A8380 */ ctx.f[1] = mem.read_f32(ctx.r[31] + (16)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 16(r31)
    /* 0x800A8384 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A8388 */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
loc_800A838C:;
    /* 0x800A838C */ ctx.r[9] = mem.read_u16(ctx.r[31] + (110)); // lhz r9, 110(r31)
    /* 0x800A8390 */ ctx.r[0] = mem.read_u16(ctx.r[31] + (114)); // lhz r0, 114(r31)
    /* 0x800A8394 */ ctx.cmp_u32(0, ctx.r[9], ctx.r[0]); // cmplw cr0, r9, r0
    /* 0x800A8398 */ if (ctx.eval_bc(12, 1)) goto loc_800A83CC; // bc 12, 1, 0x800A83CC
    /* 0x800A839C */ ctx.f[13] = mem.read_f32(ctx.r[31] + (56)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 56(r31)
    /* 0x800A83A0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A83A4 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (52)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 52(r31)
    /* 0x800A83A8 */ ctx.f[12] = mem.read_f32(ctx.r[31] + (60)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 60(r31)
    /* 0x800A83AC */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f13
    /* 0x800A83B0 */ ctx.f[11] = mem.read_f32(ctx.r[9] + (-15188)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -15188(r9) [0x8016C4AC]
    /* 0x800A83B4 */ ctx.f[13] = static_cast<float>(ctx.f[13] * ctx.f[12]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // fmuls f13, f13, f12
    /* 0x800A83B8 */ mem.write_f32(ctx.r[31] + (52), static_cast<float>(ctx.f[0])); // stfs f0, 52(r31)
    /* 0x800A83BC */ ctx.cmp_f64(0, ctx.f[0], ctx.f[11]); // fcmpu cr0, f0, f11
    /* 0x800A83C0 */ mem.write_f32(ctx.r[31] + (56), static_cast<float>(ctx.f[13])); // stfs f13, 56(r31)
    /* 0x800A83C4 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(0)); // cror 3, 2, 0
    /* 0x800A83C8 */ if (ctx.eval_bc(12, 3)) goto loc_800A8430; // bc 12, 3, 0x800A8430
loc_800A83CC:;
    /* 0x800A83CC */ ctx.r[5] = ctx.r[29] + (204); // addi r5, r29, 204
    /* 0x800A83D0 */ ctx.r[4] = ctx.r[31] + (32); // addi r4, r31, 32
    /* 0x800A83D4 */ ctx.r[3] = ctx.r[5]; // mr r3, r5
    /* 0x800A83D8 */ ctx.r[28] = ctx.r[5]; // mr r28, r5
    /* 0x800A83DC */ ctx.call_indirect(0x801038F4u, mem); // bl 0x801038F4 <PSVECAdd>
    /* 0x800A83E0 */ ctx.r[4] = mem.read_u16(ctx.r[31] + (114)); // lhz r4, 114(r31)
    /* 0x800A83E4 */ ctx.r[3] = ctx.r[31] + (64); // addi r3, r31, 64
    /* 0x800A83E8 */ EspCommonMoveColor_80083D4C(ctx, mem); // bl 0x80083D4C <EspCommonMoveColor(ESPCOLOR &, long)>
    /* 0x800A83EC */ ctx.r[3] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // mr r3, r3
    /* 0x800A83F0 */ if (ctx.eval_bc(4, 2)) goto loc_800A8430; // bc 4, 2, 0x800A8430
    /* 0x800A83F4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A83F8 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (80)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 80(r31)
    /* 0x800A83FC */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-15184)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -15184(r9) [0x8016C4B0 /* "Cz" */]
    /* 0x800A8400 */ ctx.cmp_f64(0, ctx.f[13], ctx.f[0]); // fcmpu cr0, f13, f0
    /* 0x800A8404 */ if (ctx.eval_bc(4, 0)) goto loc_800A8414; // bc 4, 0, 0x800A8414
    /* 0x800A8408 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800A840C */ mem.write_u8(ctx.r[29] + (295), static_cast<uint8_t>(ctx.r[0])); // stb r0, 295(r29)
    /* 0x800A8410 */ goto loc_800A8418; // b 0x800A8418 <sub_800A8418>
loc_800A8414:;
    /* 0x800A8414 */ mem.write_u8(ctx.r[29] + (295), static_cast<uint8_t>(ctx.r[3])); // stb r3, 295(r29)
loc_800A8418:;
    /* 0x800A8418 */ ctx.r[0] = mem.read_u16(ctx.r[31] + (112)); // lhz r0, 112(r31)
    /* 0x800A841C */ ctx.r[9] = mem.read_u16(ctx.r[31] + (114)); // lhz r9, 114(r31)
    /* 0x800A8420 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800A8424 */ if (ctx.eval_bc(12, 2)) goto loc_800A843C; // bc 12, 2, 0x800A843C
    /* 0x800A8428 */ ctx.cmp_u32(0, ctx.r[0], ctx.r[9]); // cmplw cr0, r0, r9
    /* 0x800A842C */ if (ctx.eval_bc(12, 1)) goto loc_800A843C; // bc 12, 1, 0x800A843C
loc_800A8430:;
    /* 0x800A8430 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A8434 */ cObj05__PushObj05_800A8EF0(ctx, mem); // bl 0x800A8EF0 <cObj05::PushObj05(void)>
    /* 0x800A8438 */ goto loc_800A85C0; // b 0x800A85C0 <sub_800A85C0>
loc_800A843C:;
    /* 0x800A843C */ ctx.f[0] = mem.read_f32(ctx.r[31] + (68)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 68(r31)
    /* 0x800A8440 */ ctx.r[0] = ctx.r[9] + (1); // addi r0, r9, 1
    /* 0x800A8444 */ mem.write_u16(ctx.r[31] + (114), static_cast<uint16_t>(ctx.r[0])); // sth r0, 114(r31)
    /* 0x800A8448 */ ctx.r[11] = ctx.r[9]; // mr r11, r9
    /* 0x800A844C */ { int32_t iv = static_cast<int32_t>(ctx.f[0]); uint64_t u = static_cast<uint32_t>(iv); std::memcpy(&ctx.f[13], &u, 8); } // fctiwz f13, f0
    /* 0x800A8450 */ ctx.r[7] = mem.read_u32(ctx.r[29] + (304)); // lwz r7, 304(r29)
    /* 0x800A8454 */ mem.write_f64(ctx.r[1] + (24), ctx.f[13]); // stfd f13, 24(r1)
    /* 0x800A8458 */ ctx.r[8] = ctx.r[10]; // mr r8, r10
    /* 0x800A845C */ ctx.r[9] = mem.read_u32(ctx.r[1] + (28)); // lwz r9, 28(r1)
    /* 0x800A8460 */ mem.write_u8(ctx.r[7] + (92), static_cast<uint8_t>(ctx.r[9])); // stb r9, 92(r7)
    /* 0x800A8464 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (72)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 72(r31)
    /* 0x800A8468 */ ctx.r[9] = mem.read_u32(ctx.r[29] + (304)); // lwz r9, 304(r29)
    /* 0x800A846C */ { int32_t iv = static_cast<int32_t>(ctx.f[0]); uint64_t u = static_cast<uint32_t>(iv); std::memcpy(&ctx.f[12], &u, 8); } // fctiwz f12, f0
    /* 0x800A8470 */ mem.write_f64(ctx.r[1] + (24), ctx.f[12]); // stfd f12, 24(r1)
    /* 0x800A8474 */ ctx.r[11] = mem.read_u32(ctx.r[1] + (28)); // lwz r11, 28(r1)
    /* 0x800A8478 */ mem.write_u8(ctx.r[9] + (93), static_cast<uint8_t>(ctx.r[11])); // stb r11, 93(r9)
    /* 0x800A847C */ ctx.f[0] = mem.read_f32(ctx.r[31] + (76)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 76(r31)
    /* 0x800A8480 */ ctx.r[9] = mem.read_u32(ctx.r[29] + (304)); // lwz r9, 304(r29)
    /* 0x800A8484 */ { int32_t iv = static_cast<int32_t>(ctx.f[0]); uint64_t u = static_cast<uint32_t>(iv); std::memcpy(&ctx.f[13], &u, 8); } // fctiwz f13, f0
    /* 0x800A8488 */ mem.write_f64(ctx.r[1] + (24), ctx.f[13]); // stfd f13, 24(r1)
    /* 0x800A848C */ ctx.r[10] = mem.read_u32(ctx.r[1] + (28)); // lwz r10, 28(r1)
    /* 0x800A8490 */ mem.write_u8(ctx.r[9] + (94), static_cast<uint8_t>(ctx.r[10])); // stb r10, 94(r9)
    /* 0x800A8494 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (80)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 80(r31)
    /* 0x800A8498 */ ctx.r[9] = mem.read_u32(ctx.r[29] + (304)); // lwz r9, 304(r29)
    /* 0x800A849C */ { int32_t iv = static_cast<int32_t>(ctx.f[0]); uint64_t u = static_cast<uint32_t>(iv); std::memcpy(&ctx.f[11], &u, 8); } // fctiwz f11, f0
    /* 0x800A84A0 */ mem.write_f64(ctx.r[1] + (24), ctx.f[11]); // stfd f11, 24(r1)
    /* 0x800A84A4 */ ctx.r[8] = mem.read_u32(ctx.r[1] + (28)); // lwz r8, 28(r1)
    /* 0x800A84A8 */ mem.write_u8(ctx.r[9] + (95), static_cast<uint8_t>(ctx.r[8])); // stb r8, 95(r9)
    /* 0x800A84AC */ ctx.f[13] = mem.read_f32(ctx.r[31] + (52)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 52(r31)
    /* 0x800A84B0 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (48)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 48(r31)
    /* 0x800A84B4 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f13
    /* 0x800A84B8 */ mem.write_f32(ctx.r[29] + (220), static_cast<float>(ctx.f[0])); // stfs f0, 220(r29)
    /* 0x800A84BC */ ctx.f[13] = mem.read_f32(ctx.r[31] + (44)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 44(r31)
    /* 0x800A84C0 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (52)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 52(r31)
    /* 0x800A84C4 */ ctx.f[13] = static_cast<float>(ctx.f[13] * ctx.f[0]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // fmuls f13, f13, f0
    /* 0x800A84C8 */ mem.write_f32(ctx.r[29] + (224), static_cast<float>(ctx.f[13])); // stfs f13, 224(r29)
    /* 0x800A84CC */ mem.write_f32(ctx.r[29] + (216), static_cast<float>(ctx.f[13])); // stfs f13, 216(r29)
    /* 0x800A84D0 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (128)); // lwz r0, 128(r31)
    /* 0x800A84D4 */ ctx.r[9] = ctx.r[0] & 0x0008u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0008
    /* 0x800A84D8 */ if (ctx.eval_bc(12, 2)) goto loc_800A8510; // bc 12, 2, 0x800A8510
    /* 0x800A84DC */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A84E0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A84E4 */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-15180)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15180(r9) [0x8016C4B4]
    /* 0x800A84E8 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A84EC */ ctx.f[2] = mem.read_f32(ctx.r[11] + (-15176)); ctx.ps0[2] = static_cast<float>(ctx.f[2]); // lfs f2, -15176(r11) [0x8016C4B8]
    /* 0x800A84F0 */ MotionMove_800A2434(ctx, mem); // bl 0x800A2434 <MotionMove(cEm *, float, float)>
    /* 0x800A84F4 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (126)); // lbz r0, 126(r31)
    /* 0x800A84F8 */ ctx.r[0] = ctx.r[0] ^ 0x0001u; // xori r0, r0, 0x0001
    /* 0x800A84FC */ ctx.r[9] = ctx.r[0] & 0x0001u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0001
    /* 0x800A8500 */ if (ctx.eval_bc(12, 2)) goto loc_800A8518; // bc 12, 2, 0x800A8518
    /* 0x800A8504 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A8508 */ cObj05__Obj05Move_800A8C38(ctx, mem); // bl 0x800A8C38 <cObj05::Obj05Move(void)>
    /* 0x800A850C */ goto loc_800A8518; // b 0x800A8518 <sub_800A8518>
loc_800A8510:;
    /* 0x800A8510 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A8514 */ cObj05__PartsBomb_800A85D4(ctx, mem); // bl 0x800A85D4 <cObj05::PartsBomb(void)>
loc_800A8518:;
    /* 0x800A8518 */ ctx.f[13] = mem.read_f32(ctx.r[29] + (204)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 204(r29)
    /* 0x800A851C */ ctx.r[30] = ctx.r[1] + (8); // addi r30, r1, 8
    /* 0x800A8520 */ ctx.f[12] = mem.read_f32(ctx.r[28] + (8)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 8(r28)
    /* 0x800A8524 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A8528 */ ctx.f[0] = mem.read_f32(ctx.r[28] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r28)
    /* 0x800A852C */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A8530 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800A8534 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r30)
    /* 0x800A8538 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A853C */ RotMatrix_8009E1D0(ctx, mem); // bl 0x8009E1D0 <RotMatrix(float (*)[3], cVec &)>
    /* 0x800A8540 */ ctx.f[13] = mem.read_f32(ctx.r[29] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r29)
    /* 0x800A8544 */ ctx.r[9] = ctx.r[29] + (192); // addi r9, r29, 192
    /* 0x800A8548 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A854C */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A8550 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800A8554 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A8558 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A855C */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A8560 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800A8564 */ TransMatrix_8009E1B4(ctx, mem); // bl 0x8009E1B4 <TransMatrix(float (*)[3], cVec &)>
    /* 0x800A8568 */ ctx.f[13] = mem.read_f32(ctx.r[29] + (216)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 216(r29)
    /* 0x800A856C */ ctx.r[9] = ctx.r[29] + (216); // addi r9, r29, 216
    /* 0x800A8570 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A8574 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A8578 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800A857C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A8580 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A8584 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A8588 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800A858C */ ScaleMatrix_8009E168(ctx, mem); // bl 0x8009E168 <ScaleMatrix(float (*)[3], cVec &)>
    /* 0x800A8590 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A8594 */ ctx.r[3] = mem.read_u32(ctx.r[31] + (120)); // lwz r3, 120(r31)
    /* 0x800A8598 */ ctx.r[9] = ctx.r[9] + (756); // addi r9, r9, 756
    /* 0x800A859C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), static_cast<int32_t>(ctx.r[9])); // cmpw cr0, r3, r9
    /* 0x800A85A0 */ if (ctx.eval_bc(12, 2)) goto loc_800A85B0; // bc 12, 2, 0x800A85B0
    /* 0x800A85A4 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800A85A8 */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800A85AC */ ctx.call_indirect(0x80100470u, mem); // bl 0x80100470 <PSMTXConcat>
loc_800A85B0:;
    /* 0x800A85B0 */ ctx.r[3] = mem.read_u32(ctx.r[29] + (240)); // lwz r3, 240(r29)
    /* 0x800A85B4 */ ModelMatCalc_800A0BF4(ctx, mem); // bl 0x800A0BF4 <ModelMatCalc(PARTS *)>
    /* 0x800A85B8 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A85BC */ PartsWorldCalc_800A0E5C(ctx, mem); // bl 0x800A0E5C <PartsWorldCalc(cEm *)>
loc_800A85C0:;
    /* 0x800A85C0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (52)); // lwz r0, 52(r1)
    /* 0x800A85C4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A85C8 */ ctx.lmw(mem, 28, ctx.r[1] + (32)); // lmw r28, 32(r1)
    /* 0x800A85CC */ ctx.r[1] = ctx.r[1] + (48); // addi r1, r1, 48
    /* 0x800A85D0 */ return; // blr
}

// [0x800A85D4] cObj05::PartsBomb(void) (obj05.obj, 409 insns / 0x664 bytes)
void cObj05__PartsBomb_800A85D4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A85D4 */ ctx.r[1] += (-312); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -312(r1)
    /* 0x800A85D8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A85DC */ mem.write_f64(ctx.r[1] + (256), ctx.f[25]); // stfd f25, 256(r1)
    /* 0x800A85E0 */ mem.write_f64(ctx.r[1] + (264), ctx.f[26]); // stfd f26, 264(r1)
    /* 0x800A85E4 */ mem.write_f64(ctx.r[1] + (272), ctx.f[27]); // stfd f27, 272(r1)
    /* 0x800A85E8 */ mem.write_f64(ctx.r[1] + (280), ctx.f[28]); // stfd f28, 280(r1)
    /* 0x800A85EC */ mem.write_f64(ctx.r[1] + (288), ctx.f[29]); // stfd f29, 288(r1)
    /* 0x800A85F0 */ mem.write_f64(ctx.r[1] + (296), ctx.f[30]); // stfd f30, 296(r1)
    /* 0x800A85F4 */ mem.write_f64(ctx.r[1] + (304), ctx.f[31]); // stfd f31, 304(r1)
    /* 0x800A85F8 */ ctx.stmw(mem, 14, ctx.r[1] + (184)); // stmw r14, 184(r1)
    /* 0x800A85FC */ mem.write_u32(ctx.r[1] + (316), ctx.r[0]); // stw r0, 316(r1)
    /* 0x800A8600 */ ctx.r[19] = ctx.r[3]; // mr r19, r3
    /* 0x800A8604 */ ctx.r[25] = ctx.r[19] + (1224); // addi r25, r19, 1224
    /* 0x800A8608 */ ctx.r[30] = 0x43300000u; // lis r30, 0x4330
    /* 0x800A860C */ ctx.r[9] = mem.read_u8(ctx.r[25] + (161)); // lbz r9, 161(r25)
    /* 0x800A8610 */ ctx.r[6] = ctx.r[8]; // mr r6, r8
    /* 0x800A8614 */ ctx.r[0] = mem.read_u16(ctx.r[25] + (114)); // lhz r0, 114(r25)
    /* 0x800A8618 */ ctx.r[29] = ctx.r[8]; // mr r29, r8
    /* 0x800A861C */ ctx.r[9] = ctx.r[9] + ctx.r[9]; // add r9, r9, r9
    /* 0x800A8620 */ ctx.r[10] = mem.read_u8(ctx.r[25] + (160)); // lbz r10, 160(r25)
    /* 0x800A8624 */ ctx.r[9] = ctx.r[9] + (1); // addi r9, r9, 1
    /* 0x800A8628 */ ctx.r[7] = mem.read_u8(ctx.r[25] + (162)); // lbz r7, 162(r25)
    /* 0x800A862C */ ctx.r[0] = static_cast<uint32_t>(static_cast<int32_t>(ctx.r[0]) * static_cast<int32_t>(ctx.r[9])); // mullw r0, r0, r9
    /* 0x800A8630 */ ctx.r[10] = ctx.r[10] ^ 0x80000000u; // xoris r10, r10, 0x8000
    /* 0x800A8634 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8638 */ ctx.r[5] = mem.read_u8(ctx.r[25] + (163)); // lbz r5, 163(r25)
    /* 0x800A863C */ ctx.f[12] = mem.read_f64(ctx.r[9] + (-15168)); // lfd f12, -15168(r9) [0x8016C4C0 /* "C0" */]
    /* 0x800A8640 */ ctx.r[7] = ctx.r[7] ^ 0x80000000u; // xoris r7, r7, 0x8000
    /* 0x800A8644 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8648 */ ctx.r[4] = ctx.r[8]; // mr r4, r8
    /* 0x800A864C */ ctx.r[0] = ctx.r[0] ^ 0x80000000u; // xoris r0, r0, 0x8000
    /* 0x800A8650 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-15160)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -15160(r9) [0x8016C4C8]
    /* 0x800A8654 */ mem.write_u32(ctx.r[1] + (180), ctx.r[0]); // stw r0, 180(r1)
    /* 0x800A8658 */ ctx.r[5] = ctx.r[5] ^ 0x80000000u; // xoris r5, r5, 0x8000
    /* 0x800A865C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A8660 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800A8664 */ mem.write_u32(ctx.r[1] + (176), ctx.r[30]); // stw r30, 176(r1)
    /* 0x800A8668 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A866C */ ctx.f[11] = mem.read_f32(ctx.r[11] + (-15156)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -15156(r11) [0x8016C4CC]
    /* 0x800A8670 */ ctx.r[24] = 0x00000000u; // li r24, 0
    /* 0x800A8674 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (176)); // lfd f0, 176(r1)
    /* 0x800A8678 */ mem.write_u32(ctx.r[1] + (180), ctx.r[10]); // stw r10, 180(r1)
    /* 0x800A867C */ ctx.f[0] = ctx.f[0] - ctx.f[12]; // fsub f0, f0, f12
    /* 0x800A8680 */ ctx.f[9] = mem.read_f32(ctx.r[3] + (-15152)); ctx.ps0[9] = static_cast<float>(ctx.f[9]); // lfs f9, -15152(r3) [0x8016C4D0 /* "=" */]
    /* 0x800A8684 */ mem.write_u32(ctx.r[1] + (176), ctx.r[30]); // stw r30, 176(r1)
    /* 0x800A8688 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800A868C */ ctx.f[28] = static_cast<float>(ctx.f[0] + ctx.f[13]); ctx.ps0[28] = static_cast<float>(ctx.f[28]); // fadds f28, f0, f13
    /* 0x800A8690 */ ctx.f[10] = mem.read_f32(ctx.r[9] + (-15148)); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // lfs f10, -15148(r9) [0x8016C4D4]
    /* 0x800A8694 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (176)); // lfd f0, 176(r1)
    /* 0x800A8698 */ mem.write_u32(ctx.r[1] + (180), ctx.r[7]); // stw r7, 180(r1)
    /* 0x800A869C */ ctx.f[0] = ctx.f[0] - ctx.f[12]; // fsub f0, f0, f12
    /* 0x800A86A0 */ ctx.r[0] = mem.read_u8(ctx.r[19] + (254)); // lbz r0, 254(r19)
    /* 0x800A86A4 */ mem.write_u32(ctx.r[1] + (176), ctx.r[30]); // stw r30, 176(r1)
    /* 0x800A86A8 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800A86AC */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f11
    /* 0x800A86B0 */ ctx.cmp_u32(0, ctx.r[24], ctx.r[0]); // cmplw cr0, r24, r0
    /* 0x800A86B4 */ ctx.f[13] = mem.read_f64(ctx.r[1] + (176)); // lfd f13, 176(r1)
    /* 0x800A86B8 */ ctx.f[29] = static_cast<float>(ctx.f[0] / ctx.f[28]); ctx.ps0[29] = static_cast<float>(ctx.f[29]); // fdivs f29, f0, f28
    /* 0x800A86BC */ mem.write_u32(ctx.r[1] + (180), ctx.r[5]); // stw r5, 180(r1)
    /* 0x800A86C0 */ ctx.r[31] = mem.read_u32(ctx.r[19] + (240)); // lwz r31, 240(r19)
    /* 0x800A86C4 */ mem.write_u32(ctx.r[1] + (176), ctx.r[30]); // stw r30, 176(r1)
    /* 0x800A86C8 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (176)); // lfd f0, 176(r1)
    /* 0x800A86CC */ ctx.f[13] = ctx.f[13] - ctx.f[12]; // fsub f13, f13, f12
    /* 0x800A86D0 */ ctx.f[0] = ctx.f[0] - ctx.f[12]; // fsub f0, f0, f12
    /* 0x800A86D4 */ ctx.f[13] = static_cast<double>(static_cast<float>(ctx.f[13])); // frsp f13, f13
    /* 0x800A86D8 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800A86DC */ ctx.f[25] = static_cast<float>(ctx.f[13] * ctx.f[9]); ctx.ps0[25] = static_cast<float>(ctx.f[25]); // fmuls f25, f13, f9
    /* 0x800A86E0 */ ctx.f[30] = static_cast<float>(ctx.f[0] * ctx.f[10]); ctx.ps0[30] = static_cast<float>(ctx.f[30]); // fmuls f30, f0, f10
    /* 0x800A86E4 */ if (ctx.eval_bc(4, 0)) goto loc_800A8C08; // bc 4, 0, 0x800A8C08
    /* 0x800A86E8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A86EC */ ctx.r[16] = 0x80170000u; // lis r16, 0x8017
    /* 0x800A86F0 */ ctx.f[26] = mem.read_f32(ctx.r[9] + (-15132)); ctx.ps0[26] = static_cast<float>(ctx.f[26]); // lfs f26, -15132(r9) [0x8016C4E4]
    /* 0x800A86F4 */ ctx.r[22] = ctx.r[1] + (56); // addi r22, r1, 56
    /* 0x800A86F8 */ ctx.f[27] = mem.read_f32(ctx.r[16] + (-15140)); ctx.ps0[27] = static_cast<float>(ctx.f[27]); // lfs f27, -15140(r16) [0x8016C4DC]
    /* 0x800A86FC */ ctx.r[14] = ctx.r[1] + (88); // addi r14, r1, 88
    /* 0x800A8700 */ ctx.r[15] = ctx.r[1] + (104); // addi r15, r1, 104
    /* 0x800A8704 */ ctx.r[18] = 0x80170000u; // lis r18, 0x8017
loc_800A8708:;
    /* 0x800A8708 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (328)); // lwz r0, 328(r31)
    /* 0x800A870C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800A8710 */ if (ctx.eval_bc(4, 2)) goto loc_800A8808; // bc 4, 2, 0x800A8808
    /* 0x800A8714 */ ctx.r[3] = ctx.r[19] + (192); // addi r3, r19, 192
    /* 0x800A8718 */ ctx.r[4] = ctx.r[25] + (148); // addi r4, r25, 148
    /* 0x800A871C */ ctx.r[5] = ctx.r[22]; // mr r5, r22
    /* 0x800A8720 */ ctx.r[21] = ctx.r[24] + (1); // addi r21, r24, 1
    /* 0x800A8724 */ ctx.call_indirect(0x801038F4u, mem); // bl 0x801038F4 <PSVECAdd>
    /* 0x800A8728 */ ctx.r[3] = ctx.r[31] + (264); // addi r3, r31, 264
    /* 0x800A872C */ ctx.r[4] = ctx.r[22]; // mr r4, r22
    /* 0x800A8730 */ ctx.r[5] = ctx.r[22]; // mr r5, r22
    /* 0x800A8734 */ ctx.call_indirect(0x8010394Cu, mem); // bl 0x8010394C <PSVECSubtract>
    /* 0x800A8738 */ ctx.r[3] = ctx.r[22]; // mr r3, r22
    /* 0x800A873C */ ctx.call_indirect(0x80103B90u, mem); // bl 0x80103B90 <PSVECMag>
    /* 0x800A8740 */ ctx.r[3] = ctx.r[22]; // mr r3, r22
    /* 0x800A8744 */ ctx.cmp_f64(0, ctx.f[1], ctx.f[28]); // fcmpu cr0, f1, f28
    /* 0x800A8748 */ if (ctx.eval_bc(4, 0)) goto loc_800A8BF4; // bc 4, 0, 0x800A8BF4
    /* 0x800A874C */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800A8750 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8754 */ mem.write_u32(ctx.r[31] + (328), ctx.r[0]); // stw r0, 328(r31)
    /* 0x800A8758 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-15144)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -15144(r9) [0x8016C4D8]
    /* 0x800A875C */ ctx.f[0] = mem.read_f32(ctx.r[1] + (56)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 56(r1)
    /* 0x800A8760 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[13]); // fcmpu cr0, f0, f13
    /* 0x800A8764 */ if (ctx.eval_bc(4, 2)) goto loc_800A878C; // bc 4, 2, 0x800A878C
    /* 0x800A8768 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (60)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 60(r1)
    /* 0x800A876C */ ctx.cmp_f64(0, ctx.f[0], ctx.f[13]); // fcmpu cr0, f0, f13
    /* 0x800A8770 */ if (ctx.eval_bc(4, 2)) goto loc_800A878C; // bc 4, 2, 0x800A878C
    /* 0x800A8774 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (64)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 64(r1)
    /* 0x800A8778 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[13]); // fcmpu cr0, f0, f13
    /* 0x800A877C */ if (ctx.eval_bc(4, 2)) goto loc_800A878C; // bc 4, 2, 0x800A878C
    /* 0x800A8780 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8784 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-15160)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -15160(r9) [0x8016C4C8]
    /* 0x800A8788 */ mem.write_f32(ctx.r[1] + (60), static_cast<float>(ctx.f[0])); // stfs f0, 60(r1)
loc_800A878C:;
    /* 0x800A878C */ ctx.r[30] = ctx.r[31] + (332); // addi r30, r31, 332
    /* 0x800A8790 */ ctx.f[31] = static_cast<float>(ctx.f[29] * ctx.f[25]); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // fmuls f31, f29, f25
    /* 0x800A8794 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A8798 */ ctx.r[21] = ctx.r[24] + (1); // addi r21, r24, 1
    /* 0x800A879C */ ctx.call_indirect(0x80103A7Cu, mem); // bl 0x80103A7C <PSVECNormalize>
    /* 0x800A87A0 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A87A4 */ ctx.f[1] = ctx.f[29]; ctx.ps0[1] = static_cast<float>(ctx.f[29]); // fmr f1, f29
    /* 0x800A87A8 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A87AC */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
    /* 0x800A87B0 */ fRand1_1_800C075C(ctx, mem); // bl 0x800C075C <fRand1_1(void)>
    /* 0x800A87B4 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (332)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 332(r31)
    /* 0x800A87B8 */ ctx.f[1] = static_cast<float>(ctx.f[31] * ctx.f[1] + ctx.f[0]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmadds f1, f31, f1, f0
    /* 0x800A87BC */ mem.write_f32(ctx.r[31] + (332), static_cast<float>(ctx.f[1])); // stfs f1, 332(r31)
    /* 0x800A87C0 */ fRand1_1_800C075C(ctx, mem); // bl 0x800C075C <fRand1_1(void)>
    /* 0x800A87C4 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (336)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 336(r31)
    /* 0x800A87C8 */ ctx.f[1] = static_cast<float>(ctx.f[31] * ctx.f[1] + ctx.f[0]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmadds f1, f31, f1, f0
    /* 0x800A87CC */ mem.write_f32(ctx.r[31] + (336), static_cast<float>(ctx.f[1])); // stfs f1, 336(r31)
    /* 0x800A87D0 */ fRand1_1_800C075C(ctx, mem); // bl 0x800C075C <fRand1_1(void)>
    /* 0x800A87D4 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (340)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 340(r31)
    /* 0x800A87D8 */ ctx.f[31] = static_cast<float>(ctx.f[31] * ctx.f[1] + ctx.f[0]); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // fmadds f31, f31, f1, f0
    /* 0x800A87DC */ mem.write_f32(ctx.r[31] + (340), static_cast<float>(ctx.f[31])); // stfs f31, 340(r31)
    /* 0x800A87E0 */ fRand1_1_800C075C(ctx, mem); // bl 0x800C075C <fRand1_1(void)>
    /* 0x800A87E4 */ ctx.f[1] = static_cast<float>(ctx.f[30] * ctx.f[1]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmuls f1, f30, f1
    /* 0x800A87E8 */ mem.write_f32(ctx.r[31] + (344), static_cast<float>(ctx.f[1])); // stfs f1, 344(r31)
    /* 0x800A87EC */ fRand1_1_800C075C(ctx, mem); // bl 0x800C075C <fRand1_1(void)>
    /* 0x800A87F0 */ ctx.f[1] = static_cast<float>(ctx.f[30] * ctx.f[1]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmuls f1, f30, f1
    /* 0x800A87F4 */ mem.write_f32(ctx.r[31] + (348), static_cast<float>(ctx.f[1])); // stfs f1, 348(r31)
    /* 0x800A87F8 */ fRand1_1_800C075C(ctx, mem); // bl 0x800C075C <fRand1_1(void)>
    /* 0x800A87FC */ ctx.f[1] = static_cast<float>(ctx.f[30] * ctx.f[1]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmuls f1, f30, f1
    /* 0x800A8800 */ mem.write_f32(ctx.r[31] + (352), static_cast<float>(ctx.f[1])); // stfs f1, 352(r31)
    /* 0x800A8804 */ goto loc_800A8BF4; // b 0x800A8BF4 <sub_800A8BF4>
loc_800A8808:;
    /* 0x800A8808 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 1); // cmpwi cr0, r0, 1
    /* 0x800A880C */ ctx.r[21] = ctx.r[24] + (1); // addi r21, r24, 1
    /* 0x800A8810 */ if (ctx.eval_bc(4, 2)) goto loc_800A8BF4; // bc 4, 2, 0x800A8BF4
    /* 0x800A8814 */ ctx.r[3] = mem.read_u32(ctx.r[31] + (276)); // lwz r3, 276(r31)
    /* 0x800A8818 */ ctx.r[4] = ctx.r[1] + (8); // addi r4, r1, 8
    /* 0x800A881C */ ctx.r[29] = ctx.r[31] + (332); // addi r29, r31, 332
    /* 0x800A8820 */ ctx.r[30] = ctx.r[31] + (192); // addi r30, r31, 192
    /* 0x800A8824 */ ctx.call_indirect(0x80100A94u, mem); // bl 0x80100A94 <PSMTXInverse>
    /* 0x800A8828 */ ctx.r[27] = ctx.r[29]; // mr r27, r29
    /* 0x800A882C */ ctx.r[3] = ctx.r[1] + (8); // addi r3, r1, 8
    /* 0x800A8830 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800A8834 */ ctx.r[5] = ctx.r[14]; // mr r5, r14
    /* 0x800A8838 */ ctx.r[28] = ctx.r[31] + (344); // addi r28, r31, 344
    /* 0x800A883C */ ctx.call_indirect(0x80102028u, mem); // bl 0x80102028 <PSMTXMultVecSR>
    /* 0x800A8840 */ ctx.r[17] = ctx.r[30]; // mr r17, r30
    /* 0x800A8844 */ ctx.r[5] = ctx.r[30]; // mr r5, r30
    /* 0x800A8848 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A884C */ ctx.r[4] = ctx.r[14]; // mr r4, r14
    /* 0x800A8850 */ ctx.r[20] = ctx.r[28]; // mr r20, r28
    /* 0x800A8854 */ ctx.call_indirect(0x801038F4u, mem); // bl 0x801038F4 <PSVECAdd>
    /* 0x800A8858 */ ctx.r[26] = ctx.r[31] + (264); // addi r26, r31, 264
    /* 0x800A885C */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A8860 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800A8864 */ ctx.f[1] = mem.read_f32(ctx.r[25] + (168)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 168(r25)
    /* 0x800A8868 */ ctx.r[29] = ctx.r[1] + (72); // addi r29, r1, 72
    /* 0x800A886C */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
    /* 0x800A8870 */ ctx.f[13] = mem.read_f32(ctx.r[25] + (164)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 164(r25)
    /* 0x800A8874 */ ctx.r[3] = ctx.r[31] + (204); // addi r3, r31, 204
    /* 0x800A8878 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (336)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 336(r31)
    /* 0x800A887C */ ctx.r[4] = ctx.r[28]; // mr r4, r28
    /* 0x800A8880 */ ctx.r[5] = ctx.r[3]; // mr r5, r3
    /* 0x800A8884 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f13
    /* 0x800A8888 */ mem.write_f32(ctx.r[31] + (336), static_cast<float>(ctx.f[0])); // stfs f0, 336(r31)
    /* 0x800A888C */ ctx.call_indirect(0x801038F4u, mem); // bl 0x801038F4 <PSVECAdd>
    /* 0x800A8890 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (204)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 204(r31)
    /* 0x800A8894 */ ctx.cmp_f64(0, ctx.f[13], ctx.f[27]); // fcmpu cr0, f13, f27
    /* 0x800A8898 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(1)); // cror 3, 2, 1
    /* 0x800A889C */ if (ctx.eval_bc(4, 3)) goto loc_800A88C0; // bc 4, 3, 0x800A88C0
    /* 0x800A88A0 */ ctx.f[11] = mem.read_f32(ctx.r[18] + (-15136)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -15136(r18) [0x8016C4E0]
    /* 0x800A88A4 */ ctx.f[12] = mem.read_f32(ctx.r[16] + (-15140)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -15140(r16) [0x8016C4DC]
loc_800A88A8:;
    /* 0x800A88A8 */ ctx.f[0] = static_cast<float>(ctx.f[13] - ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fsubs f0, f13, f11
    /* 0x800A88AC */ ctx.f[13] = ctx.f[0]; ctx.ps0[13] = static_cast<float>(ctx.f[0]); // fmr f13, f0
    /* 0x800A88B0 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[12]); // fcmpu cr0, f0, f12
    /* 0x800A88B4 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(1)); // cror 3, 2, 1
    /* 0x800A88B8 */ if (ctx.eval_bc(12, 3)) goto loc_800A88A8; // bc 12, 3, 0x800A88A8
    /* 0x800A88BC */ mem.write_f32(ctx.r[31] + (204), static_cast<float>(ctx.f[0])); // stfs f0, 204(r31)
loc_800A88C0:;
    /* 0x800A88C0 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (204)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 204(r31)
    /* 0x800A88C4 */ ctx.cmp_f64(0, ctx.f[13], ctx.f[26]); // fcmpu cr0, f13, f26
    /* 0x800A88C8 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(0)); // cror 3, 2, 0
    /* 0x800A88CC */ if (ctx.eval_bc(4, 3)) goto loc_800A88F4; // bc 4, 3, 0x800A88F4
    /* 0x800A88D0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A88D4 */ ctx.f[11] = mem.read_f32(ctx.r[18] + (-15136)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -15136(r18) [0x8016C4E0]
    /* 0x800A88D8 */ ctx.f[12] = mem.read_f32(ctx.r[9] + (-15132)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -15132(r9) [0x8016C4E4]
loc_800A88DC:;
    /* 0x800A88DC */ ctx.f[0] = static_cast<float>(ctx.f[13] + ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f13, f11
    /* 0x800A88E0 */ ctx.f[13] = ctx.f[0]; ctx.ps0[13] = static_cast<float>(ctx.f[0]); // fmr f13, f0
    /* 0x800A88E4 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[12]); // fcmpu cr0, f0, f12
    /* 0x800A88E8 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(0)); // cror 3, 2, 0
    /* 0x800A88EC */ if (ctx.eval_bc(12, 3)) goto loc_800A88DC; // bc 12, 3, 0x800A88DC
    /* 0x800A88F0 */ mem.write_f32(ctx.r[31] + (204), static_cast<float>(ctx.f[0])); // stfs f0, 204(r31)
loc_800A88F4:;
    /* 0x800A88F4 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (208)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 208(r31)
    /* 0x800A88F8 */ ctx.cmp_f64(0, ctx.f[13], ctx.f[27]); // fcmpu cr0, f13, f27
    /* 0x800A88FC */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(1)); // cror 3, 2, 1
    /* 0x800A8900 */ if (ctx.eval_bc(4, 3)) goto loc_800A8924; // bc 4, 3, 0x800A8924
    /* 0x800A8904 */ ctx.f[11] = mem.read_f32(ctx.r[18] + (-15136)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -15136(r18) [0x8016C4E0]
    /* 0x800A8908 */ ctx.f[12] = mem.read_f32(ctx.r[16] + (-15140)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -15140(r16) [0x8016C4DC]
loc_800A890C:;
    /* 0x800A890C */ ctx.f[0] = static_cast<float>(ctx.f[13] - ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fsubs f0, f13, f11
    /* 0x800A8910 */ ctx.f[13] = ctx.f[0]; ctx.ps0[13] = static_cast<float>(ctx.f[0]); // fmr f13, f0
    /* 0x800A8914 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[12]); // fcmpu cr0, f0, f12
    /* 0x800A8918 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(1)); // cror 3, 2, 1
    /* 0x800A891C */ if (ctx.eval_bc(12, 3)) goto loc_800A890C; // bc 12, 3, 0x800A890C
    /* 0x800A8920 */ mem.write_f32(ctx.r[31] + (208), static_cast<float>(ctx.f[0])); // stfs f0, 208(r31)
loc_800A8924:;
    /* 0x800A8924 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (208)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 208(r31)
    /* 0x800A8928 */ ctx.cmp_f64(0, ctx.f[13], ctx.f[26]); // fcmpu cr0, f13, f26
    /* 0x800A892C */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(0)); // cror 3, 2, 0
    /* 0x800A8930 */ if (ctx.eval_bc(4, 3)) goto loc_800A8958; // bc 4, 3, 0x800A8958
    /* 0x800A8934 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8938 */ ctx.f[11] = mem.read_f32(ctx.r[18] + (-15136)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -15136(r18) [0x8016C4E0]
    /* 0x800A893C */ ctx.f[12] = mem.read_f32(ctx.r[9] + (-15132)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -15132(r9) [0x8016C4E4]
loc_800A8940:;
    /* 0x800A8940 */ ctx.f[0] = static_cast<float>(ctx.f[13] + ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f13, f11
    /* 0x800A8944 */ ctx.f[13] = ctx.f[0]; ctx.ps0[13] = static_cast<float>(ctx.f[0]); // fmr f13, f0
    /* 0x800A8948 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[12]); // fcmpu cr0, f0, f12
    /* 0x800A894C */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(0)); // cror 3, 2, 0
    /* 0x800A8950 */ if (ctx.eval_bc(12, 3)) goto loc_800A8940; // bc 12, 3, 0x800A8940
    /* 0x800A8954 */ mem.write_f32(ctx.r[31] + (208), static_cast<float>(ctx.f[0])); // stfs f0, 208(r31)
loc_800A8958:;
    /* 0x800A8958 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (212)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 212(r31)
    /* 0x800A895C */ ctx.cmp_f64(0, ctx.f[13], ctx.f[27]); // fcmpu cr0, f13, f27
    /* 0x800A8960 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(1)); // cror 3, 2, 1
    /* 0x800A8964 */ if (ctx.eval_bc(4, 3)) goto loc_800A8988; // bc 4, 3, 0x800A8988
    /* 0x800A8968 */ ctx.f[11] = mem.read_f32(ctx.r[18] + (-15136)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -15136(r18) [0x8016C4E0]
    /* 0x800A896C */ ctx.f[12] = mem.read_f32(ctx.r[16] + (-15140)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -15140(r16) [0x8016C4DC]
loc_800A8970:;
    /* 0x800A8970 */ ctx.f[0] = static_cast<float>(ctx.f[13] - ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fsubs f0, f13, f11
    /* 0x800A8974 */ ctx.f[13] = ctx.f[0]; ctx.ps0[13] = static_cast<float>(ctx.f[0]); // fmr f13, f0
    /* 0x800A8978 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[12]); // fcmpu cr0, f0, f12
    /* 0x800A897C */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(1)); // cror 3, 2, 1
    /* 0x800A8980 */ if (ctx.eval_bc(12, 3)) goto loc_800A8970; // bc 12, 3, 0x800A8970
    /* 0x800A8984 */ mem.write_f32(ctx.r[31] + (212), static_cast<float>(ctx.f[0])); // stfs f0, 212(r31)
loc_800A8988:;
    /* 0x800A8988 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (212)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 212(r31)
    /* 0x800A898C */ ctx.cmp_f64(0, ctx.f[13], ctx.f[26]); // fcmpu cr0, f13, f26
    /* 0x800A8990 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(0)); // cror 3, 2, 0
    /* 0x800A8994 */ if (ctx.eval_bc(4, 3)) goto loc_800A89BC; // bc 4, 3, 0x800A89BC
    /* 0x800A8998 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A899C */ ctx.f[11] = mem.read_f32(ctx.r[18] + (-15136)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -15136(r18) [0x8016C4E0]
    /* 0x800A89A0 */ ctx.f[12] = mem.read_f32(ctx.r[9] + (-15132)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -15132(r9) [0x8016C4E4]
loc_800A89A4:;
    /* 0x800A89A4 */ ctx.f[0] = static_cast<float>(ctx.f[13] + ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f13, f11
    /* 0x800A89A8 */ ctx.f[13] = ctx.f[0]; ctx.ps0[13] = static_cast<float>(ctx.f[0]); // fmr f13, f0
    /* 0x800A89AC */ ctx.cmp_f64(0, ctx.f[0], ctx.f[12]); // fcmpu cr0, f0, f12
    /* 0x800A89B0 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(0)); // cror 3, 2, 0
    /* 0x800A89B4 */ if (ctx.eval_bc(12, 3)) goto loc_800A89A4; // bc 12, 3, 0x800A89A4
    /* 0x800A89B8 */ mem.write_f32(ctx.r[31] + (212), static_cast<float>(ctx.f[0])); // stfs f0, 212(r31)
loc_800A89BC:;
    /* 0x800A89BC */ ctx.r[11] = mem.read_u32(ctx.r[31] + (264)); // lwz r11, 264(r31)
    /* 0x800A89C0 */ ctx.r[4] = ctx.r[17]; // mr r4, r17
    /* 0x800A89C4 */ ctx.r[9] = mem.read_u32(ctx.r[26] + (4)); // lwz r9, 4(r26)
    /* 0x800A89C8 */ ctx.r[5] = ctx.r[26]; // mr r5, r26
    /* 0x800A89CC */ ctx.r[0] = mem.read_u32(ctx.r[26] + (8)); // lwz r0, 8(r26)
    /* 0x800A89D0 */ ctx.r[23] = 0x00000000u; // li r23, 0
    /* 0x800A89D4 */ mem.write_u32(ctx.r[1] + (72), ctx.r[11]); // stw r11, 72(r1)
    /* 0x800A89D8 */ mem.write_u32(ctx.r[29] + (4), ctx.r[9]); // stw r9, 4(r29)
    /* 0x800A89DC */ mem.write_u32(ctx.r[29] + (8), ctx.r[0]); // stw r0, 8(r29)
    /* 0x800A89E0 */ ctx.r[3] = mem.read_u32(ctx.r[31] + (276)); // lwz r3, 276(r31)
    /* 0x800A89E4 */ ctx.call_indirect(0x80101CC8u, mem); // bl 0x80101CC8 <PSMTXMultVec>
    /* 0x800A89E8 */ ctx.r[0] = mem.read_u32(ctx.r[25] + (128)); // lwz r0, 128(r25)
    /* 0x800A89EC */ ctx.r[9] = ctx.r[0] & 0x0002u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0002
    /* 0x800A89F0 */ if (ctx.eval_bc(12, 2)) goto loc_800A8ACC; // bc 12, 2, 0x800A8ACC
    /* 0x800A89F4 */ ctx.r[30] = ctx.r[1] + (120); // addi r30, r1, 120
    /* 0x800A89F8 */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800A89FC */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A8A00 */ ctx.r[4] = ctx.r[1] + (168); // addi r4, r1, 168
    /* 0x800A8A04 */ ctx.r[6] = ctx.r[26]; // mr r6, r26
    /* 0x800A8A08 */ ctx.r[7] = 0x00002000u; // li r7, 8192
    /* 0x800A8A0C */ ScrHitCheck2_80007AE0(ctx, mem); // bl 0x80007AE0 <ScrHitCheck2(Vec *, Vec **, Vec *, Vec *, unsigned long)>
    /* 0x800A8A10 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800A8A14 */ if (ctx.eval_bc(12, 2)) goto loc_800A8BC0; // bc 12, 2, 0x800A8BC0
    /* 0x800A8A18 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (120)); // lwz r9, 120(r1)
    /* 0x800A8A1C */ ctx.r[4] = ctx.r[26]; // mr r4, r26
    /* 0x800A8A20 */ ctx.r[11] = mem.read_u32(ctx.r[30] + (8)); // lwz r11, 8(r30)
    /* 0x800A8A24 */ ctx.r[5] = ctx.r[26]; // mr r5, r26
    /* 0x800A8A28 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800A8A2C */ ctx.r[23] = 0x00000001u; // li r23, 1
    /* 0x800A8A30 */ mem.write_u32(ctx.r[31] + (264), ctx.r[9]); // stw r9, 264(r31)
    /* 0x800A8A34 */ mem.write_u32(ctx.r[26] + (4), ctx.r[0]); // stw r0, 4(r26)
    /* 0x800A8A38 */ mem.write_u32(ctx.r[26] + (8), ctx.r[11]); // stw r11, 8(r26)
    /* 0x800A8A3C */ ctx.r[3] = mem.read_u32(ctx.r[1] + (168)); // lwz r3, 168(r1)
    /* 0x800A8A40 */ ctx.call_indirect(0x801038F4u, mem); // bl 0x801038F4 <PSVECAdd>
    /* 0x800A8A44 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (332)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 332(r31)
    /* 0x800A8A48 */ ctx.r[3] = ctx.r[1] + (152); // addi r3, r1, 152
    /* 0x800A8A4C */ mem.write_f32(ctx.r[1] + (152), static_cast<float>(ctx.f[13])); // stfs f13, 152(r1)
    /* 0x800A8A50 */ ctx.f[0] = mem.read_f32(ctx.r[27] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r27)
    /* 0x800A8A54 */ mem.write_f32(ctx.r[1] + (156), static_cast<float>(ctx.f[0])); // stfs f0, 156(r1)
    /* 0x800A8A58 */ ctx.f[13] = mem.read_f32(ctx.r[27] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r27)
    /* 0x800A8A5C */ mem.write_f32(ctx.r[1] + (160), static_cast<float>(ctx.f[13])); // stfs f13, 160(r1)
    /* 0x800A8A60 */ RootSumSquare3_800CEF94(ctx, mem); // bl 0x800CEF94 <RootSumSquare3(cVec &)>
    /* 0x800A8A64 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (168)); // lwz r9, 168(r1)
    /* 0x800A8A68 */ ctx.f[31] = ctx.f[1]; ctx.ps0[31] = static_cast<float>(ctx.f[1]); // fmr f31, f1
    /* 0x800A8A6C */ ctx.r[4] = ctx.r[1] + (136); // addi r4, r1, 136
    /* 0x800A8A70 */ ctx.r[3] = ctx.r[27]; // mr r3, r27
    /* 0x800A8A74 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (0)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 0(r9)
    /* 0x800A8A78 */ ctx.r[5] = ctx.r[15]; // mr r5, r15
    /* 0x800A8A7C */ ctx.f[13] = -ctx.f[13]; ctx.ps0[13] = -ctx.ps0[13]; // fneg f13, f13
    /* 0x800A8A80 */ mem.write_f32(ctx.r[1] + (136), static_cast<float>(ctx.f[13])); // stfs f13, 136(r1)
    /* 0x800A8A84 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A8A88 */ ctx.f[0] = -ctx.f[0]; ctx.ps0[0] = -ctx.ps0[0]; // fneg f0, f0
    /* 0x800A8A8C */ mem.write_f32(ctx.r[1] + (140), static_cast<float>(ctx.f[0])); // stfs f0, 140(r1)
    /* 0x800A8A90 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A8A94 */ ctx.f[13] = -ctx.f[13]; ctx.ps0[13] = -ctx.ps0[13]; // fneg f13, f13
    /* 0x800A8A98 */ mem.write_f32(ctx.r[1] + (144), static_cast<float>(ctx.f[13])); // stfs f13, 144(r1)
    /* 0x800A8A9C */ ctx.call_indirect(0x80103D84u, mem); // bl 0x80103D84 <C_VECReflect>
    /* 0x800A8AA0 */ ctx.f[1] = mem.read_f32(ctx.r[25] + (136)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 136(r25)
    /* 0x800A8AA4 */ ctx.r[4] = ctx.r[27]; // mr r4, r27
    /* 0x800A8AA8 */ ctx.r[3] = ctx.r[15]; // mr r3, r15
    /* 0x800A8AAC */ ctx.f[1] = static_cast<float>(ctx.f[31] * ctx.f[1]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmuls f1, f31, f1
    /* 0x800A8AB0 */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
    /* 0x800A8AB4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8AB8 */ ctx.r[3] = ctx.r[20]; // mr r3, r20
    /* 0x800A8ABC */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-15128)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15128(r9) [0x8016C4E8]
    /* 0x800A8AC0 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A8AC4 */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
    /* 0x800A8AC8 */ goto loc_800A8BC0; // b 0x800A8BC0 <sub_800A8BC0>
loc_800A8ACC:;
    /* 0x800A8ACC */ ctx.r[9] = ctx.r[0] & 0x0001u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0001
    /* 0x800A8AD0 */ if (ctx.eval_bc(12, 2)) goto loc_800A8BC0; // bc 12, 2, 0x800A8BC0
    /* 0x800A8AD4 */ ctx.r[3] = ctx.r[1] + (172); // addi r3, r1, 172
    /* 0x800A8AD8 */ ctx.r[4] = ctx.r[26]; // mr r4, r26
    /* 0x800A8ADC */ GetFloor_800078EC(ctx, mem); // bl 0x800078EC <GetFloor(Vec **, Vec *)>
    /* 0x800A8AE0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8AE4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-15124)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -15124(r9) [0x8016C4EC]
    /* 0x800A8AE8 */ ctx.cmp_f64(0, ctx.f[1], ctx.f[0]); // fcmpu cr0, f1, f0
    /* 0x800A8AEC */ if (ctx.eval_bc(12, 2)) goto loc_800A8BC0; // bc 12, 2, 0x800A8BC0
    /* 0x800A8AF0 */ ctx.f[10] = mem.read_f32(ctx.r[25] + (132)); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // lfs f10, 132(r25)
    /* 0x800A8AF4 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (268)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 268(r31)
    /* 0x800A8AF8 */ ctx.f[0] = static_cast<float>(ctx.f[0] - ctx.f[10]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fsubs f0, f0, f10
    /* 0x800A8AFC */ ctx.cmp_f64(0, ctx.f[0], ctx.f[1]); // fcmpu cr0, f0, f1
    /* 0x800A8B00 */ if (ctx.eval_bc(4, 0)) goto loc_800A8BC0; // bc 4, 0, 0x800A8BC0
    /* 0x800A8B04 */ ctx.f[11] = mem.read_f32(ctx.r[25] + (136)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 136(r25)
    /* 0x800A8B08 */ ctx.f[10] = static_cast<float>(ctx.f[1] + ctx.f[10]); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // fadds f10, f1, f10
    /* 0x800A8B0C */ ctx.f[0] = mem.read_f32(ctx.r[31] + (332)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 332(r31)
    /* 0x800A8B10 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8B14 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (336)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 336(r31)
    /* 0x800A8B18 */ ctx.r[3] = ctx.r[20]; // mr r3, r20
    /* 0x800A8B1C */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f11
    /* 0x800A8B20 */ ctx.f[12] = mem.read_f32(ctx.r[31] + (340)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 340(r31)
    /* 0x800A8B24 */ mem.write_f32(ctx.r[31] + (332), static_cast<float>(ctx.f[0])); // stfs f0, 332(r31)
    /* 0x800A8B28 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A8B2C */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-15120)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15120(r9) [0x8016C4F0]
    /* 0x800A8B30 */ ctx.rlwinm(24, 24, 0u, 24u, 31u, false); // rlwinm r24, r24, 0, 24, 31
    /* 0x800A8B34 */ ctx.f[0] = mem.read_f32(ctx.r[25] + (140)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 140(r25)
    /* 0x800A8B38 */ ctx.r[23] = 0x00000001u; // li r23, 1
    /* 0x800A8B3C */ ctx.r[29] = ctx.r[25] + (178); // addi r29, r25, 178
    /* 0x800A8B40 */ ctx.r[28] = 0x00000000u; // li r28, 0
    /* 0x800A8B44 */ ctx.f[0] = -ctx.f[0]; ctx.ps0[0] = -ctx.ps0[0]; // fneg f0, f0
    /* 0x800A8B48 */ ctx.r[27] = 0x00000005u; // li r27, 5
    /* 0x800A8B4C */ ctx.f[13] = static_cast<float>(ctx.f[13] * ctx.f[0]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // fmuls f13, f13, f0
    /* 0x800A8B50 */ mem.write_f32(ctx.r[31] + (336), static_cast<float>(ctx.f[13])); // stfs f13, 336(r31)
    /* 0x800A8B54 */ ctx.f[0] = mem.read_f32(ctx.r[25] + (136)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 136(r25)
    /* 0x800A8B58 */ mem.write_f32(ctx.r[31] + (268), static_cast<float>(ctx.f[10])); // stfs f10, 268(r31)
    /* 0x800A8B5C */ ctx.f[12] = static_cast<float>(ctx.f[12] * ctx.f[0]); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // fmuls f12, f12, f0
    /* 0x800A8B60 */ mem.write_f32(ctx.r[31] + (340), static_cast<float>(ctx.f[12])); // stfs f12, 340(r31)
    /* 0x800A8B64 */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
loc_800A8B68:;
    /* 0x800A8B68 */ ctx.r[0] = mem.read_u8(ctx.r[29] + (-4)); // lbz r0, -4(r29)
    /* 0x800A8B6C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), static_cast<int32_t>(ctx.r[24])); // cmpw cr0, r0, r24
    /* 0x800A8B70 */ if (ctx.eval_bc(4, 2)) goto loc_800A8BB0; // bc 4, 2, 0x800A8BB0
    /* 0x800A8B74 */ ctx.r[3] = mem.read_u16(ctx.r[29] + (-2)); // lhz r3, -2(r29)
    /* 0x800A8B78 */ ctx.r[0] = ctx.r[3] + (-2); // addi r0, r3, -2
    /* 0x800A8B7C */ ctx.cmp_u32(0, ctx.r[0], 0x0002u); // cmplwi cr0, r0, 0x0002
    /* 0x800A8B80 */ if (ctx.eval_bc(4, 1)) goto loc_800A8BB0; // bc 4, 1, 0x800A8BB0
    /* 0x800A8B84 */ ctx.r[30] = ctx.r[25] + (180); // addi r30, r25, 180
    /* 0x800A8B88 */ ctx.r[0] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[30] + ctx.r[28]))); // lhax r0, r30, r28
    /* 0x800A8B8C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800A8B90 */ if (ctx.eval_bc(12, 2)) goto loc_800A8BB0; // bc 12, 2, 0x800A8BB0
    /* 0x800A8B94 */ ctx.r[4] = mem.read_u16(ctx.r[29] + (0)); // lhz r4, 0(r29)
    /* 0x800A8B98 */ ctx.r[5] = ctx.r[26]; // mr r5, r26
    /* 0x800A8B9C */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800A8BA0 */ SndSeCall_800CB7DC(ctx, mem); // bl 0x800CB7DC <SndSeCall(unsigned short, unsigned short, Vec *, unsigned char)>
    /* 0x800A8BA4 */ ctx.r[9] = mem.read_u16(ctx.r[30] + ctx.r[28]); // lhzx r9, r30, r28
    /* 0x800A8BA8 */ ctx.r[9] = ctx.r[9] + (-1); // addi r9, r9, -1
    /* 0x800A8BAC */ mem.write_u16(ctx.r[30] + ctx.r[28], static_cast<uint16_t>(ctx.r[9])); // sthx r9, r30, r28
loc_800A8BB0:;
    /* 0x800A8BB0 */ ctx.r[29] = ctx.r[29] + (8); // addi r29, r29, 8
    /* 0x800A8BB4 */ ctx.r[28] = ctx.r[28] + (8); // addi r28, r28, 8
    /* 0x800A8BB8 */ { uint64_t _s = static_cast<uint64_t>(ctx.r[27]) + 0xFFFFFFFFull; ctx.r[27] = static_cast<uint32_t>(_s); ctx.set_ca(_s > 0xFFFFFFFFull); } ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[27]), 0); // addic. r27, r27, -1
    /* 0x800A8BBC */ if (ctx.eval_bc(4, 2)) goto loc_800A8B68; // bc 4, 2, 0x800A8B68
loc_800A8BC0:;
    /* 0x800A8BC0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[23]), 0); // cmpwi cr0, r23, 0
    /* 0x800A8BC4 */ if (ctx.eval_bc(12, 2)) goto loc_800A8BF4; // bc 12, 2, 0x800A8BF4
    /* 0x800A8BC8 */ ctx.r[4] = ctx.r[26]; // mr r4, r26
    /* 0x800A8BCC */ ctx.r[5] = ctx.r[17]; // mr r5, r17
    /* 0x800A8BD0 */ ctx.r[3] = ctx.r[1] + (8); // addi r3, r1, 8
    /* 0x800A8BD4 */ ctx.call_indirect(0x80101CC8u, mem); // bl 0x80101CC8 <PSMTXMultVec>
    /* 0x800A8BD8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8BDC */ ctx.f[13] = mem.read_f32(ctx.r[31] + (336)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 336(r31)
    /* 0x800A8BE0 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-15116)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -15116(r9) [0x8016C4F4 /* "Ap" */]
    /* 0x800A8BE4 */ ctx.cmp_f64(0, ctx.f[13], ctx.f[0]); // fcmpu cr0, f13, f0
    /* 0x800A8BE8 */ if (ctx.eval_bc(4, 0)) goto loc_800A8BF4; // bc 4, 0, 0x800A8BF4
    /* 0x800A8BEC */ ctx.r[0] = 0x00000002u; // li r0, 2
    /* 0x800A8BF0 */ mem.write_u32(ctx.r[31] + (328), ctx.r[0]); // stw r0, 328(r31)
loc_800A8BF4:;
    /* 0x800A8BF4 */ ctx.r[0] = mem.read_u8(ctx.r[19] + (254)); // lbz r0, 254(r19)
    /* 0x800A8BF8 */ ctx.r[24] = ctx.r[21]; // mr r24, r21
    /* 0x800A8BFC */ ctx.r[31] = mem.read_u32(ctx.r[31] + (240)); // lwz r31, 240(r31)
    /* 0x800A8C00 */ ctx.cmp_u32(0, ctx.r[24], ctx.r[0]); // cmplw cr0, r24, r0
    /* 0x800A8C04 */ if (ctx.eval_bc(12, 0)) goto loc_800A8708; // bc 12, 0, 0x800A8708
loc_800A8C08:;
    /* 0x800A8C08 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (316)); // lwz r0, 316(r1)
    /* 0x800A8C0C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A8C10 */ ctx.lmw(mem, 14, ctx.r[1] + (184)); // lmw r14, 184(r1)
    /* 0x800A8C14 */ ctx.f[25] = mem.read_f64(ctx.r[1] + (256)); // lfd f25, 256(r1)
    /* 0x800A8C18 */ ctx.f[26] = mem.read_f64(ctx.r[1] + (264)); // lfd f26, 264(r1)
    /* 0x800A8C1C */ ctx.f[27] = mem.read_f64(ctx.r[1] + (272)); // lfd f27, 272(r1)
    /* 0x800A8C20 */ ctx.f[28] = mem.read_f64(ctx.r[1] + (280)); // lfd f28, 280(r1)
    /* 0x800A8C24 */ ctx.f[29] = mem.read_f64(ctx.r[1] + (288)); // lfd f29, 288(r1)
    /* 0x800A8C28 */ ctx.f[30] = mem.read_f64(ctx.r[1] + (296)); // lfd f30, 296(r1)
    /* 0x800A8C2C */ ctx.f[31] = mem.read_f64(ctx.r[1] + (304)); // lfd f31, 304(r1)
    /* 0x800A8C30 */ ctx.r[1] = ctx.r[1] + (312); // addi r1, r1, 312
    /* 0x800A8C34 */ return; // blr
}

// [0x800A8C38] cObj05::Obj05Move(void) (obj05.obj, 125 insns / 0x1F4 bytes)
void cObj05__Obj05Move_800A8C38(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A8C38 */ ctx.r[1] += (-112); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -112(r1)
    /* 0x800A8C3C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A8C40 */ mem.write_f64(ctx.r[1] + (104), ctx.f[31]); // stfd f31, 104(r1)
    /* 0x800A8C44 */ ctx.stmw(mem, 27, ctx.r[1] + (84)); // stmw r27, 84(r1)
    /* 0x800A8C48 */ mem.write_u32(ctx.r[1] + (116), ctx.r[0]); // stw r0, 116(r1)
    /* 0x800A8C4C */ ctx.r[31] = ctx.r[3]; // mr r31, r3
    /* 0x800A8C50 */ ctx.r[27] = 0x00000000u; // li r27, 0
    /* 0x800A8C54 */ ctx.r[28] = ctx.r[31] + (1224); // addi r28, r31, 1224
    /* 0x800A8C58 */ ctx.r[0] = mem.read_u32(ctx.r[28] + (128)); // lwz r0, 128(r28)
    /* 0x800A8C5C */ ctx.r[9] = ctx.r[0] & 0x0002u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0002
    /* 0x800A8C60 */ if (ctx.eval_bc(12, 2)) goto loc_800A8D44; // bc 12, 2, 0x800A8D44
    /* 0x800A8C64 */ ctx.r[30] = ctx.r[1] + (24); // addi r30, r1, 24
    /* 0x800A8C68 */ ctx.r[29] = ctx.r[31] + (192); // addi r29, r31, 192
    /* 0x800A8C6C */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A8C70 */ ctx.r[4] = ctx.r[1] + (72); // addi r4, r1, 72
    /* 0x800A8C74 */ ctx.r[5] = ctx.r[31] + (268); // addi r5, r31, 268
    /* 0x800A8C78 */ ctx.r[6] = ctx.r[29]; // mr r6, r29
    /* 0x800A8C7C */ ctx.r[7] = 0x00002000u; // li r7, 8192
    /* 0x800A8C80 */ ScrHitCheck2_80007AE0(ctx, mem); // bl 0x80007AE0 <ScrHitCheck2(Vec *, Vec **, Vec *, Vec *, unsigned long)>
    /* 0x800A8C84 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800A8C88 */ if (ctx.eval_bc(12, 2)) goto loc_800A8DC4; // bc 12, 2, 0x800A8DC4
    /* 0x800A8C8C */ ctx.r[9] = mem.read_u32(ctx.r[1] + (24)); // lwz r9, 24(r1)
    /* 0x800A8C90 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800A8C94 */ ctx.r[11] = mem.read_u32(ctx.r[30] + (8)); // lwz r11, 8(r30)
    /* 0x800A8C98 */ ctx.r[5] = ctx.r[4]; // mr r5, r4
    /* 0x800A8C9C */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800A8CA0 */ ctx.r[27] = 0x00000001u; // li r27, 1
    /* 0x800A8CA4 */ mem.write_u32(ctx.r[31] + (192), ctx.r[9]); // stw r9, 192(r31)
    /* 0x800A8CA8 */ ctx.r[30] = ctx.r[31] + (256); // addi r30, r31, 256
    /* 0x800A8CAC */ ctx.r[3] = mem.read_u32(ctx.r[1] + (72)); // lwz r3, 72(r1)
    /* 0x800A8CB0 */ mem.write_u32(ctx.r[29] + (4), ctx.r[0]); // stw r0, 4(r29)
    /* 0x800A8CB4 */ mem.write_u32(ctx.r[29] + (8), ctx.r[11]); // stw r11, 8(r29)
    /* 0x800A8CB8 */ ctx.call_indirect(0x801038F4u, mem); // bl 0x801038F4 <PSVECAdd>
    /* 0x800A8CBC */ ctx.f[13] = mem.read_f32(ctx.r[31] + (256)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 256(r31)
    /* 0x800A8CC0 */ ctx.r[3] = ctx.r[1] + (56); // addi r3, r1, 56
    /* 0x800A8CC4 */ mem.write_f32(ctx.r[1] + (56), static_cast<float>(ctx.f[13])); // stfs f13, 56(r1)
    /* 0x800A8CC8 */ ctx.f[0] = mem.read_f32(ctx.r[30] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r30)
    /* 0x800A8CCC */ mem.write_f32(ctx.r[1] + (60), static_cast<float>(ctx.f[0])); // stfs f0, 60(r1)
    /* 0x800A8CD0 */ ctx.f[13] = mem.read_f32(ctx.r[30] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r30)
    /* 0x800A8CD4 */ mem.write_f32(ctx.r[1] + (64), static_cast<float>(ctx.f[13])); // stfs f13, 64(r1)
    /* 0x800A8CD8 */ RootSumSquare3_800CEF94(ctx, mem); // bl 0x800CEF94 <RootSumSquare3(cVec &)>
    /* 0x800A8CDC */ ctx.r[9] = mem.read_u32(ctx.r[1] + (72)); // lwz r9, 72(r1)
    /* 0x800A8CE0 */ ctx.f[31] = ctx.f[1]; ctx.ps0[31] = static_cast<float>(ctx.f[1]); // fmr f31, f1
    /* 0x800A8CE4 */ ctx.r[4] = ctx.r[1] + (40); // addi r4, r1, 40
    /* 0x800A8CE8 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A8CEC */ ctx.f[13] = mem.read_f32(ctx.r[9] + (0)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 0(r9)
    /* 0x800A8CF0 */ ctx.r[5] = ctx.r[1] + (8); // addi r5, r1, 8
    /* 0x800A8CF4 */ ctx.f[13] = -ctx.f[13]; ctx.ps0[13] = -ctx.ps0[13]; // fneg f13, f13
    /* 0x800A8CF8 */ mem.write_f32(ctx.r[1] + (40), static_cast<float>(ctx.f[13])); // stfs f13, 40(r1)
    /* 0x800A8CFC */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A8D00 */ ctx.f[0] = -ctx.f[0]; ctx.ps0[0] = -ctx.ps0[0]; // fneg f0, f0
    /* 0x800A8D04 */ mem.write_f32(ctx.r[1] + (44), static_cast<float>(ctx.f[0])); // stfs f0, 44(r1)
    /* 0x800A8D08 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A8D0C */ ctx.f[13] = -ctx.f[13]; ctx.ps0[13] = -ctx.ps0[13]; // fneg f13, f13
    /* 0x800A8D10 */ mem.write_f32(ctx.r[1] + (48), static_cast<float>(ctx.f[13])); // stfs f13, 48(r1)
    /* 0x800A8D14 */ ctx.call_indirect(0x80103D84u, mem); // bl 0x80103D84 <C_VECReflect>
    /* 0x800A8D18 */ ctx.f[1] = mem.read_f32(ctx.r[28] + (140)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 140(r28)
    /* 0x800A8D1C */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A8D20 */ ctx.r[3] = ctx.r[1] + (8); // addi r3, r1, 8
    /* 0x800A8D24 */ ctx.f[1] = static_cast<float>(ctx.f[31] * ctx.f[1]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmuls f1, f31, f1
    /* 0x800A8D28 */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
    /* 0x800A8D2C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8D30 */ ctx.r[3] = ctx.r[31] + (1256); // addi r3, r31, 1256
    /* 0x800A8D34 */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-15112)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15112(r9) [0x8016C4F8]
    /* 0x800A8D38 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A8D3C */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
    /* 0x800A8D40 */ goto loc_800A8DC4; // b 0x800A8DC4 <sub_800A8DC4>
loc_800A8D44:;
    /* 0x800A8D44 */ ctx.r[9] = ctx.r[0] & 0x0001u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0001
    /* 0x800A8D48 */ if (ctx.eval_bc(12, 2)) goto loc_800A8DC4; // bc 12, 2, 0x800A8DC4
    /* 0x800A8D4C */ ctx.r[3] = ctx.r[1] + (76); // addi r3, r1, 76
    /* 0x800A8D50 */ ctx.r[4] = ctx.r[31] + (192); // addi r4, r31, 192
    /* 0x800A8D54 */ GetFloor_800078EC(ctx, mem); // bl 0x800078EC <GetFloor(Vec **, Vec *)>
    /* 0x800A8D58 */ ctx.f[10] = ctx.f[1]; ctx.ps0[10] = static_cast<float>(ctx.f[1]); // fmr f10, f1
    /* 0x800A8D5C */ ctx.f[0] = mem.read_f32(ctx.r[31] + (196)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 196(r31)
    /* 0x800A8D60 */ ctx.f[1] = mem.read_f32(ctx.r[28] + (132)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 132(r28)
    /* 0x800A8D64 */ ctx.f[0] = static_cast<float>(ctx.f[0] - ctx.f[1]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fsubs f0, f0, f1
    /* 0x800A8D68 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[10]); // fcmpu cr0, f0, f10
    /* 0x800A8D6C */ if (ctx.eval_bc(4, 0)) goto loc_800A8DC4; // bc 4, 0, 0x800A8DC4
    /* 0x800A8D70 */ ctx.f[11] = mem.read_f32(ctx.r[28] + (136)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 136(r28)
    /* 0x800A8D74 */ ctx.f[10] = static_cast<float>(ctx.f[10] + ctx.f[1]); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // fadds f10, f10, f1
    /* 0x800A8D78 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (256)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 256(r31)
    /* 0x800A8D7C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8D80 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (260)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 260(r31)
    /* 0x800A8D84 */ ctx.r[3] = ctx.r[31] + (1256); // addi r3, r31, 1256
    /* 0x800A8D88 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f11
    /* 0x800A8D8C */ ctx.f[12] = mem.read_f32(ctx.r[31] + (264)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 264(r31)
    /* 0x800A8D90 */ mem.write_f32(ctx.r[31] + (256), static_cast<float>(ctx.f[0])); // stfs f0, 256(r31)
    /* 0x800A8D94 */ ctx.r[27] = 0x00000001u; // li r27, 1
    /* 0x800A8D98 */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-15108)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15108(r9) [0x8016C4FC]
    /* 0x800A8D9C */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A8DA0 */ ctx.f[0] = mem.read_f32(ctx.r[28] + (140)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 140(r28)
    /* 0x800A8DA4 */ ctx.f[0] = -ctx.f[0]; ctx.ps0[0] = -ctx.ps0[0]; // fneg f0, f0
    /* 0x800A8DA8 */ ctx.f[13] = static_cast<float>(ctx.f[13] * ctx.f[0]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // fmuls f13, f13, f0
    /* 0x800A8DAC */ mem.write_f32(ctx.r[31] + (260), static_cast<float>(ctx.f[13])); // stfs f13, 260(r31)
    /* 0x800A8DB0 */ ctx.f[0] = mem.read_f32(ctx.r[28] + (136)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 136(r28)
    /* 0x800A8DB4 */ mem.write_f32(ctx.r[31] + (196), static_cast<float>(ctx.f[10])); // stfs f10, 196(r31)
    /* 0x800A8DB8 */ ctx.f[12] = static_cast<float>(ctx.f[12] * ctx.f[0]); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // fmuls f12, f12, f0
    /* 0x800A8DBC */ mem.write_f32(ctx.r[31] + (264), static_cast<float>(ctx.f[12])); // stfs f12, 264(r31)
    /* 0x800A8DC0 */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
loc_800A8DC4:;
    /* 0x800A8DC4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[27]), 0); // cmpwi cr0, r27, 0
    /* 0x800A8DC8 */ if (ctx.eval_bc(12, 2)) goto loc_800A8E14; // bc 12, 2, 0x800A8E14
    /* 0x800A8DCC */ ctx.r[31] = ctx.r[31] + (256); // addi r31, r31, 256
    /* 0x800A8DD0 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A8DD4 */ ctx.call_indirect(0x80103B90u, mem); // bl 0x80103B90 <PSVECMag>
    /* 0x800A8DD8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A8DDC */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-15104)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -15104(r9) [0x8016C500 /* "Ap" */]
    /* 0x800A8DE0 */ ctx.cmp_f64(0, ctx.f[1], ctx.f[0]); // fcmpu cr0, f1, f0
    /* 0x800A8DE4 */ if (ctx.eval_bc(4, 0)) goto loc_800A8E14; // bc 4, 0, 0x800A8E14
    /* 0x800A8DE8 */ ctx.r[30] = 0x80170000u; // lis r30, 0x8017
    /* 0x800A8DEC */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A8DF0 */ ctx.f[1] = mem.read_f32(ctx.r[30] + (-15100)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15100(r30) [0x8016C504]
    /* 0x800A8DF4 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A8DF8 */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
    /* 0x800A8DFC */ ctx.r[3] = ctx.r[28] + (20); // addi r3, r28, 20
    /* 0x800A8E00 */ ctx.f[1] = mem.read_f32(ctx.r[30] + (-15100)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15100(r30) [0x8016C504]
    /* 0x800A8E04 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A8E08 */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
    /* 0x800A8E0C */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800A8E10 */ mem.write_u8(ctx.r[28] + (126), static_cast<uint8_t>(ctx.r[0])); // stb r0, 126(r28)
loc_800A8E14:;
    /* 0x800A8E14 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (116)); // lwz r0, 116(r1)
    /* 0x800A8E18 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A8E1C */ ctx.lmw(mem, 27, ctx.r[1] + (84)); // lmw r27, 84(r1)
    /* 0x800A8E20 */ ctx.f[31] = mem.read_f64(ctx.r[1] + (104)); // lfd f31, 104(r1)
    /* 0x800A8E24 */ ctx.r[1] = ctx.r[1] + (112); // addi r1, r1, 112
    /* 0x800A8E28 */ return; // blr
}

// [0x800A8E2C] cObj05::Efm05RotMatrix(float (*)[2][3]) (obj05.obj, 40 insns / 0xA0 bytes)
void cObj05__Efm05RotMatrix_800A8E2C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A8E2C */ ctx.r[1] += (-88); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -88(r1)
    /* 0x800A8E30 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A8E34 */ ctx.stmw(mem, 28, ctx.r[1] + (72)); // stmw r28, 72(r1)
    /* 0x800A8E38 */ mem.write_u32(ctx.r[1] + (92), ctx.r[0]); // stw r0, 92(r1)
    /* 0x800A8E3C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800A8E40 */ ctx.r[29] = ctx.r[4]; // mr r29, r4
    /* 0x800A8E44 */ ctx.r[4] = ctx.r[30] + (192); // addi r4, r30, 192
    /* 0x800A8E48 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A8E4C */ ctx.r[5] = ctx.r[4]; // mr r5, r4
    /* 0x800A8E50 */ ctx.r[28] = ctx.r[30] + (204); // addi r28, r30, 204
    /* 0x800A8E54 */ ctx.call_indirect(0x80101CC8u, mem); // bl 0x80101CC8 <PSMTXMultVec>
    /* 0x800A8E58 */ ctx.r[4] = ctx.r[30] + (256); // addi r4, r30, 256
    /* 0x800A8E5C */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A8E60 */ ctx.r[5] = ctx.r[4]; // mr r5, r4
    /* 0x800A8E64 */ ctx.call_indirect(0x80102028u, mem); // bl 0x80102028 <PSMTXMultVecSR>
    /* 0x800A8E68 */ ctx.r[4] = ctx.r[30] + (1244); // addi r4, r30, 1244
    /* 0x800A8E6C */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A8E70 */ ctx.r[5] = ctx.r[4]; // mr r5, r4
    /* 0x800A8E74 */ ctx.call_indirect(0x80102028u, mem); // bl 0x80102028 <PSMTXMultVecSR>
    /* 0x800A8E78 */ ctx.f[13] = mem.read_f32(ctx.r[30] + (204)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 204(r30)
    /* 0x800A8E7C */ ctx.r[3] = ctx.r[1] + (8); // addi r3, r1, 8
    /* 0x800A8E80 */ ctx.r[4] = ctx.r[1] + (56); // addi r4, r1, 56
    /* 0x800A8E84 */ mem.write_f32(ctx.r[1] + (56), static_cast<float>(ctx.f[13])); // stfs f13, 56(r1)
    /* 0x800A8E88 */ ctx.f[0] = mem.read_f32(ctx.r[28] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r28)
    /* 0x800A8E8C */ mem.write_f32(ctx.r[1] + (60), static_cast<float>(ctx.f[0])); // stfs f0, 60(r1)
    /* 0x800A8E90 */ ctx.f[13] = mem.read_f32(ctx.r[28] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r28)
    /* 0x800A8E94 */ mem.write_f32(ctx.r[1] + (64), static_cast<float>(ctx.f[13])); // stfs f13, 64(r1)
    /* 0x800A8E98 */ RotMatrix_8009E1D0(ctx, mem); // bl 0x8009E1D0 <RotMatrix(float (*)[3], cVec &)>
    /* 0x800A8E9C */ ctx.r[4] = ctx.r[1] + (8); // addi r4, r1, 8
    /* 0x800A8EA0 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A8EA4 */ ctx.r[5] = ctx.r[4]; // mr r5, r4
    /* 0x800A8EA8 */ ctx.call_indirect(0x80100470u, mem); // bl 0x80100470 <PSMTXConcat>
    /* 0x800A8EAC */ ctx.r[4] = ctx.r[28]; // mr r4, r28
    /* 0x800A8EB0 */ ctx.r[3] = ctx.r[1] + (8); // addi r3, r1, 8
    /* 0x800A8EB4 */ Matrix2AxisAngle_8009D9D4(ctx, mem); // bl 0x8009D9D4 <Matrix2AxisAngle(float (*)[3], Vec &)>
    /* 0x800A8EB8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (92)); // lwz r0, 92(r1)
    /* 0x800A8EBC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A8EC0 */ ctx.lmw(mem, 28, ctx.r[1] + (72)); // lmw r28, 72(r1)
    /* 0x800A8EC4 */ ctx.r[1] = ctx.r[1] + (88); // addi r1, r1, 88
    /* 0x800A8EC8 */ return; // blr
}

// [0x800A8ECC] cObj05::Initialize(void) (obj05.obj, 1 insns / 0x4 bytes)
void cObj05__Initialize_800A8ECC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A8ECC */ return; // blr
}

// [0x800A8ED0] cObj05::Release(void) (obj05.obj, 8 insns / 0x20 bytes)
void cObj05__Release_800A8ED0(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A8ED0 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800A8ED4 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A8ED8 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800A8EDC */ cObj05__PushObj05_800A8EF0(ctx, mem); // bl 0x800A8EF0 <cObj05::PushObj05(void)>
    /* 0x800A8EE0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800A8EE4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A8EE8 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800A8EEC */ return; // blr
}

// [0x800A8EF0] cObj05::PushObj05(void) (obj05.obj, 43 insns / 0xAC bytes)
void cObj05__PushObj05_800A8EF0(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A8EF0 */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800A8EF4 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A8EF8 */ mem.write_u32(ctx.r[1] + (12), ctx.r[31]); // stw r31, 12(r1)
    /* 0x800A8EFC */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800A8F00 */ ctx.r[31] = ctx.r[3]; // mr r31, r3
    /* 0x800A8F04 */ PushObj_800749C8(ctx, mem); // bl 0x800749C8 <PushObj(cObj *)>
    /* 0x800A8F08 */ ctx.r[10] = mem.read_u32(ctx.r[31] + (1216)); // lwz r10, 1216(r31)
    /* 0x800A8F0C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // cmpwi cr0, r10, 0
    /* 0x800A8F10 */ if (ctx.eval_bc(12, 2)) goto loc_800A8F64; // bc 12, 2, 0x800A8F64
    /* 0x800A8F14 */ ctx.r[11] = mem.read_u32(ctx.r[31] + (1212)); // lwz r11, 1212(r31)
    /* 0x800A8F18 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800A8F1C */ if (ctx.eval_bc(12, 2)) goto loc_800A8F34; // bc 12, 2, 0x800A8F34
    /* 0x800A8F20 */ mem.write_u32(ctx.r[11] + (1216), ctx.r[10]); // stw r10, 1216(r11)
    /* 0x800A8F24 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (1212)); // lwz r0, 1212(r31)
    /* 0x800A8F28 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (1216)); // lwz r9, 1216(r31)
    /* 0x800A8F2C */ mem.write_u32(ctx.r[9] + (1212), ctx.r[0]); // stw r0, 1212(r9)
    /* 0x800A8F30 */ goto loc_800A8F88; // b 0x800A8F88 <sub_800A8F88>
loc_800A8F34:;
    /* 0x800A8F34 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (1220)); // lwz r9, 1220(r31)
    /* 0x800A8F38 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800A8F3C */ if (ctx.eval_bc(12, 2)) goto loc_800A8F5C; // bc 12, 2, 0x800A8F5C
    /* 0x800A8F40 */ mem.write_u32(ctx.r[9] + (36), ctx.r[10]); // stw r10, 36(r9)
    /* 0x800A8F44 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (1216)); // lwz r9, 1216(r31)
    /* 0x800A8F48 */ mem.write_u32(ctx.r[9] + (1212), ctx.r[11]); // stw r11, 1212(r9)
    /* 0x800A8F4C */ ctx.r[0] = mem.read_u32(ctx.r[31] + (1220)); // lwz r0, 1220(r31)
    /* 0x800A8F50 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (1216)); // lwz r9, 1216(r31)
    /* 0x800A8F54 */ mem.write_u32(ctx.r[9] + (1220), ctx.r[0]); // stw r0, 1220(r9)
    /* 0x800A8F58 */ goto loc_800A8F88; // b 0x800A8F88 <sub_800A8F88>
loc_800A8F5C:;
    /* 0x800A8F5C */ mem.write_u32(ctx.r[10] + (1212), ctx.r[9]); // stw r9, 1212(r10)
    /* 0x800A8F60 */ goto loc_800A8F88; // b 0x800A8F88 <sub_800A8F88>
loc_800A8F64:;
    /* 0x800A8F64 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (1212)); // lwz r9, 1212(r31)
    /* 0x800A8F68 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800A8F6C */ if (ctx.eval_bc(12, 2)) goto loc_800A8F78; // bc 12, 2, 0x800A8F78
    /* 0x800A8F70 */ mem.write_u32(ctx.r[9] + (1216), ctx.r[10]); // stw r10, 1216(r9)
    /* 0x800A8F74 */ goto loc_800A8F88; // b 0x800A8F88 <sub_800A8F88>
loc_800A8F78:;
    /* 0x800A8F78 */ ctx.r[3] = mem.read_u32(ctx.r[31] + (1220)); // lwz r3, 1220(r31)
    /* 0x800A8F7C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800A8F80 */ if (ctx.eval_bc(12, 2)) goto loc_800A8F88; // bc 12, 2, 0x800A8F88
    /* 0x800A8F84 */ mem.write_u32(ctx.r[3] + (36), ctx.r[9]); // stw r9, 36(r3)
loc_800A8F88:;
    /* 0x800A8F88 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800A8F8C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A8F90 */ ctx.r[31] = mem.read_u32(ctx.r[1] + (12)); // lwz r31, 12(r1)
    /* 0x800A8F94 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800A8F98 */ return; // blr
}

// [0x800A8F9C] cObj05::initObj05(tagESPSEQ_TBL *, float (*)[2][3], unsigned long *) (obj05.obj, 392 insns / 0x620 bytes)
void cObj05__initObj05_800A8F9C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A8F9C */ ctx.r[1] += (-104); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -104(r1)
    /* 0x800A8FA0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A8FA4 */ ctx.stmw(mem, 14, ctx.r[1] + (32)); // stmw r14, 32(r1)
    /* 0x800A8FA8 */ mem.write_u32(ctx.r[1] + (108), ctx.r[0]); // stw r0, 108(r1)
    /* 0x800A8FAC */ ctx.r[8] = 0x00000006u; // li r8, 6
    /* 0x800A8FB0 */ ctx.r[27] = ctx.r[3]; // mr r27, r3
    /* 0x800A8FB4 */ ctx.ctr = ctx.r[8]; // mtctr r8
    /* 0x800A8FB8 */ ctx.r[31] = ctx.r[4]; // mr r31, r4
    /* 0x800A8FBC */ ctx.r[29] = ctx.r[27] + (1224); // addi r29, r27, 1224
    /* 0x800A8FC0 */ ctx.r[28] = ctx.r[6]; // mr r28, r6
    /* 0x800A8FC4 */ ctx.r[0] = 0x00000003u; // li r0, 3
    /* 0x800A8FC8 */ ctx.r[9] = ctx.r[27] + (1444); // addi r9, r27, 1444
loc_800A8FCC:;
    /* 0x800A8FCC */ mem.write_u16(ctx.r[9] + (0), static_cast<uint16_t>(ctx.r[0])); // sth r0, 0(r9)
    /* 0x800A8FD0 */ ctx.r[9] = ctx.r[9] + (-8); // addi r9, r9, -8
    /* 0x800A8FD4 */ if (ctx.eval_bc(16, 0)) goto loc_800A8FCC; // bc 16, 0, 0x800A8FCC
    /* 0x800A8FD8 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800A8FDC */ ctx.r[11] = ctx.r[29] + (148); // addi r11, r29, 148
    /* 0x800A8FE0 */ mem.write_u32(ctx.r[27] + (1216), ctx.r[0]); // stw r0, 1216(r27)
    /* 0x800A8FE4 */ ctx.r[9] = ctx.r[31] + (124); // addi r9, r31, 124
    /* 0x800A8FE8 */ mem.write_u32(ctx.r[27] + (1212), ctx.r[0]); // stw r0, 1212(r27)
    /* 0x800A8FEC */ ctx.r[8] = ctx.r[31] + (216); // addi r8, r31, 216
    /* 0x800A8FF0 */ ctx.r[26] = ctx.r[27] + (192); // addi r26, r27, 192
    /* 0x800A8FF4 */ ctx.r[10] = ctx.r[31] + (12); // addi r10, r31, 12
    /* 0x800A8FF8 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (2)); // lbz r0, 2(r31)
    /* 0x800A8FFC */ ctx.r[21] = ctx.r[31] + (24); // addi r21, r31, 24
    /* 0x800A9000 */ ctx.r[24] = ctx.r[27] + (256); // addi r24, r27, 256
    /* 0x800A9004 */ ctx.r[20] = ctx.r[31] + (36); // addi r20, r31, 36
    /* 0x800A9008 */ mem.write_u8(ctx.r[29] + (12), static_cast<uint8_t>(ctx.r[0])); // stb r0, 12(r29)
    /* 0x800A900C */ ctx.r[19] = ctx.r[31] + (52); // addi r19, r31, 52
    /* 0x800A9010 */ mem.write_u32(ctx.r[1] + (12), ctx.r[11]); // stw r11, 12(r1)
    /* 0x800A9014 */ ctx.r[22] = ctx.r[29] + (20); // addi r22, r29, 20
    /* 0x800A9018 */ mem.write_u32(ctx.r[1] + (8), ctx.r[9]); // stw r9, 8(r1)
    /* 0x800A901C */ ctx.r[11] = 0x00000005u; // li r11, 5
    /* 0x800A9020 */ ctx.r[9] = ctx.r[31] + (228); // addi r9, r31, 228
    /* 0x800A9024 */ ctx.ctr = ctx.r[11]; // mtctr r11
    /* 0x800A9028 */ mem.write_u32(ctx.r[1] + (20), ctx.r[9]); // stw r9, 20(r1)
    /* 0x800A902C */ ctx.r[18] = ctx.r[31] + (64); // addi r18, r31, 64
    /* 0x800A9030 */ mem.write_u32(ctx.r[1] + (16), ctx.r[8]); // stw r8, 16(r1)
    /* 0x800A9034 */ ctx.r[17] = ctx.r[31] + (76); // addi r17, r31, 76
    /* 0x800A9038 */ ctx.r[25] = ctx.r[27] + (204); // addi r25, r27, 204
    /* 0x800A903C */ ctx.r[16] = ctx.r[31] + (88); // addi r16, r31, 88
    /* 0x800A9040 */ ctx.r[14] = ctx.r[31] + (100); // addi r14, r31, 100
    /* 0x800A9044 */ ctx.r[23] = ctx.r[29] + (32); // addi r23, r29, 32
    /* 0x800A9048 */ ctx.r[30] = ctx.r[31] + (112); // addi r30, r31, 112
    /* 0x800A904C */ ctx.r[15] = ctx.r[29] + (136); // addi r15, r29, 136
    /* 0x800A9050 */ ctx.r[0] = 0x000000FFu; // li r0, 255
    /* 0x800A9054 */ ctx.r[9] = ctx.r[29] + (206); // addi r9, r29, 206
loc_800A9058:;
    /* 0x800A9058 */ mem.write_u8(ctx.r[9] + (0), static_cast<uint8_t>(ctx.r[0])); // stb r0, 0(r9)
    /* 0x800A905C */ ctx.r[9] = ctx.r[9] + (-8); // addi r9, r9, -8
    /* 0x800A9060 */ if (ctx.eval_bc(16, 0)) goto loc_800A9058; // bc 16, 0, 0x800A9058
    /* 0x800A9064 */ ctx.r[9] = mem.read_u8(ctx.r[31] + (7)); // lbz r9, 7(r31)
    /* 0x800A9068 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A906C */ mem.write_u8(ctx.r[29] + (125), static_cast<uint8_t>(ctx.r[9])); // stb r9, 125(r29)
    /* 0x800A9070 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (8)); // lwz r0, 8(r31)
    /* 0x800A9074 */ mem.write_u32(ctx.r[29] + (128), ctx.r[0]); // stw r0, 128(r29)
    /* 0x800A9078 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (12)); // lwz r9, 12(r31)
    /* 0x800A907C */ ctx.r[11] = mem.read_u32(ctx.r[10] + (8)); // lwz r11, 8(r10)
    /* 0x800A9080 */ ctx.r[0] = mem.read_u32(ctx.r[10] + (4)); // lwz r0, 4(r10)
    /* 0x800A9084 */ mem.write_u32(ctx.r[27] + (192), ctx.r[9]); // stw r9, 192(r27)
    /* 0x800A9088 */ mem.write_u32(ctx.r[26] + (4), ctx.r[0]); // stw r0, 4(r26)
    /* 0x800A908C */ mem.write_u32(ctx.r[26] + (8), ctx.r[11]); // stw r11, 8(r26)
    /* 0x800A9090 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A9094 */ ctx.f[13] = mem.read_f32(ctx.r[27] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r27)
    /* 0x800A9098 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A909C */ ctx.f[0] = mem.read_f32(ctx.r[31] + (24)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 24(r31)
    /* 0x800A90A0 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A90A4 */ mem.write_f32(ctx.r[27] + (192), static_cast<float>(ctx.f[0])); // stfs f0, 192(r27)
    /* 0x800A90A8 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A90AC */ ctx.f[13] = mem.read_f32(ctx.r[26] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r26)
    /* 0x800A90B0 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A90B4 */ ctx.f[0] = mem.read_f32(ctx.r[21] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r21)
    /* 0x800A90B8 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A90BC */ mem.write_f32(ctx.r[26] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r26)
    /* 0x800A90C0 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A90C4 */ ctx.f[13] = mem.read_f32(ctx.r[26] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r26)
    /* 0x800A90C8 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A90CC */ ctx.f[0] = mem.read_f32(ctx.r[21] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r21)
    /* 0x800A90D0 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A90D4 */ mem.write_f32(ctx.r[26] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r26)
    /* 0x800A90D8 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (36)); // lwz r9, 36(r31)
    /* 0x800A90DC */ ctx.r[11] = mem.read_u32(ctx.r[20] + (8)); // lwz r11, 8(r20)
    /* 0x800A90E0 */ ctx.r[0] = mem.read_u32(ctx.r[20] + (4)); // lwz r0, 4(r20)
    /* 0x800A90E4 */ mem.write_u32(ctx.r[27] + (256), ctx.r[9]); // stw r9, 256(r27)
    /* 0x800A90E8 */ mem.write_u32(ctx.r[24] + (4), ctx.r[0]); // stw r0, 4(r24)
    /* 0x800A90EC */ mem.write_u32(ctx.r[24] + (8), ctx.r[11]); // stw r11, 8(r24)
    /* 0x800A90F0 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A90F4 */ ctx.f[13] = mem.read_f32(ctx.r[27] + (256)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 256(r27)
    /* 0x800A90F8 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A90FC */ ctx.f[0] = mem.read_f32(ctx.r[31] + (52)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 52(r31)
    /* 0x800A9100 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A9104 */ mem.write_f32(ctx.r[27] + (256), static_cast<float>(ctx.f[0])); // stfs f0, 256(r27)
    /* 0x800A9108 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A910C */ ctx.f[13] = mem.read_f32(ctx.r[24] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r24)
    /* 0x800A9110 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A9114 */ ctx.f[0] = mem.read_f32(ctx.r[19] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r19)
    /* 0x800A9118 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A911C */ mem.write_f32(ctx.r[24] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r24)
    /* 0x800A9120 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A9124 */ ctx.f[13] = mem.read_f32(ctx.r[24] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r24)
    /* 0x800A9128 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A912C */ ctx.f[0] = mem.read_f32(ctx.r[19] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r19)
    /* 0x800A9130 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A9134 */ mem.write_f32(ctx.r[24] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r24)
    /* 0x800A9138 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (48)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 48(r31)
    /* 0x800A913C */ mem.write_f32(ctx.r[29] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r29)
    /* 0x800A9140 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (64)); // lwz r9, 64(r31)
    /* 0x800A9144 */ ctx.r[11] = mem.read_u32(ctx.r[18] + (8)); // lwz r11, 8(r18)
    /* 0x800A9148 */ ctx.r[0] = mem.read_u32(ctx.r[18] + (4)); // lwz r0, 4(r18)
    /* 0x800A914C */ mem.write_u32(ctx.r[29] + (20), ctx.r[9]); // stw r9, 20(r29)
    /* 0x800A9150 */ mem.write_u32(ctx.r[22] + (4), ctx.r[0]); // stw r0, 4(r22)
    /* 0x800A9154 */ mem.write_u32(ctx.r[22] + (8), ctx.r[11]); // stw r11, 8(r22)
    /* 0x800A9158 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A915C */ ctx.f[13] = mem.read_f32(ctx.r[29] + (20)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 20(r29)
    /* 0x800A9160 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A9164 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (76)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 76(r31)
    /* 0x800A9168 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A916C */ mem.write_f32(ctx.r[29] + (20), static_cast<float>(ctx.f[0])); // stfs f0, 20(r29)
    /* 0x800A9170 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A9174 */ ctx.f[13] = mem.read_f32(ctx.r[22] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r22)
    /* 0x800A9178 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A917C */ ctx.f[0] = mem.read_f32(ctx.r[17] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r17)
    /* 0x800A9180 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A9184 */ mem.write_f32(ctx.r[22] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r22)
    /* 0x800A9188 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A918C */ ctx.f[13] = mem.read_f32(ctx.r[22] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r22)
    /* 0x800A9190 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A9194 */ ctx.f[0] = mem.read_f32(ctx.r[17] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r17)
    /* 0x800A9198 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A919C */ mem.write_f32(ctx.r[22] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r22)
    /* 0x800A91A0 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (88)); // lwz r9, 88(r31)
    /* 0x800A91A4 */ ctx.r[11] = mem.read_u32(ctx.r[16] + (8)); // lwz r11, 8(r16)
    /* 0x800A91A8 */ ctx.r[0] = mem.read_u32(ctx.r[16] + (4)); // lwz r0, 4(r16)
    /* 0x800A91AC */ mem.write_u32(ctx.r[27] + (204), ctx.r[9]); // stw r9, 204(r27)
    /* 0x800A91B0 */ mem.write_u32(ctx.r[25] + (4), ctx.r[0]); // stw r0, 4(r25)
    /* 0x800A91B4 */ mem.write_u32(ctx.r[25] + (8), ctx.r[11]); // stw r11, 8(r25)
    /* 0x800A91B8 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A91BC */ ctx.f[13] = mem.read_f32(ctx.r[27] + (204)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 204(r27)
    /* 0x800A91C0 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A91C4 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (100)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 100(r31)
    /* 0x800A91C8 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A91CC */ mem.write_f32(ctx.r[27] + (204), static_cast<float>(ctx.f[0])); // stfs f0, 204(r27)
    /* 0x800A91D0 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A91D4 */ ctx.f[13] = mem.read_f32(ctx.r[25] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r25)
    /* 0x800A91D8 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A91DC */ ctx.f[0] = mem.read_f32(ctx.r[14] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r14)
    /* 0x800A91E0 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A91E4 */ mem.write_f32(ctx.r[25] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r25)
    /* 0x800A91E8 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A91EC */ ctx.f[13] = mem.read_f32(ctx.r[25] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r25)
    /* 0x800A91F0 */ ctx.r[8] = 0x80170000u; // lis r8, 0x8017
    /* 0x800A91F4 */ ctx.f[0] = mem.read_f32(ctx.r[14] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r14)
    /* 0x800A91F8 */ ctx.r[3] = ctx.r[25]; // mr r3, r25
    /* 0x800A91FC */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A9200 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A9204 */ ctx.f[1] = mem.read_f32(ctx.r[8] + (-15096)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15096(r8) [0x8016C508]
    /* 0x800A9208 */ mem.write_f32(ctx.r[25] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r25)
    /* 0x800A920C */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
    /* 0x800A9210 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (112)); // lwz r9, 112(r31)
    /* 0x800A9214 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A9218 */ ctx.r[11] = mem.read_u32(ctx.r[30] + (8)); // lwz r11, 8(r30)
    /* 0x800A921C */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800A9220 */ mem.write_u32(ctx.r[29] + (32), ctx.r[9]); // stw r9, 32(r29)
    /* 0x800A9224 */ mem.write_u32(ctx.r[23] + (4), ctx.r[0]); // stw r0, 4(r23)
    /* 0x800A9228 */ mem.write_u32(ctx.r[23] + (8), ctx.r[11]); // stw r11, 8(r23)
    /* 0x800A922C */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A9230 */ ctx.f[13] = mem.read_f32(ctx.r[29] + (32)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 32(r29)
    /* 0x800A9234 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A9238 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (124)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 124(r31)
    /* 0x800A923C */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A9240 */ mem.write_f32(ctx.r[29] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r29)
    /* 0x800A9244 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A9248 */ ctx.r[8] = mem.read_u32(ctx.r[1] + (8)); // lwz r8, 8(r1)
    /* 0x800A924C */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A9250 */ ctx.f[13] = mem.read_f32(ctx.r[23] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r23)
    /* 0x800A9254 */ ctx.f[0] = mem.read_f32(ctx.r[8] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r8)
    /* 0x800A9258 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A925C */ mem.write_f32(ctx.r[23] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r23)
    /* 0x800A9260 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A9264 */ ctx.r[8] = mem.read_u32(ctx.r[1] + (8)); // lwz r8, 8(r1)
    /* 0x800A9268 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A926C */ ctx.f[13] = mem.read_f32(ctx.r[23] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r23)
    /* 0x800A9270 */ ctx.r[3] = ctx.r[23]; // mr r3, r23
    /* 0x800A9274 */ ctx.f[0] = mem.read_f32(ctx.r[8] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r8)
    /* 0x800A9278 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A927C */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A9280 */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-15096)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15096(r9) [0x8016C508]
    /* 0x800A9284 */ mem.write_f32(ctx.r[23] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r23)
    /* 0x800A9288 */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
    /* 0x800A928C */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A9290 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A9294 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (144)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 144(r31)
    /* 0x800A9298 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A929C */ ctx.f[0] = mem.read_f32(ctx.r[31] + (136)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 136(r31)
    /* 0x800A92A0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A92A4 */ ctx.f[10] = mem.read_f32(ctx.r[9] + (-15092)); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // lfs f10, -15092(r9) [0x8016C50C]
    /* 0x800A92A8 */ ctx.f[13] = static_cast<float>(ctx.f[13] * ctx.f[1]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // fmuls f13, f13, f1
    /* 0x800A92AC */ ctx.f[11] = mem.read_f32(ctx.r[11] + (-15088)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -15088(r11) [0x8016C510]
    /* 0x800A92B0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A92B4 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[10] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f10, f13
    /* 0x800A92B8 */ ctx.f[12] = mem.read_f64(ctx.r[9] + (-15080)); // lfd f12, -15080(r9) [0x8016C518 /* "C0" */]
    /* 0x800A92BC */ mem.write_f32(ctx.r[29] + (44), static_cast<float>(ctx.f[0])); // stfs f0, 44(r29)
    /* 0x800A92C0 */ ctx.r[7] = 0x43300000u; // lis r7, 0x4330
    /* 0x800A92C4 */ ctx.r[11] = ctx.r[10]; // mr r11, r10
    /* 0x800A92C8 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (140)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 140(r31)
    /* 0x800A92CC */ ctx.r[8] = ctx.r[10]; // mr r8, r10
    /* 0x800A92D0 */ mem.write_f32(ctx.r[29] + (52), static_cast<float>(ctx.f[11])); // stfs f11, 52(r29)
    /* 0x800A92D4 */ ctx.r[6] = ctx.r[10]; // mr r6, r10
    /* 0x800A92D8 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[10] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f10, f13
    /* 0x800A92DC */ ctx.r[5] = ctx.r[10]; // mr r5, r10
    /* 0x800A92E0 */ mem.write_f32(ctx.r[29] + (48), static_cast<float>(ctx.f[0])); // stfs f0, 48(r29)
    /* 0x800A92E4 */ ctx.r[4] = ctx.r[10]; // mr r4, r10
    /* 0x800A92E8 */ ctx.r[3] = ctx.r[10]; // mr r3, r10
    /* 0x800A92EC */ ctx.f[13] = mem.read_f32(ctx.r[31] + (148)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 148(r31)
    /* 0x800A92F0 */ mem.write_f32(ctx.r[29] + (56), static_cast<float>(ctx.f[13])); // stfs f13, 56(r29)
    /* 0x800A92F4 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (152)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 152(r31)
    /* 0x800A92F8 */ mem.write_f32(ctx.r[29] + (60), static_cast<float>(ctx.f[0])); // stfs f0, 60(r29)
    /* 0x800A92FC */ ctx.r[0] = mem.read_u8(ctx.r[31] + (156)); // lbz r0, 156(r31)
    /* 0x800A9300 */ ctx.r[9] = ctx.r[0]; // mr r9, r0
    /* 0x800A9304 */ mem.write_u8(ctx.r[29] + (64), static_cast<uint8_t>(ctx.r[0])); // stb r0, 64(r29)
    /* 0x800A9308 */ mem.write_u32(ctx.r[1] + (28), ctx.r[9]); // stw r9, 28(r1)
    /* 0x800A930C */ mem.write_u32(ctx.r[1] + (24), ctx.r[7]); // stw r7, 24(r1)
    /* 0x800A9310 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (24)); // lfd f0, 24(r1)
    /* 0x800A9314 */ ctx.f[0] = ctx.f[0] - ctx.f[12]; // fsub f0, f0, f12
    /* 0x800A9318 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800A931C */ mem.write_f32(ctx.r[29] + (68), static_cast<float>(ctx.f[0])); // stfs f0, 68(r29)
    /* 0x800A9320 */ ctx.f[13] = ctx.f[0]; ctx.ps0[13] = static_cast<float>(ctx.f[0]); // fmr f13, f0
    /* 0x800A9324 */ { int32_t iv = static_cast<int32_t>(ctx.f[13]); uint64_t u = static_cast<uint32_t>(iv); std::memcpy(&ctx.f[11], &u, 8); } // fctiwz f11, f13
    /* 0x800A9328 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (157)); // lbz r0, 157(r31)
    /* 0x800A932C */ ctx.r[9] = ctx.r[0]; // mr r9, r0
    /* 0x800A9330 */ mem.write_u8(ctx.r[29] + (65), static_cast<uint8_t>(ctx.r[0])); // stb r0, 65(r29)
    /* 0x800A9334 */ mem.write_u32(ctx.r[1] + (28), ctx.r[9]); // stw r9, 28(r1)
    /* 0x800A9338 */ mem.write_u32(ctx.r[1] + (24), ctx.r[7]); // stw r7, 24(r1)
    /* 0x800A933C */ ctx.f[0] = mem.read_f64(ctx.r[1] + (24)); // lfd f0, 24(r1)
    /* 0x800A9340 */ ctx.f[0] = ctx.f[0] - ctx.f[12]; // fsub f0, f0, f12
    /* 0x800A9344 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800A9348 */ mem.write_f32(ctx.r[29] + (72), static_cast<float>(ctx.f[0])); // stfs f0, 72(r29)
    /* 0x800A934C */ ctx.r[0] = mem.read_u8(ctx.r[31] + (158)); // lbz r0, 158(r31)
    /* 0x800A9350 */ ctx.r[9] = ctx.r[0]; // mr r9, r0
    /* 0x800A9354 */ mem.write_u8(ctx.r[29] + (66), static_cast<uint8_t>(ctx.r[0])); // stb r0, 66(r29)
    /* 0x800A9358 */ mem.write_u32(ctx.r[1] + (28), ctx.r[9]); // stw r9, 28(r1)
    /* 0x800A935C */ mem.write_u32(ctx.r[1] + (24), ctx.r[7]); // stw r7, 24(r1)
    /* 0x800A9360 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (24)); // lfd f0, 24(r1)
    /* 0x800A9364 */ ctx.f[0] = ctx.f[0] - ctx.f[12]; // fsub f0, f0, f12
    /* 0x800A9368 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800A936C */ mem.write_f32(ctx.r[29] + (76), static_cast<float>(ctx.f[0])); // stfs f0, 76(r29)
    /* 0x800A9370 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (159)); // lbz r0, 159(r31)
    /* 0x800A9374 */ ctx.r[9] = ctx.r[0]; // mr r9, r0
    /* 0x800A9378 */ mem.write_u8(ctx.r[29] + (67), static_cast<uint8_t>(ctx.r[0])); // stb r0, 67(r29)
    /* 0x800A937C */ mem.write_u32(ctx.r[1] + (28), ctx.r[9]); // stw r9, 28(r1)
    /* 0x800A9380 */ mem.write_u32(ctx.r[1] + (24), ctx.r[7]); // stw r7, 24(r1)
    /* 0x800A9384 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (24)); // lfd f0, 24(r1)
    /* 0x800A9388 */ mem.write_f64(ctx.r[1] + (24), ctx.f[11]); // stfd f11, 24(r1)
    /* 0x800A938C */ ctx.f[0] = ctx.f[0] - ctx.f[12]; // fsub f0, f0, f12
    /* 0x800A9390 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800A9394 */ ctx.r[5] = mem.read_u32(ctx.r[1] + (28)); // lwz r5, 28(r1)
    /* 0x800A9398 */ mem.write_f32(ctx.r[29] + (80), static_cast<float>(ctx.f[0])); // stfs f0, 80(r29)
    /* 0x800A939C */ ctx.f[13] = mem.read_f32(ctx.r[31] + (160)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 160(r31)
    /* 0x800A93A0 */ mem.write_f32(ctx.r[29] + (84), static_cast<float>(ctx.f[13])); // stfs f13, 84(r29)
    /* 0x800A93A4 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (164)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 164(r31)
    /* 0x800A93A8 */ mem.write_f32(ctx.r[29] + (88), static_cast<float>(ctx.f[0])); // stfs f0, 88(r29)
    /* 0x800A93AC */ ctx.f[13] = mem.read_f32(ctx.r[31] + (168)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 168(r31)
    /* 0x800A93B0 */ mem.write_f32(ctx.r[29] + (92), static_cast<float>(ctx.f[13])); // stfs f13, 92(r29)
    /* 0x800A93B4 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (172)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 172(r31)
    /* 0x800A93B8 */ mem.write_f32(ctx.r[29] + (96), static_cast<float>(ctx.f[0])); // stfs f0, 96(r29)
    /* 0x800A93BC */ ctx.r[0] = mem.read_u16(ctx.r[31] + (176)); // lhz r0, 176(r31)
    /* 0x800A93C0 */ mem.write_u16(ctx.r[29] + (104), static_cast<uint16_t>(ctx.r[0])); // sth r0, 104(r29)
    /* 0x800A93C4 */ ctx.r[9] = mem.read_u16(ctx.r[31] + (178)); // lhz r9, 178(r31)
    /* 0x800A93C8 */ mem.write_u16(ctx.r[29] + (106), static_cast<uint16_t>(ctx.r[9])); // sth r9, 106(r29)
    /* 0x800A93CC */ ctx.r[0] = mem.read_u16(ctx.r[31] + (180)); // lhz r0, 180(r31)
    /* 0x800A93D0 */ mem.write_u16(ctx.r[29] + (108), static_cast<uint16_t>(ctx.r[0])); // sth r0, 108(r29)
    /* 0x800A93D4 */ ctx.r[9] = mem.read_u16(ctx.r[31] + (182)); // lhz r9, 182(r31)
    /* 0x800A93D8 */ mem.write_u16(ctx.r[29] + (110), static_cast<uint16_t>(ctx.r[9])); // sth r9, 110(r29)
    /* 0x800A93DC */ ctx.r[0] = mem.read_u16(ctx.r[31] + (184)); // lhz r0, 184(r31)
    /* 0x800A93E0 */ mem.write_u16(ctx.r[29] + (112), static_cast<uint16_t>(ctx.r[0])); // sth r0, 112(r29)
    /* 0x800A93E4 */ ctx.r[9] = mem.read_u16(ctx.r[31] + (186)); // lhz r9, 186(r31)
    /* 0x800A93E8 */ mem.write_u16(ctx.r[29] + (114), static_cast<uint16_t>(ctx.r[9])); // sth r9, 114(r29)
    /* 0x800A93EC */ ctx.r[0] = mem.read_u8(ctx.r[31] + (192)); // lbz r0, 192(r31)
    /* 0x800A93F0 */ mem.write_u8(ctx.r[29] + (124), static_cast<uint8_t>(ctx.r[0])); // stb r0, 124(r29)
    /* 0x800A93F4 */ ctx.r[9] = mem.read_u32(ctx.r[27] + (304)); // lwz r9, 304(r27)
    /* 0x800A93F8 */ mem.write_u8(ctx.r[9] + (92), static_cast<uint8_t>(ctx.r[5])); // stb r5, 92(r9)
    /* 0x800A93FC */ ctx.f[0] = mem.read_f32(ctx.r[29] + (72)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 72(r29)
    /* 0x800A9400 */ ctx.r[9] = mem.read_u32(ctx.r[27] + (304)); // lwz r9, 304(r27)
    /* 0x800A9404 */ { int32_t iv = static_cast<int32_t>(ctx.f[0]); uint64_t u = static_cast<uint32_t>(iv); std::memcpy(&ctx.f[10], &u, 8); } // fctiwz f10, f0
    /* 0x800A9408 */ mem.write_f64(ctx.r[1] + (24), ctx.f[10]); // stfd f10, 24(r1)
    /* 0x800A940C */ ctx.r[4] = mem.read_u32(ctx.r[1] + (28)); // lwz r4, 28(r1)
    /* 0x800A9410 */ mem.write_u8(ctx.r[9] + (93), static_cast<uint8_t>(ctx.r[4])); // stb r4, 93(r9)
    /* 0x800A9414 */ ctx.f[0] = mem.read_f32(ctx.r[29] + (76)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 76(r29)
    /* 0x800A9418 */ ctx.r[9] = mem.read_u32(ctx.r[27] + (304)); // lwz r9, 304(r27)
    /* 0x800A941C */ { int32_t iv = static_cast<int32_t>(ctx.f[0]); uint64_t u = static_cast<uint32_t>(iv); std::memcpy(&ctx.f[9], &u, 8); } // fctiwz f9, f0
    /* 0x800A9420 */ mem.write_f64(ctx.r[1] + (24), ctx.f[9]); // stfd f9, 24(r1)
    /* 0x800A9424 */ ctx.r[3] = mem.read_u32(ctx.r[1] + (28)); // lwz r3, 28(r1)
    /* 0x800A9428 */ mem.write_u8(ctx.r[9] + (94), static_cast<uint8_t>(ctx.r[3])); // stb r3, 94(r9)
    /* 0x800A942C */ ctx.r[0] = mem.read_u16(ctx.r[29] + (104)); // lhz r0, 104(r29)
    /* 0x800A9430 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800A9434 */ if (ctx.eval_bc(4, 2)) goto loc_800A9464; // bc 4, 2, 0x800A9464
    /* 0x800A9438 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A943C */ ctx.f[0] = mem.read_f32(ctx.r[29] + (80)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 80(r29)
    /* 0x800A9440 */ ctx.f[12] = mem.read_f32(ctx.r[9] + (-15072)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -15072(r9) [0x8016C520]
    /* 0x800A9444 */ ctx.r[9] = ctx.r[10]; // mr r9, r10
    /* 0x800A9448 */ ctx.r[11] = mem.read_u32(ctx.r[27] + (304)); // lwz r11, 304(r27)
    /* 0x800A944C */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[12]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f12
    /* 0x800A9450 */ { int32_t iv = static_cast<int32_t>(ctx.f[0]); uint64_t u = static_cast<uint32_t>(iv); std::memcpy(&ctx.f[13], &u, 8); } // fctiwz f13, f0
    /* 0x800A9454 */ mem.write_f64(ctx.r[1] + (24), ctx.f[13]); // stfd f13, 24(r1)
    /* 0x800A9458 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (28)); // lwz r9, 28(r1)
    /* 0x800A945C */ mem.write_u8(ctx.r[11] + (95), static_cast<uint8_t>(ctx.r[9])); // stb r9, 95(r11)
    /* 0x800A9460 */ goto loc_800A9470; // b 0x800A9470 <sub_800A9470>
loc_800A9464:;
    /* 0x800A9464 */ ctx.r[9] = mem.read_u32(ctx.r[27] + (304)); // lwz r9, 304(r27)
    /* 0x800A9468 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800A946C */ mem.write_u8(ctx.r[9] + (95), static_cast<uint8_t>(ctx.r[0])); // stb r0, 95(r9)
loc_800A9470:;
    /* 0x800A9470 */ ctx.r[8] = mem.read_u32(ctx.r[1] + (16)); // lwz r8, 16(r1)
    /* 0x800A9474 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800A9478 */ ctx.r[11] = mem.read_u32(ctx.r[31] + (216)); // lwz r11, 216(r31)
    /* 0x800A947C */ ctx.r[3] = ctx.r[15]; // mr r3, r15
    /* 0x800A9480 */ ctx.r[9] = mem.read_u32(ctx.r[8] + (8)); // lwz r9, 8(r8)
    /* 0x800A9484 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A9488 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800A948C */ mem.write_u32(ctx.r[29] + (148), ctx.r[11]); // stw r11, 148(r29)
    /* 0x800A9490 */ ctx.r[11] = mem.read_u32(ctx.r[1] + (12)); // lwz r11, 12(r1)
    /* 0x800A9494 */ ctx.f[1] = mem.read_f32(ctx.r[10] + (-15068)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -15068(r10) [0x8016C524]
    /* 0x800A9498 */ mem.write_u32(ctx.r[11] + (8), ctx.r[9]); // stw r9, 8(r11)
    /* 0x800A949C */ mem.write_u32(ctx.r[11] + (4), ctx.r[0]); // stw r0, 4(r11)
    /* 0x800A94A0 */ ctx.r[8] = mem.read_u32(ctx.r[1] + (20)); // lwz r8, 20(r1)
    /* 0x800A94A4 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (228)); // lwz r9, 228(r31)
    /* 0x800A94A8 */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800A94AC */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800A94B0 */ mem.write_u32(ctx.r[29] + (136), ctx.r[9]); // stw r9, 136(r29)
    /* 0x800A94B4 */ mem.write_u32(ctx.r[15] + (4), ctx.r[0]); // stw r0, 4(r15)
    /* 0x800A94B8 */ mem.write_u32(ctx.r[15] + (8), ctx.r[11]); // stw r11, 8(r15)
    /* 0x800A94BC */ ctx.call_indirect(0x80103998u, mem); // bl 0x80103998 <PSVECScale>
    /* 0x800A94C0 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (200)); // lbz r0, 200(r31)
    /* 0x800A94C4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A94C8 */ ctx.f[13] = mem.read_f64(ctx.r[9] + (-15064)); // lfd f13, -15064(r9) [0x8016C528 /* "C0" */]
    /* 0x800A94CC */ mem.write_u8(ctx.r[29] + (160), static_cast<uint8_t>(ctx.r[0])); // stb r0, 160(r29)
    /* 0x800A94D0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A94D4 */ ctx.f[10] = mem.read_f32(ctx.r[9] + (-15052)); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // lfs f10, -15052(r9) [0x8016C534]
    /* 0x800A94D8 */ ctx.r[6] = 0x43300000u; // lis r6, 0x4330
    /* 0x800A94DC */ ctx.r[0] = mem.read_u8(ctx.r[31] + (201)); // lbz r0, 201(r31)
    /* 0x800A94E0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A94E4 */ ctx.f[11] = mem.read_f32(ctx.r[11] + (-15056)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -15056(r11) [0x8016C530]
    /* 0x800A94E8 */ ctx.r[7] = ctx.r[10]; // mr r7, r10
    /* 0x800A94EC */ mem.write_u8(ctx.r[29] + (161), static_cast<uint8_t>(ctx.r[0])); // stb r0, 161(r29)
    /* 0x800A94F0 */ ctx.r[8] = 0x80170000u; // lis r8, 0x8017
    /* 0x800A94F4 */ ctx.f[12] = mem.read_f32(ctx.r[8] + (-15088)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -15088(r8) [0x8016C510]
    /* 0x800A94F8 */ ctx.r[11] = ctx.r[10]; // mr r11, r10
    /* 0x800A94FC */ ctx.r[0] = mem.read_u8(ctx.r[31] + (202)); // lbz r0, 202(r31)
    /* 0x800A9500 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800A9504 */ mem.write_u8(ctx.r[29] + (162), static_cast<uint8_t>(ctx.r[0])); // stb r0, 162(r29)
    /* 0x800A9508 */ ctx.r[9] = mem.read_u8(ctx.r[31] + (203)); // lbz r9, 203(r31)
    /* 0x800A950C */ mem.write_u8(ctx.r[29] + (163), static_cast<uint8_t>(ctx.r[9])); // stb r9, 163(r29)
    /* 0x800A9510 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (204)); // lwz r0, 204(r31)
    /* 0x800A9514 */ ctx.r[0] = ctx.r[0] ^ 0x80000000u; // xoris r0, r0, 0x8000
    /* 0x800A9518 */ mem.write_u32(ctx.r[1] + (28), ctx.r[0]); // stw r0, 28(r1)
    /* 0x800A951C */ mem.write_u32(ctx.r[1] + (24), ctx.r[6]); // stw r6, 24(r1)
    /* 0x800A9520 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (24)); // lfd f0, 24(r1)
    /* 0x800A9524 */ ctx.f[0] = ctx.f[0] - ctx.f[13]; // fsub f0, f0, f13
    /* 0x800A9528 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800A952C */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f11
    /* 0x800A9530 */ mem.write_f32(ctx.r[29] + (164), static_cast<float>(ctx.f[0])); // stfs f0, 164(r29)
    /* 0x800A9534 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (208)); // lwz r0, 208(r31)
    /* 0x800A9538 */ ctx.r[0] = ctx.r[0] ^ 0x80000000u; // xoris r0, r0, 0x8000
    /* 0x800A953C */ mem.write_u32(ctx.r[1] + (28), ctx.r[0]); // stw r0, 28(r1)
    /* 0x800A9540 */ mem.write_u32(ctx.r[1] + (24), ctx.r[6]); // stw r6, 24(r1)
    /* 0x800A9544 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (24)); // lfd f0, 24(r1)
    /* 0x800A9548 */ ctx.f[0] = ctx.f[0] - ctx.f[13]; // fsub f0, f0, f13
    /* 0x800A954C */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800A9550 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[10]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f10
    /* 0x800A9554 */ ctx.f[12] = static_cast<float>(ctx.f[12] - ctx.f[0]); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // fsubs f12, f12, f0
    /* 0x800A9558 */ mem.write_f32(ctx.r[29] + (168), static_cast<float>(ctx.f[12])); // stfs f12, 168(r29)
    /* 0x800A955C */ ctx.r[0] = mem.read_u32(ctx.r[31] + (212)); // lwz r0, 212(r31)
    /* 0x800A9560 */ ctx.r[0] = ctx.r[0] ^ 0x80000000u; // xoris r0, r0, 0x8000
    /* 0x800A9564 */ mem.write_u32(ctx.r[1] + (28), ctx.r[0]); // stw r0, 28(r1)
    /* 0x800A9568 */ mem.write_u32(ctx.r[1] + (24), ctx.r[6]); // stw r6, 24(r1)
    /* 0x800A956C */ ctx.f[0] = mem.read_f64(ctx.r[1] + (24)); // lfd f0, 24(r1)
    /* 0x800A9570 */ ctx.f[0] = ctx.f[0] - ctx.f[13]; // fsub f0, f0, f13
    /* 0x800A9574 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800A9578 */ mem.write_f32(ctx.r[29] + (132), static_cast<float>(ctx.f[0])); // stfs f0, 132(r29)
    /* 0x800A957C */ ctx.r[0] = mem.read_u8(ctx.r[27] + (254)); // lbz r0, 254(r27)
    /* 0x800A9580 */ ctx.r[9] = mem.read_u32(ctx.r[27] + (240)); // lwz r9, 240(r27)
    /* 0x800A9584 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[5]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r5, r0
    /* 0x800A9588 */ if (ctx.eval_bc(4, 0)) goto loc_800A95A8; // bc 4, 0, 0x800A95A8
    /* 0x800A958C */ ctx.r[11] = 0x00000000u; // li r11, 0
loc_800A9590:;
    /* 0x800A9590 */ mem.write_u32(ctx.r[9] + (328), ctx.r[11]); // stw r11, 328(r9)
    /* 0x800A9594 */ ctx.r[5] = ctx.r[5] + (1); // addi r5, r5, 1
    /* 0x800A9598 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (240)); // lwz r9, 240(r9)
    /* 0x800A959C */ ctx.r[0] = mem.read_u8(ctx.r[27] + (254)); // lbz r0, 254(r27)
    /* 0x800A95A0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[5]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r5, r0
    /* 0x800A95A4 */ if (ctx.eval_bc(12, 0)) goto loc_800A9590; // bc 12, 0, 0x800A9590
loc_800A95A8:;
    /* 0x800A95A8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (108)); // lwz r0, 108(r1)
    /* 0x800A95AC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A95B0 */ ctx.lmw(mem, 14, ctx.r[1] + (32)); // lmw r14, 32(r1)
    /* 0x800A95B4 */ ctx.r[1] = ctx.r[1] + (104); // addi r1, r1, 104
    /* 0x800A95B8 */ return; // blr
}

// [0x800A95BC] cObj05::initObj05Em(cEm *, float (*)[2][3], tagESPSEQ_TBL *) (obj05.obj, 102 insns / 0x198 bytes)
void cObj05__initObj05Em_800A95BC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A95BC */ ctx.r[1] += (-104); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -104(r1)
    /* 0x800A95C0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A95C4 */ ctx.stmw(mem, 28, ctx.r[1] + (88)); // stmw r28, 88(r1)
    /* 0x800A95C8 */ mem.write_u32(ctx.r[1] + (108), ctx.r[0]); // stw r0, 108(r1)
    /* 0x800A95CC */ ctx.r[28] = ctx.r[3]; // mr r28, r3
    /* 0x800A95D0 */ ctx.r[29] = ctx.r[4]; // mr r29, r4
    /* 0x800A95D4 */ ctx.r[31] = ctx.r[28] + (1224); // addi r31, r28, 1224
    /* 0x800A95D8 */ ctx.r[4] = ctx.r[5]; // mr r4, r5
    /* 0x800A95DC */ ctx.r[0] = mem.read_u8(ctx.r[31] + (125)); // lbz r0, 125(r31)
    /* 0x800A95E0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 254); // cmpwi cr0, r0, 254
    /* 0x800A95E4 */ if (ctx.eval_bc(12, 2)) goto loc_800A9618; // bc 12, 2, 0x800A9618
    /* 0x800A95E8 */ if (ctx.eval_bc(12, 1)) goto loc_800A95F8; // bc 12, 1, 0x800A95F8
    /* 0x800A95EC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 253); // cmpwi cr0, r0, 253
    /* 0x800A95F0 */ if (ctx.eval_bc(12, 2)) goto loc_800A9618; // bc 12, 2, 0x800A9618
    /* 0x800A95F4 */ goto loc_800A9628; // b 0x800A9628 <sub_800A9628>
loc_800A95F8:;
    /* 0x800A95F8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 255); // cmpwi cr0, r0, 255
    /* 0x800A95FC */ if (ctx.eval_bc(4, 2)) goto loc_800A9628; // bc 4, 2, 0x800A9628
    /* 0x800A9600 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A9604 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A9608 */ ctx.r[9] = ctx.r[9] + (756); // addi r9, r9, 756
    /* 0x800A960C */ mem.write_u32(ctx.r[31] + (120), ctx.r[9]); // stw r9, 120(r31)
    /* 0x800A9610 */ cObj05__Efm05RotMatrix_800A8E2C(ctx, mem); // bl 0x800A8E2C <cObj05::Efm05RotMatrix(float (*)[2][3])>
    /* 0x800A9614 */ goto loc_800A973C; // b 0x800A973C <sub_800A973C>
loc_800A9618:;
    /* 0x800A9618 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A961C */ ctx.r[9] = ctx.r[9] + (756); // addi r9, r9, 756
    /* 0x800A9620 */ mem.write_u32(ctx.r[31] + (120), ctx.r[9]); // stw r9, 120(r31)
    /* 0x800A9624 */ goto loc_800A973C; // b 0x800A973C <sub_800A973C>
loc_800A9628:;
    /* 0x800A9628 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[29]), 0); // cmpwi cr0, r29, 0
    /* 0x800A962C */ if (ctx.eval_bc(4, 2)) goto loc_800A9654; // bc 4, 2, 0x800A9654
    /* 0x800A9630 */ ctx.r[6] = mem.read_u8(ctx.r[31] + (125)); // lbz r6, 125(r31)
    /* 0x800A9634 */ ctx.r[5] = 0x80170000u; // lis r5, 0x8017
    /* 0x800A9638 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A963C */ ctx.r[5] = ctx.r[5] + (-15048); // addi r5, r5, -15048 -> 0x8016C538 /* "ESP_EFM05 : PARTS_NO[%d] bat Not on parts." */
    /* 0x800A9640 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800A9644 */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800A9648 */ LogErr_8007A05C(ctx, mem); // bl 0x8007A05C <LogErr(unsigned long, unsigned long, char *,...)>
    /* 0x800A964C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9650 */ goto loc_800A9740; // b 0x800A9740 <sub_800A9740>
loc_800A9654:;
    /* 0x800A9654 */ ctx.r[4] = mem.read_u8(ctx.r[31] + (125)); // lbz r4, 125(r31)
    /* 0x800A9658 */ ctx.r[7] = mem.read_u8(ctx.r[29] + (254)); // lbz r7, 254(r29)
    /* 0x800A965C */ ctx.cmp_u32(0, ctx.r[4], ctx.r[7]); // cmplw cr0, r4, r7
    /* 0x800A9660 */ if (ctx.eval_bc(4, 0)) goto loc_800A9718; // bc 4, 0, 0x800A9718
    /* 0x800A9664 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (128)); // lwz r0, 128(r31)
    /* 0x800A9668 */ ctx.r[9] = ctx.r[0] & 0x0020u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0020
    /* 0x800A966C */ if (ctx.eval_bc(12, 2)) goto loc_800A9704; // bc 12, 2, 0x800A9704
    /* 0x800A9670 */ ctx.r[3] = mem.read_u32(ctx.r[29] + (240)); // lwz r3, 240(r29)
    /* 0x800A9674 */ ctx.r[30] = ctx.r[1] + (24); // addi r30, r1, 24
    /* 0x800A9678 */ GetPartsAddr_800A0BD4(ctx, mem); // bl 0x800A0BD4 <GetPartsAddr(PARTS *, unsigned long)>
    /* 0x800A967C */ ctx.f[0] = mem.read_f32(ctx.r[29] + (204)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 204(r29)
    /* 0x800A9680 */ ctx.r[9] = ctx.r[29] + (204); // addi r9, r29, 204
    /* 0x800A9684 */ ctx.r[29] = ctx.r[3]; // mr r29, r3
    /* 0x800A9688 */ ctx.r[4] = ctx.r[1] + (72); // addi r4, r1, 72
    /* 0x800A968C */ mem.write_f32(ctx.r[1] + (72), static_cast<float>(ctx.f[0])); // stfs f0, 72(r1)
    /* 0x800A9690 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A9694 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A9698 */ mem.write_f32(ctx.r[1] + (76), static_cast<float>(ctx.f[0])); // stfs f0, 76(r1)
    /* 0x800A969C */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A96A0 */ mem.write_f32(ctx.r[1] + (80), static_cast<float>(ctx.f[13])); // stfs f13, 80(r1)
    /* 0x800A96A4 */ RotMatrix_8009E1D0(ctx, mem); // bl 0x8009E1D0 <RotMatrix(float (*)[3], cVec &)>
    /* 0x800A96A8 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A96AC */ ctx.r[4] = ctx.r[28] + (192); // addi r4, r28, 192
    /* 0x800A96B0 */ ctx.r[5] = ctx.r[1] + (8); // addi r5, r1, 8
    /* 0x800A96B4 */ ctx.call_indirect(0x80102028u, mem); // bl 0x80102028 <PSMTXMultVecSR>
    /* 0x800A96B8 */ ctx.f[0] = mem.read_f32(ctx.r[29] + (12)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 12(r29)
    /* 0x800A96BC */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A96C0 */ ctx.f[13] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r1)
    /* 0x800A96C4 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A96C8 */ ctx.f[12] = mem.read_f32(ctx.r[1] + (12)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 12(r1)
    /* 0x800A96CC */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f13
    /* 0x800A96D0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A96D4 */ mem.write_f32(ctx.r[1] + (36), static_cast<float>(ctx.f[0])); // stfs f0, 36(r1)
    /* 0x800A96D8 */ ctx.f[11] = mem.read_f32(ctx.r[1] + (16)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 16(r1)
    /* 0x800A96DC */ ctx.r[9] = ctx.r[9] + (756); // addi r9, r9, 756
    /* 0x800A96E0 */ ctx.f[0] = mem.read_f32(ctx.r[29] + (28)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 28(r29)
    /* 0x800A96E4 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[12]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f12
    /* 0x800A96E8 */ mem.write_f32(ctx.r[1] + (52), static_cast<float>(ctx.f[0])); // stfs f0, 52(r1)
    /* 0x800A96EC */ ctx.f[13] = mem.read_f32(ctx.r[29] + (44)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 44(r29)
    /* 0x800A96F0 */ mem.write_u32(ctx.r[31] + (120), ctx.r[9]); // stw r9, 120(r31)
    /* 0x800A96F4 */ ctx.f[13] = static_cast<float>(ctx.f[13] + ctx.f[11]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // fadds f13, f13, f11
    /* 0x800A96F8 */ mem.write_f32(ctx.r[1] + (68), static_cast<float>(ctx.f[13])); // stfs f13, 68(r1)
    /* 0x800A96FC */ cObj05__Efm05RotMatrix_800A8E2C(ctx, mem); // bl 0x800A8E2C <cObj05::Efm05RotMatrix(float (*)[2][3])>
    /* 0x800A9700 */ goto loc_800A973C; // b 0x800A973C <sub_800A973C>
loc_800A9704:;
    /* 0x800A9704 */ mem.write_u32(ctx.r[31] + (116), ctx.r[29]); // stw r29, 116(r31)
    /* 0x800A9708 */ ctx.r[3] = mem.read_u32(ctx.r[29] + (240)); // lwz r3, 240(r29)
    /* 0x800A970C */ GetPartsAddr_800A0BD4(ctx, mem); // bl 0x800A0BD4 <GetPartsAddr(PARTS *, unsigned long)>
    /* 0x800A9710 */ mem.write_u32(ctx.r[31] + (120), ctx.r[3]); // stw r3, 120(r31)
    /* 0x800A9714 */ goto loc_800A973C; // b 0x800A973C <sub_800A973C>
loc_800A9718:;
    /* 0x800A9718 */ ctx.r[6] = ctx.r[4]; // mr r6, r4
    /* 0x800A971C */ ctx.r[5] = 0x80170000u; // lis r5, 0x8017
    /* 0x800A9720 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9724 */ ctx.r[5] = ctx.r[5] + (-15004); // addi r5, r5, -15004 -> 0x8016C564 /* "ESP_EFM05 : PARTS_NO[%d] is invalid(MAX:%d)." */
    /* 0x800A9728 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800A972C */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800A9730 */ LogErr_8007A05C(ctx, mem); // bl 0x8007A05C <LogErr(unsigned long, unsigned long, char *,...)>
    /* 0x800A9734 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9738 */ goto loc_800A9740; // b 0x800A9740 <sub_800A9740>
loc_800A973C:;
    /* 0x800A973C */ ctx.r[3] = 0x00000001u; // li r3, 1
loc_800A9740:;
    /* 0x800A9740 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (108)); // lwz r0, 108(r1)
    /* 0x800A9744 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A9748 */ ctx.lmw(mem, 28, ctx.r[1] + (88)); // lmw r28, 88(r1)
    /* 0x800A974C */ ctx.r[1] = ctx.r[1] + (104); // addi r1, r1, 104
    /* 0x800A9750 */ return; // blr
}

// [0x800A9754] cObj05::initObj05Mot(tagESPSEQ_TBL *) (obj05.obj, 65 insns / 0x104 bytes)
void cObj05__initObj05Mot_800A9754(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A9754 */ ctx.r[1] += (-32); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -32(r1)
    /* 0x800A9758 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A975C */ ctx.stmw(mem, 29, ctx.r[1] + (20)); // stmw r29, 20(r1)
    /* 0x800A9760 */ mem.write_u32(ctx.r[1] + (36), ctx.r[0]); // stw r0, 36(r1)
    /* 0x800A9764 */ ctx.r[29] = ctx.r[3]; // mr r29, r3
    /* 0x800A9768 */ ctx.r[31] = ctx.r[4]; // mr r31, r4
    /* 0x800A976C */ ctx.r[30] = ctx.r[29] + (1224); // addi r30, r29, 1224
    /* 0x800A9770 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (128)); // lwz r0, 128(r30)
    /* 0x800A9774 */ ctx.r[9] = ctx.r[0] & 0x0008u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0008
    /* 0x800A9778 */ if (ctx.eval_bc(12, 2)) goto loc_800A9844; // bc 12, 2, 0x800A9844
    /* 0x800A977C */ ctx.r[4] = mem.read_u8(ctx.r[31] + (254)); // lbz r4, 254(r31)
    /* 0x800A9780 */ ctx.r[5] = ctx.r[1] + (8); // addi r5, r1, 8
    /* 0x800A9784 */ mem.write_u8(ctx.r[30] + (127), static_cast<uint8_t>(ctx.r[4])); // stb r4, 127(r30)
    /* 0x800A9788 */ ctx.rlwinm(4, 4, 0u, 24u, 31u, false); // rlwinm r4, r4, 0, 24, 31
    /* 0x800A978C */ ctx.r[3] = mem.read_u8(ctx.r[31] + (2)); // lbz r3, 2(r31)
    /* 0x800A9790 */ EspGetEfmMotAddr_80083820(ctx, mem); // bl 0x80083820 <EspGetEfmMotAddr(unsigned char, unsigned long, unsigned long *)>
    /* 0x800A9794 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800A9798 */ if (ctx.eval_bc(12, 2)) goto loc_800A981C; // bc 12, 2, 0x800A981C
    /* 0x800A979C */ ctx.r[0] = mem.read_u8(ctx.r[31] + (255)); // lbz r0, 255(r31)
    /* 0x800A97A0 */ ctx.r[6] = ctx.r[0]; // mr r6, r0
    /* 0x800A97A4 */ ctx.rlwinm(0, 0, 0u, 24u, 31u, false); // rlwinm r0, r0, 0, 24, 31
    /* 0x800A97A8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800A97AC */ if (ctx.eval_bc(12, 2)) goto loc_800A97BC; // bc 12, 2, 0x800A97BC
    /* 0x800A97B0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 1); // cmpwi cr0, r0, 1
    /* 0x800A97B4 */ if (ctx.eval_bc(12, 2)) goto loc_800A97D8; // bc 12, 2, 0x800A97D8
    /* 0x800A97B8 */ goto loc_800A97FC; // b 0x800A97FC <sub_800A97FC>
loc_800A97BC:;
    /* 0x800A97BC */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A97C0 */ ctx.r[5] = mem.read_u32(ctx.r[1] + (8)); // lwz r5, 8(r1)
    /* 0x800A97C4 */ ctx.r[4] = ctx.r[3] + (380); // addi r4, r3, 380
    /* 0x800A97C8 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800A97CC */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800A97D0 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800A97D4 */ goto loc_800A97F0; // b 0x800A97F0 <sub_800A97F0>
loc_800A97D8:;
    /* 0x800A97D8 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A97DC */ ctx.r[5] = mem.read_u32(ctx.r[1] + (8)); // lwz r5, 8(r1)
    /* 0x800A97E0 */ ctx.r[4] = ctx.r[3] + (380); // addi r4, r3, 380
    /* 0x800A97E4 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800A97E8 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800A97EC */ ctx.r[8] = 0x00000004u; // li r8, 4
loc_800A97F0:;
    /* 0x800A97F0 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800A97F4 */ MotionSetCore_800A1E20(ctx, mem); // bl 0x800A1E20 <MotionSetCore(cEm *, _MOTION_INFO *, void *, void *, unsigned char, unsigned short, unsigned short)>
    /* 0x800A97F8 */ goto loc_800A9844; // b 0x800A9844 <sub_800A9844>
loc_800A97FC:;
    /* 0x800A97FC */ ctx.r[5] = 0x80170000u; // lis r5, 0x8017
    /* 0x800A9800 */ ctx.rlwinm(6, 6, 0u, 24u, 31u, false); // rlwinm r6, r6, 0, 24, 31
    /* 0x800A9804 */ ctx.r[5] = ctx.r[5] + (-14956); // addi r5, r5, -14956 -> 0x8016C594 /* "ESP_EFM05 : MotionType[%d] is invalid." */
    /* 0x800A9808 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A980C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800A9810 */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800A9814 */ LogErr_8007A05C(ctx, mem); // bl 0x8007A05C <LogErr(unsigned long, unsigned long, char *,...)>
    /* 0x800A9818 */ goto loc_800A9844; // b 0x800A9844 <sub_800A9844>
loc_800A981C:;
    /* 0x800A981C */ ctx.r[5] = 0x80170000u; // lis r5, 0x8017
    /* 0x800A9820 */ ctx.r[6] = mem.read_u8(ctx.r[30] + (127)); // lbz r6, 127(r30)
    /* 0x800A9824 */ ctx.r[5] = ctx.r[5] + (-14916); // addi r5, r5, -14916 -> 0x8016C5BC /* "ESP_EFM05 : MotionNo[%d] is invalid." */
    /* 0x800A9828 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A982C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800A9830 */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800A9834 */ LogErr_8007A05C(ctx, mem); // bl 0x8007A05C <LogErr(unsigned long, unsigned long, char *,...)>
    /* 0x800A9838 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (128)); // lwz r0, 128(r30)
    /* 0x800A983C */ ctx.r[0] = ctx.r[0] | 0x0008u; // ori r0, r0, 0x0008
    /* 0x800A9840 */ mem.write_u32(ctx.r[30] + (128), ctx.r[0]); // stw r0, 128(r30)
loc_800A9844:;
    /* 0x800A9844 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (36)); // lwz r0, 36(r1)
    /* 0x800A9848 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A984C */ ctx.lmw(mem, 29, ctx.r[1] + (20)); // lmw r29, 20(r1)
    /* 0x800A9850 */ ctx.r[1] = ctx.r[1] + (32); // addi r1, r1, 32
    /* 0x800A9854 */ return; // blr
}

// [0x800A9858] getObj05(unsigned char, unsigned char) (obj05.obj, 28 insns / 0x70 bytes)
void getObj05_800A9858(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A9858 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A985C */ ctx.r[8] = ctx.r[3]; // mr r8, r3
    /* 0x800A9860 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (320)); // lwz r9, 320(r9)
    /* 0x800A9864 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800A9868 */ if (ctx.eval_bc(4, 2)) goto loc_800A9874; // bc 4, 2, 0x800A9874
    /* 0x800A986C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9870 */ return; // blr
loc_800A9874:;
    /* 0x800A9874 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (4)); // lwz r0, 4(r9)
    /* 0x800A9878 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800A987C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r11, r0
    /* 0x800A9880 */ if (ctx.eval_bc(12, 2)) goto loc_800A98C0; // bc 12, 2, 0x800A98C0
    /* 0x800A9884 */ ctx.r[10] = ctx.r[0]; // mr r10, r0
loc_800A9888:;
    /* 0x800A9888 */ ctx.r[3] = mem.read_u32(ctx.r[11] + (0)); // lwz r3, 0(r11)
    /* 0x800A988C */ ctx.r[0] = mem.read_u8(ctx.r[3] + (252)); // lbz r0, 252(r3)
    /* 0x800A9890 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 5); // cmpwi cr0, r0, 5
    /* 0x800A9894 */ if (ctx.eval_bc(4, 2)) goto loc_800A98B4; // bc 4, 2, 0x800A98B4
    /* 0x800A9898 */ ctx.r[0] = mem.read_u8(ctx.r[3] + (1236)); // lbz r0, 1236(r3)
    /* 0x800A989C */ ctx.r[9] = ctx.r[3] + (1224); // addi r9, r3, 1224
    /* 0x800A98A0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), static_cast<int32_t>(ctx.r[4])); // cmpw cr0, r0, r4
    /* 0x800A98A4 */ if (ctx.eval_bc(4, 2)) goto loc_800A98B4; // bc 4, 2, 0x800A98B4
    /* 0x800A98A8 */ ctx.r[0] = mem.read_u8(ctx.r[9] + (2)); // lbz r0, 2(r9)
    /* 0x800A98AC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), static_cast<int32_t>(ctx.r[8])); // cmpw cr0, r0, r8
    /* 0x800A98B0 */ if (ctx.eval_bc(12, 2)) return; // bclr 12, 2
loc_800A98B4:;
    /* 0x800A98B4 */ ctx.r[11] = ctx.r[11] + (4); // addi r11, r11, 4
    /* 0x800A98B8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r11, r10
    /* 0x800A98BC */ if (ctx.eval_bc(4, 2)) goto loc_800A9888; // bc 4, 2, 0x800A9888
loc_800A98C0:;
    /* 0x800A98C0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A98C4 */ return; // blr
}

// [0x800A98C8] cObj05::setSe(long, unsigned char, unsigned short, unsigned short) (obj05.obj, 25 insns / 0x64 bytes)
void cObj05__setSe_800A98C8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A98C8 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800A98CC */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A98D0 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800A98D4 */ ctx.r[9] = ctx.r[3] + (1224); // addi r9, r3, 1224
    /* 0x800A98D8 */ ctx.cmp_u32(0, ctx.r[4], 0x0004u); // cmplwi cr0, r4, 0x0004
    /* 0x800A98DC */ if (ctx.eval_bc(4, 1)) goto loc_800A9900; // bc 4, 1, 0x800A9900
    /* 0x800A98E0 */ ctx.r[5] = 0x80170000u; // lis r5, 0x8017
    /* 0x800A98E4 */ ctx.r[6] = ctx.r[4]; // mr r6, r4
    /* 0x800A98E8 */ ctx.r[5] = ctx.r[5] + (-14876); // addi r5, r5, -14876 -> 0x8016C5E4 /* "OBJ05:Don't set %d." */
    /* 0x800A98EC */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A98F0 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800A98F4 */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800A98F8 */ LogErr_8007A05C(ctx, mem); // bl 0x8007A05C <LogErr(unsigned long, unsigned long, char *,...)>
    /* 0x800A98FC */ goto loc_800A991C; // b 0x800A991C <sub_800A991C>
loc_800A9900:;
    /* 0x800A9900 */ ctx.rlwinm(0, 4, 3u, 0u, 28u, false); // rlwinm r0, r4, 3, 0, 28
    /* 0x800A9904 */ ctx.r[10] = ctx.r[3] + (1400); // addi r10, r3, 1400
    /* 0x800A9908 */ ctx.r[9] = ctx.r[9] + ctx.r[0]; // add r9, r9, r0
    /* 0x800A990C */ ctx.r[11] = ctx.r[3] + (1402); // addi r11, r3, 1402
    /* 0x800A9910 */ mem.write_u8(ctx.r[9] + (174), static_cast<uint8_t>(ctx.r[5])); // stb r5, 174(r9)
    /* 0x800A9914 */ mem.write_u16(ctx.r[10] + ctx.r[0], static_cast<uint16_t>(ctx.r[6])); // sthx r6, r10, r0
    /* 0x800A9918 */ mem.write_u16(ctx.r[11] + ctx.r[0], static_cast<uint16_t>(ctx.r[7])); // sthx r7, r11, r0
loc_800A991C:;
    /* 0x800A991C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800A9920 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A9924 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800A9928 */ return; // blr
}

// [0x800A992C] cObj05::renderRegistration(void) (obj05.obj, 13 insns / 0x34 bytes)
void cObj05__renderRegistration_800A992C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A992C */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800A9930 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A9934 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800A9938 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800A993C */ ctx.r[5] = 0x800E0000u; // lis r5, 0x800E
    /* 0x800A9940 */ ctx.r[5] = ctx.r[5] + (-25172); // addi r5, r5, -25172 -> ModelRender(void *)
    /* 0x800A9944 */ ctx.r[3] = 0x00000003u; // li r3, 3
    /* 0x800A9948 */ ctx.r[6] = 0x00000003u; // li r6, 3
    /* 0x800A994C */ AddOtDirect_800DCC40(ctx, mem); // bl 0x800DCC40 <AddOtDirect(unsigned short, void *, void (*)(void *), unsigned short)>
    /* 0x800A9950 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800A9954 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A9958 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800A995C */ return; // blr
}

// [0x800A9960] cObj05::~cObj05(void) (obj05.obj, 8 insns / 0x20 bytes)
void cObj05_dtor_cObj05_800A9960(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A9960 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800A9964 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A9968 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800A996C */ cObj_dtor_cObj_80074AD8(ctx, mem); // bl 0x80074AD8 <cObj::~cObj(void)>
    /* 0x800A9970 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800A9974 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A9978 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800A997C */ return; // blr
}

// [0x800A9980] cObj05::cObj05(void) (obj05.obj, 19 insns / 0x4C bytes)
void cObj05__cObj05_800A9980(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A9980 */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800A9984 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A9988 */ ctx.stmw(mem, 30, ctx.r[1] + (8)); // stmw r30, 8(r1)
    /* 0x800A998C */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800A9990 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800A9994 */ cObj__cObj_80074A98(ctx, mem); // bl 0x80074A98 <cObj::cObj(void)>
    /* 0x800A9998 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A999C */ ctx.r[3] = ctx.r[30] + (1224); // addi r3, r30, 1224
    /* 0x800A99A0 */ ctx.r[9] = ctx.r[9] + (-14856); // addi r9, r9, -14856 -> cObj05 virtual table
    /* 0x800A99A4 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800A99A8 */ mem.write_u32(ctx.r[30] + (1208), ctx.r[9]); // stw r9, 1208(r30)
    /* 0x800A99AC */ ctx.r[5] = 0x000000E0u; // li r5, 224
    /* 0x800A99B0 */ ctx.call_indirect(0x800E8A5Cu, mem); // bl 0x800E8A5C <memset>
    /* 0x800A99B4 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A99B8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800A99BC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A99C0 */ ctx.lmw(mem, 30, ctx.r[1] + (8)); // lmw r30, 8(r1)
    /* 0x800A99C4 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800A99C8 */ return; // blr
}

// [0x800A99CC] cObj05::getEffcore(void) (obj05.obj, 2 insns / 0x8 bytes)
void cObj05__getEffcore_800A99CC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A99CC */ ctx.r[3] = ctx.r[3] + (1224); // addi r3, r3, 1224
    /* 0x800A99D0 */ return; // blr
}

// [0x800A99D4] cObj05::getToolFlg(void) (obj05.obj, 2 insns / 0x8 bytes)
void cObj05__getToolFlg_800A99D4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A99D4 */ ctx.r[3] = mem.read_u32(ctx.r[3] + (1352)); // lwz r3, 1352(r3)
    /* 0x800A99D8 */ return; // blr
}

// [0x800A99DC] cObj05::getTexId(void) (obj05.obj, 2 insns / 0x8 bytes)
void cObj05__getTexId_800A99DC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A99DC */ ctx.r[3] = mem.read_u8(ctx.r[3] + (1236)); // lbz r3, 1236(r3)
    /* 0x800A99E0 */ return; // blr
}

// [0x800A99E4] cObj05::getEm(void) (obj05.obj, 2 insns / 0x8 bytes)
void cObj05__getEm_800A99E4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A99E4 */ ctx.r[3] = mem.read_u32(ctx.r[3] + (1340)); // lwz r3, 1340(r3)
    /* 0x800A99E8 */ return; // blr
}

// [0x800A99EC] cObj05::setEffcore(tagEFFECT_CORE *) (obj05.obj, 10 insns / 0x28 bytes)
void cObj05__setEffcore_800A99EC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A99EC */ ctx.r[4] = ctx.r[4]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[4]), 0); // mr r4, r4
    /* 0x800A99F0 */ if (ctx.eval_bc(12, 2)) return; // bclr 12, 2
    /* 0x800A99F4 */ ctx.r[10] = mem.read_u32(ctx.r[4] + (0)); // lwz r10, 0(r4)
    /* 0x800A99F8 */ ctx.r[11] = ctx.r[3] + (1224); // addi r11, r3, 1224
    /* 0x800A99FC */ ctx.r[0] = mem.read_u32(ctx.r[4] + (8)); // lwz r0, 8(r4)
    /* 0x800A9A00 */ ctx.r[9] = mem.read_u32(ctx.r[4] + (4)); // lwz r9, 4(r4)
    /* 0x800A9A04 */ mem.write_u32(ctx.r[3] + (1224), ctx.r[10]); // stw r10, 1224(r3)
    /* 0x800A9A08 */ mem.write_u32(ctx.r[11] + (8), ctx.r[0]); // stw r0, 8(r11)
    /* 0x800A9A0C */ mem.write_u32(ctx.r[11] + (4), ctx.r[9]); // stw r9, 4(r11)
    /* 0x800A9A10 */ return; // blr
}

// [0x800A9A14] cObj05::setVec(Vec &, Vec &, unsigned long *) (obj05.obj, 30 insns / 0x78 bytes)
void cObj05__setVec_800A9A14(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A9A14 */ ctx.r[1] += (-24); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -24(r1)
    /* 0x800A9A18 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A9A1C */ ctx.stmw(mem, 28, ctx.r[1] + (8)); // stmw r28, 8(r1)
    /* 0x800A9A20 */ mem.write_u32(ctx.r[1] + (28), ctx.r[0]); // stw r0, 28(r1)
    /* 0x800A9A24 */ ctx.r[29] = ctx.r[6]; // mr r29, r6
    /* 0x800A9A28 */ ctx.r[30] = ctx.r[4]; // mr r30, r4
    /* 0x800A9A2C */ ctx.r[28] = ctx.r[5]; // mr r28, r5
    /* 0x800A9A30 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A9A34 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A9A38 */ ctx.f[13] = mem.read_f32(ctx.r[30] + (0)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 0(r30)
    /* 0x800A9A3C */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A9A40 */ ctx.f[0] = mem.read_f32(ctx.r[28] + (0)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 0(r28)
    /* 0x800A9A44 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A9A48 */ mem.write_f32(ctx.r[30] + (0), static_cast<float>(ctx.f[0])); // stfs f0, 0(r30)
    /* 0x800A9A4C */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A9A50 */ ctx.f[13] = mem.read_f32(ctx.r[30] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r30)
    /* 0x800A9A54 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800A9A58 */ ctx.f[0] = mem.read_f32(ctx.r[28] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r28)
    /* 0x800A9A5C */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A9A60 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A9A64 */ fRandSeed1_1_800C080C(ctx, mem); // bl 0x800C080C <fRandSeed1_1(unsigned long *)>
    /* 0x800A9A68 */ ctx.f[0] = mem.read_f32(ctx.r[28] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r28)
    /* 0x800A9A6C */ ctx.f[13] = mem.read_f32(ctx.r[30] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r30)
    /* 0x800A9A70 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[1] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmadds f0, f0, f1, f13
    /* 0x800A9A74 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r30)
    /* 0x800A9A78 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (28)); // lwz r0, 28(r1)
    /* 0x800A9A7C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A9A80 */ ctx.lmw(mem, 28, ctx.r[1] + (8)); // lmw r28, 8(r1)
    /* 0x800A9A84 */ ctx.r[1] = ctx.r[1] + (24); // addi r1, r1, 24
    /* 0x800A9A88 */ return; // blr
}

// [0x800A9A8C] cObj10::cObj10(void) (obj10.obj, 29 insns / 0x74 bytes)
void cObj10__cObj10_800A9A8C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A9A8C */ ctx.r[1] += (-24); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -24(r1)
    /* 0x800A9A90 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A9A94 */ ctx.stmw(mem, 29, ctx.r[1] + (12)); // stmw r29, 12(r1)
    /* 0x800A9A98 */ mem.write_u32(ctx.r[1] + (28), ctx.r[0]); // stw r0, 28(r1)
    /* 0x800A9A9C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800A9AA0 */ ctx.r[29] = 0x00000000u; // li r29, 0
    /* 0x800A9AA4 */ cObj__cObj_80074A98(ctx, mem); // bl 0x80074A98 <cObj::cObj(void)>
    /* 0x800A9AA8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A9AAC */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A9AB0 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-14748)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -14748(r9) [0x8016C664]
    /* 0x800A9AB4 */ ctx.r[11] = ctx.r[11] + (-14680); // addi r11, r11, -14680 -> cObj10 virtual table
    /* 0x800A9AB8 */ mem.write_u32(ctx.r[30] + (1212), ctx.r[29]); // stw r29, 1212(r30)
    /* 0x800A9ABC */ ctx.r[3] = ctx.r[30] + (1236); // addi r3, r30, 1236
    /* 0x800A9AC0 */ mem.write_u32(ctx.r[30] + (1216), ctx.r[29]); // stw r29, 1216(r30)
    /* 0x800A9AC4 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800A9AC8 */ mem.write_u32(ctx.r[30] + (1220), ctx.r[29]); // stw r29, 1220(r30)
    /* 0x800A9ACC */ ctx.r[5] = 0x00000030u; // li r5, 48
    /* 0x800A9AD0 */ mem.write_u32(ctx.r[30] + (1208), ctx.r[11]); // stw r11, 1208(r30)
    /* 0x800A9AD4 */ mem.write_f32(ctx.r[30] + (1232), static_cast<float>(ctx.f[0])); // stfs f0, 1232(r30)
    /* 0x800A9AD8 */ mem.write_f32(ctx.r[30] + (1224), static_cast<float>(ctx.f[0])); // stfs f0, 1224(r30)
    /* 0x800A9ADC */ mem.write_f32(ctx.r[30] + (1228), static_cast<float>(ctx.f[0])); // stfs f0, 1228(r30)
    /* 0x800A9AE0 */ ctx.call_indirect(0x800E8A5Cu, mem); // bl 0x800E8A5C <memset>
    /* 0x800A9AE4 */ mem.write_u8(ctx.r[30] + (1284), static_cast<uint8_t>(ctx.r[29])); // stb r29, 1284(r30)
    /* 0x800A9AE8 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800A9AEC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (28)); // lwz r0, 28(r1)
    /* 0x800A9AF0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800A9AF4 */ ctx.lmw(mem, 29, ctx.r[1] + (12)); // lmw r29, 12(r1)
    /* 0x800A9AF8 */ ctx.r[1] = ctx.r[1] + (24); // addi r1, r1, 24
    /* 0x800A9AFC */ return; // blr
}

// [0x800A9B00] cObj10::Initialize(void) (obj10.obj, 1 insns / 0x4 bytes)
void cObj10__Initialize_800A9B00(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A9B00 */ return; // blr
}

// [0x800A9B04] cObj10::Main(void) (obj10.obj, 326 insns / 0x518 bytes)
void cObj10__Main_800A9B04(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800A9B04 */ ctx.r[1] += (-56); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -56(r1)
    /* 0x800A9B08 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800A9B0C */ ctx.stmw(mem, 26, ctx.r[1] + (32)); // stmw r26, 32(r1)
    /* 0x800A9B10 */ mem.write_u32(ctx.r[1] + (60), ctx.r[0]); // stw r0, 60(r1)
    /* 0x800A9B14 */ ctx.r[31] = ctx.r[3]; // mr r31, r3
    /* 0x800A9B18 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (1220)); // lwz r0, 1220(r31)
    /* 0x800A9B1C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800A9B20 */ if (ctx.eval_bc(12, 2)) goto loc_800A9B38; // bc 12, 2, 0x800A9B38
    /* 0x800A9B24 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A9B28 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A9B2C */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-14736)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -14736(r9) [0x8016C670]
    /* 0x800A9B30 */ ctx.f[2] = mem.read_f32(ctx.r[11] + (-14732)); ctx.ps0[2] = static_cast<float>(ctx.f[2]); // lfs f2, -14732(r11) [0x8016C674]
    /* 0x800A9B34 */ MotionMove_800A2434(ctx, mem); // bl 0x800A2434 <MotionMove(cEm *, float, float)>
loc_800A9B38:;
    /* 0x800A9B38 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A9B3C */ ctx.f[0] = mem.read_f32(ctx.r[31] + (1232)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1232(r31)
    /* 0x800A9B40 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-14728)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -14728(r9) [0x8016C678]
    /* 0x800A9B44 */ ctx.f[12] = mem.read_f32(ctx.r[31] + (1224)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 1224(r31)
    /* 0x800A9B48 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f13
    /* 0x800A9B4C */ ctx.cmp_f64(0, ctx.f[12], ctx.f[0]); // fcmpu cr0, f12, f0
    /* 0x800A9B50 */ if (ctx.eval_bc(12, 2)) goto loc_800A9C2C; // bc 12, 2, 0x800A9C2C
    /* 0x800A9B54 */ ctx.r[28] = ctx.r[31] + (1236); // addi r28, r31, 1236
    /* 0x800A9B58 */ ctx.r[10] = ctx.r[28]; // mr r10, r28
    /* 0x800A9B5C */ if (ctx.eval_bc(4, 1)) goto loc_800A9B70; // bc 4, 1, 0x800A9B70
    /* 0x800A9B60 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A9B64 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-14724)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -14724(r9) [0x8016C67C]
    /* 0x800A9B68 */ ctx.f[0] = static_cast<float>(ctx.f[12] - ctx.f[0]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fsubs f0, f12, f0
    /* 0x800A9B6C */ goto loc_800A9B7C; // b 0x800A9B7C <sub_800A9B7C>
loc_800A9B70:;
    /* 0x800A9B70 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A9B74 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-14724)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -14724(r9) [0x8016C67C]
    /* 0x800A9B78 */ ctx.f[0] = static_cast<float>(ctx.f[12] + ctx.f[0]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f12, f0
loc_800A9B7C:;
    /* 0x800A9B7C */ mem.write_f32(ctx.r[31] + (1224), static_cast<float>(ctx.f[0])); // stfs f0, 1224(r31)
    /* 0x800A9B80 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (1232)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1232(r31)
    /* 0x800A9B84 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A9B88 */ ctx.f[11] = mem.read_f32(ctx.r[9] + (-14728)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -14728(r9) [0x8016C678]
    /* 0x800A9B8C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A9B90 */ ctx.f[10] = ctx.f[0]; ctx.ps0[10] = static_cast<float>(ctx.f[0]); // fmr f10, f0
    /* 0x800A9B94 */ ctx.f[12] = mem.read_f32(ctx.r[31] + (1224)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 1224(r31)
    /* 0x800A9B98 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f11
    /* 0x800A9B9C */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-14720)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -14720(r11) [0x8016C680]
    /* 0x800A9BA0 */ ctx.f[12] = static_cast<float>(ctx.f[0] - ctx.f[12]); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // fsubs f12, f0, f12
    /* 0x800A9BA4 */ ctx.cmp_f64(0, ctx.f[12], ctx.f[13]); // fcmpu cr0, f12, f13
    /* 0x800A9BA8 */ if (ctx.eval_bc(4, 0)) goto loc_800A9BC0; // bc 4, 0, 0x800A9BC0
    /* 0x800A9BAC */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A9BB0 */ ctx.f[13] = -ctx.f[12]; ctx.ps0[13] = -ctx.ps0[12]; // fneg f13, f12
    /* 0x800A9BB4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-14724)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -14724(r9) [0x8016C67C]
    /* 0x800A9BB8 */ ctx.cmp_f64(0, ctx.f[13], ctx.f[0]); // fcmpu cr0, f13, f0
    /* 0x800A9BBC */ goto loc_800A9BCC; // b 0x800A9BCC <sub_800A9BCC>
loc_800A9BC0:;
    /* 0x800A9BC0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A9BC4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-14724)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -14724(r9) [0x8016C67C]
    /* 0x800A9BC8 */ ctx.cmp_f64(0, ctx.f[12], ctx.f[0]); // fcmpu cr0, f12, f0
loc_800A9BCC:;
    /* 0x800A9BCC */ if (ctx.eval_bc(12, 0)) goto loc_800A9BDC; // bc 12, 0, 0x800A9BDC
    /* 0x800A9BD0 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (1216)); // lwz r0, 1216(r31)
    /* 0x800A9BD4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), -1); // cmpwi cr0, r0, -1
    /* 0x800A9BD8 */ if (ctx.eval_bc(12, 2)) goto loc_800A9BF8; // bc 12, 2, 0x800A9BF8
loc_800A9BDC:;
    /* 0x800A9BDC */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A9BE0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A9BE4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-14728)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -14728(r9) [0x8016C678]
    /* 0x800A9BE8 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-14720)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -14720(r11) [0x8016C680]
    /* 0x800A9BEC */ ctx.f[0] = static_cast<float>(ctx.f[10] + ctx.f[0]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f10, f0
    /* 0x800A9BF0 */ mem.write_f32(ctx.r[31] + (1224), static_cast<float>(ctx.f[0])); // stfs f0, 1224(r31)
    /* 0x800A9BF4 */ mem.write_f32(ctx.r[31] + (1228), static_cast<float>(ctx.f[13])); // stfs f13, 1228(r31)
loc_800A9BF8:;
    /* 0x800A9BF8 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A9BFC */ ctx.f[11] = mem.read_f32(ctx.r[31] + (1224)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 1224(r31)
    /* 0x800A9C00 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-14728)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -14728(r11) [0x8016C678]
    /* 0x800A9C04 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A9C08 */ ctx.f[12] = mem.read_f32(ctx.r[9] + (-14716)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -14716(r9) [0x8016C684]
    /* 0x800A9C0C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A9C10 */ ctx.f[0] = static_cast<float>(ctx.f[11] - ctx.f[0]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fsubs f0, f11, f0
    /* 0x800A9C14 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-14712)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -14712(r11) [0x8016C688]
    /* 0x800A9C18 */ mem.write_f32(ctx.r[31] + (196), static_cast<float>(ctx.f[11])); // stfs f11, 196(r31)
    /* 0x800A9C1C */ ctx.f[0] = static_cast<float>(ctx.f[0] - ctx.f[12]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fsubs f0, f0, f12
    /* 0x800A9C20 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r10)
    /* 0x800A9C24 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800A9C28 */ goto loc_800A9C60; // b 0x800A9C60 <sub_800A9C60>
loc_800A9C2C:;
    /* 0x800A9C2C */ ctx.f[1] = mem.read_f32(ctx.r[31] + (1228)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, 1228(r31)
    /* 0x800A9C30 */ ctx.r[28] = ctx.r[31] + (1236); // addi r28, r31, 1236
    /* 0x800A9C34 */ ctx.call_indirect(0x800E46B4u, mem); // bl 0x800E46B4 <sinf>
    /* 0x800A9C38 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800A9C3C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800A9C40 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (1228)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1228(r31)
    /* 0x800A9C44 */ ctx.f[11] = mem.read_f32(ctx.r[9] + (-14724)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -14724(r9) [0x8016C67C]
    /* 0x800A9C48 */ ctx.f[12] = mem.read_f32(ctx.r[11] + (-14708)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -14708(r11) [0x8016C68C]
    /* 0x800A9C4C */ ctx.f[13] = mem.read_f32(ctx.r[31] + (1224)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 1224(r31)
    /* 0x800A9C50 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[12]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f12
    /* 0x800A9C54 */ ctx.f[1] = static_cast<float>(ctx.f[1] * ctx.f[11] + ctx.f[13]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fmadds f1, f1, f11, f13
    /* 0x800A9C58 */ mem.write_f32(ctx.r[31] + (1228), static_cast<float>(ctx.f[0])); // stfs f0, 1228(r31)
    /* 0x800A9C5C */ mem.write_f32(ctx.r[31] + (196), static_cast<float>(ctx.f[1])); // stfs f1, 196(r31)
loc_800A9C60:;
    /* 0x800A9C60 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (204)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 204(r31)
    /* 0x800A9C64 */ ctx.r[9] = ctx.r[31] + (204); // addi r9, r31, 204
    /* 0x800A9C68 */ ctx.r[30] = ctx.r[1] + (16); // addi r30, r1, 16
    /* 0x800A9C6C */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A9C70 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800A9C74 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A9C78 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A9C7C */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A9C80 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A9C84 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800A9C88 */ RotMatrix_8009E1D0(ctx, mem); // bl 0x8009E1D0 <RotMatrix(float (*)[3], cVec &)>
    /* 0x800A9C8C */ ctx.f[13] = mem.read_f32(ctx.r[31] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r31)
    /* 0x800A9C90 */ ctx.r[9] = ctx.r[31] + (192); // addi r9, r31, 192
    /* 0x800A9C94 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A9C98 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A9C9C */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800A9CA0 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A9CA4 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A9CA8 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A9CAC */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800A9CB0 */ TransMatrix_8009E1B4(ctx, mem); // bl 0x8009E1B4 <TransMatrix(float (*)[3], cVec &)>
    /* 0x800A9CB4 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (216)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 216(r31)
    /* 0x800A9CB8 */ ctx.r[9] = ctx.r[31] + (216); // addi r9, r31, 216
    /* 0x800A9CBC */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800A9CC0 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A9CC4 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800A9CC8 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800A9CCC */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800A9CD0 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800A9CD4 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800A9CD8 */ ScaleMatrix_8009E168(ctx, mem); // bl 0x8009E168 <ScaleMatrix(float (*)[3], cVec &)>
    /* 0x800A9CDC */ ctx.r[3] = mem.read_u32(ctx.r[31] + (240)); // lwz r3, 240(r31)
    /* 0x800A9CE0 */ ModelMatCalc_800A0BF4(ctx, mem); // bl 0x800A0BF4 <ModelMatCalc(PARTS *)>
    /* 0x800A9CE4 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A9CE8 */ PartsWorldCalc_800A0E5C(ctx, mem); // bl 0x800A0E5C <PartsWorldCalc(cEm *)>
    /* 0x800A9CEC */ ctx.r[0] = mem.read_u8(ctx.r[31] + (1236)); // lbz r0, 1236(r31)
    /* 0x800A9CF0 */ ctx.r[8] = ctx.r[0] & 0x0001u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[8]), 0); // andi. r8, r0, 0x0001
    /* 0x800A9CF4 */ if (ctx.eval_bc(12, 2)) goto loc_800AA008; // bc 12, 2, 0x800AA008
    /* 0x800A9CF8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A9CFC */ ctx.r[29] = 0x00000000u; // li r29, 0
    /* 0x800A9D00 */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800A9D04 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800A9D08 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800A9D0C */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800A9D10 */ ctx.rlwinm(9, 0, 30u, 2u, 31u, true); // rlwinm r9, r0, 30, 2, 31
    /* 0x800A9D14 */ if (ctx.eval_bc(4, 2)) goto loc_800A9D24; // bc 4, 2, 0x800A9D24
    /* 0x800A9D18 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800A9D1C */ ctx.r[3] = ctx.r[3] + (-14744); // addi r3, r3, -14744 -> 0x8016C668 /* "vector" */
    /* 0x800A9D20 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800A9D24:;
    /* 0x800A9D24 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800A9D28 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800A9D2C */ ctx.r[4] = mem.read_u32(ctx.r[9] + (0)); // lwz r4, 0(r9)
    /* 0x800A9D30 */ ctx.r[4] = ctx.r[4] + (192); // addi r4, r4, 192
    /* 0x800A9D34 */ AreaHitCheck_80003D20(ctx, mem); // bl 0x80003D20 <AreaHitCheck(AREA_HIT_DATA *, Vec *)>
    /* 0x800A9D38 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 1); // cmpwi cr0, r3, 1
    /* 0x800A9D3C */ if (ctx.eval_bc(4, 2)) goto loc_800AA008; // bc 4, 2, 0x800AA008
    /* 0x800A9D40 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A9D44 */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800A9D48 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800A9D4C */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800A9D50 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800A9D54 */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800A9D58 */ ctx.cmp_u32(0, ctx.r[29], ctx.r[0]); // cmplw cr0, r29, r0
    /* 0x800A9D5C */ if (ctx.eval_bc(12, 0)) goto loc_800A9D6C; // bc 12, 0, 0x800A9D6C
    /* 0x800A9D60 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800A9D64 */ ctx.r[3] = ctx.r[3] + (-14744); // addi r3, r3, -14744 -> 0x8016C668 /* "vector" */
    /* 0x800A9D68 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800A9D6C:;
    /* 0x800A9D6C */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800A9D70 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800A9D74 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (1236)); // lwz r0, 1236(r11)
    /* 0x800A9D78 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800A9D7C */ if (ctx.eval_bc(4, 1)) goto loc_800AA008; // bc 4, 1, 0x800AA008
    /* 0x800A9D80 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (1216)); // lwz r9, 1216(r31)
    /* 0x800A9D84 */ ctx.r[0] = 0x000000FEu; // li r0, 254
    /* 0x800A9D88 */ mem.write_u8(ctx.r[31] + (1236), static_cast<uint8_t>(ctx.r[0])); // stb r0, 1236(r31)
    /* 0x800A9D8C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), -1); // cmpwi cr0, r9, -1
    /* 0x800A9D90 */ if (ctx.eval_bc(12, 2)) goto loc_800A9DDC; // bc 12, 2, 0x800A9DDC
    /* 0x800A9D94 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A9D98 */ ctx.r[11] = mem.read_u16(ctx.r[31] + (1218)); // lhz r11, 1218(r31)
    /* 0x800A9D9C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800A9DA0 */ ctx.r[10] = ctx.r[9] + (27284); // addi r10, r9, 27284
    /* 0x800A9DA4 */ ctx.r[8] = ctx.r[0] & 0x00200000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[8]), 0); // andis. r8, r0, 0x0020
    /* 0x800A9DA8 */ if (ctx.eval_bc(4, 2)) goto loc_800A9DBC; // bc 4, 2, 0x800A9DBC
    /* 0x800A9DAC */ ctx.r[0] = mem.read_u8(ctx.r[9] + (27256)); // lbz r0, 27256(r9)
    /* 0x800A9DB0 */ ctx.rlwinm(0, 0, 7u, 0u, 24u, false); // rlwinm r0, r0, 7, 0, 24
    /* 0x800A9DB4 */ ctx.r[8] = ctx.r[10] + ctx.r[0]; // add r8, r10, r0
    /* 0x800A9DB8 */ goto loc_800A9DC0; // b 0x800A9DC0 <sub_800A9DC0>
loc_800A9DBC:;
    /* 0x800A9DBC */ ctx.r[8] = ctx.r[9] + (28820); // addi r8, r9, 28820
loc_800A9DC0:;
    /* 0x800A9DC0 */ ctx.rlwinm(10, 11, 29u, 19u, 29u, false); // rlwinm r10, r11, 29, 19, 29
    /* 0x800A9DC4 */ ctx.r[0] = 0x80000000u; // lis r0, 0x8000
    /* 0x800A9DC8 */ ctx.r[9] = mem.read_u32(ctx.r[10] + ctx.r[8]); // lwzx r9, r10, r8
    /* 0x800A9DCC */ ctx.rlwinm(11, 11, 0u, 27u, 31u, false); // rlwinm r11, r11, 0, 27, 31
    /* 0x800A9DD0 */ ctx.r[0] = (ctx.r[11] & 32u) ? 0u : (ctx.r[0] >> (ctx.r[11] & 31u)); // srw r0, r0, r11
    /* 0x800A9DD4 */ ctx.r[9] = ctx.r[9] | ctx.r[0]; // or r9, r9, r0
    /* 0x800A9DD8 */ mem.write_u32(ctx.r[10] + ctx.r[8], ctx.r[9]); // stwx r9, r10, r8
loc_800A9DDC:;
    /* 0x800A9DDC */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800A9DE0 */ cObj10__item_get_800AA07C(ctx, mem); // bl 0x800AA07C <cObj10::item_get(void)>
    /* 0x800A9DE4 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (1212)); // lwz r0, 1212(r31)
    /* 0x800A9DE8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 5); // cmpwi cr0, r0, 5
    /* 0x800A9DEC */ if (ctx.eval_bc(12, 2)) goto loc_800A9E0C; // bc 12, 2, 0x800A9E0C
    /* 0x800A9DF0 */ ctx.cmp_u32(0, ctx.r[0], 0x0005u); // cmplwi cr0, r0, 0x0005
    /* 0x800A9DF4 */ if (ctx.eval_bc(12, 1)) goto loc_800A9E04; // bc 12, 1, 0x800A9E04
    /* 0x800A9DF8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 2); // cmpwi cr0, r0, 2
    /* 0x800A9DFC */ if (ctx.eval_bc(12, 2)) goto loc_800A9E0C; // bc 12, 2, 0x800A9E0C
    /* 0x800A9E00 */ goto loc_800A9E24; // b 0x800A9E24 <sub_800A9E24>
loc_800A9E04:;
    /* 0x800A9E04 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 7); // cmpwi cr0, r0, 7
    /* 0x800A9E08 */ if (ctx.eval_bc(4, 2)) goto loc_800A9E24; // bc 4, 2, 0x800A9E24
loc_800A9E0C:;
    /* 0x800A9E0C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9E10 */ ctx.r[4] = 0x0000003Bu; // li r4, 59
    /* 0x800A9E14 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800A9E18 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800A9E1C */ SndSeCall_800CB7DC(ctx, mem); // bl 0x800CB7DC <SndSeCall(unsigned short, unsigned short, Vec *, unsigned char)>
    /* 0x800A9E20 */ goto loc_800A9E38; // b 0x800A9E38 <sub_800A9E38>
loc_800A9E24:;
    /* 0x800A9E24 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9E28 */ ctx.r[4] = 0x00000037u; // li r4, 55
    /* 0x800A9E2C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800A9E30 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800A9E34 */ SndSeCall_800CB7DC(ctx, mem); // bl 0x800CB7DC <SndSeCall(unsigned short, unsigned short, Vec *, unsigned char)>
loc_800A9E38:;
    /* 0x800A9E38 */ ctx.r[4] = 0x00000039u; // li r4, 57
    /* 0x800A9E3C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800A9E40 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800A9E44 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9E48 */ SndSeCall_800CB7DC(ctx, mem); // bl 0x800CB7DC <SndSeCall(unsigned short, unsigned short, Vec *, unsigned char)>
    /* 0x800A9E4C */ ctx.r[4] = mem.read_u8(ctx.r[31] + (1284)); // lbz r4, 1284(r31)
    /* 0x800A9E50 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9E54 */ ctx.r[5] = ctx.r[31]; // mr r5, r31
    /* 0x800A9E58 */ EspgenDelete_8008E8B8(ctx, mem); // bl 0x8008E8B8 <EspgenDelete(unsigned short, unsigned char, void *)>
    /* 0x800A9E5C */ ctx.r[0] = mem.read_u32(ctx.r[31] + (1212)); // lwz r0, 1212(r31)
    /* 0x800A9E60 */ ctx.cmp_u32(0, ctx.r[0], 0x0005u); // cmplwi cr0, r0, 0x0005
    /* 0x800A9E64 */ if (ctx.eval_bc(4, 1)) goto loc_800A9E74; // bc 4, 1, 0x800A9E74
    /* 0x800A9E68 */ ctx.cmp_u32(0, ctx.r[0], 0x0007u); // cmplwi cr0, r0, 0x0007
    /* 0x800A9E6C */ if (ctx.eval_bc(12, 1)) goto loc_800AA000; // bc 12, 1, 0x800AA000
    /* 0x800A9E70 */ goto loc_800A9F5C; // b 0x800A9F5C <sub_800A9F5C>
loc_800A9E74:;
    /* 0x800A9E74 */ ctx.cmp_u32(0, ctx.r[0], 0x0003u); // cmplwi cr0, r0, 0x0003
    /* 0x800A9E78 */ if (ctx.eval_bc(4, 0)) goto loc_800A9EB4; // bc 4, 0, 0x800A9EB4
    /* 0x800A9E7C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A9E80 */ ctx.r[26] = 0x00000000u; // li r26, 0
    /* 0x800A9E84 */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800A9E88 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800A9E8C */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800A9E90 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800A9E94 */ ctx.rlwinm(8, 0, 30u, 2u, 31u, true); // rlwinm r8, r0, 30, 2, 31
    /* 0x800A9E98 */ if (ctx.eval_bc(4, 2)) goto loc_800A9EA8; // bc 4, 2, 0x800A9EA8
    /* 0x800A9E9C */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800A9EA0 */ ctx.r[3] = ctx.r[3] + (-14744); // addi r3, r3, -14744 -> 0x8016C668 /* "vector" */
    /* 0x800A9EA4 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800A9EA8:;
    /* 0x800A9EA8 */ ctx.r[27] = mem.read_u32(ctx.r[30] + (0)); // lwz r27, 0(r30)
    /* 0x800A9EAC */ ctx.r[4] = 0x00000014u; // li r4, 20
    /* 0x800A9EB0 */ goto loc_800A9EE8; // b 0x800A9EE8 <sub_800A9EE8>
loc_800A9EB4:;
    /* 0x800A9EB4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A9EB8 */ ctx.r[26] = 0x00000000u; // li r26, 0
    /* 0x800A9EBC */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800A9EC0 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800A9EC4 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800A9EC8 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800A9ECC */ ctx.rlwinm(8, 0, 30u, 2u, 31u, true); // rlwinm r8, r0, 30, 2, 31
    /* 0x800A9ED0 */ if (ctx.eval_bc(4, 2)) goto loc_800A9EE0; // bc 4, 2, 0x800A9EE0
    /* 0x800A9ED4 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800A9ED8 */ ctx.r[3] = ctx.r[3] + (-14744); // addi r3, r3, -14744 -> 0x8016C668 /* "vector" */
    /* 0x800A9EDC */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800A9EE0:;
    /* 0x800A9EE0 */ ctx.r[27] = mem.read_u32(ctx.r[30] + (0)); // lwz r27, 0(r30)
    /* 0x800A9EE4 */ ctx.r[4] = 0x00000013u; // li r4, 19
loc_800A9EE8:;
    /* 0x800A9EE8 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9EEC */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800A9EF0 */ ctx.r[28] = ctx.r[3]; // mr r28, r3
    /* 0x800A9EF4 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9EF8 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800A9EFC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A9F00 */ ctx.r[29] = ctx.r[3]; // mr r29, r3
    /* 0x800A9F04 */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800A9F08 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800A9F0C */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800A9F10 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800A9F14 */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800A9F18 */ ctx.cmp_u32(0, ctx.r[26], ctx.r[0]); // cmplw cr0, r26, r0
    /* 0x800A9F1C */ if (ctx.eval_bc(12, 0)) goto loc_800A9F2C; // bc 12, 0, 0x800A9F2C
    /* 0x800A9F20 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800A9F24 */ ctx.r[3] = ctx.r[3] + (-14744); // addi r3, r3, -14744 -> 0x8016C668 /* "vector" */
    /* 0x800A9F28 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800A9F2C:;
    /* 0x800A9F2C */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800A9F30 */ ctx.r[6] = ctx.r[28]; // mr r6, r28
    /* 0x800A9F34 */ ctx.r[3] = mem.read_u32(ctx.r[27] + (0)); // lwz r3, 0(r27)
    /* 0x800A9F38 */ ctx.r[7] = ctx.r[29]; // mr r7, r29
    /* 0x800A9F3C */ ctx.r[10] = mem.read_u32(ctx.r[9] + (0)); // lwz r10, 0(r9)
    /* 0x800A9F40 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800A9F44 */ mem.write_u32(ctx.r[1] + (8), ctx.r[26]); // stw r26, 8(r1)
    /* 0x800A9F48 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800A9F4C */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800A9F50 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800A9F54 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800A9F58 */ goto loc_800AA000; // b 0x800AA000 <sub_800AA000>
loc_800A9F5C:;
    /* 0x800A9F5C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A9F60 */ ctx.r[26] = 0x00000000u; // li r26, 0
    /* 0x800A9F64 */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800A9F68 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800A9F6C */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800A9F70 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800A9F74 */ ctx.rlwinm(8, 0, 30u, 2u, 31u, true); // rlwinm r8, r0, 30, 2, 31
    /* 0x800A9F78 */ if (ctx.eval_bc(4, 2)) goto loc_800A9F88; // bc 4, 2, 0x800A9F88
    /* 0x800A9F7C */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800A9F80 */ ctx.r[3] = ctx.r[3] + (-14744); // addi r3, r3, -14744 -> 0x8016C668 /* "vector" */
    /* 0x800A9F84 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800A9F88:;
    /* 0x800A9F88 */ ctx.r[27] = mem.read_u32(ctx.r[30] + (0)); // lwz r27, 0(r30)
    /* 0x800A9F8C */ ctx.r[4] = 0x00000012u; // li r4, 18
    /* 0x800A9F90 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9F94 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800A9F98 */ ctx.r[28] = ctx.r[3]; // mr r28, r3
    /* 0x800A9F9C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800A9FA0 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800A9FA4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800A9FA8 */ ctx.r[29] = ctx.r[3]; // mr r29, r3
    /* 0x800A9FAC */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800A9FB0 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800A9FB4 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800A9FB8 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800A9FBC */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800A9FC0 */ ctx.cmp_u32(0, ctx.r[26], ctx.r[0]); // cmplw cr0, r26, r0
    /* 0x800A9FC4 */ if (ctx.eval_bc(12, 0)) goto loc_800A9FD4; // bc 12, 0, 0x800A9FD4
    /* 0x800A9FC8 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800A9FCC */ ctx.r[3] = ctx.r[3] + (-14744); // addi r3, r3, -14744 -> 0x8016C668 /* "vector" */
    /* 0x800A9FD0 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800A9FD4:;
    /* 0x800A9FD4 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800A9FD8 */ ctx.r[6] = ctx.r[28]; // mr r6, r28
    /* 0x800A9FDC */ ctx.r[3] = mem.read_u32(ctx.r[27] + (0)); // lwz r3, 0(r27)
    /* 0x800A9FE0 */ ctx.r[7] = ctx.r[29]; // mr r7, r29
    /* 0x800A9FE4 */ ctx.r[10] = mem.read_u32(ctx.r[9] + (0)); // lwz r10, 0(r9)
    /* 0x800A9FE8 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800A9FEC */ mem.write_u32(ctx.r[1] + (8), ctx.r[26]); // stw r26, 8(r1)
    /* 0x800A9FF0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800A9FF4 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800A9FF8 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800A9FFC */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800AA000:;
    /* 0x800AA000 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA004 */ PushObj_800749C8(ctx, mem); // bl 0x800749C8 <PushObj(cObj *)>
loc_800AA008:;
    /* 0x800AA008 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (60)); // lwz r0, 60(r1)
    /* 0x800AA00C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AA010 */ ctx.lmw(mem, 26, ctx.r[1] + (32)); // lmw r26, 32(r1)
    /* 0x800AA014 */ ctx.r[1] = ctx.r[1] + (56); // addi r1, r1, 56
    /* 0x800AA018 */ return; // blr
}

// [0x800AA01C] cObj10::Release(void) (obj10.obj, 15 insns / 0x3C bytes)
void cObj10__Release_800AA01C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA01C */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800AA020 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AA024 */ mem.write_u32(ctx.r[1] + (12), ctx.r[31]); // stw r31, 12(r1)
    /* 0x800AA028 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800AA02C */ ctx.r[31] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // mr r31, r3
    /* 0x800AA030 */ if (ctx.eval_bc(12, 2)) goto loc_800AA03C; // bc 12, 2, 0x800AA03C
    /* 0x800AA034 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA038 */ EspgenDeleteEm_8008E940(ctx, mem); // bl 0x8008E940 <EspgenDeleteEm(cEm *)>
loc_800AA03C:;
    /* 0x800AA03C */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA040 */ PushObj_800749C8(ctx, mem); // bl 0x800749C8 <PushObj(cObj *)>
    /* 0x800AA044 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800AA048 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AA04C */ ctx.r[31] = mem.read_u32(ctx.r[1] + (12)); // lwz r31, 12(r1)
    /* 0x800AA050 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800AA054 */ return; // blr
}

// [0x800AA058] cObj10::Show(void) (obj10.obj, 4 insns / 0x10 bytes)
void cObj10__Show_800AA058(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA058 */ ctx.r[0] = mem.read_u32(ctx.r[3] + (244)); // lwz r0, 244(r3)
    /* 0x800AA05C */ ctx.r[0] = ctx.r[0] | 0x0202u; // ori r0, r0, 0x0202
    /* 0x800AA060 */ mem.write_u32(ctx.r[3] + (244), ctx.r[0]); // stw r0, 244(r3)
    /* 0x800AA064 */ return; // blr
}

// [0x800AA068] cObj10::Hide(void) (obj10.obj, 5 insns / 0x14 bytes)
void cObj10__Hide_800AA068(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA068 */ ctx.r[0] = mem.read_u32(ctx.r[3] + (244)); // lwz r0, 244(r3)
    /* 0x800AA06C */ ctx.r[9] = 0xFFFFFDFDu; // li r9, -515
    /* 0x800AA070 */ ctx.r[0] = ctx.r[0] & ctx.r[9]; // and r0, r0, r9
    /* 0x800AA074 */ mem.write_u32(ctx.r[3] + (244), ctx.r[0]); // stw r0, 244(r3)
    /* 0x800AA078 */ return; // blr
}

// [0x800AA07C] cObj10::item_get(void) (obj10.obj, 90 insns / 0x168 bytes)
void cObj10__item_get_800AA07C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA07C */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800AA080 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AA084 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800AA088 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AA08C */ ctx.r[0] = mem.read_u8(ctx.r[9] + (26651)); // lbz r0, 26651(r9)
    /* 0x800AA090 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 1); // cmpwi cr0, r0, 1
    /* 0x800AA094 */ if (ctx.eval_bc(12, 2)) goto loc_800AA0AC; // bc 12, 2, 0x800AA0AC
    /* 0x800AA098 */ if (ctx.eval_bc(4, 1)) goto loc_800AA0A4; // bc 4, 1, 0x800AA0A4
    /* 0x800AA09C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 2); // cmpwi cr0, r0, 2
    /* 0x800AA0A0 */ if (ctx.eval_bc(12, 2)) goto loc_800AA0B4; // bc 12, 2, 0x800AA0B4
loc_800AA0A4:;
    /* 0x800AA0A4 */ ctx.r[9] = 0x000001F4u; // li r9, 500
    /* 0x800AA0A8 */ goto loc_800AA0B8; // b 0x800AA0B8 <sub_800AA0B8>
loc_800AA0AC:;
    /* 0x800AA0AC */ ctx.r[9] = 0x000000FAu; // li r9, 250
    /* 0x800AA0B0 */ goto loc_800AA0B8; // b 0x800AA0B8 <sub_800AA0B8>
loc_800AA0B4:;
    /* 0x800AA0B4 */ ctx.r[9] = 0x0000004Bu; // li r9, 75
loc_800AA0B8:;
    /* 0x800AA0B8 */ ctx.r[3] = mem.read_u32(ctx.r[3] + (1212)); // lwz r3, 1212(r3)
    /* 0x800AA0BC */ ctx.cmp_u32(0, ctx.r[3], 0x0004u); // cmplwi cr0, r3, 0x0004
    /* 0x800AA0C0 */ if (ctx.eval_bc(12, 1)) goto loc_800AA0D8; // bc 12, 1, 0x800AA0D8
    /* 0x800AA0C4 */ ctx.cmp_u32(0, ctx.r[3], 0x0003u); // cmplwi cr0, r3, 0x0003
    /* 0x800AA0C8 */ if (ctx.eval_bc(4, 0)) goto loc_800AA148; // bc 4, 0, 0x800AA148
    /* 0x800AA0CC */ ctx.cmp_u32(0, ctx.r[3], 0x0001u); // cmplwi cr0, r3, 0x0001
    /* 0x800AA0D0 */ if (ctx.eval_bc(4, 1)) goto loc_800AA0F4; // bc 4, 1, 0x800AA0F4
    /* 0x800AA0D4 */ goto loc_800AA12C; // b 0x800AA12C <sub_800AA12C>
loc_800AA0D8:;
    /* 0x800AA0D8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 6); // cmpwi cr0, r3, 6
    /* 0x800AA0DC */ if (ctx.eval_bc(12, 2)) goto loc_800AA19C; // bc 12, 2, 0x800AA19C
    /* 0x800AA0E0 */ ctx.cmp_u32(0, ctx.r[3], 0x0006u); // cmplwi cr0, r3, 0x0006
    /* 0x800AA0E4 */ if (ctx.eval_bc(12, 0)) goto loc_800AA180; // bc 12, 0, 0x800AA180
    /* 0x800AA0E8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 7); // cmpwi cr0, r3, 7
    /* 0x800AA0EC */ if (ctx.eval_bc(12, 2)) goto loc_800AA1AC; // bc 12, 2, 0x800AA1AC
    /* 0x800AA0F0 */ goto loc_800AA1BC; // b 0x800AA1BC <sub_800AA1BC>
loc_800AA0F4:;
    /* 0x800AA0F4 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800AA0F8 */ ctx.r[9] = mem.read_u16(ctx.r[10] + (26644)); // lhz r9, 26644(r10)
    /* 0x800AA0FC */ ctx.r[8] = mem.read_u16(ctx.r[10] + (26646)); // lhz r8, 26646(r10)
    /* 0x800AA100 */ ctx.r[9] = ctx.r[9] + (250); // addi r9, r9, 250
    /* 0x800AA104 */ ctx.r[11] = static_cast<uint32_t>(static_cast<int32_t>(static_cast<int16_t>(ctx.r[8]))); // extsh r11, r8
    /* 0x800AA108 */ ctx.r[0] = static_cast<uint32_t>(static_cast<int32_t>(static_cast<int16_t>(ctx.r[9]))); // extsh r0, r9
    /* 0x800AA10C */ mem.write_u16(ctx.r[10] + (26644), static_cast<uint16_t>(ctx.r[9])); // sth r9, 26644(r10)
    /* 0x800AA110 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), static_cast<int32_t>(ctx.r[11])); // cmpw cr0, r0, r11
    /* 0x800AA114 */ if (ctx.eval_bc(4, 1)) goto loc_800AA11C; // bc 4, 1, 0x800AA11C
    /* 0x800AA118 */ mem.write_u16(ctx.r[10] + (26644), static_cast<uint16_t>(ctx.r[8])); // sth r8, 26644(r10)
loc_800AA11C:;
    /* 0x800AA11C */ ctx.r[3] = 0x80190000u; // lis r3, 0x8019
    /* 0x800AA120 */ ctx.r[3] = ctx.r[3] + (22592); // addi r3, r3, 22592 -> cGaugeWk
    /* 0x800AA124 */ cGauge__EnergyUp_80097594(ctx, mem); // bl 0x80097594 <cGauge::EnergyUp(void)>
    /* 0x800AA128 */ goto loc_800AA1BC; // b 0x800AA1BC <sub_800AA1BC>
loc_800AA12C:;
    /* 0x800AA12C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AA130 */ ctx.r[3] = 0x80190000u; // lis r3, 0x8019
    /* 0x800AA134 */ ctx.r[3] = ctx.r[3] + (22592); // addi r3, r3, 22592 -> cGaugeWk
    /* 0x800AA138 */ ctx.r[0] = mem.read_u16(ctx.r[9] + (26646)); // lhz r0, 26646(r9)
    /* 0x800AA13C */ mem.write_u16(ctx.r[9] + (26644), static_cast<uint16_t>(ctx.r[0])); // sth r0, 26644(r9)
    /* 0x800AA140 */ cGauge__EnergyUp_80097594(ctx, mem); // bl 0x80097594 <cGauge::EnergyUp(void)>
    /* 0x800AA144 */ goto loc_800AA1BC; // b 0x800AA1BC <sub_800AA1BC>
loc_800AA148:;
    /* 0x800AA148 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800AA14C */ ctx.r[0] = mem.read_u16(ctx.r[10] + (26640)); // lhz r0, 26640(r10)
    /* 0x800AA150 */ ctx.r[8] = mem.read_u16(ctx.r[10] + (26642)); // lhz r8, 26642(r10)
    /* 0x800AA154 */ ctx.r[0] = ctx.r[9] + ctx.r[0]; // add r0, r9, r0
    /* 0x800AA158 */ ctx.r[11] = static_cast<uint32_t>(static_cast<int32_t>(static_cast<int16_t>(ctx.r[8]))); // extsh r11, r8
    /* 0x800AA15C */ ctx.r[9] = static_cast<uint32_t>(static_cast<int32_t>(static_cast<int16_t>(ctx.r[0]))); // extsh r9, r0
    /* 0x800AA160 */ mem.write_u16(ctx.r[10] + (26640), static_cast<uint16_t>(ctx.r[0])); // sth r0, 26640(r10)
    /* 0x800AA164 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), static_cast<int32_t>(ctx.r[11])); // cmpw cr0, r9, r11
    /* 0x800AA168 */ if (ctx.eval_bc(4, 1)) goto loc_800AA170; // bc 4, 1, 0x800AA170
    /* 0x800AA16C */ mem.write_u16(ctx.r[10] + (26640), static_cast<uint16_t>(ctx.r[8])); // sth r8, 26640(r10)
loc_800AA170:;
    /* 0x800AA170 */ ctx.r[3] = 0x80190000u; // lis r3, 0x8019
    /* 0x800AA174 */ ctx.r[3] = ctx.r[3] + (22592); // addi r3, r3, 22592 -> cGaugeWk
    /* 0x800AA178 */ cGauge__LifeUp_80097408(ctx, mem); // bl 0x80097408 <cGauge::LifeUp(void)>
    /* 0x800AA17C */ goto loc_800AA1BC; // b 0x800AA1BC <sub_800AA1BC>
loc_800AA180:;
    /* 0x800AA180 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AA184 */ ctx.r[3] = 0x80190000u; // lis r3, 0x8019
    /* 0x800AA188 */ ctx.r[3] = ctx.r[3] + (22592); // addi r3, r3, 22592 -> cGaugeWk
    /* 0x800AA18C */ ctx.r[0] = mem.read_u16(ctx.r[9] + (26642)); // lhz r0, 26642(r9)
    /* 0x800AA190 */ mem.write_u16(ctx.r[9] + (26640), static_cast<uint16_t>(ctx.r[0])); // sth r0, 26640(r9)
    /* 0x800AA194 */ cGauge__LifeUp_80097408(ctx, mem); // bl 0x80097408 <cGauge::LifeUp(void)>
    /* 0x800AA198 */ goto loc_800AA1BC; // b 0x800AA1BC <sub_800AA1BC>
loc_800AA19C:;
    /* 0x800AA19C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800AA1A0 */ ctx.r[9] = mem.read_u16(ctx.r[11] + (26648)); // lhz r9, 26648(r11)
    /* 0x800AA1A4 */ ctx.r[9] = ctx.r[9] + (1); // addi r9, r9, 1
    /* 0x800AA1A8 */ goto loc_800AA1B8; // b 0x800AA1B8 <sub_800AA1B8>
loc_800AA1AC:;
    /* 0x800AA1AC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800AA1B0 */ ctx.r[9] = mem.read_u16(ctx.r[11] + (26648)); // lhz r9, 26648(r11)
    /* 0x800AA1B4 */ ctx.r[9] = ctx.r[9] + (3); // addi r9, r9, 3
loc_800AA1B8:;
    /* 0x800AA1B8 */ mem.write_u16(ctx.r[11] + (26648), static_cast<uint16_t>(ctx.r[9])); // sth r9, 26648(r11)
loc_800AA1BC:;
    /* 0x800AA1BC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AA1C0 */ ctx.r[0] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (26648)))); // lha r0, 26648(r9)
    /* 0x800AA1C4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 99); // cmpwi cr0, r0, 99
    /* 0x800AA1C8 */ if (ctx.eval_bc(4, 1)) goto loc_800AA1D4; // bc 4, 1, 0x800AA1D4
    /* 0x800AA1CC */ ctx.r[0] = 0x00000063u; // li r0, 99
    /* 0x800AA1D0 */ mem.write_u16(ctx.r[9] + (26648), static_cast<uint16_t>(ctx.r[0])); // sth r0, 26648(r9)
loc_800AA1D4:;
    /* 0x800AA1D4 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800AA1D8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AA1DC */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800AA1E0 */ return; // blr
}

// [0x800AA1E4] cObj10::set_item_area(cVec &, long, long) (obj10.obj, 72 insns / 0x120 bytes)
void cObj10__set_item_area_800AA1E4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA1E4 */ ctx.r[1] += (-88); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -88(r1)
    /* 0x800AA1E8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AA1EC */ ctx.stmw(mem, 27, ctx.r[1] + (68)); // stmw r27, 68(r1)
    /* 0x800AA1F0 */ mem.write_u32(ctx.r[1] + (92), ctx.r[0]); // stw r0, 92(r1)
    /* 0x800AA1F4 */ ctx.r[29] = ctx.r[4]; // mr r29, r4
    /* 0x800AA1F8 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800AA1FC */ ctx.f[0] = mem.read_f32(ctx.r[29] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r29)
    /* 0x800AA200 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800AA204 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-14700)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -14700(r11) [0x8016C694 /* "GCP" */]
    /* 0x800AA208 */ ctx.r[31] = ctx.r[3]; // mr r31, r3
    /* 0x800AA20C */ ctx.f[12] = mem.read_f32(ctx.r[9] + (-14704)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -14704(r9) [0x8016C690]
    /* 0x800AA210 */ ctx.r[27] = ctx.r[5]; // mr r27, r5
    /* 0x800AA214 */ ctx.f[11] = mem.read_f32(ctx.r[29] + (0)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 0(r29)
    /* 0x800AA218 */ ctx.f[13] = static_cast<float>(ctx.f[0] - ctx.f[13]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // fsubs f13, f0, f13
    /* 0x800AA21C */ ctx.f[10] = mem.read_f32(ctx.r[29] + (8)); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // lfs f10, 8(r29)
    /* 0x800AA220 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[12]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f12
    /* 0x800AA224 */ ctx.r[28] = ctx.r[6]; // mr r28, r6
    /* 0x800AA228 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[11])); // stfs f11, 24(r1)
    /* 0x800AA22C */ ctx.r[3] = ctx.r[1] + (8); // addi r3, r1, 8
    /* 0x800AA230 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[10])); // stfs f10, 32(r1)
    /* 0x800AA234 */ ctx.r[4] = ctx.r[1] + (56); // addi r4, r1, 56
    /* 0x800AA238 */ mem.write_f32(ctx.r[1] + (28), static_cast<float>(ctx.f[0])); // stfs f0, 28(r1)
    /* 0x800AA23C */ ctx.r[5] = ctx.r[1] + (24); // addi r5, r1, 24
    /* 0x800AA240 */ mem.write_f32(ctx.r[1] + (44), static_cast<float>(ctx.f[13])); // stfs f13, 44(r1)
    /* 0x800AA244 */ ctx.r[6] = ctx.r[1] + (40); // addi r6, r1, 40
    /* 0x800AA248 */ mem.write_f32(ctx.r[1] + (40), static_cast<float>(ctx.f[11])); // stfs f11, 40(r1)
    /* 0x800AA24C */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800AA250 */ mem.write_f32(ctx.r[1] + (48), static_cast<float>(ctx.f[10])); // stfs f10, 48(r1)
    /* 0x800AA254 */ ScrHitCheck2_80007AE0(ctx, mem); // bl 0x80007AE0 <ScrHitCheck2(Vec *, Vec **, Vec *, Vec *, unsigned long)>
    /* 0x800AA258 */ ctx.r[30] = ctx.r[31] + (1236); // addi r30, r31, 1236
    /* 0x800AA25C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800AA260 */ if (ctx.eval_bc(12, 2)) goto loc_800AA26C; // bc 12, 2, 0x800AA26C
    /* 0x800AA264 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (12)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 12(r1)
    /* 0x800AA268 */ goto loc_800AA270; // b 0x800AA270 <sub_800AA270>
loc_800AA26C:;
    /* 0x800AA26C */ ctx.f[0] = mem.read_f32(ctx.r[29] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r29)
loc_800AA270:;
    /* 0x800AA270 */ mem.write_f32(ctx.r[31] + (1232), static_cast<float>(ctx.f[0])); // stfs f0, 1232(r31)
    /* 0x800AA274 */ ctx.f[0] = mem.read_f32(ctx.r[29] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r29)
    /* 0x800AA278 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800AA27C */ ctx.r[9] = 0x00000002u; // li r9, 2
    /* 0x800AA280 */ ctx.r[11] = 0x00000000u; // li r11, 0
    /* 0x800AA284 */ mem.write_f32(ctx.r[31] + (1224), static_cast<float>(ctx.f[0])); // stfs f0, 1224(r31)
    /* 0x800AA288 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800AA28C */ mem.write_u8(ctx.r[30] + (0), static_cast<uint8_t>(ctx.r[0])); // stb r0, 0(r30)
    /* 0x800AA290 */ ctx.r[8] = 0x80170000u; // lis r8, 0x8017
    /* 0x800AA294 */ mem.write_u8(ctx.r[30] + (1), static_cast<uint8_t>(ctx.r[9])); // stb r9, 1(r30)
    /* 0x800AA298 */ ctx.r[7] = 0x80170000u; // lis r7, 0x8017
    /* 0x800AA29C */ mem.write_u8(ctx.r[30] + (2), static_cast<uint8_t>(ctx.r[11])); // stb r11, 2(r30)
    /* 0x800AA2A0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[28]), -1); // cmpwi cr0, r28, -1
    /* 0x800AA2A4 */ ctx.f[11] = mem.read_f32(ctx.r[10] + (-14696)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -14696(r10) [0x8016C698]
    /* 0x800AA2A8 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (1224)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1224(r31)
    /* 0x800AA2AC */ ctx.f[13] = mem.read_f32(ctx.r[8] + (-14692)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -14692(r8) [0x8016C69C]
    /* 0x800AA2B0 */ ctx.f[0] = static_cast<float>(ctx.f[0] - ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fsubs f0, f0, f11
    /* 0x800AA2B4 */ ctx.f[12] = mem.read_f32(ctx.r[7] + (-14688)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -14688(r7) [0x8016C6A0]
    /* 0x800AA2B8 */ ctx.f[0] = static_cast<float>(ctx.f[0] - ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fsubs f0, f0, f13
    /* 0x800AA2BC */ mem.write_f32(ctx.r[30] + (12), static_cast<float>(ctx.f[11])); // stfs f11, 12(r30)
    /* 0x800AA2C0 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800AA2C4 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r30)
    /* 0x800AA2C8 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (192)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 192(r31)
    /* 0x800AA2CC */ mem.write_f32(ctx.r[30] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r30)
    /* 0x800AA2D0 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (200)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 200(r31)
    /* 0x800AA2D4 */ mem.write_f32(ctx.r[30] + (20), static_cast<float>(ctx.f[13])); // stfs f13, 20(r30)
    /* 0x800AA2D8 */ if (ctx.eval_bc(12, 2)) goto loc_800AA2E8; // bc 12, 2, 0x800AA2E8
    /* 0x800AA2DC */ ctx.f[0] = mem.read_f32(ctx.r[31] + (1232)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 1232(r31)
    /* 0x800AA2E0 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f11
    /* 0x800AA2E4 */ mem.write_f32(ctx.r[31] + (196), static_cast<float>(ctx.f[0])); // stfs f0, 196(r31)
loc_800AA2E8:;
    /* 0x800AA2E8 */ mem.write_u32(ctx.r[31] + (1216), ctx.r[28]); // stw r28, 1216(r31)
    /* 0x800AA2EC */ mem.write_u32(ctx.r[31] + (1212), ctx.r[27]); // stw r27, 1212(r31)
    /* 0x800AA2F0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (92)); // lwz r0, 92(r1)
    /* 0x800AA2F4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AA2F8 */ ctx.lmw(mem, 27, ctx.r[1] + (68)); // lmw r27, 68(r1)
    /* 0x800AA2FC */ ctx.r[1] = ctx.r[1] + (88); // addi r1, r1, 88
    /* 0x800AA300 */ return; // blr
}

// [0x800AA304] SetObj10(unsigned long, unsigned long, void *, cVec &, cVec &, long, long) (obj10.obj, 127 insns / 0x1FC bytes)
void SetObj10_800AA304(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA304 */ ctx.r[1] += (-64); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -64(r1)
    /* 0x800AA308 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AA30C */ ctx.stmw(mem, 24, ctx.r[1] + (32)); // stmw r24, 32(r1)
    /* 0x800AA310 */ mem.write_u32(ctx.r[1] + (68), ctx.r[0]); // stw r0, 68(r1)
    /* 0x800AA314 */ ctx.r[29] = ctx.r[3]; // mr r29, r3
    /* 0x800AA318 */ ctx.r[28] = ctx.r[4]; // mr r28, r4
    /* 0x800AA31C */ ctx.r[30] = ctx.r[5]; // mr r30, r5
    /* 0x800AA320 */ ctx.r[27] = ctx.r[6]; // mr r27, r6
    /* 0x800AA324 */ ctx.r[26] = ctx.r[7]; // mr r26, r7
    /* 0x800AA328 */ ctx.r[24] = ctx.r[8]; // mr r24, r8
    /* 0x800AA32C */ ctx.r[25] = ctx.r[9]; // mr r25, r9
    /* 0x800AA330 */ ctx.r[3] = 0x00000010u; // li r3, 16
    /* 0x800AA334 */ PullObj_80074784(ctx, mem); // bl 0x80074784 <PullObj(long)>
    /* 0x800AA338 */ ctx.r[31] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // mr r31, r3
    /* 0x800AA33C */ if (ctx.eval_bc(4, 2)) goto loc_800AA348; // bc 4, 2, 0x800AA348
    /* 0x800AA340 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800AA344 */ goto loc_800AA4EC; // b 0x800AA4EC <sub_800AA4EC>
loc_800AA348:;
    /* 0x800AA348 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800AA34C */ ctx.r[5] = ctx.r[28]; // mr r5, r28
    /* 0x800AA350 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA354 */ cObj__ModelInit_80074D30(ctx, mem); // bl 0x80074D30 <cObj::ModelInit(unsigned long, unsigned long)>
    /* 0x800AA358 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[30]), 0); // cmpwi cr0, r30, 0
    /* 0x800AA35C */ if (ctx.eval_bc(12, 2)) goto loc_800AA388; // bc 12, 2, 0x800AA388
    /* 0x800AA360 */ ctx.r[5] = ctx.r[30]; // mr r5, r30
    /* 0x800AA364 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA368 */ ctx.r[4] = ctx.r[31] + (380); // addi r4, r31, 380
    /* 0x800AA36C */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800AA370 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800AA374 */ ctx.r[8] = 0x00000004u; // li r8, 4
    /* 0x800AA378 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800AA37C */ MotionSetCore_800A1E20(ctx, mem); // bl 0x800A1E20 <MotionSetCore(cEm *, _MOTION_INFO *, void *, void *, unsigned char, unsigned short, unsigned short)>
    /* 0x800AA380 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800AA384 */ mem.write_u32(ctx.r[31] + (1220), ctx.r[0]); // stw r0, 1220(r31)
loc_800AA388:;
    /* 0x800AA388 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (244)); // lwz r0, 244(r31)
    /* 0x800AA38C */ ctx.r[4] = 0x80170000u; // lis r4, 0x8017
    /* 0x800AA390 */ ctx.r[4] = ctx.r[4] + (10500); // addi r4, r4, 10500 -> Obj_at_light
    /* 0x800AA394 */ ctx.r[5] = 0x00000004u; // li r5, 4
    /* 0x800AA398 */ ctx.rlwinm(0, 0, 0u, 30u, 27u, false); // rlwinm r0, r0, 0, 30, 27
    /* 0x800AA39C */ ctx.r[3] = ctx.r[31] + (312); // addi r3, r31, 312
    /* 0x800AA3A0 */ mem.write_u32(ctx.r[31] + (244), ctx.r[0]); // stw r0, 244(r31)
    /* 0x800AA3A4 */ ctx.r[28] = ctx.r[31] + (192); // addi r28, r31, 192
    /* 0x800AA3A8 */ LightInfoInit_8009AF88(ctx, mem); // bl 0x8009AF88 <LightInfoInit(tagLIGHT_INFO *, tagATARI_INFO *, unsigned char)>
    /* 0x800AA3AC */ ctx.r[29] = ctx.r[31] + (204); // addi r29, r31, 204
    /* 0x800AA3B0 */ ctx.r[0] = mem.read_u32(ctx.r[27] + (0)); // lwz r0, 0(r27)
    /* 0x800AA3B4 */ ctx.r[10] = ctx.r[31] + (268); // addi r10, r31, 268
    /* 0x800AA3B8 */ ctx.r[9] = mem.read_u32(ctx.r[27] + (4)); // lwz r9, 4(r27)
    /* 0x800AA3BC */ ctx.r[30] = ctx.r[1] + (16); // addi r30, r1, 16
    /* 0x800AA3C0 */ ctx.r[11] = mem.read_u32(ctx.r[27] + (8)); // lwz r11, 8(r27)
    /* 0x800AA3C4 */ ctx.r[6] = ctx.r[25]; // mr r6, r25
    /* 0x800AA3C8 */ mem.write_u32(ctx.r[31] + (192), ctx.r[0]); // stw r0, 192(r31)
    /* 0x800AA3CC */ ctx.r[5] = ctx.r[24]; // mr r5, r24
    /* 0x800AA3D0 */ mem.write_u32(ctx.r[28] + (4), ctx.r[9]); // stw r9, 4(r28)
    /* 0x800AA3D4 */ ctx.r[4] = ctx.r[27]; // mr r4, r27
    /* 0x800AA3D8 */ mem.write_u32(ctx.r[28] + (8), ctx.r[11]); // stw r11, 8(r28)
    /* 0x800AA3DC */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA3E0 */ ctx.r[9] = mem.read_u32(ctx.r[27] + (0)); // lwz r9, 0(r27)
    /* 0x800AA3E4 */ ctx.r[11] = mem.read_u32(ctx.r[27] + (4)); // lwz r11, 4(r27)
    /* 0x800AA3E8 */ ctx.r[0] = mem.read_u32(ctx.r[27] + (8)); // lwz r0, 8(r27)
    /* 0x800AA3EC */ mem.write_u32(ctx.r[31] + (268), ctx.r[9]); // stw r9, 268(r31)
    /* 0x800AA3F0 */ mem.write_u32(ctx.r[10] + (8), ctx.r[0]); // stw r0, 8(r10)
    /* 0x800AA3F4 */ mem.write_u32(ctx.r[10] + (4), ctx.r[11]); // stw r11, 4(r10)
    /* 0x800AA3F8 */ ctx.r[9] = mem.read_u32(ctx.r[26] + (0)); // lwz r9, 0(r26)
    /* 0x800AA3FC */ ctx.r[11] = mem.read_u32(ctx.r[26] + (8)); // lwz r11, 8(r26)
    /* 0x800AA400 */ ctx.r[0] = mem.read_u32(ctx.r[26] + (4)); // lwz r0, 4(r26)
    /* 0x800AA404 */ mem.write_u32(ctx.r[31] + (204), ctx.r[9]); // stw r9, 204(r31)
    /* 0x800AA408 */ mem.write_u32(ctx.r[29] + (4), ctx.r[0]); // stw r0, 4(r29)
    /* 0x800AA40C */ mem.write_u32(ctx.r[29] + (8), ctx.r[11]); // stw r11, 8(r29)
    /* 0x800AA410 */ cObj10__set_item_area_800AA1E4(ctx, mem); // bl 0x800AA1E4 <cObj10::set_item_area(cVec &, long, long)>
    /* 0x800AA414 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (204)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 204(r31)
    /* 0x800AA418 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800AA41C */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA420 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800AA424 */ ctx.f[0] = mem.read_f32(ctx.r[29] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r29)
    /* 0x800AA428 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800AA42C */ ctx.f[13] = mem.read_f32(ctx.r[29] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r29)
    /* 0x800AA430 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800AA434 */ RotMatrix_8009E1D0(ctx, mem); // bl 0x8009E1D0 <RotMatrix(float (*)[3], cVec &)>
    /* 0x800AA438 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r31)
    /* 0x800AA43C */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800AA440 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA444 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800AA448 */ ctx.f[0] = mem.read_f32(ctx.r[28] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r28)
    /* 0x800AA44C */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800AA450 */ ctx.f[13] = mem.read_f32(ctx.r[28] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r28)
    /* 0x800AA454 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800AA458 */ TransMatrix_8009E1B4(ctx, mem); // bl 0x8009E1B4 <TransMatrix(float (*)[3], cVec &)>
    /* 0x800AA45C */ ctx.f[13] = mem.read_f32(ctx.r[31] + (216)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 216(r31)
    /* 0x800AA460 */ ctx.r[9] = ctx.r[31] + (216); // addi r9, r31, 216
    /* 0x800AA464 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800AA468 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA46C */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800AA470 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800AA474 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800AA478 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800AA47C */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800AA480 */ ScaleMatrix_8009E168(ctx, mem); // bl 0x8009E168 <ScaleMatrix(float (*)[3], cVec &)>
    /* 0x800AA484 */ ctx.r[3] = mem.read_u32(ctx.r[31] + (240)); // lwz r3, 240(r31)
    /* 0x800AA488 */ ModelMatCalc_800A0BF4(ctx, mem); // bl 0x800A0BF4 <ModelMatCalc(PARTS *)>
    /* 0x800AA48C */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA490 */ PartsWorldCalc_800A0E5C(ctx, mem); // bl 0x800A0E5C <PartsWorldCalc(cEm *)>
    /* 0x800AA494 */ ctx.r[9] = ctx.r[13] + (-32424); // addi r9, r13, -32424 -> est_tbl.1041
    /* 0x800AA498 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800AA49C */ ctx.r[4] = mem.read_u8(ctx.r[24] + ctx.r[9]); // lbzx r4, r24, r9
    /* 0x800AA4A0 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800AA4A4 */ ctx.r[29] = ctx.r[3]; // mr r29, r3
    /* 0x800AA4A8 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800AA4AC */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800AA4B0 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AA4B4 */ EspPullCoreKind_80084BA0(ctx, mem); // bl 0x80084BA0 <EspPullCoreKind(void)>
    /* 0x800AA4B8 */ mem.write_u8(ctx.r[31] + (1284), static_cast<uint8_t>(ctx.r[3])); // stb r3, 1284(r31)
    /* 0x800AA4BC */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800AA4C0 */ ctx.rlwinm(9, 3, 0u, 24u, 31u, false); // rlwinm r9, r3, 0, 24, 31
    /* 0x800AA4C4 */ ctx.r[6] = ctx.r[29]; // mr r6, r29
    /* 0x800AA4C8 */ mem.write_u32(ctx.r[1] + (8), ctx.r[0]); // stw r0, 8(r1)
    /* 0x800AA4CC */ ctx.r[7] = ctx.r[30]; // mr r7, r30
    /* 0x800AA4D0 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA4D4 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800AA4D8 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800AA4DC */ ctx.r[8] = 0x00000004u; // li r8, 4
    /* 0x800AA4E0 */ ctx.r[10] = ctx.r[31]; // mr r10, r31
    /* 0x800AA4E4 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800AA4E8 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
loc_800AA4EC:;
    /* 0x800AA4EC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (68)); // lwz r0, 68(r1)
    /* 0x800AA4F0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AA4F4 */ ctx.lmw(mem, 24, ctx.r[1] + (32)); // lmw r24, 32(r1)
    /* 0x800AA4F8 */ ctx.r[1] = ctx.r[1] + (64); // addi r1, r1, 64
    /* 0x800AA4FC */ return; // blr
}

// [0x800AA500] cObj10::~cObj10(void) (obj10.obj, 8 insns / 0x20 bytes)
void cObj10_dtor_cObj10_800AA500(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA500 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800AA504 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AA508 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800AA50C */ cObj_dtor_cObj_80074AD8(ctx, mem); // bl 0x80074AD8 <cObj::~cObj(void)>
    /* 0x800AA510 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800AA514 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AA518 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800AA51C */ return; // blr
}

// [0x800AA520] cObj10::mot_play(void) (obj10.obj, 3 insns / 0xC bytes)
void cObj10__mot_play_800AA520(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA520 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800AA524 */ mem.write_u32(ctx.r[3] + (1220), ctx.r[0]); // stw r0, 1220(r3)
    /* 0x800AA528 */ return; // blr
}

// [0x800AA52C] cObj10::eff_get_id(void) (obj10.obj, 13 insns / 0x34 bytes)
void cObj10__eff_get_id_800AA52C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA52C */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800AA530 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AA534 */ ctx.stmw(mem, 30, ctx.r[1] + (8)); // stmw r30, 8(r1)
    /* 0x800AA538 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800AA53C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AA540 */ EspPullCoreKind_80084BA0(ctx, mem); // bl 0x80084BA0 <EspPullCoreKind(void)>
    /* 0x800AA544 */ mem.write_u8(ctx.r[30] + (1284), static_cast<uint8_t>(ctx.r[3])); // stb r3, 1284(r30)
    /* 0x800AA548 */ ctx.rlwinm(3, 3, 0u, 24u, 31u, false); // rlwinm r3, r3, 0, 24, 31
    /* 0x800AA54C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800AA550 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AA554 */ ctx.lmw(mem, 30, ctx.r[1] + (8)); // lmw r30, 8(r1)
    /* 0x800AA558 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800AA55C */ return; // blr
}

// [0x800AA560] SetPack(cEm *, unsigned long, unsigned long, PARTS *, Vec *) (obj11.obj, 35 insns / 0x8C bytes)
void SetPack_800AA560(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA560 */ ctx.r[1] += (-32); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -32(r1)
    /* 0x800AA564 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AA568 */ ctx.stmw(mem, 26, ctx.r[1] + (8)); // stmw r26, 8(r1)
    /* 0x800AA56C */ mem.write_u32(ctx.r[1] + (36), ctx.r[0]); // stw r0, 36(r1)
    /* 0x800AA570 */ ctx.r[26] = ctx.r[3]; // mr r26, r3
    /* 0x800AA574 */ ctx.r[30] = ctx.r[4]; // mr r30, r4
    /* 0x800AA578 */ ctx.r[28] = ctx.r[5]; // mr r28, r5
    /* 0x800AA57C */ ctx.r[27] = ctx.r[6]; // mr r27, r6
    /* 0x800AA580 */ ctx.r[29] = ctx.r[7]; // mr r29, r7
    /* 0x800AA584 */ ctx.r[3] = 0x00000011u; // li r3, 17
    /* 0x800AA588 */ PullObj_80074784(ctx, mem); // bl 0x80074784 <PullObj(long)>
    /* 0x800AA58C */ ctx.r[31] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // mr r31, r3
    /* 0x800AA590 */ if (ctx.eval_bc(12, 2)) goto loc_800AA5D4; // bc 12, 2, 0x800AA5D4
    /* 0x800AA594 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800AA598 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA59C */ ctx.r[5] = ctx.r[28]; // mr r5, r28
    /* 0x800AA5A0 */ ctx.r[30] = ctx.r[31] + (1212); // addi r30, r31, 1212
    /* 0x800AA5A4 */ cObj__ModelInit_80074D30(ctx, mem); // bl 0x80074D30 <cObj::ModelInit(unsigned long, unsigned long)>
    /* 0x800AA5A8 */ mem.write_u32(ctx.r[30] + (12), ctx.r[27]); // stw r27, 12(r30)
    /* 0x800AA5AC */ ctx.r[10] = ctx.r[31] + (1228); // addi r10, r31, 1228
    /* 0x800AA5B0 */ mem.write_u32(ctx.r[30] + (8), ctx.r[26]); // stw r26, 8(r30)
    /* 0x800AA5B4 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA5B8 */ ctx.r[0] = mem.read_u32(ctx.r[29] + (0)); // lwz r0, 0(r29)
    /* 0x800AA5BC */ ctx.r[9] = mem.read_u32(ctx.r[29] + (8)); // lwz r9, 8(r29)
    /* 0x800AA5C0 */ ctx.r[11] = mem.read_u32(ctx.r[29] + (4)); // lwz r11, 4(r29)
    /* 0x800AA5C4 */ mem.write_u32(ctx.r[31] + (1228), ctx.r[0]); // stw r0, 1228(r31)
    /* 0x800AA5C8 */ mem.write_u32(ctx.r[10] + (8), ctx.r[9]); // stw r9, 8(r10)
    /* 0x800AA5CC */ mem.write_u32(ctx.r[10] + (4), ctx.r[11]); // stw r11, 4(r10)
    /* 0x800AA5D0 */ goto loc_800AA5D8; // b 0x800AA5D8 <sub_800AA5D8>
loc_800AA5D4:;
    /* 0x800AA5D4 */ ctx.r[3] = 0x00000000u; // li r3, 0
loc_800AA5D8:;
    /* 0x800AA5D8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (36)); // lwz r0, 36(r1)
    /* 0x800AA5DC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AA5E0 */ ctx.lmw(mem, 26, ctx.r[1] + (8)); // lmw r26, 8(r1)
    /* 0x800AA5E4 */ ctx.r[1] = ctx.r[1] + (32); // addi r1, r1, 32
    /* 0x800AA5E8 */ return; // blr
}

// [0x800AA5EC] cObj11::Main(void) (obj11.obj, 81 insns / 0x144 bytes)
void cObj11__Main_800AA5EC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA5EC */ ctx.r[1] += (-32); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -32(r1)
    /* 0x800AA5F0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AA5F4 */ ctx.stmw(mem, 30, ctx.r[1] + (24)); // stmw r30, 24(r1)
    /* 0x800AA5F8 */ mem.write_u32(ctx.r[1] + (36), ctx.r[0]); // stw r0, 36(r1)
    /* 0x800AA5FC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AA600 */ ctx.r[31] = ctx.r[3]; // mr r31, r3
    /* 0x800AA604 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (336)); // lwz r0, 336(r9)
    /* 0x800AA608 */ ctx.r[9] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x2000
    /* 0x800AA60C */ if (ctx.eval_bc(4, 2)) goto loc_800AA71C; // bc 4, 2, 0x800AA71C
    /* 0x800AA610 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (248)); // lbz r0, 248(r31)
    /* 0x800AA614 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800AA618 */ if (ctx.eval_bc(12, 2)) goto loc_800AA628; // bc 12, 2, 0x800AA628
    /* 0x800AA61C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 1); // cmpwi cr0, r0, 1
    /* 0x800AA620 */ if (ctx.eval_bc(12, 2)) goto loc_800AA634; // bc 12, 2, 0x800AA634
    /* 0x800AA624 */ goto loc_800AA63C; // b 0x800AA63C <sub_800AA63C>
loc_800AA628:;
    /* 0x800AA628 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA62C */ cObj11__obj11_init_800AA730(ctx, mem); // bl 0x800AA730 <cObj11::obj11_init(void)>
    /* 0x800AA630 */ goto loc_800AA63C; // b 0x800AA63C <sub_800AA63C>
loc_800AA634:;
    /* 0x800AA634 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA638 */ cObj11__obj11_move_800AA79C(ctx, mem); // bl 0x800AA79C <cObj11::obj11_move(void)>
loc_800AA63C:;
    /* 0x800AA63C */ ctx.f[0] = mem.read_f32(ctx.r[31] + (204)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 204(r31)
    /* 0x800AA640 */ ctx.r[9] = ctx.r[31] + (204); // addi r9, r31, 204
    /* 0x800AA644 */ ctx.r[30] = ctx.r[1] + (8); // addi r30, r1, 8
    /* 0x800AA648 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA64C */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800AA650 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800AA654 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800AA658 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800AA65C */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800AA660 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800AA664 */ RotMatrix_8009E1D0(ctx, mem); // bl 0x8009E1D0 <RotMatrix(float (*)[3], cVec &)>
    /* 0x800AA668 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r31)
    /* 0x800AA66C */ ctx.r[9] = ctx.r[31] + (192); // addi r9, r31, 192
    /* 0x800AA670 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800AA674 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA678 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800AA67C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800AA680 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800AA684 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800AA688 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800AA68C */ TransMatrix_8009E1B4(ctx, mem); // bl 0x8009E1B4 <TransMatrix(float (*)[3], cVec &)>
    /* 0x800AA690 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (216)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 216(r31)
    /* 0x800AA694 */ ctx.r[9] = ctx.r[31] + (216); // addi r9, r31, 216
    /* 0x800AA698 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800AA69C */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA6A0 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800AA6A4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800AA6A8 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800AA6AC */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800AA6B0 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r30)
    /* 0x800AA6B4 */ ScaleMatrix_8009E168(ctx, mem); // bl 0x8009E168 <ScaleMatrix(float (*)[3], cVec &)>
    /* 0x800AA6B8 */ ctx.r[3] = mem.read_u32(ctx.r[31] + (240)); // lwz r3, 240(r31)
    /* 0x800AA6BC */ ModelMatCalc_800A0BF4(ctx, mem); // bl 0x800A0BF4 <ModelMatCalc(PARTS *)>
    /* 0x800AA6C0 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA6C4 */ PartsWorldCalc_800A0E5C(ctx, mem); // bl 0x800A0E5C <PartsWorldCalc(cEm *)>
    /* 0x800AA6C8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AA6CC */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800AA6D0 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800AA6D4 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800AA6D8 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800AA6DC */ ctx.rlwinm(9, 0, 30u, 2u, 31u, true); // rlwinm r9, r0, 30, 2, 31
    /* 0x800AA6E0 */ if (ctx.eval_bc(4, 2)) goto loc_800AA6F0; // bc 4, 2, 0x800AA6F0
    /* 0x800AA6E4 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800AA6E8 */ ctx.r[3] = ctx.r[3] + (-14572); // addi r3, r3, -14572 -> 0x8016C714 /* "vector" */
    /* 0x800AA6EC */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800AA6F0:;
    /* 0x800AA6F0 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800AA6F4 */ ctx.r[3] = mem.read_u32(ctx.r[31] + (304)); // lwz r3, 304(r31)
    /* 0x800AA6F8 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800AA6FC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800AA700 */ if (ctx.eval_bc(12, 2)) goto loc_800AA71C; // bc 12, 2, 0x800AA71C
loc_800AA704:;
    /* 0x800AA704 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (304)); // lwz r9, 304(r11)
    /* 0x800AA708 */ ctx.r[0] = mem.read_u8(ctx.r[9] + (95)); // lbz r0, 95(r9)
    /* 0x800AA70C */ mem.write_u8(ctx.r[3] + (95), static_cast<uint8_t>(ctx.r[0])); // stb r0, 95(r3)
    /* 0x800AA710 */ ctx.r[3] = mem.read_u32(ctx.r[3] + (4)); // lwz r3, 4(r3)
    /* 0x800AA714 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800AA718 */ if (ctx.eval_bc(4, 2)) goto loc_800AA704; // bc 4, 2, 0x800AA704
loc_800AA71C:;
    /* 0x800AA71C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (36)); // lwz r0, 36(r1)
    /* 0x800AA720 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AA724 */ ctx.lmw(mem, 30, ctx.r[1] + (24)); // lmw r30, 24(r1)
    /* 0x800AA728 */ ctx.r[1] = ctx.r[1] + (32); // addi r1, r1, 32
    /* 0x800AA72C */ return; // blr
}

// [0x800AA730] cObj11::obj11_init(void) (obj11.obj, 27 insns / 0x6C bytes)
void cObj11__obj11_init_800AA730(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA730 */ ctx.r[1] += (-24); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -24(r1)
    /* 0x800AA734 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AA738 */ ctx.stmw(mem, 29, ctx.r[1] + (12)); // stmw r29, 12(r1)
    /* 0x800AA73C */ mem.write_u32(ctx.r[1] + (28), ctx.r[0]); // stw r0, 28(r1)
    /* 0x800AA740 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AA744 */ ctx.r[4] = 0x80170000u; // lis r4, 0x8017
    /* 0x800AA748 */ ctx.r[4] = ctx.r[4] + (24900); // addi r4, r4, 24900 -> at_light
    /* 0x800AA74C */ ctx.r[3] = ctx.r[30] + (312); // addi r3, r30, 312
    /* 0x800AA750 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800AA754 */ ctx.r[29] = ctx.r[30] + (1212); // addi r29, r30, 1212
    /* 0x800AA758 */ LightInfoInit_8009AF88(ctx, mem); // bl 0x8009AF88 <LightInfoInit(tagLIGHT_INFO *, tagATARI_INFO *, unsigned char)>
    /* 0x800AA75C */ ctx.r[11] = mem.read_u32(ctx.r[29] + (12)); // lwz r11, 12(r29)
    /* 0x800AA760 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800AA764 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (240)); // lwz r9, 240(r30)
    /* 0x800AA768 */ ctx.r[8] = 0x00000001u; // li r8, 1
    /* 0x800AA76C */ ctx.r[10] = 0x00000005u; // li r10, 5
    /* 0x800AA770 */ mem.write_u32(ctx.r[9] + (276), ctx.r[11]); // stw r11, 276(r9)
    /* 0x800AA774 */ mem.write_u16(ctx.r[30] + (1212), static_cast<uint16_t>(ctx.r[0])); // sth r0, 1212(r30)
    /* 0x800AA778 */ mem.write_u16(ctx.r[29] + (4), static_cast<uint16_t>(ctx.r[0])); // sth r0, 4(r29)
    /* 0x800AA77C */ mem.write_u16(ctx.r[29] + (2), static_cast<uint16_t>(ctx.r[0])); // sth r0, 2(r29)
    /* 0x800AA780 */ mem.write_u8(ctx.r[30] + (250), static_cast<uint8_t>(ctx.r[10])); // stb r10, 250(r30)
    /* 0x800AA784 */ mem.write_u8(ctx.r[30] + (248), static_cast<uint8_t>(ctx.r[8])); // stb r8, 248(r30)
    /* 0x800AA788 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (28)); // lwz r0, 28(r1)
    /* 0x800AA78C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AA790 */ ctx.lmw(mem, 29, ctx.r[1] + (12)); // lmw r29, 12(r1)
    /* 0x800AA794 */ ctx.r[1] = ctx.r[1] + (24); // addi r1, r1, 24
    /* 0x800AA798 */ return; // blr
}

// [0x800AA79C] cObj11::obj11_move(void) (obj11.obj, 79 insns / 0x13C bytes)
void cObj11__obj11_move_800AA79C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA79C */ ctx.r[1] += (-32); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -32(r1)
    /* 0x800AA7A0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AA7A4 */ ctx.stmw(mem, 29, ctx.r[1] + (20)); // stmw r29, 20(r1)
    /* 0x800AA7A8 */ mem.write_u32(ctx.r[1] + (36), ctx.r[0]); // stw r0, 36(r1)
    /* 0x800AA7AC */ ctx.r[31] = ctx.r[3]; // mr r31, r3
    /* 0x800AA7B0 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (249)); // lbz r0, 249(r31)
    /* 0x800AA7B4 */ ctx.r[30] = ctx.r[31] + (1212); // addi r30, r31, 1212
    /* 0x800AA7B8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800AA7BC */ if (ctx.eval_bc(12, 2)) goto loc_800AA7CC; // bc 12, 2, 0x800AA7CC
    /* 0x800AA7C0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 1); // cmpwi cr0, r0, 1
    /* 0x800AA7C4 */ if (ctx.eval_bc(12, 2)) goto loc_800AA7D8; // bc 12, 2, 0x800AA7D8
    /* 0x800AA7C8 */ goto loc_800AA7E0; // b 0x800AA7E0 <sub_800AA7E0>
loc_800AA7CC:;
    /* 0x800AA7CC */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA7D0 */ cObj11__obj11_mv00_800AA8D8(ctx, mem); // bl 0x800AA8D8 <cObj11::obj11_mv00(void)>
    /* 0x800AA7D4 */ goto loc_800AA7E0; // b 0x800AA7E0 <sub_800AA7E0>
loc_800AA7D8:;
    /* 0x800AA7D8 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA7DC */ cObj11__obj11_mv01_800AA8E4(ctx, mem); // bl 0x800AA8E4 <cObj11::obj11_mv01(void)>
loc_800AA7E0:;
    /* 0x800AA7E0 */ ctx.r[0] = mem.read_u16(ctx.r[30] + (0)); // lhz r0, 0(r30)
    /* 0x800AA7E4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800AA7E8 */ if (ctx.eval_bc(12, 2)) goto loc_800AA8C4; // bc 12, 2, 0x800AA8C4
    /* 0x800AA7EC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AA7F0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (304)); // lwz r0, 304(r9)
    /* 0x800AA7F4 */ ctx.r[29] = ctx.r[0] & 0x8000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[29]), 0); // andi. r29, r0, 0x8000
    /* 0x800AA7F8 */ if (ctx.eval_bc(12, 2)) goto loc_800AA864; // bc 12, 2, 0x800AA864
    /* 0x800AA7FC */ ctx.r[29] = mem.read_u16(ctx.r[30] + (6)); // lhz r29, 6(r30)
    /* 0x800AA800 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[29]), 0); // cmpwi cr0, r29, 0
    /* 0x800AA804 */ if (ctx.eval_bc(4, 2)) goto loc_800AA8C4; // bc 4, 2, 0x800AA8C4
    /* 0x800AA808 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800AA80C */ ctx.r[5] = ctx.r[31]; // mr r5, r31
    /* 0x800AA810 */ mem.write_u16(ctx.r[30] + (6), static_cast<uint16_t>(ctx.r[0])); // sth r0, 6(r30)
    /* 0x800AA814 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800AA818 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800AA81C */ EspgenDelete_8008E8B8(ctx, mem); // bl 0x8008E8B8 <EspgenDelete(unsigned short, unsigned char, void *)>
    /* 0x800AA820 */ ctx.r[4] = 0x0000000Fu; // li r4, 15
    /* 0x800AA824 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AA828 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800AA82C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AA830 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AA834 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800AA838 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800AA83C */ mem.write_u32(ctx.r[1] + (8), ctx.r[29]); // stw r29, 8(r1)
    /* 0x800AA840 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA844 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800AA848 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800AA84C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800AA850 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800AA854 */ ctx.r[9] = 0x00000003u; // li r9, 3
    /* 0x800AA858 */ ctx.r[10] = ctx.r[3]; // mr r10, r3
    /* 0x800AA85C */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800AA860 */ goto loc_800AA8C4; // b 0x800AA8C4 <sub_800AA8C4>
loc_800AA864:;
    /* 0x800AA864 */ ctx.r[0] = mem.read_u16(ctx.r[30] + (6)); // lhz r0, 6(r30)
    /* 0x800AA868 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800AA86C */ if (ctx.eval_bc(12, 2)) goto loc_800AA8C4; // bc 12, 2, 0x800AA8C4
    /* 0x800AA870 */ mem.write_u16(ctx.r[30] + (6), static_cast<uint16_t>(ctx.r[29])); // sth r29, 6(r30)
    /* 0x800AA874 */ ctx.r[5] = ctx.r[31]; // mr r5, r31
    /* 0x800AA878 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800AA87C */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800AA880 */ EspgenDelete_8008E8B8(ctx, mem); // bl 0x8008E8B8 <EspgenDelete(unsigned short, unsigned char, void *)>
    /* 0x800AA884 */ ctx.r[4] = 0x00000004u; // li r4, 4
    /* 0x800AA888 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AA88C */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800AA890 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AA894 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AA898 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800AA89C */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800AA8A0 */ mem.write_u32(ctx.r[1] + (8), ctx.r[29]); // stw r29, 8(r1)
    /* 0x800AA8A4 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA8A8 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800AA8AC */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800AA8B0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800AA8B4 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800AA8B8 */ ctx.r[9] = 0x00000003u; // li r9, 3
    /* 0x800AA8BC */ ctx.r[10] = ctx.r[3]; // mr r10, r3
    /* 0x800AA8C0 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800AA8C4:;
    /* 0x800AA8C4 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (36)); // lwz r0, 36(r1)
    /* 0x800AA8C8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AA8CC */ ctx.lmw(mem, 29, ctx.r[1] + (20)); // lmw r29, 20(r1)
    /* 0x800AA8D0 */ ctx.r[1] = ctx.r[1] + (32); // addi r1, r1, 32
    /* 0x800AA8D4 */ return; // blr
}

// [0x800AA8D8] cObj11::obj11_mv00(void) (obj11.obj, 3 insns / 0xC bytes)
void cObj11__obj11_mv00_800AA8D8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA8D8 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800AA8DC */ mem.write_u8(ctx.r[3] + (249), static_cast<uint8_t>(ctx.r[0])); // stb r0, 249(r3)
    /* 0x800AA8E0 */ return; // blr
}

// [0x800AA8E4] cObj11::obj11_mv01(void) (obj11.obj, 267 insns / 0x42C bytes)
void cObj11__obj11_mv01_800AA8E4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AA8E4 */ ctx.r[1] += (-40); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -40(r1)
    /* 0x800AA8E8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AA8EC */ ctx.stmw(mem, 27, ctx.r[1] + (20)); // stmw r27, 20(r1)
    /* 0x800AA8F0 */ mem.write_u32(ctx.r[1] + (44), ctx.r[0]); // stw r0, 44(r1)
    /* 0x800AA8F4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AA8F8 */ ctx.r[31] = ctx.r[3]; // mr r31, r3
    /* 0x800AA8FC */ ctx.r[28] = ctx.r[31] + (1212); // addi r28, r31, 1212
    /* 0x800AA900 */ ctx.r[29] = 0x00000000u; // li r29, 0
    /* 0x800AA904 */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800AA908 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800AA90C */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800AA910 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800AA914 */ ctx.rlwinm(9, 0, 30u, 2u, 31u, true); // rlwinm r9, r0, 30, 2, 31
    /* 0x800AA918 */ if (ctx.eval_bc(4, 2)) goto loc_800AA928; // bc 4, 2, 0x800AA928
    /* 0x800AA91C */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800AA920 */ ctx.r[3] = ctx.r[3] + (-14572); // addi r3, r3, -14572 -> 0x8016C714 /* "vector" */
    /* 0x800AA924 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800AA928:;
    /* 0x800AA928 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800AA92C */ ctx.r[0] = mem.read_u8(ctx.r[31] + (250)); // lbz r0, 250(r31)
    /* 0x800AA930 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800AA934 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 2); // cmpwi cr0, r0, 2
    /* 0x800AA938 */ ctx.r[27] = ctx.r[11] + (1388); // addi r27, r11, 1388
    /* 0x800AA93C */ if (ctx.eval_bc(12, 2)) goto loc_800AAB0C; // bc 12, 2, 0x800AAB0C
    /* 0x800AA940 */ if (ctx.eval_bc(12, 1)) goto loc_800AA958; // bc 12, 1, 0x800AA958
    /* 0x800AA944 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800AA948 */ if (ctx.eval_bc(12, 2)) goto loc_800AA970; // bc 12, 2, 0x800AA970
    /* 0x800AA94C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 1); // cmpwi cr0, r0, 1
    /* 0x800AA950 */ if (ctx.eval_bc(12, 2)) goto loc_800AA9F8; // bc 12, 2, 0x800AA9F8
    /* 0x800AA954 */ goto loc_800AACFC; // b 0x800AACFC <sub_800AACFC>
loc_800AA958:;
    /* 0x800AA958 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 4); // cmpwi cr0, r0, 4
    /* 0x800AA95C */ if (ctx.eval_bc(12, 2)) goto loc_800AABE8; // bc 12, 2, 0x800AABE8
    /* 0x800AA960 */ if (ctx.eval_bc(12, 0)) goto loc_800AAB94; // bc 12, 0, 0x800AAB94
    /* 0x800AA964 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 5); // cmpwi cr0, r0, 5
    /* 0x800AA968 */ if (ctx.eval_bc(12, 2)) goto loc_800AACF4; // bc 12, 2, 0x800AACF4
    /* 0x800AA96C */ goto loc_800AACFC; // b 0x800AACFC <sub_800AACFC>
loc_800AA970:;
    /* 0x800AA970 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AA974 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800AA978 */ ctx.r[9] = ctx.r[0] & 0x0400u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0400
    /* 0x800AA97C */ if (ctx.eval_bc(12, 2)) goto loc_800AACFC; // bc 12, 2, 0x800AACFC
    /* 0x800AA980 */ ctx.r[30] = 0x00000001u; // li r30, 1
    /* 0x800AA984 */ ctx.r[5] = ctx.r[31] + (192); // addi r5, r31, 192
    /* 0x800AA988 */ mem.write_u16(ctx.r[28] + (4), static_cast<uint16_t>(ctx.r[30])); // sth r30, 4(r28)
    /* 0x800AA98C */ ctx.r[4] = 0x0000000Bu; // li r4, 11
    /* 0x800AA990 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800AA994 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800AA998 */ SndSeCall_800CB7DC(ctx, mem); // bl 0x800CB7DC <SndSeCall(unsigned short, unsigned short, Vec *, unsigned char)>
    /* 0x800AA99C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AA9A0 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AA9A4 */ ctx.r[4] = ctx.r[31] + (380); // addi r4, r31, 380
    /* 0x800AA9A8 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800AA9AC */ ctx.r[11] = mem.read_u32(ctx.r[9] + (280)); // lwz r11, 280(r9)
    /* 0x800AA9B0 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800AA9B4 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800AA9B8 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800AA9BC */ ctx.r[5] = mem.read_u32(ctx.r[11] + (376)); // lwz r5, 376(r11)
    /* 0x800AA9C0 */ ctx.r[5] = ctx.r[5] + ctx.r[11]; // add r5, r5, r11
    /* 0x800AA9C4 */ MotionSetCore_800A1E20(ctx, mem); // bl 0x800A1E20 <MotionSetCore(cEm *, _MOTION_INFO *, void *, void *, unsigned char, unsigned short, unsigned short)>
    /* 0x800AA9C8 */ mem.write_u16(ctx.r[28] + (2), static_cast<uint16_t>(ctx.r[30])); // sth r30, 2(r28)
    /* 0x800AA9CC */ mem.write_u16(ctx.r[28] + (6), static_cast<uint16_t>(ctx.r[29])); // sth r29, 6(r28)
    /* 0x800AA9D0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AA9D4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (332)); // lwz r0, 332(r9)
    /* 0x800AA9D8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800AA9DC */ if (ctx.eval_bc(4, 0)) goto loc_800AA9EC; // bc 4, 0, 0x800AA9EC
    /* 0x800AA9E0 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800AA9E4 */ mem.write_u32(ctx.r[28] + (28), ctx.r[0]); // stw r0, 28(r28)
    /* 0x800AA9E8 */ goto loc_800AA9F0; // b 0x800AA9F0 <sub_800AA9F0>
loc_800AA9EC:;
    /* 0x800AA9EC */ mem.write_u32(ctx.r[28] + (28), ctx.r[29]); // stw r29, 28(r28)
loc_800AA9F0:;
    /* 0x800AA9F0 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800AA9F4 */ mem.write_u8(ctx.r[31] + (250), static_cast<uint8_t>(ctx.r[0])); // stb r0, 250(r31)
loc_800AA9F8:;
    /* 0x800AA9F8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800AA9FC */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800AAA00 */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-14564)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -14564(r9) [0x8016C71C]
    /* 0x800AAA04 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AAA08 */ ctx.f[2] = mem.read_f32(ctx.r[11] + (-14560)); ctx.ps0[2] = static_cast<float>(ctx.f[2]); // lfs f2, -14560(r11) [0x8016C720]
    /* 0x800AAA0C */ MotionMove_800A2434(ctx, mem); // bl 0x800A2434 <MotionMove(cEm *, float, float)>
    /* 0x800AAA10 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800AAA14 */ if (ctx.eval_bc(12, 2)) goto loc_800AACFC; // bc 12, 2, 0x800AACFC
    /* 0x800AAA18 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800AAA1C */ ctx.r[4] = 0x00000004u; // li r4, 4
    /* 0x800AAA20 */ mem.write_u16(ctx.r[28] + (0), static_cast<uint16_t>(ctx.r[0])); // sth r0, 0(r28)
    /* 0x800AAA24 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAA28 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800AAA2C */ ctx.r[29] = 0x00000000u; // li r29, 0
    /* 0x800AAA30 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AAA34 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAA38 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800AAA3C */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800AAA40 */ ctx.r[9] = 0x00000003u; // li r9, 3
    /* 0x800AAA44 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800AAA48 */ mem.write_u32(ctx.r[1] + (8), ctx.r[29]); // stw r29, 8(r1)
    /* 0x800AAA4C */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AAA50 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800AAA54 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800AAA58 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800AAA5C */ ctx.r[10] = ctx.r[31]; // mr r10, r31
    /* 0x800AAA60 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800AAA64 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AAA68 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (332)); // lwz r0, 332(r9)
    /* 0x800AAA6C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800AAA70 */ if (ctx.eval_bc(4, 0)) goto loc_800AAB04; // bc 4, 0, 0x800AAB04
    /* 0x800AAA74 */ ctx.r[0] = mem.read_u32(ctx.r[27] + (1748)); // lwz r0, 1748(r27)
    /* 0x800AAA78 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 8); // cmpwi cr0, r0, 8
    /* 0x800AAA7C */ if (ctx.eval_bc(4, 2)) goto loc_800AAAC4; // bc 4, 2, 0x800AAAC4
    /* 0x800AAA80 */ ctx.r[4] = 0x0000003Bu; // li r4, 59
    /* 0x800AAA84 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAA88 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800AAA8C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AAA90 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAA94 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800AAA98 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800AAA9C */ mem.write_u32(ctx.r[1] + (8), ctx.r[29]); // stw r29, 8(r1)
    /* 0x800AAAA0 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800AAAA4 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AAAA8 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800AAAAC */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800AAAB0 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800AAAB4 */ ctx.r[9] = 0x00000003u; // li r9, 3
    /* 0x800AAAB8 */ ctx.r[10] = ctx.r[31]; // mr r10, r31
    /* 0x800AAABC */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800AAAC0 */ goto loc_800AAB04; // b 0x800AAB04 <sub_800AAB04>
loc_800AAAC4:;
    /* 0x800AAAC4 */ ctx.r[4] = 0x0000004Au; // li r4, 74
    /* 0x800AAAC8 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAACC */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800AAAD0 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AAAD4 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAAD8 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800AAADC */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800AAAE0 */ mem.write_u32(ctx.r[1] + (8), ctx.r[29]); // stw r29, 8(r1)
    /* 0x800AAAE4 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800AAAE8 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AAAEC */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800AAAF0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800AAAF4 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800AAAF8 */ ctx.r[9] = 0x00000003u; // li r9, 3
    /* 0x800AAAFC */ ctx.r[10] = ctx.r[31]; // mr r10, r31
    /* 0x800AAB00 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800AAB04:;
    /* 0x800AAB04 */ ctx.r[0] = 0x00000002u; // li r0, 2
    /* 0x800AAB08 */ goto loc_800AACE4; // b 0x800AACE4 <sub_800AACE4>
loc_800AAB0C:;
    /* 0x800AAB0C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AAB10 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (332)); // lwz r0, 332(r9)
    /* 0x800AAB14 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800AAB18 */ if (ctx.eval_bc(4, 0)) goto loc_800AAB7C; // bc 4, 0, 0x800AAB7C
    /* 0x800AAB1C */ ctx.r[0] = mem.read_u16(ctx.r[27] + (2598)); // lhz r0, 2598(r27)
    /* 0x800AAB20 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 60); // cmpwi cr0, r0, 60
    /* 0x800AAB24 */ if (ctx.eval_bc(4, 2)) goto loc_800AACFC; // bc 4, 2, 0x800AACFC
    /* 0x800AAB28 */ ctx.r[0] = mem.read_u32(ctx.r[27] + (1748)); // lwz r0, 1748(r27)
    /* 0x800AAB2C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 8); // cmpwi cr0, r0, 8
    /* 0x800AAB30 */ ctx.r[4] = 0x0000004Bu; // li r4, 75
    /* 0x800AAB34 */ if (ctx.eval_bc(4, 2)) goto loc_800AAB3C; // bc 4, 2, 0x800AAB3C
    /* 0x800AAB38 */ ctx.r[4] = 0x0000003Du; // li r4, 61
loc_800AAB3C:;
    /* 0x800AAB3C */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAB40 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800AAB44 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AAB48 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAB4C */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800AAB50 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800AAB54 */ mem.write_u32(ctx.r[1] + (8), ctx.r[29]); // stw r29, 8(r1)
    /* 0x800AAB58 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AAB5C */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800AAB60 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800AAB64 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800AAB68 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800AAB6C */ ctx.r[9] = 0x00000003u; // li r9, 3
    /* 0x800AAB70 */ ctx.r[10] = ctx.r[3]; // mr r10, r3
    /* 0x800AAB74 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800AAB78 */ goto loc_800AACFC; // b 0x800AACFC <sub_800AACFC>
loc_800AAB7C:;
    /* 0x800AAB7C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800AAB80 */ ctx.r[9] = ctx.r[0] & 0x0400u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0400
    /* 0x800AAB84 */ if (ctx.eval_bc(4, 2)) goto loc_800AACFC; // bc 4, 2, 0x800AACFC
    /* 0x800AAB88 */ ctx.r[0] = 0x00000003u; // li r0, 3
    /* 0x800AAB8C */ mem.write_u8(ctx.r[31] + (250), static_cast<uint8_t>(ctx.r[0])); // stb r0, 250(r31)
    /* 0x800AAB90 */ goto loc_800AACFC; // b 0x800AACFC <sub_800AACFC>
loc_800AAB94:;
    /* 0x800AAB94 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800AAB98 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AAB9C */ mem.write_u16(ctx.r[28] + (4), static_cast<uint16_t>(ctx.r[0])); // sth r0, 4(r28)
    /* 0x800AABA0 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AABA4 */ ctx.r[4] = ctx.r[31] + (380); // addi r4, r31, 380
    /* 0x800AABA8 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800AABAC */ ctx.r[11] = mem.read_u32(ctx.r[9] + (280)); // lwz r11, 280(r9)
    /* 0x800AABB0 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800AABB4 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800AABB8 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800AABBC */ ctx.r[5] = mem.read_u32(ctx.r[11] + (384)); // lwz r5, 384(r11)
    /* 0x800AABC0 */ ctx.r[5] = ctx.r[5] + ctx.r[11]; // add r5, r5, r11
    /* 0x800AABC4 */ MotionSetCore_800A1E20(ctx, mem); // bl 0x800A1E20 <MotionSetCore(cEm *, _MOTION_INFO *, void *, void *, unsigned char, unsigned short, unsigned short)>
    /* 0x800AABC8 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800AABCC */ ctx.r[4] = 0x0000000Cu; // li r4, 12
    /* 0x800AABD0 */ ctx.r[5] = ctx.r[31] + (192); // addi r5, r31, 192
    /* 0x800AABD4 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800AABD8 */ SndSeCall_800CB7DC(ctx, mem); // bl 0x800CB7DC <SndSeCall(unsigned short, unsigned short, Vec *, unsigned char)>
    /* 0x800AABDC */ mem.write_u16(ctx.r[28] + (2), static_cast<uint16_t>(ctx.r[29])); // sth r29, 2(r28)
    /* 0x800AABE0 */ ctx.r[0] = 0x00000004u; // li r0, 4
    /* 0x800AABE4 */ mem.write_u8(ctx.r[31] + (250), static_cast<uint8_t>(ctx.r[0])); // stb r0, 250(r31)
loc_800AABE8:;
    /* 0x800AABE8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800AABEC */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800AABF0 */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-14564)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -14564(r9) [0x8016C71C]
    /* 0x800AABF4 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AABF8 */ ctx.f[2] = mem.read_f32(ctx.r[11] + (-14560)); ctx.ps0[2] = static_cast<float>(ctx.f[2]); // lfs f2, -14560(r11) [0x8016C720]
    /* 0x800AABFC */ MotionMove_800A2434(ctx, mem); // bl 0x800A2434 <MotionMove(cEm *, float, float)>
    /* 0x800AAC00 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800AAC04 */ if (ctx.eval_bc(12, 2)) goto loc_800AACFC; // bc 12, 2, 0x800AACFC
    /* 0x800AAC08 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800AAC0C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800AAC10 */ mem.write_u16(ctx.r[28] + (0), static_cast<uint16_t>(ctx.r[0])); // sth r0, 0(r28)
    /* 0x800AAC14 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800AAC18 */ ctx.r[5] = ctx.r[31]; // mr r5, r31
    /* 0x800AAC1C */ EspgenDelete_8008E8B8(ctx, mem); // bl 0x8008E8B8 <EspgenDelete(unsigned short, unsigned char, void *)>
    /* 0x800AAC20 */ ctx.r[0] = mem.read_u32(ctx.r[28] + (28)); // lwz r0, 28(r28)
    /* 0x800AAC24 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800AAC28 */ if (ctx.eval_bc(12, 2)) goto loc_800AACE0; // bc 12, 2, 0x800AACE0
    /* 0x800AAC2C */ ctx.r[0] = mem.read_u32(ctx.r[27] + (1748)); // lwz r0, 1748(r27)
    /* 0x800AAC30 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 8); // cmpwi cr0, r0, 8
    /* 0x800AAC34 */ if (ctx.eval_bc(4, 2)) goto loc_800AAC80; // bc 4, 2, 0x800AAC80
    /* 0x800AAC38 */ ctx.r[4] = 0x0000003Eu; // li r4, 62
    /* 0x800AAC3C */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAC40 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800AAC44 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AAC48 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAC4C */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800AAC50 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800AAC54 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800AAC58 */ mem.write_u32(ctx.r[1] + (8), ctx.r[0]); // stw r0, 8(r1)
    /* 0x800AAC5C */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800AAC60 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AAC64 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800AAC68 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800AAC6C */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800AAC70 */ ctx.r[9] = 0x00000003u; // li r9, 3
    /* 0x800AAC74 */ ctx.r[10] = ctx.r[31]; // mr r10, r31
    /* 0x800AAC78 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800AAC7C */ goto loc_800AACC4; // b 0x800AACC4 <sub_800AACC4>
loc_800AAC80:;
    /* 0x800AAC80 */ ctx.r[4] = 0x0000004Cu; // li r4, 76
    /* 0x800AAC84 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAC88 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800AAC8C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AAC90 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800AAC94 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800AAC98 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800AAC9C */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800AACA0 */ mem.write_u32(ctx.r[1] + (8), ctx.r[0]); // stw r0, 8(r1)
    /* 0x800AACA4 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800AACA8 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800AACAC */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800AACB0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800AACB4 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800AACB8 */ ctx.r[9] = 0x00000003u; // li r9, 3
    /* 0x800AACBC */ ctx.r[10] = ctx.r[31]; // mr r10, r31
    /* 0x800AACC0 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800AACC4:;
    /* 0x800AACC4 */ ctx.r[3] = 0x00000005u; // li r3, 5
    /* 0x800AACC8 */ ctx.r[4] = 0x00000012u; // li r4, 18
    /* 0x800AACCC */ ctx.r[5] = ctx.r[31] + (192); // addi r5, r31, 192
    /* 0x800AACD0 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800AACD4 */ SndSeCall_800CB7DC(ctx, mem); // bl 0x800CB7DC <SndSeCall(unsigned short, unsigned short, Vec *, unsigned char)>
    /* 0x800AACD8 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800AACDC */ mem.write_u32(ctx.r[28] + (28), ctx.r[0]); // stw r0, 28(r28)
loc_800AACE0:;
    /* 0x800AACE0 */ ctx.r[0] = 0x00000005u; // li r0, 5
loc_800AACE4:;
    /* 0x800AACE4 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800AACE8 */ mem.write_u8(ctx.r[31] + (250), static_cast<uint8_t>(ctx.r[0])); // stb r0, 250(r31)
    /* 0x800AACEC */ mem.write_u16(ctx.r[28] + (4), static_cast<uint16_t>(ctx.r[9])); // sth r9, 4(r28)
    /* 0x800AACF0 */ goto loc_800AACFC; // b 0x800AACFC <sub_800AACFC>
loc_800AACF4:;
    /* 0x800AACF4 */ mem.write_u8(ctx.r[31] + (250), static_cast<uint8_t>(ctx.r[29])); // stb r29, 250(r31)
    /* 0x800AACF8 */ mem.write_u8(ctx.r[31] + (249), static_cast<uint8_t>(ctx.r[29])); // stb r29, 249(r31)
loc_800AACFC:;
    /* 0x800AACFC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (44)); // lwz r0, 44(r1)
    /* 0x800AAD00 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AAD04 */ ctx.lmw(mem, 27, ctx.r[1] + (20)); // lmw r27, 20(r1)
    /* 0x800AAD08 */ ctx.r[1] = ctx.r[1] + (40); // addi r1, r1, 40
    /* 0x800AAD0C */ return; // blr
}

// [0x800AAD10] cObj11::clip(void) const (obj11.obj, 44 insns / 0xB0 bytes)
void cObj11__clip_800AAD10(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AAD10 */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800AAD14 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AAD18 */ mem.write_u32(ctx.r[1] + (12), ctx.r[31]); // stw r31, 12(r1)
    /* 0x800AAD1C */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800AAD20 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AAD24 */ ctx.r[31] = mem.read_u32(ctx.r[9] + (324)); // lwz r31, 324(r9)
    /* 0x800AAD28 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (4)); // lwz r0, 4(r31)
    /* 0x800AAD2C */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800AAD30 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800AAD34 */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, true); // srawi r0, r0, 2
    /* 0x800AAD38 */ if (ctx.eval_bc(12, 2)) goto loc_800AADA8; // bc 12, 2, 0x800AADA8
    /* 0x800AAD3C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800AAD40 */ if (ctx.eval_bc(4, 2)) goto loc_800AAD50; // bc 4, 2, 0x800AAD50
    /* 0x800AAD44 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800AAD48 */ ctx.r[3] = ctx.r[3] + (-14572); // addi r3, r3, -14572 -> 0x8016C714 /* "vector" */
    /* 0x800AAD4C */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800AAD50:;
    /* 0x800AAD50 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800AAD54 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800AAD58 */ ctx.r[11] = mem.read_u8(ctx.r[11] + (252)); // lbz r11, 252(r11)
    /* 0x800AAD5C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800AAD60 */ if (ctx.eval_bc(4, 2)) goto loc_800AADA8; // bc 4, 2, 0x800AADA8
    /* 0x800AAD64 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AAD68 */ ctx.r[31] = mem.read_u32(ctx.r[9] + (324)); // lwz r31, 324(r9)
    /* 0x800AAD6C */ ctx.r[0] = mem.read_u32(ctx.r[31] + (4)); // lwz r0, 4(r31)
    /* 0x800AAD70 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800AAD74 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800AAD78 */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800AAD7C */ ctx.cmp_u32(0, ctx.r[11], ctx.r[0]); // cmplw cr0, r11, r0
    /* 0x800AAD80 */ if (ctx.eval_bc(12, 0)) goto loc_800AAD90; // bc 12, 0, 0x800AAD90
    /* 0x800AAD84 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800AAD88 */ ctx.r[3] = ctx.r[3] + (-14572); // addi r3, r3, -14572 -> 0x8016C714 /* "vector" */
    /* 0x800AAD8C */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800AAD90:;
    /* 0x800AAD90 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800AAD94 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800AAD98 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800AAD9C */ ctx.r[0] = mem.read_u32(ctx.r[11] + (244)); // lwz r0, 244(r11)
    /* 0x800AADA0 */ ctx.r[9] = ctx.r[0] & 0x0002u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0002
    /* 0x800AADA4 */ if (ctx.eval_bc(4, 2)) goto loc_800AADAC; // bc 4, 2, 0x800AADAC
loc_800AADA8:;
    /* 0x800AADA8 */ ctx.r[3] = 0x00000000u; // li r3, 0
loc_800AADAC:;
    /* 0x800AADAC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800AADB0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AADB4 */ ctx.r[31] = mem.read_u32(ctx.r[1] + (12)); // lwz r31, 12(r1)
    /* 0x800AADB8 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800AADBC */ return; // blr
}

// [0x800AADC0] cObj11::renderSetup(void) (obj11.obj, 59 insns / 0xEC bytes)
void cObj11__renderSetup_800AADC0(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AADC0 */ ctx.r[1] += (-40); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -40(r1)
    /* 0x800AADC4 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AADC8 */ ctx.stmw(mem, 25, ctx.r[1] + (12)); // stmw r25, 12(r1)
    /* 0x800AADCC */ mem.write_u32(ctx.r[1] + (44), ctx.r[0]); // stw r0, 44(r1)
    /* 0x800AADD0 */ ctx.r[27] = ctx.r[3]; // mr r27, r3
    /* 0x800AADD4 */ ctx.r[25] = 0x00000000u; // li r25, 0
    /* 0x800AADD8 */ ctx.r[26] = 0x80170000u; // lis r26, 0x8017
    /* 0x800AADDC */ ctx.r[30] = ctx.r[27] + (312); // addi r30, r27, 312
    /* 0x800AADE0 */ ctx.r[28] = 0x00000000u; // li r28, 0
    /* 0x800AADE4 */ ctx.r[29] = 0x00000008u; // li r29, 8
loc_800AADE8:;
    /* 0x800AADE8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AADEC */ ctx.r[31] = mem.read_u32(ctx.r[9] + (324)); // lwz r31, 324(r9)
    /* 0x800AADF0 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (4)); // lwz r0, 4(r31)
    /* 0x800AADF4 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800AADF8 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800AADFC */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800AAE00 */ ctx.cmp_u32(0, ctx.r[25], ctx.r[0]); // cmplw cr0, r25, r0
    /* 0x800AAE04 */ if (ctx.eval_bc(12, 0)) goto loc_800AAE10; // bc 12, 0, 0x800AAE10
    /* 0x800AAE08 */ ctx.r[3] = ctx.r[26] + (-14572); // addi r3, r26, -14572 -> 0x8016C714 /* "vector" */
    /* 0x800AAE0C */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800AAE10:;
    /* 0x800AAE10 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800AAE14 */ { uint64_t _s = static_cast<uint64_t>(ctx.r[29]) + 0xFFFFFFFFull; ctx.r[29] = static_cast<uint32_t>(_s); ctx.set_ca(_s > 0xFFFFFFFFull); } ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[29]), 0); // addic. r29, r29, -1
    /* 0x800AAE18 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800AAE1C */ ctx.r[11] = ctx.r[11] + (312); // addi r11, r11, 312
    /* 0x800AAE20 */ ctx.r[0] = mem.read_u32(ctx.r[11] + ctx.r[28]); // lwzx r0, r11, r28
    /* 0x800AAE24 */ ctx.r[28] = ctx.r[28] + (4); // addi r28, r28, 4
    /* 0x800AAE28 */ mem.write_u32(ctx.r[30] + (0), ctx.r[0]); // stw r0, 0(r30)
    /* 0x800AAE2C */ ctx.r[30] = ctx.r[30] + (4); // addi r30, r30, 4
    /* 0x800AAE30 */ if (ctx.eval_bc(4, 2)) goto loc_800AADE8; // bc 4, 2, 0x800AADE8
    /* 0x800AAE34 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800AAE38 */ ctx.r[31] = mem.read_u32(ctx.r[9] + (324)); // lwz r31, 324(r9)
    /* 0x800AAE3C */ ctx.r[0] = mem.read_u32(ctx.r[31] + (4)); // lwz r0, 4(r31)
    /* 0x800AAE40 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800AAE44 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800AAE48 */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800AAE4C */ ctx.cmp_u32(0, ctx.r[29], ctx.r[0]); // cmplw cr0, r29, r0
    /* 0x800AAE50 */ if (ctx.eval_bc(12, 0)) goto loc_800AAE60; // bc 12, 0, 0x800AAE60
    /* 0x800AAE54 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800AAE58 */ ctx.r[3] = ctx.r[3] + (-14572); // addi r3, r3, -14572 -> 0x8016C714 /* "vector" */
    /* 0x800AAE5C */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800AAE60:;
    /* 0x800AAE60 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800AAE64 */ ctx.r[3] = ctx.r[27]; // mr r3, r27
    /* 0x800AAE68 */ ctx.r[8] = mem.read_u32(ctx.r[27] + (240)); // lwz r8, 240(r27)
    /* 0x800AAE6C */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800AAE70 */ ctx.r[7] = ctx.r[8] + (264); // addi r7, r8, 264
    /* 0x800AAE74 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (240)); // lwz r9, 240(r11)
    /* 0x800AAE78 */ ctx.r[10] = mem.read_u32(ctx.r[9] + (264)); // lwz r10, 264(r9)
    /* 0x800AAE7C */ ctx.r[9] = ctx.r[9] + (264); // addi r9, r9, 264
    /* 0x800AAE80 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (8)); // lwz r0, 8(r9)
    /* 0x800AAE84 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (4)); // lwz r11, 4(r9)
    /* 0x800AAE88 */ mem.write_u32(ctx.r[8] + (264), ctx.r[10]); // stw r10, 264(r8)
    /* 0x800AAE8C */ mem.write_u32(ctx.r[7] + (8), ctx.r[0]); // stw r0, 8(r7)
    /* 0x800AAE90 */ mem.write_u32(ctx.r[7] + (4), ctx.r[11]); // stw r11, 4(r7)
    /* 0x800AAE94 */ commonScreenMat_800D95B0(ctx, mem); // bl 0x800D95B0 <commonScreenMat(tagCOMN *)>
    /* 0x800AAE98 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (44)); // lwz r0, 44(r1)
    /* 0x800AAE9C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AAEA0 */ ctx.lmw(mem, 25, ctx.r[1] + (12)); // lmw r25, 12(r1)
    /* 0x800AAEA4 */ ctx.r[1] = ctx.r[1] + (40); // addi r1, r1, 40
    /* 0x800AAEA8 */ return; // blr
}

// [0x800AAEAC] cObj11::Release(void) (obj11.obj, 16 insns / 0x40 bytes)
void cObj11__Release_800AAEAC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AAEAC */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800AAEB0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AAEB4 */ ctx.stmw(mem, 30, ctx.r[1] + (8)); // stmw r30, 8(r1)
    /* 0x800AAEB8 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800AAEBC */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AAEC0 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800AAEC4 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800AAEC8 */ ctx.r[5] = ctx.r[30]; // mr r5, r30
    /* 0x800AAECC */ EspgenDelete_8008E8B8(ctx, mem); // bl 0x8008E8B8 <EspgenDelete(unsigned short, unsigned char, void *)>
    /* 0x800AAED0 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800AAED4 */ PushObj_800749C8(ctx, mem); // bl 0x800749C8 <PushObj(cObj *)>
    /* 0x800AAED8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800AAEDC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AAEE0 */ ctx.lmw(mem, 30, ctx.r[1] + (8)); // lmw r30, 8(r1)
    /* 0x800AAEE4 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800AAEE8 */ return; // blr
}

// [0x800AAEEC] cObj11::~cObj11(void) (obj11.obj, 8 insns / 0x20 bytes)
void cObj11_dtor_cObj11_800AAEEC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AAEEC */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800AAEF0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AAEF4 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800AAEF8 */ cObj_dtor_cObj_80074AD8(ctx, mem); // bl 0x80074AD8 <cObj::~cObj(void)>
    /* 0x800AAEFC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800AAF00 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AAF04 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800AAF08 */ return; // blr
}

// [0x800AAF0C] cObj11::cObj11(void) (obj11.obj, 19 insns / 0x4C bytes)
void cObj11__cObj11_800AAF0C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AAF0C */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800AAF10 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800AAF14 */ ctx.stmw(mem, 30, ctx.r[1] + (8)); // stmw r30, 8(r1)
    /* 0x800AAF18 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800AAF1C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800AAF20 */ cObj__cObj_80074A98(ctx, mem); // bl 0x80074A98 <cObj::cObj(void)>
    /* 0x800AAF24 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800AAF28 */ ctx.r[3] = ctx.r[30] + (1212); // addi r3, r30, 1212
    /* 0x800AAF2C */ ctx.r[9] = ctx.r[9] + (-14552); // addi r9, r9, -14552 -> cObj11 virtual table
    /* 0x800AAF30 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800AAF34 */ mem.write_u32(ctx.r[30] + (1208), ctx.r[9]); // stw r9, 1208(r30)
    /* 0x800AAF38 */ ctx.r[5] = 0x00000020u; // li r5, 32
    /* 0x800AAF3C */ ctx.call_indirect(0x800E8A5Cu, mem); // bl 0x800E8A5C <memset>
    /* 0x800AAF40 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800AAF44 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800AAF48 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800AAF4C */ ctx.lmw(mem, 30, ctx.r[1] + (8)); // lmw r30, 8(r1)
    /* 0x800AAF50 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800AAF54 */ return; // blr
}

// [0x800AAF58] cObj11::getFreePtr(void) (obj11.obj, 2 insns / 0x8 bytes)
void cObj11__getFreePtr_800AAF58(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AAF58 */ ctx.r[3] = ctx.r[3] + (1212); // addi r3, r3, 1212
    /* 0x800AAF5C */ return; // blr
}

// [0x800AAF60] cObj11::Initialize(void) (obj11.obj, 1 insns / 0x4 bytes)
void cObj11__Initialize_800AAF60(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800AAF60 */ return; // blr
}

// [0x800B915C] R000Init(void) (r000.obj, 79 insns / 0x13C bytes)
void R000Init_800B915C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B915C */ ctx.r[1] += (-48); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -48(r1)
    /* 0x800B9160 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800B9164 */ ctx.stmw(mem, 29, ctx.r[1] + (36)); // stmw r29, 36(r1)
    /* 0x800B9168 */ mem.write_u32(ctx.r[1] + (52), ctx.r[0]); // stw r0, 52(r1)
    /* 0x800B916C */ ctx.r[31] = 0x00000000u; // li r31, 0
    /* 0x800B9170 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B9174 */ mem.write_u32(ctx.r[13] + (-29712), ctx.r[31]); // stw r31, -29712(r13) [str_req]
    /* 0x800B9178 */ room_barrier_800B94FC(ctx, mem); // bl 0x800B94FC <room_barrier(long)>
    /* 0x800B917C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9180 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800B9184 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800B9188 */ if (ctx.eval_bc(4, 0)) goto loc_800B9198; // bc 4, 0, 0x800B9198
    /* 0x800B918C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800B9190 */ ctx.r[0] = ctx.r[0] | 0x30000000u; // oris r0, r0, 0x3000
    /* 0x800B9194 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
loc_800B9198:;
    /* 0x800B9198 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B919C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800B91A0 */ ctx.r[11] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x2000
    /* 0x800B91A4 */ if (ctx.eval_bc(12, 2)) goto loc_800B921C; // bc 12, 2, 0x800B921C
    /* 0x800B91A8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (4)); // lwz r0, 4(r9)
    /* 0x800B91AC */ ctx.r[9] = ctx.r[0] & 0x10000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x1000
    /* 0x800B91B0 */ if (ctx.eval_bc(12, 2)) goto loc_800B921C; // bc 12, 2, 0x800B921C
    /* 0x800B91B4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B91B8 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800B91BC */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12884)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12884(r9) [0x8016CDAC]
    /* 0x800B91C0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800B91C4 */ ctx.f[0] = mem.read_f32(ctx.r[10] + (-12876)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12876(r10) [0x8016CDB4]
    /* 0x800B91C8 */ ctx.r[30] = ctx.r[1] + (16); // addi r30, r1, 16
    /* 0x800B91CC */ ctx.f[12] = mem.read_f32(ctx.r[11] + (-12880)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12880(r11) [0x8016CDB0]
    /* 0x800B91D0 */ ctx.r[4] = 0x0000001Eu; // li r4, 30
    /* 0x800B91D4 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800B91D8 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B91DC */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r30)
    /* 0x800B91E0 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r30)
    /* 0x800B91E4 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800B91E8 */ ctx.r[29] = ctx.r[3]; // mr r29, r3
    /* 0x800B91EC */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B91F0 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800B91F4 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800B91F8 */ mem.write_u32(ctx.r[1] + (8), ctx.r[31]); // stw r31, 8(r1)
    /* 0x800B91FC */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800B9200 */ ctx.r[6] = ctx.r[29]; // mr r6, r29
    /* 0x800B9204 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B9208 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B920C */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800B9210 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800B9214 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800B9218 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800B921C:;
    /* 0x800B921C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9220 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800B9224 */ mem.write_u32(ctx.r[13] + (-32268), ctx.r[0]); // stw r0, -32268(r13) [pEvent34]
    /* 0x800B9228 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (29012)); // lwz r9, 29012(r11)
    /* 0x800B922C */ mem.write_u32(ctx.r[13] + (-32272), ctx.r[0]); // stw r0, -32272(r13) [pEvent00]
    /* 0x800B9230 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800B9234 */ if (ctx.eval_bc(12, 0)) goto loc_800B9284; // bc 12, 0, 0x800B9284
    /* 0x800B9238 */ ctx.r[0] = ctx.r[9] | 0x80000000u; // oris r0, r9, 0x8000
    /* 0x800B923C */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800B9240 */ mem.write_u32(ctx.r[11] + (29012), ctx.r[0]); // stw r0, 29012(r11)
    /* 0x800B9244 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800B9248 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800B924C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9250 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800B9254 */ mem.write_u32(ctx.r[13] + (-32272), ctx.r[0]); // stw r0, -32272(r13) [pEvent00]
    /* 0x800B9258 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800B925C */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800B9260 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (56)); // lwz r4, 56(r9)
    /* 0x800B9264 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800B9268 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800B926C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9270 */ ctx.r[11] = 0x00000001u; // li r11, 1
    /* 0x800B9274 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800B9278 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800B927C */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
    /* 0x800B9280 */ mem.write_u32(ctx.r[13] + (-29712), ctx.r[11]); // stw r11, -29712(r13) [str_req]
loc_800B9284:;
    /* 0x800B9284 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (52)); // lwz r0, 52(r1)
    /* 0x800B9288 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B928C */ ctx.lmw(mem, 29, ctx.r[1] + (36)); // lmw r29, 36(r1)
    /* 0x800B9290 */ ctx.r[1] = ctx.r[1] + (48); // addi r1, r1, 48
    /* 0x800B9294 */ return; // blr
}

// [0x800B9298] R000Main(void) (r000.obj, 153 insns / 0x264 bytes)
void R000Main_800B9298(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9298 */ ctx.r[1] += (-48); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -48(r1)
    /* 0x800B929C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800B92A0 */ ctx.stmw(mem, 29, ctx.r[1] + (36)); // stmw r29, 36(r1)
    /* 0x800B92A4 */ mem.write_u32(ctx.r[1] + (52), ctx.r[0]); // stw r0, 52(r1)
    /* 0x800B92A8 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800B92AC */ room_barrier_800B94FC(ctx, mem); // bl 0x800B94FC <room_barrier(long)>
    /* 0x800B92B0 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29712)); // lwz r0, -29712(r13) [str_req]
    /* 0x800B92B4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800B92B8 */ if (ctx.eval_bc(4, 2)) goto loc_800B92DC; // bc 4, 2, 0x800B92DC
    /* 0x800B92BC */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800B92C0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B92C4 */ mem.write_u32(ctx.r[13] + (-29712), ctx.r[0]); // stw r0, -29712(r13) [str_req]
    /* 0x800B92C8 */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800B92CC */ ctx.r[5] = 0x00000002u; // li r5, 2
    /* 0x800B92D0 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800B92D4 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800B92D8 */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
loc_800B92DC:;
    /* 0x800B92DC */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-32272)); // lwz r3, -32272(r13) [pEvent00]
    /* 0x800B92E0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800B92E4 */ if (ctx.eval_bc(12, 2)) goto loc_800B934C; // bc 12, 2, 0x800B934C
    /* 0x800B92E8 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800B92EC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800B92F0 */ if (ctx.eval_bc(12, 2)) goto loc_800B9474; // bc 12, 2, 0x800B9474
    /* 0x800B92F4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-32272)); // lwz r11, -32272(r13) [pEvent00]
    /* 0x800B92F8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800B92FC */ if (ctx.eval_bc(12, 2)) goto loc_800B931C; // bc 12, 2, 0x800B931C
    /* 0x800B9300 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800B9304 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800B9308 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800B930C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800B9310 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800B9314 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B9318 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800B931C:;
    /* 0x800B931C */ ctx.r[30] = 0x00000000u; // li r30, 0
    /* 0x800B9320 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B9324 */ mem.write_u32(ctx.r[13] + (-32272), ctx.r[30]); // stw r30, -32272(r13) [pEvent00]
    /* 0x800B9328 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800B932C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9330 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
    /* 0x800B9334 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9338 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800B933C */ ctx.r[0] = ctx.r[0] | 0x10000000u; // oris r0, r0, 0x1000
    /* 0x800B9340 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800B9344 */ mem.write_u32(ctx.r[13] + (-29712), ctx.r[30]); // stw r30, -29712(r13) [str_req]
    /* 0x800B9348 */ goto loc_800B9474; // b 0x800B9474 <sub_800B9474>
loc_800B934C:;
    /* 0x800B934C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9350 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (29016)); // lwz r9, 29016(r11)
    /* 0x800B9354 */ ctx.r[0] = ctx.r[9] & 0x10000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andis. r0, r9, 0x1000
    /* 0x800B9358 */ if (ctx.eval_bc(12, 2)) goto loc_800B93B4; // bc 12, 2, 0x800B93B4
    /* 0x800B935C */ ctx.r[10] = ctx.r[9] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r9, 0x2000
    /* 0x800B9360 */ if (ctx.eval_bc(4, 2)) goto loc_800B93B4; // bc 4, 2, 0x800B93B4
    /* 0x800B9364 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (332)); // lwz r0, 332(r11)
    /* 0x800B9368 */ ctx.r[10] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r0, 0x2000
    /* 0x800B936C */ if (ctx.eval_bc(4, 2)) goto loc_800B93B4; // bc 4, 2, 0x800B93B4
    /* 0x800B9370 */ ctx.r[0] = ctx.r[9] | 0x20000000u; // oris r0, r9, 0x2000
    /* 0x800B9374 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800B9378 */ mem.write_u32(ctx.r[11] + (29016), ctx.r[0]); // stw r0, 29016(r11)
    /* 0x800B937C */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800B9380 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800B9384 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9388 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800B938C */ mem.write_u32(ctx.r[13] + (-32268), ctx.r[0]); // stw r0, -32268(r13) [pEvent34]
    /* 0x800B9390 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800B9394 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9398 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (60)); // lwz r4, 60(r9)
    /* 0x800B939C */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800B93A0 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800B93A4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B93A8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800B93AC */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800B93B0 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
loc_800B93B4:;
    /* 0x800B93B4 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-32268)); // lwz r3, -32268(r13) [pEvent34]
    /* 0x800B93B8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800B93BC */ if (ctx.eval_bc(12, 2)) goto loc_800B9474; // bc 12, 2, 0x800B9474
    /* 0x800B93C0 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800B93C4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800B93C8 */ if (ctx.eval_bc(12, 2)) goto loc_800B9474; // bc 12, 2, 0x800B9474
    /* 0x800B93CC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-32268)); // lwz r11, -32268(r13) [pEvent34]
    /* 0x800B93D0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800B93D4 */ if (ctx.eval_bc(12, 2)) goto loc_800B93F4; // bc 12, 2, 0x800B93F4
    /* 0x800B93D8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800B93DC */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800B93E0 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800B93E4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800B93E8 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800B93EC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B93F0 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800B93F4:;
    /* 0x800B93F4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B93F8 */ ctx.r[31] = 0x00000000u; // li r31, 0
    /* 0x800B93FC */ mem.write_u32(ctx.r[13] + (-32268), ctx.r[31]); // stw r31, -32268(r13) [pEvent34]
    /* 0x800B9400 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (4)); // lwz r0, 4(r9)
    /* 0x800B9404 */ ctx.r[9] = ctx.r[0] & 0x10000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x1000
    /* 0x800B9408 */ if (ctx.eval_bc(12, 2)) goto loc_800B9474; // bc 12, 2, 0x800B9474
    /* 0x800B940C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B9410 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800B9414 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12864)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12864(r9) [0x8016CDC0]
    /* 0x800B9418 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800B941C */ ctx.f[0] = mem.read_f32(ctx.r[10] + (-12856)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12856(r10) [0x8016CDC8]
    /* 0x800B9420 */ ctx.r[30] = ctx.r[1] + (16); // addi r30, r1, 16
    /* 0x800B9424 */ ctx.f[12] = mem.read_f32(ctx.r[11] + (-12860)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12860(r11) [0x8016CDC4]
    /* 0x800B9428 */ ctx.r[4] = 0x0000001Eu; // li r4, 30
    /* 0x800B942C */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800B9430 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B9434 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r30)
    /* 0x800B9438 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r30)
    /* 0x800B943C */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800B9440 */ ctx.r[29] = ctx.r[3]; // mr r29, r3
    /* 0x800B9444 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B9448 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800B944C */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800B9450 */ mem.write_u32(ctx.r[1] + (8), ctx.r[31]); // stw r31, 8(r1)
    /* 0x800B9454 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800B9458 */ ctx.r[6] = ctx.r[29]; // mr r6, r29
    /* 0x800B945C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B9460 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9464 */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800B9468 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800B946C */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800B9470 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800B9474:;
    /* 0x800B9474 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9478 */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800B947C */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800B9480 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800B9484 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800B9488 */ ctx.rlwinm(9, 0, 30u, 2u, 31u, true); // rlwinm r9, r0, 30, 2, 31
    /* 0x800B948C */ if (ctx.eval_bc(4, 2)) goto loc_800B949C; // bc 4, 2, 0x800B949C
    /* 0x800B9490 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800B9494 */ ctx.r[3] = ctx.r[3] + (-12872); // addi r3, r3, -12872 -> 0x8016CDB8 /* "vector" */
    /* 0x800B9498 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800B949C:;
    /* 0x800B949C */ ctx.r[10] = mem.read_u32(ctx.r[30] + (0)); // lwz r10, 0(r30)
    /* 0x800B94A0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B94A4 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12852)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12852(r9) [0x8016CDCC]
    /* 0x800B94A8 */ ctx.r[11] = mem.read_u32(ctx.r[10] + (0)); // lwz r11, 0(r10)
    /* 0x800B94AC */ ctx.f[0] = mem.read_f32(ctx.r[11] + (192)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 192(r11)
    /* 0x800B94B0 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[13]); // fcmpu cr0, f0, f13
    /* 0x800B94B4 */ if (ctx.eval_bc(4, 1)) goto loc_800B94E8; // bc 4, 1, 0x800B94E8
    /* 0x800B94B8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B94BC */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800B94C0 */ ctx.r[9] = ctx.r[0] & 0x08000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x0800
    /* 0x800B94C4 */ if (ctx.eval_bc(4, 2)) goto loc_800B94E8; // bc 4, 2, 0x800B94E8
    /* 0x800B94C8 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800B94CC */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800B94D0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B94D4 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
    /* 0x800B94D8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B94DC */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800B94E0 */ ctx.r[0] = ctx.r[0] | 0x08000000u; // oris r0, r0, 0x0800
    /* 0x800B94E4 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
loc_800B94E8:;
    /* 0x800B94E8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (52)); // lwz r0, 52(r1)
    /* 0x800B94EC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B94F0 */ ctx.lmw(mem, 29, ctx.r[1] + (36)); // lmw r29, 36(r1)
    /* 0x800B94F4 */ ctx.r[1] = ctx.r[1] + (48); // addi r1, r1, 48
    /* 0x800B94F8 */ return; // blr
}

// [0x800B94FC] room_barrier(long) (r000.obj, 294 insns / 0x498 bytes)
void room_barrier_800B94FC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B94FC */ ctx.r[1] += (-120); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -120(r1)
    /* 0x800B9500 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800B9504 */ mem.write_f64(ctx.r[1] + (112), ctx.f[31]); // stfd f31, 112(r1)
    /* 0x800B9508 */ ctx.stmw(mem, 20, ctx.r[1] + (64)); // stmw r20, 64(r1)
    /* 0x800B950C */ mem.write_u32(ctx.r[1] + (124), ctx.r[0]); // stw r0, 124(r1)
    /* 0x800B9510 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29716)); // lwz r0, -29716(r13) [_.tmp_0.1369]
    /* 0x800B9514 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800B9518 */ if (ctx.eval_bc(4, 2)) goto loc_800B9540; // bc 4, 2, 0x800B9540
    /* 0x800B951C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B9520 */ ctx.r[11] = 0x801C0000u; // lis r11, 0x801C
    /* 0x800B9524 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12848)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12848(r9) [0x8016CDD0]
    /* 0x800B9528 */ ctx.r[10] = ctx.r[11] + (19120); // addi r10, r11, 19120 -> pl_old.1368
    /* 0x800B952C */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800B9530 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800B9534 */ mem.write_f32(ctx.r[11] + (19120), static_cast<float>(ctx.f[0])); // stfs f0, 19120(r11) [pl_old.1368]
    /* 0x800B9538 */ mem.write_u32(ctx.r[13] + (-29716), ctx.r[0]); // stw r0, -29716(r13) [_.tmp_0.1369]
    /* 0x800B953C */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
loc_800B9540:;
    /* 0x800B9540 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800B9544 */ if (ctx.eval_bc(4, 2)) goto loc_800B9568; // bc 4, 2, 0x800B9568
    /* 0x800B9548 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B954C */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800B9550 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800B9554 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800B9558 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800B955C */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800B9560 */ ctx.cmp_u32(0, ctx.r[3], ctx.r[0]); // cmplw cr0, r3, r0
    /* 0x800B9564 */ goto loc_800B9940; // b 0x800B9940 <sub_800B9940>
loc_800B9568:;
    /* 0x800B9568 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B956C */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800B9570 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800B9574 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800B9578 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800B957C */ ctx.rlwinm(9, 0, 30u, 2u, 31u, true); // rlwinm r9, r0, 30, 2, 31
    /* 0x800B9580 */ if (ctx.eval_bc(4, 2)) goto loc_800B9590; // bc 4, 2, 0x800B9590
    /* 0x800B9584 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800B9588 */ ctx.r[3] = ctx.r[3] + (-12872); // addi r3, r3, -12872 -> 0x8016CDB8 /* "vector" */
    /* 0x800B958C */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800B9590:;
    /* 0x800B9590 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800B9594 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800B9598 */ ctx.r[0] = mem.read_u8(ctx.r[11] + (1249)); // lbz r0, 1249(r11)
    /* 0x800B959C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800B95A0 */ if (ctx.eval_bc(4, 2)) goto loc_800B997C; // bc 4, 2, 0x800B997C
    /* 0x800B95A4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B95A8 */ ctx.r[0] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (26640)))); // lha r0, 26640(r9)
    /* 0x800B95AC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800B95B0 */ if (ctx.eval_bc(4, 1)) goto loc_800B997C; // bc 4, 1, 0x800B997C
    /* 0x800B95B4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B95B8 */ ctx.r[29] = ctx.r[1] + (16); // addi r29, r1, 16
    /* 0x800B95BC */ ctx.r[26] = ctx.r[29]; // mr r26, r29
    /* 0x800B95C0 */ ctx.r[10] = ctx.r[9] + (27784); // addi r10, r9, 27784 -> DesertVec
    /* 0x800B95C4 */ ctx.r[20] = 0x00000000u; // li r20, 0
    /* 0x800B95C8 */ ctx.r[27] = 0x00000000u; // li r27, 0
    /* 0x800B95CC */ ctx.r[28] = 0x00000000u; // li r28, 0
    /* 0x800B95D0 */ ctx.r[21] = 0x801C0000u; // lis r21, 0x801C
    /* 0x800B95D4 */ ctx.r[24] = ctx.r[1] + (32); // addi r24, r1, 32
    /* 0x800B95D8 */ ctx.r[25] = ctx.r[1] + (48); // addi r25, r1, 48
    /* 0x800B95DC */ ctx.r[22] = 0x00000000u; // li r22, 0
    /* 0x800B95E0 */ ctx.r[23] = 0x80170000u; // lis r23, 0x8017
loc_800B95E4:;
    /* 0x800B95E4 */ ctx.f[13] = mem.read_f32(ctx.r[10] + (0)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 0(r10)
    /* 0x800B95E8 */ ctx.r[31] = ctx.r[10] + (12); // addi r31, r10, 12
    /* 0x800B95EC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B95F0 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800B95F4 */ ctx.f[0] = mem.read_f32(ctx.r[10] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r10)
    /* 0x800B95F8 */ mem.write_f32(ctx.r[26] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r26)
    /* 0x800B95FC */ ctx.f[13] = mem.read_f32(ctx.r[10] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r10)
    /* 0x800B9600 */ mem.write_f32(ctx.r[26] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r26)
    /* 0x800B9604 */ ctx.f[0] = mem.read_f32(ctx.r[10] + (12)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 12(r10)
    /* 0x800B9608 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800B960C */ ctx.f[13] = mem.read_f32(ctx.r[31] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r31)
    /* 0x800B9610 */ mem.write_f32(ctx.r[1] + (36), static_cast<float>(ctx.f[13])); // stfs f13, 36(r1)
    /* 0x800B9614 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r31)
    /* 0x800B9618 */ mem.write_f32(ctx.r[1] + (40), static_cast<float>(ctx.f[0])); // stfs f0, 40(r1)
    /* 0x800B961C */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800B9620 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800B9624 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800B9628 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800B962C */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800B9630 */ ctx.cmp_u32(0, ctx.r[22], ctx.r[0]); // cmplw cr0, r22, r0
    /* 0x800B9634 */ if (ctx.eval_bc(12, 0)) goto loc_800B9640; // bc 12, 0, 0x800B9640
    /* 0x800B9638 */ ctx.r[3] = ctx.r[23] + (-12872); // addi r3, r23, -12872 -> 0x8016CDB8 /* "vector" */
    /* 0x800B963C */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800B9640:;
    /* 0x800B9640 */ ctx.r[11] = mem.read_u32(ctx.r[30] + (0)); // lwz r11, 0(r30)
    /* 0x800B9644 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800B9648 */ ctx.r[4] = ctx.r[24]; // mr r4, r24
    /* 0x800B964C */ ctx.r[5] = ctx.r[25]; // mr r5, r25
    /* 0x800B9650 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (0)); // lwz r9, 0(r11)
    /* 0x800B9654 */ ctx.r[6] = ctx.r[21] + (19120); // addi r6, r21, 19120 -> pl_old.1368
    /* 0x800B9658 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r9)
    /* 0x800B965C */ ctx.r[9] = ctx.r[9] + (192); // addi r9, r9, 192
    /* 0x800B9660 */ mem.write_f32(ctx.r[1] + (48), static_cast<float>(ctx.f[13])); // stfs f13, 48(r1)
    /* 0x800B9664 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800B9668 */ mem.write_f32(ctx.r[1] + (52), static_cast<float>(ctx.f[0])); // stfs f0, 52(r1)
    /* 0x800B966C */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800B9670 */ mem.write_f32(ctx.r[1] + (56), static_cast<float>(ctx.f[13])); // stfs f13, 56(r1)
    /* 0x800B9674 */ room_line_ck_800B9994(ctx, mem); // bl 0x800B9994 <room_line_ck(cVec &, cVec &, cVec &, cVec &)>
    /* 0x800B9678 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800B967C */ if (ctx.eval_bc(12, 2)) goto loc_800B9684; // bc 12, 2, 0x800B9684
    /* 0x800B9680 */ ctx.r[27] = ctx.r[27] + (1); // addi r27, r27, 1
loc_800B9684:;
    /* 0x800B9684 */ ctx.r[28] = ctx.r[28] + (1); // addi r28, r28, 1
    /* 0x800B9688 */ ctx.r[10] = ctx.r[31]; // mr r10, r31
    /* 0x800B968C */ ctx.cmp_u32(0, ctx.r[28], 0x0004u); // cmplwi cr0, r28, 0x0004
    /* 0x800B9690 */ if (ctx.eval_bc(4, 1)) goto loc_800B95E4; // bc 4, 1, 0x800B95E4
    /* 0x800B9694 */ ctx.r[0] = ctx.r[27] & 0x0001u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andi. r0, r27, 0x0001
    /* 0x800B9698 */ if (ctx.eval_bc(12, 2)) goto loc_800B991C; // bc 12, 2, 0x800B991C
    /* 0x800B969C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B96A0 */ ctx.r[28] = 0x00000000u; // li r28, 0
    /* 0x800B96A4 */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800B96A8 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800B96AC */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800B96B0 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800B96B4 */ ctx.rlwinm(9, 0, 30u, 2u, 31u, true); // rlwinm r9, r0, 30, 2, 31
    /* 0x800B96B8 */ if (ctx.eval_bc(4, 2)) goto loc_800B96C8; // bc 4, 2, 0x800B96C8
    /* 0x800B96BC */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800B96C0 */ ctx.r[3] = ctx.r[3] + (-12872); // addi r3, r3, -12872 -> 0x8016CDB8 /* "vector" */
    /* 0x800B96C4 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800B96C8:;
    /* 0x800B96C8 */ ctx.r[11] = mem.read_u32(ctx.r[30] + (0)); // lwz r11, 0(r30)
    /* 0x800B96CC */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B96D0 */ ctx.f[12] = mem.read_f32(ctx.r[9] + (-12844)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12844(r9) [0x8016CDD4]
    /* 0x800B96D4 */ ctx.r[4] = 0x00000011u; // li r4, 17
    /* 0x800B96D8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (0)); // lwz r9, 0(r11)
    /* 0x800B96DC */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800B96E0 */ ctx.r[20] = 0x00000001u; // li r20, 1
    /* 0x800B96E4 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r9)
    /* 0x800B96E8 */ ctx.r[9] = ctx.r[9] + (192); // addi r9, r9, 192
    /* 0x800B96EC */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800B96F0 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800B96F4 */ mem.write_f32(ctx.r[29] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r29)
    /* 0x800B96F8 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800B96FC */ mem.write_f32(ctx.r[29] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r29)
    /* 0x800B9700 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (20)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 20(r1)
    /* 0x800B9704 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[12]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f12
    /* 0x800B9708 */ mem.write_f32(ctx.r[1] + (20), static_cast<float>(ctx.f[0])); // stfs f0, 20(r1)
    /* 0x800B970C */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800B9710 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800B9714 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800B9718 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800B971C */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800B9720 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800B9724 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800B9728 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800B972C */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800B9730 */ mem.write_u32(ctx.r[1] + (8), ctx.r[28]); // stw r28, 8(r1)
    /* 0x800B9734 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800B9738 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B973C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B9740 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800B9744 */ ctx.r[3] = 0x800C0000u; // lis r3, 0x800C
    /* 0x800B9748 */ ctx.r[3] = ctx.r[3] + (-26060); // addi r3, r3, -26060 -> pl_damage(cEm *)
    /* 0x800B974C */ SetPlDamage_800CF3B0(ctx, mem); // bl 0x800CF3B0 <SetPlDamage(void (*)(cEm *))>
    /* 0x800B9750 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B9754 */ PlVibSet_800B9098(ctx, mem); // bl 0x800B9098 <PlVibSet(unsigned long)>
    /* 0x800B9758 */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800B975C */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800B9760 */ ctx.r[4] = 0x0000001Du; // li r4, 29
    /* 0x800B9764 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800B9768 */ SndSeCall_800CB7DC(ctx, mem); // bl 0x800CB7DC <SndSeCall(unsigned short, unsigned short, Vec *, unsigned char)>
    /* 0x800B976C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9770 */ ctx.r[31] = mem.read_u32(ctx.r[9] + (324)); // lwz r31, 324(r9)
    /* 0x800B9774 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (4)); // lwz r0, 4(r31)
    /* 0x800B9778 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800B977C */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800B9780 */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800B9784 */ ctx.cmp_u32(0, ctx.r[28], ctx.r[0]); // cmplw cr0, r28, r0
    /* 0x800B9788 */ if (ctx.eval_bc(12, 0)) goto loc_800B9798; // bc 12, 0, 0x800B9798
    /* 0x800B978C */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800B9790 */ ctx.r[3] = ctx.r[3] + (-12872); // addi r3, r3, -12872 -> 0x8016CDB8 /* "vector" */
    /* 0x800B9794 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800B9798:;
    /* 0x800B9798 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800B979C */ ctx.r[8] = 0x801C0000u; // lis r8, 0x801C
    /* 0x800B97A0 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800B97A4 */ ctx.r[30] = ctx.r[8] + (19120); // addi r30, r8, 19120 -> pl_old.1368
    /* 0x800B97A8 */ ctx.r[31] = mem.read_u32(ctx.r[10] + (324)); // lwz r31, 324(r10)
    /* 0x800B97AC */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800B97B0 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (4)); // lwz r0, 4(r31)
    /* 0x800B97B4 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800B97B8 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r11)
    /* 0x800B97BC */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800B97C0 */ ctx.f[0] = mem.read_f32(ctx.r[8] + (19120)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 19120(r8) [pl_old.1368]
    /* 0x800B97C4 */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800B97C8 */ ctx.f[31] = static_cast<float>(ctx.f[13] - ctx.f[0]); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // fsubs f31, f13, f0
    /* 0x800B97CC */ ctx.cmp_u32(0, ctx.r[28], ctx.r[0]); // cmplw cr0, r28, r0
    /* 0x800B97D0 */ if (ctx.eval_bc(12, 0)) goto loc_800B97E0; // bc 12, 0, 0x800B97E0
    /* 0x800B97D4 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800B97D8 */ ctx.r[3] = ctx.r[3] + (-12872); // addi r3, r3, -12872 -> 0x8016CDB8 /* "vector" */
    /* 0x800B97DC */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800B97E0:;
    /* 0x800B97E0 */ ctx.r[11] = mem.read_u32(ctx.r[31] + (0)); // lwz r11, 0(r31)
    /* 0x800B97E4 */ ctx.f[1] = ctx.f[31]; ctx.ps0[1] = static_cast<float>(ctx.f[31]); // fmr f1, f31
    /* 0x800B97E8 */ ctx.f[0] = mem.read_f32(ctx.r[30] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r30)
    /* 0x800B97EC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (0)); // lwz r9, 0(r11)
    /* 0x800B97F0 */ ctx.f[2] = mem.read_f32(ctx.r[9] + (200)); ctx.ps0[2] = static_cast<float>(ctx.f[2]); // lfs f2, 200(r9)
    /* 0x800B97F4 */ ctx.f[2] = static_cast<float>(ctx.f[2] - ctx.f[0]); ctx.ps0[2] = static_cast<float>(ctx.f[2]); // fsubs f2, f2, f0
    /* 0x800B97F8 */ ctx.call_indirect(0x800E3930u, mem); // bl 0x800E3930 <atan2f>
    /* 0x800B97FC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9800 */ ctx.f[31] = ctx.f[1]; ctx.ps0[31] = static_cast<float>(ctx.f[1]); // fmr f31, f1
    /* 0x800B9804 */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800B9808 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800B980C */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800B9810 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800B9814 */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800B9818 */ ctx.cmp_u32(0, ctx.r[28], ctx.r[0]); // cmplw cr0, r28, r0
    /* 0x800B981C */ if (ctx.eval_bc(12, 0)) goto loc_800B982C; // bc 12, 0, 0x800B982C
    /* 0x800B9820 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800B9824 */ ctx.r[3] = ctx.r[3] + (-12872); // addi r3, r3, -12872 -> 0x8016CDB8 /* "vector" */
    /* 0x800B9828 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800B982C:;
    /* 0x800B982C */ ctx.r[10] = mem.read_u32(ctx.r[30] + (0)); // lwz r10, 0(r30)
    /* 0x800B9830 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B9834 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12840)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12840(r9) [0x8016CDD8]
    /* 0x800B9838 */ ctx.r[11] = mem.read_u32(ctx.r[10] + (0)); // lwz r11, 0(r10)
    /* 0x800B983C */ ctx.f[0] = mem.read_f32(ctx.r[11] + (208)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 208(r11)
    /* 0x800B9840 */ ctx.f[1] = static_cast<float>(ctx.f[31] - ctx.f[0]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fsubs f1, f31, f0
    /* 0x800B9844 */ ctx.cmp_f64(0, ctx.f[1], ctx.f[13]); // fcmpu cr0, f1, f13
    /* 0x800B9848 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(1)); // cror 3, 2, 1
    /* 0x800B984C */ if (ctx.eval_bc(4, 3)) goto loc_800B9868; // bc 4, 3, 0x800B9868
    /* 0x800B9850 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B9854 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12836)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12836(r9) [0x8016CDDC]
loc_800B9858:;
    /* 0x800B9858 */ ctx.f[1] = static_cast<float>(ctx.f[1] - ctx.f[0]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fsubs f1, f1, f0
    /* 0x800B985C */ ctx.cmp_f64(0, ctx.f[1], ctx.f[13]); // fcmpu cr0, f1, f13
    /* 0x800B9860 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(1)); // cror 3, 2, 1
    /* 0x800B9864 */ if (ctx.eval_bc(12, 3)) goto loc_800B9858; // bc 12, 3, 0x800B9858
loc_800B9868:;
    /* 0x800B9868 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B986C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12832)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12832(r9) [0x8016CDE0]
    /* 0x800B9870 */ ctx.cmp_f64(0, ctx.f[1], ctx.f[0]); // fcmpu cr0, f1, f0
    /* 0x800B9874 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(0)); // cror 3, 2, 0
    /* 0x800B9878 */ if (ctx.eval_bc(4, 3)) goto loc_800B9898; // bc 4, 3, 0x800B9898
    /* 0x800B987C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B9880 */ ctx.f[13] = ctx.f[0]; ctx.ps0[13] = static_cast<float>(ctx.f[0]); // fmr f13, f0
    /* 0x800B9884 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12836)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12836(r9) [0x8016CDDC]
loc_800B9888:;
    /* 0x800B9888 */ ctx.f[1] = static_cast<float>(ctx.f[1] + ctx.f[0]); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // fadds f1, f1, f0
    /* 0x800B988C */ ctx.cmp_f64(0, ctx.f[1], ctx.f[13]); // fcmpu cr0, f1, f13
    /* 0x800B9890 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(0)); // cror 3, 2, 0
    /* 0x800B9894 */ if (ctx.eval_bc(12, 3)) goto loc_800B9888; // bc 12, 3, 0x800B9888
loc_800B9898:;
    /* 0x800B9898 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B989C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12848)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12848(r9) [0x8016CDD0]
    /* 0x800B98A0 */ ctx.cmp_f64(0, ctx.f[1], ctx.f[0]); // fcmpu cr0, f1, f0
    /* 0x800B98A4 */ if (ctx.eval_bc(4, 0)) goto loc_800B98C0; // bc 4, 0, 0x800B98C0
    /* 0x800B98A8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B98AC */ ctx.f[13] = -ctx.f[1]; ctx.ps0[13] = -ctx.ps0[1]; // fneg f13, f1
    /* 0x800B98B0 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12828)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12828(r9) [0x8016CDE4]
    /* 0x800B98B4 */ ctx.cmp_f64(0, ctx.f[13], ctx.f[0]); // fcmpu cr0, f13, f0
    /* 0x800B98B8 */ if (ctx.eval_bc(12, 1)) goto loc_800B98D0; // bc 12, 1, 0x800B98D0
    /* 0x800B98BC */ goto loc_800B9908; // b 0x800B9908 <sub_800B9908>
loc_800B98C0:;
    /* 0x800B98C0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B98C4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12828)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12828(r9) [0x8016CDE4]
    /* 0x800B98C8 */ ctx.cmp_f64(0, ctx.f[1], ctx.f[0]); // fcmpu cr0, f1, f0
    /* 0x800B98CC */ if (ctx.eval_bc(4, 1)) goto loc_800B9908; // bc 4, 1, 0x800B9908
loc_800B98D0:;
    /* 0x800B98D0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B98D4 */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800B98D8 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800B98DC */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800B98E0 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800B98E4 */ ctx.rlwinm(9, 0, 30u, 2u, 31u, true); // rlwinm r9, r0, 30, 2, 31
    /* 0x800B98E8 */ if (ctx.eval_bc(4, 2)) goto loc_800B98F8; // bc 4, 2, 0x800B98F8
    /* 0x800B98EC */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800B98F0 */ ctx.r[3] = ctx.r[3] + (-12872); // addi r3, r3, -12872 -> 0x8016CDB8 /* "vector" */
    /* 0x800B98F4 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800B98F8:;
    /* 0x800B98F8 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800B98FC */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800B9900 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800B9904 */ mem.write_u8(ctx.r[11] + (250), static_cast<uint8_t>(ctx.r[0])); // stb r0, 250(r11)
loc_800B9908:;
    /* 0x800B9908 */ ctx.r[3] = 0x0000000Au; // li r3, 10
    /* 0x800B990C */ ctx.r[4] = 0x000000C8u; // li r4, 200
    /* 0x800B9910 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9914 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800B9918 */ VibSet_800AD2F0(ctx, mem); // bl 0x800AD2F0 <VibSet(unsigned long, unsigned long, unsigned long, unsigned long)>
loc_800B991C:;
    /* 0x800B991C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[20]), 0); // cmpwi cr0, r20, 0
    /* 0x800B9920 */ if (ctx.eval_bc(4, 2)) goto loc_800B997C; // bc 4, 2, 0x800B997C
    /* 0x800B9924 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9928 */ ctx.r[30] = mem.read_u32(ctx.r[9] + (324)); // lwz r30, 324(r9)
    /* 0x800B992C */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800B9930 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (0)); // lwz r9, 0(r30)
    /* 0x800B9934 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800B9938 */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800B993C */ ctx.cmp_u32(0, ctx.r[20], ctx.r[0]); // cmplw cr0, r20, r0
loc_800B9940:;
    /* 0x800B9940 */ if (ctx.eval_bc(12, 0)) goto loc_800B9950; // bc 12, 0, 0x800B9950
    /* 0x800B9944 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800B9948 */ ctx.r[3] = ctx.r[3] + (-12872); // addi r3, r3, -12872 -> 0x8016CDB8 /* "vector" */
    /* 0x800B994C */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800B9950:;
    /* 0x800B9950 */ ctx.r[11] = mem.read_u32(ctx.r[30] + (0)); // lwz r11, 0(r30)
    /* 0x800B9954 */ ctx.r[10] = 0x801C0000u; // lis r10, 0x801C
    /* 0x800B9958 */ ctx.r[8] = ctx.r[10] + (19120); // addi r8, r10, 19120 -> pl_old.1368
    /* 0x800B995C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (0)); // lwz r9, 0(r11)
    /* 0x800B9960 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r9)
    /* 0x800B9964 */ ctx.r[9] = ctx.r[9] + (192); // addi r9, r9, 192
    /* 0x800B9968 */ mem.write_f32(ctx.r[10] + (19120), static_cast<float>(ctx.f[13])); // stfs f13, 19120(r10) [pl_old.1368]
    /* 0x800B996C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800B9970 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800B9974 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800B9978 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r8)
loc_800B997C:;
    /* 0x800B997C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (124)); // lwz r0, 124(r1)
    /* 0x800B9980 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B9984 */ ctx.lmw(mem, 20, ctx.r[1] + (64)); // lmw r20, 64(r1)
    /* 0x800B9988 */ ctx.f[31] = mem.read_f64(ctx.r[1] + (112)); // lfd f31, 112(r1)
    /* 0x800B998C */ ctx.r[1] = ctx.r[1] + (120); // addi r1, r1, 120
    /* 0x800B9990 */ return; // blr
}

// [0x800B9994] room_line_ck(cVec &, cVec &, cVec &, cVec &) (r000.obj, 40 insns / 0xA0 bytes)
void room_line_ck_800B9994(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9994 */ ctx.f[0] = mem.read_f32(ctx.r[4] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r4)
    /* 0x800B9998 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B999C */ ctx.f[5] = mem.read_f32(ctx.r[3] + (8)); ctx.ps0[5] = static_cast<float>(ctx.f[5]); // lfs f5, 8(r3)
    /* 0x800B99A0 */ ctx.f[9] = mem.read_f32(ctx.r[5] + (0)); ctx.ps0[9] = static_cast<float>(ctx.f[9]); // lfs f9, 0(r5)
    /* 0x800B99A4 */ ctx.f[13] = mem.read_f32(ctx.r[6] + (0)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 0(r6)
    /* 0x800B99A8 */ ctx.f[4] = static_cast<float>(ctx.f[0] - ctx.f[5]); ctx.ps0[4] = static_cast<float>(ctx.f[4]); // fsubs f4, f0, f5
    /* 0x800B99AC */ ctx.f[12] = mem.read_f32(ctx.r[4] + (0)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 0(r4)
    /* 0x800B99B0 */ ctx.f[10] = mem.read_f32(ctx.r[3] + (0)); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // lfs f10, 0(r3)
    /* 0x800B99B4 */ ctx.f[13] = static_cast<float>(ctx.f[13] - ctx.f[9]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // fsubs f13, f13, f9
    /* 0x800B99B8 */ ctx.f[7] = mem.read_f32(ctx.r[5] + (8)); ctx.ps0[7] = static_cast<float>(ctx.f[7]); // lfs f7, 8(r5)
    /* 0x800B99BC */ ctx.f[0] = static_cast<float>(ctx.f[4] * ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f4, f13
    /* 0x800B99C0 */ ctx.f[11] = mem.read_f32(ctx.r[6] + (8)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 8(r6)
    /* 0x800B99C4 */ ctx.f[6] = static_cast<float>(ctx.f[12] - ctx.f[10]); ctx.ps0[6] = static_cast<float>(ctx.f[6]); // fsubs f6, f12, f10
    /* 0x800B99C8 */ ctx.f[8] = mem.read_f32(ctx.r[9] + (-12824)); ctx.ps0[8] = static_cast<float>(ctx.f[8]); // lfs f8, -12824(r9) [0x8016CDE8]
    /* 0x800B99CC */ ctx.f[11] = static_cast<float>(ctx.f[11] - ctx.f[7]); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // fsubs f11, f11, f7
    /* 0x800B99D0 */ ctx.f[12] = static_cast<float>(ctx.f[6] * ctx.f[11] - ctx.f[0]); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // fmsubs f12, f6, f11, f0
    /* 0x800B99D4 */ ctx.cmp_f64(0, ctx.f[12], ctx.f[8]); // fcmpu cr0, f12, f8
    /* 0x800B99D8 */ if (ctx.eval_bc(4, 2)) goto loc_800B99E4; // bc 4, 2, 0x800B99E4
loc_800B99DC:;
    /* 0x800B99DC */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B99E0 */ return; // blr
loc_800B99E4:;
    /* 0x800B99E4 */ ctx.f[9] = static_cast<float>(ctx.f[10] - ctx.f[9]); ctx.ps0[9] = static_cast<float>(ctx.f[9]); // fsubs f9, f10, f9
    /* 0x800B99E8 */ ctx.f[10] = static_cast<float>(ctx.f[5] - ctx.f[7]); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // fsubs f10, f5, f7
    /* 0x800B99EC */ ctx.f[0] = static_cast<float>(ctx.f[9] * ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f9, f11
    /* 0x800B99F0 */ ctx.f[0] = static_cast<float>(ctx.f[10] * ctx.f[13] - ctx.f[0]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmsubs f0, f10, f13, f0
    /* 0x800B99F4 */ ctx.f[0] = static_cast<float>(ctx.f[0] / ctx.f[12]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fdivs f0, f0, f12
    /* 0x800B99F8 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[8]); // fcmpu cr0, f0, f8
    /* 0x800B99FC */ if (ctx.eval_bc(12, 0)) goto loc_800B99DC; // bc 12, 0, 0x800B99DC
    /* 0x800B9A00 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B9A04 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12820)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12820(r9) [0x8016CDEC]
    /* 0x800B9A08 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[13]); // fcmpu cr0, f0, f13
    /* 0x800B9A0C */ if (ctx.eval_bc(12, 1)) goto loc_800B99DC; // bc 12, 1, 0x800B99DC
    /* 0x800B9A10 */ ctx.f[0] = static_cast<float>(ctx.f[9] * ctx.f[4]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f9, f4
    /* 0x800B9A14 */ ctx.f[0] = static_cast<float>(ctx.f[10] * ctx.f[6] - ctx.f[0]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmsubs f0, f10, f6, f0
    /* 0x800B9A18 */ ctx.f[0] = static_cast<float>(ctx.f[0] / ctx.f[12]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fdivs f0, f0, f12
    /* 0x800B9A1C */ ctx.cmp_f64(0, ctx.f[0], ctx.f[8]); // fcmpu cr0, f0, f8
    /* 0x800B9A20 */ if (ctx.eval_bc(12, 0)) goto loc_800B99DC; // bc 12, 0, 0x800B99DC
    /* 0x800B9A24 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[13]); // fcmpu cr0, f0, f13
    /* 0x800B9A28 */ if (ctx.eval_bc(12, 1)) goto loc_800B99DC; // bc 12, 1, 0x800B99DC
    /* 0x800B9A2C */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800B9A30 */ return; // blr
}

// [0x800B9A34] pl_damage(cEm *) (r000.obj, 58 insns / 0xE8 bytes)
void pl_damage_800B9A34(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9A34 */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800B9A38 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800B9A3C */ mem.write_u32(ctx.r[1] + (12), ctx.r[31]); // stw r31, 12(r1)
    /* 0x800B9A40 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800B9A44 */ ctx.r[31] = ctx.r[3]; // mr r31, r3
    /* 0x800B9A48 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (250)); // lbz r0, 250(r31)
    /* 0x800B9A4C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 1); // cmpwi cr0, r0, 1
    /* 0x800B9A50 */ if (ctx.eval_bc(12, 2)) goto loc_800B9AA8; // bc 12, 2, 0x800B9AA8
    /* 0x800B9A54 */ if (ctx.eval_bc(12, 1)) goto loc_800B9A64; // bc 12, 1, 0x800B9A64
    /* 0x800B9A58 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800B9A5C */ if (ctx.eval_bc(12, 2)) goto loc_800B9A70; // bc 12, 2, 0x800B9A70
    /* 0x800B9A60 */ goto loc_800B9B08; // b 0x800B9B08 <sub_800B9B08>
loc_800B9A64:;
    /* 0x800B9A64 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 2); // cmpwi cr0, r0, 2
    /* 0x800B9A68 */ if (ctx.eval_bc(12, 2)) goto loc_800B9ADC; // bc 12, 2, 0x800B9ADC
    /* 0x800B9A6C */ goto loc_800B9B08; // b 0x800B9B08 <sub_800B9B08>
loc_800B9A70:;
    /* 0x800B9A70 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9A74 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800B9A78 */ ctx.r[4] = ctx.r[31] + (380); // addi r4, r31, 380
    /* 0x800B9A7C */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800B9A80 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (280)); // lwz r11, 280(r9)
    /* 0x800B9A84 */ ctx.r[7] = 0x00000005u; // li r7, 5
    /* 0x800B9A88 */ ctx.r[8] = 0x00000005u; // li r8, 5
    /* 0x800B9A8C */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800B9A90 */ ctx.r[5] = mem.read_u32(ctx.r[11] + (96)); // lwz r5, 96(r11)
    /* 0x800B9A94 */ ctx.r[5] = ctx.r[5] + ctx.r[11]; // add r5, r5, r11
    /* 0x800B9A98 */ MotionSetCore_800A1E20(ctx, mem); // bl 0x800A1E20 <MotionSetCore(cEm *, _MOTION_INFO *, void *, void *, unsigned char, unsigned short, unsigned short)>
    /* 0x800B9A9C */ ctx.r[0] = 0x00000002u; // li r0, 2
    /* 0x800B9AA0 */ mem.write_u8(ctx.r[31] + (250), static_cast<uint8_t>(ctx.r[0])); // stb r0, 250(r31)
    /* 0x800B9AA4 */ goto loc_800B9B08; // b 0x800B9B08 <sub_800B9B08>
loc_800B9AA8:;
    /* 0x800B9AA8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9AAC */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800B9AB0 */ ctx.r[4] = ctx.r[31] + (380); // addi r4, r31, 380
    /* 0x800B9AB4 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800B9AB8 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (280)); // lwz r11, 280(r9)
    /* 0x800B9ABC */ ctx.r[7] = 0x00000005u; // li r7, 5
    /* 0x800B9AC0 */ ctx.r[8] = 0x00000005u; // li r8, 5
    /* 0x800B9AC4 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800B9AC8 */ ctx.r[5] = mem.read_u32(ctx.r[11] + (84)); // lwz r5, 84(r11)
    /* 0x800B9ACC */ ctx.r[5] = ctx.r[5] + ctx.r[11]; // add r5, r5, r11
    /* 0x800B9AD0 */ MotionSetCore_800A1E20(ctx, mem); // bl 0x800A1E20 <MotionSetCore(cEm *, _MOTION_INFO *, void *, void *, unsigned char, unsigned short, unsigned short)>
    /* 0x800B9AD4 */ ctx.r[0] = 0x00000002u; // li r0, 2
    /* 0x800B9AD8 */ mem.write_u8(ctx.r[31] + (250), static_cast<uint8_t>(ctx.r[0])); // stb r0, 250(r31)
loc_800B9ADC:;
    /* 0x800B9ADC */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B9AE0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800B9AE4 */ ctx.f[1] = mem.read_f32(ctx.r[9] + (-12816)); ctx.ps0[1] = static_cast<float>(ctx.f[1]); // lfs f1, -12816(r9) [0x8016CDF0]
    /* 0x800B9AE8 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800B9AEC */ ctx.f[2] = mem.read_f32(ctx.r[11] + (-12812)); ctx.ps0[2] = static_cast<float>(ctx.f[2]); // lfs f2, -12812(r11) [0x8016CDF4]
    /* 0x800B9AF0 */ MotionMove_800A2434(ctx, mem); // bl 0x800A2434 <MotionMove(cEm *, float, float)>
    /* 0x800B9AF4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800B9AF8 */ if (ctx.eval_bc(12, 2)) goto loc_800B9B08; // bc 12, 2, 0x800B9B08
    /* 0x800B9AFC */ EndPlDamage_800CF4DC(ctx, mem); // bl 0x800CF4DC <EndPlDamage(void)>
    /* 0x800B9B00 */ ctx.r[0] = 0x0000001Eu; // li r0, 30
    /* 0x800B9B04 */ mem.write_u8(ctx.r[31] + (1249), static_cast<uint8_t>(ctx.r[0])); // stb r0, 1249(r31)
loc_800B9B08:;
    /* 0x800B9B08 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800B9B0C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B9B10 */ ctx.r[31] = mem.read_u32(ctx.r[1] + (12)); // lwz r31, 12(r1)
    /* 0x800B9B14 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800B9B18 */ return; // blr
}

// [0x800B9B1C] R101Init(void) (r101.obj, 1 insns / 0x4 bytes)
void R101Init_800B9B1C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9B1C */ return; // blr
}

// [0x800B9B20] R101Main(void) (r101.obj, 17 insns / 0x44 bytes)
void R101Main_800B9B20(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9B20 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800B9B24 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800B9B28 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800B9B2C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9B30 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800B9B34 */ ctx.r[11] = ctx.r[0] & 0x04000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0400
    /* 0x800B9B38 */ if (ctx.eval_bc(4, 2)) goto loc_800B9B54; // bc 4, 2, 0x800B9B54
    /* 0x800B9B3C */ ctx.r[0] = ctx.r[0] | 0x04000000u; // oris r0, r0, 0x0400
    /* 0x800B9B40 */ ctx.r[3] = 0x00000002u; // li r3, 2
    /* 0x800B9B44 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800B9B48 */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800B9B4C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9B50 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
loc_800B9B54:;
    /* 0x800B9B54 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800B9B58 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B9B5C */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800B9B60 */ return; // blr
}

// [0x800B9B64] R103Init(void) (r103.obj, 5 insns / 0x14 bytes)
void R103Init_800B9B64(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9B64 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800B9B68 */ ctx.r[9] = 0x0000001Eu; // li r9, 30
    /* 0x800B9B6C */ mem.write_u32(ctx.r[13] + (-29708), ctx.r[0]); // stw r0, -29708(r13) [{anonymous}::pEvent30]
    /* 0x800B9B70 */ mem.write_u32(ctx.r[13] + (-29704), ctx.r[9]); // stw r9, -29704(r13) [{anonymous}::demoWaitTimer]
    /* 0x800B9B74 */ return; // blr
}

// [0x800B9B78] R103Main(void) (r103.obj, 85 insns / 0x154 bytes)
void R103Main_800B9B78(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9B78 */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800B9B7C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800B9B80 */ mem.write_u32(ctx.r[1] + (12), ctx.r[31]); // stw r31, 12(r1)
    /* 0x800B9B84 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800B9B88 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9B8C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800B9B90 */ ctx.r[11] = ctx.r[0] & 0x02000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0200
    /* 0x800B9B94 */ if (ctx.eval_bc(4, 2)) goto loc_800B9BB0; // bc 4, 2, 0x800B9BB0
    /* 0x800B9B98 */ ctx.r[0] = ctx.r[0] | 0x02000000u; // oris r0, r0, 0x0200
    /* 0x800B9B9C */ ctx.r[3] = 0x00000003u; // li r3, 3
    /* 0x800B9BA0 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800B9BA4 */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800B9BA8 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9BAC */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
loc_800B9BB0:;
    /* 0x800B9BB0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9BB4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800B9BB8 */ ctx.r[9] = ctx.r[0] & 0x0002u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0002
    /* 0x800B9BBC */ if (ctx.eval_bc(4, 2)) goto loc_800B9C70; // bc 4, 2, 0x800B9C70
    /* 0x800B9BC0 */ AreaDoorEmCheck_80003F90(ctx, mem); // bl 0x80003F90 <AreaDoorEmCheck(void)>
    /* 0x800B9BC4 */ ctx.r[3] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // mr r3, r3
    /* 0x800B9BC8 */ if (ctx.eval_bc(4, 2)) goto loc_800B9C70; // bc 4, 2, 0x800B9C70
    /* 0x800B9BCC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9BD0 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (336)); // lwz r0, 336(r11)
    /* 0x800B9BD4 */ ctx.r[31] = mem.read_u32(ctx.r[11] + (324)); // lwz r31, 324(r11)
    /* 0x800B9BD8 */ ctx.r[0] = ctx.r[0] | 0x00010000u; // oris r0, r0, 0x0001
    /* 0x800B9BDC */ mem.write_u32(ctx.r[11] + (336), ctx.r[0]); // stw r0, 336(r11)
    /* 0x800B9BE0 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (4)); // lwz r9, 4(r31)
    /* 0x800B9BE4 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (0)); // lwz r0, 0(r31)
    /* 0x800B9BE8 */ ctx.r[9] = ctx.r[9] - ctx.r[0]; // subf r9, r0, r9
    /* 0x800B9BEC */ ctx.r[9] = ctx.srawi_op(ctx.r[9], 2u, false); // srawi r9, r9, 2
    /* 0x800B9BF0 */ ctx.cmp_u32(0, ctx.r[3], ctx.r[9]); // cmplw cr0, r3, r9
    /* 0x800B9BF4 */ if (ctx.eval_bc(12, 0)) goto loc_800B9C04; // bc 12, 0, 0x800B9C04
    /* 0x800B9BF8 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800B9BFC */ ctx.r[3] = ctx.r[3] + (-12776); // addi r3, r3, -12776 -> 0x8016CE18 /* "vector" */
    /* 0x800B9C00 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800B9C04:;
    /* 0x800B9C04 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800B9C08 */ ctx.r[0] = 0x00000080u; // li r0, 128
    /* 0x800B9C0C */ ctx.r[11] = mem.read_u32(ctx.r[9] + (0)); // lwz r11, 0(r9)
    /* 0x800B9C10 */ mem.write_u8(ctx.r[11] + (1249), static_cast<uint8_t>(ctx.r[0])); // stb r0, 1249(r11)
    /* 0x800B9C14 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29704)); // lwz r9, -29704(r13) [{anonymous}::demoWaitTimer]
    /* 0x800B9C18 */ ctx.r[9] = ctx.r[9] + (-1); // addi r9, r9, -1
    /* 0x800B9C1C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), -1); // cmpwi cr0, r9, -1
    /* 0x800B9C20 */ mem.write_u32(ctx.r[13] + (-29704), ctx.r[9]); // stw r9, -29704(r13) [{anonymous}::demoWaitTimer]
    /* 0x800B9C24 */ if (ctx.eval_bc(4, 2)) goto loc_800B9C70; // bc 4, 2, 0x800B9C70
    /* 0x800B9C28 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9C2C */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800B9C30 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (336)); // lwz r0, 336(r11)
    /* 0x800B9C34 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (29012)); // lwz r9, 29012(r11)
    /* 0x800B9C38 */ ctx.rlwinm(0, 0, 0u, 16u, 14u, false); // rlwinm r0, r0, 0, 16, 14
    /* 0x800B9C3C */ ctx.r[9] = ctx.r[9] | 0x0002u; // ori r9, r9, 0x0002
    /* 0x800B9C40 */ mem.write_u32(ctx.r[11] + (336), ctx.r[0]); // stw r0, 336(r11)
    /* 0x800B9C44 */ mem.write_u32(ctx.r[11] + (29012), ctx.r[9]); // stw r9, 29012(r11)
    /* 0x800B9C48 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800B9C4C */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800B9C50 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9C54 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800B9C58 */ mem.write_u32(ctx.r[13] + (-29708), ctx.r[0]); // stw r0, -29708(r13) [{anonymous}::pEvent30]
    /* 0x800B9C5C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800B9C60 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9C64 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (44)); // lwz r4, 44(r9)
    /* 0x800B9C68 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800B9C6C */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
loc_800B9C70:;
    /* 0x800B9C70 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29708)); // lwz r3, -29708(r13) [{anonymous}::pEvent30]
    /* 0x800B9C74 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800B9C78 */ if (ctx.eval_bc(12, 2)) goto loc_800B9CB8; // bc 12, 2, 0x800B9CB8
    /* 0x800B9C7C */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800B9C80 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800B9C84 */ if (ctx.eval_bc(12, 2)) goto loc_800B9CB8; // bc 12, 2, 0x800B9CB8
    /* 0x800B9C88 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29708)); // lwz r11, -29708(r13) [{anonymous}::pEvent30]
    /* 0x800B9C8C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800B9C90 */ if (ctx.eval_bc(12, 2)) goto loc_800B9CB0; // bc 12, 2, 0x800B9CB0
    /* 0x800B9C94 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800B9C98 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800B9C9C */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800B9CA0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800B9CA4 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800B9CA8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B9CAC */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800B9CB0:;
    /* 0x800B9CB0 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800B9CB4 */ mem.write_u32(ctx.r[13] + (-29708), ctx.r[0]); // stw r0, -29708(r13) [{anonymous}::pEvent30]
loc_800B9CB8:;
    /* 0x800B9CB8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800B9CBC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B9CC0 */ ctx.r[31] = mem.read_u32(ctx.r[1] + (12)); // lwz r31, 12(r1)
    /* 0x800B9CC4 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800B9CC8 */ return; // blr
}

// [0x800B9CCC] R104Init(void) (r104.obj, 5 insns / 0x14 bytes)
void R104Init_800B9CCC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9CCC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9CD0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (300)); // lwz r0, 300(r9)
    /* 0x800B9CD4 */ ctx.r[0] = ctx.r[0] | 0x1000u; // ori r0, r0, 0x1000
    /* 0x800B9CD8 */ mem.write_u32(ctx.r[9] + (300), ctx.r[0]); // stw r0, 300(r9)
    /* 0x800B9CDC */ return; // blr
}

// [0x800B9CE0] R104Main(void) (r104.obj, 1 insns / 0x4 bytes)
void R104Main_800B9CE0(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9CE0 */ return; // blr
}

// [0x800B9CE4] R107Init(void) (r107.obj, 1 insns / 0x4 bytes)
void R107Init_800B9CE4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9CE4 */ return; // blr
}

// [0x800B9CE8] R107Main(void) (r107.obj, 33 insns / 0x84 bytes)
void R107Main_800B9CE8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9CE8 */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800B9CEC */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800B9CF0 */ mem.write_u32(ctx.r[1] + (12), ctx.r[31]); // stw r31, 12(r1)
    /* 0x800B9CF4 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800B9CF8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9CFC */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800B9D00 */ ctx.r[11] = ctx.r[0] & 0x8000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andi. r11, r0, 0x8000
    /* 0x800B9D04 */ if (ctx.eval_bc(12, 2)) goto loc_800B9D58; // bc 12, 2, 0x800B9D58
    /* 0x800B9D08 */ ctx.r[31] = ctx.r[0] & 0x00800000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // andis. r31, r0, 0x0080
    /* 0x800B9D0C */ if (ctx.eval_bc(4, 2)) goto loc_800B9D58; // bc 4, 2, 0x800B9D58
    /* 0x800B9D10 */ ctx.r[0] = ctx.r[0] | 0x00800000u; // oris r0, r0, 0x0080
    /* 0x800B9D14 */ ctx.r[3] = 0x00000005u; // li r3, 5
    /* 0x800B9D18 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800B9D1C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800B9D20 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9D24 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
    /* 0x800B9D28 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9D2C */ ctx.r[9] = 0x00000004u; // li r9, 4
    /* 0x800B9D30 */ mem.write_u8(ctx.r[11] + (260), static_cast<uint8_t>(ctx.r[9])); // stb r9, 260(r11)
    /* 0x800B9D34 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (328)); // lwz r0, 328(r11)
    /* 0x800B9D38 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800B9D3C */ ctx.r[0] = ctx.r[0] | 0x0008u; // ori r0, r0, 0x0008
    /* 0x800B9D40 */ mem.write_u32(ctx.r[11] + (328), ctx.r[0]); // stw r0, 328(r11)
    /* 0x800B9D44 */ mem.write_u8(ctx.r[10] + (261), static_cast<uint8_t>(ctx.r[31])); // stb r31, 261(r10)
    /* 0x800B9D48 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9D4C */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[31])); // stb r31, 262(r9)
    /* 0x800B9D50 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9D54 */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[31])); // stb r31, 263(r11)
loc_800B9D58:;
    /* 0x800B9D58 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800B9D5C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B9D60 */ ctx.r[31] = mem.read_u32(ctx.r[1] + (12)); // lwz r31, 12(r1)
    /* 0x800B9D64 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800B9D68 */ return; // blr
}

// [0x800B9D6C] R111Init(void) (r111.obj, 1 insns / 0x4 bytes)
void R111Init_800B9D6C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9D6C */ return; // blr
}

// [0x800B9D70] R111Main(void) (r111.obj, 17 insns / 0x44 bytes)
void R111Main_800B9D70(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9D70 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800B9D74 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800B9D78 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800B9D7C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9D80 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800B9D84 */ ctx.r[11] = ctx.r[0] & 0x01000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0100
    /* 0x800B9D88 */ if (ctx.eval_bc(4, 2)) goto loc_800B9DA4; // bc 4, 2, 0x800B9DA4
    /* 0x800B9D8C */ ctx.r[0] = ctx.r[0] | 0x01000000u; // oris r0, r0, 0x0100
    /* 0x800B9D90 */ ctx.r[3] = 0x00000004u; // li r3, 4
    /* 0x800B9D94 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800B9D98 */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800B9D9C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9DA0 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
loc_800B9DA4:;
    /* 0x800B9DA4 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800B9DA8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B9DAC */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800B9DB0 */ return; // blr
}

// [0x800B9DB4] R113Init(void) (r113.obj, 30 insns / 0x78 bytes)
void R113Init_800B9DB4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9DB4 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800B9DB8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800B9DBC */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800B9DC0 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800B9DC4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9DC8 */ mem.write_u32(ctx.r[13] + (-32264), ctx.r[0]); // stw r0, -32264(r13) [pEvent03]
    /* 0x800B9DCC */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800B9DD0 */ ctx.r[11] = ctx.r[0] & 0x10000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x1000
    /* 0x800B9DD4 */ if (ctx.eval_bc(4, 2)) goto loc_800B9E1C; // bc 4, 2, 0x800B9E1C
    /* 0x800B9DD8 */ ctx.r[0] = ctx.r[0] | 0x10000000u; // oris r0, r0, 0x1000
    /* 0x800B9DDC */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800B9DE0 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800B9DE4 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800B9DE8 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800B9DEC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9DF0 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800B9DF4 */ mem.write_u32(ctx.r[13] + (-32264), ctx.r[0]); // stw r0, -32264(r13) [pEvent03]
    /* 0x800B9DF8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800B9DFC */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9E00 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (48)); // lwz r4, 48(r9)
    /* 0x800B9E04 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800B9E08 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800B9E0C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9E10 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800B9E14 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800B9E18 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
loc_800B9E1C:;
    /* 0x800B9E1C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800B9E20 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B9E24 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800B9E28 */ return; // blr
}

// [0x800B9E2C] R113Main(void) (r113.obj, 103 insns / 0x19C bytes)
void R113Main_800B9E2C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9E2C */ ctx.r[1] += (-80); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -80(r1)
    /* 0x800B9E30 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800B9E34 */ mem.write_u32(ctx.r[1] + (76), ctx.r[31]); // stw r31, 76(r1)
    /* 0x800B9E38 */ mem.write_u32(ctx.r[1] + (84), ctx.r[0]); // stw r0, 84(r1)
    /* 0x800B9E3C */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-32264)); // lwz r3, -32264(r13) [pEvent03]
    /* 0x800B9E40 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800B9E44 */ if (ctx.eval_bc(12, 2)) goto loc_800B9F24; // bc 12, 2, 0x800B9F24
    /* 0x800B9E48 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800B9E4C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800B9E50 */ if (ctx.eval_bc(12, 2)) goto loc_800B9F24; // bc 12, 2, 0x800B9F24
    /* 0x800B9E54 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-32264)); // lwz r11, -32264(r13) [pEvent03]
    /* 0x800B9E58 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800B9E5C */ if (ctx.eval_bc(12, 2)) goto loc_800B9E7C; // bc 12, 2, 0x800B9E7C
    /* 0x800B9E60 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800B9E64 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800B9E68 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800B9E6C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800B9E70 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800B9E74 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B9E78 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800B9E7C:;
    /* 0x800B9E7C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B9E80 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800B9E84 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12712)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12712(r9) [0x8016CE58]
    /* 0x800B9E88 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800B9E8C */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-12708)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12708(r11) [0x8016CE5C]
    /* 0x800B9E90 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B9E94 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800B9E98 */ ctx.r[11] = ctx.r[1] + (8); // addi r11, r1, 8
    /* 0x800B9E9C */ ctx.f[12] = mem.read_f32(ctx.r[10] + (-12704)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12704(r10) [0x8016CE60]
    /* 0x800B9EA0 */ ctx.r[7] = ctx.r[1] + (24); // addi r7, r1, 24
    /* 0x800B9EA4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12700)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12700(r9) [0x8016CE64]
    /* 0x800B9EA8 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800B9EAC */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r11)
    /* 0x800B9EB0 */ ctx.r[8] = ctx.r[1] + (40); // addi r8, r1, 40
    /* 0x800B9EB4 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r11)
    /* 0x800B9EB8 */ ctx.r[6] = ctx.r[1] + (56); // addi r6, r1, 56
    /* 0x800B9EBC */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800B9EC0 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800B9EC4 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r7)
    /* 0x800B9EC8 */ ctx.r[3] = ctx.r[8]; // mr r3, r8
    /* 0x800B9ECC */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800B9ED0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9ED4 */ mem.write_u32(ctx.r[13] + (-32264), ctx.r[0]); // stw r0, -32264(r13) [pEvent03]
    /* 0x800B9ED8 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (8)); // lwz r9, 8(r1)
    /* 0x800B9EDC */ ctx.r[0] = mem.read_u32(ctx.r[11] + (4)); // lwz r0, 4(r11)
    /* 0x800B9EE0 */ ctx.r[10] = mem.read_u32(ctx.r[11] + (8)); // lwz r10, 8(r11)
    /* 0x800B9EE4 */ mem.write_u32(ctx.r[1] + (40), ctx.r[9]); // stw r9, 40(r1)
    /* 0x800B9EE8 */ mem.write_u32(ctx.r[8] + (4), ctx.r[0]); // stw r0, 4(r8)
    /* 0x800B9EEC */ mem.write_u32(ctx.r[8] + (8), ctx.r[10]); // stw r10, 8(r8)
    /* 0x800B9EF0 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (24)); // lwz r9, 24(r1)
    /* 0x800B9EF4 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800B9EF8 */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800B9EFC */ mem.write_u32(ctx.r[1] + (56), ctx.r[9]); // stw r9, 56(r1)
    /* 0x800B9F00 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800B9F04 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800B9F08 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800B9F0C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B9F10 */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800B9F14 */ ctx.r[5] = 0x00000002u; // li r5, 2
    /* 0x800B9F18 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800B9F1C */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800B9F20 */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
loc_800B9F24:;
    /* 0x800B9F24 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9F28 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800B9F2C */ ctx.r[11] = ctx.r[0] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x4000
    /* 0x800B9F30 */ if (ctx.eval_bc(12, 2)) goto loc_800B9FB4; // bc 12, 2, 0x800B9FB4
    /* 0x800B9F34 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800B9F38 */ ctx.r[31] = ctx.r[0] & 0x00800000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // andis. r31, r0, 0x0080
    /* 0x800B9F3C */ if (ctx.eval_bc(4, 2)) goto loc_800B9FB4; // bc 4, 2, 0x800B9FB4
    /* 0x800B9F40 */ ctx.r[0] = ctx.r[0] | 0x00800000u; // oris r0, r0, 0x0080
    /* 0x800B9F44 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800B9F48 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800B9F4C */ ctx.r[4] = 0x000000C8u; // li r4, 200
    /* 0x800B9F50 */ Snd_str_fadeout_800CD394(ctx, mem); // bl 0x800CD394 <Snd_str_fadeout(long, long)>
    /* 0x800B9F54 */ ctx.r[3] = 0x00000005u; // li r3, 5
    /* 0x800B9F58 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800B9F5C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9F60 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
    /* 0x800B9F64 */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800B9F68 */ ctx.r[4] = 0x00000040u; // li r4, 64
    /* 0x800B9F6C */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800B9F70 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800B9F74 */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800B9F78 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9F7C */ ctx.r[0] = 0x00000004u; // li r0, 4
    /* 0x800B9F80 */ mem.write_u8(ctx.r[11] + (260), static_cast<uint8_t>(ctx.r[0])); // stb r0, 260(r11)
    /* 0x800B9F84 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (332)); // lwz r9, 332(r11)
    /* 0x800B9F88 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (328)); // lwz r0, 328(r11)
    /* 0x800B9F8C */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800B9F90 */ ctx.r[9] = ctx.r[9] | 0x08000000u; // oris r9, r9, 0x0800
    /* 0x800B9F94 */ ctx.r[0] = ctx.r[0] | 0x0008u; // ori r0, r0, 0x0008
    /* 0x800B9F98 */ mem.write_u32(ctx.r[11] + (332), ctx.r[9]); // stw r9, 332(r11)
    /* 0x800B9F9C */ mem.write_u32(ctx.r[11] + (328), ctx.r[0]); // stw r0, 328(r11)
    /* 0x800B9FA0 */ mem.write_u8(ctx.r[10] + (261), static_cast<uint8_t>(ctx.r[31])); // stb r31, 261(r10)
    /* 0x800B9FA4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800B9FA8 */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[31])); // stb r31, 262(r9)
    /* 0x800B9FAC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800B9FB0 */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[31])); // stb r31, 263(r11)
loc_800B9FB4:;
    /* 0x800B9FB4 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (84)); // lwz r0, 84(r1)
    /* 0x800B9FB8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800B9FBC */ ctx.r[31] = mem.read_u32(ctx.r[1] + (76)); // lwz r31, 76(r1)
    /* 0x800B9FC0 */ ctx.r[1] = ctx.r[1] + (80); // addi r1, r1, 80
    /* 0x800B9FC4 */ return; // blr
}

// [0x800B9FC8] R20aInit(void) (r20a.obj, 3 insns / 0xC bytes)
void R20aInit_800B9FC8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9FC8 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800B9FCC */ mem.write_u32(ctx.r[13] + (-29700), ctx.r[0]); // stw r0, -29700(r13) [pEvent04]
    /* 0x800B9FD0 */ return; // blr
}

// [0x800B9FD4] R20aMain(void) (r20a.obj, 124 insns / 0x1F0 bytes)
void R20aMain_800B9FD4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800B9FD4 */ ctx.r[1] += (-64); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -64(r1)
    /* 0x800B9FD8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800B9FDC */ ctx.stmw(mem, 30, ctx.r[1] + (56)); // stmw r30, 56(r1)
    /* 0x800B9FE0 */ mem.write_u32(ctx.r[1] + (68), ctx.r[0]); // stw r0, 68(r1)
    /* 0x800B9FE4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800B9FE8 */ ctx.r[30] = ctx.r[1] + (8); // addi r30, r1, 8
    /* 0x800B9FEC */ ctx.r[7] = mem.read_u32(ctx.r[9] + (-12676)); // lwz r7, -12676(r9) [0x8016CE7C]
    /* 0x800B9FF0 */ ctx.r[31] = ctx.r[1] + (32); // addi r31, r1, 32
    /* 0x800B9FF4 */ ctx.r[9] = ctx.r[9] + (-12676); // addi r9, r9, -12676 -> 0x8016CE7C
    /* 0x800B9FF8 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800B9FFC */ ctx.r[11] = mem.read_u32(ctx.r[9] + (12)); // lwz r11, 12(r9)
    /* 0x800BA000 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BA004 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (16)); // lwz r0, 16(r9)
    /* 0x800BA008 */ ctx.r[5] = 0x00000018u; // li r5, 24
    /* 0x800BA00C */ ctx.r[6] = mem.read_u32(ctx.r[9] + (20)); // lwz r6, 20(r9)
    /* 0x800BA010 */ ctx.r[8] = mem.read_u32(ctx.r[9] + (4)); // lwz r8, 4(r9)
    /* 0x800BA014 */ ctx.r[10] = mem.read_u32(ctx.r[9] + (8)); // lwz r10, 8(r9)
    /* 0x800BA018 */ mem.write_u32(ctx.r[1] + (8), ctx.r[7]); // stw r7, 8(r1)
    /* 0x800BA01C */ mem.write_u32(ctx.r[30] + (12), ctx.r[11]); // stw r11, 12(r30)
    /* 0x800BA020 */ mem.write_u32(ctx.r[30] + (16), ctx.r[0]); // stw r0, 16(r30)
    /* 0x800BA024 */ mem.write_u32(ctx.r[30] + (4), ctx.r[8]); // stw r8, 4(r30)
    /* 0x800BA028 */ mem.write_u32(ctx.r[30] + (8), ctx.r[10]); // stw r10, 8(r30)
    /* 0x800BA02C */ mem.write_u32(ctx.r[30] + (20), ctx.r[6]); // stw r6, 20(r30)
    /* 0x800BA030 */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800BA034 */ ctx.call_indirect(0x800E8A5Cu, mem); // bl 0x800E8A5C <memset>
    /* 0x800BA038 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA03C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800BA040 */ ctx.r[11] = ctx.r[0] & 0x00400000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0040
    /* 0x800BA044 */ if (ctx.eval_bc(4, 2)) goto loc_800BA064; // bc 4, 2, 0x800BA064
    /* 0x800BA048 */ ctx.r[0] = ctx.r[0] | 0x00400000u; // oris r0, r0, 0x0040
    /* 0x800BA04C */ ctx.r[3] = 0x00000007u; // li r3, 7
    /* 0x800BA050 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800BA054 */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800BA058 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA05C */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
    /* 0x800BA060 */ goto loc_800BA1B0; // b 0x800BA1B0 <sub_800BA1B0>
loc_800BA064:;
    /* 0x800BA064 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29700)); // lwz r3, -29700(r13) [pEvent04]
    /* 0x800BA068 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BA06C */ if (ctx.eval_bc(4, 2)) goto loc_800BA108; // bc 4, 2, 0x800BA108
    /* 0x800BA070 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BA074 */ ctx.r[11] = ctx.r[0] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x4000
    /* 0x800BA078 */ if (ctx.eval_bc(12, 2)) goto loc_800BA1B0; // bc 12, 2, 0x800BA1B0
    /* 0x800BA07C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BA080 */ ctx.r[11] = ctx.r[0] & 0x08000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0800
    /* 0x800BA084 */ if (ctx.eval_bc(4, 2)) goto loc_800BA1B0; // bc 4, 2, 0x800BA1B0
    /* 0x800BA088 */ ctx.r[0] = ctx.r[0] | 0x08000000u; // oris r0, r0, 0x0800
    /* 0x800BA08C */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BA090 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BA094 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BA098 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BA09C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA0A0 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BA0A4 */ mem.write_u32(ctx.r[13] + (-29700), ctx.r[0]); // stw r0, -29700(r13) [pEvent04]
    /* 0x800BA0A8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BA0AC */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BA0B0 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (56)); // lwz r4, 56(r9)
    /* 0x800BA0B4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BA0B8 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BA0BC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA0C0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800BA0C4 */ ctx.r[9] = ctx.r[0] & 0x2000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x2000
    /* 0x800BA0C8 */ if (ctx.eval_bc(4, 2)) goto loc_800BA0E0; // bc 4, 2, 0x800BA0E0
    /* 0x800BA0CC */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800BA0D0 */ ctx.r[4] = ctx.r[31]; // mr r4, r31
    /* 0x800BA0D4 */ ctx.r[5] = 0x00000003u; // li r5, 3
    /* 0x800BA0D8 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BA0DC */ SetEm33Sce_800485DC(ctx, mem); // bl 0x800485DC <SetEm33Sce(Vec &, Vec &, unsigned long, unsigned long)>
loc_800BA0E0:;
    /* 0x800BA0E0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA0E4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800BA0E8 */ ctx.r[9] = ctx.r[0] & 0x1000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x1000
    /* 0x800BA0EC */ if (ctx.eval_bc(4, 2)) goto loc_800BA1B0; // bc 4, 2, 0x800BA1B0
    /* 0x800BA0F0 */ ctx.r[3] = ctx.r[1] + (20); // addi r3, r1, 20
    /* 0x800BA0F4 */ ctx.r[4] = ctx.r[1] + (44); // addi r4, r1, 44
    /* 0x800BA0F8 */ ctx.r[5] = 0x00000003u; // li r5, 3
    /* 0x800BA0FC */ ctx.r[6] = 0x00000001u; // li r6, 1
    /* 0x800BA100 */ SetEm33Sce_800485DC(ctx, mem); // bl 0x800485DC <SetEm33Sce(Vec &, Vec &, unsigned long, unsigned long)>
    /* 0x800BA104 */ goto loc_800BA1B0; // b 0x800BA1B0 <sub_800BA1B0>
loc_800BA108:;
    /* 0x800BA108 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BA10C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BA110 */ if (ctx.eval_bc(12, 2)) goto loc_800BA1B0; // bc 12, 2, 0x800BA1B0
    /* 0x800BA114 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29700)); // lwz r11, -29700(r13) [pEvent04]
    /* 0x800BA118 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BA11C */ if (ctx.eval_bc(12, 2)) goto loc_800BA13C; // bc 12, 2, 0x800BA13C
    /* 0x800BA120 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BA124 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BA128 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BA12C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BA130 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BA134 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA138 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BA13C:;
    /* 0x800BA13C */ ctx.r[30] = 0x00000000u; // li r30, 0
    /* 0x800BA140 */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800BA144 */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800BA148 */ ctx.r[4] = 0x00000041u; // li r4, 65
    /* 0x800BA14C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA150 */ mem.write_u32(ctx.r[13] + (-29700), ctx.r[30]); // stw r30, -29700(r13) [pEvent04]
    /* 0x800BA154 */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800BA158 */ ctx.r[3] = 0x00000008u; // li r3, 8
    /* 0x800BA15C */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800BA160 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA164 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
    /* 0x800BA168 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA16C */ ctx.r[0] = 0x00000004u; // li r0, 4
    /* 0x800BA170 */ mem.write_u8(ctx.r[9] + (260), static_cast<uint8_t>(ctx.r[0])); // stb r0, 260(r9)
    /* 0x800BA174 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (336)); // lwz r11, 336(r9)
    /* 0x800BA178 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (332)); // lwz r0, 332(r9)
    /* 0x800BA17C */ ctx.r[10] = mem.read_u32(ctx.r[9] + (328)); // lwz r10, 328(r9)
    /* 0x800BA180 */ ctx.r[11] = ctx.r[11] | 0x20000000u; // oris r11, r11, 0x2000
    /* 0x800BA184 */ ctx.r[8] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r8, -29836(r13) [pG]
    /* 0x800BA188 */ ctx.r[0] = ctx.r[0] | 0x08000000u; // oris r0, r0, 0x0800
    /* 0x800BA18C */ ctx.r[10] = ctx.r[10] | 0x0008u; // ori r10, r10, 0x0008
    /* 0x800BA190 */ mem.write_u32(ctx.r[9] + (336), ctx.r[11]); // stw r11, 336(r9)
    /* 0x800BA194 */ mem.write_u32(ctx.r[9] + (332), ctx.r[0]); // stw r0, 332(r9)
    /* 0x800BA198 */ mem.write_u32(ctx.r[9] + (328), ctx.r[10]); // stw r10, 328(r9)
    /* 0x800BA19C */ mem.write_u8(ctx.r[8] + (261), static_cast<uint8_t>(ctx.r[30])); // stb r30, 261(r8)
    /* 0x800BA1A0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA1A4 */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[30])); // stb r30, 262(r9)
    /* 0x800BA1A8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA1AC */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[30])); // stb r30, 263(r11)
loc_800BA1B0:;
    /* 0x800BA1B0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (68)); // lwz r0, 68(r1)
    /* 0x800BA1B4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA1B8 */ ctx.lmw(mem, 30, ctx.r[1] + (56)); // lmw r30, 56(r1)
    /* 0x800BA1BC */ ctx.r[1] = ctx.r[1] + (64); // addi r1, r1, 64
    /* 0x800BA1C0 */ return; // blr
}

// [0x800BA1C4] R301Init(void) (r301.obj, 1 insns / 0x4 bytes)
void R301Init_800BA1C4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA1C4 */ return; // blr
}

// [0x800BA1C8] R301Main(void) (r301.obj, 17 insns / 0x44 bytes)
void R301Main_800BA1C8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA1C8 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BA1CC */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BA1D0 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BA1D4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA1D8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800BA1DC */ ctx.r[11] = ctx.r[0] & 0x00200000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0020
    /* 0x800BA1E0 */ if (ctx.eval_bc(4, 2)) goto loc_800BA1FC; // bc 4, 2, 0x800BA1FC
    /* 0x800BA1E4 */ ctx.r[0] = ctx.r[0] | 0x00200000u; // oris r0, r0, 0x0020
    /* 0x800BA1E8 */ ctx.r[3] = 0x0000000Au; // li r3, 10
    /* 0x800BA1EC */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800BA1F0 */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800BA1F4 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA1F8 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
loc_800BA1FC:;
    /* 0x800BA1FC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BA200 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA204 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BA208 */ return; // blr
}

// [0x800BA20C] R306Init(void) (r306.obj, 12 insns / 0x30 bytes)
void R306Init_800BA20C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA20C */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BA210 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BA214 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BA218 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BA21C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BA220 */ mem.write_u32(ctx.r[13] + (-29696), ctx.r[0]); // stw r0, -29696(r13) [pEvent31]
    /* 0x800BA224 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BA228 */ SceAtSetEnable_800C20A0(ctx, mem); // bl 0x800C20A0 <SceAtSetEnable(unsigned long, int)>
    /* 0x800BA22C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BA230 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA234 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BA238 */ return; // blr
}

// [0x800BA23C] R306Main(void) (r306.obj, 74 insns / 0x128 bytes)
void R306Main_800BA23C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA23C */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BA240 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BA244 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BA248 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA24C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800BA250 */ ctx.r[10] = ctx.r[0] & 0x00100000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r0, 0x0010
    /* 0x800BA254 */ if (ctx.eval_bc(4, 2)) goto loc_800BA290; // bc 4, 2, 0x800BA290
    /* 0x800BA258 */ ctx.r[0] = ctx.r[0] | 0x00100000u; // oris r0, r0, 0x0010
    /* 0x800BA25C */ ctx.r[3] = 0x0000000Bu; // li r3, 11
    /* 0x800BA260 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800BA264 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BA268 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA26C */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
    /* 0x800BA270 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BA274 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BA278 */ SceAtSetEnable_800C20A0(ctx, mem); // bl 0x800C20A0 <SceAtSetEnable(unsigned long, int)>
    /* 0x800BA27C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA280 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (332)); // lwz r0, 332(r9)
    /* 0x800BA284 */ ctx.r[0] = ctx.r[0] | 0x04000000u; // oris r0, r0, 0x0400
    /* 0x800BA288 */ mem.write_u32(ctx.r[9] + (332), ctx.r[0]); // stw r0, 332(r9)
    /* 0x800BA28C */ goto loc_800BA308; // b 0x800BA308 <sub_800BA308>
loc_800BA290:;
    /* 0x800BA290 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BA294 */ ctx.r[0] = ctx.r[11] & 0x0001u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andi. r0, r11, 0x0001
    /* 0x800BA298 */ if (ctx.eval_bc(4, 2)) goto loc_800BA308; // bc 4, 2, 0x800BA308
    /* 0x800BA29C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (332)); // lwz r0, 332(r9)
    /* 0x800BA2A0 */ ctx.r[10] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r0, 0x2000
    /* 0x800BA2A4 */ if (ctx.eval_bc(4, 2)) goto loc_800BA308; // bc 4, 2, 0x800BA308
    /* 0x800BA2A8 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29696)); // lwz r0, -29696(r13) [pEvent31]
    /* 0x800BA2AC */ ctx.r[3] = ctx.r[0]; // mr r3, r0
    /* 0x800BA2B0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BA2B4 */ if (ctx.eval_bc(4, 2)) goto loc_800BA318; // bc 4, 2, 0x800BA318
    /* 0x800BA2B8 */ ctx.r[0] = ctx.r[11] | 0x0001u; // ori r0, r11, 0x0001
    /* 0x800BA2BC */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BA2C0 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BA2C4 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BA2C8 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BA2CC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA2D0 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BA2D4 */ mem.write_u32(ctx.r[13] + (-29696), ctx.r[0]); // stw r0, -29696(r13) [pEvent31]
    /* 0x800BA2D8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BA2DC */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA2E0 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (48)); // lwz r4, 48(r9)
    /* 0x800BA2E4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BA2E8 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BA2EC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA2F0 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (332)); // lwz r0, 332(r11)
    /* 0x800BA2F4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (328)); // lwz r9, 328(r11)
    /* 0x800BA2F8 */ ctx.rlwinm(0, 0, 0u, 6u, 4u, false); // rlwinm r0, r0, 0, 6, 4
    /* 0x800BA2FC */ ctx.rlwinm(9, 9, 0u, 0u, 30u, false); // rlwinm r9, r9, 0, 0, 30
    /* 0x800BA300 */ mem.write_u32(ctx.r[11] + (332), ctx.r[0]); // stw r0, 332(r11)
    /* 0x800BA304 */ mem.write_u32(ctx.r[11] + (328), ctx.r[9]); // stw r9, 328(r11)
loc_800BA308:;
    /* 0x800BA308 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29696)); // lwz r0, -29696(r13) [pEvent31]
    /* 0x800BA30C */ ctx.r[3] = ctx.r[0]; // mr r3, r0
    /* 0x800BA310 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BA314 */ if (ctx.eval_bc(12, 2)) goto loc_800BA354; // bc 12, 2, 0x800BA354
loc_800BA318:;
    /* 0x800BA318 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BA31C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BA320 */ if (ctx.eval_bc(12, 2)) goto loc_800BA354; // bc 12, 2, 0x800BA354
    /* 0x800BA324 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29696)); // lwz r11, -29696(r13) [pEvent31]
    /* 0x800BA328 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BA32C */ if (ctx.eval_bc(12, 2)) goto loc_800BA34C; // bc 12, 2, 0x800BA34C
    /* 0x800BA330 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BA334 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BA338 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BA33C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BA340 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BA344 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA348 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BA34C:;
    /* 0x800BA34C */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BA350 */ mem.write_u32(ctx.r[13] + (-29696), ctx.r[0]); // stw r0, -29696(r13) [pEvent31]
loc_800BA354:;
    /* 0x800BA354 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BA358 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA35C */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BA360 */ return; // blr
}

// [0x800BA364] R307Init(void) (r307.obj, 8 insns / 0x20 bytes)
void R307Init_800BA364(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA364 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA368 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800BA36C */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BA370 */ ctx.r[0] = ctx.r[0] | 0x00100000u; // oris r0, r0, 0x0010
    /* 0x800BA374 */ ctx.r[11] = ctx.r[11] | 0x0001u; // ori r11, r11, 0x0001
    /* 0x800BA378 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800BA37C */ mem.write_u32(ctx.r[9] + (29012), ctx.r[11]); // stw r11, 29012(r9)
    /* 0x800BA380 */ return; // blr
}

// [0x800BA384] R307Main(void) (r307.obj, 1 insns / 0x4 bytes)
void R307Main_800BA384(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA384 */ return; // blr
}

// [0x800BA388] R312Init(void) (r312.obj, 34 insns / 0x88 bytes)
void R312Init_800BA388(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA388 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BA38C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BA390 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BA394 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA398 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BA39C */ mem.write_u32(ctx.r[13] + (-29684), ctx.r[0]); // stw r0, -29684(r13) [str_req]
    /* 0x800BA3A0 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (29012)); // lwz r9, 29012(r11)
    /* 0x800BA3A4 */ mem.write_u32(ctx.r[13] + (-29692), ctx.r[0]); // stw r0, -29692(r13) [pEvent05]
    /* 0x800BA3A8 */ mem.write_u32(ctx.r[13] + (-29688), ctx.r[0]); // stw r0, -29688(r13) [pEvent06]
    /* 0x800BA3AC */ ctx.r[0] = ctx.r[9] & 0x04000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andis. r0, r9, 0x0400
    /* 0x800BA3B0 */ if (ctx.eval_bc(4, 2)) goto loc_800BA400; // bc 4, 2, 0x800BA400
    /* 0x800BA3B4 */ ctx.r[0] = ctx.r[9] | 0x04000000u; // oris r0, r9, 0x0400
    /* 0x800BA3B8 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BA3BC */ mem.write_u32(ctx.r[11] + (29012), ctx.r[0]); // stw r0, 29012(r11)
    /* 0x800BA3C0 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BA3C4 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BA3C8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA3CC */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BA3D0 */ mem.write_u32(ctx.r[13] + (-29692), ctx.r[0]); // stw r0, -29692(r13) [pEvent05]
    /* 0x800BA3D4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BA3D8 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA3DC */ ctx.r[4] = mem.read_u32(ctx.r[9] + (40)); // lwz r4, 40(r9)
    /* 0x800BA3E0 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BA3E4 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BA3E8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA3EC */ ctx.r[11] = 0x00000001u; // li r11, 1
    /* 0x800BA3F0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BA3F4 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BA3F8 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
    /* 0x800BA3FC */ mem.write_u32(ctx.r[13] + (-29684), ctx.r[11]); // stw r11, -29684(r13) [str_req]
loc_800BA400:;
    /* 0x800BA400 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BA404 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA408 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BA40C */ return; // blr
}

// [0x800BA410] R312Main(void) (r312.obj, 142 insns / 0x238 bytes)
void R312Main_800BA410(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA410 */ ctx.r[1] += (-80); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -80(r1)
    /* 0x800BA414 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BA418 */ ctx.stmw(mem, 30, ctx.r[1] + (72)); // stmw r30, 72(r1)
    /* 0x800BA41C */ mem.write_u32(ctx.r[1] + (84), ctx.r[0]); // stw r0, 84(r1)
    /* 0x800BA420 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29692)); // lwz r3, -29692(r13) [pEvent05]
    /* 0x800BA424 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BA428 */ if (ctx.eval_bc(12, 2)) goto loc_800BA4F4; // bc 12, 2, 0x800BA4F4
    /* 0x800BA42C */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BA430 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BA434 */ if (ctx.eval_bc(12, 2)) goto loc_800BA4F4; // bc 12, 2, 0x800BA4F4
    /* 0x800BA438 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29692)); // lwz r11, -29692(r13) [pEvent05]
    /* 0x800BA43C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BA440 */ if (ctx.eval_bc(12, 2)) goto loc_800BA460; // bc 12, 2, 0x800BA460
    /* 0x800BA444 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BA448 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BA44C */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BA450 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BA454 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BA458 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA45C */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BA460:;
    /* 0x800BA460 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BA464 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BA468 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12588)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12588(r9) [0x8016CED4]
    /* 0x800BA46C */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BA470 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-12584)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12584(r11) [0x8016CED8]
    /* 0x800BA474 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BA478 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800BA47C */ ctx.r[11] = ctx.r[1] + (8); // addi r11, r1, 8
    /* 0x800BA480 */ ctx.f[12] = mem.read_f32(ctx.r[10] + (-12580)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12580(r10) [0x8016CEDC]
    /* 0x800BA484 */ ctx.r[7] = ctx.r[1] + (24); // addi r7, r1, 24
    /* 0x800BA488 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12576)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12576(r9) [0x8016CEE0]
    /* 0x800BA48C */ ctx.r[30] = 0x00000000u; // li r30, 0
    /* 0x800BA490 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r11)
    /* 0x800BA494 */ ctx.r[8] = ctx.r[1] + (40); // addi r8, r1, 40
    /* 0x800BA498 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r11)
    /* 0x800BA49C */ ctx.r[6] = ctx.r[1] + (56); // addi r6, r1, 56
    /* 0x800BA4A0 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800BA4A4 */ ctx.r[3] = ctx.r[8]; // mr r3, r8
    /* 0x800BA4A8 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r7)
    /* 0x800BA4AC */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BA4B0 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800BA4B4 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA4B8 */ mem.write_u32(ctx.r[13] + (-29692), ctx.r[30]); // stw r30, -29692(r13) [pEvent05]
    /* 0x800BA4BC */ ctx.r[9] = mem.read_u32(ctx.r[1] + (8)); // lwz r9, 8(r1)
    /* 0x800BA4C0 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (4)); // lwz r0, 4(r11)
    /* 0x800BA4C4 */ ctx.r[10] = mem.read_u32(ctx.r[11] + (8)); // lwz r10, 8(r11)
    /* 0x800BA4C8 */ mem.write_u32(ctx.r[1] + (40), ctx.r[9]); // stw r9, 40(r1)
    /* 0x800BA4CC */ mem.write_u32(ctx.r[8] + (4), ctx.r[0]); // stw r0, 4(r8)
    /* 0x800BA4D0 */ mem.write_u32(ctx.r[8] + (8), ctx.r[10]); // stw r10, 8(r8)
    /* 0x800BA4D4 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (24)); // lwz r9, 24(r1)
    /* 0x800BA4D8 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BA4DC */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BA4E0 */ mem.write_u32(ctx.r[1] + (56), ctx.r[9]); // stw r9, 56(r1)
    /* 0x800BA4E4 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BA4E8 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BA4EC */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BA4F0 */ mem.write_u32(ctx.r[13] + (-29684), ctx.r[30]); // stw r30, -29684(r13) [str_req]
loc_800BA4F4:;
    /* 0x800BA4F4 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29688)); // lwz r3, -29688(r13) [pEvent06]
    /* 0x800BA4F8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BA4FC */ if (ctx.eval_bc(4, 2)) goto loc_800BA554; // bc 4, 2, 0x800BA554
    /* 0x800BA500 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA504 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BA508 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BA50C */ if (ctx.eval_bc(4, 0)) goto loc_800BA608; // bc 4, 0, 0x800BA608
    /* 0x800BA510 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BA514 */ ctx.r[11] = ctx.r[0] & 0x02000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0200
    /* 0x800BA518 */ if (ctx.eval_bc(4, 2)) goto loc_800BA608; // bc 4, 2, 0x800BA608
    /* 0x800BA51C */ ctx.r[0] = ctx.r[0] | 0x02000000u; // oris r0, r0, 0x0200
    /* 0x800BA520 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BA524 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BA528 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BA52C */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BA530 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA534 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BA538 */ mem.write_u32(ctx.r[13] + (-29688), ctx.r[0]); // stw r0, -29688(r13) [pEvent06]
    /* 0x800BA53C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BA540 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BA544 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (44)); // lwz r4, 44(r9)
    /* 0x800BA548 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BA54C */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BA550 */ goto loc_800BA608; // b 0x800BA608 <sub_800BA608>
loc_800BA554:;
    /* 0x800BA554 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BA558 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BA55C */ if (ctx.eval_bc(12, 2)) goto loc_800BA608; // bc 12, 2, 0x800BA608
    /* 0x800BA560 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29688)); // lwz r11, -29688(r13) [pEvent06]
    /* 0x800BA564 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BA568 */ if (ctx.eval_bc(12, 2)) goto loc_800BA588; // bc 12, 2, 0x800BA588
    /* 0x800BA56C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BA570 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BA574 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BA578 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BA57C */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BA580 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA584 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BA588:;
    /* 0x800BA588 */ ctx.r[30] = 0x00000000u; // li r30, 0
    /* 0x800BA58C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BA590 */ ctx.r[4] = 0x000000C8u; // li r4, 200
    /* 0x800BA594 */ mem.write_u32(ctx.r[13] + (-29688), ctx.r[30]); // stw r30, -29688(r13) [pEvent06]
    /* 0x800BA598 */ Snd_str_fadeout_800CD394(ctx, mem); // bl 0x800CD394 <Snd_str_fadeout(long, long)>
    /* 0x800BA59C */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800BA5A0 */ ctx.r[4] = 0x00000040u; // li r4, 64
    /* 0x800BA5A4 */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800BA5A8 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA5AC */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800BA5B0 */ ctx.r[3] = 0x0000000Cu; // li r3, 12
    /* 0x800BA5B4 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800BA5B8 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA5BC */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
    /* 0x800BA5C0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA5C4 */ ctx.r[0] = 0x00000004u; // li r0, 4
    /* 0x800BA5C8 */ mem.write_u8(ctx.r[9] + (260), static_cast<uint8_t>(ctx.r[0])); // stb r0, 260(r9)
    /* 0x800BA5CC */ ctx.r[11] = mem.read_u32(ctx.r[9] + (336)); // lwz r11, 336(r9)
    /* 0x800BA5D0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (332)); // lwz r0, 332(r9)
    /* 0x800BA5D4 */ ctx.r[10] = mem.read_u32(ctx.r[9] + (328)); // lwz r10, 328(r9)
    /* 0x800BA5D8 */ ctx.r[11] = ctx.r[11] | 0x20000000u; // oris r11, r11, 0x2000
    /* 0x800BA5DC */ ctx.r[8] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r8, -29836(r13) [pG]
    /* 0x800BA5E0 */ ctx.r[0] = ctx.r[0] | 0x08000000u; // oris r0, r0, 0x0800
    /* 0x800BA5E4 */ ctx.r[10] = ctx.r[10] | 0x0008u; // ori r10, r10, 0x0008
    /* 0x800BA5E8 */ mem.write_u32(ctx.r[9] + (336), ctx.r[11]); // stw r11, 336(r9)
    /* 0x800BA5EC */ mem.write_u32(ctx.r[9] + (332), ctx.r[0]); // stw r0, 332(r9)
    /* 0x800BA5F0 */ mem.write_u32(ctx.r[9] + (328), ctx.r[10]); // stw r10, 328(r9)
    /* 0x800BA5F4 */ mem.write_u8(ctx.r[8] + (261), static_cast<uint8_t>(ctx.r[30])); // stb r30, 261(r8)
    /* 0x800BA5F8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA5FC */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[30])); // stb r30, 262(r9)
    /* 0x800BA600 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA604 */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[30])); // stb r30, 263(r11)
loc_800BA608:;
    /* 0x800BA608 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29684)); // lwz r0, -29684(r13) [str_req]
    /* 0x800BA60C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BA610 */ if (ctx.eval_bc(4, 2)) goto loc_800BA634; // bc 4, 2, 0x800BA634
    /* 0x800BA614 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BA618 */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800BA61C */ ctx.r[5] = 0x00000002u; // li r5, 2
    /* 0x800BA620 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BA624 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BA628 */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
    /* 0x800BA62C */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BA630 */ mem.write_u32(ctx.r[13] + (-29684), ctx.r[0]); // stw r0, -29684(r13) [str_req]
loc_800BA634:;
    /* 0x800BA634 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (84)); // lwz r0, 84(r1)
    /* 0x800BA638 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA63C */ ctx.lmw(mem, 30, ctx.r[1] + (72)); // lmw r30, 72(r1)
    /* 0x800BA640 */ ctx.r[1] = ctx.r[1] + (80); // addi r1, r1, 80
    /* 0x800BA644 */ return; // blr
}

// [0x800BA648] R404Init(void) (r404.obj, 25 insns / 0x64 bytes)
void R404Init_800BA648(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA648 */ ctx.r[1] += (-40); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -40(r1)
    /* 0x800BA64C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BA650 */ mem.write_u32(ctx.r[1] + (44), ctx.r[0]); // stw r0, 44(r1)
    /* 0x800BA654 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BA658 */ ctx.r[11] = ctx.r[1] + (8); // addi r11, r1, 8
    /* 0x800BA65C */ ctx.r[10] = mem.read_u32(ctx.r[9] + (-12560)); // lwz r10, -12560(r9) [0x8016CEF0]
    /* 0x800BA660 */ ctx.r[3] = ctx.r[1] + (24); // addi r3, r1, 24
    /* 0x800BA664 */ ctx.r[9] = ctx.r[9] + (-12560); // addi r9, r9, -12560 -> 0x8016CEF0
    /* 0x800BA668 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BA66C */ ctx.r[8] = mem.read_u32(ctx.r[9] + (8)); // lwz r8, 8(r9)
    /* 0x800BA670 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (4)); // lwz r0, 4(r9)
    /* 0x800BA674 */ mem.write_u32(ctx.r[1] + (8), ctx.r[10]); // stw r10, 8(r1)
    /* 0x800BA678 */ mem.write_u32(ctx.r[11] + (4), ctx.r[0]); // stw r0, 4(r11)
    /* 0x800BA67C */ mem.write_u32(ctx.r[11] + (8), ctx.r[8]); // stw r8, 8(r11)
    /* 0x800BA680 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r1)
    /* 0x800BA684 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800BA688 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r11)
    /* 0x800BA68C */ mem.write_f32(ctx.r[1] + (28), static_cast<float>(ctx.f[13])); // stfs f13, 28(r1)
    /* 0x800BA690 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r11)
    /* 0x800BA694 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BA698 */ StormInit_800CE150(ctx, mem); // bl 0x800CE150 <StormInit(cVec &, unsigned char)>
    /* 0x800BA69C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (44)); // lwz r0, 44(r1)
    /* 0x800BA6A0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA6A4 */ ctx.r[1] = ctx.r[1] + (40); // addi r1, r1, 40
    /* 0x800BA6A8 */ return; // blr
}

// [0x800BA6AC] R404Main(void) (r404.obj, 32 insns / 0x80 bytes)
void R404Main_800BA6AC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA6AC */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800BA6B0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BA6B4 */ mem.write_u32(ctx.r[1] + (12), ctx.r[31]); // stw r31, 12(r1)
    /* 0x800BA6B8 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800BA6BC */ StormMain_800CE22C(ctx, mem); // bl 0x800CE22C <StormMain(void)>
    /* 0x800BA6C0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA6C4 */ ctx.r[31] = mem.read_u32(ctx.r[9] + (324)); // lwz r31, 324(r9)
    /* 0x800BA6C8 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800BA6CC */ ctx.r[0] = mem.read_u32(ctx.r[31] + (4)); // lwz r0, 4(r31)
    /* 0x800BA6D0 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800BA6D4 */ ctx.rlwinm(9, 0, 30u, 2u, 31u, true); // rlwinm r9, r0, 30, 2, 31
    /* 0x800BA6D8 */ if (ctx.eval_bc(4, 2)) goto loc_800BA6E8; // bc 4, 2, 0x800BA6E8
    /* 0x800BA6DC */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800BA6E0 */ ctx.r[3] = ctx.r[3] + (-12548); // addi r3, r3, -12548 -> 0x8016CEFC /* "vector" */
    /* 0x800BA6E4 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800BA6E8:;
    /* 0x800BA6E8 */ ctx.r[10] = mem.read_u32(ctx.r[31] + (0)); // lwz r10, 0(r31)
    /* 0x800BA6EC */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BA6F0 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12540)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12540(r9) [0x8016CF04]
    /* 0x800BA6F4 */ ctx.r[11] = mem.read_u32(ctx.r[10] + (0)); // lwz r11, 0(r10)
    /* 0x800BA6F8 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (196)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 196(r11)
    /* 0x800BA6FC */ ctx.cmp_f64(0, ctx.f[0], ctx.f[13]); // fcmpu cr0, f0, f13
    /* 0x800BA700 */ if (ctx.eval_bc(4, 0)) goto loc_800BA710; // bc 4, 0, 0x800BA710
    /* 0x800BA704 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BA708 */ StormPause_800CE310(ctx, mem); // bl 0x800CE310 <StormPause(bool)>
    /* 0x800BA70C */ goto loc_800BA718; // b 0x800BA718 <sub_800BA718>
loc_800BA710:;
    /* 0x800BA710 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BA714 */ StormPause_800CE310(ctx, mem); // bl 0x800CE310 <StormPause(bool)>
loc_800BA718:;
    /* 0x800BA718 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800BA71C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA720 */ ctx.r[31] = mem.read_u32(ctx.r[1] + (12)); // lwz r31, 12(r1)
    /* 0x800BA724 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800BA728 */ return; // blr
}

// [0x800BA72C] R405Init(void) (r405.obj, 46 insns / 0xB8 bytes)
void R405Init_800BA72C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA72C */ ctx.r[1] += (-48); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -48(r1)
    /* 0x800BA730 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BA734 */ ctx.stmw(mem, 30, ctx.r[1] + (40)); // stmw r30, 40(r1)
    /* 0x800BA738 */ mem.write_u32(ctx.r[1] + (52), ctx.r[0]); // stw r0, 52(r1)
    /* 0x800BA73C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BA740 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BA744 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12516)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12516(r9) [0x8016CF1C]
    /* 0x800BA748 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BA74C */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-12512)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12512(r11) [0x8016CF20]
    /* 0x800BA750 */ ctx.r[8] = 0x80170000u; // lis r8, 0x8017
    /* 0x800BA754 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800BA758 */ ctx.r[5] = ctx.r[1] + (8); // addi r5, r1, 8
    /* 0x800BA75C */ ctx.f[12] = mem.read_f32(ctx.r[10] + (-12508)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12508(r10) [0x8016CF24]
    /* 0x800BA760 */ ctx.r[9] = ctx.r[1] + (24); // addi r9, r1, 24
    /* 0x800BA764 */ ctx.f[0] = mem.read_f32(ctx.r[8] + (-12504)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12504(r8) [0x8016CF28]
    /* 0x800BA768 */ ctx.r[6] = ctx.r[9]; // mr r6, r9
    /* 0x800BA76C */ mem.write_f32(ctx.r[5] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r5)
    /* 0x800BA770 */ ctx.r[0] = 0x0000005Au; // li r0, 90
    /* 0x800BA774 */ mem.write_f32(ctx.r[5] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r5)
    /* 0x800BA778 */ ctx.r[30] = 0x00000000u; // li r30, 0
    /* 0x800BA77C */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800BA780 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
    /* 0x800BA784 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r9)
    /* 0x800BA788 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA78C */ mem.write_u32(ctx.r[13] + (-29668), ctx.r[0]); // stw r0, -29668(r13) [{anonymous}::demoWaitTimer]
    /* 0x800BA790 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BA794 */ mem.write_u32(ctx.r[13] + (-29672), ctx.r[30]); // stw r30, -29672(r13) [{anonymous}::pEvent07]
    /* 0x800BA798 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (60)); // lwz r3, 60(r9)
    /* 0x800BA79C */ ctx.r[4] = mem.read_u32(ctx.r[9] + (64)); // lwz r4, 64(r9)
    /* 0x800BA7A0 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BA7A4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BA7A8 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BA7AC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA7B0 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BA7B4 */ mem.write_u32(ctx.r[13] + (-29680), ctx.r[0]); // stw r0, -29680(r13) [R405_pObj]
    /* 0x800BA7B8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BA7BC */ ctx.r[5] = 0x00000005u; // li r5, 5
    /* 0x800BA7C0 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (68)); // lwz r4, 68(r9)
    /* 0x800BA7C4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BA7C8 */ cObj00__MotSetObj00_800A7C54(ctx, mem); // bl 0x800A7C54 <cObj00::MotSetObj00(void *, unsigned long)>
    /* 0x800BA7CC */ mem.write_u32(ctx.r[13] + (-29676), ctx.r[30]); // stw r30, -29676(r13) [r405_bgm_fade]
    /* 0x800BA7D0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (52)); // lwz r0, 52(r1)
    /* 0x800BA7D4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA7D8 */ ctx.lmw(mem, 30, ctx.r[1] + (40)); // lmw r30, 40(r1)
    /* 0x800BA7DC */ ctx.r[1] = ctx.r[1] + (48); // addi r1, r1, 48
    /* 0x800BA7E0 */ return; // blr
}

// [0x800BA7E4] R405Main(void) (r405.obj, 230 insns / 0x398 bytes)
void R405Main_800BA7E4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BA7E4 */ ctx.r[1] += (-120); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -120(r1)
    /* 0x800BA7E8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BA7EC */ ctx.stmw(mem, 29, ctx.r[1] + (108)); // stmw r29, 108(r1)
    /* 0x800BA7F0 */ mem.write_u32(ctx.r[1] + (124), ctx.r[0]); // stw r0, 124(r1)
    /* 0x800BA7F4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BA7F8 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BA7FC */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12492)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12492(r9) [0x8016CF34]
    /* 0x800BA800 */ ctx.r[11] = ctx.r[1] + (8); // addi r11, r1, 8
    /* 0x800BA804 */ ctx.r[9] = ctx.r[1] + (24); // addi r9, r1, 24
    /* 0x800BA808 */ ctx.r[29] = ctx.r[11]; // mr r29, r11
    /* 0x800BA80C */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800BA810 */ ctx.r[30] = ctx.r[9]; // mr r30, r9
    /* 0x800BA814 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800BA818 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BA81C */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800BA820 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
    /* 0x800BA824 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r9)
    /* 0x800BA828 */ ctx.r[0] = mem.read_u32(ctx.r[10] + (29012)); // lwz r0, 29012(r10)
    /* 0x800BA82C */ ctx.r[11] = ctx.r[0] & 0x01000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0100
    /* 0x800BA830 */ if (ctx.eval_bc(4, 2)) goto loc_800BA8DC; // bc 4, 2, 0x800BA8DC
    /* 0x800BA834 */ ctx.r[31] = mem.read_u32(ctx.r[10] + (324)); // lwz r31, 324(r10)
    /* 0x800BA838 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (4)); // lwz r0, 4(r31)
    /* 0x800BA83C */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800BA840 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800BA844 */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800BA848 */ ctx.cmp_u32(0, ctx.r[11], ctx.r[0]); // cmplw cr0, r11, r0
    /* 0x800BA84C */ if (ctx.eval_bc(12, 0)) goto loc_800BA85C; // bc 12, 0, 0x800BA85C
    /* 0x800BA850 */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800BA854 */ ctx.r[3] = ctx.r[3] + (-12500); // addi r3, r3, -12500 -> 0x8016CF2C /* "vector" */
    /* 0x800BA858 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800BA85C:;
    /* 0x800BA85C */ ctx.r[10] = mem.read_u32(ctx.r[31] + (0)); // lwz r10, 0(r31)
    /* 0x800BA860 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BA864 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12488)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12488(r9) [0x8016CF38]
    /* 0x800BA868 */ ctx.r[11] = mem.read_u32(ctx.r[10] + (0)); // lwz r11, 0(r10)
    /* 0x800BA86C */ ctx.f[0] = mem.read_f32(ctx.r[11] + (192)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 192(r11)
    /* 0x800BA870 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[13]); // fcmpu cr0, f0, f13
    /* 0x800BA874 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(1)); // cror 3, 2, 1
    /* 0x800BA878 */ if (ctx.eval_bc(4, 3)) goto loc_800BA8DC; // bc 4, 3, 0x800BA8DC
    /* 0x800BA87C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA880 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BA884 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BA888 */ ctx.r[0] = ctx.r[0] | 0x01000000u; // oris r0, r0, 0x0100
    /* 0x800BA88C */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BA890 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BA894 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BA898 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA89C */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BA8A0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA8A4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BA8A8 */ mem.write_u32(ctx.r[13] + (-29672), ctx.r[0]); // stw r0, -29672(r13) [{anonymous}::pEvent07]
    /* 0x800BA8AC */ ctx.r[4] = mem.read_u32(ctx.r[9] + (48)); // lwz r4, 48(r9)
    /* 0x800BA8B0 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BA8B4 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BA8B8 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29680)); // lwz r3, -29680(r13) [R405_pObj]
    /* 0x800BA8BC */ PushObj_800749C8(ctx, mem); // bl 0x800749C8 <PushObj(cObj *)>
    /* 0x800BA8C0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BA8C4 */ ctx.r[4] = 0x0000003Cu; // li r4, 60
    /* 0x800BA8C8 */ Snd_str_fadeout_800CD394(ctx, mem); // bl 0x800CD394 <Snd_str_fadeout(long, long)>
    /* 0x800BA8CC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BA8D0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BA8D4 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BA8D8 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
loc_800BA8DC:;
    /* 0x800BA8DC */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29672)); // lwz r3, -29672(r13) [{anonymous}::pEvent07]
    /* 0x800BA8E0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BA8E4 */ if (ctx.eval_bc(12, 2)) goto loc_800BAA84; // bc 12, 2, 0x800BAA84
    /* 0x800BA8E8 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BA8EC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BA8F0 */ if (ctx.eval_bc(12, 2)) goto loc_800BAB68; // bc 12, 2, 0x800BAB68
    /* 0x800BA8F4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29672)); // lwz r11, -29672(r13) [{anonymous}::pEvent07]
    /* 0x800BA8F8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BA8FC */ if (ctx.eval_bc(12, 2)) goto loc_800BA91C; // bc 12, 2, 0x800BA91C
    /* 0x800BA900 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BA904 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BA908 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BA90C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BA910 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BA914 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BA918 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BA91C:;
    /* 0x800BA91C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BA920 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BA924 */ ctx.f[12] = mem.read_f32(ctx.r[9] + (-12484)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12484(r9) [0x8016CF3C]
    /* 0x800BA928 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BA92C */ ctx.f[13] = mem.read_f32(ctx.r[10] + (-12480)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12480(r10) [0x8016CF40]
    /* 0x800BA930 */ ctx.r[8] = ctx.r[1] + (40); // addi r8, r1, 40
    /* 0x800BA934 */ mem.write_f32(ctx.r[1] + (40), static_cast<float>(ctx.f[12])); // stfs f12, 40(r1)
    /* 0x800BA938 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BA93C */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-12492)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12492(r11) [0x8016CF34]
    /* 0x800BA940 */ ctx.r[7] = ctx.r[1] + (56); // addi r7, r1, 56
    /* 0x800BA944 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r8)
    /* 0x800BA948 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BA94C */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800BA950 */ ctx.r[10] = ctx.r[1] + (72); // addi r10, r1, 72
    /* 0x800BA954 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12476)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12476(r9) [0x8016CF44]
    /* 0x800BA958 */ ctx.r[6] = ctx.r[1] + (88); // addi r6, r1, 88
    /* 0x800BA95C */ mem.write_f32(ctx.r[1] + (56), static_cast<float>(ctx.f[0])); // stfs f0, 56(r1)
    /* 0x800BA960 */ ctx.r[3] = ctx.r[10]; // mr r3, r10
    /* 0x800BA964 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r7)
    /* 0x800BA968 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BA96C */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r7)
    /* 0x800BA970 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BA974 */ mem.write_u32(ctx.r[13] + (-29672), ctx.r[0]); // stw r0, -29672(r13) [{anonymous}::pEvent07]
    /* 0x800BA978 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (40)); // lwz r9, 40(r1)
    /* 0x800BA97C */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BA980 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BA984 */ mem.write_u32(ctx.r[1] + (72), ctx.r[9]); // stw r9, 72(r1)
    /* 0x800BA988 */ mem.write_u32(ctx.r[10] + (4), ctx.r[0]); // stw r0, 4(r10)
    /* 0x800BA98C */ mem.write_u32(ctx.r[10] + (8), ctx.r[11]); // stw r11, 8(r10)
    /* 0x800BA990 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (56)); // lwz r9, 56(r1)
    /* 0x800BA994 */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BA998 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BA99C */ mem.write_u32(ctx.r[1] + (88), ctx.r[9]); // stw r9, 88(r1)
    /* 0x800BA9A0 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BA9A4 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BA9A8 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BA9AC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA9B0 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BA9B4 */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800BA9B8 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BA9BC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BA9C0 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (72)); // lwz r3, 72(r9)
    /* 0x800BA9C4 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BA9C8 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BA9CC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA9D0 */ ctx.r[4] = 0x00000200u; // li r4, 512
    /* 0x800BA9D4 */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800BA9D8 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BA9DC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BA9E0 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (72)); // lwz r3, 72(r9)
    /* 0x800BA9E4 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BA9E8 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BA9EC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BA9F0 */ ctx.r[4] = 0x00000100u; // li r4, 256
    /* 0x800BA9F4 */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800BA9F8 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BA9FC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BAA00 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (76)); // lwz r3, 76(r9)
    /* 0x800BAA04 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BAA08 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BAA0C */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BAA10 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BAA14 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BAA18 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12472)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12472(r9) [0x8016CF48]
    /* 0x800BAA1C */ ctx.f[12] = mem.read_f32(ctx.r[11] + (-12468)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12468(r11) [0x8016CF4C]
    /* 0x800BAA20 */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800BAA24 */ ctx.f[0] = mem.read_f32(ctx.r[10] + (-12464)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12464(r10) [0x8016CF50]
    /* 0x800BAA28 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BAA2C */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800BAA30 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[12])); // stfs f12, 12(r1)
    /* 0x800BAA34 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BAA38 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BAA3C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BAA40 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (60)); // lwz r3, 60(r9)
    /* 0x800BAA44 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (64)); // lwz r4, 64(r9)
    /* 0x800BAA48 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BAA4C */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BAA50 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BAA54 */ mem.write_u32(ctx.r[13] + (-29680), ctx.r[3]); // stw r3, -29680(r13) [R405_pObj]
    /* 0x800BAA58 */ ctx.r[4] = 0x00000014u; // li r4, 20
    /* 0x800BAA5C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BAA60 */ ctx.r[5] = 0x00000003u; // li r5, 3
    /* 0x800BAA64 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BAA68 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BAA6C */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
    /* 0x800BAA70 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BAA74 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (332)); // lwz r0, 332(r9)
    /* 0x800BAA78 */ ctx.r[0] = ctx.r[0] | 0x40000000u; // oris r0, r0, 0x4000
    /* 0x800BAA7C */ mem.write_u32(ctx.r[9] + (332), ctx.r[0]); // stw r0, 332(r9)
    /* 0x800BAA80 */ goto loc_800BAB68; // b 0x800BAB68 <sub_800BAB68>
loc_800BAA84:;
    /* 0x800BAA84 */ AreaDoorEmCheck_80003F90(ctx, mem); // bl 0x80003F90 <AreaDoorEmCheck(void)>
    /* 0x800BAA88 */ ctx.r[30] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[30]), 0); // mr r30, r3
    /* 0x800BAA8C */ if (ctx.eval_bc(4, 2)) goto loc_800BAB68; // bc 4, 2, 0x800BAB68
    /* 0x800BAA90 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BAA94 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (336)); // lwz r0, 336(r11)
    /* 0x800BAA98 */ ctx.r[31] = mem.read_u32(ctx.r[11] + (324)); // lwz r31, 324(r11)
    /* 0x800BAA9C */ ctx.r[0] = ctx.r[0] | 0x00010000u; // oris r0, r0, 0x0001
    /* 0x800BAAA0 */ mem.write_u32(ctx.r[11] + (336), ctx.r[0]); // stw r0, 336(r11)
    /* 0x800BAAA4 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (4)); // lwz r9, 4(r31)
    /* 0x800BAAA8 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (0)); // lwz r0, 0(r31)
    /* 0x800BAAAC */ ctx.r[9] = ctx.r[9] - ctx.r[0]; // subf r9, r0, r9
    /* 0x800BAAB0 */ ctx.r[9] = ctx.srawi_op(ctx.r[9], 2u, false); // srawi r9, r9, 2
    /* 0x800BAAB4 */ ctx.cmp_u32(0, ctx.r[30], ctx.r[9]); // cmplw cr0, r30, r9
    /* 0x800BAAB8 */ if (ctx.eval_bc(12, 0)) goto loc_800BAAC8; // bc 12, 0, 0x800BAAC8
    /* 0x800BAABC */ ctx.r[3] = 0x80170000u; // lis r3, 0x8017
    /* 0x800BAAC0 */ ctx.r[3] = ctx.r[3] + (-12500); // addi r3, r3, -12500 -> 0x8016CF2C /* "vector" */
    /* 0x800BAAC4 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800BAAC8:;
    /* 0x800BAAC8 */ ctx.r[11] = mem.read_u32(ctx.r[31] + (0)); // lwz r11, 0(r31)
    /* 0x800BAACC */ ctx.r[10] = 0x00000080u; // li r10, 128
    /* 0x800BAAD0 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (0)); // lwz r9, 0(r11)
    /* 0x800BAAD4 */ mem.write_u8(ctx.r[9] + (1249), static_cast<uint8_t>(ctx.r[10])); // stb r10, 1249(r9)
    /* 0x800BAAD8 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29676)); // lwz r0, -29676(r13) [r405_bgm_fade]
    /* 0x800BAADC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BAAE0 */ if (ctx.eval_bc(4, 2)) goto loc_800BAAF8; // bc 4, 2, 0x800BAAF8
    /* 0x800BAAE4 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BAAE8 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BAAEC */ mem.write_u32(ctx.r[13] + (-29676), ctx.r[0]); // stw r0, -29676(r13) [r405_bgm_fade]
    /* 0x800BAAF0 */ ctx.r[4] = 0x000000C8u; // li r4, 200
    /* 0x800BAAF4 */ Snd_str_fadeout_800CD394(ctx, mem); // bl 0x800CD394 <Snd_str_fadeout(long, long)>
loc_800BAAF8:;
    /* 0x800BAAF8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29668)); // lwz r9, -29668(r13) [{anonymous}::demoWaitTimer]
    /* 0x800BAAFC */ ctx.r[9] = ctx.r[9] + (-1); // addi r9, r9, -1
    /* 0x800BAB00 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), -1); // cmpwi cr0, r9, -1
    /* 0x800BAB04 */ mem.write_u32(ctx.r[13] + (-29668), ctx.r[9]); // stw r9, -29668(r13) [{anonymous}::demoWaitTimer]
    /* 0x800BAB08 */ if (ctx.eval_bc(4, 2)) goto loc_800BAB68; // bc 4, 2, 0x800BAB68
    /* 0x800BAB0C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BAB10 */ ctx.r[3] = 0x0000000Eu; // li r3, 14
    /* 0x800BAB14 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800BAB18 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BAB1C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (336)); // lwz r0, 336(r9)
    /* 0x800BAB20 */ ctx.rlwinm(0, 0, 0u, 16u, 14u, false); // rlwinm r0, r0, 0, 16, 14
    /* 0x800BAB24 */ mem.write_u32(ctx.r[9] + (336), ctx.r[0]); // stw r0, 336(r9)
    /* 0x800BAB28 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
    /* 0x800BAB2C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BAB30 */ ctx.r[0] = 0x00000004u; // li r0, 4
    /* 0x800BAB34 */ mem.write_u8(ctx.r[11] + (260), static_cast<uint8_t>(ctx.r[0])); // stb r0, 260(r11)
    /* 0x800BAB38 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (332)); // lwz r9, 332(r11)
    /* 0x800BAB3C */ ctx.r[0] = mem.read_u32(ctx.r[11] + (328)); // lwz r0, 328(r11)
    /* 0x800BAB40 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BAB44 */ ctx.r[9] = ctx.r[9] | 0x08000000u; // oris r9, r9, 0x0800
    /* 0x800BAB48 */ ctx.r[0] = ctx.r[0] | 0x0008u; // ori r0, r0, 0x0008
    /* 0x800BAB4C */ mem.write_u32(ctx.r[11] + (332), ctx.r[9]); // stw r9, 332(r11)
    /* 0x800BAB50 */ mem.write_u32(ctx.r[11] + (328), ctx.r[0]); // stw r0, 328(r11)
    /* 0x800BAB54 */ mem.write_u8(ctx.r[10] + (261), static_cast<uint8_t>(ctx.r[30])); // stb r30, 261(r10)
    /* 0x800BAB58 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BAB5C */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[30])); // stb r30, 262(r9)
    /* 0x800BAB60 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BAB64 */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[30])); // stb r30, 263(r11)
loc_800BAB68:;
    /* 0x800BAB68 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (124)); // lwz r0, 124(r1)
    /* 0x800BAB6C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BAB70 */ ctx.lmw(mem, 29, ctx.r[1] + (108)); // lmw r29, 108(r1)
    /* 0x800BAB74 */ ctx.r[1] = ctx.r[1] + (120); // addi r1, r1, 120
    /* 0x800BAB78 */ return; // blr
}

// [0x800BAB7C] R509Init(void) (r509.obj, 33 insns / 0x84 bytes)
void R509Init_800BAB7C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BAB7C */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BAB80 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BAB84 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BAB88 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BAB8C */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BAB90 */ mem.write_u32(ctx.r[13] + (-29660), ctx.r[0]); // stw r0, -29660(r13) [str_req]
    /* 0x800BAB94 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (29012)); // lwz r9, 29012(r11)
    /* 0x800BAB98 */ mem.write_u32(ctx.r[13] + (-29664), ctx.r[0]); // stw r0, -29664(r13) [pEvent08]
    /* 0x800BAB9C */ ctx.r[0] = ctx.r[9] & 0x00800000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andis. r0, r9, 0x0080
    /* 0x800BABA0 */ if (ctx.eval_bc(4, 2)) goto loc_800BABF0; // bc 4, 2, 0x800BABF0
    /* 0x800BABA4 */ ctx.r[0] = ctx.r[9] | 0x00800000u; // oris r0, r9, 0x0080
    /* 0x800BABA8 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BABAC */ mem.write_u32(ctx.r[11] + (29012), ctx.r[0]); // stw r0, 29012(r11)
    /* 0x800BABB0 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BABB4 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BABB8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BABBC */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BABC0 */ mem.write_u32(ctx.r[13] + (-29664), ctx.r[0]); // stw r0, -29664(r13) [pEvent08]
    /* 0x800BABC4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BABC8 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BABCC */ ctx.r[4] = mem.read_u32(ctx.r[9] + (44)); // lwz r4, 44(r9)
    /* 0x800BABD0 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BABD4 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BABD8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BABDC */ ctx.r[11] = 0x00000001u; // li r11, 1
    /* 0x800BABE0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BABE4 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BABE8 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
    /* 0x800BABEC */ mem.write_u32(ctx.r[13] + (-29660), ctx.r[11]); // stw r11, -29660(r13) [str_req]
loc_800BABF0:;
    /* 0x800BABF0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BABF4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BABF8 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BABFC */ return; // blr
}

// [0x800BAC00] R509Main(void) (r509.obj, 120 insns / 0x1E0 bytes)
void R509Main_800BAC00(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BAC00 */ ctx.r[1] += (-80); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -80(r1)
    /* 0x800BAC04 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BAC08 */ mem.write_u32(ctx.r[1] + (76), ctx.r[31]); // stw r31, 76(r1)
    /* 0x800BAC0C */ mem.write_u32(ctx.r[1] + (84), ctx.r[0]); // stw r0, 84(r1)
    /* 0x800BAC10 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29664)); // lwz r3, -29664(r13) [pEvent08]
    /* 0x800BAC14 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BAC18 */ if (ctx.eval_bc(4, 2)) goto loc_800BAC70; // bc 4, 2, 0x800BAC70
    /* 0x800BAC1C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BAC20 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BAC24 */ ctx.r[11] = ctx.r[0] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x4000
    /* 0x800BAC28 */ if (ctx.eval_bc(12, 2)) goto loc_800BADA0; // bc 12, 2, 0x800BADA0
    /* 0x800BAC2C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BAC30 */ ctx.r[11] = ctx.r[0] & 0x00010000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0001
    /* 0x800BAC34 */ if (ctx.eval_bc(4, 2)) goto loc_800BADA0; // bc 4, 2, 0x800BADA0
    /* 0x800BAC38 */ ctx.r[0] = ctx.r[0] | 0x00010000u; // oris r0, r0, 0x0001
    /* 0x800BAC3C */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BAC40 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BAC44 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BAC48 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BAC4C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BAC50 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BAC54 */ mem.write_u32(ctx.r[13] + (-29664), ctx.r[0]); // stw r0, -29664(r13) [pEvent08]
    /* 0x800BAC58 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BAC5C */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BAC60 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (48)); // lwz r4, 48(r9)
    /* 0x800BAC64 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BAC68 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BAC6C */ goto loc_800BADA0; // b 0x800BADA0 <sub_800BADA0>
loc_800BAC70:;
    /* 0x800BAC70 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BAC74 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BAC78 */ if (ctx.eval_bc(12, 2)) goto loc_800BADA0; // bc 12, 2, 0x800BADA0
    /* 0x800BAC7C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BAC80 */ ctx.r[31] = 0x00000000u; // li r31, 0
    /* 0x800BAC84 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BAC88 */ ctx.r[9] = ctx.r[0] & 0x00010000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x0001
    /* 0x800BAC8C */ if (ctx.eval_bc(4, 2)) goto loc_800BAD14; // bc 4, 2, 0x800BAD14
    /* 0x800BAC90 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BAC94 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BAC98 */ ctx.f[12] = mem.read_f32(ctx.r[9] + (-12440)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12440(r9) [0x8016CF68]
    /* 0x800BAC9C */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BACA0 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-12436)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12436(r11) [0x8016CF6C]
    /* 0x800BACA4 */ ctx.r[8] = ctx.r[1] + (8); // addi r8, r1, 8
    /* 0x800BACA8 */ ctx.f[13] = mem.read_f32(ctx.r[10] + (-12432)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12432(r10) [0x8016CF70]
    /* 0x800BACAC */ ctx.r[7] = ctx.r[1] + (24); // addi r7, r1, 24
    /* 0x800BACB0 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r1)
    /* 0x800BACB4 */ ctx.r[11] = ctx.r[1] + (40); // addi r11, r1, 40
    /* 0x800BACB8 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r8)
    /* 0x800BACBC */ ctx.r[3] = ctx.r[11]; // mr r3, r11
    /* 0x800BACC0 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800BACC4 */ ctx.r[6] = ctx.r[1] + (56); // addi r6, r1, 56
    /* 0x800BACC8 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800BACCC */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BACD0 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r7)
    /* 0x800BACD4 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BACD8 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800BACDC */ ctx.r[9] = mem.read_u32(ctx.r[1] + (8)); // lwz r9, 8(r1)
    /* 0x800BACE0 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BACE4 */ ctx.r[10] = mem.read_u32(ctx.r[8] + (8)); // lwz r10, 8(r8)
    /* 0x800BACE8 */ mem.write_u32(ctx.r[1] + (40), ctx.r[9]); // stw r9, 40(r1)
    /* 0x800BACEC */ mem.write_u32(ctx.r[11] + (4), ctx.r[0]); // stw r0, 4(r11)
    /* 0x800BACF0 */ mem.write_u32(ctx.r[11] + (8), ctx.r[10]); // stw r10, 8(r11)
    /* 0x800BACF4 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (24)); // lwz r9, 24(r1)
    /* 0x800BACF8 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BACFC */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BAD00 */ mem.write_u32(ctx.r[1] + (56), ctx.r[9]); // stw r9, 56(r1)
    /* 0x800BAD04 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BAD08 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BAD0C */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BAD10 */ mem.write_u32(ctx.r[13] + (-29660), ctx.r[31]); // stw r31, -29660(r13) [str_req]
loc_800BAD14:;
    /* 0x800BAD14 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29664)); // lwz r11, -29664(r13) [pEvent08]
    /* 0x800BAD18 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BAD1C */ if (ctx.eval_bc(12, 2)) goto loc_800BAD3C; // bc 12, 2, 0x800BAD3C
    /* 0x800BAD20 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BAD24 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BAD28 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BAD2C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BAD30 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BAD34 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BAD38 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BAD3C:;
    /* 0x800BAD3C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BAD40 */ mem.write_u32(ctx.r[13] + (-29664), ctx.r[31]); // stw r31, -29664(r13) [pEvent08]
    /* 0x800BAD44 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BAD48 */ ctx.r[9] = ctx.r[0] & 0x00010000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x0001
    /* 0x800BAD4C */ if (ctx.eval_bc(12, 2)) goto loc_800BADA0; // bc 12, 2, 0x800BADA0
    /* 0x800BAD50 */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800BAD54 */ ctx.r[4] = 0x00000044u; // li r4, 68
    /* 0x800BAD58 */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800BAD5C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BAD60 */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800BAD64 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BAD68 */ ctx.r[0] = 0x00000004u; // li r0, 4
    /* 0x800BAD6C */ mem.write_u8(ctx.r[11] + (260), static_cast<uint8_t>(ctx.r[0])); // stb r0, 260(r11)
    /* 0x800BAD70 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (336)); // lwz r9, 336(r11)
    /* 0x800BAD74 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (328)); // lwz r0, 328(r11)
    /* 0x800BAD78 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BAD7C */ ctx.r[9] = ctx.r[9] | 0x20000000u; // oris r9, r9, 0x2000
    /* 0x800BAD80 */ ctx.r[0] = ctx.r[0] | 0x0008u; // ori r0, r0, 0x0008
    /* 0x800BAD84 */ mem.write_u32(ctx.r[11] + (336), ctx.r[9]); // stw r9, 336(r11)
    /* 0x800BAD88 */ mem.write_u32(ctx.r[11] + (328), ctx.r[0]); // stw r0, 328(r11)
    /* 0x800BAD8C */ mem.write_u8(ctx.r[10] + (261), static_cast<uint8_t>(ctx.r[31])); // stb r31, 261(r10)
    /* 0x800BAD90 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BAD94 */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[31])); // stb r31, 262(r9)
    /* 0x800BAD98 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BAD9C */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[31])); // stb r31, 263(r11)
loc_800BADA0:;
    /* 0x800BADA0 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29660)); // lwz r0, -29660(r13) [str_req]
    /* 0x800BADA4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BADA8 */ if (ctx.eval_bc(4, 2)) goto loc_800BADCC; // bc 4, 2, 0x800BADCC
    /* 0x800BADAC */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BADB0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BADB4 */ mem.write_u32(ctx.r[13] + (-29660), ctx.r[0]); // stw r0, -29660(r13) [str_req]
    /* 0x800BADB8 */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800BADBC */ ctx.r[5] = 0x00000002u; // li r5, 2
    /* 0x800BADC0 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BADC4 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BADC8 */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
loc_800BADCC:;
    /* 0x800BADCC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (84)); // lwz r0, 84(r1)
    /* 0x800BADD0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BADD4 */ ctx.r[31] = mem.read_u32(ctx.r[1] + (76)); // lwz r31, 76(r1)
    /* 0x800BADD8 */ ctx.r[1] = ctx.r[1] + (80); // addi r1, r1, 80
    /* 0x800BADDC */ return; // blr
}

// [0x800BADE0] R604Init(void) (r604.obj, 1 insns / 0x4 bytes)
void R604Init_800BADE0(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BADE0 */ return; // blr
}

// [0x800BADE4] R604Main(void) (r604.obj, 17 insns / 0x44 bytes)
void R604Main_800BADE4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BADE4 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BADE8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BADEC */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BADF0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BADF4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800BADF8 */ ctx.r[11] = ctx.r[0] & 0x00040000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0004
    /* 0x800BADFC */ if (ctx.eval_bc(4, 2)) goto loc_800BAE18; // bc 4, 2, 0x800BAE18
    /* 0x800BAE00 */ ctx.r[0] = ctx.r[0] | 0x00040000u; // oris r0, r0, 0x0004
    /* 0x800BAE04 */ ctx.r[3] = 0x00000011u; // li r3, 17
    /* 0x800BAE08 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800BAE0C */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800BAE10 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BAE14 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
loc_800BAE18:;
    /* 0x800BAE18 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BAE1C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BAE20 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BAE24 */ return; // blr
}

// [0x800BAE28] {anonymous}::setLight(void) (r60c.obj, 111 insns / 0x1BC bytes)
void anonymous___setLight_800BAE28(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BAE28 */ ctx.r[1] += (-72); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -72(r1)
    /* 0x800BAE2C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BAE30 */ mem.write_f64(ctx.r[1] + (56), ctx.f[30]); // stfd f30, 56(r1)
    /* 0x800BAE34 */ mem.write_f64(ctx.r[1] + (64), ctx.f[31]); // stfd f31, 64(r1)
    /* 0x800BAE38 */ ctx.stmw(mem, 24, ctx.r[1] + (24)); // stmw r24, 24(r1)
    /* 0x800BAE3C */ mem.write_u32(ctx.r[1] + (76), ctx.r[0]); // stw r0, 76(r1)
    /* 0x800BAE40 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BAE44 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BAE48 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12388)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12388(r9) [0x8016CF9C]
    /* 0x800BAE4C */ ctx.r[7] = 0x801C0000u; // lis r7, 0x801C
    /* 0x800BAE50 */ ctx.f[12] = mem.read_f32(ctx.r[11] + (-12384)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12384(r11) [0x8016CFA0]
    /* 0x800BAE54 */ ctx.r[10] = ctx.r[1] + (8); // addi r10, r1, 8
    /* 0x800BAE58 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800BAE5C */ ctx.r[8] = ctx.r[7] + (19132); // addi r8, r7, 19132 -> {anonymous}::light
    /* 0x800BAE60 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BAE64 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r10)
    /* 0x800BAE68 */ ctx.f[10] = mem.read_f32(ctx.r[9] + (-12380)); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // lfs f10, -12380(r9) [0x8016CFA4]
    /* 0x800BAE6C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[8]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r8, r10
    /* 0x800BAE70 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r10)
    /* 0x800BAE74 */ if (ctx.eval_bc(12, 2)) goto loc_800BAE88; // bc 12, 2, 0x800BAE88
    /* 0x800BAE78 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r1)
    /* 0x800BAE7C */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r8)
    /* 0x800BAE80 */ mem.write_f32(ctx.r[7] + (19132), static_cast<float>(ctx.f[0])); // stfs f0, 19132(r7) [{anonymous}::light]
    /* 0x800BAE84 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r8)
loc_800BAE88:;
    /* 0x800BAE88 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BAE8C */ mem.write_f32(ctx.r[8] + (12), static_cast<float>(ctx.f[10])); // stfs f10, 12(r8)
    /* 0x800BAE90 */ ctx.f[11] = mem.read_f32(ctx.r[9] + (-12376)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -12376(r9) [0x8016CFA8]
    /* 0x800BAE94 */ ctx.r[11] = ctx.r[8] + (20); // addi r11, r8, 20
    /* 0x800BAE98 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r11, r10
    /* 0x800BAE9C */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r1)
    /* 0x800BAEA0 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r10)
    /* 0x800BAEA4 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r10)
    /* 0x800BAEA8 */ if (ctx.eval_bc(12, 2)) goto loc_800BAEBC; // bc 12, 2, 0x800BAEBC
    /* 0x800BAEAC */ ctx.f[0] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r1)
    /* 0x800BAEB0 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r11)
    /* 0x800BAEB4 */ mem.write_f32(ctx.r[8] + (20), static_cast<float>(ctx.f[0])); // stfs f0, 20(r8)
    /* 0x800BAEB8 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r11)
loc_800BAEBC:;
    /* 0x800BAEBC */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800BAEC0 */ ctx.r[9] = ctx.r[8] + (40); // addi r9, r8, 40
    /* 0x800BAEC4 */ mem.write_f32(ctx.r[11] + (12), static_cast<float>(ctx.f[10])); // stfs f10, 12(r11)
    /* 0x800BAEC8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r9, r10
    /* 0x800BAECC */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r10)
    /* 0x800BAED0 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r10)
    /* 0x800BAED4 */ if (ctx.eval_bc(12, 2)) goto loc_800BAEE8; // bc 12, 2, 0x800BAEE8
    /* 0x800BAED8 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r1)
    /* 0x800BAEDC */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r9)
    /* 0x800BAEE0 */ mem.write_f32(ctx.r[8] + (40), static_cast<float>(ctx.f[0])); // stfs f0, 40(r8)
    /* 0x800BAEE4 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r9)
loc_800BAEE8:;
    /* 0x800BAEE8 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r1)
    /* 0x800BAEEC */ ctx.r[7] = ctx.r[8] + (60); // addi r7, r8, 60
    /* 0x800BAEF0 */ mem.write_f32(ctx.r[9] + (12), static_cast<float>(ctx.f[10])); // stfs f10, 12(r9)
    /* 0x800BAEF4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[7]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r7, r10
    /* 0x800BAEF8 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r10)
    /* 0x800BAEFC */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r10)
    /* 0x800BAF00 */ if (ctx.eval_bc(12, 2)) goto loc_800BAF14; // bc 12, 2, 0x800BAF14
    /* 0x800BAF04 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r1)
    /* 0x800BAF08 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r7)
    /* 0x800BAF0C */ mem.write_f32(ctx.r[8] + (60), static_cast<float>(ctx.f[0])); // stfs f0, 60(r8)
    /* 0x800BAF10 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r7)
loc_800BAF14:;
    /* 0x800BAF14 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BAF18 */ ctx.r[6] = ctx.r[8] + (80); // addi r6, r8, 80
    /* 0x800BAF1C */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-12372)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12372(r11) [0x8016CFAC]
    /* 0x800BAF20 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BAF24 */ ctx.f[11] = mem.read_f32(ctx.r[9] + (-12368)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -12368(r9) [0x8016CFB0]
    /* 0x800BAF28 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[6]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r6, r10
    /* 0x800BAF2C */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800BAF30 */ mem.write_f32(ctx.r[7] + (12), static_cast<float>(ctx.f[10])); // stfs f10, 12(r7)
    /* 0x800BAF34 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r10)
    /* 0x800BAF38 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r10)
    /* 0x800BAF3C */ if (ctx.eval_bc(12, 2)) goto loc_800BAF50; // bc 12, 2, 0x800BAF50
    /* 0x800BAF40 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r1)
    /* 0x800BAF44 */ mem.write_f32(ctx.r[6] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r6)
    /* 0x800BAF48 */ mem.write_f32(ctx.r[8] + (80), static_cast<float>(ctx.f[0])); // stfs f0, 80(r8)
    /* 0x800BAF4C */ mem.write_f32(ctx.r[6] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r6)
loc_800BAF50:;
    /* 0x800BAF50 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BAF54 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BAF58 */ ctx.f[30] = mem.read_f32(ctx.r[9] + (-12364)); ctx.ps0[30] = static_cast<float>(ctx.f[30]); // lfs f30, -12364(r9) [0x8016CFB4]
    /* 0x800BAF5C */ ctx.r[30] = ctx.r[8]; // mr r30, r8
    /* 0x800BAF60 */ ctx.f[31] = mem.read_f32(ctx.r[11] + (-12360)); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // lfs f31, -12360(r11) [0x8016CFB8]
    /* 0x800BAF64 */ ctx.r[31] = 0x00000000u; // li r31, 0
    /* 0x800BAF68 */ mem.write_f32(ctx.r[6] + (12), static_cast<float>(ctx.f[11])); // stfs f11, 12(r6)
    /* 0x800BAF6C */ ctx.r[24] = 0x00000002u; // li r24, 2
    /* 0x800BAF70 */ ctx.r[29] = 0x00000000u; // li r29, 0
    /* 0x800BAF74 */ ctx.r[25] = 0x00000001u; // li r25, 1
    /* 0x800BAF78 */ ctx.r[26] = 0x00000087u; // li r26, 135
    /* 0x800BAF7C */ ctx.r[27] = 0x000000DCu; // li r27, 220
    /* 0x800BAF80 */ ctx.r[28] = 0x000000EDu; // li r28, 237
loc_800BAF84:;
    /* 0x800BAF84 */ PullLight_8009AEB4(ctx, mem); // bl 0x8009AEB4 <PullLight(void)>
    /* 0x800BAF88 */ ctx.r[3] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // mr r3, r3
    /* 0x800BAF8C */ if (ctx.eval_bc(12, 2)) goto loc_800BAFB8; // bc 12, 2, 0x800BAFB8
    /* 0x800BAF90 */ mem.write_u8(ctx.r[3] + (1), static_cast<uint8_t>(ctx.r[24])); // stb r24, 1(r3)
    /* 0x800BAF94 */ mem.write_u8(ctx.r[3] + (2), static_cast<uint8_t>(ctx.r[29])); // stb r29, 2(r3)
    /* 0x800BAF98 */ mem.write_u8(ctx.r[3] + (3), static_cast<uint8_t>(ctx.r[25])); // stb r25, 3(r3)
    /* 0x800BAF9C */ mem.write_u8(ctx.r[3] + (20), static_cast<uint8_t>(ctx.r[26])); // stb r26, 20(r3)
    /* 0x800BAFA0 */ mem.write_u8(ctx.r[3] + (21), static_cast<uint8_t>(ctx.r[27])); // stb r27, 21(r3)
    /* 0x800BAFA4 */ mem.write_u8(ctx.r[3] + (22), static_cast<uint8_t>(ctx.r[28])); // stb r28, 22(r3)
    /* 0x800BAFA8 */ mem.write_u8(ctx.r[3] + (23), static_cast<uint8_t>(ctx.r[29])); // stb r29, 23(r3)
    /* 0x800BAFAC */ mem.write_f32(ctx.r[3] + (16), static_cast<float>(ctx.f[30])); // stfs f30, 16(r3)
    /* 0x800BAFB0 */ mem.write_f32(ctx.r[3] + (24), static_cast<float>(ctx.f[31])); // stfs f31, 24(r3)
    /* 0x800BAFB4 */ mem.write_u32(ctx.r[30] + (16), ctx.r[3]); // stw r3, 16(r30)
loc_800BAFB8:;
    /* 0x800BAFB8 */ ctx.r[31] = ctx.r[31] + (1); // addi r31, r31, 1
    /* 0x800BAFBC */ ctx.r[30] = ctx.r[30] + (20); // addi r30, r30, 20
    /* 0x800BAFC0 */ ctx.cmp_u32(0, ctx.r[31], 0x0004u); // cmplwi cr0, r31, 0x0004
    /* 0x800BAFC4 */ if (ctx.eval_bc(4, 1)) goto loc_800BAF84; // bc 4, 1, 0x800BAF84
    /* 0x800BAFC8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (76)); // lwz r0, 76(r1)
    /* 0x800BAFCC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BAFD0 */ ctx.lmw(mem, 24, ctx.r[1] + (24)); // lmw r24, 24(r1)
    /* 0x800BAFD4 */ ctx.f[30] = mem.read_f64(ctx.r[1] + (56)); // lfd f30, 56(r1)
    /* 0x800BAFD8 */ ctx.f[31] = mem.read_f64(ctx.r[1] + (64)); // lfd f31, 64(r1)
    /* 0x800BAFDC */ ctx.r[1] = ctx.r[1] + (72); // addi r1, r1, 72
    /* 0x800BAFE0 */ return; // blr
}

// [0x800BAFE4] {anonymous}::moveLight(void) (r60c.obj, 63 insns / 0xFC bytes)
void anonymous___moveLight_800BAFE4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BAFE4 */ ctx.r[1] += (-112); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -112(r1)
    /* 0x800BAFE8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BAFEC */ mem.write_f64(ctx.r[1] + (104), ctx.f[31]); // stfd f31, 104(r1)
    /* 0x800BAFF0 */ ctx.stmw(mem, 25, ctx.r[1] + (76)); // stmw r25, 76(r1)
    /* 0x800BAFF4 */ mem.write_u32(ctx.r[1] + (116), ctx.r[0]); // stw r0, 116(r1)
    /* 0x800BAFF8 */ ctx.r[9] = 0x801C0000u; // lis r9, 0x801C
    /* 0x800BAFFC */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BB000 */ ctx.r[9] = ctx.r[9] + (19132); // addi r9, r9, 19132 -> {anonymous}::light
    /* 0x800BB004 */ ctx.f[31] = mem.read_f32(ctx.r[11] + (-12356)); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // lfs f31, -12356(r11) [0x8016CFBC]
    /* 0x800BB008 */ ctx.r[30] = ctx.r[9]; // mr r30, r9
    /* 0x800BB00C */ ctx.r[28] = ctx.r[1] + (24); // addi r28, r1, 24
    /* 0x800BB010 */ ctx.r[25] = ctx.r[30] + (80); // addi r25, r30, 80
    /* 0x800BB014 */ ctx.r[26] = 0x00000000u; // li r26, 0
    /* 0x800BB018 */ ctx.r[27] = 0x80170000u; // lis r27, 0x8017
    /* 0x800BB01C */ ctx.r[29] = ctx.r[1] + (8); // addi r29, r1, 8
loc_800BB020:;
    /* 0x800BB020 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB024 */ ctx.r[31] = mem.read_u32(ctx.r[9] + (324)); // lwz r31, 324(r9)
    /* 0x800BB028 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (4)); // lwz r0, 4(r31)
    /* 0x800BB02C */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800BB030 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800BB034 */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800BB038 */ ctx.cmp_u32(0, ctx.r[26], ctx.r[0]); // cmplw cr0, r26, r0
    /* 0x800BB03C */ if (ctx.eval_bc(12, 0)) goto loc_800BB048; // bc 12, 0, 0x800BB048
    /* 0x800BB040 */ ctx.r[3] = ctx.r[27] + (-12396); // addi r3, r27, -12396 -> 0x8016CF94 /* "vector" */
    /* 0x800BB044 */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800BB048:;
    /* 0x800BB048 */ ctx.r[11] = mem.read_u32(ctx.r[31] + (0)); // lwz r11, 0(r31)
    /* 0x800BB04C */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800BB050 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800BB054 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (0)); // lwz r9, 0(r11)
    /* 0x800BB058 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r9)
    /* 0x800BB05C */ ctx.r[9] = ctx.r[9] + (192); // addi r9, r9, 192
    /* 0x800BB060 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800BB064 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800BB068 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[0])); // stfs f0, 12(r1)
    /* 0x800BB06C */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800BB070 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800BB074 */ GetXZAngle_800CEB4C(ctx, mem); // bl 0x800CEB4C <GetXZAngle(cVec &, cVec &)>
    /* 0x800BB078 */ ctx.r[3] = ctx.r[1] + (24); // addi r3, r1, 24
    /* 0x800BB07C */ ctx.r[4] = 0x00000079u; // li r4, 121
    /* 0x800BB080 */ ctx.call_indirect(0x80100EE0u, mem); // bl 0x80100EE0 <PSMTXRotRad>
    /* 0x800BB084 */ ctx.f[0] = mem.read_f32(ctx.r[30] + (12)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 12(r30)
    /* 0x800BB088 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800BB08C */ ctx.r[5] = mem.read_u32(ctx.r[30] + (16)); // lwz r5, 16(r30)
    /* 0x800BB090 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800BB094 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BB098 */ ctx.r[5] = ctx.r[5] + (4); // addi r5, r5, 4
    /* 0x800BB09C */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r1)
    /* 0x800BB0A0 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[31])); // stfs f31, 12(r1)
    /* 0x800BB0A4 */ ctx.call_indirect(0x80101CC8u, mem); // bl 0x80101CC8 <PSMTXMultVec>
    /* 0x800BB0A8 */ ctx.r[3] = mem.read_u32(ctx.r[30] + (16)); // lwz r3, 16(r30)
    /* 0x800BB0AC */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800BB0B0 */ ctx.r[30] = ctx.r[30] + (20); // addi r30, r30, 20
    /* 0x800BB0B4 */ ctx.r[3] = ctx.r[3] + (4); // addi r3, r3, 4
    /* 0x800BB0B8 */ ctx.r[5] = ctx.r[3]; // mr r5, r3
    /* 0x800BB0BC */ ctx.call_indirect(0x801038F4u, mem); // bl 0x801038F4 <PSVECAdd>
    /* 0x800BB0C0 */ ctx.cmp_u32(0, ctx.r[30], ctx.r[25]); // cmplw cr0, r30, r25
    /* 0x800BB0C4 */ if (ctx.eval_bc(4, 1)) goto loc_800BB020; // bc 4, 1, 0x800BB020
    /* 0x800BB0C8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (116)); // lwz r0, 116(r1)
    /* 0x800BB0CC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB0D0 */ ctx.lmw(mem, 25, ctx.r[1] + (76)); // lmw r25, 76(r1)
    /* 0x800BB0D4 */ ctx.f[31] = mem.read_f64(ctx.r[1] + (104)); // lfd f31, 104(r1)
    /* 0x800BB0D8 */ ctx.r[1] = ctx.r[1] + (112); // addi r1, r1, 112
    /* 0x800BB0DC */ return; // blr
}

// [0x800BB0E0] R60cInit(void) (r60c.obj, 36 insns / 0x90 bytes)
void R60cInit_800BB0E0(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB0E0 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB0E4 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB0E8 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB0EC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BB0F0 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BB0F4 */ mem.write_u32(ctx.r[13] + (-29648), ctx.r[0]); // stw r0, -29648(r13) [str_req]
    /* 0x800BB0F8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (29012)); // lwz r9, 29012(r11)
    /* 0x800BB0FC */ mem.write_u32(ctx.r[13] + (-29656), ctx.r[0]); // stw r0, -29656(r13) [pEvent09]
    /* 0x800BB100 */ mem.write_u32(ctx.r[13] + (-29652), ctx.r[0]); // stw r0, -29652(r13) [pEvent10]
    /* 0x800BB104 */ ctx.r[0] = ctx.r[9] & 0x00400000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andis. r0, r9, 0x0040
    /* 0x800BB108 */ if (ctx.eval_bc(4, 2)) goto loc_800BB15C; // bc 4, 2, 0x800BB15C
    /* 0x800BB10C */ ctx.r[0] = ctx.r[9] | 0x00400000u; // oris r0, r9, 0x0040
    /* 0x800BB110 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BB114 */ mem.write_u32(ctx.r[11] + (29012), ctx.r[0]); // stw r0, 29012(r11)
    /* 0x800BB118 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BB11C */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BB120 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BB124 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BB128 */ mem.write_u32(ctx.r[13] + (-29656), ctx.r[0]); // stw r0, -29656(r13) [pEvent09]
    /* 0x800BB12C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BB130 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BB134 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (44)); // lwz r4, 44(r9)
    /* 0x800BB138 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BB13C */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BB140 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB144 */ ctx.r[11] = 0x00000001u; // li r11, 1
    /* 0x800BB148 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BB14C */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BB150 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
    /* 0x800BB154 */ mem.write_u32(ctx.r[13] + (-29648), ctx.r[11]); // stw r11, -29648(r13) [str_req]
    /* 0x800BB158 */ goto loc_800BB160; // b 0x800BB160 <sub_800BB160>
loc_800BB15C:;
    /* 0x800BB15C */ anonymous___setLight_800BAE28(ctx, mem); // bl 0x800BAE28 <{anonymous}::setLight(void)>
loc_800BB160:;
    /* 0x800BB160 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB164 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB168 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB16C */ return; // blr
}

// [0x800BB170] R60cMain(void) (r60c.obj, 138 insns / 0x228 bytes)
void R60cMain_800BB170(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB170 */ ctx.r[1] += (-80); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -80(r1)
    /* 0x800BB174 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB178 */ ctx.stmw(mem, 30, ctx.r[1] + (72)); // stmw r30, 72(r1)
    /* 0x800BB17C */ mem.write_u32(ctx.r[1] + (84), ctx.r[0]); // stw r0, 84(r1)
    /* 0x800BB180 */ ctx.r[30] = mem.read_u32(ctx.r[13] + (-29656)); // lwz r30, -29656(r13) [pEvent09]
    /* 0x800BB184 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[30]), 0); // cmpwi cr0, r30, 0
    /* 0x800BB188 */ if (ctx.eval_bc(12, 2)) goto loc_800BB250; // bc 12, 2, 0x800BB250
    /* 0x800BB18C */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800BB190 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BB194 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BB198 */ if (ctx.eval_bc(12, 2)) goto loc_800BB344; // bc 12, 2, 0x800BB344
    /* 0x800BB19C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29656)); // lwz r11, -29656(r13) [pEvent09]
    /* 0x800BB1A0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BB1A4 */ if (ctx.eval_bc(12, 2)) goto loc_800BB1C4; // bc 12, 2, 0x800BB1C4
    /* 0x800BB1A8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BB1AC */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BB1B0 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BB1B4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BB1B8 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BB1BC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB1C0 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BB1C4:;
    /* 0x800BB1C4 */ ctx.r[30] = 0x00000000u; // li r30, 0
    /* 0x800BB1C8 */ mem.write_u32(ctx.r[13] + (-29656), ctx.r[30]); // stw r30, -29656(r13) [pEvent09]
    /* 0x800BB1CC */ anonymous___setLight_800BAE28(ctx, mem); // bl 0x800BAE28 <{anonymous}::setLight(void)>
    /* 0x800BB1D0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BB1D4 */ ctx.r[10] = ctx.r[1] + (8); // addi r10, r1, 8
    /* 0x800BB1D8 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-12352)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12352(r11) [0x8016CFC0]
    /* 0x800BB1DC */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BB1E0 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12348)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12348(r9) [0x8016CFC4]
    /* 0x800BB1E4 */ ctx.r[8] = ctx.r[1] + (24); // addi r8, r1, 24
    /* 0x800BB1E8 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800BB1EC */ ctx.r[11] = ctx.r[1] + (40); // addi r11, r1, 40
    /* 0x800BB1F0 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800BB1F4 */ ctx.r[3] = ctx.r[11]; // mr r3, r11
    /* 0x800BB1F8 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800BB1FC */ ctx.r[6] = ctx.r[1] + (56); // addi r6, r1, 56
    /* 0x800BB200 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800BB204 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BB208 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r8)
    /* 0x800BB20C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BB210 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r8)
    /* 0x800BB214 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (8)); // lwz r9, 8(r1)
    /* 0x800BB218 */ ctx.r[0] = mem.read_u32(ctx.r[10] + (4)); // lwz r0, 4(r10)
    /* 0x800BB21C */ ctx.r[7] = mem.read_u32(ctx.r[10] + (8)); // lwz r7, 8(r10)
    /* 0x800BB220 */ mem.write_u32(ctx.r[1] + (40), ctx.r[9]); // stw r9, 40(r1)
    /* 0x800BB224 */ mem.write_u32(ctx.r[11] + (4), ctx.r[0]); // stw r0, 4(r11)
    /* 0x800BB228 */ mem.write_u32(ctx.r[11] + (8), ctx.r[7]); // stw r7, 8(r11)
    /* 0x800BB22C */ ctx.r[9] = mem.read_u32(ctx.r[1] + (24)); // lwz r9, 24(r1)
    /* 0x800BB230 */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BB234 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BB238 */ mem.write_u32(ctx.r[1] + (56), ctx.r[9]); // stw r9, 56(r1)
    /* 0x800BB23C */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BB240 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BB244 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BB248 */ mem.write_u32(ctx.r[13] + (-29648), ctx.r[30]); // stw r30, -29648(r13) [str_req]
    /* 0x800BB24C */ goto loc_800BB344; // b 0x800BB344 <sub_800BB344>
loc_800BB250:;
    /* 0x800BB250 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29652)); // lwz r3, -29652(r13) [pEvent10]
    /* 0x800BB254 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BB258 */ if (ctx.eval_bc(12, 2)) goto loc_800BB2E8; // bc 12, 2, 0x800BB2E8
    /* 0x800BB25C */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BB260 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BB264 */ if (ctx.eval_bc(12, 2)) goto loc_800BB344; // bc 12, 2, 0x800BB344
    /* 0x800BB268 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29652)); // lwz r11, -29652(r13) [pEvent10]
    /* 0x800BB26C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BB270 */ if (ctx.eval_bc(12, 2)) goto loc_800BB290; // bc 12, 2, 0x800BB290
    /* 0x800BB274 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BB278 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BB27C */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BB280 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BB284 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BB288 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB28C */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BB290:;
    /* 0x800BB290 */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800BB294 */ mem.write_u32(ctx.r[13] + (-29652), ctx.r[30]); // stw r30, -29652(r13) [pEvent10]
    /* 0x800BB298 */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800BB29C */ ctx.r[4] = 0x00000042u; // li r4, 66
    /* 0x800BB2A0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BB2A4 */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800BB2A8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BB2AC */ ctx.r[0] = 0x00000004u; // li r0, 4
    /* 0x800BB2B0 */ mem.write_u8(ctx.r[11] + (260), static_cast<uint8_t>(ctx.r[0])); // stb r0, 260(r11)
    /* 0x800BB2B4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (328)); // lwz r9, 328(r11)
    /* 0x800BB2B8 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (336)); // lwz r0, 336(r11)
    /* 0x800BB2BC */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BB2C0 */ ctx.r[9] = ctx.r[9] | 0x0008u; // ori r9, r9, 0x0008
    /* 0x800BB2C4 */ ctx.r[0] = ctx.r[0] | 0x20000000u; // oris r0, r0, 0x2000
    /* 0x800BB2C8 */ mem.write_u32(ctx.r[11] + (328), ctx.r[9]); // stw r9, 328(r11)
    /* 0x800BB2CC */ mem.write_u32(ctx.r[11] + (336), ctx.r[0]); // stw r0, 336(r11)
    /* 0x800BB2D0 */ mem.write_u8(ctx.r[10] + (261), static_cast<uint8_t>(ctx.r[30])); // stb r30, 261(r10)
    /* 0x800BB2D4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB2D8 */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[30])); // stb r30, 262(r9)
    /* 0x800BB2DC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BB2E0 */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[30])); // stb r30, 263(r11)
    /* 0x800BB2E4 */ goto loc_800BB344; // b 0x800BB344 <sub_800BB344>
loc_800BB2E8:;
    /* 0x800BB2E8 */ AreaDoorEmCheck_80003F90(ctx, mem); // bl 0x80003F90 <AreaDoorEmCheck(void)>
    /* 0x800BB2EC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BB2F0 */ if (ctx.eval_bc(4, 2)) goto loc_800BB344; // bc 4, 2, 0x800BB344
    /* 0x800BB2F4 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BB2F8 */ ctx.r[4] = 0x000000C8u; // li r4, 200
    /* 0x800BB2FC */ Snd_str_fadeout_800CD394(ctx, mem); // bl 0x800CD394 <Snd_str_fadeout(long, long)>
    /* 0x800BB300 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB304 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BB308 */ ctx.r[11] = ctx.r[0] & 0x00200000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0020
    /* 0x800BB30C */ if (ctx.eval_bc(4, 2)) goto loc_800BB344; // bc 4, 2, 0x800BB344
    /* 0x800BB310 */ ctx.r[0] = ctx.r[0] | 0x00200000u; // oris r0, r0, 0x0020
    /* 0x800BB314 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BB318 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BB31C */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BB320 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BB324 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BB328 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BB32C */ mem.write_u32(ctx.r[13] + (-29652), ctx.r[0]); // stw r0, -29652(r13) [pEvent10]
    /* 0x800BB330 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BB334 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BB338 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (48)); // lwz r4, 48(r9)
    /* 0x800BB33C */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BB340 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
loc_800BB344:;
    /* 0x800BB344 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29648)); // lwz r0, -29648(r13) [str_req]
    /* 0x800BB348 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BB34C */ if (ctx.eval_bc(4, 2)) goto loc_800BB370; // bc 4, 2, 0x800BB370
    /* 0x800BB350 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BB354 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BB358 */ mem.write_u32(ctx.r[13] + (-29648), ctx.r[0]); // stw r0, -29648(r13) [str_req]
    /* 0x800BB35C */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800BB360 */ ctx.r[5] = 0x00000002u; // li r5, 2
    /* 0x800BB364 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BB368 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BB36C */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
loc_800BB370:;
    /* 0x800BB370 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB374 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BB378 */ ctx.r[9] = ctx.r[0] & 0x1000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x1000
    /* 0x800BB37C */ if (ctx.eval_bc(4, 2)) goto loc_800BB384; // bc 4, 2, 0x800BB384
    /* 0x800BB380 */ anonymous___moveLight_800BAFE4(ctx, mem); // bl 0x800BAFE4 <{anonymous}::moveLight(void)>
loc_800BB384:;
    /* 0x800BB384 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (84)); // lwz r0, 84(r1)
    /* 0x800BB388 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB38C */ ctx.lmw(mem, 30, ctx.r[1] + (72)); // lmw r30, 72(r1)
    /* 0x800BB390 */ ctx.r[1] = ctx.r[1] + (80); // addi r1, r1, 80
    /* 0x800BB394 */ return; // blr
}

// [0x800BB398] __static_initialization_and_destruction_0 (r60c.obj, 19 insns / 0x4C bytes)
void static_initialization_and_destruction_0_800BB398(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB398 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BB39C */ ctx.r[0] = ctx.r[0] | 0xFFFFu; // ori r0, r0, 0xFFFF
    /* 0x800BB3A0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[4]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r4, r0
    /* 0x800BB3A4 */ if (ctx.eval_bc(4, 2)) return; // bclr 4, 2
    /* 0x800BB3A8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BB3AC */ if (ctx.eval_bc(12, 2)) return; // bclr 12, 2
    /* 0x800BB3B0 */ ctx.r[0] = 0x00000005u; // li r0, 5
    /* 0x800BB3B4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BB3B8 */ ctx.ctr = ctx.r[0]; // mtctr r0
    /* 0x800BB3BC */ ctx.r[11] = 0x801C0000u; // lis r11, 0x801C
    /* 0x800BB3C0 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12344)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12344(r9) [0x8016CFC8]
    /* 0x800BB3C4 */ ctx.r[11] = ctx.r[11] + (19132); // addi r11, r11, 19132 -> {anonymous}::light
loc_800BB3C8:;
    /* 0x800BB3C8 */ mem.write_f32(ctx.r[11] + (0), static_cast<float>(ctx.f[0])); // stfs f0, 0(r11)
    /* 0x800BB3CC */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800BB3D0 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BB3D4 */ mem.write_f32(ctx.r[11] + (12), static_cast<float>(ctx.f[0])); // stfs f0, 12(r11)
    /* 0x800BB3D8 */ ctx.r[11] = ctx.r[11] + (20); // addi r11, r11, 20
    /* 0x800BB3DC */ if (ctx.eval_bc(16, 0)) goto loc_800BB3C8; // bc 16, 0, 0x800BB3C8
    /* 0x800BB3E0 */ return; // blr
}

// [0x800BB3E4] global constructors keyed to {anonymous}::setLight(void) (r60c.obj, 11 insns / 0x2C bytes)
void global_constructors_keyed_to__anonymous___setLight_800BB3E4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB3E4 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB3E8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB3EC */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB3F0 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BB3F4 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BB3F8 */ ctx.r[4] = ctx.r[4] | 0xFFFFu; // ori r4, r4, 0xFFFF
    /* 0x800BB3FC */ static_initialization_and_destruction_0_800BB398(ctx, mem); // bl 0x800BB398 <__static_initialization_and_destruction_0>
    /* 0x800BB400 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB404 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB408 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB40C */ return; // blr
}

// [0x800BB410] R706Init(void) (r706.obj, 1 insns / 0x4 bytes)
void R706Init_800BB410(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB410 */ return; // blr
}

// [0x800BB414] R706Main(void) (r706.obj, 17 insns / 0x44 bytes)
void R706Main_800BB414(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB414 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB418 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB41C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB420 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB424 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800BB428 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BB42C */ if (ctx.eval_bc(4, 2)) goto loc_800BB448; // bc 4, 2, 0x800BB448
    /* 0x800BB430 */ ctx.r[0] = ctx.r[0] | 0x00020000u; // oris r0, r0, 0x0002
    /* 0x800BB434 */ ctx.r[3] = 0x00000013u; // li r3, 19
    /* 0x800BB438 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800BB43C */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800BB440 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BB444 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
loc_800BB448:;
    /* 0x800BB448 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB44C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB450 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB454 */ return; // blr
}

// [0x800BB458] R70bInit(void) (r70b.obj, 3 insns / 0xC bytes)
void R70bInit_800BB458(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB458 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BB45C */ mem.write_u32(ctx.r[13] + (-29644), ctx.r[0]); // stw r0, -29644(r13) [pEvent16]
    /* 0x800BB460 */ return; // blr
}

// [0x800BB464] R70bMain(void) (r70b.obj, 68 insns / 0x110 bytes)
void R70bMain_800BB464(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB464 */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800BB468 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB46C */ ctx.stmw(mem, 30, ctx.r[1] + (8)); // stmw r30, 8(r1)
    /* 0x800BB470 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800BB474 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29644)); // lwz r3, -29644(r13) [pEvent16]
    /* 0x800BB478 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BB47C */ if (ctx.eval_bc(4, 2)) goto loc_800BB4D4; // bc 4, 2, 0x800BB4D4
    /* 0x800BB480 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB484 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BB488 */ ctx.r[11] = ctx.r[0] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x4000
    /* 0x800BB48C */ if (ctx.eval_bc(12, 2)) goto loc_800BB560; // bc 12, 2, 0x800BB560
    /* 0x800BB490 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BB494 */ ctx.r[11] = ctx.r[0] & 0x8000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andi. r11, r0, 0x8000
    /* 0x800BB498 */ if (ctx.eval_bc(4, 2)) goto loc_800BB560; // bc 4, 2, 0x800BB560
    /* 0x800BB49C */ ctx.r[0] = ctx.r[0] | 0x8000u; // ori r0, r0, 0x8000
    /* 0x800BB4A0 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BB4A4 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BB4A8 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BB4AC */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BB4B0 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BB4B4 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BB4B8 */ mem.write_u32(ctx.r[13] + (-29644), ctx.r[0]); // stw r0, -29644(r13) [pEvent16]
    /* 0x800BB4BC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BB4C0 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BB4C4 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (44)); // lwz r4, 44(r9)
    /* 0x800BB4C8 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BB4CC */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BB4D0 */ goto loc_800BB560; // b 0x800BB560 <sub_800BB560>
loc_800BB4D4:;
    /* 0x800BB4D4 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BB4D8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BB4DC */ if (ctx.eval_bc(12, 2)) goto loc_800BB560; // bc 12, 2, 0x800BB560
    /* 0x800BB4E0 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29644)); // lwz r11, -29644(r13) [pEvent16]
    /* 0x800BB4E4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BB4E8 */ if (ctx.eval_bc(12, 2)) goto loc_800BB508; // bc 12, 2, 0x800BB508
    /* 0x800BB4EC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BB4F0 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BB4F4 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BB4F8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BB4FC */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BB500 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB504 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BB508:;
    /* 0x800BB508 */ ctx.r[30] = 0x00000000u; // li r30, 0
    /* 0x800BB50C */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800BB510 */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800BB514 */ mem.write_u32(ctx.r[13] + (-29644), ctx.r[30]); // stw r30, -29644(r13) [pEvent16]
    /* 0x800BB518 */ ctx.r[4] = 0x00000044u; // li r4, 68
    /* 0x800BB51C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BB520 */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800BB524 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BB528 */ ctx.r[0] = 0x00000004u; // li r0, 4
    /* 0x800BB52C */ mem.write_u8(ctx.r[11] + (260), static_cast<uint8_t>(ctx.r[0])); // stb r0, 260(r11)
    /* 0x800BB530 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (336)); // lwz r9, 336(r11)
    /* 0x800BB534 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (328)); // lwz r0, 328(r11)
    /* 0x800BB538 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BB53C */ ctx.r[9] = ctx.r[9] | 0x20000000u; // oris r9, r9, 0x2000
    /* 0x800BB540 */ ctx.r[0] = ctx.r[0] | 0x0008u; // ori r0, r0, 0x0008
    /* 0x800BB544 */ mem.write_u32(ctx.r[11] + (336), ctx.r[9]); // stw r9, 336(r11)
    /* 0x800BB548 */ mem.write_u32(ctx.r[11] + (328), ctx.r[0]); // stw r0, 328(r11)
    /* 0x800BB54C */ mem.write_u8(ctx.r[10] + (261), static_cast<uint8_t>(ctx.r[30])); // stb r30, 261(r10)
    /* 0x800BB550 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB554 */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[30])); // stb r30, 262(r9)
    /* 0x800BB558 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BB55C */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[30])); // stb r30, 263(r11)
loc_800BB560:;
    /* 0x800BB560 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800BB564 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB568 */ ctx.lmw(mem, 30, ctx.r[1] + (8)); // lmw r30, 8(r1)
    /* 0x800BB56C */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800BB570 */ return; // blr
}

// [0x800BB574] R800Init(void) (r800.obj, 17 insns / 0x44 bytes)
void R800Init_800BB574(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB574 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB578 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB57C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB580 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB584 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BB588 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BB58C */ if (ctx.eval_bc(12, 2)) goto loc_800BB5A8; // bc 12, 2, 0x800BB5A8
    /* 0x800BB590 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BB594 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (40)); // lwz r3, 40(r9)
    /* 0x800BB598 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BB59C */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BB5A0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BB5A4 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
loc_800BB5A8:;
    /* 0x800BB5A8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB5AC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB5B0 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB5B4 */ return; // blr
}

// [0x800BB5B8] R801Init(void) (r801.obj, 17 insns / 0x44 bytes)
void R801Init_800BB5B8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB5B8 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB5BC */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB5C0 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB5C4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB5C8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BB5CC */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BB5D0 */ if (ctx.eval_bc(12, 2)) goto loc_800BB5EC; // bc 12, 2, 0x800BB5EC
    /* 0x800BB5D4 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BB5D8 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (48)); // lwz r3, 48(r9)
    /* 0x800BB5DC */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BB5E0 */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BB5E4 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BB5E8 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
loc_800BB5EC:;
    /* 0x800BB5EC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB5F0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB5F4 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB5F8 */ return; // blr
}

// [0x800BB5FC] R802Init(void) (r802.obj, 17 insns / 0x44 bytes)
void R802Init_800BB5FC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB5FC */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB600 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB604 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB608 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB60C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BB610 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BB614 */ if (ctx.eval_bc(12, 2)) goto loc_800BB630; // bc 12, 2, 0x800BB630
    /* 0x800BB618 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BB61C */ ctx.r[3] = mem.read_u32(ctx.r[9] + (48)); // lwz r3, 48(r9)
    /* 0x800BB620 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BB624 */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BB628 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BB62C */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
loc_800BB630:;
    /* 0x800BB630 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB634 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB638 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB63C */ return; // blr
}

// [0x800BB640] R803Init(void) (r803.obj, 17 insns / 0x44 bytes)
void R803Init_800BB640(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB640 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB644 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB648 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB64C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB650 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BB654 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BB658 */ if (ctx.eval_bc(12, 2)) goto loc_800BB674; // bc 12, 2, 0x800BB674
    /* 0x800BB65C */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BB660 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (48)); // lwz r3, 48(r9)
    /* 0x800BB664 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BB668 */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BB66C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BB670 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
loc_800BB674:;
    /* 0x800BB674 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB678 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB67C */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB680 */ return; // blr
}

// [0x800BB684] R804Init(void) (r804.obj, 35 insns / 0x8C bytes)
void R804Init_800BB684(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB684 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB688 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB68C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB690 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB694 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BB698 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BB69C */ if (ctx.eval_bc(12, 2)) goto loc_800BB700; // bc 12, 2, 0x800BB700
    /* 0x800BB6A0 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BB6A4 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (48)); // lwz r3, 48(r9)
    /* 0x800BB6A8 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BB6AC */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BB6B0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BB6B4 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
    /* 0x800BB6B8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB6BC */ ctx.r[10] = mem.read_u32(ctx.r[9] + (25484)); // lwz r10, 25484(r9)
    /* 0x800BB6C0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // cmpwi cr0, r10, 0
    /* 0x800BB6C4 */ if (ctx.eval_bc(12, 2)) goto loc_800BB700; // bc 12, 2, 0x800BB700
    /* 0x800BB6C8 */ ctx.r[9] = mem.read_u16(ctx.r[10] + (4)); // lhz r9, 4(r10)
    /* 0x800BB6CC */ ctx.r[11] = 0x00000000u; // li r11, 0
    /* 0x800BB6D0 */ ctx.r[0] = mem.read_u16(ctx.r[10] + (6)); // lhz r0, 6(r10)
    /* 0x800BB6D4 */ ctx.r[9] = ctx.r[10] + ctx.r[9]; // add r9, r10, r9
    /* 0x800BB6D8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r11, r0
    /* 0x800BB6DC */ if (ctx.eval_bc(4, 0)) goto loc_800BB700; // bc 4, 0, 0x800BB700
loc_800BB6E0:;
    /* 0x800BB6E0 */ ctx.r[0] = mem.read_u8(ctx.r[9] + (54)); // lbz r0, 54(r9)
    /* 0x800BB6E4 */ ctx.r[11] = ctx.r[11] + (1); // addi r11, r11, 1
    /* 0x800BB6E8 */ ctx.rlwinm(0, 0, 0u, 24u, 30u, false); // rlwinm r0, r0, 0, 24, 30
    /* 0x800BB6EC */ mem.write_u8(ctx.r[9] + (54), static_cast<uint8_t>(ctx.r[0])); // stb r0, 54(r9)
    /* 0x800BB6F0 */ ctx.r[9] = ctx.r[9] + (72); // addi r9, r9, 72
    /* 0x800BB6F4 */ ctx.r[0] = mem.read_u16(ctx.r[10] + (6)); // lhz r0, 6(r10)
    /* 0x800BB6F8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r11, r0
    /* 0x800BB6FC */ if (ctx.eval_bc(12, 0)) goto loc_800BB6E0; // bc 12, 0, 0x800BB6E0
loc_800BB700:;
    /* 0x800BB700 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB704 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB708 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB70C */ return; // blr
}

// [0x800BB710] R804Main(void) (r804.obj, 17 insns / 0x44 bytes)
void R804Main_800BB710(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB710 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB714 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB718 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB71C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB720 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800BB724 */ ctx.r[11] = ctx.r[0] & 0x00010000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0001
    /* 0x800BB728 */ if (ctx.eval_bc(4, 2)) goto loc_800BB744; // bc 4, 2, 0x800BB744
    /* 0x800BB72C */ ctx.r[0] = ctx.r[0] | 0x00010000u; // oris r0, r0, 0x0001
    /* 0x800BB730 */ ctx.r[3] = 0x00000015u; // li r3, 21
    /* 0x800BB734 */ mem.write_u32(ctx.r[9] + (29016), ctx.r[0]); // stw r0, 29016(r9)
    /* 0x800BB738 */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800BB73C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BB740 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
loc_800BB744:;
    /* 0x800BB744 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB748 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB74C */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB750 */ return; // blr
}

// [0x800BB754] R805Init(void) (r805.obj, 17 insns / 0x44 bytes)
void R805Init_800BB754(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB754 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB758 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB75C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB760 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB764 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BB768 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BB76C */ if (ctx.eval_bc(12, 2)) goto loc_800BB788; // bc 12, 2, 0x800BB788
    /* 0x800BB770 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BB774 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (48)); // lwz r3, 48(r9)
    /* 0x800BB778 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BB77C */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BB780 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BB784 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
loc_800BB788:;
    /* 0x800BB788 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB78C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB790 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB794 */ return; // blr
}

// [0x800BB798] R806Init(void) (r806.obj, 38 insns / 0x98 bytes)
void R806Init_800BB798(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB798 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB79C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB7A0 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB7A4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB7A8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BB7AC */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BB7B0 */ if (ctx.eval_bc(12, 2)) goto loc_800BB820; // bc 12, 2, 0x800BB820
    /* 0x800BB7B4 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BB7B8 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (48)); // lwz r3, 48(r9)
    /* 0x800BB7BC */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BB7C0 */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BB7C4 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BB7C8 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
    /* 0x800BB7CC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB7D0 */ ctx.r[10] = mem.read_u32(ctx.r[9] + (25484)); // lwz r10, 25484(r9)
    /* 0x800BB7D4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // cmpwi cr0, r10, 0
    /* 0x800BB7D8 */ if (ctx.eval_bc(12, 2)) goto loc_800BB820; // bc 12, 2, 0x800BB820
    /* 0x800BB7DC */ ctx.r[9] = mem.read_u16(ctx.r[10] + (4)); // lhz r9, 4(r10)
    /* 0x800BB7E0 */ ctx.r[11] = 0x00000000u; // li r11, 0
    /* 0x800BB7E4 */ ctx.r[0] = mem.read_u16(ctx.r[10] + (6)); // lhz r0, 6(r10)
    /* 0x800BB7E8 */ ctx.r[9] = ctx.r[10] + ctx.r[9]; // add r9, r10, r9
    /* 0x800BB7EC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r11, r0
    /* 0x800BB7F0 */ if (ctx.eval_bc(4, 0)) goto loc_800BB820; // bc 4, 0, 0x800BB820
loc_800BB7F4:;
    /* 0x800BB7F4 */ ctx.r[0] = mem.read_u16(ctx.r[9] + (52)); // lhz r0, 52(r9)
    /* 0x800BB7F8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 2055); // cmpwi cr0, r0, 2055
    /* 0x800BB7FC */ if (ctx.eval_bc(4, 2)) goto loc_800BB80C; // bc 4, 2, 0x800BB80C
    /* 0x800BB800 */ ctx.r[0] = mem.read_u8(ctx.r[9] + (54)); // lbz r0, 54(r9)
    /* 0x800BB804 */ ctx.r[0] = ctx.r[0] | 0x0001u; // ori r0, r0, 0x0001
    /* 0x800BB808 */ mem.write_u8(ctx.r[9] + (54), static_cast<uint8_t>(ctx.r[0])); // stb r0, 54(r9)
loc_800BB80C:;
    /* 0x800BB80C */ ctx.r[0] = mem.read_u16(ctx.r[10] + (6)); // lhz r0, 6(r10)
    /* 0x800BB810 */ ctx.r[11] = ctx.r[11] + (1); // addi r11, r11, 1
    /* 0x800BB814 */ ctx.r[9] = ctx.r[9] + (72); // addi r9, r9, 72
    /* 0x800BB818 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r11, r0
    /* 0x800BB81C */ if (ctx.eval_bc(12, 0)) goto loc_800BB7F4; // bc 12, 0, 0x800BB7F4
loc_800BB820:;
    /* 0x800BB820 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB824 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB828 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB82C */ return; // blr
}

// [0x800BB830] R807Init(void) (r807.obj, 81 insns / 0x144 bytes)
void R807Init_800BB830(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB830 */ ctx.r[1] += (-80); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -80(r1)
    /* 0x800BB834 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB838 */ mem.write_f64(ctx.r[1] + (64), ctx.f[30]); // stfd f30, 64(r1)
    /* 0x800BB83C */ mem.write_f64(ctx.r[1] + (72), ctx.f[31]); // stfd f31, 72(r1)
    /* 0x800BB840 */ ctx.stmw(mem, 25, ctx.r[1] + (36)); // stmw r25, 36(r1)
    /* 0x800BB844 */ mem.write_u32(ctx.r[1] + (84), ctx.r[0]); // stw r0, 84(r1)
    /* 0x800BB848 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB84C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BB850 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BB854 */ if (ctx.eval_bc(12, 2)) goto loc_800BB958; // bc 12, 2, 0x800BB958
    /* 0x800BB858 */ ctx.r[28] = mem.read_u32(ctx.r[9] + (25484)); // lwz r28, 25484(r9)
    /* 0x800BB85C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[28]), 0); // cmpwi cr0, r28, 0
    /* 0x800BB860 */ if (ctx.eval_bc(12, 2)) goto loc_800BB958; // bc 12, 2, 0x800BB958
    /* 0x800BB864 */ ctx.r[9] = mem.read_u16(ctx.r[28] + (4)); // lhz r9, 4(r28)
    /* 0x800BB868 */ ctx.r[27] = 0x00000000u; // li r27, 0
    /* 0x800BB86C */ ctx.r[0] = mem.read_u16(ctx.r[28] + (6)); // lhz r0, 6(r28)
    /* 0x800BB870 */ ctx.r[31] = ctx.r[28] + ctx.r[9]; // add r31, r28, r9
    /* 0x800BB874 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[27]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r27, r0
    /* 0x800BB878 */ if (ctx.eval_bc(4, 0)) goto loc_800BB958; // bc 4, 0, 0x800BB958
    /* 0x800BB87C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BB880 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BB884 */ ctx.f[31] = mem.read_f32(ctx.r[9] + (-12212)); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // lfs f31, -12212(r9) [0x8016D04C]
    /* 0x800BB888 */ ctx.r[29] = ctx.r[1] + (16); // addi r29, r1, 16
    /* 0x800BB88C */ ctx.f[30] = mem.read_f32(ctx.r[11] + (-12208)); ctx.ps0[30] = static_cast<float>(ctx.f[30]); // lfs f30, -12208(r11) [0x8016D050]
    /* 0x800BB890 */ ctx.r[25] = 0x00000000u; // li r25, 0
    /* 0x800BB894 */ ctx.r[26] = 0x00000001u; // li r26, 1
loc_800BB898:;
    /* 0x800BB898 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (54)); // lbz r0, 54(r31)
    /* 0x800BB89C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 2); // cmpwi cr0, r0, 2
    /* 0x800BB8A0 */ if (ctx.eval_bc(4, 2)) goto loc_800BB944; // bc 4, 2, 0x800BB944
    /* 0x800BB8A4 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[31])); // stfs f31, 16(r1)
    /* 0x800BB8A8 */ ctx.r[4] = 0x0000003Cu; // li r4, 60
    /* 0x800BB8AC */ mem.write_f32(ctx.r[29] + (4), static_cast<float>(ctx.f[31])); // stfs f31, 4(r29)
    /* 0x800BB8B0 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800BB8B4 */ mem.write_f32(ctx.r[29] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r29)
    /* 0x800BB8B8 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (28)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 28(r31)
    /* 0x800BB8BC */ ctx.f[0] = mem.read_f32(ctx.r[31] + (20)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 20(r31)
    /* 0x800BB8C0 */ ctx.f[11] = mem.read_f32(ctx.r[31] + (36)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 36(r31)
    /* 0x800BB8C4 */ ctx.f[12] = mem.read_f32(ctx.r[31] + (44)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 44(r31)
    /* 0x800BB8C8 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f13
    /* 0x800BB8CC */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f11
    /* 0x800BB8D0 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[12]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f12
    /* 0x800BB8D4 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[30]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f30
    /* 0x800BB8D8 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BB8DC */ ctx.f[13] = mem.read_f32(ctx.r[31] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r31)
    /* 0x800BB8E0 */ mem.write_f32(ctx.r[1] + (20), static_cast<float>(ctx.f[13])); // stfs f13, 20(r1)
    /* 0x800BB8E4 */ ctx.f[13] = mem.read_f32(ctx.r[31] + (32)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 32(r31)
    /* 0x800BB8E8 */ ctx.f[0] = mem.read_f32(ctx.r[31] + (24)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 24(r31)
    /* 0x800BB8EC */ ctx.f[11] = mem.read_f32(ctx.r[31] + (40)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, 40(r31)
    /* 0x800BB8F0 */ ctx.f[12] = mem.read_f32(ctx.r[31] + (48)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 48(r31)
    /* 0x800BB8F4 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[13]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f13
    /* 0x800BB8F8 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f11
    /* 0x800BB8FC */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[12]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f12
    /* 0x800BB900 */ ctx.f[0] = static_cast<float>(ctx.f[0] * ctx.f[30]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fmuls f0, f0, f30
    /* 0x800BB904 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800BB908 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BB90C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BB910 */ ctx.r[3] = 0x00000028u; // li r3, 40
    /* 0x800BB914 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BB918 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BB91C */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BB920 */ mem.write_u32(ctx.r[1] + (8), ctx.r[25]); // stw r25, 8(r1)
    /* 0x800BB924 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BB928 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800BB92C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BB930 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800BB934 */ ctx.r[9] = 0x00000004u; // li r9, 4
    /* 0x800BB938 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BB93C */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800BB940 */ mem.write_u32(ctx.r[31] + (0), ctx.r[26]); // stw r26, 0(r31)
loc_800BB944:;
    /* 0x800BB944 */ ctx.r[0] = mem.read_u16(ctx.r[28] + (6)); // lhz r0, 6(r28)
    /* 0x800BB948 */ ctx.r[27] = ctx.r[27] + (1); // addi r27, r27, 1
    /* 0x800BB94C */ ctx.r[31] = ctx.r[31] + (72); // addi r31, r31, 72
    /* 0x800BB950 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[27]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r27, r0
    /* 0x800BB954 */ if (ctx.eval_bc(12, 0)) goto loc_800BB898; // bc 12, 0, 0x800BB898
loc_800BB958:;
    /* 0x800BB958 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (84)); // lwz r0, 84(r1)
    /* 0x800BB95C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB960 */ ctx.lmw(mem, 25, ctx.r[1] + (36)); // lmw r25, 36(r1)
    /* 0x800BB964 */ ctx.f[30] = mem.read_f64(ctx.r[1] + (64)); // lfd f30, 64(r1)
    /* 0x800BB968 */ ctx.f[31] = mem.read_f64(ctx.r[1] + (72)); // lfd f31, 72(r1)
    /* 0x800BB96C */ ctx.r[1] = ctx.r[1] + (80); // addi r1, r1, 80
    /* 0x800BB970 */ return; // blr
}

// [0x800BB974] R808Init(void) (r808.obj, 35 insns / 0x8C bytes)
void R808Init_800BB974(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BB974 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BB978 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BB97C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BB980 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB984 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BB988 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BB98C */ if (ctx.eval_bc(12, 2)) goto loc_800BB9F0; // bc 12, 2, 0x800BB9F0
    /* 0x800BB990 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BB994 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (48)); // lwz r3, 48(r9)
    /* 0x800BB998 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BB99C */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BB9A0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BB9A4 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
    /* 0x800BB9A8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BB9AC */ ctx.r[10] = mem.read_u32(ctx.r[9] + (25484)); // lwz r10, 25484(r9)
    /* 0x800BB9B0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // cmpwi cr0, r10, 0
    /* 0x800BB9B4 */ if (ctx.eval_bc(12, 2)) goto loc_800BB9F0; // bc 12, 2, 0x800BB9F0
    /* 0x800BB9B8 */ ctx.r[9] = mem.read_u16(ctx.r[10] + (4)); // lhz r9, 4(r10)
    /* 0x800BB9BC */ ctx.r[11] = 0x00000000u; // li r11, 0
    /* 0x800BB9C0 */ ctx.r[0] = mem.read_u16(ctx.r[10] + (6)); // lhz r0, 6(r10)
    /* 0x800BB9C4 */ ctx.r[9] = ctx.r[10] + ctx.r[9]; // add r9, r10, r9
    /* 0x800BB9C8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r11, r0
    /* 0x800BB9CC */ if (ctx.eval_bc(4, 0)) goto loc_800BB9F0; // bc 4, 0, 0x800BB9F0
loc_800BB9D0:;
    /* 0x800BB9D0 */ ctx.r[0] = mem.read_u8(ctx.r[9] + (54)); // lbz r0, 54(r9)
    /* 0x800BB9D4 */ ctx.r[11] = ctx.r[11] + (1); // addi r11, r11, 1
    /* 0x800BB9D8 */ ctx.rlwinm(0, 0, 0u, 24u, 30u, false); // rlwinm r0, r0, 0, 24, 30
    /* 0x800BB9DC */ mem.write_u8(ctx.r[9] + (54), static_cast<uint8_t>(ctx.r[0])); // stb r0, 54(r9)
    /* 0x800BB9E0 */ ctx.r[9] = ctx.r[9] + (72); // addi r9, r9, 72
    /* 0x800BB9E4 */ ctx.r[0] = mem.read_u16(ctx.r[10] + (6)); // lhz r0, 6(r10)
    /* 0x800BB9E8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r11, r0
    /* 0x800BB9EC */ if (ctx.eval_bc(12, 0)) goto loc_800BB9D0; // bc 12, 0, 0x800BB9D0
loc_800BB9F0:;
    /* 0x800BB9F0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BB9F4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BB9F8 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BB9FC */ return; // blr
}

// [0x800BBA00] R809Init(void) (r809.obj, 17 insns / 0x44 bytes)
void R809Init_800BBA00(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BBA00 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BBA04 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BBA08 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BBA0C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BBA10 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BBA14 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BBA18 */ if (ctx.eval_bc(12, 2)) goto loc_800BBA34; // bc 12, 2, 0x800BBA34
    /* 0x800BBA1C */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BBA20 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (48)); // lwz r3, 48(r9)
    /* 0x800BBA24 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BBA28 */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BBA2C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BBA30 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
loc_800BBA34:;
    /* 0x800BBA34 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BBA38 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BBA3C */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BBA40 */ return; // blr
}

// [0x800BBA44] R80aInit(void) (r80a.obj, 17 insns / 0x44 bytes)
void R80aInit_800BBA44(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BBA44 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BBA48 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BBA4C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BBA50 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BBA54 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BBA58 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BBA5C */ if (ctx.eval_bc(12, 2)) goto loc_800BBA78; // bc 12, 2, 0x800BBA78
    /* 0x800BBA60 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BBA64 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (44)); // lwz r3, 44(r9)
    /* 0x800BBA68 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BBA6C */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BBA70 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BBA74 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
loc_800BBA78:;
    /* 0x800BBA78 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BBA7C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BBA80 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BBA84 */ return; // blr
}

// [0x800BBA88] R80bInit(void) (r80b.obj, 17 insns / 0x44 bytes)
void R80bInit_800BBA88(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BBA88 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BBA8C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BBA90 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BBA94 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BBA98 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BBA9C */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BBAA0 */ if (ctx.eval_bc(12, 2)) goto loc_800BBABC; // bc 12, 2, 0x800BBABC
    /* 0x800BBAA4 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BBAA8 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (44)); // lwz r3, 44(r9)
    /* 0x800BBAAC */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BBAB0 */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BBAB4 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BBAB8 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
loc_800BBABC:;
    /* 0x800BBABC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BBAC0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BBAC4 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BBAC8 */ return; // blr
}

// [0x800BBACC] {anonymous}::lightChange(void) (r80c.obj, 17 insns / 0x44 bytes)
void anonymous___lightChange_800BBACC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BBACC */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BBAD0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BBAD4 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BBAD8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BBADC */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BBAE0 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BBAE4 */ if (ctx.eval_bc(12, 2)) goto loc_800BBB00; // bc 12, 2, 0x800BBB00
    /* 0x800BBAE8 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BBAEC */ ctx.r[3] = mem.read_u32(ctx.r[9] + (76)); // lwz r3, 76(r9)
    /* 0x800BBAF0 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BBAF4 */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BBAF8 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BBAFC */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
loc_800BBB00:;
    /* 0x800BBB00 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BBB04 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BBB08 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BBB0C */ return; // blr
}

// [0x800BBB10] {anonymous}::setLight(void) (r80c.obj, 111 insns / 0x1BC bytes)
void anonymous___setLight_800BBB10(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BBB10 */ ctx.r[1] += (-72); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -72(r1)
    /* 0x800BBB14 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BBB18 */ mem.write_f64(ctx.r[1] + (56), ctx.f[30]); // stfd f30, 56(r1)
    /* 0x800BBB1C */ mem.write_f64(ctx.r[1] + (64), ctx.f[31]); // stfd f31, 64(r1)
    /* 0x800BBB20 */ ctx.stmw(mem, 24, ctx.r[1] + (24)); // stmw r24, 24(r1)
    /* 0x800BBB24 */ mem.write_u32(ctx.r[1] + (76), ctx.r[0]); // stw r0, 76(r1)
    /* 0x800BBB28 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BBB2C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BBB30 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12128)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12128(r9) [0x8016D0A0]
    /* 0x800BBB34 */ ctx.r[7] = 0x801C0000u; // lis r7, 0x801C
    /* 0x800BBB38 */ ctx.f[12] = mem.read_f32(ctx.r[11] + (-12124)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12124(r11) [0x8016D0A4]
    /* 0x800BBB3C */ ctx.r[10] = ctx.r[1] + (8); // addi r10, r1, 8
    /* 0x800BBB40 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800BBB44 */ ctx.r[8] = ctx.r[7] + (19232); // addi r8, r7, 19232 -> {anonymous}::light
    /* 0x800BBB48 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BBB4C */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r10)
    /* 0x800BBB50 */ ctx.f[10] = mem.read_f32(ctx.r[9] + (-12120)); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // lfs f10, -12120(r9) [0x8016D0A8]
    /* 0x800BBB54 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[8]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r8, r10
    /* 0x800BBB58 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r10)
    /* 0x800BBB5C */ if (ctx.eval_bc(12, 2)) goto loc_800BBB70; // bc 12, 2, 0x800BBB70
    /* 0x800BBB60 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r1)
    /* 0x800BBB64 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r8)
    /* 0x800BBB68 */ mem.write_f32(ctx.r[7] + (19232), static_cast<float>(ctx.f[0])); // stfs f0, 19232(r7) [{anonymous}::light]
    /* 0x800BBB6C */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r8)
loc_800BBB70:;
    /* 0x800BBB70 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BBB74 */ mem.write_f32(ctx.r[8] + (12), static_cast<float>(ctx.f[10])); // stfs f10, 12(r8)
    /* 0x800BBB78 */ ctx.f[11] = mem.read_f32(ctx.r[9] + (-12116)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -12116(r9) [0x8016D0AC]
    /* 0x800BBB7C */ ctx.r[11] = ctx.r[8] + (20); // addi r11, r8, 20
    /* 0x800BBB80 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r11, r10
    /* 0x800BBB84 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r1)
    /* 0x800BBB88 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r10)
    /* 0x800BBB8C */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r10)
    /* 0x800BBB90 */ if (ctx.eval_bc(12, 2)) goto loc_800BBBA4; // bc 12, 2, 0x800BBBA4
    /* 0x800BBB94 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r1)
    /* 0x800BBB98 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r11)
    /* 0x800BBB9C */ mem.write_f32(ctx.r[8] + (20), static_cast<float>(ctx.f[0])); // stfs f0, 20(r8)
    /* 0x800BBBA0 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r11)
loc_800BBBA4:;
    /* 0x800BBBA4 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800BBBA8 */ ctx.r[9] = ctx.r[8] + (40); // addi r9, r8, 40
    /* 0x800BBBAC */ mem.write_f32(ctx.r[11] + (12), static_cast<float>(ctx.f[10])); // stfs f10, 12(r11)
    /* 0x800BBBB0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r9, r10
    /* 0x800BBBB4 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r10)
    /* 0x800BBBB8 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r10)
    /* 0x800BBBBC */ if (ctx.eval_bc(12, 2)) goto loc_800BBBD0; // bc 12, 2, 0x800BBBD0
    /* 0x800BBBC0 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r1)
    /* 0x800BBBC4 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r9)
    /* 0x800BBBC8 */ mem.write_f32(ctx.r[8] + (40), static_cast<float>(ctx.f[0])); // stfs f0, 40(r8)
    /* 0x800BBBCC */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r9)
loc_800BBBD0:;
    /* 0x800BBBD0 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r1)
    /* 0x800BBBD4 */ ctx.r[7] = ctx.r[8] + (60); // addi r7, r8, 60
    /* 0x800BBBD8 */ mem.write_f32(ctx.r[9] + (12), static_cast<float>(ctx.f[10])); // stfs f10, 12(r9)
    /* 0x800BBBDC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[7]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r7, r10
    /* 0x800BBBE0 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r10)
    /* 0x800BBBE4 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r10)
    /* 0x800BBBE8 */ if (ctx.eval_bc(12, 2)) goto loc_800BBBFC; // bc 12, 2, 0x800BBBFC
    /* 0x800BBBEC */ ctx.f[0] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r1)
    /* 0x800BBBF0 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r7)
    /* 0x800BBBF4 */ mem.write_f32(ctx.r[8] + (60), static_cast<float>(ctx.f[0])); // stfs f0, 60(r8)
    /* 0x800BBBF8 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r7)
loc_800BBBFC:;
    /* 0x800BBBFC */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BBC00 */ ctx.r[6] = ctx.r[8] + (80); // addi r6, r8, 80
    /* 0x800BBC04 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-12112)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12112(r11) [0x8016D0B0]
    /* 0x800BBC08 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BBC0C */ ctx.f[11] = mem.read_f32(ctx.r[9] + (-12108)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -12108(r9) [0x8016D0B4]
    /* 0x800BBC10 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[6]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r6, r10
    /* 0x800BBC14 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800BBC18 */ mem.write_f32(ctx.r[7] + (12), static_cast<float>(ctx.f[10])); // stfs f10, 12(r7)
    /* 0x800BBC1C */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r10)
    /* 0x800BBC20 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r10)
    /* 0x800BBC24 */ if (ctx.eval_bc(12, 2)) goto loc_800BBC38; // bc 12, 2, 0x800BBC38
    /* 0x800BBC28 */ ctx.f[0] = mem.read_f32(ctx.r[1] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r1)
    /* 0x800BBC2C */ mem.write_f32(ctx.r[6] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r6)
    /* 0x800BBC30 */ mem.write_f32(ctx.r[8] + (80), static_cast<float>(ctx.f[0])); // stfs f0, 80(r8)
    /* 0x800BBC34 */ mem.write_f32(ctx.r[6] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r6)
loc_800BBC38:;
    /* 0x800BBC38 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BBC3C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BBC40 */ ctx.f[30] = mem.read_f32(ctx.r[9] + (-12104)); ctx.ps0[30] = static_cast<float>(ctx.f[30]); // lfs f30, -12104(r9) [0x8016D0B8]
    /* 0x800BBC44 */ ctx.r[30] = ctx.r[8]; // mr r30, r8
    /* 0x800BBC48 */ ctx.f[31] = mem.read_f32(ctx.r[11] + (-12100)); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // lfs f31, -12100(r11) [0x8016D0BC]
    /* 0x800BBC4C */ ctx.r[31] = 0x00000000u; // li r31, 0
    /* 0x800BBC50 */ mem.write_f32(ctx.r[6] + (12), static_cast<float>(ctx.f[11])); // stfs f11, 12(r6)
    /* 0x800BBC54 */ ctx.r[24] = 0x00000002u; // li r24, 2
    /* 0x800BBC58 */ ctx.r[29] = 0x00000000u; // li r29, 0
    /* 0x800BBC5C */ ctx.r[25] = 0x00000001u; // li r25, 1
    /* 0x800BBC60 */ ctx.r[26] = 0x000000C6u; // li r26, 198
    /* 0x800BBC64 */ ctx.r[27] = 0x000000ACu; // li r27, 172
    /* 0x800BBC68 */ ctx.r[28] = 0x0000009Du; // li r28, 157
loc_800BBC6C:;
    /* 0x800BBC6C */ PullLight_8009AEB4(ctx, mem); // bl 0x8009AEB4 <PullLight(void)>
    /* 0x800BBC70 */ ctx.r[3] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // mr r3, r3
    /* 0x800BBC74 */ if (ctx.eval_bc(12, 2)) goto loc_800BBCA0; // bc 12, 2, 0x800BBCA0
    /* 0x800BBC78 */ mem.write_u8(ctx.r[3] + (1), static_cast<uint8_t>(ctx.r[24])); // stb r24, 1(r3)
    /* 0x800BBC7C */ mem.write_u8(ctx.r[3] + (2), static_cast<uint8_t>(ctx.r[29])); // stb r29, 2(r3)
    /* 0x800BBC80 */ mem.write_u8(ctx.r[3] + (3), static_cast<uint8_t>(ctx.r[25])); // stb r25, 3(r3)
    /* 0x800BBC84 */ mem.write_u8(ctx.r[3] + (20), static_cast<uint8_t>(ctx.r[26])); // stb r26, 20(r3)
    /* 0x800BBC88 */ mem.write_u8(ctx.r[3] + (21), static_cast<uint8_t>(ctx.r[27])); // stb r27, 21(r3)
    /* 0x800BBC8C */ mem.write_u8(ctx.r[3] + (22), static_cast<uint8_t>(ctx.r[28])); // stb r28, 22(r3)
    /* 0x800BBC90 */ mem.write_u8(ctx.r[3] + (23), static_cast<uint8_t>(ctx.r[29])); // stb r29, 23(r3)
    /* 0x800BBC94 */ mem.write_f32(ctx.r[3] + (16), static_cast<float>(ctx.f[30])); // stfs f30, 16(r3)
    /* 0x800BBC98 */ mem.write_f32(ctx.r[3] + (24), static_cast<float>(ctx.f[31])); // stfs f31, 24(r3)
    /* 0x800BBC9C */ mem.write_u32(ctx.r[30] + (16), ctx.r[3]); // stw r3, 16(r30)
loc_800BBCA0:;
    /* 0x800BBCA0 */ ctx.r[31] = ctx.r[31] + (1); // addi r31, r31, 1
    /* 0x800BBCA4 */ ctx.r[30] = ctx.r[30] + (20); // addi r30, r30, 20
    /* 0x800BBCA8 */ ctx.cmp_u32(0, ctx.r[31], 0x0004u); // cmplwi cr0, r31, 0x0004
    /* 0x800BBCAC */ if (ctx.eval_bc(4, 1)) goto loc_800BBC6C; // bc 4, 1, 0x800BBC6C
    /* 0x800BBCB0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (76)); // lwz r0, 76(r1)
    /* 0x800BBCB4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BBCB8 */ ctx.lmw(mem, 24, ctx.r[1] + (24)); // lmw r24, 24(r1)
    /* 0x800BBCBC */ ctx.f[30] = mem.read_f64(ctx.r[1] + (56)); // lfd f30, 56(r1)
    /* 0x800BBCC0 */ ctx.f[31] = mem.read_f64(ctx.r[1] + (64)); // lfd f31, 64(r1)
    /* 0x800BBCC4 */ ctx.r[1] = ctx.r[1] + (72); // addi r1, r1, 72
    /* 0x800BBCC8 */ return; // blr
}

// [0x800BBCCC] {anonymous}::moveLight(void) (r80c.obj, 63 insns / 0xFC bytes)
void anonymous___moveLight_800BBCCC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BBCCC */ ctx.r[1] += (-112); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -112(r1)
    /* 0x800BBCD0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BBCD4 */ mem.write_f64(ctx.r[1] + (104), ctx.f[31]); // stfd f31, 104(r1)
    /* 0x800BBCD8 */ ctx.stmw(mem, 25, ctx.r[1] + (76)); // stmw r25, 76(r1)
    /* 0x800BBCDC */ mem.write_u32(ctx.r[1] + (116), ctx.r[0]); // stw r0, 116(r1)
    /* 0x800BBCE0 */ ctx.r[9] = 0x801C0000u; // lis r9, 0x801C
    /* 0x800BBCE4 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BBCE8 */ ctx.r[9] = ctx.r[9] + (19232); // addi r9, r9, 19232 -> {anonymous}::light
    /* 0x800BBCEC */ ctx.f[31] = mem.read_f32(ctx.r[11] + (-12096)); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // lfs f31, -12096(r11) [0x8016D0C0]
    /* 0x800BBCF0 */ ctx.r[30] = ctx.r[9]; // mr r30, r9
    /* 0x800BBCF4 */ ctx.r[28] = ctx.r[1] + (24); // addi r28, r1, 24
    /* 0x800BBCF8 */ ctx.r[25] = ctx.r[30] + (80); // addi r25, r30, 80
    /* 0x800BBCFC */ ctx.r[26] = 0x00000000u; // li r26, 0
    /* 0x800BBD00 */ ctx.r[27] = 0x80170000u; // lis r27, 0x8017
    /* 0x800BBD04 */ ctx.r[29] = ctx.r[1] + (8); // addi r29, r1, 8
loc_800BBD08:;
    /* 0x800BBD08 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BBD0C */ ctx.r[31] = mem.read_u32(ctx.r[9] + (324)); // lwz r31, 324(r9)
    /* 0x800BBD10 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (4)); // lwz r0, 4(r31)
    /* 0x800BBD14 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800BBD18 */ ctx.r[0] = ctx.r[0] - ctx.r[9]; // subf r0, r9, r0
    /* 0x800BBD1C */ ctx.r[0] = ctx.srawi_op(ctx.r[0], 2u, false); // srawi r0, r0, 2
    /* 0x800BBD20 */ ctx.cmp_u32(0, ctx.r[26], ctx.r[0]); // cmplw cr0, r26, r0
    /* 0x800BBD24 */ if (ctx.eval_bc(12, 0)) goto loc_800BBD30; // bc 12, 0, 0x800BBD30
    /* 0x800BBD28 */ ctx.r[3] = ctx.r[27] + (-12136); // addi r3, r27, -12136 -> 0x8016D098 /* "vector" */
    /* 0x800BBD2C */ ctx.call_indirect(0x8013E678u, mem); // bl 0x8013E678 <_STL::__stl_throw_out_of_range(char *)>
loc_800BBD30:;
    /* 0x800BBD30 */ ctx.r[11] = mem.read_u32(ctx.r[31] + (0)); // lwz r11, 0(r31)
    /* 0x800BBD34 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800BBD38 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800BBD3C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (0)); // lwz r9, 0(r11)
    /* 0x800BBD40 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (192)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 192(r9)
    /* 0x800BBD44 */ ctx.r[9] = ctx.r[9] + (192); // addi r9, r9, 192
    /* 0x800BBD48 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r1)
    /* 0x800BBD4C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r9)
    /* 0x800BBD50 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[0])); // stfs f0, 12(r1)
    /* 0x800BBD54 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r9)
    /* 0x800BBD58 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800BBD5C */ GetXZAngle_800CEB4C(ctx, mem); // bl 0x800CEB4C <GetXZAngle(cVec &, cVec &)>
    /* 0x800BBD60 */ ctx.r[3] = ctx.r[1] + (24); // addi r3, r1, 24
    /* 0x800BBD64 */ ctx.r[4] = 0x00000079u; // li r4, 121
    /* 0x800BBD68 */ ctx.call_indirect(0x80100EE0u, mem); // bl 0x80100EE0 <PSMTXRotRad>
    /* 0x800BBD6C */ ctx.f[0] = mem.read_f32(ctx.r[30] + (12)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 12(r30)
    /* 0x800BBD70 */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800BBD74 */ ctx.r[5] = mem.read_u32(ctx.r[30] + (16)); // lwz r5, 16(r30)
    /* 0x800BBD78 */ ctx.r[4] = ctx.r[29]; // mr r4, r29
    /* 0x800BBD7C */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BBD80 */ ctx.r[5] = ctx.r[5] + (4); // addi r5, r5, 4
    /* 0x800BBD84 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r1)
    /* 0x800BBD88 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[31])); // stfs f31, 12(r1)
    /* 0x800BBD8C */ ctx.call_indirect(0x80101CC8u, mem); // bl 0x80101CC8 <PSMTXMultVec>
    /* 0x800BBD90 */ ctx.r[3] = mem.read_u32(ctx.r[30] + (16)); // lwz r3, 16(r30)
    /* 0x800BBD94 */ ctx.r[4] = ctx.r[30]; // mr r4, r30
    /* 0x800BBD98 */ ctx.r[30] = ctx.r[30] + (20); // addi r30, r30, 20
    /* 0x800BBD9C */ ctx.r[3] = ctx.r[3] + (4); // addi r3, r3, 4
    /* 0x800BBDA0 */ ctx.r[5] = ctx.r[3]; // mr r5, r3
    /* 0x800BBDA4 */ ctx.call_indirect(0x801038F4u, mem); // bl 0x801038F4 <PSVECAdd>
    /* 0x800BBDA8 */ ctx.cmp_u32(0, ctx.r[30], ctx.r[25]); // cmplw cr0, r30, r25
    /* 0x800BBDAC */ if (ctx.eval_bc(4, 1)) goto loc_800BBD08; // bc 4, 1, 0x800BBD08
    /* 0x800BBDB0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (116)); // lwz r0, 116(r1)
    /* 0x800BBDB4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BBDB8 */ ctx.lmw(mem, 25, ctx.r[1] + (76)); // lmw r25, 76(r1)
    /* 0x800BBDBC */ ctx.f[31] = mem.read_f64(ctx.r[1] + (104)); // lfd f31, 104(r1)
    /* 0x800BBDC0 */ ctx.r[1] = ctx.r[1] + (112); // addi r1, r1, 112
    /* 0x800BBDC4 */ return; // blr
}

// [0x800BBDC8] R80cInit(void) (r80c.obj, 153 insns / 0x264 bytes)
void R80cInit_800BBDC8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BBDC8 */ ctx.r[1] += (-56); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -56(r1)
    /* 0x800BBDCC */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BBDD0 */ ctx.stmw(mem, 30, ctx.r[1] + (48)); // stmw r30, 48(r1)
    /* 0x800BBDD4 */ mem.write_u32(ctx.r[1] + (60), ctx.r[0]); // stw r0, 60(r1)
    /* 0x800BBDD8 */ anonymous___lightChange_800BBACC(ctx, mem); // bl 0x800BBACC <{anonymous}::lightChange(void)>
    /* 0x800BBDDC */ ctx.r[31] = 0x00000000u; // li r31, 0
    /* 0x800BBDE0 */ ctx.r[8] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r8, -29836(r13) [pG]
    /* 0x800BBDE4 */ mem.write_u32(ctx.r[13] + (-29636), ctx.r[31]); // stw r31, -29636(r13) [{anonymous}::pEvent11]
    /* 0x800BBDE8 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (29012)); // lwz r0, 29012(r8)
    /* 0x800BBDEC */ mem.write_u32(ctx.r[13] + (-29632), ctx.r[31]); // stw r31, -29632(r13) [{anonymous}::pEvent20]
    /* 0x800BBDF0 */ mem.write_u32(ctx.r[13] + (-29628), ctx.r[31]); // stw r31, -29628(r13) [{anonymous}::pEvent21]
    /* 0x800BBDF4 */ ctx.r[9] = ctx.r[0] & 0x0800u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0800
    /* 0x800BBDF8 */ mem.write_u32(ctx.r[13] + (-29624), ctx.r[31]); // stw r31, -29624(r13) [{anonymous}::pEvent32]
    /* 0x800BBDFC */ mem.write_u32(ctx.r[13] + (-29640), ctx.r[31]); // stw r31, -29640(r13) [str_req]
    /* 0x800BBE00 */ if (ctx.eval_bc(12, 2)) goto loc_800BBE0C; // bc 12, 2, 0x800BBE0C
    /* 0x800BBE04 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BBE08 */ mem.write_u32(ctx.r[13] + (-29640), ctx.r[0]); // stw r0, -29640(r13) [str_req]
loc_800BBE0C:;
    /* 0x800BBE0C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BBE10 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BBE14 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-12092)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12092(r11) [0x8016D0C4]
    /* 0x800BBE18 */ ctx.r[9] = ctx.r[1] + (16); // addi r9, r1, 16
    /* 0x800BBE1C */ ctx.f[13] = mem.read_f32(ctx.r[10] + (-12088)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12088(r10) [0x8016D0C8]
    /* 0x800BBE20 */ ctx.r[11] = ctx.r[1] + (32); // addi r11, r1, 32
    /* 0x800BBE24 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BBE28 */ ctx.r[5] = ctx.r[9]; // mr r5, r9
    /* 0x800BBE2C */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r9)
    /* 0x800BBE30 */ ctx.r[6] = ctx.r[11]; // mr r6, r11
    /* 0x800BBE34 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
    /* 0x800BBE38 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BBE3C */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BBE40 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800BBE44 */ ctx.r[9] = mem.read_u32(ctx.r[8] + (272)); // lwz r9, 272(r8)
    /* 0x800BBE48 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (68)); // lwz r3, 68(r9)
    /* 0x800BBE4C */ ctx.r[4] = mem.read_u32(ctx.r[9] + (72)); // lwz r4, 72(r9)
    /* 0x800BBE50 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BBE54 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BBE58 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BBE5C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BBE60 */ mem.write_u32(ctx.r[13] + (-29620), ctx.r[3]); // stw r3, -29620(r13) [{anonymous}::pEle]
    /* 0x800BBE64 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BBE68 */ ctx.r[9] = ctx.r[0] & 0x0800u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0800
    /* 0x800BBE6C */ if (ctx.eval_bc(4, 2)) goto loc_800BBE80; // bc 4, 2, 0x800BBE80
    /* 0x800BBE70 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BBE74 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BBE78 */ SceAtSetEnable_800C20A0(ctx, mem); // bl 0x800C20A0 <SceAtSetEnable(unsigned long, int)>
    /* 0x800BBE7C */ goto loc_800BBEC0; // b 0x800BBEC0 <sub_800BBEC0>
loc_800BBE80:;
    /* 0x800BBE80 */ ctx.r[4] = 0x00000005u; // li r4, 5
    /* 0x800BBE84 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BBE88 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BBE8C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BBE90 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BBE94 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BBE98 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BBE9C */ mem.write_u32(ctx.r[1] + (8), ctx.r[31]); // stw r31, 8(r1)
    /* 0x800BBEA0 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BBEA4 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BBEA8 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BBEAC */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BBEB0 */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800BBEB4 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BBEB8 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BBEBC */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800BBEC0:;
    /* 0x800BBEC0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BBEC4 */ ctx.r[31] = mem.read_u32(ctx.r[9] + (25484)); // lwz r31, 25484(r9)
    /* 0x800BBEC8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // cmpwi cr0, r31, 0
    /* 0x800BBECC */ if (ctx.eval_bc(12, 2)) goto loc_800BBF40; // bc 12, 2, 0x800BBF40
    /* 0x800BBED0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BBED4 */ ctx.r[9] = mem.read_u16(ctx.r[31] + (4)); // lhz r9, 4(r31)
    /* 0x800BBED8 */ ctx.r[11] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x2000
    /* 0x800BBEDC */ ctx.r[9] = ctx.r[31] + ctx.r[9]; // add r9, r31, r9
    /* 0x800BBEE0 */ if (ctx.eval_bc(4, 2)) goto loc_800BBF14; // bc 4, 2, 0x800BBF14
    /* 0x800BBEE4 */ ctx.r[0] = mem.read_u16(ctx.r[31] + (6)); // lhz r0, 6(r31)
    /* 0x800BBEE8 */ ctx.r[11] = 0x00000000u; // li r11, 0
    /* 0x800BBEEC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r11, r0
    /* 0x800BBEF0 */ if (ctx.eval_bc(4, 0)) goto loc_800BBF40; // bc 4, 0, 0x800BBF40
    /* 0x800BBEF4 */ ctx.r[10] = 0x00000000u; // li r10, 0
loc_800BBEF8:;
    /* 0x800BBEF8 */ mem.write_u32(ctx.r[9] + (0), ctx.r[10]); // stw r10, 0(r9)
    /* 0x800BBEFC */ ctx.r[11] = ctx.r[11] + (1); // addi r11, r11, 1
    /* 0x800BBF00 */ ctx.r[9] = ctx.r[9] + (72); // addi r9, r9, 72
    /* 0x800BBF04 */ ctx.r[0] = mem.read_u16(ctx.r[31] + (6)); // lhz r0, 6(r31)
    /* 0x800BBF08 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r11, r0
    /* 0x800BBF0C */ if (ctx.eval_bc(12, 0)) goto loc_800BBEF8; // bc 12, 0, 0x800BBEF8
    /* 0x800BBF10 */ goto loc_800BBF40; // b 0x800BBF40 <sub_800BBF40>
loc_800BBF14:;
    /* 0x800BBF14 */ ctx.r[0] = mem.read_u16(ctx.r[31] + (6)); // lhz r0, 6(r31)
    /* 0x800BBF18 */ ctx.r[11] = 0x00000000u; // li r11, 0
    /* 0x800BBF1C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r11, r0
    /* 0x800BBF20 */ if (ctx.eval_bc(4, 0)) goto loc_800BBF40; // bc 4, 0, 0x800BBF40
    /* 0x800BBF24 */ ctx.r[10] = 0x00000001u; // li r10, 1
loc_800BBF28:;
    /* 0x800BBF28 */ mem.write_u32(ctx.r[9] + (0), ctx.r[10]); // stw r10, 0(r9)
    /* 0x800BBF2C */ ctx.r[11] = ctx.r[11] + (1); // addi r11, r11, 1
    /* 0x800BBF30 */ ctx.r[9] = ctx.r[9] + (72); // addi r9, r9, 72
    /* 0x800BBF34 */ ctx.r[0] = mem.read_u16(ctx.r[31] + (6)); // lhz r0, 6(r31)
    /* 0x800BBF38 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r11, r0
    /* 0x800BBF3C */ if (ctx.eval_bc(12, 0)) goto loc_800BBF28; // bc 12, 0, 0x800BBF28
loc_800BBF40:;
    /* 0x800BBF40 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BBF44 */ ctx.r[0] = mem.read_u16(ctx.r[9] + (27258)); // lhz r0, 27258(r9)
    /* 0x800BBF48 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 2062); // cmpwi cr0, r0, 2062
    /* 0x800BBF4C */ if (ctx.eval_bc(4, 2)) goto loc_800BBF9C; // bc 4, 2, 0x800BBF9C
    /* 0x800BBF50 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BBF54 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BBF58 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BBF5C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BBF60 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BBF64 */ mem.write_u32(ctx.r[13] + (-29624), ctx.r[0]); // stw r0, -29624(r13) [{anonymous}::pEvent32]
    /* 0x800BBF68 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BBF6C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BBF70 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (56)); // lwz r4, 56(r9)
    /* 0x800BBF74 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BBF78 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BBF7C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29620)); // lwz r11, -29620(r13) [{anonymous}::pEle]
    /* 0x800BBF80 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BBF84 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BBF88 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BBF8C */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BBF90 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BBF94 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BBF98 */ goto loc_800BC018; // b 0x800BC018 <sub_800BC018>
loc_800BBF9C:;
    /* 0x800BBF9C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BBFA0 */ ctx.r[11] = ctx.r[0] & 0x00100000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0010
    /* 0x800BBFA4 */ if (ctx.eval_bc(4, 2)) goto loc_800BC014; // bc 4, 2, 0x800BC014
    /* 0x800BBFA8 */ ctx.r[0] = ctx.r[0] | 0x00100000u; // oris r0, r0, 0x0010
    /* 0x800BBFAC */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BBFB0 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BBFB4 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BBFB8 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BBFBC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BBFC0 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BBFC4 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BBFC8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BBFCC */ mem.write_u32(ctx.r[13] + (-29636), ctx.r[0]); // stw r0, -29636(r13) [{anonymous}::pEvent11]
    /* 0x800BBFD0 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (44)); // lwz r4, 44(r9)
    /* 0x800BBFD4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BBFD8 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BBFDC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29620)); // lwz r11, -29620(r13) [{anonymous}::pEle]
    /* 0x800BBFE0 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BBFE4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BBFE8 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BBFEC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BBFF0 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BBFF4 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BBFF8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BBFFC */ ctx.r[11] = 0x00000001u; // li r11, 1
    /* 0x800BC000 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BC004 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BC008 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
    /* 0x800BC00C */ mem.write_u32(ctx.r[13] + (-29640), ctx.r[11]); // stw r11, -29640(r13) [str_req]
    /* 0x800BC010 */ goto loc_800BC018; // b 0x800BC018 <sub_800BC018>
loc_800BC014:;
    /* 0x800BC014 */ anonymous___setLight_800BBB10(ctx, mem); // bl 0x800BBB10 <{anonymous}::setLight(void)>
loc_800BC018:;
    /* 0x800BC018 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (60)); // lwz r0, 60(r1)
    /* 0x800BC01C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC020 */ ctx.lmw(mem, 30, ctx.r[1] + (48)); // lmw r30, 48(r1)
    /* 0x800BC024 */ ctx.r[1] = ctx.r[1] + (56); // addi r1, r1, 56
    /* 0x800BC028 */ return; // blr
}

// [0x800BC02C] R80cMain(void) (r80c.obj, 300 insns / 0x4B0 bytes)
void R80cMain_800BC02C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BC02C */ ctx.r[1] += (-112); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -112(r1)
    /* 0x800BC030 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BC034 */ ctx.stmw(mem, 29, ctx.r[1] + (100)); // stmw r29, 100(r1)
    /* 0x800BC038 */ mem.write_u32(ctx.r[1] + (116), ctx.r[0]); // stw r0, 116(r1)
    /* 0x800BC03C */ ctx.r[30] = mem.read_u32(ctx.r[13] + (-29624)); // lwz r30, -29624(r13) [{anonymous}::pEvent32]
    /* 0x800BC040 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[30]), 0); // cmpwi cr0, r30, 0
    /* 0x800BC044 */ if (ctx.eval_bc(12, 2)) goto loc_800BC128; // bc 12, 2, 0x800BC128
    /* 0x800BC048 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800BC04C */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BC050 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BC054 */ if (ctx.eval_bc(12, 2)) goto loc_800BC488; // bc 12, 2, 0x800BC488
    /* 0x800BC058 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29624)); // lwz r11, -29624(r13) [{anonymous}::pEvent32]
    /* 0x800BC05C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BC060 */ if (ctx.eval_bc(12, 2)) goto loc_800BC080; // bc 12, 2, 0x800BC080
    /* 0x800BC064 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BC068 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BC06C */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BC070 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BC074 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BC078 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC07C */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BC080:;
    /* 0x800BC080 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29620)); // lwz r11, -29620(r13) [{anonymous}::pEle]
    /* 0x800BC084 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BC088 */ mem.write_u32(ctx.r[13] + (-29624), ctx.r[0]); // stw r0, -29624(r13) [{anonymous}::pEvent32]
    /* 0x800BC08C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BC090 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BC094 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BC098 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC09C */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BC0A0 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BC0A4 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BC0A8 */ ctx.r[10] = ctx.r[1] + (16); // addi r10, r1, 16
    /* 0x800BC0AC */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-12084)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12084(r11) [0x8016D0CC]
    /* 0x800BC0B0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BC0B4 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12080)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12080(r9) [0x8016D0D0]
    /* 0x800BC0B8 */ ctx.r[8] = ctx.r[1] + (32); // addi r8, r1, 32
    /* 0x800BC0BC */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BC0C0 */ ctx.r[11] = ctx.r[1] + (48); // addi r11, r1, 48
    /* 0x800BC0C4 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800BC0C8 */ ctx.r[3] = ctx.r[11]; // mr r3, r11
    /* 0x800BC0CC */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800BC0D0 */ ctx.r[6] = ctx.r[1] + (64); // addi r6, r1, 64
    /* 0x800BC0D4 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BC0D8 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BC0DC */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r8)
    /* 0x800BC0E0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BC0E4 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r8)
    /* 0x800BC0E8 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (16)); // lwz r9, 16(r1)
    /* 0x800BC0EC */ ctx.r[0] = mem.read_u32(ctx.r[10] + (4)); // lwz r0, 4(r10)
    /* 0x800BC0F0 */ ctx.r[7] = mem.read_u32(ctx.r[10] + (8)); // lwz r7, 8(r10)
    /* 0x800BC0F4 */ mem.write_u32(ctx.r[1] + (48), ctx.r[9]); // stw r9, 48(r1)
    /* 0x800BC0F8 */ mem.write_u32(ctx.r[11] + (8), ctx.r[7]); // stw r7, 8(r11)
    /* 0x800BC0FC */ mem.write_u32(ctx.r[11] + (4), ctx.r[0]); // stw r0, 4(r11)
    /* 0x800BC100 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (32)); // lwz r9, 32(r1)
    /* 0x800BC104 */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BC108 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BC10C */ mem.write_u32(ctx.r[1] + (64), ctx.r[9]); // stw r9, 64(r1)
    /* 0x800BC110 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BC114 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BC118 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BC11C */ anonymous___lightChange_800BBACC(ctx, mem); // bl 0x800BBACC <{anonymous}::lightChange(void)>
    /* 0x800BC120 */ anonymous___setLight_800BBB10(ctx, mem); // bl 0x800BBB10 <{anonymous}::setLight(void)>
    /* 0x800BC124 */ goto loc_800BC488; // b 0x800BC488 <sub_800BC488>
loc_800BC128:;
    /* 0x800BC128 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29636)); // lwz r3, -29636(r13) [{anonymous}::pEvent11]
    /* 0x800BC12C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BC130 */ if (ctx.eval_bc(12, 2)) goto loc_800BC20C; // bc 12, 2, 0x800BC20C
    /* 0x800BC134 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BC138 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BC13C */ if (ctx.eval_bc(12, 2)) goto loc_800BC488; // bc 12, 2, 0x800BC488
    /* 0x800BC140 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29636)); // lwz r11, -29636(r13) [{anonymous}::pEvent11]
    /* 0x800BC144 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BC148 */ if (ctx.eval_bc(12, 2)) goto loc_800BC168; // bc 12, 2, 0x800BC168
    /* 0x800BC14C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BC150 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BC154 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BC158 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BC15C */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BC160 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC164 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BC168:;
    /* 0x800BC168 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BC16C */ ctx.r[10] = ctx.r[1] + (16); // addi r10, r1, 16
    /* 0x800BC170 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-12084)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12084(r11) [0x8016D0CC]
    /* 0x800BC174 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BC178 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12080)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12080(r9) [0x8016D0D0]
    /* 0x800BC17C */ ctx.r[7] = ctx.r[1] + (32); // addi r7, r1, 32
    /* 0x800BC180 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BC184 */ ctx.r[11] = ctx.r[1] + (48); // addi r11, r1, 48
    /* 0x800BC188 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800BC18C */ ctx.r[3] = ctx.r[11]; // mr r3, r11
    /* 0x800BC190 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800BC194 */ ctx.r[6] = ctx.r[1] + (80); // addi r6, r1, 80
    /* 0x800BC198 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BC19C */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BC1A0 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r7)
    /* 0x800BC1A4 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BC1A8 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r7)
    /* 0x800BC1AC */ mem.write_u32(ctx.r[13] + (-29636), ctx.r[30]); // stw r30, -29636(r13) [{anonymous}::pEvent11]
    /* 0x800BC1B0 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (16)); // lwz r9, 16(r1)
    /* 0x800BC1B4 */ ctx.r[0] = mem.read_u32(ctx.r[10] + (4)); // lwz r0, 4(r10)
    /* 0x800BC1B8 */ ctx.r[8] = mem.read_u32(ctx.r[10] + (8)); // lwz r8, 8(r10)
    /* 0x800BC1BC */ mem.write_u32(ctx.r[1] + (48), ctx.r[9]); // stw r9, 48(r1)
    /* 0x800BC1C0 */ mem.write_u32(ctx.r[11] + (8), ctx.r[8]); // stw r8, 8(r11)
    /* 0x800BC1C4 */ mem.write_u32(ctx.r[11] + (4), ctx.r[0]); // stw r0, 4(r11)
    /* 0x800BC1C8 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (32)); // lwz r9, 32(r1)
    /* 0x800BC1CC */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BC1D0 */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BC1D4 */ mem.write_u32(ctx.r[1] + (80), ctx.r[9]); // stw r9, 80(r1)
    /* 0x800BC1D8 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BC1DC */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BC1E0 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BC1E4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29620)); // lwz r11, -29620(r13) [{anonymous}::pEle]
    /* 0x800BC1E8 */ mem.write_u32(ctx.r[13] + (-29640), ctx.r[30]); // stw r30, -29640(r13) [str_req]
    /* 0x800BC1EC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BC1F0 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BC1F4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BC1F8 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BC1FC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC200 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BC204 */ anonymous___setLight_800BBB10(ctx, mem); // bl 0x800BBB10 <{anonymous}::setLight(void)>
    /* 0x800BC208 */ goto loc_800BC488; // b 0x800BC488 <sub_800BC488>
loc_800BC20C:;
    /* 0x800BC20C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC210 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BC214 */ ctx.r[0] = ctx.r[11] & 0x0800u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andi. r0, r11, 0x0800
    /* 0x800BC218 */ if (ctx.eval_bc(4, 2)) goto loc_800BC28C; // bc 4, 2, 0x800BC28C
    /* 0x800BC21C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BC220 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BC224 */ if (ctx.eval_bc(4, 0)) goto loc_800BC28C; // bc 4, 0, 0x800BC28C
    /* 0x800BC228 */ ctx.r[0] = ctx.r[11] | 0x0800u; // ori r0, r11, 0x0800
    /* 0x800BC22C */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BC230 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BC234 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BC238 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BC23C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC240 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BC244 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BC248 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BC24C */ mem.write_u32(ctx.r[13] + (-29632), ctx.r[0]); // stw r0, -29632(r13) [{anonymous}::pEvent20]
    /* 0x800BC250 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (48)); // lwz r4, 48(r9)
    /* 0x800BC254 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BC258 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BC25C */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800BC260 */ ctx.r[4] = 0x00000042u; // li r4, 66
    /* 0x800BC264 */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800BC268 */ ctx.r[5] = 0x10000000u; // lis r5, 0x1000
    /* 0x800BC26C */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800BC270 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC274 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BC278 */ ctx.r[4] = 0x000000C8u; // li r4, 200
    /* 0x800BC27C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (332)); // lwz r0, 332(r9)
    /* 0x800BC280 */ ctx.r[0] = ctx.r[0] | 0x10000000u; // oris r0, r0, 0x1000
    /* 0x800BC284 */ mem.write_u32(ctx.r[9] + (332), ctx.r[0]); // stw r0, 332(r9)
    /* 0x800BC288 */ Snd_str_fadeout_800CD394(ctx, mem); // bl 0x800CD394 <Snd_str_fadeout(long, long)>
loc_800BC28C:;
    /* 0x800BC28C */ ctx.r[30] = mem.read_u32(ctx.r[13] + (-29632)); // lwz r30, -29632(r13) [{anonymous}::pEvent20]
    /* 0x800BC290 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[30]), 0); // cmpwi cr0, r30, 0
    /* 0x800BC294 */ if (ctx.eval_bc(12, 2)) goto loc_800BC32C; // bc 12, 2, 0x800BC32C
    /* 0x800BC298 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800BC29C */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BC2A0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BC2A4 */ if (ctx.eval_bc(12, 2)) goto loc_800BC488; // bc 12, 2, 0x800BC488
    /* 0x800BC2A8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29632)); // lwz r11, -29632(r13) [{anonymous}::pEvent20]
    /* 0x800BC2AC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BC2B0 */ if (ctx.eval_bc(12, 2)) goto loc_800BC2D0; // bc 12, 2, 0x800BC2D0
    /* 0x800BC2B4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BC2B8 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BC2BC */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BC2C0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BC2C4 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BC2C8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC2CC */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BC2D0:;
    /* 0x800BC2D0 */ ctx.r[29] = 0x00000000u; // li r29, 0
    /* 0x800BC2D4 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BC2D8 */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800BC2DC */ mem.write_u32(ctx.r[13] + (-29632), ctx.r[29]); // stw r29, -29632(r13) [{anonymous}::pEvent20]
    /* 0x800BC2E0 */ SceAtSetEnable_800C20A0(ctx, mem); // bl 0x800C20A0 <SceAtSetEnable(unsigned long, int)>
    /* 0x800BC2E4 */ ctx.r[4] = 0x00000005u; // li r4, 5
    /* 0x800BC2E8 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BC2EC */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BC2F0 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BC2F4 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BC2F8 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BC2FC */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BC300 */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800BC304 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BC308 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BC30C */ mem.write_u32(ctx.r[1] + (8), ctx.r[29]); // stw r29, 8(r1)
    /* 0x800BC310 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BC314 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BC318 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BC31C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BC320 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800BC324 */ anonymous___setLight_800BBB10(ctx, mem); // bl 0x800BBB10 <{anonymous}::setLight(void)>
    /* 0x800BC328 */ goto loc_800BC488; // b 0x800BC488 <sub_800BC488>
loc_800BC32C:;
    /* 0x800BC32C */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29628)); // lwz r3, -29628(r13) [{anonymous}::pEvent21]
    /* 0x800BC330 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BC334 */ if (ctx.eval_bc(12, 2)) goto loc_800BC414; // bc 12, 2, 0x800BC414
    /* 0x800BC338 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BC33C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BC340 */ if (ctx.eval_bc(12, 2)) goto loc_800BC488; // bc 12, 2, 0x800BC488
    /* 0x800BC344 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29628)); // lwz r11, -29628(r13) [{anonymous}::pEvent21]
    /* 0x800BC348 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BC34C */ if (ctx.eval_bc(12, 2)) goto loc_800BC36C; // bc 12, 2, 0x800BC36C
    /* 0x800BC350 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BC354 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BC358 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BC35C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BC360 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BC364 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC368 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BC36C:;
    /* 0x800BC36C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29620)); // lwz r11, -29620(r13) [{anonymous}::pEle]
    /* 0x800BC370 */ mem.write_u32(ctx.r[13] + (-29628), ctx.r[30]); // stw r30, -29628(r13) [{anonymous}::pEvent21]
    /* 0x800BC374 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BC378 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BC37C */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BC380 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC384 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BC388 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BC38C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC390 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BC394 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12084)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12084(r9) [0x8016D0CC]
    /* 0x800BC398 */ ctx.r[8] = 0x00000008u; // li r8, 8
    /* 0x800BC39C */ ctx.r[0] = mem.read_u8(ctx.r[11] + (27256)); // lbz r0, 27256(r11)
    /* 0x800BC3A0 */ ctx.r[7] = 0x0000000Eu; // li r7, 14
    /* 0x800BC3A4 */ ctx.r[6] = 0x00000004u; // li r6, 4
    /* 0x800BC3A8 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BC3AC */ mem.write_u8(ctx.r[11] + (27258), static_cast<uint8_t>(ctx.r[0])); // stb r0, 27258(r11)
    /* 0x800BC3B0 */ ctx.f[13] = mem.read_f32(ctx.r[10] + (-12076)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12076(r10) [0x8016D0D4]
    /* 0x800BC3B4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC3B8 */ ctx.r[0] = mem.read_u8(ctx.r[11] + (27257)); // lbz r0, 27257(r11)
    /* 0x800BC3BC */ mem.write_u8(ctx.r[11] + (27259), static_cast<uint8_t>(ctx.r[0])); // stb r0, 27259(r11)
    /* 0x800BC3C0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC3C4 */ mem.write_u8(ctx.r[9] + (27277), static_cast<uint8_t>(ctx.r[8])); // stb r8, 27277(r9)
    /* 0x800BC3C8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC3CC */ mem.write_u8(ctx.r[11] + (27276), static_cast<uint8_t>(ctx.r[7])); // stb r7, 27276(r11)
    /* 0x800BC3D0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC3D4 */ mem.write_u8(ctx.r[9] + (260), static_cast<uint8_t>(ctx.r[6])); // stb r6, 260(r9)
    /* 0x800BC3D8 */ mem.write_f32(ctx.r[9] + (27264), static_cast<float>(ctx.f[13])); // stfs f13, 27264(r9)
    /* 0x800BC3DC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC3E0 */ mem.write_f32(ctx.r[9] + (27272), static_cast<float>(ctx.f[0])); // stfs f0, 27272(r9)
    /* 0x800BC3E4 */ mem.write_f32(ctx.r[9] + (27260), static_cast<float>(ctx.f[0])); // stfs f0, 27260(r9)
    /* 0x800BC3E8 */ mem.write_f32(ctx.r[9] + (27268), static_cast<float>(ctx.f[0])); // stfs f0, 27268(r9)
    /* 0x800BC3EC */ mem.write_u8(ctx.r[11] + (261), static_cast<uint8_t>(ctx.r[30])); // stb r30, 261(r11)
    /* 0x800BC3F0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC3F4 */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[30])); // stb r30, 262(r9)
    /* 0x800BC3F8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC3FC */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[30])); // stb r30, 263(r11)
    /* 0x800BC400 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC404 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (336)); // lwz r0, 336(r9)
    /* 0x800BC408 */ ctx.r[0] = ctx.r[0] | 0x7D010000u; // oris r0, r0, 0x7D01
    /* 0x800BC40C */ mem.write_u32(ctx.r[9] + (336), ctx.r[0]); // stw r0, 336(r9)
    /* 0x800BC410 */ goto loc_800BC488; // b 0x800BC488 <sub_800BC488>
loc_800BC414:;
    /* 0x800BC414 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC418 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BC41C */ ctx.r[11] = ctx.r[0] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x4000
    /* 0x800BC420 */ if (ctx.eval_bc(12, 2)) goto loc_800BC488; // bc 12, 2, 0x800BC488
    /* 0x800BC424 */ ctx.rlwinm(0, 0, 0u, 2u, 0u, false); // rlwinm r0, r0, 0, 2, 0
    /* 0x800BC428 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BC42C */ mem.write_u32(ctx.r[9] + (340), ctx.r[0]); // stw r0, 340(r9)
    /* 0x800BC430 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BC434 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BC438 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC43C */ mem.write_u32(ctx.r[13] + (-29628), ctx.r[3]); // stw r3, -29628(r13) [{anonymous}::pEvent21]
    /* 0x800BC440 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BC444 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BC448 */ if (ctx.eval_bc(12, 2)) goto loc_800BC458; // bc 12, 2, 0x800BC458
    /* 0x800BC44C */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BC450 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (80)); // lwz r0, 80(r9)
    /* 0x800BC454 */ goto loc_800BC460; // b 0x800BC460 <sub_800BC460>
loc_800BC458:;
    /* 0x800BC458 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BC45C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
loc_800BC460:;
    /* 0x800BC460 */ ctx.r[4] = ctx.r[0] + ctx.r[9]; // add r4, r0, r9
    /* 0x800BC464 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BC468 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BC46C */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29620)); // lwz r3, -29620(r13) [{anonymous}::pEle]
    /* 0x800BC470 */ ctx.r[9] = mem.read_u32(ctx.r[3] + (1208)); // lwz r9, 1208(r3)
    /* 0x800BC474 */ ctx.r[0] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r0, 48(r9)
    /* 0x800BC478 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (52)); // lwz r9, 52(r9)
    /* 0x800BC47C */ ctx.r[3] = ctx.r[3] + ctx.r[0]; // add r3, r3, r0
    /* 0x800BC480 */ ctx.lr = ctx.r[9]; // mtlr r9
    /* 0x800BC484 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BC488:;
    /* 0x800BC488 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29640)); // lwz r0, -29640(r13) [str_req]
    /* 0x800BC48C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BC490 */ if (ctx.eval_bc(4, 2)) goto loc_800BC4B4; // bc 4, 2, 0x800BC4B4
    /* 0x800BC494 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BC498 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BC49C */ mem.write_u32(ctx.r[13] + (-29640), ctx.r[0]); // stw r0, -29640(r13) [str_req]
    /* 0x800BC4A0 */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800BC4A4 */ ctx.r[5] = 0x00000002u; // li r5, 2
    /* 0x800BC4A8 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BC4AC */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BC4B0 */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
loc_800BC4B4:;
    /* 0x800BC4B4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC4B8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BC4BC */ ctx.r[9] = ctx.r[0] & 0x1000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x1000
    /* 0x800BC4C0 */ if (ctx.eval_bc(4, 2)) goto loc_800BC4C8; // bc 4, 2, 0x800BC4C8
    /* 0x800BC4C4 */ anonymous___moveLight_800BBCCC(ctx, mem); // bl 0x800BBCCC <{anonymous}::moveLight(void)>
loc_800BC4C8:;
    /* 0x800BC4C8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (116)); // lwz r0, 116(r1)
    /* 0x800BC4CC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC4D0 */ ctx.lmw(mem, 29, ctx.r[1] + (100)); // lmw r29, 100(r1)
    /* 0x800BC4D4 */ ctx.r[1] = ctx.r[1] + (112); // addi r1, r1, 112
    /* 0x800BC4D8 */ return; // blr
}

// [0x800BC4DC] __static_initialization_and_destruction_0 (r80c.obj, 19 insns / 0x4C bytes)
void static_initialization_and_destruction_0_800BC4DC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BC4DC */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BC4E0 */ ctx.r[0] = ctx.r[0] | 0xFFFFu; // ori r0, r0, 0xFFFF
    /* 0x800BC4E4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[4]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r4, r0
    /* 0x800BC4E8 */ if (ctx.eval_bc(4, 2)) return; // bclr 4, 2
    /* 0x800BC4EC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BC4F0 */ if (ctx.eval_bc(12, 2)) return; // bclr 12, 2
    /* 0x800BC4F4 */ ctx.r[0] = 0x00000005u; // li r0, 5
    /* 0x800BC4F8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BC4FC */ ctx.ctr = ctx.r[0]; // mtctr r0
    /* 0x800BC500 */ ctx.r[11] = 0x801C0000u; // lis r11, 0x801C
    /* 0x800BC504 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12072)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12072(r9) [0x8016D0D8]
    /* 0x800BC508 */ ctx.r[11] = ctx.r[11] + (19232); // addi r11, r11, 19232 -> {anonymous}::light
loc_800BC50C:;
    /* 0x800BC50C */ mem.write_f32(ctx.r[11] + (0), static_cast<float>(ctx.f[0])); // stfs f0, 0(r11)
    /* 0x800BC510 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800BC514 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BC518 */ mem.write_f32(ctx.r[11] + (12), static_cast<float>(ctx.f[0])); // stfs f0, 12(r11)
    /* 0x800BC51C */ ctx.r[11] = ctx.r[11] + (20); // addi r11, r11, 20
    /* 0x800BC520 */ if (ctx.eval_bc(16, 0)) goto loc_800BC50C; // bc 16, 0, 0x800BC50C
    /* 0x800BC524 */ return; // blr
}

// [0x800BC528] global constructors keyed to {anonymous}::lightChange(void) (r80c.obj, 11 insns / 0x2C bytes)
void global_constructors_keyed_to__anonymous___lightChange_800BC528(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BC528 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BC52C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BC530 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BC534 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BC538 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BC53C */ ctx.r[4] = ctx.r[4] | 0xFFFFu; // ori r4, r4, 0xFFFF
    /* 0x800BC540 */ static_initialization_and_destruction_0_800BC4DC(ctx, mem); // bl 0x800BC4DC <__static_initialization_and_destruction_0>
    /* 0x800BC544 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BC548 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC54C */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BC550 */ return; // blr
}

// [0x800BC554] R80dInit(void) (r80d.obj, 47 insns / 0xBC bytes)
void R80dInit_800BC554(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BC554 */ ctx.r[1] += (-40); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -40(r1)
    /* 0x800BC558 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BC55C */ mem.write_u32(ctx.r[1] + (44), ctx.r[0]); // stw r0, 44(r1)
    /* 0x800BC560 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BC564 */ ctx.r[9] = 0x00000001u; // li r9, 1
    /* 0x800BC568 */ mem.write_u32(ctx.r[13] + (-29616), ctx.r[0]); // stw r0, -29616(r13) [pEvent02]
    /* 0x800BC56C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BC570 */ mem.write_u32(ctx.r[13] + (-29612), ctx.r[9]); // stw r9, -29612(r13) [str_req]
    /* 0x800BC574 */ SmdGetObjPtr_800C33C8(ctx, mem); // bl 0x800C33C8 <SmdGetObjPtr(long)>
    /* 0x800BC578 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BC57C */ ctx.r[11] = 0x00000005u; // li r11, 5
    /* 0x800BC580 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12048)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12048(r9) [0x8016D0F0]
    /* 0x800BC584 */ ctx.r[8] = 0x00000005u; // li r8, 5
    /* 0x800BC588 */ ctx.r[0] = 0x0000001Eu; // li r0, 30
    /* 0x800BC58C */ mem.write_u8(ctx.r[3] + (295), static_cast<uint8_t>(ctx.r[11])); // stb r11, 295(r3)
    /* 0x800BC590 */ mem.write_u16(ctx.r[3] + (1292), static_cast<uint16_t>(ctx.r[0])); // sth r0, 1292(r3)
    /* 0x800BC594 */ ctx.r[9] = ctx.r[1] + (8); // addi r9, r1, 8
    /* 0x800BC598 */ mem.write_u32(ctx.r[3] + (1288), ctx.r[8]); // stw r8, 1288(r3)
    /* 0x800BC59C */ ctx.r[10] = ctx.r[1] + (24); // addi r10, r1, 24
    /* 0x800BC5A0 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800BC5A4 */ ctx.r[5] = ctx.r[9]; // mr r5, r9
    /* 0x800BC5A8 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r9)
    /* 0x800BC5AC */ ctx.r[6] = ctx.r[10]; // mr r6, r10
    /* 0x800BC5B0 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
    /* 0x800BC5B4 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800BC5B8 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800BC5BC */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800BC5C0 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC5C4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BC5C8 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (52)); // lwz r3, 52(r9)
    /* 0x800BC5CC */ ctx.r[4] = mem.read_u32(ctx.r[9] + (56)); // lwz r4, 56(r9)
    /* 0x800BC5D0 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BC5D4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BC5D8 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BC5DC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC5E0 */ ctx.r[3] = 0x801C0000u; // lis r3, 0x801C
    /* 0x800BC5E4 */ ctx.r[3] = ctx.r[3] + (19332); // addi r3, r3, 19332 -> mes80D
    /* 0x800BC5E8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BC5EC */ ctx.r[4] = mem.read_u32(ctx.r[9] + (72)); // lwz r4, 72(r9)
    /* 0x800BC5F0 */ ctx.r[5] = mem.read_u32(ctx.r[9] + (68)); // lwz r5, 68(r9)
    /* 0x800BC5F4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BC5F8 */ ctx.r[5] = ctx.r[5] + ctx.r[9]; // add r5, r5, r9
    /* 0x800BC5FC */ cIdMain__SetTexPrim_8007245C(ctx, mem); // bl 0x8007245C <cIdMain::SetTexPrim(unsigned long, unsigned long)>
    /* 0x800BC600 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (44)); // lwz r0, 44(r1)
    /* 0x800BC604 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC608 */ ctx.r[1] = ctx.r[1] + (40); // addi r1, r1, 40
    /* 0x800BC60C */ return; // blr
}

// [0x800BC610] R80dMain(void) (r80d.obj, 122 insns / 0x1E8 bytes)
void R80dMain_800BC610(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BC610 */ ctx.r[1] += (-80); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -80(r1)
    /* 0x800BC614 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BC618 */ ctx.stmw(mem, 30, ctx.r[1] + (72)); // stmw r30, 72(r1)
    /* 0x800BC61C */ mem.write_u32(ctx.r[1] + (84), ctx.r[0]); // stw r0, 84(r1)
    /* 0x800BC620 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC624 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (292)); // lwz r0, 292(r11)
    /* 0x800BC628 */ ctx.r[9] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x0002
    /* 0x800BC62C */ if (ctx.eval_bc(12, 2)) goto loc_800BC65C; // bc 12, 2, 0x800BC65C
    /* 0x800BC630 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (340)); // lwz r0, 340(r11)
    /* 0x800BC634 */ ctx.r[9] = ctx.r[0] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x4000
    /* 0x800BC638 */ if (ctx.eval_bc(4, 2)) goto loc_800BC65C; // bc 4, 2, 0x800BC65C
    /* 0x800BC63C */ ctx.r[0] = ctx.r[0] | 0x40000000u; // oris r0, r0, 0x4000
    /* 0x800BC640 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BC644 */ mem.write_u32(ctx.r[11] + (340), ctx.r[0]); // stw r0, 340(r11)
    /* 0x800BC648 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (64)); // lwz r3, 64(r9)
    /* 0x800BC64C */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BC650 */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BC654 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BC658 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
loc_800BC65C:;
    /* 0x800BC65C */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29612)); // lwz r0, -29612(r13) [str_req]
    /* 0x800BC660 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BC664 */ if (ctx.eval_bc(4, 2)) goto loc_800BC698; // bc 4, 2, 0x800BC698
    /* 0x800BC668 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BC66C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BC670 */ mem.write_u32(ctx.r[13] + (-29612), ctx.r[0]); // stw r0, -29612(r13) [str_req]
    /* 0x800BC674 */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800BC678 */ ctx.r[5] = 0x00000002u; // li r5, 2
    /* 0x800BC67C */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BC680 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BC684 */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
    /* 0x800BC688 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC68C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (296)); // lwz r0, 296(r9)
    /* 0x800BC690 */ ctx.rlwinm(0, 0, 0u, 12u, 10u, false); // rlwinm r0, r0, 0, 12, 10
    /* 0x800BC694 */ mem.write_u32(ctx.r[9] + (296), ctx.r[0]); // stw r0, 296(r9)
loc_800BC698:;
    /* 0x800BC698 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC69C */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BC6A0 */ ctx.r[0] = ctx.r[11] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andis. r0, r11, 0x2000
    /* 0x800BC6A4 */ if (ctx.eval_bc(4, 2)) goto loc_800BC6E8; // bc 4, 2, 0x800BC6E8
    /* 0x800BC6A8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BC6AC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BC6B0 */ if (ctx.eval_bc(4, 0)) goto loc_800BC6E8; // bc 4, 0, 0x800BC6E8
    /* 0x800BC6B4 */ ctx.r[0] = ctx.r[11] | 0x20000000u; // oris r0, r11, 0x2000
    /* 0x800BC6B8 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BC6BC */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BC6C0 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BC6C4 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BC6C8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC6CC */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BC6D0 */ mem.write_u32(ctx.r[13] + (-29616), ctx.r[0]); // stw r0, -29616(r13) [pEvent02]
    /* 0x800BC6D4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BC6D8 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BC6DC */ ctx.r[4] = mem.read_u32(ctx.r[9] + (44)); // lwz r4, 44(r9)
    /* 0x800BC6E0 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BC6E4 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
loc_800BC6E8:;
    /* 0x800BC6E8 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29616)); // lwz r3, -29616(r13) [pEvent02]
    /* 0x800BC6EC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BC6F0 */ if (ctx.eval_bc(12, 2)) goto loc_800BC7E4; // bc 12, 2, 0x800BC7E4
    /* 0x800BC6F4 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BC6F8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BC6FC */ if (ctx.eval_bc(12, 2)) goto loc_800BC7E4; // bc 12, 2, 0x800BC7E4
    /* 0x800BC700 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29616)); // lwz r11, -29616(r13) [pEvent02]
    /* 0x800BC704 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BC708 */ if (ctx.eval_bc(12, 2)) goto loc_800BC728; // bc 12, 2, 0x800BC728
    /* 0x800BC70C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BC710 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BC714 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BC718 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BC71C */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BC720 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC724 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BC728:;
    /* 0x800BC728 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BC72C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BC730 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12044)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12044(r9) [0x8016D0F4]
    /* 0x800BC734 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BC738 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-12040)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12040(r11) [0x8016D0F8]
    /* 0x800BC73C */ ctx.r[8] = ctx.r[1] + (8); // addi r8, r1, 8
    /* 0x800BC740 */ ctx.f[12] = mem.read_f32(ctx.r[10] + (-12036)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -12036(r10) [0x8016D0FC]
    /* 0x800BC744 */ ctx.r[7] = ctx.r[1] + (24); // addi r7, r1, 24
    /* 0x800BC748 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800BC74C */ ctx.r[30] = 0x00000000u; // li r30, 0
    /* 0x800BC750 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r8)
    /* 0x800BC754 */ ctx.r[10] = ctx.r[1] + (40); // addi r10, r1, 40
    /* 0x800BC758 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r8)
    /* 0x800BC75C */ ctx.r[6] = ctx.r[1] + (56); // addi r6, r1, 56
    /* 0x800BC760 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800BC764 */ ctx.r[3] = ctx.r[10]; // mr r3, r10
    /* 0x800BC768 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r7)
    /* 0x800BC76C */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BC770 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800BC774 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BC778 */ mem.write_u32(ctx.r[13] + (-29616), ctx.r[30]); // stw r30, -29616(r13) [pEvent02]
    /* 0x800BC77C */ ctx.r[9] = mem.read_u32(ctx.r[1] + (8)); // lwz r9, 8(r1)
    /* 0x800BC780 */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BC784 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BC788 */ mem.write_u32(ctx.r[1] + (40), ctx.r[9]); // stw r9, 40(r1)
    /* 0x800BC78C */ mem.write_u32(ctx.r[10] + (4), ctx.r[0]); // stw r0, 4(r10)
    /* 0x800BC790 */ mem.write_u32(ctx.r[10] + (8), ctx.r[11]); // stw r11, 8(r10)
    /* 0x800BC794 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (24)); // lwz r9, 24(r1)
    /* 0x800BC798 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BC79C */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BC7A0 */ mem.write_u32(ctx.r[1] + (56), ctx.r[9]); // stw r9, 56(r1)
    /* 0x800BC7A4 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BC7A8 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BC7AC */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BC7B0 */ ctx.r[3] = 0x00000016u; // li r3, 22
    /* 0x800BC7B4 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800BC7B8 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BC7BC */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
    /* 0x800BC7C0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC7C4 */ ctx.r[10] = 0x801D0000u; // lis r10, 0x801D
    /* 0x800BC7C8 */ ctx.r[11] = 0x00002328u; // li r11, 9000
    /* 0x800BC7CC */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BC7D0 */ ctx.r[0] = ctx.r[0] | 0x00020000u; // oris r0, r0, 0x0002
    /* 0x800BC7D4 */ mem.write_u32(ctx.r[9] + (292), ctx.r[0]); // stw r0, 292(r9)
    /* 0x800BC7D8 */ mem.write_u32(ctx.r[10] + (-20536), ctx.r[11]); // stw r11, -20536(r10) [0x801CAFC8]
    /* 0x800BC7DC */ Snd_bgmtbl_chg_r80d_800CD370(ctx, mem); // bl 0x800CD370 <Snd_bgmtbl_chg_r80d(void)>
    /* 0x800BC7E0 */ mem.write_u32(ctx.r[13] + (-29612), ctx.r[30]); // stw r30, -29612(r13) [str_req]
loc_800BC7E4:;
    /* 0x800BC7E4 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (84)); // lwz r0, 84(r1)
    /* 0x800BC7E8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC7EC */ ctx.lmw(mem, 30, ctx.r[1] + (72)); // lmw r30, 72(r1)
    /* 0x800BC7F0 */ ctx.r[1] = ctx.r[1] + (80); // addi r1, r1, 80
    /* 0x800BC7F4 */ return; // blr
}

// [0x800BC7F8] __static_initialization_and_destruction_0 (r80d.obj, 10 insns / 0x28 bytes)
void static_initialization_and_destruction_0_800BC7F8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BC7F8 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BC7FC */ ctx.r[0] = ctx.r[0] | 0xFFFFu; // ori r0, r0, 0xFFFF
    /* 0x800BC800 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[4]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r4, r0
    /* 0x800BC804 */ if (ctx.eval_bc(4, 2)) return; // bclr 4, 2
    /* 0x800BC808 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BC80C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BC810 */ ctx.r[11] = 0x801C0000u; // lis r11, 0x801C
    /* 0x800BC814 */ ctx.r[9] = ctx.r[9] + (-30272); // addi r9, r9, -30272 -> cIdMain virtual table
    /* 0x800BC818 */ mem.write_u32(ctx.r[11] + (19356), ctx.r[9]); // stw r9, 19356(r11) [0x801C4B9C]
    /* 0x800BC81C */ return; // blr
}

// [0x800BC820] global constructors keyed to R80dInit(void) (r80d.obj, 11 insns / 0x2C bytes)
void global_constructors_keyed_to_R80dInit_800BC820(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BC820 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BC824 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BC828 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BC82C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BC830 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BC834 */ ctx.r[4] = ctx.r[4] | 0xFFFFu; // ori r4, r4, 0xFFFF
    /* 0x800BC838 */ static_initialization_and_destruction_0_800BC7F8(ctx, mem); // bl 0x800BC7F8 <__static_initialization_and_destruction_0>
    /* 0x800BC83C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BC840 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC844 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BC848 */ return; // blr
}

// [0x800BC84C] global destructors keyed to R80dInit(void) (r80d.obj, 11 insns / 0x2C bytes)
void global_destructors_keyed_to_R80dInit_800BC84C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BC84C */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BC850 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BC854 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BC858 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BC85C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BC860 */ ctx.r[4] = ctx.r[4] | 0xFFFFu; // ori r4, r4, 0xFFFF
    /* 0x800BC864 */ static_initialization_and_destruction_0_800BC7F8(ctx, mem); // bl 0x800BC7F8 <__static_initialization_and_destruction_0>
    /* 0x800BC868 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BC86C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC870 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BC874 */ return; // blr
}

// [0x800BC878] {anonymous}::lightChange(void) (r80e.obj, 17 insns / 0x44 bytes)
void anonymous___lightChange_800BC878(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BC878 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BC87C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BC880 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BC884 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC888 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (292)); // lwz r0, 292(r9)
    /* 0x800BC88C */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BC890 */ if (ctx.eval_bc(12, 2)) goto loc_800BC8AC; // bc 12, 2, 0x800BC8AC
    /* 0x800BC894 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (272)); // lwz r9, 272(r9)
    /* 0x800BC898 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (84)); // lwz r3, 84(r9)
    /* 0x800BC89C */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BC8A0 */ LightDataSet_8009A088(ctx, mem); // bl 0x8009A088 <LightDataSet(unsigned long)>
    /* 0x800BC8A4 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BC8A8 */ LightUpdate_8009A9AC(ctx, mem); // bl 0x8009A9AC <LightUpdate(long)>
loc_800BC8AC:;
    /* 0x800BC8AC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BC8B0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BC8B4 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BC8B8 */ return; // blr
}

// [0x800BC8BC] R80eInit(void) (r80e.obj, 206 insns / 0x338 bytes)
void R80eInit_800BC8BC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BC8BC */ ctx.r[1] += (-88); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -88(r1)
    /* 0x800BC8C0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BC8C4 */ mem.write_f64(ctx.r[1] + (80), ctx.f[31]); // stfd f31, 80(r1)
    /* 0x800BC8C8 */ ctx.stmw(mem, 28, ctx.r[1] + (64)); // stmw r28, 64(r1)
    /* 0x800BC8CC */ mem.write_u32(ctx.r[1] + (92), ctx.r[0]); // stw r0, 92(r1)
    /* 0x800BC8D0 */ anonymous___lightChange_800BC878(ctx, mem); // bl 0x800BC878 <{anonymous}::lightChange(void)>
    /* 0x800BC8D4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC8D8 */ ctx.r[11] = 0x00000000u; // li r11, 0
    /* 0x800BC8DC */ mem.write_u32(ctx.r[13] + (-29604), ctx.r[11]); // stw r11, -29604(r13) [{anonymous}::pEvent12]
    /* 0x800BC8E0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BC8E4 */ mem.write_u32(ctx.r[13] + (-29600), ctx.r[11]); // stw r11, -29600(r13) [{anonymous}::pEvent13]
    /* 0x800BC8E8 */ mem.write_u32(ctx.r[13] + (-29596), ctx.r[11]); // stw r11, -29596(r13) [{anonymous}::pEvent22]
    /* 0x800BC8EC */ ctx.r[9] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x2000
    /* 0x800BC8F0 */ mem.write_u32(ctx.r[13] + (-29592), ctx.r[11]); // stw r11, -29592(r13) [{anonymous}::pEvent33]
    /* 0x800BC8F4 */ if (ctx.eval_bc(12, 2)) goto loc_800BC900; // bc 12, 2, 0x800BC900
    /* 0x800BC8F8 */ mem.write_u32(ctx.r[13] + (-29608), ctx.r[11]); // stw r11, -29608(r13) [str_req]
    /* 0x800BC8FC */ goto loc_800BC908; // b 0x800BC908 <sub_800BC908>
loc_800BC900:;
    /* 0x800BC900 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BC904 */ mem.write_u32(ctx.r[13] + (-29608), ctx.r[0]); // stw r0, -29608(r13) [str_req]
loc_800BC908:;
    /* 0x800BC908 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BC90C */ ctx.r[0] = mem.read_u32(ctx.r[10] + (292)); // lwz r0, 292(r10)
    /* 0x800BC910 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BC914 */ if (ctx.eval_bc(12, 2)) goto loc_800BC920; // bc 12, 2, 0x800BC920
    /* 0x800BC918 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BC91C */ mem.write_u32(ctx.r[13] + (-29608), ctx.r[0]); // stw r0, -29608(r13) [str_req]
loc_800BC920:;
    /* 0x800BC920 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BC924 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BC928 */ ctx.f[31] = mem.read_f32(ctx.r[9] + (-12012)); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // lfs f31, -12012(r9) [0x8016D114]
    /* 0x800BC92C */ ctx.r[30] = ctx.r[1] + (16); // addi r30, r1, 16
    /* 0x800BC930 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-12008)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12008(r11) [0x8016D118]
    /* 0x800BC934 */ ctx.r[5] = ctx.r[30]; // mr r5, r30
    /* 0x800BC938 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[31])); // stfs f31, 16(r1)
    /* 0x800BC93C */ ctx.r[11] = ctx.r[1] + (32); // addi r11, r1, 32
    /* 0x800BC940 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r30)
    /* 0x800BC944 */ ctx.r[6] = ctx.r[11]; // mr r6, r11
    /* 0x800BC948 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r30)
    /* 0x800BC94C */ ctx.r[31] = ctx.r[11]; // mr r31, r11
    /* 0x800BC950 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[31])); // stfs f31, 32(r1)
    /* 0x800BC954 */ ctx.r[29] = ctx.r[30]; // mr r29, r30
    /* 0x800BC958 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[31])); // stfs f31, 4(r11)
    /* 0x800BC95C */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r11)
    /* 0x800BC960 */ ctx.r[9] = mem.read_u32(ctx.r[10] + (272)); // lwz r9, 272(r10)
    /* 0x800BC964 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (76)); // lwz r3, 76(r9)
    /* 0x800BC968 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (80)); // lwz r4, 80(r9)
    /* 0x800BC96C */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BC970 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BC974 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BC978 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BC97C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BC980 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-12004)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -12004(r9) [0x8016D11C]
    /* 0x800BC984 */ ctx.r[10] = ctx.r[1] + (48); // addi r10, r1, 48
    /* 0x800BC988 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-12000)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12000(r11) [0x8016D120 /* "FyE^" */]
    /* 0x800BC98C */ ctx.r[6] = ctx.r[10]; // mr r6, r10
    /* 0x800BC990 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[31])); // stfs f31, 16(r1)
    /* 0x800BC994 */ ctx.r[5] = ctx.r[30]; // mr r5, r30
    /* 0x800BC998 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r30)
    /* 0x800BC99C */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r30)
    /* 0x800BC9A0 */ mem.write_f32(ctx.r[1] + (48), static_cast<float>(ctx.f[31])); // stfs f31, 48(r1)
    /* 0x800BC9A4 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r10)
    /* 0x800BC9A8 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[31])); // stfs f31, 4(r10)
    /* 0x800BC9AC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC9B0 */ mem.write_u32(ctx.r[13] + (-29588), ctx.r[3]); // stw r3, -29588(r13) [{anonymous}::pEle]
    /* 0x800BC9B4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BC9B8 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (88)); // lwz r3, 88(r9)
    /* 0x800BC9BC */ ctx.r[4] = mem.read_u32(ctx.r[9] + (92)); // lwz r4, 92(r9)
    /* 0x800BC9C0 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BC9C4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BC9C8 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BC9CC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BC9D0 */ mem.write_u32(ctx.r[13] + (-29584), ctx.r[3]); // stw r3, -29584(r13) [{anonymous}::pSht]
    /* 0x800BC9D4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BC9D8 */ ctx.r[11] = ctx.r[0] & 0x00080000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0008
    /* 0x800BC9DC */ if (ctx.eval_bc(4, 2)) goto loc_800BCA60; // bc 4, 2, 0x800BCA60
    /* 0x800BC9E0 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BC9E4 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BC9E8 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BC9EC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BC9F0 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BC9F4 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BC9F8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BC9FC */ mem.write_u32(ctx.r[13] + (-29604), ctx.r[0]); // stw r0, -29604(r13) [{anonymous}::pEvent12]
    /* 0x800BCA00 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (44)); // lwz r4, 44(r9)
    /* 0x800BCA04 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BCA08 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BCA0C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29588)); // lwz r11, -29588(r13) [{anonymous}::pEle]
    /* 0x800BCA10 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCA14 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BCA18 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BCA1C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCA20 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCA24 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BCA28 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29584)); // lwz r11, -29584(r13) [{anonymous}::pSht]
    /* 0x800BCA2C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCA30 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BCA34 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BCA38 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCA3C */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCA40 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BCA44 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BCA48 */ ctx.r[11] = 0x00000001u; // li r11, 1
    /* 0x800BCA4C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BCA50 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BCA54 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
    /* 0x800BCA58 */ mem.write_u32(ctx.r[13] + (-29608), ctx.r[11]); // stw r11, -29608(r13) [str_req]
    /* 0x800BCA5C */ goto loc_800BCAD0; // b 0x800BCAD0 <sub_800BCAD0>
loc_800BCA60:;
    /* 0x800BCA60 */ ctx.r[0] = mem.read_u16(ctx.r[9] + (27258)); // lhz r0, 27258(r9)
    /* 0x800BCA64 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 2060); // cmpwi cr0, r0, 2060
    /* 0x800BCA68 */ if (ctx.eval_bc(4, 2)) goto loc_800BCAD0; // bc 4, 2, 0x800BCAD0
    /* 0x800BCA6C */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BCA70 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BCA74 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BCA78 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BCA7C */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BCA80 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BCA84 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BCA88 */ mem.write_u32(ctx.r[13] + (-29592), ctx.r[0]); // stw r0, -29592(r13) [{anonymous}::pEvent33]
    /* 0x800BCA8C */ ctx.r[4] = mem.read_u32(ctx.r[9] + (72)); // lwz r4, 72(r9)
    /* 0x800BCA90 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BCA94 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BCA98 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29588)); // lwz r11, -29588(r13) [{anonymous}::pEle]
    /* 0x800BCA9C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCAA0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BCAA4 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BCAA8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCAAC */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCAB0 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BCAB4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29584)); // lwz r11, -29584(r13) [{anonymous}::pSht]
    /* 0x800BCAB8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCABC */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BCAC0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BCAC4 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCAC8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCACC */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BCAD0:;
    /* 0x800BCAD0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BCAD4 */ ctx.r[28] = 0x00000000u; // li r28, 0
    /* 0x800BCAD8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BCADC */ ctx.r[9] = ctx.r[0] & 0x00040000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x0004
    /* 0x800BCAE0 */ if (ctx.eval_bc(4, 2)) goto loc_800BCB70; // bc 4, 2, 0x800BCB70
    /* 0x800BCAE4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BCAE8 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-12012)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -12012(r9) [0x8016D114]
    /* 0x800BCAEC */ mem.write_f32(ctx.r[31] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r31)
    /* 0x800BCAF0 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BCAF4 */ mem.write_f32(ctx.r[29] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r29)
    /* 0x800BCAF8 */ mem.write_f32(ctx.r[29] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r29)
    /* 0x800BCAFC */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BCB00 */ mem.write_f32(ctx.r[31] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r31)
    /* 0x800BCB04 */ EspPullCoreKind_80084BA0(ctx, mem); // bl 0x80084BA0 <EspPullCoreKind(void)>
    /* 0x800BCB08 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BCB0C */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800BCB10 */ mem.write_u16(ctx.r[13] + (-29576), static_cast<uint16_t>(ctx.r[3])); // sth r3, -29576(r13) [{anonymous}::R80e_core_kind]
    /* 0x800BCB14 */ ctx.r[6] = ctx.r[31]; // mr r6, r31
    /* 0x800BCB18 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BCB1C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BCB20 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (96)); // lwz r3, 96(r9)
    /* 0x800BCB24 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BCB28 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BCB2C */ mem.write_u32(ctx.r[13] + (-29580), ctx.r[3]); // stw r3, -29580(r13) [{anonymous}::R80e_wall]
    /* 0x800BCB30 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BCB34 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BCB38 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BCB3C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BCB40 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BCB44 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BCB48 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BCB4C */ ctx.r[9] = mem.read_u8(ctx.r[13] + (-29575)); // lbz r9, -29575(r13) [sda1_0x8026E859]
    /* 0x800BCB50 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BCB54 */ mem.write_u32(ctx.r[1] + (8), ctx.r[28]); // stw r28, 8(r1)
    /* 0x800BCB58 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BCB5C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BCB60 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BCB64 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800BCB68 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BCB6C */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800BCB70:;
    /* 0x800BCB70 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BCB74 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BCB78 */ ctx.r[9] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x2000
    /* 0x800BCB7C */ if (ctx.eval_bc(4, 2)) goto loc_800BCB9C; // bc 4, 2, 0x800BCB9C
    /* 0x800BCB80 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BCB84 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BCB88 */ SceAtSetEnable_800C20A0(ctx, mem); // bl 0x800C20A0 <SceAtSetEnable(unsigned long, int)>
    /* 0x800BCB8C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BCB90 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BCB94 */ ctx.r[9] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andis. r9, r0, 0x2000
    /* 0x800BCB98 */ if (ctx.eval_bc(12, 2)) goto loc_800BCBDC; // bc 12, 2, 0x800BCBDC
loc_800BCB9C:;
    /* 0x800BCB9C */ ctx.r[4] = 0x00000001u; // li r4, 1
    /* 0x800BCBA0 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BCBA4 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BCBA8 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BCBAC */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BCBB0 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BCBB4 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BCBB8 */ mem.write_u32(ctx.r[1] + (8), ctx.r[28]); // stw r28, 8(r1)
    /* 0x800BCBBC */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BCBC0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BCBC4 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BCBC8 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BCBCC */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800BCBD0 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BCBD4 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BCBD8 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800BCBDC:;
    /* 0x800BCBDC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (92)); // lwz r0, 92(r1)
    /* 0x800BCBE0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCBE4 */ ctx.lmw(mem, 28, ctx.r[1] + (64)); // lmw r28, 64(r1)
    /* 0x800BCBE8 */ ctx.f[31] = mem.read_f64(ctx.r[1] + (80)); // lfd f31, 80(r1)
    /* 0x800BCBEC */ ctx.r[1] = ctx.r[1] + (88); // addi r1, r1, 88
    /* 0x800BCBF0 */ return; // blr
}

// [0x800BCBF4] R80eMain(void) (r80e.obj, 375 insns / 0x5DC bytes)
void R80eMain_800BCBF4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BCBF4 */ ctx.r[1] += (-112); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -112(r1)
    /* 0x800BCBF8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BCBFC */ ctx.stmw(mem, 27, ctx.r[1] + (92)); // stmw r27, 92(r1)
    /* 0x800BCC00 */ mem.write_u32(ctx.r[1] + (116), ctx.r[0]); // stw r0, 116(r1)
    /* 0x800BCC04 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29592)); // lwz r3, -29592(r13) [{anonymous}::pEvent33]
    /* 0x800BCC08 */ ctx.r[31] = 0x00000000u; // li r31, 0
    /* 0x800BCC0C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BCC10 */ if (ctx.eval_bc(12, 2)) goto loc_800BCC8C; // bc 12, 2, 0x800BCC8C
    /* 0x800BCC14 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BCC18 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BCC1C */ if (ctx.eval_bc(12, 2)) goto loc_800BD190; // bc 12, 2, 0x800BD190
    /* 0x800BCC20 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29592)); // lwz r11, -29592(r13) [{anonymous}::pEvent33]
    /* 0x800BCC24 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BCC28 */ if (ctx.eval_bc(12, 2)) goto loc_800BCC48; // bc 12, 2, 0x800BCC48
    /* 0x800BCC2C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BCC30 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BCC34 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BCC38 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BCC3C */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCC40 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCC44 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BCC48:;
    /* 0x800BCC48 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29588)); // lwz r11, -29588(r13) [{anonymous}::pEle]
    /* 0x800BCC4C */ mem.write_u32(ctx.r[13] + (-29592), ctx.r[31]); // stw r31, -29592(r13) [{anonymous}::pEvent33]
    /* 0x800BCC50 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCC54 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BCC58 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BCC5C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCC60 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCC64 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BCC68 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29584)); // lwz r11, -29584(r13) [{anonymous}::pSht]
    /* 0x800BCC6C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCC70 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BCC74 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BCC78 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCC7C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCC80 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BCC84 */ anonymous___lightChange_800BC878(ctx, mem); // bl 0x800BC878 <{anonymous}::lightChange(void)>
    /* 0x800BCC88 */ goto loc_800BD190; // b 0x800BD190 <sub_800BD190>
loc_800BCC8C:;
    /* 0x800BCC8C */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29604)); // lwz r3, -29604(r13) [{anonymous}::pEvent12]
    /* 0x800BCC90 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BCC94 */ if (ctx.eval_bc(12, 2)) goto loc_800BCDD4; // bc 12, 2, 0x800BCDD4
    /* 0x800BCC98 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BCC9C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BCCA0 */ if (ctx.eval_bc(12, 2)) goto loc_800BD190; // bc 12, 2, 0x800BD190
    /* 0x800BCCA4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29604)); // lwz r11, -29604(r13) [{anonymous}::pEvent12]
    /* 0x800BCCA8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BCCAC */ if (ctx.eval_bc(12, 2)) goto loc_800BCCCC; // bc 12, 2, 0x800BCCCC
    /* 0x800BCCB0 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BCCB4 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BCCB8 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BCCBC */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BCCC0 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCCC4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCCC8 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BCCCC:;
    /* 0x800BCCCC */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BCCD0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BCCD4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11996)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11996(r9) [0x8016D124]
    /* 0x800BCCD8 */ ctx.r[10] = ctx.r[1] + (8); // addi r10, r1, 8
    /* 0x800BCCDC */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-11992)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11992(r11) [0x8016D128]
    /* 0x800BCCE0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BCCE4 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800BCCE8 */ ctx.r[7] = ctx.r[1] + (24); // addi r7, r1, 24
    /* 0x800BCCEC */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r10)
    /* 0x800BCCF0 */ ctx.r[11] = ctx.r[1] + (40); // addi r11, r1, 40
    /* 0x800BCCF4 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800BCCF8 */ ctx.r[3] = ctx.r[11]; // mr r3, r11
    /* 0x800BCCFC */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-11988)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11988(r9) [0x8016D12C]
    /* 0x800BCD00 */ ctx.r[6] = ctx.r[1] + (56); // addi r6, r1, 56
    /* 0x800BCD04 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800BCD08 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BCD0C */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r7)
    /* 0x800BCD10 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BCD14 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r7)
    /* 0x800BCD18 */ mem.write_u32(ctx.r[13] + (-29604), ctx.r[31]); // stw r31, -29604(r13) [{anonymous}::pEvent12]
    /* 0x800BCD1C */ ctx.r[9] = mem.read_u32(ctx.r[1] + (8)); // lwz r9, 8(r1)
    /* 0x800BCD20 */ ctx.r[0] = mem.read_u32(ctx.r[10] + (4)); // lwz r0, 4(r10)
    /* 0x800BCD24 */ ctx.r[8] = mem.read_u32(ctx.r[10] + (8)); // lwz r8, 8(r10)
    /* 0x800BCD28 */ mem.write_u32(ctx.r[1] + (40), ctx.r[9]); // stw r9, 40(r1)
    /* 0x800BCD2C */ mem.write_u32(ctx.r[11] + (8), ctx.r[8]); // stw r8, 8(r11)
    /* 0x800BCD30 */ mem.write_u32(ctx.r[11] + (4), ctx.r[0]); // stw r0, 4(r11)
    /* 0x800BCD34 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (24)); // lwz r9, 24(r1)
    /* 0x800BCD38 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BCD3C */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BCD40 */ mem.write_u32(ctx.r[1] + (56), ctx.r[9]); // stw r9, 56(r1)
    /* 0x800BCD44 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BCD48 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BCD4C */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BCD50 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29588)); // lwz r11, -29588(r13) [{anonymous}::pEle]
    /* 0x800BCD54 */ mem.write_u32(ctx.r[13] + (-29608), ctx.r[31]); // stw r31, -29608(r13) [str_req]
    /* 0x800BCD58 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCD5C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BCD60 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BCD64 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCD68 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCD6C */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BCD70 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29584)); // lwz r11, -29584(r13) [{anonymous}::pSht]
    /* 0x800BCD74 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCD78 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BCD7C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BCD80 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCD84 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCD88 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BCD8C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BCD90 */ ctx.r[31] = mem.read_u32(ctx.r[9] + (25484)); // lwz r31, 25484(r9)
    /* 0x800BCD94 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // cmpwi cr0, r31, 0
    /* 0x800BCD98 */ if (ctx.eval_bc(12, 2)) goto loc_800BD190; // bc 12, 2, 0x800BD190
    /* 0x800BCD9C */ ctx.r[9] = mem.read_u16(ctx.r[31] + (4)); // lhz r9, 4(r31)
    /* 0x800BCDA0 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BCDA4 */ ctx.r[0] = mem.read_u16(ctx.r[31] + (6)); // lhz r0, 6(r31)
    /* 0x800BCDA8 */ ctx.r[11] = ctx.r[31] + ctx.r[9]; // add r11, r31, r9
    /* 0x800BCDAC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r10, r0
    /* 0x800BCDB0 */ if (ctx.eval_bc(4, 0)) goto loc_800BD190; // bc 4, 0, 0x800BD190
    /* 0x800BCDB4 */ ctx.r[9] = 0x00000000u; // li r9, 0
loc_800BCDB8:;
    /* 0x800BCDB8 */ mem.write_u32(ctx.r[11] + (0), ctx.r[9]); // stw r9, 0(r11)
    /* 0x800BCDBC */ ctx.r[10] = ctx.r[10] + (1); // addi r10, r10, 1
    /* 0x800BCDC0 */ ctx.r[11] = ctx.r[11] + (72); // addi r11, r11, 72
    /* 0x800BCDC4 */ ctx.r[0] = mem.read_u16(ctx.r[31] + (6)); // lhz r0, 6(r31)
    /* 0x800BCDC8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r10, r0
    /* 0x800BCDCC */ if (ctx.eval_bc(12, 0)) goto loc_800BCDB8; // bc 12, 0, 0x800BCDB8
    /* 0x800BCDD0 */ goto loc_800BD190; // b 0x800BD190 <sub_800BD190>
loc_800BCDD4:;
    /* 0x800BCDD4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BCDD8 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BCDDC */ ctx.r[0] = ctx.r[11] & 0x00040000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andis. r0, r11, 0x0004
    /* 0x800BCDE0 */ if (ctx.eval_bc(4, 2)) goto loc_800BCE68; // bc 4, 2, 0x800BCE68
    /* 0x800BCDE4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BCDE8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BCDEC */ if (ctx.eval_bc(4, 0)) goto loc_800BCE68; // bc 4, 0, 0x800BCE68
    /* 0x800BCDF0 */ ctx.r[0] = ctx.r[11] | 0x00040000u; // oris r0, r11, 0x0004
    /* 0x800BCDF4 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BCDF8 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BCDFC */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BCE00 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BCE04 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BCE08 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BCE0C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BCE10 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BCE14 */ mem.write_u32(ctx.r[13] + (-29600), ctx.r[0]); // stw r0, -29600(r13) [{anonymous}::pEvent13]
    /* 0x800BCE18 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (48)); // lwz r4, 48(r9)
    /* 0x800BCE1C */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BCE20 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BCE24 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29588)); // lwz r11, -29588(r13) [{anonymous}::pEle]
    /* 0x800BCE28 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCE2C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BCE30 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BCE34 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCE38 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCE3C */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BCE40 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29584)); // lwz r11, -29584(r13) [{anonymous}::pSht]
    /* 0x800BCE44 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCE48 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BCE4C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BCE50 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCE54 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCE58 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BCE5C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BCE60 */ ctx.r[4] = 0x000000C8u; // li r4, 200
    /* 0x800BCE64 */ Snd_str_fadeout_800CD394(ctx, mem); // bl 0x800CD394 <Snd_str_fadeout(long, long)>
loc_800BCE68:;
    /* 0x800BCE68 */ ctx.r[31] = mem.read_u32(ctx.r[13] + (-29600)); // lwz r31, -29600(r13) [{anonymous}::pEvent13]
    /* 0x800BCE6C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // cmpwi cr0, r31, 0
    /* 0x800BCE70 */ if (ctx.eval_bc(12, 2)) goto loc_800BD00C; // bc 12, 2, 0x800BD00C
    /* 0x800BCE74 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800BCE78 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BCE7C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BCE80 */ if (ctx.eval_bc(12, 2)) goto loc_800BD190; // bc 12, 2, 0x800BD190
    /* 0x800BCE84 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29600)); // lwz r11, -29600(r13) [{anonymous}::pEvent13]
    /* 0x800BCE88 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BCE8C */ if (ctx.eval_bc(12, 2)) goto loc_800BCEAC; // bc 12, 2, 0x800BCEAC
    /* 0x800BCE90 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BCE94 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BCE98 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BCE9C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BCEA0 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCEA4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCEA8 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BCEAC:;
    /* 0x800BCEAC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BCEB0 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BCEB4 */ mem.write_u32(ctx.r[13] + (-29600), ctx.r[0]); // stw r0, -29600(r13) [{anonymous}::pEvent13]
    /* 0x800BCEB8 */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800BCEBC */ ctx.r[0] = mem.read_u32(ctx.r[9] + (332)); // lwz r0, 332(r9)
    /* 0x800BCEC0 */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800BCEC4 */ ctx.r[4] = 0x00000047u; // li r4, 71
    /* 0x800BCEC8 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BCECC */ ctx.r[0] = ctx.r[0] | 0x10000000u; // oris r0, r0, 0x1000
    /* 0x800BCED0 */ ctx.r[30] = ctx.r[1] + (8); // addi r30, r1, 8
    /* 0x800BCED4 */ mem.write_u32(ctx.r[9] + (332), ctx.r[0]); // stw r0, 332(r9)
    /* 0x800BCED8 */ ctx.r[29] = ctx.r[1] + (24); // addi r29, r1, 24
    /* 0x800BCEDC */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800BCEE0 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29588)); // lwz r11, -29588(r13) [{anonymous}::pEle]
    /* 0x800BCEE4 */ ctx.r[28] = ctx.r[1] + (40); // addi r28, r1, 40
    /* 0x800BCEE8 */ ctx.r[27] = ctx.r[1] + (72); // addi r27, r1, 72
    /* 0x800BCEEC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCEF0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BCEF4 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BCEF8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCEFC */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCF00 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BCF04 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29584)); // lwz r11, -29584(r13) [{anonymous}::pSht]
    /* 0x800BCF08 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BCF0C */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BCF10 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BCF14 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BCF18 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BCF1C */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BCF20 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BCF24 */ ctx.r[31] = mem.read_u32(ctx.r[9] + (25484)); // lwz r31, 25484(r9)
    /* 0x800BCF28 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // cmpwi cr0, r31, 0
    /* 0x800BCF2C */ if (ctx.eval_bc(12, 2)) goto loc_800BCF70; // bc 12, 2, 0x800BCF70
    /* 0x800BCF30 */ ctx.r[0] = mem.read_u16(ctx.r[31] + (4)); // lhz r0, 4(r31)
    /* 0x800BCF34 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BCF38 */ ctx.r[9] = mem.read_u16(ctx.r[31] + (6)); // lhz r9, 6(r31)
    /* 0x800BCF3C */ ctx.r[11] = ctx.r[31] + ctx.r[0]; // add r11, r31, r0
    /* 0x800BCF40 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), static_cast<int32_t>(ctx.r[9])); // cmpw cr0, r10, r9
    /* 0x800BCF44 */ if (ctx.eval_bc(4, 0)) goto loc_800BCF70; // bc 4, 0, 0x800BCF70
    /* 0x800BCF48 */ ctx.r[9] = 0x00000001u; // li r9, 1
loc_800BCF4C:;
    /* 0x800BCF4C */ ctx.r[0] = mem.read_u16(ctx.r[11] + (52)); // lhz r0, 52(r11)
    /* 0x800BCF50 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 2061); // cmpwi cr0, r0, 2061
    /* 0x800BCF54 */ if (ctx.eval_bc(4, 2)) goto loc_800BCF5C; // bc 4, 2, 0x800BCF5C
    /* 0x800BCF58 */ mem.write_u32(ctx.r[11] + (0), ctx.r[9]); // stw r9, 0(r11)
loc_800BCF5C:;
    /* 0x800BCF5C */ ctx.r[0] = mem.read_u16(ctx.r[31] + (6)); // lhz r0, 6(r31)
    /* 0x800BCF60 */ ctx.r[10] = ctx.r[10] + (1); // addi r10, r10, 1
    /* 0x800BCF64 */ ctx.r[11] = ctx.r[11] + (72); // addi r11, r11, 72
    /* 0x800BCF68 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r10, r0
    /* 0x800BCF6C */ if (ctx.eval_bc(12, 0)) goto loc_800BCF4C; // bc 12, 0, 0x800BCF4C
loc_800BCF70:;
    /* 0x800BCF70 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29580)); // lwz r3, -29580(r13) [{anonymous}::R80e_wall]
    /* 0x800BCF74 */ ScrAtDelete_8000646C(ctx, mem); // bl 0x8000646C <ScrAtDelete(tagSCR_AT *)>
    /* 0x800BCF78 */ ctx.r[4] = mem.read_u8(ctx.r[13] + (-29575)); // lbz r4, -29575(r13) [sda1_0x8026E859]
    /* 0x800BCF7C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BCF80 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BCF84 */ EspgenDelete_8008E8B8(ctx, mem); // bl 0x8008E8B8 <EspgenDelete(unsigned short, unsigned char, void *)>
    /* 0x800BCF88 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BCF8C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BCF90 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11984)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11984(r9) [0x8016D130]
    /* 0x800BCF94 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BCF98 */ ctx.f[12] = mem.read_f32(ctx.r[11] + (-11992)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -11992(r11) [0x8016D128]
    /* 0x800BCF9C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BCFA0 */ ctx.f[11] = mem.read_f32(ctx.r[10] + (-11980)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -11980(r10) [0x8016D134]
    /* 0x800BCFA4 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BCFA8 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800BCFAC */ ctx.r[3] = ctx.r[28]; // mr r3, r28
    /* 0x800BCFB0 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-11996)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11996(r9) [0x8016D124]
    /* 0x800BCFB4 */ ctx.r[4] = ctx.r[27]; // mr r4, r27
    /* 0x800BCFB8 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r30)
    /* 0x800BCFBC */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BCFC0 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r30)
    /* 0x800BCFC4 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-11988)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11988(r11) [0x8016D12C]
    /* 0x800BCFC8 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[13])); // stfs f13, 24(r1)
    /* 0x800BCFCC */ mem.write_f32(ctx.r[29] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r29)
    /* 0x800BCFD0 */ mem.write_f32(ctx.r[29] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r29)
    /* 0x800BCFD4 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (8)); // lwz r9, 8(r1)
    /* 0x800BCFD8 */ ctx.r[11] = mem.read_u32(ctx.r[30] + (8)); // lwz r11, 8(r30)
    /* 0x800BCFDC */ ctx.r[0] = mem.read_u32(ctx.r[30] + (4)); // lwz r0, 4(r30)
    /* 0x800BCFE0 */ mem.write_u32(ctx.r[1] + (40), ctx.r[9]); // stw r9, 40(r1)
    /* 0x800BCFE4 */ mem.write_u32(ctx.r[28] + (4), ctx.r[0]); // stw r0, 4(r28)
    /* 0x800BCFE8 */ mem.write_u32(ctx.r[28] + (8), ctx.r[11]); // stw r11, 8(r28)
    /* 0x800BCFEC */ ctx.r[9] = mem.read_u32(ctx.r[1] + (24)); // lwz r9, 24(r1)
    /* 0x800BCFF0 */ ctx.r[11] = mem.read_u32(ctx.r[29] + (8)); // lwz r11, 8(r29)
    /* 0x800BCFF4 */ ctx.r[0] = mem.read_u32(ctx.r[29] + (4)); // lwz r0, 4(r29)
    /* 0x800BCFF8 */ mem.write_u32(ctx.r[1] + (72), ctx.r[9]); // stw r9, 72(r1)
    /* 0x800BCFFC */ mem.write_u32(ctx.r[27] + (4), ctx.r[0]); // stw r0, 4(r27)
    /* 0x800BD000 */ mem.write_u32(ctx.r[27] + (8), ctx.r[11]); // stw r11, 8(r27)
    /* 0x800BD004 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BD008 */ goto loc_800BD190; // b 0x800BD190 <sub_800BD190>
loc_800BD00C:;
    /* 0x800BD00C */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29596)); // lwz r3, -29596(r13) [{anonymous}::pEvent22]
    /* 0x800BD010 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BD014 */ if (ctx.eval_bc(12, 2)) goto loc_800BD108; // bc 12, 2, 0x800BD108
    /* 0x800BD018 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BD01C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BD020 */ if (ctx.eval_bc(12, 2)) goto loc_800BD190; // bc 12, 2, 0x800BD190
    /* 0x800BD024 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29596)); // lwz r11, -29596(r13) [{anonymous}::pEvent22]
    /* 0x800BD028 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BD02C */ if (ctx.eval_bc(12, 2)) goto loc_800BD04C; // bc 12, 2, 0x800BD04C
    /* 0x800BD030 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BD034 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BD038 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BD03C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BD040 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BD044 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD048 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BD04C:;
    /* 0x800BD04C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29588)); // lwz r11, -29588(r13) [{anonymous}::pEle]
    /* 0x800BD050 */ mem.write_u32(ctx.r[13] + (-29596), ctx.r[31]); // stw r31, -29596(r13) [{anonymous}::pEvent22]
    /* 0x800BD054 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BD058 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BD05C */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BD060 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD064 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BD068 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BD06C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29584)); // lwz r11, -29584(r13) [{anonymous}::pSht]
    /* 0x800BD070 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BD074 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BD078 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BD07C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD080 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BD084 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BD088 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BD08C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BD090 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11996)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11996(r9) [0x8016D124]
    /* 0x800BD094 */ ctx.r[8] = 0x00000008u; // li r8, 8
    /* 0x800BD098 */ ctx.r[0] = mem.read_u8(ctx.r[10] + (27256)); // lbz r0, 27256(r10)
    /* 0x800BD09C */ ctx.r[7] = 0x0000000Cu; // li r7, 12
    /* 0x800BD0A0 */ ctx.r[6] = 0x00000004u; // li r6, 4
    /* 0x800BD0A4 */ mem.write_u8(ctx.r[10] + (27258), static_cast<uint8_t>(ctx.r[0])); // stb r0, 27258(r10)
    /* 0x800BD0A8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD0AC */ ctx.r[0] = mem.read_u8(ctx.r[11] + (27257)); // lbz r0, 27257(r11)
    /* 0x800BD0B0 */ mem.write_u8(ctx.r[11] + (27259), static_cast<uint8_t>(ctx.r[0])); // stb r0, 27259(r11)
    /* 0x800BD0B4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD0B8 */ mem.write_u8(ctx.r[9] + (27277), static_cast<uint8_t>(ctx.r[8])); // stb r8, 27277(r9)
    /* 0x800BD0BC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD0C0 */ mem.write_u8(ctx.r[11] + (27276), static_cast<uint8_t>(ctx.r[7])); // stb r7, 27276(r11)
    /* 0x800BD0C4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD0C8 */ mem.write_u8(ctx.r[9] + (260), static_cast<uint8_t>(ctx.r[6])); // stb r6, 260(r9)
    /* 0x800BD0CC */ mem.write_f32(ctx.r[9] + (27272), static_cast<float>(ctx.f[0])); // stfs f0, 27272(r9)
    /* 0x800BD0D0 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD0D4 */ mem.write_f32(ctx.r[9] + (27260), static_cast<float>(ctx.f[0])); // stfs f0, 27260(r9)
    /* 0x800BD0D8 */ mem.write_f32(ctx.r[9] + (27264), static_cast<float>(ctx.f[0])); // stfs f0, 27264(r9)
    /* 0x800BD0DC */ mem.write_f32(ctx.r[9] + (27268), static_cast<float>(ctx.f[0])); // stfs f0, 27268(r9)
    /* 0x800BD0E0 */ mem.write_u8(ctx.r[11] + (261), static_cast<uint8_t>(ctx.r[31])); // stb r31, 261(r11)
    /* 0x800BD0E4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD0E8 */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[31])); // stb r31, 262(r9)
    /* 0x800BD0EC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD0F0 */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[31])); // stb r31, 263(r11)
    /* 0x800BD0F4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD0F8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (336)); // lwz r0, 336(r9)
    /* 0x800BD0FC */ ctx.r[0] = ctx.r[0] | 0x7D010000u; // oris r0, r0, 0x7D01
    /* 0x800BD100 */ mem.write_u32(ctx.r[9] + (336), ctx.r[0]); // stw r0, 336(r9)
    /* 0x800BD104 */ goto loc_800BD190; // b 0x800BD190 <sub_800BD190>
loc_800BD108:;
    /* 0x800BD108 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD10C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BD110 */ ctx.r[11] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x2000
    /* 0x800BD114 */ if (ctx.eval_bc(12, 2)) goto loc_800BD190; // bc 12, 2, 0x800BD190
    /* 0x800BD118 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BD11C */ ctx.r[11] = ctx.r[0] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x4000
    /* 0x800BD120 */ if (ctx.eval_bc(12, 2)) goto loc_800BD190; // bc 12, 2, 0x800BD190
    /* 0x800BD124 */ ctx.rlwinm(0, 0, 0u, 2u, 0u, false); // rlwinm r0, r0, 0, 2, 0
    /* 0x800BD128 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BD12C */ mem.write_u32(ctx.r[9] + (340), ctx.r[0]); // stw r0, 340(r9)
    /* 0x800BD130 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BD134 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BD138 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD13C */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BD140 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BD144 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BD148 */ mem.write_u32(ctx.r[13] + (-29596), ctx.r[0]); // stw r0, -29596(r13) [{anonymous}::pEvent22]
    /* 0x800BD14C */ ctx.r[4] = mem.read_u32(ctx.r[9] + (52)); // lwz r4, 52(r9)
    /* 0x800BD150 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BD154 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BD158 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29588)); // lwz r11, -29588(r13) [{anonymous}::pEle]
    /* 0x800BD15C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BD160 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BD164 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BD168 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD16C */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BD170 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BD174 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29584)); // lwz r11, -29584(r13) [{anonymous}::pSht]
    /* 0x800BD178 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BD17C */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BD180 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BD184 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BD188 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD18C */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BD190:;
    /* 0x800BD190 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29608)); // lwz r0, -29608(r13) [str_req]
    /* 0x800BD194 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BD198 */ if (ctx.eval_bc(4, 2)) goto loc_800BD1BC; // bc 4, 2, 0x800BD1BC
    /* 0x800BD19C */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BD1A0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BD1A4 */ mem.write_u32(ctx.r[13] + (-29608), ctx.r[0]); // stw r0, -29608(r13) [str_req]
    /* 0x800BD1A8 */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800BD1AC */ ctx.r[5] = 0x00000002u; // li r5, 2
    /* 0x800BD1B0 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BD1B4 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BD1B8 */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
loc_800BD1BC:;
    /* 0x800BD1BC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (116)); // lwz r0, 116(r1)
    /* 0x800BD1C0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD1C4 */ ctx.lmw(mem, 27, ctx.r[1] + (92)); // lmw r27, 92(r1)
    /* 0x800BD1C8 */ ctx.r[1] = ctx.r[1] + (112); // addi r1, r1, 112
    /* 0x800BD1CC */ return; // blr
}

// [0x800BD1D0] R901Init(void) (r901.obj, 1 insns / 0x4 bytes)
void R901Init_800BD1D0(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BD1D0 */ return; // blr
}

// [0x800BD1D4] R901Main(void) (r901.obj, 1 insns / 0x4 bytes)
void R901Main_800BD1D4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BD1D4 */ return; // blr
}

// [0x800BD1D8] R90eInit(void) (r90e.obj, 3 insns / 0xC bytes)
void R90eInit_800BD1D8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BD1D8 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BD1DC */ mem.write_u32(ctx.r[13] + (-29572), ctx.r[0]); // stw r0, -29572(r13) [pEvent14]
    /* 0x800BD1E0 */ return; // blr
}

// [0x800BD1E4] R90eMain(void) (r90e.obj, 107 insns / 0x1AC bytes)
void R90eMain_800BD1E4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BD1E4 */ ctx.r[1] += (-64); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -64(r1)
    /* 0x800BD1E8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BD1EC */ ctx.stmw(mem, 30, ctx.r[1] + (56)); // stmw r30, 56(r1)
    /* 0x800BD1F0 */ mem.write_u32(ctx.r[1] + (68), ctx.r[0]); // stw r0, 68(r1)
    /* 0x800BD1F4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BD1F8 */ ctx.r[30] = ctx.r[1] + (8); // addi r30, r1, 8
    /* 0x800BD1FC */ ctx.r[7] = mem.read_u32(ctx.r[9] + (-11944)); // lwz r7, -11944(r9) [0x8016D158]
    /* 0x800BD200 */ ctx.r[31] = ctx.r[1] + (32); // addi r31, r1, 32
    /* 0x800BD204 */ ctx.r[9] = ctx.r[9] + (-11944); // addi r9, r9, -11944 -> 0x8016D158
    /* 0x800BD208 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800BD20C */ ctx.r[6] = mem.read_u32(ctx.r[9] + (20)); // lwz r6, 20(r9)
    /* 0x800BD210 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BD214 */ ctx.r[8] = mem.read_u32(ctx.r[9] + (4)); // lwz r8, 4(r9)
    /* 0x800BD218 */ ctx.r[5] = 0x00000018u; // li r5, 24
    /* 0x800BD21C */ ctx.r[10] = mem.read_u32(ctx.r[9] + (8)); // lwz r10, 8(r9)
    /* 0x800BD220 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (12)); // lwz r11, 12(r9)
    /* 0x800BD224 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (16)); // lwz r0, 16(r9)
    /* 0x800BD228 */ mem.write_u32(ctx.r[1] + (8), ctx.r[7]); // stw r7, 8(r1)
    /* 0x800BD22C */ mem.write_u32(ctx.r[30] + (4), ctx.r[8]); // stw r8, 4(r30)
    /* 0x800BD230 */ mem.write_u32(ctx.r[30] + (8), ctx.r[10]); // stw r10, 8(r30)
    /* 0x800BD234 */ mem.write_u32(ctx.r[30] + (12), ctx.r[11]); // stw r11, 12(r30)
    /* 0x800BD238 */ mem.write_u32(ctx.r[30] + (16), ctx.r[0]); // stw r0, 16(r30)
    /* 0x800BD23C */ mem.write_u32(ctx.r[30] + (20), ctx.r[6]); // stw r6, 20(r30)
    /* 0x800BD240 */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800BD244 */ ctx.call_indirect(0x800E8A5Cu, mem); // bl 0x800E8A5C <memset>
    /* 0x800BD248 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29572)); // lwz r3, -29572(r13) [pEvent14]
    /* 0x800BD24C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BD250 */ if (ctx.eval_bc(4, 2)) goto loc_800BD2F0; // bc 4, 2, 0x800BD2F0
    /* 0x800BD254 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD258 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BD25C */ ctx.r[11] = ctx.r[0] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x4000
    /* 0x800BD260 */ if (ctx.eval_bc(12, 2)) goto loc_800BD37C; // bc 12, 2, 0x800BD37C
    /* 0x800BD264 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BD268 */ ctx.r[11] = ctx.r[0] & 0x00020000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // andis. r11, r0, 0x0002
    /* 0x800BD26C */ if (ctx.eval_bc(4, 2)) goto loc_800BD37C; // bc 4, 2, 0x800BD37C
    /* 0x800BD270 */ ctx.r[0] = ctx.r[0] | 0x00020000u; // oris r0, r0, 0x0002
    /* 0x800BD274 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BD278 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BD27C */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BD280 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BD284 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD288 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BD28C */ mem.write_u32(ctx.r[13] + (-29572), ctx.r[0]); // stw r0, -29572(r13) [pEvent14]
    /* 0x800BD290 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BD294 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BD298 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (48)); // lwz r4, 48(r9)
    /* 0x800BD29C */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BD2A0 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BD2A4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD2A8 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800BD2AC */ ctx.r[9] = ctx.r[0] & 0x0800u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0800
    /* 0x800BD2B0 */ if (ctx.eval_bc(4, 2)) goto loc_800BD2C8; // bc 4, 2, 0x800BD2C8
    /* 0x800BD2B4 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800BD2B8 */ ctx.r[4] = ctx.r[31]; // mr r4, r31
    /* 0x800BD2BC */ ctx.r[5] = 0x00000003u; // li r5, 3
    /* 0x800BD2C0 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BD2C4 */ SetEm33Sce_800485DC(ctx, mem); // bl 0x800485DC <SetEm33Sce(Vec &, Vec &, unsigned long, unsigned long)>
loc_800BD2C8:;
    /* 0x800BD2C8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD2CC */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29016)); // lwz r0, 29016(r9)
    /* 0x800BD2D0 */ ctx.r[9] = ctx.r[0] & 0x0400u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0400
    /* 0x800BD2D4 */ if (ctx.eval_bc(4, 2)) goto loc_800BD37C; // bc 4, 2, 0x800BD37C
    /* 0x800BD2D8 */ ctx.r[3] = ctx.r[1] + (20); // addi r3, r1, 20
    /* 0x800BD2DC */ ctx.r[4] = ctx.r[1] + (44); // addi r4, r1, 44
    /* 0x800BD2E0 */ ctx.r[5] = 0x00000003u; // li r5, 3
    /* 0x800BD2E4 */ ctx.r[6] = 0x00000001u; // li r6, 1
    /* 0x800BD2E8 */ SetEm33Sce_800485DC(ctx, mem); // bl 0x800485DC <SetEm33Sce(Vec &, Vec &, unsigned long, unsigned long)>
    /* 0x800BD2EC */ goto loc_800BD37C; // b 0x800BD37C <sub_800BD37C>
loc_800BD2F0:;
    /* 0x800BD2F0 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BD2F4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BD2F8 */ if (ctx.eval_bc(12, 2)) goto loc_800BD37C; // bc 12, 2, 0x800BD37C
    /* 0x800BD2FC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29572)); // lwz r11, -29572(r13) [pEvent14]
    /* 0x800BD300 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BD304 */ if (ctx.eval_bc(12, 2)) goto loc_800BD324; // bc 12, 2, 0x800BD324
    /* 0x800BD308 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BD30C */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BD310 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BD314 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BD318 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BD31C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD320 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BD324:;
    /* 0x800BD324 */ ctx.r[30] = 0x00000000u; // li r30, 0
    /* 0x800BD328 */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800BD32C */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800BD330 */ mem.write_u32(ctx.r[13] + (-29572), ctx.r[30]); // stw r30, -29572(r13) [pEvent14]
    /* 0x800BD334 */ ctx.r[4] = 0x00000041u; // li r4, 65
    /* 0x800BD338 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BD33C */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800BD340 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD344 */ ctx.r[0] = 0x00000004u; // li r0, 4
    /* 0x800BD348 */ mem.write_u8(ctx.r[11] + (260), static_cast<uint8_t>(ctx.r[0])); // stb r0, 260(r11)
    /* 0x800BD34C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (336)); // lwz r9, 336(r11)
    /* 0x800BD350 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (328)); // lwz r0, 328(r11)
    /* 0x800BD354 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BD358 */ ctx.r[9] = ctx.r[9] | 0x20000000u; // oris r9, r9, 0x2000
    /* 0x800BD35C */ ctx.r[0] = ctx.r[0] | 0x0008u; // ori r0, r0, 0x0008
    /* 0x800BD360 */ mem.write_u32(ctx.r[11] + (336), ctx.r[9]); // stw r9, 336(r11)
    /* 0x800BD364 */ mem.write_u32(ctx.r[11] + (328), ctx.r[0]); // stw r0, 328(r11)
    /* 0x800BD368 */ mem.write_u8(ctx.r[10] + (261), static_cast<uint8_t>(ctx.r[30])); // stb r30, 261(r10)
    /* 0x800BD36C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD370 */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[30])); // stb r30, 262(r9)
    /* 0x800BD374 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD378 */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[30])); // stb r30, 263(r11)
loc_800BD37C:;
    /* 0x800BD37C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (68)); // lwz r0, 68(r1)
    /* 0x800BD380 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD384 */ ctx.lmw(mem, 30, ctx.r[1] + (56)); // lmw r30, 56(r1)
    /* 0x800BD388 */ ctx.r[1] = ctx.r[1] + (64); // addi r1, r1, 64
    /* 0x800BD38C */ return; // blr
}

// [0x800BD390] Ra07Init(void) (ra07.obj, 54 insns / 0xD8 bytes)
void Ra07Init_800BD390(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BD390 */ ctx.r[1] += (-56); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -56(r1)
    /* 0x800BD394 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BD398 */ ctx.stmw(mem, 30, ctx.r[1] + (48)); // stmw r30, 48(r1)
    /* 0x800BD39C */ mem.write_u32(ctx.r[1] + (60), ctx.r[0]); // stw r0, 60(r1)
    /* 0x800BD3A0 */ ctx.r[8] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r8, -29836(r13) [pG]
    /* 0x800BD3A4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BD3A8 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11908)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11908(r9) [0x8016D17C]
    /* 0x800BD3AC */ ctx.r[11] = ctx.r[1] + (16); // addi r11, r1, 16
    /* 0x800BD3B0 */ ctx.r[9] = mem.read_u32(ctx.r[8] + (272)); // lwz r9, 272(r8)
    /* 0x800BD3B4 */ ctx.r[10] = ctx.r[1] + (32); // addi r10, r1, 32
    /* 0x800BD3B8 */ ctx.r[5] = ctx.r[11]; // mr r5, r11
    /* 0x800BD3BC */ ctx.r[6] = ctx.r[10]; // mr r6, r10
    /* 0x800BD3C0 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (48)); // lwz r3, 48(r9)
    /* 0x800BD3C4 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (52)); // lwz r4, 52(r9)
    /* 0x800BD3C8 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BD3CC */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BD3D0 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800BD3D4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BD3D8 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BD3DC */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BD3E0 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800BD3E4 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800BD3E8 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BD3EC */ ctx.r[31] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // mr r31, r3
    /* 0x800BD3F0 */ if (ctx.eval_bc(12, 2)) goto loc_800BD454; // bc 12, 2, 0x800BD454
    /* 0x800BD3F4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD3F8 */ ctx.r[5] = 0x00000004u; // li r5, 4
    /* 0x800BD3FC */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800BD400 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BD404 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (56)); // lwz r4, 56(r9)
    /* 0x800BD408 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BD40C */ cObj00__MotSetObj00_800A7C54(ctx, mem); // bl 0x800A7C54 <cObj00::MotSetObj00(void *, unsigned long)>
    /* 0x800BD410 */ ctx.r[4] = 0x00000010u; // li r4, 16
    /* 0x800BD414 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BD418 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BD41C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BD420 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BD424 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BD428 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BD42C */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BD430 */ mem.write_u32(ctx.r[1] + (8), ctx.r[0]); // stw r0, 8(r1)
    /* 0x800BD434 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800BD438 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BD43C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BD440 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BD444 */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800BD448 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BD44C */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BD450 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800BD454:;
    /* 0x800BD454 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (60)); // lwz r0, 60(r1)
    /* 0x800BD458 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD45C */ ctx.lmw(mem, 30, ctx.r[1] + (48)); // lmw r30, 48(r1)
    /* 0x800BD460 */ ctx.r[1] = ctx.r[1] + (56); // addi r1, r1, 56
    /* 0x800BD464 */ return; // blr
}

// [0x800BD468] Ra07Main(void) (ra07.obj, 1 insns / 0x4 bytes)
void Ra07Main_800BD468(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BD468 */ return; // blr
}

// [0x800BD46C] Ra10Init(void) (ra10.obj, 58 insns / 0xE8 bytes)
void Ra10Init_800BD46C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BD46C */ ctx.r[1] += (-64); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -64(r1)
    /* 0x800BD470 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BD474 */ ctx.stmw(mem, 29, ctx.r[1] + (52)); // stmw r29, 52(r1)
    /* 0x800BD478 */ mem.write_u32(ctx.r[1] + (68), ctx.r[0]); // stw r0, 68(r1)
    /* 0x800BD47C */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BD480 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BD484 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11884)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11884(r9) [0x8016D194]
    /* 0x800BD488 */ ctx.r[11] = ctx.r[1] + (16); // addi r11, r1, 16
    /* 0x800BD48C */ ctx.r[9] = mem.read_u32(ctx.r[10] + (272)); // lwz r9, 272(r10)
    /* 0x800BD490 */ ctx.r[31] = 0x00000000u; // li r31, 0
    /* 0x800BD494 */ ctx.r[10] = ctx.r[1] + (32); // addi r10, r1, 32
    /* 0x800BD498 */ ctx.r[5] = ctx.r[11]; // mr r5, r11
    /* 0x800BD49C */ ctx.r[3] = mem.read_u32(ctx.r[9] + (68)); // lwz r3, 68(r9)
    /* 0x800BD4A0 */ ctx.r[6] = ctx.r[10]; // mr r6, r10
    /* 0x800BD4A4 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (72)); // lwz r4, 72(r9)
    /* 0x800BD4A8 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BD4AC */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BD4B0 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800BD4B4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BD4B8 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BD4BC */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BD4C0 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800BD4C4 */ mem.write_u32(ctx.r[13] + (-29568), ctx.r[31]); // stw r31, -29568(r13) [pEvent23]
    /* 0x800BD4C8 */ mem.write_u32(ctx.r[13] + (-29564), ctx.r[31]); // stw r31, -29564(r13) [pEvent24]
    /* 0x800BD4CC */ mem.write_u32(ctx.r[13] + (-29560), ctx.r[31]); // stw r31, -29560(r13) [pEvent25]
    /* 0x800BD4D0 */ mem.write_u32(ctx.r[13] + (-29556), ctx.r[31]); // stw r31, -29556(r13) [pEvent26]
    /* 0x800BD4D4 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800BD4D8 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BD4DC */ ctx.r[29] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[29]), 0); // mr r29, r3
    /* 0x800BD4E0 */ if (ctx.eval_bc(12, 2)) goto loc_800BD540; // bc 12, 2, 0x800BD540
    /* 0x800BD4E4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD4E8 */ ctx.r[5] = 0x00000004u; // li r5, 4
    /* 0x800BD4EC */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800BD4F0 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BD4F4 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (76)); // lwz r4, 76(r9)
    /* 0x800BD4F8 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BD4FC */ cObj00__MotSetObj00_800A7C54(ctx, mem); // bl 0x800A7C54 <cObj00::MotSetObj00(void *, unsigned long)>
    /* 0x800BD500 */ ctx.r[4] = 0x00000009u; // li r4, 9
    /* 0x800BD504 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BD508 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BD50C */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BD510 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BD514 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BD518 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BD51C */ mem.write_u32(ctx.r[1] + (8), ctx.r[31]); // stw r31, 8(r1)
    /* 0x800BD520 */ ctx.r[3] = ctx.r[29]; // mr r3, r29
    /* 0x800BD524 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BD528 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BD52C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BD530 */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800BD534 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BD538 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BD53C */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800BD540:;
    /* 0x800BD540 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (68)); // lwz r0, 68(r1)
    /* 0x800BD544 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD548 */ ctx.lmw(mem, 29, ctx.r[1] + (52)); // lmw r29, 52(r1)
    /* 0x800BD54C */ ctx.r[1] = ctx.r[1] + (64); // addi r1, r1, 64
    /* 0x800BD550 */ return; // blr
}

// [0x800BD554] Ra10Main(void) (ra10.obj, 398 insns / 0x638 bytes)
void Ra10Main_800BD554(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BD554 */ ctx.r[1] += (-112); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -112(r1)
    /* 0x800BD558 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BD55C */ ctx.stmw(mem, 29, ctx.r[1] + (100)); // stmw r29, 100(r1)
    /* 0x800BD560 */ mem.write_u32(ctx.r[1] + (116), ctx.r[0]); // stw r0, 116(r1)
    /* 0x800BD564 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD568 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (29012)); // lwz r9, 29012(r11)
    /* 0x800BD56C */ ctx.r[31] = ctx.r[9] & 0x0100u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // andi. r31, r9, 0x0100
    /* 0x800BD570 */ if (ctx.eval_bc(4, 2)) goto loc_800BD69C; // bc 4, 2, 0x800BD69C
    /* 0x800BD574 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (340)); // lwz r0, 340(r11)
    /* 0x800BD578 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BD57C */ if (ctx.eval_bc(4, 0)) goto loc_800BD69C; // bc 4, 0, 0x800BD69C
    /* 0x800BD580 */ ctx.r[0] = ctx.r[9] | 0x0100u; // ori r0, r9, 0x0100
    /* 0x800BD584 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BD588 */ mem.write_u32(ctx.r[11] + (29012), ctx.r[0]); // stw r0, 29012(r11)
    /* 0x800BD58C */ ctx.r[29] = ctx.r[13] + (-29545); // addi r29, r13, -29545 -> sda1_0x8026E877
    /* 0x800BD590 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BD594 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BD598 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD59C */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BD5A0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BD5A4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BD5A8 */ mem.write_u32(ctx.r[13] + (-29568), ctx.r[0]); // stw r0, -29568(r13) [pEvent23]
    /* 0x800BD5AC */ ctx.r[4] = mem.read_u32(ctx.r[9] + (44)); // lwz r4, 44(r9)
    /* 0x800BD5B0 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BD5B4 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BD5B8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BD5BC */ ctx.r[11] = ctx.r[1] + (16); // addi r11, r1, 16
    /* 0x800BD5C0 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11880)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11880(r9) [0x8016D198]
    /* 0x800BD5C4 */ ctx.r[10] = ctx.r[1] + (32); // addi r10, r1, 32
    /* 0x800BD5C8 */ ctx.r[8] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r8, -29836(r13) [pG]
    /* 0x800BD5CC */ ctx.r[5] = ctx.r[11]; // mr r5, r11
    /* 0x800BD5D0 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BD5D4 */ ctx.r[6] = ctx.r[10]; // mr r6, r10
    /* 0x800BD5D8 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800BD5DC */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BD5E0 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BD5E4 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BD5E8 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800BD5EC */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800BD5F0 */ ctx.r[9] = mem.read_u32(ctx.r[8] + (272)); // lwz r9, 272(r8)
    /* 0x800BD5F4 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (80)); // lwz r3, 80(r9)
    /* 0x800BD5F8 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BD5FC */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BD600 */ mem.write_u32(ctx.r[13] + (-29552), ctx.r[3]); // stw r3, -29552(r13) [Ra10_pSat]
    /* 0x800BD604 */ EspPullCoreKind_80084BA0(ctx, mem); // bl 0x80084BA0 <EspPullCoreKind(void)>
    /* 0x800BD608 */ mem.write_u32(ctx.r[13] + (-29548), ctx.r[3]); // stw r3, -29548(r13) [eff_barrier]
    /* 0x800BD60C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BD610 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BD614 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BD618 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BD61C */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BD620 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BD624 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BD628 */ ctx.r[9] = mem.read_u8(ctx.r[29] + (0)); // lbz r9, 0(r29)
    /* 0x800BD62C */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BD630 */ mem.write_u32(ctx.r[1] + (8), ctx.r[31]); // stw r31, 8(r1)
    /* 0x800BD634 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BD638 */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800BD63C */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BD640 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BD644 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BD648 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800BD64C */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800BD650 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BD654 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BD658 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BD65C */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BD660 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BD664 */ ctx.r[9] = mem.read_u8(ctx.r[29] + (0)); // lbz r9, 0(r29)
    /* 0x800BD668 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BD66C */ mem.write_u32(ctx.r[1] + (8), ctx.r[31]); // stw r31, 8(r1)
    /* 0x800BD670 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BD674 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BD678 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BD67C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BD680 */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800BD684 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BD688 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800BD68C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD690 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BD694 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BD698 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
loc_800BD69C:;
    /* 0x800BD69C */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29568)); // lwz r3, -29568(r13) [pEvent23]
    /* 0x800BD6A0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BD6A4 */ if (ctx.eval_bc(12, 2)) goto loc_800BD77C; // bc 12, 2, 0x800BD77C
    /* 0x800BD6A8 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BD6AC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BD6B0 */ if (ctx.eval_bc(12, 2)) goto loc_800BDB78; // bc 12, 2, 0x800BDB78
    /* 0x800BD6B4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29568)); // lwz r11, -29568(r13) [pEvent23]
    /* 0x800BD6B8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BD6BC */ if (ctx.eval_bc(12, 2)) goto loc_800BD6DC; // bc 12, 2, 0x800BD6DC
    /* 0x800BD6C0 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BD6C4 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BD6C8 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BD6CC */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BD6D0 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BD6D4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD6D8 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BD6DC:;
    /* 0x800BD6DC */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BD6E0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BD6E4 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-11880)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11880(r9) [0x8016D198]
    /* 0x800BD6E8 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BD6EC */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-11876)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11876(r11) [0x8016D19C]
    /* 0x800BD6F0 */ ctx.r[8] = ctx.r[1] + (16); // addi r8, r1, 16
    /* 0x800BD6F4 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800BD6F8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BD6FC */ ctx.f[12] = mem.read_f32(ctx.r[10] + (-11872)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -11872(r10) [0x8016D1A0]
    /* 0x800BD700 */ ctx.r[7] = ctx.r[1] + (48); // addi r7, r1, 48
    /* 0x800BD704 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800BD708 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BD70C */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r8)
    /* 0x800BD710 */ ctx.r[10] = ctx.r[1] + (64); // addi r10, r1, 64
    /* 0x800BD714 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11868)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11868(r9) [0x8016D1A4]
    /* 0x800BD718 */ ctx.r[6] = ctx.r[1] + (80); // addi r6, r1, 80
    /* 0x800BD71C */ mem.write_f32(ctx.r[1] + (48), static_cast<float>(ctx.f[13])); // stfs f13, 48(r1)
    /* 0x800BD720 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BD724 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800BD728 */ ctx.r[3] = ctx.r[10]; // mr r3, r10
    /* 0x800BD72C */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r7)
    /* 0x800BD730 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BD734 */ mem.write_u32(ctx.r[13] + (-29568), ctx.r[0]); // stw r0, -29568(r13) [pEvent23]
    /* 0x800BD738 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (16)); // lwz r9, 16(r1)
    /* 0x800BD73C */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BD740 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BD744 */ mem.write_u32(ctx.r[1] + (64), ctx.r[9]); // stw r9, 64(r1)
    /* 0x800BD748 */ mem.write_u32(ctx.r[10] + (4), ctx.r[0]); // stw r0, 4(r10)
    /* 0x800BD74C */ mem.write_u32(ctx.r[10] + (8), ctx.r[11]); // stw r11, 8(r10)
    /* 0x800BD750 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (48)); // lwz r9, 48(r1)
    /* 0x800BD754 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BD758 */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BD75C */ mem.write_u32(ctx.r[1] + (80), ctx.r[9]); // stw r9, 80(r1)
    /* 0x800BD760 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BD764 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BD768 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BD76C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BD770 */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800BD774 */ ctx.r[5] = 0x00000002u; // li r5, 2
    /* 0x800BD778 */ goto loc_800BD9F8; // b 0x800BD9F8 <sub_800BD9F8>
loc_800BD77C:;
    /* 0x800BD77C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD780 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BD784 */ ctx.r[0] = ctx.r[11] & 0x0080u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andi. r0, r11, 0x0080
    /* 0x800BD788 */ if (ctx.eval_bc(4, 2)) goto loc_800BD7DC; // bc 4, 2, 0x800BD7DC
    /* 0x800BD78C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BD790 */ ctx.r[10] = ctx.r[0] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r0, 0x4000
    /* 0x800BD794 */ if (ctx.eval_bc(12, 2)) goto loc_800BD7DC; // bc 12, 2, 0x800BD7DC
    /* 0x800BD798 */ ctx.r[0] = ctx.r[11] | 0x0080u; // ori r0, r11, 0x0080
    /* 0x800BD79C */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BD7A0 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BD7A4 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BD7A8 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BD7AC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD7B0 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BD7B4 */ mem.write_u32(ctx.r[13] + (-29564), ctx.r[0]); // stw r0, -29564(r13) [pEvent24]
    /* 0x800BD7B8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BD7BC */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BD7C0 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (48)); // lwz r4, 48(r9)
    /* 0x800BD7C4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BD7C8 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BD7CC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD7D0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BD7D4 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BD7D8 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
loc_800BD7DC:;
    /* 0x800BD7DC */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29564)); // lwz r3, -29564(r13) [pEvent24]
    /* 0x800BD7E0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BD7E4 */ if (ctx.eval_bc(12, 2)) goto loc_800BD8B0; // bc 12, 2, 0x800BD8B0
    /* 0x800BD7E8 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BD7EC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BD7F0 */ if (ctx.eval_bc(12, 2)) goto loc_800BDB78; // bc 12, 2, 0x800BDB78
    /* 0x800BD7F4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29564)); // lwz r11, -29564(r13) [pEvent24]
    /* 0x800BD7F8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BD7FC */ if (ctx.eval_bc(12, 2)) goto loc_800BD81C; // bc 12, 2, 0x800BD81C
    /* 0x800BD800 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BD804 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BD808 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BD80C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BD810 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BD814 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD818 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BD81C:;
    /* 0x800BD81C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BD820 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BD824 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-11880)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11880(r9) [0x8016D198]
    /* 0x800BD828 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BD82C */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-11876)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11876(r11) [0x8016D19C]
    /* 0x800BD830 */ ctx.r[8] = ctx.r[1] + (16); // addi r8, r1, 16
    /* 0x800BD834 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800BD838 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BD83C */ ctx.f[12] = mem.read_f32(ctx.r[10] + (-11872)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -11872(r10) [0x8016D1A0]
    /* 0x800BD840 */ ctx.r[7] = ctx.r[1] + (32); // addi r7, r1, 32
    /* 0x800BD844 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800BD848 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BD84C */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r8)
    /* 0x800BD850 */ ctx.r[10] = ctx.r[1] + (48); // addi r10, r1, 48
    /* 0x800BD854 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11868)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11868(r9) [0x8016D1A4]
    /* 0x800BD858 */ ctx.r[6] = ctx.r[1] + (64); // addi r6, r1, 64
    /* 0x800BD85C */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[13])); // stfs f13, 32(r1)
    /* 0x800BD860 */ ctx.r[3] = ctx.r[10]; // mr r3, r10
    /* 0x800BD864 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800BD868 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BD86C */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r7)
    /* 0x800BD870 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BD874 */ mem.write_u32(ctx.r[13] + (-29564), ctx.r[0]); // stw r0, -29564(r13) [pEvent24]
    /* 0x800BD878 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (16)); // lwz r9, 16(r1)
    /* 0x800BD87C */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BD880 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BD884 */ mem.write_u32(ctx.r[1] + (48), ctx.r[9]); // stw r9, 48(r1)
    /* 0x800BD888 */ mem.write_u32(ctx.r[10] + (4), ctx.r[0]); // stw r0, 4(r10)
    /* 0x800BD88C */ mem.write_u32(ctx.r[10] + (8), ctx.r[11]); // stw r11, 8(r10)
    /* 0x800BD890 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (32)); // lwz r9, 32(r1)
    /* 0x800BD894 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BD898 */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BD89C */ mem.write_u32(ctx.r[1] + (64), ctx.r[9]); // stw r9, 64(r1)
    /* 0x800BD8A0 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BD8A4 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BD8A8 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BD8AC */ goto loc_800BDB78; // b 0x800BDB78 <sub_800BDB78>
loc_800BD8B0:;
    /* 0x800BD8B0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD8B4 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BD8B8 */ ctx.r[0] = ctx.r[11] & 0x0040u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andi. r0, r11, 0x0040
    /* 0x800BD8BC */ if (ctx.eval_bc(4, 2)) goto loc_800BD91C; // bc 4, 2, 0x800BD91C
    /* 0x800BD8C0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BD8C4 */ ctx.r[10] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r0, 0x2000
    /* 0x800BD8C8 */ if (ctx.eval_bc(12, 2)) goto loc_800BD91C; // bc 12, 2, 0x800BD91C
    /* 0x800BD8CC */ ctx.r[0] = ctx.r[11] | 0x0040u; // ori r0, r11, 0x0040
    /* 0x800BD8D0 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BD8D4 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BD8D8 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BD8DC */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BD8E0 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BD8E4 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BD8E8 */ mem.write_u32(ctx.r[13] + (-29560), ctx.r[0]); // stw r0, -29560(r13) [pEvent25]
    /* 0x800BD8EC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BD8F0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BD8F4 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (52)); // lwz r4, 52(r9)
    /* 0x800BD8F8 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BD8FC */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BD900 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BD904 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BD908 */ ctx.r[4] = 0x00000014u; // li r4, 20
    /* 0x800BD90C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BD910 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BD914 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
    /* 0x800BD918 */ Snd_str_fadeout_800CD394(ctx, mem); // bl 0x800CD394 <Snd_str_fadeout(long, long)>
loc_800BD91C:;
    /* 0x800BD91C */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29560)); // lwz r3, -29560(r13) [pEvent25]
    /* 0x800BD920 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BD924 */ if (ctx.eval_bc(12, 2)) goto loc_800BDA08; // bc 12, 2, 0x800BDA08
    /* 0x800BD928 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BD92C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BD930 */ if (ctx.eval_bc(12, 2)) goto loc_800BDB78; // bc 12, 2, 0x800BDB78
    /* 0x800BD934 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29560)); // lwz r11, -29560(r13) [pEvent25]
    /* 0x800BD938 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BD93C */ if (ctx.eval_bc(12, 2)) goto loc_800BD95C; // bc 12, 2, 0x800BD95C
    /* 0x800BD940 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BD944 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BD948 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BD94C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BD950 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BD954 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BD958 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BD95C:;
    /* 0x800BD95C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BD960 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BD964 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-11880)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11880(r9) [0x8016D198]
    /* 0x800BD968 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BD96C */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-11876)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11876(r11) [0x8016D19C]
    /* 0x800BD970 */ ctx.r[8] = ctx.r[1] + (16); // addi r8, r1, 16
    /* 0x800BD974 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800BD978 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BD97C */ ctx.f[12] = mem.read_f32(ctx.r[10] + (-11872)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -11872(r10) [0x8016D1A0]
    /* 0x800BD980 */ ctx.r[7] = ctx.r[1] + (32); // addi r7, r1, 32
    /* 0x800BD984 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800BD988 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BD98C */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r8)
    /* 0x800BD990 */ ctx.r[10] = ctx.r[1] + (48); // addi r10, r1, 48
    /* 0x800BD994 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11868)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11868(r9) [0x8016D1A4]
    /* 0x800BD998 */ ctx.r[6] = ctx.r[1] + (64); // addi r6, r1, 64
    /* 0x800BD99C */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[13])); // stfs f13, 32(r1)
    /* 0x800BD9A0 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BD9A4 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800BD9A8 */ ctx.r[3] = ctx.r[10]; // mr r3, r10
    /* 0x800BD9AC */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r7)
    /* 0x800BD9B0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BD9B4 */ mem.write_u32(ctx.r[13] + (-29560), ctx.r[0]); // stw r0, -29560(r13) [pEvent25]
    /* 0x800BD9B8 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (16)); // lwz r9, 16(r1)
    /* 0x800BD9BC */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BD9C0 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BD9C4 */ mem.write_u32(ctx.r[1] + (48), ctx.r[9]); // stw r9, 48(r1)
    /* 0x800BD9C8 */ mem.write_u32(ctx.r[10] + (4), ctx.r[0]); // stw r0, 4(r10)
    /* 0x800BD9CC */ mem.write_u32(ctx.r[10] + (8), ctx.r[11]); // stw r11, 8(r10)
    /* 0x800BD9D0 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (32)); // lwz r9, 32(r1)
    /* 0x800BD9D4 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BD9D8 */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BD9DC */ mem.write_u32(ctx.r[1] + (64), ctx.r[9]); // stw r9, 64(r1)
    /* 0x800BD9E0 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BD9E4 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BD9E8 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BD9EC */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BD9F0 */ ctx.r[4] = 0x00000021u; // li r4, 33
    /* 0x800BD9F4 */ ctx.r[5] = 0x00000003u; // li r5, 3
loc_800BD9F8:;
    /* 0x800BD9F8 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BD9FC */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BDA00 */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
    /* 0x800BDA04 */ goto loc_800BDB78; // b 0x800BDB78 <sub_800BDB78>
loc_800BDA08:;
    /* 0x800BDA08 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BDA0C */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BDA10 */ ctx.r[0] = ctx.r[11] & 0x0020u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andi. r0, r11, 0x0020
    /* 0x800BDA14 */ if (ctx.eval_bc(4, 2)) goto loc_800BDA74; // bc 4, 2, 0x800BDA74
    /* 0x800BDA18 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BDA1C */ ctx.r[10] = ctx.r[0] & 0x10000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r0, 0x1000
    /* 0x800BDA20 */ if (ctx.eval_bc(12, 2)) goto loc_800BDA74; // bc 12, 2, 0x800BDA74
    /* 0x800BDA24 */ ctx.r[0] = ctx.r[11] | 0x0020u; // ori r0, r11, 0x0020
    /* 0x800BDA28 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BDA2C */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BDA30 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BDA34 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BDA38 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BDA3C */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BDA40 */ mem.write_u32(ctx.r[13] + (-29556), ctx.r[0]); // stw r0, -29556(r13) [pEvent26]
    /* 0x800BDA44 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BDA48 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BDA4C */ ctx.r[4] = mem.read_u32(ctx.r[9] + (56)); // lwz r4, 56(r9)
    /* 0x800BDA50 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BDA54 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BDA58 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29552)); // lwz r3, -29552(r13) [Ra10_pSat]
    /* 0x800BDA5C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BDA60 */ if (ctx.eval_bc(12, 2)) goto loc_800BDA68; // bc 12, 2, 0x800BDA68
    /* 0x800BDA64 */ ScrAtDelete_8000646C(ctx, mem); // bl 0x8000646C <ScrAtDelete(tagSCR_AT *)>
loc_800BDA68:;
    /* 0x800BDA68 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BDA6C */ ctx.r[4] = 0x000000C8u; // li r4, 200
    /* 0x800BDA70 */ Snd_str_fadeout_800CD394(ctx, mem); // bl 0x800CD394 <Snd_str_fadeout(long, long)>
loc_800BDA74:;
    /* 0x800BDA74 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29556)); // lwz r3, -29556(r13) [pEvent26]
    /* 0x800BDA78 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BDA7C */ if (ctx.eval_bc(12, 2)) goto loc_800BDB78; // bc 12, 2, 0x800BDB78
    /* 0x800BDA80 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BDA84 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BDA88 */ if (ctx.eval_bc(12, 2)) goto loc_800BDB78; // bc 12, 2, 0x800BDB78
    /* 0x800BDA8C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29556)); // lwz r11, -29556(r13) [pEvent26]
    /* 0x800BDA90 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BDA94 */ if (ctx.eval_bc(12, 2)) goto loc_800BDAB4; // bc 12, 2, 0x800BDAB4
    /* 0x800BDA98 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BDA9C */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BDAA0 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BDAA4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BDAA8 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BDAAC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BDAB0 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BDAB4:;
    /* 0x800BDAB4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BDAB8 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BDABC */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-11880)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11880(r9) [0x8016D198]
    /* 0x800BDAC0 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BDAC4 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-11876)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11876(r11) [0x8016D19C]
    /* 0x800BDAC8 */ ctx.r[8] = ctx.r[1] + (16); // addi r8, r1, 16
    /* 0x800BDACC */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800BDAD0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BDAD4 */ ctx.f[12] = mem.read_f32(ctx.r[10] + (-11872)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -11872(r10) [0x8016D1A0]
    /* 0x800BDAD8 */ ctx.r[7] = ctx.r[1] + (32); // addi r7, r1, 32
    /* 0x800BDADC */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800BDAE0 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BDAE4 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r8)
    /* 0x800BDAE8 */ ctx.r[10] = ctx.r[1] + (48); // addi r10, r1, 48
    /* 0x800BDAEC */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11868)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11868(r9) [0x8016D1A4]
    /* 0x800BDAF0 */ ctx.r[6] = ctx.r[1] + (64); // addi r6, r1, 64
    /* 0x800BDAF4 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[13])); // stfs f13, 32(r1)
    /* 0x800BDAF8 */ ctx.r[3] = ctx.r[10]; // mr r3, r10
    /* 0x800BDAFC */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800BDB00 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BDB04 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r7)
    /* 0x800BDB08 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BDB0C */ mem.write_u32(ctx.r[13] + (-29556), ctx.r[0]); // stw r0, -29556(r13) [pEvent26]
    /* 0x800BDB10 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (16)); // lwz r9, 16(r1)
    /* 0x800BDB14 */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BDB18 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BDB1C */ mem.write_u32(ctx.r[1] + (48), ctx.r[9]); // stw r9, 48(r1)
    /* 0x800BDB20 */ mem.write_u32(ctx.r[10] + (4), ctx.r[0]); // stw r0, 4(r10)
    /* 0x800BDB24 */ mem.write_u32(ctx.r[10] + (8), ctx.r[11]); // stw r11, 8(r10)
    /* 0x800BDB28 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (32)); // lwz r9, 32(r1)
    /* 0x800BDB2C */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BDB30 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BDB34 */ mem.write_u32(ctx.r[1] + (64), ctx.r[9]); // stw r9, 64(r1)
    /* 0x800BDB38 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BDB3C */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BDB40 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BDB44 */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800BDB48 */ ctx.r[4] = 0x00000046u; // li r4, 70
    /* 0x800BDB4C */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800BDB50 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BDB54 */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800BDB58 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BDB5C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BDB60 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BDB64 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (332)); // lwz r0, 332(r9)
    /* 0x800BDB68 */ ctx.r[0] = ctx.r[0] | 0x10000000u; // oris r0, r0, 0x1000
    /* 0x800BDB6C */ mem.write_u32(ctx.r[9] + (332), ctx.r[0]); // stw r0, 332(r9)
    /* 0x800BDB70 */ ctx.r[4] = mem.read_u8(ctx.r[13] + (-29545)); // lbz r4, -29545(r13) [sda1_0x8026E877]
    /* 0x800BDB74 */ EspgenDelete_8008E8B8(ctx, mem); // bl 0x8008E8B8 <EspgenDelete(unsigned short, unsigned char, void *)>
loc_800BDB78:;
    /* 0x800BDB78 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (116)); // lwz r0, 116(r1)
    /* 0x800BDB7C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BDB80 */ ctx.lmw(mem, 29, ctx.r[1] + (100)); // lmw r29, 100(r1)
    /* 0x800BDB84 */ ctx.r[1] = ctx.r[1] + (112); // addi r1, r1, 112
    /* 0x800BDB88 */ return; // blr
}

// [0x800BDB8C] Ra11Init(void) (ra11.obj, 119 insns / 0x1DC bytes)
void Ra11Init_800BDB8C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BDB8C */ ctx.r[1] += (-128); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -128(r1)
    /* 0x800BDB90 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BDB94 */ mem.write_f64(ctx.r[1] + (120), ctx.f[31]); // stfd f31, 120(r1)
    /* 0x800BDB98 */ ctx.stmw(mem, 29, ctx.r[1] + (108)); // stmw r29, 108(r1)
    /* 0x800BDB9C */ mem.write_u32(ctx.r[1] + (132), ctx.r[0]); // stw r0, 132(r1)
    /* 0x800BDBA0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BDBA4 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BDBA8 */ ctx.f[31] = mem.read_f32(ctx.r[9] + (-11844)); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // lfs f31, -11844(r9) [0x8016D1BC]
    /* 0x800BDBAC */ ctx.r[30] = ctx.r[1] + (8); // addi r30, r1, 8
    /* 0x800BDBB0 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-11840)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11840(r11) [0x8016D1C0]
    /* 0x800BDBB4 */ ctx.r[29] = ctx.r[1] + (24); // addi r29, r1, 24
    /* 0x800BDBB8 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r1)
    /* 0x800BDBBC */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BDBC0 */ mem.write_f32(ctx.r[30] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r30)
    /* 0x800BDBC4 */ ctx.r[5] = ctx.r[30]; // mr r5, r30
    /* 0x800BDBC8 */ mem.write_f32(ctx.r[30] + (4), static_cast<float>(ctx.f[31])); // stfs f31, 4(r30)
    /* 0x800BDBCC */ ctx.r[6] = ctx.r[29]; // mr r6, r29
    /* 0x800BDBD0 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[31])); // stfs f31, 24(r1)
    /* 0x800BDBD4 */ mem.write_f32(ctx.r[29] + (4), static_cast<float>(ctx.f[31])); // stfs f31, 4(r29)
    /* 0x800BDBD8 */ mem.write_f32(ctx.r[29] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r29)
    /* 0x800BDBDC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BDBE0 */ mem.write_u32(ctx.r[13] + (-29512), ctx.r[0]); // stw r0, -29512(r13) [pEvent29]
    /* 0x800BDBE4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BDBE8 */ mem.write_u32(ctx.r[13] + (-29520), ctx.r[0]); // stw r0, -29520(r13) [pEvent27]
    /* 0x800BDBEC */ ctx.r[3] = mem.read_u32(ctx.r[9] + (52)); // lwz r3, 52(r9)
    /* 0x800BDBF0 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (56)); // lwz r4, 56(r9)
    /* 0x800BDBF4 */ mem.write_u32(ctx.r[13] + (-29516), ctx.r[0]); // stw r0, -29516(r13) [pEvent28]
    /* 0x800BDBF8 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BDBFC */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BDC00 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BDC04 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BDC08 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BDC0C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11836)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11836(r9) [0x8016D1C4 /* "GCP" */]
    /* 0x800BDC10 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BDC14 */ mem.write_u32(ctx.r[13] + (-29540), ctx.r[3]); // stw r3, -29540(r13) [R11a_pStp]
    /* 0x800BDC18 */ ctx.r[5] = ctx.r[30]; // mr r5, r30
    /* 0x800BDC1C */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BDC20 */ ctx.r[6] = ctx.r[29]; // mr r6, r29
    /* 0x800BDC24 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BDC28 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (76)); // lwz r3, 76(r9)
    /* 0x800BDC2C */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BDC30 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BDC34 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BDC38 */ ctx.r[4] = 0x00000100u; // li r4, 256
    /* 0x800BDC3C */ mem.write_u32(ctx.r[13] + (-29532), ctx.r[3]); // stw r3, -29532(r13) [R11a_pSat]
    /* 0x800BDC40 */ ctx.r[5] = ctx.r[30]; // mr r5, r30
    /* 0x800BDC44 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BDC48 */ ctx.r[6] = ctx.r[29]; // mr r6, r29
    /* 0x800BDC4C */ ctx.r[3] = mem.read_u32(ctx.r[9] + (76)); // lwz r3, 76(r9)
    /* 0x800BDC50 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BDC54 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BDC58 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BDC5C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BDC60 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11832)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11832(r9) [0x8016D1C8]
    /* 0x800BDC64 */ ctx.r[6] = ctx.r[29]; // mr r6, r29
    /* 0x800BDC68 */ mem.write_u32(ctx.r[13] + (-29536), ctx.r[3]); // stw r3, -29536(r13) [R11a_pEat]
    /* 0x800BDC6C */ ctx.r[5] = ctx.r[30]; // mr r5, r30
    /* 0x800BDC70 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[0])); // stfs f0, 12(r1)
    /* 0x800BDC74 */ ctx.r[4] = 0x00000200u; // li r4, 512
    /* 0x800BDC78 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BDC7C */ ctx.r[3] = mem.read_u32(ctx.r[9] + (76)); // lwz r3, 76(r9)
    /* 0x800BDC80 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BDC84 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BDC88 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29540)); // lwz r9, -29540(r13) [R11a_pStp]
    /* 0x800BDC8C */ ctx.r[8] = 0x00000004u; // li r8, 4
    /* 0x800BDC90 */ mem.write_u32(ctx.r[13] + (-29524), ctx.r[3]); // stw r3, -29524(r13) [R11a_pCam]
    /* 0x800BDC94 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800BDC98 */ ctx.r[6] = mem.read_u32(ctx.r[9] + (304)); // lwz r6, 304(r9)
    /* 0x800BDC9C */ ctx.r[3] = ctx.r[9] + (312); // addi r3, r9, 312
    /* 0x800BDCA0 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BDCA4 */ ctx.r[7] = ctx.r[6] + (32); // addi r7, r6, 32
    /* 0x800BDCA8 */ ctx.r[6] = ctx.r[6] + (20); // addi r6, r6, 20
    /* 0x800BDCAC */ LightInfoInit2_8009AFDC(ctx, mem); // bl 0x8009AFDC <LightInfoInit2(tagLIGHT_INFO *, unsigned char, short, Vec *, Vec *, unsigned char)>
    /* 0x800BDCB0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BDCB4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BDCB8 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29540)); // lwz r10, -29540(r13) [R11a_pStp]
    /* 0x800BDCBC */ ctx.r[8] = ctx.r[1] + (40); // addi r8, r1, 40
    /* 0x800BDCC0 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-11828)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11828(r11) [0x8016D1CC /* "A " */]
    /* 0x800BDCC4 */ ctx.r[6] = ctx.r[1] + (56); // addi r6, r1, 56
    /* 0x800BDCC8 */ ctx.f[11] = mem.read_f32(ctx.r[9] + (-11824)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -11824(r9) [0x8016D1D0]
    /* 0x800BDCCC */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BDCD0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BDCD4 */ mem.write_f32(ctx.r[10] + (224), static_cast<float>(ctx.f[0])); // stfs f0, 224(r10)
    /* 0x800BDCD8 */ mem.write_f32(ctx.r[10] + (216), static_cast<float>(ctx.f[0])); // stfs f0, 216(r10)
    /* 0x800BDCDC */ ctx.r[7] = ctx.r[1] + (72); // addi r7, r1, 72
    /* 0x800BDCE0 */ mem.write_f32(ctx.r[10] + (220), static_cast<float>(ctx.f[0])); // stfs f0, 220(r10)
    /* 0x800BDCE4 */ ctx.r[3] = ctx.r[7]; // mr r3, r7
    /* 0x800BDCE8 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (-11820)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11820(r11) [0x8016D1D4]
    /* 0x800BDCEC */ ctx.r[10] = ctx.r[1] + (88); // addi r10, r1, 88
    /* 0x800BDCF0 */ ctx.f[12] = mem.read_f32(ctx.r[9] + (-11816)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -11816(r9) [0x8016D1D8]
    /* 0x800BDCF4 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BDCF8 */ mem.write_f32(ctx.r[1] + (40), static_cast<float>(ctx.f[11])); // stfs f11, 40(r1)
    /* 0x800BDCFC */ ctx.r[4] = ctx.r[10]; // mr r4, r10
    /* 0x800BDD00 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r8)
    /* 0x800BDD04 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BDD08 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r8)
    /* 0x800BDD0C */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-11812)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11812(r11) [0x8016D1DC]
    /* 0x800BDD10 */ mem.write_f32(ctx.r[1] + (56), static_cast<float>(ctx.f[31])); // stfs f31, 56(r1)
    /* 0x800BDD14 */ mem.write_f32(ctx.r[6] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r6)
    /* 0x800BDD18 */ mem.write_f32(ctx.r[6] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r6)
    /* 0x800BDD1C */ ctx.r[9] = mem.read_u32(ctx.r[1] + (40)); // lwz r9, 40(r1)
    /* 0x800BDD20 */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BDD24 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BDD28 */ mem.write_u32(ctx.r[1] + (72), ctx.r[9]); // stw r9, 72(r1)
    /* 0x800BDD2C */ mem.write_u32(ctx.r[7] + (4), ctx.r[0]); // stw r0, 4(r7)
    /* 0x800BDD30 */ mem.write_u32(ctx.r[7] + (8), ctx.r[11]); // stw r11, 8(r7)
    /* 0x800BDD34 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (56)); // lwz r9, 56(r1)
    /* 0x800BDD38 */ ctx.r[11] = mem.read_u32(ctx.r[6] + (8)); // lwz r11, 8(r6)
    /* 0x800BDD3C */ ctx.r[0] = mem.read_u32(ctx.r[6] + (4)); // lwz r0, 4(r6)
    /* 0x800BDD40 */ mem.write_u32(ctx.r[1] + (88), ctx.r[9]); // stw r9, 88(r1)
    /* 0x800BDD44 */ mem.write_u32(ctx.r[10] + (4), ctx.r[0]); // stw r0, 4(r10)
    /* 0x800BDD48 */ mem.write_u32(ctx.r[10] + (8), ctx.r[11]); // stw r11, 8(r10)
    /* 0x800BDD4C */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BDD50 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (132)); // lwz r0, 132(r1)
    /* 0x800BDD54 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BDD58 */ ctx.lmw(mem, 29, ctx.r[1] + (108)); // lmw r29, 108(r1)
    /* 0x800BDD5C */ ctx.f[31] = mem.read_f64(ctx.r[1] + (120)); // lfd f31, 120(r1)
    /* 0x800BDD60 */ ctx.r[1] = ctx.r[1] + (128); // addi r1, r1, 128
    /* 0x800BDD64 */ return; // blr
}

// [0x800BDD68] Ra11Main(void) (ra11.obj, 471 insns / 0x75C bytes)
void Ra11Main_800BDD68(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BDD68 */ ctx.r[1] += (-136); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -136(r1)
    /* 0x800BDD6C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BDD70 */ ctx.stmw(mem, 29, ctx.r[1] + (124)); // stmw r29, 124(r1)
    /* 0x800BDD74 */ mem.write_u32(ctx.r[1] + (140), ctx.r[0]); // stw r0, 140(r1)
    /* 0x800BDD78 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BDD7C */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BDD80 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11808)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11808(r9) [0x8016D1E0]
    /* 0x800BDD84 */ ctx.r[11] = ctx.r[1] + (8); // addi r11, r1, 8
    /* 0x800BDD88 */ ctx.r[9] = ctx.r[1] + (24); // addi r9, r1, 24
    /* 0x800BDD8C */ ctx.r[29] = ctx.r[11]; // mr r29, r11
    /* 0x800BDD90 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r1)
    /* 0x800BDD94 */ ctx.r[30] = ctx.r[9]; // mr r30, r9
    /* 0x800BDD98 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800BDD9C */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BDDA0 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[0])); // stfs f0, 24(r1)
    /* 0x800BDDA4 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
    /* 0x800BDDA8 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r9)
    /* 0x800BDDAC */ ctx.r[0] = mem.read_u32(ctx.r[10] + (29012)); // lwz r0, 29012(r10)
    /* 0x800BDDB0 */ ctx.r[9] = ctx.r[0] & 0x0010u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0010
    /* 0x800BDDB4 */ if (ctx.eval_bc(4, 2)) goto loc_800BDE40; // bc 4, 2, 0x800BDE40
    /* 0x800BDDB8 */ ctx.r[0] = mem.read_u32(ctx.r[10] + (340)); // lwz r0, 340(r10)
    /* 0x800BDDBC */ ctx.r[10] = ctx.r[0] & 0x04000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r0, 0x0400
    /* 0x800BDDC0 */ if (ctx.eval_bc(12, 2)) goto loc_800BDE40; // bc 12, 2, 0x800BDE40
    /* 0x800BDDC4 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29532)); // lwz r3, -29532(r13) [R11a_pSat]
    /* 0x800BDDC8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BDDCC */ if (ctx.eval_bc(12, 2)) goto loc_800BDDD4; // bc 12, 2, 0x800BDDD4
    /* 0x800BDDD0 */ ScrAtDelete_8000646C(ctx, mem); // bl 0x8000646C <ScrAtDelete(tagSCR_AT *)>
loc_800BDDD4:;
    /* 0x800BDDD4 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29524)); // lwz r3, -29524(r13) [R11a_pCam]
    /* 0x800BDDD8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BDDDC */ if (ctx.eval_bc(12, 2)) goto loc_800BDDE4; // bc 12, 2, 0x800BDDE4
    /* 0x800BDDE0 */ ScrAtDelete_8000646C(ctx, mem); // bl 0x8000646C <ScrAtDelete(tagSCR_AT *)>
loc_800BDDE4:;
    /* 0x800BDDE4 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29540)); // lwz r3, -29540(r13) [R11a_pStp]
    /* 0x800BDDE8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BDDEC */ if (ctx.eval_bc(12, 2)) goto loc_800BDDF4; // bc 12, 2, 0x800BDDF4
    /* 0x800BDDF0 */ PushObj_800749C8(ctx, mem); // bl 0x800749C8 <PushObj(cObj *)>
loc_800BDDF4:;
    /* 0x800BDDF4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BDDF8 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BDDFC */ ctx.r[0] = mem.read_u32(ctx.r[9] + (29012)); // lwz r0, 29012(r9)
    /* 0x800BDE00 */ ctx.r[0] = ctx.r[0] | 0x0010u; // ori r0, r0, 0x0010
    /* 0x800BDE04 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BDE08 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BDE0C */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BDE10 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BDE14 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BDE18 */ mem.write_u32(ctx.r[13] + (-29520), ctx.r[0]); // stw r0, -29520(r13) [pEvent27]
    /* 0x800BDE1C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BDE20 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BDE24 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (88)); // lwz r4, 88(r9)
    /* 0x800BDE28 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BDE2C */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BDE30 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BDE34 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BDE38 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BDE3C */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
loc_800BDE40:;
    /* 0x800BDE40 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29520)); // lwz r3, -29520(r13) [pEvent27]
    /* 0x800BDE44 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BDE48 */ if (ctx.eval_bc(12, 2)) goto loc_800BDFC4; // bc 12, 2, 0x800BDFC4
    /* 0x800BDE4C */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BDE50 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BDE54 */ if (ctx.eval_bc(12, 2)) goto loc_800BDFC4; // bc 12, 2, 0x800BDFC4
    /* 0x800BDE58 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29520)); // lwz r11, -29520(r13) [pEvent27]
    /* 0x800BDE5C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BDE60 */ if (ctx.eval_bc(12, 2)) goto loc_800BDE80; // bc 12, 2, 0x800BDE80
    /* 0x800BDE64 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BDE68 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BDE6C */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BDE70 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BDE74 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BDE78 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BDE7C */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BDE80:;
    /* 0x800BDE80 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BDE84 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BDE88 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11804)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11804(r9) [0x8016D1E4]
    /* 0x800BDE8C */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BDE90 */ ctx.r[5] = ctx.r[1] + (8); // addi r5, r1, 8
    /* 0x800BDE94 */ mem.write_u32(ctx.r[13] + (-29520), ctx.r[0]); // stw r0, -29520(r13) [pEvent27]
    /* 0x800BDE98 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[0])); // stfs f0, 12(r1)
    /* 0x800BDE9C */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BDEA0 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BDEA4 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (44)); // lwz r3, 44(r9)
    /* 0x800BDEA8 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (56)); // lwz r4, 56(r9)
    /* 0x800BDEAC */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BDEB0 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BDEB4 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BDEB8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BDEBC */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BDEC0 */ mem.write_u32(ctx.r[13] + (-29544), ctx.r[3]); // stw r3, -29544(r13) [R11a_pObj]
    /* 0x800BDEC4 */ ctx.r[4] = 0x00000100u; // li r4, 256
    /* 0x800BDEC8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BDECC */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800BDED0 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (60)); // lwz r3, 60(r9)
    /* 0x800BDED4 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BDED8 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BDEDC */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BDEE0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BDEE4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11800)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11800(r9) [0x8016D1E8]
    /* 0x800BDEE8 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BDEEC */ ctx.f[12] = mem.read_f32(ctx.r[11] + (-11796)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -11796(r11) [0x8016D1EC]
    /* 0x800BDEF0 */ ctx.r[8] = 0x80170000u; // lis r8, 0x8017
    /* 0x800BDEF4 */ ctx.f[11] = mem.read_f32(ctx.r[10] + (-11792)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -11792(r10) [0x8016D1F0]
    /* 0x800BDEF8 */ ctx.r[9] = ctx.r[1] + (40); // addi r9, r1, 40
    /* 0x800BDEFC */ mem.write_f32(ctx.r[1] + (40), static_cast<float>(ctx.f[0])); // stfs f0, 40(r1)
    /* 0x800BDF00 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BDF04 */ ctx.f[13] = mem.read_f32(ctx.r[8] + (-11808)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11808(r8) [0x8016D1E0]
    /* 0x800BDF08 */ ctx.r[7] = ctx.r[1] + (56); // addi r7, r1, 56
    /* 0x800BDF0C */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r9)
    /* 0x800BDF10 */ ctx.r[11] = ctx.r[1] + (72); // addi r11, r1, 72
    /* 0x800BDF14 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[11])); // stfs f11, 8(r9)
    /* 0x800BDF18 */ ctx.r[6] = ctx.r[1] + (88); // addi r6, r1, 88
    /* 0x800BDF1C */ ctx.f[0] = mem.read_f32(ctx.r[10] + (-11788)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11788(r10) [0x8016D1F4]
    /* 0x800BDF20 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BDF24 */ mem.write_f32(ctx.r[1] + (56), static_cast<float>(ctx.f[13])); // stfs f13, 56(r1)
    /* 0x800BDF28 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BDF2C */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800BDF30 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r7)
    /* 0x800BDF34 */ mem.write_u32(ctx.r[13] + (-29536), ctx.r[3]); // stw r3, -29536(r13) [R11a_pEat]
    /* 0x800BDF38 */ ctx.r[10] = mem.read_u32(ctx.r[1] + (40)); // lwz r10, 40(r1)
    /* 0x800BDF3C */ ctx.r[3] = ctx.r[11]; // mr r3, r11
    /* 0x800BDF40 */ ctx.r[8] = mem.read_u32(ctx.r[9] + (8)); // lwz r8, 8(r9)
    /* 0x800BDF44 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (4)); // lwz r0, 4(r9)
    /* 0x800BDF48 */ mem.write_u32(ctx.r[1] + (72), ctx.r[10]); // stw r10, 72(r1)
    /* 0x800BDF4C */ mem.write_u32(ctx.r[11] + (8), ctx.r[8]); // stw r8, 8(r11)
    /* 0x800BDF50 */ mem.write_u32(ctx.r[11] + (4), ctx.r[0]); // stw r0, 4(r11)
    /* 0x800BDF54 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (56)); // lwz r9, 56(r1)
    /* 0x800BDF58 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BDF5C */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BDF60 */ mem.write_u32(ctx.r[1] + (88), ctx.r[9]); // stw r9, 88(r1)
    /* 0x800BDF64 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BDF68 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BDF6C */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BDF70 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29544)); // lwz r3, -29544(r13) [R11a_pObj]
    /* 0x800BDF74 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800BDF78 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BDF7C */ ctx.r[8] = 0x00000004u; // li r8, 4
    /* 0x800BDF80 */ ctx.r[6] = mem.read_u32(ctx.r[3] + (304)); // lwz r6, 304(r3)
    /* 0x800BDF84 */ ctx.r[3] = ctx.r[3] + (312); // addi r3, r3, 312
    /* 0x800BDF88 */ ctx.r[7] = ctx.r[6] + (32); // addi r7, r6, 32
    /* 0x800BDF8C */ ctx.r[6] = ctx.r[6] + (20); // addi r6, r6, 20
    /* 0x800BDF90 */ LightInfoInit2_8009AFDC(ctx, mem); // bl 0x8009AFDC <LightInfoInit2(tagLIGHT_INFO *, unsigned char, short, Vec *, Vec *, unsigned char)>
    /* 0x800BDF94 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BDF98 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29544)); // lwz r11, -29544(r13) [R11a_pObj]
    /* 0x800BDF9C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11784)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11784(r9) [0x8016D1F8 /* "A " */]
    /* 0x800BDFA0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BDFA4 */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800BDFA8 */ ctx.r[5] = 0x00000002u; // li r5, 2
    /* 0x800BDFAC */ mem.write_f32(ctx.r[11] + (224), static_cast<float>(ctx.f[0])); // stfs f0, 224(r11)
    /* 0x800BDFB0 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BDFB4 */ mem.write_f32(ctx.r[11] + (216), static_cast<float>(ctx.f[0])); // stfs f0, 216(r11)
    /* 0x800BDFB8 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BDFBC */ mem.write_f32(ctx.r[11] + (220), static_cast<float>(ctx.f[0])); // stfs f0, 220(r11)
    /* 0x800BDFC0 */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
loc_800BDFC4:;
    /* 0x800BDFC4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BDFC8 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BDFCC */ ctx.r[0] = ctx.r[11] & 0x0008u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andi. r0, r11, 0x0008
    /* 0x800BDFD0 */ if (ctx.eval_bc(4, 2)) goto loc_800BE04C; // bc 4, 2, 0x800BE04C
    /* 0x800BDFD4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BDFD8 */ ctx.r[10] = ctx.r[0] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r0, 0x4000
    /* 0x800BDFDC */ if (ctx.eval_bc(12, 2)) goto loc_800BE04C; // bc 12, 2, 0x800BE04C
    /* 0x800BDFE0 */ ctx.r[0] = ctx.r[11] | 0x0008u; // ori r0, r11, 0x0008
    /* 0x800BDFE4 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BDFE8 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BDFEC */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BDFF0 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BDFF4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BDFF8 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BDFFC */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BE000 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BE004 */ mem.write_u32(ctx.r[13] + (-29516), ctx.r[0]); // stw r0, -29516(r13) [pEvent28]
    /* 0x800BE008 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (92)); // lwz r4, 92(r9)
    /* 0x800BE00C */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BE010 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BE014 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29544)); // lwz r11, -29544(r13) [R11a_pObj]
    /* 0x800BE018 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BE01C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BE020 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BE024 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE028 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BE02C */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BE030 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BE034 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BE038 */ ctx.r[4] = 0x00000014u; // li r4, 20
    /* 0x800BE03C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BE040 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BE044 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
    /* 0x800BE048 */ Snd_str_fadeout_800CD394(ctx, mem); // bl 0x800CD394 <Snd_str_fadeout(long, long)>
loc_800BE04C:;
    /* 0x800BE04C */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29516)); // lwz r3, -29516(r13) [pEvent28]
    /* 0x800BE050 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BE054 */ if (ctx.eval_bc(12, 2)) goto loc_800BE238; // bc 12, 2, 0x800BE238
    /* 0x800BE058 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BE05C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BE060 */ if (ctx.eval_bc(12, 2)) goto loc_800BE238; // bc 12, 2, 0x800BE238
    /* 0x800BE064 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29516)); // lwz r11, -29516(r13) [pEvent28]
    /* 0x800BE068 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BE06C */ if (ctx.eval_bc(12, 2)) goto loc_800BE08C; // bc 12, 2, 0x800BE08C
    /* 0x800BE070 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BE074 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BE078 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BE07C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BE080 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BE084 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE088 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BE08C:;
    /* 0x800BE08C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE090 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29536)); // lwz r3, -29536(r13) [R11a_pEat]
    /* 0x800BE094 */ ctx.r[31] = mem.read_u32(ctx.r[9] + (-11808)); // lwz r31, -11808(r9) [0x8016D1E0]
    /* 0x800BE098 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BE09C */ mem.write_u32(ctx.r[13] + (-29516), ctx.r[0]); // stw r0, -29516(r13) [pEvent28]
    /* 0x800BE0A0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BE0A4 */ mem.write_u32(ctx.r[1] + (12), ctx.r[31]); // stw r31, 12(r1)
    /* 0x800BE0A8 */ if (ctx.eval_bc(12, 2)) goto loc_800BE0B0; // bc 12, 2, 0x800BE0B0
    /* 0x800BE0AC */ ScrAtDelete_8000646C(ctx, mem); // bl 0x8000646C <ScrAtDelete(tagSCR_AT *)>
loc_800BE0B0:;
    /* 0x800BE0B0 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29544)); // lwz r3, -29544(r13) [R11a_pObj]
    /* 0x800BE0B4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BE0B8 */ if (ctx.eval_bc(12, 2)) goto loc_800BE0C0; // bc 12, 2, 0x800BE0C0
    /* 0x800BE0BC */ PushObj_800749C8(ctx, mem); // bl 0x800749C8 <PushObj(cObj *)>
loc_800BE0C0:;
    /* 0x800BE0C0 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE0C4 */ ctx.r[5] = ctx.r[1] + (8); // addi r5, r1, 8
    /* 0x800BE0C8 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BE0CC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BE0D0 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (48)); // lwz r3, 48(r9)
    /* 0x800BE0D4 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (56)); // lwz r4, 56(r9)
    /* 0x800BE0D8 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BE0DC */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BE0E0 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BE0E4 */ ctx.r[9] = ctx.r[3]; // mr r9, r3
    /* 0x800BE0E8 */ ctx.r[8] = 0x00000004u; // li r8, 4
    /* 0x800BE0EC */ ctx.r[6] = mem.read_u32(ctx.r[9] + (304)); // lwz r6, 304(r9)
    /* 0x800BE0F0 */ ctx.r[3] = ctx.r[9] + (312); // addi r3, r9, 312
    /* 0x800BE0F4 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800BE0F8 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BE0FC */ ctx.r[7] = ctx.r[6] + (32); // addi r7, r6, 32
    /* 0x800BE100 */ mem.write_u32(ctx.r[13] + (-29544), ctx.r[9]); // stw r9, -29544(r13) [R11a_pObj]
    /* 0x800BE104 */ ctx.r[6] = ctx.r[6] + (20); // addi r6, r6, 20
    /* 0x800BE108 */ LightInfoInit2_8009AFDC(ctx, mem); // bl 0x8009AFDC <LightInfoInit2(tagLIGHT_INFO *, unsigned char, short, Vec *, Vec *, unsigned char)>
    /* 0x800BE10C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE110 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29544)); // lwz r11, -29544(r13) [R11a_pObj]
    /* 0x800BE114 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11784)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11784(r9) [0x8016D1F8 /* "A " */]
    /* 0x800BE118 */ ctx.r[4] = 0x00000100u; // li r4, 256
    /* 0x800BE11C */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BE120 */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800BE124 */ mem.write_f32(ctx.r[11] + (224), static_cast<float>(ctx.f[0])); // stfs f0, 224(r11)
    /* 0x800BE128 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BE12C */ mem.write_f32(ctx.r[11] + (216), static_cast<float>(ctx.f[0])); // stfs f0, 216(r11)
    /* 0x800BE130 */ mem.write_f32(ctx.r[11] + (220), static_cast<float>(ctx.f[0])); // stfs f0, 220(r11)
    /* 0x800BE134 */ ctx.r[9] = mem.read_u32(ctx.r[10] + (272)); // lwz r9, 272(r10)
    /* 0x800BE138 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (64)); // lwz r3, 64(r9)
    /* 0x800BE13C */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BE140 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BE144 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE148 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BE14C */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800BE150 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BE154 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BE158 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (72)); // lwz r3, 72(r9)
    /* 0x800BE15C */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BE160 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BE164 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE168 */ ctx.r[4] = 0x00000200u; // li r4, 512
    /* 0x800BE16C */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800BE170 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BE174 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BE178 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (72)); // lwz r3, 72(r9)
    /* 0x800BE17C */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BE180 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BE184 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE188 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BE18C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BE190 */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800BE194 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BE198 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (80)); // lwz r3, 80(r9)
    /* 0x800BE19C */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BE1A0 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BE1A4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE1A8 */ mem.write_u32(ctx.r[1] + (40), ctx.r[31]); // stw r31, 40(r1)
    /* 0x800BE1AC */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11780)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11780(r9) [0x8016D1FC]
    /* 0x800BE1B0 */ ctx.r[11] = ctx.r[1] + (40); // addi r11, r1, 40
    /* 0x800BE1B4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE1B8 */ mem.write_u32(ctx.r[11] + (4), ctx.r[31]); // stw r31, 4(r11)
    /* 0x800BE1BC */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BE1C0 */ ctx.r[8] = ctx.r[1] + (56); // addi r8, r1, 56
    /* 0x800BE1C4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11788)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11788(r9) [0x8016D1F4]
    /* 0x800BE1C8 */ ctx.r[10] = ctx.r[1] + (72); // addi r10, r1, 72
    /* 0x800BE1CC */ mem.write_u32(ctx.r[1] + (56), ctx.r[31]); // stw r31, 56(r1)
    /* 0x800BE1D0 */ ctx.r[6] = ctx.r[1] + (104); // addi r6, r1, 104
    /* 0x800BE1D4 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800BE1D8 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BE1DC */ mem.write_u32(ctx.r[8] + (8), ctx.r[31]); // stw r31, 8(r8)
    /* 0x800BE1E0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BE1E4 */ mem.write_u32(ctx.r[13] + (-29528), ctx.r[3]); // stw r3, -29528(r13) [R11a_pWall]
    /* 0x800BE1E8 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (40)); // lwz r9, 40(r1)
    /* 0x800BE1EC */ ctx.r[3] = ctx.r[10]; // mr r3, r10
    /* 0x800BE1F0 */ ctx.r[7] = mem.read_u32(ctx.r[11] + (8)); // lwz r7, 8(r11)
    /* 0x800BE1F4 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (4)); // lwz r0, 4(r11)
    /* 0x800BE1F8 */ mem.write_u32(ctx.r[1] + (72), ctx.r[9]); // stw r9, 72(r1)
    /* 0x800BE1FC */ mem.write_u32(ctx.r[10] + (8), ctx.r[7]); // stw r7, 8(r10)
    /* 0x800BE200 */ mem.write_u32(ctx.r[10] + (4), ctx.r[0]); // stw r0, 4(r10)
    /* 0x800BE204 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (56)); // lwz r9, 56(r1)
    /* 0x800BE208 */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BE20C */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BE210 */ mem.write_u32(ctx.r[1] + (104), ctx.r[9]); // stw r9, 104(r1)
    /* 0x800BE214 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BE218 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BE21C */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BE220 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BE224 */ ctx.r[4] = 0x00000026u; // li r4, 38
    /* 0x800BE228 */ ctx.r[5] = 0x00000003u; // li r5, 3
    /* 0x800BE22C */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BE230 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BE234 */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
loc_800BE238:;
    /* 0x800BE238 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BE23C */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BE240 */ ctx.r[0] = ctx.r[11] & 0x0004u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andi. r0, r11, 0x0004
    /* 0x800BE244 */ if (ctx.eval_bc(4, 2)) goto loc_800BE2B0; // bc 4, 2, 0x800BE2B0
    /* 0x800BE248 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BE24C */ ctx.r[10] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r0, 0x2000
    /* 0x800BE250 */ if (ctx.eval_bc(12, 2)) goto loc_800BE2B0; // bc 12, 2, 0x800BE2B0
    /* 0x800BE254 */ ctx.r[0] = ctx.r[11] | 0x0004u; // ori r0, r11, 0x0004
    /* 0x800BE258 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BE25C */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BE260 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BE264 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BE268 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE26C */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BE270 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BE274 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BE278 */ mem.write_u32(ctx.r[13] + (-29512), ctx.r[0]); // stw r0, -29512(r13) [pEvent29]
    /* 0x800BE27C */ ctx.r[4] = mem.read_u32(ctx.r[9] + (112)); // lwz r4, 112(r9)
    /* 0x800BE280 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BE284 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BE288 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29544)); // lwz r11, -29544(r13) [R11a_pObj]
    /* 0x800BE28C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BE290 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (48)))); // lha r3, 48(r9)
    /* 0x800BE294 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (52)); // lwz r0, 52(r9)
    /* 0x800BE298 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BE29C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE2A0 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BE2A4 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BE2A8 */ ctx.r[4] = 0x000000C8u; // li r4, 200
    /* 0x800BE2AC */ Snd_str_fadeout_800CD394(ctx, mem); // bl 0x800CD394 <Snd_str_fadeout(long, long)>
loc_800BE2B0:;
    /* 0x800BE2B0 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29512)); // lwz r3, -29512(r13) [pEvent29]
    /* 0x800BE2B4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BE2B8 */ if (ctx.eval_bc(12, 2)) goto loc_800BE4B0; // bc 12, 2, 0x800BE4B0
    /* 0x800BE2BC */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BE2C0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BE2C4 */ if (ctx.eval_bc(12, 2)) goto loc_800BE4B0; // bc 12, 2, 0x800BE4B0
    /* 0x800BE2C8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29512)); // lwz r11, -29512(r13) [pEvent29]
    /* 0x800BE2CC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BE2D0 */ if (ctx.eval_bc(12, 2)) goto loc_800BE2F0; // bc 12, 2, 0x800BE2F0
    /* 0x800BE2D4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BE2D8 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BE2DC */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BE2E0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BE2E4 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BE2E8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE2EC */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BE2F0:;
    /* 0x800BE2F0 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29544)); // lwz r11, -29544(r13) [R11a_pObj]
    /* 0x800BE2F4 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BE2F8 */ mem.write_u32(ctx.r[13] + (-29512), ctx.r[0]); // stw r0, -29512(r13) [pEvent29]
    /* 0x800BE2FC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BE300 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (44)); // lwz r0, 44(r9)
    /* 0x800BE304 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (40)))); // lha r3, 40(r9)
    /* 0x800BE308 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE30C */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BE310 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BE314 */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800BE318 */ ctx.r[4] = 0x00000043u; // li r4, 67
    /* 0x800BE31C */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800BE320 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BE324 */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800BE328 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BE32C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE330 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-11776)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11776(r9) [0x8016D200]
    /* 0x800BE334 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BE338 */ ctx.r[0] = mem.read_u32(ctx.r[10] + (332)); // lwz r0, 332(r10)
    /* 0x800BE33C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE340 */ ctx.f[12] = mem.read_f32(ctx.r[11] + (-11772)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -11772(r11) [0x8016D204]
    /* 0x800BE344 */ ctx.r[7] = 0x80170000u; // lis r7, 0x8017
    /* 0x800BE348 */ ctx.r[0] = ctx.r[0] | 0x10000000u; // oris r0, r0, 0x1000
    /* 0x800BE34C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11768)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11768(r9) [0x8016D208]
    /* 0x800BE350 */ mem.write_u32(ctx.r[10] + (332), ctx.r[0]); // stw r0, 332(r10)
    /* 0x800BE354 */ ctx.r[11] = ctx.r[1] + (40); // addi r11, r1, 40
    /* 0x800BE358 */ mem.write_f32(ctx.r[1] + (40), static_cast<float>(ctx.f[13])); // stfs f13, 40(r1)
    /* 0x800BE35C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE360 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BE364 */ ctx.r[8] = ctx.r[1] + (56); // addi r8, r1, 56
    /* 0x800BE368 */ ctx.f[13] = mem.read_f32(ctx.r[7] + (-11808)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11808(r7) [0x8016D1E0]
    /* 0x800BE36C */ ctx.r[10] = ctx.r[1] + (72); // addi r10, r1, 72
    /* 0x800BE370 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r11)
    /* 0x800BE374 */ ctx.r[6] = ctx.r[1] + (88); // addi r6, r1, 88
    /* 0x800BE378 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11788)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11788(r9) [0x8016D1F4]
    /* 0x800BE37C */ ctx.r[3] = ctx.r[10]; // mr r3, r10
    /* 0x800BE380 */ mem.write_f32(ctx.r[1] + (56), static_cast<float>(ctx.f[13])); // stfs f13, 56(r1)
    /* 0x800BE384 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BE388 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800BE38C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BE390 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r8)
    /* 0x800BE394 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (40)); // lwz r9, 40(r1)
    /* 0x800BE398 */ ctx.r[7] = mem.read_u32(ctx.r[11] + (8)); // lwz r7, 8(r11)
    /* 0x800BE39C */ ctx.r[0] = mem.read_u32(ctx.r[11] + (4)); // lwz r0, 4(r11)
    /* 0x800BE3A0 */ mem.write_u32(ctx.r[1] + (72), ctx.r[9]); // stw r9, 72(r1)
    /* 0x800BE3A4 */ mem.write_u32(ctx.r[10] + (4), ctx.r[0]); // stw r0, 4(r10)
    /* 0x800BE3A8 */ mem.write_u32(ctx.r[10] + (8), ctx.r[7]); // stw r7, 8(r10)
    /* 0x800BE3AC */ ctx.r[9] = mem.read_u32(ctx.r[1] + (56)); // lwz r9, 56(r1)
    /* 0x800BE3B0 */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BE3B4 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BE3B8 */ mem.write_u32(ctx.r[1] + (88), ctx.r[9]); // stw r9, 88(r1)
    /* 0x800BE3BC */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BE3C0 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BE3C4 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BE3C8 */ ctx.r[3] = 0x0000001Au; // li r3, 26
    /* 0x800BE3CC */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BE3D0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BE3D4 */ SetCommunication_8007748C(ctx, mem); // bl 0x8007748C <SetCommunication(COMMUNICATION_NO, COMMUNICATION_TYPE, unsigned long *)>
    /* 0x800BE3D8 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29528)); // lwz r3, -29528(r13) [R11a_pWall]
    /* 0x800BE3DC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BE3E0 */ if (ctx.eval_bc(12, 2)) goto loc_800BE3E8; // bc 12, 2, 0x800BE3E8
    /* 0x800BE3E4 */ ScrAtDelete_8000646C(ctx, mem); // bl 0x8000646C <ScrAtDelete(tagSCR_AT *)>
loc_800BE3E8:;
    /* 0x800BE3E8 */ ctx.r[3] = 0x00000002u; // li r3, 2
    /* 0x800BE3EC */ PullObj_80074784(ctx, mem); // bl 0x80074784 <PullObj(long)>
    /* 0x800BE3F0 */ ctx.r[31] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // mr r31, r3
    /* 0x800BE3F4 */ if (ctx.eval_bc(12, 2)) goto loc_800BE484; // bc 12, 2, 0x800BE484
    /* 0x800BE3F8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE3FC */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800BE400 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BE404 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (104)); // lwz r4, 104(r9)
    /* 0x800BE408 */ ctx.r[5] = mem.read_u32(ctx.r[9] + (108)); // lwz r5, 108(r9)
    /* 0x800BE40C */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BE410 */ ctx.r[5] = ctx.r[5] + ctx.r[9]; // add r5, r5, r9
    /* 0x800BE414 */ cObj__ModelInit_80074D30(ctx, mem); // bl 0x80074D30 <cObj::ModelInit(unsigned long, unsigned long)>
    /* 0x800BE418 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (8)); // lwz r9, 8(r1)
    /* 0x800BE41C */ ctx.r[11] = ctx.r[31] + (192); // addi r11, r31, 192
    /* 0x800BE420 */ ctx.r[0] = mem.read_u32(ctx.r[29] + (8)); // lwz r0, 8(r29)
    /* 0x800BE424 */ ctx.r[8] = ctx.r[31] + (204); // addi r8, r31, 204
    /* 0x800BE428 */ ctx.r[10] = mem.read_u32(ctx.r[29] + (4)); // lwz r10, 4(r29)
    /* 0x800BE42C */ ctx.r[6] = 0x00000005u; // li r6, 5
    /* 0x800BE430 */ mem.write_u32(ctx.r[31] + (192), ctx.r[9]); // stw r9, 192(r31)
    /* 0x800BE434 */ ctx.r[5] = 0x00000005u; // li r5, 5
    /* 0x800BE438 */ mem.write_u32(ctx.r[11] + (8), ctx.r[0]); // stw r0, 8(r11)
    /* 0x800BE43C */ ctx.r[7] = 0x000000FFu; // li r7, 255
    /* 0x800BE440 */ mem.write_u32(ctx.r[11] + (4), ctx.r[10]); // stw r10, 4(r11)
    /* 0x800BE444 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (24)); // lwz r9, 24(r1)
    /* 0x800BE448 */ ctx.r[11] = mem.read_u32(ctx.r[30] + (4)); // lwz r11, 4(r30)
    /* 0x800BE44C */ ctx.r[0] = mem.read_u32(ctx.r[30] + (8)); // lwz r0, 8(r30)
    /* 0x800BE450 */ mem.write_u32(ctx.r[31] + (204), ctx.r[9]); // stw r9, 204(r31)
    /* 0x800BE454 */ mem.write_u32(ctx.r[8] + (8), ctx.r[0]); // stw r0, 8(r8)
    /* 0x800BE458 */ mem.write_u32(ctx.r[8] + (4), ctx.r[11]); // stw r11, 4(r8)
    /* 0x800BE45C */ mem.write_u8(ctx.r[31] + (295), static_cast<uint8_t>(ctx.r[6])); // stb r6, 295(r31)
    /* 0x800BE460 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (304)); // lwz r9, 304(r31)
    /* 0x800BE464 */ mem.write_u32(ctx.r[31] + (1288), ctx.r[5]); // stw r5, 1288(r31)
    /* 0x800BE468 */ mem.write_u16(ctx.r[31] + (1292), static_cast<uint16_t>(ctx.r[7])); // sth r7, 1292(r31)
    /* 0x800BE46C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800BE470 */ if (ctx.eval_bc(12, 2)) goto loc_800BE484; // bc 12, 2, 0x800BE484
    /* 0x800BE474 */ ctx.r[9] = mem.read_u32(ctx.r[9] + (156)); // lwz r9, 156(r9)
    /* 0x800BE478 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (32)); // lwz r0, 32(r9)
    /* 0x800BE47C */ ctx.r[0] = ctx.r[0] | 0x0002u; // ori r0, r0, 0x0002
    /* 0x800BE480 */ mem.write_u32(ctx.r[9] + (32), ctx.r[0]); // stw r0, 32(r9)
loc_800BE484:;
    /* 0x800BE484 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE488 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE48C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11764)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11764(r9) [0x8016D20C]
    /* 0x800BE490 */ ctx.r[5] = ctx.r[29]; // mr r5, r29
    /* 0x800BE494 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BE498 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BE49C */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[0])); // stfs f0, 12(r1)
    /* 0x800BE4A0 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BE4A4 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (84)); // lwz r3, 84(r9)
    /* 0x800BE4A8 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BE4AC */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
loc_800BE4B0:;
    /* 0x800BE4B0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (140)); // lwz r0, 140(r1)
    /* 0x800BE4B4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE4B8 */ ctx.lmw(mem, 29, ctx.r[1] + (124)); // lmw r29, 124(r1)
    /* 0x800BE4BC */ ctx.r[1] = ctx.r[1] + (136); // addi r1, r1, 136
    /* 0x800BE4C0 */ return; // blr
}

// [0x800BE4C4] Ra12Init(void) (ra12.obj, 18 insns / 0x48 bytes)
void Ra12Init_800BE4C4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BE4C4 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BE4C8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BE4CC */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BE4D0 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE4D4 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BE4D8 */ ctx.r[3] = 0x801C0000u; // lis r3, 0x801C
    /* 0x800BE4DC */ mem.write_u32(ctx.r[13] + (-29508), ctx.r[0]); // stw r0, -29508(r13) [pEvent01]
    /* 0x800BE4E0 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BE4E4 */ ctx.r[3] = ctx.r[3] + (19360); // addi r3, r3, 19360 -> mesA12
    /* 0x800BE4E8 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (60)); // lwz r4, 60(r9)
    /* 0x800BE4EC */ ctx.r[5] = mem.read_u32(ctx.r[9] + (56)); // lwz r5, 56(r9)
    /* 0x800BE4F0 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BE4F4 */ ctx.r[5] = ctx.r[5] + ctx.r[9]; // add r5, r5, r9
    /* 0x800BE4F8 */ cIdMain__SetTexPrim_8007245C(ctx, mem); // bl 0x8007245C <cIdMain::SetTexPrim(unsigned long, unsigned long)>
    /* 0x800BE4FC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BE500 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE504 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BE508 */ return; // blr
}

// [0x800BE50C] Ra12Main(void) (ra12.obj, 72 insns / 0x120 bytes)
void Ra12Main_800BE50C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BE50C */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BE510 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BE514 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BE518 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BE51C */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BE520 */ ctx.r[0] = ctx.r[11] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andis. r0, r11, 0x4000
    /* 0x800BE524 */ if (ctx.eval_bc(4, 2)) goto loc_800BE568; // bc 4, 2, 0x800BE568
    /* 0x800BE528 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BE52C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BE530 */ if (ctx.eval_bc(4, 0)) goto loc_800BE568; // bc 4, 0, 0x800BE568
    /* 0x800BE534 */ ctx.r[0] = ctx.r[11] | 0x40000000u; // oris r0, r11, 0x4000
    /* 0x800BE538 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BE53C */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BE540 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BE544 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BE548 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE54C */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BE550 */ mem.write_u32(ctx.r[13] + (-29508), ctx.r[0]); // stw r0, -29508(r13) [pEvent01]
    /* 0x800BE554 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BE558 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BE55C */ ctx.r[4] = mem.read_u32(ctx.r[9] + (36)); // lwz r4, 36(r9)
    /* 0x800BE560 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BE564 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
loc_800BE568:;
    /* 0x800BE568 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29508)); // lwz r3, -29508(r13) [pEvent01]
    /* 0x800BE56C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BE570 */ if (ctx.eval_bc(12, 2)) goto loc_800BE61C; // bc 12, 2, 0x800BE61C
    /* 0x800BE574 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BE578 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BE57C */ if (ctx.eval_bc(12, 2)) goto loc_800BE61C; // bc 12, 2, 0x800BE61C
    /* 0x800BE580 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29508)); // lwz r11, -29508(r13) [pEvent01]
    /* 0x800BE584 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BE588 */ if (ctx.eval_bc(12, 2)) goto loc_800BE5A8; // bc 12, 2, 0x800BE5A8
    /* 0x800BE58C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BE590 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BE594 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BE598 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BE59C */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BE5A0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE5A4 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BE5A8:;
    /* 0x800BE5A8 */ ctx.r[8] = 0x00000000u; // li r8, 0
    /* 0x800BE5AC */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BE5B0 */ mem.write_u32(ctx.r[13] + (-29508), ctx.r[8]); // stw r8, -29508(r13) [pEvent01]
    /* 0x800BE5B4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE5B8 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11740)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11740(r9) [0x8016D224]
    /* 0x800BE5BC */ ctx.r[7] = 0x0000000Au; // li r7, 10
    /* 0x800BE5C0 */ ctx.r[0] = mem.read_u8(ctx.r[10] + (27256)); // lbz r0, 27256(r10)
    /* 0x800BE5C4 */ ctx.r[6] = 0x00000013u; // li r6, 19
    /* 0x800BE5C8 */ ctx.r[5] = 0x00000004u; // li r5, 4
    /* 0x800BE5CC */ mem.write_u8(ctx.r[10] + (27258), static_cast<uint8_t>(ctx.r[0])); // stb r0, 27258(r10)
    /* 0x800BE5D0 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE5D4 */ ctx.r[0] = mem.read_u8(ctx.r[11] + (27257)); // lbz r0, 27257(r11)
    /* 0x800BE5D8 */ mem.write_u8(ctx.r[11] + (27259), static_cast<uint8_t>(ctx.r[0])); // stb r0, 27259(r11)
    /* 0x800BE5DC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BE5E0 */ mem.write_u8(ctx.r[9] + (27277), static_cast<uint8_t>(ctx.r[7])); // stb r7, 27277(r9)
    /* 0x800BE5E4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE5E8 */ mem.write_u8(ctx.r[11] + (27276), static_cast<uint8_t>(ctx.r[6])); // stb r6, 27276(r11)
    /* 0x800BE5EC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BE5F0 */ mem.write_u8(ctx.r[9] + (260), static_cast<uint8_t>(ctx.r[5])); // stb r5, 260(r9)
    /* 0x800BE5F4 */ mem.write_f32(ctx.r[9] + (27272), static_cast<float>(ctx.f[0])); // stfs f0, 27272(r9)
    /* 0x800BE5F8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE5FC */ mem.write_f32(ctx.r[9] + (27260), static_cast<float>(ctx.f[0])); // stfs f0, 27260(r9)
    /* 0x800BE600 */ mem.write_f32(ctx.r[9] + (27264), static_cast<float>(ctx.f[0])); // stfs f0, 27264(r9)
    /* 0x800BE604 */ mem.write_f32(ctx.r[9] + (27268), static_cast<float>(ctx.f[0])); // stfs f0, 27268(r9)
    /* 0x800BE608 */ mem.write_u8(ctx.r[11] + (261), static_cast<uint8_t>(ctx.r[8])); // stb r8, 261(r11)
    /* 0x800BE60C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BE610 */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[8])); // stb r8, 262(r9)
    /* 0x800BE614 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE618 */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[8])); // stb r8, 263(r11)
loc_800BE61C:;
    /* 0x800BE61C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BE620 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE624 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BE628 */ return; // blr
}

// [0x800BE62C] __static_initialization_and_destruction_0 (ra12.obj, 10 insns / 0x28 bytes)
void static_initialization_and_destruction_0_800BE62C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BE62C */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BE630 */ ctx.r[0] = ctx.r[0] | 0xFFFFu; // ori r0, r0, 0xFFFF
    /* 0x800BE634 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[4]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r4, r0
    /* 0x800BE638 */ if (ctx.eval_bc(4, 2)) return; // bclr 4, 2
    /* 0x800BE63C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BE640 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE644 */ ctx.r[11] = 0x801C0000u; // lis r11, 0x801C
    /* 0x800BE648 */ ctx.r[9] = ctx.r[9] + (-30272); // addi r9, r9, -30272 -> cIdMain virtual table
    /* 0x800BE64C */ mem.write_u32(ctx.r[11] + (19384), ctx.r[9]); // stw r9, 19384(r11) [0x801C4BB8]
    /* 0x800BE650 */ return; // blr
}

// [0x800BE654] global constructors keyed to Ra12Init(void) (ra12.obj, 11 insns / 0x2C bytes)
void global_constructors_keyed_to_Ra12Init_800BE654(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BE654 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BE658 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BE65C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BE660 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BE664 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BE668 */ ctx.r[4] = ctx.r[4] | 0xFFFFu; // ori r4, r4, 0xFFFF
    /* 0x800BE66C */ static_initialization_and_destruction_0_800BE62C(ctx, mem); // bl 0x800BE62C <__static_initialization_and_destruction_0>
    /* 0x800BE670 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BE674 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE678 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BE67C */ return; // blr
}

// [0x800BE680] global destructors keyed to Ra12Init(void) (ra12.obj, 11 insns / 0x2C bytes)
void global_destructors_keyed_to_Ra12Init_800BE680(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BE680 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BE684 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BE688 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BE68C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BE690 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BE694 */ ctx.r[4] = ctx.r[4] | 0xFFFFu; // ori r4, r4, 0xFFFF
    /* 0x800BE698 */ static_initialization_and_destruction_0_800BE62C(ctx, mem); // bl 0x800BE62C <__static_initialization_and_destruction_0>
    /* 0x800BE69C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BE6A0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE6A4 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BE6A8 */ return; // blr
}

// [0x800BE6AC] Ra13Init(void) (ra13.obj, 171 insns / 0x2AC bytes)
void Ra13Init_800BE6AC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BE6AC */ ctx.r[1] += (-40); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -40(r1)
    /* 0x800BE6B0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BE6B4 */ ctx.stmw(mem, 29, ctx.r[1] + (28)); // stmw r29, 28(r1)
    /* 0x800BE6B8 */ mem.write_u32(ctx.r[1] + (44), ctx.r[0]); // stw r0, 44(r1)
    /* 0x800BE6BC */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BE6C0 */ ctx.r[29] = 0x801C0000u; // lis r29, 0x801C
    /* 0x800BE6C4 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BE6C8 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BE6CC */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BE6D0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE6D4 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BE6D8 */ ctx.r[9] = ctx.r[9] + (-11672); // addi r9, r9, -11672 -> cEvent99 virtual table
    /* 0x800BE6DC */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BE6E0 */ mem.write_u32(ctx.r[30] + (16), ctx.r[9]); // stw r9, 16(r30)
    /* 0x800BE6E4 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800BE6E8 */ mem.write_u32(ctx.r[13] + (-29504), ctx.r[30]); // stw r30, -29504(r13) [{anonymous}::pEvent99]
    /* 0x800BE6EC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BE6F0 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (120)); // lwz r4, 120(r9)
    /* 0x800BE6F4 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BE6F8 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BE6FC */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BE700 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BE704 */ mem.write_u8(ctx.r[13] + (-29499), static_cast<uint8_t>(ctx.r[0])); // stb r0, -29499(r13) [{anonymous}::r_no_0]
    /* 0x800BE708 */ ctx.r[3] = ctx.r[29] + (19388); // addi r3, r29, 19388 -> {anonymous}::staffIdd
    /* 0x800BE70C */ ctx.r[0] = mem.read_u32(ctx.r[10] + (296)); // lwz r0, 296(r10)
    /* 0x800BE710 */ ctx.r[9] = mem.read_u32(ctx.r[10] + (336)); // lwz r9, 336(r10)
    /* 0x800BE714 */ ctx.r[0] = ctx.r[0] | 0x18000000u; // oris r0, r0, 0x1800
    /* 0x800BE718 */ ctx.r[11] = mem.read_u32(ctx.r[10] + (272)); // lwz r11, 272(r10)
    /* 0x800BE71C */ ctx.r[9] = ctx.r[9] | 0x00010000u; // oris r9, r9, 0x0001
    /* 0x800BE720 */ mem.write_u32(ctx.r[10] + (296), ctx.r[0]); // stw r0, 296(r10)
    /* 0x800BE724 */ mem.write_u32(ctx.r[10] + (336), ctx.r[9]); // stw r9, 336(r10)
    /* 0x800BE728 */ ctx.r[4] = mem.read_u32(ctx.r[11] + (128)); // lwz r4, 128(r11)
    /* 0x800BE72C */ ctx.r[5] = mem.read_u32(ctx.r[11] + (124)); // lwz r5, 124(r11)
    /* 0x800BE730 */ ctx.r[4] = ctx.r[4] + ctx.r[11]; // add r4, r4, r11
    /* 0x800BE734 */ ctx.r[5] = ctx.r[5] + ctx.r[11]; // add r5, r5, r11
    /* 0x800BE738 */ cIdMain__SetTexPrim_8007245C(ctx, mem); // bl 0x8007245C <cIdMain::SetTexPrim(unsigned long, unsigned long)>
    /* 0x800BE73C */ ctx.r[29] = ctx.r[29] + (19388); // addi r29, r29, 19388 -> {anonymous}::staffIdd
    /* 0x800BE740 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE744 */ ctx.r[0] = mem.read_u32(ctx.r[29] + (20)); // lwz r0, 20(r29)
    /* 0x800BE748 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BE74C */ ctx.f[10] = mem.read_f32(ctx.r[9] + (-11716)); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // lfs f10, -11716(r9) [0x8016D23C]
    /* 0x800BE750 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[7]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r7, r0
    /* 0x800BE754 */ if (ctx.eval_bc(4, 0)) goto loc_800BE84C; // bc 4, 0, 0x800BE84C
    /* 0x800BE758 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE75C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BE760 */ ctx.f[11] = mem.read_f32(ctx.r[9] + (-11700)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -11700(r9) [0x8016D24C /* "BH" */]
    /* 0x800BE764 */ ctx.r[30] = 0x43300000u; // lis r30, 0x4330
    /* 0x800BE768 */ ctx.r[9] = 0x801C0000u; // lis r9, 0x801C
    /* 0x800BE76C */ ctx.f[12] = mem.read_f64(ctx.r[11] + (-11712)); // lfd f12, -11712(r11) [0x8016D240 /* "C0" */]
    /* 0x800BE770 */ ctx.r[3] = ctx.r[9] + (19416); // addi r3, r9, 19416 -> {anonymous}::tex_y
    /* 0x800BE774 */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800BE778 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BE77C */ ctx.r[6] = 0xFFFFFFFFu; // li r6, -1
loc_800BE780:;
    /* 0x800BE780 */ ctx.f[0] = ctx.f[10]; ctx.ps0[0] = static_cast<float>(ctx.f[10]); // fmr f0, f10
    /* 0x800BE784 */ { int32_t iv = static_cast<int32_t>(ctx.f[0]); uint64_t u = static_cast<uint32_t>(iv); std::memcpy(&ctx.f[13], &u, 8); } // fctiwz f13, f0
    /* 0x800BE788 */ ctx.r[0] = mem.read_u32(ctx.r[29] + (20)); // lwz r0, 20(r29)
    /* 0x800BE78C */ mem.write_f64(ctx.r[1] + (16), ctx.f[13]); // stfd f13, 16(r1)
    /* 0x800BE790 */ ctx.r[11] = 0x00000000u; // li r11, 0
    /* 0x800BE794 */ mem.write_f32(ctx.r[3] + (0), static_cast<float>(ctx.f[10])); // stfs f10, 0(r3)
    /* 0x800BE798 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[7]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r7, r0
    /* 0x800BE79C */ ctx.r[10] = mem.read_u32(ctx.r[1] + (20)); // lwz r10, 20(r1)
    /* 0x800BE7A0 */ ctx.r[3] = ctx.r[3] + (4); // addi r3, r3, 4
    /* 0x800BE7A4 */ if (ctx.eval_bc(4, 0)) goto loc_800BE7AC; // bc 4, 0, 0x800BE7AC
    /* 0x800BE7A8 */ ctx.rlwinm(11, 6, 1u, 31u, 31u, false); // rlwinm r11, r6, 1, 31, 31
loc_800BE7AC:;
    /* 0x800BE7AC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BE7B0 */ ctx.r[8] = static_cast<uint32_t>(static_cast<int32_t>(ctx.r[7]) * (156)); // mulli r8, r7, 156
    /* 0x800BE7B4 */ if (ctx.eval_bc(12, 2)) goto loc_800BE7C4; // bc 12, 2, 0x800BE7C4
    /* 0x800BE7B8 */ ctx.r[9] = mem.read_u32(ctx.r[29] + (8)); // lwz r9, 8(r29)
    /* 0x800BE7BC */ ctx.r[9] = ctx.r[5] + ctx.r[9]; // add r9, r5, r9
    /* 0x800BE7C0 */ mem.write_f32(ctx.r[9] + (80), static_cast<float>(ctx.f[11])); // stfs f11, 80(r9)
loc_800BE7C4:;
    /* 0x800BE7C4 */ ctx.r[0] = mem.read_u32(ctx.r[29] + (20)); // lwz r0, 20(r29)
    /* 0x800BE7C8 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BE7CC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[7]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r7, r0
    /* 0x800BE7D0 */ if (ctx.eval_bc(4, 0)) goto loc_800BE7D8; // bc 4, 0, 0x800BE7D8
    /* 0x800BE7D4 */ ctx.rlwinm(9, 4, 1u, 31u, 31u, false); // rlwinm r9, r4, 1, 31, 31
loc_800BE7D8:;
    /* 0x800BE7D8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800BE7DC */ if (ctx.eval_bc(12, 2)) goto loc_800BE804; // bc 12, 2, 0x800BE804
    /* 0x800BE7E0 */ ctx.r[0] = ctx.r[10] ^ 0x80000000u; // xoris r0, r10, 0x8000
    /* 0x800BE7E4 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800BE7E8 */ ctx.r[11] = mem.read_u32(ctx.r[29] + (8)); // lwz r11, 8(r29)
    /* 0x800BE7EC */ mem.write_u32(ctx.r[1] + (16), ctx.r[30]); // stw r30, 16(r1)
    /* 0x800BE7F0 */ ctx.r[11] = ctx.r[8] + ctx.r[11]; // add r11, r8, r11
    /* 0x800BE7F4 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (16)); // lfd f0, 16(r1)
    /* 0x800BE7F8 */ ctx.f[0] = ctx.f[0] - ctx.f[12]; // fsub f0, f0, f12
    /* 0x800BE7FC */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800BE800 */ mem.write_f32(ctx.r[11] + (84), static_cast<float>(ctx.f[0])); // stfs f0, 84(r11)
loc_800BE804:;
    /* 0x800BE804 */ ctx.r[11] = mem.read_u32(ctx.r[29] + (8)); // lwz r11, 8(r29)
    /* 0x800BE808 */ ctx.r[0] = mem.read_u32(ctx.r[29] + (20)); // lwz r0, 20(r29)
    /* 0x800BE80C */ ctx.r[7] = ctx.r[7] + (1); // addi r7, r7, 1
    /* 0x800BE810 */ ctx.r[11] = ctx.r[8] + ctx.r[11]; // add r11, r8, r11
    /* 0x800BE814 */ ctx.r[4] = ctx.r[4] + (-1); // addi r4, r4, -1
    /* 0x800BE818 */ ctx.r[9] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[11] + (90)))); // lha r9, 90(r11)
    /* 0x800BE81C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[7]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r7, r0
    /* 0x800BE820 */ ctx.r[5] = ctx.r[5] + (156); // addi r5, r5, 156
    /* 0x800BE824 */ ctx.r[6] = ctx.r[6] + (-1); // addi r6, r6, -1
    /* 0x800BE828 */ ctx.r[9] = ctx.r[9] + (100); // addi r9, r9, 100
    /* 0x800BE82C */ ctx.r[9] = ctx.r[9] ^ 0x80000000u; // xoris r9, r9, 0x8000
    /* 0x800BE830 */ mem.write_u32(ctx.r[1] + (20), ctx.r[9]); // stw r9, 20(r1)
    /* 0x800BE834 */ mem.write_u32(ctx.r[1] + (16), ctx.r[30]); // stw r30, 16(r1)
    /* 0x800BE838 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (16)); // lfd f0, 16(r1)
    /* 0x800BE83C */ ctx.f[0] = ctx.f[0] - ctx.f[12]; // fsub f0, f0, f12
    /* 0x800BE840 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800BE844 */ ctx.f[10] = static_cast<float>(ctx.f[10] + ctx.f[0]); ctx.ps0[10] = static_cast<float>(ctx.f[10]); // fadds f10, f10, f0
    /* 0x800BE848 */ if (ctx.eval_bc(12, 0)) goto loc_800BE780; // bc 12, 0, 0x800BE780
loc_800BE84C:;
    /* 0x800BE84C */ ctx.r[9] = 0x801C0000u; // lis r9, 0x801C
    /* 0x800BE850 */ ctx.r[4] = ctx.r[9] + (19388); // addi r4, r9, 19388 -> {anonymous}::staffIdd
    /* 0x800BE854 */ ctx.r[3] = 0x43300000u; // lis r3, 0x4330
    /* 0x800BE858 */ ctx.r[8] = mem.read_u32(ctx.r[4] + (20)); // lwz r8, 20(r4)
    /* 0x800BE85C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE860 */ ctx.r[7] = mem.read_u32(ctx.r[4] + (8)); // lwz r7, 8(r4)
    /* 0x800BE864 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BE868 */ ctx.r[5] = ctx.r[8] + (-1); // addi r5, r8, -1
    /* 0x800BE86C */ ctx.f[9] = mem.read_f64(ctx.r[9] + (-11712)); // lfd f9, -11712(r9) [0x8016D240 /* "C0" */]
    /* 0x800BE870 */ ctx.r[30] = static_cast<uint32_t>(static_cast<int32_t>(ctx.r[5]) * (156)); // mulli r30, r5, 156
    /* 0x800BE874 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[5]), static_cast<int32_t>(ctx.r[8])); // cmpw cr0, r5, r8
    /* 0x800BE878 */ ctx.f[11] = mem.read_f32(ctx.r[11] + (-11704)); ctx.ps0[11] = static_cast<float>(ctx.f[11]); // lfs f11, -11704(r11) [0x8016D248]
    /* 0x800BE87C */ ctx.r[9] = 0x801C0000u; // lis r9, 0x801C
    /* 0x800BE880 */ ctx.r[11] = ctx.r[10]; // mr r11, r10
    /* 0x800BE884 */ ctx.rlwinm(6, 5, 2u, 0u, 29u, false); // rlwinm r6, r5, 2, 0, 29
    /* 0x800BE888 */ ctx.r[9] = ctx.r[9] + (19416); // addi r9, r9, 19416 -> {anonymous}::tex_y
    /* 0x800BE88C */ ctx.r[8] = ctx.r[30] + ctx.r[7]; // add r8, r30, r7
    /* 0x800BE890 */ ctx.r[0] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[8] + (90)))); // lha r0, 90(r8)
    /* 0x800BE894 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BE898 */ ctx.r[0] = ctx.r[0] ^ 0x80000000u; // xoris r0, r0, 0x8000
    /* 0x800BE89C */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800BE8A0 */ mem.write_u32(ctx.r[1] + (16), ctx.r[3]); // stw r3, 16(r1)
    /* 0x800BE8A4 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (16)); // lfd f0, 16(r1)
    /* 0x800BE8A8 */ ctx.f[0] = ctx.f[0] - ctx.f[9]; // fsub f0, f0, f9
    /* 0x800BE8AC */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800BE8B0 */ ctx.f[0] = static_cast<float>(ctx.f[10] - ctx.f[0]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fsubs f0, f10, f0
    /* 0x800BE8B4 */ ctx.f[0] = static_cast<float>(ctx.f[0] + ctx.f[11]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // fadds f0, f0, f11
    /* 0x800BE8B8 */ ctx.f[13] = ctx.f[0]; ctx.ps0[13] = static_cast<float>(ctx.f[0]); // fmr f13, f0
    /* 0x800BE8BC */ mem.write_f32(ctx.r[9] + ctx.r[6], static_cast<float>(ctx.f[0])); // stfsx f0, r9, r6
    /* 0x800BE8C0 */ { int32_t iv = static_cast<int32_t>(ctx.f[13]); uint64_t u = static_cast<uint32_t>(iv); std::memcpy(&ctx.f[12], &u, 8); } // fctiwz f12, f13
    /* 0x800BE8C4 */ mem.write_f64(ctx.r[1] + (16), ctx.f[12]); // stfd f12, 16(r1)
    /* 0x800BE8C8 */ ctx.r[11] = mem.read_u32(ctx.r[1] + (20)); // lwz r11, 20(r1)
    /* 0x800BE8CC */ if (ctx.eval_bc(4, 0)) goto loc_800BE8D8; // bc 4, 0, 0x800BE8D8
    /* 0x800BE8D0 */ ctx.r[0] = ~(ctx.r[5] | ctx.r[5]); // nor r0, r5, r5
    /* 0x800BE8D4 */ ctx.rlwinm(7, 0, 1u, 31u, 31u, false); // rlwinm r7, r0, 1, 31, 31
loc_800BE8D8:;
    /* 0x800BE8D8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[7]), 0); // cmpwi cr0, r7, 0
    /* 0x800BE8DC */ if (ctx.eval_bc(12, 2)) goto loc_800BE900; // bc 12, 2, 0x800BE900
    /* 0x800BE8E0 */ ctx.r[0] = 0x00000032u; // li r0, 50
    /* 0x800BE8E4 */ ctx.r[0] = ctx.r[0] ^ 0x80000000u; // xoris r0, r0, 0x8000
    /* 0x800BE8E8 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800BE8EC */ mem.write_u32(ctx.r[1] + (16), ctx.r[3]); // stw r3, 16(r1)
    /* 0x800BE8F0 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (16)); // lfd f0, 16(r1)
    /* 0x800BE8F4 */ ctx.f[0] = ctx.f[0] - ctx.f[9]; // fsub f0, f0, f9
    /* 0x800BE8F8 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800BE8FC */ mem.write_f32(ctx.r[8] + (80), static_cast<float>(ctx.f[0])); // stfs f0, 80(r8)
loc_800BE900:;
    /* 0x800BE900 */ ctx.r[0] = mem.read_u32(ctx.r[4] + (20)); // lwz r0, 20(r4)
    /* 0x800BE904 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BE908 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[5]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r5, r0
    /* 0x800BE90C */ if (ctx.eval_bc(4, 0)) goto loc_800BE918; // bc 4, 0, 0x800BE918
    /* 0x800BE910 */ ctx.r[0] = ~(ctx.r[5] | ctx.r[5]); // nor r0, r5, r5
    /* 0x800BE914 */ ctx.rlwinm(6, 0, 1u, 31u, 31u, false); // rlwinm r6, r0, 1, 31, 31
loc_800BE918:;
    /* 0x800BE918 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[6]), 0); // cmpwi cr0, r6, 0
    /* 0x800BE91C */ if (ctx.eval_bc(12, 2)) goto loc_800BE944; // bc 12, 2, 0x800BE944
    /* 0x800BE920 */ ctx.r[0] = ctx.r[11] ^ 0x80000000u; // xoris r0, r11, 0x8000
    /* 0x800BE924 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800BE928 */ ctx.r[11] = mem.read_u32(ctx.r[4] + (8)); // lwz r11, 8(r4)
    /* 0x800BE92C */ mem.write_u32(ctx.r[1] + (16), ctx.r[3]); // stw r3, 16(r1)
    /* 0x800BE930 */ ctx.r[11] = ctx.r[30] + ctx.r[11]; // add r11, r30, r11
    /* 0x800BE934 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (16)); // lfd f0, 16(r1)
    /* 0x800BE938 */ ctx.f[0] = ctx.f[0] - ctx.f[9]; // fsub f0, f0, f9
    /* 0x800BE93C */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800BE940 */ mem.write_f32(ctx.r[11] + (84), static_cast<float>(ctx.f[0])); // stfs f0, 84(r11)
loc_800BE944:;
    /* 0x800BE944 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (44)); // lwz r0, 44(r1)
    /* 0x800BE948 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BE94C */ ctx.lmw(mem, 29, ctx.r[1] + (28)); // lmw r29, 28(r1)
    /* 0x800BE950 */ ctx.r[1] = ctx.r[1] + (40); // addi r1, r1, 40
    /* 0x800BE954 */ return; // blr
}

// [0x800BE958] draw(void) (ra13.obj, 171 insns / 0x2AC bytes)
void draw_800BE958(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BE958 */ ctx.r[1] += (-80); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -80(r1)
    /* 0x800BE95C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BE960 */ mem.write_f64(ctx.r[1] + (48), ctx.f[28]); // stfd f28, 48(r1)
    /* 0x800BE964 */ mem.write_f64(ctx.r[1] + (56), ctx.f[29]); // stfd f29, 56(r1)
    /* 0x800BE968 */ mem.write_f64(ctx.r[1] + (64), ctx.f[30]); // stfd f30, 64(r1)
    /* 0x800BE96C */ mem.write_f64(ctx.r[1] + (72), ctx.f[31]); // stfd f31, 72(r1)
    /* 0x800BE970 */ ctx.stmw(mem, 24, ctx.r[1] + (16)); // stmw r24, 16(r1)
    /* 0x800BE974 */ mem.write_u32(ctx.r[1] + (84), ctx.r[0]); // stw r0, 84(r1)
    /* 0x800BE978 */ ctx.r[30] = 0x801C0000u; // lis r30, 0x801C
    /* 0x800BE97C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BE980 */ ctx.r[3] = ctx.r[30] + (19388); // addi r3, r30, 19388 -> {anonymous}::staffIdd
    /* 0x800BE984 */ ctx.r[5] = 0xFFFFFFFFu; // li r5, -1
    /* 0x800BE988 */ cIdMain__PrimMove_800725F8(ctx, mem); // bl 0x800725F8 <cIdMain::PrimMove(long, long)>
    /* 0x800BE98C */ ctx.r[31] = 0x00000000u; // li r31, 0
    /* 0x800BE990 */ ctx.r[3] = ctx.r[30] + (19388); // addi r3, r30, 19388 -> {anonymous}::staffIdd
    /* 0x800BE994 */ ctx.r[0] = mem.read_u32(ctx.r[3] + (20)); // lwz r0, 20(r3)
    /* 0x800BE998 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r31, r0
    /* 0x800BE99C */ if (ctx.eval_bc(4, 0)) goto loc_800BEB28; // bc 4, 0, 0x800BEB28
    /* 0x800BE9A0 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BE9A4 */ ctx.r[26] = 0x80170000u; // lis r26, 0x8017
    /* 0x800BE9A8 */ ctx.f[28] = mem.read_f32(ctx.r[9] + (-11696)); ctx.ps0[28] = static_cast<float>(ctx.f[28]); // lfs f28, -11696(r9) [0x8016D250]
    /* 0x800BE9AC */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BE9B0 */ ctx.r[9] = 0x801C0000u; // lis r9, 0x801C
    /* 0x800BE9B4 */ ctx.f[30] = mem.read_f32(ctx.r[11] + (-11676)); ctx.ps0[30] = static_cast<float>(ctx.f[30]); // lfs f30, -11676(r11) [0x8016D264 /* "BH" */]
    /* 0x800BE9B8 */ ctx.f[29] = mem.read_f64(ctx.r[26] + (-11688)); // lfd f29, -11688(r26) [0x8016D258 /* "C0" */]
    /* 0x800BE9BC */ ctx.r[27] = ctx.r[9] + (19416); // addi r27, r9, 19416 -> {anonymous}::tex_y
    /* 0x800BE9C0 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BE9C4 */ ctx.r[24] = 0x43300000u; // lis r24, 0x4330
    /* 0x800BE9C8 */ ctx.r[29] = 0x00000000u; // li r29, 0
    /* 0x800BE9CC */ ctx.r[28] = 0x00000000u; // li r28, 0
    /* 0x800BE9D0 */ ctx.r[25] = 0x43300000u; // lis r25, 0x4330
loc_800BE9D4:;
    /* 0x800BE9D4 */ ctx.f[13] = mem.read_f32(ctx.r[28] + ctx.r[27]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfsx f13, r28, r27
    /* 0x800BE9D8 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (20)); // lwz r0, 20(r30)
    /* 0x800BE9DC */ ctx.r[11] = 0x00000000u; // li r11, 0
    /* 0x800BE9E0 */ ctx.f[13] = static_cast<float>(ctx.f[13] - ctx.f[28]); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // fsubs f13, f13, f28
    /* 0x800BE9E4 */ ctx.f[0] = ctx.f[13]; ctx.ps0[0] = static_cast<float>(ctx.f[13]); // fmr f0, f13
    /* 0x800BE9E8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r31, r0
    /* 0x800BE9EC */ { int32_t iv = static_cast<int32_t>(ctx.f[0]); uint64_t u = static_cast<uint32_t>(iv); std::memcpy(&ctx.f[12], &u, 8); } // fctiwz f12, f0
    /* 0x800BE9F0 */ mem.write_f32(ctx.r[28] + ctx.r[27], static_cast<float>(ctx.f[13])); // stfsx f13, r28, r27
    /* 0x800BE9F4 */ mem.write_f64(ctx.r[1] + (8), ctx.f[12]); // stfd f12, 8(r1)
    /* 0x800BE9F8 */ ctx.r[10] = mem.read_u32(ctx.r[1] + (12)); // lwz r10, 12(r1)
    /* 0x800BE9FC */ if (ctx.eval_bc(4, 0)) goto loc_800BEA08; // bc 4, 0, 0x800BEA08
    /* 0x800BEA00 */ ctx.r[0] = ~(ctx.r[31] | ctx.r[31]); // nor r0, r31, r31
    /* 0x800BEA04 */ ctx.rlwinm(11, 0, 1u, 31u, 31u, false); // rlwinm r11, r0, 1, 31, 31
loc_800BEA08:;
    /* 0x800BEA08 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BEA0C */ if (ctx.eval_bc(12, 2)) goto loc_800BEA1C; // bc 12, 2, 0x800BEA1C
    /* 0x800BEA10 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (8)); // lwz r9, 8(r30)
    /* 0x800BEA14 */ ctx.r[9] = ctx.r[29] + ctx.r[9]; // add r9, r29, r9
    /* 0x800BEA18 */ mem.write_f32(ctx.r[9] + (80), static_cast<float>(ctx.f[30])); // stfs f30, 80(r9)
loc_800BEA1C:;
    /* 0x800BEA1C */ ctx.r[0] = mem.read_u32(ctx.r[30] + (20)); // lwz r0, 20(r30)
    /* 0x800BEA20 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BEA24 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r31, r0
    /* 0x800BEA28 */ if (ctx.eval_bc(4, 0)) goto loc_800BEA34; // bc 4, 0, 0x800BEA34
    /* 0x800BEA2C */ ctx.r[0] = ~(ctx.r[31] | ctx.r[31]); // nor r0, r31, r31
    /* 0x800BEA30 */ ctx.rlwinm(9, 0, 1u, 31u, 31u, false); // rlwinm r9, r0, 1, 31, 31
loc_800BEA34:;
    /* 0x800BEA34 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800BEA38 */ if (ctx.eval_bc(12, 2)) goto loc_800BEA60; // bc 12, 2, 0x800BEA60
    /* 0x800BEA3C */ ctx.r[0] = ctx.r[10] ^ 0x80000000u; // xoris r0, r10, 0x8000
    /* 0x800BEA40 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BEA44 */ ctx.r[11] = mem.read_u32(ctx.r[30] + (8)); // lwz r11, 8(r30)
    /* 0x800BEA48 */ mem.write_u32(ctx.r[1] + (8), ctx.r[24]); // stw r24, 8(r1)
    /* 0x800BEA4C */ ctx.r[11] = ctx.r[29] + ctx.r[11]; // add r11, r29, r11
    /* 0x800BEA50 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (8)); // lfd f0, 8(r1)
    /* 0x800BEA54 */ ctx.f[0] = ctx.f[0] - ctx.f[29]; // fsub f0, f0, f29
    /* 0x800BEA58 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800BEA5C */ mem.write_f32(ctx.r[11] + (84), static_cast<float>(ctx.f[0])); // stfs f0, 84(r11)
loc_800BEA60:;
    /* 0x800BEA60 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (20)); // lwz r9, 20(r30)
    /* 0x800BEA64 */ ctx.r[9] = ctx.r[9] + (-1); // addi r9, r9, -1
    /* 0x800BEA68 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), static_cast<int32_t>(ctx.r[9])); // cmpw cr0, r31, r9
    /* 0x800BEA6C */ if (ctx.eval_bc(12, 2)) goto loc_800BEB10; // bc 12, 2, 0x800BEB10
    /* 0x800BEA70 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (8)); // lwz r9, 8(r30)
    /* 0x800BEA74 */ ctx.f[13] = mem.read_f64(ctx.r[26] + (-11688)); // lfd f13, -11688(r26) [0x8016D258 /* "C0" */]
    /* 0x800BEA78 */ ctx.r[9] = ctx.r[29] + ctx.r[9]; // add r9, r29, r9
    /* 0x800BEA7C */ ctx.f[12] = mem.read_f32(ctx.r[28] + ctx.r[27]); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfsx f12, r28, r27
    /* 0x800BEA80 */ ctx.r[0] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (90)))); // lha r0, 90(r9)
    /* 0x800BEA84 */ ctx.r[0] = static_cast<uint32_t>(-static_cast<int32_t>(ctx.r[0])); // neg r0, r0
    /* 0x800BEA88 */ ctx.r[0] = ctx.r[0] ^ 0x80000000u; // xoris r0, r0, 0x8000
    /* 0x800BEA8C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BEA90 */ mem.write_u32(ctx.r[1] + (8), ctx.r[25]); // stw r25, 8(r1)
    /* 0x800BEA94 */ ctx.f[0] = mem.read_f64(ctx.r[1] + (8)); // lfd f0, 8(r1)
    /* 0x800BEA98 */ ctx.f[0] = ctx.f[0] - ctx.f[13]; // fsub f0, f0, f13
    /* 0x800BEA9C */ ctx.f[31] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f31, f0
    /* 0x800BEAA0 */ ctx.cmp_f64(0, ctx.f[31], ctx.f[12]); // fcmpu cr0, f31, f12
    /* 0x800BEAA4 */ if (ctx.eval_bc(4, 1)) goto loc_800BEB10; // bc 4, 1, 0x800BEB10
    /* 0x800BEAA8 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800BEAAC */ ctx.r[4] = ctx.r[31]; // mr r4, r31
    /* 0x800BEAB0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BEAB4 */ cIdMain__SetSwitch_80072710(ctx, mem); // bl 0x80072710 <cIdMain::SetSwitch(long, bool)>
    /* 0x800BEAB8 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (20)); // lwz r0, 20(r30)
    /* 0x800BEABC */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BEAC0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r31, r0
    /* 0x800BEAC4 */ if (ctx.eval_bc(4, 0)) goto loc_800BEAD0; // bc 4, 0, 0x800BEAD0
    /* 0x800BEAC8 */ ctx.r[0] = ~(ctx.r[31] | ctx.r[31]); // nor r0, r31, r31
    /* 0x800BEACC */ ctx.rlwinm(9, 0, 1u, 31u, 31u, false); // rlwinm r9, r0, 1, 31, 31
loc_800BEAD0:;
    /* 0x800BEAD0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800BEAD4 */ if (ctx.eval_bc(12, 2)) goto loc_800BEAE4; // bc 12, 2, 0x800BEAE4
    /* 0x800BEAD8 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (8)); // lwz r9, 8(r30)
    /* 0x800BEADC */ ctx.r[9] = ctx.r[29] + ctx.r[9]; // add r9, r29, r9
    /* 0x800BEAE0 */ mem.write_f32(ctx.r[9] + (80), static_cast<float>(ctx.f[30])); // stfs f30, 80(r9)
loc_800BEAE4:;
    /* 0x800BEAE4 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (20)); // lwz r0, 20(r30)
    /* 0x800BEAE8 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BEAEC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r31, r0
    /* 0x800BEAF0 */ if (ctx.eval_bc(4, 0)) goto loc_800BEAFC; // bc 4, 0, 0x800BEAFC
    /* 0x800BEAF4 */ ctx.r[0] = ~(ctx.r[31] | ctx.r[31]); // nor r0, r31, r31
    /* 0x800BEAF8 */ ctx.rlwinm(9, 0, 1u, 31u, 31u, false); // rlwinm r9, r0, 1, 31, 31
loc_800BEAFC:;
    /* 0x800BEAFC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800BEB00 */ if (ctx.eval_bc(12, 2)) goto loc_800BEB10; // bc 12, 2, 0x800BEB10
    /* 0x800BEB04 */ ctx.r[9] = mem.read_u32(ctx.r[30] + (8)); // lwz r9, 8(r30)
    /* 0x800BEB08 */ ctx.r[9] = ctx.r[29] + ctx.r[9]; // add r9, r29, r9
    /* 0x800BEB0C */ mem.write_f32(ctx.r[9] + (84), static_cast<float>(ctx.f[31])); // stfs f31, 84(r9)
loc_800BEB10:;
    /* 0x800BEB10 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (20)); // lwz r0, 20(r30)
    /* 0x800BEB14 */ ctx.r[31] = ctx.r[31] + (1); // addi r31, r31, 1
    /* 0x800BEB18 */ ctx.r[29] = ctx.r[29] + (156); // addi r29, r29, 156
    /* 0x800BEB1C */ ctx.r[28] = ctx.r[28] + (4); // addi r28, r28, 4
    /* 0x800BEB20 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r31, r0
    /* 0x800BEB24 */ if (ctx.eval_bc(12, 0)) goto loc_800BE9D4; // bc 12, 0, 0x800BE9D4
loc_800BEB28:;
    /* 0x800BEB28 */ ctx.r[9] = 0x801C0000u; // lis r9, 0x801C
    /* 0x800BEB2C */ ctx.r[11] = 0x801C0000u; // lis r11, 0x801C
    /* 0x800BEB30 */ ctx.r[6] = ctx.r[9] + (19388); // addi r6, r9, 19388 -> {anonymous}::staffIdd
    /* 0x800BEB34 */ ctx.r[11] = ctx.r[11] + (19416); // addi r11, r11, 19416 -> {anonymous}::tex_y
    /* 0x800BEB38 */ ctx.r[10] = mem.read_u32(ctx.r[6] + (20)); // lwz r10, 20(r6)
    /* 0x800BEB3C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BEB40 */ ctx.f[12] = mem.read_f32(ctx.r[9] + (-11680)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -11680(r9) [0x8016D260]
    /* 0x800BEB44 */ ctx.r[7] = ctx.r[10] + (-1); // addi r7, r10, -1
    /* 0x800BEB48 */ ctx.rlwinm(0, 7, 2u, 0u, 29u, false); // rlwinm r0, r7, 2, 0, 29
    /* 0x800BEB4C */ ctx.f[0] = mem.read_f32(ctx.r[11] + ctx.r[0]); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfsx f0, r11, r0
    /* 0x800BEB50 */ ctx.cmp_f64(0, ctx.f[0], ctx.f[12]); // fcmpu cr0, f0, f12
    /* 0x800BEB54 */ ctx.set_cr_bit(3, ctx.get_cr_bit(2) | ctx.get_cr_bit(0)); // cror 3, 2, 0
    /* 0x800BEB58 */ if (ctx.eval_bc(4, 3)) goto loc_800BEBE0; // bc 4, 3, 0x800BEBE0
    /* 0x800BEB5C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[7]), static_cast<int32_t>(ctx.r[10])); // cmpw cr0, r7, r10
    /* 0x800BEB60 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BEB64 */ if (ctx.eval_bc(4, 0)) goto loc_800BEB70; // bc 4, 0, 0x800BEB70
    /* 0x800BEB68 */ ctx.r[0] = ~(ctx.r[7] | ctx.r[7]); // nor r0, r7, r7
    /* 0x800BEB6C */ ctx.rlwinm(0, 0, 1u, 31u, 31u, false); // rlwinm r0, r0, 1, 31, 31
loc_800BEB70:;
    /* 0x800BEB70 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BEB74 */ if (ctx.eval_bc(12, 2)) goto loc_800BEBB0; // bc 12, 2, 0x800BEBB0
    /* 0x800BEB78 */ ctx.r[0] = 0x00000032u; // li r0, 50
    /* 0x800BEB7C */ ctx.r[0] = ctx.r[0] ^ 0x80000000u; // xoris r0, r0, 0x8000
    /* 0x800BEB80 */ ctx.r[8] = 0x43300000u; // lis r8, 0x4330
    /* 0x800BEB84 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BEB88 */ ctx.r[10] = static_cast<uint32_t>(static_cast<int32_t>(ctx.r[7]) * (156)); // mulli r10, r7, 156
    /* 0x800BEB8C */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BEB90 */ ctx.r[0] = mem.read_u32(ctx.r[6] + (8)); // lwz r0, 8(r6)
    /* 0x800BEB94 */ mem.write_u32(ctx.r[1] + (8), ctx.r[8]); // stw r8, 8(r1)
    /* 0x800BEB98 */ ctx.f[13] = mem.read_f64(ctx.r[11] + (-11688)); // lfd f13, -11688(r11) [0x8016D258 /* "C0" */]
    /* 0x800BEB9C */ ctx.f[0] = mem.read_f64(ctx.r[1] + (8)); // lfd f0, 8(r1)
    /* 0x800BEBA0 */ ctx.r[10] = ctx.r[10] + ctx.r[0]; // add r10, r10, r0
    /* 0x800BEBA4 */ ctx.f[0] = ctx.f[0] - ctx.f[13]; // fsub f0, f0, f13
    /* 0x800BEBA8 */ ctx.f[0] = static_cast<double>(static_cast<float>(ctx.f[0])); // frsp f0, f0
    /* 0x800BEBAC */ mem.write_f32(ctx.r[10] + (80), static_cast<float>(ctx.f[0])); // stfs f0, 80(r10)
loc_800BEBB0:;
    /* 0x800BEBB0 */ ctx.r[0] = mem.read_u32(ctx.r[6] + (20)); // lwz r0, 20(r6)
    /* 0x800BEBB4 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BEBB8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[7]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r7, r0
    /* 0x800BEBBC */ if (ctx.eval_bc(4, 0)) goto loc_800BEBC8; // bc 4, 0, 0x800BEBC8
    /* 0x800BEBC0 */ ctx.r[0] = ~(ctx.r[7] | ctx.r[7]); // nor r0, r7, r7
    /* 0x800BEBC4 */ ctx.rlwinm(9, 0, 1u, 31u, 31u, false); // rlwinm r9, r0, 1, 31, 31
loc_800BEBC8:;
    /* 0x800BEBC8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800BEBCC */ if (ctx.eval_bc(12, 2)) goto loc_800BEBE0; // bc 12, 2, 0x800BEBE0
    /* 0x800BEBD0 */ ctx.r[9] = static_cast<uint32_t>(static_cast<int32_t>(ctx.r[7]) * (156)); // mulli r9, r7, 156
    /* 0x800BEBD4 */ ctx.r[0] = mem.read_u32(ctx.r[6] + (8)); // lwz r0, 8(r6)
    /* 0x800BEBD8 */ ctx.r[9] = ctx.r[9] + ctx.r[0]; // add r9, r9, r0
    /* 0x800BEBDC */ mem.write_f32(ctx.r[9] + (84), static_cast<float>(ctx.f[12])); // stfs f12, 84(r9)
loc_800BEBE0:;
    /* 0x800BEBE0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (84)); // lwz r0, 84(r1)
    /* 0x800BEBE4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BEBE8 */ ctx.lmw(mem, 24, ctx.r[1] + (16)); // lmw r24, 16(r1)
    /* 0x800BEBEC */ ctx.f[28] = mem.read_f64(ctx.r[1] + (48)); // lfd f28, 48(r1)
    /* 0x800BEBF0 */ ctx.f[29] = mem.read_f64(ctx.r[1] + (56)); // lfd f29, 56(r1)
    /* 0x800BEBF4 */ ctx.f[30] = mem.read_f64(ctx.r[1] + (64)); // lfd f30, 64(r1)
    /* 0x800BEBF8 */ ctx.f[31] = mem.read_f64(ctx.r[1] + (72)); // lfd f31, 72(r1)
    /* 0x800BEBFC */ ctx.r[1] = ctx.r[1] + (80); // addi r1, r1, 80
    /* 0x800BEC00 */ return; // blr
}

// [0x800BEC04] Ra13Main(void) (ra13.obj, 140 insns / 0x230 bytes)
void Ra13Main_800BEC04(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BEC04 */ ctx.r[1] += (-32); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -32(r1)
    /* 0x800BEC08 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BEC0C */ mem.write_u32(ctx.r[1] + (28), ctx.r[31]); // stw r31, 28(r1)
    /* 0x800BEC10 */ mem.write_u32(ctx.r[1] + (36), ctx.r[0]); // stw r0, 36(r1)
    /* 0x800BEC14 */ ctx.r[0] = 0xFF000000u; // lis r0, 0xFF00
    /* 0x800BEC18 */ ctx.r[11] = 0x000000FFu; // li r11, 255
    /* 0x800BEC1C */ mem.write_u32(ctx.r[1] + (16), ctx.r[0]); // stw r0, 16(r1)
    /* 0x800BEC20 */ ctx.r[9] = ctx.r[1] + (16); // addi r9, r1, 16
    /* 0x800BEC24 */ mem.write_u8(ctx.r[9] + (2), static_cast<uint8_t>(ctx.r[11])); // stb r11, 2(r9)
    /* 0x800BEC28 */ ctx.r[4] = 0x00FF0000u; // lis r4, 0x00FF
    /* 0x800BEC2C */ mem.write_u8(ctx.r[9] + (1), static_cast<uint8_t>(ctx.r[11])); // stb r11, 1(r9)
    /* 0x800BEC30 */ ctx.r[3] = ctx.r[1] + (8); // addi r3, r1, 8
    /* 0x800BEC34 */ ctx.r[4] = ctx.r[4] | 0xFFFFu; // ori r4, r4, 0xFFFF
    /* 0x800BEC38 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (16)); // lwz r0, 16(r1)
    /* 0x800BEC3C */ mem.write_u32(ctx.r[1] + (8), ctx.r[0]); // stw r0, 8(r1)
    /* 0x800BEC40 */ ctx.call_indirect(0x80121674u, mem); // bl 0x80121674 <GXSetCopyClear>
    /* 0x800BEC44 */ ctx.r[31] = mem.read_u32(ctx.r[13] + (-29504)); // lwz r31, -29504(r13) [{anonymous}::pEvent99]
    /* 0x800BEC48 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // cmpwi cr0, r31, 0
    /* 0x800BEC4C */ if (ctx.eval_bc(12, 2)) goto loc_800BEE1C; // bc 12, 2, 0x800BEE1C
    /* 0x800BEC50 */ ctx.r[3] = mem.read_u32(ctx.r[31] + (4)); // lwz r3, 4(r31)
    /* 0x800BEC54 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BEC58 */ if (ctx.eval_bc(12, 2)) goto loc_800BEC90; // bc 12, 2, 0x800BEC90
    /* 0x800BEC5C */ ctx.r[4] = mem.read_u32(ctx.r[31] + (0)); // lwz r4, 0(r31)
    /* 0x800BEC60 */ evtScene__Update_800931B0(ctx, mem); // bl 0x800931B0 <evtScene::Update(long)>
    /* 0x800BEC64 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BEC68 */ if (ctx.eval_bc(4, 2)) goto loc_800BEC88; // bc 4, 2, 0x800BEC88
    /* 0x800BEC6C */ ctx.r[9] = mem.read_u32(ctx.r[31] + (0)); // lwz r9, 0(r31)
    /* 0x800BEC70 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 4297); // cmpwi cr0, r9, 4297
    /* 0x800BEC74 */ if (ctx.eval_bc(12, 1)) goto loc_800BEC88; // bc 12, 1, 0x800BEC88
    /* 0x800BEC78 */ ctx.r[0] = ctx.r[9] + (1); // addi r0, r9, 1
    /* 0x800BEC7C */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BEC80 */ mem.write_u32(ctx.r[31] + (0), ctx.r[0]); // stw r0, 0(r31)
    /* 0x800BEC84 */ goto loc_800BEC94; // b 0x800BEC94 <sub_800BEC94>
loc_800BEC88:;
    /* 0x800BEC88 */ ctx.r[9] = 0x00000001u; // li r9, 1
    /* 0x800BEC8C */ goto loc_800BEC94; // b 0x800BEC94 <sub_800BEC94>
loc_800BEC90:;
    /* 0x800BEC90 */ ctx.r[9] = 0x00000000u; // li r9, 0
loc_800BEC94:;
    /* 0x800BEC94 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800BEC98 */ if (ctx.eval_bc(12, 2)) goto loc_800BEE1C; // bc 12, 2, 0x800BEE1C
    /* 0x800BEC9C */ ctx.r[11] = mem.read_u8(ctx.r[13] + (-29499)); // lbz r11, -29499(r13) [{anonymous}::r_no_0]
    /* 0x800BECA0 */ ctx.r[0] = static_cast<uint32_t>(static_cast<int32_t>(static_cast<int8_t>(ctx.r[11]))); // extsb r0, r11
    /* 0x800BECA4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 1); // cmpwi cr0, r0, 1
    /* 0x800BECA8 */ if (ctx.eval_bc(12, 2)) goto loc_800BECE4; // bc 12, 2, 0x800BECE4
    /* 0x800BECAC */ if (ctx.eval_bc(12, 1)) goto loc_800BECBC; // bc 12, 1, 0x800BECBC
    /* 0x800BECB0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BECB4 */ if (ctx.eval_bc(12, 2)) goto loc_800BECD0; // bc 12, 2, 0x800BECD0
    /* 0x800BECB8 */ goto loc_800BEE1C; // b 0x800BEE1C <sub_800BEE1C>
loc_800BECBC:;
    /* 0x800BECBC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 2); // cmpwi cr0, r0, 2
    /* 0x800BECC0 */ if (ctx.eval_bc(12, 2)) goto loc_800BED08; // bc 12, 2, 0x800BED08
    /* 0x800BECC4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 3); // cmpwi cr0, r0, 3
    /* 0x800BECC8 */ if (ctx.eval_bc(12, 2)) goto loc_800BED4C; // bc 12, 2, 0x800BED4C
    /* 0x800BECCC */ goto loc_800BEE1C; // b 0x800BEE1C <sub_800BEE1C>
loc_800BECD0:;
    /* 0x800BECD0 */ ctx.r[0] = ctx.r[11] + (1); // addi r0, r11, 1
    /* 0x800BECD4 */ ctx.r[9] = 0x0000005Au; // li r9, 90
    /* 0x800BECD8 */ mem.write_u8(ctx.r[13] + (-29499), static_cast<uint8_t>(ctx.r[0])); // stb r0, -29499(r13) [{anonymous}::r_no_0]
    /* 0x800BECDC */ mem.write_u8(ctx.r[13] + (-29500), static_cast<uint8_t>(ctx.r[9])); // stb r9, -29500(r13) [{anonymous}::timer]
    /* 0x800BECE0 */ goto loc_800BEE1C; // b 0x800BEE1C <sub_800BEE1C>
loc_800BECE4:;
    /* 0x800BECE4 */ ctx.r[9] = mem.read_u8(ctx.r[13] + (-29500)); // lbz r9, -29500(r13) [{anonymous}::timer]
    /* 0x800BECE8 */ ctx.r[9] = ctx.r[9] + (-1); // addi r9, r9, -1
    /* 0x800BECEC */ ctx.r[0] = static_cast<uint32_t>(static_cast<int32_t>(static_cast<int8_t>(ctx.r[9]))); // extsb r0, r9
    /* 0x800BECF0 */ mem.write_u8(ctx.r[13] + (-29500), static_cast<uint8_t>(ctx.r[9])); // stb r9, -29500(r13) [{anonymous}::timer]
    /* 0x800BECF4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), -1); // cmpwi cr0, r0, -1
    /* 0x800BECF8 */ if (ctx.eval_bc(4, 2)) goto loc_800BEE1C; // bc 4, 2, 0x800BEE1C
    /* 0x800BECFC */ ctx.r[0] = ctx.r[11] + (1); // addi r0, r11, 1
    /* 0x800BED00 */ mem.write_u8(ctx.r[13] + (-29499), static_cast<uint8_t>(ctx.r[0])); // stb r0, -29499(r13) [{anonymous}::r_no_0]
    /* 0x800BED04 */ goto loc_800BEE1C; // b 0x800BEE1C <sub_800BEE1C>
loc_800BED08:;
    /* 0x800BED08 */ ctx.r[9] = 0x801A0000u; // lis r9, 0x801A
    /* 0x800BED0C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (-8140)); // lwz r0, -8140(r9) [0x8019E034]
    /* 0x800BED10 */ ctx.r[9] = ctx.r[0] & 0x1F70u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x1F70
    /* 0x800BED14 */ if (ctx.eval_bc(12, 2)) goto loc_800BEE1C; // bc 12, 2, 0x800BEE1C
    /* 0x800BED18 */ ctx.r[0] = ctx.r[11] + (1); // addi r0, r11, 1
    /* 0x800BED1C */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BED20 */ ctx.r[11] = 0x000000FFu; // li r11, 255
    /* 0x800BED24 */ mem.write_u8(ctx.r[13] + (-29499), static_cast<uint8_t>(ctx.r[0])); // stb r0, -29499(r13) [{anonymous}::r_no_0]
    /* 0x800BED28 */ mem.write_u32(ctx.r[1] + (8), ctx.r[9]); // stw r9, 8(r1)
    /* 0x800BED2C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BED30 */ mem.write_u32(ctx.r[1] + (12), ctx.r[11]); // stw r11, 12(r1)
    /* 0x800BED34 */ ctx.r[4] = ctx.r[1] + (8); // addi r4, r1, 8
    /* 0x800BED38 */ ctx.r[5] = ctx.r[1] + (12); // addi r5, r1, 12
    /* 0x800BED3C */ ctx.r[6] = 0x0000000Au; // li r6, 10
    /* 0x800BED40 */ ctx.r[7] = 0x00000001u; // li r7, 1
    /* 0x800BED44 */ FadeSet_80094358(ctx, mem); // bl 0x80094358 <FadeSet(unsigned long, _GXColor, _GXColor, unsigned long, unsigned long)>
    /* 0x800BED48 */ goto loc_800BEE1C; // b 0x800BEE1C <sub_800BEE1C>
loc_800BED4C:;
    /* 0x800BED4C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BED50 */ FadeCheck_800943D8(ctx, mem); // bl 0x800943D8 <FadeCheck(unsigned long)>
    /* 0x800BED54 */ ctx.r[31] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // mr r31, r3
    /* 0x800BED58 */ if (ctx.eval_bc(4, 2)) goto loc_800BEE1C; // bc 4, 2, 0x800BEE1C
    /* 0x800BED5C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29504)); // lwz r11, -29504(r13) [{anonymous}::pEvent99]
    /* 0x800BED60 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BED64 */ if (ctx.eval_bc(12, 2)) goto loc_800BED84; // bc 12, 2, 0x800BED84
    /* 0x800BED68 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BED6C */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BED70 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BED74 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BED78 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BED7C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BED80 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BED84:;
    /* 0x800BED84 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-32472)); // lwz r0, -32472(r13) [myBgColor]
    /* 0x800BED88 */ ctx.r[4] = 0x00FF0000u; // lis r4, 0x00FF
    /* 0x800BED8C */ mem.write_u32(ctx.r[13] + (-29504), ctx.r[31]); // stw r31, -29504(r13) [{anonymous}::pEvent99]
    /* 0x800BED90 */ ctx.r[3] = ctx.r[1] + (12); // addi r3, r1, 12
    /* 0x800BED94 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BED98 */ ctx.r[4] = ctx.r[4] | 0xFFFFu; // ori r4, r4, 0xFFFF
    /* 0x800BED9C */ ctx.call_indirect(0x80121674u, mem); // bl 0x80121674 <GXSetCopyClear>
    /* 0x800BEDA0 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BEDA4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (336)); // lwz r0, 336(r9)
    /* 0x800BEDA8 */ ctx.r[10] = mem.read_u32(ctx.r[9] + (324)); // lwz r10, 324(r9)
    /* 0x800BEDAC */ ctx.rlwinm(0, 0, 0u, 16u, 14u, false); // rlwinm r0, r0, 0, 16, 14
    /* 0x800BEDB0 */ mem.write_u32(ctx.r[9] + (336), ctx.r[0]); // stw r0, 336(r9)
    /* 0x800BEDB4 */ ctx.r[11] = mem.read_u32(ctx.r[10] + (4)); // lwz r11, 4(r10)
    /* 0x800BEDB8 */ ctx.r[31] = mem.read_u32(ctx.r[10] + (0)); // lwz r31, 0(r10)
    /* 0x800BEDBC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), static_cast<int32_t>(ctx.r[11])); // cmpw cr0, r31, r11
    /* 0x800BEDC0 */ if (ctx.eval_bc(12, 2)) goto loc_800BEDF8; // bc 12, 2, 0x800BEDF8
loc_800BEDC4:;
    /* 0x800BEDC4 */ ctx.r[11] = mem.read_u32(ctx.r[31] + (0)); // lwz r11, 0(r31)
    /* 0x800BEDC8 */ ctx.r[31] = ctx.r[31] + (4); // addi r31, r31, 4
    /* 0x800BEDCC */ ctx.r[9] = mem.read_u32(ctx.r[11] + (1208)); // lwz r9, 1208(r11)
    /* 0x800BEDD0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (36)); // lwz r0, 36(r9)
    /* 0x800BEDD4 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (32)))); // lha r3, 32(r9)
    /* 0x800BEDD8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BEDDC */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BEDE0 */ ctx.call_indirect(ctx.lr, mem); // blrl
    /* 0x800BEDE4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BEDE8 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (324)); // lwz r11, 324(r9)
    /* 0x800BEDEC */ ctx.r[0] = mem.read_u32(ctx.r[11] + (4)); // lwz r0, 4(r11)
    /* 0x800BEDF0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r31, r0
    /* 0x800BEDF4 */ if (ctx.eval_bc(4, 2)) goto loc_800BEDC4; // bc 4, 2, 0x800BEDC4
loc_800BEDF8:;
    /* 0x800BEDF8 */ ctx.r[3] = 0x000000C8u; // li r3, 200
    /* 0x800BEDFC */ SndBgmAllFadeOut_800CC4B0(ctx, mem); // bl 0x800CC4B0 <SndBgmAllFadeOut(long)>
    /* 0x800BEE00 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BEE04 */ ctx.r[3] = 0x80000000u; // lis r3, 0x8000
    /* 0x800BEE08 */ ctx.r[3] = ctx.r[3] + (13504); // addi r3, r3, 13504 -> allResultTask(void)
    /* 0x800BEE0C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (296)); // lwz r0, 296(r9)
    /* 0x800BEE10 */ ctx.r[0] = ctx.r[0] | 0x00100000u; // oris r0, r0, 0x0010
    /* 0x800BEE14 */ mem.write_u32(ctx.r[9] + (296), ctx.r[0]); // stw r0, 296(r9)
    /* 0x800BEE18 */ TaskChain_800A1BE4(ctx, mem); // bl 0x800A1BE4 <TaskChain(void *)>
loc_800BEE1C:;
    /* 0x800BEE1C */ draw_800BE958(ctx, mem); // bl 0x800BE958 <draw(void)>
    /* 0x800BEE20 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (36)); // lwz r0, 36(r1)
    /* 0x800BEE24 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BEE28 */ ctx.r[31] = mem.read_u32(ctx.r[1] + (28)); // lwz r31, 28(r1)
    /* 0x800BEE2C */ ctx.r[1] = ctx.r[1] + (32); // addi r1, r1, 32
    /* 0x800BEE30 */ return; // blr
}

// [0x800BEE34] __static_initialization_and_destruction_0 (ra13.obj, 10 insns / 0x28 bytes)
void static_initialization_and_destruction_0_800BEE34(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BEE34 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BEE38 */ ctx.r[0] = ctx.r[0] | 0xFFFFu; // ori r0, r0, 0xFFFF
    /* 0x800BEE3C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[4]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r4, r0
    /* 0x800BEE40 */ if (ctx.eval_bc(4, 2)) return; // bclr 4, 2
    /* 0x800BEE44 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BEE48 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BEE4C */ ctx.r[11] = 0x801C0000u; // lis r11, 0x801C
    /* 0x800BEE50 */ ctx.r[9] = ctx.r[9] + (-30272); // addi r9, r9, -30272 -> cIdMain virtual table
    /* 0x800BEE54 */ mem.write_u32(ctx.r[11] + (19412), ctx.r[9]); // stw r9, 19412(r11) [0x801C4BD4]
    /* 0x800BEE58 */ return; // blr
}

// [0x800BEE5C] cEvent99::~cEvent99(void) (ra13.obj, 12 insns / 0x30 bytes)
void cEvent99_dtor_cEvent99_800BEE5C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BEE5C */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BEE60 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BEE64 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BEE68 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BEE6C */ ctx.r[11] = ctx.r[3]; // mr r11, r3
    /* 0x800BEE70 */ ctx.r[9] = ctx.r[9] + (-11672); // addi r9, r9, -11672 -> cEvent99 virtual table
    /* 0x800BEE74 */ mem.write_u32(ctx.r[11] + (16), ctx.r[9]); // stw r9, 16(r11)
    /* 0x800BEE78 */ cEvent_dtor_cEvent_80070D30(ctx, mem); // bl 0x80070D30 <cEvent::~cEvent(void)>
    /* 0x800BEE7C */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BEE80 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BEE84 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BEE88 */ return; // blr
}

// [0x800BEE8C] global constructors keyed to Ra13Init(void) (ra13.obj, 11 insns / 0x2C bytes)
void global_constructors_keyed_to_Ra13Init_800BEE8C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BEE8C */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BEE90 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BEE94 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BEE98 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BEE9C */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BEEA0 */ ctx.r[4] = ctx.r[4] | 0xFFFFu; // ori r4, r4, 0xFFFF
    /* 0x800BEEA4 */ static_initialization_and_destruction_0_800BEE34(ctx, mem); // bl 0x800BEE34 <__static_initialization_and_destruction_0>
    /* 0x800BEEA8 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BEEAC */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BEEB0 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BEEB4 */ return; // blr
}

// [0x800BEEB8] global destructors keyed to Ra13Init(void) (ra13.obj, 11 insns / 0x2C bytes)
void global_destructors_keyed_to_Ra13Init_800BEEB8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BEEB8 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800BEEBC */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BEEC0 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800BEEC4 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BEEC8 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BEECC */ ctx.r[4] = ctx.r[4] | 0xFFFFu; // ori r4, r4, 0xFFFF
    /* 0x800BEED0 */ static_initialization_and_destruction_0_800BEE34(ctx, mem); // bl 0x800BEE34 <__static_initialization_and_destruction_0>
    /* 0x800BEED4 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800BEED8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BEEDC */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800BEEE0 */ return; // blr
}

// [0x800BEEE4] Rb00Init(void) (rb00.obj, 113 insns / 0x1C4 bytes)
void Rb00Init_800BEEE4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BEEE4 */ ctx.r[1] += (-104); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -104(r1)
    /* 0x800BEEE8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BEEEC */ mem.write_f64(ctx.r[1] + (72), ctx.f[28]); // stfd f28, 72(r1)
    /* 0x800BEEF0 */ mem.write_f64(ctx.r[1] + (80), ctx.f[29]); // stfd f29, 80(r1)
    /* 0x800BEEF4 */ mem.write_f64(ctx.r[1] + (88), ctx.f[30]); // stfd f30, 88(r1)
    /* 0x800BEEF8 */ mem.write_f64(ctx.r[1] + (96), ctx.f[31]); // stfd f31, 96(r1)
    /* 0x800BEEFC */ ctx.stmw(mem, 25, ctx.r[1] + (44)); // stmw r25, 44(r1)
    /* 0x800BEF00 */ mem.write_u32(ctx.r[1] + (108), ctx.r[0]); // stw r0, 108(r1)
    /* 0x800BEF04 */ ctx.r[30] = ctx.r[1] + (8); // addi r30, r1, 8
    /* 0x800BEF08 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BEF0C */ SmdGetObjPtr_800C33C8(ctx, mem); // bl 0x800C33C8 <SmdGetObjPtr(long)>
    /* 0x800BEF10 */ ctx.r[29] = 0x801C0000u; // lis r29, 0x801C
    /* 0x800BEF14 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BEF18 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BEF1C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BEF20 */ ctx.f[28] = mem.read_f32(ctx.r[10] + (-11628)); ctx.ps0[28] = static_cast<float>(ctx.f[28]); // lfs f28, -11628(r10) [0x8016D294]
    /* 0x800BEF24 */ ctx.f[31] = mem.read_f32(ctx.r[9] + (-11636)); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // lfs f31, -11636(r9) [0x8016D28C]
    /* 0x800BEF28 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800BEF2C */ ctx.f[29] = mem.read_f32(ctx.r[11] + (-11632)); ctx.ps0[29] = static_cast<float>(ctx.f[29]); // lfs f29, -11632(r11) [0x8016D290]
    /* 0x800BEF30 */ ctx.r[28] = ctx.r[1] + (24); // addi r28, r1, 24
    /* 0x800BEF34 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r1)
    /* 0x800BEF38 */ ctx.r[3] = ctx.r[29] + (19508); // addi r3, r29, 19508 -> SLight
    /* 0x800BEF3C */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[31])); // stfs f31, 24(r1)
    /* 0x800BEF40 */ ctx.r[8] = ctx.r[3] + (56); // addi r8, r3, 56
    /* 0x800BEF44 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[29])); // stfs f29, 12(r1)
    /* 0x800BEF48 */ ctx.r[5] = ctx.r[28]; // mr r5, r28
    /* 0x800BEF4C */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[28])); // stfs f28, 16(r1)
    /* 0x800BEF50 */ ctx.r[6] = 0x00000001u; // li r6, 1
    /* 0x800BEF54 */ ctx.r[7] = 0x00000010u; // li r7, 16
    /* 0x800BEF58 */ ctx.r[27] = 0x801C0000u; // lis r27, 0x801C
    /* 0x800BEF5C */ ctx.f[13] = mem.read_f32(ctx.r[30] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r30)
    /* 0x800BEF60 */ ctx.r[26] = 0x801C0000u; // lis r26, 0x801C
    /* 0x800BEF64 */ ctx.r[25] = 0x801C0000u; // lis r25, 0x801C
    /* 0x800BEF68 */ mem.write_f32(ctx.r[1] + (28), static_cast<float>(ctx.f[13])); // stfs f13, 28(r1)
    /* 0x800BEF6C */ ctx.f[0] = mem.read_f32(ctx.r[30] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r30)
    /* 0x800BEF70 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BEF74 */ SearchLightInit_800CA8A4(ctx, mem); // bl 0x800CA8A4 <SearchLightInit(tagSLIGHT *, cObj *, cVec &, unsigned long, unsigned char, tagSLIGHT *)>
    /* 0x800BEF78 */ ctx.r[4] = 0x00000004u; // li r4, 4
    /* 0x800BEF7C */ ctx.r[3] = ctx.r[29] + (19508); // addi r3, r29, 19508 -> SLight
    /* 0x800BEF80 */ SearchLightSetType_800CB13C(ctx, mem); // bl 0x800CB13C <SearchLightSetType(tagSLIGHT *, unsigned long)>
    /* 0x800BEF84 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BEF88 */ SmdGetObjPtr_800C33C8(ctx, mem); // bl 0x800C33C8 <SmdGetObjPtr(long)>
    /* 0x800BEF8C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BEF90 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[31])); // stfs f31, 24(r1)
    /* 0x800BEF94 */ ctx.f[30] = mem.read_f32(ctx.r[9] + (-11624)); ctx.ps0[30] = static_cast<float>(ctx.f[30]); // lfs f30, -11624(r9) [0x8016D298]
    /* 0x800BEF98 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800BEF9C */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r1)
    /* 0x800BEFA0 */ ctx.r[8] = ctx.r[29] + (19508); // addi r8, r29, 19508 -> SLight
    /* 0x800BEFA4 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[29])); // stfs f29, 12(r1)
    /* 0x800BEFA8 */ ctx.r[5] = ctx.r[28]; // mr r5, r28
    /* 0x800BEFAC */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[30])); // stfs f30, 16(r1)
    /* 0x800BEFB0 */ ctx.r[6] = 0x00000001u; // li r6, 1
    /* 0x800BEFB4 */ ctx.r[7] = 0x00000010u; // li r7, 16
    /* 0x800BEFB8 */ ctx.r[3] = ctx.r[27] + (19564); // addi r3, r27, 19564 -> 0x801C4C6C
    /* 0x800BEFBC */ ctx.f[13] = mem.read_f32(ctx.r[30] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r30)
    /* 0x800BEFC0 */ mem.write_f32(ctx.r[1] + (28), static_cast<float>(ctx.f[13])); // stfs f13, 28(r1)
    /* 0x800BEFC4 */ ctx.f[0] = mem.read_f32(ctx.r[30] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r30)
    /* 0x800BEFC8 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BEFCC */ SearchLightInit_800CA8A4(ctx, mem); // bl 0x800CA8A4 <SearchLightInit(tagSLIGHT *, cObj *, cVec &, unsigned long, unsigned char, tagSLIGHT *)>
    /* 0x800BEFD0 */ ctx.r[4] = 0x00000004u; // li r4, 4
    /* 0x800BEFD4 */ ctx.r[3] = ctx.r[27] + (19564); // addi r3, r27, 19564 -> 0x801C4C6C
    /* 0x800BEFD8 */ SearchLightSetType_800CB13C(ctx, mem); // bl 0x800CB13C <SearchLightSetType(tagSLIGHT *, unsigned long)>
    /* 0x800BEFDC */ ctx.r[3] = 0x00000002u; // li r3, 2
    /* 0x800BEFE0 */ SmdGetObjPtr_800C33C8(ctx, mem); // bl 0x800C33C8 <SmdGetObjPtr(long)>
    /* 0x800BEFE4 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BEFE8 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BEFEC */ ctx.f[31] = mem.read_f32(ctx.r[9] + (-11620)); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // lfs f31, -11620(r9) [0x8016D29C]
    /* 0x800BEFF0 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800BEFF4 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-11616)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11616(r11) [0x8016D2A0]
    /* 0x800BEFF8 */ ctx.r[3] = ctx.r[26] + (19620); // addi r3, r26, 19620 -> 0x801C4CA4
    /* 0x800BEFFC */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[30])); // stfs f30, 16(r1)
    /* 0x800BF000 */ ctx.r[8] = ctx.r[3] + (56); // addi r8, r3, 56
    /* 0x800BF004 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[0])); // stfs f0, 12(r1)
    /* 0x800BF008 */ ctx.r[5] = ctx.r[28]; // mr r5, r28
    /* 0x800BF00C */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r1)
    /* 0x800BF010 */ ctx.r[6] = 0x00000001u; // li r6, 1
    /* 0x800BF014 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[31])); // stfs f31, 24(r1)
    /* 0x800BF018 */ ctx.r[7] = 0x00000012u; // li r7, 18
    /* 0x800BF01C */ ctx.f[0] = mem.read_f32(ctx.r[30] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r30)
    /* 0x800BF020 */ mem.write_f32(ctx.r[1] + (28), static_cast<float>(ctx.f[0])); // stfs f0, 28(r1)
    /* 0x800BF024 */ ctx.f[13] = mem.read_f32(ctx.r[30] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r30)
    /* 0x800BF028 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[13])); // stfs f13, 32(r1)
    /* 0x800BF02C */ SearchLightInit_800CA8A4(ctx, mem); // bl 0x800CA8A4 <SearchLightInit(tagSLIGHT *, cObj *, cVec &, unsigned long, unsigned char, tagSLIGHT *)>
    /* 0x800BF030 */ ctx.r[3] = 0x00000003u; // li r3, 3
    /* 0x800BF034 */ SmdGetObjPtr_800C33C8(ctx, mem); // bl 0x800C33C8 <SmdGetObjPtr(long)>
    /* 0x800BF038 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BF03C */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[28])); // stfs f28, 16(r1)
    /* 0x800BF040 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11612)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11612(r9) [0x8016D2A4]
    /* 0x800BF044 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800BF048 */ mem.write_f32(ctx.r[1] + (24), static_cast<float>(ctx.f[31])); // stfs f31, 24(r1)
    /* 0x800BF04C */ ctx.r[3] = ctx.r[25] + (19676); // addi r3, r25, 19676 -> 0x801C4CDC
    /* 0x800BF050 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[0])); // stfs f0, 12(r1)
    /* 0x800BF054 */ ctx.r[5] = ctx.r[28]; // mr r5, r28
    /* 0x800BF058 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r1)
    /* 0x800BF05C */ ctx.r[8] = ctx.r[26] + (19620); // addi r8, r26, 19620 -> 0x801C4CA4
    /* 0x800BF060 */ ctx.r[6] = 0x00000001u; // li r6, 1
    /* 0x800BF064 */ ctx.r[7] = 0x00000012u; // li r7, 18
    /* 0x800BF068 */ ctx.f[13] = mem.read_f32(ctx.r[30] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r30)
    /* 0x800BF06C */ mem.write_f32(ctx.r[1] + (28), static_cast<float>(ctx.f[13])); // stfs f13, 28(r1)
    /* 0x800BF070 */ ctx.f[0] = mem.read_f32(ctx.r[30] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r30)
    /* 0x800BF074 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BF078 */ SearchLightInit_800CA8A4(ctx, mem); // bl 0x800CA8A4 <SearchLightInit(tagSLIGHT *, cObj *, cVec &, unsigned long, unsigned char, tagSLIGHT *)>
    /* 0x800BF07C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BF080 */ room_barrier_800B94FC(ctx, mem); // bl 0x800B94FC <room_barrier(long)>
    /* 0x800BF084 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (108)); // lwz r0, 108(r1)
    /* 0x800BF088 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BF08C */ ctx.lmw(mem, 25, ctx.r[1] + (44)); // lmw r25, 44(r1)
    /* 0x800BF090 */ ctx.f[28] = mem.read_f64(ctx.r[1] + (72)); // lfd f28, 72(r1)
    /* 0x800BF094 */ ctx.f[29] = mem.read_f64(ctx.r[1] + (80)); // lfd f29, 80(r1)
    /* 0x800BF098 */ ctx.f[30] = mem.read_f64(ctx.r[1] + (88)); // lfd f30, 88(r1)
    /* 0x800BF09C */ ctx.f[31] = mem.read_f64(ctx.r[1] + (96)); // lfd f31, 96(r1)
    /* 0x800BF0A0 */ ctx.r[1] = ctx.r[1] + (104); // addi r1, r1, 104
    /* 0x800BF0A4 */ return; // blr
}

// [0x800BF0A8] Rb00Main(void) (rb00.obj, 19 insns / 0x4C bytes)
void Rb00Main_800BF0A8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BF0A8 */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800BF0AC */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BF0B0 */ ctx.stmw(mem, 30, ctx.r[1] + (8)); // stmw r30, 8(r1)
    /* 0x800BF0B4 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800BF0B8 */ ctx.r[9] = 0x801C0000u; // lis r9, 0x801C
    /* 0x800BF0BC */ ctx.r[31] = ctx.r[9] + (19508); // addi r31, r9, 19508 -> SLight
    /* 0x800BF0C0 */ ctx.r[30] = ctx.r[31] + (168); // addi r30, r31, 168
loc_800BF0C4:;
    /* 0x800BF0C4 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800BF0C8 */ SearchLightMain_800CA9A0(ctx, mem); // bl 0x800CA9A0 <SearchLightMain(tagSLIGHT *)>
    /* 0x800BF0CC */ ctx.r[31] = ctx.r[31] + (56); // addi r31, r31, 56
    /* 0x800BF0D0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), static_cast<int32_t>(ctx.r[30])); // cmpw cr0, r31, r30
    /* 0x800BF0D4 */ if (ctx.eval_bc(4, 1)) goto loc_800BF0C4; // bc 4, 1, 0x800BF0C4
    /* 0x800BF0D8 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BF0DC */ room_barrier_800B94FC(ctx, mem); // bl 0x800B94FC <room_barrier(long)>
    /* 0x800BF0E0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800BF0E4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BF0E8 */ ctx.lmw(mem, 30, ctx.r[1] + (8)); // lmw r30, 8(r1)
    /* 0x800BF0EC */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800BF0F0 */ return; // blr
}

// [0x800BF0F4] Rb04Init(void) (rb04.obj, 59 insns / 0xEC bytes)
void Rb04Init_800BF0F4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BF0F4 */ ctx.r[1] += (-64); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -64(r1)
    /* 0x800BF0F8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BF0FC */ ctx.stmw(mem, 29, ctx.r[1] + (52)); // stmw r29, 52(r1)
    /* 0x800BF100 */ mem.write_u32(ctx.r[1] + (68), ctx.r[0]); // stw r0, 68(r1)
    /* 0x800BF104 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BF108 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BF10C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11588)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11588(r9) [0x8016D2BC]
    /* 0x800BF110 */ ctx.r[11] = ctx.r[1] + (16); // addi r11, r1, 16
    /* 0x800BF114 */ ctx.r[9] = mem.read_u32(ctx.r[10] + (272)); // lwz r9, 272(r10)
    /* 0x800BF118 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BF11C */ ctx.r[10] = ctx.r[1] + (32); // addi r10, r1, 32
    /* 0x800BF120 */ ctx.r[29] = 0x00000000u; // li r29, 0
    /* 0x800BF124 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (64)); // lwz r3, 64(r9)
    /* 0x800BF128 */ ctx.r[5] = ctx.r[11]; // mr r5, r11
    /* 0x800BF12C */ ctx.r[4] = mem.read_u32(ctx.r[9] + (68)); // lwz r4, 68(r9)
    /* 0x800BF130 */ ctx.r[6] = ctx.r[10]; // mr r6, r10
    /* 0x800BF134 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BF138 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BF13C */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800BF140 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BF144 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BF148 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BF14C */ mem.write_u32(ctx.r[13] + (-29480), ctx.r[0]); // stw r0, -29480(r13) [str_req]
    /* 0x800BF150 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800BF154 */ mem.write_u32(ctx.r[13] + (-29496), ctx.r[29]); // stw r29, -29496(r13) [pEvent17]
    /* 0x800BF158 */ mem.write_u32(ctx.r[13] + (-29492), ctx.r[29]); // stw r29, -29492(r13) [pEvent18]
    /* 0x800BF15C */ mem.write_u32(ctx.r[13] + (-29488), ctx.r[29]); // stw r29, -29488(r13) [pEvent19]
    /* 0x800BF160 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800BF164 */ SetObj00_800A7C90(ctx, mem); // bl 0x800A7C90 <SetObj00(unsigned long, unsigned long, cVec &, cVec &)>
    /* 0x800BF168 */ ctx.r[31] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // mr r31, r3
    /* 0x800BF16C */ if (ctx.eval_bc(12, 2)) goto loc_800BF1CC; // bc 12, 2, 0x800BF1CC
    /* 0x800BF170 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BF174 */ ctx.r[5] = 0x00000004u; // li r5, 4
    /* 0x800BF178 */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800BF17C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BF180 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (72)); // lwz r4, 72(r9)
    /* 0x800BF184 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BF188 */ cObj00__MotSetObj00_800A7C54(ctx, mem); // bl 0x800A7C54 <cObj00::MotSetObj00(void *, unsigned long)>
    /* 0x800BF18C */ ctx.r[4] = 0x00000009u; // li r4, 9
    /* 0x800BF190 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BF194 */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BF198 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BF19C */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BF1A0 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BF1A4 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BF1A8 */ mem.write_u32(ctx.r[1] + (8), ctx.r[29]); // stw r29, 8(r1)
    /* 0x800BF1AC */ ctx.r[3] = ctx.r[31]; // mr r3, r31
    /* 0x800BF1B0 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BF1B4 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BF1B8 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BF1BC */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800BF1C0 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800BF1C4 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BF1C8 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
loc_800BF1CC:;
    /* 0x800BF1CC */ ctx.r[0] = mem.read_u32(ctx.r[1] + (68)); // lwz r0, 68(r1)
    /* 0x800BF1D0 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BF1D4 */ ctx.lmw(mem, 29, ctx.r[1] + (52)); // lmw r29, 52(r1)
    /* 0x800BF1D8 */ ctx.r[1] = ctx.r[1] + (64); // addi r1, r1, 64
    /* 0x800BF1DC */ return; // blr
}

// [0x800BF1E0] Rb04Main(void) (rb04.obj, 286 insns / 0x478 bytes)
void Rb04Main_800BF1E0(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800BF1E0 */ ctx.r[1] += (-112); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -112(r1)
    /* 0x800BF1E4 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800BF1E8 */ ctx.stmw(mem, 29, ctx.r[1] + (100)); // stmw r29, 100(r1)
    /* 0x800BF1EC */ mem.write_u32(ctx.r[1] + (116), ctx.r[0]); // stw r0, 116(r1)
    /* 0x800BF1F0 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BF1F4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (29012)); // lwz r9, 29012(r11)
    /* 0x800BF1F8 */ ctx.r[31] = ctx.r[9] & 0x4000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // andi. r31, r9, 0x4000
    /* 0x800BF1FC */ if (ctx.eval_bc(4, 2)) goto loc_800BF324; // bc 4, 2, 0x800BF324
    /* 0x800BF200 */ ctx.r[0] = mem.read_u32(ctx.r[11] + (340)); // lwz r0, 340(r11)
    /* 0x800BF204 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BF208 */ if (ctx.eval_bc(4, 0)) goto loc_800BF324; // bc 4, 0, 0x800BF324
    /* 0x800BF20C */ ctx.r[0] = ctx.r[9] | 0x4000u; // ori r0, r9, 0x4000
    /* 0x800BF210 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BF214 */ mem.write_u32(ctx.r[11] + (29012), ctx.r[0]); // stw r0, 29012(r11)
    /* 0x800BF218 */ ctx.r[29] = ctx.r[13] + (-29481); // addi r29, r13, -29481 -> sda1_0x8026E8B7
    /* 0x800BF21C */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BF220 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BF224 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BF228 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BF22C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BF230 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BF234 */ mem.write_u32(ctx.r[13] + (-29496), ctx.r[0]); // stw r0, -29496(r13) [pEvent17]
    /* 0x800BF238 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (44)); // lwz r4, 44(r9)
    /* 0x800BF23C */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BF240 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BF244 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BF248 */ ctx.r[11] = ctx.r[1] + (16); // addi r11, r1, 16
    /* 0x800BF24C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11584)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11584(r9) [0x8016D2C0]
    /* 0x800BF250 */ ctx.r[10] = ctx.r[1] + (32); // addi r10, r1, 32
    /* 0x800BF254 */ ctx.r[8] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r8, -29836(r13) [pG]
    /* 0x800BF258 */ ctx.r[5] = ctx.r[11]; // mr r5, r11
    /* 0x800BF25C */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800BF260 */ ctx.r[6] = ctx.r[10]; // mr r6, r10
    /* 0x800BF264 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800BF268 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BF26C */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800BF270 */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[0])); // stfs f0, 32(r1)
    /* 0x800BF274 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800BF278 */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800BF27C */ ctx.r[9] = mem.read_u32(ctx.r[8] + (272)); // lwz r9, 272(r8)
    /* 0x800BF280 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (76)); // lwz r3, 76(r9)
    /* 0x800BF284 */ ctx.r[3] = ctx.r[3] + ctx.r[9]; // add r3, r3, r9
    /* 0x800BF288 */ ScrAtAdd_800063D4(ctx, mem); // bl 0x800063D4 <ScrAtAdd(unsigned long, unsigned long, Vec *, Vec *)>
    /* 0x800BF28C */ EspPullCoreKind_80084BA0(ctx, mem); // bl 0x80084BA0 <EspPullCoreKind(void)>
    /* 0x800BF290 */ mem.write_u32(ctx.r[13] + (-29484), ctx.r[3]); // stw r3, -29484(r13) [eff_barrier]
    /* 0x800BF294 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BF298 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BF29C */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BF2A0 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BF2A4 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BF2A8 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BF2AC */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BF2B0 */ ctx.r[9] = mem.read_u8(ctx.r[29] + (0)); // lbz r9, 0(r29)
    /* 0x800BF2B4 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BF2B8 */ mem.write_u32(ctx.r[1] + (8), ctx.r[31]); // stw r31, 8(r1)
    /* 0x800BF2BC */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BF2C0 */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800BF2C4 */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BF2C8 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BF2CC */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BF2D0 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800BF2D4 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800BF2D8 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BF2DC */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800BF2E0 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800BF2E4 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800BF2E8 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800BF2EC */ ctx.r[9] = mem.read_u8(ctx.r[29] + (0)); // lbz r9, 0(r29)
    /* 0x800BF2F0 */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800BF2F4 */ mem.write_u32(ctx.r[1] + (8), ctx.r[31]); // stw r31, 8(r1)
    /* 0x800BF2F8 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800BF2FC */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BF300 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800BF304 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BF308 */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800BF30C */ ctx.r[10] = 0x00000000u; // li r10, 0
    /* 0x800BF310 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800BF314 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BF318 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BF31C */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BF320 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
loc_800BF324:;
    /* 0x800BF324 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29496)); // lwz r3, -29496(r13) [pEvent17]
    /* 0x800BF328 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BF32C */ if (ctx.eval_bc(12, 2)) goto loc_800BF3FC; // bc 12, 2, 0x800BF3FC
    /* 0x800BF330 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BF334 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BF338 */ if (ctx.eval_bc(12, 2)) goto loc_800BF618; // bc 12, 2, 0x800BF618
    /* 0x800BF33C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29496)); // lwz r11, -29496(r13) [pEvent17]
    /* 0x800BF340 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BF344 */ if (ctx.eval_bc(12, 2)) goto loc_800BF364; // bc 12, 2, 0x800BF364
    /* 0x800BF348 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BF34C */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BF350 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BF354 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BF358 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BF35C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BF360 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BF364:;
    /* 0x800BF364 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BF368 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BF36C */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-11584)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11584(r9) [0x8016D2C0]
    /* 0x800BF370 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BF374 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-11580)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11580(r11) [0x8016D2C4]
    /* 0x800BF378 */ ctx.r[8] = ctx.r[1] + (16); // addi r8, r1, 16
    /* 0x800BF37C */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800BF380 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BF384 */ ctx.f[12] = mem.read_f32(ctx.r[10] + (-11576)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -11576(r10) [0x8016D2C8]
    /* 0x800BF388 */ ctx.r[7] = ctx.r[1] + (48); // addi r7, r1, 48
    /* 0x800BF38C */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800BF390 */ ctx.r[30] = 0x00000000u; // li r30, 0
    /* 0x800BF394 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r8)
    /* 0x800BF398 */ ctx.r[10] = ctx.r[1] + (64); // addi r10, r1, 64
    /* 0x800BF39C */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11572)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11572(r9) [0x8016D2CC]
    /* 0x800BF3A0 */ ctx.r[6] = ctx.r[1] + (80); // addi r6, r1, 80
    /* 0x800BF3A4 */ mem.write_f32(ctx.r[1] + (48), static_cast<float>(ctx.f[13])); // stfs f13, 48(r1)
    /* 0x800BF3A8 */ ctx.r[3] = ctx.r[10]; // mr r3, r10
    /* 0x800BF3AC */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800BF3B0 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BF3B4 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r7)
    /* 0x800BF3B8 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BF3BC */ mem.write_u32(ctx.r[13] + (-29496), ctx.r[30]); // stw r30, -29496(r13) [pEvent17]
    /* 0x800BF3C0 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (16)); // lwz r9, 16(r1)
    /* 0x800BF3C4 */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BF3C8 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BF3CC */ mem.write_u32(ctx.r[1] + (64), ctx.r[9]); // stw r9, 64(r1)
    /* 0x800BF3D0 */ mem.write_u32(ctx.r[10] + (4), ctx.r[0]); // stw r0, 4(r10)
    /* 0x800BF3D4 */ mem.write_u32(ctx.r[10] + (8), ctx.r[11]); // stw r11, 8(r10)
    /* 0x800BF3D8 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (48)); // lwz r9, 48(r1)
    /* 0x800BF3DC */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BF3E0 */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BF3E4 */ mem.write_u32(ctx.r[1] + (80), ctx.r[9]); // stw r9, 80(r1)
    /* 0x800BF3E8 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BF3EC */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BF3F0 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BF3F4 */ mem.write_u32(ctx.r[13] + (-29480), ctx.r[30]); // stw r30, -29480(r13) [str_req]
    /* 0x800BF3F8 */ goto loc_800BF618; // b 0x800BF618 <sub_800BF618>
loc_800BF3FC:;
    /* 0x800BF3FC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BF400 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BF404 */ ctx.r[0] = ctx.r[11] & 0x2000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andi. r0, r11, 0x2000
    /* 0x800BF408 */ if (ctx.eval_bc(4, 2)) goto loc_800BF45C; // bc 4, 2, 0x800BF45C
    /* 0x800BF40C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BF410 */ ctx.r[10] = ctx.r[0] & 0x40000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r0, 0x4000
    /* 0x800BF414 */ if (ctx.eval_bc(12, 2)) goto loc_800BF45C; // bc 12, 2, 0x800BF45C
    /* 0x800BF418 */ ctx.r[0] = ctx.r[11] | 0x2000u; // ori r0, r11, 0x2000
    /* 0x800BF41C */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BF420 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BF424 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BF428 */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BF42C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BF430 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BF434 */ mem.write_u32(ctx.r[13] + (-29492), ctx.r[0]); // stw r0, -29492(r13) [pEvent18]
    /* 0x800BF438 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BF43C */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BF440 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (48)); // lwz r4, 48(r9)
    /* 0x800BF444 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BF448 */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
    /* 0x800BF44C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BF450 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (328)); // lwz r0, 328(r9)
    /* 0x800BF454 */ ctx.rlwinm(0, 0, 0u, 0u, 30u, false); // rlwinm r0, r0, 0, 0, 30
    /* 0x800BF458 */ mem.write_u32(ctx.r[9] + (328), ctx.r[0]); // stw r0, 328(r9)
loc_800BF45C:;
    /* 0x800BF45C */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29492)); // lwz r3, -29492(r13) [pEvent18]
    /* 0x800BF460 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BF464 */ if (ctx.eval_bc(12, 2)) goto loc_800BF530; // bc 12, 2, 0x800BF530
    /* 0x800BF468 */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BF46C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BF470 */ if (ctx.eval_bc(12, 2)) goto loc_800BF618; // bc 12, 2, 0x800BF618
    /* 0x800BF474 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29492)); // lwz r11, -29492(r13) [pEvent18]
    /* 0x800BF478 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BF47C */ if (ctx.eval_bc(12, 2)) goto loc_800BF49C; // bc 12, 2, 0x800BF49C
    /* 0x800BF480 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BF484 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BF488 */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BF48C */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BF490 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BF494 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BF498 */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BF49C:;
    /* 0x800BF49C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BF4A0 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800BF4A4 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (-11584)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, -11584(r9) [0x8016D2C0]
    /* 0x800BF4A8 */ ctx.r[10] = 0x80170000u; // lis r10, 0x8017
    /* 0x800BF4AC */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-11580)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11580(r11) [0x8016D2C4]
    /* 0x800BF4B0 */ ctx.r[8] = ctx.r[1] + (16); // addi r8, r1, 16
    /* 0x800BF4B4 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[13])); // stfs f13, 16(r1)
    /* 0x800BF4B8 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800BF4BC */ ctx.f[12] = mem.read_f32(ctx.r[10] + (-11576)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, -11576(r10) [0x8016D2C8]
    /* 0x800BF4C0 */ ctx.r[7] = ctx.r[1] + (32); // addi r7, r1, 32
    /* 0x800BF4C4 */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800BF4C8 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800BF4CC */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[12])); // stfs f12, 8(r8)
    /* 0x800BF4D0 */ ctx.r[10] = ctx.r[1] + (48); // addi r10, r1, 48
    /* 0x800BF4D4 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-11572)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -11572(r9) [0x8016D2CC]
    /* 0x800BF4D8 */ ctx.r[6] = ctx.r[1] + (64); // addi r6, r1, 64
    /* 0x800BF4DC */ mem.write_f32(ctx.r[1] + (32), static_cast<float>(ctx.f[13])); // stfs f13, 32(r1)
    /* 0x800BF4E0 */ ctx.r[3] = ctx.r[10]; // mr r3, r10
    /* 0x800BF4E4 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800BF4E8 */ ctx.r[4] = ctx.r[6]; // mr r4, r6
    /* 0x800BF4EC */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[13])); // stfs f13, 8(r7)
    /* 0x800BF4F0 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BF4F4 */ mem.write_u32(ctx.r[13] + (-29492), ctx.r[0]); // stw r0, -29492(r13) [pEvent18]
    /* 0x800BF4F8 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (16)); // lwz r9, 16(r1)
    /* 0x800BF4FC */ ctx.r[11] = mem.read_u32(ctx.r[8] + (8)); // lwz r11, 8(r8)
    /* 0x800BF500 */ ctx.r[0] = mem.read_u32(ctx.r[8] + (4)); // lwz r0, 4(r8)
    /* 0x800BF504 */ mem.write_u32(ctx.r[1] + (48), ctx.r[9]); // stw r9, 48(r1)
    /* 0x800BF508 */ mem.write_u32(ctx.r[10] + (4), ctx.r[0]); // stw r0, 4(r10)
    /* 0x800BF50C */ mem.write_u32(ctx.r[10] + (8), ctx.r[11]); // stw r11, 8(r10)
    /* 0x800BF510 */ ctx.r[9] = mem.read_u32(ctx.r[1] + (32)); // lwz r9, 32(r1)
    /* 0x800BF514 */ ctx.r[11] = mem.read_u32(ctx.r[7] + (8)); // lwz r11, 8(r7)
    /* 0x800BF518 */ ctx.r[0] = mem.read_u32(ctx.r[7] + (4)); // lwz r0, 4(r7)
    /* 0x800BF51C */ mem.write_u32(ctx.r[1] + (64), ctx.r[9]); // stw r9, 64(r1)
    /* 0x800BF520 */ mem.write_u32(ctx.r[6] + (4), ctx.r[0]); // stw r0, 4(r6)
    /* 0x800BF524 */ mem.write_u32(ctx.r[6] + (8), ctx.r[11]); // stw r11, 8(r6)
    /* 0x800BF528 */ PlFootworkSet_800AF368(ctx, mem); // bl 0x800AF368 <PlFootworkSet(cVec, cVec, unsigned long)>
    /* 0x800BF52C */ goto loc_800BF618; // b 0x800BF618 <sub_800BF618>
loc_800BF530:;
    /* 0x800BF530 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BF534 */ ctx.r[11] = mem.read_u32(ctx.r[9] + (29012)); // lwz r11, 29012(r9)
    /* 0x800BF538 */ ctx.r[0] = ctx.r[11] & 0x1000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // andi. r0, r11, 0x1000
    /* 0x800BF53C */ if (ctx.eval_bc(4, 2)) goto loc_800BF580; // bc 4, 2, 0x800BF580
    /* 0x800BF540 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (340)); // lwz r0, 340(r9)
    /* 0x800BF544 */ ctx.r[10] = ctx.r[0] & 0x20000000u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[10]), 0); // andis. r10, r0, 0x2000
    /* 0x800BF548 */ if (ctx.eval_bc(12, 2)) goto loc_800BF580; // bc 12, 2, 0x800BF580
    /* 0x800BF54C */ ctx.r[0] = ctx.r[11] | 0x1000u; // ori r0, r11, 0x1000
    /* 0x800BF550 */ ctx.r[3] = 0x00000014u; // li r3, 20
    /* 0x800BF554 */ mem.write_u32(ctx.r[9] + (29012), ctx.r[0]); // stw r0, 29012(r9)
    /* 0x800BF558 */ builtin_new_8009C8C8(ctx, mem); // bl 0x8009C8C8 <__builtin_new>
    /* 0x800BF55C */ cEvent__cEvent_80070D04(ctx, mem); // bl 0x80070D04 <cEvent::cEvent(void)>
    /* 0x800BF560 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BF564 */ ctx.r[0] = ctx.r[3]; // mr r0, r3
    /* 0x800BF568 */ mem.write_u32(ctx.r[13] + (-29488), ctx.r[0]); // stw r0, -29488(r13) [pEvent19]
    /* 0x800BF56C */ ctx.r[9] = mem.read_u32(ctx.r[11] + (272)); // lwz r9, 272(r11)
    /* 0x800BF570 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800BF574 */ ctx.r[4] = mem.read_u32(ctx.r[9] + (52)); // lwz r4, 52(r9)
    /* 0x800BF578 */ ctx.r[4] = ctx.r[4] + ctx.r[9]; // add r4, r4, r9
    /* 0x800BF57C */ cEvent__Initialize_80070DDC(ctx, mem); // bl 0x80070DDC <cEvent::Initialize(unsigned long, bool)>
loc_800BF580:;
    /* 0x800BF580 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29488)); // lwz r3, -29488(r13) [pEvent19]
    /* 0x800BF584 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BF588 */ if (ctx.eval_bc(12, 2)) goto loc_800BF618; // bc 12, 2, 0x800BF618
    /* 0x800BF58C */ cEvent__Move_80070E2C(ctx, mem); // bl 0x80070E2C <cEvent::Move(void)>
    /* 0x800BF590 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800BF594 */ if (ctx.eval_bc(12, 2)) goto loc_800BF618; // bc 12, 2, 0x800BF618
    /* 0x800BF598 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29488)); // lwz r11, -29488(r13) [pEvent19]
    /* 0x800BF59C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), 0); // cmpwi cr0, r11, 0
    /* 0x800BF5A0 */ if (ctx.eval_bc(12, 2)) goto loc_800BF5C0; // bc 12, 2, 0x800BF5C0
    /* 0x800BF5A4 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (16)); // lwz r9, 16(r11)
    /* 0x800BF5A8 */ ctx.r[4] = 0x00000003u; // li r4, 3
    /* 0x800BF5AC */ ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16(ctx.r[9] + (8)))); // lha r3, 8(r9)
    /* 0x800BF5B0 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (12)); // lwz r0, 12(r9)
    /* 0x800BF5B4 */ ctx.r[3] = ctx.r[11] + ctx.r[3]; // add r3, r11, r3
    /* 0x800BF5B8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BF5BC */ ctx.call_indirect(ctx.lr, mem); // blrl
loc_800BF5C0:;
    /* 0x800BF5C0 */ ctx.r[30] = 0x00000000u; // li r30, 0
    /* 0x800BF5C4 */ ctx.r[3] = 0x80180000u; // lis r3, 0x8018
    /* 0x800BF5C8 */ ctx.r[3] = ctx.r[3] + (30404); // addi r3, r3, 30404 -> Combo
    /* 0x800BF5CC */ mem.write_u32(ctx.r[13] + (-29488), ctx.r[30]); // stw r30, -29488(r13) [pEvent19]
    /* 0x800BF5D0 */ ctx.r[4] = 0x00000045u; // li r4, 69
    /* 0x800BF5D4 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800BF5D8 */ cCombo__BossPts_80020D8C(ctx, mem); // bl 0x80020D8C <cCombo::BossPts(unsigned char, unsigned long)>
    /* 0x800BF5DC */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BF5E0 */ ctx.r[0] = 0x00000004u; // li r0, 4
    /* 0x800BF5E4 */ mem.write_u8(ctx.r[11] + (260), static_cast<uint8_t>(ctx.r[0])); // stb r0, 260(r11)
    /* 0x800BF5E8 */ ctx.r[9] = mem.read_u32(ctx.r[11] + (336)); // lwz r9, 336(r11)
    /* 0x800BF5EC */ ctx.r[0] = mem.read_u32(ctx.r[11] + (328)); // lwz r0, 328(r11)
    /* 0x800BF5F0 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r10, -29836(r13) [pG]
    /* 0x800BF5F4 */ ctx.r[9] = ctx.r[9] | 0x20000000u; // oris r9, r9, 0x2000
    /* 0x800BF5F8 */ ctx.r[0] = ctx.r[0] | 0x0008u; // ori r0, r0, 0x0008
    /* 0x800BF5FC */ mem.write_u32(ctx.r[11] + (336), ctx.r[9]); // stw r9, 336(r11)
    /* 0x800BF600 */ mem.write_u32(ctx.r[11] + (328), ctx.r[0]); // stw r0, 328(r11)
    /* 0x800BF604 */ mem.write_u8(ctx.r[10] + (261), static_cast<uint8_t>(ctx.r[30])); // stb r30, 261(r10)
    /* 0x800BF608 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800BF60C */ mem.write_u8(ctx.r[9] + (262), static_cast<uint8_t>(ctx.r[30])); // stb r30, 262(r9)
    /* 0x800BF610 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800BF614 */ mem.write_u8(ctx.r[11] + (263), static_cast<uint8_t>(ctx.r[30])); // stb r30, 263(r11)
loc_800BF618:;
    /* 0x800BF618 */ ctx.r[0] = mem.read_u32(ctx.r[13] + (-29480)); // lwz r0, -29480(r13) [str_req]
    /* 0x800BF61C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800BF620 */ if (ctx.eval_bc(4, 2)) goto loc_800BF644; // bc 4, 2, 0x800BF644
    /* 0x800BF624 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800BF628 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800BF62C */ mem.write_u32(ctx.r[13] + (-29480), ctx.r[0]); // stw r0, -29480(r13) [str_req]
    /* 0x800BF630 */ ctx.r[4] = 0xFFFFFFFFu; // li r4, -1
    /* 0x800BF634 */ ctx.r[5] = 0x00000002u; // li r5, 2
    /* 0x800BF638 */ ctx.r[6] = 0x00000000u; // li r6, 0
    /* 0x800BF63C */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800BF640 */ SndStmReq_800CBC70(ctx, mem); // bl 0x800CBC70 <SndStmReq(long, long, long, long, long)>
loc_800BF644:;
    /* 0x800BF644 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (116)); // lwz r0, 116(r1)
    /* 0x800BF648 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800BF64C */ ctx.lmw(mem, 29, ctx.r[1] + (100)); // lmw r29, 100(r1)
    /* 0x800BF650 */ ctx.r[1] = ctx.r[1] + (112); // addi r1, r1, 112
    /* 0x800BF654 */ return; // blr
}

// [0x800C0A28] GetNextPos(unsigned char, unsigned char) (room_jmp.obj, 33 insns / 0x84 bytes)
void GetNextPos_800C0A28(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800C0A28 */ ctx.r[10] = static_cast<uint32_t>(static_cast<int32_t>(ctx.r[4]) * (24)); // mulli r10, r4, 24
    /* 0x800C0A2C */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800C0A30 */ ctx.rlwinm(0, 3, 3u, 0u, 28u, false); // rlwinm r0, r3, 3, 0, 28
    /* 0x800C0A34 */ ctx.r[9] = ctx.r[9] + (28396); // addi r9, r9, 28396 -> Room_jump_tbl
    /* 0x800C0A38 */ ctx.r[11] = mem.read_u32(ctx.r[9] + ctx.r[0]); // lwzx r11, r9, r0
    /* 0x800C0A3C */ ctx.r[0] = mem.read_u8(ctx.r[11] + ctx.r[10]); // lbzx r0, r11, r10
    /* 0x800C0A40 */ ctx.r[8] = ctx.r[11] + ctx.r[10]; // add r8, r11, r10
    /* 0x800C0A44 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 0); // cmpwi cr0, r0, 0
    /* 0x800C0A48 */ if (ctx.eval_bc(12, 2)) goto loc_800C0A74; // bc 12, 2, 0x800C0A74
    /* 0x800C0A4C */ ctx.f[0] = mem.read_f32(ctx.r[8] + (4)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 4(r8)
    /* 0x800C0A50 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800C0A54 */ mem.write_f32(ctx.r[9] + (27260), static_cast<float>(ctx.f[0])); // stfs f0, 27260(r9)
    /* 0x800C0A58 */ ctx.f[13] = mem.read_f32(ctx.r[8] + (8)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 8(r8)
    /* 0x800C0A5C */ mem.write_f32(ctx.r[9] + (27264), static_cast<float>(ctx.f[13])); // stfs f13, 27264(r9)
    /* 0x800C0A60 */ ctx.f[0] = mem.read_f32(ctx.r[8] + (12)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 12(r8)
    /* 0x800C0A64 */ mem.write_f32(ctx.r[9] + (27268), static_cast<float>(ctx.f[0])); // stfs f0, 27268(r9)
    /* 0x800C0A68 */ ctx.f[13] = mem.read_f32(ctx.r[8] + (16)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 16(r8)
    /* 0x800C0A6C */ mem.write_f32(ctx.r[9] + (27272), static_cast<float>(ctx.f[13])); // stfs f13, 27272(r9)
    /* 0x800C0A70 */ goto loc_800C0A90; // b 0x800C0A90 <sub_800C0A90>
loc_800C0A74:;
    /* 0x800C0A74 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800C0A78 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800C0A7C */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-10988)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -10988(r11) [0x8016D514]
    /* 0x800C0A80 */ mem.write_f32(ctx.r[9] + (27272), static_cast<float>(ctx.f[0])); // stfs f0, 27272(r9)
    /* 0x800C0A84 */ mem.write_f32(ctx.r[9] + (27260), static_cast<float>(ctx.f[0])); // stfs f0, 27260(r9)
    /* 0x800C0A88 */ mem.write_f32(ctx.r[9] + (27264), static_cast<float>(ctx.f[0])); // stfs f0, 27264(r9)
    /* 0x800C0A8C */ mem.write_f32(ctx.r[9] + (27268), static_cast<float>(ctx.f[0])); // stfs f0, 27268(r9)
loc_800C0A90:;
    /* 0x800C0A90 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r9, -29836(r13) [pG]
    /* 0x800C0A94 */ mem.write_u8(ctx.r[9] + (27277), static_cast<uint8_t>(ctx.r[3])); // stb r3, 27277(r9)
    /* 0x800C0A98 */ ctx.r[0] = mem.read_u16(ctx.r[9] + (27256)); // lhz r0, 27256(r9)
    /* 0x800C0A9C */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r11, -29836(r13) [pG]
    /* 0x800C0AA0 */ mem.write_u16(ctx.r[9] + (27258), static_cast<uint16_t>(ctx.r[0])); // sth r0, 27258(r9)
    /* 0x800C0AA4 */ mem.write_u8(ctx.r[11] + (27276), static_cast<uint8_t>(ctx.r[4])); // stb r4, 27276(r11)
    /* 0x800C0AA8 */ return; // blr
}

// [0x800C2EBC] SmdInit(tagSMD_HEADER *, tagSMX_HEADER *) (scroll.obj, 111 insns / 0x1BC bytes)
void SmdInit_800C2EBC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800C2EBC */ ctx.r[1] += (-16); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -16(r1)
    /* 0x800C2EC0 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800C2EC4 */ mem.write_u32(ctx.r[1] + (12), ctx.r[31]); // stw r31, 12(r1)
    /* 0x800C2EC8 */ mem.write_u32(ctx.r[1] + (20), ctx.r[0]); // stw r0, 20(r1)
    /* 0x800C2ECC */ ctx.r[31] = ctx.r[3]; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[31]), 0); // mr r31, r3
    /* 0x800C2ED0 */ if (ctx.eval_bc(4, 2)) goto loc_800C2EE0; // bc 4, 2, 0x800C2EE0
    /* 0x800C2ED4 */ mem.write_u32(ctx.r[13] + (-29464), ctx.r[31]); // stw r31, -29464(r13) [pSmd]
    /* 0x800C2ED8 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800C2EDC */ goto loc_800C3064; // b 0x800C3064 <sub_800C3064>
loc_800C2EE0:;
    /* 0x800C2EE0 */ ctx.r[0] = mem.read_u16(ctx.r[31] + (2)); // lhz r0, 2(r31)
    /* 0x800C2EE4 */ mem.write_u32(ctx.r[13] + (-29460), ctx.r[4]); // stw r4, -29460(r13) [pSmx]
    /* 0x800C2EE8 */ ctx.rlwinm(3, 0, 2u, 0u, 29u, false); // rlwinm r3, r0, 2, 0, 29
    /* 0x800C2EEC */ mem.write_u32(ctx.r[13] + (-29464), ctx.r[31]); // stw r31, -29464(r13) [pSmd]
    /* 0x800C2EF0 */ mem.write_u32(ctx.r[13] + (-29452), ctx.r[0]); // stw r0, -29452(r13) [objNum]
    /* 0x800C2EF4 */ memAlloc_8009CB2C(ctx, mem); // bl 0x8009CB2C <memAlloc(unsigned long)>
    /* 0x800C2EF8 */ mem.write_u32(ctx.r[13] + (-29456), ctx.r[3]); // stw r3, -29456(r13) [objTbl]
    /* 0x800C2EFC */ ctx.r[3] = mem.read_u8(ctx.r[31] + (0)); // lbz r3, 0(r31)
    /* 0x800C2F00 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800C2F04 */ if (ctx.eval_bc(12, 2)) goto loc_800C2F14; // bc 12, 2, 0x800C2F14
    /* 0x800C2F08 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 16); // cmpwi cr0, r3, 16
    /* 0x800C2F0C */ if (ctx.eval_bc(12, 2)) goto loc_800C2F1C; // bc 12, 2, 0x800C2F1C
    /* 0x800C2F10 */ goto loc_800C2F20; // b 0x800C2F20 <sub_800C2F20>
loc_800C2F14:;
    /* 0x800C2F14 */ setObjOld_800C3078(ctx, mem); // bl 0x800C3078 <setObjOld(void)>
    /* 0x800C2F18 */ goto loc_800C2F20; // b 0x800C2F20 <sub_800C2F20>
loc_800C2F1C:;
    /* 0x800C2F1C */ setObj_800C3204(ctx, mem); // bl 0x800C3204 <setObj(void)>
loc_800C2F20:;
    /* 0x800C2F20 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29460)); // lwz r9, -29460(r13) [pSmx]
    /* 0x800C2F24 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // cmpwi cr0, r9, 0
    /* 0x800C2F28 */ if (ctx.eval_bc(12, 2)) goto loc_800C305C; // bc 12, 2, 0x800C305C
    /* 0x800C2F2C */ ctx.r[0] = mem.read_u8(ctx.r[9] + (1)); // lbz r0, 1(r9)
    /* 0x800C2F30 */ ctx.r[7] = 0x00000000u; // li r7, 0
    /* 0x800C2F34 */ ctx.r[8] = ctx.r[9] + (16); // addi r8, r9, 16
    /* 0x800C2F38 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[7]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r7, r0
    /* 0x800C2F3C */ if (ctx.eval_bc(4, 0)) goto loc_800C305C; // bc 4, 0, 0x800C305C
    /* 0x800C2F40 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800C2F44 */ ctx.r[4] = 0x000003FFu; // li r4, 1023
    /* 0x800C2F48 */ ctx.r[5] = ctx.r[9] + (28624); // addi r5, r9, 28624 -> ScrIdRefTbl
    /* 0x800C2F4C */ ctx.r[6] = 0x00000000u; // li r6, 0
loc_800C2F50:;
    /* 0x800C2F50 */ ctx.r[9] = mem.read_u8(ctx.r[8] + (0)); // lbz r9, 0(r8)
    /* 0x800C2F54 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29456)); // lwz r10, -29456(r13) [objTbl]
    /* 0x800C2F58 */ ctx.rlwinm(9, 9, 2u, 0u, 29u, false); // rlwinm r9, r9, 2, 0, 29
    /* 0x800C2F5C */ ctx.r[11] = mem.read_u32(ctx.r[8] + (4)); // lwz r11, 4(r8)
    /* 0x800C2F60 */ ctx.r[10] = mem.read_u32(ctx.r[9] + ctx.r[10]); // lwzx r10, r9, r10
    /* 0x800C2F64 */ mem.write_u32(ctx.r[10] + (352), ctx.r[11]); // stw r11, 352(r10)
    /* 0x800C2F68 */ ctx.r[0] = mem.read_u8(ctx.r[8] + (2)); // lbz r0, 2(r8)
    /* 0x800C2F6C */ ctx.r[9] = ctx.r[0]; // mr r9, r0
    /* 0x800C2F70 */ mem.write_u8(ctx.r[10] + (295), static_cast<uint8_t>(ctx.r[0])); // stb r0, 295(r10)
    /* 0x800C2F74 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 5); // cmpwi cr0, r9, 5
    /* 0x800C2F78 */ if (ctx.eval_bc(4, 2)) goto loc_800C2F84; // bc 4, 2, 0x800C2F84
    /* 0x800C2F7C */ mem.write_u32(ctx.r[10] + (1288), ctx.r[9]); // stw r9, 1288(r10)
    /* 0x800C2F80 */ mem.write_u16(ctx.r[10] + (1292), static_cast<uint16_t>(ctx.r[4])); // sth r4, 1292(r10)
loc_800C2F84:;
    /* 0x800C2F84 */ ctx.r[9] = ctx.r[8] + (16); // addi r9, r8, 16
    /* 0x800C2F88 */ ctx.r[11] = ctx.r[10] + (1240); // addi r11, r10, 1240
    /* 0x800C2F8C */ ctx.r[0] = ctx.r[8] + (28); // addi r0, r8, 28
    /* 0x800C2F90 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[9])); // cmpw cr0, r11, r9
    /* 0x800C2F94 */ if (ctx.eval_bc(12, 2)) goto loc_800C2FB0; // bc 12, 2, 0x800C2FB0
    /* 0x800C2F98 */ ctx.f[0] = mem.read_f32(ctx.r[8] + (16)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 16(r8)
    /* 0x800C2F9C */ mem.write_f32(ctx.r[10] + (1240), static_cast<float>(ctx.f[0])); // stfs f0, 1240(r10)
    /* 0x800C2FA0 */ ctx.f[13] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r9)
    /* 0x800C2FA4 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r11)
    /* 0x800C2FA8 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r9)
    /* 0x800C2FAC */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
loc_800C2FB0:;
    /* 0x800C2FB0 */ ctx.r[11] = ctx.r[0]; // mr r11, r0
    /* 0x800C2FB4 */ ctx.r[9] = ctx.r[10] + (1252); // addi r9, r10, 1252
    /* 0x800C2FB8 */ ctx.r[0] = ctx.r[8] + (40); // addi r0, r8, 40
    /* 0x800C2FBC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), static_cast<int32_t>(ctx.r[11])); // cmpw cr0, r9, r11
    /* 0x800C2FC0 */ if (ctx.eval_bc(12, 2)) goto loc_800C2FDC; // bc 12, 2, 0x800C2FDC
    /* 0x800C2FC4 */ ctx.f[0] = mem.read_f32(ctx.r[8] + (28)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 28(r8)
    /* 0x800C2FC8 */ mem.write_f32(ctx.r[10] + (1252), static_cast<float>(ctx.f[0])); // stfs f0, 1252(r10)
    /* 0x800C2FCC */ ctx.f[13] = mem.read_f32(ctx.r[11] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r11)
    /* 0x800C2FD0 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r9)
    /* 0x800C2FD4 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r11)
    /* 0x800C2FD8 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
loc_800C2FDC:;
    /* 0x800C2FDC */ ctx.r[11] = ctx.r[0]; // mr r11, r0
    /* 0x800C2FE0 */ ctx.r[9] = ctx.r[10] + (1276); // addi r9, r10, 1276
    /* 0x800C2FE4 */ ctx.r[0] = ctx.r[8] + (52); // addi r0, r8, 52
    /* 0x800C2FE8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), static_cast<int32_t>(ctx.r[11])); // cmpw cr0, r9, r11
    /* 0x800C2FEC */ if (ctx.eval_bc(12, 2)) goto loc_800C3008; // bc 12, 2, 0x800C3008
    /* 0x800C2FF0 */ ctx.f[0] = mem.read_f32(ctx.r[8] + (40)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 40(r8)
    /* 0x800C2FF4 */ mem.write_f32(ctx.r[10] + (1276), static_cast<float>(ctx.f[0])); // stfs f0, 1276(r10)
    /* 0x800C2FF8 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r11)
    /* 0x800C2FFC */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r9)
    /* 0x800C3000 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r11)
    /* 0x800C3004 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
loc_800C3008:;
    /* 0x800C3008 */ ctx.r[11] = ctx.r[0]; // mr r11, r0
    /* 0x800C300C */ ctx.r[9] = ctx.r[10] + (1264); // addi r9, r10, 1264
    /* 0x800C3010 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), static_cast<int32_t>(ctx.r[11])); // cmpw cr0, r9, r11
    /* 0x800C3014 */ if (ctx.eval_bc(12, 2)) goto loc_800C3030; // bc 12, 2, 0x800C3030
    /* 0x800C3018 */ ctx.f[0] = mem.read_f32(ctx.r[8] + (52)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 52(r8)
    /* 0x800C301C */ mem.write_f32(ctx.r[10] + (1264), static_cast<float>(ctx.f[0])); // stfs f0, 1264(r10)
    /* 0x800C3020 */ ctx.f[13] = mem.read_f32(ctx.r[11] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r11)
    /* 0x800C3024 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r9)
    /* 0x800C3028 */ ctx.f[0] = mem.read_f32(ctx.r[11] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r11)
    /* 0x800C302C */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
loc_800C3030:;
    /* 0x800C3030 */ ctx.r[0] = mem.read_u8(ctx.r[8] + (1)); // lbz r0, 1(r8)
    /* 0x800C3034 */ ctx.r[7] = ctx.r[7] + (1); // addi r7, r7, 1
    /* 0x800C3038 */ ctx.r[8] = ctx.r[8] + (144); // addi r8, r8, 144
    /* 0x800C303C */ ctx.rlwinm(0, 0, 3u, 0u, 28u, false); // rlwinm r0, r0, 3, 0, 28
    /* 0x800C3040 */ ctx.r[11] = mem.read_u32(ctx.r[5] + ctx.r[0]); // lwzx r11, r5, r0
    /* 0x800C3044 */ mem.write_u8(ctx.r[10] + (248), static_cast<uint8_t>(ctx.r[6])); // stb r6, 248(r10)
    /* 0x800C3048 */ mem.write_u32(ctx.r[10] + (1212), ctx.r[11]); // stw r11, 1212(r10)
    /* 0x800C304C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29460)); // lwz r9, -29460(r13) [pSmx]
    /* 0x800C3050 */ ctx.r[0] = mem.read_u8(ctx.r[9] + (1)); // lbz r0, 1(r9)
    /* 0x800C3054 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[7]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r7, r0
    /* 0x800C3058 */ if (ctx.eval_bc(12, 0)) goto loc_800C2F50; // bc 12, 0, 0x800C2F50
loc_800C305C:;
    /* 0x800C305C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29464)); // lwz r9, -29464(r13) [pSmd]
    /* 0x800C3060 */ ctx.r[3] = mem.read_u16(ctx.r[9] + (2)); // lhz r3, 2(r9)
loc_800C3064:;
    /* 0x800C3064 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (20)); // lwz r0, 20(r1)
    /* 0x800C3068 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800C306C */ ctx.r[31] = mem.read_u32(ctx.r[1] + (12)); // lwz r31, 12(r1)
    /* 0x800C3070 */ ctx.r[1] = ctx.r[1] + (16); // addi r1, r1, 16
    /* 0x800C3074 */ return; // blr
}

// [0x800C3078] setObjOld(void) (scroll.obj, 99 insns / 0x18C bytes)
void setObjOld_800C3078(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800C3078 */ ctx.r[1] += (-32); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -32(r1)
    /* 0x800C307C */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800C3080 */ ctx.stmw(mem, 26, ctx.r[1] + (8)); // stmw r26, 8(r1)
    /* 0x800C3084 */ mem.write_u32(ctx.r[1] + (36), ctx.r[0]); // stw r0, 36(r1)
    /* 0x800C3088 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29464)); // lwz r10, -29464(r13) [pSmd]
    /* 0x800C308C */ ctx.r[29] = 0x00000000u; // li r29, 0
    /* 0x800C3090 */ ctx.r[0] = mem.read_u32(ctx.r[10] + (4)); // lwz r0, 4(r10)
    /* 0x800C3094 */ ctx.r[11] = mem.read_u32(ctx.r[10] + (8)); // lwz r11, 8(r10)
    /* 0x800C3098 */ ctx.r[9] = mem.read_u16(ctx.r[10] + (2)); // lhz r9, 2(r10)
    /* 0x800C309C */ ctx.r[27] = ctx.r[10] + ctx.r[0]; // add r27, r10, r0
    /* 0x800C30A0 */ ctx.r[28] = ctx.r[10] + ctx.r[11]; // add r28, r10, r11
    /* 0x800C30A4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[29]), static_cast<int32_t>(ctx.r[9])); // cmpw cr0, r29, r9
    /* 0x800C30A8 */ if (ctx.eval_bc(4, 0)) goto loc_800C31EC; // bc 4, 0, 0x800C31EC
    /* 0x800C30AC */ ctx.r[31] = ctx.r[10] + (28); // addi r31, r10, 28
    /* 0x800C30B0 */ ctx.r[26] = 0x00000000u; // li r26, 0
loc_800C30B4:;
    /* 0x800C30B4 */ ctx.r[3] = 0x00000002u; // li r3, 2
    /* 0x800C30B8 */ PullObj_80074784(ctx, mem); // bl 0x80074784 <PullObj(long)>
    /* 0x800C30BC */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800C30C0 */ ctx.r[0] = 0x00000002u; // li r0, 2
    /* 0x800C30C4 */ mem.write_u8(ctx.r[30] + (294), static_cast<uint8_t>(ctx.r[0])); // stb r0, 294(r30)
    /* 0x800C30C8 */ ctx.r[9] = mem.read_u8(ctx.r[31] + (12)); // lbz r9, 12(r31)
    /* 0x800C30CC */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 255); // cmpwi cr0, r9, 255
    /* 0x800C30D0 */ if (ctx.eval_bc(4, 2)) goto loc_800C30F0; // bc 4, 2, 0x800C30F0
    /* 0x800C30D4 */ ctx.r[5] = 0x80170000u; // lis r5, 0x8017
    /* 0x800C30D8 */ mem.write_u8(ctx.r[31] + (12), static_cast<uint8_t>(ctx.r[26])); // stb r26, 12(r31)
    /* 0x800C30DC */ ctx.r[5] = ctx.r[5] + (-9232); // addi r5, r5, -9232 -> 0x8016DBF0 /* "SmdInit() NULL BIN USED" */
    /* 0x800C30E0 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800C30E4 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800C30E8 */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800C30EC */ LogErr_8007A05C(ctx, mem); // bl 0x8007A05C <LogErr(unsigned long, unsigned long, char *,...)>
loc_800C30F0:;
    /* 0x800C30F0 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (13)); // lbz r0, 13(r31)
    /* 0x800C30F4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 255); // cmpwi cr0, r0, 255
    /* 0x800C30F8 */ if (ctx.eval_bc(4, 2)) goto loc_800C3118; // bc 4, 2, 0x800C3118
    /* 0x800C30FC */ ctx.r[5] = 0x80170000u; // lis r5, 0x8017
    /* 0x800C3100 */ mem.write_u8(ctx.r[31] + (13), static_cast<uint8_t>(ctx.r[26])); // stb r26, 13(r31)
    /* 0x800C3104 */ ctx.r[5] = ctx.r[5] + (-9208); // addi r5, r5, -9208 -> 0x8016DC08 /* "SmdInit() NULL TPL USED" */
    /* 0x800C3108 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800C310C */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800C3110 */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800C3114 */ LogErr_8007A05C(ctx, mem); // bl 0x8007A05C <LogErr(unsigned long, unsigned long, char *,...)>
loc_800C3118:;
    /* 0x800C3118 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (14)); // lbz r0, 14(r31)
    /* 0x800C311C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 255); // cmpwi cr0, r0, 255
    /* 0x800C3120 */ if (ctx.eval_bc(4, 2)) goto loc_800C3140; // bc 4, 2, 0x800C3140
    /* 0x800C3124 */ ctx.r[5] = 0x80170000u; // lis r5, 0x8017
    /* 0x800C3128 */ mem.write_u8(ctx.r[31] + (14), static_cast<uint8_t>(ctx.r[26])); // stb r26, 14(r31)
    /* 0x800C312C */ ctx.r[5] = ctx.r[5] + (-9184); // addi r5, r5, -9184 -> 0x8016DC20 /* "SmdInit() NULL MOT USED" */
    /* 0x800C3130 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800C3134 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800C3138 */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800C313C */ LogErr_8007A05C(ctx, mem); // bl 0x8007A05C <LogErr(unsigned long, unsigned long, char *,...)>
loc_800C3140:;
    /* 0x800C3140 */ ctx.r[9] = mem.read_u8(ctx.r[31] + (12)); // lbz r9, 12(r31)
    /* 0x800C3144 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800C3148 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (13)); // lbz r0, 13(r31)
    /* 0x800C314C */ ctx.rlwinm(9, 9, 2u, 0u, 29u, false); // rlwinm r9, r9, 2, 0, 29
    /* 0x800C3150 */ ctx.rlwinm(0, 0, 2u, 0u, 29u, false); // rlwinm r0, r0, 2, 0, 29
    /* 0x800C3154 */ ctx.r[4] = mem.read_u32(ctx.r[9] + ctx.r[27]); // lwzx r4, r9, r27
    /* 0x800C3158 */ ctx.r[5] = mem.read_u32(ctx.r[28] + ctx.r[0]); // lwzx r5, r28, r0
    /* 0x800C315C */ ctx.r[4] = ctx.r[27] + ctx.r[4]; // add r4, r27, r4
    /* 0x800C3160 */ ctx.r[5] = ctx.r[28] + ctx.r[5]; // add r5, r28, r5
    /* 0x800C3164 */ cObj__ModelInit_80074D30(ctx, mem); // bl 0x80074D30 <cObj::ModelInit(unsigned long, unsigned long)>
    /* 0x800C3168 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (-12)); // lwz r9, -12(r31)
    /* 0x800C316C */ ctx.r[11] = ctx.r[30] + (192); // addi r11, r30, 192
    /* 0x800C3170 */ ctx.r[10] = mem.read_u32(ctx.r[31] + (-8)); // lwz r10, -8(r31)
    /* 0x800C3174 */ ctx.r[7] = ctx.r[30] + (204); // addi r7, r30, 204
    /* 0x800C3178 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (-4)); // lwz r0, -4(r31)
    /* 0x800C317C */ ctx.r[3] = ctx.r[30] + (312); // addi r3, r30, 312
    /* 0x800C3180 */ mem.write_u32(ctx.r[30] + (192), ctx.r[9]); // stw r9, 192(r30)
    /* 0x800C3184 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800C3188 */ mem.write_u32(ctx.r[11] + (4), ctx.r[10]); // stw r10, 4(r11)
    /* 0x800C318C */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800C3190 */ mem.write_u32(ctx.r[11] + (8), ctx.r[0]); // stw r0, 8(r11)
    /* 0x800C3194 */ ctx.r[8] = 0x00000010u; // li r8, 16
    /* 0x800C3198 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (0)); // lwz r0, 0(r31)
    /* 0x800C319C */ ctx.r[11] = mem.read_u32(ctx.r[31] + (4)); // lwz r11, 4(r31)
    /* 0x800C31A0 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (8)); // lwz r9, 8(r31)
    /* 0x800C31A4 */ mem.write_u32(ctx.r[30] + (204), ctx.r[0]); // stw r0, 204(r30)
    /* 0x800C31A8 */ ctx.r[31] = ctx.r[31] + (28); // addi r31, r31, 28
    /* 0x800C31AC */ mem.write_u32(ctx.r[7] + (8), ctx.r[9]); // stw r9, 8(r7)
    /* 0x800C31B0 */ mem.write_u32(ctx.r[7] + (4), ctx.r[11]); // stw r11, 4(r7)
    /* 0x800C31B4 */ ctx.r[6] = mem.read_u32(ctx.r[30] + (304)); // lwz r6, 304(r30)
    /* 0x800C31B8 */ ctx.r[7] = ctx.r[6] + (32); // addi r7, r6, 32
    /* 0x800C31BC */ ctx.r[6] = ctx.r[6] + (20); // addi r6, r6, 20
    /* 0x800C31C0 */ LightInfoInit2_8009AFDC(ctx, mem); // bl 0x8009AFDC <LightInfoInit2(tagLIGHT_INFO *, unsigned char, short, Vec *, Vec *, unsigned char)>
    /* 0x800C31C4 */ ctx.r[0] = 0x00000003u; // li r0, 3
    /* 0x800C31C8 */ ctx.rlwinm(10, 29, 2u, 0u, 29u, false); // rlwinm r10, r29, 2, 0, 29
    /* 0x800C31CC */ mem.write_u8(ctx.r[30] + (295), static_cast<uint8_t>(ctx.r[0])); // stb r0, 295(r30)
    /* 0x800C31D0 */ ctx.r[29] = ctx.r[29] + (1); // addi r29, r29, 1
    /* 0x800C31D4 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29456)); // lwz r9, -29456(r13) [objTbl]
    /* 0x800C31D8 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29464)); // lwz r11, -29464(r13) [pSmd]
    /* 0x800C31DC */ mem.write_u32(ctx.r[10] + ctx.r[9], ctx.r[30]); // stwx r30, r10, r9
    /* 0x800C31E0 */ ctx.r[0] = mem.read_u16(ctx.r[11] + (2)); // lhz r0, 2(r11)
    /* 0x800C31E4 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[29]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r29, r0
    /* 0x800C31E8 */ if (ctx.eval_bc(12, 0)) goto loc_800C30B4; // bc 12, 0, 0x800C30B4
loc_800C31EC:;
    /* 0x800C31EC */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800C31F0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (36)); // lwz r0, 36(r1)
    /* 0x800C31F4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800C31F8 */ ctx.lmw(mem, 26, ctx.r[1] + (8)); // lmw r26, 8(r1)
    /* 0x800C31FC */ ctx.r[1] = ctx.r[1] + (32); // addi r1, r1, 32
    /* 0x800C3200 */ return; // blr
}

// [0x800C3204] setObj(void) (scroll.obj, 106 insns / 0x1A8 bytes)
void setObj_800C3204(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800C3204 */ ctx.r[1] += (-32); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -32(r1)
    /* 0x800C3208 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800C320C */ ctx.stmw(mem, 26, ctx.r[1] + (8)); // stmw r26, 8(r1)
    /* 0x800C3210 */ mem.write_u32(ctx.r[1] + (36), ctx.r[0]); // stw r0, 36(r1)
    /* 0x800C3214 */ ctx.r[10] = mem.read_u32(ctx.r[13] + (-29464)); // lwz r10, -29464(r13) [pSmd]
    /* 0x800C3218 */ ctx.r[29] = 0x00000000u; // li r29, 0
    /* 0x800C321C */ ctx.r[0] = mem.read_u32(ctx.r[10] + (4)); // lwz r0, 4(r10)
    /* 0x800C3220 */ ctx.r[11] = mem.read_u32(ctx.r[10] + (8)); // lwz r11, 8(r10)
    /* 0x800C3224 */ ctx.r[9] = mem.read_u16(ctx.r[10] + (2)); // lhz r9, 2(r10)
    /* 0x800C3228 */ ctx.r[27] = ctx.r[10] + ctx.r[0]; // add r27, r10, r0
    /* 0x800C322C */ ctx.r[28] = ctx.r[10] + ctx.r[11]; // add r28, r10, r11
    /* 0x800C3230 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[29]), static_cast<int32_t>(ctx.r[9])); // cmpw cr0, r29, r9
    /* 0x800C3234 */ if (ctx.eval_bc(4, 0)) goto loc_800C3394; // bc 4, 0, 0x800C3394
    /* 0x800C3238 */ ctx.r[31] = ctx.r[10] + (40); // addi r31, r10, 40
    /* 0x800C323C */ ctx.r[26] = 0x00000000u; // li r26, 0
loc_800C3240:;
    /* 0x800C3240 */ ctx.r[3] = 0x00000002u; // li r3, 2
    /* 0x800C3244 */ PullObj_80074784(ctx, mem); // bl 0x80074784 <PullObj(long)>
    /* 0x800C3248 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800C324C */ ctx.r[0] = 0x00000002u; // li r0, 2
    /* 0x800C3250 */ mem.write_u8(ctx.r[30] + (294), static_cast<uint8_t>(ctx.r[0])); // stb r0, 294(r30)
    /* 0x800C3254 */ ctx.r[9] = mem.read_u8(ctx.r[31] + (12)); // lbz r9, 12(r31)
    /* 0x800C3258 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 255); // cmpwi cr0, r9, 255
    /* 0x800C325C */ if (ctx.eval_bc(4, 2)) goto loc_800C327C; // bc 4, 2, 0x800C327C
    /* 0x800C3260 */ ctx.r[5] = 0x80170000u; // lis r5, 0x8017
    /* 0x800C3264 */ mem.write_u8(ctx.r[31] + (12), static_cast<uint8_t>(ctx.r[26])); // stb r26, 12(r31)
    /* 0x800C3268 */ ctx.r[5] = ctx.r[5] + (-9232); // addi r5, r5, -9232 -> 0x8016DBF0 /* "SmdInit() NULL BIN USED" */
    /* 0x800C326C */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800C3270 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800C3274 */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800C3278 */ LogErr_8007A05C(ctx, mem); // bl 0x8007A05C <LogErr(unsigned long, unsigned long, char *,...)>
loc_800C327C:;
    /* 0x800C327C */ ctx.r[0] = mem.read_u8(ctx.r[31] + (13)); // lbz r0, 13(r31)
    /* 0x800C3280 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 255); // cmpwi cr0, r0, 255
    /* 0x800C3284 */ if (ctx.eval_bc(4, 2)) goto loc_800C32A4; // bc 4, 2, 0x800C32A4
    /* 0x800C3288 */ ctx.r[5] = 0x80170000u; // lis r5, 0x8017
    /* 0x800C328C */ mem.write_u8(ctx.r[31] + (13), static_cast<uint8_t>(ctx.r[26])); // stb r26, 13(r31)
    /* 0x800C3290 */ ctx.r[5] = ctx.r[5] + (-9208); // addi r5, r5, -9208 -> 0x8016DC08 /* "SmdInit() NULL TPL USED" */
    /* 0x800C3294 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800C3298 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800C329C */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800C32A0 */ LogErr_8007A05C(ctx, mem); // bl 0x8007A05C <LogErr(unsigned long, unsigned long, char *,...)>
loc_800C32A4:;
    /* 0x800C32A4 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (14)); // lbz r0, 14(r31)
    /* 0x800C32A8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[0]), 255); // cmpwi cr0, r0, 255
    /* 0x800C32AC */ if (ctx.eval_bc(4, 2)) goto loc_800C32CC; // bc 4, 2, 0x800C32CC
    /* 0x800C32B0 */ ctx.r[5] = 0x80170000u; // lis r5, 0x8017
    /* 0x800C32B4 */ mem.write_u8(ctx.r[31] + (14), static_cast<uint8_t>(ctx.r[26])); // stb r26, 14(r31)
    /* 0x800C32B8 */ ctx.r[5] = ctx.r[5] + (-9184); // addi r5, r5, -9184 -> 0x8016DC20 /* "SmdInit() NULL MOT USED" */
    /* 0x800C32BC */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800C32C0 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800C32C4 */ ctx.set_cr_bit(6, ctx.get_cr_bit(6) ^ ctx.get_cr_bit(6)); // crxor 6, 6, 6
    /* 0x800C32C8 */ LogErr_8007A05C(ctx, mem); // bl 0x8007A05C <LogErr(unsigned long, unsigned long, char *,...)>
loc_800C32CC:;
    /* 0x800C32CC */ ctx.r[9] = mem.read_u8(ctx.r[31] + (12)); // lbz r9, 12(r31)
    /* 0x800C32D0 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800C32D4 */ ctx.r[0] = mem.read_u8(ctx.r[31] + (13)); // lbz r0, 13(r31)
    /* 0x800C32D8 */ ctx.rlwinm(9, 9, 2u, 0u, 29u, false); // rlwinm r9, r9, 2, 0, 29
    /* 0x800C32DC */ ctx.rlwinm(0, 0, 2u, 0u, 29u, false); // rlwinm r0, r0, 2, 0, 29
    /* 0x800C32E0 */ ctx.r[4] = mem.read_u32(ctx.r[9] + ctx.r[27]); // lwzx r4, r9, r27
    /* 0x800C32E4 */ ctx.r[5] = mem.read_u32(ctx.r[28] + ctx.r[0]); // lwzx r5, r28, r0
    /* 0x800C32E8 */ ctx.r[4] = ctx.r[27] + ctx.r[4]; // add r4, r27, r4
    /* 0x800C32EC */ ctx.r[5] = ctx.r[28] + ctx.r[5]; // add r5, r28, r5
    /* 0x800C32F0 */ cObj__ModelInit_80074D30(ctx, mem); // bl 0x80074D30 <cObj::ModelInit(unsigned long, unsigned long)>
    /* 0x800C32F4 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (-24)); // lwz r9, -24(r31)
    /* 0x800C32F8 */ ctx.r[11] = ctx.r[30] + (192); // addi r11, r30, 192
    /* 0x800C32FC */ ctx.r[10] = mem.read_u32(ctx.r[31] + (-20)); // lwz r10, -20(r31)
    /* 0x800C3300 */ ctx.r[7] = ctx.r[30] + (204); // addi r7, r30, 204
    /* 0x800C3304 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (-16)); // lwz r0, -16(r31)
    /* 0x800C3308 */ ctx.r[6] = ctx.r[30] + (216); // addi r6, r30, 216
    /* 0x800C330C */ mem.write_u32(ctx.r[30] + (192), ctx.r[9]); // stw r9, 192(r30)
    /* 0x800C3310 */ ctx.r[3] = ctx.r[30] + (312); // addi r3, r30, 312
    /* 0x800C3314 */ mem.write_u32(ctx.r[11] + (4), ctx.r[10]); // stw r10, 4(r11)
    /* 0x800C3318 */ ctx.r[4] = 0x00000002u; // li r4, 2
    /* 0x800C331C */ mem.write_u32(ctx.r[11] + (8), ctx.r[0]); // stw r0, 8(r11)
    /* 0x800C3320 */ ctx.r[5] = 0x00000001u; // li r5, 1
    /* 0x800C3324 */ ctx.r[8] = 0x00000010u; // li r8, 16
    /* 0x800C3328 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (-12)); // lwz r9, -12(r31)
    /* 0x800C332C */ ctx.r[11] = mem.read_u32(ctx.r[31] + (-8)); // lwz r11, -8(r31)
    /* 0x800C3330 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (-4)); // lwz r0, -4(r31)
    /* 0x800C3334 */ mem.write_u32(ctx.r[30] + (204), ctx.r[9]); // stw r9, 204(r30)
    /* 0x800C3338 */ mem.write_u32(ctx.r[7] + (8), ctx.r[0]); // stw r0, 8(r7)
    /* 0x800C333C */ mem.write_u32(ctx.r[7] + (4), ctx.r[11]); // stw r11, 4(r7)
    /* 0x800C3340 */ ctx.r[0] = mem.read_u32(ctx.r[31] + (0)); // lwz r0, 0(r31)
    /* 0x800C3344 */ ctx.r[11] = mem.read_u32(ctx.r[31] + (4)); // lwz r11, 4(r31)
    /* 0x800C3348 */ ctx.r[9] = mem.read_u32(ctx.r[31] + (8)); // lwz r9, 8(r31)
    /* 0x800C334C */ mem.write_u32(ctx.r[30] + (216), ctx.r[0]); // stw r0, 216(r30)
    /* 0x800C3350 */ ctx.r[31] = ctx.r[31] + (72); // addi r31, r31, 72
    /* 0x800C3354 */ mem.write_u32(ctx.r[6] + (8), ctx.r[9]); // stw r9, 8(r6)
    /* 0x800C3358 */ mem.write_u32(ctx.r[6] + (4), ctx.r[11]); // stw r11, 4(r6)
    /* 0x800C335C */ ctx.r[6] = mem.read_u32(ctx.r[30] + (304)); // lwz r6, 304(r30)
    /* 0x800C3360 */ ctx.r[7] = ctx.r[6] + (32); // addi r7, r6, 32
    /* 0x800C3364 */ ctx.r[6] = ctx.r[6] + (20); // addi r6, r6, 20
    /* 0x800C3368 */ LightInfoInit2_8009AFDC(ctx, mem); // bl 0x8009AFDC <LightInfoInit2(tagLIGHT_INFO *, unsigned char, short, Vec *, Vec *, unsigned char)>
    /* 0x800C336C */ ctx.r[0] = 0x00000003u; // li r0, 3
    /* 0x800C3370 */ ctx.rlwinm(10, 29, 2u, 0u, 29u, false); // rlwinm r10, r29, 2, 0, 29
    /* 0x800C3374 */ mem.write_u8(ctx.r[30] + (295), static_cast<uint8_t>(ctx.r[0])); // stb r0, 295(r30)
    /* 0x800C3378 */ ctx.r[29] = ctx.r[29] + (1); // addi r29, r29, 1
    /* 0x800C337C */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29456)); // lwz r9, -29456(r13) [objTbl]
    /* 0x800C3380 */ ctx.r[11] = mem.read_u32(ctx.r[13] + (-29464)); // lwz r11, -29464(r13) [pSmd]
    /* 0x800C3384 */ mem.write_u32(ctx.r[10] + ctx.r[9], ctx.r[30]); // stwx r30, r10, r9
    /* 0x800C3388 */ ctx.r[0] = mem.read_u16(ctx.r[11] + (2)); // lhz r0, 2(r11)
    /* 0x800C338C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[29]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r29, r0
    /* 0x800C3390 */ if (ctx.eval_bc(12, 0)) goto loc_800C3240; // bc 12, 0, 0x800C3240
loc_800C3394:;
    /* 0x800C3394 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800C3398 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (36)); // lwz r0, 36(r1)
    /* 0x800C339C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800C33A0 */ ctx.lmw(mem, 26, ctx.r[1] + (8)); // lmw r26, 8(r1)
    /* 0x800C33A4 */ ctx.r[1] = ctx.r[1] + (32); // addi r1, r1, 32
    /* 0x800C33A8 */ return; // blr
}

// [0x800C33AC] SmdGetTplPtr(long) (scroll.obj, 7 insns / 0x1C bytes)
void SmdGetTplPtr_800C33AC(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800C33AC */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29464)); // lwz r9, -29464(r13) [pSmd]
    /* 0x800C33B0 */ ctx.rlwinm(3, 3, 2u, 0u, 29u, false); // rlwinm r3, r3, 2, 0, 29
    /* 0x800C33B4 */ ctx.r[0] = mem.read_u32(ctx.r[9] + (8)); // lwz r0, 8(r9)
    /* 0x800C33B8 */ ctx.r[9] = ctx.r[9] + ctx.r[0]; // add r9, r9, r0
    /* 0x800C33BC */ ctx.r[3] = mem.read_u32(ctx.r[3] + ctx.r[9]); // lwzx r3, r3, r9
    /* 0x800C33C0 */ ctx.r[3] = ctx.r[9] + ctx.r[3]; // add r3, r9, r3
    /* 0x800C33C4 */ return; // blr
}

// [0x800C33C8] SmdGetObjPtr(long) (scroll.obj, 4 insns / 0x10 bytes)
void SmdGetObjPtr_800C33C8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800C33C8 */ ctx.r[9] = mem.read_u32(ctx.r[13] + (-29456)); // lwz r9, -29456(r13) [objTbl]
    /* 0x800C33CC */ ctx.rlwinm(3, 3, 2u, 0u, 29u, false); // rlwinm r3, r3, 2, 0, 29
    /* 0x800C33D0 */ ctx.r[3] = mem.read_u32(ctx.r[3] + ctx.r[9]); // lwzx r3, r3, r9
    /* 0x800C33D4 */ return; // blr
}

// [0x800CE150] StormInit(cVec &, unsigned char) (storm.obj, 55 insns / 0xDC bytes)
void StormInit_800CE150(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800CE150 */ ctx.r[1] += (-40); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -40(r1)
    /* 0x800CE154 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800CE158 */ ctx.stmw(mem, 30, ctx.r[1] + (32)); // stmw r30, 32(r1)
    /* 0x800CE15C */ mem.write_u32(ctx.r[1] + (44), ctx.r[0]); // stw r0, 44(r1)
    /* 0x800CE160 */ ctx.r[9] = 0x80170000u; // lis r9, 0x8017
    /* 0x800CE164 */ ctx.r[11] = 0x801C0000u; // lis r11, 0x801C
    /* 0x800CE168 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (-7764)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -7764(r9) [0x8016E1AC]
    /* 0x800CE16C */ ctx.r[31] = ctx.r[11] + (25128); // addi r31, r11, 25128 -> StormWk
    /* 0x800CE170 */ ctx.r[9] = ctx.r[1] + (16); // addi r9, r1, 16
    /* 0x800CE174 */ ctx.r[11] = ctx.r[31] + (192); // addi r11, r31, 192
    /* 0x800CE178 */ mem.write_f32(ctx.r[1] + (16), static_cast<float>(ctx.f[0])); // stfs f0, 16(r1)
    /* 0x800CE17C */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[3])); // cmpw cr0, r11, r3
    /* 0x800CE180 */ mem.write_f32(ctx.r[9] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r9)
    /* 0x800CE184 */ mem.write_f32(ctx.r[9] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r9)
    /* 0x800CE188 */ if (ctx.eval_bc(12, 2)) goto loc_800CE1A4; // bc 12, 2, 0x800CE1A4
    /* 0x800CE18C */ ctx.f[0] = mem.read_f32(ctx.r[3] + (0)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 0(r3)
    /* 0x800CE190 */ mem.write_f32(ctx.r[31] + (192), static_cast<float>(ctx.f[0])); // stfs f0, 192(r31)
    /* 0x800CE194 */ ctx.f[13] = mem.read_f32(ctx.r[3] + (4)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 4(r3)
    /* 0x800CE198 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[13])); // stfs f13, 4(r11)
    /* 0x800CE19C */ ctx.f[0] = mem.read_f32(ctx.r[3] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r3)
    /* 0x800CE1A0 */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
loc_800CE1A4:;
    /* 0x800CE1A4 */ ctx.r[11] = ctx.r[31] + (204); // addi r11, r31, 204
    /* 0x800CE1A8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[11]), static_cast<int32_t>(ctx.r[9])); // cmpw cr0, r11, r9
    /* 0x800CE1AC */ if (ctx.eval_bc(12, 2)) goto loc_800CE1C8; // bc 12, 2, 0x800CE1C8
    /* 0x800CE1B0 */ ctx.f[0] = mem.read_f32(ctx.r[9] + (8)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, 8(r9)
    /* 0x800CE1B4 */ ctx.f[13] = mem.read_f32(ctx.r[1] + (16)); ctx.ps0[13] = static_cast<float>(ctx.f[13]); // lfs f13, 16(r1)
    /* 0x800CE1B8 */ ctx.f[12] = mem.read_f32(ctx.r[9] + (4)); ctx.ps0[12] = static_cast<float>(ctx.f[12]); // lfs f12, 4(r9)
    /* 0x800CE1BC */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800CE1C0 */ mem.write_f32(ctx.r[31] + (204), static_cast<float>(ctx.f[13])); // stfs f13, 204(r31)
    /* 0x800CE1C4 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[12])); // stfs f12, 4(r11)
loc_800CE1C8:;
    /* 0x800CE1C8 */ ctx.r[0] = 0x00000001u; // li r0, 1
    /* 0x800CE1CC */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800CE1D0 */ mem.write_u8(ctx.r[31] + (254), static_cast<uint8_t>(ctx.r[0])); // stb r0, 254(r31)
    /* 0x800CE1D4 */ mem.write_u32(ctx.r[31] + (244), ctx.r[0]); // stw r0, 244(r31)
    /* 0x800CE1D8 */ mem.write_u32(ctx.r[31] + (240), ctx.r[31]); // stw r31, 240(r31)
    /* 0x800CE1DC */ EspGetEstAddr_800833A4(ctx, mem); // bl 0x800833A4 <EspGetEstAddr(unsigned long, unsigned char)>
    /* 0x800CE1E0 */ ctx.r[30] = ctx.r[3]; // mr r30, r3
    /* 0x800CE1E4 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800CE1E8 */ EspGetEffAddr_800834AC(ctx, mem); // bl 0x800834AC <EspGetEffAddr(unsigned long)>
    /* 0x800CE1EC */ ctx.r[7] = ctx.r[3]; // mr r7, r3
    /* 0x800CE1F0 */ ctx.r[6] = ctx.r[30]; // mr r6, r30
    /* 0x800CE1F4 */ mem.write_u32(ctx.r[1] + (8), ctx.r[31]); // stw r31, 8(r1)
    /* 0x800CE1F8 */ ctx.r[3] = 0x00000000u; // li r3, 0
    /* 0x800CE1FC */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800CE200 */ ctx.r[5] = 0x00000000u; // li r5, 0
    /* 0x800CE204 */ ctx.r[8] = 0x00000002u; // li r8, 2
    /* 0x800CE208 */ ctx.r[9] = 0x00000000u; // li r9, 0
    /* 0x800CE20C */ ctx.r[10] = ctx.r[31]; // mr r10, r31
    /* 0x800CE210 */ EstSet_800906FC(ctx, mem); // bl 0x800906FC <EstSet(cEm *, Vec *, Vec *, tagESPSEQ_HEAD *, tagESP_EFF_HEADER *, unsigned short, unsigned char, void *, BLT_WK *)>
    /* 0x800CE214 */ mem.write_u32(ctx.r[31] + (324), ctx.r[3]); // stw r3, 324(r31)
    /* 0x800CE218 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (44)); // lwz r0, 44(r1)
    /* 0x800CE21C */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800CE220 */ ctx.lmw(mem, 30, ctx.r[1] + (32)); // lmw r30, 32(r1)
    /* 0x800CE224 */ ctx.r[1] = ctx.r[1] + (40); // addi r1, r1, 40
    /* 0x800CE228 */ return; // blr
}

// [0x800CE22C] StormMain(void) (storm.obj, 47 insns / 0xBC bytes)
void StormMain_800CE22C(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800CE22C */ ctx.r[1] += (-40); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -40(r1)
    /* 0x800CE230 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800CE234 */ mem.write_f64(ctx.r[1] + (32), ctx.f[31]); // stfd f31, 32(r1)
    /* 0x800CE238 */ ctx.stmw(mem, 30, ctx.r[1] + (24)); // stmw r30, 24(r1)
    /* 0x800CE23C */ mem.write_u32(ctx.r[1] + (44), ctx.r[0]); // stw r0, 44(r1)
    /* 0x800CE240 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800CE244 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r3, -29836(r13) [pG]
    /* 0x800CE248 */ ctx.f[31] = mem.read_f32(ctx.r[11] + (-7760)); ctx.ps0[31] = static_cast<float>(ctx.f[31]); // lfs f31, -7760(r11) [0x8016E1B0]
    /* 0x800CE24C */ ctx.r[9] = 0x801C0000u; // lis r9, 0x801C
    /* 0x800CE250 */ ctx.r[30] = ctx.r[9] + (25128); // addi r30, r9, 25128 -> StormWk
    /* 0x800CE254 */ ctx.r[31] = ctx.r[1] + (8); // addi r31, r1, 8
    /* 0x800CE258 */ mem.write_f32(ctx.r[1] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r1)
    /* 0x800CE25C */ ctx.r[3] = ctx.r[3] + (756); // addi r3, r3, 756
    /* 0x800CE260 */ mem.write_f32(ctx.r[31] + (4), static_cast<float>(ctx.f[31])); // stfs f31, 4(r31)
    /* 0x800CE264 */ ctx.r[4] = ctx.r[30] + (192); // addi r4, r30, 192
    /* 0x800CE268 */ mem.write_f32(ctx.r[31] + (8), static_cast<float>(ctx.f[31])); // stfs f31, 8(r31)
    /* 0x800CE26C */ ctx.r[5] = ctx.r[31]; // mr r5, r31
    /* 0x800CE270 */ ctx.call_indirect(0x80101CC8u, mem); // bl 0x80101CC8 <PSMTXMultVec>
    /* 0x800CE274 */ ctx.r[0] = mem.read_u32(ctx.r[30] + (244)); // lwz r0, 244(r30)
    /* 0x800CE278 */ mem.write_f32(ctx.r[1] + (12), static_cast<float>(ctx.f[31])); // stfs f31, 12(r1)
    /* 0x800CE27C */ ctx.r[9] = ctx.r[0] & 0x0001u; ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[9]), 0); // andi. r9, r0, 0x0001
    /* 0x800CE280 */ if (ctx.eval_bc(12, 2)) goto loc_800CE2D0; // bc 12, 2, 0x800CE2D0
    /* 0x800CE284 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800CE288 */ ctx.r[4] = ctx.r[30] + (204); // addi r4, r30, 204
    /* 0x800CE28C */ RotMatrix_8009E1D0(ctx, mem); // bl 0x8009E1D0 <RotMatrix(float (*)[3], cVec &)>
    /* 0x800CE290 */ ctx.r[4] = ctx.r[31]; // mr r4, r31
    /* 0x800CE294 */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800CE298 */ TransMatrix_8009E1B4(ctx, mem); // bl 0x8009E1B4 <TransMatrix(float (*)[3], cVec &)>
    /* 0x800CE29C */ ctx.r[3] = mem.read_u32(ctx.r[30] + (240)); // lwz r3, 240(r30)
    /* 0x800CE2A0 */ ctx.r[3] = ctx.r[3] + (48); // addi r3, r3, 48
    /* 0x800CE2A4 */ ctx.call_indirect(0x801000FCu, mem); // bl 0x801000FC <PSMTXIdentity>
    /* 0x800CE2A8 */ ctx.r[4] = mem.read_u32(ctx.r[30] + (240)); // lwz r4, 240(r30)
    /* 0x800CE2AC */ ctx.r[3] = ctx.r[30]; // mr r3, r30
    /* 0x800CE2B0 */ ctx.r[5] = ctx.r[4]; // mr r5, r4
    /* 0x800CE2B4 */ ctx.r[4] = ctx.r[4] + (48); // addi r4, r4, 48
    /* 0x800CE2B8 */ ctx.call_indirect(0x80100470u, mem); // bl 0x80100470 <PSMTXConcat>
    /* 0x800CE2BC */ ctx.r[4] = mem.read_u32(ctx.r[30] + (240)); // lwz r4, 240(r30)
    /* 0x800CE2C0 */ ctx.r[3] = mem.read_u32(ctx.r[13] + (-29836)); // lwz r3, -29836(r13) [pG]
    /* 0x800CE2C4 */ ctx.r[5] = ctx.r[4] + (96); // addi r5, r4, 96
    /* 0x800CE2C8 */ ctx.r[3] = ctx.r[3] + (852); // addi r3, r3, 852
    /* 0x800CE2CC */ ctx.call_indirect(0x80100470u, mem); // bl 0x80100470 <PSMTXConcat>
loc_800CE2D0:;
    /* 0x800CE2D0 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (44)); // lwz r0, 44(r1)
    /* 0x800CE2D4 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800CE2D8 */ ctx.lmw(mem, 30, ctx.r[1] + (24)); // lmw r30, 24(r1)
    /* 0x800CE2DC */ ctx.f[31] = mem.read_f64(ctx.r[1] + (32)); // lfd f31, 32(r1)
    /* 0x800CE2E0 */ ctx.r[1] = ctx.r[1] + (40); // addi r1, r1, 40
    /* 0x800CE2E4 */ return; // blr
}

// [0x800CE2E8] StormEnd(void) (storm.obj, 10 insns / 0x28 bytes)
void StormEnd_800CE2E8(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800CE2E8 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800CE2EC */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800CE2F0 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800CE2F4 */ ctx.r[9] = 0x801C0000u; // lis r9, 0x801C
    /* 0x800CE2F8 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (25452)); // lwz r3, 25452(r9) [0x801C636C]
    /* 0x800CE2FC */ PushEspgen_8008E3E4(ctx, mem); // bl 0x8008E3E4 <PushEspgen(ESPGEN *)>
    /* 0x800CE300 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800CE304 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800CE308 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800CE30C */ return; // blr
}

// [0x800CE310] StormPause(bool) (storm.obj, 13 insns / 0x34 bytes)
void StormPause_800CE310(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800CE310 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800CE314 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800CE318 */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800CE31C */ ctx.r[9] = 0x801C0000u; // lis r9, 0x801C
    /* 0x800CE320 */ ctx.r[4] = ctx.r[3]; // mr r4, r3
    /* 0x800CE324 */ ctx.r[3] = mem.read_u32(ctx.r[9] + (25452)); // lwz r3, 25452(r9) [0x801C636C]
    /* 0x800CE328 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800CE32C */ if (ctx.eval_bc(12, 2)) goto loc_800CE334; // bc 12, 2, 0x800CE334
    /* 0x800CE330 */ EspgenSetMove_8008E598(ctx, mem); // bl 0x8008E598 <EspgenSetMove(ESPGEN *, bool)>
loc_800CE334:;
    /* 0x800CE334 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800CE338 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800CE33C */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800CE340 */ return; // blr
}

// [0x800CE344] BLT_WK::BLT_WK(void) (storm.obj, 32 insns / 0x80 bytes)
void BLT_WK__BLT_WK_800CE344(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800CE344 */ ctx.r[11] = 0x80170000u; // lis r11, 0x8017
    /* 0x800CE348 */ ctx.r[9] = ctx.r[3]; // mr r9, r3
    /* 0x800CE34C */ ctx.f[0] = mem.read_f32(ctx.r[11] + (-7756)); ctx.ps0[0] = static_cast<float>(ctx.f[0]); // lfs f0, -7756(r11) [0x8016E1B4]
    /* 0x800CE350 */ ctx.r[10] = ctx.r[9] + (192); // addi r10, r9, 192
    /* 0x800CE354 */ ctx.r[11] = ctx.r[9] + (204); // addi r11, r9, 204
    /* 0x800CE358 */ ctx.r[8] = ctx.r[9] + (216); // addi r8, r9, 216
    /* 0x800CE35C */ mem.write_f32(ctx.r[9] + (192), static_cast<float>(ctx.f[0])); // stfs f0, 192(r9)
    /* 0x800CE360 */ ctx.r[7] = ctx.r[9] + (256); // addi r7, r9, 256
    /* 0x800CE364 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800CE368 */ ctx.r[6] = ctx.r[9] + (268); // addi r6, r9, 268
    /* 0x800CE36C */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800CE370 */ ctx.r[5] = ctx.r[9] + (284); // addi r5, r9, 284
    /* 0x800CE374 */ mem.write_f32(ctx.r[9] + (204), static_cast<float>(ctx.f[0])); // stfs f0, 204(r9)
    /* 0x800CE378 */ ctx.r[10] = ctx.r[9] + (312); // addi r10, r9, 312
    /* 0x800CE37C */ mem.write_f32(ctx.r[11] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r11)
    /* 0x800CE380 */ mem.write_f32(ctx.r[11] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r11)
    /* 0x800CE384 */ mem.write_f32(ctx.r[9] + (216), static_cast<float>(ctx.f[0])); // stfs f0, 216(r9)
    /* 0x800CE388 */ mem.write_f32(ctx.r[8] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r8)
    /* 0x800CE38C */ mem.write_f32(ctx.r[8] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r8)
    /* 0x800CE390 */ mem.write_f32(ctx.r[9] + (256), static_cast<float>(ctx.f[0])); // stfs f0, 256(r9)
    /* 0x800CE394 */ mem.write_f32(ctx.r[7] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r7)
    /* 0x800CE398 */ mem.write_f32(ctx.r[7] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r7)
    /* 0x800CE39C */ mem.write_f32(ctx.r[9] + (268), static_cast<float>(ctx.f[0])); // stfs f0, 268(r9)
    /* 0x800CE3A0 */ mem.write_f32(ctx.r[6] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r6)
    /* 0x800CE3A4 */ mem.write_f32(ctx.r[6] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r6)
    /* 0x800CE3A8 */ mem.write_f32(ctx.r[9] + (284), static_cast<float>(ctx.f[0])); // stfs f0, 284(r9)
    /* 0x800CE3AC */ mem.write_f32(ctx.r[5] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r5)
    /* 0x800CE3B0 */ mem.write_f32(ctx.r[5] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r5)
    /* 0x800CE3B4 */ mem.write_f32(ctx.r[9] + (312), static_cast<float>(ctx.f[0])); // stfs f0, 312(r9)
    /* 0x800CE3B8 */ mem.write_f32(ctx.r[10] + (8), static_cast<float>(ctx.f[0])); // stfs f0, 8(r10)
    /* 0x800CE3BC */ mem.write_f32(ctx.r[10] + (4), static_cast<float>(ctx.f[0])); // stfs f0, 4(r10)
    /* 0x800CE3C0 */ return; // blr
}

// [0x800CE3C4] __static_initialization_and_destruction_0 (storm.obj, 16 insns / 0x40 bytes)
void static_initialization_and_destruction_0_800CE3C4(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800CE3C4 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800CE3C8 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800CE3CC */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800CE3D0 */ ctx.r[0] = 0x00000000u; // li r0, 0
    /* 0x800CE3D4 */ ctx.r[0] = ctx.r[0] | 0xFFFFu; // ori r0, r0, 0xFFFF
    /* 0x800CE3D8 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[4]), static_cast<int32_t>(ctx.r[0])); // cmpw cr0, r4, r0
    /* 0x800CE3DC */ if (ctx.eval_bc(4, 2)) goto loc_800CE3F4; // bc 4, 2, 0x800CE3F4
    /* 0x800CE3E0 */ ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[3]), 0); // cmpwi cr0, r3, 0
    /* 0x800CE3E4 */ if (ctx.eval_bc(12, 2)) goto loc_800CE3F4; // bc 12, 2, 0x800CE3F4
    /* 0x800CE3E8 */ ctx.r[3] = 0x801C0000u; // lis r3, 0x801C
    /* 0x800CE3EC */ ctx.r[3] = ctx.r[3] + (25128); // addi r3, r3, 25128 -> StormWk
    /* 0x800CE3F0 */ BLT_WK__BLT_WK_8000D414(ctx, mem); // bl 0x8000D414 <BLT_WK::BLT_WK(void)>
loc_800CE3F4:;
    /* 0x800CE3F4 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800CE3F8 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800CE3FC */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800CE400 */ return; // blr
}

// [0x800CE404] global constructors keyed to StormInit(cVec &, unsigned char) (storm.obj, 11 insns / 0x2C bytes)
void global_constructors_keyed_to_StormInit_800CE404(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    /* 0x800CE404 */ ctx.r[1] += (-8); mem.write_u32(ctx.r[1], ctx.r[1]); // stwu r1, -8(r1)
    /* 0x800CE408 */ ctx.r[0] = ctx.lr; // mflr r0
    /* 0x800CE40C */ mem.write_u32(ctx.r[1] + (12), ctx.r[0]); // stw r0, 12(r1)
    /* 0x800CE410 */ ctx.r[4] = 0x00000000u; // li r4, 0
    /* 0x800CE414 */ ctx.r[3] = 0x00000001u; // li r3, 1
    /* 0x800CE418 */ ctx.r[4] = ctx.r[4] | 0xFFFFu; // ori r4, r4, 0xFFFF
    /* 0x800CE41C */ static_initialization_and_destruction_0_800CE3C4(ctx, mem); // bl 0x800CE3C4 <__static_initialization_and_destruction_0>
    /* 0x800CE420 */ ctx.r[0] = mem.read_u32(ctx.r[1] + (12)); // lwz r0, 12(r1)
    /* 0x800CE424 */ ctx.lr = ctx.r[0]; // mtlr r0
    /* 0x800CE428 */ ctx.r[1] = ctx.r[1] + (8); // addi r1, r1, 8
    /* 0x800CE42C */ return; // blr
}

} // namespace pn03::recomp
