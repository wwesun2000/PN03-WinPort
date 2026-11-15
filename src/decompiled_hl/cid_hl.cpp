// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: CId.obj
// Functions Decompiled: 74
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdRender(void)
// Unit: CId.obj | Address: 0x80070EC0 | Size: 0x68 bytes
// ============================================================================
/* [0x80070EC0] */ void cIdCtrl::IdRender(cIdCtrl* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r29 = this_r3;
    r30 = 0;
    r31 = *(uint32_t*)(this_r3 + 0x0);
    r3 = cIdCtrl::IdCamera(void) const(); // [0x80070F60]
    *(uint32_t*)(this_r3 + 0x8) = 0;
    if (*(uint32_t*)(this_r3 + 0x0) == 0) goto label_80070F0C;
label_80070EEC:;
    r9 = *(uint32_t*)(this_r3 + 0x8);
    r3 = *(uint32_t*)(this_r3 + 0x0);
    r9 = *(uint32_t*)(this_r3 + 0x8) + (1);
    *(uint32_t*)(this_r3 + 0x8) = (*(uint32_t*)(this_r3 + 0x8) + 1);
    r3 = cIdPrim::IdPrimRender(void) const(); // [0x800718D8]
    r31 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x0) + 0x0);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x0) + 0x0) != 0) goto label_80070EEC;
label_80070F0C:;
    r0 = 0;
    *(uint32_t*)(this_r3 + 0x0) = 0;
    r0 = stack_0x1C;
    return; // r3 = ret_80070EFC
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdAddOt(cIdPrim *, unsigned short, unsigned char)
// Unit: CId.obj | Address: 0x80070F28 | Size: 0x38 bytes
// ============================================================================
/* [0x80070F28] */ void cIdCtrl::IdAddOt(cIdCtrl* this_r3, cIdPrim * arg0_r4, unsigned short arg1_r5, unsigned char arg2_r6) {
    goto label_80070F30;
label_80070F2C:;
    r3 = *(uint32_t*)(this_r3 + 0x0);
label_80070F30:;
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x0) + 0x0);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x0) + 0x0) == 0) goto label_80070F48;
    r0 = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x0) + 0x0) + 0x4);
    if (*(uint8_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x0) + 0x0) + 0x4) > arg1_r5) goto label_80070F2C;
label_80070F48:;
    *(uint8_t*)(arg0_r4 + 0x4) = arg1_r5;
    *(uint8_t*)(arg0_r4 + 0x5) = arg2_r6;
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x0) + 0x0);
    *(uint32_t*)(arg0_r4 + 0x0) = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x0) + 0x0);
    *(uint32_t*)(*(uint32_t*)(this_r3 + 0x0) + 0x0) = arg0_r4;
    return; // r3 = *(uint32_t*)(this_r3 + 0x0)
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdCamera(void) const
// Unit: CId.obj | Address: 0x80070F60 | Size: 0xB4 bytes
// ============================================================================
/* [0x80070F60] */ void cIdCtrl::IdCamera(void) const(void) {
    // Stack frame allocated: 144 bytes
    stack_0x94 = r0;
    f1 = *(float*)0x801688DC;
    f6 = *(float*)0x801688E8;
    f3 = *(float*)0x801688E0;
    f4 = *(float*)0x801688E4;
    r27 = &stack_0x48;
    r3 = GXSetViewport(); // [0x80126334]
    r5 = 512;
    r6 = 448;
    r4 = 0;
    r3 = 0;
    r3 = GXSetScissor(); // [0x80126390]
    f1 = *(float*)0x801688DC;
    f2 = *(float*)0x801688E4;
    r3 = &stack_0x08;
    f4 = *(float*)0x801688E0;
    f6 = *(float*)0x801688EC;
    r3 = C_MTXOrtho(); // [0x8010242C]
    r3 = &stack_0x08;
    r4 = 1;
    r3 = GXSetProjection(); // [0x80125D20]
    r3 = &stack_0x48;
    r3 = PSMTXIdentity(); // [0x801000FC]
    r3 = &stack_0x48;
    r4 = 0;
    r3 = GXLoadPosMtxImm(); // [0x80125FAC]
    r3 = 0;
    r3 = GXSetCurrentMtx(); // [0x801260E8]
    r0 = stack_0x94;
    return; // r3 = ret_80070FFC
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdSetPrim(TEXDescriptor *, idRect &, cColor, unsigned char, unsigned long)
// Unit: CId.obj | Address: 0x80071014 | Size: 0xE8 bytes
// ============================================================================
/* [0x80071014] */ void cIdCtrl::IdSetPrim(cIdCtrl* this_r3, TEXDescriptor * arg0_r4, idRect & arg1_r5, cColor arg2_r6, unsigned char arg3_r7, unsigned long arg4_r8) {
    // Stack frame allocated: 64 bytes
    stack_0x44 = r0;
    r28 = arg4_r8;
    r27 = this_r3;
    r25 = arg0_r4;
    r31 = arg1_r5;
    r30 = arg2_r6;
    r26 = arg3_r7;
    if (arg4_r8 != -1) goto label_80071048;
    r28 = 0;
label_80071048:;
    r3 = 52;
    r3 = GetPrimBuff(52); // [0x8009D048]
    r0 = *(uint32_t*)(arg2_r6 + 0x0);
    r11 = &stack_0x08;
    r10 = *(uint32_t*)(arg2_r6 + 0xC);
    r9 = ret_8007104C;
    r8 = *(uint32_t*)(arg2_r6 + 0x4);
    r7 = ret_8007104C + (8);
    r6 = *(uint32_t*)(arg2_r6 + 0x8);
    r29 = ret_8007104C + (24);
    stack_0x08 = *(uint32_t*)(arg2_r6 + 0x0);
    r3 = this_r3;
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)(arg2_r6 + 0x8);
    r4 = ret_8007104C;
    *(uint32_t*)(&stack_0x08 + 0xC) = *(uint32_t*)(arg2_r6 + 0xC);
    r5 = arg3_r7;
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)(arg2_r6 + 0x4);
    r6 = 0;
    *(uint32_t*)(ret_8007104C + 0x2C) = arg0_r4;
    r30 = *(uint32_t*)(ret_8007104C + 0x14);
    r10 = *(uint32_t*)(arg1_r5 + 0x0);
    r8 = *(uint32_t*)(arg1_r5 + 0xC);
    stack_0x18 = *(uint32_t*)(ret_8007104C + 0x14);
    r0 = *(uint32_t*)(arg1_r5 + 0x4);
    r11 = *(uint32_t*)(arg1_r5 + 0x8);
    *(uint32_t*)(ret_8007104C + 0x8) = *(uint32_t*)(arg1_r5 + 0x0);
    *(uint32_t*)((ret_8007104C + 8) + 0xC) = *(uint32_t*)(arg1_r5 + 0xC);
    *(uint32_t*)((ret_8007104C + 8) + 0x4) = *(uint32_t*)(arg1_r5 + 0x4);
    *(uint32_t*)((ret_8007104C + 8) + 0x8) = *(uint32_t*)(arg1_r5 + 0x8);
    *(uint32_t*)(ret_8007104C + 0x14) = *(uint32_t*)(ret_8007104C + 0x14);
    r11 = stack_0x08;
    r10 = stack_0x0C;
    r8 = stack_0x10;
    r0 = stack_0x14;
    *(uint32_t*)(ret_8007104C + 0x18) = stack_0x08;
    *(uint32_t*)((ret_8007104C + 24) + 0xC) = stack_0x14;
    *(uint32_t*)((ret_8007104C + 24) + 0x4) = stack_0x0C;
    *(uint32_t*)((ret_8007104C + 24) + 0x8) = stack_0x10;
    *(uint32_t*)(ret_8007104C + 0x28) = 0;
    r3 = cIdCtrl::IdAddOt(this_r3, ret_8007104C, arg3_r7, 0); // [0x80070F28]
    r0 = stack_0x44;
    return; // r3 = ret_800710E4
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdCalcTpl(unsigned long)
// Unit: CId.obj | Address: 0x800710FC | Size: 0xA4 bytes
// ============================================================================
/* [0x800710FC] */ void cIdCtrl::IdCalcTpl(cIdCtrl* this_r3, unsigned long arg0_r4) {
    r0 = *(uint32_t*)(arg0_r4 + 0x8);
    if (*(uint32_t*)(arg0_r4 + 0x8) < 0) goto label_80071198;
    r9 = *(uint32_t*)(arg0_r4 + 0x4);
    r0 = (*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4);
    r8 = 0;
    r10 = (*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4);
    *(uint32_t*)(arg0_r4 + 0x8) = (*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4);
    if (0 >= *(uint32_t*)(arg0_r4 + 0x4)) goto label_80071198;
    r7 = 1;
label_80071128:;
    r0 = *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0);
    r9 = *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4);
    r11 = (arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0));
    r9 = (arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4));
    *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0) = (arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0));
    *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) = (arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4));
    r0 = *(uint8_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x23);
    if (*(uint8_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x23) != 0) goto label_80071160;
    r0 = *(uint32_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x8);
    r0 = (arg0_r4 + *(uint32_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x8));
    *(uint32_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x8) = (arg0_r4 + *(uint32_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x8));
    r9 = *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0);
    *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0) + 0x23) = 1;
label_80071160:;
    r9 = *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4);
    r0 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x2);
    if (*(uint8_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x2) != 0) goto label_80071184;
    r0 = *(uint32_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x8);
    r0 = (arg0_r4 + *(uint32_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x8));
    *(uint32_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x8) = (arg0_r4 + *(uint32_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x8));
    r9 = *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4);
    *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x2) = 1;
