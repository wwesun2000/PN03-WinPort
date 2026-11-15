// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: option.obj
// Functions Decompiled: 28
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: OptionTask(unsigned long *)
// Unit: option.obj | Address: 0x800AAF64 | Size: 0xB0 bytes
// ============================================================================
/* [0x800AAF64] */ void OptionTask(unsigned long * arg0_r3) {
    // Stack frame allocated: 112 bytes
    stack_0x74 = r0;
    r30 = &stack_0x08;
    r27 = &vtable_cSubScrn;
    *(uint32_t*)(&stack_0x08 + 0x24) = &vtable_cSubScrn;
    r28 = &vtable_cCursol;
    r25 = &stack_0x18;
    *(uint32_t*)(&stack_0x18 + 0x8) = &vtable_cCursol;
    r29 = &vtable_cAram2Mem;
    r26 = &stack_0x24;
    r0 = 0;
    *(uint32_t*)(&stack_0x24 + 0x4) = &vtable_cAram2Mem;
    stack_0x24 = 0;
    r9 = &vtable_cOptionCtrl;
    *(uint8_t*)(&stack_0x08 + 0x3) = 0;
    r11 = 1;
    *(uint8_t*)(&stack_0x08 + 0x2) = 0;
    *(uint8_t*)(&stack_0x08 + 0x1) = 0;
    stack_0x08 = 0;
    *(uint32_t*)(&stack_0x08 + 0x24) = &vtable_cOptionCtrl;
    *(uint32_t*)(&stack_0x08 + 0x8) = 1;
    *(uint32_t*)(&stack_0x08 + 0x40) = 0;
    *(uint32_t*)(&stack_0x08 + 0x4) = 0;
    *(uint32_t*)(&stack_0x08 + 0xC) = 0;
    *(uint32_t*)(&stack_0x08 + 0x34) = 0;
    *(uint32_t*)(&stack_0x08 + 0x38) = 0;
    stack_0x48 = arg0_r3;
    r3 = &stack_0x08;
    r3 = cOptionCtrl::Option(&stack_0x08); // [0x800AB0D4]
    *(uint32_t*)(&stack_0x08 + 0x24) = &vtable_cSubScrn;
    *(uint32_t*)(&stack_0x24 + 0x4) = &vtable_cAram2Mem;
    *(uint32_t*)(&stack_0x18 + 0x8) = &vtable_cCursol;
    r3 = TaskExit(); // [0x800A1C38]
    r0 = stack_0x74;
    return; // r3 = ret_800AAFFC
}

// ============================================================================
// High-Level AST Decompilation: OptionTaskTitle(void)
// Unit: option.obj | Address: 0x800AB014 | Size: 0xC0 bytes
// ============================================================================
/* [0x800AB014] */ void OptionTaskTitle(void) {
    // Stack frame allocated: 112 bytes
    stack_0x74 = r0;
    r30 = &stack_0x08;
    r3 = 0;
    r3 = TaskSuspend(0); // [0x800A1CF4]
    r25 = &stack_0x18;
    r26 = &stack_0x24;
    r3 = 1;
    r3 = TaskSleep(1); // [0x800A1B5C]
    r28 = &vtable_cSubScrn;
    r27 = &vtable_cCursol;
    *(uint32_t*)(&stack_0x08 + 0x24) = &vtable_cSubScrn;
    *(uint32_t*)(&stack_0x18 + 0x8) = &vtable_cCursol;
    r29 = &vtable_cAram2Mem;
    *(uint32_t*)(&stack_0x24 + 0x4) = &vtable_cAram2Mem;
    r0 = 0;
    stack_0x24 = 0;
    *(uint8_t*)(&stack_0x08 + 0x3) = 0;
    r9 = &vtable_cOptionCtrl;
    *(uint8_t*)(&stack_0x08 + 0x2) = 0;
    r3 = &stack_0x08;
    *(uint8_t*)(&stack_0x08 + 0x1) = 0;
    stack_0x08 = 0;
    *(uint32_t*)(&stack_0x08 + 0x24) = &vtable_cOptionCtrl;
    *(uint32_t*)(&stack_0x08 + 0x40) = 0;
    *(uint32_t*)(&stack_0x08 + 0x4) = 0;
    *(uint32_t*)(&stack_0x08 + 0xC) = 0;
    *(uint32_t*)(&stack_0x08 + 0x34) = 0;
    *(uint32_t*)(&stack_0x08 + 0x38) = 0;
    *(uint32_t*)(&stack_0x08 + 0x8) = 0;
    r3 = cOptionCtrl::Option(&stack_0x08); // [0x800AB0D4]
    *(uint32_t*)(&stack_0x08 + 0x24) = &vtable_cSubScrn;
    r3 = 0;
    *(uint32_t*)(&stack_0x24 + 0x4) = &vtable_cAram2Mem;
    *(uint32_t*)(&stack_0x18 + 0x8) = &vtable_cCursol;
    r3 = TaskSignal(0); // [0x800A1D14]
    r3 = TaskExit(); // [0x800A1C38]
    r0 = stack_0x74;
    return; // r3 = ret_800AB0BC
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::Option(void)
// Unit: option.obj | Address: 0x800AB0D4 | Size: 0xE8 bytes
// ============================================================================
/* [0x800AB0D4] */ void cOptionCtrl::Option(cOptionCtrl* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r31 = this_r3;
    r0 = *(uint32_t*)(this_r3 + 0x4);
    if (*(uint32_t*)(this_r3 + 0x4) != 0) goto label_800AB1A8;
    r29 = 0;
    r30 = 4;
label_800AB0FC:;
    r0 = *(uint8_t*)(this_r3 + 0x0);
    *(uint32_t*)(this_r3 + 0x4) = 0;
    if (*(uint8_t*)(this_r3 + 0x0) == 2) goto label_800AB150;
    if (*(uint8_t*)(this_r3 + 0x0) > 2) goto label_800AB124;
    if (*(uint8_t*)(this_r3 + 0x0) == 0) goto label_800AB138;
    if (*(uint8_t*)(this_r3 + 0x0) == 1) goto label_800AB144;
    goto label_800AB174;
label_800AB124:;
    if (*(uint8_t*)(this_r3 + 0x0) == 3) goto label_800AB15C;
    if (*(uint8_t*)(this_r3 + 0x0) == 4) goto label_800AB168;
    goto label_800AB174;
label_800AB138:;
    r3 = this_r3;
    r3 = cOptionCtrl::OptionInit(this_r3); // [0x800AB1BC]
    goto label_800AB178;
label_800AB144:;
    r3 = this_r3;
    r3 = cOptionCtrl::OptionOpen(this_r3); // [0x800AB440]
    goto label_800AB178;
label_800AB150:;
    r3 = this_r3;
    r3 = cOptionCtrl::OptionMenu(this_r3); // [0x800AB550]
    goto label_800AB178;
label_800AB15C:;
    r3 = this_r3;
    r3 = cOptionCtrl::OptionClose(this_r3); // [0x800AB5C8]
    goto label_800AB178;
label_800AB168:;
    r3 = this_r3;
    r3 = cOptionCtrl::OptionQuit(this_r3); // [0x800AB6F4]
    goto label_800AB178;
label_800AB174:;
    *(uint8_t*)(this_r3 + 0x0) = 4;
label_800AB178:;
    r3 = this_r3;
    r3 = cOptionCtrl::optionTrans(this_r3); // [0x800AC9A8]
    r0 = *(uint8_t*)(this_r3 + 0x0);
    if (*(uint8_t*)(this_r3 + 0x0) > 0x2u) goto label_800AB194;
    r3 = this_r3;
    r3 = cOptionCtrl::optionMessage(void) const(); // [0x800ACA0C]
label_800AB194:;
    r3 = 1;
    r3 = TaskSleep(1); // [0x800A1B5C]
    r0 = *(uint32_t*)(this_r3 + 0x4);
    if (*(uint32_t*)(this_r3 + 0x4) == 0) goto label_800AB0FC;
label_800AB1A8:;
    r0 = stack_0x1C;
    return; // r3 = ret_800AB198
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::OptionInit(void)
// Unit: option.obj | Address: 0x800AB1BC | Size: 0x284 bytes
// ============================================================================
/* [0x800AB1BC] */ void cOptionCtrl::OptionInit(cOptionCtrl* this_r3) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r29 = this_r3;
    r0 = 4;
    r9 = 2;
    r28 = this_r3 + (28);
    *(uint8_t*)(this_r3 + 0x0) = 4;
    r3 = (this_r3 + 28);
    *(uint32_t*)(this_r3 + 0x4) = 2;
    r4 = 1;
    r3 = cAram2Mem::DeployData((this_r3 + 28), 1); // [0x800D0B2C]
    if (ret_800AB1EC == 0) goto label_800AB42C;
    r0 = 0x8048001Cu;
    r9 = 0x80480038u;
    *(uint32_t*)(this_r3 + 0x2C) = 0x8048001Cu;
    *(uint32_t*)(this_r3 + 0x28) = 0x80480000u;
    r3 = (this_r3 + 28);
    *(uint32_t*)(this_r3 + 0x30) = 0x80480038u;
    r3 = cAram2Mem::GetWorkAddr(void) const(); // [0x800D0E0C]
    r31 = 0x80480054u;
    r30 = ret_800AB220;
    r3 = (this_r3 + 28);
    r3 = cAram2Mem::GetWorkSize(void) const(); // [0x800D0E18]
    r30 = (ret_800AB220 + ret_800AB230);
    if (0x80480054u <= (ret_800AB220 + ret_800AB230)) goto label_800AB25C;
    r3 = 0;
    r5 = "Work size is over!!";
    r4 = 0;
    r3 = LogErr(0, 0, "Work size is over!!", r6); // [0x8007A05C]
    goto label_800AB42C;
label_800AB25C:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    if (0x80480054u != (ret_800AB220 + ret_800AB230)) goto label_800AB2F8;
    r4 = 35;
    r3 = (this_r3 + 28);
    r3 = cAram2Mem::GetSize(long) const(); // [0x800D0D9C]
    r30 = ret_800AB270;
    r4 = 36;
    r3 = (this_r3 + 28);
    r3 = cAram2Mem::GetSize(long) const(); // [0x800D0D9C]
    r3 = (ret_800AB270 + ret_800AB280);
    r3 = memAlloc((ret_800AB270 + ret_800AB280)); // [0x8009CB2C]
    *(uint32_t*)(this_r3 + 0x34) = ret_800AB288;
    if (ret_800AB288 == 0) goto label_800AB42C;
    r5 = ret_800AB288;
    r4 = 35;
    r3 = (this_r3 + 28);
    r3 = cAram2Mem::LoadData((this_r3 + 28), 35, ret_800AB288); // [0x800D0C38]
    r30 = ret_800AB2A4;
    r4 = 36;
    r3 = (this_r3 + 28);
    r5 = ret_800AB2A4;
    r3 = cAram2Mem::LoadData((this_r3 + 28), 36, ret_800AB2A4); // [0x800D0C38]
    r31 = ret_800AB2B8;
    if (ret_800AB2A4 == 0) goto label_800AB42C;
    if (ret_800AB2B8 == 0) goto label_800AB42C;
    r3 = *(uint32_t*)(this_r3 + 0x28);
    r4 = ret_800AB2A4;
    r5 = *(uint32_t*)(this_r3 + 0x34);
    r3 = cIdMain::SetTexPrim(*(uint32_t*)(this_r3 + 0x28), ret_800AB2A4, *(uint32_t*)(this_r3 + 0x34)); // [0x8007245C]
    if (ret_800AB2DC == 0) goto label_800AB42C;
    r3 = (this_r3 + 28);
    r3 = cAram2Mem::GetMemAddr(void) const(); // [0x800D0E20]
    r27 = ret_800AB2EC;
    goto label_800AB2FC;
label_800AB2F8:;
    r27 = SDA1::cAram2Mem::m_memAddr;
label_800AB2FC:;
    r28 = this_r3 + (28);
    r4 = 31;
    r5 = SDA1::cAram2Mem::m_memAddr;
    r3 = (this_r3 + 28);
    r3 = cAram2Mem::LoadData((this_r3 + 28), 31, SDA1::cAram2Mem::m_memAddr); // [0x800D0C38]
    r30 = ret_800AB30C;
    r4 = 32;
    r5 = 0;
    r3 = (this_r3 + 28);
    r3 = cAram2Mem::LoadData((this_r3 + 28), 32, 0); // [0x800D0C38]
    *(uint32_t*)(this_r3 + 0x38) = ret_800AB320;
    r4 = 34;
    r3 = (this_r3 + 28);
    r5 = 0;
    r3 = cAram2Mem::LoadData((this_r3 + 28), 34, 0); // [0x800D0C38]
    r31 = ret_800AB334;
    if (ret_800AB30C == 0) goto label_800AB42C;
    r0 = *(uint32_t*)(this_r3 + 0x38);
    if (*(uint32_t*)(this_r3 + 0x38) == 0) goto label_800AB42C;
    if (ret_800AB334 == 0) goto label_800AB42C;
    r3 = *(uint32_t*)(this_r3 + 0x2C);
    r4 = ret_800AB30C;
    r5 = SDA1::cAram2Mem::m_memAddr;
    r3 = cIdMain::SetTexPrim(*(uint32_t*)(this_r3 + 0x2C), ret_800AB30C, SDA1::cAram2Mem::m_memAddr); // [0x8007245C]
    if (ret_800AB364 == 0) goto label_800AB42C;
    r4 = 33;
    r5 = 0;
    r3 = (this_r3 + 28);
    r30 = ret_800AB334;
    r3 = cAram2Mem::LoadData((this_r3 + 28), 33, 0); // [0x800D0C38]
    r3 = *(uint32_t*)(this_r3 + 0x30);
    r4 = ret_800AB334;
    r5 = SDA1::cAram2Mem::m_memAddr;
    r3 = cIdMain::SetTexPrim(*(uint32_t*)(this_r3 + 0x30), ret_800AB334, SDA1::cAram2Mem::m_memAddr); // [0x8007245C]
    if (ret_800AB390 == 0) goto label_800AB42C;
    r31 = *(uint32_t*)(this_r3 + 0x30);
    r30 = 0;
    r28 = this_r3 + (16);
    goto label_800AB3C0;
label_800AB3AC:;
    r4 = 0;
    r3 = *(uint32_t*)(this_r3 + 0x30);
    r5 = 0;
    r30 = 0 + (1);
    r3 = cIdMain::SetSwitch(*(uint32_t*)(this_r3 + 0x30), 0, 0); // [0x80072710]
label_800AB3C0:;
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14);
    if ((0 + 1) < *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14)) goto label_800AB3AC;
    r11 = SDA1::pG;
    r8 = 255;
    r7 = 128;
    r10 = 16;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A91);
    *(uint16_t*)(this_r3 + 0x10) = 255;
    r30 = 0;
    *(uint8_t*)(this_r3 + 0x3D) = *(uint8_t*)(SDA1::pG + 0x6A91);
    r9 = &cMes;
    *(uint16_t*)((this_r3 + 16) + 0x6) = 16;
    *(uint16_t*)((this_r3 + 16) + 0x4) = 255;
    r3 = this_r3;
    *(uint16_t*)((this_r3 + 16) + 0x2) = 128;
    *(uint32_t*)(this_r3 + 0xC) = 0;
    r0 = *(uint32_t*)(this_r3 + 0x38);
    *(uint32_t*)((&cMes + 0x00010000u) - 0x6374) = *(uint32_t*)(this_r3 + 0x38);
    r3 = cOptionCtrl::optionSndMode(this_r3); // [0x800ACA34]
    r0 = 1;
    *(uint32_t*)(this_r3 + 0x4) = 0;
    *(uint8_t*)(this_r3 + 0x0) = 1;
    *(uint8_t*)(this_r3 + 0x1) = 0;
    *(uint8_t*)(this_r3 + 0x2) = 0;
