// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: mes.obj
// Functions Decompiled: 48
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::MesInit(unsigned long)
// Unit: mes.obj | Address: 0x8009F0A4 | Size: 0x88 bytes
// ============================================================================
/* [0x8009F0A4] */ void CMesCtrl::MesInit(CMesCtrl* this_r3, unsigned long arg0_r4) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r31 = this_r3;
    r0 = 0;
    *(uint32_t*)((this_r3 + 0x00010000u) - 0x6370) = 0;
    r3 = CMesCtrl::CreateFont(this_r3, arg0_r4); // [0x8009F384]
    r3 = this_r3;
    r3 = CMesCtrl::MesSetLanguage(this_r3); // [0x8009F12C]
    r0 = *(uint32_t*)(this_r3 + 0x0);
    if (*(uint32_t*)(this_r3 + 0x0) == 0) goto label_8009F0E8;
    r9 = &font_p_width;
    goto label_8009F0F0;
label_8009F0E8:;
    r9 = &font_j_width;
label_8009F0F0:;
    *(uint32_t*)((this_r3 + 0x00010000u) - 0x6380) = &font_j_width;
    r10 = SDA1::pG;
    r8 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0xF8);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x14);
    *(uint32_t*)((this_r3 + 0x00010000u) - 0x6374) = 0;
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x14) + *(uint32_t*)(SDA1::pG + 0xF8));
    *(uint32_t*)((this_r3 + 0x00010000u) - 0x6378) = 0;
    *(uint32_t*)((this_r3 + 0x00010000u) - 0x637C) = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x14) + *(uint32_t*)(SDA1::pG + 0xF8));
    r0 = stack_0x14;
    return; // r3 = ret_8009F0CC
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::MesSetLanguage(void)
// Unit: mes.obj | Address: 0x8009F12C | Size: 0xC bytes
// ============================================================================
/* [0x8009F12C] */ void CMesCtrl::MesSetLanguage(CMesCtrl* this_r3) {
    r0 = 1;
    *(uint32_t*)(this_r3 + 0x0) = 1;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::GetLanguage(void) const
// Unit: mes.obj | Address: 0x8009F138 | Size: 0x8 bytes
// ============================================================================
/* [0x8009F138] */ void CMesCtrl::GetLanguage(void) const(void) {
    r3 = *(uint32_t*)(r3 + 0x0);
    return; // r3 = *(uint32_t*)(r3 + 0x0)
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::MesMove(void)
// Unit: mes.obj | Address: 0x8009F140 | Size: 0x4C bytes
// ============================================================================
/* [0x8009F140] */ void CMesCtrl::MesMove(CMesCtrl* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r31 = this_r3 + (4);
    r30 = 5;
label_8009F158:;
    r0 = *(uint32_t*)((this_r3 + 4) + 0x0);
    r3 = (this_r3 + 4);
    r31 = (this_r3 + 4) + (7812);
    if (r0 == 0) goto label_8009F170;
    r3 = CMesWk::MesWorkMove((this_r3 + 4)); // [0x8009F70C]
label_8009F170:;
    if (r0 != 0) goto label_8009F158;
    r0 = stack_0x14;
    return; // r3 = ret_8009F16C
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::MesTrans(void)
// Unit: mes.obj | Address: 0x8009F18C | Size: 0x4C bytes
// ============================================================================
/* [0x8009F18C] */ void CMesCtrl::MesTrans(CMesCtrl* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r31 = this_r3 + (4);
    r30 = 5;
label_8009F1A4:;
    r0 = *(uint32_t*)((this_r3 + 4) + 0x0);
    r3 = (this_r3 + 4);
    r31 = (this_r3 + 4) + (7812);
    if (r0 == 0) goto label_8009F1BC;
    r3 = CMesWk::MesWorkTrans((this_r3 + 4)); // [0x8009FDF0]
label_8009F1BC:;
    if (r0 != 0) goto label_8009F1A4;
    r0 = stack_0x14;
    return; // r3 = ret_8009F1B8
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::MesSet(unsigned long, long, long, unsigned long, long, MES_COLOR)
// Unit: mes.obj | Address: 0x8009F1D8 | Size: 0x30 bytes
// ============================================================================
/* [0x8009F1D8] */ void CMesCtrl::MesSet(CMesCtrl* this_r3, unsigned long arg0_r4, long arg1_r5, long arg2_r6, unsigned long arg3_r7, long arg4_r8, MES_COLOR arg5_r9) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r8 = arg5_r9;
    r11 = r11 + (4);
    r3 = (this_r3 + (r11 + 4));
    r3 = CMesWk::MesWorkInit((this_r3 + (r11 + 4)), arg0_r4, arg1_r5, arg2_r6, arg3_r7, arg5_r9); // [0x8009F5A4]
    r0 = stack_0x0C;
    return; // r3 = ret_8009F1F4
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::MesClear(long)
// Unit: mes.obj | Address: 0x8009F208 | Size: 0x1C bytes
// ============================================================================
/* [0x8009F208] */ void CMesCtrl::MesClear(CMesCtrl* this_r3, long arg0_r4) {
    r0 = 0;
    r9 = (r9 + this_r3);
    *(uint32_t*)((r9 + this_r3) + 0x4) = 0;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::MesRoomInit(unsigned long)
// Unit: mes.obj | Address: 0x8009F224 | Size: 0x50 bytes
// ============================================================================
/* [0x8009F224] */ void CMesCtrl::MesRoomInit(CMesCtrl* this_r3, unsigned long arg0_r4) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r30 = this_r3;
    r29 = arg0_r4;
    r31 = 0;
label_8009F240:;
    r4 = 0;
    r3 = this_r3;
    r3 = CMesCtrl::MesClear(this_r3, 0); // [0x8009F208]
    r31 = 0 + (1);
    if ((0 + 1) <= 4) goto label_8009F240;
    *(uint32_t*)((this_r3 + 0x00010000u) - 0x6378) = arg0_r4;
    r0 = stack_0x1C;
    return; // r3 = ret_8009F248
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::GetFontTexAddr(short &)
// Unit: mes.obj | Address: 0x8009F274 | Size: 0x48 bytes
// ============================================================================
/* [0x8009F274] */ void CMesCtrl::GetFontTexAddr(CMesCtrl* this_r3, short & arg0_r4) {
    r11 = *(uint16_t*)(arg0_r4 + 0x0);
    r10 = this_r3;
    r3 = 0;
    if (r0 <= 252) goto label_8009F2A8;
label_8009F28C:;
    r9 = *(uint16_t*)(arg0_r4 + 0x0) + (-253);
    r3 = 0 + (1);
    r11 = (*(uint16_t*)(arg0_r4 + 0x0) + -253);
    if (r0 > 252) goto label_8009F28C;
    *(uint16_t*)(arg0_r4 + 0x0) = (*(uint16_t*)(arg0_r4 + 0x0) + -253);
label_8009F2A8:;
    r3 = ((0 + 1) + 0x00010000u) + (-26472);
    r3 = (this_r3 + (((0 + 1) + 0x00010000u) + -26472));
    return; // r3 = (this_r3 + (((0 + 1) + 0x00010000u) + -26472))
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::GetFontSize(short, signed char &, signed char &, float) const
// Unit: mes.obj | Address: 0x8009F2BC | Size: 0x84 bytes
// ============================================================================
/* [0x8009F2BC] */ void CMesCtrl::GetFontSize(short, signed char &, signed char &, float) const(void) {
    // Stack frame allocated: 16 bytes
    r9 = *(uint32_t*)((r3 + 0x00010000u) - 0x6380);
    r3 = r11;
    *(uint8_t*)(r5 + 0x0) = r0;
    f13 = *(double*)0x8016BBD8;
    r0 = *(uint32_t*)((r3 + 0x00010000u) - 0x6380);
    r4 = (r4 + *(uint32_t*)((r3 + 0x00010000u) - 0x6380));
    r9 = *(uint8_t*)((r4 + *(uint32_t*)((r3 + 0x00010000u) - 0x6380)) + 0x1);
    *(uint8_t*)(r6 + 0x0) = *(uint8_t*)((r4 + *(uint32_t*)((r3 + 0x00010000u) - 0x6380)) + 0x1);
    r0 = *(uint8_t*)(r5 + 0x0);
    r9 = (*(uint8_t*)((r4 + *(uint32_t*)((r3 + 0x00010000u) - 0x6380)) + 0x1) - *(uint8_t*)(r5 + 0x0));
    stack_0x0C = (*(uint8_t*)((r4 + *(uint32_t*)((r3 + 0x00010000u) - 0x6380)) + 0x1) - *(uint8_t*)(r5 + 0x0));
    stack_0x08 = 0x43300000u;
    f0 = stack_0x08;
    stack_0x08 = f12;
    r3 = stack_0x0C;
    return; // r3 = stack_0x0C
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::GetMesDataAddr(unsigned long) const
// Unit: mes.obj | Address: 0x8009F340 | Size: 0x44 bytes
// ============================================================================
/* [0x8009F340] */ void CMesCtrl::GetMesDataAddr(unsigned long) const(void) {
    if (r0 == 0) goto label_8009F354;
    r3 = *(uint32_t*)((r3 + 0x00010000u) - 0x637C);
    return; // r3 = *(uint32_t*)((r3 + 0x00010000u) - 0x637C)
label_8009F354:;
    if (r0 == 0) goto label_8009F368;
    r3 = *(uint32_t*)((*(uint32_t*)((r3 + 0x00010000u) - 0x637C) + 0x00010000u) - 0x6378);
    return; // r3 = *(uint32_t*)((*(uint32_t*)((r3 + 0x00010000u) - 0x637C) + 0x00010000u) - 0x6378)
label_8009F368:;
    if (r0 != 0) goto label_8009F378;
    r3 = 0;
    return; // r3 = 0
label_8009F378:;
    r3 = *(uint32_t*)((0 + 0x00010000u) - 0x6374);
    return; // r3 = *(uint32_t*)((0 + 0x00010000u) - 0x6374)
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::CreateFont(unsigned long)
// Unit: mes.obj | Address: 0x8009F384 | Size: 0x220 bytes
// ============================================================================
/* [0x8009F384] */ void CMesCtrl::CreateFont(CMesCtrl* this_r3, unsigned long arg0_r4) {
    // Stack frame allocated: 56 bytes
    stack_0x30 = f31;
    stack_0x3C = r0;
    r28 = arg0_r4;
    r0 = *(uint32_t*)(arg0_r4 + 0x8);
    if (*(uint32_t*)(arg0_r4 + 0x8) < 0) goto label_8009F438;
    r9 = *(uint32_t*)(arg0_r4 + 0x4);
    r0 = (*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4);
    r27 = 0;
    r31 = (*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4);
    *(uint32_t*)(arg0_r4 + 0x8) = (*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4);
    if (0 >= *(uint32_t*)(arg0_r4 + 0x4)) goto label_8009F438;
    r10 = 1;
label_8009F3C8:;
    r0 = *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0);
    r9 = *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4);
    r11 = (arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0));
    r9 = (arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4));
    *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0) = (arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0));
    *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) = (arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4));
    r0 = *(uint8_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x23);
    if (*(uint8_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x23) != 0) goto label_8009F400;
    r0 = *(uint32_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x8);
    r0 = (arg0_r4 + *(uint32_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x8));
    *(uint32_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x8) = (arg0_r4 + *(uint32_t*)((arg0_r4 + *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0)) + 0x8));
    r9 = *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0);
    *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x0) + 0x23) = 1;
