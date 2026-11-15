// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: trans.obj
// Functions Decompiled: 28
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: Trans(void)
// Unit: trans.obj | Address: 0x800D91CC | Size: 0x3E4 bytes
// ============================================================================
/* [0x800D91CC] */ void Trans(void) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x128);
    if (*(uint32_t*)(SDA1::pG + 0x128) < 0) goto label_800D930C;
    r3 = *(uint32_t*)(SDA1::pG + 0x144);
    if (*(uint32_t*)(SDA1::pG + 0x144) == 0) goto label_800D930C;
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r29 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    if (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) == *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4)) goto label_800D930C;
label_800D920C:;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xF4);
    if (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) == *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4)) goto label_800D92DC;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0x4B8);
    r4 = 2;
    r31 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + (4);
    r3 = *(int16_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0x4B8) + 0x8);
    r0 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0x4B8) + 0xC);
    r3 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + *(int16_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0x4B8) + 0x8));
    return; // r3 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + *(int16_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0x4B8) + 0x8))
    r8 = &heap_em;
    r11 = 0;
    r10 = *(uint32_t*)(&heap_em + 0x4);
    r3 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r9 = heap_em;
    if (0 >= *(uint32_t*)(&heap_em + 0x4)) goto label_800D9278;
label_800D925C:;
    r0 = heap_em;
    r9 = heap_em + (4096);
    if (heap_em == *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0)) goto label_800D92B8;
    r11 = 0 + (1);
    if ((0 + 1) < *(uint32_t*)(&heap_em + 0x4)) goto label_800D925C;
label_800D9278:;
    r3 = __builtin_delete(); // [0x8009C908]
label_800D927C:;
    r9 = SDA1::pG;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 4) == *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4)) goto label_800D92A8;
    if (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) == (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 4)) goto label_800D92A8;
    r4 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 4);
    r3 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 4));
    r3 = memmove(); // [0x800E8970]
label_800D92A8:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) + (-4);
    *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) + -4);
    goto label_800D92F8;
label_800D92B8:;
    r8 = *(uint32_t*)(&heap_em + 0x8);
    goto label_800D927C;
label_800D92DC:;
    r9 = *(uint32_t*)((0 + 1) + 0x4B8);
    r29 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + (4);
    r3 = *(int16_t*)(*(uint32_t*)((0 + 1) + 0x4B8) + 0x38);
    r0 = *(uint32_t*)(*(uint32_t*)((0 + 1) + 0x4B8) + 0x3C);
    r3 = ((0 + 1) + *(int16_t*)(*(uint32_t*)((0 + 1) + 0x4B8) + 0x38));
    return; // r3 = ((0 + 1) + *(int16_t*)(*(uint32_t*)((0 + 1) + 0x4B8) + 0x38))
label_800D92F8:;
    r9 = SDA1::pG;
    r11 = *(uint32_t*)(SDA1::pG + 0x144);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 4) != *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4)) goto label_800D920C;
label_800D930C:;
    r0 = *(uint32_t*)(SDA1::pG + 0x128);
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 4) != *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4)) goto label_800D9438;
    r3 = *(uint32_t*)(SDA1::pG + 0x140);
    if (*(uint32_t*)(SDA1::pG + 0x140) == 0) goto label_800D9438;
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4);
    r29 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0);
    if (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) == *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4)) goto label_800D9438;
label_800D9338:;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 0x0) + 0xF4);
    if (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) == *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4)) goto label_800D9408;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 0x0) + 0x4B8);
    r4 = 2;
    r31 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + (4);
    r3 = *(int16_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 0x0) + 0x4B8) + 0x8);
    r0 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 0x0) + 0x4B8) + 0xC);
    r3 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 0x0) + *(int16_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 0x0) + 0x4B8) + 0x8));
    return; // r3 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 0x0) + *(int16_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 0x0) + 0x4B8) + 0x8))
    r8 = &heap_obj;
    r11 = 0;
    r10 = *(uint32_t*)(&heap_obj + 0x4);
    r3 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 0x0);
    r9 = heap_obj;
    if (0 >= *(uint32_t*)(&heap_obj + 0x4)) goto label_800D93A4;
label_800D9388:;
    r0 = heap_obj;
    r9 = heap_obj + (1536);
    if (heap_obj == *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 0x0)) goto label_800D93E4;
    r11 = 0 + (1);
    if ((0 + 1) < *(uint32_t*)(&heap_obj + 0x4)) goto label_800D9388;
label_800D93A4:;
    r3 = __builtin_delete(); // [0x8009C908]
label_800D93A8:;
    r9 = SDA1::pG;
    r30 = *(uint32_t*)(SDA1::pG + 0x140);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4);
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 4) == *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4)) goto label_800D93D4;
    if (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4) == (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 4)) goto label_800D93D4;
    r4 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 4);
    r3 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4) - (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 4));
    r3 = memmove(); // [0x800E8970]
label_800D93D4:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4) + (-4);
    *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4) = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4) + -4);
    goto label_800D9424;
label_800D93E4:;
    r8 = *(uint32_t*)(&heap_obj + 0x8);
    goto label_800D93A8;
label_800D9408:;
    r9 = *(uint32_t*)((0 + 1) + 0x4B8);
    r29 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + (4);
    r3 = *(int16_t*)(*(uint32_t*)((0 + 1) + 0x4B8) + 0x38);
    r0 = *(uint32_t*)(*(uint32_t*)((0 + 1) + 0x4B8) + 0x3C);
    r3 = ((0 + 1) + *(int16_t*)(*(uint32_t*)((0 + 1) + 0x4B8) + 0x38));
    return; // r3 = ((0 + 1) + *(int16_t*)(*(uint32_t*)((0 + 1) + 0x4B8) + 0x38))
label_800D9424:;
    r9 = SDA1::pG;
    r11 = *(uint32_t*)(SDA1::pG + 0x140);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4);
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 4) != *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4)) goto label_800D9338;
label_800D9438:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x128);
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 4) != *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4)) goto label_800D9450;
    r3 = EspTrans(); // [0x80083A40]
    r3 = EspgenTrans(); // [0x8008E778]
label_800D9450:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x128);
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 4) != *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4)) goto label_800D9464;
    r3 = Draw_cinesco(); // [0x80073348]
label_800D9464:;
    r11 = SDA1::pG;
    r31 = &CountDown;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 4) == *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4)) goto label_800D9584;
    r0 = *(uint32_t*)(SDA1::pG + 0x14C);
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 4) != *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4)) goto label_800D9584;
    r0 = *(uint32_t*)(SDA1::pG + 0x128);
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 4) != *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4)) goto label_800D9584;
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x0) + 4) != *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x140) + 0x4)) goto label_800D9584;
    r0 = *(uint32_t*)(&CountDown + 0x1C);
    if (*(uint32_t*)(&CountDown + 0x1C) == 0) goto label_800D9584;
    r11 = *(uint32_t*)(&CountDown + 0x20);
    r5 = 0x91A2B3C5u;
    r30 = 0x88888889u;
    r3 = &CountDown;
    r29 = 0x66666667u;
    r4 = 2;
    r5 = (0x91A2B3C5u + *(uint32_t*)(&CountDown + 0x20));
    r6 = 2;
    r7 = 1;
    r5 = ((0x91A2B3C5u + *(uint32_t*)(&CountDown + 0x20)) - *(uint32_t*)(&CountDown + 0x1C));
    r8 = 0;
    r11 = (*(uint32_t*)(&CountDown + 0x20) - *(uint32_t*)(&CountDown + 0x1C));
    r30 = (0x88888889u + (*(uint32_t*)(&CountDown + 0x20) - *(uint32_t*)(&CountDown + 0x1C)));
    r30 = ((0x88888889u + (*(uint32_t*)(&CountDown + 0x20) - *(uint32_t*)(&CountDown + 0x1C))) - *(uint32_t*)(&CountDown + 0x1C));
    r11 = ((*(uint32_t*)(&CountDown + 0x20) - *(uint32_t*)(&CountDown + 0x1C)) - 0x801D0000u);
    r0 = (*(uint32_t*)(&CountDown + 0x1C) + ((*(uint32_t*)(&CountDown + 0x20) - *(uint32_t*)(&CountDown + 0x1C)) - 0x801D0000u));
    r29 = (0x66666667u - (*(uint32_t*)(&CountDown + 0x1C) + ((*(uint32_t*)(&CountDown + 0x20) - *(uint32_t*)(&CountDown + 0x1C)) - 0x801D0000u)));
    r3 = cIdMain::SetNumber(&CountDown, 2, ((0x91A2B3C5u + *(uint32_t*)(&CountDown + 0x20)) - *(uint32_t*)(&CountDown + 0x1C)), 2, 1, 0); // [0x800730E8]
    r5 = ((0x88888889u + (*(uint32_t*)(&CountDown + 0x20) - *(uint32_t*)(&CountDown + 0x1C))) - *(uint32_t*)(&CountDown + 0x1C));
    r3 = &CountDown;
    r4 = 4;
    r6 = 2;
    r7 = 1;
    r8 = 0;
    r3 = cIdMain::SetNumber(&CountDown, 4, ((0x88888889u + (*(uint32_t*)(&CountDown + 0x20) - *(uint32_t*)(&CountDown + 0x1C))) - *(uint32_t*)(&CountDown + 0x1C)), 2, 1, 0); // [0x800730E8]
    r3 = &CountDown;
    r5 = (0x66666667u - (*(uint32_t*)(&CountDown + 0x1C) + ((*(uint32_t*)(&CountDown + 0x20) - *(uint32_t*)(&CountDown + 0x1C)) - 0x801D0000u)));
    r4 = 6;
    r6 = 2;
    r7 = 1;
    r8 = 0;
    r3 = cIdMain::SetNumber(&CountDown, 6, (0x66666667u - (*(uint32_t*)(&CountDown + 0x1C) + ((*(uint32_t*)(&CountDown + 0x20) - *(uint32_t*)(&CountDown + 0x1C)) - 0x801D0000u))), 2, 1, 0); // [0x800730E8]
    r9 = *(uint32_t*)(&CountDown + 0x18);
    r4 = 0;
    r5 = -1;
    r3 = *(int16_t*)(*(uint32_t*)(&CountDown + 0x18) + 0x8);
    r0 = *(uint32_t*)(*(uint32_t*)(&CountDown + 0x18) + 0xC);
    r3 = (*(int16_t*)(*(uint32_t*)(&CountDown + 0x18) + 0x8) + &CountDown);
    return; // r3 = (*(int16_t*)(*(uint32_t*)(&CountDown + 0x18) + 0x8) + &CountDown)
label_800D9584:;
    r3 = &cGaugeWk;
    r3 = cGauge::GaugeTrans(&cGaugeWk); // [0x8009701C]
    r3 = &cCockpit;
    r3 = cCockpitWk::CockpitTrans(&cCockpit); // [0x800754D8]
    r0 = stack_0x1C;
    return; // r3 = ret_800D9598
}

// ============================================================================
// High-Level AST Decompilation: commonScreenMat(tagCOMN *)
// Unit: trans.obj | Address: 0x800D95B0 | Size: 0x50 bytes
// ============================================================================
/* [0x800D95B0] */ void commonScreenMat(tagCOMN * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r31 = arg0_r3;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    if (r0 == 0) goto label_800D95EC;
    r4 = *(uint32_t*)(arg0_r3 + 0x130);
    r3 = commonScreenMatSub(arg0_r3, *(uint32_t*)(arg0_r3 + 0x130)); // [0x800D9600]
    r4 = *(uint32_t*)(arg0_r3 + 0x134);
    if (*(uint32_t*)(arg0_r3 + 0x134) == 0) goto label_800D95EC;
    r3 = arg0_r3;
    r3 = commonScreenMatSub(arg0_r3, *(uint32_t*)(arg0_r3 + 0x134)); // [0x800D9600]
label_800D95EC:;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_800D95E8
}

// ============================================================================
// High-Level AST Decompilation: commonScreenMatSub(tagCOMN *, cModelInfo *)
// Unit: trans.obj | Address: 0x800D9600 | Size: 0x2D0 bytes
// ============================================================================
/* [0x800D9600] */ void commonScreenMatSub(tagCOMN * arg0_r3, cModelInfo * arg1_r4) {
    // Stack frame allocated: 144 bytes
    stack_0x94 = r0;
    r30 = *(uint32_t*)(arg0_r3 + 0xF0);
    r28 = arg1_r4;
    r31 = SDA1::pG;
    r4 = &stack_0x08;
    r3 = *(uint32_t*)(arg0_r3 + 0xF0);
    r3 = PSMTXInverse(); // [0x80100A94]
    if (*(uint32_t*)(arg0_r3 + 0xF0) == 0) goto label_800D98B4;
    r29 = SDA1::pG + (1084);
    r31 = &stack_0x38;
label_800D9638:;
    r3 = &stack_0x08;
    r4 = *(uint32_t*)(arg0_r3 + 0xF0);
    r5 = &stack_0x38;
    r3 = PSMTXConcat(); // [0x80100470]
    r4 = *(uint32_t*)(arg0_r3 + 0xF0) + (280);
    r5 = (SDA1::pG + 1084);
    r3 = &stack_0x38;
    r29 = (SDA1::pG + 1084) + (48);
    r3 = PSMTXConcat(); // [0x80100470]
    r3 = SDA1::pG;
    r4 = *(uint32_t*)(arg0_r3 + 0xF0);
    r5 = *(uint32_t*)(arg0_r3 + 0xF0) + (96);
    r3 = SDA1::pG + (852);
    r3 = PSMTXConcat(); // [0x80100470]
    r30 = *(uint32_t*)(*(uint32_t*)(arg0_r3 + 0xF0) + 0xF0);
    if (*(uint32_t*)(*(uint32_t*)(arg0_r3 + 0xF0) + 0xF0) != 0) goto label_800D9638;
    goto label_800D98B4;
label_800D9680:;
    r27 = *(uint32_t*)(arg1_r4 + 0x9C);
    r0 = *(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18);
    if (*(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18) != 1) goto label_800D969C;
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    if (*(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18) == 1) goto label_800D98B0;
label_800D969C:;
    r0 = *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x38);
    r3 = r9 + (31);
    r3 = GetPrimBuff((r9 + 31)); // [0x8009D048]
    r3 = ret_800D96AC;
    if (*(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18) == 1) goto label_800D98BC;
    r9 = SDA1::pG;
    r11 = arg1_r4 + (96);
    r24 = (arg1_r4 + 96);
    r0 = *(uint32_t*)(SDA1::pG + 0x108);
    r9 = *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x3A);
    r3 = *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x3A) + (31);
    r3 = GetPrimBuff((*(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x3A) + 31)); // [0x8009D048]
    r3 = ret_800D96E0;
    if (*(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18) == 1) goto label_800D98BC;
    r11 = SDA1::pG;
    r9 = arg1_r4 + (104);
    r22 = (arg1_r4 + 104);
    r0 = *(uint32_t*)(SDA1::pG + 0x108);
    r4 = *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x2A);
    if (*(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x2A) <= 0xFFu) goto label_800D9724;
    r3 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x14);
    r23 = &aaaa;
    r3 = MakeWeightPaletteExt(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x14), *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x2A)); // [0x800D98D0]
    goto label_800D9734;