label_800AB42C:;
    r0 = stack_0x24;
    return; // r3 = ret_800AB414
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::OptionOpen(void)
// Unit: option.obj | Address: 0x800AB440 | Size: 0x110 bytes
// ============================================================================
/* [0x800AB440] */ void cOptionCtrl::OptionOpen(cOptionCtrl* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r31 = this_r3;
    r9 = *(uint8_t*)(this_r3 + 0x1);
    r9 = *(uint8_t*)(this_r3 + 0x1) + (1);
    *(uint8_t*)(this_r3 + 0x1) = (*(uint8_t*)(this_r3 + 0x1) + 1);
    if (r0 <= 0x7u) goto label_800AB53C;
    r5 = 20;
    r6 = 360;
    r7 = 0x38200004u;
    r8 = 0;
    r9 = 0xDFDFBFFFu;
    r3 = &cMes;
    r4 = 0;
    r3 = CMesCtrl::MesSet(&cMes, 0, 20, 360, 0x38200004u, 0, 0xDFDFBFFFu); // [0x8009F1D8]
    r30 = &cMes;
    r29 = &cMes + (4);
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r11 = 0;
    r0 = 2;
    *(uint8_t*)(this_r3 + 0x2) = 0;
    r5 = 20;
    *(uint8_t*)(this_r3 + 0x0) = 2;
    r6 = 360;
    r7 = 0x38200004u;
    r8 = 0;
    r9 = 0xDFDFBFFFu;
    *(uint8_t*)(this_r3 + 0x1) = 0;
    r3 = &cMes;
    r4 = 0;
    r3 = CMesCtrl::MesSet(&cMes, 0, 20, 360, 0x38200004u, 0, 0xDFDFBFFFu); // [0x8009F1D8]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
label_800AB53C:;
    r0 = stack_0x1C;
    return; // r3 = ret_800AB538
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::OptionMenu(void)
// Unit: option.obj | Address: 0x800AB550 | Size: 0x78 bytes
// ============================================================================
/* [0x800AB550] */ void cOptionCtrl::OptionMenu(cOptionCtrl* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r0 = *(uint8_t*)(this_r3 + 0x1);
    if (*(uint8_t*)(this_r3 + 0x1) == 2) goto label_800AB5A4;
    if (*(uint8_t*)(this_r3 + 0x1) > 2) goto label_800AB580;
    if (*(uint8_t*)(this_r3 + 0x1) == 0) goto label_800AB594;
    if (*(uint8_t*)(this_r3 + 0x1) == 1) goto label_800AB59C;
    goto label_800AB5B8;
label_800AB580:;
    if (*(uint8_t*)(this_r3 + 0x1) == 3) goto label_800AB5AC;
    if (*(uint8_t*)(this_r3 + 0x1) == 4) goto label_800AB5B4;
    goto label_800AB5B8;
label_800AB594:;
    r3 = cOptionCtrl::optionMenu(this_r3); // [0x800AB7B4]
    goto label_800AB5B8;
label_800AB59C:;
    r3 = cOptionCtrl::optionConfig(ret_800AB594); // [0x800ABB38]
    goto label_800AB5B8;
label_800AB5A4:;
    r3 = cOptionCtrl::optionReset(ret_800AB59C); // [0x800ABE24]
    goto label_800AB5B8;
label_800AB5AC:;
    r3 = cOptionCtrl::optionFade(ret_800AB5A4); // [0x800ABFA8]
    goto label_800AB5B8;
label_800AB5B4:;
    r3 = cOptionCtrl::optionQuit(ret_800AB5AC); // [0x800ABFD4]
label_800AB5B8:;
    r0 = stack_0x0C;
    return; // r3 = ret_800AB5B4
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::OptionClose(void)
// Unit: option.obj | Address: 0x800AB5C8 | Size: 0x12C bytes
// ============================================================================
/* [0x800AB5C8] */ void cOptionCtrl::OptionClose(cOptionCtrl* this_r3) {
    // Stack frame allocated: 32 bytes
    stack_0x1C = r31;
    stack_0x24 = r0;
    r31 = this_r3;
    r5 = -1;
    r3 = *(uint32_t*)(this_r3 + 0x2C);
    r4 = 0;
    r3 = cIdMain::PrimReverseSet(*(uint32_t*)(this_r3 + 0x2C), 0, -1); // [0x80072570]
    f0 = *(float*)0x8016C7A8;
    r6 = &stack_0x08;
    r3 = *(uint32_t*)(this_r3 + 0x2C);
    r5 = 0;
    f13 = *(float*)0x8016C7AC;
    r12 = &stack_0x08;
    stack_0x08 = *(float*)0x8016C7A8;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x8016C7A8;
    *(float*)(&stack_0x08 + 0xC) = *(float*)0x8016C7AC;
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x8016C7A8;
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14);
    if (0 >= *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14)) goto label_800AB66C;
    r4 = 0;
label_800AB62C:;
    r11 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8);
    r5 = 0 + (1);
    r10 = *(uint32_t*)(&stack_0x08 + 0x0);
    r0 = *(uint32_t*)(&stack_0x08 + 0xC);
    r11 = (0 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8));
    r8 = *(uint32_t*)(&stack_0x08 + 0x4);
    r9 = (0 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8)) + (96);
    r7 = *(uint32_t*)(&stack_0x08 + 0x8);
    r4 = 0 + (156);
    *(uint32_t*)((0 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8)) + 0x60) = *(uint32_t*)(&stack_0x08 + 0x0);
    *(uint32_t*)(((0 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8)) + 96) + 0xC) = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)(((0 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8)) + 96) + 0x4) = *(uint32_t*)(&stack_0x08 + 0x4);
    *(uint32_t*)(((0 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8)) + 96) + 0x8) = *(uint32_t*)(&stack_0x08 + 0x8);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14);
    if ((0 + 1) < *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14)) goto label_800AB62C;
