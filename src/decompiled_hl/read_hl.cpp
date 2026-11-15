// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: read.obj
// Functions Decompiled: 11
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: ReadAreaData(void)
// Unit: read.obj | Address: 0x800BF658 | Size: 0x54 bytes
// ============================================================================
/* [0x800BF658] */ void ReadAreaData(void) {
    // Stack frame allocated: 72 bytes
    stack_0x4C = r0;
    r9 = SDA1::pG;
    r4 = "st%x/r%x%02x.lze";
    r3 = &stack_0x08;
    r5 = *(uint8_t*)(SDA1::pG + 0x6A78);
    r7 = *(uint8_t*)(SDA1::pG + 0x6A79);
    r6 = *(uint8_t*)(SDA1::pG + 0x6A78);
    r3 = sprintf(); // [0x800E6E74]
    r3 = &stack_0x08;
    r4 = 0;
    r3 = ReadCompressData(&stack_0x08, 0); // [0x800BFB2C]
    r9 = SDA1::pG;
    *(uint32_t*)(SDA1::pG + 0x110) = ret_800BF690;
    r0 = stack_0x4C;
    return; // r3 = ret_800BF690
}

// ============================================================================
// High-Level AST Decompilation: CoreDataRead(void)
// Unit: read.obj | Address: 0x800BF6AC | Size: 0x8C bytes
// ============================================================================
/* [0x800BF6AC] */ void CoreDataRead(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r6 = 0;
    r7 = 0;
    *(uint32_t*)(SDA1::pG + 0xF8) = 0x80520000u;
    r8 = 260;
    r9 = 0;
    r10 = 0;
    r4 = 0;
    r3 = 5;
    r3 = DvdReadReqMain(5, 0, 0x80520000u, 0, 0, 260, 0, 0); // [0x8007B744]
    r4 = &stack_0x08;
    r5 = 0;
    r3 = DvdReadCheck(ret_800BF6E4, &stack_0x08, 0); // [0x8007BCFC]
    r11 = SDA1::pG;
    r3 = &cMes;
    r9 = *(uint32_t*)(SDA1::pG + 0xF8);
    r4 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x10);
    r4 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x10) + *(uint32_t*)(SDA1::pG + 0xF8));
    r3 = CMesCtrl::MesInit(&cMes, (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x10) + *(uint32_t*)(SDA1::pG + 0xF8))); // [0x8009F0A4]
    r3 = LoadSubScreen(); // [0x800CF894]
    r9 = SDA1::pG;
    r11 = *(uint32_t*)(SDA1::pG + 0xF8);
    r3 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x8);
    r3 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x8) + *(uint32_t*)(SDA1::pG + 0xF8));
    r3 = SpecularInit((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x8) + *(uint32_t*)(SDA1::pG + 0xF8))); // [0x800DBA98]
    r0 = stack_0x14;
    return; // r3 = ret_800BF724
}

// ============================================================================
// High-Level AST Decompilation: ModuleDatInit(tagMODULE_DAT *, unsigned long)
// Unit: read.obj | Address: 0x800BF738 | Size: 0x40 bytes
// ============================================================================
/* [0x800BF738] */ void ModuleDatInit(tagMODULE_DAT * arg0_r3, unsigned long arg1_r4) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = 0;
    if (0 >= arg1_r4) goto label_800BF75C;
label_800BF750:;
    r9 = 0 + (1);
    if ((0 + 1) < arg1_r4) goto label_800BF750;
label_800BF75C:;
    r4 = 0;
    r3 = memset(); // [0x800E8A5C]
    r0 = stack_0x0C;
    return; // r3 = ret_800BF764
}

