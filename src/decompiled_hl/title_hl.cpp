// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: title.obj
// Functions Decompiled: 20
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: Title_task(void)
// Unit: title.obj | Address: 0x800D7A58 | Size: 0xA0 bytes
// ============================================================================
/* [0x800D7A58] */ void Title_task(void) {
    // Stack frame allocated: 112 bytes
    stack_0x74 = r0;
    f0 = *(float*)0x8016E954;
    r30 = &stack_0x08;
    r0 = 0;
    r9 = 0;
    r11 = &vtable_cTitle;
    r29 = &vtable_cIdMain;
    *(uint32_t*)(&stack_0x08 + 0x18) = &vtable_cTitle;
    *(uint8_t*)(&stack_0x08 + 0x1C) = 0;
    r3 = &stack_0x08;
    *(float*)(&stack_0x08 + 0x34) = *(float*)0x8016E954;
    *(uint32_t*)(&stack_0x08 + 0x28) = 0;
    *(uint8_t*)(&stack_0x08 + 0x1F) = 0;
    *(uint8_t*)(&stack_0x08 + 0x1E) = 0;
    *(uint8_t*)(&stack_0x08 + 0x1D) = 0;
    *(uint32_t*)(&stack_0x08 + 0x24) = 0;
    *(uint32_t*)(&stack_0x08 + 0x20) = 0;
    *(uint32_t*)(&stack_0x08 + 0x44) = 0;
    *(uint32_t*)(&stack_0x08 + 0x40) = 0;
    *(uint32_t*)(&stack_0x08 + 0x4C) = 0;
    *(uint32_t*)(&stack_0x08 + 0x48) = 0;
    *(uint32_t*)(&stack_0x08 + 0x54) = 0;
    *(uint32_t*)(&stack_0x08 + 0x50) = 0;
    *(uint32_t*)(&stack_0x08 + 0x38) = 0;
    *(uint32_t*)(&stack_0x08 + 0x2C) = 0;
    *(float*)(&stack_0x08 + 0x30) = *(float*)0x8016E954;
    *(uint32_t*)(&stack_0x08 + 0x3C) = 0;
    r3 = cTitle::Title_move(&stack_0x08); // [0x800D7AF8]
    *(uint32_t*)(&stack_0x08 + 0x18) = &vtable_cIdMain;
    r0 = stack_0x74;
    return; // r3 = ret_800D7ADC
}

// ============================================================================
// High-Level AST Decompilation: cTitle::Title_move(void)
// Unit: title.obj | Address: 0x800D7AF8 | Size: 0x108 bytes
// ============================================================================
/* [0x800D7AF8] */ void cTitle::Title_move(cTitle* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x10 = f31;
    stack_0x0C = r31;
    stack_0x1C = r0;
    r31 = this_r3;
    f31 = *(float*)0x8016E958;
label_800D7B18:;
    f1 = *(float*)(this_r3 + 0x34);
    r3 = sinf(); // [0x800E46B4]
    f0 = *(float*)(this_r3 + 0x34);
    r0 = *(uint8_t*)(this_r3 + 0x1C);
    *(float*)(this_r3 + 0x30) = *(float*)(this_r3 + 0x34);
    *(float*)(this_r3 + 0x34) = *(float*)(this_r3 + 0x34);
    if (*(uint8_t*)(this_r3 + 0x1C) == 4) goto label_800D7BBC;
    if (*(uint8_t*)(this_r3 + 0x1C) > 4) goto label_800D7B6C;
    if (*(uint8_t*)(this_r3 + 0x1C) == 1) goto label_800D7B98;
    if (*(uint8_t*)(this_r3 + 0x1C) > 1) goto label_800D7B58;
    if (*(uint8_t*)(this_r3 + 0x1C) == 0) goto label_800D7B8C;
    goto label_800D7BF4;
label_800D7B58:;
    if (*(uint8_t*)(this_r3 + 0x1C) == 2) goto label_800D7BA4;
    if (*(uint8_t*)(this_r3 + 0x1C) == 3) goto label_800D7BB0;
    goto label_800D7BF4;
label_800D7B6C:;
    if (*(uint8_t*)(this_r3 + 0x1C) == 6) goto label_800D7BD4;
    if (*(uint8_t*)(this_r3 + 0x1C) < 6) goto label_800D7BC8;
    if (*(uint8_t*)(this_r3 + 0x1C) == 7) goto label_800D7BE0;
    if (*(uint8_t*)(this_r3 + 0x1C) == 8) goto label_800D7BEC;
    goto label_800D7BF4;
label_800D7B8C:;
    r3 = this_r3;
    r3 = cTitle::title_init(this_r3); // [0x800D7C00]
    goto label_800D7BF4;
label_800D7B98:;
    r3 = this_r3;
    r3 = cTitle::title_progressive(this_r3); // [0x800D7D24]
    goto label_800D7BF4;
label_800D7BA4:;
    r3 = this_r3;
    r3 = cTitle::title_card_check(this_r3); // [0x800D7F64]
    goto label_800D7BF4;
label_800D7BB0:;
    r3 = this_r3;
    r3 = cTitle::title_license(this_r3); // [0x800D7FD0]
    goto label_800D7BF4;
label_800D7BBC:;
    r3 = this_r3;
    r3 = cTitle::title_caplogo(this_r3); // [0x800D80E0]
    goto label_800D7BF4;
label_800D7BC8:;
    r3 = this_r3;
    r3 = cTitle::title_main(this_r3); // [0x800D8200]
    goto label_800D7BF4;
label_800D7BD4:;
    r3 = this_r3;
    r3 = cTitle::title_demo(this_r3); // [0x800D895C]
    goto label_800D7BF4;
label_800D7BE0:;
    r3 = this_r3;
    r3 = cTitle::title_load_game(this_r3); // [0x800D8A00]
    goto label_800D7BF4;
label_800D7BEC:;
    r3 = this_r3;
    r3 = cTitle::title_exit(this_r3); // [0x800D8B2C]
label_800D7BF4:;
    r3 = 1;
    r3 = TaskSleep(1); // [0x800A1B5C]
    goto label_800D7B18;
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_init(void)
// Unit: title.obj | Address: 0x800D7C00 | Size: 0x124 bytes
// ============================================================================
/* [0x800D7C00] */ void cTitle::title_init(cTitle* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = this_r3;
    r0 = *(uint32_t*)(SDA1::pG + 0xF8);
    if (*(uint32_t*)(SDA1::pG + 0xF8) != 0) goto label_800D7C28;
    r3 = CoreDataRead(); // [0x800BF6AC]
label_800D7C28:;
    r3 = 0;
    r4 = "/etc/title.dat";
    r9 = 16;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r8 = 260;
    r10 = this_r3 + (40);
    r3 = 0 | 0xFFFFu;
    r3 = DvdReadReqMain(0, "/etc/title.dat", 0, 0, 0, 260, 16, (this_r3 + 40)); // [0x8007B744]
    r31 = 0;
    r9 = *(uint32_t*)(this_r3 + 0x28);
    r3 = this_r3;
    r4 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x28) + 0x8);
    r5 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x28) + 0x4);
    r4 = (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x28) + 0x8) + *(uint32_t*)(this_r3 + 0x28));
    r5 = (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x28) + 0x4) + *(uint32_t*)(this_r3 + 0x28));
    r3 = cIdMain::SetTexPrim(this_r3, (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x28) + 0x8) + *(uint32_t*)(this_r3 + 0x28)), (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x28) + 0x4) + *(uint32_t*)(this_r3 + 0x28))); // [0x8007245C]
    r3 = 0;
    r4 = 1;
    r5 = 1;
    r3 = Snd_data_load(0, 1, 1); // [0x800CCB10]
label_800D7C84:;
    r3 = 0;
    r3 = FadeKill(0); // [0x800943F4]
    r31 = 0 + (1);
    if ((0 + 1) <= 3) goto label_800D7C84;
    r3 = 0;
    r3 = VISetBlack(); // [0x8010E7E0]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if ((0 + 1) != 3) goto label_800D7CF4;
    r3 = VIGetDTVStatus(); // [0x8010EBC4]
    if (ret_800D7CB0 == 0) goto label_800D7CF4;
    r0 = *(uint32_t*)0x8019D690;
    if (ret_800D7CB0 != 0) goto label_800D7CD8;
    r3 = OSGetProgressiveMode(); // [0x800F7D8C]
    if (ret_800D7CCC == 0) goto label_800D7CF4;
label_800D7CD8:;
    r0 = 1;
    *(uint32_t*)(this_r3 + 0x20) = (0 + 1);
    *(uint8_t*)(this_r3 + 0x1C) = 1;
    *(uint8_t*)(this_r3 + 0x1D) = (0 + 1);
    *(uint8_t*)(this_r3 + 0x1E) = (0 + 1);
    *(uint8_t*)(this_r3 + 0x1F) = (0 + 1);
    goto label_800D7D10;