label_800AB66C:;
    r11 = *(uint32_t*)(this_r3 + 0x2C);
    f0 = *(float*)0x8016C7A8;
    r6 = 0;
    *(float*)(&stack_0x08 + 0xC) = *(float*)0x8016C7A8;
    stack_0x08 = *(float*)0x8016C7A8;
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x8016C7A8;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x8016C7A8;
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14) <= 0) goto label_800AB6C0;
    r11 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8);
    r8 = stack_0x08;
    r7 = *(uint32_t*)(&stack_0x08 + 0xC);
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + (96);
    r0 = *(uint32_t*)(&stack_0x08 + 0x4);
    r10 = *(uint32_t*)(&stack_0x08 + 0x8);
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + 0x60) = stack_0x08;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + 96) + 0xC) = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + 96) + 0x4) = *(uint32_t*)(&stack_0x08 + 0x4);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + 96) + 0x8) = *(uint32_t*)(&stack_0x08 + 0x8);
label_800AB6C0:;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r0 = 4;
    *(uint8_t*)(this_r3 + 0x0) = 4;
    *(uint8_t*)(this_r3 + 0x1) = 0;
    if (*(uint32_t*)(this_r3 + 0x40) == 0) goto label_800AB6E0;
    r0 = 1;
    *(uint32_t*)(*(uint32_t*)(this_r3 + 0x40) + 0x0) = 1;
label_800AB6E0:;
    r0 = stack_0x24;
    r31 = stack_0x1C;
    return; // r3 = *(uint32_t*)(this_r3 + 0x2C)
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::OptionQuit(void)
// Unit: option.obj | Address: 0x800AB6F4 | Size: 0xC0 bytes
// ============================================================================
/* [0x800AB6F4] */ void cOptionCtrl::OptionQuit(cOptionCtrl* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r31 = this_r3;
    r9 = *(uint8_t*)(this_r3 + 0x1);
    r9 = *(uint8_t*)(this_r3 + 0x1) + (1);
    *(uint8_t*)(this_r3 + 0x1) = (*(uint8_t*)(this_r3 + 0x1) + 1);
    if (r0 <= 0x7u) goto label_800AB7A0;
    r30 = this_r3 + (28);
    r4 = 33;
    r3 = (this_r3 + 28);
    r3 = cAram2Mem::GetSize(long) const(); // [0x800D0D9C]
    r0 = SDA1::cAram2Mem::m_memAddr;
    r4 = 34;
    r0 = (SDA1::cAram2Mem::m_memAddr - ret_800AB72C);
    SDA1::cAram2Mem::m_memAddr = (SDA1::cAram2Mem::m_memAddr - ret_800AB72C);
    r3 = (this_r3 + 28);
    r3 = cAram2Mem::GetSize(long) const(); // [0x800D0D9C]
    r0 = SDA1::cAram2Mem::m_memAddr;
    r4 = 32;
    r0 = (SDA1::cAram2Mem::m_memAddr - ret_800AB744);
    SDA1::cAram2Mem::m_memAddr = (SDA1::cAram2Mem::m_memAddr - ret_800AB744);
    r3 = (this_r3 + 28);
    r3 = cAram2Mem::GetSize(long) const(); // [0x800D0D9C]
    r0 = SDA1::cAram2Mem::m_memAddr;
    r4 = 31;
    r0 = (SDA1::cAram2Mem::m_memAddr - ret_800AB75C);
    SDA1::cAram2Mem::m_memAddr = (SDA1::cAram2Mem::m_memAddr - ret_800AB75C);
    r3 = (this_r3 + 28);
    r3 = cAram2Mem::GetSize(long) const(); // [0x800D0D9C]
    r0 = SDA1::cAram2Mem::m_memAddr;
    r9 = 1;
    r11 = *(uint32_t*)(this_r3 + 0x34);
    r0 = (SDA1::cAram2Mem::m_memAddr - ret_800AB774);
    SDA1::cAram2Mem::m_memAddr = (SDA1::cAram2Mem::m_memAddr - ret_800AB774);
    *(uint32_t*)(this_r3 + 0x4) = 1;
    if (*(uint32_t*)(this_r3 + 0x34) == 0) goto label_800AB7A0;
    r3 = *(uint32_t*)(this_r3 + 0x34);
    r3 = Mem_free(*(uint32_t*)(this_r3 + 0x34)); // [0x8009CC68]
label_800AB7A0:;
    r0 = stack_0x14;
    return; // r3 = ret_800AB79C
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionMenu(void)
// Unit: option.obj | Address: 0x800AB7B4 | Size: 0x384 bytes
// ============================================================================
/* [0x800AB7B4] */ void cOptionCtrl::optionMenu(cOptionCtrl* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = &Joy;
    r0 = 0x00080008u;
    r11 = *(uint32_t*)(&Joy + 0x1C);
    r31 = this_r3;
    if (r0 == 0) goto label_800AB870;
    r9 = *(uint32_t*)(this_r3 + 0xC);
    r9 = *(uint32_t*)(this_r3 + 0xC) + (-1);
    *(uint32_t*)(this_r3 + 0xC) = (*(uint32_t*)(this_r3 + 0xC) + -1);
    if ((*(uint32_t*)(this_r3 + 0xC) + -1) >= 0) goto label_800AB800;
    r0 = 5;
    *(uint32_t*)(this_r3 + 0xC) = 5;
label_800AB800:;
    r4 = *(uint32_t*)(this_r3 + 0xC);
    r5 = 20;
    r6 = 360;
    r7 = 0x38200004u;
    r8 = 0;
    r9 = 0xDFDFBFFFu;
    r3 = &cMes;
    r3 = CMesCtrl::MesSet(&cMes, *(uint32_t*)(this_r3 + 0xC), 20, 360, 0x38200004u, 0, 0xDFDFBFFFu); // [0x8009F1D8]
    r30 = &cMes;
    r4 = 0;
    r30 = &cMes + (4);
    r4 = 0 | 0xFFFFu;
    r3 = (&cMes + 4);
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r3 = 0;
    r4 = 0;
    goto label_800ABA84;
label_800AB870:;
    r0 = 0x00040004u;
    if ((*(uint32_t*)(this_r3 + 0xC) + -1) == 0) goto label_800AB908;
    r9 = *(uint32_t*)(this_r3 + 0xC);
    r9 = *(uint32_t*)(this_r3 + 0xC) + (1);
    *(uint32_t*)(this_r3 + 0xC) = (*(uint32_t*)(this_r3 + 0xC) + 1);
    if ((*(uint32_t*)(this_r3 + 0xC) + 1) <= 5) goto label_800AB898;
    *(uint32_t*)(this_r3 + 0xC) = r10;
label_800AB898:;
    r4 = *(uint32_t*)(this_r3 + 0xC);
    r5 = 20;
    r6 = 360;
    r7 = 0x38200004u;
    r8 = 0;
    r9 = 0xDFDFBFFFu;
    r3 = &cMes;
    r3 = CMesCtrl::MesSet(&cMes, *(uint32_t*)(this_r3 + 0xC), 20, 360, 0x38200004u, 0, 0xDFDFBFFFu); // [0x8009F1D8]
    r30 = &cMes;
    r4 = 0;
    r30 = &cMes + (4);
    r4 = 0 | 0xFFFFu;
    r3 = (&cMes + 4);
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r3 = 0;
    r4 = 0;
    goto label_800ABA84;
label_800AB908:;
    r0 = 0x00010001u;
    if ((*(uint32_t*)(this_r3 + 0xC) + 1) == 5) goto label_800AB970;
    r0 = *(uint32_t*)(this_r3 + 0xC);
    if (*(uint32_t*)(this_r3 + 0xC) == 1) goto label_800AB950;
    if (*(uint32_t*)(this_r3 + 0xC) > 1) goto label_800AB934;
    if (*(uint32_t*)(this_r3 + 0xC) == 0) goto label_800AB940;
    goto label_800ABB14;
label_800AB934:;
    if (*(uint32_t*)(this_r3 + 0xC) == 2) goto label_800AB960;
    goto label_800ABB14;
label_800AB940:;
    r3 = this_r3;
    r4 = -1;
    r3 = cOptionCtrl::optionSound(this_r3, -1); // [0x800AC014]
    goto label_800ABB14;
label_800AB950:;
    r3 = this_r3;
    r4 = -1;
    r3 = cOptionCtrl::optionBGM(this_r3, -1); // [0x800AC17C]
    goto label_800ABB14;
label_800AB960:;
    r3 = this_r3;
    r4 = -1;
    r3 = cOptionCtrl::optionSE(this_r3, -1); // [0x800AC26C]
    goto label_800ABB14;
label_800AB970:;
    r0 = 0x00020002u;
    if (*(uint32_t*)(this_r3 + 0xC) == 2) goto label_800AB9D8;
    r0 = *(uint32_t*)(this_r3 + 0xC);
    if (*(uint32_t*)(this_r3 + 0xC) == 1) goto label_800AB9B8;
    if (*(uint32_t*)(this_r3 + 0xC) > 1) goto label_800AB99C;
    if (*(uint32_t*)(this_r3 + 0xC) == 0) goto label_800AB9A8;
    goto label_800ABB14;
label_800AB99C:;
    if (*(uint32_t*)(this_r3 + 0xC) == 2) goto label_800AB9C8;
    goto label_800ABB14;
label_800AB9A8:;
    r3 = this_r3;
    r4 = 1;
    r3 = cOptionCtrl::optionSound(this_r3, 1); // [0x800AC014]
    goto label_800ABB14;
label_800AB9B8:;
    r3 = this_r3;
    r4 = 1;
    r3 = cOptionCtrl::optionBGM(this_r3, 1); // [0x800AC17C]
    goto label_800ABB14;
label_800AB9C8:;
    r3 = this_r3;
    r4 = 1;
    r3 = cOptionCtrl::optionSE(this_r3, 1); // [0x800AC26C]
    goto label_800ABB14;
label_800AB9D8:;
    r9 = *(uint32_t*)(0xDFDFBFFFu + 0x14);
    if (*(uint32_t*)(this_r3 + 0xC) == 2) goto label_800ABA48;
    r0 = *(uint32_t*)(this_r3 + 0xC);
    if (*(uint32_t*)(this_r3 + 0xC) == 4) goto label_800ABA1C;
    if (*(uint32_t*)(this_r3 + 0xC) > 4) goto label_800ABA00;
    if (*(uint32_t*)(this_r3 + 0xC) == 3) goto label_800ABA0C;
    goto label_800ABB14;
label_800ABA00:;
    if (*(uint32_t*)(this_r3 + 0xC) == 5) goto label_800ABA28;
    goto label_800ABB14;
label_800ABA0C:;
    r3 = this_r3;
    r4 = 1;
    r3 = cOptionCtrl::optionKeyConf(this_r3, 1); // [0x800AC52C]
    goto label_800ABB24;
label_800ABA1C:;
    r0 = 2;
    *(uint8_t*)(this_r3 + 0x1) = 2;
    goto label_800ABB14;
label_800ABA28:;
    r0 = 4;
    r9 = *(uint32_t*)(this_r3 + 0x8);
    *(uint8_t*)(this_r3 + 0x1) = 4;
    if (*(uint32_t*)(this_r3 + 0xC) == 5) goto label_800ABA7C;
    r3 = 0;
    r4 = 2;
    goto label_800ABA84;
label_800ABA48:;
    if (*(uint32_t*)(this_r3 + 0xC) == 5) goto label_800ABB14;
    r0 = *(uint32_t*)(this_r3 + 0xC);
    if (*(uint32_t*)(this_r3 + 0xC) != 5) goto label_800ABA94;
    r9 = *(uint32_t*)(this_r3 + 0x8);
    r0 = 4;
    *(uint8_t*)(this_r3 + 0x1) = 4;
    if (*(uint32_t*)(this_r3 + 0xC) == 5) goto label_800ABA7C;
    r3 = 0;
    r4 = 2;
    goto label_800ABA84;
label_800ABA7C:;
    r3 = 0;
    r4 = 4;
label_800ABA84:;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 4, 0, 0); // [0x800CB7DC]
    goto label_800ABB14;
label_800ABA94:;
    r5 = 20;
    r6 = 360;
    r7 = 0x38200004u;
    r8 = 0;
    r9 = 0xDFDFBFFFu;
    r3 = &cMes;
    r4 = 5;
    r3 = CMesCtrl::MesSet(&cMes, 5, 20, 360, 0x38200004u, 0, 0xDFDFBFFFu); // [0x8009F1D8]
    r30 = &cMes;
    r4 = 0;
    r30 = &cMes + (4);
    r4 = 0 | 0xFFFFu;
    r3 = (&cMes + 4);
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r0 = 5;
    r3 = 0;
    *(uint32_t*)(this_r3 + 0xC) = 5;
    r4 = 2;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 2, 0, 0); // [0x800CB7DC]