label_80071184:;
    r0 = *(uint32_t*)(arg0_r4 + 0x4);
    r8 = 0 + (1);
    r10 = (*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + (8);
    if ((0 + 1) < *(uint32_t*)(arg0_r4 + 0x4)) goto label_80071128;
label_80071198:;
    r3 = *(uint32_t*)(arg0_r4 + 0x4);
    return; // r3 = *(uint32_t*)(arg0_r4 + 0x4)
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdLoad(unsigned long, unsigned long, unsigned long &, unsigned short, unsigned long) const
// Unit: CId.obj | Address: 0x800711A0 | Size: 0xC0 bytes
// ============================================================================
/* [0x800711A0] */ void cIdCtrl::IdLoad(unsigned long, unsigned long, unsigned long &, unsigned short, unsigned long) const(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r30 = r6;
    r5 = r5;
    r6 = r8;
    if (r0 < 0) goto label_80071200;
    r8 = r8 | 0x0004u;
    r7 = *(uint32_t*)(r6 + 0x0);
    r4 = 0;
    r9 = 3;
    r10 = 0;
    r3 = DvdReadReqMain(r3, 0, r5, r8, *(uint32_t*)(r6 + 0x0), r8, 3, 0); // [0x8007B744]
    r31 = ret_800711E0;
    if (r0 < 0) goto label_80071240;
    r5 = r6;
    r3 = ret_800711E0;
    r4 = 0;
    r3 = DvdReadCheck(ret_800711E0, 0, r6); // [0x8007BCFC]
    goto label_80071248;
label_80071200:;
    r8 = r8 | 0x0004u;
    r7 = *(uint32_t*)(r6 + 0x0);
    r4 = 0;
    r9 = 0;
    r10 = 0;
    r3 = DvdReadReqMain(ret_800711F8, 0, r6, r8, *(uint32_t*)(r6 + 0x0), r8, 0, 0); // [0x8007B744]
    r31 = ret_80071220;
    if (r0 < 0) goto label_80071240;
    r4 = r6;
    r3 = ret_80071220;
    r5 = 0;
    r3 = DvdReadCheck(ret_80071220, r6, 0); // [0x8007BCFC]
    goto label_80071248;
label_80071240:;
    r0 = 0;
    *(uint32_t*)(r6 + 0x0) = 0;
label_80071248:;
    r3 = ret_80071220;
    r0 = stack_0x14;
    return; // r3 = ret_80071220
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdLoad(char *, unsigned long, unsigned long &, unsigned short, unsigned long) const
// Unit: CId.obj | Address: 0x80071260 | Size: 0xC0 bytes
// ============================================================================
/* [0x80071260] */ void cIdCtrl::IdLoad(char *, unsigned long, unsigned long &, unsigned short, unsigned long) const(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r30 = r6;
    r5 = r5;
    r6 = r8;
    if (r0 < 0) goto label_800712C0;
    r3 = 0;
    r8 = r8 | 0x0004u;
    r7 = *(uint32_t*)(r6 + 0x0);
    r3 = 0 | 0xFFFFu;
    r9 = 3;
    r10 = 0;
    r3 = DvdReadReqMain(0, r4, r5, r8, *(uint32_t*)(r6 + 0x0), r8, 3, 0); // [0x8007B744]
    r31 = ret_800712A0;
    if (r0 < 0) goto label_80071300;
    r5 = r6;
    r3 = ret_800712A0;
    r4 = 0;
    r3 = DvdReadCheck(ret_800712A0, 0, r6); // [0x8007BCFC]
    goto label_80071308;
label_800712C0:;
    r3 = 0;
    r8 = r8 | 0x0004u;
    r7 = *(uint32_t*)(r6 + 0x0);
    r3 = 0 | 0xFFFFu;
    r9 = 0;
    r10 = 0;
    r3 = DvdReadReqMain(0, 0, r6, r8, *(uint32_t*)(r6 + 0x0), r8, 0, 0); // [0x8007B744]
    r31 = ret_800712E0;
    if (r0 < 0) goto label_80071300;
    r4 = r6;
    r3 = ret_800712E0;
    r5 = 0;
    r3 = DvdReadCheck(ret_800712E0, r6, 0); // [0x8007BCFC]
    goto label_80071308;
label_80071300:;
    r0 = 0;
    *(uint32_t*)(r6 + 0x0) = 0;
label_80071308:;
    r3 = ret_800712E0;
    r0 = stack_0x14;
    return; // r3 = ret_800712E0
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdLoadAlloc(unsigned long, void *, unsigned long &, unsigned short, unsigned long) const
// Unit: CId.obj | Address: 0x80071320 | Size: 0x7C bytes
// ============================================================================
/* [0x80071320] */ void cIdCtrl::IdLoadAlloc(unsigned long, void *, unsigned long &, unsigned short, unsigned long) const(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r10 = r5;
    r8 = r8 | 0x0004u;
    r30 = r6;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r9 = 16;
    r3 = DvdReadReqMain(r3, 0, 0, 0, 0, r8, 16, r5); // [0x8007B744]
    r31 = ret_8007135C;
    if (r0 < 0) goto label_8007137C;
    r4 = r6;
    r3 = ret_8007135C;
    r5 = 0;
    r3 = DvdReadCheck(ret_8007135C, r6, 0); // [0x8007BCFC]
    goto label_80071384;
label_8007137C:;
    r0 = 0;
    *(uint32_t*)(r6 + 0x0) = 0;
label_80071384:;
    r3 = ret_8007135C;
    r0 = stack_0x14;
    return; // r3 = ret_8007135C
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdLoadAlloc(char *, void *, unsigned long &, unsigned short, unsigned long) const
// Unit: CId.obj | Address: 0x8007139C | Size: 0x7C bytes
// ============================================================================
/* [0x8007139C] */ void cIdCtrl::IdLoadAlloc(char *, void *, unsigned long &, unsigned short, unsigned long) const(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r10 = r5;
    r8 = r8 | 0x0004u;
    r30 = r6;
    r3 = 0;
    r3 = 0 | 0xFFFFu;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r9 = 16;
    r3 = DvdReadReqMain(0, r4, 0, 0, 0, r8, 16, r5); // [0x8007B744]
    r31 = ret_800713D8;
    if (r0 < 0) goto label_800713F8;
    r4 = r6;
    r3 = ret_800713D8;
    r5 = 0;
    r3 = DvdReadCheck(ret_800713D8, r6, 0); // [0x8007BCFC]
    goto label_80071400;
label_800713F8:;
    r0 = 0;
    *(uint32_t*)(r6 + 0x0) = 0;
label_80071400:;
    r3 = ret_800713D8;
    r0 = stack_0x14;
    return; // r3 = ret_800713D8
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdLoadAram(unsigned long, unsigned long, unsigned long, unsigned short) const
// Unit: CId.obj | Address: 0x80071418 | Size: 0x60 bytes
// ============================================================================
/* [0x80071418] */ void cIdCtrl::IdLoadAram(unsigned long, unsigned long, unsigned long, unsigned short) const(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r4 = r4;
    if (r0 < 0) goto label_8007144C;
    if (r4 <= r5) goto label_8007143C;
    r3 = -10;
    goto label_80071468;
label_8007143C:;
    r3 = 1;
    r3 = AramDmaTransReq(1, r4, r5, r6, r7); // [0x8007BFD4]
    goto label_80071468;
label_8007144C:;
    if (r4 >= r5) goto label_8007145C;
    r3 = -11;
    goto label_80071468;
label_8007145C:;
    r3 = 0;
    r3 = AramDmaTransReq(0, r4, r5, r6, r7); // [0x8007BFD4]
label_80071468:;
    r0 = stack_0x0C;
    return; // r3 = ret_80071464
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdLoadAram(unsigned long, unsigned long)
// Unit: CId.obj | Address: 0x80071478 | Size: 0x98 bytes
// ============================================================================
/* [0x80071478] */ void cIdCtrl::IdLoadAram(cIdCtrl* this_r3, unsigned long arg0_r4, unsigned long arg1_r5) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r30 = arg1_r5;
    r31 = this_r3;
    r29 = arg0_r4;
    r4 = arg1_r5;
    r3 = cIdCtrl::IdLoadAramSub(this_r3, arg1_r5); // [0x800715A8]
    if (ret_80071498 == 0) goto label_800714F8;
    r0 = 0;
    r5 = arg1_r5;
    stack_0x08 = 0;
    r3 = this_r3;
    r4 = arg0_r4;
    r6 = &stack_0x08;
    r7 = 1;
    r8 = 0;
    r3 = cIdCtrl::IdLoad(unsigned long, unsigned long, unsigned long &, unsigned short, unsigned long) const(); // [0x800711A0]
    if (ret_800714C4 < 0) goto label_800714DC;
    r3 = *(uint32_t*)(this_r3 + 0xC);
    r3 = *(uint32_t*)(this_r3 + 0xC) + (-1);
    goto label_800714FC;
label_800714DC:;
    r3 = 0;
    r6 = arg0_r4;
    r5 = "file number %d is not found!";
    r4 = 0;
    r3 = LogErr(0, 0, "file number %d is not found!", arg0_r4); // [0x8007A05C]
label_800714F8:;
    r3 = -1;
label_800714FC:;
    r0 = stack_0x24;
    return; // r3 = -1
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdLoadAram(char *, unsigned long)
// Unit: CId.obj | Address: 0x80071510 | Size: 0x98 bytes
// ============================================================================
/* [0x80071510] */ void cIdCtrl::IdLoadAram(cIdCtrl* this_r3, char * arg0_r4, unsigned long arg1_r5) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r30 = arg1_r5;
    r31 = this_r3;
    r29 = arg0_r4;
    r4 = arg1_r5;
    r3 = cIdCtrl::IdLoadAramSub(this_r3, arg1_r5); // [0x800715A8]
    if (ret_80071530 == 0) goto label_80071590;
    r0 = 0;
    r5 = arg1_r5;
    stack_0x08 = 0;
    r3 = this_r3;
    r4 = arg0_r4;
    r6 = &stack_0x08;
    r7 = 1;
    r8 = 0;
    r3 = cIdCtrl::IdLoad(char *, unsigned long, unsigned long &, unsigned short, unsigned long) const(); // [0x80071260]
    if (ret_8007155C < 0) goto label_80071574;
    r3 = *(uint32_t*)(this_r3 + 0xC);
    r3 = *(uint32_t*)(this_r3 + 0xC) + (-1);
    goto label_80071594;
label_80071574:;
    r3 = 0;
    r6 = arg0_r4;
    r5 = "%s is not found!";
    r4 = 0;
    r3 = LogErr(0, 0, "%s is not found!", arg0_r4); // [0x8007A05C]
label_80071590:;
    r3 = -1;
label_80071594:;
    r0 = stack_0x24;
    return; // r3 = -1
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdLoadAramSub(unsigned long)
// Unit: CId.obj | Address: 0x800715A8 | Size: 0x94 bytes
// ============================================================================
/* [0x800715A8] */ void cIdCtrl::IdLoadAramSub(cIdCtrl* this_r3, unsigned long arg0_r4) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r0 = *(uint32_t*)(this_r3 + 0xC);
    if (*(uint32_t*)(this_r3 + 0xC) <= 9) goto label_800715E4;
    r3 = 0;
    r5 = "file number over %d.";
    r4 = 0;
    r6 = 10;
    r3 = LogErr(0, 0, "file number over %d.", 10); // [0x8007A05C]
    r3 = 0;
    goto label_8007162C;
label_800715E4:;
    if (0 != 0) goto label_80071604;
    if (*(uint32_t*)(this_r3 + 0xC) != 0) goto label_80071628;
    r3 = 0;
    r5 = "address unknown.";
    goto label_80071614;
label_80071604:;
    if (*(uint32_t*)(this_r3 + 0xC) >= 0) goto label_80071628;
    r3 = 0;
    r5 = "address is not ARAM.";
label_80071614:;
    r4 = 0;
    r3 = LogErr(0, 0, "address is not ARAM.", 10); // [0x8007A05C]
    r3 = 0;
    goto label_8007162C;
label_80071628:;
    r3 = 1;
label_8007162C:;
    r0 = stack_0x0C;
    return; // r3 = 1
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdLoadAramSub2(unsigned long, unsigned long)
// Unit: CId.obj | Address: 0x8007163C | Size: 0x58 bytes
// ============================================================================
/* [0x8007163C] */ void cIdCtrl::IdLoadAramSub2(cIdCtrl* this_r3, unsigned long arg0_r4, unsigned long arg1_r5) {
    r8 = *(uint32_t*)(this_r3 + 0xC);
    r9 = *(uint32_t*)(this_r3 + 0xC) + (-1);
    if (*(uint32_t*)(this_r3 + 0xC) == 0) goto label_80071670;
    r7 = this_r3 + (16);
    r11 = this_r3 + (56);
    r0 = (r0 + r10);
    goto label_80071678;
label_80071670:;
    *(uint32_t*)(this_r3 + 0x10) = arg0_r4;
    r11 = this_r3 + (56);
label_80071678:;
    r0 = *(uint32_t*)(this_r3 + 0xC);
    r9 = *(uint32_t*)(this_r3 + 0xC);
    r9 = *(uint32_t*)(this_r3 + 0xC) + (1);
    *(uint32_t*)(this_r3 + 0xC) = (*(uint32_t*)(this_r3 + 0xC) + 1);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdSetNum(IDData *, long, long, long)
// Unit: CId.obj | Address: 0x80071694 | Size: 0xE4 bytes
// ============================================================================
/* [0x80071694] */ void cIdCtrl::IdSetNum(cIdCtrl* this_r3, IDData * arg0_r4, long arg1_r5, long arg2_r6, long arg3_r7) {
    r0 = arg2_r6;
    r10 = 1;
    if (arg1_r5 >= 0) goto label_800716B4;
label_800716AC:;
    if (arg1_r5 >= 0) goto label_800716AC;
label_800716B4:;
    if (arg1_r5 >= 0) goto label_800716F0;
    r8 = 0x66666667u;
label_800716C8:;
    r9 = *(uint8_t*)(arg0_r4 + 0x71);
    *(uint8_t*)(arg0_r4 + 0x71) = *(uint8_t*)(arg0_r4 + 0x71);
    r4 = arg0_r4 + (156);
    r10 = (arg2_r6 - r11);
    if (1 != 0) goto label_800716C8;
    return; // r3 = this_r3
label_800716F0:;
    r8 = 0x66666667u;
label_80071700:;
    if (r11 <= 9) goto label_80071710;
    r11 = 9;
label_80071710:;
    if (arg3_r7 != 0) goto label_80071728;
    if (9 != 0) goto label_80071728;
    if ((arg2_r6 - r11) != 1) goto label_80071748;
label_80071728:;
    r9 = *(uint8_t*)((arg0_r4 + 156) + 0x71);
    r7 = 1;
    r0 = *(int16_t*)((arg0_r4 + 156) + 0x22);
    r9 = *(uint8_t*)((arg0_r4 + 156) + 0x71) | 0x0007u;
    r0 = (*(int16_t*)((arg0_r4 + 156) + 0x22) + 9);
    *(uint8_t*)((arg0_r4 + 156) + 0x71) = *(uint8_t*)((arg0_r4 + 156) + 0x71);
    *(uint16_t*)((arg0_r4 + 156) + 0x72) = (*(int16_t*)((arg0_r4 + 156) + 0x22) + 9);
    goto label_80071754;
label_80071748:;
    r0 = *(uint8_t*)((arg0_r4 + 156) + 0x71);
    *(uint8_t*)((arg0_r4 + 156) + 0x71) = *(uint8_t*)((arg0_r4 + 156) + 0x71);
label_80071754:;
    r4 = (arg0_r4 + 156) + (156);
    r10 = (*(uint8_t*)((arg0_r4 + 156) + 0x71) - *(uint8_t*)((arg0_r4 + 156) + 0x71));
    r5 = (arg1_r5 - 9);
    if ((arg2_r6 - r11) != 1) goto label_80071700;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdSetAlign(IDData *, unsigned long, long)
// Unit: CId.obj | Address: 0x80071778 | Size: 0x114 bytes
// ============================================================================
/* [0x80071778] */ void cIdCtrl::IdSetAlign(cIdCtrl* this_r3, IDData * arg0_r4, unsigned long arg1_r5, long arg2_r6) {
    // Stack frame allocated: 64 bytes
    stack_0x30 = f30;
    stack_0x38 = f31;
    stack_0x44 = r0;
    r31 = arg0_r4;
    r28 = arg1_r5;
    f12 = *(float*)0x80168968;
    r3 = 0;
    r29 = arg2_r6;
    if (r0 <= 0) goto label_80071870;
    f31 = *(float*)(arg0_r4 + 0x50);
    if (0 >= arg2_r6) goto label_8007181C;
    f30 = *(double*)0x80168970;
    r30 = arg2_r6;
label_800717C8:;
    r4 = *(int16_t*)(arg0_r4 + 0x72);
    r3 = arg1_r5;
    r3 = TEXGet(); // [0x80127870]
    r3 = *(uint32_t*)(ret_800717D0 + 0x0);
    f12 = *(float*)(arg0_r4 + 0x50);
    r0 = *(uint16_t*)(*(uint32_t*)(ret_800717D0 + 0x0) + 0x2);
    *(uint16_t*)(arg0_r4 + 0x58) = *(uint16_t*)(*(uint32_t*)(ret_800717D0 + 0x0) + 0x2);
    r9 = *(uint16_t*)(*(uint32_t*)(ret_800717D0 + 0x0) + 0x0);
    *(float*)(arg0_r4 + 0x50) = *(float*)(arg0_r4 + 0x50);
    *(uint16_t*)(arg0_r4 + 0x5A) = *(uint16_t*)(*(uint32_t*)(ret_800717D0 + 0x0) + 0x0);
    r31 = arg0_r4 + (156);
    r0 = *(uint16_t*)(*(uint32_t*)(ret_800717D0 + 0x0) + 0x2);
    stack_0x14 = *(uint16_t*)(*(uint32_t*)(ret_800717D0 + 0x0) + 0x2);
    stack_0x10 = 0x43300000u;
    f0 = stack_0x10;
    if (0 != arg2_r6) goto label_800717C8;
label_8007181C:;
    r0 = *(uint16_t*)(*(uint32_t*)(ret_800717D0 + 0x0) + 0x2);
    f13 = *(double*)0x80168970;
    stack_0x14 = *(uint16_t*)(*(uint32_t*)(ret_800717D0 + 0x0) + 0x2);
    r31 = (arg0_r4 + 156) + (-156);
    stack_0x10 = 0x43300000u;
    f0 = stack_0x10;
    if (arg2_r6 <= 0) goto label_80071870;
label_8007185C:;
    f0 = *(float*)(((arg0_r4 + 156) + -156) + 0x50);
    *(float*)(((arg0_r4 + 156) + -156) + 0x50) = *(float*)(((arg0_r4 + 156) + -156) + 0x50);
    r31 = ((arg0_r4 + 156) + -156) + (-156);
    if (arg2_r6 >= 0) goto label_8007185C;
label_80071870:;
    r0 = stack_0x44;
    f30 = stack_0x30;
    f31 = stack_0x38;
    return; // r3 = *(uint32_t*)(ret_800717D0 + 0x0)
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::IdSetPrim(IDData *, long)
// Unit: CId.obj | Address: 0x8007188C | Size: 0x4C bytes
// ============================================================================
/* [0x8007188C] */ void cIdCtrl::IdSetPrim(cIdCtrl* this_r3, IDData * arg0_r4, long arg1_r5) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r0 = arg1_r5;
    r30 = arg0_r4;
    if (r0 <= 0) goto label_800718C4;
label_800718B0:;
    r3 = arg0_r4;
    r3 = IDData::IdDataInit(arg0_r4); // [0x80072100]
    r30 = arg0_r4 + (156);
    if (r0 != 0) goto label_800718B0;
label_800718C4:;
    r0 = stack_0x14;
    return; // r3 = ret_800718B4
}

// ============================================================================
// High-Level AST Decompilation: cIdPrim::IdPrimRender(void) const
// Unit: CId.obj | Address: 0x800718D8 | Size: 0x68 bytes
// ============================================================================
/* [0x800718D8] */ void cIdPrim::IdPrimRender(void) const(void) {
    // Stack frame allocated: 64 bytes
    stack_0x3C = r31;
    stack_0x44 = r0;
    r31 = r3;
    r4 = &stack_0x08;
    r0 = *(uint32_t*)(r3 + 0x2C);
    stack_0x34 = *(uint32_t*)(r3 + 0x2C);
    r3 = cIdPrim::IdPrimTexSet(tagTexData &) const(); // [0x80071940]
    r3 = r3;
    r4 = &stack_0x08;
    r3 = cIdPrim::IdPrimSetAttr(tagTexData &) const(); // [0x80071AB8]
    r0 = *(uint32_t*)(r3 + 0x2C);
    if (*(uint32_t*)(r3 + 0x2C) == 0) goto label_80071924;
    r3 = r3;
    r4 = &stack_0x08;
    r3 = cIdPrim::IdPrimDraw(tagTexData &) const(); // [0x80071C84]
    goto label_8007192C;
label_80071924:;
    r3 = r3;
    r3 = cIdPrim::IdPrimDraw(void) const(); // [0x80071EE8]
label_8007192C:;
    r0 = stack_0x44;
    r31 = stack_0x3C;
    return; // r3 = ret_80071928
}

// ============================================================================
// High-Level AST Decompilation: cIdPrim::IdPrimTexSet(tagTexData &) const
// Unit: CId.obj | Address: 0x80071940 | Size: 0xEC bytes
// ============================================================================
/* [0x80071940] */ void cIdPrim::IdPrimTexSet(tagTexData &) const(void) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r31 = r4;
    r29 = r3;
    r30 = *(uint32_t*)(r4 + 0x2C);
    if (*(uint32_t*)(r4 + 0x2C) != 0) goto label_8007196C;
    r3 = 0;
    goto label_80071A18;
label_8007196C:;
    r9 = *(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0);
    r7 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x4);
    r0 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x4) + (-8);
    if ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x4) + -8) > 0x1u) goto label_800719E8;
    r0 = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x23);
    if (*(uint8_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x23) == 0) goto label_800719C0;
    r4 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x8);
    r0 = 0;
    r6 = *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x0);
    r3 = r4;
    r5 = *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x2);
    r8 = 0;
    stack_0x08 = 0;
    r9 = 0;
    r10 = 0;
    r3 = GXInitTexObjCI(); // [0x80122980]
    r3 = r3;
    r4 = r4;
    r3 = cIdPrim::IdTexInitLOD(tagTexData &) const(); // [0x80071A2C]