label_800D9724:;
    r3 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x14);
    r4 = *(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18);
    r3 = MakeWeightPalette(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x14), *(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18)); // [0x800D9AE8]
label_800D9734:;
    r3 = *(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x28);
    r3 = *(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x28) | 0x0007u;
    r3 = setupGQR6(*(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x28)); // [0x800DB628]
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    r31 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30);
    if (*(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x2A) == 0xFFu) goto label_800D97C8;
    r9 = SDA1::pG;
    r29 = 0;
    r25 = arg1_r4 + (116);
    r30 = arg1_r4 + (112);
    r0 = *(uint32_t*)(SDA1::pG + 0x108);
    r26 = 0;
label_800D9780:;
    if (0 != 0) goto label_800D9794;
    r3 = arg1_r4;
    r4 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30);
    r3 = ResetShape(arg1_r4, *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30)); // [0x800C3618]
label_800D9794:;
    if (*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30) == 0) goto label_800D97B0;
    f1 = *(float*)((arg1_r4 + 112) + 0x0);
    r3 = arg1_r4;
    r5 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30);
    r3 = CalculateShape(arg1_r4, *(float*)((arg1_r4 + 112) + 0x0), *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30), *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30)); // [0x800C3668]
label_800D97B0:;
    r3 = PPCSync(); // [0x800EF2D0]
    r29 = 0 + (1);
    r30 = (arg1_r4 + 112) + (8);
    r26 = 0 + (8);
    if ((0 + 1) <= 4) goto label_800D9780;
label_800D97C8:;
    r9 = SDA1::pG;
    r29 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30);
    r31 = *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x38);
    r0 = *(uint32_t*)(SDA1::pG + 0x108);
    r31 = *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x38) + (-1);
    if (*(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x38) == 0) goto label_800D9818;
label_800D97EC:;
    r3 = *(int16_t*)(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30) + 0x6);
    r4 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30);
    r5 = ((arg1_r4 + 112) + 8);
    r29 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30) + (8);
    r30 = ((arg1_r4 + 112) + 8) + (6);
    r3 = (0xE0000000u + *(int16_t*)(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30) + 0x6));
    r3 = CalcSk1((0xE0000000u + *(int16_t*)(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30) + 0x6))); // [0x800DB5DC]
    r31 = (*(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x38) + -1) + (-1);
    if ((*(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x38) + -1) != 0) goto label_800D97EC;
label_800D9818:;
    r9 = SDA1::pG;
    r4 = *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x38);
    r0 = *(uint32_t*)(SDA1::pG + 0x108);
    r3 = DCStoreRangeNoSync(); // [0x800F19FC]
    r3 = 0x32073207u;
    r3 = setupGQR6(0x32073207u); // [0x800DB628]
    r9 = SDA1::pG;
    r31 = *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x3A);
    r0 = *(uint32_t*)(SDA1::pG + 0x108);
    r30 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x34);
    r31 = *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x3A) + (-1);
    if (*(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x3A) == 0) goto label_800D9890;
label_800D9864:;
    r3 = *(int16_t*)(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x34) + 0x6);
    r4 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x34);
    r5 = (*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30) + 8);
    r30 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x34) + (8);
    r29 = (*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30) + 8) + (6);
    r3 = (0xE0000000u + *(int16_t*)(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x34) + 0x6));
    r3 = CalcSk1((0xE0000000u + *(int16_t*)(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x34) + 0x6))); // [0x800DB5DC]
    r31 = (*(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x3A) + -1) + (-1);
    if ((*(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x3A) + -1) != 0) goto label_800D9864;
label_800D9890:;
    r9 = SDA1::pG;
    r4 = *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x3A);
    r0 = *(uint32_t*)(SDA1::pG + 0x108);
    r3 = DCStoreRangeNoSync(); // [0x800F19FC]
    r3 = PPCSync(); // [0x800EF2D0]
label_800D98B0:;
    r28 = *(uint32_t*)(arg1_r4 + 0x4);
label_800D98B4:;
    if (*(uint32_t*)(arg1_r4 + 0x4) != 0) goto label_800D9680;
label_800D98BC:;
    r0 = stack_0x94;
    return; // r3 = ret_800D98AC
}

// ============================================================================
// High-Level AST Decompilation: MakeWeightPaletteExt(tagWEIGHT_EXT *, long)
// Unit: trans.obj | Address: 0x800D98D0 | Size: 0x218 bytes
// ============================================================================
/* [0x800D98D0] */ void MakeWeightPaletteExt(tagWEIGHT_EXT * arg0_r3, long arg1_r4) {
    // Stack frame allocated: 160 bytes
    stack_0x90 = f30;
    stack_0x98 = f31;
    stack_0xA4 = r0;
    r11 = SDA1::pG;
    r17 = arg1_r4;
    r21 = 0;
    r30 = SDA1::pG + (1072);
    r15 = &aaaa;
    r29 = arg0_r3;
    r31 = 0;
    if (0 >= arg1_r4) goto label_800D9AC8;
label_800D9910:;
    r3 = &stack_0x08;
    r4 = 0;
    r5 = 48;
    r18 = 0 + (1);
    r3 = memset(); // [0x800E8A5C]
    r19 = arg0_r3 + (12);
    r0 = *(uint16_t*)(arg0_r3 + 0x6);
    r7 = 0;
    f2 = *(float*)0x8016EB20;
    if (0 >= *(uint16_t*)(arg0_r3 + 0x6)) goto label_800D9AAC;
    f1 = *(double*)0x8016EB28;
    f30 = *(float*)0x8016EB30;
    r22 = arg0_r3 + (8);
    f31 = *(float*)0x8016EB34;
    r23 = (SDA1::pG + 1072) + (12);
    r24 = (SDA1::pG + 1072) + (16);
    r25 = (SDA1::pG + 1072) + (20);
    r26 = (SDA1::pG + 1072) + (24);
    r27 = (SDA1::pG + 1072) + (28);
    r28 = (SDA1::pG + 1072) + (32);
    r12 = (SDA1::pG + 1072) + (36);
    r8 = arg0_r3;
    r31 = (SDA1::pG + 1072) + (40);
    r3 = (SDA1::pG + 1072) + (44);
    r4 = (SDA1::pG + 1072) + (48);
    r5 = (SDA1::pG + 1072) + (52);
    r6 = (SDA1::pG + 1072) + (56);
label_800D9998:;
    r10 = *(uint16_t*)(arg0_r3 + 0x6);
    stack_0x44 = 0x80170000u;
    r0 = *(uint16_t*)(arg0_r3 + 0x6) + (-1);
    stack_0x40 = 0x43300000u;
    f0 = stack_0x40;
    if (0 != (*(uint16_t*)(arg0_r3 + 0x6) + -1)) goto label_800D99CC;
label_800D99CC:;
    r0 = *(uint16_t*)(arg0_r3 + 0x0);
    r7 = 0 + (1);
    f13 = stack_0x08;
    f12 = stack_0x0C;
    f11 = stack_0x10;
    f10 = stack_0x14;
    r8 = arg0_r3 + (2);
    f9 = stack_0x18;
    r21 = 0 + (1);
    f8 = stack_0x1C;
    f7 = stack_0x20;
    stack_0x08 = stack_0x40;
    f6 = stack_0x24;
    f5 = stack_0x28;
    f4 = stack_0x2C;
    stack_0x0C = stack_0x40;
    f12 = stack_0x30;
    stack_0x10 = stack_0x40;
    stack_0x14 = stack_0x08;
    stack_0x18 = stack_0x40;
    stack_0x1C = stack_0x08;
    stack_0x20 = stack_0x40;
    stack_0x24 = stack_0x08;
    stack_0x28 = stack_0x40;
    stack_0x2C = stack_0x08;
    stack_0x30 = stack_0x40;
    f0 = stack_0x34;
    stack_0x34 = stack_0x08;
    if ((0 + 1) < *(uint16_t*)(arg0_r3 + 0x6)) goto label_800D9998;
label_800D9AAC:;
    r4 = (&aaaa + r20);
    r3 = &stack_0x08;
    r3 = PSMTXReorder(); // [0x80105394]
    r31 = (0 + 1);
    r29 = (arg0_r3 + 12);
    if ((0 + 1) < arg1_r4) goto label_800D9910;
label_800D9AC8:;
    r3 = (0 + 1);
    r0 = stack_0xA4;
    f30 = stack_0x90;
    f31 = stack_0x98;
    return; // r3 = (0 + 1)
}

// ============================================================================
// High-Level AST Decompilation: MakeWeightPalette(tagWEIGHT *, long)
// Unit: trans.obj | Address: 0x800D9AE8 | Size: 0x208 bytes
// ============================================================================
/* [0x800D9AE8] */ void MakeWeightPalette(tagWEIGHT * arg0_r3, long arg1_r4) {
    // Stack frame allocated: 152 bytes
    stack_0x88 = f30;
    stack_0x90 = f31;
    stack_0x9C = r0;
    r9 = SDA1::pG;
    r18 = arg1_r4;
    r22 = 0;
    r29 = arg0_r3;
    r30 = SDA1::pG + (1072);
    r31 = 0;
    if (0 >= arg1_r4) goto label_800D9CD0;
label_800D9B20:;
    r3 = &stack_0x08;
    r4 = 0;
    r5 = 48;
    r19 = 0 + (1);
    r3 = memset(); // [0x800E8A5C]
    r20 = arg0_r3 + (8);
    r0 = *(uint8_t*)(arg0_r3 + 0x3);
    r8 = 0;
    f2 = *(float*)0x8016EB38;
    if (0 >= *(uint8_t*)(arg0_r3 + 0x3)) goto label_800D9CB4;
    f1 = *(double*)0x8016EB40;
    f30 = *(float*)0x8016EB48;
    r23 = arg0_r3 + (4);
    f31 = *(float*)0x8016EB4C;
    r24 = (SDA1::pG + 1072) + (12);
    r25 = (SDA1::pG + 1072) + (16);
    r26 = (SDA1::pG + 1072) + (20);
    r27 = (SDA1::pG + 1072) + (24);
    r28 = (SDA1::pG + 1072) + (28);
    r4 = (SDA1::pG + 1072) + (32);
    r12 = (SDA1::pG + 1072) + (36);
    r31 = (SDA1::pG + 1072) + (40);
    r3 = (SDA1::pG + 1072) + (44);
    r5 = (SDA1::pG + 1072) + (48);
    r6 = (SDA1::pG + 1072) + (52);
    r7 = (SDA1::pG + 1072) + (56);
label_800D9BA4:;
    r10 = *(uint8_t*)(arg0_r3 + 0x3);
    stack_0x44 = 0x80170000u;
    r0 = *(uint8_t*)(arg0_r3 + 0x3) + (-1);
    stack_0x40 = 0x43300000u;
    f0 = stack_0x40;
    if (0 != (*(uint8_t*)(arg0_r3 + 0x3) + -1)) goto label_800D9BD8;
label_800D9BD8:;
    f13 = stack_0x08;
    r8 = 0 + (1);
    f12 = stack_0x0C;
    f11 = stack_0x10;
    f10 = stack_0x14;
    r22 = 0 + (1);
    f9 = stack_0x18;
    f8 = stack_0x1C;
    f7 = stack_0x20;
    stack_0x08 = stack_0x40;
    f6 = stack_0x24;
    f5 = stack_0x28;
    f4 = stack_0x2C;
    stack_0x0C = stack_0x40;
    f12 = stack_0x30;
    stack_0x10 = stack_0x40;
    stack_0x14 = stack_0x08;
    stack_0x18 = stack_0x40;
    stack_0x1C = stack_0x08;
    stack_0x20 = stack_0x40;
    stack_0x24 = stack_0x08;
    stack_0x28 = stack_0x40;
    stack_0x2C = stack_0x08;
    stack_0x30 = stack_0x40;
    f0 = stack_0x34;
    stack_0x34 = stack_0x08;
    if ((0 + 1) < *(uint8_t*)(arg0_r3 + 0x3)) goto label_800D9BA4;
label_800D9CB4:;
    r3 = &stack_0x08;
    r3 = PSMTXReorder(); // [0x80105394]
    r31 = (0 + 1);
    r29 = (arg0_r3 + 8);
    if ((0 + 1) < arg1_r4) goto label_800D9B20;
label_800D9CD0:;
    r3 = (0 + 1);
    r0 = stack_0x9C;
    f30 = stack_0x88;
    f31 = stack_0x90;
    return; // r3 = (0 + 1)
}

// ============================================================================
// High-Level AST Decompilation: RenderInit(void)
// Unit: trans.obj | Address: 0x800D9CF0 | Size: 0x20 bytes
// ============================================================================
/* [0x800D9CF0] */ void RenderInit(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = LightSetInit(); // [0x800DBD70]
    r0 = stack_0x0C;
    return; // r3 = ret_800D9CFC
}

// ============================================================================
// High-Level AST Decompilation: Render(void)
// Unit: trans.obj | Address: 0x800D9D10 | Size: 0x9C bytes
// ============================================================================
/* [0x800D9D10] */ void Render(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = GXSetCurrentGXThread(); // [0x8011DEF4]
    r0 = SDA1::boostFlag;
    if (SDA1::boostFlag == 0) goto label_800D9D40;
    r0 = 128;
    r9 = 0;
    SDA1::blur_rate = 128;
    SDA1::blur_type = 0;
    goto label_800D9D44;
label_800D9D40:;
    SDA1::blur_rate = 128;
label_800D9D44:;
    r3 = 0;
    r3 = ExecOt(0); // [0x800DCCEC]
    r3 = 1;
    r3 = ExecOt(1); // [0x800DCCEC]
    r3 = 2;
    r3 = ExecOt(2); // [0x800DCCEC]
    r3 = 3;
    r3 = ExecOt(3); // [0x800DCCEC]
    r3 = 4;
    r3 = ExecOt(4); // [0x800DCCEC]
    r3 = 5;
    r3 = ExecOt(5); // [0x800DCCEC]
    r3 = 6;
    r3 = ExecOt(6); // [0x800DCCEC]
    r3 = FilterRender(); // [0x80094F04]
    r3 = &cId;
    r3 = cIdCtrl::IdRender(&cId); // [0x80070EC0]
    r3 = &cMes;
    r3 = CMesCtrl::MesTrans(&cMes); // [0x8009F18C]
    r3 = FadeRender(); // [0x8009456C]
    r0 = stack_0x0C;
    return; // r3 = ret_800D9D98
}

