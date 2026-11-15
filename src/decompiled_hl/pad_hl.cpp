// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: pad.obj
// Functions Decompiled: 11
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: PadInit(void)
// Unit: pad.obj | Address: 0x800ACBEC | Size: 0x40 bytes
// ============================================================================
/* [0x800ACBEC] */ void PadInit(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = PADInit(); // [0x80110014]
    r3 = 0;
    r3 = PADSetSamplingRate(); // [0x801105D8]
    r3 = PADReset(); // [0x8010FE10]
    r3 = 3;
    r3 = PADSetAnalogMode(); // [0x80110FE4]
    r0 = 0;
    SDA1::Vib_level = 0;
    r0 = stack_0x0C;
    return; // r3 = ret_800ACC10
}

// ============================================================================
// High-Level AST Decompilation: PadRead(void)
// Unit: pad.obj | Address: 0x800ACC2C | Size: 0x534 bytes
// ============================================================================
/* [0x800ACC2C] */ void PadRead(void) {
    // Stack frame allocated: 112 bytes
    stack_0x40 = f26;
    stack_0x48 = f27;
    stack_0x50 = f28;
    stack_0x58 = f29;
    stack_0x60 = f30;
    stack_0x68 = f31;
    stack_0x74 = r0;
    r23 = 10;
    r31 = 0;
    r3 = &Pad_data;
    r3 = PADRead(); // [0x8011022C]
    r3 = &Pad_data;
    r3 = PADClamp(); // [0x8010F228]
    r0 = 4;
    r30 = &Pad_data;
    r30 = &Pad_data + (10);
label_800ACC84:;
    r0 = *(uint8_t*)((&Pad_data + 10) + 0x0);
    r30 = (&Pad_data + 10) + (12);
    if (*(uint8_t*)((&Pad_data + 10) + 0x0) == -1) goto label_800ACCB8;
    if (*(uint8_t*)((&Pad_data + 10) + 0x0) <= -1) goto label_800ACCC4;
    if (*(uint8_t*)((&Pad_data + 10) + 0x0) != 0) goto label_800ACCC4;
    r0 = SDA1::ConnectedBits;
    SDA1::ConnectedBits = SDA1::ConnectedBits;
    goto label_800ACCC4;
label_800ACCB8:;
    r0 = SDA1::ResetBits;
    SDA1::ResetBits = SDA1::ResetBits;
label_800ACCC4:;
    r31 = 0 + (1);
    if (*(uint8_t*)((&Pad_data + 10) + 0x0) >= 0) goto label_800ACC84;
    r3 = SDA1::ResetBits;
    if (SDA1::ResetBits == 0) goto label_800ACCEC;
    r3 = PADReset(); // [0x8010FE10]
    if (ret_800ACCD8 == 0) goto label_800ACCEC;
    r0 = 0;
    SDA1::ResetBits = 0;
label_800ACCEC:;
    r24 = &Pad_data;
    f29 = *(double*)0x8016C890;
    f26 = *(float*)0x8016C898;
    r10 = &Key;
    f28 = *(float*)0x8016C89C;
    r26 = &Key + (36);
    f27 = *(float*)0x8016C8A0;
    r27 = 0;
    r30 = &Key + (68);
    r31 = &Pad_data;
label_800ACD30:;
    r0 = *(uint8_t*)(&Pad_data + 0xA);
    *(uint8_t*)((&Key + 68) - 0x3C) = *(uint8_t*)(&Pad_data + 0xA);
    if (0x80170000u == -2) goto label_800ACD94;
    r9 = *(uint16_t*)(&Pad_data + 0x0);
    r11 = *(uint8_t*)(&Pad_data + 0x2);
    r10 = *(uint8_t*)(&Pad_data + 0x3);
    r8 = *(uint8_t*)(&Pad_data + 0x4);
    r7 = *(uint8_t*)(&Pad_data + 0x5);
    r6 = *(uint8_t*)(&Pad_data + 0x6);
    r5 = *(uint8_t*)(&Pad_data + 0x7);
    r4 = *(uint8_t*)(&Pad_data + 0x8);
    r3 = *(uint8_t*)(&Pad_data + 0x9);
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
    *(uint32_t*)((&Key + 68) - 0x34) = *(uint16_t*)(&Pad_data + 0x0);
    *(uint32_t*)((&Key + 68) - 0x38) = *(uint32_t*)((&Key + 68) - 0x34);
    *(uint8_t*)((&Key + 68) - 0x44) = *(uint8_t*)(&Pad_data + 0x2);
    *(uint8_t*)((&Key + 68) - 0x43) = *(uint8_t*)(&Pad_data + 0x3);
    *(uint8_t*)((&Key + 68) - 0x42) = *(uint8_t*)(&Pad_data + 0x4);
    *(uint8_t*)((&Key + 68) - 0x41) = *(uint8_t*)(&Pad_data + 0x5);
    *(uint8_t*)((&Key + 68) - 0x40) = *(uint8_t*)(&Pad_data + 0x6);
    *(uint8_t*)((&Key + 68) - 0x3F) = *(uint8_t*)(&Pad_data + 0x7);
    *(uint8_t*)((&Key + 68) - 0x3E) = *(uint8_t*)(&Pad_data + 0x8);
    *(uint8_t*)((&Key + 68) - 0x3D) = *(uint8_t*)(&Pad_data + 0x9);
label_800ACD94:;
    r0 = *(uint8_t*)((&Key + 68) - 0x3C);
    if (*(uint8_t*)((&Key + 68) - 0x3C) == 0) goto label_800ACDB0;
    *(uint32_t*)((&Key + 68) - 0x30) = 0;
    *(uint32_t*)((&Key + 68) - 0x2C) = 0;
    *(uint32_t*)((&Key + 68) - 0x28) = 0;
    goto label_800AD070;
label_800ACDB0:;
    r0 = *(uint8_t*)((&Key + 68) - 0x40);
    if (*(uint8_t*)((&Key + 68) - 0x40) <= 0x1Eu) goto label_800ACDC8;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
    r0 = *(uint32_t*)((&Key + 68) - 0x34) | 0x0040u;
    *(uint32_t*)((&Key + 68) - 0x34) = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACDC8:;
    r0 = *(uint8_t*)((&Key + 68) - 0x3F);
    if (*(uint8_t*)((&Key + 68) - 0x3F) <= 0x1Eu) goto label_800ACDE0;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
    r0 = *(uint32_t*)((&Key + 68) - 0x34) | 0x0020u;
    *(uint32_t*)((&Key + 68) - 0x34) = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACDE0:;
    r0 = *(uint8_t*)((&Key + 68) - 0x44);
    r9 = *(uint8_t*)((&Key + 68) - 0x43);
    r10 = *(uint8_t*)(&Pad_data + 0x2);
    stack_0x14 = *(uint8_t*)((&Key + 68) - 0x44);
    stack_0x10 = 0x43300000u;
    f30 = stack_0x10;
    stack_0x14 = *(uint8_t*)((&Key + 68) - 0x43);
    stack_0x10 = 0x43300000u;
    f31 = stack_0x10;
    r3 = atan2f(); // [0x800E3930]
    if (*(uint8_t*)((&Key + 68) - 0x3F) <= 0x1Eu) goto label_800ACF0C;
    if (*(uint8_t*)((&Key + 68) - 0x3F) >= 0x1Eu) goto label_800ACEA8;
    if (*(uint8_t*)((&Key + 68) - 0x3F) <= 0x1Eu) goto label_800ACE60;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
    *(uint32_t*)((&Key + 68) - 0x34) = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACE60:;
    f0 = *(float*)0x8016C8A4;
    if (*(uint8_t*)((&Key + 68) - 0x3F) >= 0x1Eu) goto label_800ACE7C;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
    *(uint32_t*)((&Key + 68) - 0x34) = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACE7C:;
    f0 = *(float*)0x8016C8A8;
    if (*(uint8_t*)((&Key + 68) - 0x3F) >= 0x1Eu) goto label_800ACF0C;
    f0 = *(float*)0x8016C8AC;
    if (*(uint8_t*)((&Key + 68) - 0x3F) <= 0x1Eu) goto label_800ACF0C;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
    goto label_800ACF08;
label_800ACEA8:;
    f0 = *(float*)0x8016C8B0;
    if (*(uint8_t*)((&Key + 68) - 0x3F) >= 0x1Eu) goto label_800ACEC4;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
    *(uint32_t*)((&Key + 68) - 0x34) = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACEC4:;
    f0 = *(float*)0x8016C8B4;
    if (*(uint8_t*)((&Key + 68) - 0x3F) <= 0x1Eu) goto label_800ACEE0;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
    *(uint32_t*)((&Key + 68) - 0x34) = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACEE0:;
    f0 = *(float*)0x8016C8B8;
    if (*(uint8_t*)((&Key + 68) - 0x3F) <= 0x1Eu) goto label_800ACF0C;
    f0 = *(float*)0x8016C8BC;
    if (*(uint8_t*)((&Key + 68) - 0x3F) >= 0x1Eu) goto label_800ACF0C;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACF08:;
    *(uint32_t*)((&Key + 68) - 0x34) = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACF0C:;
    r0 = *(uint8_t*)((&Key + 68) - 0x42);
    if (*(uint8_t*)((&Key + 68) - 0x42) >= -10) goto label_800ACF28;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
    goto label_800ACF38;
label_800ACF28:;
    if (10 >= *(uint32_t*)((&Key + 68) - 0x34)) goto label_800ACF3C;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACF38:;
    *(uint32_t*)((&Key + 68) - 0x34) = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACF3C:;
    r0 = *(uint8_t*)((&Key + 68) - 0x41);
    if (*(uint8_t*)((&Key + 68) - 0x41) >= -10) goto label_800ACF58;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
    goto label_800ACF68;
label_800ACF58:;
    if (10 >= *(uint32_t*)((&Key + 68) - 0x34)) goto label_800ACF6C;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACF68:;
    *(uint32_t*)((&Key + 68) - 0x34) = *(uint32_t*)((&Key + 68) - 0x34);
label_800ACF6C:;
    r11 = *(uint32_t*)((&Key + 68) - 0x34);
    r8 = 1;
    r0 = *(uint32_t*)((&Key + 68) - 0x38);
    r10 = 0;
    *(uint32_t*)((&Key + 68) - 0x28) = 0;
    r4 = (&Key + 36);
    *(uint32_t*)((&Key + 68) - 0x24) = 0;
    r6 = SDA1::pG;
    *(uint32_t*)((&Key + 68) - 0x2C) = *(uint32_t*)((&Key + 68) - 0x38);
    r0 = 32;
    *(uint32_t*)((&Key + 68) - 0x30) = 0x80170000u;
    r5 = (&Key + 68);
    r7 = (&Key + 36);
    r28 = 6;
    r11 = (&Key + 68);
    r29 = 4;
    r12 = 24;
    r3 = 15;
label_800ACFC4:;
    r0 = *(uint32_t*)((&Key + 68) - 0x34);
    if (10 == *(uint32_t*)((&Key + 68) - 0x34)) goto label_800AD05C;
    r0 = *(uint32_t*)((&Key + 68) - 0x30);
    if (10 == *(uint32_t*)((&Key + 68) - 0x34)) goto label_800ACFF8;
    r0 = *(uint32_t*)((&Key + 68) - 0x28);
    r9 = *(uint32_t*)((&Key + 68) - 0x24);
    *(uint32_t*)((&Key + 68) - 0x28) = *(uint32_t*)((&Key + 68) - 0x28);
    *(uint32_t*)((&Key + 68) - 0x24) = *(uint32_t*)((&Key + 68) - 0x24);
    goto label_800AD038;
label_800ACFF8:;
    if (*(uint32_t*)((&Key + 68) - 0x28) > 0) goto label_800AD018;
    r0 = *(uint32_t*)((&Key + 68) - 0x28);
    *(uint32_t*)((&Key + 68) - 0x28) = *(uint32_t*)((&Key + 68) - 0x28);
label_800AD018:;
    if (*(uint32_t*)((&Key + 68) - 0x28) > 0) goto label_800AD038;
    r0 = *(uint32_t*)((&Key + 68) - 0x24);
    *(uint32_t*)((&Key + 68) - 0x24) = *(uint32_t*)((&Key + 68) - 0x24);
label_800AD038:;
    r9 = *(uint8_t*)(SDA1::pG + 0x11F);
    r0 = (*(uint32_t*)((&Key + 68) - 0x24) - *(uint8_t*)(SDA1::pG + 0x11F));
    r0 = *(uint8_t*)(SDA1::pG + 0x11F);
    r9 = (*(uint8_t*)(SDA1::pG + 0x11F) - *(uint8_t*)(SDA1::pG + 0x11F));
    goto label_800AD064;
label_800AD05C:;
label_800AD064:;
    r10 = 0 + (1);
    if (*(uint32_t*)((&Key + 68) - 0x28) >= 0) goto label_800ACFC4;
label_800AD070:;
    r31 = &Pad_data + (12);
    r0 = &Pad_data + (36);
    r30 = (&Key + 68) + (616);
    r26 = (&Key + 36) + (616);
    if ((&Pad_data + 12) <= (&Pad_data + 36)) goto label_800ACD30;
    r30 = &Joy;
    r29 = &Key;
    r31 = 0;
label_800AD09C:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x150);
    if ((&Pad_data + 12) == (&Pad_data + 36)) goto label_800AD0C8;
    r4 = 0;
    r5 = 100;
    r3 = (15 + &Joy);
    r3 = memset(); // [0x800E8A5C]
    r3 = 0 + (1);
    goto label_800AD124;