label_800ABB14:;
    r0 = 0;
    r3 = this_r3;
    *(uint8_t*)(this_r3 + 0x2) = 0;
    r3 = cOptionCtrl::optionCursol(this_r3); // [0x800AC730]
label_800ABB24:;
    r0 = stack_0x14;
    return; // r3 = ret_800ABB20
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionConfig(void)
// Unit: option.obj | Address: 0x800ABB38 | Size: 0x2EC bytes
// ============================================================================
/* [0x800ABB38] */ void cOptionCtrl::optionConfig(cOptionCtrl* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = &Joy;
    r0 = 0x00080008u;
    r11 = *(uint32_t*)(&Joy + 0x1C);
    r31 = this_r3;
    if (r0 == 0) goto label_800ABBC8;
    r9 = *(uint32_t*)(this_r3 + 0xC);
    r9 = *(uint32_t*)(this_r3 + 0xC) + (-1);
    *(uint32_t*)(this_r3 + 0xC) = (*(uint32_t*)(this_r3 + 0xC) + -1);
    if ((*(uint32_t*)(this_r3 + 0xC) + -1) >= 0) goto label_800ABB84;
    r0 = 2;
    *(uint32_t*)(this_r3 + 0xC) = 2;
label_800ABB84:;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r3 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
    r4 = *(uint32_t*)(this_r3 + 0xC);
    r5 = 20;
    r6 = 360;
    r7 = 0x38200004u;
    r8 = 0;
    r9 = 0xDFDFBFFFu;
    r3 = &cMes;
    r4 = *(uint32_t*)(this_r3 + 0xC) + (7);
    goto label_800ABD3C;
label_800ABBC8:;
    r0 = 0x00040004u;
    if ((*(uint32_t*)(this_r3 + 0xC) + -1) == 0) goto label_800ABC34;
    r9 = *(uint32_t*)(this_r3 + 0xC);
    r9 = *(uint32_t*)(this_r3 + 0xC) + (1);
    *(uint32_t*)(this_r3 + 0xC) = (*(uint32_t*)(this_r3 + 0xC) + 1);
    if ((*(uint32_t*)(this_r3 + 0xC) + 1) <= 2) goto label_800ABBF0;
    *(uint32_t*)(this_r3 + 0xC) = r10;
label_800ABBF0:;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r3 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
    r4 = *(uint32_t*)(this_r3 + 0xC);
    r5 = 20;
    r6 = 360;
    r7 = 0x38200004u;
    r8 = 0;
    r9 = 0xDFDFBFFFu;
    r3 = &cMes;
    r4 = *(uint32_t*)(this_r3 + 0xC) + (7);
    goto label_800ABD3C;
label_800ABC34:;
    r0 = 0x00010001u;
    if ((*(uint32_t*)(this_r3 + 0xC) + 1) == 2) goto label_800ABC7C;
    r0 = *(uint32_t*)(this_r3 + 0xC);
    if (*(uint32_t*)(this_r3 + 0xC) == 0) goto label_800ABC5C;
    if (*(uint32_t*)(this_r3 + 0xC) == 1) goto label_800ABC6C;
    goto label_800ABE08;
label_800ABC5C:;
    r3 = this_r3;
    r4 = -1;
    r3 = cOptionCtrl::optionConfChange(this_r3, -1); // [0x800AC35C]
    goto label_800ABE08;
label_800ABC6C:;
    r3 = this_r3;
    r4 = 0;
    r3 = cOptionCtrl::optionRamble(this_r3, 0); // [0x800AC440]
    goto label_800ABE08;
label_800ABC7C:;
    r0 = 0x00020002u;
    if (*(uint32_t*)(this_r3 + 0xC) == 1) goto label_800ABCC4;
    r0 = *(uint32_t*)(this_r3 + 0xC);
    if (*(uint32_t*)(this_r3 + 0xC) == 0) goto label_800ABCA4;
    if (*(uint32_t*)(this_r3 + 0xC) == 1) goto label_800ABCB4;
    goto label_800ABE08;
label_800ABCA4:;
    r3 = this_r3;
    r4 = 1;
    r3 = cOptionCtrl::optionConfChange(this_r3, 1); // [0x800AC35C]
    goto label_800ABE08;
label_800ABCB4:;
    r3 = this_r3;
    r4 = 1;
    r3 = cOptionCtrl::optionRamble(this_r3, 1); // [0x800AC440]
    goto label_800ABE08;
label_800ABCC4:;
    r0 = *(uint32_t*)(this_r3 + 0xC);
    if (*(uint32_t*)(this_r3 + 0xC) != 2) goto label_800ABD7C;
    r9 = *(uint32_t*)(0xDFDFBFFFu + 0x14);
    if (*(uint32_t*)(this_r3 + 0xC) == 2) goto label_800ABCEC;
    r5 = 0;
    r6 = 0;
    r4 = 1;
    goto label_800ABD00;
label_800ABCEC:;
    if (*(uint32_t*)(this_r3 + 0xC) == 2) goto label_800ABE08;
    r5 = 0;
    r6 = 0;
    r4 = 2;
label_800ABD00:;
    r3 = 0;
    r3 = SndSeCall(0, 2, 0, 0); // [0x800CB7DC]
    r3 = this_r3;
    r4 = 0;
    r3 = cOptionCtrl::optionKeyConf(this_r3, 0); // [0x800AC52C]
    r5 = 20;
    r6 = 360;
    r7 = 0x38200004u;
    r8 = 0;
    r9 = 0xDFDFBFFFu;
    r3 = &cMes;
    r4 = 3;
label_800ABD3C:;
    r3 = CMesCtrl::MesSet(&cMes, 3, 20, 360, 0x38200004u, 0, 0xDFDFBFFFu); // [0x8009F1D8]
    r30 = &cMes;
    r4 = 0;
    r30 = &cMes + (4);
    r4 = 0 | 0xFFFFu;
    r3 = (&cMes + 4);
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    goto label_800ABE08;
label_800ABD7C:;
    r0 = *(uint32_t*)(0xDFDFBFFFu + 0x14);
    if (*(uint32_t*)(this_r3 + 0xC) == 2) goto label_800ABE08;
    r0 = 2;
    r4 = 2;
    *(uint32_t*)(this_r3 + 0xC) = 2;
    r5 = 0;
    r6 = 0;
    r3 = 0;
    r3 = SndSeCall(0, 2, 0, 0); // [0x800CB7DC]
    r5 = 20;
    r6 = 360;
    r7 = 0x38200004u;
    r8 = 0;
    r9 = 0xDFDFBFFFu;
    r3 = &cMes;
    r4 = 9;
    r3 = CMesCtrl::MesSet(&cMes, 9, 20, 360, 0x38200004u, 0, 0xDFDFBFFFu); // [0x8009F1D8]
    r30 = &cMes;
    r4 = 0;
    r30 = &cMes + (4);
    r4 = 0 | 0xFFFFu;
    r3 = (&cMes + 4);
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
label_800ABE08:;
    r3 = this_r3;
    r3 = cOptionCtrl::optionCursolConf(this_r3); // [0x800AC86C]
    r0 = stack_0x14;
    return; // r3 = ret_800ABE0C
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionReset(void)
// Unit: option.obj | Address: 0x800ABE24 | Size: 0x184 bytes
// ============================================================================
/* [0x800ABE24] */ void cOptionCtrl::optionReset(cOptionCtrl* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r31 = this_r3;
    r0 = *(uint8_t*)(this_r3 + 0x2);
    if (*(uint8_t*)(this_r3 + 0x2) == 0) goto label_800ABE50;
    if (*(uint8_t*)(this_r3 + 0x2) == 1) goto label_800ABED8;
    goto label_800ABF94;
label_800ABE50:;
    r4 = 1;
    r5 = 0;
    r6 = 0;
    r3 = 0;
    r3 = SndSeCall(0, 1, 0, 0); // [0x800CB7DC]
    r9 = 0xDFDFBFFFu;
    r5 = 20;
    r6 = 360;
    r7 = 0x38E00004u;
    r8 = 0;
    r3 = &cMes;
    r4 = 6;
    r3 = CMesCtrl::MesSet(&cMes, 6, 20, 360, 0x38E00004u, 0, 0xDFDFBFFFu); // [0x8009F1D8]
    r30 = &cMes;
    r4 = 0;
    r30 = &cMes + (4);
    r4 = 0 | 0xFFFFu;
    r3 = (&cMes + 4);
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r9 = *(uint8_t*)(this_r3 + 0x2);
    r9 = *(uint8_t*)(this_r3 + 0x2) + (1);
    *(uint8_t*)(this_r3 + 0x2) = (*(uint8_t*)(this_r3 + 0x2) + 1);
    goto label_800ABF94;
label_800ABED8:;
    r29 = &cMes;
    r30 = &cMes + (4);
    r0 = *(uint8_t*)((&cMes + 4) + 0x1E7D);
    if (*(uint8_t*)((&cMes + 4) + 0x1E7D) != 1) goto label_800ABF08;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    *(uint32_t*)(SDA1::pG + 0x124) = *(uint32_t*)(SDA1::pG + 0x124);
    goto label_800ABF94;
label_800ABF08:;
    if (*(uint32_t*)(SDA1::pG + 0x124) != 2) goto label_800ABF94;
    r0 = *(uint32_t*)0x8019D690;
    if (*(uint32_t*)(SDA1::pG + 0x124) == 2) goto label_800ABF34;
    r3 = 0;
    r4 = 1;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 1, 0, 0); // [0x800CB7DC]
label_800ABF34:;
    r5 = 20;
    r6 = 360;
    r7 = 0x38200004u;
    r8 = 0;
    r9 = 0xDFDFBFFFu;
    r3 = &cMes;
    r4 = 4;
    r3 = CMesCtrl::MesSet(&cMes, 4, 20, 360, 0x38200004u, 0, 0xDFDFBFFFu); // [0x8009F1D8]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r4 = 0;
    r3 = (&cMes + 4);
    r4 = 0 | 0xFFFFu;
    r3 = CMesWk::SetJump((&cMes + 4), 0); // [0x8009FD24]
    r0 = 0;
    *(uint8_t*)(this_r3 + 0x1) = 0;
label_800ABF94:;
    r0 = stack_0x1C;
    return; // r3 = ret_800ABF88
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionFade(void)
// Unit: option.obj | Address: 0x800ABFA8 | Size: 0x2C bytes
// ============================================================================
/* [0x800ABFA8] */ void cOptionCtrl::optionFade(cOptionCtrl* this_r3) {
    r9 = *(uint8_t*)(this_r3 + 0x3);
    r9 = *(uint8_t*)(this_r3 + 0x3) + (1);
    *(uint8_t*)(this_r3 + 0x3) = (*(uint8_t*)(this_r3 + 0x3) + 1);
    r9 = *(uint8_t*)(this_r3 + 0x2);
    r0 = 0;
    *(uint8_t*)(this_r3 + 0x2) = 0;
    *(uint8_t*)(this_r3 + 0x1) = *(uint8_t*)(this_r3 + 0x2);
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionQuit(void)
// Unit: option.obj | Address: 0x800ABFD4 | Size: 0x40 bytes
// ============================================================================
/* [0x800ABFD4] */ void cOptionCtrl::optionQuit(cOptionCtrl* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r30 = this_r3;
    r4 = 0;
    r3 = &cMes;
    r3 = CMesCtrl::MesClear(&cMes, 0); // [0x8009F208]
    r0 = 3;
    *(uint8_t*)(this_r3 + 0x0) = 3;
    r0 = stack_0x14;
    return; // r3 = ret_800ABFF4
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionSound(long)
// Unit: option.obj | Address: 0x800AC014 | Size: 0x168 bytes
// ============================================================================
/* [0x800AC014] */ void cOptionCtrl::optionSound(cOptionCtrl* this_r3, long arg0_r4) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r31 = this_r3;
    if (arg0_r4 >= 0) goto label_800AC0A8;
    r9 = SDA1::pG;
    r11 = *(uint8_t*)(SDA1::pG + 0x6A90);
    if (*(uint8_t*)(SDA1::pG + 0x6A90) == 0) goto label_800AC06C;
    r0 = 0;
    r10 = 1;
    *(uint8_t*)(SDA1::pG + 0x6A90) = 0;
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x10E) = 1;
    r11 = SDA1::pG;
    r4 = *(uint8_t*)(SDA1::pG + 0x6A90);
    r3 = *(uint8_t*)(SDA1::pG + 0x10E);
    r3 = SndModeSet(*(uint8_t*)(SDA1::pG + 0x10E), *(uint8_t*)(SDA1::pG + 0x6A90)); // [0x800CB534]
    r0 = 24;
    goto label_800AC118;
label_800AC06C:;
    r0 = *(uint8_t*)(SDA1::pG + 0x10E);
    if (*(uint8_t*)(SDA1::pG + 0x10E) != 1) goto label_800AC09C;
    *(uint8_t*)(SDA1::pG + 0x6A90) = SDA1::pG;
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x10E) = SDA1::pG;
    r11 = SDA1::pG;
    r4 = *(uint8_t*)(SDA1::pG + 0x6A90);
    r3 = *(uint8_t*)(SDA1::pG + 0x10E);
    r3 = SndModeSet(*(uint8_t*)(SDA1::pG + 0x10E), *(uint8_t*)(SDA1::pG + 0x6A90)); // [0x800CB534]
    r0 = 23;
    goto label_800AC118;
label_800AC09C:;
    r3 = 0;
    r4 = 2;
    goto label_800AC124;
label_800AC0A8:;
    r9 = SDA1::pG;
    r11 = *(uint8_t*)(SDA1::pG + 0x10E);
    if (*(uint8_t*)(SDA1::pG + 0x10E) != 0) goto label_800AC0E0;
    *(uint8_t*)(SDA1::pG + 0x6A90) = *(uint8_t*)(SDA1::pG + 0x10E);
    r0 = 1;
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x10E) = 1;
    r11 = SDA1::pG;
    r4 = *(uint8_t*)(SDA1::pG + 0x6A90);
    r3 = *(uint8_t*)(SDA1::pG + 0x10E);
    r3 = SndModeSet(*(uint8_t*)(SDA1::pG + 0x10E), *(uint8_t*)(SDA1::pG + 0x6A90)); // [0x800CB534]
    r0 = 24;
    goto label_800AC118;