label_800D7CF4:;
    r0 = 0;
    r9 = 2;
    *(uint32_t*)(this_r3 + 0x20) = 0;
    *(uint8_t*)(this_r3 + 0x1C) = 2;
    *(uint8_t*)(this_r3 + 0x1D) = 0;
    *(uint8_t*)(this_r3 + 0x1E) = 0;
    *(uint8_t*)(this_r3 + 0x1F) = 0;
label_800D7D10:;
    r0 = stack_0x14;
    return; // r3 = ret_800D7CCC
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_progressive(void)
// Unit: title.obj | Address: 0x800D7D24 | Size: 0x240 bytes
// ============================================================================
/* [0x800D7D24] */ void cTitle::title_progressive(cTitle* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r31 = this_r3;
    r9 = *(uint8_t*)(this_r3 + 0x1D);
    if (*(uint8_t*)(this_r3 + 0x1D) == 1) goto label_800D7D74;
    if (*(uint8_t*)(this_r3 + 0x1D) > 1) goto label_800D7D54;
    if (*(uint8_t*)(this_r3 + 0x1D) == 0) goto label_800D7D68;
    goto label_800D7F50;
label_800D7D54:;
    if (*(uint8_t*)(this_r3 + 0x1D) == 2) goto label_800D7EA8;
    if (*(uint8_t*)(this_r3 + 0x1D) == 3) goto label_800D7EBC;
    goto label_800D7F50;
label_800D7D68:;
    r0 = 1;
    *(uint8_t*)(this_r3 + 0x1E) = *(uint8_t*)(this_r3 + 0x1D);
    *(uint8_t*)(this_r3 + 0x1D) = 1;
label_800D7D74:;
    r0 = *(uint8_t*)(this_r3 + 0x1E);
    r30 = 7;
    if (*(uint8_t*)(this_r3 + 0x1E) != 0) goto label_800D7D88;
    r30 = 4;
label_800D7D88:;
    r29 = 7;
    if (*(uint8_t*)(this_r3 + 0x1E) == 0) goto label_800D7D94;
    r29 = 4;
label_800D7D94:;
    r3 = 20;
    r9 = "Would you like to display in progressive \nscan mode?";
    r4 = 20;
    r5 = 48;
    r6 = 160;
    r7 = 0;
    r8 = 0;
    r3 = eprintf3(20, 20, 48, 160, 0, 0, "Would you like to display in progressive \nscan mode?", r10); // [0x80081A94]
    r7 = 4;
    r9 = "YES";
    r3 = 20;
    r4 = 20;
    r5 = 320;
    r6 = 224;
    r8 = 0;
    r3 = eprintf3(20, 20, 320, 224, 4, 0, "YES", r10); // [0x80081A94]
    r7 = 4;
    r9 = "NO";
    r3 = 20;
    r4 = 20;
    r5 = 384;
    r6 = 224;
    r8 = 0;
    r3 = eprintf3(20, 20, 384, 224, 4, 0, "NO", r10); // [0x80081A94]
    r11 = &Joy;
    r0 = 0x00030003u;
    r9 = *(uint32_t*)(&Joy + 0x1C);
    if (*(uint8_t*)(this_r3 + 0x1E) == 0) goto label_800D7E4C;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
    r0 = *(uint8_t*)(this_r3 + 0x1E);
    *(uint8_t*)(this_r3 + 0x1E) = *(uint8_t*)(this_r3 + 0x1E);
    goto label_800D7F50;
label_800D7E4C:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (*(uint8_t*)(this_r3 + 0x1E) == 0) goto label_800D7F50;
    r0 = *(uint8_t*)(this_r3 + 0x1E);
    if (*(uint8_t*)(this_r3 + 0x1E) != 0) goto label_800D7E74;
    r3 = 1;
    r4 = 60;
    r3 = Progressive_set(1, 60); // [0x8009D878]
    goto label_800D7E80;
label_800D7E74:;
    r3 = 0;
    r4 = 60;
    r3 = Progressive_set(0, 60); // [0x8009D878]
label_800D7E80:;
    r3 = 0;
    r4 = 1;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 1, 0, 0); // [0x800CB7DC]
    r9 = 45;
    r0 = 2;
    *(uint8_t*)(this_r3 + 0x1D) = 2;
    *(uint32_t*)(this_r3 + 0x20) = 45;
    goto label_800D7F50;
label_800D7EA8:;
    r3 = 0;
    r3 = VISetBlack(); // [0x8010E7E0]
    r0 = 3;
    *(uint8_t*)(this_r3 + 0x1D) = 3;
    goto label_800D7F50;
label_800D7EBC:;
    r9 = *(uint32_t*)(this_r3 + 0x20);
    r9 = *(uint32_t*)(this_r3 + 0x20) + (-1);
    *(uint32_t*)(this_r3 + 0x20) = (*(uint32_t*)(this_r3 + 0x20) + -1);
    if ((*(uint32_t*)(this_r3 + 0x20) + -1) != -1) goto label_800D7EF0;
    r0 = 0;
    r9 = 2;
    *(uint32_t*)(this_r3 + 0x20) = 0;
    *(uint8_t*)(this_r3 + 0x1C) = 2;
    *(uint8_t*)(this_r3 + 0x1D) = 0;
    *(uint8_t*)(this_r3 + 0x1E) = 0;
    *(uint8_t*)(this_r3 + 0x1F) = 0;
    goto label_800D7F50;
label_800D7EF0:;
    r0 = *(uint8_t*)(this_r3 + 0x1E);
    if (*(uint8_t*)(this_r3 + 0x1E) != 0) goto label_800D7F28;
    r3 = 20;
    r9 = "Progressive scan mode has been turned on.";
    r4 = 20;
    r5 = 32;
    r6 = 160;
    r7 = 0;
    r8 = 0;
    r3 = eprintf3(20, 20, 32, 160, 0, 0, "Progressive scan mode has been turned on.", r10); // [0x80081A94]
    goto label_800D7F50;
label_800D7F28:;
    r3 = 20;
    r9 = "Progressive scan mode has been turned off.";
    r4 = 20;
    r5 = 32;
    r6 = 160;
    r7 = 0;
    r8 = 0;
    r3 = eprintf3(20, 20, 32, 160, 0, 0, "Progressive scan mode has been turned off.", r10); // [0x80081A94]