label_800AD0C8:;
    r3 = 0 + (1);
    r10 = 96;
    r11 = (*(uint32_t*)(SDA1::pG + 0x150) + &Key);
    r9 = (*(uint32_t*)(SDA1::pG + 0x150) + &Joy);
label_800AD0DC:;
    r0 = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0x0);
    *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Joy) + 0x0) = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0x0);
    r0 = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0x4);
    *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Joy) + 0x4) = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0x4);
    r0 = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0x8);
    *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Joy) + 0x8) = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0x8);
    r0 = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0xC);
    *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Joy) + 0xC) = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0xC);
    r0 = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0x10);
    *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Joy) + 0x10) = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0x10);
    r0 = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0x14);
    r11 = (*(uint32_t*)(SDA1::pG + 0x150) + &Key) + (24);
    *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Joy) + 0x14) = *(uint32_t*)((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 0x14);
    r9 = (*(uint32_t*)(SDA1::pG + 0x150) + &Joy) + (24);
    if ((&Pad_data + 12) != (&Pad_data + 36)) goto label_800AD0DC;
    r0 = *(uint32_t*)(((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 24) + 0x0);
    *(uint32_t*)(((*(uint32_t*)(SDA1::pG + 0x150) + &Joy) + 24) + 0x0) = *(uint32_t*)(((*(uint32_t*)(SDA1::pG + 0x150) + &Key) + 24) + 0x0);
label_800AD124:;
    r31 = (0 + 1);
    if ((0 + 1) <= 3) goto label_800AD09C;
    r3 = VibControl(); // [0x800AD160]
    r0 = stack_0x74;
    f26 = stack_0x40;
    f27 = stack_0x48;
    f28 = stack_0x50;
    f29 = stack_0x58;
    f30 = stack_0x60;
    f31 = stack_0x68;
    return; // r3 = ret_800AD130
}

// ============================================================================
// High-Level AST Decompilation: VibControl(void)
// Unit: pad.obj | Address: 0x800AD160 | Size: 0x14C bytes
// ============================================================================
/* [0x800AD160] */ void VibControl(void) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r9 = SDA1::pG;
    r10 = &Joy;
    r0 = *(uint32_t*)(SDA1::pG + 0x150);
    r26 = *(uint8_t*)(&Joy + 0x64);
    if (r0 == 0) goto label_800AD1B4;
    if (*(uint8_t*)(&Joy + 0x64) != 1) goto label_800AD298;
    r0 = 2;
    r3 = 0;
    *(uint8_t*)(&Joy + 0x64) = 2;
    r4 = 2;
    r3 = PADControlMotor(); // [0x801106B0]
    r0 = 0;
    SDA1::Vib_level = 0;
    goto label_800AD298;
label_800AD1B4:;
    r27 = &Joy + (248);
    r28 = 0;
    r29 = &Joy + (104);
label_800AD1C0:;
    r11 = *(uint16_t*)((&Joy + 104) + 0x4);
    if (*(uint16_t*)((&Joy + 104) + 0x4) == 0) goto label_800AD23C;
    r9 = *(uint16_t*)((&Joy + 104) + 0x2);
    if (*(uint16_t*)((&Joy + 104) + 0x2) == 0) goto label_800AD1E4;
    r0 = *(uint16_t*)((&Joy + 104) + 0x2) + (-1);
    *(uint16_t*)((&Joy + 104) + 0x2) = (*(uint16_t*)((&Joy + 104) + 0x2) + -1);
    goto label_800AD23C;
label_800AD1E4:;
    r0 = *(uint32_t*)((&Joy + 104) + 0x8);
    r11 = *(uint16_t*)((&Joy + 104) + 0x4) + (-1);
    r9 = *(uint32_t*)((&Joy + 104) + 0xC);
    r10 = *(uint16_t*)((&Joy + 104) + 0x0);
    r0 = (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC));
    *(uint16_t*)((&Joy + 104) + 0x4) = (*(uint16_t*)((&Joy + 104) + 0x4) + -1);
    r31 = (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC));
    *(uint32_t*)((&Joy + 104) + 0x8) = (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC));
    if (*(uint16_t*)((&Joy + 104) + 0x2) == 0) goto label_800AD230;
    r3 = Rnd(); // [0x800C06C4]
    r30 = ret_800AD20C;
    r3 = Rnd(); // [0x800C06C4]
    r9 = (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC)) + (1);
    r30 = (ret_800AD20C + ret_800AD214);
    r31 = ((ret_800AD20C + ret_800AD214) - (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC)));
