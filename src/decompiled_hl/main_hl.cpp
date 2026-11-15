// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: main.obj
// Functions Decompiled: 5
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: main
// Unit: main.obj | Address: 0x8009C4DC | Size: 0xB0 bytes
// ============================================================================
/* [0x8009C4DC] */ void main(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = __main(); // [0x800ED768]
    r9 = &Global;
    SDA1::pG = &Global;
    r3 = systemStartInit(); // [0x8009C5B8]
label_8009C4FC:;
    r3 = systemRestartInit(); // [0x8009C65C]
    r3 = 0;
    r4 = &Title_task(void);
    r3 = TaskExec(0, &Title_task(void)); // [0x800A1B08]
label_8009C510:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (r0 != 0) goto label_8009C568;
    r3 = Render_before(); // [0x8009D2B0]
    r3 = PadRead(); // [0x800ACC2C]
    r3 = Render(); // [0x800D9D10]
    r3 = FlipTransBuffer(); // [0x8009D00C]
    r3 = ClearOt(); // [0x800DC780]
    r11 = SDA1::pG;
    r9 = *(uint32_t*)(SDA1::pG + 0x7200);
    r9 = *(uint32_t*)(SDA1::pG + 0x7200) + (1);
    *(uint32_t*)(SDA1::pG + 0x7200) = (*(uint32_t*)(SDA1::pG + 0x7200) + 1);
    r3 = Scheduler(); // [0x800A18E4]
    r3 = Trans(); // [0x800D91CC]
    r3 = FadeControl(); // [0x80094480]
    r3 = CinescoMove(); // [0x800731DC]
    r3 = DvdControl(); // [0x8007B9BC]
    r3 = SndWatcher(); // [0x800CBFB8]
    r3 = EprintfFlush(); // [0x80081BE0]
    r3 = Render_done(); // [0x8009D3CC]
    goto label_8009C574;
label_8009C568:;
    r3 = PadRead(); // [0x800ACC2C]
    r3 = ThpMovieWait(); // [0x800D78AC]
    r3 = DvdErrCheck(); // [0x8007BD5C]
label_8009C574:;
    r3 = SystemResetCheck(); // [0x8009D674]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if (r0 != 0) goto label_8009C4FC;
    goto label_8009C510;
}

// ============================================================================
// High-Level AST Decompilation: postVSyncCallback(unsigned long)
// Unit: main.obj | Address: 0x8009C58C | Size: 0x2C bytes
// ============================================================================
/* [0x8009C58C] */ void postVSyncCallback(unsigned long arg0_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = SDA1::vsync_cnt;
    r9 = SDA1::vsync_cnt + (1);
    SDA1::vsync_cnt = (SDA1::vsync_cnt + 1);
    r3 = Rnd(); // [0x800C06C4]
    r0 = stack_0x0C;
    return; // r3 = ret_8009C5A4
}

// ============================================================================
// High-Level AST Decompilation: systemStartInit(void)
// Unit: main.obj | Address: 0x8009C5B8 | Size: 0xA4 bytes
// ============================================================================
/* [0x8009C5B8] */ void systemStartInit(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = SDA1::pG;
    r4 = 0;
    r5 = 31936;
    r3 = memset(); // [0x800E8A5C]
    r3 = OSInit(); // [0x800EF76C]
    r3 = OSInitAlarm(); // [0x800F0178]
    r3 = VIInit(); // [0x8010CC48]
    r3 = &postVSyncCallback(unsigned long);
    r3 = VISetPostRetraceCallback(); // [0x8010C7C8]
    r3 = LCEnable(); // [0x800F1BEC]
    r3 = DvdInit(); // [0x8007B5D4]
    r3 = CARDInit(); // [0x80115508]
    r3 = 4;
    r3 = 5;
    r3 = 6;
    r3 = 7;
    r3 = RenderInit(); // [0x800D9CF0]
    r3 = SystemMemInit(); // [0x8009C958]
    r3 = SchedulerInit(); // [0x800A1800]
    r3 = RndInit(); // [0x800C06B8]
    r3 = Render_init(); // [0x8009D098]
    r3 = SndInit(); // [0x800CB2D4]
    r3 = EprintfInit(); // [0x80081C04]
    r3 = 1;
    r3 = EprintfSetCurrentNo(1); // [0x800817D0]
    r0 = stack_0x0C;
    return; // r3 = ret_8009C648
}

// ============================================================================
// High-Level AST Decompilation: systemRestartInit(void)
// Unit: main.obj | Address: 0x8009C65C | Size: 0x11C bytes
// ============================================================================
/* [0x8009C65C] */ void systemRestartInit(void) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r3 = PadInit(); // [0x800ACBEC]
    r3 = SDA1::pG;
    r5 = 31680;
    r4 = 0;
    r3 = SDA1::pG + (256);
    r3 = memset(); // [0x800E8A5C]
    r3 = SDA1::pMainMem.1080;
    r3 = MemAllocReplace(SDA1::pMainMem.1080, 0x817E0000u); // [0x8009CA78]
    SDA1::pMainMem.1080 = ret_8009C68C;
    r3 = SoundAllocInit(); // [0x8009CC94]
    r3 = systemWorkInit(); // [0x8009C778]
    r3 = PrimBuffInit(); // [0x8009CFD8]
    r3 = SchedulerTaskInit(); // [0x800A18A8]
    r3 = InitOt(); // [0x800DC718]
    r3 = SndInit2(); // [0x800CB360]
    r3 = FadeInit(); // [0x80094410]
    r3 = CinescoInit(); // [0x80073660]
    r3 = EmInit(); // [0x8007C478]
    r3 = ObjInit(); // [0x80074550]
    r3 = LightInit(); // [0x8009A000]
    r3 = EspInit(); // [0x800826A4]
    r3 = EspgenInit(); // [0x8008E228]
    r3 = FilterInit(); // [0x80094EB4]
    r3 = BltInit(); // [0x8000AE30]
    r0 = 0;
    cId = 0;
    r11 = &cId;
    *(uint32_t*)(&cId + 0xC) = 0;
    r10 = 0;
    r0 = 10;
    r9 = &cId + (16);