label_800719C0:;
    r9 = *(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x4);
    r0 = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x4) + 0x2);
    if (*(uint8_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x4) + 0x2) != 1) goto label_80071A14;
    r6 = *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x4) + 0x0);
    r3 = r4 + (32);
    r4 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x4) + 0x8);
    r5 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x4) + 0x4);
    r3 = GXInitTlutObj(); // [0x801231F0]
    goto label_80071A14;
label_800719E8:;
    r4 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x4) + 0x8);
    r3 = r4;
    r6 = *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x4) + 0x0);
    r8 = 0;
    r5 = *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x4) + 0x2);
    r10 = 0;
    r9 = 0;
    r3 = GXInitTexObj(); // [0x8012270C]
    r3 = r3;
    r4 = r4;
    r3 = cIdPrim::IdTexInitLOD(tagTexData &) const(); // [0x80071A2C]
label_80071A14:;
    r3 = 1;
label_80071A18:;
    r0 = stack_0x24;
    return; // r3 = 1
}

// ============================================================================
// High-Level AST Decompilation: cIdPrim::IdTexInitLOD(tagTexData &) const
// Unit: CId.obj | Address: 0x80071A2C | Size: 0x8C bytes
// ============================================================================
/* [0x80071A2C] */ void cIdPrim::IdTexInitLOD(tagTexData &) const(void) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r10 = *(uint32_t*)(r4 + 0x2C);
    r9 = *(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0);
    r29 = r30;
    f0 = *(double*)0x80168978;
    r3 = r4;
    r0 = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x21);
    r4 = 1;
    r11 = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x22);
    r5 = 1;
    stack_0x0C = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x21);
    r6 = 0;
    r7 = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x20);
    r8 = 0;
    stack_0x08 = 0x43300000u;
    f3 = *(float*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x1C);
    f1 = stack_0x08;
    stack_0x0C = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x22);
    stack_0x08 = 0x43300000u;
    f2 = stack_0x08;
    r3 = GXInitTexObjLOD(); // [0x801229C8]
    r0 = stack_0x24;
    return; // r3 = ret_80071AA0
}

// ============================================================================
// High-Level AST Decompilation: cIdPrim::IdPrimSetAttr(tagTexData &) const
// Unit: CId.obj | Address: 0x80071AB8 | Size: 0x1CC bytes
// ============================================================================
/* [0x80071AB8] */ void cIdPrim::IdPrimSetAttr(tagTexData &) const(void) {
    // Stack frame allocated: 64 bytes
    stack_0x44 = r0;
    r30 = r3;
    r31 = r4;
    r3 = 0;
    r3 = GXSetCullMode(); // [0x80120D3C]
    r4 = 3;
    r5 = 1;
    r3 = 0;
    r3 = GXSetZMode(); // [0x80125730]
    r3 = 1;
    r3 = GXSetNumTevStages(); // [0x80125170]
    r3 = 1;
    r3 = GXSetNumChans(); // [0x80122374]
    r5 = 1;
    r3 = 4;
    r4 = 0;
    r6 = 1;
    r7 = 0;
    r8 = 0;
    r9 = 2;
    r3 = GXSetChanCtrl(); // [0x801223B8]
    r0 = *(uint32_t*)(r3 + 0x28);
    r5 = 1;
    if (*(uint32_t*)(r3 + 0x28) != 0) goto label_80071B2C;
    r5 = 5;
label_80071B2C:;
    r6 = 0;
    r3 = 1;
    r4 = 4;
    r3 = GXSetBlendMode(); // [0x80125684]
    r3 = GXClearVtxDesc(); // [0x8011EDD4]
    r3 = 9;
    r4 = 1;
    r3 = GXSetVtxDesc(); // [0x8011E354]
    r3 = 11;
    r4 = 1;
    r3 = GXSetVtxDesc(); // [0x8011E354]
    r3 = 0;
    r4 = 9;
    r5 = 0;
    r6 = 3;
    r7 = 0;
    r3 = GXSetVtxAttrFmt(); // [0x8011EE0C]
    r3 = 0;
    r4 = 11;
    r5 = 1;
    r6 = 5;
    r7 = 0;
    r3 = GXSetVtxAttrFmt(); // [0x8011EE0C]
    r0 = *(uint32_t*)(r4 + 0x2C);
    if (*(uint32_t*)(r4 + 0x2C) == 0) goto label_80071C48;
    r3 = 0;
    r4 = 0;
    r3 = GXSetTevOp(); // [0x801249B8]
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 4;
    r3 = GXSetTevOrder(); // [0x80124F98]
    r9 = *(uint32_t*)(r4 + 0x2C);
    r10 = *(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x4);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x4) + (-8);
    if ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x4) + -8) > 0x1u) goto label_80071BD8;
    r3 = r4 + (32);
    r4 = 0;
    r3 = GXLoadTlut(); // [0x8012327C]