label_800AD230:;
    if (0 >= ((ret_800AD20C + ret_800AD214) - (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC)))) goto label_800AD23C;
    r28 = ((ret_800AD20C + ret_800AD214) - (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC)));
label_800AD23C:;
    r29 = (&Joy + 104) + (16);
    if (((&Joy + 104) + 16) <= (&Joy + 248)) goto label_800AD1C0;
    r0 = SDA1::Vib_level;
    r9 = (SDA1::Vib_level + ((ret_800AD20C + ret_800AD214) - (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC))));
    SDA1::Vib_level = (SDA1::Vib_level + ((ret_800AD20C + ret_800AD214) - (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC))));
    if ((SDA1::Vib_level + ((ret_800AD20C + ret_800AD214) - (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC)))) <= 32639) goto label_800AD274;
    r0 = (SDA1::Vib_level + ((ret_800AD20C + ret_800AD214) - (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC)))) + (-32640);
    r9 = 1;
    SDA1::Vib_level = ((SDA1::Vib_level + ((ret_800AD20C + ret_800AD214) - (*(uint32_t*)((&Joy + 104) + 0x8) + *(uint32_t*)((&Joy + 104) + 0xC)))) + -32640);
    *(uint8_t*)0x8019D6E4 = 1;
    goto label_800AD280;
