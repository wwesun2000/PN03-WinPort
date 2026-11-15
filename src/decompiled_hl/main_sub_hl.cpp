// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: main_sub.obj
// Functions Decompiled: 15
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: Render_init(void)
// Unit: main_sub.obj | Address: 0x8009D098 | Size: 0x218 bytes
// ============================================================================
/* [0x8009D098] */ void Render_init(void) {
    // Stack frame allocated: 40 bytes
    stack_0x20 = f31;
    stack_0x2C = r0;
    r3 = VIGetTvFormat(); // [0x8010EB5C]
    r31 = &Rmode;
    if (ret_8009D0AC == 1) goto label_8009D0EC;
    if (ret_8009D0AC < 0x1u) goto label_8009D134;
    if (ret_8009D0AC == 2) goto label_8009D10C;
    if (ret_8009D0AC != 5) goto label_8009D118;
    r0 = 20;
    r9 = 16;
    Rmode = 20;
    *(uint16_t*)(&Rmode + 0xC) = 16;
    goto label_8009D134;
label_8009D0EC:;
    r9 = 4;
    r0 = 528;
    Rmode = 4;
    r11 = 23;
    *(uint16_t*)(&Rmode + 0xC) = 23;
    *(uint16_t*)(&Rmode + 0x10) = 528;
    *(uint16_t*)(&Rmode + 0x8) = 528;
    goto label_8009D134;
label_8009D10C:;
    r0 = 8;
    Rmode = 8;
    goto label_8009D134;
label_8009D118:;
    r3 = "D:/MEKA/Prog/main_sub.cpp";
    r5 = "invalid TV format\n";
    r4 = 141;
    r3 = OSPanic(); // [0x800F2E20]
label_8009D134:;
    r9 = *(uint16_t*)(&Rmode + 0x8);
    r29 = &pFrame_buff;
    *(uint32_t*)(&pFrame_buff + 0x0) = 0x80A00000u;
    r28 = 0x8026E75Cu;
    SDA1::pCurrent_buff = (*(uint16_t*)(&Rmode + 0x8) + 0x80A00000u);
    r3 = &Rmode;
    SDA1::DefaultFifo = 0x80980000u;
    *(uint32_t*)(0x8026E75Cu + 0x0) = (*(uint16_t*)(&Rmode + 0x8) + 0x80A00000u);
    r3 = VIConfigure(); // [0x8010DA0C]
    r3 = SDA1::DefaultFifo;
    r3 = GXInit(); // [0x8011C108]
    r0 = *(uint16_t*)(&Rmode + 0x4);
    r7 = *(uint16_t*)(&Rmode + 0x6);
    r8 = 0x80980000u;
    stack_0x0C = *(uint16_t*)(&Rmode + 0x4);
    f1 = *(float*)0x8016BAE8;
    stack_0x08 = 0x43300000u;
    f31 = *(double*)0x8016BAE0;
    f3 = stack_0x08;
    stack_0x0C = *(uint16_t*)(&Rmode + 0x6);
    f6 = *(float*)0x8016BAEC;
    stack_0x08 = 0x43300000u;
    SDA1::DefaultFifoObj = ret_8009D174;
    f4 = stack_0x08;
    r3 = GXSetViewport(); // [0x80126334]
    r5 = *(uint16_t*)(&Rmode + 0x4);
    r3 = 0;
    r6 = *(uint16_t*)(&Rmode + 0x6);
    r4 = 0;
    r3 = GXSetScissor(); // [0x80126390]
    r5 = *(uint16_t*)(&Rmode + 0x4);
    r3 = 0;
    r6 = *(uint16_t*)(&Rmode + 0x6);
    r4 = 0;
    r3 = GXSetDispCopySrc(); // [0x80120F4C]
    r4 = *(uint16_t*)(&Rmode + 0x8);
    r3 = *(uint16_t*)(&Rmode + 0x4);
    r3 = GXSetDispCopyDst(); // [0x8012106C]
    r0 = *(uint16_t*)(&Rmode + 0x8);
    r10 = *(uint16_t*)(&Rmode + 0x6);
    r11 = 0x80170000u;
    stack_0x0C = *(uint16_t*)(&Rmode + 0x8);
    stack_0x08 = 0x43300000u;
    f0 = stack_0x08;
    stack_0x0C = *(uint16_t*)(&Rmode + 0x6);
    stack_0x08 = 0x43300000u;
    f1 = stack_0x08;
    r3 = GXSetDispCopyYScale(); // [0x801215AC]
    r3 = *(uint8_t*)(&Rmode + 0x19);
    r6 = &Rmode + (50);
    r5 = 1;
    r4 = &Rmode + (26);
    r3 = GXSetCopyFilter(); // [0x801216DC]
    r4 = 0;
    r3 = 1;
    r3 = GXSetPixelFmt(); // [0x8012579C]
    r3 = 0;
    r3 = GXSetZCompLoc(); // [0x80125764]
    r3 = SDA1::pCurrent_buff;
    r4 = 0;
    r3 = GXCopyDisp(); // [0x80121920]
    r3 = 0;
    r3 = GXSetDispCopyGamma(); // [0x80121904]
    r3 = *(uint32_t*)(&pFrame_buff + 0x0);
    r3 = VISetNextFrameBuffer(); // [0x8010E6F8]
    r0 = *(uint32_t*)(0x8026E75Cu + 0x0);
    SDA1::pCurrent_buff = *(uint32_t*)(0x8026E75Cu + 0x0);
    r3 = VIFlush(); // [0x8010E5C8]
    r3 = VIWaitForRetrace(); // [0x8010D0F8]
    r0 = stack_0x2C;
    f31 = stack_0x20;
    return; // r3 = ret_8009D294
}