label_800D7F50:;
    r0 = stack_0x1C;
    return; // r3 = ret_800D7F4C
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_card_check(void)
// Unit: title.obj | Address: 0x800D7F64 | Size: 0x6C bytes
// ============================================================================
/* [0x800D7F64] */ void cTitle::title_card_check(cTitle* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r31 = this_r3;
    r0 = *(uint8_t*)(this_r3 + 0x1D);
    if (*(uint8_t*)(this_r3 + 0x1D) != 0) goto label_800D7FA0;
    r3 = 1;
    r4 = &Card_check(void);
    r3 = TaskExec(1, &Card_check(void)); // [0x800A1B08]
    r0 = 1;
    *(uint8_t*)(this_r3 + 0x1D) = 1;
    goto label_800D7FBC;
label_800D7FA0:;
    r0 = 0;
    r9 = 3;
    *(uint32_t*)(this_r3 + 0x20) = 0;
    *(uint8_t*)(this_r3 + 0x1C) = 3;
    *(uint8_t*)(this_r3 + 0x1D) = 0;
    *(uint8_t*)(this_r3 + 0x1E) = 0;
    *(uint8_t*)(this_r3 + 0x1F) = 0;
label_800D7FBC:;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_800D7F90
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_license(void)
// Unit: title.obj | Address: 0x800D7FD0 | Size: 0x110 bytes
// ============================================================================
/* [0x800D7FD0] */ void cTitle::title_license(cTitle* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r31 = this_r3;
    r30 = *(uint8_t*)(this_r3 + 0x1D);
    if (*(uint8_t*)(this_r3 + 0x1D) == 1) goto label_800D8028;
    if (*(uint8_t*)(this_r3 + 0x1D) > 1) goto label_800D8000;
    if (*(uint8_t*)(this_r3 + 0x1D) == 0) goto label_800D800C;
    goto label_800D80AC;
label_800D8000:;
    if (*(uint8_t*)(this_r3 + 0x1D) == 2) goto label_800D807C;
    goto label_800D80AC;
label_800D800C:;
    r0 = 255;
    stack_0x0C = *(uint8_t*)(this_r3 + 0x1D);
    stack_0x08 = 255;
    r3 = 0;
    r4 = &stack_0x08;
    r5 = &stack_0x0C;
    goto label_800D805C;
label_800D8028:;
    r9 = *(uint32_t*)(this_r3 + 0x20);
    r9 = *(uint32_t*)(this_r3 + 0x20) + (1);
    *(uint32_t*)(this_r3 + 0x20) = (*(uint32_t*)(this_r3 + 0x20) + 1);
    if ((*(uint32_t*)(this_r3 + 0x20) + 1) <= 39) goto label_800D80AC;
    r30 = 0;
    r0 = 0xE1E1E1FFu;
    stack_0x0C = 0;
    stack_0x08 = 0xE1E1E1FFu;
    r3 = 0;
    r4 = &stack_0x0C;
    r5 = &stack_0x08;
label_800D805C:;
    r6 = 20;
    r7 = 3;
    r3 = FadeSet(0, &stack_0x0C, &stack_0x08, 20, 3); // [0x80094358]
    r9 = *(uint8_t*)(this_r3 + 0x1D);
    *(uint32_t*)(this_r3 + 0x20) = 0;
    r9 = *(uint8_t*)(this_r3 + 0x1D) + (1);
    *(uint8_t*)(this_r3 + 0x1D) = (*(uint8_t*)(this_r3 + 0x1D) + 1);
    goto label_800D80AC;
label_800D807C:;
    r9 = *(uint32_t*)(this_r3 + 0x20);
    r9 = *(uint32_t*)(this_r3 + 0x20) + (1);
    *(uint32_t*)(this_r3 + 0x20) = (*(uint32_t*)(this_r3 + 0x20) + 1);
    if ((*(uint32_t*)(this_r3 + 0x20) + 1) <= 14) goto label_800D80AC;
    r9 = 0;
    r0 = 4;
    *(uint8_t*)(this_r3 + 0x1C) = 4;
    *(uint32_t*)(this_r3 + 0x20) = 0;
    *(uint8_t*)(this_r3 + 0x1D) = 0;
    *(uint8_t*)(this_r3 + 0x1E) = 0;
    *(uint8_t*)(this_r3 + 0x1F) = 0;
label_800D80AC:;
    r9 = *(uint32_t*)(this_r3 + 0x18);
    r4 = 31;
    r5 = 31;
    r3 = *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x18) + 0xC);
    r3 = (this_r3 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8));
    return; // r3 = (this_r3 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8))
    r0 = stack_0x1C;
    return; // r3 = (this_r3 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8))
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_caplogo(void)
// Unit: title.obj | Address: 0x800D80E0 | Size: 0x120 bytes
// ============================================================================
/* [0x800D80E0] */ void cTitle::title_caplogo(cTitle* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r31 = this_r3;
    r30 = *(uint8_t*)(this_r3 + 0x1D);
    if (*(uint8_t*)(this_r3 + 0x1D) == 1) goto label_800D8138;
    if (*(uint8_t*)(this_r3 + 0x1D) > 1) goto label_800D8110;
    if (*(uint8_t*)(this_r3 + 0x1D) == 0) goto label_800D811C;
    goto label_800D81CC;
label_800D8110:;
    if (*(uint8_t*)(this_r3 + 0x1D) == 2) goto label_800D819C;
    goto label_800D81CC;
label_800D811C:;
    r0 = 255;
    stack_0x0C = *(uint8_t*)(this_r3 + 0x1D);
    stack_0x08 = 255;
    r3 = 0;
    r4 = &stack_0x08;
    r5 = &stack_0x0C;
    goto label_800D817C;
label_800D8138:;
    r9 = *(uint32_t*)(this_r3 + 0x20);
    r9 = *(uint32_t*)(this_r3 + 0x20) + (1);
    *(uint32_t*)(this_r3 + 0x20) = (*(uint32_t*)(this_r3 + 0x20) + 1);
    if ((*(uint32_t*)(this_r3 + 0x20) + 1) > 59) goto label_800D815C;
    r0 = *(uint32_t*)0x8019D694;
    if ((*(uint32_t*)(this_r3 + 0x20) + 1) == 59) goto label_800D81CC;
label_800D815C:;
    r30 = 0;
    r0 = 0xE1E1E1FFu;
    stack_0x0C = 0;
    stack_0x08 = 0xE1E1E1FFu;
    r3 = 0;
    r4 = &stack_0x0C;
    r5 = &stack_0x08;
label_800D817C:;
    r6 = 20;
    r7 = 3;
    r3 = FadeSet(0, &stack_0x0C, &stack_0x08, 20, 3); // [0x80094358]
    r9 = *(uint8_t*)(this_r3 + 0x1D);
    *(uint32_t*)(this_r3 + 0x20) = 0;
    r9 = *(uint8_t*)(this_r3 + 0x1D) + (1);
    *(uint8_t*)(this_r3 + 0x1D) = (*(uint8_t*)(this_r3 + 0x1D) + 1);
    goto label_800D81CC;
label_800D819C:;
    r9 = *(uint32_t*)(this_r3 + 0x20);
    r9 = *(uint32_t*)(this_r3 + 0x20) + (1);
    *(uint32_t*)(this_r3 + 0x20) = (*(uint32_t*)(this_r3 + 0x20) + 1);
    if ((*(uint32_t*)(this_r3 + 0x20) + 1) <= 14) goto label_800D81CC;
    r9 = 0;
    r0 = 5;
    *(uint8_t*)(this_r3 + 0x1C) = 5;
    *(uint32_t*)(this_r3 + 0x20) = 0;
    *(uint8_t*)(this_r3 + 0x1D) = 0;
    *(uint8_t*)(this_r3 + 0x1E) = 0;
    *(uint8_t*)(this_r3 + 0x1F) = 0;
label_800D81CC:;
    r9 = *(uint32_t*)(this_r3 + 0x18);
    r4 = 0;
    r5 = 30;
    r3 = *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x18) + 0xC);
    r3 = (this_r3 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8));
    return; // r3 = (this_r3 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8))
    r0 = stack_0x1C;
    return; // r3 = (this_r3 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8))
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_main(void)
// Unit: title.obj | Address: 0x800D8200 | Size: 0x75C bytes
// ============================================================================
/* [0x800D8200] */ void cTitle::title_main(cTitle* this_r3) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r31 = this_r3;
    r30 = *(uint8_t*)(this_r3 + 0x1D);
    if (*(uint8_t*)(this_r3 + 0x1D) == 4) goto label_800D8568;
    if (*(uint8_t*)(this_r3 + 0x1D) > 4) goto label_800D8250;
    if (*(uint8_t*)(this_r3 + 0x1D) == 1) goto label_800D8314;
    if (*(uint8_t*)(this_r3 + 0x1D) > 1) goto label_800D823C;
    if (*(uint8_t*)(this_r3 + 0x1D) == 0) goto label_800D8284;
    goto label_800D8920;
label_800D823C:;
    if (*(uint8_t*)(this_r3 + 0x1D) == 2) goto label_800D83C0;
    if (*(uint8_t*)(this_r3 + 0x1D) == 3) goto label_800D841C;
    goto label_800D8920;
label_800D8250:;
    if (*(uint8_t*)(this_r3 + 0x1D) == 7) goto label_800D876C;
    if (*(uint8_t*)(this_r3 + 0x1D) > 7) goto label_800D8270;
    if (*(uint8_t*)(this_r3 + 0x1D) == 5) goto label_800D85A4;
    if (*(uint8_t*)(this_r3 + 0x1D) == 6) goto label_800D8728;
    goto label_800D8920;
label_800D8270:;
    if (*(uint8_t*)(this_r3 + 0x1D) == 8) goto label_800D8898;
    if (*(uint8_t*)(this_r3 + 0x1D) == 9) goto label_800D88F4;
    goto label_800D8920;
label_800D8284:;
    stack_0x0C = *(uint8_t*)(this_r3 + 0x1D);
    r0 = 0xE1E1E1FFu;
    stack_0x08 = 0xE1E1E1FFu;
    r4 = &stack_0x08;
    r5 = &stack_0x0C;
    r6 = 20;
    r7 = 3;
    r3 = FadeSet(0x80000000u, &stack_0x08, &stack_0x0C, 20, 3); // [0x80094358]
    r11 = 2;
    r10 = 3;
    *(uint32_t*)(this_r3 + 0x44) = 3;
    *(uint32_t*)(this_r3 + 0x4C) = 2;
    *(uint32_t*)(this_r3 + 0x54) = 2;
    *(uint32_t*)(this_r3 + 0x24) = *(uint8_t*)(this_r3 + 0x1D);
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x4);
    if (*(uint32_t*)(SDA1::pG + 0x4) >= 0) goto label_800D82D8;
    *(uint32_t*)(this_r3 + 0x4C) = 3;
label_800D82D8:;
    r9 = SDA1::pG;
    *(uint32_t*)(this_r3 + 0x2C) = *(uint8_t*)(this_r3 + 0x1D);
    r0 = *(uint32_t*)(SDA1::pG + 0x4);
    if (*(uint32_t*)(SDA1::pG + 0x4) == 0) goto label_800D82F4;
    r0 = 1;
    *(uint32_t*)(this_r3 + 0x2C) = 1;
label_800D82F4:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x4);
    if (*(uint32_t*)(SDA1::pG + 0x4) == 0) goto label_800D8308;
    *(uint32_t*)(this_r3 + 0x2C) = 2;