label_800AD274:;
    r0 = 0;
    *(uint8_t*)0x8019D6E4 = 0;
label_800AD280:;
    r4 = *(uint8_t*)0x8019D6E4;
    if (*(uint8_t*)0x8019D6E4 == *(uint8_t*)(&Joy + 0x64)) goto label_800AD298;
    r3 = 0;
    r3 = PADControlMotor(); // [0x801106B0]
label_800AD298:;
    r0 = stack_0x24;
    return; // r3 = ret_800AD294
}

// ============================================================================
// High-Level AST Decompilation: PullVibWork(void)
// Unit: pad.obj | Address: 0x800AD2AC | Size: 0x44 bytes
// ============================================================================
/* [0x800AD2AC] */ void PullVibWork(void) {
    r9 = SDA1::pG;
    r3 = 0x8019D6E8u;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A92);
    if (*(uint8_t*)(SDA1::pG + 0x6A92) != 0) goto label_800AD2CC;
    r3 = 0;
    return; // r3 = 0
label_800AD2CC:;
    r0 = 10;
label_800AD2D4:;
    r0 = *(uint16_t*)(0 + 0x4);
    r3 = 0 + (16);
    if (*(uint16_t*)(0 + 0x4) >= 0) goto label_800AD2D4;
    r3 = 0;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: VibSet(unsigned long, unsigned long, unsigned long, unsigned long)