// ============================================================================
// High-Level AST Decompilation: Render_before(void)
// Unit: main_sub.obj | Address: 0x8009D2B0 | Size: 0x11C bytes
// ============================================================================
/* [0x8009D2B0] */ void Render_before(void) {
    // Stack frame allocated: 32 bytes
    stack_0x10 = f30;
    stack_0x18 = f31;
    stack_0x24 = r0;
    r11 = &Rmode;
    r0 = *(uint8_t*)(&Rmode + 0x18);
    if (*(uint8_t*)(&Rmode + 0x18) == 0) goto label_8009D344;
    r0 = *(uint16_t*)(&Rmode + 0x4);
    r7 = *(uint16_t*)(&Rmode + 0x6);
    stack_0x0C = *(uint16_t*)(&Rmode + 0x4);
    r10 = 0x80170000u;
    stack_0x08 = 0x43300000u;
    f0 = *(double*)0x8016BAF0;
    f30 = stack_0x08;
    stack_0x0C = *(uint16_t*)(&Rmode + 0x6);
    stack_0x08 = 0x43300000u;
    f31 = stack_0x08;
    r3 = VIGetNextField(); // [0x8010EA1C]
    f1 = *(float*)0x8016BAF8;
    f6 = *(float*)0x8016BAFC;
    r3 = GXSetViewportJitter(); // [0x80126230]
    goto label_8009D3A0;
label_8009D344:;
    r0 = *(uint16_t*)0x80170004;
    r5 = *(uint16_t*)0x80170006;
    stack_0x0C = *(uint16_t*)0x80170004;
    r11 = 0x80170000u;
    stack_0x08 = 0x43300000u;
    f0 = *(double*)0x8016BAF0;
    f3 = stack_0x08;
    stack_0x0C = *(uint16_t*)0x80170006;
    f1 = *(float*)0x8016BAF8;
    stack_0x08 = 0x43300000u;
    f6 = *(float*)0x8016BAFC;
    f4 = stack_0x08;
    r3 = GXSetViewport(); // [0x80126334]
label_8009D3A0:;
    r3 = GXInvalidateVtxCache(); // [0x8011F8F8]
    r3 = GXInvalidateTexAll(); // [0x80123748]
    f1 = *(float*)0x8016BB00;
    r3 = Bg_brightness_set(*(float*)0x8016BB00); // [0x8009D5A4]
    r0 = stack_0x24;
    f30 = stack_0x10;
    f31 = stack_0x18;
    return; // r3 = ret_8009D3B0
}