label_800D8308:;
    r0 = 5;
    r9 = 1;
    goto label_800D88DC;
label_800D8314:;
    r3 = this_r3;
    r3 = cTitle::title_disp_press(this_r3); // [0x800D8BFC]
    r0 = *(uint32_t*)0x8019D694;
    if (*(uint32_t*)(SDA1::pG + 0x4) == 0) goto label_800D8368;
    r3 = 0;
    r4 = 1;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 1, 0, 0); // [0x800CB7DC]
    r10 = 0;
    r0 = 5;
    r9 = 2;
    r11 = 8;
    *(uint8_t*)(this_r3 + 0x1C) = 5;
    *(uint8_t*)(this_r3 + 0x1D) = 2;
    *(uint8_t*)(this_r3 + 0x1F) = 0;
    *(uint32_t*)(this_r3 + 0x20) = 8;
    *(uint8_t*)(this_r3 + 0x1E) = 0;
    goto label_800D8920;
label_800D8368:;
    r9 = *(uint32_t*)(this_r3 + 0x24);
    r9 = *(uint32_t*)(this_r3 + 0x24) + (1);
    *(uint32_t*)(this_r3 + 0x24) = (*(uint32_t*)(this_r3 + 0x24) + 1);
    if ((*(uint32_t*)(this_r3 + 0x24) + 1) <= 299) goto label_800D8920;
    r0 = 255;
    stack_0x0C = *(uint8_t*)(this_r3 + 0x1D);
    stack_0x08 = 255;
    r3 = 0;
    r4 = &stack_0x0C;
    r5 = &stack_0x08;
    r6 = 20;
    r7 = 3;
    r3 = FadeSet(0, &stack_0x0C, &stack_0x08, 20, 3); // [0x80094358]
    r0 = 6;
    *(uint32_t*)(this_r3 + 0x24) = *(uint8_t*)(this_r3 + 0x1D);
    *(uint8_t*)(this_r3 + 0x1C) = 6;
    *(uint8_t*)(this_r3 + 0x1D) = *(uint8_t*)(this_r3 + 0x1D);
    *(uint8_t*)(this_r3 + 0x1E) = *(uint8_t*)(this_r3 + 0x1D);
    *(uint8_t*)(this_r3 + 0x1F) = *(uint8_t*)(this_r3 + 0x1D);
    *(uint32_t*)(this_r3 + 0x20) = *(uint8_t*)(this_r3 + 0x1D);
    goto label_800D8948;
label_800D83C0:;
    r3 = this_r3;
    r3 = cTitle::title_disp_mode_appear(this_r3); // [0x800D8C84]
    r9 = *(uint32_t*)(this_r3 + 0x20);
    r9 = *(uint32_t*)(this_r3 + 0x20) + (-1);
    *(uint32_t*)(this_r3 + 0x20) = (*(uint32_t*)(this_r3 + 0x20) + -1);
    if ((*(uint32_t*)(this_r3 + 0x20) + -1) != -1) goto label_800D8920;
    r0 = 0;
    r9 = 5;
    r11 = 3;
    *(uint8_t*)(this_r3 + 0x1C) = 5;
    *(uint8_t*)(this_r3 + 0x1D) = 3;
    *(uint8_t*)(this_r3 + 0x1E) = 0;
    *(uint8_t*)(this_r3 + 0x1F) = 0;
    *(uint32_t*)(this_r3 + 0x20) = 0;
    r9 = SDA1::pG;
    r0 = *(uint8_t*)(SDA1::pG + 0x10F);
    if (*(uint8_t*)(SDA1::pG + 0x10F) == 0) goto label_800D8414;
    r0 = 1;
label_800D8414:;
    *(uint32_t*)(this_r3 + 0x40) = 1;
    goto label_800D8920;
label_800D841C:;
    r3 = this_r3;
    r3 = cTitle::title_disp_mode(this_r3); // [0x800D8D04]
    r29 = &Joy;
    r9 = 0x000C000Cu;
    r0 = *(uint32_t*)(&Joy + 0x1C);
    if (*(uint8_t*)(SDA1::pG + 0x10F) == 0) goto label_800D84AC;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
    r9 = *(uint32_t*)(&Joy + 0x1C);
    r0 = 0x00080008u;
    if (*(uint8_t*)(SDA1::pG + 0x10F) == 0) goto label_800D848C;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r9 = *(uint32_t*)(this_r3 + 0x40) + (-1);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + -1);
    if ((*(uint32_t*)(this_r3 + 0x40) + -1) >= 0) goto label_800D8920;
    r9 = *(uint32_t*)(this_r3 + 0x44);
    r9 = *(uint32_t*)(this_r3 + 0x44) + (-1);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x44) + -1);
    goto label_800D8920;
label_800D848C:;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r11 = *(uint32_t*)(this_r3 + 0x44);
    r9 = *(uint32_t*)(this_r3 + 0x40) + (1);
    r11 = *(uint32_t*)(this_r3 + 0x44) + (-1);
    *(uint32_t*)(this_r3 + 0x40) = (*(uint32_t*)(this_r3 + 0x40) + 1);
    if ((*(uint32_t*)(this_r3 + 0x40) + 1) <= (*(uint32_t*)(this_r3 + 0x44) + -1)) goto label_800D8920;
    goto label_800D8414;
label_800D84AC:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if ((*(uint32_t*)(this_r3 + 0x40) + 1) == (*(uint32_t*)(this_r3 + 0x44) + -1)) goto label_800D8920;
    r3 = 0;
    r4 = 1;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 1, 0, 0); // [0x800CB7DC]
    r0 = *(uint32_t*)(this_r3 + 0x40);
    if (*(uint32_t*)(this_r3 + 0x40) == 1) goto label_800D8500;
    if (*(uint32_t*)(this_r3 + 0x40) > 1) goto label_800D84E8;
    if (*(uint32_t*)(this_r3 + 0x40) == 0) goto label_800D84F4;
    goto label_800D8920;
label_800D84E8:;
    if (*(uint32_t*)(this_r3 + 0x40) == 2) goto label_800D8544;
    goto label_800D8920;
label_800D84F4:;
    r0 = 5;
    r9 = 4;
    goto label_800D854C;
label_800D8500:;
    r9 = 7;
    *(uint8_t*)(this_r3 + 0x1D) = *(uint8_t*)(this_r3 + 0x1D);
    r0 = 0xE1E1E1FFu;
    *(uint8_t*)(this_r3 + 0x1E) = *(uint8_t*)(this_r3 + 0x1D);
    r3 = 0;
    *(uint8_t*)(this_r3 + 0x1F) = *(uint8_t*)(this_r3 + 0x1D);
    r4 = &stack_0x0C;
    *(uint32_t*)(this_r3 + 0x20) = *(uint8_t*)(this_r3 + 0x1D);
    r5 = &stack_0x08;
    *(uint8_t*)(this_r3 + 0x1C) = 7;
    r6 = 30;
    stack_0x0C = *(uint8_t*)(this_r3 + 0x1D);
    r7 = 3;
    stack_0x08 = 0xE1E1E1FFu;
    r3 = FadeSet(0, &stack_0x0C, &stack_0x08, 30, 3); // [0x80094358]
    goto label_800D8920;
label_800D8544:;
    r0 = 5;
    r9 = 6;
label_800D854C:;
    r11 = 8;
    *(uint8_t*)(this_r3 + 0x1C) = 5;
    *(uint8_t*)(this_r3 + 0x1D) = 6;
    *(uint8_t*)(this_r3 + 0x1F) = *(uint8_t*)(this_r3 + 0x1D);
    *(uint32_t*)(this_r3 + 0x20) = 8;
    *(uint8_t*)(this_r3 + 0x1E) = *(uint8_t*)(this_r3 + 0x1D);
    goto label_800D8920;
label_800D8568:;
    r3 = this_r3;
    r3 = cTitle::title_disp_dif_appear(this_r3); // [0x800D8E10]
    r9 = *(uint32_t*)(this_r3 + 0x20);
    r9 = *(uint32_t*)(this_r3 + 0x20) + (-1);
    *(uint32_t*)(this_r3 + 0x20) = (*(uint32_t*)(this_r3 + 0x20) + -1);
    if ((*(uint32_t*)(this_r3 + 0x20) + -1) != -1) goto label_800D8920;
    r0 = 0;
    r11 = 5;
    r9 = 1;
    *(uint8_t*)(this_r3 + 0x1D) = 5;
    *(uint32_t*)(this_r3 + 0x20) = 0;
    *(uint32_t*)(this_r3 + 0x48) = 1;
    *(uint8_t*)(this_r3 + 0x1C) = 5;
    goto label_800D86EC;