// ============================================================================
// High-Level AST Decompilation: ModelRender(void *)
// Unit: trans.obj | Address: 0x800D9DAC | Size: 0x8C bytes
// ============================================================================
/* [0x800D9DAC] */ void ModelRender(void * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r30 = arg0_r3;
    r7 = 0;
    r3 = 7;
    r4 = 0;
    r5 = 1;
    r6 = 7;
    r3 = GXSetAlphaCompare(); // [0x80124EC0]
    r6 = 0;
    r4 = 1;
    r5 = 0;
    r3 = 0;
    r3 = GXSetBlendMode(); // [0x80125684]
    r3 = 1;
    r3 = GXSetCullMode(); // [0x80120D3C]
    r5 = 1;
    r3 = 1;
    r4 = 3;
    r3 = GXSetZMode(); // [0x80125730]
    r3 = CameraCurrentProjection(); // [0x8001A5B4]
    r3 = arg0_r3;
    r5 = SDA1::pG;
    r4 = *(uint32_t*)(arg0_r3 + 0x130);
    r6 = 0;
    r5 = SDA1::pG + (852);
    r3 = commonModelRender(arg0_r3, *(uint32_t*)(arg0_r3 + 0x130), (SDA1::pG + 852)); // [0x800D9E38]
    r3 = shaderReset(); // [0x800DB564]
    r0 = stack_0x14;
    return; // r3 = ret_800D9E20
}

// ============================================================================
// High-Level AST Decompilation: commonModelRender(tagCOMN *, cModelInfo *, float (*)[3], unsigned long)
// Unit: trans.obj | Address: 0x800D9E38 | Size: 0x534 bytes
// ============================================================================
/* [0x800D9E38] */ void commonModelRender(tagCOMN * arg0_r3, cModelInfo * arg1_r4, float (* arg2_r5) {
    // Stack frame allocated: 304 bytes
    stack_0x128 = f31;
    stack_0x134 = r0;
    r9 = SDA1::pG;
    r24 = arg0_r3;
    r17 = arg2_r5;
    r19 = r6;
    r18 = SDA1::pG + (1072);
    r27 = arg1_r4;
    if (r0 == 0) goto label_800DA354;
    r22 = &stack_0x10;
    r20 = &stack_0x40;
    r21 = &stack_0x70;
label_800D9E74:;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    if (r0 == 0) goto label_800D9EE0;
    r3 = 1;
    r3 = GXSetNumChans(); // [0x80122374]
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r8 = 2;
    r9 = 2;
    r3 = GXSetChanCtrl(); // [0x801223B8]
    r3 = 2;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r8 = 2;
    r9 = 2;
    r3 = GXSetChanCtrl(); // [0x801223B8]
    r0 = SDA1::col128;
    r3 = 4;
    r4 = &stack_0x08;
    stack_0x08 = SDA1::col128;
    r3 = GXSetChanAmbColor(); // [0x8012218C]
    goto label_800D9FA8;
label_800D9EE0:;
    r9 = *(uint32_t*)(arg1_r4 + 0x9C);
    r0 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x20);
    if (r0 == 0) goto label_800D9FA0;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r8 = 2;
    r9 = 2;
    r31 = &stack_0xD0;
    r3 = GXSetChanCtrl(); // [0x801223B8]
    r9 = 2;
    r3 = 2;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r8 = 2;
    r3 = GXSetChanCtrl(); // [0x801223B8]
    stack_0xD0 = r30;
    r9 = SDA1::pG;
    r0 = *(uint16_t*)(SDA1::pG + 0x6A78);
    if (*(uint16_t*)(SDA1::pG + 0x6A78) != 2577) goto label_800D9F50;
    r0 = 255;
    *(uint8_t*)(&stack_0xD0 + 0x3) = 255;
label_800D9F50:;
    r0 = stack_0xD0;
    r3 = 4;
    r4 = &stack_0x08;
    stack_0x08 = stack_0xD0;
    r3 = GXSetChanAmbColor(); // [0x8012218C]
    r9 = SDA1::pG;
    r11 = 64;
    r0 = *(uint32_t*)(SDA1::pG + 0x12C);
    if (*(uint16_t*)(SDA1::pG + 0x6A78) == 2577) goto label_800D9F7C;
    r11 = 255;
label_800D9F7C:;
    *(uint8_t*)(&stack_0xD0 + 0x1) = 255;
    r3 = 4;
    *(uint8_t*)(&stack_0xD0 + 0x2) = 255;
    r4 = &stack_0x08;
    stack_0xD0 = 255;
    r0 = stack_0xD0;
    stack_0x08 = stack_0xD0;
    r3 = GXSetChanMatColor(); // [0x80122280]
    goto label_800D9FA8;
label_800D9FA0:;
    r3 = arg0_r3;
    r3 = LightSetModel(arg0_r3); // [0x800DBDFC]
label_800D9FA8:;
    r29 = *(uint32_t*)(arg1_r4 + 0x9C);
    r23 = *(uint32_t*)(arg1_r4 + 0xA0);
    SDA1::pInfo = arg1_r4;
    r0 = *(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18);
    if (*(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18) != 1) goto label_800D9FEC;
    r9 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x14);
    r11 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x0);
    r0 = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x14) + 0x0);
    r3 = *(uint32_t*)(arg0_r3 + 0xF0);
    r3 = GetPartsAddr(*(uint32_t*)(arg0_r3 + 0xF0), &stack_0x08); // [0x800A0BD4]
    r4 = arg1_r4 + (44);
    r5 = &stack_0xA0;
    goto label_800D9FF8;
label_800D9FEC:;
    r3 = *(uint32_t*)(arg0_r3 + 0xF0);
    r4 = arg1_r4 + (44);
    r5 = &stack_0xA0;
label_800D9FF8:;
    r3 = PSMTXConcat(); // [0x80100470]
    r4 = &stack_0xA0;
    r5 = &stack_0x10;
    r3 = arg2_r5;
    r3 = PSMTXConcat(); // [0x80100470]
    r4 = &stack_0x40;
    r3 = &stack_0x10;
    r3 = PSMTXInverse(); // [0x80100A94]
    r3 = &stack_0x40;
    r4 = &stack_0x70;
    r3 = PSMTXTranspose(); // [0x80100798]
    r3 = &stack_0x10;
    r4 = 0;
    r3 = GXLoadPosMtxImm(); // [0x80125FAC]
    r4 = 0;
    r3 = &stack_0x70;
    r3 = GXLoadNrmMtxImm(); // [0x80126024]
    r3 = 0;
    r3 = GXSetCurrentMtx(); // [0x801260E8]
    r28 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x10);
    r3 = GXClearVtxDesc(); // [0x8011EDD4]
    r3 = 9;
    r4 = 3;
    r3 = GXSetVtxDesc(); // [0x8011E354]
    r3 = 10;
    r4 = 3;
    r3 = GXSetVtxDesc(); // [0x8011E354]
    r3 = 13;
    r4 = 3;
    r3 = GXSetVtxDesc(); // [0x8011E354]
    r3 = 0;
    r4 = 10;
    r5 = 0;
    r6 = 3;
    r7 = 14;
    r3 = GXSetVtxAttrFmt(); // [0x8011EE0C]
    r0 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x20);
    if (*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x20) >= 0) goto label_800DA0E8;
    r5 = 1;
    r6 = 3;
    r7 = 8;
    r30 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0xC);
    r3 = 0;
    r4 = 13;
    r3 = GXSetVtxAttrFmt(); // [0x8011EE0C]
    r3 = 11;
    r4 = 3;
    r3 = GXSetVtxDesc(); // [0x8011E354]
    r3 = 0;
    r4 = 11;
    r5 = 1;
    r6 = 5;
    r7 = 0;
    r3 = GXSetVtxAttrFmt(); // [0x8011EE0C]
    r4 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0xC);
    r3 = 11;
    r5 = 4;
    r3 = GXSetArray(); // [0x8011F86C]
    goto label_800DA100;
label_800DA0E8:;
    r3 = 0;
    r4 = 13;
    r5 = 1;
    r6 = 2;
    r7 = 15;
    r3 = GXSetVtxAttrFmt(); // [0x8011EE0C]
label_800DA100:;
    r9 = SDA1::pG;
    r11 = arg1_r4 + (96);
    r3 = 9;
    r5 = 6;
    r0 = *(uint32_t*)(SDA1::pG + 0x108);
    r3 = GXSetArray(); // [0x8011F86C]
    r9 = SDA1::pG;
    r11 = arg1_r4 + (104);
    r3 = 10;
    r5 = 6;
    r0 = *(uint32_t*)(SDA1::pG + 0x108);
    r3 = GXSetArray(); // [0x8011F86C]
    r4 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x10);
    r3 = 13;
    r5 = 4;
    r3 = GXSetArray(); // [0x8011F86C]
    r7 = *(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x28);
    r3 = 0;
    r4 = 9;
    r5 = 1;
    r6 = 3;
    r3 = GXSetVtxAttrFmt(); // [0x8011EE0C]
    r0 = *(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18);
    if (*(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18) != 1) goto label_800DA1A0;
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    if (*(uint8_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x18) != 1) goto label_800DA1A0;
    r4 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x30);
    r3 = 9;
    r5 = 8;
    r3 = GXSetArray(); // [0x8011F86C]
    r4 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x34);
    r3 = 10;
    r5 = 8;
    r3 = GXSetArray(); // [0x8011F86C]
label_800DA1A0:;
    r3 = *(uint32_t*)(arg1_r4 + 0xA4);
    if (*(uint32_t*)(arg1_r4 + 0xA4) != 1) goto label_800DA1B4;
    r3 = 2;
    goto label_800DA1C0;
label_800DA1B4:;
    if (2 != 2) goto label_800DA1C0;
    r3 = 1;
label_800DA1C0:;
    r3 = GXSetCullMode(); // [0x80120D3C]
    r28 = 0;
    r0 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x24);
    if (0 >= *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x24)) goto label_800DA2A4;
    r25 = 1;
    f31 = *(double*)0x8016EB50;
    r31 = (SDA1::pG + 1072) + (4812);
label_800DA1E8:;
    r3 = *(uint32_t*)(arg1_r4 + 0xA0);
    r4 = 0;
    r3 = TEXGet(); // [0x80127870]
    r0 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x20);
    r30 = ret_800DA1F0;
    if (*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x20) >= 0) goto label_800DA210;
    r9 = *(uint32_t*)(ret_800DA1F0 + 0x0);
    *(uint32_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0xC) = 1;
    *(uint32_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x10) = 1;
label_800DA210:;
    r11 = *(uint32_t*)(ret_800DA1F0 + 0x0);
    r3 = ((SDA1::pG + 1072) + 4812);
    r10 = 0;
    r28 = 0 + (1);
    r9 = *(uint32_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x10);
    r4 = *(uint32_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x8);
    r5 = *(uint16_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x2);
    r6 = *(uint16_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x0);
    r7 = *(uint32_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x4);
    r8 = *(uint32_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0xC);
    r3 = GXInitTexObj(); // [0x8012270C]
    r9 = *(uint32_t*)(ret_800DA1F0 + 0x0);
    r10 = *(uint32_t*)(ret_800DA1F0 + 0x0);
    r3 = ((SDA1::pG + 1072) + 4812);
    r0 = *(uint8_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x21);
    r4 = 4;
    r30 = *(uint8_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x22);
    r5 = 1;
    stack_0xE4 = *(uint8_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x21);
    r6 = 0;
    r7 = *(uint8_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x20);
    r8 = 0;
    stack_0xE0 = 0x43300000u;
    r31 = ((SDA1::pG + 1072) + 4812) + (32);
    f3 = *(float*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x1C);
    f1 = stack_0xE0;
    stack_0xE4 = *(uint8_t*)(*(uint32_t*)(ret_800DA1F0 + 0x0) + 0x22);
    stack_0xE0 = 0x43300000u;
    f2 = stack_0xE0;
    r3 = GXInitTexObjLOD(); // [0x801229C8]
    r0 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x24);
    if ((0 + 1) < *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x24)) goto label_800DA1E8;
label_800DA2A4:;
    r26 = *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1A);
    r28 = 0;
    r31 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1C);
    if (0 >= *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1A)) goto label_800DA348;
label_800DA2C4:;
    r3 = arg0_r3;
    r4 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1C);
    r3 = shaderSetup(arg0_r3, *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1C)); // [0x800DA36C]
    if (0 == *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1A)) goto label_800DA324;
    r0 = *(uint8_t*)(arg1_r4 + 0x5F);
    if (*(uint8_t*)(arg1_r4 + 0x5F) > 0xFEu) goto label_800DA324;
    r0 = *(uint32_t*)(arg1_r4 + 0x5C);
    r4 = &stack_0x08;
    r3 = 4;
    stack_0x08 = *(uint32_t*)(arg1_r4 + 0x5C);
    r3 = GXSetChanMatColor(); // [0x80122280]
    r3 = 4;
    r4 = 0;
    r5 = 1;
    r6 = 4;
    r7 = 255;
    r3 = GXSetAlphaCompare(); // [0x80124EC0]
    r3 = 1;
    r4 = 4;
    r5 = 5;
    r6 = 0;
    r3 = GXSetBlendMode(); // [0x80125684]
label_800DA324:;
    r30 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1C) + (32);
    r4 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1C) + 0x18);
    r3 = (*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1C) + 32);
    r28 = 0 + (1);
    r3 = GXCallDisplayList(); // [0x80125B3C]
    r0 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1C) + 0x18);
    r31 = ((*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1C) + 32) + *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1C) + 0x18));
    if ((0 + 1) < *(uint16_t*)(*(uint32_t*)(arg1_r4 + 0x9C) + 0x1A)) goto label_800DA2C4;
label_800DA348:;
    r27 = *(uint32_t*)(arg1_r4 + 0x4);
    if (*(uint32_t*)(arg1_r4 + 0x4) != 0) goto label_800D9E74;