// ============================================================================
// High-Level AST Decompilation: ReadEmData(unsigned long)
// Unit: read.obj | Address: 0x800BF778 | Size: 0x148 bytes
// ============================================================================
/* [0x800BF778] */ void ReadEmData(unsigned long arg0_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    if (arg0_r3 > 0xFu) goto label_800BF7D4;
    r9 = SDA1::pG;
    r8 = 0;
    r0 = *(uint32_t*)(SDA1::pG + 0x66A4);
    r11 = SDA1::pG;
    if (*(uint32_t*)(SDA1::pG + 0x66A4) == 0) goto label_800BF7C4;
    r10 = SDA1::pG + (26276);
label_800BF7AC:;
    r8 = 0 + (1);
    if ((0 + 1) > 1) goto label_800BF85C;
    if (*(uint32_t*)(SDA1::pG + 0x66A4) != 0) goto label_800BF7AC;
label_800BF7C4:;
    if ((0 + 1) > 1) goto label_800BF85C;
    r8 = (0 + 1) + (4);
    goto label_800BF814;
label_800BF7D4:;
    r9 = SDA1::pG;
    r8 = 0;
    r10 = SDA1::pG + (25636);
    r11 = SDA1::pG;
    if (*(uint32_t*)(SDA1::pG + 0x66A4) == 0) goto label_800BF80C;
    r9 = (SDA1::pG + 25636);
label_800BF7F4:;
    r8 = 0 + (1);
    if ((0 + 1) > 3) goto label_800BF85C;
    if (*(uint32_t*)(SDA1::pG + 0x66A4) != 0) goto label_800BF7F4;
label_800BF80C:;
    if ((0 + 1) > 3) goto label_800BF85C;
label_800BF814:;
    r11 = SDA1::pG + (25632);
    r9 = &EmFileTbl;
    r10 = (arg0_r3 + arg0_r3);
    r4 = 0;
    r5 = 0;
    r31 = *(uint32_t*)(SDA1::pG + 0x66A4);
    r6 = 0;
    r7 = 0;
    r8 = 4;
    r9 = 16;
    r10 = &stack_0x08;
    r3 = DvdReadReqMain(arg0_r3, 0, 0, 0, 0, 4, 16, &stack_0x08); // [0x8007B744]
    r30 = ret_800BF850;
    if ((0 + 1) >= 3) goto label_800BF86C;
label_800BF85C:;
    r3 = 0;
    goto label_800BF8AC;
label_800BF864:;
    r3 = 1;
    r3 = TaskSleep(1); // [0x800A1B5C]
label_800BF86C:;
    r3 = ret_800BF850;
    r4 = 0;
    r5 = 0;
    r3 = DvdReadCheck(ret_800BF850, 0, 0); // [0x8007BCFC]
    if (ret_800BF878 == 0) goto label_800BF864;
    r9 = SDA1::pG;
    r8 = 0;
    r0 = stack_0x08;
    r11 = SDA1::pG + (25636);
    r10 = SDA1::pG + (25640);
    r9 = SDA1::pG + (25648);
label_800BF8AC:;
    r0 = stack_0x1C;
    return; // r3 = ret_800BF878
}

// ============================================================================
// High-Level AST Decompilation: ReadPlayerData(void)
// Unit: read.obj | Address: 0x800BF8C0 | Size: 0x5C bytes
// ============================================================================
/* [0x800BF8C0] */ void ReadPlayerData(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r4 = 0;
    *(uint32_t*)(SDA1::pG + 0x118) = 0x80800000u;
    r6 = 0;
    r7 = 0;
    r8 = 260;
    r9 = 0;
    r10 = 0;
    r3 = 7;
    r3 = DvdReadReqMain(7, 0, 0x80800000u, 0, 0, 260, 0, 0); // [0x8007B744]
    r4 = &stack_0x08;
    r5 = 0;
    r3 = DvdReadCheck(ret_800BF8F8, &stack_0x08, 0); // [0x8007BCFC]
    r3 = ReadSuitData(); // [0x800BF91C]
    r0 = stack_0x14;
    return; // r3 = ret_800BF908
}