// ============================================================================
// High-Level AST Decompilation: Render_done(void)
// Unit: main_sub.obj | Address: 0x8009D3CC | Size: 0x160 bytes
// ============================================================================
/* [0x8009D3CC] */ void Render_done(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r4 = 3;
    r5 = 1;
    r3 = 1;
    r3 = GXSetZMode(); // [0x80125730]
    r3 = 1;
    r3 = GXSetColorUpdate(); // [0x801256D8]
    r3 = GXDrawDone(); // [0x80120300]
    r3 = 7;
    r3 = ExecOt(7); // [0x800DCCEC]
    r10 = SDA1::pG;
    r0 = *(int16_t*)(SDA1::pG + 0x681C);
    f0 = *(double*)0x8016BB08;
    stack_0x0C = *(int16_t*)(SDA1::pG + 0x681C);
    stack_0x08 = 0x43300000u;
    f1 = stack_0x08;
    r3 = Bg_brightness_set(stack_0x08); // [0x8009D5A4]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (r0 == 0) goto label_8009D4B8;
    r4 = 0;
    r3 = &Rmode;
    r5 = 0;
    r6 = 512;
    r7 = 448;
    r3 = ThpMovieDraw(&Rmode, 0, 0, 512, 448); // [0x800D6D10]
    if (ret_8009D454 == -1) goto label_8009D514;
    r3 = SDA1::pCurrent_buff;
    r4 = 1;
    r3 = GXCopyDisp(); // [0x80121920]
    r3 = ThpMovieDrawDone(); // [0x800D6DD4]
    r3 = SDA1::pCurrent_buff;
    r3 = VISetNextFrameBuffer(); // [0x8010E6F8]
    r9 = SDA1::pFrame_buff;
    r0 = SDA1::pCurrent_buff;
    if (SDA1::pCurrent_buff != SDA1::pFrame_buff) goto label_8009D494;
    r0 = *(uint32_t*)0x8026E75C;
    SDA1::pCurrent_buff = *(uint32_t*)0x8026E75C;
    goto label_8009D498;
label_8009D494:;
    SDA1::pCurrent_buff = SDA1::pFrame_buff;
label_8009D498:;
    r3 = VIFlush(); // [0x8010E5C8]
    r9 = SDA1::pG;
    r11 = SDA1::vsync_cnt;
    r0 = *(uint32_t*)(SDA1::pG + 0x11C);
    if (SDA1::vsync_cnt >= *(uint32_t*)(SDA1::pG + 0x11C)) goto label_8009D514;
    r3 = VIWaitForRetrace(); // [0x8010D0F8]
    goto label_8009D514;
label_8009D4B8:;
    r9 = *(uint32_t*)(SDA1::pG + 0x11C);
label_8009D4BC:;
    r0 = SDA1::vsync_cnt;
    if (SDA1::vsync_cnt < *(uint32_t*)(SDA1::pG + 0x11C)) goto label_8009D4BC;
    r3 = 1;
    r3 = GXSetAlphaUpdate(); // [0x80125704]
    r3 = SDA1::pCurrent_buff;
    r4 = 1;
    r3 = GXCopyDisp(); // [0x80121920]
    r3 = 0;
    r3 = GXSetAlphaUpdate(); // [0x80125704]
    r3 = GXDrawDone(); // [0x80120300]
    r3 = SDA1::pCurrent_buff;
    r3 = VISetNextFrameBuffer(); // [0x8010E6F8]
    r9 = SDA1::pFrame_buff;
    r0 = SDA1::pCurrent_buff;
    if (SDA1::pCurrent_buff != SDA1::pFrame_buff) goto label_8009D50C;
    r0 = *(uint32_t*)0x8026E75C;
    SDA1::pCurrent_buff = *(uint32_t*)0x8026E75C;
    goto label_8009D510;
label_8009D50C:;
    SDA1::pCurrent_buff = SDA1::pFrame_buff;
label_8009D510:;
    r3 = VIFlush(); // [0x8010E5C8]
label_8009D514:;
    r0 = 0;
    SDA1::vsync_cnt = 0;
    r0 = stack_0x14;
    return; // r3 = ret_8009D510
}

// ============================================================================
// High-Level AST Decompilation: Get_system_cnt(void)
// Unit: main_sub.obj | Address: 0x8009D52C | Size: 0x34 bytes
// ============================================================================
/* [0x8009D52C] */ void Get_system_cnt(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = VIGetRetraceCount(); // [0x8010E95C]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x120);
    r11 = *(uint32_t*)(SDA1::pG + 0x7204);
    r3 = (ret_8009D538 - *(uint32_t*)(SDA1::pG + 0x120));
    r3 = ((ret_8009D538 - *(uint32_t*)(SDA1::pG + 0x120)) + *(uint32_t*)(SDA1::pG + 0x7204));
    r0 = stack_0x0C;
    return; // r3 = ((ret_8009D538 - *(uint32_t*)(SDA1::pG + 0x120)) + *(uint32_t*)(SDA1::pG + 0x7204))
}