label_8009F400:;
    r9 = *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4);
    r0 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x2);
    if (*(uint8_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x2) != 0) goto label_8009F424;
    r0 = *(uint32_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x8);
    r0 = (arg0_r4 + *(uint32_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x8));
    *(uint32_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x8) = (arg0_r4 + *(uint32_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x8));
    r9 = *(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4);
    *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + 0x4) + 0x2) = 1;
label_8009F424:;
    r0 = *(uint32_t*)(arg0_r4 + 0x4);
    r27 = 0 + (1);
    r31 = (*(uint32_t*)(arg0_r4 + 0x8) + arg0_r4) + (8);
    if ((0 + 1) < *(uint32_t*)(arg0_r4 + 0x4)) goto label_8009F3C8;
label_8009F438:;
    r0 = *(uint32_t*)(arg0_r4 + 0x4);
    r27 = 0;
    r29 = (this_r3 + 0x00010000u) + (-26472);
    r31 = *(uint32_t*)(arg0_r4 + 0x8);
    if (0 >= *(uint32_t*)(arg0_r4 + 0x4)) goto label_8009F58C;
    f31 = *(double*)0x8016BBE0;
label_8009F460:;
    r11 = *(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0);
    *(uint32_t*)(((this_r3 + 0x00010000u) + -26472) + 0x60) = arg0_r4;
    *(uint32_t*)(((this_r3 + 0x00010000u) + -26472) + 0x5C) = *(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0);
    r10 = *(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0);
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x4);
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x4) + (-8);
    if ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x4) + -8) > 0x1u) goto label_8009F4E0;
    r0 = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x23);
    if (*(uint8_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x23) == 0) goto label_8009F4B8;
    r7 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x4);
    r0 = 0;
    r4 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x8);
    r3 = ((this_r3 + 0x00010000u) + -26472);
    r5 = *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x2);
    r8 = 0;
    r6 = *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x0);
    r9 = 0;
    stack_0x08 = 0;
    r10 = 0;
    r3 = GXInitTexObjCI(); // [0x80122980]
label_8009F4B8:;
    r9 = *(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x4);
    r0 = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x4) + 0x2);
    if (*(uint8_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x4) + 0x2) != 1) goto label_8009F55C;
    r6 = *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x4) + 0x0);
    r3 = ((this_r3 + 0x00010000u) + -26472) + (32);
    r4 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x4) + 0x8);
    r5 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x4) + 0x4);
    r3 = GXInitTlutObj(); // [0x801231F0]
    goto label_8009F55C;
label_8009F4E0:;
    r7 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x4);
    r3 = ((this_r3 + 0x00010000u) + -26472);
    r4 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x8);
    r8 = 0;
    r5 = *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x2);
    r9 = 0;
    r6 = *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0) + 0x0);
    r10 = 0;
    r3 = GXInitTexObj(); // [0x8012270C]
    r9 = *(uint32_t*)(((this_r3 + 0x00010000u) + -26472) + 0x5C);
    r10 = *(uint32_t*)(*(uint32_t*)(arg0_r4 + 0x8) + 0x0);
    r3 = ((this_r3 + 0x00010000u) + -26472);
    r0 = *(uint8_t*)(*(uint32_t*)(((this_r3 + 0x00010000u) + -26472) + 0x5C) + 0x21);
    r4 = 1;
    r30 = *(uint8_t*)(*(uint32_t*)(((this_r3 + 0x00010000u) + -26472) + 0x5C) + 0x22);
    r5 = 1;
    stack_0x14 = *(uint8_t*)(*(uint32_t*)(((this_r3 + 0x00010000u) + -26472) + 0x5C) + 0x21);
    r6 = 0;
    r7 = *(uint8_t*)(*(uint32_t*)(((this_r3 + 0x00010000u) + -26472) + 0x5C) + 0x20);
    r8 = 0;
    stack_0x10 = 0x43300000u;
    f3 = *(float*)(*(uint32_t*)(((this_r3 + 0x00010000u) + -26472) + 0x5C) + 0x1C);
    f1 = stack_0x10;
    stack_0x14 = *(uint8_t*)(*(uint32_t*)(((this_r3 + 0x00010000u) + -26472) + 0x5C) + 0x22);
    stack_0x10 = 0x43300000u;
    f2 = stack_0x10;
    r3 = GXInitTexObjLOD(); // [0x801229C8]
label_8009F55C:;
    r3 = ((this_r3 + 0x00010000u) + -26472) + (44);
    f1 = *(float*)0x8016BBE8;
    r27 = 0 + (1);
    r31 = *(uint32_t*)(arg0_r4 + 0x8) + (8);
    r29 = ((this_r3 + 0x00010000u) + -26472) + (100);
    r3 = PSMTXScale(); // [0x801014A8]
    r0 = *(uint32_t*)(arg0_r4 + 0x4);
    if ((0 + 1) < *(uint32_t*)(arg0_r4 + 0x4)) goto label_8009F460;
label_8009F58C:;
    r0 = stack_0x3C;
    f31 = stack_0x30;
    return; // r3 = ret_8009F57C
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::MesWorkInit(unsigned long, long, long, unsigned long, unsigned long)
// Unit: mes.obj | Address: 0x8009F5A4 | Size: 0x168 bytes
// ============================================================================
/* [0x8009F5A4] */ void CMesWk::MesWorkInit(CMesWk* this_r3, unsigned long arg0_r4, long arg1_r5, long arg2_r6, unsigned long arg3_r7, unsigned long arg4_r8) {
    // Stack frame allocated: 40 bytes
    stack_0x2C = r0;
    r31 = this_r3;
    r29 = arg3_r7;
    r26 = arg0_r4;
    r30 = arg1_r5;
    r28 = arg2_r6;
    r27 = arg4_r8;
    r3 = &cMes;
    r4 = arg3_r7;
    r3 = CMesCtrl::GetMesDataAddr(unsigned long) const(); // [0x8009F340]
    r25 = ret_8009F5D8;
    if (r0 != 0) goto label_8009F600;
    r3 = 0;
    r5 = "Room Message is not set!";
    r4 = 0;
    r3 = LogErr(0, 0, "Room Message is not set!", arg2_r6); // [0x8007A05C]
    goto label_8009F6F8;
label_8009F600:;
    r4 = 0;
    r5 = 7812;
    r3 = this_r3;
    r3 = memset(); // [0x800E8A5C]
    r0 = 0;
    f0 = *(float*)0x8016BC08;
    r11 = 0;
    r5 = 1;
    r6 = 0;
    r9 = 24;
    r10 = 23;
    r8 = this_r3 + (88);
    r7 = -1;
    *(uint8_t*)(this_r3 + 0x4) = 0;
    *(uint16_t*)(this_r3 + 0x8) = arg1_r5;
    *(uint16_t*)(this_r3 + 0xA) = arg2_r6;
    *(uint16_t*)(this_r3 + 0x10) = 24;
    *(uint32_t*)(this_r3 + 0x24) = arg4_r8;
    *(uint16_t*)(this_r3 + 0x16) = 23;
    *(uint32_t*)(this_r3 + 0x1E58) = (this_r3 + 88);
    *(uint8_t*)(this_r3 + 0x3E) = 0;
    *(uint8_t*)(this_r3 + 0x1B) = -1;
    *(float*)(this_r3 + 0x20) = *(float*)0x8016BC08;
    *(uint32_t*)(this_r3 + 0x0) = 1;
    *(uint8_t*)(this_r3 + 0x7) = 0;
    *(uint8_t*)(this_r3 + 0x6) = 0;
    *(uint8_t*)(this_r3 + 0x5) = 0;
    *(uint16_t*)(this_r3 + 0xC) = arg1_r5;
    *(uint16_t*)(this_r3 + 0xE) = arg2_r6;
    *(uint32_t*)(this_r3 + 0x28) = arg3_r7;
    *(uint16_t*)(this_r3 + 0x36) = 0;
    *(uint8_t*)(this_r3 + 0x1E7D) = 0;
    *(uint32_t*)(this_r3 + 0x48) = 0;
    *(uint8_t*)(this_r3 + 0x3F) = 0;
    *(float*)(this_r3 + 0x1C) = *(float*)0x8016BC08;
    if (r0 == 0) goto label_8009F6A0;
    *(uint16_t*)(this_r3 + 0x2C) = 0;
    goto label_8009F6A4;
label_8009F6A0:;
    *(uint16_t*)(this_r3 + 0x2C) = 1;
label_8009F6A4:;
    r0 = 0;
    *(uint16_t*)(this_r3 + 0x32) = 0;
    *(uint16_t*)(this_r3 + 0x2E) = 0;
    if (arg0_r4 < 0) goto label_8009F6F8;
    r30 = ret_8009F5D8;
    if (arg0_r4 != 0) goto label_8009F6E0;
    r3 = &cMes;
    r3 = CMesCtrl::GetLanguage(void) const(); // [0x8009F138]
    r3 = (ret_8009F6CC + ret_8009F5D8);
    r0 = *(uint32_t*)((ret_8009F6CC + ret_8009F5D8) + 0x4);
    r30 = (ret_8009F5D8 + *(uint32_t*)((ret_8009F6CC + ret_8009F5D8) + 0x4));
label_8009F6E0:;
    *(uint32_t*)(this_r3 + 0x44) = (ret_8009F5D8 + *(uint32_t*)((ret_8009F6CC + ret_8009F5D8) + 0x4));
    r9 = (24 + (ret_8009F5D8 + *(uint32_t*)((ret_8009F6CC + ret_8009F5D8) + 0x4)));
    r0 = *(uint32_t*)((24 + (ret_8009F5D8 + *(uint32_t*)((ret_8009F6CC + ret_8009F5D8) + 0x4))) + 0x8);
    r0 = ((ret_8009F5D8 + *(uint32_t*)((ret_8009F6CC + ret_8009F5D8) + 0x4)) + *(uint32_t*)((24 + (ret_8009F5D8 + *(uint32_t*)((ret_8009F6CC + ret_8009F5D8) + 0x4))) + 0x8));
    *(uint32_t*)(this_r3 + 0x40) = ((ret_8009F5D8 + *(uint32_t*)((ret_8009F6CC + ret_8009F5D8) + 0x4)) + *(uint32_t*)((24 + (ret_8009F5D8 + *(uint32_t*)((ret_8009F6CC + ret_8009F5D8) + 0x4))) + 0x8));
label_8009F6F8:;
    r0 = stack_0x2C;
    return; // r3 = (ret_8009F6CC + ret_8009F5D8)
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::MesWorkMove(void)
// Unit: mes.obj | Address: 0x8009F70C | Size: 0x1A4 bytes
// ============================================================================
/* [0x8009F70C] */ void CMesWk::MesWorkMove(CMesWk* this_r3) {
    // Stack frame allocated: 56 bytes
    stack_0x30 = f31;
    stack_0x3C = r0;
    r9 = 0x8016BC0Cu;
    r0 = *(uint32_t*)0x8019D694;
    r11 = *(uint32_t*)(0x8016BC0Cu + 0x0);
    r12 = *(uint32_t*)(0x8016BC0Cu + 0x4);
    r31 = this_r3;
    stack_0x08 = *(uint32_t*)(0x8016BC0Cu + 0x0);
    stack_0x0C = *(uint32_t*)(0x8016BC0Cu + 0x4);
    if (r0 == 0) goto label_8009F754;
    r0 = 1;
    *(uint16_t*)(this_r3 + 0x32) = 1;
label_8009F754:;
    r30 = this_r3 + (7768);
    f31 = *(double*)0x8016BC18;
    goto label_8009F850;
label_8009F768:;
    r9 = *(uint16_t*)(this_r3 + 0x2E);
    r11 = *(int16_t*)(this_r3 + 0x2C);
    r9 = *(uint16_t*)(this_r3 + 0x2E) + (1);
    *(uint16_t*)(this_r3 + 0x2E) = (*(uint16_t*)(this_r3 + 0x2E) + 1);
    if (*(int16_t*)(this_r3 + 0x2C) > 1) goto label_8009F898;
    r11 = *(uint32_t*)(this_r3 + 0x40);
    r9 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0);
    r9 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) + (-128);
    if (r4 != 0) goto label_8009F808;
    r3 = &cMes;
    r3 = CMesCtrl::GetLanguage(void) const(); // [0x8009F138]
    r0 = 1;
    if (ret_8009F7A4 != 0) goto label_8009F7B8;
    r0 = 0;