// ============================================================================
// High-Level AST Decompilation: ReadSuitData(void)
// Unit: read.obj | Address: 0x800BF91C | Size: 0xC8 bytes
// ============================================================================
/* [0x800BF91C] */ void ReadSuitData(void) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r9 = SDA1::pG;
    r10 = &tpl_tbl;
    r6 = 0;
    r4 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 0;
    r11 = *(uint8_t*)(SDA1::pG + 0x681A);
    r8 = 260;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8);
    r9 = 0;
    r11 = (*(uint8_t*)(SDA1::pG + 0x681A) + &tpl_tbl);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = *(uint16_t*)((*(uint8_t*)(SDA1::pG + 0x681A) + &tpl_tbl) + 0x2);
    r10 = 0;
    r4 = 0;
    r3 = DvdReadReqMain(*(uint16_t*)((*(uint8_t*)(SDA1::pG + 0x681A) + &tpl_tbl) + 0x2), 0, (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 0, 260, 0, 0); // [0x8007B744]
    r29 = &stack_0x08;
    r5 = 0;
    r4 = &stack_0x08;
    r3 = DvdReadCheck(ret_800BF96C, &stack_0x08, 0); // [0x8007BCFC]
    r10 = SDA1::pG;
    r11 = &pack_tpl_tbl;
    r4 = 0;
    r9 = *(uint8_t*)(SDA1::pG + 0x681A);
    r6 = 0;
    r30 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 0;
    r8 = 260;
    r9 = (*(uint8_t*)(SDA1::pG + 0x681A) + &pack_tpl_tbl);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x10);
    r3 = *(uint16_t*)((*(uint8_t*)(SDA1::pG + 0x681A) + &pack_tpl_tbl) + 0x2);
    r10 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x10) + *(uint32_t*)(SDA1::pG + 0x118));
    r9 = 0;
    r3 = DvdReadReqMain(*(uint16_t*)((*(uint8_t*)(SDA1::pG + 0x681A) + &pack_tpl_tbl) + 0x2), 0, (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x10) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 0, 260, 0, 0); // [0x8007B744]
    r4 = &stack_0x08;
    r5 = 0;
    r3 = DvdReadCheck(ret_800BF9C0, &stack_0x08, 0); // [0x8007BCFC]
    r0 = stack_0x24;
    return; // r3 = ret_800BF9CC
}

// ============================================================================
// High-Level AST Decompilation: EmReadInit(void)
// Unit: read.obj | Address: 0x800BF9E4 | Size: 0x2C bytes
// ============================================================================
/* [0x800BF9E4] */ void EmReadInit(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = SDA1::pG;
    r4 = 6;
    r3 = SDA1::pG + (25504);
    r3 = ModuleDatInit((SDA1::pG + 25504), 6); // [0x800BF738]
    r0 = stack_0x0C;
    return; // r3 = ret_800BF9FC
}

// ============================================================================
// High-Level AST Decompilation: EmReadSearch(unsigned char)
// Unit: read.obj | Address: 0x800BFA10 | Size: 0x90 bytes
// ============================================================================
/* [0x800BFA10] */ void EmReadSearch(unsigned char arg0_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r10 = arg0_r3;
    r8 = 0;
    r7 = 4;
    if (arg0_r3 > 0xFu) goto label_800BFA34;
    r7 = 6;
label_800BFA34:;
    r11 = 0;
    if (0 >= 6) goto label_800BFA7C;
    r9 = SDA1::pG;
    r3 = SDA1::pG + (25640);
label_800BFA48:;
    r0 = *(uint32_t*)((SDA1::pG + 25640) - 0x4);
    if (*(uint32_t*)((SDA1::pG + 25640) - 0x4) == 0) goto label_800BFA68;
    r0 = *(uint32_t*)((SDA1::pG + 25640) - 0x8);
    if (*(uint32_t*)((SDA1::pG + 25640) - 0x8) != arg0_r3) goto label_800BFA6C;
    r3 = *(uint32_t*)((SDA1::pG + 25640) + 0x0);
    goto label_800BFA90;
label_800BFA68:;
    r8 = 0 + (1);
label_800BFA6C:;
    r11 = 0 + (1);
    r3 = *(uint32_t*)((SDA1::pG + 25640) + 0x0) + (160);
    if ((0 + 1) < 6) goto label_800BFA48;
label_800BFA7C:;
    r3 = 0;
    if ((0 + 1) == 0) goto label_800BFA90;
    r3 = arg0_r3;
    r3 = ReadEmData(arg0_r3); // [0x800BF778]
label_800BFA90:;
    r0 = stack_0x0C;
    return; // r3 = ret_800BFA8C
}