label_800DA354:;
    r0 = stack_0x134;
    f31 = stack_0x128;
    return; // r3 = ret_800DA334
}

// ============================================================================
// High-Level AST Decompilation: shaderSetup(tagCOMN *, POLY_HEADER *)
// Unit: trans.obj | Address: 0x800DA36C | Size: 0x1F0 bytes
// ============================================================================
/* [0x800DA36C] */ void shaderSetup(tagCOMN * arg0_r3, POLY_HEADER * arg1_r4) {
    // Stack frame allocated: 64 bytes
    stack_0x44 = r0;
    r0 = 0;
    r11 = &tev_reg;
    *(uint32_t*)(&tev_reg + 0x0) = 0;
    r9 = &tex_coord;
    *(uint32_t*)(&tex_coord + 0x0) = 0;
    r10 = &tev_kcolor;
    *(uint32_t*)(&tev_kcolor + 0x0) = 0;
    r8 = &tex_map;
    *(uint32_t*)(&tex_map + 0x0) = 0;
    SDA1::tev_stage = 0;
    r31 = arg0_r3;
    f0 = *(float*)0x8016EB58;
    r3 = &stack_0x08;
    f1 = *(float*)(arg0_r3 + 0xD8);
    r30 = arg1_r4;
    f2 = *(float*)(arg0_r3 + 0xDC);
    f3 = *(float*)(arg0_r3 + 0xE0);
    r3 = PSMTXScale(); // [0x801014A8]
    r3 = &stack_0x08;
    r4 = arg0_r3;
    r5 = &stack_0x08;
    r3 = PSMTXConcat(); // [0x80100470]
    r3 = &stack_0x08;
    r5 = arg0_r3;
    r4 = &specular_mat;
    r3 = updateMatrices(&stack_0x08); // [0x800DBB90]
    r3 = arg1_r4;
    r3 = materialSetup(arg1_r4); // [0x800DA55C]
    r3 = arg1_r4;
    r3 = specularSetup(arg1_r4); // [0x800DA8E0]
    r3 = arg1_r4;
    r3 = bumpSetup(arg1_r4); // [0x800DB214]
    r3 = arg1_r4;
    r3 = reflectionSetup(arg1_r4); // [0x800DAF20]
    r0 = *(uint8_t*)(arg1_r4 + 0xB);
    if (r0 == 0) goto label_800DA430;
    r3 = arg1_r4;
    r3 = alphaSetup(arg1_r4); // [0x800DB3D0]
    goto label_800DA498;
label_800DA430:;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    if (r0 == 0) goto label_800DA46C;
    r3 = 4;
    r4 = 0;
    r5 = 1;
    r6 = 4;
    r7 = 255;
    r3 = GXSetAlphaCompare(); // [0x80124EC0]
    r3 = 1;
    r4 = 4;
    r5 = 5;
    r6 = 0;
    r3 = GXSetBlendMode(); // [0x80125684]
    goto label_800DA498;
label_800DA46C:;
    r3 = 0;
    r4 = 1;
    r5 = 0;
    r6 = 0;
    r3 = GXSetBlendMode(); // [0x80125684]
    r3 = 7;
    r4 = 0;
    r5 = 1;
    r6 = 7;
    r7 = 0;
    r3 = GXSetAlphaCompare(); // [0x80124EC0]
label_800DA498:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x12C);
    if (r0 != 0) goto label_800DA538;
    r3 = &tev_stage;
    r3 = cTevStage::getID(void) const(); // [0x800DBCCC]
    r30 = ret_800DA4AC;
    r4 = 255;
    r5 = 255;
    r6 = 4;
    r3 = GXSetTevOrder(); // [0x80124F98]
    r3 = ret_800DA4AC;
    r4 = 15;
    r5 = 15;
    r6 = 15;
    r7 = 0;
    r3 = GXSetTevColorIn(); // [0x80124A44]
    r8 = 0;
    r3 = ret_800DA4AC;
    r4 = 0;
    r5 = 0;
    r6 = 2;
    r7 = 1;
    r3 = GXSetTevColorOp(); // [0x80124ACC]
    r3 = ret_800DA4AC;
    r4 = 7;
    r5 = 7;
    r6 = 7;
    r7 = 0;
    r3 = GXSetTevAlphaIn(); // [0x80124A88]
    r3 = ret_800DA4AC;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r8 = 0;
    r3 = GXSetTevAlphaOp(); // [0x80124B34]
    r9 = SDA1::tev_stage;
    r9 = SDA1::tev_stage + (1);
    SDA1::tev_stage = (SDA1::tev_stage + 1);
label_800DA538:;
    r3 = *(uint8_t*)0x8026E8F7;
    r3 = GXSetNumTevStages(); // [0x80125170]
    r3 = *(uint8_t*)0x8026E907;
    r3 = GXSetNumTexGens(); // [0x8011FBD8]
    r0 = stack_0x44;
    return; // r3 = ret_800DA544
}

// ============================================================================
// High-Level AST Decompilation: materialSetup(POLY_HEADER *)
// Unit: trans.obj | Address: 0x800DA55C | Size: 0x384 bytes
// ============================================================================
/* [0x800DA55C] */ void materialSetup(POLY_HEADER * arg0_r3) {
    // Stack frame allocated: 152 bytes
    stack_0x9C = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r3 = &tev_stage;
    r27 = SDA1::pG + (1072);
    r3 = cTevStage::getID(void) const(); // [0x800DBCCC]
    r10 = &stack_0x08;
    r31 = ret_800DA57C;
    r8 = 0x8016EA94u;
    r29 = &stack_0x08;
    r0 = 24;
label_800DA598:;
    r11 = *(uint32_t*)(0x8016EA94u + 0x0);
    *(uint32_t*)(&stack_0x08 + 0x0) = *(uint32_t*)(0x8016EA94u + 0x0);
    r11 = *(uint32_t*)(0x8016EA94u + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)(0x8016EA94u + 0x4);
    r11 = *(uint32_t*)(0x8016EA94u + 0x8);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)(0x8016EA94u + 0x8);
    r11 = *(uint32_t*)(0x8016EA94u + 0xC);
    *(uint32_t*)(&stack_0x08 + 0xC) = *(uint32_t*)(0x8016EA94u + 0xC);
    r11 = *(uint32_t*)(0x8016EA94u + 0x10);
    *(uint32_t*)(&stack_0x08 + 0x10) = *(uint32_t*)(0x8016EA94u + 0x10);
    r11 = *(uint32_t*)(0x8016EA94u + 0x14);
    r8 = 0x8016EA94u + (24);
    *(uint32_t*)(&stack_0x08 + 0x14) = *(uint32_t*)(0x8016EA94u + 0x14);
    r10 = &stack_0x08 + (24);
    if (r0 != 0) goto label_800DA598;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r0 = SDA1::tex_map;
    r9 = 0x8016EA94u;
    *(uint32_t*)((&stack_0x08 + 24) + 0x0) = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r7 = &stack_0x08;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r8 = 24;
    *(uint32_t*)((&stack_0x08 + 24) + 0x4) = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
label_800DA604:;
    r11 = *(uint32_t*)(0x8016EA94u + 0x0);
    *(uint32_t*)(&stack_0x08 + 0x0) = *(uint32_t*)(0x8016EA94u + 0x0);
    r11 = *(uint32_t*)(0x8016EA94u + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)(0x8016EA94u + 0x4);
    r11 = *(uint32_t*)(0x8016EA94u + 0x8);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)(0x8016EA94u + 0x8);
    r11 = *(uint32_t*)(0x8016EA94u + 0xC);
    *(uint32_t*)(&stack_0x08 + 0xC) = *(uint32_t*)(0x8016EA94u + 0xC);
    r11 = *(uint32_t*)(0x8016EA94u + 0x10);
    *(uint32_t*)(&stack_0x08 + 0x10) = *(uint32_t*)(0x8016EA94u + 0x10);
    r11 = *(uint32_t*)(0x8016EA94u + 0x14);
    r9 = 0x8016EA94u + (24);
    *(uint32_t*)(&stack_0x08 + 0x14) = *(uint32_t*)(0x8016EA94u + 0x14);
    r7 = &stack_0x08 + (24);
    if (r0 != 0) goto label_800DA604;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r4 = r28;
    r3 = *(uint8_t*)(arg0_r3 + 0xC);
    *(uint32_t*)((&stack_0x08 + 24) + 0x0) = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r0 = SDA1::tex_coord;
    r3 = *(uint8_t*)(arg0_r3 + 0xC) + (4812);
    *(uint32_t*)((&stack_0x08 + 24) + 0x4) = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r3 = ((SDA1::pG + 1072) + (*(uint8_t*)(arg0_r3 + 0xC) + 4812));
    r3 = GXLoadTexObj(); // [0x8012319C]
    r8 = 125;
    r7 = 0;
    r4 = 1;
    r5 = 4;
    r6 = 60;
    r3 = arg0_r3;
    r3 = GXSetTexCoordGen2(); // [0x8011F908]
    r3 = ret_800DA57C;
    r3 = GXSetTevDirect(); // [0x801244D8]
    r4 = arg0_r3;
    r3 = ret_800DA57C;
    r5 = r28;
    r6 = 4;
    r3 = GXSetTevOrder(); // [0x80124F98]
    r3 = ret_800DA57C;
    r4 = 15;
    r5 = 8;
    r6 = 10;
    r7 = 15;
    r3 = GXSetTevColorIn(); // [0x80124A44]
    r8 = 0;
    r3 = ret_800DA57C;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r3 = GXSetTevColorOp(); // [0x80124ACC]
    r3 = ret_800DA57C;
    r4 = 7;
    r5 = 4;
    r6 = 5;
    r7 = 7;
    r3 = GXSetTevAlphaIn(); // [0x80124A88]
    r3 = ret_800DA57C;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r8 = 0;
    r3 = GXSetTevAlphaOp(); // [0x80124B34]
    r9 = SDA1::pInfo;
    r0 = *(uint32_t*)(SDA1::pInfo + 0x0);
    if (*(uint32_t*)(SDA1::pInfo + 0x0) >= 0) goto label_800DA8A8;
    f13 = SDA1::u.1252;
    f0 = *(float*)0x8016EB5C;
    f2 = *(float*)0x8016EB60;
    SDA1::u.1252 = SDA1::u.1252;
    if (*(uint32_t*)(SDA1::pInfo + 0x0) >= 0) goto label_800DA75C;
    f0 = *(float*)0x8016EB64;
    SDA1::u.1252 = *(float*)0x8016EB64;
label_800DA75C:;
    r30 = &stack_0x28;
    f1 = SDA1::u.1252;
    r3 = &stack_0x28;
    r3 = PSMTXTrans(); // [0x80101378]
    r11 = SDA1::tex_coord;
    r3 = &stack_0x28;
    r6 = &stack_0x58;
    r11 = SDA1::tex_coord + (1);
    r10 = 0x8016EA94u;
    SDA1::tex_coord = (SDA1::tex_coord + 1);
    r7 = &stack_0x08;
    r0 = 24;
label_800DA794:;
    r11 = *(uint32_t*)(0x8016EA94u + 0x0);
    *(uint32_t*)(&stack_0x08 + 0x0) = *(uint32_t*)(0x8016EA94u + 0x0);
    r11 = *(uint32_t*)(0x8016EA94u + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)(0x8016EA94u + 0x4);
    r11 = *(uint32_t*)(0x8016EA94u + 0x8);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)(0x8016EA94u + 0x8);
    r11 = *(uint32_t*)(0x8016EA94u + 0xC);
    *(uint32_t*)(&stack_0x08 + 0xC) = *(uint32_t*)(0x8016EA94u + 0xC);
    r11 = *(uint32_t*)(0x8016EA94u + 0x10);
    *(uint32_t*)(&stack_0x08 + 0x10) = *(uint32_t*)(0x8016EA94u + 0x10);
    r11 = *(uint32_t*)(0x8016EA94u + 0x14);
    r10 = 0x8016EA94u + (24);
    *(uint32_t*)(&stack_0x08 + 0x14) = *(uint32_t*)(0x8016EA94u + 0x14);
    r7 = &stack_0x08 + (24);
    if (*(uint32_t*)(SDA1::pInfo + 0x0) != 0) goto label_800DA794;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r0 = SDA1::tex_coord;
    r9 = 0x8016EAB4u;
    *(uint32_t*)((&stack_0x08 + 24) + 0x0) = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r8 = &stack_0x58;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r10 = 24;
    *(uint32_t*)((&stack_0x08 + 24) + 0x4) = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
label_800DA800:;
    r11 = *(uint32_t*)(0x8016EAB4u + 0x0);
    *(uint32_t*)(&stack_0x58 + 0x0) = *(uint32_t*)(0x8016EAB4u + 0x0);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x4);
    *(uint32_t*)(&stack_0x58 + 0x4) = *(uint32_t*)(0x8016EAB4u + 0x4);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x8);
    *(uint32_t*)(&stack_0x58 + 0x8) = *(uint32_t*)(0x8016EAB4u + 0x8);
    r11 = *(uint32_t*)(0x8016EAB4u + 0xC);
    *(uint32_t*)(&stack_0x58 + 0xC) = *(uint32_t*)(0x8016EAB4u + 0xC);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x10);
    *(uint32_t*)(&stack_0x58 + 0x10) = *(uint32_t*)(0x8016EAB4u + 0x10);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x14);
    r9 = 0x8016EAB4u + (24);
    *(uint32_t*)(&stack_0x58 + 0x14) = *(uint32_t*)(0x8016EAB4u + 0x14);
    r8 = &stack_0x58 + (24);
    if (*(uint32_t*)(SDA1::pInfo + 0x0) != 0) goto label_800DA800;
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0x0);
    r5 = 0;
    r0 = SDA1::tex_coord;
    *(uint32_t*)((&stack_0x58 + 24) + 0x0) = *(uint32_t*)((0x8016EAB4u + 24) + 0x0);
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0x4);
    *(uint32_t*)((&stack_0x58 + 24) + 0x4) = *(uint32_t*)((0x8016EAB4u + 24) + 0x4);
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0x8);
    *(uint32_t*)((&stack_0x58 + 24) + 0x8) = *(uint32_t*)((0x8016EAB4u + 24) + 0x8);
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0xC);
    *(uint32_t*)((&stack_0x58 + 24) + 0xC) = *(uint32_t*)((0x8016EAB4u + 24) + 0xC);
    r4 = &stack_0x28;
    r3 = GXLoadTexMtxImm(); // [0x80126120]
    r6 = &stack_0x28;
    r3 = &stack_0x08;
    r4 = 0;
    r5 = 4;
    r7 = 0;
    r8 = 125;
    r3 = GXSetTexCoordGen2(); // [0x8011F908]
    r3 = ret_800DA57C;
    r4 = &stack_0x08;
    r5 = r28;
    r6 = 4;
    r3 = GXSetTevOrder(); // [0x80124F98]
