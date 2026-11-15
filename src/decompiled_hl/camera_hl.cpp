// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: camera.obj
// Functions Decompiled: 15
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: CameraSetProjection(unsigned long)
// Unit: camera.obj | Address: 0x8001A560 | Size: 0x54 bytes
// ============================================================================
/* [0x8001A560] */ void CameraSetProjection(unsigned long arg0_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    if (arg0_r3 == 1) goto label_8001A580;
    if (arg0_r3 == 2) goto label_8001A594;
    goto label_8001A5A4;
label_8001A580:;
    r3 = SDA1::pG;
    r4 = 0;
    r3 = SDA1::pG + (948);
    r3 = GXSetProjection(); // [0x80125D20]
    goto label_8001A5A4;
label_8001A594:;
    r3 = SDA1::pG;
    r4 = 1;
    r3 = SDA1::pG + (948);
    r3 = GXSetProjection(); // [0x80125D20]
label_8001A5A4:;
    r0 = stack_0x0C;
    return; // r3 = ret_8001A5A0
}

// ============================================================================
// High-Level AST Decompilation: CameraCurrentProjection(void)
// Unit: camera.obj | Address: 0x8001A5B4 | Size: 0x24 bytes
// ============================================================================
/* [0x8001A5B4] */ void CameraCurrentProjection(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = SDA1::ProjType;
    r3 = CameraSetProjection(SDA1::ProjType); // [0x8001A560]
    r0 = stack_0x0C;
    return; // r3 = ret_8001A5C4
}

// ============================================================================
// High-Level AST Decompilation: CameraGetProjection(void)
// Unit: camera.obj | Address: 0x8001A5D8 | Size: 0x8 bytes
// ============================================================================
/* [0x8001A5D8] */ void CameraGetProjection(void) {
    r3 = SDA1::ProjType;
    return; // r3 = SDA1::ProjType
}

// ============================================================================
// High-Level AST Decompilation: get_angle(tagCAMERA *)
// Unit: camera.obj | Address: 0x8001A5E0 | Size: 0x110 bytes
// ============================================================================
/* [0x8001A5E0] */ void get_angle(tagCAMERA * arg0_r3) {
    // Stack frame allocated: 80 bytes
    stack_0x54 = r0;
    r31 = arg0_r3;
    f12 = *(float*)(arg0_r3 + 0x10C);
    f13 = *(float*)(arg0_r3 + 0x100);
    f0 = *(float*)(arg0_r3 + 0x104);
    f11 = *(float*)(arg0_r3 + 0x110);
    f10 = *(float*)(arg0_r3 + 0x108);
    f12 = *(float*)(arg0_r3 + 0x114);
    f9 = *(float*)0x80163E54;
    stack_0x0C = *(float*)(arg0_r3 + 0x104);
    stack_0x08 = *(float*)(arg0_r3 + 0x100);
    stack_0x10 = *(float*)(arg0_r3 + 0x108);
    if (r0 != 0) goto label_8001A644;
    if (r0 != 0) goto label_8001A644;
    *(float*)(arg0_r3 + 0x128) = *(float*)0x80163E54;
    goto label_8001A660;
label_8001A644:;
    f1 = stack_0x08;
    f2 = stack_0x10;
    r3 = atan2f(); // [0x800E3930]
    f0 = *(float*)0x80163E58;
    *(float*)(arg0_r3 + 0x128) = stack_0x08;
label_8001A660:;
    f1 = *(float*)(arg0_r3 + 0x128);
    f0 = *(float*)0x80163E5C;
    r30 = &stack_0x18;
    r3 = &stack_0x18;
    r4 = 121;
    r3 = PSMTXRotRad(); // [0x80100EE0]
    r4 = &stack_0x08;
    r3 = &stack_0x18;
    r5 = &stack_0x08;
    r3 = PSMTXMultVec(); // [0x80101CC8]
    f0 = stack_0x0C;
    f13 = *(float*)0x80163E54;
    if (r0 != 0) goto label_8001A6BC;
    f0 = stack_0x10;
    if (r0 != 0) goto label_8001A6BC;
    *(float*)(arg0_r3 + 0x124) = *(float*)0x80163E54;
    goto label_8001A6DC;
label_8001A6BC:;
    f1 = stack_0x0C;
    f2 = stack_0x10;
    r3 = atan2f(); // [0x800E3930]
    f0 = *(float*)0x80163E58;
    *(float*)(arg0_r3 + 0x124) = stack_0x0C;
label_8001A6DC:;
    r0 = stack_0x54;
    return; // r3 = ret_8001A6C4
}