label_80071BD8:;
    r4 = 0;
    r3 = r4;
    r3 = GXLoadTexObj(); // [0x8012319C]
    r3 = &stack_0x08;
    r3 = PSMTXIdentity(); // [0x801000FC]
    r3 = &stack_0x08;
    r4 = 30;
    r5 = 1;
    r3 = GXLoadTexMtxImm(); // [0x80126120]
    r5 = 4;
    r6 = 30;
    r7 = 0;
    r4 = 1;
    r8 = 125;
    r3 = 0;
    r3 = GXSetTexCoordGen2(); // [0x8011F908]
    r3 = 1;
    r3 = GXSetNumTexGens(); // [0x8011FBD8]
    r3 = 13;
    r4 = 1;
    r3 = GXSetVtxDesc(); // [0x8011E354]
    r3 = 0;
    r4 = 13;
    r5 = 1;
    r6 = 3;
    r7 = 8;
    r3 = GXSetVtxAttrFmt(); // [0x8011EE0C]
    goto label_80071C70;
label_80071C48:;
    r4 = 4;
    r3 = 0;
    r3 = GXSetTevOp(); // [0x801249B8]
    r3 = 0;
    r3 = GXSetNumTexGens(); // [0x8011FBD8]
    r3 = 0;
    r4 = 255;
    r5 = 255;
    r6 = 4;
    r3 = GXSetTevOrder(); // [0x80124F98]
label_80071C70:;
    r0 = stack_0x44;
    return; // r3 = ret_80071C6C
}

// ============================================================================
// High-Level AST Decompilation: cIdPrim::IdPrimDraw(tagTexData &) const
// Unit: CId.obj | Address: 0x80071C84 | Size: 0x264 bytes
// ============================================================================
/* [0x80071C84] */ void cIdPrim::IdPrimDraw(tagTexData &) const(void) {
    // Stack frame allocated: 64 bytes
    stack_0x44 = r0;
    r27 = r3;
    f12 = *(float*)0x80168980;
    r11 = r3 + (24);
    f0 = *(float*)(r3 + 0x18);
    f13 = *(float*)0x80168984;
    r26 = r4;
    if (r0 >= 0) goto label_80071CC4;
    goto label_80071CD4;
label_80071CC4:;
    if (r0 > 0) goto label_80071CD4;
label_80071CD4:;
    f0 = *(float*)((r3 + 24) + 0x4);
    if (r0 >= 0) goto label_80071CE8;
    goto label_80071CF8;
label_80071CE8:;
    if (r0 > 0) goto label_80071CF8;
label_80071CF8:;
    f0 = *(float*)((r3 + 24) + 0x8);
    if (r0 >= 0) goto label_80071D0C;
    goto label_80071D1C;
label_80071D0C:;
    if (r0 > 0) goto label_80071D1C;
label_80071D1C:;
    f0 = *(float*)((r3 + 24) + 0xC);
    if (r0 >= 0) goto label_80071D30;
    goto label_80071D40;
label_80071D30:;
    if (r0 > 0) goto label_80071D40;
label_80071D40:;
    f11 = *(float*)0x80168988;
    r10 = (r3 + 24);
    stack_0x10 = f9;
    r8 = &stack_0x18;
    stack_0x14 = f10;
    stack_0x08 = f7;
    stack_0x0C = f8;
    stack_0x20 = *(float*)0x80168984;
    r11 = stack_0x24;
    stack_0x20 = *(float*)0x80168980;
    r4 = 0;
    stack_0x18 = stack_0x24;
    r3 = 128;
    r10 = stack_0x24;
    r11 = 0x80170000u;
    r5 = 4;
    *(uint8_t*)(&stack_0x18 + 0x1) = stack_0x24;
    f0 = stack_0x10;
    stack_0x20 = *(float*)0x80168984;
    r9 = stack_0x24;
    *(uint8_t*)(&stack_0x18 + 0x2) = stack_0x24;
    f0 = stack_0x14;
    stack_0x20 = *(float*)0x80168980;
    r11 = stack_0x24;
    *(uint8_t*)(&stack_0x18 + 0x3) = stack_0x24;
    r0 = stack_0x18;
    stack_0x1C = stack_0x18;
    r31 = stack_0x1D;
    r30 = stack_0x1E;
    r29 = stack_0x1F;
    r3 = GXBegin(); // [0x80120A9C]
    f0 = *(float*)(r3 + 0x8);
    f13 = *(float*)(r3 + 0xC);
    r9 = stack_0x24;
    r0 = *(int16_t*)(r3 + 0x10);
    r10 = *(uint32_t*)(r4 + 0x2C);
    stack_0x20 = *(float*)0x80168980;
    r4 = *(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0);
    r11 = stack_0x24;
    stack_0x20 = *(float*)0x80168988;
    r9 = stack_0x24;
    if (*(int16_t*)(r3 + 0x10) != 0) goto label_80071E28;
    r0 = *(int16_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x2);
label_80071E28:;
    r0 = (*(int16_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x2) + r6);
    r0 = *(int16_t*)(r3 + 0x12);
    if (*(int16_t*)(r3 + 0x12) != 0) goto label_80071E40;
    r0 = *(int16_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x0);
label_80071E40:;
    r0 = (*(int16_t*)(*(uint32_t*)(*(uint32_t*)(r4 + 0x2C) + 0x0) + 0x0) + &stack_0x18);
    r11 = 0;
    *(uint16_t*)0xCC008000 = r6;
    r0 = 255;
    *(uint16_t*)0xCC008000 = &stack_0x18;
    *(uint8_t*)0xCC008000 = r28;
    *(uint8_t*)0xCC008000 = stack_0x1D;
    *(uint8_t*)0xCC008000 = stack_0x1E;
    *(uint8_t*)0xCC008000 = stack_0x1F;
    *(uint16_t*)0xCC008000 = 0;
    *(uint16_t*)0xCC008000 = 0;
    *(uint16_t*)0xCC008000 = r7;
    *(uint16_t*)0xCC008000 = &stack_0x18;
    *(uint8_t*)0xCC008000 = r28;
    *(uint8_t*)0xCC008000 = stack_0x1D;
    *(uint8_t*)0xCC008000 = stack_0x1E;
    *(uint8_t*)0xCC008000 = stack_0x1F;
    *(uint16_t*)0xCC008000 = 255;
    *(uint16_t*)0xCC008000 = 0;
    *(uint16_t*)0xCC008000 = r7;
    *(uint16_t*)0xCC008000 = ret_80071DE0;
    *(uint8_t*)0xCC008000 = r28;
    *(uint8_t*)0xCC008000 = stack_0x1D;
    *(uint8_t*)0xCC008000 = stack_0x1E;
    *(uint8_t*)0xCC008000 = stack_0x1F;
    *(uint16_t*)0xCC008000 = 255;
    *(uint16_t*)0xCC008000 = 255;
    *(uint16_t*)0xCC008000 = r6;
    *(uint16_t*)0xCC008000 = ret_80071DE0;
    *(uint8_t*)0xCC008000 = r28;
    *(uint8_t*)0xCC008000 = stack_0x1D;
    *(uint8_t*)0xCC008000 = stack_0x1E;
    *(uint8_t*)0xCC008000 = stack_0x1F;
    *(uint16_t*)0xCC008000 = 0;
    *(uint16_t*)0xCC008000 = 255;
    r0 = stack_0x44;
    return; // r3 = ret_80071DE0
}

// ============================================================================
// High-Level AST Decompilation: cIdPrim::IdPrimDraw(void) const
// Unit: CId.obj | Address: 0x80071EE8 | Size: 0x218 bytes
// ============================================================================
/* [0x80071EE8] */ void cIdPrim::IdPrimDraw(void) const(void) {
    // Stack frame allocated: 88 bytes
    stack_0x5C = r0;
    f0 = *(float*)(r3 + 0x18);
    f12 = *(float*)0x8016898C;
    r11 = r3 + (24);
    f13 = *(float*)0x80168990;
    if (r0 >= 0) goto label_80071F20;
    goto label_80071F30;
label_80071F20:;
    if (r0 > 0) goto label_80071F30;
label_80071F30:;
    f0 = *(float*)((r3 + 24) + 0x4);
    if (r0 >= 0) goto label_80071F44;
    goto label_80071F54;
label_80071F44:;
    if (r0 > 0) goto label_80071F54;
label_80071F54:;
    f0 = *(float*)((r3 + 24) + 0x8);
    if (r0 >= 0) goto label_80071F68;
    goto label_80071F78;
label_80071F68:;
    if (r0 > 0) goto label_80071F78;
label_80071F78:;
    f0 = *(float*)((r3 + 24) + 0xC);
    if (r0 >= 0) goto label_80071F8C;
    goto label_80071F9C;
label_80071F8C:;
    if (r0 > 0) goto label_80071F9C;
label_80071F9C:;
    f8 = *(float*)0x80168994;
    r8 = &stack_0x18;
    r9 = (r3 + 24);
    stack_0x10 = f10;
    stack_0x14 = f11;
    stack_0x08 = f7;
    stack_0x0C = f9;
    stack_0x28 = *(float*)0x80168990;
    r4 = 0;
    r11 = stack_0x2C;
    stack_0x28 = *(float*)0x8016898C;
    r5 = 4;
    stack_0x18 = stack_0x2C;
    r9 = stack_0x2C;
    r10 = stack_0x2C;
    r28 = stack_0x2C;
    *(uint8_t*)(&stack_0x18 + 0x1) = stack_0x2C;
    r29 = stack_0x2C;
    f0 = stack_0x10;
    f12 = *(float*)(r3 + 0x8);
    f13 = *(float*)(r3 + 0xC);
    r23 = *(uint16_t*)(r3 + 0x12);
    r24 = *(uint16_t*)(r3 + 0x10);
    stack_0x28 = f11;
    r3 = 128;
    r11 = stack_0x2C;
    *(uint8_t*)(&stack_0x18 + 0x2) = stack_0x2C;
    f0 = stack_0x14;
    stack_0x28 = f7;
    r10 = stack_0x2C;
    stack_0x28 = f9;
    *(uint8_t*)(&stack_0x18 + 0x3) = stack_0x2C;
    r28 = stack_0x2C;
    stack_0x28 = f10;
    r30 = stack_0x18;
    r29 = stack_0x2C;
    r24 = (stack_0x2C + *(uint16_t*)(r3 + 0x10));
    stack_0x1C = stack_0x18;
    r23 = (stack_0x2C + *(uint16_t*)(r3 + 0x12));
    r25 = stack_0x1D;
    r27 = stack_0x1E;
    r26 = stack_0x1F;
    r3 = GXBegin(); // [0x80120A9C]
    *(uint16_t*)0xCC008000 = stack_0x2C;
    *(uint16_t*)0xCC008000 = stack_0x2C;
    *(uint8_t*)0xCC008000 = stack_0x18;
    *(uint8_t*)0xCC008000 = stack_0x1D;
    *(uint8_t*)0xCC008000 = stack_0x1E;
    *(uint8_t*)0xCC008000 = stack_0x1F;
    *(uint16_t*)0xCC008000 = (stack_0x2C + *(uint16_t*)(r3 + 0x10));
    *(uint16_t*)0xCC008000 = stack_0x2C;
    *(uint8_t*)0xCC008000 = stack_0x18;
    *(uint8_t*)0xCC008000 = stack_0x1D;
    *(uint8_t*)0xCC008000 = stack_0x1E;
    *(uint8_t*)0xCC008000 = stack_0x1F;
    *(uint16_t*)0xCC008000 = (stack_0x2C + *(uint16_t*)(r3 + 0x10));
    *(uint16_t*)0xCC008000 = (stack_0x2C + *(uint16_t*)(r3 + 0x12));
    *(uint8_t*)0xCC008000 = stack_0x18;
    *(uint8_t*)0xCC008000 = stack_0x1D;
    *(uint8_t*)0xCC008000 = stack_0x1E;
    *(uint8_t*)0xCC008000 = stack_0x1F;
    *(uint16_t*)0xCC008000 = stack_0x2C;
    *(uint16_t*)0xCC008000 = (stack_0x2C + *(uint16_t*)(r3 + 0x12));
    *(uint8_t*)0xCC008000 = stack_0x18;
    *(uint8_t*)0xCC008000 = stack_0x1D;
    *(uint8_t*)0xCC008000 = stack_0x1E;
    *(uint8_t*)0xCC008000 = stack_0x1F;
    r0 = stack_0x5C;
    return; // r3 = ret_80072084
}