// Unit: pad.obj | Address: 0x800AD2F0 | Size: 0x68 bytes
// ============================================================================
/* [0x800AD2F0] */ void VibSet(unsigned long arg0_r3, unsigned long arg1_r4, unsigned long arg2_r5, unsigned long arg3_r6) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r31 = arg0_r3;
    r30 = arg1_r4;
    r28 = arg2_r5;
    r29 = arg3_r6;
    r3 = PullVibWork(); // [0x800AD2AC]
    r3 = ret_800AD310;
    if (r0 == 0) goto label_800AD344;
    if (arg0_r3 <= 0xFFu) goto label_800AD328;
    r31 = 255;
label_800AD328:;
    r0 = 0;
    *(uint32_t*)(ret_800AD310 + 0xC) = 0;
    *(uint16_t*)(ret_800AD310 + 0x0) = arg3_r6;
    *(uint16_t*)(ret_800AD310 + 0x4) = 255;
    *(uint16_t*)(ret_800AD310 + 0x2) = arg2_r5;
    *(uint32_t*)(ret_800AD310 + 0x8) = r9;
label_800AD344:;
    r0 = stack_0x1C;
    return; // r3 = ret_800AD310
}

// ============================================================================
// High-Level AST Decompilation: VibSetFade(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// Unit: pad.obj | Address: 0x800AD358 | Size: 0x80 bytes
// ============================================================================
/* [0x800AD358] */ void VibSetFade(unsigned long arg0_r3, unsigned long arg1_r4, unsigned long arg2_r5, unsigned long arg3_r6, unsigned long arg4_r7) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r28 = arg0_r3;
    r31 = arg1_r4;
    r30 = arg2_r5;
    r27 = arg3_r6;
    r29 = arg4_r7;
    r3 = PullVibWork(); // [0x800AD2AC]
    r3 = ret_800AD37C;
    if (r0 == 0) goto label_800AD3C4;
    if (arg1_r4 <= 0xFFu) goto label_800AD394;
    r31 = 255;