label_800AC0E0:;
    if (SDA1::pG != 1) goto label_800AC134;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A90);
    if (*(uint8_t*)(SDA1::pG + 0x6A90) == 2) goto label_800AC134;
    r0 = 2;
    *(uint8_t*)(SDA1::pG + 0x6A90) = 2;
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x10E) = SDA1::pG;
    r11 = SDA1::pG;
    r4 = *(uint8_t*)(SDA1::pG + 0x6A90);
    r3 = *(uint8_t*)(SDA1::pG + 0x10E);
    r3 = SndModeSet(*(uint8_t*)(SDA1::pG + 0x10E), *(uint8_t*)(SDA1::pG + 0x6A90)); // [0x800CB534]
    r0 = 25;
label_800AC118:;
    r3 = 0;
    *(uint8_t*)(this_r3 + 0x3C) = 25;
    r4 = 0;
label_800AC124:;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
    goto label_800AC148;
label_800AC134:;
    r3 = 0;
    r4 = 2;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 2, 0, 0); // [0x800CB7DC]
label_800AC148:;
    r11 = *(uint32_t*)(this_r3 + 0x2C);
    r0 = *(uint8_t*)(this_r3 + 0x3C);
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14) <= 4) goto label_800AC168;
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8);
    *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + 0x2E2) = *(uint8_t*)(this_r3 + 0x3C);