label_800DA8A8:;
    r9 = SDA1::tev_stage;
    r11 = SDA1::tex_map;
    r10 = SDA1::tex_coord;
    r9 = SDA1::tev_stage + (1);
    r11 = SDA1::tex_map + (1);
    SDA1::tev_stage = (SDA1::tev_stage + 1);
    r10 = SDA1::tex_coord + (1);
    SDA1::tex_map = (SDA1::tex_map + 1);
    SDA1::tex_coord = (SDA1::tex_coord + 1);
    r0 = stack_0x9C;
    return; // r3 = ret_800DA8A4
}

// ============================================================================
// High-Level AST Decompilation: specularSetup(POLY_HEADER *)
// Unit: trans.obj | Address: 0x800DA8E0 | Size: 0x640 bytes
// ============================================================================
/* [0x800DA8E0] */ void specularSetup(POLY_HEADER * arg0_r3) {
    // Stack frame allocated: 208 bytes
    stack_0xD4 = r0;
    stack_0xB4 = r12;
    r31 = arg0_r3;
    r0 = *(uint8_t*)(arg0_r3 + 0xB);
    if (r0 == 0) goto label_800DAF04;
    r9 = *(uint8_t*)(arg0_r3 + 0x10);
    r10 = &stack_0x9C;
    r11 = *(uint8_t*)(arg0_r3 + 0x11);
    r0 = *(uint8_t*)(arg0_r3 + 0x12);
    r28 = *(uint8_t*)(arg0_r3 + 0xF);
    stack_0x9C = *(uint8_t*)(arg0_r3 + 0x10);
    *(uint8_t*)(&stack_0x9C + 0x2) = *(uint8_t*)(arg0_r3 + 0x12);
    *(uint8_t*)(&stack_0x9C + 0x1) = *(uint8_t*)(arg0_r3 + 0x11);
    if (*(uint8_t*)(arg0_r3 + 0xF) != 255) goto label_800DA940;
    r28 = 0;
label_800DA940:;
    r0 = *(uint8_t*)(arg0_r3 + 0x15);
    f13 = *(double*)0x8016EB68;
    stack_0xAC = *(uint8_t*)(arg0_r3 + 0x15);
    f12 = *(float*)0x8016EB70;
    stack_0xA8 = 0x43300000u;
    f3 = *(float*)0x8016EB74;
    f0 = stack_0xA8;
    if (*(uint8_t*)(arg0_r3 + 0xF) != 255) goto label_800DA98C;
    f1 = *(float*)0x8016EB78;
label_800DA98C:;
    r29 = &stack_0x38;
    r3 = &stack_0x38;
    r27 = &stack_0x38;
    r3 = PSMTXScale(); // [0x801014A8]
    f1 = *(float*)0x8016EB78;
    r30 = &stack_0x68;
    f3 = *(float*)0x8016EB7C;
    r3 = &stack_0x68;
    r3 = PSMTXTrans(); // [0x80101378]
    r5 = &stack_0x08;
    r3 = &stack_0x38;
    r4 = &specular_mat;
    r3 = PSMTXConcat(); // [0x80100470]
    r4 = &stack_0x08;
    r3 = &stack_0x68;
    r5 = &stack_0x08;
    r3 = PSMTXConcat(); // [0x80100470]
    r0 = *(uint8_t*)(arg0_r3 + 0xB);
    r3 = &tev_stage;
    r26 = *(uint8_t*)(arg0_r3 + 0x13);
    r3 = cTevStage::getID(void) const(); // [0x800DBCCC]
    r31 = ret_800DA9F4;
    r9 = 0x8016EA94u;
    r10 = &stack_0x38;
    r0 = 24;
label_800DAA10:;
    r11 = *(uint32_t*)(0x8016EA94u + 0x0);
    *(uint32_t*)(&stack_0x38 + 0x0) = *(uint32_t*)(0x8016EA94u + 0x0);
    r11 = *(uint32_t*)(0x8016EA94u + 0x4);
    *(uint32_t*)(&stack_0x38 + 0x4) = *(uint32_t*)(0x8016EA94u + 0x4);
    r11 = *(uint32_t*)(0x8016EA94u + 0x8);
    *(uint32_t*)(&stack_0x38 + 0x8) = *(uint32_t*)(0x8016EA94u + 0x8);
    r11 = *(uint32_t*)(0x8016EA94u + 0xC);
    *(uint32_t*)(&stack_0x38 + 0xC) = *(uint32_t*)(0x8016EA94u + 0xC);
    r11 = *(uint32_t*)(0x8016EA94u + 0x10);
    *(uint32_t*)(&stack_0x38 + 0x10) = *(uint32_t*)(0x8016EA94u + 0x10);
    r11 = *(uint32_t*)(0x8016EA94u + 0x14);
    r9 = 0x8016EA94u + (24);
    *(uint32_t*)(&stack_0x38 + 0x14) = *(uint32_t*)(0x8016EA94u + 0x14);
    r10 = &stack_0x38 + (24);
    if (*(uint8_t*)(arg0_r3 + 0xF) != 255) goto label_800DAA10;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r0 = SDA1::tex_map;
    r3 = &Specular;
    *(uint32_t*)((&stack_0x38 + 24) + 0x0) = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r3 = (0x43300000u + &Specular);
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    *(uint32_t*)((&stack_0x38 + 24) + 0x4) = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r4 = 0;
    r3 = GXLoadTexObj(); // [0x8012319C]
    r7 = &stack_0x38;
    r10 = 0x8016EA94u;
    r0 = 24;
label_800DAA94:;
    r11 = *(uint32_t*)(0x8016EA94u + 0x0);
    *(uint32_t*)(&stack_0x38 + 0x0) = *(uint32_t*)(0x8016EA94u + 0x0);
    r11 = *(uint32_t*)(0x8016EA94u + 0x4);
    *(uint32_t*)(&stack_0x38 + 0x4) = *(uint32_t*)(0x8016EA94u + 0x4);
    r11 = *(uint32_t*)(0x8016EA94u + 0x8);
    *(uint32_t*)(&stack_0x38 + 0x8) = *(uint32_t*)(0x8016EA94u + 0x8);
    r11 = *(uint32_t*)(0x8016EA94u + 0xC);
    *(uint32_t*)(&stack_0x38 + 0xC) = *(uint32_t*)(0x8016EA94u + 0xC);
    r11 = *(uint32_t*)(0x8016EA94u + 0x10);
    *(uint32_t*)(&stack_0x38 + 0x10) = *(uint32_t*)(0x8016EA94u + 0x10);
    r11 = *(uint32_t*)(0x8016EA94u + 0x14);
    r10 = 0x8016EA94u + (24);
    *(uint32_t*)(&stack_0x38 + 0x14) = *(uint32_t*)(0x8016EA94u + 0x14);
    r7 = &stack_0x38 + (24);
    if (&stack_0x68 != 0) goto label_800DAA94;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r0 = SDA1::tex_coord;
    r9 = 0x8016EAB4u;
    *(uint32_t*)((&stack_0x38 + 24) + 0x0) = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r8 = &stack_0x38;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r10 = 24;
    *(uint32_t*)((&stack_0x38 + 24) + 0x4) = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
label_800DAB00:;
    r11 = *(uint32_t*)(0x8016EAB4u + 0x0);
    *(uint32_t*)(&stack_0x38 + 0x0) = *(uint32_t*)(0x8016EAB4u + 0x0);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x4);
    *(uint32_t*)(&stack_0x38 + 0x4) = *(uint32_t*)(0x8016EAB4u + 0x4);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x8);
    *(uint32_t*)(&stack_0x38 + 0x8) = *(uint32_t*)(0x8016EAB4u + 0x8);
    r11 = *(uint32_t*)(0x8016EAB4u + 0xC);
    *(uint32_t*)(&stack_0x38 + 0xC) = *(uint32_t*)(0x8016EAB4u + 0xC);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x10);
    *(uint32_t*)(&stack_0x38 + 0x10) = *(uint32_t*)(0x8016EAB4u + 0x10);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x14);
    r9 = 0x8016EAB4u + (24);
    *(uint32_t*)(&stack_0x38 + 0x14) = *(uint32_t*)(0x8016EAB4u + 0x14);
    r8 = &stack_0x38 + (24);
    if (&stack_0x68 != 0) goto label_800DAB00;
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0x0);
    r3 = &stack_0x08;
    r0 = SDA1::tex_coord;
    r5 = 0;
    *(uint32_t*)((&stack_0x38 + 24) + 0x0) = *(uint32_t*)((0x8016EAB4u + 24) + 0x0);
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0x4);
    *(uint32_t*)((&stack_0x38 + 24) + 0x4) = *(uint32_t*)((0x8016EAB4u + 24) + 0x4);
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0x8);
    *(uint32_t*)((&stack_0x38 + 24) + 0x8) = *(uint32_t*)((0x8016EAB4u + 24) + 0x8);
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0xC);
    *(uint32_t*)((&stack_0x38 + 24) + 0xC) = *(uint32_t*)((0x8016EAB4u + 24) + 0xC);
    r4 = &stack_0x68;
    r3 = GXLoadTexMtxImm(); // [0x80126120]
    r6 = &stack_0x68;
    r3 = &stack_0x38;
    r4 = 0;
    r5 = 1;
    r7 = 0;
    r8 = 125;
    r3 = GXSetTexCoordGen2(); // [0x8011F908]
    r4 = &stack_0x38;
    r5 = 0;
    r3 = ret_800DA9F4;
    r6 = 4;
    r3 = GXSetTevOrder(); // [0x80124F98]
    if (&stack_0x68 != 0) goto label_800DADEC;
    if (*(uint8_t*)(arg0_r3 + 0x13) == 0) goto label_800DABC4;
    if (*(uint8_t*)(arg0_r3 + 0x13) == 1) goto label_800DADC4;
    goto label_800DAEF8;
label_800DABC4:;
    r0 = SDA1::tev_reg;
    r10 = *(uint32_t*)0x8016EAFC;
    r11 = 0x8016EAFCu;
    r8 = *(uint32_t*)(0x8016EAFCu + 0x8);
    r9 = *(uint32_t*)(0x8016EAFCu + 0x4);
    r3 = ret_800DA9F4;
    stack_0x38 = *(uint32_t*)0x8016EAFC;
    r4 = 15;
    stack_0x3C = *(uint32_t*)(0x8016EAFCu + 0x4);
    r5 = 8;
    stack_0x40 = *(uint32_t*)(0x8016EAFCu + 0x8);
    r6 = 10;
    r7 = 15;
    r3 = GXSetTevColorIn(); // [0x80124A44]
    r8 = &stack_0x68;
    r3 = ret_800DA9F4;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r3 = GXSetTevColorOp(); // [0x80124ACC]
    r3 = ret_800DA9F4;
    r4 = 7;
    r5 = 7;
    r6 = 7;
    r7 = 0;
    r3 = GXSetTevAlphaIn(); // [0x80124A88]
    r8 = 0;
    r7 = 1;
    r6 = 0;
    r5 = 0;
    r3 = ret_800DA9F4;
    r4 = 0;
    r3 = GXSetTevAlphaOp(); // [0x80124B34]
    r11 = SDA1::tev_stage;
    r3 = &tev_stage;
    r9 = SDA1::tex_map;
    r11 = SDA1::tev_stage + (1);
    r9 = SDA1::tex_map + (1);
    SDA1::tev_stage = (SDA1::tev_stage + 1);
    SDA1::tex_map = (SDA1::tex_map + 1);
    r3 = cTevStage::getID(void) const(); // [0x800DBCCC]
    r0 = SDA1::tev_kcolor;
    r9 = 0x8016EAECu;
    r8 = *(uint32_t*)0x8016EAEC;
    r7 = *(uint32_t*)(0x8016EAECu + 0xC);
    r10 = *(uint32_t*)(0x8016EAECu + 0x4);
    r31 = ret_800DAC74;
    r11 = *(uint32_t*)(0x8016EAECu + 0x8);
    stack_0x38 = *(uint32_t*)0x8016EAEC;
    stack_0x3C = *(uint32_t*)(0x8016EAECu + 0x4);
    stack_0x40 = *(uint32_t*)(0x8016EAECu + 0x8);
    stack_0x44 = *(uint32_t*)(0x8016EAECu + 0xC);
    r3 = GXSetTevKColorSel(); // [0x80124CF8]
    r7 = stack_0x9C;
    r9 = 0x8016EADCu;
    r8 = *(uint32_t*)0x8016EADC;
    r11 = *(uint32_t*)(0x8016EADCu + 0x4);
    r4 = &stack_0x98;
    r10 = *(uint32_t*)(0x8016EADCu + 0x8);
    r6 = *(uint32_t*)(0x8016EADCu + 0xC);
    r0 = SDA1::tev_kcolor;
    stack_0x98 = stack_0x9C;
    stack_0x38 = *(uint32_t*)0x8016EADC;
    stack_0x3C = *(uint32_t*)(0x8016EADCu + 0x4);
    stack_0x40 = *(uint32_t*)(0x8016EADCu + 0x8);
    stack_0x44 = *(uint32_t*)(0x8016EADCu + 0xC);
    r3 = GXSetTevKColor(); // [0x80124C84]
    r9 = SDA1::tev_kcolor;
    r3 = ret_800DAC74;
    r4 = 255;
    r5 = 255;
    r9 = SDA1::tev_kcolor + (1);
    r6 = 4;
    SDA1::tev_kcolor = (SDA1::tev_kcolor + 1);
    r3 = GXSetTevOrder(); // [0x80124F98]
    r0 = SDA1::tev_reg;
    r11 = 0x8016EB08u;
    r10 = *(uint32_t*)0x8016EB08;
    r8 = *(uint32_t*)(0x8016EB08u + 0x8);
    r9 = *(uint32_t*)(0x8016EB08u + 0x4);
    r3 = ret_800DAC74;
    stack_0x40 = *(uint32_t*)(0x8016EB08u + 0x8);
    r4 = 15;
    stack_0x3C = *(uint32_t*)(0x8016EB08u + 0x4);
    r5 = 14;
    stack_0x38 = *(uint32_t*)0x8016EB08;
    r7 = 0;
    r3 = GXSetTevColorIn(); // [0x80124A44]
    r8 = 0;
    r3 = ret_800DAC74;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r3 = GXSetTevColorOp(); // [0x80124ACC]
    r3 = ret_800DAC74;
    r4 = 7;
    r5 = 7;
    r6 = 7;
    r7 = 0;
    r3 = GXSetTevAlphaIn(); // [0x80124A88]
    r3 = ret_800DAC74;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r8 = 0;
    r3 = GXSetTevAlphaOp(); // [0x80124B34]
    r9 = SDA1::tev_stage;
    r11 = SDA1::tev_reg;
    r9 = SDA1::tev_stage + (1);
    r11 = SDA1::tev_reg + (1);
    SDA1::tev_stage = (SDA1::tev_stage + 1);
    SDA1::tev_reg = (SDA1::tev_reg + 1);
    goto label_800DAEF8;