label_800D85A4:;
    r3 = this_r3;
    r3 = cTitle::title_disp_dif(this_r3); // [0x800D8EC4]
    r29 = &Joy;
    r9 = 0x000C000Cu;
    r0 = *(uint32_t*)(&Joy + 0x1C);
    if ((*(uint32_t*)(this_r3 + 0x20) + -1) == -1) goto label_800D8638;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
    r9 = *(uint32_t*)(&Joy + 0x1C);
    r0 = 0x00080008u;
    if ((*(uint32_t*)(this_r3 + 0x20) + -1) == -1) goto label_800D8614;
    r9 = *(uint32_t*)(this_r3 + 0x48);
    r9 = *(uint32_t*)(this_r3 + 0x48) + (-1);
    *(uint32_t*)(this_r3 + 0x48) = (*(uint32_t*)(this_r3 + 0x48) + -1);
    if ((*(uint32_t*)(this_r3 + 0x48) + -1) >= 0) goto label_800D8920;
    r9 = *(uint32_t*)(this_r3 + 0x4C);
    r9 = *(uint32_t*)(this_r3 + 0x4C) + (-1);
    *(uint32_t*)(this_r3 + 0x48) = (*(uint32_t*)(this_r3 + 0x4C) + -1);
    goto label_800D8920;
label_800D8614:;
    r9 = *(uint32_t*)(this_r3 + 0x48);
    r11 = *(uint32_t*)(this_r3 + 0x4C);
    r9 = *(uint32_t*)(this_r3 + 0x48) + (1);
    r11 = *(uint32_t*)(this_r3 + 0x4C) + (-1);
    *(uint32_t*)(this_r3 + 0x48) = (*(uint32_t*)(this_r3 + 0x48) + 1);
    if ((*(uint32_t*)(this_r3 + 0x48) + 1) <= (*(uint32_t*)(this_r3 + 0x4C) + -1)) goto label_800D8920;
    *(uint32_t*)(this_r3 + 0x48) = 0x00080008u;
    goto label_800D8920;
label_800D8638:;
    r11 = *(uint32_t*)(&Joy + 0x14);
    if ((*(uint32_t*)(this_r3 + 0x48) + 1) == (*(uint32_t*)(this_r3 + 0x4C) + -1)) goto label_800D8920;
    if ((*(uint32_t*)(this_r3 + 0x48) + 1) == (*(uint32_t*)(this_r3 + 0x4C) + -1)) goto label_800D86F8;
    r4 = 5;
    r5 = 0;
    r6 = 0;
    r3 = 0;
    r3 = SndSeCall(0, 5, 0, 0); // [0x800CB7DC]
    r4 = 6;
    r5 = 0;
    r6 = 0;
    r3 = 0;
    r3 = SndSeCall(0, 6, 0, 0); // [0x800CB7DC]
    r9 = SDA1::pG;
    r0 = 0xE1E1E1FFu;
    r3 = 0;
    *(uint8_t*)(SDA1::pG + 0x6A78) = r28;
    r4 = &stack_0x0C;
    *(uint8_t*)(SDA1::pG + 0x6A79) = r28;
    r5 = &stack_0x08;
    stack_0x08 = 0xE1E1E1FFu;
    r6 = 40;
    stack_0x0C = r28;
    r7 = 3;
    r3 = FadeSet(0, &stack_0x0C, &stack_0x08, 40, 3); // [0x80094358]
    r0 = *(uint32_t*)(this_r3 + 0x48);
    if (*(uint32_t*)(this_r3 + 0x48) == 1) goto label_800D86CC;
    if (*(uint32_t*)(this_r3 + 0x48) > 1) goto label_800D86C4;
    if (*(uint32_t*)(this_r3 + 0x48) == 0) goto label_800D86CC;
    goto label_800D86D4;
label_800D86C4:;
    if (*(uint32_t*)(this_r3 + 0x48) != 2) goto label_800D86D4;
label_800D86CC:;
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x681B) = *(uint32_t*)(this_r3 + 0x48);
label_800D86D4:;
    r0 = 0;
    r9 = 5;
    r11 = 8;
    *(uint8_t*)(this_r3 + 0x1C) = 5;
    *(uint8_t*)(this_r3 + 0x1D) = 8;
    *(uint32_t*)(this_r3 + 0x20) = 0;
label_800D86EC:;
    *(uint8_t*)(this_r3 + 0x1E) = 0;
    *(uint8_t*)(this_r3 + 0x1F) = 0;
    goto label_800D8920;
label_800D86F8:;
    r3 = 0;
    r4 = 2;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 2, 0, 0); // [0x800CB7DC]
    r0 = 2;
    *(uint8_t*)(this_r3 + 0x1C) = *(uint8_t*)(this_r3 + 0x1D);
    *(uint8_t*)(this_r3 + 0x1D) = 2;
    *(uint32_t*)(this_r3 + 0x20) = &Joy;
    *(uint8_t*)(this_r3 + 0x1E) = &Joy;
    *(uint8_t*)(this_r3 + 0x1F) = &Joy;
    goto label_800D8920;
label_800D8728:;
    r3 = this_r3;
    r3 = cTitle::title_disp_options_appear(this_r3); // [0x800D900C]
    r9 = *(uint32_t*)(this_r3 + 0x20);
    r9 = *(uint32_t*)(this_r3 + 0x20) + (-1);
    *(uint32_t*)(this_r3 + 0x20) = (*(uint32_t*)(this_r3 + 0x20) + -1);
    if ((*(uint32_t*)(this_r3 + 0x20) + -1) != -1) goto label_800D8920;
    r0 = 0;
    r9 = 5;
    r11 = 7;
    *(uint8_t*)(this_r3 + 0x1C) = 5;
    *(uint8_t*)(this_r3 + 0x1D) = 7;
    *(uint32_t*)(this_r3 + 0x50) = 0;
    *(uint8_t*)(this_r3 + 0x1E) = 0;
    *(uint8_t*)(this_r3 + 0x1F) = 0;
    *(uint32_t*)(this_r3 + 0x20) = 0;
    goto label_800D8920;
label_800D876C:;
    r3 = this_r3;
    r3 = cTitle::title_disp_options(this_r3); // [0x800D908C]
    r29 = &Joy;
    r0 = 0x000C000Cu;
    r9 = *(uint32_t*)(&Joy + 0x1C);
    if ((*(uint32_t*)(this_r3 + 0x20) + -1) == -1) goto label_800D8800;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 0, 0, 0); // [0x800CB7DC]
    r9 = *(uint32_t*)(&Joy + 0x1C);
    r0 = 0x00080008u;
    if ((*(uint32_t*)(this_r3 + 0x20) + -1) == -1) goto label_800D87DC;
    r9 = *(uint32_t*)(this_r3 + 0x50);
    r9 = *(uint32_t*)(this_r3 + 0x50) + (-1);
    *(uint32_t*)(this_r3 + 0x50) = (*(uint32_t*)(this_r3 + 0x50) + -1);
    if ((*(uint32_t*)(this_r3 + 0x50) + -1) >= 0) goto label_800D8920;
    r9 = *(uint32_t*)(this_r3 + 0x54);
    r9 = *(uint32_t*)(this_r3 + 0x54) + (-1);
    *(uint32_t*)(this_r3 + 0x50) = (*(uint32_t*)(this_r3 + 0x54) + -1);
    goto label_800D8920;
label_800D87DC:;
    r9 = *(uint32_t*)(this_r3 + 0x50);
    r11 = *(uint32_t*)(this_r3 + 0x54);
    r9 = *(uint32_t*)(this_r3 + 0x50) + (1);
    r11 = *(uint32_t*)(this_r3 + 0x54) + (-1);
    *(uint32_t*)(this_r3 + 0x50) = (*(uint32_t*)(this_r3 + 0x50) + 1);
    if ((*(uint32_t*)(this_r3 + 0x50) + 1) <= (*(uint32_t*)(this_r3 + 0x54) + -1)) goto label_800D8920;
    *(uint32_t*)(this_r3 + 0x50) = 0x00080008u;
    goto label_800D8920;
label_800D8800:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if ((*(uint32_t*)(this_r3 + 0x50) + 1) == (*(uint32_t*)(this_r3 + 0x54) + -1)) goto label_800D8920;
    if ((*(uint32_t*)(this_r3 + 0x50) + 1) == (*(uint32_t*)(this_r3 + 0x54) + -1)) goto label_800D8878;
    r0 = *(uint32_t*)(this_r3 + 0x50);
    if (*(uint32_t*)(this_r3 + 0x50) == 0) goto label_800D882C;
    if (*(uint32_t*)(this_r3 + 0x50) == 1) goto label_800D8854;
    goto label_800D8920;
label_800D882C:;
    r4 = 1;
    r5 = 0;
    r6 = 0;
    r3 = 0;
    r3 = SndSeCall(0, 1, 0, 0); // [0x800CB7DC]
    r3 = 1;
    r4 = &OptionTaskTitle(void);
    r3 = TaskExec(1, &OptionTaskTitle(void)); // [0x800A1B08]
    goto label_800D886C;