label_8009F7B8:;
    r9 = &stack_0x08;
    f11 = *(float*)(this_r3 + 0x1C);
    r9 = 0x801A0000u;
    r0 = *(uint16_t*)(this_r3 + 0xC);
    stack_0x1C = *(uint32_t*)(this_r3 + 0x40);
    stack_0x18 = 0x43300000u;
    f0 = stack_0x18;
    stack_0x18 = f12;
    r9 = stack_0x1C;
    r0 = (*(uint16_t*)(this_r3 + 0xC) + stack_0x1C);
    *(uint16_t*)(this_r3 + 0xC) = (*(uint16_t*)(this_r3 + 0xC) + stack_0x1C);
    goto label_8009F810;
label_8009F808:;
    r3 = this_r3;
    r3 = CMesWk::QueSet(this_r3, r4); // [0x8009FA94]
label_8009F810:;
    r0 = *(uint32_t*)(this_r3 + 0x28);
    if (ret_8009F7A4 == 0) goto label_8009F83C;
    r0 = *(int16_t*)(this_r3 + 0x32);
    if (*(int16_t*)(this_r3 + 0x32) != 0) goto label_8009F83C;
    r3 = *(uint16_t*)(this_r3 + 0x54);
    r5 = 0;
    r4 = *(uint16_t*)(this_r3 + 0x56);
    r6 = 0;
    r3 = SndSeCall(*(uint16_t*)(this_r3 + 0x54), *(uint16_t*)(this_r3 + 0x56), 0, 0); // [0x800CB7DC]
label_8009F83C:;
    r0 = 0;
    *(uint16_t*)(this_r3 + 0x2E) = 0;
label_8009F844:;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r9 = *(uint32_t*)(this_r3 + 0x40) + (2);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + 2);
label_8009F850:;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r0 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0);
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) > 0x7Fu) goto label_8009F874;
    r3 = this_r3;
    r3 = CMesWk::CommandExec(this_r3); // [0x800A0230]
    if (ret_8009F864 != 0) goto label_8009F898;
    goto label_8009F844;
label_8009F874:;
    r0 = *(int16_t*)(this_r3 + 0x32);
    if (*(int16_t*)(this_r3 + 0x32) != 1) goto label_8009F88C;
    r9 = *(uint16_t*)(this_r3 + 0x2C);
    r9 = *(uint16_t*)(this_r3 + 0x2C) + (1);
    *(uint16_t*)(this_r3 + 0x2E) = (*(uint16_t*)(this_r3 + 0x2C) + 1);
label_8009F88C:;
    r0 = *(uint32_t*)(this_r3 + 0x1E58);
    if (*(uint32_t*)(this_r3 + 0x1E58) < (this_r3 + 7768)) goto label_8009F768;
label_8009F898:;
    r0 = stack_0x3C;
    f31 = stack_0x30;
    return; // r3 = ret_8009F864
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::WidthCk(void)
// Unit: mes.obj | Address: 0x8009F8B0 | Size: 0x1E4 bytes
// ============================================================================
/* [0x8009F8B0] */ void CMesWk::WidthCk(CMesWk* this_r3) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r31 = this_r3;
    r30 = 0;
    r0 = this_r3 + (88);
    r27 = *(uint32_t*)(this_r3 + 0x40);
    *(uint16_t*)(this_r3 + 0x18) = 0;
    r28 = this_r3 + (7768);
    *(uint32_t*)(this_r3 + 0x1E58) = (this_r3 + 88);
    r29 = 1;
label_8009F8E0:;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r9 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0);
    if ((this_r3 + 88) > 0x7Fu) goto label_8009F9B8;
    if ((this_r3 + 88) == 4) goto label_8009F954;
    if ((this_r3 + 88) > 4) goto label_8009F918;
    if ((this_r3 + 88) == 2) goto label_8009F990;
    if ((this_r3 + 88) > 2) goto label_8009F93C;
    if ((this_r3 + 88) == 1) goto label_8009F954;
    goto label_8009F99C;
label_8009F918:;
    if ((this_r3 + 88) == 10) goto label_8009F970;
    if ((this_r3 + 88) > 10) goto label_8009F930;
    if ((this_r3 + 88) == 7) goto label_8009F95C;
    goto label_8009F99C;
label_8009F930:;
    if ((this_r3 + 88) == 14) goto label_8009F990;
    goto label_8009F99C;
label_8009F93C:;
    r0 = *(int16_t*)(this_r3 + 0x18);
    if (0 <= *(int16_t*)(this_r3 + 0x18)) goto label_8009F94C;
    *(uint16_t*)(this_r3 + 0x18) = 0;
label_8009F94C:;
    r30 = 0;
    goto label_8009FA2C;
label_8009F954:;
    r29 = 0;
    goto label_8009FA2C;
label_8009F95C:;
    r3 = this_r3;
    r3 = CMesWk::CommandExec(this_r3); // [0x800A0230]
    r0 = *(uint16_t*)(this_r3 + 0x30);
    *(uint16_t*)(this_r3 + 0x2C) = *(uint16_t*)(this_r3 + 0x30);
    goto label_8009FA2C;
label_8009F970:;
    r3 = this_r3;
    r3 = CMesWk::CommandExec(this_r3); // [0x800A0230]
    if (ret_8009F974 == 0) goto label_8009FA2C;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r9 = *(uint32_t*)(this_r3 + 0x40) + (-2);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + -2);
    goto label_8009FA2C;
label_8009F990:;
    r3 = this_r3;
    r3 = CMesWk::CommandExec(this_r3); // [0x800A0230]
    goto label_8009FA2C;
label_8009F99C:;
    r3 = this_r3;
    r3 = CMesWk::CommandArg(this_r3); // [0x800A0374]
    r0 = *(uint32_t*)(this_r3 + 0x40);
    r0 = (*(uint32_t*)(this_r3 + 0x40) + ret_8009F9A0);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + ret_8009F9A0);
    goto label_8009FA2C;
label_8009F9B8:;
    r5 = *(uint32_t*)(this_r3 + 0x1E58);
    if (*(uint32_t*)(this_r3 + 0x1E58) < (this_r3 + 7768)) goto label_8009F9E0;
    r3 = 0;
    r5 = "Message [%d]:Overflow!!";
    r4 = 0;
    r3 = LogErr(0, 0, "Message [%d]:Overflow!!", r6); // [0x8007A05C]
    goto label_8009FA40;
label_8009F9E0:;
    r0 = (*(uint32_t*)(this_r3 + 0x40) + -2) + (-128);
    if (((*(uint32_t*)(this_r3 + 0x40) + -2) + -128) == 0) goto label_8009FA2C;
    r6 = "Message [%d]:Overflow!!" + (9);
    f1 = *(float*)(this_r3 + 0x1C);
    r3 = &cMes;
    r5 = "Message [%d]:Overflow!!" + (8);
    r3 = CMesCtrl::GetFontSize(short, signed char &, signed char &, float) const(); // [0x8009F2BC]
    r11 = *(uint32_t*)(this_r3 + 0x1E58);
    r3 = ret_8009FA08 + (1);
    *(uint16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6) = (ret_8009FA08 + 1);
    r9 = *(uint32_t*)(this_r3 + 0x1E58);
    r11 = *(int16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6);
    r0 = *(uint32_t*)(this_r3 + 0x1E58) + (20);
    *(uint32_t*)(this_r3 + 0x1E58) = (*(uint32_t*)(this_r3 + 0x1E58) + 20);
    r30 = (0 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6));
label_8009FA2C:;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r9 = *(uint32_t*)(this_r3 + 0x40) + (2);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + 2);
    if (0 != 0) goto label_8009F8E0;
label_8009FA40:;
    r0 = *(int16_t*)(this_r3 + 0x18);
    if ((0 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6)) <= *(int16_t*)(this_r3 + 0x18)) goto label_8009FA50;
    *(uint16_t*)(this_r3 + 0x18) = (0 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6));
label_8009FA50:;
    r0 = *(uint32_t*)(this_r3 + 0x28);
    if (*(uint32_t*)(this_r3 + 0x28) >= 0) goto label_8009FA6C;
    r0 = *(int16_t*)(this_r3 + 0x18);
    *(uint16_t*)(this_r3 + 0x8) = *(int16_t*)(this_r3 + 0x18);