label_800AD394:;
    if (arg2_r5 <= 0xFFu) goto label_800AD3A0;
    r30 = 255;
label_800AD3A0:;
    r0 = (255 - 255);
    *(uint16_t*)(ret_800AD37C + 0x0) = arg4_r7;
    *(uint16_t*)(ret_800AD37C + 0x2) = arg3_r6;
    *(uint32_t*)(ret_800AD37C + 0x8) = r9;
    *(uint16_t*)(ret_800AD37C + 0x4) = arg0_r3;
    *(uint32_t*)(ret_800AD37C + 0xC) = (255 - 255);
label_800AD3C4:;
    r0 = stack_0x24;
    return; // r3 = ret_800AD37C
}

// ============================================================================
// High-Level AST Decompilation: VibSetDataCore(VIB_INFO *, unsigned long)
// Unit: pad.obj | Address: 0x800AD3D8 | Size: 0xA8 bytes
// ============================================================================
/* [0x800AD3D8] */ void VibSetDataCore(VIB_INFO * arg0_r3, unsigned long arg1_r4) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r30 = arg0_r3;
    r31 = 0;
    r0 = *(uint32_t*)(arg0_r3 + 0x0);
    r28 = arg1_r4;
    if (0 >= *(uint32_t*)(arg0_r3 + 0x0)) goto label_800AD46C;
    r29 = 0;
label_800AD404:;
    r3 = PullVibWork(); // [0x800AD2AC]
    r3 = ret_800AD404;
    if (0 == *(uint32_t*)(arg0_r3 + 0x0)) goto label_800AD46C;
    r10 = arg0_r3 + (4);
    r31 = 0 + (1);
    r10 = ((arg0_r3 + 4) + 0);
    r0 = *(uint8_t*)(((arg0_r3 + 4) + 0) + 0x6);
    r29 = 0 + (8);
    r11 = *(uint8_t*)(((arg0_r3 + 4) + 0) + 0x7);
    r8 = *(uint16_t*)(((arg0_r3 + 4) + 0) + 0x4);
    r11 = (*(uint8_t*)(((arg0_r3 + 4) + 0) + 0x7) - *(uint8_t*)(((arg0_r3 + 4) + 0) + 0x6));
    r9 = *(uint16_t*)(((arg0_r3 + 4) + 0) + 0x0);
    *(uint16_t*)(ret_800AD404 + 0x0) = *(uint16_t*)(((arg0_r3 + 4) + 0) + 0x0);
    r0 = *(uint16_t*)(((arg0_r3 + 4) + 0) + 0x4);
    *(uint16_t*)(ret_800AD404 + 0x4) = *(uint16_t*)(((arg0_r3 + 4) + 0) + 0x4);
    r9 = *(uint16_t*)(((arg0_r3 + 4) + 0) + 0x2);
    *(uint32_t*)(ret_800AD404 + 0x8) = r7;
    *(uint16_t*)(ret_800AD404 + 0x2) = *(uint16_t*)(((arg0_r3 + 4) + 0) + 0x2);
    *(uint32_t*)(ret_800AD404 + 0xC) = (*(uint8_t*)(((arg0_r3 + 4) + 0) + 0x7) - *(uint8_t*)(((arg0_r3 + 4) + 0) + 0x6));
    r0 = *(uint32_t*)(arg0_r3 + 0x0);
    if ((0 + 1) < *(uint32_t*)(arg0_r3 + 0x0)) goto label_800AD404;
