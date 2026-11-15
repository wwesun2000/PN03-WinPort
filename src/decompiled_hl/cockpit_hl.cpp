// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: cockpit.obj
// Functions Decompiled: 28
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::CockpitInit(void)
// Unit: cockpit.obj | Address: 0x800753D4 | Size: 0x1C bytes
// ============================================================================
/* [0x800753D4] */ void cCockpitWk::CockpitInit(cCockpitWk* this_r3) {
    r0 = 0;
    *(uint8_t*)(this_r3 + 0x0) = 0;
    *(uint32_t*)(this_r3 + 0x4) = 0;
    *(uint8_t*)(this_r3 + 0x3) = 0;
    *(uint8_t*)(this_r3 + 0x2) = 0;
    *(uint8_t*)(this_r3 + 0x1) = 0;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::CockpitRoomInit(void)
// Unit: cockpit.obj | Address: 0x800753F0 | Size: 0x88 bytes
// ============================================================================
/* [0x800753F0] */ void cCockpitWk::CockpitRoomInit(cCockpitWk* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r30 = this_r3;
    r29 = this_r3 + (12);
    r3 = cCockpitWk::CockpitInit(this_r3); // [0x800753D4]
    r11 = SDA1::pG;
    r3 = (this_r3 + 12);
    r9 = *(uint32_t*)(SDA1::pG + 0xF8);
    r4 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x24);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20);
    r4 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x24) + *(uint32_t*)(SDA1::pG + 0xF8));
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20) + *(uint32_t*)(SDA1::pG + 0xF8));
    r3 = cIdMain::SetTexPrim((this_r3 + 12), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x24) + *(uint32_t*)(SDA1::pG + 0xF8)), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20) + *(uint32_t*)(SDA1::pG + 0xF8))); // [0x8007245C]
    r11 = SDA1::pG;
    r3 = (this_r3 + 12);
    r9 = *(uint32_t*)(SDA1::pG + 0xF8);
    r4 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x2C);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20);
    r4 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x2C) + *(uint32_t*)(SDA1::pG + 0xF8));
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20) + *(uint32_t*)(SDA1::pG + 0xF8));
    r3 = cIdMain::SetTexPrim((this_r3 + 12), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x2C) + *(uint32_t*)(SDA1::pG + 0xF8)), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20) + *(uint32_t*)(SDA1::pG + 0xF8))); // [0x8007245C]
    f0 = *(float*)0x80168B5C;
    f13 = *(float*)0x80168B60;
    *(float*)(this_r3 + 0x44) = *(float*)0x80168B5C;
    *(float*)(this_r3 + 0x48) = *(float*)0x80168B60;
    r0 = stack_0x1C;
    return; // r3 = ret_80075448
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::CockpitMove(void)
// Unit: cockpit.obj | Address: 0x80075478 | Size: 0x60 bytes
// ============================================================================
/* [0x80075478] */ void cCockpitWk::CockpitMove(cCockpitWk* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r31 = this_r3;
    r0 = *(uint32_t*)(this_r3 + 0x4);
    if (r0 == 0) goto label_800754A0;
    r3 = cCockpitWk::comboOn(this_r3); // [0x80075CA4]
    goto label_800754B0;
label_800754A0:;
    if (r0 == 0) goto label_800754B0;
    r3 = this_r3;
    r3 = cCockpitWk::combo(this_r3); // [0x80075F94]
label_800754B0:;
    r0 = *(uint32_t*)(this_r3 + 0x4);
    if (r0 == 0) goto label_800754C4;
    r3 = this_r3;
    r3 = cCockpitWk::comboPoint(this_r3); // [0x80076290]
label_800754C4:;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_800754C0
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::CockpitTrans(void)
// Unit: cockpit.obj | Address: 0x800754D8 | Size: 0x78 bytes
// ============================================================================
/* [0x800754D8] */ void cCockpitWk::CockpitTrans(cCockpitWk* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r31 = this_r3;
    r0 = *(uint32_t*)(SDA1::pG + 0x128);
    if (r0 != 0) goto label_8007553C;
    r0 = *(uint32_t*)(this_r3 + 0x4);
    if (r0 != 0) goto label_8007553C;
    if (r0 == 0) goto label_80075520;
    r3 = this_r3 + (12);
    r4 = 0;
    r5 = -1;
    r3 = cIdMain::PrimMove((this_r3 + 12), 0, -1); // [0x800725F8]
label_80075520:;
    r0 = *(uint32_t*)(this_r3 + 0x4);
    if (r0 == 0) goto label_8007553C;
    r3 = this_r3 + (40);
    r4 = 0;
    r5 = -1;
    r3 = cIdMain::PrimMove((this_r3 + 40), 0, -1); // [0x800725F8]
label_8007553C:;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_80075538
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::getTimer(void)
// Unit: cockpit.obj | Address: 0x80075550 | Size: 0x1EC bytes
// ============================================================================
/* [0x80075550] */ void cCockpitWk::getTimer(cCockpitWk* this_r3) {
    // Stack frame allocated: 56 bytes
    stack_0x3C = r0;
    r11 = *(uint32_t*)0x801876CC;
    r0 = 0x88888889u;
    r9 = &stack_0x08;
    f0 = *(float*)0x80168B64;
    r12 = &stack_0x08;
    stack_0x08 = *(float*)0x80168B64;
    *(float*)(&stack_0x08 + 0xC) = *(float*)0x80168B64;
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x80168B64;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x80168B64;
    if (r31 > 4) goto label_800756E0;
    f13 = *(float*)(this_r3 + 0x48);
    f0 = *(float*)0x80168B68;
    if (r31 <= 4) goto label_800755D8;
    f0 = *(float*)(this_r3 + 0x44);
    f12 = *(float*)0x80168B6C;
    if (r31 != 4) goto label_800755D8;
    *(float*)(this_r3 + 0x44) = *(float*)0x80168B6C;
    goto label_80075604;
label_800755D8:;
    f12 = *(float*)(this_r3 + 0x48);
    f13 = *(float*)0x80168B68;
    if (r31 >= 4) goto label_80075608;
    f0 = *(float*)(this_r3 + 0x44);
    if (r31 != 4) goto label_80075608;
    *(float*)(this_r3 + 0x44) = *(float*)0x80168B68;
label_80075604:;
    *(float*)(this_r3 + 0x48) = *(float*)(this_r3 + 0x44);
label_80075608:;
    f13 = *(float*)(this_r3 + 0x44);
    f12 = *(float*)(this_r3 + 0x48);
    f11 = *(float*)0x80168B6C;
    f0 = *(float*)0x80168B64;
    f12 = *(float*)0x80168B68;
    stack_0x18 = *(float*)0x80168B64;
    r9 = &stack_0x18;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x80168B68;
    r0 = 6;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x80168B68;
    *(float*)(this_r3 + 0x44) = *(float*)(this_r3 + 0x44);
    r4 = this_r3 + (12);
    r29 = (this_r3 + 12);
    r30 = 0;
    r8 = stack_0x18;
    r5 = 1248;
    r6 = -9;
    stack_0x24 = *(float*)0x80168B6C;
    r10 = *(uint32_t*)(&stack_0x18 + 0xC);
    r0 = *(uint32_t*)(&stack_0x18 + 0x4);
    r11 = *(uint32_t*)(&stack_0x18 + 0x8);
    stack_0x08 = stack_0x18;
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)(&stack_0x18 + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)(&stack_0x18 + 0x8);
    *(uint32_t*)(&stack_0x08 + 0xC) = *(uint32_t*)(&stack_0x18 + 0xC);
label_80075684:;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r0 = 0 + (8);
    r11 = 0;
    if ((0 + 8) >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_8007569C;
label_8007569C:;
    if (0 == 0) goto label_800756D0;
    r11 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r10 = stack_0x08;
    r8 = *(uint32_t*)(&stack_0x08 + 0x4);
    r11 = (1248 + *(uint32_t*)((this_r3 + 12) + 0x8));
    r7 = *(uint32_t*)(&stack_0x08 + 0x8);
    r9 = (1248 + *(uint32_t*)((this_r3 + 12) + 0x8)) + (96);
    r0 = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)((1248 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x60) = stack_0x08;
    *(uint32_t*)(((1248 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 96) + 0xC) = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)(((1248 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 96) + 0x4) = *(uint32_t*)(&stack_0x08 + 0x4);
    *(uint32_t*)(((1248 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 96) + 0x8) = *(uint32_t*)(&stack_0x08 + 0x8);
label_800756D0:;
    r5 = 1248 + (156);
    r6 = -9 + (-1);
    r30 = 0 + (1);
    if (0 >= 0) goto label_80075684;
label_800756E0:;
    r30 = this_r3 + (12);
    r5 = r31;
    r4 = 8;
    r3 = (this_r3 + 12);
    r6 = 3;
    r7 = 1;
    r8 = 0;
    r3 = cIdMain::SetNumber((this_r3 + 12), 8, r31, 3, 1, 0); // [0x800730E8]
    r5 = *(uint32_t*)0x801876CC;
    r3 = (this_r3 + 12);
    r4 = 12;
    r6 = 2;
    r7 = 1;
    r8 = 0;
    r5 = (*(uint32_t*)0x801876CC - *(uint32_t*)(&stack_0x08 + 0xC));
    r3 = cIdMain::SetNumber((this_r3 + 12), 12, (*(uint32_t*)0x801876CC - *(uint32_t*)(&stack_0x08 + 0xC)), 2, 1, 0); // [0x800730E8]
    r0 = stack_0x3C;
    return; // r3 = ret_80075724
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::getCount(void)
// Unit: cockpit.obj | Address: 0x8007573C | Size: 0x3F8 bytes
// ============================================================================
/* [0x8007573C] */ void cCockpitWk::getCount(cCockpitWk* this_r3) {
    // Stack frame allocated: 56 bytes
    stack_0x3C = r0;
    r29 = *(uint32_t*)0x801876D0;
    r0 = 0xCCCCCCCDu;
    if (r0 == 0) goto label_80075AA0;
    r30 = this_r3 + (12);
    r3 = (this_r3 + 12);
    r25 = &rect01;
    r4 = 20;
    r5 = 1;
    r28 = (*(uint32_t*)0x801876D0 - 0xCCCCCCCDu);
    r31 = (this_r3 + 12);
    r3 = cIdMain::SetSwitchSt((this_r3 + 12), 20, 1); // [0x8007279C]
    r3 = (this_r3 + 12);
    r4 = 20;
    r5 = 1;
    r3 = cIdMain::SetSwitchEnd((this_r3 + 12), 20, 1); // [0x80072834]
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r7 = 20;
    r11 = ((*(uint32_t*)0x801876D0 - 0xCCCCCCCDu) + (*(uint32_t*)0x801876D0 - 0xCCCCCCCDu));
    r30 = (r27 + &rect01);
    r11 = ((*(uint32_t*)0x801876D0 - 0xCCCCCCCDu) + (*(uint32_t*)0x801876D0 - 0xCCCCCCCDu)) + (33);
    if (20 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_800757C8;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    *(uint16_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xCA2) = (((*(uint32_t*)0x801876D0 - 0xCCCCCCCDu) + (*(uint32_t*)0x801876D0 - 0xCCCCCCCDu)) + 33);
label_800757C8:;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    stack_0x10 = f13;
    r0 = stack_0x14;
    if (20 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075810;
    stack_0x14 = stack_0x14;
    f13 = *(double*)0x80168B70;
    stack_0x10 = 0x43300000u;
    r8 = *(uint32_t*)((this_r3 + 12) + 0x8);
    f0 = stack_0x10;
    *(float*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xC80) = stack_0x10;
label_80075810:;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r11 = *(int16_t*)((r27 + &rect01) + 0x4);
    r10 = *(int16_t*)((r27 + &rect01) + 0x6);
    if (20 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075840;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    *(uint16_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xC88) = *(int16_t*)((r27 + &rect01) + 0x4);
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    if (20 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075840;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    *(uint16_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xC8A) = *(int16_t*)((r27 + &rect01) + 0x6);
label_80075840:;
    r3 = (this_r3 + 12);
    r4 = 22;
    r5 = 1;
    r3 = cIdMain::SetSwitchSt((this_r3 + 12), 22, 1); // [0x8007279C]
    r3 = (this_r3 + 12);
    r4 = 22;
    r5 = 1;
    r3 = cIdMain::SetSwitchEnd((this_r3 + 12), 22, 1); // [0x80072834]
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r7 = 22;
    r11 = ((*(uint32_t*)0x801876D0 - 0xCCCCCCCDu) + (*(uint32_t*)0x801876D0 - 0xCCCCCCCDu));
    r11 = ((*(uint32_t*)0x801876D0 - 0xCCCCCCCDu) + (*(uint32_t*)0x801876D0 - 0xCCCCCCCDu)) + (34);
    if (22 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075880;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    *(uint16_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xDDA) = (((*(uint32_t*)0x801876D0 - 0xCCCCCCCDu) + (*(uint32_t*)0x801876D0 - 0xCCCCCCCDu)) + 34);
label_80075880:;
    f0 = *(float*)((r27 + &rect01) + 0x8);
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    stack_0x10 = *(double*)0x80168B70;
    r0 = stack_0x14;
    if (22 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_800758C8;
    stack_0x14 = stack_0x14;
    f13 = *(double*)0x80168B70;
    stack_0x10 = 0x43300000u;
    r8 = *(uint32_t*)((this_r3 + 12) + 0x8);
    f0 = stack_0x10;
    *(float*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xDB8) = stack_0x10;
label_800758C8:;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r27 = 0;
    if (22 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_800758FC;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8) + (3432);
    *(uint16_t*)((*(uint32_t*)((this_r3 + 12) + 0x8) + 3432) + 0x58) = 0;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    if (22 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_800758FC;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8) + (3432);
    *(uint16_t*)((*(uint32_t*)((this_r3 + 12) + 0x8) + 3432) + 0x5A) = 0;
label_800758FC:;
    r3 = (this_r3 + 12);
    r28 = 0x80172998u;
    r4 = 21;
    r5 = 1;
    r3 = cIdMain::SetSwitchSt((this_r3 + 12), 21, 1); // [0x8007279C]
    r25 = (r26 + r26);
    r3 = (this_r3 + 12);
    r4 = 21;
    r5 = 1;
    r3 = cIdMain::SetSwitchEnd((this_r3 + 12), 21, 1); // [0x80072834]
    r30 = (*(uint32_t*)0x801876D0 + 0x80172998u);
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r7 = 21;
    r11 = (r26 + r26);
    r11 = (r26 + r26) + (33);
    if (21 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075950;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    *(uint16_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xD3E) = ((r26 + r26) + 33);
label_80075950:;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    stack_0x10 = *(double*)0x80168B70;
    r0 = stack_0x14;
    if (21 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075998;
    stack_0x14 = stack_0x14;
    f13 = *(double*)0x80168B70;
    stack_0x10 = 0x43300000u;
    r8 = *(uint32_t*)((this_r3 + 12) + 0x8);
    f0 = stack_0x10;
    *(float*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xD1C) = stack_0x10;
label_80075998:;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r11 = *(int16_t*)((*(uint32_t*)0x801876D0 + 0x80172998u) + 0x4);
    r10 = *(int16_t*)((*(uint32_t*)0x801876D0 + 0x80172998u) + 0x6);
    if (21 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_800759C8;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    *(uint16_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xD24) = *(int16_t*)((*(uint32_t*)0x801876D0 + 0x80172998u) + 0x4);
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    if (21 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_800759C8;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    *(uint16_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xD26) = *(int16_t*)((*(uint32_t*)0x801876D0 + 0x80172998u) + 0x6);
label_800759C8:;
    r3 = (this_r3 + 12);
    r4 = 23;
    r5 = 1;
    r3 = cIdMain::SetSwitchSt((this_r3 + 12), 23, 1); // [0x8007279C]
    r3 = (this_r3 + 12);
    r4 = 23;
    r5 = 1;
    r3 = cIdMain::SetSwitchEnd((this_r3 + 12), 23, 1); // [0x80072834]
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r7 = 23;
    r11 = (r26 + r26) + (34);
    if (23 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075A04;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    *(uint16_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xE76) = ((r26 + r26) + 34);
label_80075A04:;
    f0 = *(float*)((*(uint32_t*)0x801876D0 + 0x80172998u) + 0x8);
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    stack_0x10 = *(double*)0x80168B70;
    r0 = stack_0x14;
    if (23 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075A4C;
    stack_0x14 = stack_0x14;
    f13 = *(double*)0x80168B70;
    stack_0x10 = 0x43300000u;
    r8 = *(uint32_t*)((this_r3 + 12) + 0x8);
    f0 = stack_0x10;
    *(float*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xE54) = stack_0x10;
label_80075A4C:;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    if (23 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075A7C;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8) + (3588);
    *(uint16_t*)((*(uint32_t*)((this_r3 + 12) + 0x8) + 3588) + 0x58) = 0;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    if (23 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075A7C;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8) + (3588);
    *(uint16_t*)((*(uint32_t*)((this_r3 + 12) + 0x8) + 3588) + 0x5A) = 0;
label_80075A7C:;
    r3 = (this_r3 + 12);
    r4 = 18;
    r5 = 0;
    r3 = cIdMain::SetSwitch((this_r3 + 12), 18, 0); // [0x80072710]
    r3 = (this_r3 + 12);
    r4 = 19;
    r5 = 0;
    r3 = cIdMain::SetSwitch((this_r3 + 12), 19, 0); // [0x80072710]
    goto label_80075B20;
label_80075AA0:;
    r30 = ret_80075A98 + (12);
    r4 = 18;
    r3 = (ret_80075A98 + 12);
    r5 = 1;
    r3 = cIdMain::SetSwitchSt((ret_80075A98 + 12), 18, 1); // [0x8007279C]
    r29 = *(uint32_t*)0x801876D0 + (-2);
    r3 = (ret_80075A98 + 12);
    r4 = 18;
    r5 = 1;
    r3 = cIdMain::SetSwitchEnd((ret_80075A98 + 12), 18, 1); // [0x80072834]
    r0 = *(uint32_t*)((ret_80075A98 + 12) + 0x14);
    r11 = ((*(uint32_t*)0x801876D0 + -2) + (*(uint32_t*)0x801876D0 + -2));
    r11 = ((*(uint32_t*)0x801876D0 + -2) + (*(uint32_t*)0x801876D0 + -2)) + (17);
    if (*(uint32_t*)((ret_80075A98 + 12) + 0x14) <= 18) goto label_80075AE4;
    r9 = *(uint32_t*)((ret_80075A98 + 12) + 0x8);
    *(uint16_t*)(*(uint32_t*)((ret_80075A98 + 12) + 0x8) + 0xB6A) = (((*(uint32_t*)0x801876D0 + -2) + (*(uint32_t*)0x801876D0 + -2)) + 17);
label_80075AE4:;
    r3 = (ret_80075A98 + 12);
    r4 = 19;
    r5 = 1;
    r3 = cIdMain::SetSwitchSt((ret_80075A98 + 12), 19, 1); // [0x8007279C]
    r3 = (ret_80075A98 + 12);
    r4 = 19;
    r5 = 1;
    r3 = cIdMain::SetSwitchEnd((ret_80075A98 + 12), 19, 1); // [0x80072834]
    r0 = *(uint32_t*)((ret_80075A98 + 12) + 0x14);
    r11 = ((*(uint32_t*)0x801876D0 + -2) + (*(uint32_t*)0x801876D0 + -2));
    r11 = ((*(uint32_t*)0x801876D0 + -2) + (*(uint32_t*)0x801876D0 + -2)) + (18);
    if (*(uint32_t*)((ret_80075A98 + 12) + 0x14) <= 19) goto label_80075B20;
    r9 = *(uint32_t*)((ret_80075A98 + 12) + 0x8);
    *(uint16_t*)(*(uint32_t*)((ret_80075A98 + 12) + 0x8) + 0xC06) = (((*(uint32_t*)0x801876D0 + -2) + (*(uint32_t*)0x801876D0 + -2)) + 18);
label_80075B20:;
    r0 = stack_0x3C;
    return; // r3 = ret_80075B00
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::getPoint(void)
// Unit: cockpit.obj | Address: 0x80075B34 | Size: 0x3C bytes
// ============================================================================
/* [0x80075B34] */ void cCockpitWk::getPoint(cCockpitWk* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = this_r3 + (12);
    r5 = *(uint32_t*)0x801876D4;
    r4 = 25;
    r6 = 4;
    r7 = 0;
    r8 = 1;
    r3 = cIdMain::SetNumber((this_r3 + 12), 25, *(uint32_t*)0x801876D4, 4, 0, 1); // [0x800730E8]
    r0 = stack_0x0C;
    return; // r3 = ret_80075B5C
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::getTotal(void)
// Unit: cockpit.obj | Address: 0x80075B70 | Size: 0x38 bytes
// ============================================================================
/* [0x80075B70] */ void cCockpitWk::getTotal(cCockpitWk* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r5 = *(uint32_t*)(this_r3 + 0x54);
    r4 = 6;
    r3 = this_r3 + (40);
    r6 = 5;
    r7 = 0;
    r8 = 1;
    r3 = cIdMain::SetNumber((this_r3 + 40), 6, *(uint32_t*)(this_r3 + 0x54), 5, 0, 1); // [0x800730E8]
    r0 = stack_0x0C;
    return; // r3 = ret_80075B94
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::blink(cIdMain &, long)
// Unit: cockpit.obj | Address: 0x80075BA8 | Size: 0xFC bytes
// ============================================================================
/* [0x80075BA8] */ void cCockpitWk::blink(cCockpitWk* this_r3, cIdMain & arg0_r4, long arg1_r5) {
    // Stack frame allocated: 24 bytes
    f13 = *(float*)(this_r3 + 0x50);
    f0 = *(float*)0x80168B78;
    if (r0 <= 0) goto label_80075BD8;
    f0 = *(float*)(this_r3 + 0x4C);
    f12 = *(float*)0x80168B7C;
    if (r0 != 0) goto label_80075C04;
label_80075BD8:;
    f13 = *(float*)(this_r3 + 0x50);
    f0 = *(float*)0x80168B78;
    if (r0 >= 0) goto label_80075C10;
    f0 = *(float*)(this_r3 + 0x4C);
    f12 = *(float*)0x80168B80;
    if (r0 != 0) goto label_80075C10;
label_80075C04:;
    *(float*)(this_r3 + 0x4C) = *(float*)0x80168B80;
    *(float*)(this_r3 + 0x50) = *(float*)(this_r3 + 0x4C);
label_80075C10:;
    f12 = *(float*)(this_r3 + 0x44);
    f0 = *(float*)0x80168B7C;
    f13 = *(float*)(this_r3 + 0x4C);
    r10 = &stack_0x08;
    f11 = *(float*)(this_r3 + 0x50);
    f0 = *(float*)0x80168B84;
    r9 = 0;
    stack_0x08 = *(float*)0x80168B84;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x80168B84;
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x80168B84;
    *(float*)(&stack_0x08 + 0xC) = *(float*)(this_r3 + 0x44);
    *(float*)(this_r3 + 0x4C) = *(float*)(this_r3 + 0x4C);
    r0 = *(uint32_t*)(arg0_r4 + 0x14);
    if (arg1_r5 >= *(uint32_t*)(arg0_r4 + 0x14)) goto label_80075C64;
label_80075C64:;
    if (0 == 0) goto label_80075C9C;
    r0 = *(uint32_t*)(arg0_r4 + 0x8);
    r8 = *(uint32_t*)(&stack_0x08 + 0xC);
    r7 = *(uint32_t*)(&stack_0x08 + 0x4);
    r11 = stack_0x08;
    r10 = *(uint32_t*)(&stack_0x08 + 0x8);
    r9 = (0 + *(uint32_t*)(arg0_r4 + 0x8));
    *(uint32_t*)((0 + *(uint32_t*)(arg0_r4 + 0x8)) + 0x60) = stack_0x08;
    r9 = (0 + *(uint32_t*)(arg0_r4 + 0x8)) + (96);
    *(uint32_t*)(((0 + *(uint32_t*)(arg0_r4 + 0x8)) + 96) + 0xC) = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)(((0 + *(uint32_t*)(arg0_r4 + 0x8)) + 96) + 0x4) = *(uint32_t*)(&stack_0x08 + 0x4);
    *(uint32_t*)(((0 + *(uint32_t*)(arg0_r4 + 0x8)) + 96) + 0x8) = *(uint32_t*)(&stack_0x08 + 0x8);
label_80075C9C:;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboOn(void)
// Unit: cockpit.obj | Address: 0x80075CA4 | Size: 0x58 bytes
// ============================================================================
/* [0x80075CA4] */ void cCockpitWk::comboOn(cCockpitWk* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r0 = *(uint8_t*)(this_r3 + 0x0);
    if (*(uint8_t*)(this_r3 + 0x0) == 1) goto label_80075CE0;
    if (*(uint8_t*)(this_r3 + 0x0) > 1) goto label_80075CCC;
    if (*(uint8_t*)(this_r3 + 0x0) == 0) goto label_80075CD8;
    goto label_80075CEC;
label_80075CCC:;
    if (*(uint8_t*)(this_r3 + 0x0) == 2) goto label_80075CE8;
    goto label_80075CEC;
label_80075CD8:;
    r3 = cCockpitWk::comboOnInit(this_r3); // [0x80075CFC]
    goto label_80075CEC;
label_80075CE0:;
    r3 = cCockpitWk::comboOnMove(ret_80075CD8); // [0x80075D84]
    goto label_80075CEC;
label_80075CE8:;
    r3 = cCockpitWk::comboOnEnd(ret_80075CE0); // [0x80075E4C]
label_80075CEC:;
    r0 = stack_0x0C;
    return; // r3 = ret_80075CE8
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboOnInit(void)
// Unit: cockpit.obj | Address: 0x80075CFC | Size: 0x88 bytes
// ============================================================================
/* [0x80075CFC] */ void cCockpitWk::comboOnInit(cCockpitWk* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r11 = SDA1::pG;
    r30 = this_r3;
    r3 = this_r3 + (12);
    r9 = *(uint32_t*)(SDA1::pG + 0xF8);
    r4 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x24);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20);
    r4 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x24) + *(uint32_t*)(SDA1::pG + 0xF8));
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20) + *(uint32_t*)(SDA1::pG + 0xF8));
    r3 = cIdMain::SetTexPrim((this_r3 + 12), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x24) + *(uint32_t*)(SDA1::pG + 0xF8)), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20) + *(uint32_t*)(SDA1::pG + 0xF8))); // [0x8007245C]
    f0 = *(float*)0x80168B88;
    r0 = 0;
    f13 = *(float*)0x80168B8C;
    r3 = 0;
    *(float*)(this_r3 + 0x4C) = *(float*)0x80168B88;
    r4 = 53;
    *(float*)(this_r3 + 0x50) = *(float*)0x80168B8C;
    r5 = 0;
    *(uint32_t*)(this_r3 + 0x54) = 0;
    r6 = 0;
    r3 = SndSeCall(0, 53, 0, 0); // [0x800CB7DC]
    r9 = *(uint8_t*)(this_r3 + 0x0);
    r9 = *(uint8_t*)(this_r3 + 0x0) + (1);
    *(uint8_t*)(this_r3 + 0x0) = (*(uint8_t*)(this_r3 + 0x0) + 1);
    r0 = stack_0x14;
    return; // r3 = ret_80075D60
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboOnMove(void)
// Unit: cockpit.obj | Address: 0x80075D84 | Size: 0xC8 bytes
// ============================================================================
/* [0x80075D84] */ void cCockpitWk::comboOnMove(cCockpitWk* this_r3) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r30 = this_r3;
    r5 = 3;
    r31 = this_r3 + (12);
    r4 = (this_r3 + 12);
    r3 = cCockpitWk::blink(this_r3, (this_r3 + 12), 3); // [0x80075BA8]
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r0 = *(uint8_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0x551);
    if (r0 == 0) goto label_80075DC0;
    r3 = this_r3;
    r3 = cCockpitWk::getTimer(this_r3); // [0x80075550]
label_80075DC0:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (r0 != 0) goto label_80075E38;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    f0 = *(float*)0x80168B90;
    r10 = &stack_0x08;
    stack_0x08 = *(float*)0x80168B90;
    *(float*)(&stack_0x08 + 0xC) = *(float*)0x80168B90;
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x80168B90;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x80168B90;
    if (*(uint32_t*)((this_r3 + 12) + 0x14) <= 2) goto label_80075E20;
    r11 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r7 = *(uint32_t*)(&stack_0x08 + 0xC);
    r0 = *(uint32_t*)(&stack_0x08 + 0x4);
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8) + (408);
    r8 = stack_0x08;
    r10 = *(uint32_t*)(&stack_0x08 + 0x8);
    *(uint32_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0x198) = stack_0x08;
    *(uint32_t*)((*(uint32_t*)((this_r3 + 12) + 0x8) + 408) + 0xC) = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)((*(uint32_t*)((this_r3 + 12) + 0x8) + 408) + 0x4) = *(uint32_t*)(&stack_0x08 + 0x4);
    *(uint32_t*)((*(uint32_t*)((this_r3 + 12) + 0x8) + 408) + 0x8) = *(uint32_t*)(&stack_0x08 + 0x8);
label_80075E20:;
    r9 = *(uint8_t*)(this_r3 + 0x0);
    f0 = *(float*)0x80168B94;
    r9 = *(uint8_t*)(this_r3 + 0x0) + (1);
    *(uint8_t*)(this_r3 + 0x0) = (*(uint8_t*)(this_r3 + 0x0) + 1);
    *(float*)(this_r3 + 0x44) = *(float*)0x80168B94;
label_80075E38:;
    r0 = stack_0x24;
    return; // r3 = ret_80075DBC
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboOnEnd(void)
// Unit: cockpit.obj | Address: 0x80075E4C | Size: 0x148 bytes
// ============================================================================
/* [0x80075E4C] */ void cCockpitWk::comboOnEnd(cCockpitWk* this_r3) {
    // Stack frame allocated: 40 bytes
    f0 = *(float*)(this_r3 + 0x44);
    f13 = *(float*)0x80168B98;
    r4 = 0;
    r0 = *(uint32_t*)(this_r3 + 0x20);
    *(float*)(this_r3 + 0x44) = *(float*)(this_r3 + 0x44);
    if (0 >= *(uint32_t*)(this_r3 + 0x20)) goto label_80075F68;
    f11 = *(float*)0x80168B9C;
    f13 = *(float*)0x80168BA0;
    r29 = 0;
    f12 = *(float*)0x80168BA4;
    r30 = -1;
    r31 = 0;
    r12 = -1;
label_80075EA0:;
    r5 = this_r3 + (12);
    if (0 == 3) goto label_80075F10;
    f0 = *(float*)(this_r3 + 0x44);
    r6 = &stack_0x08;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r9 = 0;
    stack_0x08 = *(float*)0x80168BA0;
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x80168BA0;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x80168BA0;
    *(float*)(&stack_0x08 + 0xC) = *(float*)(this_r3 + 0x44);
    if (0 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075EDC;
label_80075EDC:;
    if (0 == 0) goto label_80075F10;
    r11 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r8 = stack_0x08;
    r7 = *(uint32_t*)(&stack_0x08 + 0xC);
    r11 = (0 + *(uint32_t*)((this_r3 + 12) + 0x8));
    r10 = *(uint32_t*)(&stack_0x08 + 0x4);
    r9 = (0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + (96);
    r0 = *(uint32_t*)(&stack_0x08 + 0x8);
    *(uint32_t*)((0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x60) = stack_0x08;
    *(uint32_t*)(((0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 96) + 0xC) = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)(((0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 96) + 0x4) = *(uint32_t*)(&stack_0x08 + 0x4);
    *(uint32_t*)(((0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 96) + 0x8) = *(uint32_t*)(&stack_0x08 + 0x8);
label_80075F10:;
    if (0 == 2) goto label_80075F48;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r9 = 0;
    if (0 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075F2C;
label_80075F2C:;
    if (0 == 0) goto label_80075F48;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r9 = (0 + *(uint32_t*)((this_r3 + 12) + 0x8));
    f0 = *(float*)((0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x50);
    *(float*)((0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x50) = *(float*)((0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x50);
label_80075F48:;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r4 = 0 + (1);
    r29 = 0 + (156);
    r30 = -1 + (-1);
    r31 = 0 + (156);
    r12 = -1 + (-1);
    if ((0 + 1) < *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075EA0;
label_80075F68:;
    f13 = *(float*)(this_r3 + 0x44);
    f0 = *(float*)0x80168BA8;
    if ((0 + 1) >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80075F88;
    r0 = *(uint32_t*)(this_r3 + 0x4);
    *(uint32_t*)(this_r3 + 0x4) = *(uint32_t*)(this_r3 + 0x4);
label_80075F88:;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::combo(void)
// Unit: cockpit.obj | Address: 0x80075F94 | Size: 0x68 bytes
// ============================================================================
/* [0x80075F94] */ void cCockpitWk::combo(cCockpitWk* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r0 = *(uint8_t*)(this_r3 + 0x0);
    if (*(uint8_t*)(this_r3 + 0x0) == 1) goto label_80075FD8;
    if (*(uint8_t*)(this_r3 + 0x0) > 1) goto label_80075FBC;
    if (*(uint8_t*)(this_r3 + 0x0) == 0) goto label_80075FD0;
    goto label_80075FEC;
label_80075FBC:;
    if (*(uint8_t*)(this_r3 + 0x0) == 2) goto label_80075FE0;
    if (*(uint8_t*)(this_r3 + 0x0) == 3) goto label_80075FE8;
    goto label_80075FEC;
label_80075FD0:;
    r3 = cCockpitWk::comboInit(this_r3); // [0x80075FFC]
    goto label_80075FEC;
label_80075FD8:;
    r3 = cCockpitWk::comboMove(ret_80075FD0); // [0x8007608C]
    goto label_80075FEC;
label_80075FE0:;
    r3 = cCockpitWk::comboEnd(ret_80075FD8); // [0x800760FC]
    goto label_80075FEC;
label_80075FE8:;
    r3 = cCockpitWk::comboLine(ret_80075FE0); // [0x80076230]
label_80075FEC:;
    r0 = stack_0x0C;
    return; // r3 = ret_80075FE8
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboInit(void)
// Unit: cockpit.obj | Address: 0x80075FFC | Size: 0x90 bytes
// ============================================================================
/* [0x80075FFC] */ void cCockpitWk::comboInit(cCockpitWk* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r11 = SDA1::pG;
    r30 = this_r3;
    r3 = this_r3 + (12);
    r9 = *(uint32_t*)(SDA1::pG + 0xF8);
    r4 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x28);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20);
    r4 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x28) + *(uint32_t*)(SDA1::pG + 0xF8));
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20) + *(uint32_t*)(SDA1::pG + 0xF8));
    r3 = cIdMain::SetTexPrim((this_r3 + 12), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x28) + *(uint32_t*)(SDA1::pG + 0xF8)), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20) + *(uint32_t*)(SDA1::pG + 0xF8))); // [0x8007245C]
    f13 = *(float*)0x80168BAC;
    r3 = this_r3;
    f0 = *(float*)0x80168BB0;
    *(float*)(this_r3 + 0x4C) = *(float*)0x80168BAC;
    *(float*)(this_r3 + 0x50) = *(float*)0x80168BB0;
    r3 = cCockpitWk::getCount(this_r3); // [0x8007573C]
    r3 = this_r3;
    r3 = cCockpitWk::getPoint(this_r3); // [0x80075B34]
    r9 = *(uint8_t*)(this_r3 + 0x0);
    r3 = 0;
    r4 = 53;
    r5 = 0;
    r9 = *(uint8_t*)(this_r3 + 0x0) + (1);
    r6 = 0;
    *(uint8_t*)(this_r3 + 0x0) = (*(uint8_t*)(this_r3 + 0x0) + 1);
    r3 = SndSeCall(0, 53, 0, 0); // [0x800CB7DC]
    r0 = stack_0x14;
    return; // r3 = ret_80076074
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboMove(void)
// Unit: cockpit.obj | Address: 0x8007608C | Size: 0x70 bytes
// ============================================================================
/* [0x8007608C] */ void cCockpitWk::comboMove(cCockpitWk* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r31 = this_r3;
    r5 = 6;
    r30 = this_r3 + (12);
    r4 = (this_r3 + 12);
    r3 = cCockpitWk::blink(this_r3, (this_r3 + 12), 6); // [0x80075BA8]
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r0 = *(uint8_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0x551);
    if (r0 == 0) goto label_800760C8;
    r3 = this_r3;
    r3 = cCockpitWk::getTimer(this_r3); // [0x80075550]
label_800760C8:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (r0 != 0) goto label_800760E8;
    r9 = *(uint8_t*)(this_r3 + 0x0);
    *(uint8_t*)(this_r3 + 0x1) = *(uint32_t*)(SDA1::pG + 0x148);
    r9 = *(uint8_t*)(this_r3 + 0x0) + (1);
    *(uint8_t*)(this_r3 + 0x0) = (*(uint8_t*)(this_r3 + 0x0) + 1);
label_800760E8:;
    r0 = stack_0x14;
    return; // r3 = ret_800760C4
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboEnd(void)
// Unit: cockpit.obj | Address: 0x800760FC | Size: 0x134 bytes
// ============================================================================
/* [0x800760FC] */ void cCockpitWk::comboEnd(cCockpitWk* this_r3) {
    // Stack frame allocated: 48 bytes
    stack_0x34 = r0;
    r24 = this_r3;
    r30 = 0;
    r29 = this_r3 + (12);
    r25 = 0;
    r31 = (this_r3 + 12);
    r26 = -1;
    r27 = -1;
    r28 = -1;
label_80076130:;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r9 = 0;
    if (0 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_80076144;
label_80076144:;
    if (0 == 0) goto label_80076164;
    r11 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r11 = (0 + *(uint32_t*)((this_r3 + 12) + 0x8));
    r9 = *(uint16_t*)((0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x5A);
    r9 = *(uint16_t*)((0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x5A) + (-10);
    *(uint16_t*)((0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x5A) = (*(uint16_t*)((0 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x5A) + -10);
label_80076164:;
    if (0 > 24) goto label_80076188;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    r9 = 0;
    f13 = *(float*)0x80168BB4;
    if (0 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_800761A4;
    goto label_800761A4;
label_80076188:;
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    f13 = *(float*)0x80168BB8;
    r9 = 0;
    if (0 >= *(uint32_t*)((this_r3 + 12) + 0x14)) goto label_800761A4;
label_800761A4:;
    if (0 == 0) goto label_800761C0;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r9 = (r10 + *(uint32_t*)((this_r3 + 12) + 0x8));
    f0 = *(float*)((r10 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x54);
    *(float*)((r10 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x54) = *(float*)((r10 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x54);
label_800761C0:;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r9 = (r10 + *(uint32_t*)((this_r3 + 12) + 0x8));
    r0 = *(int16_t*)((r10 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x5A);
    if (*(int16_t*)((r10 + *(uint32_t*)((this_r3 + 12) + 0x8)) + 0x5A) > 0) goto label_800761E4;
    r3 = (this_r3 + 12);
    r4 = 0;
    r5 = 0;
    r3 = cIdMain::SetSwitch((this_r3 + 12), 0, 0); // [0x80072710]
label_800761E4:;
    r30 = 0 + (1);
    r25 = 0 + (156);
    r26 = -1 + (-1);
    r27 = -1 + (-1);
    r28 = -1 + (-1);
    if ((0 + 1) <= 28) goto label_80076130;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r0 = *(int16_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xC8A);
    if (*(int16_t*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0xC8A) > 0) goto label_8007621C;
    r9 = *(uint8_t*)(this_r3 + 0x0);
    r9 = *(uint8_t*)(this_r3 + 0x0) + (1);
    *(uint8_t*)(this_r3 + 0x0) = (*(uint8_t*)(this_r3 + 0x0) + 1);
label_8007621C:;
    r0 = stack_0x34;
    return; // r3 = ret_800761E0
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboLine(void)
// Unit: cockpit.obj | Address: 0x80076230 | Size: 0x60 bytes
// ============================================================================
/* [0x80076230] */ void cCockpitWk::comboLine(cCockpitWk* this_r3) {
    // Stack frame allocated: 16 bytes
    r11 = this_r3 + (12);
    r0 = *(uint32_t*)((this_r3 + 12) + 0x14);
    f13 = *(float*)0x80168BBC;
    if (*(uint32_t*)((this_r3 + 12) + 0x14) <= 29) goto label_80076260;
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8);
    r9 = *(uint32_t*)((this_r3 + 12) + 0x8) + (4524);
    f0 = *(float*)((*(uint32_t*)((this_r3 + 12) + 0x8) + 4524) + 0x50);
    *(float*)((*(uint32_t*)((this_r3 + 12) + 0x8) + 4524) + 0x50) = *(float*)((*(uint32_t*)((this_r3 + 12) + 0x8) + 4524) + 0x50);
label_80076260:;
    r11 = *(uint32_t*)((this_r3 + 12) + 0x8);
    f0 = *(float*)(*(uint32_t*)((this_r3 + 12) + 0x8) + 0x11FC);
    stack_0x08 = *(float*)0x80168BBC;
    r9 = stack_0x0C;
    if (stack_0x0C >= -513) goto label_80076288;
    r0 = *(uint32_t*)(this_r3 + 0x4);
    *(uint32_t*)(this_r3 + 0x4) = *(uint32_t*)(this_r3 + 0x4);
label_80076288:;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboPoint(void)
// Unit: cockpit.obj | Address: 0x80076290 | Size: 0x68 bytes
// ============================================================================
/* [0x80076290] */ void cCockpitWk::comboPoint(cCockpitWk* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r0 = *(uint8_t*)(this_r3 + 0x1);
    if (*(uint8_t*)(this_r3 + 0x1) == 1) goto label_800762D4;
    if (*(uint8_t*)(this_r3 + 0x1) > 1) goto label_800762B8;
    if (*(uint8_t*)(this_r3 + 0x1) == 0) goto label_800762CC;
    goto label_800762E8;
label_800762B8:;
    if (*(uint8_t*)(this_r3 + 0x1) == 2) goto label_800762DC;
    if (*(uint8_t*)(this_r3 + 0x1) == 3) goto label_800762E4;
    goto label_800762E8;
label_800762CC:;
    r3 = cCockpitWk::comboPointInit(this_r3); // [0x800762F8]
    goto label_800762E8;
label_800762D4:;
    r3 = cCockpitWk::comboPointMove(ret_800762CC); // [0x80076370]
    goto label_800762E8;
label_800762DC:;
    r3 = cCockpitWk::comboPointEnd(ret_800762D4); // [0x800763C8]
    goto label_800762E8;
label_800762E4:;
    r3 = cCockpitWk::comboPointLine(ret_800762DC); // [0x8007651C]
label_800762E8:;
    r0 = stack_0x0C;
    return; // r3 = ret_800762E4
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboPointInit(void)
// Unit: cockpit.obj | Address: 0x800762F8 | Size: 0x78 bytes
// ============================================================================
/* [0x800762F8] */ void cCockpitWk::comboPointInit(cCockpitWk* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r11 = SDA1::pG;
    r30 = this_r3;
    r3 = this_r3 + (40);
    r9 = *(uint32_t*)(SDA1::pG + 0xF8);
    r4 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x2C);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20);
    r4 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x2C) + *(uint32_t*)(SDA1::pG + 0xF8));
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20) + *(uint32_t*)(SDA1::pG + 0xF8));
    r3 = cIdMain::SetTexPrim((this_r3 + 40), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x2C) + *(uint32_t*)(SDA1::pG + 0xF8)), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x20) + *(uint32_t*)(SDA1::pG + 0xF8))); // [0x8007245C]
    r3 = this_r3;
    r3 = cCockpitWk::getTotal(this_r3); // [0x80075B70]
    r9 = *(uint8_t*)(this_r3 + 0x1);
    r0 = 150;
    *(uint16_t*)(this_r3 + 0x8) = 150;
    r3 = 0;
    r9 = *(uint8_t*)(this_r3 + 0x1) + (1);
    r4 = 56;
    *(uint8_t*)(this_r3 + 0x1) = (*(uint8_t*)(this_r3 + 0x1) + 1);
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 56, 0, 0); // [0x800CB7DC]
    r0 = stack_0x14;
    return; // r3 = ret_80076358
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboPointMove(void)
// Unit: cockpit.obj | Address: 0x80076370 | Size: 0x58 bytes
// ============================================================================
/* [0x80076370] */ void cCockpitWk::comboPointMove(cCockpitWk* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r31 = this_r3;
    r5 = 5;
    r4 = this_r3 + (40);
    r3 = cCockpitWk::blink(this_r3, (this_r3 + 40), 5); // [0x80075BA8]
    r9 = *(uint16_t*)(this_r3 + 0x8);
    r9 = *(uint16_t*)(this_r3 + 0x8) + (-1);
    *(uint16_t*)(this_r3 + 0x8) = (*(uint16_t*)(this_r3 + 0x8) + -1);
    if (r0 != 0) goto label_800763B4;
    r9 = *(uint8_t*)(this_r3 + 0x1);
    r9 = *(uint8_t*)(this_r3 + 0x1) + (1);
    *(uint8_t*)(this_r3 + 0x1) = (*(uint8_t*)(this_r3 + 0x1) + 1);
label_800763B4:;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_8007638C
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboPointEnd(void)
// Unit: cockpit.obj | Address: 0x800763C8 | Size: 0x154 bytes
// ============================================================================
/* [0x800763C8] */ void cCockpitWk::comboPointEnd(cCockpitWk* this_r3) {
    // Stack frame allocated: 48 bytes
    stack_0x34 = r0;
    r25 = this_r3;
    r29 = 1;
    r3 = this_r3 + (40);
    r30 = 1;
    r0 = *(uint32_t*)((this_r3 + 40) + 0x14);
    if (1 >= *(uint32_t*)((this_r3 + 40) + 0x14)) goto label_800764B4;
    r31 = (this_r3 + 40);
    r26 = -2;
    r27 = 156;
    r28 = -2;
label_80076408:;
    r0 = *(uint32_t*)((this_r3 + 40) + 0x14);
    r9 = 0;
    if (1 >= *(uint32_t*)((this_r3 + 40) + 0x14)) goto label_8007641C;
label_8007641C:;
    if (0 == 0) goto label_8007643C;
    r11 = *(uint32_t*)((this_r3 + 40) + 0x8);
    r11 = (156 + *(uint32_t*)((this_r3 + 40) + 0x8));
    r9 = *(uint16_t*)((156 + *(uint32_t*)((this_r3 + 40) + 0x8)) + 0x5A);
    r9 = *(uint16_t*)((156 + *(uint32_t*)((this_r3 + 40) + 0x8)) + 0x5A) + (-10);
    *(uint16_t*)((156 + *(uint32_t*)((this_r3 + 40) + 0x8)) + 0x5A) = (*(uint16_t*)((156 + *(uint32_t*)((this_r3 + 40) + 0x8)) + 0x5A) + -10);
label_8007643C:;
    r0 = *(uint32_t*)((this_r3 + 40) + 0x14);
    r9 = 0;
    f13 = *(float*)0x80168BC0;
    if (1 >= *(uint32_t*)((this_r3 + 40) + 0x14)) goto label_80076454;
label_80076454:;
    if (0 == 0) goto label_80076470;
    r9 = *(uint32_t*)((this_r3 + 40) + 0x8);
    r9 = (r10 + *(uint32_t*)((this_r3 + 40) + 0x8));
    f0 = *(float*)((r10 + *(uint32_t*)((this_r3 + 40) + 0x8)) + 0x54);
    *(float*)((r10 + *(uint32_t*)((this_r3 + 40) + 0x8)) + 0x54) = *(float*)((r10 + *(uint32_t*)((this_r3 + 40) + 0x8)) + 0x54);
label_80076470:;
    r9 = *(uint32_t*)((this_r3 + 40) + 0x8);
    r9 = (r10 + *(uint32_t*)((this_r3 + 40) + 0x8));
    r0 = *(int16_t*)((r10 + *(uint32_t*)((this_r3 + 40) + 0x8)) + 0x5A);
    if (*(int16_t*)((r10 + *(uint32_t*)((this_r3 + 40) + 0x8)) + 0x5A) > 0) goto label_80076498;
    r3 = (this_r3 + 40);
    r4 = 1;
    r5 = 0;
    r29 = 1 + (1);
    r3 = cIdMain::SetSwitch((this_r3 + 40), 1, 0); // [0x80072710]
label_80076498:;
    r0 = *(uint32_t*)((this_r3 + 40) + 0x14);
    r30 = 1 + (1);
    r26 = -2 + (-1);
    r27 = 156 + (156);
    r28 = -2 + (-1);
    if ((1 + 1) < *(uint32_t*)((this_r3 + 40) + 0x14)) goto label_80076408;
label_800764B4:;
    r8 = this_r3 + (40);
    r0 = *(uint32_t*)((this_r3 + 40) + 0x14);
    if ((1 + 1) != *(uint32_t*)((this_r3 + 40) + 0x14)) goto label_80076508;
    if ((1 + 1) <= 0) goto label_800764FC;
    r0 = 512;
    stack_0x0C = 512;
    f13 = *(double*)0x80168BC8;
    stack_0x08 = 0x43300000u;
    r8 = *(uint32_t*)((this_r3 + 40) + 0x8);
    f0 = stack_0x08;
    *(float*)(*(uint32_t*)((this_r3 + 40) + 0x8) + 0x50) = stack_0x08;
label_800764FC:;
    r9 = *(uint8_t*)(this_r3 + 0x1);
    r9 = *(uint8_t*)(this_r3 + 0x1) + (1);
    *(uint8_t*)(this_r3 + 0x1) = (*(uint8_t*)(this_r3 + 0x1) + 1);
label_80076508:;
    r0 = stack_0x34;
    return; // r3 = ret_80076494
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::comboPointLine(void)
// Unit: cockpit.obj | Address: 0x8007651C | Size: 0x5C bytes
// ============================================================================
/* [0x8007651C] */ void cCockpitWk::comboPointLine(cCockpitWk* this_r3) {
    // Stack frame allocated: 16 bytes
    r11 = this_r3 + (40);
    r0 = *(uint32_t*)((this_r3 + 40) + 0x14);
    f13 = *(float*)0x80168BD0;
    if (*(uint32_t*)((this_r3 + 40) + 0x14) <= 0) goto label_80076548;
    r9 = *(uint32_t*)((this_r3 + 40) + 0x8);
    f0 = *(float*)(*(uint32_t*)((this_r3 + 40) + 0x8) + 0x50);
    *(float*)(*(uint32_t*)((this_r3 + 40) + 0x8) + 0x50) = *(float*)(*(uint32_t*)((this_r3 + 40) + 0x8) + 0x50);
label_80076548:;
    r11 = *(uint32_t*)((this_r3 + 40) + 0x8);
    f0 = *(float*)(*(uint32_t*)((this_r3 + 40) + 0x8) + 0x50);
    stack_0x08 = *(float*)0x80168BD0;
    r9 = stack_0x0C;
    if (stack_0x0C >= -513) goto label_80076570;
    r0 = *(uint32_t*)(this_r3 + 0x4);
    *(uint32_t*)(this_r3 + 0x4) = *(uint32_t*)(this_r3 + 0x4);
label_80076570:;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::CockpitSetLanguage(void)
// Unit: cockpit.obj | Address: 0x80076578 | Size: 0x4 bytes
// ============================================================================
/* [0x80076578] */ void cCockpitWk::CockpitSetLanguage(cCockpitWk* this_r3) {
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: __static_initialization_and_destruction_0
// Unit: cockpit.obj | Address: 0x8007657C | Size: 0x68 bytes
// ============================================================================
/* [0x8007657C] */ void __static_initialization_and_destruction_0(void) {
    r0 = 0;
    r0 = 0 | 0xFFFFu;
    if (r3 == 0) goto label_800765BC;
    r9 = &cCockpit;
    r11 = &vtable_cIdMain;
    r10 = &vtable_cCockpitWk;
    *(uint32_t*)(&cCockpit + 0x40) = &vtable_cIdMain;
    *(uint32_t*)(&cCockpit + 0x58) = &vtable_cCockpitWk;
    *(uint32_t*)(&cCockpit + 0x24) = &vtable_cIdMain;
    return; // r3 = r3
label_800765BC:;
    r9 = &cCockpit;
    r11 = &vtable_cIdMain;
    r10 = &vtable_cCockpitWk;
    *(uint32_t*)(&cCockpit + 0x24) = &vtable_cIdMain;
    *(uint32_t*)(&cCockpit + 0x58) = &vtable_cCockpitWk;
    *(uint32_t*)(&cCockpit + 0x40) = &vtable_cIdMain;
    return; // r3 = r3
}

// ============================================================================
// High-Level AST Decompilation: cCockpitWk::~cCockpitWk(void)
// Unit: cockpit.obj | Address: 0x800765E4 | Size: 0x44 bytes
// ============================================================================
/* [0x800765E4] */ void cCockpitWk::~cCockpitWk(cCockpitWk* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = &vtable_cIdMain;
    r11 = &vtable_cCockpitWk;
    *(uint32_t*)(this_r3 + 0x24) = &vtable_cIdMain;
    *(uint32_t*)(this_r3 + 0x58) = &vtable_cCockpitWk;
    *(uint32_t*)(this_r3 + 0x40) = &vtable_cIdMain;
    if (r0 == 0) goto label_80076618;
    r3 = __builtin_delete(); // [0x8009C908]
label_80076618:;
    r0 = stack_0x0C;
    return; // r3 = ret_80076614
}

// ============================================================================
// High-Level AST Decompilation: global constructors keyed to cCockpitWk::CockpitInit(void)
// Unit: cockpit.obj | Address: 0x80076628 | Size: 0x2C bytes
// ============================================================================
/* [0x80076628] */ void global constructors keyed to cCockpitWk::CockpitInit(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r4 = 0;
    r3 = 1;
    r4 = 0 | 0xFFFFu;
    r3 = __static_initialization_and_destruction_0(); // [0x8007657C]
    r0 = stack_0x0C;
    return; // r3 = ret_80076640
}

// ============================================================================
// High-Level AST Decompilation: global destructors keyed to cCockpitWk::CockpitInit(void)
// Unit: cockpit.obj | Address: 0x80076654 | Size: 0x2C bytes
// ============================================================================
/* [0x80076654] */ void global destructors keyed to cCockpitWk::CockpitInit(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r4 = 0;
    r3 = 0;
    r4 = 0 | 0xFFFFu;
    r3 = __static_initialization_and_destruction_0(); // [0x8007657C]
    r0 = stack_0x0C;
    return; // r3 = ret_8007666C
}