label_8009FA6C:;
    r9 = this_r3 + (88);
    r0 = 0;
    *(uint8_t*)(this_r3 + 0x3E) = 0;
    *(uint32_t*)(this_r3 + 0x40) = *(uint32_t*)(this_r3 + 0x40);
    *(uint32_t*)(this_r3 + 0x1E58) = (this_r3 + 88);
    r0 = stack_0x24;
    return; // r3 = (ret_8009FA08 + 1)
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::QueSet(unsigned short)
// Unit: mes.obj | Address: 0x8009FA94 | Size: 0x58 bytes
// ============================================================================
/* [0x8009FA94] */ void CMesWk::QueSet(CMesWk* this_r3, unsigned short arg0_r4) {
    r9 = *(uint32_t*)(this_r3 + 0x1E58);
    r0 = *(uint16_t*)(this_r3 + 0xC);
    *(uint16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x0) = *(uint16_t*)(this_r3 + 0xC);
    r11 = *(uint32_t*)(this_r3 + 0x1E58);
    r0 = *(uint16_t*)(this_r3 + 0xE);
    *(uint16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x2) = *(uint16_t*)(this_r3 + 0xE);
    r9 = *(uint32_t*)(this_r3 + 0x1E58);
    r0 = *(uint32_t*)(this_r3 + 0x28);
    *(uint32_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0xC) = *(uint32_t*)(this_r3 + 0x28);
    r10 = *(uint32_t*)(this_r3 + 0x1E58);
    r0 = *(uint32_t*)(this_r3 + 0x24);
    *(uint32_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x10) = *(uint32_t*)(this_r3 + 0x24);
    r11 = *(uint32_t*)(this_r3 + 0x1E58);
    *(uint16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x4) = arg0_r4;
    r9 = *(uint32_t*)(this_r3 + 0x1E58);
    r0 = *(uint16_t*)(this_r3 + 0xC);
    r11 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6);
    r9 = *(uint32_t*)(this_r3 + 0x1E58) + (20);
    r0 = (*(uint16_t*)(this_r3 + 0xC) + *(uint16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6));
    *(uint32_t*)(this_r3 + 0x1E58) = (*(uint32_t*)(this_r3 + 0x1E58) + 20);
    *(uint16_t*)(this_r3 + 0xC) = (*(uint16_t*)(this_r3 + 0xC) + *(uint16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6));
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::SetNumber(unsigned short, unsigned short)
// Unit: mes.obj | Address: 0x8009FAEC | Size: 0x7C bytes
// ============================================================================
/* [0x8009FAEC] */ void CMesWk::SetNumber(CMesWk* this_r3, unsigned short arg0_r4, unsigned short arg1_r5) {
    *(uint16_t*)(this_r3 + 0x50) = arg0_r4;
    r5 = arg1_r5;
    *(uint16_t*)(this_r3 + 0x4C) = arg0_r4;
    if (r0 != 0) goto label_8009FB24;
    if (arg0_r4 == 0) goto label_8009FB24;
    r11 = 0xCCCCCCCDu;
label_8009FB0C:;
    r0 = arg1_r5 + (1);
    if (arg0_r4 != 0) goto label_8009FB0C;
label_8009FB24:;
    r0 = 1;
    r9 = 1;
    *(uint16_t*)(this_r3 + 0x4E) = 1;
    if (1 >= arg1_r5) goto label_8009FB5C;
    r11 = 1;
label_8009FB3C:;
    r9 = 1 + (1);
    r11 = 1;
    if ((1 + 1) < arg1_r5) goto label_8009FB3C;
    *(uint16_t*)(this_r3 + 0x4E) = 1;
label_8009FB5C:;
    r0 = *(uint16_t*)(this_r3 + 0x4E);
    *(uint16_t*)(this_r3 + 0x52) = *(uint16_t*)(this_r3 + 0x4E);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::putSelCursol(void)
// Unit: mes.obj | Address: 0x8009FB68 | Size: 0x50 bytes
// ============================================================================
/* [0x8009FB68] */ void CMesWk::putSelCursol(CMesWk* this_r3) {
    r0 = *(uint8_t*)(this_r3 + 0x1E7C);
    r10 = 0;
    r11 = this_r3 + (7772);
label_8009FB80:;
    r0 = *(uint8_t*)(this_r3 + 0x1E7E);
    r9 = *(uint32_t*)((this_r3 + 7772) + 0x0);
    r11 = (this_r3 + 7772) + (4);
    *(uint16_t*)(*(uint32_t*)((this_r3 + 7772) + 0x0) + 0x4) = *(uint8_t*)(this_r3 + 0x1E7E);
    r10 = 0 + (1);
    r0 = *(uint8_t*)(this_r3 + 0x1E7C);
    if ((0 + 1) < *(uint8_t*)(this_r3 + 0x1E7C)) goto label_8009FB80;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::putNextCursol(bool)
// Unit: mes.obj | Address: 0x8009FBB8 | Size: 0x16C bytes
// ============================================================================
/* [0x8009FBB8] */ void CMesWk::putNextCursol(CMesWk* this_r3, bool arg0_r4) {
    // Stack frame allocated: 40 bytes
    stack_0x2C = r0;
    r31 = this_r3;
    r29 = arg0_r4;
    r0 = *(uint8_t*)(this_r3 + 0x1E7F);
    if (*(uint8_t*)(this_r3 + 0x1E7F) != 0) goto label_8009FCC0;
    r5 = *(uint32_t*)(this_r3 + 0x1E58);
    f1 = *(float*)(this_r3 + 0x1C);
    r3 = &cMes;
    r6 = *(uint32_t*)(this_r3 + 0x1E58) + (9);
    r4 = 2;
    r5 = *(uint32_t*)(this_r3 + 0x1E58) + (8);
    r3 = CMesCtrl::GetFontSize(short, signed char &, signed char &, float) const(); // [0x8009F2BC]
    r9 = *(uint32_t*)(this_r3 + 0x1E58);
    r3 = ret_8009FBF8 + (1);
    *(uint16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6) = (ret_8009FBF8 + 1);
    r0 = *(uint32_t*)(this_r3 + 0x28);
    if (*(uint8_t*)(this_r3 + 0x1E7F) == 0) goto label_8009FCB4;
    r9 = *(uint32_t*)(this_r3 + 0x1E58);
    r3 = &cMes;
    r0 = *(int16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6);
    *(uint16_t*)(this_r3 + 0xC) = *(int16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6);
    r3 = CMesCtrl::GetLanguage(void) const(); // [0x8009F138]
    if (ret_8009FC2C != 1) goto label_8009FC50;
    r0 = *(int16_t*)(this_r3 + 0x10);
    r9 = *(uint16_t*)(this_r3 + 0xA);
    r0 = (*(int16_t*)(this_r3 + 0x10) + *(int16_t*)(this_r3 + 0x10));
    r9 = (*(uint16_t*)(this_r3 + 0xA) + (*(int16_t*)(this_r3 + 0x10) + *(int16_t*)(this_r3 + 0x10)));
    r9 = (*(uint16_t*)(this_r3 + 0xA) + (*(int16_t*)(this_r3 + 0x10) + *(int16_t*)(this_r3 + 0x10))) + (-8);
    goto label_8009FCB0;
label_8009FC50:;
    r10 = *(int16_t*)(this_r3 + 0x10);
    r9 = *(int16_t*)(this_r3 + 0xA);
    r0 = ((*(int16_t*)(this_r3 + 0x10) + *(int16_t*)(this_r3 + 0x10)) + *(int16_t*)(this_r3 + 0x10));
    f13 = *(double*)0x8016BC38;
    r9 = (*(int16_t*)(this_r3 + 0xA) + ((*(int16_t*)(this_r3 + 0x10) + *(int16_t*)(this_r3 + 0x10)) + *(int16_t*)(this_r3 + 0x10)));
    f10 = *(float*)0x8016BC40;
    stack_0x14 = (*(int16_t*)(this_r3 + 0xA) + ((*(int16_t*)(this_r3 + 0x10) + *(int16_t*)(this_r3 + 0x10)) + *(int16_t*)(this_r3 + 0x10)));
    f12 = *(float*)(this_r3 + 0x20);
    r9 = r8;
    stack_0x10 = 0x43300000u;
    f0 = stack_0x10;
    stack_0x10 = f11;
    r9 = stack_0x14;
label_8009FCB0:;
    *(uint16_t*)(this_r3 + 0xE) = stack_0x14;
label_8009FCB4:;
    r3 = this_r3;
    r4 = 2;
    r3 = CMesWk::QueSet(this_r3, 2); // [0x8009FA94]
label_8009FCC0:;
    if (arg0_r4 != 0) goto label_8009FCD0;
    r0 = 20;
    *(uint8_t*)(this_r3 + 0x1E7F) = 20;
label_8009FCD0:;
    r9 = *(uint8_t*)(this_r3 + 0x1E7F);
    r11 = *(uint32_t*)(this_r3 + 0x1E58);
    r9 = *(uint8_t*)(this_r3 + 0x1E7F) + (1);
    *(uint8_t*)(this_r3 + 0x1E7F) = (*(uint8_t*)(this_r3 + 0x1E7F) + 1);
    *(uint16_t*)(*(uint32_t*)(this_r3 + 0x1E58) - 0x10) = (*(uint8_t*)(this_r3 + 0x1E7F) + 1);
    r0 = *(uint8_t*)(this_r3 + 0x1E7F);
    if (*(uint8_t*)(this_r3 + 0x1E7F) <= 30) goto label_8009FD10;
    r0 = 1;
    *(uint8_t*)(this_r3 + 0x1E7F) = 1;
label_8009FD10:;
    r0 = stack_0x2C;
    return; // r3 = ret_8009FCBC
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::SetJump(unsigned short)
// Unit: mes.obj | Address: 0x8009FD24 | Size: 0x60 bytes
// ============================================================================
/* [0x8009FD24] */ void CMesWk::SetJump(CMesWk* this_r3, unsigned short arg0_r4) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r0 = *(uint8_t*)(this_r3 + 0x3F);
    if (*(uint8_t*)(this_r3 + 0x3F) > 2) goto label_8009FD5C;
    r0 = (*(uint8_t*)(this_r3 + 0x3F) + *(uint8_t*)(this_r3 + 0x3F));
    r11 = this_r3 + (56);
    r9 = *(uint8_t*)(this_r3 + 0x3F);
    r9 = *(uint8_t*)(this_r3 + 0x3F) + (1);
    *(uint8_t*)(this_r3 + 0x3F) = (*(uint8_t*)(this_r3 + 0x3F) + 1);
    goto label_8009FD74;
label_8009FD5C:;
    r3 = 0;
    r5 = "JumpTbl is Max!";
    r4 = 0;
    r3 = LogWarn(0, 0, "JumpTbl is Max!", r6); // [0x8007A0A0]
label_8009FD74:;
    r0 = stack_0x0C;
    return; // r3 = ret_8009FD70
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::SetScale(float, float)
// Unit: mes.obj | Address: 0x8009FD84 | Size: 0x6C bytes
// ============================================================================
/* [0x8009FD84] */ void CMesWk::SetScale(CMesWk* this_r3, float arg0_f1, float arg1_f2) {
    // Stack frame allocated: 16 bytes
    f0 = *(float*)0x8016BC54;
    if (r0 == 0) goto label_8009FD9C;
    *(float*)(this_r3 + 0x1C) = arg0_f1;
label_8009FD9C:;
    if (r0 == 0) goto label_8009FDA8;
    *(float*)(this_r3 + 0x20) = arg1_f2;
label_8009FDA8:;
    f13 = *(float*)(this_r3 + 0x20);
    f0 = *(float*)0x8016BC58;
    f10 = *(float*)0x8016BC5C;
    r9 = 0x80170000u;
    stack_0x08 = f12;
    r11 = stack_0x0C;
    stack_0x08 = f11;
    *(uint16_t*)(this_r3 + 0x10) = stack_0x0C;
    r9 = stack_0x0C;
    *(uint16_t*)(this_r3 + 0x16) = stack_0x0C;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::MesWorkTrans(void)
// Unit: mes.obj | Address: 0x8009FDF0 | Size: 0xC4 bytes
// ============================================================================
/* [0x8009FDF0] */ void CMesWk::MesWorkTrans(CMesWk* this_r3) {
    // Stack frame allocated: 40 bytes
    stack_0x2C = r0;
    r29 = this_r3;
    r31 = this_r3 + (88);
    r3 = CMesWk::SetMesCamera(void) const(); // [0x8009FEB4]
    r0 = *(uint32_t*)(this_r3 + 0x1E58);
    if ((this_r3 + 88) >= *(uint32_t*)(this_r3 + 0x1E58)) goto label_8009FE8C;
    r28 = 0xA0A0A0A1u;
label_8009FE24:;
    r30 = *(uint16_t*)((this_r3 + 88) + 0x4);
    r4 = &stack_0x08;
    r3 = &cMes;
    r30 = (*(uint16_t*)((this_r3 + 88) + 0x4) - r9);
    stack_0x08 = *(uint32_t*)(this_r3 + 0x1E58);
    r3 = CMesCtrl::GetFontTexAddr(&cMes, &stack_0x08); // [0x8009F274]
    r4 = ret_8009FE58;
    r3 = this_r3;
    r3 = CMesWk::FontSetAttr(tagFONT_TEX *) const(); // [0x8009FF68]
    r6 = stack_0x08;
    r4 = (this_r3 + 88);
    r5 = (*(uint16_t*)((this_r3 + 88) + 0x4) - r9);
    r3 = this_r3;
    r3 = CMesWk::FontDraw(CMesWk::tagMSG_QUE *, short, short) const(); // [0x800A00DC]
    r31 = (this_r3 + 88) + (20);
    r0 = *(uint32_t*)(this_r3 + 0x1E58);
    if (((this_r3 + 88) + 20) < *(uint32_t*)(this_r3 + 0x1E58)) goto label_8009FE24;
label_8009FE8C:;
    r0 = *(uint32_t*)(this_r3 + 0x28);
    if (((this_r3 + 88) + 20) == *(uint32_t*)(this_r3 + 0x1E58)) goto label_8009FEA0;
    r0 = 0;
    *(uint32_t*)(this_r3 + 0x0) = 0;
label_8009FEA0:;
    r0 = stack_0x2C;
    return; // r3 = ret_8009FE78
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::SetMesCamera(void) const
// Unit: mes.obj | Address: 0x8009FEB4 | Size: 0xB4 bytes
// ============================================================================
/* [0x8009FEB4] */ void CMesWk::SetMesCamera(void) const(void) {
    // Stack frame allocated: 144 bytes
    stack_0x94 = r0;
    f1 = *(float*)0x8016BC60;
    f6 = *(float*)0x8016BC6C;
    f3 = *(float*)0x8016BC64;
    f4 = *(float*)0x8016BC68;
    r27 = &stack_0x48;
    r3 = GXSetViewport(); // [0x80126334]
    r5 = 512;
    r6 = 448;
    r4 = 0;
    r3 = 0;
    r3 = GXSetScissor(); // [0x80126390]
    f1 = *(float*)0x8016BC60;
    f2 = *(float*)0x8016BC68;
    r3 = &stack_0x08;
    f4 = *(float*)0x8016BC64;
    f6 = *(float*)0x8016BC70;
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
    return; // r3 = ret_8009FF50
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::FontSetAttr(tagFONT_TEX *) const
// Unit: mes.obj | Address: 0x8009FF68 | Size: 0x174 bytes
// ============================================================================
/* [0x8009FF68] */ void CMesWk::FontSetAttr(tagFONT_TEX *) const(void) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r31 = r4;
    r3 = 0;
    r3 = GXSetCullMode(); // [0x80120D3C]
    r5 = 1;
    r4 = 3;
    r3 = 0;
    r3 = GXSetZMode(); // [0x80125730]
    r3 = 1;
    r3 = GXSetNumTevStages(); // [0x80125170]
    r3 = 1;
    r3 = GXSetNumChans(); // [0x80122374]
    r3 = 0;
    r4 = 0;
    r3 = GXSetTevOp(); // [0x801249B8]
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 4;
    r3 = GXSetTevOrder(); // [0x80124F98]
    r9 = 2;
    r3 = 4;
    r4 = 0;
    r5 = 1;
    r6 = 1;
    r7 = 0;
    r8 = 0;
    r3 = GXSetChanCtrl(); // [0x801223B8]
    r11 = *(uint32_t*)(r4 + 0x5C);
    r9 = *(uint32_t*)(*(uint32_t*)(r4 + 0x5C) + 0x4);
    r9 = *(uint32_t*)(*(uint32_t*)(r4 + 0x5C) + 0x4) + (-8);
    if ((*(uint32_t*)(*(uint32_t*)(r4 + 0x5C) + 0x4) + -8) > 0x1u) goto label_800A0004;
    r3 = r4 + (32);
    r4 = 0;
    r3 = GXLoadTlut(); // [0x8012327C]
label_800A0004:;
    r3 = r4;
    r4 = 0;
    r3 = GXLoadTexObj(); // [0x8012319C]
    r4 = 30;
    r5 = 1;
    r3 = r4 + (44);
    r3 = GXLoadTexMtxImm(); // [0x80126120]
    r3 = 1;
    r3 = GXSetNumTexGens(); // [0x8011FBD8]
    r8 = 125;
    r7 = 0;
    r3 = 0;
    r4 = 1;
    r5 = 4;
    r6 = 30;
    r3 = GXSetTexCoordGen2(); // [0x8011F908]
    r5 = 5;
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
    r3 = 13;
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
    r3 = 0;
    r4 = 13;
    r5 = 1;
    r6 = 3;
    r7 = 10;
    r3 = GXSetVtxAttrFmt(); // [0x8011EE0C]
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_800A00C4
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::FontDraw(CMesWk::tagMSG_QUE *, short, short) const
// Unit: mes.obj | Address: 0x800A00DC | Size: 0x154 bytes
// ============================================================================
/* [0x800A00DC] */ void CMesWk::FontDraw(CMesWk::tagMSG_QUE *, short, short) const(void) {
    // Stack frame allocated: 56 bytes
    stack_0x3C = r0;
    r30 = r4;
    r21 = r3;
    r29 = *(uint8_t*)(r4 + 0x9);
    r25 = r5;
    r0 = *(uint8_t*)(r4 + 0x8);
    r26 = r6;
    r27 = *(uint32_t*)(r4 + 0x10);
    r28 = *(uint16_t*)(r4 + 0x6);
    r29 = (*(uint8_t*)(r4 + 0x9) - *(uint8_t*)(r4 + 0x8));
    r28 = *(uint16_t*)(r4 + 0x6) + (-1);
    r3 = 128;
    r4 = 0;
    r5 = 4;
    r3 = GXBegin(); // [0x80120A9C]
    r11 = *(int16_t*)(r4 + 0x0);
    r0 = *(uint8_t*)(r4 + 0x8);
    r10 = *(int16_t*)(r4 + 0x2);
    *(uint16_t*)0xCC008000 = *(int16_t*)(r4 + 0x0);
    *(uint16_t*)0xCC008000 = *(int16_t*)(r4 + 0x2);
    r25 = (r5 + *(uint8_t*)(r4 + 0x8));
    *(uint8_t*)0xCC008000 = r23;
    *(uint8_t*)0xCC008000 = *(uint32_t*)(r4 + 0x10);
    r11 = (*(int16_t*)(r4 + 0x0) + (*(uint16_t*)(r4 + 0x6) + -1));
    *(uint8_t*)0xCC008000 = r24;
    *(uint8_t*)0xCC008000 = r22;
    r8 = ((r5 + *(uint8_t*)(r4 + 0x8)) + (*(uint8_t*)(r4 + 0x9) - *(uint8_t*)(r4 + 0x8)));
    *(uint16_t*)0xCC008000 = (r5 + *(uint8_t*)(r4 + 0x8));
    *(uint16_t*)0xCC008000 = r6;
    r7 = r6 + (92);
    *(uint16_t*)0xCC008000 = (*(int16_t*)(r4 + 0x0) + (*(uint16_t*)(r4 + 0x6) + -1));
    *(uint16_t*)0xCC008000 = *(int16_t*)(r4 + 0x2);
    r28 = ((*(int16_t*)(r4 + 0x0) + (*(uint16_t*)(r4 + 0x6) + -1)) - (*(uint16_t*)(r4 + 0x6) + -1));
    *(uint8_t*)0xCC008000 = r23;
    *(uint8_t*)0xCC008000 = *(uint32_t*)(r4 + 0x10);
    r29 = (((r5 + *(uint8_t*)(r4 + 0x8)) + (*(uint8_t*)(r4 + 0x9) - *(uint8_t*)(r4 + 0x8))) - (*(uint8_t*)(r4 + 0x9) - *(uint8_t*)(r4 + 0x8)));
    *(uint8_t*)0xCC008000 = r24;
    *(uint8_t*)0xCC008000 = r22;
    *(uint16_t*)0xCC008000 = ((r5 + *(uint8_t*)(r4 + 0x8)) + (*(uint8_t*)(r4 + 0x9) - *(uint8_t*)(r4 + 0x8)));
    *(uint16_t*)0xCC008000 = r6;
    r0 = *(uint16_t*)(r3 + 0x16);
    *(uint16_t*)0xCC008000 = (*(int16_t*)(r4 + 0x0) + (*(uint16_t*)(r4 + 0x6) + -1));
    r10 = (*(int16_t*)(r4 + 0x2) + *(uint16_t*)(r3 + 0x16));
    *(uint16_t*)0xCC008000 = (*(int16_t*)(r4 + 0x2) + *(uint16_t*)(r3 + 0x16));
    *(uint8_t*)0xCC008000 = r23;
    *(uint8_t*)0xCC008000 = *(uint32_t*)(r4 + 0x10);
    *(uint8_t*)0xCC008000 = r24;
    *(uint8_t*)0xCC008000 = r22;
    *(uint16_t*)0xCC008000 = ((r5 + *(uint8_t*)(r4 + 0x8)) + (*(uint8_t*)(r4 + 0x9) - *(uint8_t*)(r4 + 0x8)));
    *(uint16_t*)0xCC008000 = (r6 + 92);
    *(uint16_t*)0xCC008000 = ((*(int16_t*)(r4 + 0x0) + (*(uint16_t*)(r4 + 0x6) + -1)) - (*(uint16_t*)(r4 + 0x6) + -1));
    *(uint16_t*)0xCC008000 = (*(int16_t*)(r4 + 0x2) + *(uint16_t*)(r3 + 0x16));
    *(uint8_t*)0xCC008000 = r23;
    *(uint8_t*)0xCC008000 = *(uint32_t*)(r4 + 0x10);
    *(uint8_t*)0xCC008000 = r24;
    *(uint8_t*)0xCC008000 = r22;
    *(uint16_t*)0xCC008000 = (((r5 + *(uint8_t*)(r4 + 0x8)) + (*(uint8_t*)(r4 + 0x9) - *(uint8_t*)(r4 + 0x8))) - (*(uint8_t*)(r4 + 0x9) - *(uint8_t*)(r4 + 0x8)));
    *(uint16_t*)0xCC008000 = (r6 + 92);
    r0 = stack_0x3C;
    return; // r3 = ret_800A0140
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::CommandExec(void)
// Unit: mes.obj | Address: 0x800A0230 | Size: 0x144 bytes
// ============================================================================
/* [0x800A0230] */ void CMesWk::CommandExec(CMesWk* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r0 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0);
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) == 7) goto label_800A0314;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) > 7) goto label_800A0284;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) == 3) goto label_800A02DC;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) > 3) goto label_800A0274;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) == 1) goto label_800A02C0;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) > 1) goto label_800A02D4;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) == 0) goto label_800A02B8;
    goto label_800A0360;