// ============================================================================
// High-Level AST Decompilation: IDData::IdDataInit(void)
// Unit: CId.obj | Address: 0x80072100 | Size: 0xDC bytes
// ============================================================================
/* [0x80072100] */ void IDData::IdDataInit(IDData* this_r3) {
    // Stack frame allocated: 24 bytes
    r11 = *(uint32_t*)(this_r3 + 0x0);
    r9 = this_r3 + (80);
    r6 = *(uint32_t*)(this_r3 + 0x4);
    r8 = this_r3 + (16);
    r10 = *(uint32_t*)(this_r3 + 0x8);
    r7 = this_r3 + (96);
    r0 = *(uint32_t*)(this_r3 + 0xC);
    r5 = this_r3 + (56);
    *(uint32_t*)(this_r3 + 0x50) = *(uint32_t*)(this_r3 + 0x0);
    r4 = this_r3 + (132);
    r30 = *(uint32_t*)(this_r3 + 0x5C);
    *(uint32_t*)((this_r3 + 80) + 0xC) = *(uint32_t*)(this_r3 + 0xC);
    *(uint32_t*)((this_r3 + 80) + 0x4) = *(uint32_t*)(this_r3 + 0x4);
    *(uint32_t*)((this_r3 + 80) + 0x8) = *(uint32_t*)(this_r3 + 0x8);
    *(uint32_t*)(this_r3 + 0x5C) = *(uint32_t*)(this_r3 + 0x5C);
    r0 = *(uint8_t*)(this_r3 + 0x20);
    r9 = *(uint8_t*)(this_r3 + 0x21);
    r11 = *(uint16_t*)(this_r3 + 0x22);
    r10 = *(uint16_t*)(this_r3 + 0x26);
    f0 = *(float*)(this_r3 + 0x28);
    f13 = *(float*)(this_r3 + 0x2C);
    f12 = *(float*)(this_r3 + 0x30);
    f11 = *(float*)(this_r3 + 0x34);
    r6 = *(uint16_t*)(this_r3 + 0x4C);
    *(uint8_t*)(this_r3 + 0x70) = *(uint8_t*)(this_r3 + 0x20);
    *(uint8_t*)(this_r3 + 0x71) = *(uint8_t*)(this_r3 + 0x21);
    *(uint16_t*)(this_r3 + 0x72) = *(uint16_t*)(this_r3 + 0x22);
    *(float*)(this_r3 + 0x74) = *(float*)(this_r3 + 0x28);
    *(float*)(this_r3 + 0x78) = *(float*)(this_r3 + 0x2C);
    *(float*)(this_r3 + 0x7C) = *(float*)(this_r3 + 0x30);
    *(float*)(this_r3 + 0x80) = *(float*)(this_r3 + 0x34);
    *(uint16_t*)(this_r3 + 0x94) = *(uint16_t*)(this_r3 + 0x26);
    *(uint16_t*)(this_r3 + 0x96) = *(uint16_t*)(this_r3 + 0x4C);
    r0 = *(uint32_t*)(this_r3 + 0x10);
    r9 = *(uint32_t*)((this_r3 + 16) + 0xC);
    r11 = *(uint32_t*)((this_r3 + 16) + 0x4);
    r10 = *(uint32_t*)((this_r3 + 16) + 0x8);
    stack_0x08 = *(uint32_t*)(this_r3 + 0x5C);
    *(uint32_t*)(this_r3 + 0x60) = *(uint32_t*)(this_r3 + 0x10);
    *(uint32_t*)((this_r3 + 96) + 0xC) = *(uint32_t*)((this_r3 + 16) + 0xC);
    *(uint32_t*)((this_r3 + 96) + 0x4) = *(uint32_t*)((this_r3 + 16) + 0x4);
    *(uint32_t*)((this_r3 + 96) + 0x8) = *(uint32_t*)((this_r3 + 16) + 0x8);
    r0 = *(uint32_t*)(this_r3 + 0x38);
    r9 = *(uint32_t*)((this_r3 + 56) + 0xC);
    r11 = *(uint32_t*)((this_r3 + 56) + 0x4);
    r10 = *(uint32_t*)((this_r3 + 56) + 0x8);
    *(uint32_t*)(this_r3 + 0x84) = *(uint32_t*)(this_r3 + 0x38);
    *(uint32_t*)((this_r3 + 132) + 0xC) = *(uint32_t*)((this_r3 + 56) + 0xC);
    *(uint32_t*)((this_r3 + 132) + 0x4) = *(uint32_t*)((this_r3 + 56) + 0x4);
    *(uint32_t*)((this_r3 + 132) + 0x8) = *(uint32_t*)((this_r3 + 56) + 0x8);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: IDData::IdDataInitReverse(void)
// Unit: CId.obj | Address: 0x800721DC | Size: 0x78 bytes
// ============================================================================
/* [0x800721DC] */ void IDData::IdDataInitReverse(IDData* this_r3) {
    f10 = *(float*)(this_r3 + 0x84);
    r9 = this_r3 + (132);
    f12 = *(float*)(this_r3 + 0x28);
    f11 = *(float*)(this_r3 + 0x2C);
    f13 = *(float*)(this_r3 + 0x30);
    f0 = *(float*)(this_r3 + 0x34);
    r11 = *(uint16_t*)(this_r3 + 0x26);
    r0 = *(uint16_t*)(this_r3 + 0x4C);
    *(float*)(this_r3 + 0x84) = *(float*)(this_r3 + 0x84);
    *(float*)(this_r3 + 0x74) = *(float*)(this_r3 + 0x28);
    *(float*)(this_r3 + 0x78) = *(float*)(this_r3 + 0x2C);
    *(float*)(this_r3 + 0x7C) = *(float*)(this_r3 + 0x30);
    *(float*)(this_r3 + 0x80) = *(float*)(this_r3 + 0x34);
    *(uint16_t*)(this_r3 + 0x94) = *(uint16_t*)(this_r3 + 0x26);
    *(uint16_t*)(this_r3 + 0x96) = *(uint16_t*)(this_r3 + 0x4C);
    f0 = *(float*)((this_r3 + 132) + 0x4);
    f13 = *(float*)((this_r3 + 132) + 0x8);
    f12 = *(float*)((this_r3 + 132) + 0xC);
    *(float*)((this_r3 + 132) + 0x4) = *(float*)((this_r3 + 132) + 0x4);
    *(float*)((this_r3 + 132) + 0x8) = *(float*)((this_r3 + 132) + 0x8);
    *(float*)((this_r3 + 132) + 0xC) = *(float*)((this_r3 + 132) + 0xC);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: IDData::IdDataMove(void)
// Unit: CId.obj | Address: 0x80072254 | Size: 0x208 bytes
// ============================================================================
/* [0x80072254] */ void IDData::IdDataMove(IDData* this_r3) {
    r5 = this_r3;
    r9 = *(uint16_t*)(this_r3 + 0x96);
    r9 = *(uint16_t*)(this_r3 + 0x96) + (-1);
    *(uint16_t*)(this_r3 + 0x96) = (*(uint16_t*)(this_r3 + 0x96) + -1);
    if (r0 <= 0) goto label_80072278;
    r3 = 0;
    return; // r3 = 0
label_80072278:;
    r0 = 0;
    r9 = *(uint8_t*)(this_r3 + 0x71);
    *(uint16_t*)(this_r3 + 0x96) = 0;
    if (r0 == 0) goto label_80072294;
    r0 = *(uint8_t*)(this_r3 + 0x71) | 0x0001u;
    goto label_80072298;
label_80072294:;
label_80072298:;
    *(uint8_t*)(this_r3 + 0x71) = 0;
    r9 = *(uint16_t*)(this_r3 + 0x94);
    if (r0 != 0) goto label_800722CC;
    r0 = *(uint8_t*)(this_r3 + 0x71);
    if (r0 == 0) goto label_800722BC;
    r0 = *(uint8_t*)(this_r3 + 0x71) | 0x0001u;
    goto label_800722C0;
label_800722BC:;
label_800722C0:;
    *(uint8_t*)(this_r3 + 0x71) = *(uint8_t*)(this_r3 + 0x71);
    r3 = 1;
    return; // r3 = 1
label_800722CC:;
    if (r0 <= 0) goto label_800722D8;
    r0 = *(uint16_t*)(this_r3 + 0x94) + (-1);
    *(uint16_t*)(this_r3 + 0x94) = (*(uint16_t*)(this_r3 + 0x94) + -1);
label_800722D8:;
    f11 = *(float*)(this_r3 + 0x50);
    r10 = this_r3 + (96);
    f0 = *(float*)(this_r3 + 0x74);
    r7 = this_r3 + (132);
    f10 = *(float*)(this_r3 + 0x54);
    r11 = *(uint16_t*)(this_r3 + 0x58);
    r0 = *(uint16_t*)(this_r3 + 0x5A);
    f13 = *(float*)(this_r3 + 0x60);
    f12 = *(float*)(this_r3 + 0x78);
    f0 = *(float*)(this_r3 + 0x84);
    r8 = *(uint16_t*)(this_r3 + 0x48);
    r9 = *(uint16_t*)(this_r3 + 0x4A);
    r11 = (*(uint16_t*)(this_r3 + 0x58) + *(uint16_t*)(this_r3 + 0x48));
    *(float*)(this_r3 + 0x54) = *(float*)(this_r3 + 0x54);
    r0 = (*(uint16_t*)(this_r3 + 0x5A) + *(uint16_t*)(this_r3 + 0x4A));
    *(float*)(this_r3 + 0x60) = *(float*)(this_r3 + 0x60);
    *(float*)(this_r3 + 0x50) = *(float*)(this_r3 + 0x50);
    *(uint16_t*)(this_r3 + 0x58) = (*(uint16_t*)(this_r3 + 0x58) + *(uint16_t*)(this_r3 + 0x48));
    *(uint16_t*)(this_r3 + 0x5A) = (*(uint16_t*)(this_r3 + 0x5A) + *(uint16_t*)(this_r3 + 0x4A));
    f10 = *(float*)0x80168998;
    f13 = *(float*)((this_r3 + 132) + 0x4);
    f0 = *(float*)((this_r3 + 96) + 0x4);
    f12 = *(float*)((this_r3 + 96) + 0x8);
    f11 = *(float*)((this_r3 + 96) + 0xC);
    *(float*)((this_r3 + 96) + 0x4) = *(float*)((this_r3 + 96) + 0x4);
    f13 = *(float*)((this_r3 + 132) + 0x8);
    *(float*)((this_r3 + 96) + 0x8) = *(float*)((this_r3 + 96) + 0x8);
    f0 = *(float*)((this_r3 + 132) + 0xC);
    *(float*)((this_r3 + 96) + 0xC) = *(float*)((this_r3 + 96) + 0xC);
    f0 = *(float*)(this_r3 + 0x60);
    if (r0 >= 0) goto label_80072384;
    f0 = *(float*)0x8016899C;
    *(float*)(this_r3 + 0x60) = *(float*)0x8016899C;
    goto label_80072398;
label_80072384:;
    f13 = *(float*)0x801689A0;
    if (r0 <= 0) goto label_80072398;
    *(float*)(this_r3 + 0x60) = *(float*)0x801689A0;
label_80072398:;
    f13 = *(float*)(this_r3 + 0x64);
    f0 = *(float*)0x80168998;
    if (r0 >= 0) goto label_800723B8;
    f0 = *(float*)0x8016899C;
    goto label_800723C8;
label_800723B8:;
    f0 = *(float*)0x801689A0;
    if (r0 <= 0) goto label_800723CC;
label_800723C8:;
    *(float*)(this_r3 + 0x64) = *(float*)0x801689A0;
label_800723CC:;
    f13 = *(float*)(this_r3 + 0x68);
    f0 = *(float*)0x80168998;
    if (r0 >= 0) goto label_800723EC;
    f0 = *(float*)0x8016899C;
    goto label_800723FC;
label_800723EC:;
    f0 = *(float*)0x801689A0;
    if (r0 <= 0) goto label_80072400;
label_800723FC:;
    *(float*)(this_r3 + 0x68) = *(float*)0x801689A0;
label_80072400:;
    f13 = *(float*)(this_r3 + 0x6C);
    f0 = *(float*)0x80168998;
    if (r0 >= 0) goto label_80072420;
    f0 = *(float*)0x8016899C;
    goto label_80072430;
label_80072420:;
    f0 = *(float*)0x801689A0;
    if (r0 <= 0) goto label_80072434;
label_80072430:;
    *(float*)(this_r3 + 0x6C) = *(float*)0x801689A0;
label_80072434:;
    f13 = *(float*)(this_r3 + 0x74);
    r3 = 0;
    f0 = *(float*)(this_r3 + 0x78);
    f12 = *(float*)(this_r3 + 0x7C);
    f11 = *(float*)(this_r3 + 0x80);
    *(float*)(this_r3 + 0x74) = *(float*)(this_r3 + 0x74);
    *(float*)(this_r3 + 0x78) = *(float*)(this_r3 + 0x78);
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetTexPrim(unsigned long, unsigned long)
// Unit: CId.obj | Address: 0x8007245C | Size: 0x8C bytes
// ============================================================================
/* [0x8007245C] */ void cIdMain::SetTexPrim(cIdMain* this_r3, unsigned long arg0_r4, unsigned long arg1_r5) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r31 = this_r3;
    *(uint32_t*)(this_r3 + 0x10) = arg1_r5;
    r11 = arg0_r4 + (4);
    *(uint32_t*)(this_r3 + 0xC) = arg0_r4;
    r0 = *(uint32_t*)(arg0_r4 + 0x0);
    *(uint32_t*)(this_r3 + 0x0) = *(uint32_t*)(arg0_r4 + 0x0);
    if (*(uint32_t*)(arg0_r4 + 0x0) != 0x12280000u) goto label_800724D0;
    r0 = *(uint32_t*)(arg0_r4 + 0x4);
    r11 = (arg0_r4 + 4) + (4);
    r4 = ((arg0_r4 + 4) + 4);
    r5 = *(uint32_t*)(arg0_r4 + 0x4);
    *(uint32_t*)(this_r3 + 0x14) = *(uint32_t*)(arg0_r4 + 0x4);
    r3 = &cId;
    *(uint32_t*)(this_r3 + 0x8) = ((arg0_r4 + 4) + 4);
    r3 = cIdCtrl::IdSetPrim(&cId, ((arg0_r4 + 4) + 4), *(uint32_t*)(arg0_r4 + 0x4)); // [0x8007188C]
    r4 = *(uint32_t*)(this_r3 + 0x10);
    r3 = &cId;
    r3 = cIdCtrl::IdCalcTpl(&cId, *(uint32_t*)(this_r3 + 0x10)); // [0x800710FC]
    r0 = 0;
    r3 = 1;
    *(uint32_t*)(this_r3 + 0x4) = 0;
    goto label_800724D4;
label_800724D0:;
    r3 = 0;
label_800724D4:;
    r0 = stack_0x14;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::PrimSet(long, long)
// Unit: CId.obj | Address: 0x800724E8 | Size: 0x88 bytes
// ============================================================================
/* [0x800724E8] */ void cIdMain::PrimSet(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r29 = arg1_r5;
    if (arg0_r4 <= arg1_r5) goto label_80072510;
    r9 = *(uint32_t*)(this_r3 + 0x14);
    r4 = 0;
    r29 = *(uint32_t*)(this_r3 + 0x14) + (-1);
label_80072510:;
    if (0 >= 0) goto label_8007251C;
    r4 = 0;
label_8007251C:;
    r9 = *(uint32_t*)(this_r3 + 0x14);
    if ((*(uint32_t*)(this_r3 + 0x14) + -1) < *(uint32_t*)(this_r3 + 0x14)) goto label_8007252C;
    r29 = *(uint32_t*)(this_r3 + 0x14) + (-1);
label_8007252C:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r31 = 0;
    r30 = (*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14));
    if (0 > (*(uint32_t*)(this_r3 + 0x14) + -1)) goto label_8007255C;
label_80072544:;
    r3 = (*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14));
    r31 = 0 + (1);
    r3 = IDData::IdDataInit((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14))); // [0x80072100]
    r30 = (*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + (156);
    if ((0 + 1) <= (*(uint32_t*)(this_r3 + 0x14) + -1)) goto label_80072544;
label_8007255C:;
    r0 = stack_0x1C;
    return; // r3 = ret_8007254C
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::PrimReverseSet(long, long)
// Unit: CId.obj | Address: 0x80072570 | Size: 0x88 bytes
// ============================================================================
/* [0x80072570] */ void cIdMain::PrimReverseSet(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r29 = arg1_r5;
    if (arg0_r4 <= arg1_r5) goto label_80072598;
    r9 = *(uint32_t*)(this_r3 + 0x14);
    r4 = 0;
    r29 = *(uint32_t*)(this_r3 + 0x14) + (-1);
label_80072598:;
    if (0 >= 0) goto label_800725A4;
    r4 = 0;
label_800725A4:;
    r9 = *(uint32_t*)(this_r3 + 0x14);
    if ((*(uint32_t*)(this_r3 + 0x14) + -1) < *(uint32_t*)(this_r3 + 0x14)) goto label_800725B4;
    r29 = *(uint32_t*)(this_r3 + 0x14) + (-1);
label_800725B4:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r31 = 0;
    r30 = (*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14));
    if (0 > (*(uint32_t*)(this_r3 + 0x14) + -1)) goto label_800725E4;
label_800725CC:;
    r3 = (*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14));
    r31 = 0 + (1);
    r3 = IDData::IdDataInitReverse((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14))); // [0x800721DC]
    r30 = (*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + (156);
    if ((0 + 1) <= (*(uint32_t*)(this_r3 + 0x14) + -1)) goto label_800725CC;
label_800725E4:;
    r0 = stack_0x1C;
    return; // r3 = ret_800725D4
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::PrimMove(long, long)
// Unit: CId.obj | Address: 0x800725F8 | Size: 0x118 bytes
// ============================================================================
/* [0x800725F8] */ void cIdMain::PrimMove(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    // Stack frame allocated: 64 bytes
    stack_0x44 = r0;
    r27 = arg1_r5;
    r26 = this_r3;
    if (arg0_r4 <= arg1_r5) goto label_80072624;
    r9 = *(uint32_t*)(this_r3 + 0x14);
    r4 = 0;
    r27 = *(uint32_t*)(this_r3 + 0x14) + (-1);
label_80072624:;
    if (0 >= 0) goto label_80072630;
    r4 = 0;
label_80072630:;
    r9 = *(uint32_t*)(this_r3 + 0x14);
    if ((*(uint32_t*)(this_r3 + 0x14) + -1) < *(uint32_t*)(this_r3 + 0x14)) goto label_80072640;
    r27 = *(uint32_t*)(this_r3 + 0x14) + (-1);
label_80072640:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r28 = 0;
    r24 = ((*(uint32_t*)(this_r3 + 0x14) + -1) - 0);
    r25 = 0;
    r30 = (*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14));
    if (0 > (*(uint32_t*)(this_r3 + 0x14) + -1)) goto label_800726EC;
    r29 = &stack_0x08;
    r31 = (*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + (96);
label_8007266C:;
    r0 = *(uint8_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0x11);
    if (0 == (*(uint32_t*)(this_r3 + 0x14) + -1)) goto label_800726C4;
    r4 = *(int16_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0x12);
    r3 = *(uint32_t*)(this_r3 + 0x10);
    r3 = TEXGet(); // [0x80127870]
    r11 = *(uint32_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0x0);
    r4 = ret_80072680;
    r10 = *(uint32_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0x4);
    r3 = &cId;
    r9 = *(uint32_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0x8);
    r5 = (*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + (80);
    r0 = *(uint32_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0xC);
    r6 = &stack_0x08;
    stack_0x08 = *(uint32_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0x0);
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0x8);
    *(uint32_t*)(&stack_0x08 + 0xC) = *(uint32_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0xC);
    r8 = *(uint8_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) - 0x3C);
    r7 = *(uint8_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0x10);
    r3 = cIdCtrl::IdSetPrim(&cId, ret_80072680, ((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 80), &stack_0x08, *(uint8_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + 0x10), *(uint8_t*)(((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) - 0x3C)); // [0x80071014]
label_800726C4:;
    r3 = (*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14));
    r3 = IDData::IdDataMove((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14))); // [0x80072254]
    if (ret_800726C8 == 0) goto label_800726D8;
    r25 = 0 + (1);
label_800726D8:;
    r28 = 0 + (1);
    r31 = ((*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + 96) + (156);
    r30 = (*(uint32_t*)(this_r3 + 0x8) + *(uint32_t*)(this_r3 + 0x14)) + (156);
    if ((0 + 1) <= (*(uint32_t*)(this_r3 + 0x14) + -1)) goto label_8007266C;
label_800726EC:;
    r3 = ((*(uint32_t*)(this_r3 + 0x14) + -1) - 0) + (1);
    r0 = stack_0x44;
    return; // r3 = (((*(uint32_t*)(this_r3 + 0x14) + -1) - 0) + 1)
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetSwitch(long, bool)
// Unit: CId.obj | Address: 0x80072710 | Size: 0x8C bytes
// ============================================================================
/* [0x80072710] */ void cIdMain::SetSwitch(cIdMain* this_r3, long arg0_r4, bool arg1_r5) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072734;
label_80072734:;
    if (0 == 0) goto label_80072770;
    if (arg1_r5 == 0) goto label_8007275C;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r11 = 7;
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint8_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x71) = 7;
    goto label_8007278C;
label_8007275C:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r9 = ((0 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8));
    *(uint8_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8)) + 0x71) = arg1_r5;
    goto label_8007278C;