label_8009C6F4:;
    *(uint32_t*)((&cId + 16) + 0x28) = 0;
    *(uint32_t*)((&cId + 16) + 0x0) = 0;
    r9 = (&cId + 16) + (4);
    if (r0 >= 0) goto label_8009C6F4;
    r31 = 0;
    r30 = &cMes;
label_8009C710:;
    r4 = 0;
    r3 = &cMes;
    r3 = CMesCtrl::MesClear(&cMes, 0); // [0x8009F208]
    r31 = 0 + (1);
    if ((0 + 1) <= 4) goto label_8009C710;
    r3 = &cGaugeWk;
    r3 = cGauge::GaugeInit(&cGaugeWk); // [0x80096F10]
    r3 = &cCockpit;
    r3 = cCockpitWk::CockpitInit(&cCockpit); // [0x800753D4]
    r0 = SDA1::myBgColor;
    r3 = &stack_0x08;
    r4 = 0x00FFFFFFu;
    stack_0x08 = SDA1::myBgColor;
    r3 = GXSetCopyClear(); // [0x80121674]
    r3 = SDA1::pCurrent_buff;
    r4 = 1;
    r3 = GXCopyDisp(); // [0x80121920]
    r0 = stack_0x1C;
    return; // r3 = ret_8009C760
}

// ============================================================================
// High-Level AST Decompilation: systemWorkInit(void)
// Unit: main.obj | Address: 0x8009C778 | Size: 0x150 bytes
// ============================================================================
/* [0x8009C778] */ void systemWorkInit(void) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    f10 = *(float*)0x8016BA74;
    r8 = 0;
    f9 = *(float*)0x8016BA78;
    r0 = 2;
    f11 = *(float*)0x8016BA7C;
    f12 = *(float*)0x8016BA80;
    r30 = &Rmode;
    f13 = *(float*)0x8016BA84;
    r31 = 1;
    f0 = *(float*)0x8016BA88;
    r7 = -1;
    r10 = SDA1::pG;
    r6 = 64;
    SDA1::ZNEAR = *(float*)0x8016BA74;
    r29 = 0;
    SDA1::ZFAR = *(float*)0x8016BA78;
    SDA1::ORTHO_T = *(float*)0x8016BA7C;
    SDA1::ORTHO_B = *(float*)0x8016BA80;
    SDA1::ORTHO_L = *(float*)0x8016BA84;
    SDA1::ORTHO_R = *(float*)0x8016BA88;
    SDA1::Soft_reset_cnt = 0;
    *(uint32_t*)(SDA1::pG + 0x11C) = 2;
    *(uint32_t*)(SDA1::pG + 0x7C94) = 0;
    *(uint32_t*)(SDA1::pG + 0x7C98) = 0;
    r0 = *(int16_t*)(&Rmode + 0x4);
    *(uint32_t*)(SDA1::pG + 0x7C9C) = *(int16_t*)(&Rmode + 0x4);
    r11 = *(int16_t*)(&Rmode + 0x6);
    *(uint8_t*)(SDA1::pG + 0x7C8C) = 1;
    *(uint32_t*)(SDA1::pG + 0x7CA0) = *(int16_t*)(&Rmode + 0x6);
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x7C8D) = -1;
    r11 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x681E) = 1;
    *(uint16_t*)(SDA1::pG + 0x6A78) = 0;
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x681B) = 1;
    r11 = SDA1::pG;
    *(uint16_t*)(SDA1::pG + 0x681C) = 64;
    r3 = OSGetSoundMode(); // [0x800F7C68]
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x10E) = ret_8009C83C;
    r3 = Snd_get_sound_mode(); // [0x801392DC]
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x6A90) = ret_8009C848;
    r9 = SDA1::pG;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A90);
    if (*(uint8_t*)(SDA1::pG + 0x6A90) != 1) goto label_8009C868;
    *(uint8_t*)(SDA1::pG + 0x6A90) = 0;
label_8009C868:;
    r9 = SDA1::pG;
    r0 = 100;
    *(uint8_t*)(SDA1::pG + 0x6A8E) = 100;
    r3 = "width = %d\n";
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x6A8F) = 100;
    r11 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x6A91) = 0;
    r9 = SDA1::pG;
    *(uint8_t*)(SDA1::pG + 0x6A92) = 1;
    r4 = *(uint16_t*)(&Rmode + 0x4);
    r3 = OSReport(); // [0x800F2D80]
    r4 = *(uint16_t*)(&Rmode + 0x6);
    r3 = "height = %d\n";
    r3 = OSReport(); // [0x800F2D80]
    r0 = stack_0x1C;
    return; // r3 = ret_8009C8B0
}