label_800A0274:;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) == 5) goto label_800A02F8;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) > 5) goto label_800A030C;
    goto label_800A02E4;
label_800A0284:;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) == 11) goto label_800A0340;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) > 11) goto label_800A02A0;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) == 9) goto label_800A0324;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) > 9) goto label_800A0338;
    goto label_800A031C;
label_800A02A0:;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) == 13) goto label_800A0350;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) < 13) goto label_800A0348;
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) == 14) goto label_800A0358;
    goto label_800A0360;
label_800A02B8:;
    r3 = CMesWk::code00(this_r3); // [0x800A0390]
    goto label_800A0364;
label_800A02C0:;
    r0 = *(uint32_t*)(ret_800A02B8 + 0x28);
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) != 14) goto label_800A0360;
    r3 = CMesWk::code01(ret_800A02B8); // [0x800A040C]
    goto label_800A0364;
label_800A02D4:;
    r3 = CMesWk::code02(ret_800A02CC); // [0x800A0468]
    goto label_800A0364;
label_800A02DC:;
    r3 = CMesWk::code03(ret_800A02D4); // [0x800A04D8]
    goto label_800A0364;
label_800A02E4:;
    r0 = *(uint32_t*)(ret_800A02DC + 0x28);
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) != 14) goto label_800A0360;
    r3 = CMesWk::code04(ret_800A02DC); // [0x800A04FC]
    goto label_800A0364;