label_80072770:;
    r6 = arg0_r4;
    r5 = "Primitive %d is inaccurate.";
    r3 = 0;
    r4 = 0;
    r3 = LogWarn(0, 0, "Primitive %d is inaccurate.", arg0_r4); // [0x8007A0A0]
label_8007278C:;
    r0 = stack_0x0C;
    return; // r3 = ret_80072788
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetSwitchSt(long, bool)
// Unit: CId.obj | Address: 0x8007279C | Size: 0x98 bytes
// ============================================================================
/* [0x8007279C] */ void cIdMain::SetSwitchSt(cIdMain* this_r3, long arg0_r4, bool arg1_r5) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_800727C0;
label_800727C0:;
    if (0 == 0) goto label_80072808;
    if (arg1_r5 == 0) goto label_800727EC;
    r11 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    r0 = *(uint8_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x71);
    r0 = *(uint8_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x71) | 0x0002u;
    *(uint8_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x71) = *(uint8_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x71);
    goto label_80072824;
label_800727EC:;
    r11 = *(uint32_t*)(this_r3 + 0x8);
    r9 = ((0 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8));
    r0 = *(uint8_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8)) + 0x71);
    *(uint8_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8)) + 0x71) = *(uint8_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8)) + 0x71);
    goto label_80072824;
label_80072808:;
    r6 = arg0_r4;
    r5 = "Primitive %d is inaccurate.";
    r3 = 0;
    r4 = 0;
    r3 = LogWarn(0, 0, "Primitive %d is inaccurate.", arg0_r4); // [0x8007A0A0]
label_80072824:;
    r0 = stack_0x0C;
    return; // r3 = ret_80072820
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetSwitchEnd(long, bool)
// Unit: CId.obj | Address: 0x80072834 | Size: 0x98 bytes
// ============================================================================
/* [0x80072834] */ void cIdMain::SetSwitchEnd(cIdMain* this_r3, long arg0_r4, bool arg1_r5) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072858;
label_80072858:;
    if (0 == 0) goto label_800728A0;
    if (arg1_r5 == 0) goto label_80072884;
    r11 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    r0 = *(uint8_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x71);
    r0 = *(uint8_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x71) | 0x0004u;
    *(uint8_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x71) = *(uint8_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x71);
    goto label_800728BC;
label_80072884:;
    r11 = *(uint32_t*)(this_r3 + 0x8);
    r9 = ((0 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8));
    r0 = *(uint8_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8)) + 0x71);
    *(uint8_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8)) + 0x71) = *(uint8_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8)) + 0x71);
    goto label_800728BC;
label_800728A0:;
    r6 = arg0_r4;
    r5 = "Primitive %d is inaccurate.";
    r3 = 0;
    r4 = 0;
    r3 = LogWarn(0, 0, "Primitive %d is inaccurate.", arg0_r4); // [0x8007A0A0]
label_800728BC:;
    r0 = stack_0x0C;
    return; // r3 = ret_800728B8
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::GetTexSize(long, long &, long &) const
// Unit: CId.obj | Address: 0x800728CC | Size: 0x60 bytes
// ============================================================================
/* [0x800728CC] */ void cIdMain::GetTexSize(long, long &, long &) const(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = *(uint32_t*)(r3 + 0x8);
    r3 = *(uint32_t*)(r3 + 0x10);
    r31 = r5;
    r30 = r6;
    r9 = (*(uint32_t*)(r3 + 0x8) + r4);
    r4 = *(int16_t*)((*(uint32_t*)(r3 + 0x8) + r4) + 0x72);
    r3 = TEXGet(); // [0x80127870]
    r3 = ret_800728F8;
    if (r0 == 0) goto label_80072918;
    r9 = *(uint32_t*)(ret_800728F8 + 0x0);
    r0 = *(uint16_t*)(*(uint32_t*)(ret_800728F8 + 0x0) + 0x2);
    *(uint32_t*)(r5 + 0x0) = *(uint16_t*)(*(uint32_t*)(ret_800728F8 + 0x0) + 0x2);
    r11 = *(uint16_t*)(*(uint32_t*)(ret_800728F8 + 0x0) + 0x0);
    *(uint32_t*)(r6 + 0x0) = *(uint16_t*)(*(uint32_t*)(ret_800728F8 + 0x0) + 0x0);
label_80072918:;
    r0 = stack_0x14;
    return; // r3 = ret_800728F8
}