label_800DADC4:;
    r3 = ret_800DAC74;
    r4 = 15;
    r5 = 9;
    r6 = 0;
    r7 = 0;
    r3 = GXSetTevColorIn(); // [0x80124A44]
    r8 = 0;
    r3 = ret_800DAC74;
    r4 = 0;
    goto label_800DAE9C;
label_800DADEC:;
    r0 = SDA1::tev_kcolor;
    r9 = 0x8016EAECu;
    r8 = *(uint32_t*)0x8016EAEC;
    r7 = *(uint32_t*)(0x8016EAECu + 0xC);
    r10 = *(uint32_t*)(0x8016EAECu + 0x4);
    r3 = ret_800DAC74;
    r11 = *(uint32_t*)(0x8016EAECu + 0x8);
    stack_0x38 = *(uint32_t*)0x8016EAEC;
    stack_0x3C = *(uint32_t*)(0x8016EAECu + 0x4);
    stack_0x40 = *(uint32_t*)(0x8016EAECu + 0x8);
    stack_0x44 = *(uint32_t*)(0x8016EAECu + 0xC);
    r3 = GXSetTevKColorSel(); // [0x80124CF8]
    r7 = stack_0x9C;
    r9 = 0x8016EADCu;
    r8 = *(uint32_t*)0x8016EADC;
    r11 = *(uint32_t*)(0x8016EADCu + 0x4);
    r4 = &stack_0x98;
    r10 = *(uint32_t*)(0x8016EADCu + 0x8);
    r6 = *(uint32_t*)(0x8016EADCu + 0xC);
    r0 = SDA1::tev_kcolor;
    stack_0x98 = stack_0x9C;
    stack_0x38 = *(uint32_t*)0x8016EADC;
    stack_0x3C = *(uint32_t*)(0x8016EADCu + 0x4);
    stack_0x44 = *(uint32_t*)(0x8016EADCu + 0xC);
    stack_0x40 = *(uint32_t*)(0x8016EADCu + 0x8);
    r3 = GXSetTevKColor(); // [0x80124C84]
    r9 = SDA1::tev_kcolor;
    r3 = ret_800DAC74;
    r4 = 15;
    r5 = 9;
    r9 = SDA1::tev_kcolor + (1);
    r6 = 14;
    SDA1::tev_kcolor = (SDA1::tev_kcolor + 1);
    r7 = 0;
    r3 = GXSetTevColorIn(); // [0x80124A44]
    r8 = 0;
    r3 = ret_800DAC74;
    r4 = 1;
label_800DAE9C:;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r3 = GXSetTevColorOp(); // [0x80124ACC]
    r3 = ret_800DAC74;
    r4 = 7;
    r5 = 7;
    r6 = 7;
    r7 = 0;
    r3 = GXSetTevAlphaIn(); // [0x80124A88]
    r3 = ret_800DAC74;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r8 = 0;
    r3 = GXSetTevAlphaOp(); // [0x80124B34]
    r9 = SDA1::tev_stage;
    r11 = SDA1::tex_map;
    r9 = SDA1::tev_stage + (1);
    r11 = SDA1::tex_map + (1);
    SDA1::tev_stage = (SDA1::tev_stage + 1);
    SDA1::tex_map = (SDA1::tex_map + 1);
label_800DAEF8:;
    r9 = SDA1::tex_coord;
    r9 = SDA1::tex_coord + (1);
    SDA1::tex_coord = (SDA1::tex_coord + 1);
label_800DAF04:;
    r0 = stack_0xD4;
    r12 = stack_0xB4;
    return; // r3 = ret_800DAEDC
}

// ============================================================================
// High-Level AST Decompilation: reflectionSetup(POLY_HEADER *)
// Unit: trans.obj | Address: 0x800DAF20 | Size: 0x2F4 bytes
// ============================================================================
/* [0x800DAF20] */ void reflectionSetup(POLY_HEADER * arg0_r3) {
    // Stack frame allocated: 256 bytes
    stack_0xF8 = f31;
    stack_0x104 = r0;
    r31 = arg0_r3;
    r0 = *(uint8_t*)(arg0_r3 + 0xB);
    if (r0 == 0) goto label_800DB1FC;
    f3 = *(float*)0x8016EB80;
    r30 = &stack_0x38;
    f31 = *(float*)0x8016EB84;
    r29 = &stack_0x68;
    r28 = &stack_0xB8;
    r3 = &stack_0x38;
    r3 = PSMTXScale(); // [0x801014A8]
    f3 = *(float*)0x8016EB88;
    r3 = &stack_0x68;
    r3 = PSMTXTrans(); // [0x80101378]
    r3 = &stack_0x38;
    r5 = &stack_0x08;
    r4 = &specular_mat;
    r3 = PSMTXConcat(); // [0x80100470]
    r4 = &stack_0x08;
    r3 = &stack_0x68;
    r5 = &stack_0x08;
    r3 = PSMTXConcat(); // [0x80100470]
    r9 = SDA1::pG;
    r4 = &stack_0x98;
    r3 = *(uint8_t*)(arg0_r3 + 0x17);
    r30 = &stack_0x98;
    r8 = &stack_0x98;
    r9 = SDA1::pG + (1072);
    r11 = 0x8016EA94u;
    r0 = 24;
label_800DAFD0:;
    r10 = *(uint32_t*)(0x8016EA94u + 0x0);
    *(uint32_t*)(&stack_0x98 + 0x0) = *(uint32_t*)(0x8016EA94u + 0x0);
    r10 = *(uint32_t*)(0x8016EA94u + 0x4);
    *(uint32_t*)(&stack_0x98 + 0x4) = *(uint32_t*)(0x8016EA94u + 0x4);
    r10 = *(uint32_t*)(0x8016EA94u + 0x8);
    *(uint32_t*)(&stack_0x98 + 0x8) = *(uint32_t*)(0x8016EA94u + 0x8);
    r10 = *(uint32_t*)(0x8016EA94u + 0xC);
    *(uint32_t*)(&stack_0x98 + 0xC) = *(uint32_t*)(0x8016EA94u + 0xC);
    r10 = *(uint32_t*)(0x8016EA94u + 0x10);
    *(uint32_t*)(&stack_0x98 + 0x10) = *(uint32_t*)(0x8016EA94u + 0x10);
    r10 = *(uint32_t*)(0x8016EA94u + 0x14);
    r11 = 0x8016EA94u + (24);
    *(uint32_t*)(&stack_0x98 + 0x14) = *(uint32_t*)(0x8016EA94u + 0x14);
    r8 = &stack_0x98 + (24);
    if (r0 != 0) goto label_800DAFD0;
    r10 = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r0 = SDA1::tex_map;
    r3 = *(uint8_t*)(arg0_r3 + 0x17) + (4812);
    *(uint32_t*)((&stack_0x98 + 24) + 0x0) = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r3 = ((SDA1::pG + 1072) + (*(uint8_t*)(arg0_r3 + 0x17) + 4812));
    r10 = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    *(uint32_t*)((&stack_0x98 + 24) + 0x4) = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r4 = arg0_r3;
    r3 = GXLoadTexObj(); // [0x8012319C]
    r7 = &stack_0x98;
    r10 = 0x8016EA94u;
    r0 = 24;
label_800DB050:;
    r11 = *(uint32_t*)(0x8016EA94u + 0x0);
    *(uint32_t*)(&stack_0x98 + 0x0) = *(uint32_t*)(0x8016EA94u + 0x0);
    r11 = *(uint32_t*)(0x8016EA94u + 0x4);
    *(uint32_t*)(&stack_0x98 + 0x4) = *(uint32_t*)(0x8016EA94u + 0x4);
    r11 = *(uint32_t*)(0x8016EA94u + 0x8);
    *(uint32_t*)(&stack_0x98 + 0x8) = *(uint32_t*)(0x8016EA94u + 0x8);
    r11 = *(uint32_t*)(0x8016EA94u + 0xC);
    *(uint32_t*)(&stack_0x98 + 0xC) = *(uint32_t*)(0x8016EA94u + 0xC);
    r11 = *(uint32_t*)(0x8016EA94u + 0x10);
    *(uint32_t*)(&stack_0x98 + 0x10) = *(uint32_t*)(0x8016EA94u + 0x10);
    r11 = *(uint32_t*)(0x8016EA94u + 0x14);
    r10 = 0x8016EA94u + (24);
    *(uint32_t*)(&stack_0x98 + 0x14) = *(uint32_t*)(0x8016EA94u + 0x14);
    r7 = &stack_0x98 + (24);
    if (r0 != 0) goto label_800DB050;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r0 = SDA1::tex_coord;
    r9 = 0x8016EAB4u;
    *(uint32_t*)((&stack_0x98 + 24) + 0x0) = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r8 = &stack_0xB8;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r10 = 24;
    *(uint32_t*)((&stack_0x98 + 24) + 0x4) = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
label_800DB0BC:;
    r11 = *(uint32_t*)(0x8016EAB4u + 0x0);
    *(uint32_t*)(&stack_0xB8 + 0x0) = *(uint32_t*)(0x8016EAB4u + 0x0);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x4);
    *(uint32_t*)(&stack_0xB8 + 0x4) = *(uint32_t*)(0x8016EAB4u + 0x4);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x8);
    *(uint32_t*)(&stack_0xB8 + 0x8) = *(uint32_t*)(0x8016EAB4u + 0x8);
    r11 = *(uint32_t*)(0x8016EAB4u + 0xC);
    *(uint32_t*)(&stack_0xB8 + 0xC) = *(uint32_t*)(0x8016EAB4u + 0xC);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x10);
    *(uint32_t*)(&stack_0xB8 + 0x10) = *(uint32_t*)(0x8016EAB4u + 0x10);
    r11 = *(uint32_t*)(0x8016EAB4u + 0x14);
    r9 = 0x8016EAB4u + (24);
    *(uint32_t*)(&stack_0xB8 + 0x14) = *(uint32_t*)(0x8016EAB4u + 0x14);
    r8 = &stack_0xB8 + (24);
    if (r0 != 0) goto label_800DB0BC;
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0x0);
    r3 = &stack_0x08;
    r0 = SDA1::tex_coord;
    r5 = 0;
    *(uint32_t*)((&stack_0xB8 + 24) + 0x0) = *(uint32_t*)((0x8016EAB4u + 24) + 0x0);
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0x4);
    *(uint32_t*)((&stack_0xB8 + 24) + 0x4) = *(uint32_t*)((0x8016EAB4u + 24) + 0x4);
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0x8);
    *(uint32_t*)((&stack_0xB8 + 24) + 0x8) = *(uint32_t*)((0x8016EAB4u + 24) + 0x8);
    r11 = *(uint32_t*)((0x8016EAB4u + 24) + 0xC);
    *(uint32_t*)((&stack_0xB8 + 24) + 0xC) = *(uint32_t*)((0x8016EAB4u + 24) + 0xC);
    r4 = &stack_0x98;
    r3 = GXLoadTexMtxImm(); // [0x80126120]
    r8 = 125;
    r6 = &stack_0x98;
    r7 = 0;
    r4 = 0;
    r5 = 1;
    r3 = &stack_0x68;
    r3 = GXSetTexCoordGen2(); // [0x8011F908]
    r3 = &tev_stage;
    r3 = cTevStage::getID(void) const(); // [0x800DBCCC]
    r30 = ret_800DB158;
    r4 = &stack_0x68;
    r5 = arg0_r3;
    r6 = 255;
    r3 = GXSetTevOrder(); // [0x80124F98]
    r3 = ret_800DB158;
    r4 = 15;
    r5 = 8;
    r6 = 9;
    r7 = 0;
    r3 = GXSetTevColorIn(); // [0x80124A44]
    r8 = 0;
    r3 = ret_800DB158;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r3 = GXSetTevColorOp(); // [0x80124ACC]
    r3 = ret_800DB158;
    r4 = 7;
    r5 = 7;
    r6 = 7;
    r7 = 0;
    r3 = GXSetTevAlphaIn(); // [0x80124A88]
    r3 = ret_800DB158;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r8 = 0;
    r3 = GXSetTevAlphaOp(); // [0x80124B34]
    r9 = SDA1::tev_stage;
    r11 = SDA1::tex_map;
    r10 = SDA1::tex_coord;
    r9 = SDA1::tev_stage + (1);
    r11 = SDA1::tex_map + (1);
    SDA1::tev_stage = (SDA1::tev_stage + 1);
    r10 = SDA1::tex_coord + (1);
    SDA1::tex_map = (SDA1::tex_map + 1);
    SDA1::tex_coord = (SDA1::tex_coord + 1);
label_800DB1FC:;
    r0 = stack_0x104;
    f31 = stack_0xF8;
    return; // r3 = ret_800DB1D4
}