// ============================================================================
// High-Level AST Decompilation: Set_system_cnt(void)
// Unit: main_sub.obj | Address: 0x8009D560 | Size: 0x44 bytes
// ============================================================================
/* [0x8009D560] */ void Set_system_cnt(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = VIGetRetraceCount(); // [0x8010E95C]
    r9 = SDA1::pG;
    r11 = *(uint32_t*)(SDA1::pG + 0x120);
    r0 = *(uint32_t*)(SDA1::pG + 0x7204);
    r3 = (ret_8009D56C - *(uint32_t*)(SDA1::pG + 0x120));
    r0 = (*(uint32_t*)(SDA1::pG + 0x7204) + (ret_8009D56C - *(uint32_t*)(SDA1::pG + 0x120)));
    *(uint32_t*)(SDA1::pG + 0x7204) = (*(uint32_t*)(SDA1::pG + 0x7204) + (ret_8009D56C - *(uint32_t*)(SDA1::pG + 0x120)));
    r3 = VIGetRetraceCount(); // [0x8010E95C]
    r9 = SDA1::pG;
    *(uint32_t*)(SDA1::pG + 0x120) = ret_8009D588;
    r0 = stack_0x0C;
    return; // r3 = ret_8009D588
}

// ============================================================================
// High-Level AST Decompilation: Bg_brightness_set(float)
// Unit: main_sub.obj | Address: 0x8009D5A4 | Size: 0x54 bytes
// ============================================================================
/* [0x8009D5A4] */ void Bg_brightness_set(float arg0_f1) {
    // Stack frame allocated: 24 bytes
    r0 = *(uint32_t*)0x8016BB10;
    r11 = &stack_0x08;
    r9 = 0x8016BB10u;
    r10 = 0x8016BB17u;
    r4 = *(uint8_t*)(0x8016BB10u + 0x6);
    r7 = &stack_0x10;
    r5 = *(uint16_t*)(0x8016BB10u + 0x4);
    stack_0x08 = *(uint32_t*)0x8016BB10;
    r8 = *(uint32_t*)0x8016BB17;
    *(uint8_t*)(&stack_0x08 + 0x6) = *(uint8_t*)(0x8016BB10u + 0x6);
    *(uint16_t*)(&stack_0x08 + 0x4) = *(uint16_t*)(0x8016BB10u + 0x4);
    r0 = *(uint8_t*)(0x8016BB17u + 0x6);
    r9 = *(uint16_t*)(0x8016BB17u + 0x4);
    stack_0x10 = *(uint32_t*)0x8016BB17;
    *(uint8_t*)(&stack_0x10 + 0x6) = *(uint8_t*)(0x8016BB17u + 0x6);
    *(uint16_t*)(&stack_0x10 + 0x4) = *(uint16_t*)(0x8016BB17u + 0x4);
    return; // r3 = r3
}