// ============================================================================
// High-Level AST Decompilation: __static_initialization_and_destruction_0
// Unit: CId.obj | Address: 0x8007292C | Size: 0x4C bytes
// ============================================================================
/* [0x8007292C] */ void __static_initialization_and_destruction_0(void) {
    r0 = 0;
    r0 = 0 | 0xFFFFu;
    if (r3 == 0) goto label_80072964;
    r9 = &vtable_cIdCtrl;
    r11 = &cId;
    r0 = 0;
    *(uint32_t*)(&cId + 0x60) = &vtable_cIdCtrl;
    cId = 0;
    return; // r3 = r3
label_80072964:;
    r9 = &vtable_cIdCtrl;
    *(uint32_t*)0x80188820 = &vtable_cIdCtrl;
    return; // r3 = r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::flagOn(unsigned long)
// Unit: CId.obj | Address: 0x80072978 | Size: 0x10 bytes
// ============================================================================
/* [0x80072978] */ void cIdMain::flagOn(cIdMain* this_r3, unsigned long arg0_r4) {
    r0 = *(uint32_t*)(this_r3 + 0x4);
    *(uint32_t*)(this_r3 + 0x4) = *(uint32_t*)(this_r3 + 0x4);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::flagOff(unsigned long)
// Unit: CId.obj | Address: 0x80072988 | Size: 0x10 bytes
// ============================================================================
/* [0x80072988] */ void cIdMain::flagOff(cIdMain* this_r3, unsigned long arg0_r4) {
    r0 = *(uint32_t*)(this_r3 + 0x4);
    *(uint32_t*)(this_r3 + 0x4) = arg0_r4;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::flagCk(unsigned long)
// Unit: CId.obj | Address: 0x80072998 | Size: 0xC bytes
// ============================================================================
/* [0x80072998] */ void cIdMain::flagCk(cIdMain* this_r3, unsigned long arg0_r4) {
    r3 = *(uint32_t*)(this_r3 + 0x4);
    return; // r3 = *(uint32_t*)(this_r3 + 0x4)
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::numCheck(long)
// Unit: CId.obj | Address: 0x800729A4 | Size: 0x20 bytes
// ============================================================================
/* [0x800729A4] */ void cIdMain::numCheck(cIdMain* this_r3, long arg0_r4) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_800729BC;
    r3 = 1;
label_800729BC:;
    r3 = 0;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetColor(long, cColor &)
// Unit: CId.obj | Address: 0x800729C4 | Size: 0x54 bytes
// ============================================================================
/* [0x800729C4] */ void cIdMain::SetColor(cIdMain* this_r3, long arg0_r4, cColor & arg1_r5) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_800729DC;
label_800729DC:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r11 = *(uint32_t*)(arg1_r5 + 0x0);
    r8 = *(uint32_t*)(arg1_r5 + 0xC);
    r7 = *(uint32_t*)(arg1_r5 + 0x4);
    r10 = *(uint32_t*)(arg1_r5 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint32_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x60) = *(uint32_t*)(arg1_r5 + 0x0);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8)) + (96);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 96) + 0xC) = *(uint32_t*)(arg1_r5 + 0xC);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 96) + 0x4) = *(uint32_t*)(arg1_r5 + 0x4);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 96) + 0x8) = *(uint32_t*)(arg1_r5 + 0x8);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetColorAll(cColor &)
// Unit: CId.obj | Address: 0x80072A18 | Size: 0x58 bytes
// ============================================================================
/* [0x80072A18] */ void cIdMain::SetColorAll(cIdMain* this_r3, cColor & arg0_r4) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r6 = 0;
    r5 = 0;
label_80072A2C:;
    r11 = *(uint32_t*)(this_r3 + 0x8);
    r6 = 0 + (1);
    r10 = *(uint32_t*)(arg0_r4 + 0x0);
    r0 = *(uint32_t*)(arg0_r4 + 0xC);
    r11 = (0 + *(uint32_t*)(this_r3 + 0x8));
    r8 = *(uint32_t*)(arg0_r4 + 0x4);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8)) + (96);
    r7 = *(uint32_t*)(arg0_r4 + 0x8);
    r5 = 0 + (156);
    *(uint32_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x60) = *(uint32_t*)(arg0_r4 + 0x0);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 96) + 0xC) = *(uint32_t*)(arg0_r4 + 0xC);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 96) + 0x4) = *(uint32_t*)(arg0_r4 + 0x4);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 96) + 0x8) = *(uint32_t*)(arg0_r4 + 0x8);
    r0 = *(uint32_t*)(this_r3 + 0x14);
    if ((0 + 1) < *(uint32_t*)(this_r3 + 0x14)) goto label_80072A2C;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetColAdd(long, cColor &)
// Unit: CId.obj | Address: 0x80072A70 | Size: 0x54 bytes
// ============================================================================
/* [0x80072A70] */ void cIdMain::SetColAdd(cIdMain* this_r3, long arg0_r4, cColor & arg1_r5) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072A88;
label_80072A88:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r11 = *(uint32_t*)(arg1_r5 + 0x0);
    r8 = *(uint32_t*)(arg1_r5 + 0xC);
    r7 = *(uint32_t*)(arg1_r5 + 0x4);
    r10 = *(uint32_t*)(arg1_r5 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint32_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x84) = *(uint32_t*)(arg1_r5 + 0x0);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8)) + (132);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 132) + 0xC) = *(uint32_t*)(arg1_r5 + 0xC);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 132) + 0x4) = *(uint32_t*)(arg1_r5 + 0x4);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 132) + 0x8) = *(uint32_t*)(arg1_r5 + 0x8);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetColAddAll(cColor &)
// Unit: CId.obj | Address: 0x80072AC4 | Size: 0x58 bytes
// ============================================================================
/* [0x80072AC4] */ void cIdMain::SetColAddAll(cIdMain* this_r3, cColor & arg0_r4) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r6 = 0;
    r5 = 0;
label_80072AD8:;
    r11 = *(uint32_t*)(this_r3 + 0x8);
    r6 = 0 + (1);
    r10 = *(uint32_t*)(arg0_r4 + 0x0);
    r0 = *(uint32_t*)(arg0_r4 + 0xC);
    r11 = (0 + *(uint32_t*)(this_r3 + 0x8));
    r8 = *(uint32_t*)(arg0_r4 + 0x4);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8)) + (132);
    r7 = *(uint32_t*)(arg0_r4 + 0x8);
    r5 = 0 + (156);
    *(uint32_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x84) = *(uint32_t*)(arg0_r4 + 0x0);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 132) + 0xC) = *(uint32_t*)(arg0_r4 + 0xC);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 132) + 0x4) = *(uint32_t*)(arg0_r4 + 0x4);
    *(uint32_t*)(((0 + *(uint32_t*)(this_r3 + 0x8)) + 132) + 0x8) = *(uint32_t*)(arg0_r4 + 0x8);
    r0 = *(uint32_t*)(this_r3 + 0x14);
    if ((0 + 1) < *(uint32_t*)(this_r3 + 0x14)) goto label_80072AD8;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetPosX(long, long)
// Unit: CId.obj | Address: 0x80072B1C | Size: 0x60 bytes
// ============================================================================
/* [0x80072B1C] */ void cIdMain::SetPosX(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    // Stack frame allocated: 16 bytes
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072B38;
label_80072B38:;
    if (0 == 0) goto label_80072B74;
    stack_0x0C = *(uint32_t*)(this_r3 + 0x14);
    stack_0x08 = 0x43300000u;
    f13 = *(double*)0x801689E0;
    f0 = stack_0x08;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r10 = (r10 + *(uint32_t*)(this_r3 + 0x8));
    *(float*)((r10 + *(uint32_t*)(this_r3 + 0x8)) + 0x50) = stack_0x08;
label_80072B74:;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetPosY(long, long)
// Unit: CId.obj | Address: 0x80072B7C | Size: 0x60 bytes
// ============================================================================
/* [0x80072B7C] */ void cIdMain::SetPosY(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    // Stack frame allocated: 16 bytes
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072B98;
label_80072B98:;
    if (0 == 0) goto label_80072BD4;
    stack_0x0C = *(uint32_t*)(this_r3 + 0x14);
    stack_0x08 = 0x43300000u;
    f13 = *(double*)0x801689E8;
    f0 = stack_0x08;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r10 = (r10 + *(uint32_t*)(this_r3 + 0x8));
    *(float*)((r10 + *(uint32_t*)(this_r3 + 0x8)) + 0x54) = stack_0x08;
label_80072BD4:;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetPos(long, long, long)
// Unit: CId.obj | Address: 0x80072BDC | Size: 0xB4 bytes
// ============================================================================
/* [0x80072BDC] */ void cIdMain::SetPos(cIdMain* this_r3, long arg0_r4, long arg1_r5, long arg2_r6) {
    // Stack frame allocated: 16 bytes
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072BF8;
label_80072BF8:;
    if (0 == 0) goto label_80072C34;
    stack_0x0C = *(uint32_t*)(this_r3 + 0x14);
    stack_0x08 = 0x43300000u;
    f13 = *(double*)0x801689F0;
    f0 = stack_0x08;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r10 = (r10 + *(uint32_t*)(this_r3 + 0x8));
    *(float*)((r10 + *(uint32_t*)(this_r3 + 0x8)) + 0x50) = stack_0x08;
label_80072C34:;
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072C4C;
label_80072C4C:;
    if (0 == 0) goto label_80072C88;
    stack_0x0C = *(uint32_t*)(this_r3 + 0x14);
    stack_0x08 = 0x43300000u;
    f13 = *(double*)0x801689F0;
    f0 = stack_0x08;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r10 = ((r10 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8));
    *(float*)(((r10 + *(uint32_t*)(this_r3 + 0x8)) + *(uint32_t*)(this_r3 + 0x8)) + 0x54) = stack_0x08;
label_80072C88:;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetId(long, long)
// Unit: CId.obj | Address: 0x80072C90 | Size: 0x34 bytes
// ============================================================================
/* [0x80072C90] */ void cIdMain::SetId(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072CA8;
label_80072CA8:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x72) = arg1_r5;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetSwitchAll(bool)
// Unit: CId.obj | Address: 0x80072CC4 | Size: 0x5C bytes
// ============================================================================
/* [0x80072CC4] */ void cIdMain::SetSwitchAll(cIdMain* this_r3, bool arg0_r4) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r30 = this_r3;
    r31 = 0;
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r29 = arg0_r4;
    if (0 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072D0C;
label_80072CEC:;
    r4 = 0;
    r3 = this_r3;
    r5 = arg0_r4;
    r31 = 0 + (1);
    r3 = cIdMain::SetSwitch(this_r3, 0, arg0_r4); // [0x80072710]
    r0 = *(uint32_t*)(this_r3 + 0x14);
    if ((0 + 1) < *(uint32_t*)(this_r3 + 0x14)) goto label_80072CEC;
label_80072D0C:;
    r0 = stack_0x1C;
    return; // r3 = ret_80072CFC
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetSwitchStEnd(long, bool, bool)
// Unit: CId.obj | Address: 0x80072D20 | Size: 0x44 bytes
// ============================================================================
/* [0x80072D20] */ void cIdMain::SetSwitchStEnd(cIdMain* this_r3, long arg0_r4, bool arg1_r5, bool arg2_r6) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r30 = this_r3;
    r29 = arg0_r4;
    r28 = arg2_r6;
    r3 = cIdMain::SetSwitchSt(this_r3, arg0_r4, arg1_r5); // [0x8007279C]
    r3 = this_r3;
    r4 = arg0_r4;
    r5 = arg2_r6;
    r3 = cIdMain::SetSwitchEnd(this_r3, arg0_r4, arg2_r6); // [0x80072834]
    r0 = stack_0x1C;
    return; // r3 = ret_80072D4C
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetW(long, long)
// Unit: CId.obj | Address: 0x80072D64 | Size: 0x34 bytes
// ============================================================================
/* [0x80072D64] */ void cIdMain::SetW(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072D7C;
label_80072D7C:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x58) = arg1_r5;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetH(long, long)
// Unit: CId.obj | Address: 0x80072D98 | Size: 0x34 bytes
// ============================================================================
/* [0x80072D98] */ void cIdMain::SetH(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072DB0;
label_80072DB0:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x5A) = arg1_r5;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetWH(long, long, long)
// Unit: CId.obj | Address: 0x80072DCC | Size: 0x64 bytes
// ============================================================================
/* [0x80072DCC] */ void cIdMain::SetWH(cIdMain* this_r3, long arg0_r4, long arg1_r5, long arg2_r6) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072DE4;
label_80072DE4:;
    if (0 == 0) goto label_80072DFC;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x58) = arg1_r5;
label_80072DFC:;
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072E14;
label_80072E14:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x5A) = arg2_r6;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetTimerSt(long, long)
// Unit: CId.obj | Address: 0x80072E30 | Size: 0x34 bytes
// ============================================================================
/* [0x80072E30] */ void cIdMain::SetTimerSt(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072E48;
label_80072E48:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x96) = arg1_r5;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetTimerStAll(long)
// Unit: CId.obj | Address: 0x80072E64 | Size: 0x38 bytes
// ============================================================================
/* [0x80072E64] */ void cIdMain::SetTimerStAll(cIdMain* this_r3, long arg0_r4) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r11 = 0;
    r10 = 0;
label_80072E78:;
    r9 = *(uint32_t*)(this_r3 + 0x8);
    r11 = 0 + (1);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x96) = arg0_r4;
    r10 = 0 + (156);
    r0 = *(uint32_t*)(this_r3 + 0x14);
    if ((0 + 1) < *(uint32_t*)(this_r3 + 0x14)) goto label_80072E78;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetTimer(long, long)
// Unit: CId.obj | Address: 0x80072E9C | Size: 0x34 bytes
// ============================================================================
/* [0x80072E9C] */ void cIdMain::SetTimer(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072EB4;
label_80072EB4:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x94) = arg1_r5;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetTimerAll(long)
// Unit: CId.obj | Address: 0x80072ED0 | Size: 0x38 bytes
// ============================================================================
/* [0x80072ED0] */ void cIdMain::SetTimerAll(cIdMain* this_r3, long arg0_r4) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r11 = 0;
    r10 = 0;
label_80072EE4:;
    r9 = *(uint32_t*)(this_r3 + 0x8);
    r11 = 0 + (1);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x94) = arg0_r4;
    r10 = 0 + (156);
    r0 = *(uint32_t*)(this_r3 + 0x14);
    if ((0 + 1) < *(uint32_t*)(this_r3 + 0x14)) goto label_80072EE4;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::GetSwitch(long) const