label_800A02F8:;
    r0 = *(uint32_t*)(ret_800A02F0 + 0x28);
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) != 14) goto label_800A0360;
    r3 = CMesWk::code05(ret_800A02F0); // [0x800A0530]
    goto label_800A0364;
label_800A030C:;
    r3 = CMesWk::code06(ret_800A0304); // [0x800A0558]
    goto label_800A0364;
label_800A0314:;
    r3 = CMesWk::code07(ret_800A030C); // [0x800A0588]
    goto label_800A0364;
label_800A031C:;
    r3 = CMesWk::code08(ret_800A0314); // [0x800A0630]
    goto label_800A0364;
label_800A0324:;
    r0 = *(uint32_t*)(ret_800A031C + 0x28);
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) != 14) goto label_800A0360;
    r3 = CMesWk::code09(ret_800A031C); // [0x800A083C]
    goto label_800A0364;
label_800A0338:;
    r3 = CMesWk::code0a(ret_800A0330); // [0x800A0884]
    goto label_800A0364;
label_800A0340:;
    r3 = CMesWk::code0b(ret_800A0338); // [0x800A0960]
    goto label_800A0364;
label_800A0348:;
    r3 = CMesWk::code0c(ret_800A0340); // [0x800A0980]
    goto label_800A0364;
label_800A0350:;
    r3 = CMesWk::code0d(ret_800A0348); // [0x800A09A0]
    goto label_800A0364;
label_800A0358:;
    r3 = CMesWk::code0e(ret_800A0350); // [0x800A09C0]
    goto label_800A0364;
label_800A0360:;
    r3 = 0;
label_800A0364:;
    r0 = stack_0x0C;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::CommandArg(void)
// Unit: mes.obj | Address: 0x800A0374 | Size: 0x1C bytes
// ============================================================================
/* [0x800A0374] */ void CMesWk::CommandArg(CMesWk* this_r3) {
    r11 = *(uint32_t*)(this_r3 + 0x40);
    r9 = &arg.633;
    r0 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0);
    r0 = (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) + *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0));
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code00(void)
// Unit: mes.obj | Address: 0x800A0390 | Size: 0x7C bytes
// ============================================================================
/* [0x800A0390] */ void CMesWk::code00(CMesWk* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r30 = this_r3;
    r4 = 0;
    r0 = this_r3 + (88);
    r5 = 7680;
    r3 = (this_r3 + 88);
    *(uint32_t*)(this_r3 + 0x1E58) = (this_r3 + 88);
    r3 = memset(); // [0x800E8A5C]
    r3 = this_r3;
    r3 = CMesWk::WidthCk(this_r3); // [0x8009F8B0]
    r11 = *(uint16_t*)(this_r3 + 0x8);
    r0 = 0;
    r9 = *(uint16_t*)(this_r3 + 0xA);
    r3 = 0;
    *(uint16_t*)(this_r3 + 0x32) = 0;
    *(uint16_t*)(this_r3 + 0xC) = *(uint16_t*)(this_r3 + 0x8);
    *(uint16_t*)(this_r3 + 0xE) = *(uint16_t*)(this_r3 + 0xA);
    *(uint16_t*)(this_r3 + 0x2E) = 0;
    *(uint16_t*)(this_r3 + 0x36) = 0;
    *(uint8_t*)(this_r3 + 0x1E7C) = 0;
    *(uint16_t*)(this_r3 + 0x30) = 0;
    *(uint8_t*)(this_r3 + 0x1A) = 0;
    *(uint8_t*)(this_r3 + 0x1E7F) = 0;
    r0 = stack_0x14;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code01(void)
// Unit: mes.obj | Address: 0x800A040C | Size: 0x5C bytes
// ============================================================================
/* [0x800A040C] */ void CMesWk::code01(CMesWk* this_r3) {
    r9 = *(uint8_t*)(this_r3 + 0x4);
    if (r0 == 0) goto label_800A0428;
    if (r0 == 1) goto label_800A0434;
    goto label_800A0460;
label_800A0428:;
    r0 = *(uint8_t*)(this_r3 + 0x4) + (1);
    *(uint8_t*)(this_r3 + 0x4) = (*(uint8_t*)(this_r3 + 0x4) + 1);
    goto label_800A0460;
label_800A0434:;
    r0 = *(uint32_t*)(this_r3 + 0x0);
    r9 = *(uint32_t*)(this_r3 + 0x28);
    r0 = *(uint32_t*)(this_r3 + 0x0) | 0x0002u;
    *(uint32_t*)(this_r3 + 0x0) = *(uint32_t*)(this_r3 + 0x0);
    if (r0 != 1) goto label_800A0460;
    r0 = *(uint32_t*)0x8019D694;
    if (r0 == 1) goto label_800A0460;
    *(uint32_t*)(this_r3 + 0x0) = r11;
label_800A0460:;
    r3 = 1;
    return; // r3 = 1
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code02(void)
// Unit: mes.obj | Address: 0x800A0468 | Size: 0x70 bytes
// ============================================================================
/* [0x800A0468] */ void CMesWk::code02(CMesWk* this_r3) {
    r11 = *(uint32_t*)(this_r3 + 0x40);
    r0 = 0;
    r0 = 0 | 0xFFFFu;
    r9 = *(uint32_t*)(this_r3 + 0x40) + (2);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + 2);
    r9 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2);
    r10 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2);
    if (*(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2) != 0) goto label_800A04B0;
    r9 = *(uint8_t*)(this_r3 + 0x3E);
    r11 = this_r3 + (56);
    r0 = *(uint8_t*)(this_r3 + 0x3E) + (1);
    *(uint8_t*)(this_r3 + 0x3E) = (*(uint8_t*)(this_r3 + 0x3E) + 1);
    r9 = (*(uint8_t*)(this_r3 + 0x3E) + *(uint8_t*)(this_r3 + 0x3E));
    if ((*(uint8_t*)(this_r3 + 0x3E) + *(uint8_t*)(this_r3 + 0x3E)) == *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2)) goto label_800A04D0;
label_800A04B0:;
    r11 = *(uint32_t*)(this_r3 + 0x40);
    r0 = *(uint32_t*)(this_r3 + 0x44);
    *(uint32_t*)(this_r3 + 0x48) = *(uint32_t*)(this_r3 + 0x40);
    r9 = ((*(uint8_t*)(this_r3 + 0x3E) + *(uint8_t*)(this_r3 + 0x3E)) + *(uint32_t*)(this_r3 + 0x44));
    r11 = *(uint32_t*)(((*(uint8_t*)(this_r3 + 0x3E) + *(uint8_t*)(this_r3 + 0x3E)) + *(uint32_t*)(this_r3 + 0x44)) + 0x8);
    r0 = (*(uint32_t*)(this_r3 + 0x44) + *(uint32_t*)(((*(uint8_t*)(this_r3 + 0x3E) + *(uint8_t*)(this_r3 + 0x3E)) + *(uint32_t*)(this_r3 + 0x44)) + 0x8));
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x44) + *(uint32_t*)(((*(uint8_t*)(this_r3 + 0x3E) + *(uint8_t*)(this_r3 + 0x3E)) + *(uint32_t*)(this_r3 + 0x44)) + 0x8));
label_800A04D0:;
    r3 = 0;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code03(void)