// ============================================================================
// High-Level AST Decompilation: CameraInit(void)
// Unit: camera.obj | Address: 0x8001A6F0 | Size: 0x4C bytes
// ============================================================================
/* [0x8001A6F0] */ void CameraInit(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = SDA1::pG;
    f1 = SDA1::roll.674;
    f2 = SDA1::fovy.675;
    r3 = SDA1::pG + (756);
    r4 = &campos.673;
    r5 = &target.672;
    r3 = CameraSetWithRoll((SDA1::pG + 756), &campos.673, &target.672, SDA1::roll.674, SDA1::fovy.675); // [0x8001A480]
    r3 = SDA1::pG;
    r3 = SDA1::pG + (756);
    r3 = CameraSetOrientationRoll((SDA1::pG + 756)); // [0x80019D18]
    r0 = stack_0x0C;
    return; // r3 = ret_8001A728
}

// ============================================================================
// High-Level AST Decompilation: SetCameraMotion(unsigned long)
// Unit: camera.obj | Address: 0x8001A73C | Size: 0x34 bytes
// ============================================================================
/* [0x8001A73C] */ void SetCameraMotion(unsigned long arg0_r3) {
    r11 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x154);
    r9 = arg0_r3 + (4);
    *(uint32_t*)(SDA1::pG + 0x154) = *(uint32_t*)(SDA1::pG + 0x154);
    SDA1::ppp = arg0_r3;
    r0 = *(uint32_t*)(arg0_r3 + 0x0);
    SDA1::ppp = (arg0_r3 + 4);
    SDA1::max_frame = *(uint32_t*)(arg0_r3 + 0x0);
    SDA1::frame = r10;
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: CameraMove(void)
// Unit: camera.obj | Address: 0x8001A770 | Size: 0x24 bytes
// ============================================================================
/* [0x8001A770] */ void CameraMove(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = CamCtrlMove(); // [0x80018340]
    r3 = CameraUpdate(); // [0x8001A794]
    r0 = stack_0x0C;
    return; // r3 = ret_8001A780
}

// ============================================================================
// High-Level AST Decompilation: CameraUpdate(void)
// Unit: camera.obj | Address: 0x8001A794 | Size: 0xA8 bytes
// ============================================================================
/* [0x8001A794] */ void CameraUpdate(void) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r30 = SDA1::pG;
    r29 = SDA1::pG + (756);
    r28 = SDA1::pG + (1012);
    r3 = (SDA1::pG + 756);
    r27 = SDA1::pG + (1024);
    r3 = CameraSetOrientationRoll((SDA1::pG + 756)); // [0x80019D18]
    f2 = *(float*)0x80163E60;
    r3 = SDA1::pG + (948);
    f3 = SDA1::ZNEAR;
    f4 = SDA1::ZFAR;
    f1 = *(float*)((SDA1::pG + 756) + 0x130);
    r3 = C_MTXPerspective(); // [0x8010235C]
    r3 = (SDA1::pG + 1012);
    r4 = (SDA1::pG + 1024);
    r3 = PSVECDistance(); // [0x80103F68]
    *(float*)((SDA1::pG + 756) + 0x138) = *(float*)((SDA1::pG + 756) + 0x130);
    r4 = (SDA1::pG + 1012);
    r5 = SDA1::pG + (1036);
    r6 = (SDA1::pG + 1024);
    r3 = SDA1::pG + (852);
    r3 = C_MTXLookAt(); // [0x801018C0]
    f13 = *(float*)((SDA1::pG + 756) + 0x130);
    f0 = SDA1::old_Fovy.685;
    if (r0 == 0) goto label_8001A824;
    f2 = *(float*)0x80163E60;
    f3 = SDA1::ZNEAR;
    f4 = SDA1::ZFAR;
    SDA1::old_Fovy.685 = *(float*)((SDA1::pG + 756) + 0x130);
    r3 = ViewInitPerspective(*(float*)((SDA1::pG + 756) + 0x130), *(float*)0x80163E60, SDA1::ZNEAR, SDA1::ZFAR); // [0x800DE730]