label_800D8854:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (*(uint32_t*)(this_r3 + 0x50) != 1) goto label_800D8920;
    r3 = "movie/joe.thp";
    r3 = ThpMovieOpen("movie/joe.thp"); // [0x800D594C]
label_800D886C:;
    r3 = 1;
    r3 = TaskSleep(1); // [0x800A1B5C]
    goto label_800D8920;
label_800D8878:;
    r3 = 0;
    r4 = 2;
    r5 = 0;
    r6 = 0;
    r3 = SndSeCall(0, 2, 0, 0); // [0x800CB7DC]
    r0 = 5;
    r9 = 2;
    goto label_800D88DC;
label_800D8898:;
    r3 = 0;
    r3 = FadeCheck(0); // [0x800943D8]
    r30 = ret_800D889C;
    if (*(uint32_t*)(this_r3 + 0x50) != 1) goto label_800D8920;
    r0 = 0xE1E1E1FFu;
    r9 = 255;
    stack_0x0C = 0xE1E1E1FFu;
    r3 = 0;
    stack_0x08 = 255;
    r4 = &stack_0x0C;
    r5 = &stack_0x08;
    r6 = 20;
    r7 = 3;
    r3 = FadeSet(0, &stack_0x0C, &stack_0x08, 20, 3); // [0x80094358]
    r0 = 5;
    r9 = 9;
label_800D88DC:;
    *(uint8_t*)(this_r3 + 0x1C) = 5;
    *(uint8_t*)(this_r3 + 0x1D) = 9;
    *(uint32_t*)(this_r3 + 0x20) = ret_800D889C;
    *(uint8_t*)(this_r3 + 0x1E) = ret_800D889C;
    *(uint8_t*)(this_r3 + 0x1F) = ret_800D889C;
    goto label_800D8920;
label_800D88F4:;
    r3 = 0;
    r3 = FadeCheck(0); // [0x800943D8]
    r3 = ret_800D88F8;
    if (*(uint32_t*)(this_r3 + 0x50) != 1) goto label_800D8920;
    r0 = 8;
    *(uint32_t*)(this_r3 + 0x20) = ret_800D88F8;
    *(uint8_t*)(this_r3 + 0x1C) = 8;
    *(uint8_t*)(this_r3 + 0x1D) = ret_800D88F8;
    *(uint8_t*)(this_r3 + 0x1E) = ret_800D88F8;
    *(uint8_t*)(this_r3 + 0x1F) = ret_800D88F8;
    goto label_800D8948;
label_800D8920:;
    r3 = this_r3;
    r3 = cTitle::title_disp_vanessa(this_r3); // [0x800D8B88]
    r9 = *(uint32_t*)(this_r3 + 0x18);
    r4 = 0;
    r5 = 29;
    r3 = *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x18) + 0xC);
    r3 = (this_r3 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8));
    return; // r3 = (this_r3 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8))