// Unit: mes.obj | Address: 0x800A04D8 | Size: 0x24 bytes
// ============================================================================
/* [0x800A04D8] */ void CMesWk::code03(CMesWk* this_r3) {
    r9 = this_r3;
    r0 = *(uint16_t*)(this_r3 + 0xE);
    r3 = 0;
    r11 = *(uint16_t*)(this_r3 + 0x10);
    r10 = *(uint16_t*)(this_r3 + 0x8);
    r0 = (*(uint16_t*)(this_r3 + 0xE) + *(uint16_t*)(this_r3 + 0x10));
    *(uint16_t*)(this_r3 + 0xC) = *(uint16_t*)(this_r3 + 0x8);
    *(uint16_t*)(this_r3 + 0xE) = (*(uint16_t*)(this_r3 + 0xE) + *(uint16_t*)(this_r3 + 0x10));
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code04(void)
// Unit: mes.obj | Address: 0x800A04FC | Size: 0x34 bytes
// ============================================================================
/* [0x800A04FC] */ void CMesWk::code04(CMesWk* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r11 = this_r3;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r9 = *(uint32_t*)(this_r3 + 0x40) + (2);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + 2);
    r3 = CMesWk::code00(this_r3); // [0x800A0390]
    r3 = 1;
    r0 = stack_0x0C;
    return; // r3 = 1
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code05(void)
// Unit: mes.obj | Address: 0x800A0530 | Size: 0x28 bytes
// ============================================================================
/* [0x800A0530] */ void CMesWk::code05(CMesWk* this_r3) {
    r9 = this_r3;
    r8 = 0;
    r10 = *(uint32_t*)(this_r3 + 0x40);
    r3 = 0;
    r0 = *(uint32_t*)(this_r3 + 0x40) + (2);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + 2);
    r11 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2);
    *(uint16_t*)(this_r3 + 0x2E) = 0;
    *(uint16_t*)(this_r3 + 0x2C) = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2);
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code06(void)
// Unit: mes.obj | Address: 0x800A0558 | Size: 0x30 bytes
// ============================================================================
/* [0x800A0558] */ void CMesWk::code06(CMesWk* this_r3) {
    r10 = this_r3;
    r8 = *(uint32_t*)(this_r3 + 0x40);
    r11 = &col_tbl.655;
    r3 = 0;
    r9 = *(uint32_t*)(this_r3 + 0x40) + (2);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + 2);
    r0 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2);
    *(uint32_t*)(this_r3 + 0x24) = (*(uint32_t*)(this_r3 + 0x40) + 2);
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code07(void)
// Unit: mes.obj | Address: 0x800A0588 | Size: 0xA8 bytes
// ============================================================================
/* [0x800A0588] */ void CMesWk::code07(CMesWk* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r31 = this_r3;
    r0 = *(int16_t*)(this_r3 + 0x30);
    if (*(int16_t*)(this_r3 + 0x30) != 0) goto label_800A05B0;
    r0 = *(uint16_t*)(this_r3 + 0x2C);
    *(uint16_t*)(this_r3 + 0x30) = *(uint16_t*)(this_r3 + 0x2C);
label_800A05B0:;
    r9 = *(uint8_t*)(this_r3 + 0x1E7C);
    r30 = 0;
    r10 = *(uint32_t*)(this_r3 + 0x1E58);
    r11 = this_r3 + (7772);
    *(uint16_t*)(this_r3 + 0x2C) = 0;
    r9 = *(uint8_t*)(this_r3 + 0x1E7C) + (1);
    *(uint8_t*)(this_r3 + 0x1E7C) = (*(uint8_t*)(this_r3 + 0x1E7C) + 1);
    r4 = 1;
    r3 = &cMes;
    r5 = *(uint32_t*)(this_r3 + 0x1E58);
    f1 = *(float*)(this_r3 + 0x1C);
    r6 = *(uint32_t*)(this_r3 + 0x1E58) + (9);
    r5 = *(uint32_t*)(this_r3 + 0x1E58) + (8);
    r3 = CMesCtrl::GetFontSize(short, signed char &, signed char &, float) const(); // [0x8009F2BC]
    r9 = *(uint32_t*)(this_r3 + 0x1E58);
    r0 = ret_800A05F4 + (1);
    r3 = this_r3;
    r4 = 0;
    *(uint16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6) = (ret_800A05F4 + 1);
    r3 = CMesWk::QueSet(this_r3, 0); // [0x8009FA94]
    *(uint8_t*)(this_r3 + 0x1E7D) = 0;
    r3 = 0;
    *(uint8_t*)(this_r3 + 0x1E7E) = 0;
    r0 = stack_0x14;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code08(void)
// Unit: mes.obj | Address: 0x800A0630 | Size: 0x20C bytes
// ============================================================================
/* [0x800A0630] */ void CMesWk::code08(CMesWk* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r31 = this_r3;
    r30 = 1;
    r0 = *(uint8_t*)(this_r3 + 0x1A);
    if (*(uint8_t*)(this_r3 + 0x1A) != 0) goto label_800A067C;
    r0 = *(uint32_t*)(this_r3 + 0x28);
    if (*(uint8_t*)(this_r3 + 0x1A) == 0) goto label_800A0670;
    r9 = *(uint8_t*)(this_r3 + 0x1E7C);
    r9 = *(uint8_t*)(this_r3 + 0x1E7C) + (-1);
    *(uint8_t*)(this_r3 + 0x1E7E) = (*(uint8_t*)(this_r3 + 0x1E7C) + -1);
    r3 = CMesWk::putSelCursol(this_r3); // [0x8009FB68]
label_800A0670:;
    *(uint8_t*)(this_r3 + 0x1A) = 1;
    r3 = 1;
    goto label_800A0828;
label_800A067C:;
    r11 = *(uint8_t*)(this_r3 + 0x1E7C);
    if (*(uint8_t*)(this_r3 + 0x1E7C) == 0) goto label_800A07F8;
    r0 = *(uint32_t*)0x8019D694;
    if (*(uint8_t*)(this_r3 + 0x1E7C) == 0) goto label_800A06C0;
    r9 = *(uint8_t*)(this_r3 + 0x1E7E);
    r30 = 0;
    r0 = *(uint32_t*)(this_r3 + 0x28);
    r9 = *(uint8_t*)(this_r3 + 0x1E7E) + (1);
    *(uint8_t*)(this_r3 + 0x1E7D) = (*(uint8_t*)(this_r3 + 0x1E7E) + 1);
    if (*(uint8_t*)(this_r3 + 0x1E7C) != 0) goto label_800A07EC;
    r3 = 0;
    r4 = 1;
    goto label_800A0794;
label_800A06C0:;
    r0 = *(uint32_t*)(this_r3 + 0x28);
    if (*(uint8_t*)(this_r3 + 0x1E7C) == 0) goto label_800A06E8;
    if (*(uint8_t*)(this_r3 + 0x1E7C) == 0) goto label_800A06E8;
    *(uint8_t*)(this_r3 + 0x1E7D) = *(uint8_t*)(this_r3 + 0x1E7C);
    r30 = 0;
    r3 = 0;
    r4 = 2;
    goto label_800A0794;
label_800A06E8:;
    if (*(uint8_t*)(this_r3 + 0x1E7C) == 0) goto label_800A0754;
    r9 = *(uint32_t*)0x8019D69C;
    r0 = 0x00080008u;
    if (*(uint8_t*)(this_r3 + 0x1E7C) == 0) goto label_800A071C;
    r9 = *(uint8_t*)(this_r3 + 0x1E7E);
    r9 = *(uint8_t*)(this_r3 + 0x1E7E) + (-1);
    *(uint8_t*)(this_r3 + 0x1E7E) = (*(uint8_t*)(this_r3 + 0x1E7E) + -1);
    goto label_800A077C;
label_800A071C:;
    r0 = 0x00040004u;
    if (*(uint8_t*)(this_r3 + 0x1E7C) == 0) goto label_800A07EC;
    r9 = *(uint8_t*)(this_r3 + 0x1E7E);
    r0 = *(uint8_t*)(this_r3 + 0x1E7C);
    r9 = *(uint8_t*)(this_r3 + 0x1E7E) + (1);
    *(uint8_t*)(this_r3 + 0x1E7E) = (*(uint8_t*)(this_r3 + 0x1E7E) + 1);
    if (*(uint8_t*)(this_r3 + 0x1E7C) < *(uint8_t*)(this_r3 + 0x1E7C)) goto label_800A078C;
    *(uint8_t*)(this_r3 + 0x1E7E) = r10;
    goto label_800A078C;
label_800A0754:;
    r9 = *(uint32_t*)0x8019D69C;
    r0 = 0x00010001u;
    if (*(uint8_t*)(this_r3 + 0x1E7C) == *(uint8_t*)(this_r3 + 0x1E7C)) goto label_800A07A4;
    r9 = *(uint8_t*)(this_r3 + 0x1E7E);
    r9 = *(uint8_t*)(this_r3 + 0x1E7E) + (-1);
    *(uint8_t*)(this_r3 + 0x1E7E) = (*(uint8_t*)(this_r3 + 0x1E7E) + -1);
label_800A077C:;
    if (*(uint8_t*)(this_r3 + 0x1E7C) == *(uint8_t*)(this_r3 + 0x1E7C)) goto label_800A078C;
    r9 = *(uint8_t*)(this_r3 + 0x1E7C);
    r9 = *(uint8_t*)(this_r3 + 0x1E7C) + (-1);
    *(uint8_t*)(this_r3 + 0x1E7E) = (*(uint8_t*)(this_r3 + 0x1E7C) + -1);
label_800A078C:;
    r3 = 0;
    r4 = 0;
label_800A0794:;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
    goto label_800A07EC;
label_800A07A4:;
    r0 = 0x00020002u;
    if (*(uint8_t*)(this_r3 + 0x1E7C) == *(uint8_t*)(this_r3 + 0x1E7C)) goto label_800A07EC;
    r9 = *(uint8_t*)(this_r3 + 0x1E7E);
    r0 = *(uint8_t*)(this_r3 + 0x1E7C);
    r9 = *(uint8_t*)(this_r3 + 0x1E7E) + (1);
    *(uint8_t*)(this_r3 + 0x1E7E) = (*(uint8_t*)(this_r3 + 0x1E7E) + 1);
    if (*(uint8_t*)(this_r3 + 0x1E7C) < *(uint8_t*)(this_r3 + 0x1E7C)) goto label_800A07D8;
    *(uint8_t*)(this_r3 + 0x1E7E) = r10;
label_800A07D8:;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
label_800A07EC:;
    r3 = this_r3;
    r3 = CMesWk::putSelCursol(this_r3); // [0x8009FB68]
    goto label_800A0824;
label_800A07F8:;
    r3 = this_r3;
    r4 = 1;
    r3 = CMesWk::putNextCursol(this_r3, 1); // [0x8009FBB8]
    r0 = *(uint32_t*)0x8019D694;
    if (*(uint8_t*)(this_r3 + 0x1E7C) == *(uint8_t*)(this_r3 + 0x1E7C)) goto label_800A0824;
    r3 = this_r3;
    r30 = 0;
    r4 = 0;
    r3 = CMesWk::putNextCursol(this_r3, 0); // [0x8009FBB8]
label_800A0824:;
    r3 = 0;
label_800A0828:;
    r0 = stack_0x14;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code09(void)
// Unit: mes.obj | Address: 0x800A083C | Size: 0x48 bytes
// ============================================================================
/* [0x800A083C] */ void CMesWk::code09(CMesWk* this_r3) {
    r9 = *(uint16_t*)(this_r3 + 0x36);
    r10 = 1;
    if (*(uint16_t*)(this_r3 + 0x36) != 0) goto label_800A0864;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r0 = *(uint32_t*)(this_r3 + 0x40) + (2);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + 2);
    r11 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2);
    *(uint16_t*)(this_r3 + 0x36) = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2);
    goto label_800A087C;
label_800A0864:;
    r0 = *(uint32_t*)(this_r3 + 0x40) + (-1);
    *(uint16_t*)(this_r3 + 0x36) = (*(uint32_t*)(this_r3 + 0x40) + -1);
    if (*(uint32_t*)(this_r3 + 0x40) != 0) goto label_800A087C;
    r10 = 0;
label_800A087C:;
    r3 = 0;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code0a(void)