label_8001A824:;
    r3 = ViewOrientation(); // [0x800DEC48]
    r0 = stack_0x24;
    return; // r3 = ret_8001A824
}

// ============================================================================
// High-Level AST Decompilation: CameraMotionSet(_MOTION_INFO *, void *, unsigned long, float)
// Unit: camera.obj | Address: 0x8001A83C | Size: 0xFC bytes
// ============================================================================
/* [0x8001A83C] */ void CameraMotionSet(_MOTION_INFO * arg0_r3, void * arg1_r4, unsigned long arg2_r5, float arg3_f1) {
    // Stack frame allocated: 16 bytes
    *(uint32_t*)(arg0_r3 + 0x0) = arg1_r4;
    r0 = *(uint16_t*)(arg1_r4 + 0x0);
    r8 = arg1_r4 + (3);
    f13 = *(double*)0x80163E68;
    stack_0x0C = *(uint16_t*)(arg1_r4 + 0x0);
    stack_0x08 = 0x43300000u;
    f0 = stack_0x08;
    *(float*)(arg0_r3 + 0x224) = stack_0x08;
    r0 = *(uint8_t*)(arg1_r4 + 0x2);
    *(uint32_t*)(arg0_r3 + 0x234) = (arg1_r4 + 3);
    r11 = *(uint8_t*)(arg1_r4 + 0x2);
    *(uint8_t*)(arg0_r3 + 0x22C) = *(uint8_t*)(arg1_r4 + 0x2);
    r9 = (*(uint8_t*)(arg1_r4 + 0x2) + *(uint8_t*)(arg1_r4 + 0x2));
    r9 = (*(uint8_t*)(arg1_r4 + 0x2) + *(uint8_t*)(arg1_r4 + 0x2)) + (3);
    r4 = (arg1_r4 + ((*(uint8_t*)(arg1_r4 + 0x2) + *(uint8_t*)(arg1_r4 + 0x2)) + 3));
    r8 = ((arg1_r4 + ((*(uint8_t*)(arg1_r4 + 0x2) + *(uint8_t*)(arg1_r4 + 0x2)) + 3)) + *(uint8_t*)(arg1_r4 + 0x2));
    *(uint32_t*)(arg0_r3 + 0x230) = (arg1_r4 + ((*(uint8_t*)(arg1_r4 + 0x2) + *(uint8_t*)(arg1_r4 + 0x2)) + 3));
    r0 = ((arg1_r4 + ((*(uint8_t*)(arg1_r4 + 0x2) + *(uint8_t*)(arg1_r4 + 0x2)) + 3)) + *(uint8_t*)(arg1_r4 + 0x2)) + (3);
    if (((*(uint8_t*)(arg1_r4 + 0x2) + *(uint8_t*)(arg1_r4 + 0x2)) + 3) < 0) goto label_8001A8E4;
    r10 = 0;
    if (0 >= *(uint8_t*)(arg1_r4 + 0x2)) goto label_8001A8E4;
    r11 = 0;
label_8001A8C0:;
    r10 = 0 + (1);
    r9 = *(uint32_t*)(arg0_r3 + 0x0);
    r0 = ((((arg1_r4 + ((*(uint8_t*)(arg1_r4 + 0x2) + *(uint8_t*)(arg1_r4 + 0x2)) + 3)) + *(uint8_t*)(arg1_r4 + 0x2)) + 3) + *(uint32_t*)(arg0_r3 + 0x0));
    r11 = 0 + (4);
    r0 = *(uint8_t*)(arg0_r3 + 0x22C);
    if ((0 + 1) < *(uint8_t*)(arg0_r3 + 0x22C)) goto label_8001A8C0;
label_8001A8E4:;
    r0 = *(uint8_t*)(arg0_r3 + 0x22C);
    r10 = 0;
    *(uint32_t*)(arg0_r3 + 0x4) = ((arg1_r4 + ((*(uint8_t*)(arg1_r4 + 0x2) + *(uint8_t*)(arg1_r4 + 0x2)) + 3)) + *(uint8_t*)(arg1_r4 + 0x2));
    if (0 >= *(uint8_t*)(arg0_r3 + 0x22C)) goto label_8001A920;
    r11 = 0;
    r9 = arg0_r3 + (8);
label_8001A900:;
    *(uint16_t*)((arg0_r3 + 8) + 0x4) = 0;
    r10 = 0 + (1);
    *(uint16_t*)((arg0_r3 + 8) + 0x2) = 0;
    *(uint16_t*)((arg0_r3 + 8) + 0x0) = 0;
    r9 = (arg0_r3 + 8) + (6);
    r0 = *(uint8_t*)(arg0_r3 + 0x22C);
    if ((0 + 1) < *(uint8_t*)(arg0_r3 + 0x22C)) goto label_8001A900;
label_8001A920:;
    r0 = 0;
    *(float*)(arg0_r3 + 0x228) = arg3_f1;
    *(uint8_t*)(arg0_r3 + 0x23E) = 0;
    *(uint16_t*)(arg0_r3 + 0x23C) = arg2_r5;
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: CameraMotionMove(tagCAMERA *, _MOTION_INFO *)
// Unit: camera.obj | Address: 0x8001A938 | Size: 0x1BC bytes
// ============================================================================
/* [0x8001A938] */ void CameraMotionMove(tagCAMERA * arg0_r3, _MOTION_INFO * arg1_r4) {
    // Stack frame allocated: 144 bytes
    stack_0x94 = r0;
    r24 = arg0_r3;
    r30 = arg1_r4;
    r3 = &stack_0x40;
    r31 = &stack_0x08;
    r4 = 0;
    r20 = &stack_0x40;
    r5 = 12;
    r27 = 0;
    r3 = memset(); // [0x800E8A5C]
    f13 = *(float*)(arg1_r4 + 0x228);
    r9 = 2;
    r0 = *(uint8_t*)(arg1_r4 + 0x22C);
    r23 = &stack_0x20;
    f0 = *(float*)(arg1_r4 + 0x224);
    r21 = &stack_0x30;
    stack_0x08 = *(float*)(arg1_r4 + 0x228);
    *(float*)(&stack_0x08 + 0x4) = *(float*)(arg1_r4 + 0x224);
    *(uint32_t*)(&stack_0x08 + 0x8) = 2;
    if (0 >= *(uint8_t*)(arg1_r4 + 0x22C)) goto label_8001AA74;
    r29 = arg1_r4 + (8);
    r22 = 0;
    r28 = (arg1_r4 + 8);
    r25 = (arg1_r4 + 8);
    r26 = (arg1_r4 + 8);
label_8001A9B0:;
    r11 = *(uint32_t*)(arg1_r4 + 0x234);
    r9 = (0 + 0);
    r10 = *(uint32_t*)(arg1_r4 + 0x4);
    r8 = *(uint32_t*)(arg1_r4 + 0x230);
    *(uint8_t*)(&stack_0x08 + 0xC) = *(uint8_t*)(arg1_r4 + 0x22C);
    *(uint32_t*)(&stack_0x08 + 0x10) = (0 + 0);
    if (*(uint8_t*)(arg1_r4 + 0x22C) == 1) goto label_8001AA18;
    if (*(uint8_t*)(arg1_r4 + 0x22C) > 1) goto label_8001A9F0;
    if (*(uint8_t*)(arg1_r4 + 0x22C) == 0) goto label_8001AA04;
    goto label_8001AA50;
label_8001A9F0:;
    if (*(uint8_t*)(arg1_r4 + 0x22C) == 2) goto label_8001AA2C;
    if (*(uint8_t*)(arg1_r4 + 0x22C) == 3) goto label_8001AA40;
    goto label_8001AA50;
label_8001AA04:;
    r3 = &stack_0x08;
    r4 = &stack_0x20;
    r5 = (arg1_r4 + 8);
    r3 = HermiteInterpolation(&stack_0x08, &stack_0x20, (arg1_r4 + 8)); // [0x800A3468]
    goto label_8001AA50;
label_8001AA18:;
    r3 = &stack_0x08;
    r4 = &stack_0x30;
    r5 = (arg1_r4 + 8);
    r3 = HermiteInterpolation(&stack_0x08, &stack_0x30, (arg1_r4 + 8)); // [0x800A3468]
    goto label_8001AA50;
label_8001AA2C:;
    r3 = &stack_0x08;
    r4 = &stack_0x40;
    r5 = (arg1_r4 + 8);
    r3 = HermiteInterpolation(&stack_0x08, &stack_0x40, (arg1_r4 + 8)); // [0x800A3468]
    goto label_8001AA50;
label_8001AA40:;
    r3 = &stack_0x08;
    r4 = &stack_0x50;
    r5 = (arg1_r4 + 8);
    r3 = HermiteInterpolation(&stack_0x08, &stack_0x50, (arg1_r4 + 8)); // [0x800A3468]
label_8001AA50:;
    r0 = *(uint8_t*)(arg1_r4 + 0x22C);
    r27 = 0 + (1);
    r25 = (arg1_r4 + 8) + (6);
    r29 = (arg1_r4 + 8) + (6);
    r26 = (arg1_r4 + 8) + (6);
    r28 = (arg1_r4 + 8) + (6);
    r22 = 0 + (4);
    if ((0 + 1) < *(uint8_t*)(arg1_r4 + 0x22C)) goto label_8001A9B0;
label_8001AA74:;
    f0 = stack_0x54;
    f12 = *(float*)0x80163E70;
    f13 = *(double*)0x80163E78;
    r7 = arg0_r3 + (256);
    r0 = stack_0x20;
    r9 = *(uint32_t*)(&stack_0x20 + 0x4);
    r8 = *(uint32_t*)(&stack_0x20 + 0x8);
    *(uint32_t*)(arg0_r3 + 0x100) = stack_0x20;
    r10 = arg0_r3 + (268);
    r3 = arg0_r3;
    r11 = stack_0x30;
    *(uint32_t*)((arg0_r3 + 256) + 0x8) = *(uint32_t*)(&stack_0x20 + 0x8);
    *(uint32_t*)((arg0_r3 + 256) + 0x4) = *(uint32_t*)(&stack_0x20 + 0x4);
    r9 = *(uint32_t*)(&stack_0x30 + 0x4);
    r0 = *(uint32_t*)(&stack_0x30 + 0x8);
    *(uint32_t*)(arg0_r3 + 0x10C) = stack_0x30;
    f13 = stack_0x44;
    *(uint32_t*)((arg0_r3 + 268) + 0x8) = *(uint32_t*)(&stack_0x30 + 0x8);
    *(uint32_t*)((arg0_r3 + 268) + 0x4) = *(uint32_t*)(&stack_0x30 + 0x4);
    *(float*)(arg0_r3 + 0x134) = stack_0x44;
    *(float*)(arg0_r3 + 0x130) = stack_0x54;
    r3 = CameraSetOrientationRoll(arg0_r3); // [0x80019D18]
    r0 = stack_0x94;
    return; // r3 = ret_8001AADC
}

// ============================================================================
// High-Level AST Decompilation: CameraSequenceCtrl(_MOTION_INFO *)
// Unit: camera.obj | Address: 0x8001AAF4 | Size: 0x60 bytes
// ============================================================================
/* [0x8001AAF4] */ void CameraSequenceCtrl(_MOTION_INFO * arg0_r3) {
    r0 = *(uint16_t*)(arg0_r3 + 0x23C);
    if (r0 != 0) goto label_8001AB4C;
    f13 = *(float*)(arg0_r3 + 0x228);
    f0 = *(float*)(arg0_r3 + 0x224);
    if (r0 != 0) goto label_8001AB3C;
    if (r0 == 0) goto label_8001AB30;
    r0 = 1;
    f0 = *(float*)0x80163E80;
    *(uint8_t*)(arg0_r3 + 0x23E) = 1;
    goto label_8001AB48;
label_8001AB30:;
    r0 = 4;
    *(uint8_t*)(arg0_r3 + 0x23E) = 4;
    goto label_8001AB4C;
label_8001AB3C:;
    f0 = *(float*)0x80163E84;
label_8001AB48:;
    *(float*)(arg0_r3 + 0x228) = *(float*)0x80163E84;
label_8001AB4C:;
    r3 = *(uint8_t*)(arg0_r3 + 0x23E);
    return; // r3 = *(uint8_t*)(arg0_r3 + 0x23E)
}

// ============================================================================
// High-Level AST Decompilation: CameraViewFrustumPtr(tagCAMERA *)
// Unit: camera.obj | Address: 0x8001AB54 | Size: 0xC bytes
// ============================================================================
/* [0x8001AB54] */ void CameraViewFrustumPtr(tagCAMERA * arg0_r3) {
    r3 = 0x801D2F7Cu;
    return; // r3 = 0x801D2F7Cu
}

// ============================================================================
// High-Level AST Decompilation: CameraGetUpVector(tagCAMERA *, Vec *)
// Unit: camera.obj | Address: 0x8001AB60 | Size: 0x1C bytes
// ============================================================================
/* [0x8001AB60] */ void CameraGetUpVector(tagCAMERA * arg0_r3, Vec * arg1_r4) {
    f0 = *(float*)(arg0_r3 + 0x4);
    *(float*)(arg1_r4 + 0x0) = *(float*)(arg0_r3 + 0x4);
    f13 = *(float*)(arg0_r3 + 0x14);
    *(float*)(arg1_r4 + 0x4) = *(float*)(arg0_r3 + 0x14);
    f0 = *(float*)(arg0_r3 + 0x24);
    *(float*)(arg1_r4 + 0x8) = *(float*)(arg0_r3 + 0x24);
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: CameraGetLookVector(tagCAMERA *, Vec *)
// Unit: camera.obj | Address: 0x8001AB7C | Size: 0x1C bytes
// ============================================================================
/* [0x8001AB7C] */ void CameraGetLookVector(tagCAMERA * arg0_r3, Vec * arg1_r4) {
    f0 = *(float*)(arg0_r3 + 0x8);
    *(float*)(arg1_r4 + 0x0) = *(float*)(arg0_r3 + 0x8);
    f13 = *(float*)(arg0_r3 + 0x18);
    *(float*)(arg1_r4 + 0x4) = *(float*)(arg0_r3 + 0x18);
    f0 = *(float*)(arg0_r3 + 0x28);
    *(float*)(arg1_r4 + 0x8) = *(float*)(arg0_r3 + 0x28);
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: CameraGetRightVector(tagCAMERA *, Vec *)
// Unit: camera.obj | Address: 0x8001AB98 | Size: 0x1C bytes
// ============================================================================
/* [0x8001AB98] */ void CameraGetRightVector(tagCAMERA * arg0_r3, Vec * arg1_r4) {
    f0 = *(float*)(arg0_r3 + 0x0);
    *(float*)(arg1_r4 + 0x0) = *(float*)(arg0_r3 + 0x0);
    f13 = *(float*)(arg0_r3 + 0x10);
    *(float*)(arg1_r4 + 0x4) = *(float*)(arg0_r3 + 0x10);
    f0 = *(float*)(arg0_r3 + 0x20);
    *(float*)(arg1_r4 + 0x8) = *(float*)(arg0_r3 + 0x20);
    return; // r3 = arg0_r3
}