label_800D8948:;
    r0 = stack_0x24;
    return; // r3 = (this_r3 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x18) + 0x8))
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_demo(void)
// Unit: title.obj | Address: 0x800D895C | Size: 0xA4 bytes
// ============================================================================
/* [0x800D895C] */ void cTitle::title_demo(cTitle* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r31 = this_r3;
    r0 = *(uint8_t*)(this_r3 + 0x1D);
    if (*(uint8_t*)(this_r3 + 0x1D) == 0) goto label_800D8988;
    if (*(uint8_t*)(this_r3 + 0x1D) == 1) goto label_800D89D0;
    goto label_800D89EC;
label_800D8988:;
    r0 = *(uint32_t*)(this_r3 + 0x38);
    if (*(uint8_t*)(this_r3 + 0x1D) == 1) goto label_800D89A4;
    r3 = "movie/dance.thp";
    r3 = ThpMovieOpen("movie/dance.thp"); // [0x800D594C]
    goto label_800D89B0;
label_800D89A4:;
    r3 = "movie/demo.thp";
    r3 = ThpMovieOpen("movie/demo.thp"); // [0x800D594C]
label_800D89B0:;
    r3 = 1;
    r3 = TaskSleep(1); // [0x800A1B5C]
    r0 = *(uint32_t*)(this_r3 + 0x38);
    r9 = 1;
    *(uint8_t*)(this_r3 + 0x1D) = 1;
    *(uint32_t*)(this_r3 + 0x38) = *(uint32_t*)(this_r3 + 0x38);
    goto label_800D89EC;
label_800D89D0:;
    r0 = 0;
    r9 = 5;
    *(uint32_t*)(this_r3 + 0x20) = 0;
    *(uint8_t*)(this_r3 + 0x1C) = 5;
    *(uint8_t*)(this_r3 + 0x1D) = 0;
    *(uint8_t*)(this_r3 + 0x1E) = 0;
    *(uint8_t*)(this_r3 + 0x1F) = 0;
label_800D89EC:;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_800D89B4
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_load_game(void)
// Unit: title.obj | Address: 0x800D8A00 | Size: 0x12C bytes
// ============================================================================
/* [0x800D8A00] */ void cTitle::title_load_game(cTitle* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r31 = this_r3;
    r30 = *(uint8_t*)(this_r3 + 0x1D);
    if (*(uint8_t*)(this_r3 + 0x1D) == 0) goto label_800D8A2C;
    if (*(uint8_t*)(this_r3 + 0x1D) == 1) goto label_800D8A80;
    goto label_800D8A9C;
label_800D8A2C:;
    r3 = 0;
    r3 = FadeCheck(0); // [0x800943D8]
    if (ret_800D8A30 == 0) goto label_800D8A80;
    stack_0x0C = *(uint8_t*)(this_r3 + 0x1D);
    r0 = 0xE1E1E1FFu;
    r3 = 0;
    stack_0x08 = 0xE1E1E1FFu;
    r4 = &stack_0x08;
    r5 = &stack_0x0C;
    r6 = 30;
    r7 = 3;
    r3 = FadeSet(0, &stack_0x08, &stack_0x0C, 30, 3); // [0x80094358]
    r9 = SDA1::pG;
    r11 = 1;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    *(uint32_t*)(SDA1::pG + 0x124) = *(uint32_t*)(SDA1::pG + 0x124);
    *(uint8_t*)(this_r3 + 0x1D) = 1;
label_800D8A80:;
    r3 = 1;
    r4 = &Card_load(void);
    r3 = TaskExec(1, &Card_load(void)); // [0x800A1B08]
    r0 = 2;
    *(uint8_t*)(this_r3 + 0x1D) = 2;
    goto label_800D8B18;
label_800D8A9C:;
    r3 = 0;
    r3 = FadeCheck(0); // [0x800943D8]
    r3 = ret_800D8AA0;
    if (ret_800D8A30 != 0) goto label_800D8B18;
    r11 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if (ret_800D8A30 != 0) goto label_800D8AD4;
    r0 = 5;
    r9 = 2;
    *(uint32_t*)(this_r3 + 0x20) = ret_800D8AA0;
    *(uint8_t*)(this_r3 + 0x1C) = 5;
    *(uint8_t*)(this_r3 + 0x1D) = 2;
    goto label_800D8AF4;
label_800D8AD4:;
    if (ret_800D8A30 == 0) goto label_800D8B00;
    r9 = 5;
    *(uint32_t*)(SDA1::pG + 0x124) = 5;
    *(uint32_t*)(this_r3 + 0x20) = ret_800D8AA0;
    *(uint8_t*)(this_r3 + 0x1C) = 5;
    *(uint8_t*)(this_r3 + 0x1D) = ret_800D8AA0;
label_800D8AF4:;
    *(uint8_t*)(this_r3 + 0x1E) = ret_800D8AA0;
    *(uint8_t*)(this_r3 + 0x1F) = ret_800D8AA0;
    goto label_800D8B18;
label_800D8B00:;
    r0 = 8;
    *(uint32_t*)(this_r3 + 0x20) = 5;
    *(uint8_t*)(this_r3 + 0x1C) = 8;
    *(uint8_t*)(this_r3 + 0x1D) = 5;
    *(uint8_t*)(this_r3 + 0x1E) = 5;
    *(uint8_t*)(this_r3 + 0x1F) = 5;
label_800D8B18:;
    r0 = stack_0x1C;
    return; // r3 = ret_800D8AA0
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_exit(void)
// Unit: title.obj | Address: 0x800D8B2C | Size: 0x5C bytes
// ============================================================================
/* [0x800D8B2C] */ void cTitle::title_exit(cTitle* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r30 = this_r3;
    r3 = 0;
    r3 = FadeKill(0); // [0x800943F4]
    r3 = *(uint32_t*)(this_r3 + 0x28);
    if (*(uint32_t*)(this_r3 + 0x28) == 0) goto label_800D8B58;
    r3 = Mem_free(*(uint32_t*)(this_r3 + 0x28)); // [0x8009CC68]
label_800D8B58:;
    r9 = SDA1::pG;
    r3 = &GameTask(void);
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    r0 = *(uint32_t*)(SDA1::pG + 0x124) | 0x0400u;
    *(uint32_t*)(SDA1::pG + 0x124) = *(uint32_t*)(SDA1::pG + 0x124);
    r3 = TaskChain(&GameTask(void)); // [0x800A1BE4]
    r0 = stack_0x14;
    return; // r3 = ret_800D8B70
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_disp_vanessa(void)
// Unit: title.obj | Address: 0x800D8B88 | Size: 0x74 bytes
// ============================================================================
/* [0x800D8B88] */ void cTitle::title_disp_vanessa(cTitle* this_r3) {
    // Stack frame allocated: 32 bytes
    stack_0x18 = f31;
    stack_0x24 = r0;
    r29 = this_r3;
    f31 = *(float*)0x8016EA34;
    r30 = 3;
    r28 = 468;
label_800D8BB0:;
    r0 = *(uint32_t*)(this_r3 + 0x8);
    r31 = (*(uint32_t*)(this_r3 + 0x8) + 468);
    r3 = (*(uint32_t*)(this_r3 + 0x8) + 468);
    r28 = 468 + (156);
    r3 = IDData::IdDataInit((*(uint32_t*)(this_r3 + 0x8) + 468)); // [0x80072100]
    r0 = 3 + (-3);
    r9 = *(uint32_t*)(this_r3 + 0x2C);
    r30 = 3 + (1);
    if (*(uint32_t*)(this_r3 + 0x2C) != (3 + -3)) goto label_800D8BE0;
    *(float*)((*(uint32_t*)(this_r3 + 0x8) + 468) + 0x6C) = *(float*)0x8016EA34;
label_800D8BE0:;
    if (*(uint32_t*)(this_r3 + 0x2C) <= (3 + -3)) goto label_800D8BB0;
    r0 = stack_0x24;
    f31 = stack_0x18;
    return; // r3 = ret_800D8BC0
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_disp_press(void)
// Unit: title.obj | Address: 0x800D8BFC | Size: 0x88 bytes
// ============================================================================
/* [0x800D8BFC] */ void cTitle::title_disp_press(cTitle* this_r3) {
    // Stack frame allocated: 40 bytes
    stack_0x18 = f30;
    stack_0x20 = f31;
    stack_0x2C = r0;
    r29 = this_r3;
    f30 = *(float*)0x8016EA38;
    f31 = *(float*)0x8016EA3C;
    r30 = 0;
    r31 = *(uint32_t*)(this_r3 + 0x8);
label_800D8C30:;
    if (0 == 6) goto label_800D8C58;
    r3 = *(uint32_t*)(this_r3 + 0x8);
    if (0 != 6) goto label_800D8C54;
    f0 = *(float*)(this_r3 + 0x30);
    *(float*)(*(uint32_t*)(this_r3 + 0x8) + 0x6C) = *(float*)(this_r3 + 0x30);
    goto label_800D8C58;
label_800D8C54:;
    r3 = IDData::IdDataInit(*(uint32_t*)(this_r3 + 0x8)); // [0x80072100]
label_800D8C58:;
    r30 = 0 + (1);
    r31 = *(uint32_t*)(this_r3 + 0x8) + (156);
    if ((0 + 1) <= 31) goto label_800D8C30;
    r0 = stack_0x2C;
    f30 = stack_0x18;
    f31 = stack_0x20;
    return; // r3 = ret_800D8C54
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_disp_mode_appear(void)
// Unit: title.obj | Address: 0x800D8C84 | Size: 0x80 bytes
// ============================================================================
/* [0x800D8C84] */ void cTitle::title_disp_mode_appear(cTitle* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r30 = *(uint32_t*)(this_r3 + 0x8);
    r31 = 0;
label_800D8C9C:;
    r3 = *(uint32_t*)(this_r3 + 0x8);
    if (0 > 7) goto label_800D8CBC;
    if (0 >= 0) goto label_800D8CCC;
    if (0 == 0) goto label_800D8CE0;
    goto label_800D8CDC;
label_800D8CBC:;
    if (0 > 23) goto label_800D8CDC;
    if (0 < 23) goto label_800D8CDC;
label_800D8CCC:;
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) | 0x0006u;
    *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    goto label_800D8CE0;
label_800D8CDC:;
    r3 = IDData::IdDataInit(*(uint32_t*)(this_r3 + 0x8)); // [0x80072100]
label_800D8CE0:;
    r31 = 0 + (1);
    r30 = *(uint32_t*)(this_r3 + 0x8) + (156);
    if ((0 + 1) <= 31) goto label_800D8C9C;
    r0 = stack_0x14;
    return; // r3 = ret_800D8CDC
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_disp_mode(void)
// Unit: title.obj | Address: 0x800D8D04 | Size: 0x10C bytes
// ============================================================================
/* [0x800D8D04] */ void cTitle::title_disp_mode(cTitle* this_r3) {
    // Stack frame allocated: 48 bytes
    stack_0x18 = f29;
    stack_0x20 = f30;
    stack_0x28 = f31;
    stack_0x34 = r0;
    r29 = this_r3;
    f29 = *(float*)0x8016EA40;
    f30 = *(float*)0x8016EA44;
    f31 = *(float*)0x8016EA48;
    r30 = 0;
    r31 = *(uint32_t*)(this_r3 + 0x8);
label_800D8D44:;
    if (0 <= 17) goto label_800D8D60;
    if (0 > 25) goto label_800D8DD8;
    if (0 < 23) goto label_800D8DD8;
    goto label_800D8DE0;
label_800D8D60:;
    if (0 >= 15) goto label_800D8DAC;
    if (0 == 0) goto label_800D8DE0;
    if (0 < 0) goto label_800D8DD8;
    if (0 > 9) goto label_800D8DD8;
    if (0 < 7) goto label_800D8DD8;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r0 = 0 + (-7);
    if (*(uint32_t*)(this_r3 + 0x40) != (0 + -7)) goto label_800D8DA4;
    f0 = *(float*)(this_r3 + 0x30);
    *(float*)(*(uint32_t*)(this_r3 + 0x8) + 0x6C) = *(float*)(this_r3 + 0x30);
    goto label_800D8DE0;
label_800D8DA4:;
    *(float*)(*(uint32_t*)(this_r3 + 0x8) + 0x6C) = *(float*)0x8016EA48;
    goto label_800D8DE0;
label_800D8DAC:;
    r9 = *(uint32_t*)(this_r3 + 0x40);
    r0 = 0 + (-15);
    if (*(uint32_t*)(this_r3 + 0x40) != (0 + -15)) goto label_800D8DCC;
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) | 0x0006u;
    *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    goto label_800D8DE0;
label_800D8DCC:;
    r3 = *(uint32_t*)(this_r3 + 0x8);
    r3 = IDData::IdDataInit(*(uint32_t*)(this_r3 + 0x8)); // [0x80072100]
    goto label_800D8DE0;
label_800D8DD8:;
    r3 = *(uint32_t*)(this_r3 + 0x8);
    r3 = IDData::IdDataInit(*(uint32_t*)(this_r3 + 0x8)); // [0x80072100]
label_800D8DE0:;
    r30 = 0 + (1);
    r31 = *(uint32_t*)(this_r3 + 0x8) + (156);
    if ((0 + 1) <= 31) goto label_800D8D44;
    r0 = stack_0x34;
    f29 = stack_0x18;
    f30 = stack_0x20;
    f31 = stack_0x28;
    return; // r3 = ret_800D8DDC
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_disp_dif_appear(void)
// Unit: title.obj | Address: 0x800D8E10 | Size: 0xB4 bytes
// ============================================================================
/* [0x800D8E10] */ void cTitle::title_disp_dif_appear(cTitle* this_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r29 = this_r3;
    r30 = 0;
    r31 = *(uint32_t*)(this_r3 + 0x8);
label_800D8E2C:;
    if (0 == 12) goto label_800D8E70;
    if (0 > 12) goto label_800D8E50;
    if (0 == 0) goto label_800D8EA0;
    if (0 < 0) goto label_800D8E98;
    if (0 < 10) goto label_800D8E98;
    goto label_800D8E88;
label_800D8E50:;
    if (0 == 26) goto label_800D8E88;
    if (0 > 26) goto label_800D8E68;
    if (0 == 23) goto label_800D8EA0;
    goto label_800D8E98;
label_800D8E68:;
    if (0 != 27) goto label_800D8E98;
label_800D8E70:;
    r0 = *(uint32_t*)(this_r3 + 0x4C);
    if (*(uint32_t*)(this_r3 + 0x4C) > 2) goto label_800D8E88;
    r3 = *(uint32_t*)(this_r3 + 0x8);
    r3 = IDData::IdDataInit(*(uint32_t*)(this_r3 + 0x8)); // [0x80072100]
    goto label_800D8EA0;
label_800D8E88:;
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) | 0x0006u;
    *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    goto label_800D8EA0;
label_800D8E98:;
    r3 = *(uint32_t*)(this_r3 + 0x8);
    r3 = IDData::IdDataInit(*(uint32_t*)(this_r3 + 0x8)); // [0x80072100]
label_800D8EA0:;
    r30 = 0 + (1);
    r31 = *(uint32_t*)(this_r3 + 0x8) + (156);
    if ((0 + 1) <= 31) goto label_800D8E2C;
    r0 = stack_0x1C;
    return; // r3 = ret_800D8E9C
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_disp_dif(void)
// Unit: title.obj | Address: 0x800D8EC4 | Size: 0x148 bytes
// ============================================================================
/* [0x800D8EC4] */ void cTitle::title_disp_dif(cTitle* this_r3) {
    // Stack frame allocated: 48 bytes
    stack_0x18 = f29;
    stack_0x20 = f30;
    stack_0x28 = f31;
    stack_0x34 = r0;
    r29 = this_r3;
    f29 = *(float*)0x8016EA4C;
    f30 = *(float*)0x8016EA50;
    f31 = *(float*)0x8016EA54;
    r30 = 0;
    r31 = *(uint32_t*)(this_r3 + 0x8);
label_800D8F04:;
    if (0 > 19) goto label_800D8F3C;
    if (0 >= 18) goto label_800D8FA8;
    if (0 > 11) goto label_800D8F30;
    if (0 >= 10) goto label_800D8F74;
    if (0 == 0) goto label_800D8FDC;
    goto label_800D8FD4;
label_800D8F30:;
    if (0 == 12) goto label_800D8F68;
    goto label_800D8FD4;
label_800D8F3C:;
    if (0 == 23) goto label_800D8FDC;
    if (0 > 23) goto label_800D8F54;
    if (0 == 20) goto label_800D8F9C;
    goto label_800D8FD4;
label_800D8F54:;
    if (0 > 27) goto label_800D8FD4;
    if (0 < 26) goto label_800D8FD4;
    goto label_800D8FDC;
label_800D8F68:;
    r0 = *(uint32_t*)(this_r3 + 0x4C);
    if (*(uint32_t*)(this_r3 + 0x4C) <= 2) goto label_800D8FC8;
label_800D8F74:;
    r9 = *(uint32_t*)(this_r3 + 0x48);
    r0 = 0 + (-10);
    if (*(uint32_t*)(this_r3 + 0x48) != (0 + -10)) goto label_800D8F94;
    f0 = *(float*)(this_r3 + 0x30);
    *(float*)(*(uint32_t*)(this_r3 + 0x8) + 0x6C) = *(float*)(this_r3 + 0x30);
    goto label_800D8FDC;
label_800D8F94:;
    *(float*)(*(uint32_t*)(this_r3 + 0x8) + 0x6C) = *(float*)0x8016EA54;
    goto label_800D8FDC;
label_800D8F9C:;
    r0 = *(uint32_t*)(this_r3 + 0x4C);
    if (*(uint32_t*)(this_r3 + 0x4C) <= 2) goto label_800D8FC8;
label_800D8FA8:;
    r9 = *(uint32_t*)(this_r3 + 0x48);
    r0 = 0 + (-18);
    if (*(uint32_t*)(this_r3 + 0x48) != (0 + -18)) goto label_800D8FC8;
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) | 0x0006u;
    *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    goto label_800D8FDC;
label_800D8FC8:;
    r3 = *(uint32_t*)(this_r3 + 0x8);
    r3 = IDData::IdDataInit(*(uint32_t*)(this_r3 + 0x8)); // [0x80072100]
    goto label_800D8FDC;
label_800D8FD4:;
    r3 = *(uint32_t*)(this_r3 + 0x8);
    r3 = IDData::IdDataInit(*(uint32_t*)(this_r3 + 0x8)); // [0x80072100]
label_800D8FDC:;
    r30 = 0 + (1);
    r31 = *(uint32_t*)(this_r3 + 0x8) + (156);
    if ((0 + 1) <= 31) goto label_800D8F04;
    r0 = stack_0x34;
    f29 = stack_0x18;
    f30 = stack_0x20;
    f31 = stack_0x28;
    return; // r3 = ret_800D8FD8
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_disp_options_appear(void)
// Unit: title.obj | Address: 0x800D900C | Size: 0x80 bytes
// ============================================================================
/* [0x800D900C] */ void cTitle::title_disp_options_appear(cTitle* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r30 = *(uint32_t*)(this_r3 + 0x8);
    r31 = 0;
label_800D9024:;
    if (0 > 13) goto label_800D9040;
    if (0 >= 0) goto label_800D9050;
    if (0 == 0) goto label_800D9068;
    goto label_800D9060;
label_800D9040:;
    if (0 == 29) goto label_800D9068;
    if (0 != 29) goto label_800D9060;
label_800D9050:;
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) | 0x0006u;
    *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    goto label_800D9068;
label_800D9060:;
    r3 = *(uint32_t*)(this_r3 + 0x8);
    r3 = IDData::IdDataInit(*(uint32_t*)(this_r3 + 0x8)); // [0x80072100]
label_800D9068:;
    r31 = 0 + (1);
    r30 = *(uint32_t*)(this_r3 + 0x8) + (156);
    if ((0 + 1) <= 31) goto label_800D9024;
    r0 = stack_0x14;
    return; // r3 = ret_800D9064
}

// ============================================================================
// High-Level AST Decompilation: cTitle::title_disp_options(void)
// Unit: title.obj | Address: 0x800D908C | Size: 0x10C bytes
// ============================================================================
/* [0x800D908C] */ void cTitle::title_disp_options(cTitle* this_r3) {
    // Stack frame allocated: 48 bytes
    stack_0x18 = f29;
    stack_0x20 = f30;
    stack_0x28 = f31;
    stack_0x34 = r0;
    r29 = this_r3;
    f29 = *(float*)0x8016EA58;
    f30 = *(float*)0x8016EA5C;
    f31 = *(float*)0x8016EA60;
    r30 = 0;
    r31 = *(uint32_t*)(this_r3 + 0x8);
label_800D90CC:;
    if (0 <= 22) goto label_800D90E8;
    if (0 == 23) goto label_800D9168;
    if (0 != 29) goto label_800D9160;
    goto label_800D9168;
label_800D90E8:;
    if (0 >= 21) goto label_800D9134;
    if (0 == 0) goto label_800D9168;
    if (0 < 0) goto label_800D9160;
    if (0 > 14) goto label_800D9160;
    if (0 < 13) goto label_800D9160;
    r9 = *(uint32_t*)(this_r3 + 0x50);
    r0 = 0 + (-13);
    if (*(uint32_t*)(this_r3 + 0x50) != (0 + -13)) goto label_800D912C;
    f0 = *(float*)(this_r3 + 0x30);
    *(float*)(*(uint32_t*)(this_r3 + 0x8) + 0x6C) = *(float*)(this_r3 + 0x30);
    goto label_800D9168;
label_800D912C:;
    *(float*)(*(uint32_t*)(this_r3 + 0x8) + 0x6C) = *(float*)0x8016EA60;
    goto label_800D9168;
label_800D9134:;
    r9 = *(uint32_t*)(this_r3 + 0x50);
    r0 = 0 + (-21);
    if (*(uint32_t*)(this_r3 + 0x50) != (0 + -21)) goto label_800D9154;
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    r0 = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) | 0x0006u;
    *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71) = *(uint8_t*)(*(uint32_t*)(this_r3 + 0x8) + 0x71);
    goto label_800D9168;
label_800D9154:;
    r3 = *(uint32_t*)(this_r3 + 0x8);
    r3 = IDData::IdDataInit(*(uint32_t*)(this_r3 + 0x8)); // [0x80072100]
    goto label_800D9168;
label_800D9160:;
    r3 = *(uint32_t*)(this_r3 + 0x8);
    r3 = IDData::IdDataInit(*(uint32_t*)(this_r3 + 0x8)); // [0x80072100]
label_800D9168:;
    r30 = 0 + (1);
    r31 = *(uint32_t*)(this_r3 + 0x8) + (156);
    if ((0 + 1) <= 31) goto label_800D90CC;
    r0 = stack_0x34;
    f29 = stack_0x18;
    f30 = stack_0x20;
    f31 = stack_0x28;
    return; // r3 = ret_800D9164
}

// ============================================================================
// High-Level AST Decompilation: cTitle::~cTitle(void)
// Unit: title.obj | Address: 0x800D9198 | Size: 0x34 bytes
// ============================================================================
/* [0x800D9198] */ void cTitle::~cTitle(cTitle* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = &vtable_cIdMain;
    *(uint32_t*)(this_r3 + 0x18) = &vtable_cIdMain;
    if (r0 == 0) goto label_800D91BC;
    r3 = __builtin_delete(); // [0x8009C908]
label_800D91BC:;
    r0 = stack_0x0C;
    return; // r3 = ret_800D91B8
}