// Unit: mes.obj | Address: 0x800A0884 | Size: 0xDC bytes
// ============================================================================
/* [0x800A0884] */ void CMesWk::code0a(CMesWk* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r31 = this_r3;
    r5 = *(uint32_t*)(this_r3 + 0x1E58);
    r0 = this_r3 + (7768);
    if (*(uint32_t*)(this_r3 + 0x1E58) >= (this_r3 + 7768)) goto label_800A0930;
    r9 = *(uint16_t*)(this_r3 + 0x4C);
    r0 = *(uint16_t*)(this_r3 + 0x4E);
    if (r29 <= 0x9u) goto label_800A08C0;
    r29 = 0;
label_800A08C0:;
    r30 = 0 + (3);
    r6 = *(uint32_t*)(this_r3 + 0x1E58) + (9);
    f1 = *(float*)(this_r3 + 0x1C);
    r5 = *(uint32_t*)(this_r3 + 0x1E58) + (8);
    r3 = &cMes;
    r3 = CMesCtrl::GetFontSize(short, signed char &, signed char &, float) const(); // [0x8009F2BC]
    r9 = *(uint32_t*)(this_r3 + 0x1E58);
    r0 = ret_800A08E0 + (1);
    r4 = (0 + 3);
    r3 = this_r3;
    *(uint16_t*)(*(uint32_t*)(this_r3 + 0x1E58) + 0x6) = (ret_800A08E0 + 1);
    r3 = CMesWk::QueSet(this_r3, (0 + 3)); // [0x8009FA94]
    r9 = *(uint16_t*)(this_r3 + 0x4E);
    r0 = 0xCCCCCCCDu;
    r11 = *(uint16_t*)(this_r3 + 0x4C);
    *(uint16_t*)(this_r3 + 0x4E) = 0xCCCCCCCDu;
    r11 = (*(uint16_t*)(this_r3 + 0x4C) - *(uint16_t*)(this_r3 + 0x4E));
    *(uint16_t*)(this_r3 + 0x4C) = (*(uint16_t*)(this_r3 + 0x4C) - *(uint16_t*)(this_r3 + 0x4E));
    if (r10 == 0) goto label_800A0938;
label_800A0930:;
    r3 = 1;
    goto label_800A094C;
label_800A0938:;
    r9 = *(uint16_t*)(this_r3 + 0x50);
    r3 = 0;
    r0 = *(uint16_t*)(this_r3 + 0x52);
    *(uint16_t*)(this_r3 + 0x4C) = *(uint16_t*)(this_r3 + 0x50);
    *(uint16_t*)(this_r3 + 0x4E) = *(uint16_t*)(this_r3 + 0x52);
label_800A094C:;
    r0 = stack_0x1C;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code0b(void)
// Unit: mes.obj | Address: 0x800A0960 | Size: 0x20 bytes
// ============================================================================
/* [0x800A0960] */ void CMesWk::code0b(CMesWk* this_r3) {
    r11 = this_r3;
    r10 = *(uint32_t*)(this_r3 + 0x40);
    r3 = 0;
    r0 = *(uint32_t*)(this_r3 + 0x40) + (2);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + 2);
    r9 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2);
    *(uint16_t*)(this_r3 + 0xC) = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2);
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code0c(void)
// Unit: mes.obj | Address: 0x800A0980 | Size: 0x20 bytes
// ============================================================================
/* [0x800A0980] */ void CMesWk::code0c(CMesWk* this_r3) {
    r11 = this_r3;
    r10 = *(uint32_t*)(this_r3 + 0x40);
    r3 = 0;
    r0 = *(uint32_t*)(this_r3 + 0x40) + (2);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + 2);
    r9 = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2);
    *(uint16_t*)(this_r3 + 0xE) = *(uint16_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x2);
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code0d(void)
// Unit: mes.obj | Address: 0x800A09A0 | Size: 0x20 bytes
// ============================================================================
/* [0x800A09A0] */ void CMesWk::code0d(CMesWk* this_r3) {
    r9 = this_r3;
    r11 = *(uint32_t*)(this_r3 + 0x40);
    r3 = 0;
    r11 = *(uint32_t*)(this_r3 + 0x40) + (2);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + 2);
    r0 = *(uint8_t*)((*(uint32_t*)(this_r3 + 0x40) + 2) + 0x1);
    *(uint8_t*)(this_r3 + 0x1B) = *(uint8_t*)((*(uint32_t*)(this_r3 + 0x40) + 2) + 0x1);
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code0e(void)
// Unit: mes.obj | Address: 0x800A09C0 | Size: 0x20 bytes
// ============================================================================
/* [0x800A09C0] */ void CMesWk::code0e(CMesWk* this_r3) {
    r9 = *(uint32_t*)(this_r3 + 0x48);
    if (*(uint32_t*)(this_r3 + 0x48) == 0) goto label_800A09D8;
    r0 = 0;
    *(uint32_t*)(this_r3 + 0x40) = *(uint32_t*)(this_r3 + 0x48);
    *(uint32_t*)(this_r3 + 0x48) = 0;
label_800A09D8:;
    r3 = 0;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::code0f(void)
// Unit: mes.obj | Address: 0x800A09E0 | Size: 0x8 bytes
// ============================================================================
/* [0x800A09E0] */ void CMesWk::code0f(CMesWk* this_r3) {
    r3 = 0;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: __static_initialization_and_destruction_0
// Unit: mes.obj | Address: 0x800A09E8 | Size: 0xD0 bytes
// ============================================================================
/* [0x800A09E8] */ void __static_initialization_and_destruction_0(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r0 = 0;
    r0 = 0 | 0xFFFFu;
    if (r4 != 0) goto label_800A0AA4;
    if (r3 == 0) goto label_800A0A4C;
    r11 = &cMes;
    r0 = 5;
    r9 = &vtable_CMesCtrl;
    *(uint32_t*)((&cMes + 0x00010000u) - 0x636C) = &vtable_CMesCtrl;
    r8 = &vtable_CMesWk;
    r11 = &cMes + (4);
label_800A0A3C:;
    *(uint32_t*)((&cMes + 4) + 0x1E80) = &vtable_CMesWk;
    r11 = (&cMes + 4) + (7812);
    if (r3 >= 0) goto label_800A0A3C;
    goto label_800A0AA4;
label_800A0A4C:;
    r9 = &cMes;
    r11 = &vtable_CMesCtrl;
    *(uint32_t*)((&cMes + 0x00010000u) - 0x636C) = &vtable_CMesCtrl;
    if (r3 == 0) goto label_800A0AA4;
    r31 = (&cMes + 0x00010000u) + (-26472);
    if (&cMes == ((&cMes + 0x00010000u) + -26472)) goto label_800A0AA4;
    r30 = &cMes;
label_800A0A7C:;
    r31 = ((&cMes + 0x00010000u) + -26472) + (-7812);
    r4 = 0;
    r9 = *(uint32_t*)((((&cMes + 0x00010000u) + -26472) + -7812) + 0x1E80);
    r3 = *(int16_t*)(*(uint32_t*)((((&cMes + 0x00010000u) + -26472) + -7812) + 0x1E80) + 0x8);
    r0 = *(uint32_t*)(*(uint32_t*)((((&cMes + 0x00010000u) + -26472) + -7812) + 0x1E80) + 0xC);
    r3 = ((((&cMes + 0x00010000u) + -26472) + -7812) + *(int16_t*)(*(uint32_t*)((((&cMes + 0x00010000u) + -26472) + -7812) + 0x1E80) + 0x8));
    return; // r3 = ((((&cMes + 0x00010000u) + -26472) + -7812) + *(int16_t*)(*(uint32_t*)((((&cMes + 0x00010000u) + -26472) + -7812) + 0x1E80) + 0x8))
    if (&cMes != (((&cMes + 0x00010000u) + -26472) + -7812)) goto label_800A0A7C;
label_800A0AA4:;
    r0 = stack_0x14;
    return; // r3 = ((((&cMes + 0x00010000u) + -26472) + -7812) + *(int16_t*)(*(uint32_t*)((((&cMes + 0x00010000u) + -26472) + -7812) + 0x1E80) + 0x8))
}

// ============================================================================
// High-Level AST Decompilation: CMesWk::~CMesWk(void)
// Unit: mes.obj | Address: 0x800A0AB8 | Size: 0x34 bytes
// ============================================================================
/* [0x800A0AB8] */ void CMesWk::~CMesWk(CMesWk* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = &vtable_CMesWk;
    *(uint32_t*)(this_r3 + 0x1E80) = &vtable_CMesWk;
    if (r0 == 0) goto label_800A0ADC;
    r3 = __builtin_delete(); // [0x8009C908]
label_800A0ADC:;
    r0 = stack_0x0C;
    return; // r3 = ret_800A0AD8
}

// ============================================================================
// High-Level AST Decompilation: CMesCtrl::~CMesCtrl(void)
// Unit: mes.obj | Address: 0x800A0AEC | Size: 0x8C bytes
// ============================================================================
/* [0x800A0AEC] */ void CMesCtrl::~CMesCtrl(CMesCtrl* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r30 = this_r3;
    r9 = &vtable_CMesCtrl;
    r28 = r4;
    *(uint32_t*)((this_r3 + 0x00010000u) - 0x636C) = &vtable_CMesCtrl;
    if (r0 == 0) goto label_800A0B54;
    r31 = (this_r3 + 0x00010000u) + (-26472);
    if (r0 == ((this_r3 + 0x00010000u) + -26472)) goto label_800A0B54;
    r29 = r0;
label_800A0B2C:;
    r31 = ((this_r3 + 0x00010000u) + -26472) + (-7812);
    r4 = 0;
    r9 = *(uint32_t*)((((this_r3 + 0x00010000u) + -26472) + -7812) + 0x1E80);
    r3 = *(int16_t*)(*(uint32_t*)((((this_r3 + 0x00010000u) + -26472) + -7812) + 0x1E80) + 0x8);
    r0 = *(uint32_t*)(*(uint32_t*)((((this_r3 + 0x00010000u) + -26472) + -7812) + 0x1E80) + 0xC);
    r3 = ((((this_r3 + 0x00010000u) + -26472) + -7812) + *(int16_t*)(*(uint32_t*)((((this_r3 + 0x00010000u) + -26472) + -7812) + 0x1E80) + 0x8));
    return; // r3 = ((((this_r3 + 0x00010000u) + -26472) + -7812) + *(int16_t*)(*(uint32_t*)((((this_r3 + 0x00010000u) + -26472) + -7812) + 0x1E80) + 0x8))
    if (r0 != (((this_r3 + 0x00010000u) + -26472) + -7812)) goto label_800A0B2C;
label_800A0B54:;
    if (r0 == (((this_r3 + 0x00010000u) + -26472) + -7812)) goto label_800A0B64;
    r3 = this_r3;
    r3 = __builtin_delete(); // [0x8009C908]
label_800A0B64:;
    r0 = stack_0x1C;
    return; // r3 = ret_800A0B60
}

// ============================================================================
// High-Level AST Decompilation: global constructors keyed to font_j_width
// Unit: mes.obj | Address: 0x800A0B78 | Size: 0x2C bytes
// ============================================================================
/* [0x800A0B78] */ void global constructors keyed to font_j_width(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r4 = 0;
    r3 = 1;
    r4 = 0 | 0xFFFFu;
    r3 = __static_initialization_and_destruction_0(); // [0x800A09E8]
    r0 = stack_0x0C;
    return; // r3 = ret_800A0B90
}

// ============================================================================
// High-Level AST Decompilation: global destructors keyed to font_j_width
// Unit: mes.obj | Address: 0x800A0BA4 | Size: 0x2C bytes
// ============================================================================
/* [0x800A0BA4] */ void global destructors keyed to font_j_width(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r4 = 0;
    r3 = 0;
    r4 = 0 | 0xFFFFu;
    r3 = __static_initialization_and_destruction_0(); // [0x800A09E8]
    r0 = stack_0x0C;
    return; // r3 = ret_800A0BBC
}