label_800AC168:;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_800AC144
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionBGM(long)
// Unit: option.obj | Address: 0x800AC17C | Size: 0xF0 bytes
// ============================================================================
/* [0x800AC17C] */ void cOptionCtrl::optionBGM(cOptionCtrl* this_r3, long arg0_r4) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = this_r3;
    r31 = arg0_r4;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A8E);
    if (*(uint8_t*)(SDA1::pG + 0x6A8E) != 0) goto label_800AC1AC;
    if (arg0_r4 < 0) goto label_800AC1BC;
label_800AC1AC:;
    if (*(uint8_t*)(SDA1::pG + 0x6A8E) != 100) goto label_800AC1D4;
    if (arg0_r4 <= 0) goto label_800AC1D4;
label_800AC1BC:;
    r3 = 0;
    r4 = 2;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 2, 0, 0); // [0x800CB7DC]
    goto label_800AC258;
label_800AC1D4:;
    r5 = 0;
    r6 = 0;
    r4 = 0;
    r3 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
    r11 = SDA1::pG;
    r4 = 0x51EB851Fu;
    r3 = 1;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A8E);
    r0 = (*(uint8_t*)(SDA1::pG + 0x6A8E) + arg0_r4);
    *(uint8_t*)(SDA1::pG + 0x6A8E) = (*(uint8_t*)(SDA1::pG + 0x6A8E) + arg0_r4);
    r9 = SDA1::pG;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A8E);
    r4 = (0x51EB851Fu - *(uint8_t*)(SDA1::pG + 0x6A8E));
    r3 = Snd_set_system_vol(); // [0x801393B0]
    r3 = 2;
    r3 = Snd_str_reset_vol_type(); // [0x80138A00]
    r3 = 2;
    r3 = Snd_seq_reset_vol_type(); // [0x8013832C]
    r9 = SDA1::pG;
    r4 = 8;
    r3 = *(uint32_t*)(this_r3 + 0x2C);
    r6 = 3;
    r5 = *(uint8_t*)(SDA1::pG + 0x6A8E);
    r7 = 0;
    r8 = 0;
    r3 = cIdMain::SetNumber(*(uint32_t*)(this_r3 + 0x2C), 8, *(uint8_t*)(SDA1::pG + 0x6A8E), 3, 0, 0); // [0x800730E8]
label_800AC258:;
    r0 = stack_0x14;
    return; // r3 = ret_800AC254
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionSE(long)
// Unit: option.obj | Address: 0x800AC26C | Size: 0xF0 bytes
// ============================================================================
/* [0x800AC26C] */ void cOptionCtrl::optionSE(cOptionCtrl* this_r3, long arg0_r4) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = this_r3;
    r31 = arg0_r4;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A8F);
    if (*(uint8_t*)(SDA1::pG + 0x6A8F) != 0) goto label_800AC29C;
    if (arg0_r4 < 0) goto label_800AC2AC;
label_800AC29C:;
    if (*(uint8_t*)(SDA1::pG + 0x6A8F) != 100) goto label_800AC2C4;
    if (arg0_r4 <= 0) goto label_800AC2C4;
label_800AC2AC:;
    r3 = 0;
    r4 = 2;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 2, 0, 0); // [0x800CB7DC]
    goto label_800AC348;
label_800AC2C4:;
    r5 = 0;
    r6 = 0;
    r4 = 0;
    r3 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
    r11 = SDA1::pG;
    r4 = 0x51EB851Fu;
    r3 = 2;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A8F);
    r0 = (*(uint8_t*)(SDA1::pG + 0x6A8F) + arg0_r4);
    *(uint8_t*)(SDA1::pG + 0x6A8F) = (*(uint8_t*)(SDA1::pG + 0x6A8F) + arg0_r4);
    r9 = SDA1::pG;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A8F);
    r4 = (0x51EB851Fu - *(uint8_t*)(SDA1::pG + 0x6A8F));
    r3 = Snd_set_system_vol(); // [0x801393B0]
    r3 = 1;
    r3 = Snd_str_reset_vol_type(); // [0x80138A00]
    r3 = 1;
    r3 = Snd_seq_reset_vol_type(); // [0x8013832C]
    r9 = SDA1::pG;
    r4 = 14;
    r3 = *(uint32_t*)(this_r3 + 0x2C);
    r6 = 3;
    r5 = *(uint8_t*)(SDA1::pG + 0x6A8F);
    r7 = 0;
    r8 = 0;
    r3 = cIdMain::SetNumber(*(uint32_t*)(this_r3 + 0x2C), 14, *(uint8_t*)(SDA1::pG + 0x6A8F), 3, 0, 0); // [0x800730E8]
label_800AC348:;
    r0 = stack_0x14;
    return; // r3 = ret_800AC344
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionConfChange(long)
// Unit: option.obj | Address: 0x800AC35C | Size: 0xE4 bytes
// ============================================================================
/* [0x800AC35C] */ void cOptionCtrl::optionConfChange(cOptionCtrl* this_r3, long arg0_r4) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r31 = this_r3;
    r30 = arg0_r4;
    r0 = *(uint8_t*)(this_r3 + 0x3D);
    if (*(uint8_t*)(this_r3 + 0x3D) != 0) goto label_800AC388;
    if (arg0_r4 == -1) goto label_800AC39C;
label_800AC388:;
    r0 = *(uint8_t*)(this_r3 + 0x3D);
    if (*(uint8_t*)(this_r3 + 0x3D) != 1) goto label_800AC3B4;
    if (arg0_r4 != 1) goto label_800AC3B4;
label_800AC39C:;
    r3 = 0;
    r4 = 2;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 2, 0, 0); // [0x800CB7DC]
    goto label_800AC3C8;
label_800AC3B4:;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
label_800AC3C8:;
    r0 = 1;
    if (arg0_r4 > 0) goto label_800AC3D8;
    r0 = 0;
label_800AC3D8:;
    *(uint8_t*)(this_r3 + 0x3D) = 0;
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x6A91) = 0;
    r10 = *(uint32_t*)(this_r3 + 0x30);
    r9 = *(uint8_t*)(this_r3 + 0x3D);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14);
    r11 = *(uint8_t*)(this_r3 + 0x3D) + (28);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14) <= 2) goto label_800AC408;
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8);
    *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8) + 0x1AA) = (*(uint8_t*)(this_r3 + 0x3D) + 28);
label_800AC408:;
    r11 = *(uint32_t*)(this_r3 + 0x30);
    r9 = *(uint8_t*)(this_r3 + 0x3D);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14);
    r3 = *(uint8_t*)(this_r3 + 0x3D) + (26);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14) <= 6) goto label_800AC42C;
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8);
    *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8) + 0x41A) = (*(uint8_t*)(this_r3 + 0x3D) + 26);
label_800AC42C:;
    r0 = stack_0x14;
    return; // r3 = (*(uint8_t*)(this_r3 + 0x3D) + 26)
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionRamble(bool)
// Unit: option.obj | Address: 0x800AC440 | Size: 0xEC bytes
// ============================================================================
/* [0x800AC440] */ void cOptionCtrl::optionRamble(cOptionCtrl* this_r3, bool arg0_r4) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    stack_0x0C = r12;
    r9 = SDA1::pG;
    r30 = this_r3;
    r31 = arg0_r4;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A92);
    if (*(uint8_t*)(SDA1::pG + 0x6A92) != 1) goto label_800AC478;
    if (arg0_r4 == 1) goto label_800AC490;
label_800AC478:;
    r9 = SDA1::pG;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A92);
    if (*(uint8_t*)(SDA1::pG + 0x6A92) != 0) goto label_800AC4A8;
    if (*(uint8_t*)(SDA1::pG + 0x6A92) != 0) goto label_800AC4A8;
label_800AC490:;
    r3 = 0;
    r4 = 2;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 2, 0, 0); // [0x800CB7DC]
    goto label_800AC4EC;