// ============================================================================
// High-Level AST Decompilation: GetDataExt(unsigned long *, char *, unsigned long)
// Unit: read.obj | Address: 0x800BFAA0 | Size: 0x8C bytes
// ============================================================================
/* [0x800BFAA0] */ void GetDataExt(unsigned long * arg0_r3, char * arg1_r4, unsigned long arg2_r5) {
    r8 = arg0_r3;
    r10 = 1;
    r7 = *(uint32_t*)(arg0_r3 + 0x0);
    r6 = 0;
    r11 = (arg0_r3 + r0);
    if (1 > *(uint32_t*)(arg0_r3 + 0x0)) goto label_800BFB24;
    r0 = *(uint8_t*)(arg1_r4 + 0x0);
    r3 = arg0_r3 + (4);
label_800BFACC:;
    if (*(uint8_t*)(arg1_r4 + 0x0) != r12) goto label_800BFB14;
    r9 = *(uint8_t*)(arg1_r4 + 0x1);
    r0 = *(uint8_t*)((arg0_r3 + r0) + 0x1);
    if (*(uint8_t*)((arg0_r3 + r0) + 0x1) != *(uint8_t*)(arg1_r4 + 0x1)) goto label_800BFB14;
    r9 = *(uint8_t*)(arg1_r4 + 0x2);
    r0 = *(uint8_t*)((arg0_r3 + r0) + 0x2);
    if (*(uint8_t*)((arg0_r3 + r0) + 0x2) != *(uint8_t*)(arg1_r4 + 0x2)) goto label_800BFB14;
    if (0 != arg2_r5) goto label_800BFB10;
    r3 = *(uint32_t*)((arg0_r3 + 4) + 0x0);
    r3 = (*(uint32_t*)((arg0_r3 + 4) + 0x0) + arg0_r3);
    return; // r3 = (*(uint32_t*)((arg0_r3 + 4) + 0x0) + arg0_r3)
label_800BFB10:;
    r6 = 0 + (1);
label_800BFB14:;
    r10 = 1 + (1);
    r3 = (*(uint32_t*)((arg0_r3 + 4) + 0x0) + arg0_r3) + (4);
    if ((1 + 1) <= *(uint32_t*)(arg0_r3 + 0x0)) goto label_800BFACC;
label_800BFB24:;
    r3 = 0;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: ReadCompressData(char *, void *)
// Unit: read.obj | Address: 0x800BFB2C | Size: 0x168 bytes
// ============================================================================
/* [0x800BFB2C] */ void ReadCompressData(char * arg0_r3, void * arg1_r4) {
    // Stack frame allocated: 40 bytes
    stack_0x2C = r0;
    stack_0x14 = r12;
    r28 = arg0_r3;
    r30 = arg1_r4;
    r4 = &stack_0x08;
    r3 = DvdFileExistCheck(arg0_r3, &stack_0x08); // [0x8007B6E8]
    if (ret_800BFB50 >= 0) goto label_800BFB6C;
    r4 = arg0_r3;
    r3 = "DvdFileExistCheck Faild  %s\n";
    goto label_800BFC6C;
label_800BFB6C:;
    r9 = stack_0x08;
    r3 = 0;
    r4 = arg0_r3;
    r31 = (0x817E0000u - stack_0x08);
    r6 = 0;
    r5 = (0x817E0000u - stack_0x08);
    r7 = 0;
    r8 = 4;
    r9 = 0;
    r10 = 0;
    r3 = 0 | 0xFFFFu;
    r3 = DvdReadReqMain(0, arg0_r3, (0x817E0000u - stack_0x08), 0, 0, 4, 0, 0); // [0x8007B744]
    r29 = ret_800BFB9C;
    r3 = "RoomData Read Start!!\n";
    r3 = OSReport(); // [0x800F2D80]
    goto label_800BFBC4;
label_800BFBBC:;
    r3 = 1;
    r3 = TaskSleep(1); // [0x800A1B5C]
label_800BFBC4:;
    r3 = ret_800BFB9C;
    r4 = 0;
    r5 = 0;
    r3 = DvdReadCheck(ret_800BFB9C, 0, 0); // [0x8007BCFC]
    if (ret_800BFBD0 == 0) goto label_800BFBBC;
    r3 = "RoomData Read End!!\n";
    r3 = OSReport(); // [0x800F2D80]
    if (ret_800BFBD0 != 0) goto label_800BFBFC;
    r3 = *(uint32_t*)((0x817E0000u - stack_0x08) + 0x0);
    r3 = memAlloc(*(uint32_t*)((0x817E0000u - stack_0x08) + 0x0)); // [0x8009CB2C]
    r30 = ret_800BFBF4;
label_800BFBFC:;
    r3 = SDA1::Heap_handle;
    r3 = SystemHeapEndCheck(SDA1::Heap_handle); // [0x8009C9E0]
    if ((0x817E0000u - stack_0x08) < ret_800BFC00) goto label_800BFC40;
    r3 = "RoomData Decomp Start!!\n";
    r3 = OSReport(); // [0x800F2D80]
    r3 = ret_800BFBF4;
    r4 = (0x817E0000u - stack_0x08);
    r3 = LzsDecode(ret_800BFBF4, (0x817E0000u - stack_0x08)); // [0x80077680]
    r3 = "RoomData Decomp end!!\n";
    r3 = OSReport(); // [0x800F2D80]
    r3 = ret_800BFBF4;
    goto label_800BFC78;
label_800BFC40:;
    r9 = SDA1::pG;
    r3 = 0;
    r5 = "ReadCompressData(): memory over! R%x03";
    r6 = *(uint16_t*)(SDA1::pG + 0x6A78);
    r4 = 0;
    r3 = LogErr(0, 0, "ReadCompressData(): memory over! R%x03", *(uint16_t*)(SDA1::pG + 0x6A78)); // [0x8007A05C]
    r4 = arg0_r3;
    r3 = "ReadCompressData Alloc Faild  %s\n";
label_800BFC6C:;
    r3 = OSReport(); // [0x800F2D80]
    r3 = 0;
label_800BFC78:;
    r0 = stack_0x2C;
    r12 = stack_0x14;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: ReadAdrData(unsigned short, unsigned short)
// Unit: read.obj | Address: 0x800BFC94 | Size: 0x68 bytes
// ============================================================================
/* [0x800BFC94] */ void ReadAdrData(unsigned short arg0_r3, unsigned short arg1_r4) {
    // Stack frame allocated: 72 bytes
    stack_0x4C = r0;
    r7 = arg1_r4;
    r5 = arg0_r3;
    r6 = arg0_r3;
    r4 = "st%x/r%x%02x.adr";
    r3 = &stack_0x08;
    r3 = sprintf(); // [0x800E6E74]
    r10 = SDA1::pG;
    r3 = 0;
    r3 = 0 | 0xFFFFu;
    r4 = &stack_0x08;
    r10 = SDA1::pG + (272);
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r8 = 260;
    r9 = 16;
    r3 = DvdReadReqMain(0, &stack_0x08, 0, 0, 0, 260, 16, (SDA1::pG + 272)); // [0x8007B744]
    r0 = stack_0x4C;
    return; // r3 = ret_800BFCE8
}