// ============================================================================
// High-Level AST Decompilation: bumpSetup(POLY_HEADER *)
// Unit: trans.obj | Address: 0x800DB214 | Size: 0x1BC bytes
// ============================================================================
/* [0x800DB214] */ void bumpSetup(POLY_HEADER * arg0_r3) {
    // Stack frame allocated: 48 bytes
    stack_0x34 = r0;
    r30 = arg0_r3;
    r0 = *(uint8_t*)(arg0_r3 + 0xB);
    if (r0 == 0) goto label_800DB24C;
    r3 = 0;
    r3 = GXSetNumIndStages(); // [0x801244B0]
    r3 = 1;
    r3 = GXSetTevDirect(); // [0x801244D8]
    goto label_800DB3BC;
label_800DB24C:;
    r3 = 1;
    r3 = GXSetNumIndStages(); // [0x801244B0]
    r11 = SDA1::pG;
    r3 = *(uint8_t*)(arg0_r3 + 0xD);
    r8 = &stack_0x08;
    r30 = &stack_0x08;
    r9 = 0x8016EA94u;
    r11 = SDA1::pG + (1072);
    r0 = 24;
label_800DB274:;
    r10 = *(uint32_t*)(0x8016EA94u + 0x0);
    *(uint32_t*)(&stack_0x08 + 0x0) = *(uint32_t*)(0x8016EA94u + 0x0);
    r10 = *(uint32_t*)(0x8016EA94u + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)(0x8016EA94u + 0x4);
    r10 = *(uint32_t*)(0x8016EA94u + 0x8);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)(0x8016EA94u + 0x8);
    r10 = *(uint32_t*)(0x8016EA94u + 0xC);
    *(uint32_t*)(&stack_0x08 + 0xC) = *(uint32_t*)(0x8016EA94u + 0xC);
    r10 = *(uint32_t*)(0x8016EA94u + 0x10);
    *(uint32_t*)(&stack_0x08 + 0x10) = *(uint32_t*)(0x8016EA94u + 0x10);
    r10 = *(uint32_t*)(0x8016EA94u + 0x14);
    r9 = 0x8016EA94u + (24);
    *(uint32_t*)(&stack_0x08 + 0x14) = *(uint32_t*)(0x8016EA94u + 0x14);
    r8 = &stack_0x08 + (24);
    if (r0 != 0) goto label_800DB274;
    r10 = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r0 = SDA1::tex_map;
    r3 = *(uint8_t*)(arg0_r3 + 0xD) + (4812);
    *(uint32_t*)((&stack_0x08 + 24) + 0x0) = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r3 = ((SDA1::pG + 1072) + (*(uint8_t*)(arg0_r3 + 0xD) + 4812));
    r10 = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    *(uint32_t*)((&stack_0x08 + 24) + 0x4) = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r4 = r31;
    r3 = GXLoadTexObj(); // [0x8012319C]
    r10 = &stack_0x08;
    r9 = 0x8016EA94u;
    r0 = 24;
label_800DB2F4:;
    r11 = *(uint32_t*)(0x8016EA94u + 0x0);
    *(uint32_t*)(&stack_0x08 + 0x0) = *(uint32_t*)(0x8016EA94u + 0x0);
    r11 = *(uint32_t*)(0x8016EA94u + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)(0x8016EA94u + 0x4);
    r11 = *(uint32_t*)(0x8016EA94u + 0x8);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)(0x8016EA94u + 0x8);
    r11 = *(uint32_t*)(0x8016EA94u + 0xC);
    *(uint32_t*)(&stack_0x08 + 0xC) = *(uint32_t*)(0x8016EA94u + 0xC);
    r11 = *(uint32_t*)(0x8016EA94u + 0x10);
    *(uint32_t*)(&stack_0x08 + 0x10) = *(uint32_t*)(0x8016EA94u + 0x10);
    r11 = *(uint32_t*)(0x8016EA94u + 0x14);
    r9 = 0x8016EA94u + (24);
    *(uint32_t*)(&stack_0x08 + 0x14) = *(uint32_t*)(0x8016EA94u + 0x14);
    r10 = &stack_0x08 + (24);
    if (r0 != 0) goto label_800DB2F4;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r6 = 60;
    r0 = SDA1::tex_coord;
    r7 = 0;
    *(uint32_t*)((&stack_0x08 + 24) + 0x0) = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r8 = 125;
    r11 = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r4 = 1;
    r5 = 4;
    *(uint32_t*)((&stack_0x08 + 24) + 0x4) = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r3 = &stack_0x08;
    r3 = GXSetTexCoordGen2(); // [0x8011F908]
    r3 = 1;
    r3 = GXSetNumIndStages(); // [0x801244B0]
    r4 = &stack_0x08;
    r5 = r31;
    r3 = 0;
    r3 = GXSetIndTexOrder(); // [0x8012439C]
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r3 = GXSetIndTexCoordScale(); // [0x80124220]
    r3 = 1;
    r4 = 0;
    r5 = 1;
    r3 = GXSetTevIndBumpXYZ(); // [0x8012483C]
    r9 = SDA1::tex_map;
    r11 = SDA1::tex_coord;
    r9 = SDA1::tex_map + (1);
    r11 = SDA1::tex_coord + (1);
    SDA1::tex_map = (SDA1::tex_map + 1);
    SDA1::tex_coord = (SDA1::tex_coord + 1);
label_800DB3BC:;
    r0 = stack_0x34;
    return; // r3 = ret_800DB3A0
}

// ============================================================================
// High-Level AST Decompilation: alphaSetup(POLY_HEADER *)
// Unit: trans.obj | Address: 0x800DB3D0 | Size: 0x194 bytes
// ============================================================================
/* [0x800DB3D0] */ void alphaSetup(POLY_HEADER * arg0_r3) {
    // Stack frame allocated: 56 bytes
    stack_0x3C = r0;
    r30 = arg0_r3;
    r0 = *(uint8_t*)(arg0_r3 + 0xB);
    if (r0 == 0) goto label_800DB550;
    r3 = 0;
    r3 = GXSetZCompLoc(); // [0x80125764]
    r4 = *(uint8_t*)(arg0_r3 + 0x14);
    r7 = 255;
    r3 = 4;
    r5 = 1;
    r6 = 4;
    r3 = GXSetAlphaCompare(); // [0x80124EC0]
    r3 = 1;
    r4 = 4;
    r5 = 5;
    r6 = 0;
    r3 = GXSetBlendMode(); // [0x80125684]
    r11 = SDA1::pG;
    r8 = &stack_0x08;
    r9 = 0x8016EA94u;
    r11 = SDA1::pG + (1072);
    r7 = &stack_0x08;
    r0 = 24;
label_800DB440:;
    r10 = *(uint32_t*)(0x8016EA94u + 0x0);
    *(uint32_t*)(&stack_0x08 + 0x0) = *(uint32_t*)(0x8016EA94u + 0x0);
    r10 = *(uint32_t*)(0x8016EA94u + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)(0x8016EA94u + 0x4);
    r10 = *(uint32_t*)(0x8016EA94u + 0x8);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)(0x8016EA94u + 0x8);
    r10 = *(uint32_t*)(0x8016EA94u + 0xC);
    *(uint32_t*)(&stack_0x08 + 0xC) = *(uint32_t*)(0x8016EA94u + 0xC);
    r10 = *(uint32_t*)(0x8016EA94u + 0x10);
    *(uint32_t*)(&stack_0x08 + 0x10) = *(uint32_t*)(0x8016EA94u + 0x10);
    r10 = *(uint32_t*)(0x8016EA94u + 0x14);
    r9 = 0x8016EA94u + (24);
    *(uint32_t*)(&stack_0x08 + 0x14) = *(uint32_t*)(0x8016EA94u + 0x14);
    r8 = &stack_0x08 + (24);
    if (r0 != 0) goto label_800DB440;
    r10 = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r0 = SDA1::tex_map;
    *(uint32_t*)((&stack_0x08 + 24) + 0x0) = *(uint32_t*)((0x8016EA94u + 24) + 0x0);
    r10 = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r3 = *(uint8_t*)(arg0_r3 + 0xE);
    *(uint32_t*)((&stack_0x08 + 24) + 0x4) = *(uint32_t*)((0x8016EA94u + 24) + 0x4);
    r3 = *(uint8_t*)(arg0_r3 + 0xE) + (4812);
    r3 = ((SDA1::pG + 1072) + (*(uint8_t*)(arg0_r3 + 0xE) + 4812));
    r4 = r29;
    r3 = GXLoadTexObj(); // [0x8012319C]
    r3 = &tev_stage;
    r3 = cTevStage::getID(void) const(); // [0x800DBCCC]
    r30 = ret_800DB4B8;
    r5 = r29;
    r4 = 0;
    r6 = 4;
    r3 = GXSetTevOrder(); // [0x80124F98]
    r3 = ret_800DB4B8;
    r4 = 15;
    r5 = 15;
    r6 = 15;
    r7 = 0;
    r3 = GXSetTevColorIn(); // [0x80124A44]
    r8 = 0;
    r3 = ret_800DB4B8;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r3 = GXSetTevColorOp(); // [0x80124ACC]
    r3 = ret_800DB4B8;
    r4 = 7;
    r5 = 4;
    r6 = 0;
    r7 = 7;
    r3 = GXSetTevAlphaIn(); // [0x80124A88]
    r3 = ret_800DB4B8;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r8 = 0;
    r3 = GXSetTevAlphaOp(); // [0x80124B34]
    r9 = SDA1::tev_stage;
    r11 = SDA1::tex_map;
    r9 = SDA1::tev_stage + (1);
    r11 = SDA1::tex_map + (1);
    SDA1::tev_stage = (SDA1::tev_stage + 1);
    SDA1::tex_map = (SDA1::tex_map + 1);
label_800DB550:;
    r0 = stack_0x3C;
    return; // r3 = ret_800DB534
}

// ============================================================================
// High-Level AST Decompilation: shaderReset(void)
// Unit: trans.obj | Address: 0x800DB564 | Size: 0x78 bytes
// ============================================================================
/* [0x800DB564] */ void shaderReset(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = 0;
    r3 = GXSetNumIndStages(); // [0x801244B0]
    r3 = 1;
    r3 = GXSetTevDirect(); // [0x801244D8]
    r8 = 0;
    r9 = 2;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r3 = GXSetChanCtrl(); // [0x801223B8]
    r3 = 7;
    r4 = 0;
    r5 = 1;
    r6 = 7;
    r7 = 0;
    r3 = GXSetAlphaCompare(); // [0x80124EC0]
    r3 = 0;
    r4 = 1;
    r5 = 0;
    r6 = 0;
    r3 = GXSetBlendMode(); // [0x80125684]
    r0 = stack_0x0C;
    return; // r3 = ret_800DB5C8
}