label_800AC4A8:;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
    if (*(uint8_t*)(SDA1::pG + 0x6A92) == 0) goto label_800AC4E4;
    r9 = SDA1::pG;
    r0 = 1;
    r3 = 10;
    r4 = 200;
    *(uint8_t*)(SDA1::pG + 0x6A92) = 1;
    r5 = 0;
    r6 = 0;
    r3 = VibSet(10, 200, 0, 0); // [0x800AD2F0]
    goto label_800AC4EC;
label_800AC4E4:;
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x6A92) = arg0_r4;
label_800AC4EC:;
    r3 = *(uint32_t*)(this_r3 + 0x30);
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14);
    r11 = *(uint8_t*)(SDA1::pG + 0x6A92);
    r11 = *(uint8_t*)(SDA1::pG + 0x6A92) + (30);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14) <= 10) goto label_800AC510;
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8);
    *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8) + 0x68A) = (*(uint8_t*)(SDA1::pG + 0x6A92) + 30);
label_800AC510:;
    r0 = stack_0x1C;
    r12 = stack_0x0C;
    return; // r3 = *(uint32_t*)(this_r3 + 0x30)
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionKeyConf(bool)
// Unit: option.obj | Address: 0x800AC52C | Size: 0x204 bytes
// ============================================================================
/* [0x800AC52C] */ void cOptionCtrl::optionKeyConf(cOptionCtrl* this_r3, bool arg0_r4) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    f0 = *(float*)0x8016C7B0;
    r9 = &stack_0x08;
    f13 = *(float*)0x8016C7B4;
    r30 = &stack_0x08;
    stack_0x08 = *(float*)0x8016C7B0;
    r31 = this_r3;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x8016C7B0;
    *(float*)(&stack_0x08 + 0xC) = *(float*)0x8016C7B4;
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x8016C7B0;
    if (arg0_r4 == 0) goto label_800AC664;
    r3 = *(uint32_t*)(this_r3 + 0x2C);
    r4 = 1;
    r5 = 19;
    r3 = cIdMain::PrimReverseSet(*(uint32_t*)(this_r3 + 0x2C), 1, 19); // [0x80072570]
    r9 = *(uint32_t*)(this_r3 + 0x2C);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14) <= 17) goto label_800AC5B8;
    r11 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8);
    r8 = stack_0x08;
    r7 = *(uint32_t*)(&stack_0x08 + 0xC);
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + (2748);
    r0 = *(uint32_t*)(&stack_0x08 + 0x4);
    r10 = *(uint32_t*)(&stack_0x08 + 0x8);
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + 0xABC) = stack_0x08;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + 2748) + 0xC) = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + 2748) + 0x4) = *(uint32_t*)(&stack_0x08 + 0x4);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + 2748) + 0x8) = *(uint32_t*)(&stack_0x08 + 0x8);
label_800AC5B8:;
    r3 = *(uint32_t*)(this_r3 + 0x30);
    r4 = 0;
    r5 = -1;
    r3 = cIdMain::PrimSet(*(uint32_t*)(this_r3 + 0x30), 0, -1); // [0x800724E8]
    r10 = *(uint32_t*)(this_r3 + 0x30);
    r9 = *(uint8_t*)(this_r3 + 0x3D);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14);
    r11 = *(uint8_t*)(this_r3 + 0x3D) + (28);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14) <= 2) goto label_800AC5EC;
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8);
    *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8) + 0x1AA) = (*(uint8_t*)(this_r3 + 0x3D) + 28);
label_800AC5EC:;
    r10 = *(uint32_t*)(this_r3 + 0x30);
    r9 = *(uint8_t*)(this_r3 + 0x3D);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14);
    r11 = *(uint8_t*)(this_r3 + 0x3D) + (26);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14) <= 6) goto label_800AC610;
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8);
    *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8) + 0x41A) = (*(uint8_t*)(this_r3 + 0x3D) + 26);
label_800AC610:;
    r9 = SDA1::pG;
    r10 = *(uint32_t*)(this_r3 + 0x30);
    r11 = *(uint8_t*)(SDA1::pG + 0x6A92);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14);
    r11 = *(uint8_t*)(SDA1::pG + 0x6A92) + (30);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14) <= 10) goto label_800AC634;
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8);
    *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8) + 0x68A) = (*(uint8_t*)(SDA1::pG + 0x6A92) + 30);
label_800AC634:;
    r0 = 3;
    r9 = 1;
    r11 = 0;
    *(uint8_t*)(this_r3 + 0x1) = 3;
    *(uint8_t*)(this_r3 + 0x2) = 1;
    r3 = 0;
    *(uint32_t*)(this_r3 + 0xC) = 0;
    r4 = 1;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 1, 0, 0); // [0x800CB7DC]
    goto label_800AC714;
label_800AC664:;
    r3 = *(uint32_t*)(this_r3 + 0x2C);
    r4 = 1;
    r5 = 19;
    r3 = cIdMain::PrimSet(*(uint32_t*)(this_r3 + 0x2C), 1, 19); // [0x800724E8]
    r3 = this_r3;
    r3 = cOptionCtrl::optionSndMode(this_r3); // [0x800ACA34]
    r3 = *(uint32_t*)(this_r3 + 0x30);
    r4 = 0;
    r5 = -1;
    r3 = cIdMain::PrimReverseSet(*(uint32_t*)(this_r3 + 0x30), 0, -1); // [0x80072570]
    r0 = 9;
    r4 = 3;
    r5 = 468;
    r6 = -4;
label_800AC6A0:;
    r9 = *(uint32_t*)(this_r3 + 0x30);
    r11 = 0;
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14);
    if (3 >= *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14)) goto label_800AC6B8;
label_800AC6B8:;
    if (0 == 0) goto label_800AC6EC;
    r11 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8);
    r10 = stack_0x08;
    r8 = *(uint32_t*)(&stack_0x08 + 0x4);
    r11 = (468 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8));
    r7 = *(uint32_t*)(&stack_0x08 + 0x8);
    r9 = (468 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8)) + (96);
    r0 = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)((468 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8)) + 0x60) = stack_0x08;
    *(uint32_t*)(((468 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8)) + 96) + 0xC) = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)(((468 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8)) + 96) + 0x4) = *(uint32_t*)(&stack_0x08 + 0x4);
    *(uint32_t*)(((468 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8)) + 96) + 0x8) = *(uint32_t*)(&stack_0x08 + 0x8);
label_800AC6EC:;
    r5 = 468 + (156);
    r6 = -4 + (-1);
    r4 = 3 + (1);
    if (0 >= 0) goto label_800AC6A0;
    r0 = 3;
    r9 = 0;
    r11 = 3;
    *(uint8_t*)(this_r3 + 0x1) = 3;
    *(uint8_t*)(this_r3 + 0x2) = 0;
    *(uint32_t*)(this_r3 + 0xC) = 3;
label_800AC714:;
    r0 = 0;
    *(uint8_t*)(this_r3 + 0x3) = 0;
    r0 = stack_0x24;
    return; // r3 = ret_800AC688
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionCursol(void)
// Unit: option.obj | Address: 0x800AC730 | Size: 0x13C bytes
// ============================================================================
/* [0x800AC730] */ void cOptionCtrl::optionCursol(cOptionCtrl* this_r3) {
    // Stack frame allocated: 64 bytes
    stack_0x44 = r0;
    r31 = this_r3;
    r3 = this_r3 + (16);
    r3 = cCursol::cursolBlink((this_r3 + 16)); // [0x800D0ACC]
    r27 = &prim_no.1077;
    f12 = *(double*)0x8016C7E8;
    r12 = &stack_0x08;
    r28 = &prim_no.1077 + (4);
    f11 = *(float*)0x8016C7F0;
    f13 = *(float*)0x8016C7F4;
    r29 = &stack_0x08;
    r25 = (&prim_no.1077 + 4);
    r10 = 0;
label_800AC788:;
    r0 = *(uint32_t*)(this_r3 + 0xC);
    r9 = 128;
    if (*(uint32_t*)(this_r3 + 0xC) != 0) goto label_800AC79C;
    r9 = r26;
label_800AC79C:;
    stack_0x1C = *(uint32_t*)(this_r3 + 0xC);
    r30 = 0 + (1);
    stack_0x18 = 0x43300000u;
    stack_0x08 = *(float*)0x8016C7F4;
    f0 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x8016C7F4;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x8016C7F4;
    *(float*)(&stack_0x08 + 0xC) = stack_0x18;
    if (r6 > *(uint32_t*)(this_r3 + 0xC)) goto label_800AC84C;
label_800AC7EC:;
    r9 = *(uint32_t*)(this_r3 + 0x2C);
    r11 = 0;
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14);
    r6 = r6 + (1);
    if (r6 >= *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14)) goto label_800AC808;
label_800AC808:;
    r5 = r5 + (-1);
    if (0 == 0) goto label_800AC844;
    r11 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8);
    r10 = stack_0x08;
    r8 = *(uint32_t*)(&stack_0x08 + 0x4);
    r11 = (r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8));
    r7 = *(uint32_t*)(&stack_0x08 + 0x8);
    r9 = (r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8)) + (96);
    r0 = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)((r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8)) + 0x60) = stack_0x08;
    *(uint32_t*)(((r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8)) + 96) + 0xC) = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)(((r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8)) + 96) + 0x4) = *(uint32_t*)(&stack_0x08 + 0x4);
    *(uint32_t*)(((r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8)) + 96) + 0x8) = *(uint32_t*)(&stack_0x08 + 0x8);
label_800AC844:;
    r4 = r4 + (156);
    if (0 <= 0) goto label_800AC7EC;