// Unit: CId.obj | Address: 0x80072F08 | Size: 0x18 bytes
// ============================================================================
/* [0x80072F08] */ void cIdMain::GetSwitch(long) const(void) {
    r0 = *(uint32_t*)(r3 + 0x8);
    r4 = (r4 + *(uint32_t*)(r3 + 0x8));
    r3 = *(uint8_t*)((r4 + *(uint32_t*)(r3 + 0x8)) + 0x71);
    return; // r3 = *(uint8_t*)((r4 + *(uint32_t*)(r3 + 0x8)) + 0x71)
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::GetPosX(long) const
// Unit: CId.obj | Address: 0x80072F20 | Size: 0x28 bytes
// ============================================================================
/* [0x80072F20] */ void cIdMain::GetPosX(long) const(void) {
    // Stack frame allocated: 16 bytes
    r0 = *(uint32_t*)(r3 + 0x8);
    r4 = (r4 + *(uint32_t*)(r3 + 0x8));
    f0 = *(float*)((r4 + *(uint32_t*)(r3 + 0x8)) + 0x50);
    stack_0x08 = f13;
    r3 = stack_0x0C;
    return; // r3 = stack_0x0C
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::GetPosY(long) const
// Unit: CId.obj | Address: 0x80072F48 | Size: 0x28 bytes
// ============================================================================
/* [0x80072F48] */ void cIdMain::GetPosY(long) const(void) {
    // Stack frame allocated: 16 bytes
    r0 = *(uint32_t*)(r3 + 0x8);
    r4 = (r4 + *(uint32_t*)(r3 + 0x8));
    f0 = *(float*)((r4 + *(uint32_t*)(r3 + 0x8)) + 0x54);
    stack_0x08 = f13;
    r3 = stack_0x0C;
    return; // r3 = stack_0x0C
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::GetW(long) const
// Unit: CId.obj | Address: 0x80072F70 | Size: 0x14 bytes
// ============================================================================
/* [0x80072F70] */ void cIdMain::GetW(long) const(void) {
    r0 = *(uint32_t*)(r3 + 0x8);
    r4 = (r4 + *(uint32_t*)(r3 + 0x8));
    r3 = *(int16_t*)((r4 + *(uint32_t*)(r3 + 0x8)) + 0x58);
    return; // r3 = *(int16_t*)((r4 + *(uint32_t*)(r3 + 0x8)) + 0x58)
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::GetH(long) const
// Unit: CId.obj | Address: 0x80072F84 | Size: 0x14 bytes
// ============================================================================
/* [0x80072F84] */ void cIdMain::GetH(long) const(void) {
    r0 = *(uint32_t*)(r3 + 0x8);
    r4 = (r4 + *(uint32_t*)(r3 + 0x8));
    r3 = *(int16_t*)((r4 + *(uint32_t*)(r3 + 0x8)) + 0x5A);
    return; // r3 = *(int16_t*)((r4 + *(uint32_t*)(r3 + 0x8)) + 0x5A)
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::GetMaxPrim(void) const
// Unit: CId.obj | Address: 0x80072F98 | Size: 0x8 bytes
// ============================================================================
/* [0x80072F98] */ void cIdMain::GetMaxPrim(void) const(void) {
    r3 = *(uint32_t*)(r3 + 0x14);
    return; // r3 = *(uint32_t*)(r3 + 0x14)
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::GetTexAddr(void) const
// Unit: CId.obj | Address: 0x80072FA0 | Size: 0x8 bytes
// ============================================================================
/* [0x80072FA0] */ void cIdMain::GetTexAddr(void) const(void) {
    r3 = *(uint32_t*)(r3 + 0x10);
    return; // r3 = *(uint32_t*)(r3 + 0x10)
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::GetMemAddr(void) const
// Unit: CId.obj | Address: 0x80072FA8 | Size: 0x8 bytes
// ============================================================================
/* [0x80072FA8] */ void cIdMain::GetMemAddr(void) const(void) {
    r3 = *(uint32_t*)(r3 + 0xC);
    return; // r3 = *(uint32_t*)(r3 + 0xC)
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::AddPosX(long, float)
// Unit: CId.obj | Address: 0x80072FB0 | Size: 0x3C bytes
// ============================================================================
/* [0x80072FB0] */ void cIdMain::AddPosX(cIdMain* this_r3, long arg0_r4, float arg1_f1) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80072FC8;
label_80072FC8:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    f0 = *(float*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x50);
    *(float*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x50) = *(float*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x50);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::AddPosY(long, float)
// Unit: CId.obj | Address: 0x80072FEC | Size: 0x3C bytes
// ============================================================================
/* [0x80072FEC] */ void cIdMain::AddPosY(cIdMain* this_r3, long arg0_r4, float arg1_f1) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80073004;
label_80073004:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    f0 = *(float*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x54);
    *(float*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x54) = *(float*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x54);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::AddW(long, long)
// Unit: CId.obj | Address: 0x80073028 | Size: 0x3C bytes
// ============================================================================
/* [0x80073028] */ void cIdMain::AddW(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_80073040;
label_80073040:;
    r11 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    r0 = *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x58);
    r0 = (*(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x58) + arg1_r5);
    *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x58) = (*(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x58) + arg1_r5);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::AddH(long, long)
// Unit: CId.obj | Address: 0x80073064 | Size: 0x3C bytes
// ============================================================================
/* [0x80073064] */ void cIdMain::AddH(cIdMain* this_r3, long arg0_r4, long arg1_r5) {
    r0 = *(uint32_t*)(this_r3 + 0x14);
    r9 = 0;
    if (arg0_r4 >= *(uint32_t*)(this_r3 + 0x14)) goto label_8007307C;
label_8007307C:;
    r11 = *(uint32_t*)(this_r3 + 0x8);
    r9 = (0 + *(uint32_t*)(this_r3 + 0x8));
    r0 = *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x5A);
    r0 = (*(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x5A) + arg1_r5);
    *(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x5A) = (*(uint16_t*)((0 + *(uint32_t*)(this_r3 + 0x8)) + 0x5A) + arg1_r5);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::cIdMain(void)
// Unit: CId.obj | Address: 0x800730A0 | Size: 0x14 bytes
// ============================================================================
/* [0x800730A0] */ void cIdMain::cIdMain(cIdMain* this_r3) {
    r11 = this_r3;
    r9 = &vtable_cIdMain;
    *(uint32_t*)(this_r3 + 0x18) = &vtable_cIdMain;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::~cIdMain(void)
// Unit: CId.obj | Address: 0x800730B4 | Size: 0x34 bytes
// ============================================================================
/* [0x800730B4] */ void cIdMain::~cIdMain(cIdMain* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = &vtable_cIdMain;
    *(uint32_t*)(this_r3 + 0x18) = &vtable_cIdMain;
    if (r0 == 0) goto label_800730D8;
    r3 = __builtin_delete(); // [0x8009C908]
label_800730D8:;
    r0 = stack_0x0C;
    return; // r3 = ret_800730D4
}

// ============================================================================
// High-Level AST Decompilation: cIdMain::SetNumber(long, long, long, long, long)
// Unit: CId.obj | Address: 0x800730E8 | Size: 0x68 bytes
// ============================================================================
/* [0x800730E8] */ void cIdMain::SetNumber(cIdMain* this_r3, long arg0_r4, long arg1_r5, long arg2_r6, long arg3_r7, long arg4_r8) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r31 = this_r3;
    r4 = *(uint32_t*)(this_r3 + 0x8);
    r29 = arg2_r6;
    r30 = arg4_r8;
    r3 = &cId;
    r4 = (*(uint32_t*)(this_r3 + 0x8) + r28);
    r3 = cIdCtrl::IdSetNum(&cId, (*(uint32_t*)(this_r3 + 0x8) + r28), arg1_r5, arg2_r6, arg3_r7); // [0x80071694]
    if (arg4_r8 == 0) goto label_8007313C;
    r4 = *(uint32_t*)(this_r3 + 0x8);
    r3 = &cId;
    r5 = *(uint32_t*)(this_r3 + 0x10);
    r6 = arg2_r6;
    r4 = (*(uint32_t*)(this_r3 + 0x8) + r28);
    r3 = cIdCtrl::IdSetAlign(&cId, (*(uint32_t*)(this_r3 + 0x8) + r28), *(uint32_t*)(this_r3 + 0x10), arg2_r6); // [0x80071778]
label_8007313C:;
    r0 = stack_0x24;
    return; // r3 = ret_80073138
}

// ============================================================================
// High-Level AST Decompilation: cIdCtrl::~cIdCtrl(void)
// Unit: CId.obj | Address: 0x80073150 | Size: 0x34 bytes
// ============================================================================
/* [0x80073150] */ void cIdCtrl::~cIdCtrl(cIdCtrl* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = &vtable_cIdCtrl;
    *(uint32_t*)(this_r3 + 0x60) = &vtable_cIdCtrl;
    if (r0 == 0) goto label_80073174;
    r3 = __builtin_delete(); // [0x8009C908]
label_80073174:;
    r0 = stack_0x0C;
    return; // r3 = ret_80073170
}

// ============================================================================
// High-Level AST Decompilation: global constructors keyed to cIdCtrl::IdRender(void)
// Unit: CId.obj | Address: 0x80073184 | Size: 0x2C bytes
// ============================================================================
/* [0x80073184] */ void global constructors keyed to cIdCtrl::IdRender(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r4 = 0;
    r3 = 1;
    r4 = 0 | 0xFFFFu;
    r3 = __static_initialization_and_destruction_0(); // [0x8007292C]
    r0 = stack_0x0C;
    return; // r3 = ret_8007319C
}

// ============================================================================
// High-Level AST Decompilation: global destructors keyed to cIdCtrl::IdRender(void)
// Unit: CId.obj | Address: 0x800731B0 | Size: 0x2C bytes
// ============================================================================
/* [0x800731B0] */ void global destructors keyed to cIdCtrl::IdRender(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r4 = 0;
    r3 = 0;
    r4 = 0 | 0xFFFFu;
    r3 = __static_initialization_and_destruction_0(); // [0x8007292C]
    r0 = stack_0x0C;
    return; // r3 = ret_800731C8
}