label_800AD46C:;
    r0 = stack_0x1C;
    return; // r3 = ret_800AD404
}

// ============================================================================
// High-Level AST Decompilation: VibSetData(unsigned long, unsigned long, unsigned long)
// Unit: pad.obj | Address: 0x800AD480 | Size: 0x44 bytes
// ============================================================================
/* [0x800AD480] */ void VibSetData(unsigned long arg0_r3, unsigned long arg1_r4, unsigned long arg2_r5) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = arg0_r3;
    r0 = *(uint32_t*)(arg0_r3 + 0x0);
    r11 = arg0_r3 + (4);
    if (*(uint32_t*)(arg0_r3 + 0x0) <= arg1_r4) goto label_800AD4B4;
    r4 = arg2_r5;
    r3 = (arg0_r3 + arg0_r3);
    r3 = VibSetDataCore((arg0_r3 + arg0_r3), arg2_r5); // [0x800AD3D8]
label_800AD4B4:;
    r0 = stack_0x0C;
    return; // r3 = ret_800AD4B0
}

// ============================================================================
// High-Level AST Decompilation: VibSetClear(void)
// Unit: pad.obj | Address: 0x800AD4C4 | Size: 0x5C bytes
// ============================================================================
/* [0x800AD4C4] */ void VibSetClear(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r11 = 10;
    r0 = 0;
    r9 = 0x8019D6E8u;
label_800AD4E4:;
    *(uint16_t*)(0x8019D6E8u + 0x4) = 0;
    r9 = 0x8019D6E8u + (16);
    if (r0 >= 0) goto label_800AD4E4;
    r0 = 2;
    *(uint8_t*)0x8019D6E4 = 2;
    r3 = 0;
    r4 = 2;
    r3 = PADControlMotor(); // [0x801106B0]
    r0 = 0;
    SDA1::Vib_level = 0;
    r0 = stack_0x0C;
    return; // r3 = ret_800AD504
}