label_800AC84C:;
    r10 = (0 + 1);
    if ((0 + 1) <= 5) goto label_800AC788;
    r0 = stack_0x44;
    return; // r3 = ret_800AC748
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionCursolConf(void)
// Unit: option.obj | Address: 0x800AC86C | Size: 0x13C bytes
// ============================================================================
/* [0x800AC86C] */ void cOptionCtrl::optionCursolConf(cOptionCtrl* this_r3) {
    // Stack frame allocated: 64 bytes
    stack_0x44 = r0;
    r31 = this_r3;
    r3 = this_r3 + (16);
    r3 = cCursol::cursolBlink((this_r3 + 16)); // [0x800D0ACC]
    r27 = &prim_no.1081;
    f12 = *(double*)0x8016C810;
    r12 = &stack_0x08;
    r28 = &prim_no.1081 + (4);
    f11 = *(float*)0x8016C818;
    f13 = *(float*)0x8016C81C;
    r29 = &stack_0x08;
    r25 = (&prim_no.1081 + 4);
    r10 = 0;
label_800AC8C4:;
    r0 = *(uint32_t*)(this_r3 + 0xC);
    r9 = 128;
    if (*(uint32_t*)(this_r3 + 0xC) != 0) goto label_800AC8D8;
    r9 = r26;
label_800AC8D8:;
    stack_0x1C = *(uint32_t*)(this_r3 + 0xC);
    r30 = 0 + (1);
    stack_0x18 = 0x43300000u;
    stack_0x08 = *(float*)0x8016C81C;
    f0 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x8016C81C;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x8016C81C;
    *(float*)(&stack_0x08 + 0xC) = stack_0x18;
    if (r6 > *(uint32_t*)(this_r3 + 0xC)) goto label_800AC988;
label_800AC928:;
    r9 = *(uint32_t*)(this_r3 + 0x30);
    r11 = 0;
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14);
    r6 = r6 + (1);
    if (r6 >= *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x14)) goto label_800AC944;
label_800AC944:;
    r5 = r5 + (-1);
    if (0 == 0) goto label_800AC980;
    r11 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8);
    r10 = stack_0x08;
    r8 = *(uint32_t*)(&stack_0x08 + 0x4);
    r11 = (r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8));
    r7 = *(uint32_t*)(&stack_0x08 + 0x8);
    r9 = (r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8)) + (96);
    r0 = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)((r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8)) + 0x60) = stack_0x08;
    *(uint32_t*)(((r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8)) + 96) + 0xC) = *(uint32_t*)(&stack_0x08 + 0xC);
    *(uint32_t*)(((r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8)) + 96) + 0x4) = *(uint32_t*)(&stack_0x08 + 0x4);
    *(uint32_t*)(((r4 + *(uint32_t*)(*(uint32_t*)(this_r3 + 0x30) + 0x8)) + 96) + 0x8) = *(uint32_t*)(&stack_0x08 + 0x8);
label_800AC980:;
    r4 = r4 + (156);
    if (0 <= 0) goto label_800AC928;
label_800AC988:;
    r10 = (0 + 1);
    if ((0 + 1) <= 2) goto label_800AC8C4;
    r0 = stack_0x44;
    return; // r3 = ret_800AC884
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionTrans(void)
// Unit: option.obj | Address: 0x800AC9A8 | Size: 0x64 bytes
// ============================================================================
/* [0x800AC9A8] */ void cOptionCtrl::optionTrans(cOptionCtrl* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r31 = this_r3;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    if (r0 != 0) goto label_800AC9D8;
    r3 = *(uint32_t*)(this_r3 + 0x28);
    r4 = 0;
    r5 = -1;
    r3 = cIdMain::PrimMove(*(uint32_t*)(this_r3 + 0x28), 0, -1); // [0x800725F8]
label_800AC9D8:;
    r3 = *(uint32_t*)(this_r3 + 0x2C);
    r4 = 0;
    r5 = -1;
    r3 = cIdMain::PrimMove(*(uint32_t*)(this_r3 + 0x2C), 0, -1); // [0x800725F8]
    r3 = *(uint32_t*)(this_r3 + 0x30);
    r4 = 0;
    r5 = -1;
    r3 = cIdMain::PrimMove(*(uint32_t*)(this_r3 + 0x30), 0, -1); // [0x800725F8]
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_800AC9F4
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionMessage(void) const
// Unit: option.obj | Address: 0x800ACA0C | Size: 0x28 bytes
// ============================================================================
/* [0x800ACA0C] */ void cOptionCtrl::optionMessage(void) const(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = &cMes;
    r3 = CMesCtrl::MesMove(&cMes); // [0x8009F140]
    r0 = stack_0x0C;
    return; // r3 = ret_800ACA20
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::optionSndMode(void)
// Unit: option.obj | Address: 0x800ACA34 | Size: 0xB8 bytes
// ============================================================================
/* [0x800ACA34] */ void cOptionCtrl::optionSndMode(cOptionCtrl* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r31 = this_r3;
    r0 = *(uint8_t*)(SDA1::pG + 0x10E);
    if (*(uint8_t*)(SDA1::pG + 0x10E) != 0) goto label_800ACA60;
    r0 = 23;
    goto label_800ACA74;
label_800ACA60:;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A90);
    r0 = 24;
    if (*(uint8_t*)(SDA1::pG + 0x6A90) != 2) goto label_800ACA74;
    r0 = 25;
label_800ACA74:;
    *(uint8_t*)(this_r3 + 0x3C) = 25;
    r11 = *(uint32_t*)(this_r3 + 0x2C);
    r0 = *(uint8_t*)(this_r3 + 0x3C);
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x14) <= 4) goto label_800ACA98;
    r9 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8);
    *(uint16_t*)(*(uint32_t*)(*(uint32_t*)(this_r3 + 0x2C) + 0x8) + 0x2E2) = *(uint8_t*)(this_r3 + 0x3C);
label_800ACA98:;
    r9 = SDA1::pG;
    r4 = 8;
    r3 = *(uint32_t*)(this_r3 + 0x2C);
    r6 = 3;
    r5 = *(uint8_t*)(SDA1::pG + 0x6A8E);
    r7 = 0;
    r8 = 0;
    r3 = cIdMain::SetNumber(*(uint32_t*)(this_r3 + 0x2C), 8, *(uint8_t*)(SDA1::pG + 0x6A8E), 3, 0, 0); // [0x800730E8]
    r9 = SDA1::pG;
    r4 = 14;
    r3 = *(uint32_t*)(this_r3 + 0x2C);
    r6 = 3;
    r5 = *(uint8_t*)(SDA1::pG + 0x6A8F);
    r7 = 0;
    r8 = 0;
    r3 = cIdMain::SetNumber(*(uint32_t*)(this_r3 + 0x2C), 14, *(uint8_t*)(SDA1::pG + 0x6A8F), 3, 0, 0); // [0x800730E8]
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_800ACAD4
}

// ============================================================================
// High-Level AST Decompilation: cCursol::~cCursol(void)
// Unit: option.obj | Address: 0x800ACAEC | Size: 0x34 bytes
// ============================================================================
/* [0x800ACAEC] */ void cCursol::~cCursol(cCursol* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = &vtable_cCursol;
    *(uint32_t*)(this_r3 + 0x8) = &vtable_cCursol;
    if (r0 == 0) goto label_800ACB10;
    r3 = __builtin_delete(); // [0x8009C908]
label_800ACB10:;
    r0 = stack_0x0C;
    return; // r3 = ret_800ACB0C
}

// ============================================================================
// High-Level AST Decompilation: cAram2Mem::~cAram2Mem(void)
// Unit: option.obj | Address: 0x800ACB20 | Size: 0x34 bytes
// ============================================================================
/* [0x800ACB20] */ void cAram2Mem::~cAram2Mem(cAram2Mem* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = &vtable_cAram2Mem;
    *(uint32_t*)(this_r3 + 0x4) = &vtable_cAram2Mem;
    if (r0 == 0) goto label_800ACB44;
    r3 = __builtin_delete(); // [0x8009C908]
label_800ACB44:;
    r0 = stack_0x0C;
    return; // r3 = ret_800ACB40
}

// ============================================================================
// High-Level AST Decompilation: cSubScrn::~cSubScrn(void)
// Unit: option.obj | Address: 0x800ACB54 | Size: 0x4C bytes
// ============================================================================
/* [0x800ACB54] */ void cSubScrn::~cSubScrn(cSubScrn* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = &vtable_cSubScrn;
    r11 = &vtable_cAram2Mem;
    r10 = &vtable_cCursol;
    *(uint32_t*)(this_r3 + 0x24) = &vtable_cSubScrn;
    *(uint32_t*)(this_r3 + 0x20) = &vtable_cAram2Mem;
    *(uint32_t*)(this_r3 + 0x18) = &vtable_cCursol;
    if (r0 == 0) goto label_800ACB90;
    r3 = __builtin_delete(); // [0x8009C908]
label_800ACB90:;
    r0 = stack_0x0C;
    return; // r3 = ret_800ACB8C
}

// ============================================================================
// High-Level AST Decompilation: cOptionCtrl::~cOptionCtrl(void)
// Unit: option.obj | Address: 0x800ACBA0 | Size: 0x4C bytes
// ============================================================================
/* [0x800ACBA0] */ void cOptionCtrl::~cOptionCtrl(cOptionCtrl* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = &vtable_cSubScrn;
    r11 = &vtable_cAram2Mem;
    r10 = &vtable_cCursol;
    *(uint32_t*)(this_r3 + 0x24) = &vtable_cSubScrn;
    *(uint32_t*)(this_r3 + 0x20) = &vtable_cAram2Mem;
    *(uint32_t*)(this_r3 + 0x18) = &vtable_cCursol;
    if (r0 == 0) goto label_800ACBDC;
    r3 = __builtin_delete(); // [0x8009C908]
label_800ACBDC:;
    r0 = stack_0x0C;
    return; // r3 = ret_800ACBD8
}