// ============================================================================
// High-Level AST Decompilation: CalcSk1(float (*)[2], signed char *, signed char *)
// Unit: trans.obj | Address: 0x800DB5DC | Size: 0x20 bytes
// ============================================================================
/* [0x800DB5DC] */ void CalcSk1(float (* arg0_r3) {
}

// ============================================================================
// High-Level AST Decompilation: loop_1bone
// Unit: trans.obj | Address: 0x800DB5FC | Size: 0x40 bytes
// ============================================================================
/* [0x800DB5FC] */ void loop_1bone(void) {
    return; // r3 = r3
    return; // r3 = r3
    // Stack frame allocated: 152 bytes
}

// ============================================================================
// High-Level AST Decompilation: setupGQR6(unsigned long)
// Unit: trans.obj | Address: 0x800DB628 | Size: 0x8 bytes
// ============================================================================
/* [0x800DB628] */ void setupGQR6(unsigned long arg0_r3) {
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: ClearAlphabuf(void)
// Unit: trans.obj | Address: 0x800DB630 | Size: 0x240 bytes
// ============================================================================
/* [0x800DB630] */ void ClearAlphabuf(void) {
    // Stack frame allocated: 152 bytes
    stack_0x9C = r0;
    r3 = 0;
    r3 = GXSetColorUpdate(); // [0x801256D8]
    r3 = 1;
    r3 = GXSetAlphaUpdate(); // [0x80125704]
    r30 = &stack_0x48;
    r4 = 0;
    r3 = 1;
    r3 = GXSetDstAlpha(); // [0x801258B0]
    r3 = 0;
    r3 = GXSetCullMode(); // [0x80120D3C]
    r5 = 0;
    r4 = 7;
    r3 = 1;
    r3 = GXSetZMode(); // [0x80125730]
    f1 = *(float*)0x8016EB8C;
    f6 = *(float*)0x8016EB98;
    r3 = &stack_0x08;
    f2 = *(float*)0x8016EB90;
    f4 = *(float*)0x8016EB94;
    r3 = C_MTXOrtho(); // [0x8010242C]
    r3 = &stack_0x08;
    r4 = 1;
    r3 = GXSetProjection(); // [0x80125D20]
    r3 = &stack_0x48;
    r3 = PSMTXIdentity(); // [0x801000FC]
    r4 = 0;
    r3 = &stack_0x48;
    r3 = GXLoadPosMtxImm(); // [0x80125FAC]
    r3 = 0;
    r3 = GXSetCurrentMtx(); // [0x801260E8]
    r3 = 1;
    r3 = GXSetNumTevStages(); // [0x80125170]
    r3 = 1;
    r3 = GXSetNumChans(); // [0x80122374]
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r8 = 2;
    r9 = 2;
    r3 = GXSetChanCtrl(); // [0x801223B8]
    r9 = 2;
    r8 = 2;
    r7 = 0;
    r3 = 2;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r3 = GXSetChanCtrl(); // [0x801223B8]
    r3 = 0;
    r4 = 255;
    r5 = 255;
    r6 = 4;
    r3 = GXSetTevOrder(); // [0x80124F98]
    r3 = 0;
    r4 = 15;
    r5 = 15;
    r6 = 15;
    r7 = 0;
    r3 = GXSetTevColorIn(); // [0x80124A44]
    r8 = 0;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r3 = GXSetTevColorOp(); // [0x80124ACC]
    r3 = 0;
    r4 = 7;
    r5 = 7;
    r6 = 7;
    r7 = 0;
    r3 = GXSetTevAlphaIn(); // [0x80124A88]
    r8 = 0;
    r7 = 1;
    r5 = 0;
    r6 = 0;
    r3 = 0;
    r4 = 0;
    r3 = GXSetTevAlphaOp(); // [0x80124B34]
    r0 = SDA1::colZero;
    r4 = &stack_0x78;
    r3 = 4;
    stack_0x78 = SDA1::colZero;
    r3 = GXSetChanMatColor(); // [0x80122280]
    r5 = 1;
    r6 = 0;
    r3 = 1;
    r4 = 4;
    r3 = GXSetBlendMode(); // [0x80125684]
    r3 = GXClearVtxDesc(); // [0x8011EDD4]
    r3 = 9;
    r4 = 1;
    r3 = GXSetVtxDesc(); // [0x8011E354]
    r6 = 4;
    r7 = 0;
    r3 = 0;
    r4 = 9;
    r5 = 1;
    r3 = GXSetVtxAttrFmt(); // [0x8011EE0C]
    r4 = 0;
    r5 = 4;
    r3 = 128;
    r3 = GXBegin(); // [0x80120A9C]
    f0 = *(float*)0x8016EB8C;
    f13 = SDA1::TEST_Z.1277;
    r3 = 1;
    *(float*)0xCC008000 = *(float*)0x8016EB8C;
    *(float*)0xCC008000 = *(float*)0x8016EB8C;
    f11 = *(float*)0x8016EB94;
    *(float*)0xCC008000 = SDA1::TEST_Z.1277;
    *(float*)0xCC008000 = *(float*)0x8016EB94;
    *(float*)0xCC008000 = *(float*)0x8016EB8C;
    *(float*)0xCC008000 = SDA1::TEST_Z.1277;
    f12 = *(float*)0x8016EB90;
    *(float*)0xCC008000 = *(float*)0x8016EB94;
    *(float*)0xCC008000 = *(float*)0x8016EB90;
    *(float*)0xCC008000 = SDA1::TEST_Z.1277;
    *(float*)0xCC008000 = *(float*)0x8016EB8C;
    *(float*)0xCC008000 = *(float*)0x8016EB90;
    *(float*)0xCC008000 = SDA1::TEST_Z.1277;
    r3 = GXSetColorUpdate(); // [0x801256D8]
    r3 = 0;
    r3 = GXSetAlphaUpdate(); // [0x80125704]
    r3 = 0;
    r4 = 0;
    r3 = GXSetDstAlpha(); // [0x801258B0]
    r0 = stack_0x9C;
    return; // r3 = ret_800DB858
}

// ============================================================================
// High-Level AST Decompilation: ClearZbuf(void)
// Unit: trans.obj | Address: 0x800DB870 | Size: 0x228 bytes
// ============================================================================
/* [0x800DB870] */ void ClearZbuf(void) {
    // Stack frame allocated: 152 bytes
    stack_0x9C = r0;
    r3 = 0;
    r3 = GXSetColorUpdate(); // [0x801256D8]
    r3 = 0;
    r3 = GXSetAlphaUpdate(); // [0x80125704]
    r30 = &stack_0x48;
    r3 = 0;
    r3 = GXSetCullMode(); // [0x80120D3C]
    r5 = 1;
    r4 = 7;
    r3 = 1;
    r3 = GXSetZMode(); // [0x80125730]
    f1 = *(float*)0x8016EB9C;
    f6 = *(float*)0x8016EBA8;
    r3 = &stack_0x08;
    f2 = *(float*)0x8016EBA0;
    f4 = *(float*)0x8016EBA4;
    r3 = C_MTXOrtho(); // [0x8010242C]
    r3 = &stack_0x08;
    r4 = 1;
    r3 = GXSetProjection(); // [0x80125D20]
    r3 = &stack_0x48;
    r3 = PSMTXIdentity(); // [0x801000FC]
    r4 = 0;
    r3 = &stack_0x48;
    r3 = GXLoadPosMtxImm(); // [0x80125FAC]
    r3 = 0;
    r3 = GXSetCurrentMtx(); // [0x801260E8]
    r3 = 1;
    r3 = GXSetNumTevStages(); // [0x80125170]
    r3 = 1;
    r3 = GXSetNumChans(); // [0x80122374]
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r8 = 2;
    r9 = 2;
    r3 = GXSetChanCtrl(); // [0x801223B8]
    r9 = 2;
    r8 = 2;
    r7 = 0;
    r3 = 2;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r3 = GXSetChanCtrl(); // [0x801223B8]
    r3 = 0;
    r4 = 255;
    r5 = 255;
    r6 = 4;
    r3 = GXSetTevOrder(); // [0x80124F98]
    r3 = 0;
    r4 = 15;
    r5 = 15;
    r6 = 15;
    r7 = 0;
    r3 = GXSetTevColorIn(); // [0x80124A44]
    r8 = 0;
    r3 = 0;
    r4 = 0;
    r5 = 0;
    r6 = 0;
    r7 = 1;
    r3 = GXSetTevColorOp(); // [0x80124ACC]
    r3 = 0;
    r4 = 7;
    r5 = 7;
    r6 = 7;
    r7 = 0;
    r3 = GXSetTevAlphaIn(); // [0x80124A88]
    r8 = 0;
    r7 = 1;
    r5 = 0;
    r6 = 0;
    r3 = 0;
    r4 = 0;
    r3 = GXSetTevAlphaOp(); // [0x80124B34]
    r0 = SDA1::col.1281;
    r4 = &stack_0x78;
    r3 = 4;
    stack_0x78 = SDA1::col.1281;
    r3 = GXSetChanMatColor(); // [0x80122280]
    r5 = 1;
    r6 = 0;
    r3 = 1;
    r4 = 4;
    r3 = GXSetBlendMode(); // [0x80125684]
    r3 = GXClearVtxDesc(); // [0x8011EDD4]
    r3 = 9;
    r4 = 1;
    r3 = GXSetVtxDesc(); // [0x8011E354]
    r6 = 4;
    r7 = 0;
    r3 = 0;
    r4 = 9;
    r5 = 1;
    r3 = GXSetVtxAttrFmt(); // [0x8011EE0C]
    r3 = 128;
    r4 = 0;
    r5 = 4;
    r3 = GXBegin(); // [0x80120A9C]
    f0 = *(float*)0x8016EB9C;
    f13 = SDA1::TEST_Z.1282;
    r3 = 1;
    *(float*)0xCC008000 = *(float*)0x8016EB9C;
    *(float*)0xCC008000 = *(float*)0x8016EB9C;
    f11 = *(float*)0x8016EBA4;
    *(float*)0xCC008000 = SDA1::TEST_Z.1282;
    *(float*)0xCC008000 = *(float*)0x8016EBA4;
    *(float*)0xCC008000 = *(float*)0x8016EB9C;
    *(float*)0xCC008000 = SDA1::TEST_Z.1282;
    f12 = *(float*)0x8016EBA0;
    *(float*)0xCC008000 = *(float*)0x8016EBA4;
    *(float*)0xCC008000 = *(float*)0x8016EBA0;
    *(float*)0xCC008000 = SDA1::TEST_Z.1282;
    *(float*)0xCC008000 = *(float*)0x8016EB9C;
    *(float*)0xCC008000 = *(float*)0x8016EBA0;
    *(float*)0xCC008000 = SDA1::TEST_Z.1282;
    r3 = GXSetColorUpdate(); // [0x801256D8]
    r3 = 0;
    r3 = GXSetAlphaUpdate(); // [0x80125704]
    r0 = stack_0x9C;
    return; // r3 = ret_800DBA80
}

// ============================================================================
// High-Level AST Decompilation: SpecularInit(unsigned long)
// Unit: trans.obj | Address: 0x800DBA98 | Size: 0xF8 bytes
// ============================================================================
/* [0x800DBA98] */ void SpecularInit(unsigned long arg0_r3) {
    // Stack frame allocated: 48 bytes
    stack_0x28 = f31;
    stack_0x34 = r0;
    r28 = arg0_r3;
    r29 = 0;
    r3 = calcTplAddr(arg0_r3); // [0x80074348]
    r27 = *(uint32_t*)(arg0_r3 + 0x4);
    if (0 >= *(uint32_t*)(arg0_r3 + 0x4)) goto label_800DBB78;
    f31 = *(double*)0x8016EBB0;
    r31 = &Specular;
label_800DBAD8:;
    r4 = 0;
    r3 = arg0_r3;
    r3 = TEXGet(); // [0x80127870]
    r29 = 0 + (1);
    r30 = ret_800DBAE0;
    r9 = 0;
    r11 = *(uint32_t*)(ret_800DBAE0 + 0x0);
    r10 = 0;
    r3 = &Specular;
    r8 = 0;
    r7 = *(uint32_t*)(*(uint32_t*)(ret_800DBAE0 + 0x0) + 0x4);
    r4 = *(uint32_t*)(*(uint32_t*)(ret_800DBAE0 + 0x0) + 0x8);
    r5 = *(uint16_t*)(*(uint32_t*)(ret_800DBAE0 + 0x0) + 0x2);
    r6 = *(uint16_t*)(*(uint32_t*)(ret_800DBAE0 + 0x0) + 0x0);
    r3 = GXInitTexObj(); // [0x8012270C]
    r9 = *(uint32_t*)(ret_800DBAE0 + 0x0);
    r10 = *(uint32_t*)(ret_800DBAE0 + 0x0);
    r3 = &Specular;
    r0 = *(uint8_t*)(*(uint32_t*)(ret_800DBAE0 + 0x0) + 0x21);
    r4 = 1;
    r30 = *(uint8_t*)(*(uint32_t*)(ret_800DBAE0 + 0x0) + 0x22);
    r5 = 1;
    stack_0x0C = *(uint8_t*)(*(uint32_t*)(ret_800DBAE0 + 0x0) + 0x21);
    r6 = 0;
    r7 = *(uint8_t*)(*(uint32_t*)(ret_800DBAE0 + 0x0) + 0x20);
    r8 = 0;
    stack_0x08 = 0x43300000u;
    r31 = &Specular + (32);
    f3 = *(float*)(*(uint32_t*)(ret_800DBAE0 + 0x0) + 0x1C);
    f1 = stack_0x08;
    stack_0x0C = *(uint8_t*)(*(uint32_t*)(ret_800DBAE0 + 0x0) + 0x22);
    stack_0x08 = 0x43300000u;
    f2 = stack_0x08;
    r3 = GXInitTexObjLOD(); // [0x801229C8]
    if ((0 + 1) < *(uint32_t*)(arg0_r3 + 0x4)) goto label_800DBAD8;
label_800DBB78:;
    r0 = stack_0x34;
    f31 = stack_0x28;
    return; // r3 = ret_800DBB6C
}

// ============================================================================
// High-Level AST Decompilation: updateMatrices(float (*)[3], float (*)[3], tagCOMN *)
// Unit: trans.obj | Address: 0x800DBB90 | Size: 0xE8 bytes
// ============================================================================
/* [0x800DBB90] */ void updateMatrices(float (* arg0_r3) {
    // Stack frame allocated: 296 bytes
    stack_0x12C = r0;
    r9 = SDA1::pG;
    r0 = arg0_r3;
    r27 = r4;
    r5 = &stack_0x08;
    r4 = arg0_r3;
    r3 = SDA1::pG + (852);
    r3 = PSMTXConcat(); // [0x80100470]
    r29 = &stack_0x98;
    r3 = &stack_0x08;
    r4 = &stack_0x98;
    r3 = PSMTXInverse(); // [0x80100A94]
    r28 = &stack_0x38;
    r3 = &stack_0x98;
    r4 = &stack_0x38;
    r3 = PSMTXTranspose(); // [0x80100798]
    r30 = &stack_0xE0;
    r3 = &stack_0x08;
    r4 = &stack_0xE0;
    r3 = PSMTXInverse(); // [0x80100A94]
    r4 = r4;
    r3 = &stack_0xE0;
    r3 = PSMTXTranspose(); // [0x80100798]
    r3 = &stack_0x98;
    f1 = *(float*)0x8016EBB8;
    r3 = PSMTXScale(); // [0x801014A8]
    r3 = &stack_0x98;
    r4 = &stack_0x38;
    r5 = &stack_0x68;
    r3 = PSMTXConcat(); // [0x80100470]
    f0 = stack_0x7C;
    r3 = 1;
    f9 = stack_0x68;
    r4 = &stack_0xC8;
    f10 = stack_0x6C;
    f12 = stack_0x70;
    r5 = 0;
    f13 = stack_0x78;
    f11 = stack_0x80;
    stack_0xC8 = stack_0x68;
    stack_0xCC = stack_0x6C;
    stack_0xD0 = stack_0x70;
    stack_0xD4 = stack_0x78;
    stack_0xD8 = stack_0x7C;
    stack_0xDC = stack_0x80;
    r3 = GXSetIndTexMtx(); // [0x801240C0]
    r0 = stack_0x12C;
    return; // r3 = ret_800DBC60
}

// ============================================================================
// High-Level AST Decompilation: __static_initialization_and_destruction_0
// Unit: trans.obj | Address: 0x800DBC78 | Size: 0x54 bytes
// ============================================================================
/* [0x800DBC78] */ void __static_initialization_and_destruction_0(void) {
    r0 = 0;
    r0 = 0 | 0xFFFFu;
    if (r3 == 0) goto label_800DBCB8;
    r9 = &CountDown;
    r11 = &vtable_cCountDown;
    r10 = 0;
    r0 = 9000;
    *(uint32_t*)(&CountDown + 0x20) = 9000;
    *(uint32_t*)(&CountDown + 0x18) = &vtable_cCountDown;
    *(uint32_t*)(&CountDown + 0x1C) = 0;
    return; // r3 = r3
label_800DBCB8:;
    r9 = &vtable_cIdMain;
    *(uint32_t*)0x801CAFC0 = &vtable_cIdMain;
    return; // r3 = r3
}

// ============================================================================
// High-Level AST Decompilation: cTevStage::getID(void) const
// Unit: trans.obj | Address: 0x800DBCCC | Size: 0x18 bytes
// ============================================================================
/* [0x800DBCCC] */ void cTevStage::getID(void) const(void) {
    r0 = *(uint32_t*)(r3 + 0x0);
    r9 = &tbl.1176;
    return; // r3 = r3
}

// ============================================================================
// High-Level AST Decompilation: cCountDown::~cCountDown(void)
// Unit: trans.obj | Address: 0x800DBCE4 | Size: 0x34 bytes
// ============================================================================
/* [0x800DBCE4] */ void cCountDown::~cCountDown(cCountDown* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = &vtable_cIdMain;
    *(uint32_t*)(this_r3 + 0x18) = &vtable_cIdMain;
    if (r0 == 0) goto label_800DBD08;
    r3 = __builtin_delete(); // [0x8009C908]
label_800DBD08:;
    r0 = stack_0x0C;
    return; // r3 = ret_800DBD04
}

// ============================================================================
// High-Level AST Decompilation: global constructors keyed to boostFlag
// Unit: trans.obj | Address: 0x800DBD18 | Size: 0x2C bytes
// ============================================================================
/* [0x800DBD18] */ void global constructors keyed to boostFlag(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r4 = 0;
    r3 = 1;
    r4 = 0 | 0xFFFFu;
    r3 = __static_initialization_and_destruction_0(); // [0x800DBC78]
    r0 = stack_0x0C;
    return; // r3 = ret_800DBD30
}

// ============================================================================
// High-Level AST Decompilation: global destructors keyed to boostFlag
// Unit: trans.obj | Address: 0x800DBD44 | Size: 0x2C bytes
// ============================================================================
/* [0x800DBD44] */ void global destructors keyed to boostFlag(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r4 = 0;
    r3 = 0;
    r4 = 0 | 0xFFFFu;
    r3 = __static_initialization_and_destruction_0(); // [0x800DBC78]
    r0 = stack_0x0C;
    return; // r3 = ret_800DBD5C
}