// ============================================================================
// High-Level AST Decompilation: VibSetClearType(unsigned long)
// Unit: pad.obj | Address: 0x800AD520 | Size: 0x34 bytes
// ============================================================================
/* [0x800AD520] */ void VibSetClearType(unsigned long arg0_r3) {
    r0 = 10;
    r9 = 0x8019D6E8u;
    r11 = 0;
label_800AD538:;
    r0 = *(uint16_t*)(0x8019D6E8u + 0x0);
    if (r0 == 0) goto label_800AD548;
    *(uint16_t*)(0x8019D6E8u + 0x4) = 0;
label_800AD548:;
    r9 = 0x8019D6E8u + (16);
    if (r0 >= 0) goto label_800AD538;
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: Pad_test(void)
// Unit: pad.obj | Address: 0x800AD554 | Size: 0x220 bytes
// ============================================================================
/* [0x800AD554] */ void Pad_test(void) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r30 = &Joy;
    r9 = "ON   %32b";
    r10 = *(uint32_t*)(&Joy + 0x10);
    r3 = 10;
    r4 = 16;
    r5 = 32;
    r6 = 48;
    r7 = 0;
    r8 = 5;
    r3 = eprintf2(10, 16, 32, 48, 0, 5, "ON   %32b", *(uint32_t*)(&Joy + 0x10)); // [0x8008193C]
    r10 = *(uint32_t*)(&Joy + 0x14);
    r9 = "TRG  %32b";
    r3 = 10;
    r4 = 16;
    r5 = 32;
    r6 = 64;
    r7 = 0;
    r8 = 5;
    r3 = eprintf2(10, 16, 32, 64, 0, 5, "TRG  %32b", *(uint32_t*)(&Joy + 0x14)); // [0x8008193C]
    r10 = *(uint32_t*)(&Joy + 0x18);
    r9 = "REL  %32b";
    r3 = 10;
    r4 = 16;
    r5 = 32;
    r6 = 80;
    r7 = 0;
    r8 = 5;
    r3 = eprintf2(10, 16, 32, 80, 0, 5, "REL  %32b", *(uint32_t*)(&Joy + 0x18)); // [0x8008193C]
    r10 = *(uint32_t*)(&Joy + 0x1C);
    r9 = "REP  %32b";
    r3 = 10;
    r4 = 16;
    r5 = 32;
    r6 = 96;
    r7 = 0;
    r8 = 5;
    r3 = eprintf2(10, 16, 32, 96, 0, 5, "REP  %32b", *(uint32_t*)(&Joy + 0x1C)); // [0x8008193C]
    r10 = *(uint32_t*)(&Joy + 0x20);
    r9 = "REP2 %32b";
    r3 = 10;
    r4 = 16;
    r5 = 32;
    r6 = 112;
    r7 = 0;
    r8 = 5;
    r3 = eprintf2(10, 16, 32, 112, 0, 5, "REP2 %32b", *(uint32_t*)(&Joy + 0x20)); // [0x8008193C]
    r10 = Joy;
    r9 = "STICK_X       %d";
    r3 = 10;
    r4 = 16;
    r5 = 32;
    r6 = 144;
    r7 = 0;
    r8 = 5;
    r3 = eprintf2(10, 16, 32, 144, 0, 5, "STICK_X       %d", Joy); // [0x8008193C]
    r10 = *(uint8_t*)(&Joy + 0x1);
    r9 = "STICK_Y       %d";
    r3 = 10;
    r4 = 16;
    r5 = 32;
    r6 = 160;
    r7 = 0;
    r8 = 5;
    r3 = eprintf2(10, 16, 32, 160, 0, 5, "STICK_Y       %d", *(uint8_t*)(&Joy + 0x1)); // [0x8008193C]
    r10 = *(uint8_t*)(&Joy + 0x2);
    r9 = "SUB_STICK_X   %d";
    r3 = 10;
    r4 = 16;
    r5 = 32;
    r6 = 176;
    r7 = 0;
    r8 = 5;
    r3 = eprintf2(10, 16, 32, 176, 0, 5, "SUB_STICK_X   %d", *(uint8_t*)(&Joy + 0x2)); // [0x8008193C]
    r10 = *(uint8_t*)(&Joy + 0x3);
    r9 = "SUB_STICK_Y   %d";
    r3 = 10;
    r4 = 16;
    r5 = 32;
    r6 = 192;
    r7 = 0;
    r8 = 5;
    r3 = eprintf2(10, 16, 32, 192, 0, 5, "SUB_STICK_Y   %d", *(uint8_t*)(&Joy + 0x3)); // [0x8008193C]
    r10 = *(uint8_t*)(&Joy + 0x4);
    r9 = "TRIGGER_LEFT  %d";
    r3 = 10;
    r4 = 16;
    r5 = 32;
    r6 = 208;
    r7 = 0;
    r8 = 5;
    r3 = eprintf2(10, 16, 32, 208, 0, 5, "TRIGGER_LEFT  %d", *(uint8_t*)(&Joy + 0x4)); // [0x8008193C]
    r10 = *(uint8_t*)(&Joy + 0x5);
    r9 = "TRIGGER_RIGHT %d";
    r3 = 10;
    r4 = 16;
    r5 = 32;
    r6 = 224;
    r7 = 0;
    r8 = 5;
    r3 = eprintf2(10, 16, 32, 224, 0, 5, "TRIGGER_RIGHT %d", *(uint8_t*)(&Joy + 0x5)); // [0x8008193C]
    r0 = stack_0x1C;
    return; // r3 = ret_800AD75C
}