// ============================================================================
// High-Level AST Decompilation: Flg_on(unsigned long *, unsigned long)
// Unit: main_sub.obj | Address: 0x8009D5F8 | Size: 0x20 bytes
// ============================================================================
/* [0x8009D5F8] */ void Flg_on(unsigned long * arg0_r3, unsigned long arg1_r4) {
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: Flg_off(unsigned long *, unsigned long)
// Unit: main_sub.obj | Address: 0x8009D618 | Size: 0x20 bytes
// ============================================================================
/* [0x8009D618] */ void Flg_off(unsigned long * arg0_r3, unsigned long arg1_r4) {
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: Flg_ck(unsigned long *, unsigned long)
// Unit: main_sub.obj | Address: 0x8009D638 | Size: 0x1C bytes
// ============================================================================
/* [0x8009D638] */ void Flg_ck(unsigned long * arg0_r3, unsigned long arg1_r4) {
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: Flg_xor(unsigned long *, unsigned long)
// Unit: main_sub.obj | Address: 0x8009D654 | Size: 0x20 bytes
// ============================================================================
/* [0x8009D654] */ void Flg_xor(unsigned long * arg0_r3, unsigned long arg1_r4) {
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: SystemResetCheck(void)
// Unit: main_sub.obj | Address: 0x8009D674 | Size: 0x124 bytes
// ============================================================================
/* [0x8009D674] */ void SystemResetCheck(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if (r0 != 0) goto label_8009D6AC;
    r3 = OSGetResetButtonState(); // [0x800F6920]
    if (ret_8009D690 != 1) goto label_8009D6AC;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    *(uint32_t*)(SDA1::pG + 0x124) = *(uint32_t*)(SDA1::pG + 0x124);
label_8009D6AC:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if (ret_8009D690 == 1) goto label_8009D6D8;
    r3 = OSGetResetButtonState(); // [0x800F6920]
    if (ret_8009D6BC != 0) goto label_8009D6D8;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    *(uint32_t*)(SDA1::pG + 0x124) = *(uint32_t*)(SDA1::pG + 0x124);
label_8009D6D8:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if (ret_8009D6BC == 0) goto label_8009D720;
    if (ret_8009D6BC != 0) goto label_8009D720;
    r3 = 1;
    r3 = VISetBlack(); // [0x8010E7E0]
    r3 = VIFlush(); // [0x8010E5C8]
    r3 = VIWaitForRetrace(); // [0x8010D0F8]
    r3 = GXDrawDone(); // [0x80120300]
    r3 = PADRecalibrate(); // [0x8010FF10]
    r3 = 0;
    r4 = 0;
    r5 = 1;
    r3 = OSResetSystem(); // [0x800F6500]
    goto label_8009D788;
label_8009D720:;
    r0 = *(uint32_t*)0x8019E030;
    if (*(uint32_t*)0x8019E030 != 5632) goto label_8009D76C;
    r10 = SDA1::pG;
    r11 = *(uint32_t*)(SDA1::pG + 0x124);
    if (*(uint32_t*)0x8019E030 != 5632) goto label_8009D76C;
    r0 = SDA1::Soft_reset_cnt;
    r9 = *(uint32_t*)(SDA1::pG + 0x11C);
    r0 = (SDA1::Soft_reset_cnt + *(uint32_t*)(SDA1::pG + 0x11C));
    SDA1::Soft_reset_cnt = (SDA1::Soft_reset_cnt + *(uint32_t*)(SDA1::pG + 0x11C));
    if ((SDA1::Soft_reset_cnt + *(uint32_t*)(SDA1::pG + 0x11C)) <= 0x3Cu) goto label_8009D774;
    *(uint32_t*)(SDA1::pG + 0x124) = (SDA1::Soft_reset_cnt + *(uint32_t*)(SDA1::pG + 0x11C));
    SDA1::Soft_reset_cnt = r8;
    goto label_8009D774;
label_8009D76C:;
    r0 = 0;
    SDA1::Soft_reset_cnt = 0;
label_8009D774:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if ((SDA1::Soft_reset_cnt + *(uint32_t*)(SDA1::pG + 0x11C)) == 0x3Cu) goto label_8009D788;
    r3 = systemSoftReset(); // [0x8009D798]
label_8009D788:;
    r0 = stack_0x0C;
    return; // r3 = ret_8009D784
}

// ============================================================================
// High-Level AST Decompilation: systemSoftReset(void)
// Unit: main_sub.obj | Address: 0x8009D798 | Size: 0xE0 bytes
// ============================================================================
/* [0x8009D798] */ void systemSoftReset(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = 1;
    r3 = VISetBlack(); // [0x8010E7E0]
    r3 = VIFlush(); // [0x8010E5C8]
    r3 = VIWaitForRetrace(); // [0x8010D0F8]
    r3 = GXDrawDone(); // [0x80120300]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (r0 == 0) goto label_8009D7CC;
    r3 = ThpMovieClose(); // [0x800D5CF0]
label_8009D7CC:;
    r3 = VibSetClear(); // [0x800AD4C4]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if (r0 != 0) goto label_8009D800;
    r3 = DVDCheckDisk(); // [0x8010A2D8]
    if (ret_8009D7E0 != 0) goto label_8009D800;
    r3 = 1;
    r4 = 0;
    r5 = 0;
    r3 = OSResetSystem(); // [0x800F6500]
    goto label_8009D868;
label_8009D800:;
    r3 = ResetDebugAlloc(); // [0x8009CD98]
    r3 = Snd_soft_reset_req(); // [0x801394EC]
    goto label_8009D814;
label_8009D80C:;
    r3 = SndWatcher(); // [0x800CBFB8]
    r3 = VIWaitForRetrace(); // [0x8010D0F8]
label_8009D814:;
    r3 = Snd_soft_reset_ck(); // [0x80139504]
    if (ret_8009D814 != 0) goto label_8009D80C;
    r4 = 0;
    r3 = 0;
    r3 = Snd_efx_req(); // [0x80136F3C]
    r3 = SndWatcher(); // [0x800CBFB8]
    r3 = DvdAllReset(); // [0x8007B670]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if (ret_8009D814 != 0) goto label_8009D84C;
    r3 = PADRecalibrate(); // [0x8010FF10]
label_8009D84C:;
    r9 = SDA1::pG;
    r11 = 1;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    *(uint32_t*)(SDA1::pG + 0xFC) = 1;
    *(uint32_t*)(SDA1::pG + 0x124) = *(uint32_t*)(SDA1::pG + 0x124);
label_8009D868:;
    r0 = stack_0x0C;
    return; // r3 = ret_8009D848
}

// ============================================================================
// High-Level AST Decompilation: Progressive_set(long, long)
// Unit: main_sub.obj | Address: 0x8009D878 | Size: 0xD8 bytes
// ============================================================================
/* [0x8009D878] */ void Progressive_set(long arg0_r3, long arg1_r4) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r28 = arg0_r3;
    r30 = arg1_r4 + (2);
    r3 = 1;
    r3 = VISetBlack(); // [0x8010E7E0]
    r31 = &Rmode;
    r3 = VIFlush(); // [0x8010E5C8]
    r3 = VIWaitForRetrace(); // [0x8010D0F8]
    if (arg0_r3 == 0) goto label_8009D8E0;
    r3 = 1;
    r3 = OSSetProgressiveMode(); // [0x800F7DFC]
    r9 = 2;
    r0 = 0;
    Rmode = 2;
    r10 = 20;
    r11 = 24;
    *(uint8_t*)(&Rmode + 0x36) = 20;
    *(uint8_t*)(&Rmode + 0x35) = 24;
    *(uint8_t*)(&Rmode + 0x38) = 0;
    *(uint32_t*)(&Rmode + 0x14) = 0;
    goto label_8009D90C;
label_8009D8E0:;
    r3 = 0;
    r3 = OSSetProgressiveMode(); // [0x800F7DFC]
    Rmode = arg0_r3;
    r0 = 8;
    r10 = 10;
    r9 = 1;
    r11 = 12;
    *(uint32_t*)(&Rmode + 0x14) = 1;
    *(uint8_t*)(&Rmode + 0x35) = 12;
    *(uint8_t*)(&Rmode + 0x36) = 10;
    *(uint8_t*)(&Rmode + 0x38) = 8;
label_8009D90C:;
    *(uint8_t*)(&Rmode + 0x32) = 8;
    *(uint8_t*)(&Rmode + 0x33) = 8;
    *(uint8_t*)(&Rmode + 0x34) = 10;
    *(uint8_t*)(&Rmode + 0x37) = 8;
    r3 = &Rmode;
    r3 = VIConfigure(); // [0x8010DA0C]
    r3 = VIFlush(); // [0x8010E5C8]
    goto label_8009D930;
label_8009D92C:;
    r3 = VIWaitForRetrace(); // [0x8010D0F8]
label_8009D930:;
    r30 = (arg1_r4 + 2) + (-1);
    if ((arg1_r4 + 2) != 0) goto label_8009D92C;
    r0 = stack_0x1C;
    return; // r3 = ret_8009D92C
}

// ============================================================================
// High-Level AST Decompilation: Buff_alarm_set(void)
// Unit: main_sub.obj | Address: 0x8009D950 | Size: 0x74 bytes
// ============================================================================
/* [0x8009D950] */ void Buff_alarm_set(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r3 = &Buff_alarm;
    r3 = OSCreateAlarm(); // [0x800F01C4]
    r3 = OSGetTime(); // [0x800FA6A0]
    r0 = *(uint32_t*)0x800000F8;
    r9 = 0x431BDE83u;
    r5 = ret_8009D96C;
    r6 = r4;
    r3 = &Buff_alarm;
    r9 = &Buff_alarm_handler(OSAlarm *, OSContext *);
    r8 = *(uint32_t*)0x800000F8;
    r7 = 0;
    r3 = OSSetPeriodicAlarm(); // [0x800F04FC]
    r0 = stack_0x14;
    return; // r3 = ret_8009D9AC
}

// ============================================================================
// High-Level AST Decompilation: Buff_alarm_handler(OSAlarm *, OSContext *)
// Unit: main_sub.obj | Address: 0x8009D9C4 | Size: 0x10 bytes
// ============================================================================
/* [0x8009D9C4] */ void Buff_alarm_handler(OSAlarm * arg0_r3, OSContext * arg1_r4) {
    r9 = SDA1::vsync_cnt;
    r9 = SDA1::vsync_cnt + (1);
    SDA1::vsync_cnt = (SDA1::vsync_cnt + 1);
    return; // r3 = arg0_r3
}
