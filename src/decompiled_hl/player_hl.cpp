// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: player.obj
// Functions Decompiled: 53
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: cPlayer::Main(void)
// Unit: player.obj | Address: 0x800B17AC | Size: 0x6C8 bytes
// ============================================================================
/* [0x800B17AC] */ void cPlayer::Main(cPlayer* this_r3) {
    // Stack frame allocated: 56 bytes
    stack_0x3C = r0;
    stack_0x20 = r12;
    r9 = SDA1::pG;
    r31 = this_r3;
    r28 = 0;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B17F4;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B17F4:;
    r10 = SDA1::pG;
    r3 = this_r3;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r29 = *(uint32_t*)(this_r3 + 0xF0);
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA28) = 0;
    r3 = keyConfig(this_r3); // [0x800B6418]
    r11 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x14C);
    if (*(uint32_t*)(SDA1::pG + 0x14C) >= 0) goto label_800B185C;
    r9 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA26);
    r9 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA26) + (-1);
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA26) = (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA26) + -1);
    if (*(uint32_t*)(SDA1::pG + 0x14C) != 0) goto label_800B185C;
    r0 = *(uint32_t*)(SDA1::pG + 0x14C);
    r9 = 30;
    *(uint32_t*)(SDA1::pG + 0x14C) = *(uint32_t*)(SDA1::pG + 0x14C);
    *(uint8_t*)(this_r3 + 0x4E1) = 30;
label_800B185C:;
    r9 = *(uint8_t*)(this_r3 + 0x4E1);
    if (*(uint8_t*)(this_r3 + 0x4E1) == 0) goto label_800B18A4;
    if (*(uint8_t*)(this_r3 + 0x4E1) != 0) goto label_800B18A4;
    r0 = *(uint8_t*)(this_r3 + 0x4E1) + (-1);
    r28 = this_r3 + (192);
    *(uint8_t*)(this_r3 + 0x4E1) = (*(uint8_t*)(this_r3 + 0x4E1) + -1);
    r27 = this_r3 + (268);
    if (*(uint32_t*)(this_r3 + 0xF0) == 0) goto label_800B18CC;
    r0 = 2;
label_800B1890:;
    *(uint16_t*)(*(uint8_t*)(this_r3 + 0x4E1) + 0x24) = 2;
    r9 = *(uint32_t*)(*(uint8_t*)(this_r3 + 0x4E1) + 0x34);
    if (*(uint32_t*)(*(uint8_t*)(this_r3 + 0x4E1) + 0x34) != 0) goto label_800B1890;
    goto label_800B18CC;
label_800B18A4:;
    r28 = this_r3 + (192);
    r27 = this_r3 + (268);
    if (*(uint32_t*)(this_r3 + 0xF0) == 0) goto label_800B18CC;
    r0 = 1;
label_800B18BC:;
    *(uint16_t*)(*(uint32_t*)(*(uint8_t*)(this_r3 + 0x4E1) + 0x34) + 0x24) = 1;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint8_t*)(this_r3 + 0x4E1) + 0x34) + 0x34);
    if (*(uint32_t*)(*(uint32_t*)(*(uint8_t*)(this_r3 + 0x4E1) + 0x34) + 0x34) != 0) goto label_800B18BC;
label_800B18CC:;
    r9 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA24);
    if (*(uint32_t*)(*(uint32_t*)(*(uint8_t*)(this_r3 + 0x4E1) + 0x34) + 0x34) == 0) goto label_800B190C;
    if (*(uint32_t*)(*(uint32_t*)(*(uint8_t*)(this_r3 + 0x4E1) + 0x34) + 0x34) == 0) goto label_800B18FC;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA24) + (-1);
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA24) = (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA24) + -1);
    r0 = *(uint32_t*)(this_r3 + 0xF4);
    if (*(uint32_t*)(*(uint32_t*)(*(uint8_t*)(this_r3 + 0x4E1) + 0x34) + 0x34) == 0) goto label_800B1904;
    goto label_800B1908;
label_800B18FC:;
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA24) = *(uint32_t*)(this_r3 + 0xF4);
    r0 = *(uint32_t*)(this_r3 + 0xF4);
label_800B1904:;
    r0 = *(uint32_t*)(this_r3 + 0xF4) | 0x0002u;
label_800B1908:;
    *(uint32_t*)(this_r3 + 0xF4) = *(uint32_t*)(this_r3 + 0xF4);
label_800B190C:;
    r3 = this_r3;
    r3 = PlDamageCk(this_r3); // [0x800B788C]
    r0 = *(uint8_t*)(this_r3 + 0xF8);
    if (*(uint8_t*)(this_r3 + 0xF8) != 1) goto label_800B19D8;
    r10 = *(uint32_t*)(this_r3 + 0xC0);
    r9 = &stack_0x08;
    r11 = *(uint32_t*)((this_r3 + 192) + 0x4);
    r0 = *(uint32_t*)((this_r3 + 192) + 0x8);
    r3 = &stack_0x08;
    stack_0x08 = *(uint32_t*)(this_r3 + 0xC0);
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)((this_r3 + 192) + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)((this_r3 + 192) + 0x8);
    f13 = *(float*)0x8016CAF4;
    f0 = stack_0x0C;
    stack_0x0C = stack_0x0C;
    r4 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    r3 = SearchLockEm(&stack_0x08, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48)); // [0x8007D508]
    r8 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C);
    if (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C) == 0) goto label_800B19D8;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r11 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1756);
    if (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C) == 0) goto label_800B19C8;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C) != 0) goto label_800B19C8;
    r9 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85E);
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C) + (-1);
    if (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85E) >= (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C) + -1)) goto label_800B19A4;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85E) + (1);
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85E) = (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85E) + 1);
    goto label_800B19A8;
label_800B19A4:;
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85E) = *(uint32_t*)(this_r3 + 0xC0);
label_800B19A8:;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C);
    r11 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1756);
    if (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C) == 0) goto label_800B19C8;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85E);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x4C) = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85E);
label_800B19C8:;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85E);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85E);
label_800B19D8:;
    r0 = *(uint8_t*)(this_r3 + 0xF8);
    if (*(uint8_t*)(this_r3 + 0xF8) == 0) goto label_800B1A44;
    r3 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B19F4;
    r3 = cEm::lockOn(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48)); // [0x8002117C]
label_800B19F4:;
    r3 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) == 0) goto label_800B1A04;
    r3 = cEm::lockOn(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C)); // [0x8002117C]
label_800B1A04:;
    r3 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950) == 0) goto label_800B1A14;
    r3 = cEm::lockOn(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950)); // [0x8002117C]
label_800B1A14:;
    r3 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x954);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x954) == 0) goto label_800B1A24;
    r3 = cEm::lockOn(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x954)); // [0x8002117C]
label_800B1A24:;
    r3 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x958);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x958) == 0) goto label_800B1A34;
    r3 = cEm::lockOn(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x958)); // [0x8002117C]
label_800B1A34:;
    r3 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x95C);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x95C) == 0) goto label_800B1A44;
    r3 = cEm::lockOn(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x95C)); // [0x8002117C]
label_800B1A44:;
    r0 = *(uint8_t*)(this_r3 + 0xF8);
    if (*(uint8_t*)(this_r3 + 0xF8) == 2) goto label_800B1AA0;
    if (*(uint8_t*)(this_r3 + 0xF8) > 2) goto label_800B1A68;
    if (*(uint8_t*)(this_r3 + 0xF8) == 0) goto label_800B1A80;
    if (*(uint8_t*)(this_r3 + 0xF8) == 1) goto label_800B1A90;
    goto label_800B1ADC;
label_800B1A68:;
    if (*(uint8_t*)(this_r3 + 0xF8) == 4) goto label_800B1ADC;
    if (*(uint8_t*)(this_r3 + 0xF8) < 4) goto label_800B1AB0;
    if (*(uint8_t*)(this_r3 + 0xF8) == 5) goto label_800B1ACC;
    goto label_800B1ADC;
label_800B1A80:;
    r9 = *(uint32_t*)(this_r3 + 0x4B8);
    r3 = *(int16_t*)(*(uint32_t*)(this_r3 + 0x4B8) + 0x10);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x4B8) + 0x14);
    goto label_800B1ABC;
label_800B1A90:;
    r9 = *(uint32_t*)(this_r3 + 0x4B8);
    r3 = *(int16_t*)(*(uint32_t*)(this_r3 + 0x4B8) + 0x58);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x4B8) + 0x5C);
    goto label_800B1ABC;
label_800B1AA0:;
    r9 = *(uint32_t*)(this_r3 + 0x4B8);
    r3 = *(int16_t*)(*(uint32_t*)(this_r3 + 0x4B8) + 0x60);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x4B8) + 0x64);
    goto label_800B1ABC;
label_800B1AB0:;
    r9 = *(uint32_t*)(this_r3 + 0x4B8);
    r3 = *(int16_t*)(*(uint32_t*)(this_r3 + 0x4B8) + 0x68);
    r0 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x4B8) + 0x6C);
label_800B1ABC:;
    r3 = (this_r3 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x4B8) + 0x68));
    return; // r3 = (this_r3 + *(int16_t*)(*(uint32_t*)(this_r3 + 0x4B8) + 0x68))
    goto label_800B1ADC;
label_800B1ACC:;
    r9 = SDA1::EmDamageFunc;
    r3 = this_r3;
    return; // r3 = this_r3
label_800B1ADC:;
    f13 = *(float*)(this_r3 + 0xD0);
    f0 = *(float*)0x8016CAF8;
    if (*(uint8_t*)(this_r3 + 0xF8) != 5) goto label_800B1B18;
    f12 = *(float*)0x8016CAFC;
label_800B1B00:;
    if (*(uint8_t*)(this_r3 + 0xF8) != 5) goto label_800B1B00;
    *(float*)(this_r3 + 0xD0) = *(float*)0x8016CAF8;
label_800B1B18:;
    f13 = *(float*)(this_r3 + 0xD0);
    f0 = *(float*)0x8016CB00;
    if (*(uint8_t*)(this_r3 + 0xF8) != 5) goto label_800B1B54;
    f12 = *(float*)0x8016CAFC;
label_800B1B3C:;
    if (*(uint8_t*)(this_r3 + 0xF8) != 5) goto label_800B1B3C;
    *(float*)(this_r3 + 0xD0) = *(float*)0x8016CB00;
label_800B1B54:;
    r3 = this_r3;
    r3 = PartsWorldCalc(this_r3); // [0x800A0E5C]
    r3 = this_r3;
    r3 = PlWaistCtrl(this_r3); // [0x800AE384]
    r3 = this_r3;
    r3 = PartsWorldPosCalc(this_r3); // [0x800A1D58]
    r3 = this_r3;
    r3 = EmAtCheck(this_r3); // [0x8000892C]
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA28);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA28) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA28);
    r3 = this_r3;
    r3 = ScrAtCheck(this_r3); // [0x80006670]
    r3 = this_r3;
    r3 = PlFallCheck(this_r3); // [0x800B7520]
    r3 = this_r3;
    r3 = FallDieCk(this_r3); // [0x800B7AD4]
    r3 = this_r3;
    r3 = AtariMove(this_r3); // [0x800086EC]
    r3 = this_r3;
    r3 = PartsWorldPosCalc(this_r3); // [0x800A1D58]
    r9 = *(uint32_t*)(this_r3 + 0xC0);
    r11 = *(uint32_t*)((this_r3 + 192) + 0x4);
    r0 = *(uint32_t*)((this_r3 + 192) + 0x8);
    *(uint32_t*)(this_r3 + 0x10C) = *(uint32_t*)(this_r3 + 0xC0);
    *(uint32_t*)((this_r3 + 268) + 0x8) = *(uint32_t*)((this_r3 + 192) + 0x8);
    *(uint32_t*)((this_r3 + 268) + 0x4) = *(uint32_t*)((this_r3 + 192) + 0x4);
    if (*(uint8_t*)(this_r3 + 0xF8) == 5) goto label_800B1BF0;
label_800B1BC4:;
    r8 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0x108);
    r9 = *(uint32_t*)(this_r3 + 0xF0) + (264);
    r10 = *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 264) + 0x8);
    r11 = *(uint32_t*)(this_r3 + 0xF0) + (428);
    r0 = *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 264) + 0x4);
    *(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0x1AC) = *(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0x108);
    *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 428) + 0x8) = *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 264) + 0x8);
    *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 428) + 0x4) = *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 264) + 0x4);
    r29 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0xF0);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0xF0) != 0) goto label_800B1BC4;
label_800B1BF0:;
    r3 = this_r3;
    r3 = PlayerSubCamera(this_r3); // [0x800ADD8C]
    r0 = *(uint8_t*)(this_r3 + 0xF8);
    if (*(uint8_t*)(this_r3 + 0xF8) == 1) goto label_800B1C70;
    r11 = *(uint32_t*)(this_r3 + 0xC0);
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1668);
    r10 = *(uint32_t*)((this_r3 + 192) + 0x8);
    r7 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1680);
    r0 = *(uint32_t*)((this_r3 + 192) + 0x4);
    r6 = 2;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x684) = *(uint32_t*)(this_r3 + 0xC0);
    r8 = this_r3;
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1668) + 0x8) = *(uint32_t*)((this_r3 + 192) + 0x8);
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1668) + 0x4) = *(uint32_t*)((this_r3 + 192) + 0x4);
label_800B1C2C:;
    r11 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680);
    r9 = this_r3;
    r7 = 4;
    r10 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + (16);
    r8 = this_r3 + (16);
    r0 = 2 + (-1);
label_800B1C48:;
    f0 = *(float*)(this_r3 + 0x0);
    r9 = this_r3 + (4);
    *(float*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + 0x0) = *(float*)(this_r3 + 0x0);
    r11 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + (4);
    if (*(uint8_t*)(this_r3 + 0xF8) >= 1) goto label_800B1C48;
    r6 = (2 + -1);
    r7 = (((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + 16);
    if ((2 + -1) != -1) goto label_800B1C2C;
    goto label_800B1D64;
label_800B1C70:;
    r0 = *(uint8_t*)(this_r3 + 0xF9);
    if (*(uint8_t*)(this_r3 + 0xF9) == 0) goto label_800B1CF0;
    if (*(uint8_t*)(this_r3 + 0xF9) == 5) goto label_800B1CF0;
    r11 = *(uint32_t*)(this_r3 + 0xC0);
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1668);
    r10 = *(uint32_t*)((this_r3 + 192) + 0x8);
    r7 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1680);
    r0 = *(uint32_t*)((this_r3 + 192) + 0x4);
    r6 = 2;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x684) = *(uint32_t*)(this_r3 + 0xC0);
    r8 = this_r3;
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1668) + 0x8) = *(uint32_t*)((this_r3 + 192) + 0x8);
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1668) + 0x4) = *(uint32_t*)((this_r3 + 192) + 0x4);
label_800B1CAC:;
    r11 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680);
    r9 = this_r3;
    r7 = 4;
    r10 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + (16);
    r8 = this_r3 + (16);
    r0 = 2 + (-1);
label_800B1CC8:;
    f0 = *(float*)(this_r3 + 0x0);
    r9 = this_r3 + (4);
    *(float*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + 0x0) = *(float*)(this_r3 + 0x0);
    r11 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + (4);
    if (*(uint8_t*)(this_r3 + 0xF9) >= 5) goto label_800B1CC8;
    r6 = (2 + -1);
    r7 = (((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + 16);
    if ((2 + -1) != -1) goto label_800B1CAC;
    goto label_800B1D64;
label_800B1CF0:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA28);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA28) == 0) goto label_800B1D64;
    r11 = *(uint32_t*)(this_r3 + 0xC0);
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1668);
    r10 = *(uint32_t*)((this_r3 + 192) + 0x8);
    r7 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1680);
    r0 = *(uint32_t*)((this_r3 + 192) + 0x4);
    r6 = 2;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x684) = *(uint32_t*)(this_r3 + 0xC0);
    r8 = this_r3;
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1668) + 0x8) = *(uint32_t*)((this_r3 + 192) + 0x8);
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1668) + 0x4) = *(uint32_t*)((this_r3 + 192) + 0x4);
label_800B1D24:;
    r11 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680);
    r9 = this_r3;
    r7 = 4;
    r10 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + (16);
    r8 = this_r3 + (16);
    r0 = 2 + (-1);
label_800B1D40:;
    f0 = *(float*)(this_r3 + 0x0);
    r9 = this_r3 + (4);
    *(float*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + 0x0) = *(float*)(this_r3 + 0x0);
    r11 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + (4);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA28) >= 0) goto label_800B1D40;
    r6 = (2 + -1);
    r7 = (((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + 16);
    if ((2 + -1) != -1) goto label_800B1D24;
label_800B1D64:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if ((2 + -1) == -1) goto label_800B1DF0;
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D0);
    f13 = *(float*)0x8016CB04;
    f12 = *(float*)0x8016CB08;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D0) = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D0);
    if ((2 + -1) >= -1) goto label_800B1D9C;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D0) = *(float*)0x8016CB08;
label_800B1D9C:;
    r3 = *(uint32_t*)(this_r3 + 0x130);
    r4 = 0;
    r3 = GetModelInfo(*(uint32_t*)(this_r3 + 0x130), 0); // [0x800B7350]
    r0 = *(uint8_t*)(ret_800B1DA4 + 0x5F);
    f13 = *(double*)0x8016CB10;
    stack_0x1C = *(uint8_t*)(ret_800B1DA4 + 0x5F);
    r9 = 0x80170000u;
    f11 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D0);
    stack_0x18 = 0x43300000u;
    f0 = stack_0x18;
    stack_0x18 = *(float*)0x8016CB08;
    r9 = stack_0x1C;
    *(uint8_t*)(ret_800B1DA4 + 0x5F) = stack_0x1C;
label_800B1DF0:;
    r0 = *(uint8_t*)(this_r3 + 0xF9);
    if (*(uint8_t*)(this_r3 + 0xF9) == 10) goto label_800B1E58;
    r11 = SDA1::pG;
    f13 = *(float*)0x8016CB18;
    f0 = *(float*)(SDA1::pG + 0x42C);
    if (*(uint8_t*)(this_r3 + 0xF9) >= 10) goto label_800B1E38;
    r3 = *(uint32_t*)(this_r3 + 0x130);
    if (*(uint32_t*)(this_r3 + 0x130) == 0) goto label_800B1E58;
    r0 = 64;
label_800B1E24:;
    *(uint8_t*)(*(uint32_t*)(this_r3 + 0x130) + 0x5F) = 64;
    r3 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x130) + 0x4);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x130) + 0x4) != 0) goto label_800B1E24;
    goto label_800B1E58;
label_800B1E38:;
    r3 = *(uint32_t*)(this_r3 + 0x130);
    if (*(uint32_t*)(this_r3 + 0x130) == 0) goto label_800B1E58;
    r0 = 255;
label_800B1E48:;
    *(uint8_t*)(*(uint32_t*)(this_r3 + 0x130) + 0x5F) = 255;
    r3 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x130) + 0x4);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0x130) + 0x4) != 0) goto label_800B1E48;
label_800B1E58:;
    r0 = stack_0x3C;
    r12 = stack_0x20;
    return; // r3 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0x130) + 0x4)
}

// ============================================================================
// High-Level AST Decompilation: cPlayer::Initialize(void)
// Unit: player.obj | Address: 0x800B1E74 | Size: 0x42C bytes
// ============================================================================
/* [0x800B1E74] */ void cPlayer::Initialize(cPlayer* this_r3) {
    // Stack frame allocated: 88 bytes
    stack_0x5C = r0;
    r9 = SDA1::pG;
    r31 = this_r3;
    r29 = 0;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B1EB4;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B1EB4:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r5 = 1;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r4 = &Pl_at_light;
    *(uint32_t*)(this_r3 + 0x50C) = 0x80800000u;
    r3 = this_r3 + (312);
    r23 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    r3 = LightInfoInit((this_r3 + 312), &Pl_at_light, 1); // [0x8009AF88]
    r22 = this_r3 + (192);
    f1 = *(float*)0x8016CB1C;
    f2 = *(float*)0x8016CB20;
    f4 = *(float*)0x8016CB24;
    r5 = 10;
    f5 = *(float*)0x8016CB28;
    r6 = 4096;
    f6 = *(float*)0x8016CB2C;
    r3 = this_r3;
    f7 = *(float*)0x8016CB30;
    r4 = 1;
    r3 = AtariInit2(this_r3, *(float*)0x8016CB1C, *(float*)0x8016CB20, f3, *(float*)0x8016CB24, *(float*)0x8016CB28, *(float*)0x8016CB2C, *(float*)0x8016CB30, 1, 10, 4096); // [0x800085FC]
    r0 = 130;
    f0 = *(float*)0x8016CB1C;
    *(uint8_t*)(this_r3 + 0x125) = 130;
    r9 = SDA1::pG;
    r4 = &stack_0x20;
    f11 = *(float*)0x8016CB34;
    r3 = &stack_0x10;
    r0 = *(int16_t*)(SDA1::pG + 0x6810);
    f12 = *(float*)0x8016CB38;
    *(uint32_t*)(this_r3 + 0x4D4) = *(int16_t*)(SDA1::pG + 0x6810);
    f13 = *(float*)0x8016CB3C;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x64) = *(float*)0x8016CB1C;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x68) = *(float*)0x8016CB1C;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C) = *(float*)0x8016CB1C;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) = 0;
    stack_0x14 = *(float*)0x8016CB34;
    stack_0x18 = *(float*)0x8016CB38;
    stack_0x24 = *(float*)0x8016CB3C;
    stack_0x28 = *(float*)0x8016CB1C;
    stack_0x10 = *(float*)0x8016CB1C;
    stack_0x20 = *(float*)0x8016CB1C;
    SDA1::EmDamageFunc = 0;
    r3 = CameraBehindSet(&stack_0x10, &stack_0x20); // [0x800B7370]
    r0 = 1;
    r3 = this_r3;
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C2) = 1;
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C0) = 1;
    r3 = plModelInit(this_r3); // [0x800B7064]
    r3 = *(uint32_t*)(this_r3 + 0xF0);
    r4 = 0;
    r3 = GetPartsAddr(*(uint32_t*)(this_r3 + 0xF0), 0); // [0x800A0BD4]
    r0 = *(uint32_t*)(ret_800B1FAC + 0x194);
    r4 = 40;
    r11 = SDA1::pG;
    r0 = *(uint32_t*)(ret_800B1FAC + 0x194) | 0x0001u;
    *(uint32_t*)(ret_800B1FAC + 0x194) = *(uint32_t*)(ret_800B1FAC + 0x194);
    r9 = *(uint32_t*)(SDA1::pG + 0x118);
    r3 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x14);
    r3 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x14) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = EspDataLoad((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x14) + *(uint32_t*)(SDA1::pG + 0x118)), 40); // [0x800828A8]
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = this_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r4 = this_r3 + (380);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18);
    r6 = 0;
    r7 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(this_r3, (this_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 0, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    f1 = *(float*)0x8016CB40;
    r3 = this_r3;
    f2 = *(float*)0x8016CB44;
    r3 = MotionMove(this_r3, *(float*)0x8016CB40, *(float*)0x8016CB44); // [0x800A2434]
    r3 = *(uint32_t*)(this_r3 + 0xF0);
    if (*(uint32_t*)(this_r3 + 0xF0) == 0) goto label_800B205C;
label_800B2030:;
    r8 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0x108);
    r9 = *(uint32_t*)(this_r3 + 0xF0) + (264);
    r10 = *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 264) + 0x8);
    r11 = *(uint32_t*)(this_r3 + 0xF0) + (428);
    r0 = *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 264) + 0x4);
    *(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0x1AC) = *(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0x108);
    *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 428) + 0x8) = *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 264) + 0x8);
    *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 428) + 0x4) = *(uint32_t*)((*(uint32_t*)(this_r3 + 0xF0) + 264) + 0x4);
    r3 = *(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0xF0);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0xF0) != 0) goto label_800B2030;
label_800B205C:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0xF0) == 0) goto label_800B2088;
    *(uint32_t*)(this_r3 + 0xF8) = 0x010A0000u;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    *(uint32_t*)(SDA1::pG + 0x124) = *(uint32_t*)(SDA1::pG + 0x124);
    goto label_800B2110;
label_800B2088:;
    r4 = 5;
    *(uint32_t*)(this_r3 + 0xF8) = 0x01000000u;
    r3 = 40;
    r3 = EspGetEstAddr(40, 5); // [0x800833A4]
    r30 = ret_800B2098;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B20A4;
    r6 = ret_800B2098;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = this_r3;
    stack_0x08 = 0;
    r4 = 0;
    r3 = this_r3;
    r3 = EstSet(this_r3, 0, 0, ret_800B2098, ret_800B20A4, 0, 0, this_r3, (*(uint32_t*)(this_r3 + 0xF0) + 428)); // [0x800906FC]
    r4 = 6;
    r3 = 40;
    r3 = EspGetEstAddr(40, 6); // [0x800833A4]
    r30 = ret_800B20D8;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B20E4;
    stack_0x08 = 0;
    r6 = ret_800B20D8;
    r3 = this_r3;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = this_r3;
    r3 = EstSet(this_r3, 0, 0, ret_800B20D8, ret_800B20E4, 0, 0, this_r3, (*(uint32_t*)(this_r3 + 0xF0) + 428)); // [0x800906FC]
label_800B2110:;
    f1 = *(float*)0x8016CB1C;
    f2 = *(float*)0x8016CB48;
    f4 = *(float*)0x8016CB4C;
    f5 = *(float*)0x8016CB50;
    r3 = this_r3;
    r4 = 3;
    r5 = 1;
    r3 = YarareInit(this_r3, *(float*)0x8016CB1C, *(float*)0x8016CB48, f3, *(float*)0x8016CB4C, *(float*)0x8016CB50, 3, 1, *(float*)0x8016CB2C, *(float*)0x8016CB30); // [0x800088B4]
    f1 = *(float*)0x8016CB1C;
    f2 = *(float*)0x8016CB54;
    f4 = *(float*)0x8016CB58;
    f5 = *(float*)0x8016CB40;
    r3 = this_r3;
    r4 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2156);
    r5 = 17;
    r6 = 1;
    r3 = YarareAdd(this_r3, ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 2156), *(float*)0x8016CB1C, *(float*)0x8016CB54, f3, *(float*)0x8016CB58, *(float*)0x8016CB40, 17, 1, *(float*)0x8016CB2C, *(float*)0x8016CB30); // [0x800088D8]
    f1 = *(float*)0x8016CB1C;
    f2 = *(float*)0x8016CB5C;
    r3 = this_r3;
    f4 = *(float*)0x8016CB60;
    f5 = *(float*)0x8016CB64;
    r4 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2212);
    r5 = 18;
    r6 = 1;
    r3 = YarareAdd(this_r3, ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 2212), *(float*)0x8016CB1C, *(float*)0x8016CB5C, f3, *(float*)0x8016CB60, *(float*)0x8016CB64, 18, 1, *(float*)0x8016CB2C, *(float*)0x8016CB30); // [0x800088D8]
    f1 = *(float*)0x8016CB1C;
    r3 = this_r3;
    f2 = *(float*)0x8016CB54;
    r4 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2268);
    f4 = *(float*)0x8016CB58;
    f5 = *(float*)0x8016CB40;
    r5 = 21;
    r6 = 1;
    r3 = YarareAdd(this_r3, ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 2268), *(float*)0x8016CB1C, *(float*)0x8016CB54, f3, *(float*)0x8016CB58, *(float*)0x8016CB40, 21, 1, *(float*)0x8016CB2C, *(float*)0x8016CB30); // [0x800088D8]
    f1 = *(float*)0x8016CB1C;
    r3 = this_r3;
    f2 = *(float*)0x8016CB5C;
    r4 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2324);
    f4 = *(float*)0x8016CB60;
    f5 = *(float*)0x8016CB64;
    r5 = 22;
    r6 = 1;
    r3 = YarareAdd(this_r3, ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 2324), *(float*)0x8016CB1C, *(float*)0x8016CB5C, f3, *(float*)0x8016CB60, *(float*)0x8016CB64, 22, 1, *(float*)0x8016CB2C, *(float*)0x8016CB30); // [0x800088D8]
    r11 = *(uint32_t*)(this_r3 + 0xC0);
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1668);
    r10 = *(uint32_t*)((this_r3 + 192) + 0x8);
    r8 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1680);
    r0 = *(uint32_t*)((this_r3 + 192) + 0x4);
    r3 = this_r3;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x684) = *(uint32_t*)(this_r3 + 0xC0);
    r7 = 2;
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1668) + 0x8) = *(uint32_t*)((this_r3 + 192) + 0x8);
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1668) + 0x4) = *(uint32_t*)((this_r3 + 192) + 0x4);
label_800B224C:;
    r9 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680);
    r10 = this_r3 + (16);
    r8 = 4;
    r11 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + (16);
    r0 = 2 + (-1);
label_800B2264:;
    f0 = *(float*)(this_r3 + 0x0);
    r3 = this_r3 + (4);
    *(float*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + 0x0) = *(float*)(this_r3 + 0x0);
    r9 = ((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + (4);
    if (*(uint32_t*)(*(uint32_t*)(this_r3 + 0xF0) + 0xF0) >= 0) goto label_800B2264;
    r7 = (2 + -1);
    r8 = (((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 1680) + 16);
    r3 = (this_r3 + 16);
    if ((2 + -1) != -1) goto label_800B224C;
    r0 = stack_0x5C;
    return; // r3 = (this_r3 + 16)
}

// ============================================================================
// High-Level AST Decompilation: cPlayer::Move(void)
// Unit: player.obj | Address: 0x800B22A0 | Size: 0x38 bytes
// ============================================================================
/* [0x800B22A0] */ void cPlayer::Move(cPlayer* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r0 = *(uint8_t*)(this_r3 + 0xF9);
    r9 = &pl_move_func_tbl.1059;
    return; // r3 = this_r3
    r0 = stack_0x0C;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cPlayer::Damage(void)
// Unit: player.obj | Address: 0x800B22D8 | Size: 0x4E4 bytes
// ============================================================================
/* [0x800B22D8] */ void cPlayer::Damage(cPlayer* this_r3) {
    // Stack frame allocated: 56 bytes
    stack_0x30 = f31;
    stack_0x3C = r0;
    r9 = SDA1::pG;
    r31 = this_r3;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B2318;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B2318:;
    r11 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r8 = this_r3 + (192);
    r7 = *(uint32_t*)(this_r3 + 0xC0);
    r9 = &stack_0x10;
    r10 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r0 = *(uint32_t*)((this_r3 + 192) + 0x4);
    r4 = &stack_0x10;
    r11 = *(uint32_t*)((this_r3 + 192) + 0x8);
    r29 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    stack_0x10 = *(uint32_t*)(this_r3 + 0xC0);
    r3 = this_r3 + (284);
    *(uint32_t*)(&stack_0x10 + 0x4) = *(uint32_t*)((this_r3 + 192) + 0x4);
    r5 = 0;
    *(uint32_t*)(&stack_0x10 + 0x8) = *(uint32_t*)((this_r3 + 192) + 0x8);
    f13 = *(float*)0x8016CB68;
    f0 = stack_0x14;
    stack_0x14 = stack_0x14;
    r3 = GetFloor2((this_r3 + 284), &stack_0x10, 0); // [0x80007910]
    r0 = *(uint8_t*)(this_r3 + 0xF9);
    if (*(uint8_t*)(this_r3 + 0xF9) == 2) goto label_800B254C;
    if (*(uint8_t*)(this_r3 + 0xF9) > 2) goto label_800B2390;
    if (*(uint8_t*)(this_r3 + 0xF9) == 0) goto label_800B23A8;
    if (*(uint8_t*)(this_r3 + 0xF9) == 1) goto label_800B24B0;
    goto label_800B27A4;
label_800B2390:;
    if (*(uint8_t*)(this_r3 + 0xF9) == 4) goto label_800B26BC;
    if (*(uint8_t*)(this_r3 + 0xF9) < 4) goto label_800B2650;
    if (*(uint8_t*)(this_r3 + 0xF9) == 5) goto label_800B2708;
    goto label_800B27A4;
label_800B23A8:;
    r0 = 90;
    r9 = -32168;
    *(uint8_t*)(this_r3 + 0x4E1) = 90;
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA24) = -32168;
    r0 = *(uint8_t*)(this_r3 + 0x4E3);
    if (*(uint8_t*)(this_r3 + 0x4E3) != 3) goto label_800B2400;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = this_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = this_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x184);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x184) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(this_r3, (this_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x184) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B2438;
label_800B2400:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = this_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = this_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x5C);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x5C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(this_r3, (this_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x5C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
label_800B2438:;
    r4 = 49;
    r3 = 40;
    r3 = EspGetEstAddr(40, 49); // [0x800833A4]
    r29 = 0;
    r30 = ret_800B2440;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B2450;
    r9 = 0;
    r6 = ret_800B2440;
    stack_0x08 = 0;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r10 = this_r3;
    r3 = this_r3;
    r3 = EstSet(this_r3, 0, 0, ret_800B2440, ret_800B2450, 0, 0, this_r3, SDA1::pG); // [0x800906FC]
    r3 = 0;
    r4 = 16;
    r5 = this_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 16, (this_r3 + 192), 0); // [0x800CB7DC]
    r9 = *(uint16_t*)(this_r3 + 0x45A);
    r0 = 1;
    *(uint8_t*)(this_r3 + 0xF9) = 1;
    r3 = 1;
    *(uint16_t*)(this_r3 + 0x45A) = *(uint16_t*)(this_r3 + 0x45A);
    SDA1::damage_se = 0;
    r3 = PlVibSet(1); // [0x800B9098]
label_800B24B0:;
    f1 = *(float*)0x8016CB6C;
    r3 = this_r3;
    f2 = *(float*)0x8016CB70;
    r3 = MotionMove(this_r3, *(float*)0x8016CB6C, *(float*)0x8016CB70); // [0x800A2434]
    if (ret_800B24C4 == 0) goto label_800B2510;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (ret_800B24C4 != 0) goto label_800B2510;
    r0 = SDA1::damage_se;
    if (SDA1::damage_se != 0) goto label_800B2508;
    r0 = *(uint16_t*)(this_r3 + 0x42C);
    if (*(uint16_t*)(this_r3 + 0x42C) <= 0x10u) goto label_800B2508;
    r3 = 3;
    r3 = Snd_footse_call(3); // [0x800CD030]
    r0 = 1;
    SDA1::damage_se = 1;
label_800B2508:;
    r0 = 4;
    *(uint8_t*)(this_r3 + 0xF9) = 4;
label_800B2510:;
    f0 = *(float*)(this_r3 + 0xC4);
    if (*(uint16_t*)(this_r3 + 0x42C) != 0x10u) goto label_800B27A4;
    r0 = SDA1::damage_se;
    if (SDA1::damage_se != 0) goto label_800B27A4;
    r0 = *(uint16_t*)(this_r3 + 0x42C);
    if (*(uint16_t*)(this_r3 + 0x42C) <= 0x10u) goto label_800B27A4;
    r3 = 3;
    r3 = Snd_footse_call(3); // [0x800CD030]
    r0 = 1;
    SDA1::damage_se = 1;
    goto label_800B27A4;
label_800B254C:;
    r0 = 60;
    r9 = -32168;
    *(uint8_t*)(this_r3 + 0x4E1) = 60;
    *(uint16_t*)(0 + 0xA24) = -32168;
    r0 = *(uint8_t*)(this_r3 + 0x4E3);
    if (*(uint8_t*)(this_r3 + 0x4E3) != 3) goto label_800B25A4;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = this_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = this_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x54);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x54) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(this_r3, (this_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x54) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B25DC;
label_800B25A4:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = this_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = this_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x60);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x60) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(this_r3, (this_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x60) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
label_800B25DC:;
    r5 = this_r3 + (192);
    r6 = 0;
    r4 = 16;
    r3 = 0;
    r3 = SndSeCall(0, 16, (this_r3 + 192), 0); // [0x800CB7DC]
    r4 = 48;
    r3 = 40;
    r3 = EspGetEstAddr(40, 48); // [0x800833A4]
    r30 = ret_800B25F8;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r0 = 0;
    r7 = ret_800B2604;
    stack_0x08 = 0;
    r9 = 0;
    r6 = ret_800B25F8;
    r3 = this_r3;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r10 = this_r3;
    r3 = EstSet(this_r3, 0, 0, ret_800B25F8, ret_800B2604, 0, 0, this_r3, SDA1::pG); // [0x800906FC]
    r9 = *(uint16_t*)(this_r3 + 0x45A);
    r0 = 3;
    *(uint8_t*)(this_r3 + 0xF9) = 3;
    r3 = 0;
    *(uint16_t*)(this_r3 + 0x45A) = *(uint16_t*)(this_r3 + 0x45A);
    r3 = PlVibSet(0); // [0x800B9098]
label_800B2650:;
    r0 = 1;
    f1 = *(float*)0x8016CB6C;
    f2 = *(float*)0x8016CB70;
    r3 = this_r3;
    *(uint8_t*)(this_r3 + 0x4E1) = 1;
    r3 = MotionMove(this_r3, *(float*)0x8016CB6C, *(float*)0x8016CB70); // [0x800A2434]
    if (ret_800B266C == 0) goto label_800B27A4;
    f0 = *(float*)(this_r3 + 0xC4);
    if (ret_800B266C != 0) goto label_800B2694;
    r0 = 0x01000001u;
    *(uint32_t*)(this_r3 + 0xF8) = 0x01000001u;
label_800B2694:;
    r9 = 30;
    r0 = 0x01000001u;
    *(uint8_t*)(this_r3 + 0x4E1) = 30;
    *(uint32_t*)(this_r3 + 0xF8) = 0x01000001u;
    r9 = -32738;
    *(uint16_t*)(0 + 0xA24) = -32738;
    r0 = 0;
    *(uint8_t*)(this_r3 + 0x4E0) = 0;
    goto label_800B27A4;
label_800B26BC:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = this_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r4 = this_r3 + (380);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x58);
    r6 = 0;
    r7 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x58) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(this_r3, (this_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x58) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 0, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = *(uint32_t*)(this_r3 + 0xF4);
    r9 = 5;
    *(uint8_t*)(this_r3 + 0xF9) = 5;
    r0 = *(uint32_t*)(this_r3 + 0xF4) | 0x0040u;
    *(uint32_t*)(this_r3 + 0xF4) = *(uint32_t*)(this_r3 + 0xF4);
label_800B2708:;
    r0 = 1;
    f1 = *(float*)0x8016CB6C;
    f2 = *(float*)0x8016CB70;
    r3 = this_r3;
    *(uint8_t*)(this_r3 + 0x4E1) = 1;
    r3 = MotionMove(this_r3, *(float*)0x8016CB6C, *(float*)0x8016CB70); // [0x800A2434]
    if (ret_800B2724 == 0) goto label_800B2760;
    r9 = *(uint32_t*)(this_r3 + 0xF4);
    r0 = 0x01000001u;
    r10 = 30;
    *(uint32_t*)(this_r3 + 0xF8) = 0x01000001u;
    *(uint32_t*)(this_r3 + 0xF4) = *(uint32_t*)(this_r3 + 0xF4);
    r11 = -32738;
    *(uint8_t*)(this_r3 + 0x4E1) = 30;
    r0 = 0;
    *(uint16_t*)(0 + 0xA24) = -32738;
    *(uint8_t*)(this_r3 + 0x4E0) = 0;
label_800B2760:;
    r0 = *(uint16_t*)(this_r3 + 0x42C);
    if (*(uint16_t*)(this_r3 + 0x42C) != 20) goto label_800B2780;
    r3 = 0;
    r4 = 10;
    r5 = this_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 10, (this_r3 + 192), 0); // [0x800CB7DC]
label_800B2780:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (*(uint16_t*)(this_r3 + 0x42C) != 20) goto label_800B27A4;
    r0 = *(uint16_t*)(this_r3 + 0x42C);
    if (*(uint16_t*)(this_r3 + 0x42C) != 46) goto label_800B27A4;
    r3 = 2;
    r3 = Snd_footse_call(2); // [0x800CD030]
label_800B27A4:;
    r0 = stack_0x3C;
    f31 = stack_0x30;
    return; // r3 = ret_800B27A0
}

// ============================================================================
// High-Level AST Decompilation: cPlayer::Die(void)
// Unit: player.obj | Address: 0x800B27BC | Size: 0x294 bytes
// ============================================================================
/* [0x800B27BC] */ void cPlayer::Die(cPlayer* this_r3) {
    // Stack frame allocated: 56 bytes
    stack_0x30 = f31;
    stack_0x3C = r0;
    r9 = SDA1::pG;
    r31 = this_r3;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B27FC;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B27FC:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r7 = *(uint32_t*)(this_r3 + 0xC0);
    r11 = this_r3 + (192);
    f13 = *(float*)0x8016CB74;
    r28 = (this_r3 + 192);
    r8 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r3 = this_r3 + (284);
    f0 = *(float*)(this_r3 + 0x110);
    r10 = &stack_0x10;
    r0 = *(uint32_t*)((this_r3 + 192) + 0x4);
    r29 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    r9 = *(uint32_t*)((this_r3 + 192) + 0x8);
    stack_0x10 = *(uint32_t*)(this_r3 + 0xC0);
    r4 = &stack_0x10;
    *(uint32_t*)(&stack_0x10 + 0x4) = *(uint32_t*)((this_r3 + 192) + 0x4);
    *(uint32_t*)(&stack_0x10 + 0x8) = *(uint32_t*)((this_r3 + 192) + 0x8);
    stack_0x14 = *(float*)(this_r3 + 0x110);
    r3 = GetFloor((this_r3 + 284), &stack_0x10); // [0x800078EC]
    r30 = *(uint8_t*)(this_r3 + 0xF9);
    if (*(uint8_t*)(this_r3 + 0xF9) == 1) goto label_800B2970;
    if (*(uint8_t*)(this_r3 + 0xF9) > 1) goto label_800B286C;
    if (*(uint8_t*)(this_r3 + 0xF9) == 0) goto label_800B2880;
    goto label_800B2A38;
label_800B286C:;
    if (*(uint8_t*)(this_r3 + 0xF9) == 2) goto label_800B29B0;
    if (*(uint8_t*)(this_r3 + 0xF9) == 3) goto label_800B29F8;
    goto label_800B2A38;
label_800B2880:;
    r0 = *(uint8_t*)(this_r3 + 0x4E3);
    if (*(uint8_t*)(this_r3 + 0x4E3) != 3) goto label_800B28C8;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = this_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = this_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x184);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x184) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(this_r3, (this_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x184) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B2900;
label_800B28C8:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = this_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = this_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x5C);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x5C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(this_r3, (this_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x5C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
label_800B2900:;
    r4 = 49;
    r3 = 40;
    r3 = EspGetEstAddr(40, 49); // [0x800833A4]
    r29 = 0;
    r30 = ret_800B2908;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B2918;
    r10 = this_r3;
    r6 = ret_800B2908;
    stack_0x08 = 0;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r3 = this_r3;
    r3 = EstSet(this_r3, 0, 0, ret_800B2908, ret_800B2918, 0, 0, this_r3, SDA1::pG); // [0x800906FC]
    r5 = (this_r3 + 192);
    r3 = 0;
    r4 = 20;
    r6 = 0;
    r3 = SndSeCall(0, 20, (this_r3 + 192), 0); // [0x800CB7DC]
    r0 = 1;
    r3 = 10;
    *(uint8_t*)(this_r3 + 0xF9) = 1;
    SDA1::damage_se = 0;
    r3 = PlVibSet(10); // [0x800B9098]
    goto label_800B2A38;
label_800B2970:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    f0 = *(float*)(this_r3 + 0xC4);
    if (*(uint8_t*)(this_r3 + 0x4E3) != 3) goto label_800B2A38;
    r0 = SDA1::damage_se;
    if (SDA1::damage_se != 0) goto label_800B2A38;
    r0 = *(uint16_t*)(this_r3 + 0x42C);
    if (*(uint16_t*)(this_r3 + 0x42C) <= 0x15u) goto label_800B2A38;
    r3 = 3;
    r3 = Snd_footse_call(3); // [0x800CD030]
    SDA1::damage_se = ret_800B2908;
    goto label_800B2A38;
label_800B29B0:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = this_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r4 = this_r3 + (380);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x34);
    r6 = 0;
    r7 = 5;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x34) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(this_r3, (this_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x34) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = 20;
    r9 = 3;
    *(uint16_t*)(0 + 0x660) = 20;
    *(uint8_t*)(this_r3 + 0xF9) = 3;
label_800B29F8:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    r9 = *(uint16_t*)(0 + 0x660);
    if (20 == 0) goto label_800B2A1C;
    r0 = *(uint16_t*)(0 + 0x660) + (-1);
    *(uint16_t*)(0 + 0x660) = (*(uint16_t*)(0 + 0x660) + -1);
    goto label_800B2A38;
label_800B2A1C:;
    *(uint8_t*)(this_r3 + 0x4E0) = (*(uint16_t*)(0 + 0x660) + -1);
    r9 = SDA1::pG;
    r0 = *(int16_t*)(SDA1::pG + 0x6812);
    *(uint16_t*)(SDA1::pG + 0x6810) = *(int16_t*)(SDA1::pG + 0x6812);
    *(uint32_t*)(this_r3 + 0xF8) = 0x01000000u;
    *(uint32_t*)(this_r3 + 0x4D4) = *(int16_t*)(SDA1::pG + 0x6812);
label_800B2A38:;
    r0 = stack_0x3C;
    f31 = stack_0x30;
    return; // r3 = ret_800B29FC
}

// ============================================================================
// High-Level AST Decompilation: cPlayer::Show(void)
// Unit: player.obj | Address: 0x800B2A50 | Size: 0xB8 bytes
// ============================================================================
/* [0x800B2A50] */ void cPlayer::Show(cPlayer* this_r3) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r29 = this_r3;
    r4 = 5;
    r0 = *(uint32_t*)(this_r3 + 0xF4);
    r3 = 40;
    r28 = 0;
    r0 = *(uint32_t*)(this_r3 + 0xF4) | 0x000Au;
    *(uint32_t*)(this_r3 + 0xF4) = *(uint32_t*)(this_r3 + 0xF4);
    r3 = EspGetEstAddr(40, 5); // [0x800833A4]
    r30 = ret_800B2A7C;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B2A88;
    r6 = ret_800B2A7C;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = this_r3;
    stack_0x08 = 0;
    r4 = 0;
    r3 = this_r3;
    r3 = EstSet(this_r3, 0, 0, ret_800B2A7C, ret_800B2A88, 0, 0, this_r3, r11); // [0x800906FC]
    r4 = 6;
    r3 = 40;
    r3 = EspGetEstAddr(40, 6); // [0x800833A4]
    r30 = ret_800B2ABC;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B2AC8;
    stack_0x08 = 0;
    r3 = this_r3;
    r6 = ret_800B2ABC;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = this_r3;
    r3 = EstSet(this_r3, 0, 0, ret_800B2ABC, ret_800B2AC8, 0, 0, this_r3, r11); // [0x800906FC]
    r0 = stack_0x24;
    return; // r3 = ret_800B2AF0
}

// ============================================================================
// High-Level AST Decompilation: cPlayer::Hide(void)
// Unit: player.obj | Address: 0x800B2B08 | Size: 0x40 bytes
// ============================================================================
/* [0x800B2B08] */ void cPlayer::Hide(cPlayer* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r9 = this_r3;
    r11 = -11;
    r0 = *(uint32_t*)(this_r3 + 0xF4);
    r5 = this_r3;
    r3 = 0;
    r4 = 0;
    *(uint32_t*)(this_r3 + 0xF4) = *(uint32_t*)(this_r3 + 0xF4);
    r3 = EspgenDelete(0, 0, this_r3); // [0x8008E8B8]
    r0 = stack_0x0C;
    return; // r3 = ret_800B2B34
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Footwork(cEm *)
// Unit: player.obj | Address: 0x800B2B48 | Size: 0x140 bytes
// ============================================================================
/* [0x800B2B48] */ void pl_R1_Footwork(cEm * arg0_r3) {
    // Stack frame allocated: 56 bytes
    stack_0x30 = f31;
    stack_0x3C = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B2B88;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B2B88:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r31 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B2C44;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 1) goto label_800B2BB0;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B2BBC;
    goto label_800B2C68;
label_800B2BB0:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 2) goto label_800B2C50;
    goto label_800B2C68;
label_800B2BBC:;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    f31 = *(float*)0x8016CB78;
    f0 = *(float*)0x8016CB7C;
    f13 = *(float*)0x8016CB80;
    f12 = *(float*)0x8016CB84;
    r3 = arg0_r3;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r4 = arg0_r3 + (380);
    stack_0x0C = *(float*)0x8016CB7C;
    r6 = 0;
    stack_0x10 = *(float*)0x8016CB80;
    r7 = 5;
    stack_0x1C = *(float*)0x8016CB84;
    r9 = 0;
    stack_0x08 = *(float*)0x8016CB78;
    stack_0x18 = *(float*)0x8016CB78;
    stack_0x20 = *(float*)0x8016CB78;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CB78;
    r0 = 1;
    *(uint8_t*)(arg0_r3 + 0xFA) = 1;
label_800B2C44:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    goto label_800B2C68;
label_800B2C50:;
    r9 = *(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x627);
    if (*(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x627) != 0) goto label_800B2C60;
    *(uint8_t*)(arg0_r3 + 0xFA) = *(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x627);
label_800B2C60:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
label_800B2C68:;
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
    r0 = stack_0x3C;
    f31 = stack_0x30;
    return; // r3 = ret_800B2C6C
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Run(cEm *)
// Unit: player.obj | Address: 0x800B2C88 | Size: 0x1B8 bytes
// ============================================================================
/* [0x800B2C88] */ void pl_R1_Run(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B2CC4;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B2CC4:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r31 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B2CE8;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B2D34;
    goto label_800B2D3C;
label_800B2CE8:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r4 = arg0_r3 + (380);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x1C);
    r6 = 0;
    r7 = 5;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x1C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x1C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = 1;
    f0 = *(float*)0x8016CB88;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CB88;
    *(uint8_t*)(arg0_r3 + 0xFA) = 1;
label_800B2D34:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
label_800B2D3C:;
    r3 = arg0_r3;
    r3 = snd_footse_call(arg0_r3); // [0x800B71C8]
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
    if (ret_800B2D48 != 0) goto label_800B2E2C;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (ret_800B2D48 == 0) goto label_800B2D78;
    r9 = 10;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x65C) = 10;
    goto label_800B2E2C;
label_800B2D78:;
    if (ret_800B2D48 == 0) goto label_800B2D94;
    f0 = *(float*)(arg0_r3 + 0xD0);
    f13 = *(float*)0x8016CB8C;
    *(float*)(arg0_r3 + 0xD0) = *(float*)(arg0_r3 + 0xD0);
label_800B2D94:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (ret_800B2D48 == 0) goto label_800B2DB4;
    f0 = *(float*)(arg0_r3 + 0xD0);
    f13 = *(float*)0x8016CB8C;
    *(float*)(arg0_r3 + 0xD0) = *(float*)(arg0_r3 + 0xD0);
label_800B2DB4:;
    f13 = *(float*)(arg0_r3 + 0xD0);
    f0 = *(float*)0x8016CB90;
    if (ret_800B2D48 != 0) goto label_800B2DF0;
    f12 = *(float*)0x8016CB94;
label_800B2DD8:;
    if (ret_800B2D48 != 0) goto label_800B2DD8;
    *(float*)(arg0_r3 + 0xD0) = *(float*)0x8016CB90;
label_800B2DF0:;
    f13 = *(float*)(arg0_r3 + 0xD0);
    f0 = *(float*)0x8016CB98;
    if (ret_800B2D48 != 0) goto label_800B2E2C;
    f12 = *(float*)0x8016CB94;
label_800B2E14:;
    if (ret_800B2D48 != 0) goto label_800B2E14;
    *(float*)(arg0_r3 + 0xD0) = *(float*)0x8016CB98;
label_800B2E2C:;
    r0 = stack_0x14;
    return; // r3 = ret_800B2D48
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Side(cEm *)
// Unit: player.obj | Address: 0x800B2E40 | Size: 0x678 bytes
// ============================================================================
/* [0x800B2E40] */ void pl_R1_Side(cEm * arg0_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r9 = SDA1::pG;
    r31 = arg0_r3;
    r28 = 0;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B2E80;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B2E80:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r29 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 5) goto label_800B31E8;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 5) goto label_800B2ED0;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 2) goto label_800B3030;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 2) goto label_800B2EBC;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B2F08;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B2F9C;
    goto label_800B34A4;
label_800B2EBC:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 3) goto label_800B30C4;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 4) goto label_800B3158;
    goto label_800B34A4;
label_800B2ED0:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 8) goto label_800B3264;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 8) goto label_800B2EF0;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 6) goto label_800B31A0;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 7) goto label_800B31E8;
    goto label_800B34A4;
label_800B2EF0:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 10) goto label_800B3328;
    if (*(uint8_t*)(arg0_r3 + 0xFA) < 10) goto label_800B32EC;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 11) goto label_800B33F0;
    goto label_800B34A4;
label_800B2F08:;
    r0 = 64;
    *(uint32_t*)0x801C4AA8 = 64;
    r3 = arg0_r3;
    r9 = SDA1::pG;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 5;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r8 = 65;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x28);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x28) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x28) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, 65, 0); // [0x800A1E20]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x14C);
    if (*(uint32_t*)(SDA1::pG + 0x14C) < 0) goto label_800B2F68;
    r0 = *(uint8_t*)(arg0_r3 + 0x4E1);
    if (*(uint8_t*)(arg0_r3 + 0x4E1) > 2) goto label_800B2F68;
    r0 = 3;
    *(uint8_t*)(arg0_r3 + 0x4E1) = 3;
label_800B2F68:;
    r3 = 0;
    f0 = *(float*)0x8016CB9C;
    r4 = 13;
    r5 = arg0_r3 + (192);
    r6 = 0;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CB9C;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r0 = *(uint32_t*)(arg0_r3 + 0xF4) | 0x0040u;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r3 = SndSeCall(0, 13, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = 1;
    *(uint8_t*)(arg0_r3 + 0xFA) = 1;
label_800B2F9C:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B2FA0 == 0) goto label_800B2FD0;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r11 = SDA1::pG;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r9 = *(uint32_t*)(SDA1::pG + 0x148);
    if (ret_800B2FA0 != 0) goto label_800B34A4;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B2FD0:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (ret_800B2FA0 != 0) goto label_800B34A4;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) <= 0x9u) goto label_800B34A4;
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
    if (ret_800B2FF0 == 0) goto label_800B34A4;
    f0 = *(float*)0x8016CBA0;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBA0;
    r0 = *(uint8_t*)(arg0_r3 + 0xF9);
    if (*(uint8_t*)(arg0_r3 + 0xF9) != 2) goto label_800B3028;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)(arg0_r3 + 0xF9) == 2) goto label_800B34A4;
    r0 = 4;
    goto label_800B34A0;
label_800B3028:;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    goto label_800B3444;
label_800B3030:;
    r10 = SDA1::pG;
    r9 = &Weapon;
    r3 = arg0_r3;
    *(uint32_t*)(&Weapon + 0x10) = 0;
    r4 = arg0_r3 + (380);
    r9 = 0;
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 5;
    r8 = 1;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x28);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x28) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x28) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, 1, 0); // [0x800A1E20]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x14C);
    if (*(uint32_t*)(SDA1::pG + 0x14C) < 0) goto label_800B3090;
    r0 = *(uint8_t*)(arg0_r3 + 0x4E1);
    if (*(uint8_t*)(arg0_r3 + 0x4E1) > 2) goto label_800B3090;
    r0 = 3;
    *(uint8_t*)(arg0_r3 + 0x4E1) = 3;
label_800B3090:;
    r3 = 0;
    f0 = *(float*)0x8016CB9C;
    r4 = 13;
    r5 = arg0_r3 + (192);
    r6 = 0;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CB9C;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r0 = *(uint32_t*)(arg0_r3 + 0xF4) | 0x0040u;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r3 = SndSeCall(0, 13, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = 3;
    *(uint8_t*)(arg0_r3 + 0xFA) = 3;
label_800B30C4:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B30C8 == 0) goto label_800B30F8;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r11 = SDA1::pG;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r9 = *(uint32_t*)(SDA1::pG + 0x148);
    if (ret_800B30C8 != 0) goto label_800B34A4;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B30F8:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (ret_800B30C8 != 0) goto label_800B34A4;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) <= 0x9u) goto label_800B34A4;
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
    if (ret_800B3118 == 0) goto label_800B34A4;
    f0 = *(float*)0x8016CBA0;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBA0;
    r0 = *(uint8_t*)(arg0_r3 + 0xF9);
    if (*(uint8_t*)(arg0_r3 + 0xF9) != 2) goto label_800B3150;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)(arg0_r3 + 0xF9) == 2) goto label_800B34A4;
    r0 = 6;
    goto label_800B34A0;
label_800B3150:;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    goto label_800B3444;
label_800B3158:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 1;
    r8 = 65;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x2C);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x2C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x2C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 1, 65, 0); // [0x800A1E20]
    r3 = 0;
    r4 = 13;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 13, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = 5;
    goto label_800B31E4;
label_800B31A0:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 1;
    r8 = 1;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x2C);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x2C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x2C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 1, 1, 0); // [0x800A1E20]
    r3 = 0;
    r4 = 13;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 13, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = 7;
label_800B31E4:;
    *(uint8_t*)(arg0_r3 + 0xFA) = 7;
label_800B31E8:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B31EC == 0) goto label_800B321C;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r11 = SDA1::pG;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r9 = *(uint32_t*)(SDA1::pG + 0x148);
    if (ret_800B31EC != 0) goto label_800B34A4;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B321C:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (ret_800B31EC != 0) goto label_800B34A4;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) <= 0x10u) goto label_800B34A4;
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
    if (ret_800B323C == 0) goto label_800B34A4;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    f0 = *(float*)0x8016CBA0;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBA0;
    goto label_800B34A4;
label_800B3264:;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r10 = SDA1::pG;
    r9 = 64;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4) | 0x0040u;
    r3 = arg0_r3;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r4 = arg0_r3 + (380);
    *(uint32_t*)0x801C4AA8 = 64;
    r6 = 0;
    r9 = 0;
    r7 = 5;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r8 = 65;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x114);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x114) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x114) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, 65, 0); // [0x800A1E20]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x14C);
    if (*(uint32_t*)(SDA1::pG + 0x14C) < 0) goto label_800B32D0;
    r0 = *(uint8_t*)(arg0_r3 + 0x4E1);
    if (*(uint8_t*)(arg0_r3 + 0x4E1) > 2) goto label_800B32D0;
    r0 = 3;
    *(uint8_t*)(arg0_r3 + 0x4E1) = 3;
label_800B32D0:;
    r3 = 0;
    r4 = 14;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 14, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = 9;
    *(uint8_t*)(arg0_r3 + 0xFA) = 9;
label_800B32EC:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B32F0 == 0) goto label_800B3450;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (ret_800B32F0 != 0) goto label_800B34A4;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    f0 = *(float*)0x8016CBA0;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBA0;
    if (ret_800B32F0 != 0) goto label_800B3428;
    goto label_800B3438;
label_800B3328:;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r10 = SDA1::pG;
    r9 = &Weapon;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4) | 0x0040u;
    r3 = arg0_r3;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r4 = arg0_r3 + (380);
    *(uint32_t*)(&Weapon + 0x10) = 0;
    r6 = 0;
    r9 = 0;
    r7 = 5;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r8 = 1;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x114);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x114) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x114) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, 1, 0); // [0x800A1E20]
    r9 = SDA1::pG;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (0 < (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0))) goto label_800B3398;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", (arg0_r3 + 380)); // [0x8013E678]
label_800B3398:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r10 = SDA1::pG;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xDD4);
    r0 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xDD4) | 0x0002u;
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xDD4) = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xDD4);
    r9 = *(uint32_t*)(SDA1::pG + 0x14C);
    if (*(uint32_t*)(SDA1::pG + 0x14C) < 0) goto label_800B33D4;
    r0 = *(uint8_t*)(arg0_r3 + 0x4E1);
    if (*(uint8_t*)(arg0_r3 + 0x4E1) > 2) goto label_800B33D4;
    r0 = 3;
    *(uint8_t*)(arg0_r3 + 0x4E1) = 3;
label_800B33D4:;
    r3 = 0;
    r4 = 14;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 14, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = 11;
    *(uint8_t*)(arg0_r3 + 0xFA) = 11;
label_800B33F0:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B33F4 == 0) goto label_800B3450;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (ret_800B33F4 != 0) goto label_800B34A4;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    f0 = *(float*)0x8016CBA0;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBA0;
    if (ret_800B33F4 == 0) goto label_800B3438;
label_800B3428:;
    r0 = 0x01050100u;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01050100u;
    goto label_800B34A4;
label_800B3438:;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B3444:;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    goto label_800B34A4;
label_800B3450:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (ret_800B33F4 != 0) goto label_800B34A4;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) <= 0x10u) goto label_800B34A4;
    r11 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) == 0x10u) goto label_800B34A4;
    r0 = *(uint8_t*)(arg0_r3 + 0xF9);
    if (*(uint8_t*)(arg0_r3 + 0xF9) != 2) goto label_800B34A4;
    f0 = *(float*)0x8016CBA0;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBA0;
    r0 = 8;
    if (*(uint8_t*)(arg0_r3 + 0xF9) != 2) goto label_800B34A0;
    r0 = 10;
label_800B34A0:;
    *(uint8_t*)(arg0_r3 + 0xFA) = 10;
label_800B34A4:;
    r0 = stack_0x1C;
    return; // r3 = ret_800B33F4
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Jump(cEm *)
// Unit: player.obj | Address: 0x800B34B8 | Size: 0xA94 bytes
// ============================================================================
/* [0x800B34B8] */ void pl_R1_Jump(cEm * arg0_r3) {
    // Stack frame allocated: 88 bytes
    stack_0x50 = f31;
    stack_0x5C = r0;
    r9 = SDA1::pG;
    r31 = arg0_r3;
    r28 = 0;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B34FC;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B34FC:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint8_t*)(arg0_r3 + 0xFA);
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r29 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 7) goto label_800B398C;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 7) goto label_800B354C;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 3) goto label_800B3894;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 3) goto label_800B353C;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B36A8;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 1) goto label_800B36F4;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B3580;
    goto label_800B3F34;
label_800B353C:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 5) goto label_800B3B88;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 5) goto label_800B3944;
    goto label_800B38F4;
label_800B354C:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 11) goto label_800B3BBC;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 11) goto label_800B3568;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 9) goto label_800B3B78;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 9) goto label_800B3B88;
    goto label_800B3AB0;
label_800B3568:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 13) goto label_800B3E44;
    if (*(uint8_t*)(arg0_r3 + 0xFA) < 13) goto label_800B3C0C;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 14) goto label_800B3ECC;
    goto label_800B3F34;
label_800B3580:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 14) goto label_800B35D4;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x20);
    r7 = 2;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x20) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x20) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 2, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0x56C) = 0;
    r0 = 11;
    *(uint8_t*)(arg0_r3 + 0xFA) = 11;
    goto label_800B366C;
label_800B35D4:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 14) goto label_800B3624;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x3C);
    r7 = 2;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x3C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x3C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 2, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0x56C) = 0;
    r0 = 6;
    *(uint8_t*)(arg0_r3 + 0xFA) = 6;
    goto label_800B366C;
label_800B3624:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r4 = arg0_r3 + (380);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x80);
    r6 = 0;
    r7 = 5;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x80) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x80) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = 25;
    r9 = 1;
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0x56C) = 25;
    *(uint8_t*)(arg0_r3 + 0xFA) = 1;
label_800B366C:;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r10 = 0;
    r9 = *(uint16_t*)(arg0_r3 + 0x45A);
    r0 = *(uint32_t*)(arg0_r3 + 0xF4) | 0x0040u;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r9 = *(uint16_t*)(arg0_r3 + 0x45A) | 0x0004u;
    SDA1::trg_flag.1084 = 0;
    r3 = arg0_r3;
    f1 = *(float*)0x8016CBA4;
    f2 = *(float*)0x8016CBA8;
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
    r3 = MotionMove(arg0_r3, *(float*)0x8016CBA4, *(float*)0x8016CBA8); // [0x800A2434]
    goto label_800B3F34;
label_800B36A8:;
    r4 = 10;
    f0 = *(float*)0x8016CBAC;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = 0;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBAC;
    r3 = SndSeCall(0, 10, (arg0_r3 + 192), 0); // [0x800CB7DC]
    f1 = *(float*)0x8016CBA4;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CBA8;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CBA4, *(float*)0x8016CBA8); // [0x800A2434]
    r0 = 2;
    f0 = *(float*)0x8016CBB0;
    *(uint8_t*)(arg0_r3 + 0xFA) = 2;
    *(float*)(arg0_r3 + 0x104) = *(float*)0x8016CBB0;
label_800B36F4:;
    f31 = *(float*)0x8016CBB0;
    *(float*)(arg0_r3 + 0x108) = *(float*)0x8016CBB0;
    *(float*)(arg0_r3 + 0x100) = *(float*)0x8016CBB0;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 14) goto label_800B371C;
    f0 = *(float*)0x8016CBB4;
    *(float*)(arg0_r3 + 0x100) = *(float*)0x8016CBB4;
label_800B371C:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 14) goto label_800B3734;
    f0 = *(float*)0x8016CBB8;
    *(float*)(arg0_r3 + 0x100) = *(float*)0x8016CBB8;
label_800B3734:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 14) goto label_800B374C;
    f0 = *(float*)0x8016CBB8;
    *(float*)(arg0_r3 + 0x108) = *(float*)0x8016CBB8;
label_800B374C:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 14) goto label_800B3764;
    f0 = *(float*)0x8016CBB4;
    *(float*)(arg0_r3 + 0x108) = *(float*)0x8016CBB4;
label_800B3764:;
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    f13 = *(float*)(arg0_r3 + 0xC4);
    f12 = *(float*)0x8016CBBC;
    *(float*)(arg0_r3 + 0xC4) = *(float*)(arg0_r3 + 0xC4);
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    if (*(uint8_t*)(arg0_r3 + 0xFA) >= 14) goto label_800B3848;
    r8 = *(uint32_t*)(arg0_r3 + 0xC0);
    r10 = arg0_r3 + (192);
    f0 = *(float*)(arg0_r3 + 0x110);
    r7 = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    r9 = &stack_0x20;
    r0 = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    r3 = arg0_r3 + (284);
    f13 = *(float*)0x8016CBC0;
    r4 = &stack_0x20;
    stack_0x20 = *(uint32_t*)(arg0_r3 + 0xC0);
    r30 = &stack_0x20;
    *(uint32_t*)(&stack_0x20 + 0x4) = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    *(uint32_t*)(&stack_0x20 + 0x8) = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    stack_0x24 = *(float*)(arg0_r3 + 0x110);
    r3 = GetFloor((arg0_r3 + 284), &stack_0x20); // [0x800078EC]
    f0 = *(float*)(arg0_r3 + 0xC4);
    if (*(uint8_t*)(arg0_r3 + 0xFA) <= 14) goto label_800B37F4;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBB0;
    r0 = 3;
    *(float*)(arg0_r3 + 0xC4) = *(float*)0x8016CBA4;
    *(uint8_t*)(arg0_r3 + 0xFA) = 3;
    goto label_800B3E00;
label_800B37F4:;
    r0 = *(uint8_t*)(arg0_r3 + 0x3BA);
    if (*(uint8_t*)(arg0_r3 + 0x3BA) == 0) goto label_800B3E00;
    r11 = SDA1::pG;
    r10 = *(uint32_t*)(arg0_r3 + 0x17C);
    r9 = *(uint32_t*)(SDA1::pG + 0x118);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x40);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x40) + *(uint32_t*)(SDA1::pG + 0x118));
    if (*(uint32_t*)(arg0_r3 + 0x17C) == (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x40) + *(uint32_t*)(SDA1::pG + 0x118))) goto label_800B3E00;
    r3 = arg0_r3;
    r8 = *(uint32_t*)0x801C4AA8;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r9 = 0;
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x40) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 0, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B3E00;
label_800B3848:;
    r0 = *(uint32_t*)(arg0_r3 + 0xC0);
    r5 = arg0_r3 + (192);
    r11 = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    r9 = &stack_0x10;
    r10 = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    stack_0x10 = *(uint32_t*)(arg0_r3 + 0xC0);
    r3 = &stack_0x10;
    *(uint32_t*)(&stack_0x10 + 0x4) = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    r4 = &stack_0x30;
    *(uint32_t*)(&stack_0x10 + 0x8) = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    r6 = &stack_0x10;
    f13 = *(float*)0x8016CBC4;
    r7 = 0;
    f0 = stack_0x14;
    r30 = &stack_0x20;
    stack_0x14 = stack_0x14;
    goto label_800B3DE8;
label_800B3894:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r4 = arg0_r3 + (380);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x84);
    r6 = 0;
    r7 = 5;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x84) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x84) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r3 = 2;
    r3 = Snd_footse_call(2); // [0x800CD030]
    r9 = *(uint32_t*)(arg0_r3 + 0xF4);
    r11 = 4;
    r0 = *(uint16_t*)(arg0_r3 + 0x45A);
    *(uint8_t*)(arg0_r3 + 0xFA) = 4;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
label_800B38F4:;
    f1 = *(float*)0x8016CBA4;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CBA8;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CBA4, *(float*)0x8016CBA8); // [0x800A2434]
    if (ret_800B3908 == 0) goto label_800B391C;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B391C:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) <= 0x1u) goto label_800B3F34;
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) == 0x1u) goto label_800B3F34;
    goto label_800B3F30;
label_800B3944:;
    r3 = 0;
    r4 = 10;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 10, (arg0_r3 + 192), 0); // [0x800CB7DC]
    f13 = *(float*)0x8016CBB0;
    f0 = *(float*)0x8016CBC8;
    f12 = *(float*)0x8016CBCC;
    *(float*)(arg0_r3 + 0x104) = *(float*)0x8016CBB0;
    *(float*)(arg0_r3 + 0x108) = *(float*)0x8016CBC8;
    *(float*)(arg0_r3 + 0x100) = *(float*)0x8016CBB0;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBCC;
    r9 = *(uint8_t*)(arg0_r3 + 0xFA);
    r9 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
label_800B398C:;
    f31 = *(float*)0x8016CBB0;
    *(float*)(arg0_r3 + 0x100) = *(float*)0x8016CBB0;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) == 0x1u) goto label_800B39B0;
    f0 = *(float*)0x8016CBD0;
    *(float*)(arg0_r3 + 0x100) = *(float*)0x8016CBD0;
label_800B39B0:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) == 0x1u) goto label_800B39C8;
    f0 = *(float*)0x8016CBD4;
    *(float*)(arg0_r3 + 0x100) = *(float*)0x8016CBD4;
label_800B39C8:;
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    f13 = *(float*)(arg0_r3 + 0xC4);
    r26 = 0;
    f12 = *(float*)0x8016CBD8;
    r9 = SDA1::pG;
    *(float*)(arg0_r3 + 0xC4) = *(float*)(arg0_r3 + 0xC4);
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 0x1u) goto label_800B3A18;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", 10); // [0x8013E678]
label_800B3A18:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    f13 = *(float*)0x8016CBC4;
    r28 = &stack_0x10;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r10 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xC0);
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (192);
    r11 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 192) + 0x8);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 192) + 0x4);
    stack_0x10 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xC0);
    *(uint32_t*)(&stack_0x10 + 0x4) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 192) + 0x4);
    *(uint32_t*)(&stack_0x10 + 0x8) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 192) + 0x8);
    f0 = stack_0x14;
    stack_0x14 = stack_0x14;
    f13 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    if (*(uint16_t*)(arg0_r3 + 0x42C) >= 0x1u) goto label_800B3D98;
    r0 = *(uint32_t*)(arg0_r3 + 0xC0);
    r11 = arg0_r3 + (192);
    r8 = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    r9 = &stack_0x20;
    r10 = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    r3 = arg0_r3 + (284);
    stack_0x20 = *(uint32_t*)(arg0_r3 + 0xC0);
    r4 = &stack_0x20;
    r30 = &stack_0x20;
    f0 = *(float*)(arg0_r3 + 0x110);
    *(uint32_t*)(&stack_0x20 + 0x4) = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    *(uint32_t*)(&stack_0x20 + 0x8) = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    stack_0x24 = *(float*)(arg0_r3 + 0x110);
    r3 = GetFloor((arg0_r3 + 284), &stack_0x20); // [0x800078EC]
    f0 = *(float*)(arg0_r3 + 0xC4);
    if (*(uint16_t*)(arg0_r3 + 0x42C) <= 0x1u) goto label_800B3E00;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBB0;
    *(float*)(arg0_r3 + 0xC4) = *(float*)0x8016CBA4;
    goto label_800B3BAC;
label_800B3AB0:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x6A78);
    if (*(uint32_t*)(SDA1::pG + 0x6A78) != 0x00020000u) goto label_800B3B0C;
    r4 = 8;
    r3 = 40;
    r3 = EspGetEstAddr(40, 8); // [0x800833A4]
    r30 = ret_800B3AD0;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B3ADC;
    r0 = 0;
    stack_0x08 = 0;
    r6 = ret_800B3AD0;
    r3 = arg0_r3;
    r4 = arg0_r3 + (192);
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, (arg0_r3 + 192), 0, ret_800B3AD0, ret_800B3ADC, 0, 0, arg0_r3, 0x00020000u); // [0x800906FC]
label_800B3B0C:;
    r0 = 0;
    r3 = 2;
    SDA1::trg_flag.1084 = 0;
    r3 = Snd_footse_call(2); // [0x800CD030]
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r4 = arg0_r3 + (380);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x44);
    r6 = 0;
    r7 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x44) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x44) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 0, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r9 = *(uint16_t*)(arg0_r3 + 0x45A);
    r11 = *(uint8_t*)(arg0_r3 + 0xFA);
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r11 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
label_800B3B78:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x0);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x0) != 0) goto label_800B3ED8;
    goto label_800B3EE4;
label_800B3B88:;
    f1 = *(float*)0x8016CBA4;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CBA8;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CBA4, *(float*)0x8016CBA8); // [0x800A2434]
    r0 = *(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x668);
    if (*(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x668) == 0) goto label_800B3F34;
label_800B3BAC:;
    r9 = *(uint8_t*)(arg0_r3 + 0xFA);
    r9 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
    goto label_800B3F34;
label_800B3BBC:;
    r0 = 1;
    r3 = 0;
    SDA1::trg_flag.1084 = 1;
    r4 = 10;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 10, (arg0_r3 + 192), 0); // [0x800CB7DC]
    f13 = *(float*)0x8016CBB0;
    f0 = *(float*)0x8016CBDC;
    f12 = *(float*)0x8016CBCC;
    *(float*)(arg0_r3 + 0x104) = *(float*)0x8016CBB0;
    *(float*)(arg0_r3 + 0x108) = *(float*)0x8016CBDC;
    *(float*)(arg0_r3 + 0x100) = *(float*)0x8016CBB0;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBCC;
    r9 = *(uint8_t*)(arg0_r3 + 0xFA);
    r9 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
label_800B3C0C:;
    f31 = *(float*)0x8016CBB0;
    *(float*)(arg0_r3 + 0x100) = *(float*)0x8016CBB0;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x668) == 0) goto label_800B3C30;
    f0 = *(float*)0x8016CBD0;
    *(float*)(arg0_r3 + 0x100) = *(float*)0x8016CBD0;
label_800B3C30:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x668) == 0) goto label_800B3C48;
    f0 = *(float*)0x8016CBD4;
    *(float*)(arg0_r3 + 0x100) = *(float*)0x8016CBD4;
label_800B3C48:;
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    f13 = *(float*)(arg0_r3 + 0xC4);
    r26 = 0;
    f12 = *(float*)0x8016CBD8;
    r9 = SDA1::pG;
    *(float*)(arg0_r3 + 0xC4) = *(float*)(arg0_r3 + 0xC4);
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (*(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x668) != 0) goto label_800B3C98;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", 10); // [0x8013E678]
label_800B3C98:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    f13 = *(float*)0x8016CBC4;
    r28 = &stack_0x10;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r10 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xC0);
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (192);
    r11 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 192) + 0x8);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 192) + 0x4);
    stack_0x10 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xC0);
    *(uint32_t*)(&stack_0x10 + 0x4) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 192) + 0x4);
    *(uint32_t*)(&stack_0x10 + 0x8) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 192) + 0x8);
    f0 = stack_0x14;
    stack_0x14 = stack_0x14;
    f13 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    if (*(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x668) >= 0) goto label_800B3D98;
    r8 = *(uint32_t*)(arg0_r3 + 0xC0);
    r10 = arg0_r3 + (192);
    f0 = *(float*)(arg0_r3 + 0x110);
    r7 = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    r9 = &stack_0x20;
    r0 = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    r3 = arg0_r3 + (284);
    f13 = *(float*)0x8016CBE0;
    r4 = &stack_0x20;
    stack_0x20 = *(uint32_t*)(arg0_r3 + 0xC0);
    r30 = &stack_0x20;
    *(uint32_t*)(&stack_0x20 + 0x4) = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    *(uint32_t*)(&stack_0x20 + 0x8) = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    stack_0x24 = *(float*)(arg0_r3 + 0x110);
    r3 = GetFloor((arg0_r3 + 284), &stack_0x20); // [0x800078EC]
    f0 = *(float*)(arg0_r3 + 0xC4);
    if (*(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x668) <= 0) goto label_800B3E00;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBB0;
    *(float*)(arg0_r3 + 0xC4) = *(float*)0x8016CBA4;
    r3 = arg0_r3;
    r11 = *(uint8_t*)(arg0_r3 + 0xFA);
    r9 = 2;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    r7 = 0;
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
    r10 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x24);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x24) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x24) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 0, *(uint32_t*)0x801C4AA8, 2); // [0x800A1E20]
    f1 = *(float*)0x8016CBA4;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CBA8;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CBA4, *(float*)0x8016CBA8); // [0x800A2434]
    goto label_800B3F34;
label_800B3D98:;
    r9 = SDA1::pG;
    r27 = &stack_0x30;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (0 < (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0))) goto label_800B3DC8;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", (arg0_r3 + 380)); // [0x8013E678]
label_800B3DC8:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r3 = &stack_0x10;
    r4 = &stack_0x30;
    r6 = &stack_0x10;
    r5 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r7 = 0;
    r30 = &stack_0x20;
    r5 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (192);
label_800B3DE8:;
    r3 = ScrHitCheck2(&stack_0x10, &stack_0x30, (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 192), &stack_0x10, 0); // [0x80007AE0]
    if (ret_800B3DE8 == 0) goto label_800B3E00;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBB0;
    f0 = *(float*)(arg0_r3 + 0x110);
    *(float*)(arg0_r3 + 0xC4) = *(float*)(arg0_r3 + 0x110);
label_800B3E00:;
    f1 = *(float*)0x8016CBA4;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CBA8;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CBA4, *(float*)0x8016CBA8); // [0x800A2434]
    f13 = *(float*)(arg0_r3 + 0x100);
    r9 = arg0_r3 + (256);
    r3 = arg0_r3;
    r4 = &stack_0x20;
    stack_0x20 = *(float*)(arg0_r3 + 0x100);
    f0 = *(float*)((arg0_r3 + 256) + 0x4);
    stack_0x24 = *(float*)((arg0_r3 + 256) + 0x4);
    f13 = *(float*)((arg0_r3 + 256) + 0x8);
    stack_0x28 = *(float*)((arg0_r3 + 256) + 0x8);
    r3 = AddSpeed(arg0_r3, &stack_0x20); // [0x800CEEF4]
    goto label_800B3F34;
label_800B3E44:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x6A78);
    if (*(uint32_t*)(SDA1::pG + 0x6A78) != 0x00020000u) goto label_800B3E9C;
    r4 = 8;
    r3 = 40;
    r3 = EspGetEstAddr(40, 8); // [0x800833A4]
    r30 = ret_800B3E64;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B3E70;
    r6 = ret_800B3E64;
    stack_0x08 = &stack_0x10;
    r3 = arg0_r3;
    r4 = arg0_r3 + (192);
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, (arg0_r3 + 192), 0, ret_800B3E64, ret_800B3E70, 0, 0, arg0_r3, 0x00020000u); // [0x800906FC]
label_800B3E9C:;
    SDA1::trg_flag.1084 = &stack_0x10;
    r3 = 2;
    r3 = Snd_footse_call(2); // [0x800CD030]
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r9 = *(uint16_t*)(arg0_r3 + 0x45A);
    r11 = *(uint8_t*)(arg0_r3 + 0xFA);
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r11 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
label_800B3ECC:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x0);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x0) == 0) goto label_800B3EE4;
label_800B3ED8:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x0) + (-1);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x0) = (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x0) + -1);
    goto label_800B3F00;
label_800B3EE4:;
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x0) == 0) goto label_800B3F00;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x010B0000u;
label_800B3F00:;
    f1 = *(float*)0x8016CBA4;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CBA8;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CBA4, *(float*)0x8016CBA8); // [0x800A2434]
    r0 = 20;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x65C) = 20;
    r9 = *(uint8_t*)(arg0_r3 + 0x3BA);
    if (*(uint8_t*)(arg0_r3 + 0x3BA) == 0) goto label_800B3F34;
label_800B3F30:;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B3F34:;
    r0 = stack_0x5C;
    f31 = stack_0x50;
    return; // r3 = ret_800B3F14
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Weapon(cEm *)
// Unit: player.obj | Address: 0x800B3F4C | Size: 0xA8 bytes
// ============================================================================
/* [0x800B3F4C] */ void pl_R1_Weapon(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B3F88;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B3F88:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    r11 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x660);
    if (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x660) == 0) goto label_800B3FA8;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x660) + (-1);
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x660) = (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x660) + -1);
label_800B3FA8:;
    r11 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x662);
    if (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x662) == 0) goto label_800B3FBC;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x662) + (-1);
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x662) = (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x662) + -1);
label_800B3FBC:;
    r11 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x664);
    if (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x664) == 0) goto label_800B3FD0;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x664) + (-1);
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x664) = (*(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x664) + -1);
label_800B3FD0:;
    r4 = arg0_r3;
    r3 = &Weapon;
    r3 = cWeapon::Move(&Weapon, arg0_r3); // [0x800AFE20]
    r0 = stack_0x14;
    return; // r3 = ret_800B3FDC
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Sit(cEm *)
// Unit: player.obj | Address: 0x800B3FF4 | Size: 0x2DC bytes
// ============================================================================
/* [0x800B3FF4] */ void pl_R1_Sit(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r31 = arg0_r3;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B4030;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B4030:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 2) goto label_800B4148;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 2) goto label_800B4060;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B4074;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B40E0;
    goto label_800B42BC;
label_800B4060:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 3) goto label_800B4238;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 4) goto label_800B4278;
    goto label_800B42BC;
label_800B4074:;
    r8 = SDA1::pG;
    f0 = *(float*)0x8016CBE4;
    r9 = 0;
    r3 = arg0_r3;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBE4;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 1;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r8 = *(uint32_t*)0x801C4AA8;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x13C);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x13C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x13C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 1, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r3 = 0;
    r4 = 15;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 15, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r9 = 1;
    *(uint8_t*)(arg0_r3 + 0xFA) = 1;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4) | 0x0040u;
    goto label_800B42B8;
label_800B40E0:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B40E4 == 0) goto label_800B4130;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = 2;
    *(uint8_t*)(arg0_r3 + 0xFA) = 2;
label_800B4130:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (ret_800B40E4 != 0) goto label_800B42BC;
    r0 = 3;
    *(uint8_t*)(arg0_r3 + 0xFA) = 3;
    goto label_800B42BC;
label_800B4148:;
    f1 = *(float*)0x8016CBE8;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CBEC;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CBE8, *(float*)0x8016CBEC); // [0x800A2434]
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (ret_800B40E4 != 0) goto label_800B41C4;
    r0 = 4;
    r5 = arg0_r3 + (192);
    r4 = 15;
    r6 = 0;
    *(uint8_t*)(arg0_r3 + 0xFA) = 4;
    r3 = 0;
    r3 = SndSeCall(0, 15, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x140);
    r7 = 1;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x140) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x140) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 1, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B42BC;
label_800B41C4:;
    if (ret_800B40E4 == 0) goto label_800B41F4;
    if (ret_800B40E4 == 0) goto label_800B41E4;
    r0 = 0x01020800u;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01020800u;
    goto label_800B42BC;
label_800B41E4:;
    r0 = 0x01020A00u;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01020A00u;
    goto label_800B42BC;
label_800B41F4:;
    if (ret_800B40E4 == 0) goto label_800B4208;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x010D0000u;
    goto label_800B42BC;
label_800B4208:;
    if (ret_800B40E4 == 0) goto label_800B4220;
    r0 = 0x010D0200u;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x010D0200u;
    goto label_800B42BC;
label_800B4220:;
    if (ret_800B40E4 == 0) goto label_800B42BC;
    r0 = 0x010B0300u;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x010B0300u;
    goto label_800B42BC;
label_800B4238:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x140);
    r7 = 1;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x140) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x140) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 1, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = 4;
    *(uint8_t*)(arg0_r3 + 0xFA) = 4;
label_800B4278:;
    f1 = *(float*)0x8016CBE8;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CBEC;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CBE8, *(float*)0x8016CBEC); // [0x800A2434]
    if (ret_800B428C == 0) goto label_800B42A0;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B42A0:;
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
    if (ret_800B42A4 == 0) goto label_800B42BC;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
label_800B42B8:;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
label_800B42BC:;
    r0 = stack_0x14;
    return; // r3 = ret_800B42A4
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Invisible(cEm *)
// Unit: player.obj | Address: 0x800B42D0 | Size: 0xF8 bytes
// ============================================================================
/* [0x800B42D0] */ void pl_R1_Invisible(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B430C;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B430C:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r10 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0)) == 2) goto label_800B437C;
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0)) > 2) goto label_800B4340;
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0)) == 0) goto label_800B4354;
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0)) == 1) goto label_800B435C;
    goto label_800B43B4;
label_800B4340:;
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0)) == 3) goto label_800B4394;
    if ((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0)) == 4) goto label_800B439C;
    goto label_800B43B4;
label_800B4354:;
    r0 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
label_800B435C:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B4360 == 0) goto label_800B43B4;
    r9 = *(uint8_t*)(arg0_r3 + 0xFA);
    r9 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
    goto label_800B43B4;
label_800B437C:;
    r0 = *(uint32_t*)((*(uint8_t*)(arg0_r3 + 0xFA) + 1) + 0x8C);
    if (ret_800B4360 != 0) goto label_800B43B4;
    r0 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
    goto label_800B43B4;
label_800B4394:;
    r0 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
label_800B439C:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B43A0 == 0) goto label_800B43B4;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B43B4:;
    r0 = stack_0x14;
    return; // r3 = ret_800B43A0
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Fall(cEm *)
// Unit: player.obj | Address: 0x800B43C8 | Size: 0x1F0 bytes
// ============================================================================
/* [0x800B43C8] */ void pl_R1_Fall(cEm * arg0_r3) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r9 = SDA1::pG;
    r31 = arg0_r3;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B4404;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B4404:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B4494;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 1) goto label_800B442C;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B4438;
    goto label_800B45A4;
label_800B442C:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 2) goto label_800B4578;
    goto label_800B45A4;
label_800B4438:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r4 = arg0_r3 + (380);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x40);
    r6 = 0;
    r7 = 5;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x40) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x40) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = *(uint16_t*)(arg0_r3 + 0x45A);
    f0 = *(float*)0x8016CBF0;
    r0 = *(uint16_t*)(arg0_r3 + 0x45A) | 0x0004u;
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBF0;
    r9 = *(uint8_t*)(arg0_r3 + 0xFA);
    r9 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
label_800B4494:;
    f13 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    f0 = *(float*)(arg0_r3 + 0xC4);
    r8 = arg0_r3 + (192);
    f12 = *(float*)0x8016CBF4;
    f11 = *(float*)0x8016CBF8;
    *(float*)(arg0_r3 + 0xC4) = *(float*)(arg0_r3 + 0xC4);
    r9 = &stack_0x08;
    r4 = &stack_0x08;
    r3 = arg0_r3 + (284);
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    r0 = *(uint32_t*)(arg0_r3 + 0xC0);
    f0 = *(float*)(arg0_r3 + 0x110);
    r10 = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    r11 = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    stack_0x08 = *(uint32_t*)(arg0_r3 + 0xC0);
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    stack_0x0C = *(float*)(arg0_r3 + 0x110);
    r3 = GetFloor((arg0_r3 + 284), &stack_0x08); // [0x800078EC]
    f0 = *(float*)(arg0_r3 + 0xC4);
    if (*(uint8_t*)(arg0_r3 + 0xFA) <= 2) goto label_800B456C;
    r8 = SDA1::pG;
    f0 = *(float*)0x8016CBF0;
    r9 = 0;
    r3 = arg0_r3;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBF0;
    r4 = arg0_r3 + (380);
    *(float*)(arg0_r3 + 0xC4) = f1;
    r6 = 0;
    r0 = *(uint16_t*)(arg0_r3 + 0x45A);
    r7 = 2;
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r8 = *(uint32_t*)0x801C4AA8;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x6C);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0001u;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x6C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x6C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 2, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r3 = 2;
    r3 = Snd_footse_call(2); // [0x800CD030]
    r9 = *(uint8_t*)(arg0_r3 + 0xFA);
    r9 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
label_800B456C:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    goto label_800B45A4;
label_800B4578:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B457C == 0) goto label_800B4590;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B4590:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) <= 0x3u) goto label_800B45A4;
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
label_800B45A4:;
    r0 = stack_0x24;
    return; // r3 = ret_800B45A0
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_180turn(cEm *)
// Unit: player.obj | Address: 0x800B45B8 | Size: 0x1C4 bytes
// ============================================================================
/* [0x800B45B8] */ void pl_R1_180turn(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B45F4;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B45F4:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r31 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B4618;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B4750;
    goto label_800B4768;
label_800B4618:;
    r0 = *(uint32_t*)0x8019D690;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B468C;
    r8 = *(uint32_t*)0x801C4AA8;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4664;
    r9 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x64);
    r9 = 0;
    goto label_800B46F4;
label_800B4664:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 3;
    r8 = 5;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x68);
    goto label_800B46F4;
label_800B468C:;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4700;
    r8 = *(uint32_t*)0x801C4AA8;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B46D0;
    r9 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x68);
    r9 = 0;
    goto label_800B46F4;
label_800B46D0:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 3;
    r8 = 5;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x64);
label_800B46F4:;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x64) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x64) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, 5, 0); // [0x800A1E20]
    goto label_800B4738;
label_800B4700:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x30);
    r7 = 3;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x30) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x30) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
label_800B4738:;
    r0 = 1;
    f0 = *(float*)0x8016CBFC;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CBFC;
    *(uint8_t*)(arg0_r3 + 0xFA) = 1;
    goto label_800B4768;
label_800B4750:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B4754 == 0) goto label_800B4768;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B4768:;
    r0 = stack_0x14;
    return; // r3 = ret_800B4754
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Turn(cEm *)
// Unit: player.obj | Address: 0x800B477C | Size: 0x73C bytes
// ============================================================================
/* [0x800B477C] */ void pl_R1_Turn(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r31 = arg0_r3;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B47B8;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B47B8:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = 1;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA28) = 1;
    r0 = *(uint8_t*)(arg0_r3 + 0xFA);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 2) goto label_800B49F4;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 2) goto label_800B47F0;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B4808;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B4964;
    goto label_800B4E00;
label_800B47F0:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 4) goto label_800B4C00;
    if (*(uint8_t*)(arg0_r3 + 0xFA) < 4) goto label_800B4A84;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 5) goto label_800B4D00;
    goto label_800B4E00;
label_800B4808:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 5) goto label_800B4890;
    r8 = *(uint32_t*)0x801C4AA8;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4858;
    r9 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 5;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50);
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B4884;
label_800B4858:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 5;
    r8 = 5;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, 5, 0); // [0x800A1E20]
label_800B4884:;
    r0 = 1;
    *(uint8_t*)(arg0_r3 + 0xFA) = 1;
    goto label_800B4958;
label_800B4890:;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4914;
    r8 = *(uint32_t*)0x801C4AA8;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B48DC;
    r9 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 5;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C);
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B4908;
label_800B48DC:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 5;
    r8 = 5;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, 5, 0); // [0x800A1E20]
label_800B4908:;
    r0 = 2;
    *(uint8_t*)(arg0_r3 + 0xFA) = 2;
    goto label_800B4958;
label_800B4914:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = 0x01000100u;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000100u;
label_800B4958:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    goto label_800B4E00;
label_800B4964:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B4968 == 0) goto label_800B49E4;
    r8 = *(uint32_t*)0x801C4AA8;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B49B8;
    r9 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 5;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50);
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B49E4;
label_800B49B8:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 5;
    r8 = 5;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, 5, 0); // [0x800A1E20]
label_800B49E4:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint32_t*)0x801C4AA8 != 0) goto label_800B4E00;
    goto label_800B4E9C;
label_800B49F4:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B49F8 == 0) goto label_800B4A74;
    r8 = *(uint32_t*)0x801C4AA8;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4A48;
    r9 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 5;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C);
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B4A74;
label_800B4A48:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 5;
    r8 = 5;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x50) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, 5, 0); // [0x800A1E20]
label_800B4A74:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint32_t*)0x801C4AA8 != 0) goto label_800B4E00;
    goto label_800B4E9C;
label_800B4A84:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4B0C;
    r8 = *(uint32_t*)0x801C4AA8;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4AD4;
    r9 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 2;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120);
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 2, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B4B00;
label_800B4AD4:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 2;
    r8 = 5;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 2, 5, 0); // [0x800A1E20]
label_800B4B00:;
    r0 = 4;
    *(uint8_t*)(arg0_r3 + 0xFA) = 4;
    goto label_800B4BE4;
label_800B4B0C:;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4B90;
    r8 = *(uint32_t*)0x801C4AA8;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4B58;
    r9 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 2;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C);
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 2, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B4B84;
label_800B4B58:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 2;
    r8 = 5;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 2, 5, 0); // [0x800A1E20]
label_800B4B84:;
    r0 = 5;
    *(uint8_t*)(arg0_r3 + 0xFA) = 5;
    goto label_800B4BE4;
label_800B4B90:;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4BA4;
    r0 = 0x01050200u;
    goto label_800B4BE0;
label_800B4BA4:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x18) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
label_800B4BE0:;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B4BE4:;
    f1 = *(float*)0x8016CC00;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CC04;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CC00, *(float*)0x8016CC04); // [0x800A2434]
    goto label_800B4E00;
label_800B4C00:;
    f1 = *(float*)0x8016CC00;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CC04;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CC00, *(float*)0x8016CC04); // [0x800A2434]
    if (ret_800B4C14 == 0) goto label_800B4CA8;
    r8 = *(uint32_t*)0x801C4AA8;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4C64;
    r9 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 4;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120);
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 4, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B4C90;
label_800B4C64:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 4;
    r8 = 5;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 4, 5, 0); // [0x800A1E20]
label_800B4C90:;
    f1 = *(float*)0x8016CC00;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CC04;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CC00, *(float*)0x8016CC04); // [0x800A2434]
label_800B4CA8:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint32_t*)0x801C4AA8 != 0) goto label_800B4E00;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4E9C;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = 0x01050200u;
    goto label_800B4EA0;
label_800B4D00:;
    f1 = *(float*)0x8016CC00;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CC04;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CC00, *(float*)0x8016CC04); // [0x800A2434]
    if (ret_800B4D14 == 0) goto label_800B4DA8;
    r8 = *(uint32_t*)0x801C4AA8;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4D64;
    r9 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 4;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C);
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x11C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 4, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    goto label_800B4D90;
label_800B4D64:;
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 4;
    r8 = 5;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x120) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 4, 5, 0); // [0x800A1E20]
label_800B4D90:;
    f1 = *(float*)0x8016CC00;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CC04;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CC00, *(float*)0x8016CC04); // [0x800A2434]
label_800B4DA8:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint32_t*)0x801C4AA8 != 0) goto label_800B4E00;
    if (*(uint32_t*)0x801C4AA8 == 0) goto label_800B4E9C;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = 0x01050200u;
    goto label_800B4EA0;
label_800B4E00:;
    f13 = *(float*)(arg0_r3 + 0xD0);
    f0 = *(float*)0x8016CC08;
    if (*(uint32_t*)0x801C4AA8 != 0) goto label_800B4E3C;
    f12 = *(float*)0x8016CC0C;
label_800B4E24:;
    if (*(uint32_t*)0x801C4AA8 != 0) goto label_800B4E24;
    *(float*)(arg0_r3 + 0xD0) = *(float*)0x8016CC08;
label_800B4E3C:;
    f13 = *(float*)(arg0_r3 + 0xD0);
    f0 = *(float*)0x8016CC10;
    if (*(uint32_t*)0x801C4AA8 != 0) goto label_800B4E78;
    f12 = *(float*)0x8016CC0C;
label_800B4E60:;
    if (*(uint32_t*)0x801C4AA8 != 0) goto label_800B4E60;
    *(float*)(arg0_r3 + 0xD0) = *(float*)0x8016CC10;
label_800B4E78:;
    r0 = *(uint8_t*)(arg0_r3 + 0xFA);
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 0x2u) goto label_800B4E90;
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
    goto label_800B4EA4;
label_800B4E90:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)(arg0_r3 + 0xFA) != 0x2u) goto label_800B4EA4;
label_800B4E9C:;
label_800B4EA0:;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B4EA4:;
    r0 = stack_0x14;
    return; // r3 = ret_800B4E88
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Back(cEm *)
// Unit: player.obj | Address: 0x800B4EB8 | Size: 0x104 bytes
// ============================================================================
/* [0x800B4EB8] */ void pl_R1_Back(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B4EF4;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B4EF4:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B4F18;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B4F88;
    goto label_800B4FA8;
label_800B4F18:;
    r8 = SDA1::pG;
    f0 = *(float*)0x8016CC14;
    r9 = 0;
    r3 = arg0_r3;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CC14;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r7 = 5;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r8 = *(uint32_t*)0x801C4AA8;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x38);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x38) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x38) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r3 = 0;
    r4 = 11;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 11, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r9 = *(uint8_t*)(arg0_r3 + 0xFA);
    r9 = *(uint8_t*)(arg0_r3 + 0xFA) + (1);
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    *(uint8_t*)(arg0_r3 + 0xFA) = (*(uint8_t*)(arg0_r3 + 0xFA) + 1);
label_800B4F88:;
    r3 = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B4F8C == 0) goto label_800B4FA0;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
label_800B4FA0:;
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
label_800B4FA8:;
    r0 = stack_0x14;
    return; // r3 = ret_800B4FA4
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Roll(cEm *)
// Unit: player.obj | Address: 0x800B4FBC | Size: 0x244 bytes
// ============================================================================
/* [0x800B4FBC] */ void pl_R1_Roll(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r31 = arg0_r3;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B4FF8;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B4FF8:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B50A0;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 1) goto label_800B5020;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B5034;
    goto label_800B51EC;
label_800B5020:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 2) goto label_800B50D0;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 3) goto label_800B5130;
    goto label_800B51EC;
label_800B5034:;
    r8 = SDA1::pG;
    f0 = *(float*)0x8016CC18;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CC18;
    r6 = 0;
    r7 = 1;
    r9 = 0;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r0 = *(uint32_t*)(arg0_r3 + 0xF4) | 0x0040u;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r8 = *(uint32_t*)0x801C4AA8;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x124);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x124) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x124) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 1, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r3 = 0;
    r4 = 14;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 14, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = 1;
    *(uint8_t*)(arg0_r3 + 0xFA) = 1;
label_800B50A0:;
    f1 = *(float*)0x8016CC1C;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CC20;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CC1C, *(float*)0x8016CC20); // [0x800A2434]
    if (ret_800B50B4 == 0) goto label_800B51B8;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (ret_800B50B4 != 0) goto label_800B515C;
    goto label_800B51A4;
label_800B50D0:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r4 = arg0_r3 + (380);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x128);
    r6 = 0;
    r7 = 1;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x128) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x128) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 1, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r3 = 0;
    r4 = 14;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 14, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r9 = 1;
    *(uint8_t*)(arg0_r3 + 0xFA) = 1;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4) | 0x0040u;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
label_800B5130:;
    f1 = *(float*)0x8016CC1C;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CC20;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CC1C, *(float*)0x8016CC20); // [0x800A2434]
    if (ret_800B5144 == 0) goto label_800B51B8;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (ret_800B5144 == 0) goto label_800B51A4;
label_800B515C:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r3 = arg0_r3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = arg0_r3 + (380);
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110);
    r7 = 5;
    r9 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x110) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r0 = 0x01050200u;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01050200u;
    goto label_800B51B8;
label_800B51A4:;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
label_800B51B8:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) <= 0xBu) goto label_800B51EC;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 0xBu) goto label_800B51EC;
    r3 = arg0_r3;
    r3 = plActionSelect(arg0_r3); // [0x800B6E94]
    if (ret_800B51D4 == 0) goto label_800B51EC;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
label_800B51EC:;
    r0 = stack_0x14;
    return; // r3 = ret_800B51D4
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Odori(cEm *)
// Unit: player.obj | Address: 0x800B5200 | Size: 0xDCC bytes
// ============================================================================
/* [0x800B5200] */ void pl_R1_Odori(cEm * arg0_r3) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r9 = SDA1::pG;
    r31 = arg0_r3;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B523C;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B523C:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r28 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r29 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B5C9C;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 1) goto label_800B5264;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B5278;
    goto label_800B5FB8;
label_800B5264:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 2) goto label_800B5F28;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 3) goto label_800B5F64;
    goto label_800B5FB8;
label_800B5278:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    r0 = *(uint32_t*)(SDA1::pG + 0x148) | 0x0400u;
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
    r11 = *(uint32_t*)(arg0_r3 + 0xF4);
    r11 = *(uint32_t*)(arg0_r3 + 0xF4) | 0x0040u;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    r3 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4);
    r3 = PlGaugeDown(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4)); // [0x800AE58C]
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 8) goto label_800B5A38;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) > 0x8u) goto label_800B52F0;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 4) goto label_800B594C;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) > 0x4u) goto label_800B52DC;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 2) goto label_800B54BC;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) > 0x2u) goto label_800B57BC;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 1) goto label_800B5338;
    goto label_800B5C84;
label_800B52DC:;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 6) goto label_800B5598;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) > 0x6u) goto label_800B5B58;
    goto label_800B56F0;
label_800B52F0:;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 12) goto label_800B59A0;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) > 0xCu) goto label_800B5314;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 10) goto label_800B5504;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) > 0xAu) goto label_800B5860;
    goto label_800B53D0;
label_800B5314:;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 14) goto label_800B5640;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) < 0xEu) goto label_800B574C;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 15) goto label_800B5BF0;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 16) goto label_800B5AAC;
    goto label_800B5C84;
label_800B5338:;
    r7 = 0;
    r8 = 0;
    r4 = arg0_r3 + (380);
    r30 = arg0_r3 + (192);
    goto label_800B5350;
label_800B534C:;
    r7 = 0 + (1);
label_800B5350:;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C);
    if ((0 + 1) > *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C)) goto label_800B538C;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1756);
    r11 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == r10) goto label_800B5384;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2380);
    r8 = 0 + (1);
label_800B5384:;
    if ((0 + 1) <= 2) goto label_800B534C;
label_800B538C:;
    r9 = SDA1::pG;
    r7 = 3;
    r8 = 65;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r6 = 0;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, 65, 0); // [0x800A1E20]
    r5 = (arg0_r3 + 192);
    r6 = 0;
    r4 = 11;
    r3 = 5;
    r3 = SndSeCall(5, 11, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 27;
    goto label_800B5464;
label_800B53D0:;
    r7 = 0;
    r8 = 0;
    r4 = arg0_r3 + (380);
    r30 = arg0_r3 + (192);
    goto label_800B53E8;
label_800B53E4:;
    r7 = 0 + (1);
label_800B53E8:;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C);
    if ((0 + 1) > *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C)) goto label_800B5424;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1756);
    r11 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == r10) goto label_800B541C;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2380);
    r8 = 0 + (1);
label_800B541C:;
    if ((0 + 1) <= 6) goto label_800B53E4;
label_800B5424:;
    r9 = SDA1::pG;
    r7 = 3;
    r8 = 65;
    r3 = arg0_r3;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r6 = 0;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, 65, 0); // [0x800A1E20]
    r5 = (arg0_r3 + 192);
    r6 = 0;
    r4 = 11;
    r3 = 5;
    r3 = SndSeCall(5, 11, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 42;
label_800B5464:;
    r3 = 40;
    r3 = EspGetEstAddr(40, 42); // [0x800833A4]
    r30 = ret_800B5468;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r0 = 0;
    r7 = ret_800B5474;
    stack_0x08 = 0;
    r9 = 0;
    r6 = ret_800B5468;
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B5468, ret_800B5474, 0, 0, arg0_r3, *(uint32_t*)(SDA1::pG + 0x118)); // [0x800906FC]
    r0 = 64;
    *(uint32_t*)0x801C4AA8 = 64;
    r3 = 4;
    r3 = PlVibSet(4); // [0x800B9098]
    goto label_800B5C84;
label_800B54BC:;
    r10 = SDA1::pG;
    r7 = 3;
    r8 = 5;
    r9 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, 5, 0); // [0x800A1E20]
    r5 = arg0_r3 + (192);
    r6 = 0;
    r4 = 11;
    r3 = 5;
    r3 = SndSeCall(5, 11, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 30;
    goto label_800B5548;
label_800B5504:;
    r10 = SDA1::pG;
    r7 = 3;
    r8 = 5;
    r9 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x78) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, 5, 0); // [0x800A1E20]
    r5 = arg0_r3 + (192);
    r6 = 0;
    r4 = 11;
    r3 = 5;
    r3 = SndSeCall(5, 11, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 70;
label_800B5548:;
    r3 = 40;
    r3 = EspGetEstAddr(40, 70); // [0x800833A4]
    r30 = ret_800B554C;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B5558;
    r9 = 0;
    r6 = ret_800B554C;
    stack_0x08 = *(uint8_t*)(arg0_r3 + 0xFA);
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B554C, ret_800B5558, 0, 0, arg0_r3, *(uint32_t*)(SDA1::pG + 0x118)); // [0x800906FC]
    r3 = 5;
    *(uint32_t*)0x801C4AA8 = *(uint8_t*)(arg0_r3 + 0xFA);
    r3 = PlVibSet(5); // [0x800B9098]
    goto label_800B5C84;
label_800B5598:;
    r7 = 0;
    r8 = 0;
    r4 = arg0_r3 + (380);
    r30 = arg0_r3 + (192);
    goto label_800B55B0;
label_800B55AC:;
    r7 = 0 + (1);
label_800B55B0:;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C);
    if ((0 + 1) > *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C)) goto label_800B55EC;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1756);
    r11 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == arg0_r3) goto label_800B55E4;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2380);
    r8 = 0 + (1);
label_800B55E4:;
    if ((0 + 1) <= 0) goto label_800B55AC;
label_800B55EC:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x70);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x70) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x70) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r5 = (arg0_r3 + 192);
    r4 = 10;
    r6 = 0;
    r3 = 5;
    r3 = SndSeCall(5, 10, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r3 = arg0_r3;
    r3 = SpecialAtck01(arg0_r3); // [0x800B8808]
    goto label_800B56E4;
label_800B5640:;
    r7 = 0;
    r8 = 0;
    r4 = arg0_r3 + (380);
    r30 = arg0_r3 + (192);
    goto label_800B5658;
label_800B5654:;
    r7 = 0 + (1);
label_800B5658:;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C);
    if ((0 + 1) > *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C)) goto label_800B5694;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1756);
    r11 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == *(uint32_t*)(SDA1::pG + 0x118)) goto label_800B568C;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2380);
    r8 = 0 + (1);
label_800B568C:;
    if ((0 + 1) <= 0) goto label_800B5654;
label_800B5694:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x70);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x70) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x70) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r5 = (arg0_r3 + 192);
    r4 = 10;
    r6 = 0;
    r3 = 5;
    r3 = SndSeCall(5, 10, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r3 = arg0_r3;
    r3 = SpecialAtck11(arg0_r3); // [0x800B8954]
label_800B56E4:;
    r3 = 3;
    r3 = PlVibSet(3); // [0x800B9098]
    goto label_800B5C84;
label_800B56F0:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x74);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x74) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x74) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r4 = 12;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = 5;
    r3 = SndSeCall(5, 12, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    goto label_800B57A4;
label_800B574C:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x74);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x74) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x74) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r4 = 12;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = 5;
    r3 = SndSeCall(5, 12, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r3 = arg0_r3;
    r4 = 0;
    r5 = 1;
label_800B57A4:;
    r6 = 0;
    r7 = 0;
    r3 = Blt07Set(arg0_r3, 0, 1, 0, 0); // [0x800139AC]
    r3 = 2;
    r3 = PlVibSet(2); // [0x800B9098]
    goto label_800B5C84;
label_800B57BC:;
    r7 = 0;
    r8 = 0;
    r4 = arg0_r3 + (380);
    r30 = arg0_r3 + (192);
    goto label_800B57D4;
label_800B57D0:;
    r7 = 0 + (1);
label_800B57D4:;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C);
    if ((0 + 1) > *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C)) goto label_800B5810;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1756);
    r11 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == *(uint32_t*)(SDA1::pG + 0x118)) goto label_800B5808;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2380);
    r8 = 0 + (1);
label_800B5808:;
    if ((0 + 1) <= 1) goto label_800B57D0;
label_800B5810:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x88);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x88) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x88) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r5 = (arg0_r3 + 192);
    r6 = 0;
    r4 = 14;
    r3 = 5;
    r3 = SndSeCall(5, 14, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 50;
    goto label_800B5900;
label_800B5860:;
    r7 = 0;
    r8 = 0;
    r4 = arg0_r3 + (380);
    r30 = arg0_r3 + (192);
    goto label_800B5878;
label_800B5874:;
    r7 = 0 + (1);
label_800B5878:;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C);
    if ((0 + 1) > *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C)) goto label_800B58B4;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (1756);
    r11 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == *(uint32_t*)(SDA1::pG + 0x118)) goto label_800B58AC;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2380);
    r8 = 0 + (1);
label_800B58AC:;
    if ((0 + 1) <= 1) goto label_800B5874;
label_800B58B4:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x88);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x88) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x88) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r5 = (arg0_r3 + 192);
    r6 = 0;
    r4 = 14;
    r3 = 5;
    r3 = SndSeCall(5, 14, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 65;
label_800B5900:;
    r3 = 40;
    r3 = EspGetEstAddr(40, 65); // [0x800833A4]
    r30 = ret_800B5904;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B5910;
    r0 = 0;
    stack_0x08 = 0;
    r6 = ret_800B5904;
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B5904, ret_800B5910, 0, 0, arg0_r3, SDA1::pG); // [0x800906FC]
    r3 = 7;
    r3 = PlVibSet(7); // [0x800B9098]
    goto label_800B5C84;
label_800B594C:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x90);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x90) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x90) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r5 = arg0_r3 + (192);
    r6 = 0;
    r4 = 15;
    r3 = 5;
    r3 = SndSeCall(5, 15, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 53;
    goto label_800B59F0;
label_800B59A0:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x90);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x90) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x90) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r5 = arg0_r3 + (192);
    r6 = 0;
    r4 = 15;
    r3 = 5;
    r3 = SndSeCall(5, 15, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 86;
label_800B59F0:;
    r3 = 40;
    r3 = EspGetEstAddr(40, 86); // [0x800833A4]
    r30 = ret_800B59F4;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B5A00;
    stack_0x08 = *(uint8_t*)(arg0_r3 + 0xFA);
    r6 = ret_800B59F4;
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B59F4, ret_800B5A00, 0, 0, arg0_r3, SDA1::pG); // [0x800906FC]
    r3 = 8;
    r3 = PlVibSet(8); // [0x800B9098]
    goto label_800B5C84;
label_800B5A38:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8C);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r5 = arg0_r3 + (192);
    r6 = 0;
    r4 = 16;
    r3 = 5;
    r3 = SndSeCall(5, 16, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 56;
    r3 = 40;
    r3 = EspGetEstAddr(40, 56); // [0x800833A4]
    r30 = ret_800B5A8C;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B5A98;
    r9 = 0;
    stack_0x08 = *(uint8_t*)(arg0_r3 + 0xFA);
    goto label_800B5B20;
label_800B5AAC:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8C);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8C) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8C) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r5 = arg0_r3 + (192);
    r6 = 0;
    r4 = 16;
    r3 = 5;
    r3 = SndSeCall(5, 16, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 73;
    r3 = 40;
    r3 = EspGetEstAddr(40, 73); // [0x800833A4]
    r30 = ret_800B5B00;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r0 = 0;
    r7 = ret_800B5B0C;
    stack_0x08 = 0;
    r9 = 0;
label_800B5B20:;
    r6 = ret_800B5B00;
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B5B00, ret_800B5B0C, 0, 0, arg0_r3, SDA1::pG); // [0x800906FC]
    r9 = SDA1::pG;
    r3 = 9;
    r0 = *(uint32_t*)(SDA1::pG + 0x14C);
    *(uint32_t*)(SDA1::pG + 0x14C) = *(uint32_t*)(SDA1::pG + 0x14C);
    r3 = PlVibSet(9); // [0x800B9098]
    goto label_800B5C84;
label_800B5B58:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x94);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x94) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x94) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r5 = arg0_r3 + (192);
    r6 = 0;
    r4 = 13;
    r3 = 5;
    r3 = SndSeCall(5, 13, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 54;
    r3 = 40;
    r3 = EspGetEstAddr(40, 54); // [0x800833A4]
    r30 = ret_800B5BAC;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B5BB8;
    stack_0x08 = *(uint8_t*)(arg0_r3 + 0xFA);
    r6 = ret_800B5BAC;
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B5BAC, ret_800B5BB8, 0, 0, arg0_r3, SDA1::pG); // [0x800906FC]
    r3 = 6;
    r3 = PlVibSet(6); // [0x800B9098]
    goto label_800B5C84;
label_800B5BF0:;
    r11 = SDA1::pG;
    r8 = *(uint32_t*)0x801C4AA8;
    r7 = 3;
    r10 = *(uint32_t*)(SDA1::pG + 0x118);
    r9 = 0;
    r8 = *(uint32_t*)0x801C4AA8 | 0x0005u;
    r3 = arg0_r3;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x94);
    r4 = arg0_r3 + (380);
    r6 = 0;
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x94) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x94) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 3, *(uint32_t*)0x801C4AA8, 0); // [0x800A1E20]
    r5 = arg0_r3 + (192);
    r6 = 0;
    r4 = 13;
    r3 = 5;
    r3 = SndSeCall(5, 13, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r4 = 82;
    r3 = 40;
    r3 = EspGetEstAddr(40, 82); // [0x800833A4]
    r30 = ret_800B5C44;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B5C50;
    stack_0x08 = *(uint8_t*)(arg0_r3 + 0xFA);
    r6 = ret_800B5C44;
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B5C44, ret_800B5C50, 0, 0, arg0_r3, SDA1::pG); // [0x800906FC]
    r3 = 6;
    r3 = PlVibSet(6); // [0x800B9098]
label_800B5C84:;
    r0 = 1;
    *(uint8_t*)(arg0_r3 + 0xFA) = 1;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    r0 = *(uint32_t*)(SDA1::pG + 0x148) | 0x0020u;
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
label_800B5C9C:;
    r0 = 1;
    r3 = 1;
    *(uint8_t*)(arg0_r3 + 0x4E1) = 1;
    r3 = MotionMovePl(1); // [0x800B7158]
    if (ret_800B5CA8 == 0) goto label_800B5CC8;
    r0 = 10;
    r9 = 2;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10) = 10;
    *(uint8_t*)(arg0_r3 + 0xFA) = 2;
    goto label_800B5FB8;
label_800B5CC8:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 7) goto label_800B5E7C;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) > 0x7u) goto label_800B5D0C;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 2) goto label_800B5D74;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) > 0x2u) goto label_800B5CF8;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 1) goto label_800B5D44;
    goto label_800B5FB8;
label_800B5CF8:;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 3) goto label_800B5E20;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 4) goto label_800B5E38;
    goto label_800B5FB8;
label_800B5D0C:;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 11) goto label_800B5E2C;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) > 0xBu) goto label_800B5D30;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 9) goto label_800B5D5C;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 10) goto label_800B5DD0;
    goto label_800B5FB8;
label_800B5D30:;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 12) goto label_800B5E54;
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) == 15) goto label_800B5EB8;
    goto label_800B5FB8;
label_800B5D44:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 29) goto label_800B5FB8;
    r3 = arg0_r3;
    r3 = SpecialAtck00(arg0_r3); // [0x800B7CD4]
    goto label_800B5FB8;
label_800B5D5C:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 29) goto label_800B5FB8;
    r3 = arg0_r3;
    r3 = SpecialAtck10(arg0_r3); // [0x800B8270]
    goto label_800B5FB8;
label_800B5D74:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 29) goto label_800B5FB8;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B5DAC;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125);
    r3 = arg0_r3;
    r4 = 25;
    r5 = 0;
label_800B5D9C:;
    r6 = 0;
    r7 = 0;
    r3 = Blt08Set(arg0_r3, 25, 0, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125)); // [0x80014408]
    goto label_800B5F10;
label_800B5DAC:;
    r3 = arg0_r3;
    r4 = 25;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r9 = 0;
    r3 = Blt08Set(arg0_r3, 25, 0, 0, 0, 0, 0); // [0x80014408]
    goto label_800B5F10;
label_800B5DD0:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 29) goto label_800B5FB8;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B5DFC;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125);
    r3 = arg0_r3;
    r4 = 25;
    r5 = 1;
    goto label_800B5D9C;
label_800B5DFC:;
    r3 = arg0_r3;
    r4 = 25;
    r5 = 1;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r9 = 0;
    r3 = Blt08Set(arg0_r3, 25, 1, 0, 0, 0, 0); // [0x80014408]
    goto label_800B5F10;
label_800B5E20:;
    r3 = arg0_r3;
    r3 = SpecialAtck02(arg0_r3); // [0x800B8A54]
    goto label_800B5FB8;
label_800B5E2C:;
    r3 = arg0_r3;
    r3 = SpecialAtck12(arg0_r3); // [0x800B8CF0]
    goto label_800B5FB8;
label_800B5E38:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 20) goto label_800B5FB8;
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    goto label_800B5E6C;
label_800B5E54:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 20) goto label_800B5FB8;
    r3 = arg0_r3;
    r4 = 0;
    r5 = 1;
label_800B5E6C:;
    r6 = 0;
    r7 = 0;
    r3 = Blt0cSet(arg0_r3, 0, 1, 0, 0); // [0x80015C40]
    goto label_800B5FB8;
label_800B5E7C:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 76) goto label_800B5FB8;
    r6 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B5EA8;
    r7 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125);
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    goto label_800B5EE0;
label_800B5EA8:;
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    goto label_800B5EFC;
label_800B5EB8:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 76) goto label_800B5FB8;
    r6 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B5EF0;
    r7 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125);
    r3 = arg0_r3;
    r4 = 0;
    r5 = 1;
label_800B5EE0:;
    r8 = 0;
    r9 = 0;
    r3 = Blt01Set(arg0_r3, 0, 1, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125), 0, 0); // [0x8000DCE0]
    goto label_800B5F10;
label_800B5EF0:;
    r3 = arg0_r3;
    r4 = 0;
    r5 = 1;
label_800B5EFC:;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r9 = 0;
    r3 = Blt01Set(arg0_r3, 0, 1, 0, 0, 0, 0); // [0x8000DCE0]
label_800B5F10:;
    r5 = arg0_r3 + (192);
    r3 = 5;
    r4 = 3;
    r6 = 0;
    r3 = SndSeCall(5, 3, (arg0_r3 + 192), 0); // [0x800CB7DC]
    goto label_800B5FB8;
label_800B5F28:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) != 8) goto label_800B5F40;
    r0 = 128;
    r9 = 150;
    goto label_800B5F50;
label_800B5F40:;
    if (128 != 16) goto label_800B5F5C;
    r0 = 128;
    r9 = 300;
label_800B5F50:;
    *(uint8_t*)(arg0_r3 + 0x4E1) = 128;
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA26) = 300;
    goto label_800B5F64;
label_800B5F5C:;
    r0 = 15;
    *(uint8_t*)(arg0_r3 + 0x4E1) = 15;
label_800B5F64:;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r11 = *(uint16_t*)(arg0_r3 + 0x45A);
    r9 = 0;
    r10 = SDA1::pG;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x964) = 0;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) = 0;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950) = 0;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x954) = 0;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x958) = 0;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x95C) = 0;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x960) = 0;
label_800B5FB8:;
    r0 = stack_0x24;
    return; // r3 = ret_800B5F20
}

// ============================================================================
// High-Level AST Decompilation: pl_R1_Appear(cEm *)
// Unit: player.obj | Address: 0x800B5FCC | Size: 0x44C bytes
// ============================================================================
/* [0x800B5FCC] */ void pl_R1_Appear(cEm * arg0_r3) {
    // Stack frame allocated: 88 bytes
    stack_0x5C = r0;
    r9 = SDA1::pG;
    r31 = arg0_r3;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B6008;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B6008:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r27 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r28 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 1) goto label_800B61B0;
    if (*(uint8_t*)(arg0_r3 + 0xFA) > 1) goto label_800B6030;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 0) goto label_800B6044;
    goto label_800B6404;
label_800B6030:;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 2) goto label_800B6310;
    if (*(uint8_t*)(arg0_r3 + 0xFA) == 3) goto label_800B63D0;
    goto label_800B6404;
label_800B6044:;
    r0 = *(uint32_t*)0x8016CC24;
    r3 = &stack_0x10;
    r9 = 0x8016CC24u;
    r5 = *(uint32_t*)0x8016CC30;
    r10 = *(uint32_t*)(0x8016CC24u + 0x4);
    r8 = 0x8016CC30u;
    r6 = *(uint32_t*)(0x8016CC24u + 0x8);
    stack_0x10 = *(uint32_t*)0x8016CC24;
    r7 = 1;
    *(uint32_t*)(&stack_0x10 + 0x4) = *(uint32_t*)(0x8016CC24u + 0x4);
    r9 = &stack_0x20;
    *(uint32_t*)(&stack_0x10 + 0x8) = *(uint32_t*)(0x8016CC24u + 0x8);
    r4 = &stack_0x20;
    stack_0x20 = *(uint32_t*)0x8016CC30;
    r29 = arg0_r3 + (192);
    r0 = *(uint32_t*)(0x8016CC30u + 0x4);
    *(uint32_t*)0x801C4AA8 = *(uint8_t*)(arg0_r3 + 0xFA);
    r11 = *(uint32_t*)(0x8016CC30u + 0x8);
    *(uint8_t*)(arg0_r3 + 0x4E1) = 1;
    *(uint32_t*)(&stack_0x20 + 0x4) = *(uint32_t*)(0x8016CC30u + 0x4);
    *(uint32_t*)(&stack_0x20 + 0x8) = *(uint32_t*)(0x8016CC30u + 0x8);
    r3 = CameraBehindSet2(&stack_0x10, &stack_0x20); // [0x800B7414]
    r9 = SDA1::pG;
    r6 = 0;
    r7 = 0;
    r8 = 5;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r3 = arg0_r3;
    r9 = 0;
    r4 = arg0_r3 + (380);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x48);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x48) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x48) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 0, 5, 0); // [0x800A1E20]
    r4 = 20;
    r3 = 40;
    r3 = EspGetEstAddr(40, 20); // [0x800833A4]
    r30 = ret_800B60DC;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B60E8;
    r6 = ret_800B60DC;
    stack_0x08 = *(uint8_t*)(arg0_r3 + 0xFA);
    r5 = arg0_r3 + (204);
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    r4 = (arg0_r3 + 192);
    r3 = arg0_r3;
    r3 = EstSet(arg0_r3, (arg0_r3 + 192), (arg0_r3 + 204), ret_800B60DC, ret_800B60E8, 0, 0, arg0_r3, *(uint32_t*)(SDA1::pG + 0x118)); // [0x800906FC]
    r4 = 5;
    r3 = 40;
    r3 = EspGetEstAddr(40, 5); // [0x800833A4]
    r30 = ret_800B611C;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B6128;
    r5 = 0;
    r9 = 0;
    r6 = ret_800B611C;
    stack_0x08 = *(uint8_t*)(arg0_r3 + 0xFA);
    r3 = arg0_r3;
    r4 = 0;
    r8 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B611C, ret_800B6128, 0, 0, arg0_r3, *(uint32_t*)(SDA1::pG + 0x118)); // [0x800906FC]
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    r9 = 50;
    r5 = (arg0_r3 + 192);
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x14) = *(uint8_t*)(arg0_r3 + 0xFA);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10) = 50;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xC) = *(uint8_t*)(arg0_r3 + 0xFA);
    r9 = *(uint32_t*)(arg0_r3 + 0x130);
    if (*(uint32_t*)(arg0_r3 + 0x130) == 0) goto label_800B6194;
    r0 = 0;
label_800B6184:;
    *(uint8_t*)(*(uint32_t*)(arg0_r3 + 0x130) + 0x5F) = 0;
    r9 = *(uint32_t*)(*(uint32_t*)(arg0_r3 + 0x130) + 0x4);
    if (*(uint32_t*)(*(uint32_t*)(arg0_r3 + 0x130) + 0x4) != 0) goto label_800B6184;
label_800B6194:;
    r0 = 1;
    r3 = 0;
    *(uint8_t*)(arg0_r3 + 0xFA) = 1;
    r4 = 36;
    r6 = 0;
    r3 = SndSeCall(0, 36, (arg0_r3 + 192), 0); // [0x800CB7DC]
    goto label_800B6404;
label_800B61B0:;
    f1 = *(float*)0x8016CC48;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CC4C;
    *(uint8_t*)(arg0_r3 + 0x4E1) = *(uint8_t*)(arg0_r3 + 0xFA);
    r3 = MotionMove(arg0_r3, *(float*)0x8016CC48, *(float*)0x8016CC4C); // [0x800A2434]
    if (ret_800B61C8 == 0) goto label_800B6234;
    r0 = *(uint32_t*)0x8016CC3C;
    r11 = &stack_0x10;
    r9 = 0x8016CC3Cu;
    r7 = 0x8016CC30u;
    r5 = *(uint32_t*)(0x8016CC3Cu + 0x8);
    r3 = &stack_0x10;
    r8 = *(uint32_t*)(0x8016CC3Cu + 0x4);
    stack_0x10 = *(uint32_t*)0x8016CC3C;
    r9 = &stack_0x30;
    r6 = *(uint32_t*)0x8016CC30;
    r4 = &stack_0x30;
    *(uint32_t*)(&stack_0x10 + 0x4) = *(uint32_t*)(0x8016CC3Cu + 0x4);
    *(uint32_t*)(&stack_0x10 + 0x8) = *(uint32_t*)(0x8016CC3Cu + 0x8);
    r0 = *(uint32_t*)(0x8016CC30u + 0x4);
    r10 = *(uint32_t*)(0x8016CC30u + 0x8);
    stack_0x30 = *(uint32_t*)0x8016CC30;
    *(uint32_t*)(&stack_0x30 + 0x4) = *(uint32_t*)(0x8016CC30u + 0x4);
    *(uint32_t*)(&stack_0x30 + 0x8) = *(uint32_t*)(0x8016CC30u + 0x8);
    r3 = CameraBehindSet2(&stack_0x10, &stack_0x30); // [0x800B7414]
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
    goto label_800B6404;
label_800B6234:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 162) goto label_800B6254;
    r3 = 0;
    r4 = 9;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r3 = SndSeCall(0, 9, (arg0_r3 + 192), 0); // [0x800CB7DC]
label_800B6254:;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 203) goto label_800B6268;
    r3 = 2;
    r3 = Snd_footse_call(2); // [0x800CD030]
label_800B6268:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10) == 0) goto label_800B6280;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10) + (-1);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10) = (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10) + -1);
    goto label_800B6404;
label_800B6280:;
    r29 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xC);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xC) != 0) goto label_800B62D0;
    r4 = 6;
    r3 = 40;
    r3 = EspGetEstAddr(40, 6); // [0x800833A4]
    r30 = ret_800B6294;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B62A0;
    stack_0x08 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xC);
    r6 = ret_800B6294;
    r3 = arg0_r3;
    r4 = 0;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B6294, ret_800B62A0, 0, 0, arg0_r3, &stack_0x10); // [0x800906FC]
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xC) = *(uint8_t*)(arg0_r3 + 0xFA);
label_800B62D0:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x14);
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x14) + (25);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x14) = (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x14) + 25);
    if ((*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x14) + 25) <= 254) goto label_800B62EC;
    r0 = 255;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x14) = 255;
label_800B62EC:;
    r3 = *(uint32_t*)(arg0_r3 + 0x130);
    if (*(uint32_t*)(arg0_r3 + 0x130) == 0) goto label_800B6404;
label_800B62F8:;
    r0 = *(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x17);
    *(uint8_t*)(*(uint32_t*)(arg0_r3 + 0x130) + 0x5F) = *(uint8_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x17);
    r3 = *(uint32_t*)(*(uint32_t*)(arg0_r3 + 0x130) + 0x4);
    if (*(uint32_t*)(*(uint32_t*)(arg0_r3 + 0x130) + 0x4) != 0) goto label_800B62F8;
    goto label_800B6404;
label_800B6310:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10) == 0) goto label_800B6344;
    f1 = *(float*)0x8016CC48;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CC4C;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CC48, *(float*)0x8016CC4C); // [0x800A2434]
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10);
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10) + (-1);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10) = (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x10) + -1);
    goto label_800B6404;
label_800B6344:;
    r0 = *(uint32_t*)0x8016CC3C;
    r11 = &stack_0x10;
    r9 = 0x8016CC3Cu;
    r6 = *(uint32_t*)0x8016CC30;
    r4 = *(uint32_t*)(0x8016CC3Cu + 0x8);
    r7 = 0x8016CC30u;
    r8 = *(uint32_t*)(0x8016CC3Cu + 0x4);
    r3 = &stack_0x10;
    stack_0x10 = *(uint32_t*)0x8016CC3C;
    r5 = 3;
    *(uint32_t*)(&stack_0x10 + 0x4) = *(uint32_t*)(0x8016CC3Cu + 0x4);
    r9 = &stack_0x20;
    *(uint32_t*)(&stack_0x10 + 0x8) = *(uint32_t*)(0x8016CC3Cu + 0x8);
    stack_0x20 = *(uint32_t*)0x8016CC30;
    r4 = &stack_0x20;
    r11 = *(uint32_t*)(0x8016CC30u + 0x8);
    r0 = *(uint32_t*)(0x8016CC30u + 0x4);
    *(uint8_t*)(arg0_r3 + 0xFA) = 3;
    *(uint32_t*)(&stack_0x20 + 0x8) = *(uint32_t*)(0x8016CC30u + 0x8);
    *(uint32_t*)(&stack_0x20 + 0x4) = *(uint32_t*)(0x8016CC30u + 0x4);
    r3 = CameraBehindSet2(&stack_0x10, &stack_0x20); // [0x800B7414]
    r9 = SDA1::pG;
    r3 = arg0_r3;
    r4 = arg0_r3 + (380);
    r6 = 0;
    r11 = *(uint32_t*)(SDA1::pG + 0x118);
    r7 = 5;
    r8 = 5;
    r9 = 0;
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x140);
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x140) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = MotionSetCore(arg0_r3, (arg0_r3 + 380), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x140) + *(uint32_t*)(SDA1::pG + 0x118)), 0, 5, 5, 0); // [0x800A1E20]
    goto label_800B6404;
label_800B63D0:;
    f1 = *(float*)0x8016CC48;
    r3 = arg0_r3;
    f2 = *(float*)0x8016CC4C;
    r3 = MotionMove(arg0_r3, *(float*)0x8016CC48, *(float*)0x8016CC4C); // [0x800A2434]
    if (ret_800B63E4 == 0) goto label_800B6404;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4);
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01000000u;
    r0 = *(uint32_t*)(arg0_r3 + 0xF4) | 0x0400u;
    *(uint32_t*)(arg0_r3 + 0xF4) = *(uint32_t*)(arg0_r3 + 0xF4);
label_800B6404:;
    r0 = stack_0x5C;
    return; // r3 = ret_800B63E4
}

// ============================================================================
// High-Level AST Decompilation: keyConfig(cEm *)
// Unit: player.obj | Address: 0x800B6418 | Size: 0x88 bytes
// ============================================================================
/* [0x800B6418] */ void keyConfig(cEm * arg0_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r29 = 0;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B6458;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B6458:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r8 = SDA1::pG;
    r11 = &keyconfig_func_tbl.1118;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r3 = arg0_r3;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = 0;
    r0 = *(uint8_t*)(SDA1::pG + 0x6A91);
    return; // r3 = arg0_r3
    r0 = stack_0x1C;
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: keyConfigTypeA(cEm *)
// Unit: player.obj | Address: 0x800B64A0 | Size: 0x1DC bytes
// ============================================================================
/* [0x800B64A0] */ void keyConfigTypeA(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B64DC;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B64DC:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r9 = &Joy;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r0 = *(uint32_t*)(&Joy + 0x10);
    r10 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (r0 == 0) goto label_800B6508;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0001u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6508:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6520;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0004u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6520:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6538;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0008u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6538:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6550;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0002u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6550:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6568;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0010u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6568:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6580;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0020u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6580:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6598;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0400u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6598:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B65B0;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0800u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B65B0:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B65C8;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x1000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B65C8:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B65F0;
    r9 = *(uint32_t*)(&Joy + 0x10);
    if (r0 != 0) goto label_800B65E4;
label_800B65E4:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x2000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B65F0:;
    r9 = &Joy;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6614;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x4000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6614:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6630;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x8000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6630:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6648;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0100u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6648:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6660;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6660:;
    r3 = arg0_r3;
    r3 = SpecialCk(arg0_r3); // [0x800AE920]
    r0 = stack_0x14;
    return; // r3 = ret_800B6664
}

// ============================================================================
// High-Level AST Decompilation: keyConfigTypeB(cEm *)
// Unit: player.obj | Address: 0x800B667C | Size: 0x1DC bytes
// ============================================================================
/* [0x800B667C] */ void keyConfigTypeB(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B66B8;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B66B8:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r9 = &Joy;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r0 = *(uint32_t*)(&Joy + 0x10);
    r10 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (r0 == 0) goto label_800B66E4;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0001u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B66E4:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B66FC;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0004u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B66FC:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6714;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0008u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6714:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B672C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0002u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B672C:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6744;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0010u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6744:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B675C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0020u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B675C:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6774;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0400u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6774:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B678C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0800u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B678C:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B67A4;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x1000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B67A4:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B67CC;
    r9 = *(uint32_t*)(&Joy + 0x10);
    if (r0 != 0) goto label_800B67C0;
label_800B67C0:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x2000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B67CC:;
    r9 = &Joy;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B67F0;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x4000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B67F0:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B680C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x8000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B680C:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6824;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0100u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6824:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B683C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B683C:;
    r3 = arg0_r3;
    r3 = SpecialCk(arg0_r3); // [0x800AE920]
    r0 = stack_0x14;
    return; // r3 = ret_800B6840
}

// ============================================================================
// High-Level AST Decompilation: keyConfigTypeC(cEm *)
// Unit: player.obj | Address: 0x800B6858 | Size: 0x438 bytes
// ============================================================================
/* [0x800B6858] */ void keyConfigTypeC(cEm * arg0_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r9 = SDA1::pG;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B6890;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B6890:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r9 = &Joy;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r0 = *(uint32_t*)(&Joy + 0x10);
    r31 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (r0 == 0) goto label_800B68BC;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0001u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B68BC:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B68D4;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0004u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B68D4:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B68EC;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0008u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B68EC:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6904;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0002u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6904:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B691C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0010u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B691C:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6934;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0020u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6934:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B694C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0400u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B694C:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6964;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0800u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6964:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B697C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x1000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B697C:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B69A4;
    r9 = *(uint32_t*)(&Joy + 0x10);
    if (r0 != 0) goto label_800B6998;
label_800B6998:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x2000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B69A4:;
    r29 = &Joy;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B69C4;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B69C4:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B69DC;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B69DC:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B69F4;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x4000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B69F4:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6A0C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x8000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6A0C:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6A24;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0100u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6A24:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6A3C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6A3C:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (r0 != 0) goto label_800B6C7C;
    r0 = *(uint32_t*)(SDA1::pG + 0x130);
    r28 = 1;
    if (r0 != 0) goto label_800B6A6C;
    r3 = 200;
    r3 = PlGaugeCheck(200); // [0x800AE550]
    if (ret_800B6A60 == 0) goto label_800B6C7C;
label_800B6A6C:;
    r0 = SDA1::r_no.1129;
    if (SDA1::r_no.1129 == 4) goto label_800B6B74;
    if (SDA1::r_no.1129 > 4) goto label_800B6AA8;
    if (SDA1::r_no.1129 == 1) goto label_800B6AE4;
    if (SDA1::r_no.1129 > 1) goto label_800B6A94;
    if (SDA1::r_no.1129 == 0) goto label_800B6AC8;
    goto label_800B6C7C;
label_800B6A94:;
    if (SDA1::r_no.1129 == 2) goto label_800B6B14;
    if (SDA1::r_no.1129 == 3) goto label_800B6B44;
    goto label_800B6C7C;
label_800B6AA8:;
    if (SDA1::r_no.1129 == 6) goto label_800B6BD4;
    if (SDA1::r_no.1129 < 6) goto label_800B6BA4;
    if (SDA1::r_no.1129 == 7) goto label_800B6C04;
    if (SDA1::r_no.1129 == 8) goto label_800B6C3C;
    goto label_800B6C7C;
label_800B6AC8:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (SDA1::r_no.1129 == 8) goto label_800B6C7C;
    r0 = 10;
    SDA1::r_no.1129 = 1;
    SDA1::timer.1128 = 10;
    goto label_800B6C7C;
label_800B6AE4:;
    r9 = SDA1::timer.1128;
    r9 = SDA1::timer.1128 + (-1);
    SDA1::timer.1128 = (SDA1::timer.1128 + -1);
    if ((SDA1::timer.1128 + -1) != -1) goto label_800B6AFC;
    SDA1::r_no.1129 = r30;
label_800B6AFC:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if ((SDA1::timer.1128 + -1) == -1) goto label_800B6C7C;
    r0 = 10;
    r9 = 2;
    goto label_800B6C30;
label_800B6B14:;
    r9 = SDA1::timer.1128;
    r9 = SDA1::timer.1128 + (-1);
    SDA1::timer.1128 = (SDA1::timer.1128 + -1);
    if ((SDA1::timer.1128 + -1) != -1) goto label_800B6B2C;
    SDA1::r_no.1129 = r30;
label_800B6B2C:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if ((SDA1::timer.1128 + -1) == -1) goto label_800B6C7C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) = r30;
    goto label_800B6C6C;
label_800B6B44:;
    r9 = SDA1::timer.1128;
    r9 = SDA1::timer.1128 + (-1);
    SDA1::timer.1128 = (SDA1::timer.1128 + -1);
    if ((SDA1::timer.1128 + -1) != -1) goto label_800B6B5C;
    SDA1::r_no.1129 = r30;
label_800B6B5C:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if ((SDA1::timer.1128 + -1) == -1) goto label_800B6C7C;
    r0 = 10;
    r9 = 4;
    goto label_800B6C30;
label_800B6B74:;
    r9 = SDA1::timer.1128;
    r9 = SDA1::timer.1128 + (-1);
    SDA1::timer.1128 = (SDA1::timer.1128 + -1);
    if ((SDA1::timer.1128 + -1) != -1) goto label_800B6B8C;
    SDA1::r_no.1129 = r30;
label_800B6B8C:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if ((SDA1::timer.1128 + -1) == -1) goto label_800B6C7C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) = 1;
    goto label_800B6C6C;
label_800B6BA4:;
    r9 = SDA1::timer.1128;
    r9 = SDA1::timer.1128 + (-1);
    SDA1::timer.1128 = (SDA1::timer.1128 + -1);
    if ((SDA1::timer.1128 + -1) != -1) goto label_800B6BBC;
    SDA1::r_no.1129 = r30;
label_800B6BBC:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if ((SDA1::timer.1128 + -1) == -1) goto label_800B6C7C;
    r0 = 10;
    r9 = 6;
    goto label_800B6C30;
label_800B6BD4:;
    r9 = SDA1::timer.1128;
    r9 = SDA1::timer.1128 + (-1);
    SDA1::timer.1128 = (SDA1::timer.1128 + -1);
    if ((SDA1::timer.1128 + -1) != -1) goto label_800B6BEC;
    SDA1::r_no.1129 = r30;
label_800B6BEC:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if ((SDA1::timer.1128 + -1) == -1) goto label_800B6C7C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r9 = 2;
    goto label_800B6C68;
label_800B6C04:;
    r9 = SDA1::timer.1128;
    r9 = SDA1::timer.1128 + (-1);
    SDA1::timer.1128 = (SDA1::timer.1128 + -1);
    if ((SDA1::timer.1128 + -1) != -1) goto label_800B6C1C;
    SDA1::r_no.1129 = r30;
label_800B6C1C:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if ((SDA1::timer.1128 + -1) == -1) goto label_800B6C7C;
    r0 = 10;
    r9 = 8;
label_800B6C30:;
    SDA1::timer.1128 = 10;
    SDA1::r_no.1129 = 8;
    goto label_800B6C7C;
label_800B6C3C:;
    r9 = SDA1::timer.1128;
    r9 = SDA1::timer.1128 + (-1);
    SDA1::timer.1128 = (SDA1::timer.1128 + -1);
    if ((SDA1::timer.1128 + -1) != -1) goto label_800B6C54;
    SDA1::r_no.1129 = r30;
label_800B6C54:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if ((SDA1::timer.1128 + -1) == -1) goto label_800B6C7C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r9 = 3;
label_800B6C68:;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6D4) = 3;
label_800B6C6C:;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    SDA1::r_no.1129 = r30;
    SDA1::timer.1128 = r30;
label_800B6C7C:;
    r0 = stack_0x1C;
    return; // r3 = ret_800B6A60
}

// ============================================================================
// High-Level AST Decompilation: keyConfigTypeD(cEm *)
// Unit: player.obj | Address: 0x800B6C90 | Size: 0x204 bytes
// ============================================================================
/* [0x800B6C90] */ void keyConfigTypeD(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B6CCC;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B6CCC:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r9 = &Joy;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r0 = *(uint32_t*)(&Joy + 0x10);
    r10 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (r0 == 0) goto label_800B6CF8;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0001u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6CF8:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6D10;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0004u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6D10:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6D28;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0008u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6D28:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6D40;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0002u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6D40:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6D58;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0010u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6D58:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6D70;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0020u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6D70:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6D88;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0400u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6D88:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6DA0;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0800u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6DA0:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6DB8;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x1000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6DB8:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6DE0;
    r9 = *(uint32_t*)(&Joy + 0x10);
    if (r0 != 0) goto label_800B6DD4;
label_800B6DD4:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x2000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6DE0:;
    r9 = &Joy;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6E00;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6E00:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6E18;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6E18:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6E30;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x4000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6E30:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6E48;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x8000u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6E48:;
    r0 = *(uint32_t*)(&Joy + 0x14);
    if (r0 == 0) goto label_800B6E60;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) | 0x0100u;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6E60:;
    r0 = *(uint32_t*)(&Joy + 0x10);
    if (r0 == 0) goto label_800B6E78;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
label_800B6E78:;
    r3 = arg0_r3;
    r3 = SpecialCk(arg0_r3); // [0x800AE920]
    r0 = stack_0x14;
    return; // r3 = ret_800B6E7C
}

// ============================================================================
// High-Level AST Decompilation: plActionSelect(cEm *)
// Unit: player.obj | Address: 0x800B6E94 | Size: 0x1D0 bytes
// ============================================================================
/* [0x800B6E94] */ void plActionSelect(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B6ED0;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B6ED0:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r3 = 0;
    r9 = SDA1::pG;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    r31 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (r0 != 0) goto label_800B7050;
    r3 = arg0_r3;
    r3 = CheckCtrl(arg0_r3); // [0x800B7A48]
    r10 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (r0 == 0) goto label_800B6F0C;
    goto label_800B7040;
label_800B6F0C:;
    r0 = *(uint8_t*)(arg0_r3 + 0xF9);
    r8 = *(uint8_t*)(arg0_r3 + 0xF9);
    if (*(uint8_t*)(arg0_r3 + 0xF9) == 5) goto label_800B6F68;
    r11 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (*(uint8_t*)(arg0_r3 + 0xF9) != 5) goto label_800B6F68;
    if (*(uint8_t*)(arg0_r3 + 0xF9) != 5) goto label_800B6F68;
    r9 = *(uint8_t*)(SDA1::pG + 0x681A);
    r9 = (SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A));
    r0 = *(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689D);
    if (*(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689D) == 0) goto label_800B6F5C;
    if (*(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689D) == 0) goto label_800B6F68;
    goto label_800B7040;
label_800B6F5C:;
    if (*(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689D) != 0) goto label_800B7040;
label_800B6F68:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (*(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689D) != 0) goto label_800B7040;
    if (0x01030000u == 8) goto label_800B6F98;
    if (0x01030000u == 8) goto label_800B6F98;
    goto label_800B7040;
label_800B6F98:;
    if (0x01030000u == 8) goto label_800B6FBC;
    if (0x01080000u == 5) goto label_800B6FBC;
    if (0x01080000u == 13) goto label_800B6FBC;
    goto label_800B7040;
label_800B6FBC:;
    if (0x01080000u == 13) goto label_800B6FE4;
    if (0x01080000u != 13) goto label_800B6FD8;
    r0 = 0x01020200u;
label_800B6FD8:;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01020200u;
    r3 = 1;
    goto label_800B7050;
label_800B6FE4:;
    if (0x01020200u == 1) goto label_800B7010;
    if (0x01020200u == 1) goto label_800B7010;
    r9 = 10;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01010000u;
    r3 = 1;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x65C) = 10;
    goto label_800B7050;
label_800B7010:;
    if (0x01010000u == 12) goto label_800B7028;
    if (0x01010000u != 12) goto label_800B7040;
label_800B7028:;
    if (0x010C0000u != 0) goto label_800B704C;
    if (0x010C0000u == 0) goto label_800B704C;
label_800B7040:;
    r3 = 1;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x010B0000u;
    goto label_800B7050;
label_800B704C:;
    r3 = 0;
label_800B7050:;
    r0 = stack_0x14;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: plModelInit(cEm *)
// Unit: player.obj | Address: 0x800B7064 | Size: 0xF4 bytes
// ============================================================================
/* [0x800B7064] */ void plModelInit(cEm * arg0_r3) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r9 = SDA1::pG;
    r31 = arg0_r3;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B70A0;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B70A0:;
    r11 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r10 = SDA1::pG;
    r9 = &XFlip;
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r3 = arg0_r3;
    *(uint32_t*)(arg0_r3 + 0x43C) = &XFlip;
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    r9 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8);
    r4 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4) + *(uint32_t*)(SDA1::pG + 0x118));
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = cObj::ModelInit(arg0_r3, (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x4) + *(uint32_t*)(SDA1::pG + 0x118)), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x8) + *(uint32_t*)(SDA1::pG + 0x118))); // [0x80074D30]
    r3 = *(uint32_t*)(arg0_r3 + 0xF0);
    r4 = 2;
    r3 = GetPartsAddr(*(uint32_t*)(arg0_r3 + 0xF0), 2); // [0x800A0BD4]
    r11 = SDA1::pG;
    f0 = *(float*)0x8016CC50;
    r6 = ret_800B70E0;
    r7 = &stack_0x08;
    r3 = arg0_r3;
    stack_0x10 = *(float*)0x8016CC50;
    stack_0x08 = *(float*)0x8016CC50;
    stack_0x0C = *(float*)0x8016CC50;
    r9 = *(uint32_t*)(SDA1::pG + 0x118);
    r4 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0xC);
    r5 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x10);
    r4 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0xC) + *(uint32_t*)(SDA1::pG + 0x118));
    r5 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x10) + *(uint32_t*)(SDA1::pG + 0x118));
    r3 = SetPack(arg0_r3, (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0xC) + *(uint32_t*)(SDA1::pG + 0x118)), (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x118) + 0x10) + *(uint32_t*)(SDA1::pG + 0x118)), ret_800B70E0, &stack_0x08); // [0x800AA560]
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA2C) = ret_800B711C;
    r4 = arg0_r3;
    r3 = &Weapon;
    r3 = cWeapon::Initialize(&Weapon, arg0_r3); // [0x800AF58C]
    r3 = *(uint32_t*)(arg0_r3 + 0xF0);
    r4 = &pl00_ik;
    r3 = InitIk(*(uint32_t*)(arg0_r3 + 0xF0), &pl00_ik); // [0x800990F8]
    r0 = stack_0x24;
    return; // r3 = ret_800B7140
}

// ============================================================================
// High-Level AST Decompilation: MotionMovePl(unsigned long)
// Unit: player.obj | Address: 0x800B7158 | Size: 0x70 bytes
// ============================================================================
/* [0x800B7158] */ void MotionMovePl(unsigned long arg0_r3) {
    // Stack frame allocated: 176 bytes
    stack_0xB4 = r0;
    r9 = SDA1::pG;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B7190;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B7190:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    f1 = *(float*)0x8016CC54;
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    f2 = *(float*)0x8016CC58;
    r3 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r3 = MotionMove(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0), *(float*)0x8016CC54, *(float*)0x8016CC58); // [0x800A2434]
    r3 = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0x3BA);
    r0 = stack_0xB4;
    return; // r3 = *(uint8_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0x3BA)
}

// ============================================================================
// High-Level AST Decompilation: snd_footse_call(cEm *)
// Unit: player.obj | Address: 0x800B71C8 | Size: 0x188 bytes
// ============================================================================
/* [0x800B71C8] */ void snd_footse_call(cEm * arg0_r3) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r31 = arg0_r3;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 6) goto label_800B7290;
    r3 = 0;
    r3 = Snd_footse_call(0); // [0x800CD030]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x6A78);
    if (*(uint32_t*)(SDA1::pG + 0x6A78) != 0x00020000u) goto label_800B733C;
    r4 = 11;
    r3 = 40;
    r3 = EspGetEstAddr(40, 11); // [0x800833A4]
    r29 = 0;
    r30 = ret_800B7210;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B7220;
    r6 = ret_800B7210;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    stack_0x08 = 0;
    r4 = 0;
    r3 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B7210, ret_800B7220, 0, 0, arg0_r3, 0x00020000u); // [0x800906FC]
    r4 = 7;
    r3 = 40;
    r3 = EspGetEstAddr(40, 7); // [0x800833A4]
    r30 = ret_800B7254;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B7260;
    stack_0x08 = 0;
    r3 = arg0_r3;
    r6 = ret_800B7254;
    r4 = arg0_r3 + (192);
    r5 = arg0_r3 + (204);
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, (arg0_r3 + 192), (arg0_r3 + 204), ret_800B7254, ret_800B7260, 0, 0, arg0_r3, 0x00020000u); // [0x800906FC]
    goto label_800B733C;
label_800B7290:;
    if (*(uint32_t*)(SDA1::pG + 0x6A78) != 15) goto label_800B733C;
    r3 = 1;
    r3 = Snd_footse_call(1); // [0x800CD030]
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x6A78);
    if (*(uint32_t*)(SDA1::pG + 0x6A78) != 0x00020000u) goto label_800B733C;
    r4 = 10;
    r3 = 40;
    r3 = EspGetEstAddr(40, 10); // [0x800833A4]
    r29 = 0;
    r30 = ret_800B72C0;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B72D0;
    r6 = ret_800B72C0;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    stack_0x08 = 0;
    r4 = 0;
    r3 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B72C0, ret_800B72D0, 0, 0, arg0_r3, 0x00020000u); // [0x800906FC]
    r4 = 7;
    r3 = 40;
    r3 = EspGetEstAddr(40, 7); // [0x800833A4]
    r30 = ret_800B7304;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B7310;
    stack_0x08 = 0;
    r3 = arg0_r3;
    r6 = ret_800B7304;
    r4 = arg0_r3 + (192);
    r5 = arg0_r3 + (204);
    r8 = 0;
    r9 = 0;
    r10 = arg0_r3;
    r3 = EstSet(arg0_r3, (arg0_r3 + 192), (arg0_r3 + 204), ret_800B7304, ret_800B7310, 0, 0, arg0_r3, 0x00020000u); // [0x800906FC]
label_800B733C:;
    r0 = stack_0x24;
    return; // r3 = ret_800B7338
}

// ============================================================================
// High-Level AST Decompilation: GetModelInfo(cModelInfo *, unsigned long)
// Unit: player.obj | Address: 0x800B7350 | Size: 0x20 bytes
// ============================================================================
/* [0x800B7350] */ void GetModelInfo(cModelInfo * arg0_r3, unsigned long arg1_r4) {
    r9 = arg1_r4 + (-1);
label_800B735C:;
    r3 = *(uint32_t*)(arg0_r3 + 0x4);
    r9 = (arg1_r4 + -1) + (-1);
    if ((arg1_r4 + -1) != 0) goto label_800B735C;
    return; // r3 = *(uint32_t*)(arg0_r3 + 0x4)
}

// ============================================================================
// High-Level AST Decompilation: CameraBehindSet(Vec *, Vec *)
// Unit: player.obj | Address: 0x800B7370 | Size: 0xA4 bytes
// ============================================================================
/* [0x800B7370] */ void CameraBehindSet(Vec * arg0_r3, Vec * arg1_r4) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r29 = arg1_r4;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B73B0;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", arg1_r4); // [0x8013E678]
label_800B73B0:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r8 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    if (arg0_r3 == 0) goto label_800B73DC;
    r10 = *(uint32_t*)(arg0_r3 + 0x0);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (3032);
    r0 = *(uint32_t*)(arg0_r3 + 0x8);
    r9 = *(uint32_t*)(arg0_r3 + 0x4);
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xBD8) = *(uint32_t*)(arg0_r3 + 0x0);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3032) + 0x8) = *(uint32_t*)(arg0_r3 + 0x8);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3032) + 0x4) = *(uint32_t*)(arg0_r3 + 0x4);
label_800B73DC:;
    if (arg1_r4 == 0) goto label_800B7400;
    r10 = *(uint32_t*)(arg1_r4 + 0x0);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (3044);
    r0 = *(uint32_t*)(arg1_r4 + 0x8);
    r9 = *(uint32_t*)(arg1_r4 + 0x4);
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xBE4) = *(uint32_t*)(arg1_r4 + 0x0);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3044) + 0x8) = *(uint32_t*)(arg1_r4 + 0x8);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3044) + 0x4) = *(uint32_t*)(arg1_r4 + 0x4);
label_800B7400:;
    r0 = stack_0x1C;
    return; // r3 = ret_800B73AC
}

// ============================================================================
// High-Level AST Decompilation: CameraBehindSet2(Vec, Vec)
// Unit: player.obj | Address: 0x800B7414 | Size: 0x94 bytes
// ============================================================================
/* [0x800B7414] */ void CameraBehindSet2(Vec arg0_r3, Vec arg1_r4) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r29 = arg1_r4;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B7454;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", arg1_r4); // [0x8013E678]
label_800B7454:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(arg0_r3 + 0x0);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r10 = *(uint32_t*)(arg0_r3 + 0x8);
    r8 = *(uint32_t*)(arg0_r3 + 0x4);
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (3032);
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xBD8) = *(uint32_t*)(arg0_r3 + 0x0);
    r7 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (3044);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3032) + 0x8) = *(uint32_t*)(arg0_r3 + 0x8);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3032) + 0x4) = *(uint32_t*)(arg0_r3 + 0x4);
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    r9 = *(uint32_t*)(arg1_r4 + 0x8);
    r10 = *(uint32_t*)(arg1_r4 + 0x4);
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xBE4) = *(uint32_t*)(arg1_r4 + 0x0);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3044) + 0x8) = *(uint32_t*)(arg1_r4 + 0x8);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3044) + 0x4) = *(uint32_t*)(arg1_r4 + 0x4);
    r0 = stack_0x1C;
    return; // r3 = ret_800B7450
}

// ============================================================================
// High-Level AST Decompilation: CheckAction(cEm *)
// Unit: player.obj | Address: 0x800B74A8 | Size: 0x78 bytes
// ============================================================================
/* [0x800B74A8] */ void CheckAction(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B74E4;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B74E4:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0x5F8);
    if (r0 != 0) goto label_800B7500;
    r3 = 0;
    goto label_800B750C;
label_800B7500:;
    r3 = 1;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01050000u;
label_800B750C:;
    r0 = stack_0x14;
    return; // r3 = 1
}

// ============================================================================
// High-Level AST Decompilation: PlFallCheck(cEm *)
// Unit: player.obj | Address: 0x800B7520 | Size: 0x36C bytes
// ============================================================================
/* [0x800B7520] */ void PlFallCheck(cEm * arg0_r3) {
    // Stack frame allocated: 48 bytes
    stack_0x28 = f31;
    stack_0x34 = r0;
    r9 = SDA1::pG;
    r31 = arg0_r3;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B7560;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B7560:;
    r10 = SDA1::pG;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
    r28 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    r9 = *(uint8_t*)(arg0_r3 + 0xF8);
    if (*(uint8_t*)(arg0_r3 + 0xF8) == 4) goto label_800B7874;
    r0 = *(uint8_t*)(arg0_r3 + 0xF9);
    if (*(uint8_t*)(arg0_r3 + 0xF9) == 7) goto label_800B7874;
    r30 = arg0_r3 + (284);
    r29 = arg0_r3 + (192);
    r3 = (arg0_r3 + 284);
    r4 = (arg0_r3 + 192);
    r3 = GetFloor((arg0_r3 + 284), (arg0_r3 + 192)); // [0x800078EC]
    r0 = *(uint8_t*)(arg0_r3 + 0xF8);
    r3 = (arg0_r3 + 284);
    if (*(uint8_t*)(arg0_r3 + 0xF8) <= 3) goto label_800B75C8;
    if (*(uint8_t*)(arg0_r3 + 0xF8) == 5) goto label_800B777C;
    goto label_800B7874;
label_800B75C8:;
    if (*(uint8_t*)(arg0_r3 + 0xF8) >= 2) goto label_800B777C;
    if (*(uint8_t*)(arg0_r3 + 0xF8) < 0) goto label_800B7874;
    r0 = *(uint8_t*)(arg0_r3 + 0xF9);
    if (*(uint8_t*)(arg0_r3 + 0xF9) > 5) goto label_800B7608;
    if (*(uint8_t*)(arg0_r3 + 0xF9) >= 4) goto label_800B7624;
    if (*(uint8_t*)(arg0_r3 + 0xF9) < 0) goto label_800B7874;
    if (*(uint8_t*)(arg0_r3 + 0xF9) <= 1) goto label_800B7624;
    if (*(uint8_t*)(arg0_r3 + 0xF9) == 2) goto label_800B7654;
    goto label_800B7874;
label_800B7608:;
    if (*(uint8_t*)(arg0_r3 + 0xF9) == 9) goto label_800B7654;
    if (*(uint8_t*)(arg0_r3 + 0xF9) < 9) goto label_800B7874;
    if (*(uint8_t*)(arg0_r3 + 0xF9) > 13) goto label_800B7874;
    if (*(uint8_t*)(arg0_r3 + 0xF9) < 11) goto label_800B7874;
label_800B7624:;
    f1 = *(float*)(arg0_r3 + 0xC4);
    f13 = *(double*)0x8016CC60;
    if (*(uint8_t*)(arg0_r3 + 0xF9) < 11) goto label_800B7798;
    if (*(uint8_t*)(arg0_r3 + 0xF9) >= 11) goto label_800B7874;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x01070000u;
    goto label_800B7874;
label_800B7654:;
    f0 = *(float*)(arg0_r3 + 0xC4);
    f31 = *(double*)0x8016CC60;
    if (*(uint8_t*)(arg0_r3 + 0xF9) < 11) goto label_800B7798;
    r8 = SDA1::pG;
    f12 = *(float*)0x8016CC68;
    r9 = *(uint32_t*)(SDA1::pG + 0x148);
    r10 = &stack_0x08;
    f11 = *(float*)0x8016CC6C;
    r4 = &stack_0x08;
    r9 = *(uint32_t*)(SDA1::pG + 0x148) | 0x0080u;
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
    r0 = *(uint16_t*)(arg0_r3 + 0x45A);
    f13 = *(float*)(arg0_r3 + 0xC4);
    r0 = *(uint16_t*)(arg0_r3 + 0x45A) | 0x0004u;
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    *(float*)(arg0_r3 + 0xC4) = *(float*)(arg0_r3 + 0xC4);
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    r0 = *(uint32_t*)(arg0_r3 + 0xC0);
    f0 = *(float*)(arg0_r3 + 0xC4);
    r11 = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    r9 = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    stack_0x08 = *(uint32_t*)(arg0_r3 + 0xC0);
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    stack_0x0C = *(float*)(arg0_r3 + 0xC4);
    r3 = GetFloor((arg0_r3 + 284), &stack_0x08); // [0x800078EC]
    f13 = *(float*)(arg0_r3 + 0xC4);
    if (*(uint8_t*)(arg0_r3 + 0xF9) >= 11) goto label_800B7734;
    r11 = SDA1::pG;
    f0 = *(float*)0x8016CC70;
    r3 = 2;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CC70;
    *(float*)(arg0_r3 + 0xC4) = *(float*)(arg0_r3 + 0xC4);
    r0 = *(uint16_t*)(arg0_r3 + 0x45A);
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
    r3 = Snd_footse_call(2); // [0x800CD030]
    goto label_800B7770;
label_800B7734:;
    if (*(uint8_t*)(arg0_r3 + 0xF9) >= 11) goto label_800B7770;
    r11 = SDA1::pG;
    f0 = *(float*)0x8016CC70;
    r3 = 2;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CC70;
    *(float*)(arg0_r3 + 0xC4) = *(float*)(arg0_r3 + 0xC4);
    r0 = *(uint16_t*)(arg0_r3 + 0x45A);
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
    r3 = Snd_footse_call(2); // [0x800CD030]
label_800B7770:;
    r3 = arg0_r3;
    r3 = ScrAtCheck(arg0_r3); // [0x80006670]
    goto label_800B7874;
label_800B777C:;
    f0 = *(float*)(arg0_r3 + 0xC4);
    f13 = *(double*)0x8016CC60;
    if (*(uint8_t*)(arg0_r3 + 0xF9) >= 11) goto label_800B77B0;
label_800B7798:;
    r0 = *(uint16_t*)(arg0_r3 + 0x45A);
    if (*(uint8_t*)(arg0_r3 + 0xF9) == 11) goto label_800B7874;
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
    goto label_800B7874;
label_800B77B0:;
    r11 = SDA1::pG;
    f31 = *(float*)0x8016CC70;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    r0 = *(uint32_t*)(SDA1::pG + 0x148) | 0x0080u;
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    if (*(uint8_t*)(arg0_r3 + 0xF9) <= 11) goto label_800B77D8;
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CC70;
label_800B77D8:;
    f13 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    f0 = *(float*)(arg0_r3 + 0xC4);
    f12 = *(float*)0x8016CC68;
    r10 = &stack_0x08;
    f11 = *(float*)0x8016CC6C;
    *(float*)(arg0_r3 + 0xC4) = *(float*)(arg0_r3 + 0xC4);
    r4 = &stack_0x08;
    f0 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    r0 = *(uint32_t*)(arg0_r3 + 0xC0);
    f0 = *(float*)(arg0_r3 + 0x110);
    r11 = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    r9 = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    stack_0x08 = *(uint32_t*)(arg0_r3 + 0xC0);
    *(uint32_t*)(&stack_0x08 + 0x4) = *(uint32_t*)((arg0_r3 + 192) + 0x4);
    *(uint32_t*)(&stack_0x08 + 0x8) = *(uint32_t*)((arg0_r3 + 192) + 0x8);
    stack_0x0C = *(float*)(arg0_r3 + 0x110);
    r3 = GetFloor(ret_800B7774, &stack_0x08); // [0x800078EC]
    f0 = *(float*)(arg0_r3 + 0xC4);
    if (*(uint8_t*)(arg0_r3 + 0xF9) <= 11) goto label_800B786C;
    r9 = SDA1::pG;
    r3 = 2;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
    *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4) = *(float*)0x8016CC70;
    *(float*)(arg0_r3 + 0xC4) = *(float*)(arg0_r3 + 0xC4);
    r0 = *(uint16_t*)(arg0_r3 + 0x45A);
    *(uint16_t*)(arg0_r3 + 0x45A) = *(uint16_t*)(arg0_r3 + 0x45A);
    r3 = Snd_footse_call(2); // [0x800CD030]
label_800B786C:;
    r3 = arg0_r3;
    r3 = ScrAtCheck(arg0_r3); // [0x80006670]
label_800B7874:;
    r0 = stack_0x34;
    f31 = stack_0x28;
    return; // r3 = ret_800B7870
}

// ============================================================================
// High-Level AST Decompilation: PlDamageCk(cEm *)
// Unit: player.obj | Address: 0x800B788C | Size: 0x1BC bytes
// ============================================================================
/* [0x800B788C] */ void PlDamageCk(cEm * arg0_r3) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r29 = 0;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B78CC;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B78CC:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r7 = *(uint32_t*)(arg0_r3 + 0x4F0);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r31 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (*(uint32_t*)(arg0_r3 + 0x4F0) == 0) goto label_800B7A34;
    r9 = SDA1::pG;
    r0 = *(int16_t*)(SDA1::pG + 0x6810);
    if (*(int16_t*)(SDA1::pG + 0x6810) <= 0) goto label_800B7A34;
    r0 = *(uint8_t*)(arg0_r3 + 0x4E1);
    if (*(uint8_t*)(arg0_r3 + 0x4E1) == 0) goto label_800B7908;
    *(uint32_t*)(arg0_r3 + 0x4F0) = 0;
    goto label_800B7A34;
label_800B7908:;
    r11 = *(uint8_t*)(SDA1::pG + 0x681A);
    r10 = &calc_tbl;
    r8 = 0x51EB851Fu;
    r11 = (SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A));
    r9 = *(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689B);
    r9 = *(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689B) + (-1);
    *(uint32_t*)(arg0_r3 + 0x4F0) = *(uint8_t*)(arg0_r3 + 0x4E1);
    if (*(uint8_t*)(arg0_r3 + 0x4E1) != 0) goto label_800B7958;
    r0 = 1;
    *(uint32_t*)(arg0_r3 + 0x4F0) = 1;
label_800B7958:;
    r9 = SDA1::pG;
    r0 = *(uint8_t*)(SDA1::pG + 0x681A);
    if (*(uint8_t*)(SDA1::pG + 0x681A) != 10) goto label_800B7970;
    r0 = 1000;
    *(uint32_t*)(arg0_r3 + 0x4F0) = 1000;
label_800B7970:;
    r11 = SDA1::pG;
    r10 = *(uint16_t*)(arg0_r3 + 0x4F2);
    r3 = &cGaugeWk;
    r0 = *(uint16_t*)(SDA1::pG + 0x6810);
    r9 = *(uint32_t*)(SDA1::pG + 0x148);
    r0 = (*(uint16_t*)(SDA1::pG + 0x6810) - *(uint16_t*)(arg0_r3 + 0x4F2));
    r9 = *(uint32_t*)(SDA1::pG + 0x148) | 0x0004u;
    *(uint16_t*)(SDA1::pG + 0x6810) = (*(uint16_t*)(SDA1::pG + 0x6810) - *(uint16_t*)(arg0_r3 + 0x4F2));
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
    r3 = cGauge::LifeDown(&cGaugeWk); // [0x800974AC]
    r11 = SDA1::pG;
    r0 = *(int16_t*)(SDA1::pG + 0x6810);
    if (*(int16_t*)(SDA1::pG + 0x6810) > 0) goto label_800B79C0;
    r0 = -1;
    *(uint16_t*)(SDA1::pG + 0x6810) = -1;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x03000000u;
    goto label_800B7A1C;
label_800B79C0:;
    r3 = Rnd(); // [0x800C06C4]
    r4 = ret_800B79C0;
    r9 = 0xAAAAAAABu;
    r3 = 0;
    r5 = arg0_r3 + (192);
    r6 = 0;
    r0 = (-1 + 0xAAAAAAABu);
    r4 = (ret_800B79C0 - (-1 + 0xAAAAAAABu));
    r4 = (ret_800B79C0 - (-1 + 0xAAAAAAABu)) + (17);
    r3 = SndSeCall(0, ((ret_800B79C0 - (-1 + 0xAAAAAAABu)) + 17), (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = -32768;
    *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA24) = -32768;
    r9 = *(uint32_t*)(arg0_r3 + 0x4F0);
    if (*(uint32_t*)(arg0_r3 + 0x4F0) <= 399) goto label_800B7A18;
label_800B7A18:;
    *(uint32_t*)(arg0_r3 + 0xF8) = 0x02000000u;
label_800B7A1C:;
    r9 = SDA1::pG;
    r11 = 0;
    r0 = *(int16_t*)(SDA1::pG + 0x6810);
    *(uint32_t*)(arg0_r3 + 0x4F0) = 0;
    *(uint32_t*)(arg0_r3 + 0x4D4) = *(int16_t*)(SDA1::pG + 0x6810);
    *(uint32_t*)(arg0_r3 + 0x4E4) = 0;
label_800B7A34:;
    r0 = stack_0x1C;
    return; // r3 = ret_800B79F8
}

// ============================================================================
// High-Level AST Decompilation: CheckCtrl(cEm *)
// Unit: player.obj | Address: 0x800B7A48 | Size: 0x8C bytes
// ============================================================================
/* [0x800B7A48] */ void CheckCtrl(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B7A80;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B7A80:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r10 = SDA1::pG;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (r0 == 0) goto label_800B7AC0;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x8C);
    if (r0 == 0) goto label_800B7AB0;
    goto label_800B7ABC;
label_800B7AB0:;
    if (r0 == 0) goto label_800B7AC0;
label_800B7ABC:;
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
label_800B7AC0:;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_800B7A7C
}

// ============================================================================
// High-Level AST Decompilation: FallDieCk(cEm *)
// Unit: player.obj | Address: 0x800B7AD4 | Size: 0xCC bytes
// ============================================================================
/* [0x800B7AD4] */ void FallDieCk(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B7B10;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B7B10:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r10 = SDA1::pG;
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r8 = *(uint32_t*)(SDA1::pG + 0x150);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    if (r0 != 0) goto label_800B7B8C;
    f13 = *(float*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x6C4);
    f0 = *(float*)0x8016CC74;
    if (r0 >= 0) goto label_800B7B58;
    r0 = *(uint32_t*)(SDA1::pG + 0x128);
    *(uint32_t*)(SDA1::pG + 0x150) = 0x80170000u;
    *(uint32_t*)(SDA1::pG + 0x128) = *(uint32_t*)(SDA1::pG + 0x128);
    goto label_800B7B8C;
label_800B7B58:;
    f0 = *(float*)0x8016CC78;
    if (r0 >= 0) goto label_800B7B8C;
    r0 = -1;
    *(uint16_t*)(SDA1::pG + 0x6810) = -1;
    r9 = -1;
    *(uint32_t*)(SDA1::pG + 0x150) = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388);
    *(uint32_t*)(arg0_r3 + 0x4D4) = -1;
    r3 = &cGaugeWk;
    r3 = cGauge::LifeDown(&cGaugeWk); // [0x800974AC]
label_800B7B8C:;
    r0 = stack_0x14;
    return; // r3 = ret_800B7B88
}

// ============================================================================
// High-Level AST Decompilation: SetTarget00(void)
// Unit: player.obj | Address: 0x800B7BA0 | Size: 0x134 bytes
// ============================================================================
/* [0x800B7BA0] */ void SetTarget00(void) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r9 = SDA1::pG;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B7BD8;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B7BD8:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r4 = 0;
    r5 = 28;
    r29 = 0;
    r28 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (3796);
    r31 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    r3 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3796);
    r3 = memset(); // [0x800E8A5C]
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B7C10;
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xED4) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    r29 = 1;
label_800B7C10:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) == 0) goto label_800B7C28;
    r29 = 1 + (1);
label_800B7C28:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950) == 0) goto label_800B7C40;
    r29 = (1 + 1) + (1);
label_800B7C40:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x954);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x954) == 0) goto label_800B7C58;
    r29 = ((1 + 1) + 1) + (1);
label_800B7C58:;
    if ((((1 + 1) + 1) + 1) == 2) goto label_800B7CA0;
    if ((((1 + 1) + 1) + 1) > 0x2u) goto label_800B7C74;
    if ((((1 + 1) + 1) + 1) == 1) goto label_800B7C80;
    goto label_800B7CBC;
label_800B7C74:;
    if ((((1 + 1) + 1) + 1) == 3) goto label_800B7CB4;
    goto label_800B7CBC;
label_800B7C80:;
    r0 = 3;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (3800);
label_800B7C8C:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3800) + 0x0) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3800) + (4);
    if ((((1 + 1) + 1) + 1) >= 3) goto label_800B7C8C;
    goto label_800B7CBC;
label_800B7CA0:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3796) + 0x8) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3796) + 0xC) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C);
    goto label_800B7CBC;
label_800B7CB4:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3796) + 0xC) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
label_800B7CBC:;
    r3 = (((1 + 1) + 1) + 1);
    r0 = stack_0x1C;
    return; // r3 = (((1 + 1) + 1) + 1)
}

// ============================================================================
// High-Level AST Decompilation: SpecialAtck00(cEm *)
// Unit: player.obj | Address: 0x800B7CD4 | Size: 0x3D8 bytes
// ============================================================================
/* [0x800B7CD4] */ void SpecialAtck00(cEm * arg0_r3) {
    // Stack frame allocated: 72 bytes
    stack_0x40 = f31;
    stack_0x4C = r0;
    stack_0x2C = r12;
    r9 = SDA1::pG;
    r29 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B7D1C;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B7D1C:;
    r11 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    f31 = *(float*)0x8016CC7C;
    r31 = &stack_0x08;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r4 = 24;
    stack_0x08 = *(float*)0x8016CC7C;
    r28 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    r3 = *(uint32_t*)(arg0_r3 + 0xF0);
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x8016CC7C;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x8016CC7C;
    r3 = GetPartsAddr(*(uint32_t*)(arg0_r3 + 0xF0), 24); // [0x800A0BD4]
    f13 = *(float*)(ret_800B7D48 + 0xCC);
    r3 = ret_800B7D48 + (204);
    stack_0x08 = *(float*)(ret_800B7D48 + 0xCC);
    f0 = *(float*)((ret_800B7D48 + 204) + 0x4);
    *(float*)(&stack_0x08 + 0x4) = *(float*)((ret_800B7D48 + 204) + 0x4);
    f13 = *(float*)((ret_800B7D48 + 204) + 0x8);
    *(float*)(&stack_0x08 + 0x8) = *(float*)((ret_800B7D48 + 204) + 0x8);
    r3 = SetTarget00(); // [0x800B7BA0]
    if (ret_800B7D68 == 0) goto label_800B7F08;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    r30 = &stack_0x18;
    r3 = arg0_r3;
    r4 = 24;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968) + 0x125);
    r5 = 11;
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 24, 11, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968) + 0x125)); // [0x800105E8]
    f0 = *(float*)0x8016CC80;
    stack_0x18 = *(float*)0x8016CC80;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CC7C;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CC7C;
    if (&stack_0x08 == &stack_0x18) goto label_800B7DCC;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    f0 = stack_0x20;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B7DCC:;
    if (ret_800B7D94 == 0) goto label_800B7DDC;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B7D94, &stack_0x08); // [0x8000EC28]
label_800B7DDC:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C);
    r3 = arg0_r3;
    r4 = 24;
    r5 = 11;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C) + 0x125);
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 24, 11, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C) + 0x125)); // [0x800105E8]
    stack_0x18 = *(float*)0x8016CC7C;
    f0 = *(float*)0x8016CC84;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CC7C;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CC84;
    if (ret_800B7D94 == 0) goto label_800B7E2C;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    f0 = stack_0x20;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B7E2C:;
    if (ret_800B7DF8 == 0) goto label_800B7E3C;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B7DF8, &stack_0x08); // [0x8000EC28]
label_800B7E3C:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x970);
    r3 = arg0_r3;
    r4 = 24;
    r5 = 11;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x970) + 0x125);
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 24, 11, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x970), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x970) + 0x125)); // [0x800105E8]
    f13 = *(float*)0x8016CC88;
    f0 = *(float*)0x8016CC8C;
    stack_0x18 = *(float*)0x8016CC88;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CC8C;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CC7C;
    if (ret_800B7DF8 == 0) goto label_800B7E94;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    f0 = stack_0x20;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B7E94:;
    if (ret_800B7E58 == 0) goto label_800B7EA4;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B7E58, &stack_0x08); // [0x8000EC28]
label_800B7EA4:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x974);
    r3 = arg0_r3;
    r4 = 24;
    r5 = 11;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x974) + 0x125);
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 24, 11, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x974), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x974) + 0x125)); // [0x800105E8]
    f0 = *(float*)0x8016CC90;
    stack_0x18 = *(float*)0x8016CC90;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CC7C;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CC7C;
    if (ret_800B7E58 == 0) goto label_800B7EF4;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    f0 = stack_0x20;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B7EF4:;
    if (ret_800B7EC0 == 0) goto label_800B8078;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B7EC0, &stack_0x08); // [0x8000EC28]
    goto label_800B8078;
label_800B7F08:;
    r30 = &stack_0x18;
    r9 = 0;
    r3 = arg0_r3;
    r4 = 24;
    r5 = 11;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 24, 11, 0, 0, 0, 0); // [0x800105E8]
    f0 = *(float*)0x8016CC80;
    stack_0x18 = *(float*)0x8016CC80;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CC7C;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CC7C;
    if (&stack_0x08 == &stack_0x18) goto label_800B7F60;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    f0 = stack_0x20;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B7F60:;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B7F28, &stack_0x08); // [0x8000EC28]
    r9 = 0;
    r3 = arg0_r3;
    r4 = 24;
    r5 = 11;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 24, 11, 0, 0, 0, 0); // [0x800105E8]
    stack_0x18 = *(float*)0x8016CC7C;
    f0 = *(float*)0x8016CC84;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CC7C;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CC84;
    if (&stack_0x08 == &stack_0x18) goto label_800B7FB8;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    f0 = stack_0x20;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B7FB8:;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B7F84, &stack_0x08); // [0x8000EC28]
    r9 = 0;
    r3 = arg0_r3;
    r4 = 24;
    r5 = 11;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 24, 11, 0, 0, 0, 0); // [0x800105E8]
    f13 = *(float*)0x8016CC88;
    f0 = *(float*)0x8016CC8C;
    stack_0x18 = *(float*)0x8016CC88;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CC8C;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CC7C;
    if (&stack_0x08 == &stack_0x18) goto label_800B8018;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    f0 = stack_0x20;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B8018:;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B7FDC, &stack_0x08); // [0x8000EC28]
    r9 = 0;
    r3 = arg0_r3;
    r4 = 24;
    r5 = 11;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 24, 11, 0, 0, 0, 0); // [0x800105E8]
    f0 = *(float*)0x8016CC90;
    stack_0x18 = *(float*)0x8016CC90;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CC7C;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CC7C;
    if (&stack_0x08 == &stack_0x18) goto label_800B8070;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    f0 = stack_0x20;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B8070:;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B803C, &stack_0x08); // [0x8000EC28]
label_800B8078:;
    r5 = arg0_r3 + (192);
    r3 = 5;
    r4 = 3;
    r6 = 0;
    r3 = SndSeCall(5, 3, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = stack_0x4C;
    r12 = stack_0x2C;
    f31 = stack_0x40;
    return; // r3 = ret_800B8088
}

// ============================================================================
// High-Level AST Decompilation: SetTarget10(void)
// Unit: player.obj | Address: 0x800B80AC | Size: 0x1C4 bytes
// ============================================================================
/* [0x800B80AC] */ void SetTarget10(void) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r9 = SDA1::pG;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B80E4;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B80E4:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r4 = 0;
    r5 = 28;
    r29 = 0;
    r28 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (3796);
    r31 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    r3 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3796);
    r3 = memset(); // [0x800E8A5C]
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B811C;
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 0xED4) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    r29 = 1;
label_800B811C:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) == 0) goto label_800B8134;
    r29 = 1 + (1);
label_800B8134:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950) == 0) goto label_800B814C;
    r29 = (1 + 1) + (1);
label_800B814C:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x954);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x954) == 0) goto label_800B8164;
    r29 = ((1 + 1) + 1) + (1);
label_800B8164:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x958);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x958) == 0) goto label_800B817C;
    r29 = (((1 + 1) + 1) + 1) + (1);
label_800B817C:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x95C);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x95C) == 0) goto label_800B8194;
    r29 = ((((1 + 1) + 1) + 1) + 1) + (1);
label_800B8194:;
    if ((((((1 + 1) + 1) + 1) + 1) + 1) == 3) goto label_800B8214;
    if ((((((1 + 1) + 1) + 1) + 1) + 1) > 0x3u) goto label_800B81B8;
    if ((((((1 + 1) + 1) + 1) + 1) + 1) == 1) goto label_800B81CC;
    if ((((((1 + 1) + 1) + 1) + 1) + 1) == 2) goto label_800B81EC;
    goto label_800B8258;
label_800B81B8:;
    if ((((((1 + 1) + 1) + 1) + 1) + 1) == 5) goto label_800B8250;
    if ((((((1 + 1) + 1) + 1) + 1) + 1) < 0x5u) goto label_800B822C;
    goto label_800B8258;
label_800B81CC:;
    r0 = 5;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (3800);
label_800B81D8:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3800) + 0x0) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3800) + (4);
    if ((((((1 + 1) + 1) + 1) + 1) + 1) >= 0x5u) goto label_800B81D8;
    goto label_800B8258;
label_800B81EC:;
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    r11 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2408);
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 2408) + 0x8) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C);
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 2408) + 0xC) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C);
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 2408) + 0x10) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C);
    *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 2408) + 0x14) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C);
    goto label_800B8258;
label_800B8214:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3796) + 0xC) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C);
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3796) + 0x10) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C);
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x970);
    goto label_800B8254;
label_800B822C:;
    r11 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    r10 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + (2408);
    r0 = (((((1 + 1) + 1) + 1) + 1) + 1) + (1);
    r9 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C);
    goto label_800B8258;
label_800B8250:;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
label_800B8254:;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3796) + 0x14) = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
label_800B8258:;
    r3 = (((((1 + 1) + 1) + 1) + 1) + 1);
    r0 = stack_0x1C;
    return; // r3 = (((((1 + 1) + 1) + 1) + 1) + 1)
}

// ============================================================================
// High-Level AST Decompilation: SpecialAtck10(cEm *)
// Unit: player.obj | Address: 0x800B8270 | Size: 0x598 bytes
// ============================================================================
/* [0x800B8270] */ void SpecialAtck10(cEm * arg0_r3) {
    // Stack frame allocated: 88 bytes
    stack_0x48 = f30;
    stack_0x50 = f31;
    stack_0x5C = r0;
    stack_0x30 = r12;
    r9 = SDA1::pG;
    r29 = arg0_r3;
    r27 = 0;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B82C0;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B82C0:;
    r11 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    f31 = *(float*)0x8016CC94;
    r31 = &stack_0x10;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r4 = 43;
    stack_0x10 = *(float*)0x8016CC94;
    r3 = 40;
    r28 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    *(float*)(&stack_0x10 + 0x4) = *(float*)0x8016CC94;
    *(float*)(&stack_0x10 + 0x8) = *(float*)0x8016CC94;
    r3 = EspGetEstAddr(40, 43); // [0x800833A4]
    r30 = ret_800B82EC;
    r3 = 40;
    r3 = EspGetEffAddr(40); // [0x800834AC]
    r7 = ret_800B82F8;
    r10 = arg0_r3;
    stack_0x08 = 0;
    r6 = ret_800B82EC;
    r5 = 0;
    r8 = 0;
    r9 = 0;
    r4 = 0;
    r3 = arg0_r3;
    r3 = EstSet(arg0_r3, 0, 0, ret_800B82EC, ret_800B82F8, 0, 0, arg0_r3, *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0)); // [0x800906FC]
    r3 = *(uint32_t*)(arg0_r3 + 0xF0);
    r4 = 24;
    r3 = GetPartsAddr(*(uint32_t*)(arg0_r3 + 0xF0), 24); // [0x800A0BD4]
    f13 = *(float*)(ret_800B832C + 0xCC);
    r3 = ret_800B832C + (204);
    stack_0x10 = *(float*)(ret_800B832C + 0xCC);
    f0 = *(float*)((ret_800B832C + 204) + 0x4);
    *(float*)(&stack_0x10 + 0x4) = *(float*)((ret_800B832C + 204) + 0x4);
    f13 = *(float*)((ret_800B832C + 204) + 0x8);
    *(float*)(&stack_0x10 + 0x8) = *(float*)((ret_800B832C + 204) + 0x8);
    r3 = SetTarget10(); // [0x800B80AC]
    if (ret_800B834C == 0) goto label_800B85B0;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968);
    r30 = &stack_0x20;
    r3 = arg0_r3;
    r4 = 24;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968) + 0x125);
    r5 = 12;
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 24, 12, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x968) + 0x125)); // [0x800105E8]
    f0 = *(float*)0x8016CC98;
    stack_0x20 = *(float*)0x8016CC98;
    *(float*)(&stack_0x20 + 0x4) = *(float*)0x8016CC94;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    if (&stack_0x10 == &stack_0x20) goto label_800B83B0;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B83B0:;
    if (ret_800B8378 == 0) goto label_800B83C0;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B8378, &stack_0x10); // [0x8000EC28]
label_800B83C0:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C);
    r3 = arg0_r3;
    r4 = 24;
    r5 = 13;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C) + 0x125);
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 24, 13, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x96C) + 0x125)); // [0x800105E8]
    stack_0x20 = *(float*)0x8016CC94;
    f0 = *(float*)0x8016CC9C;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    *(float*)(&stack_0x20 + 0x4) = *(float*)0x8016CC9C;
    if (ret_800B8378 == 0) goto label_800B8410;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B8410:;
    if (ret_800B83DC == 0) goto label_800B8420;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B83DC, &stack_0x10); // [0x8000EC28]
label_800B8420:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x970);
    r3 = arg0_r3;
    r4 = 24;
    r5 = 13;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x970) + 0x125);
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 24, 13, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x970), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x970) + 0x125)); // [0x800105E8]
    f13 = *(float*)0x8016CCA0;
    f0 = *(float*)0x8016CCA4;
    stack_0x20 = *(float*)0x8016CCA0;
    *(float*)(&stack_0x20 + 0x4) = *(float*)0x8016CCA4;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    if (ret_800B83DC == 0) goto label_800B8478;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B8478:;
    if (ret_800B843C == 0) goto label_800B8488;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B843C, &stack_0x10); // [0x8000EC28]
label_800B8488:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x974);
    r3 = arg0_r3;
    r4 = 24;
    r5 = 13;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x974) + 0x125);
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 24, 13, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x974), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x974) + 0x125)); // [0x800105E8]
    f30 = *(float*)0x8016CCA8;
    stack_0x20 = *(float*)0x8016CCA8;
    *(float*)(&stack_0x20 + 0x4) = *(float*)0x8016CC94;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    if (ret_800B843C == 0) goto label_800B84D8;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B84D8:;
    if (ret_800B84A4 == 0) goto label_800B84E8;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B84A4, &stack_0x10); // [0x8000EC28]
label_800B84E8:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x978);
    r3 = arg0_r3;
    r4 = 24;
    r5 = 13;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x978) + 0x125);
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 24, 13, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x978), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x978) + 0x125)); // [0x800105E8]
    r27 = *(uint32_t*)0x8016CCAC;
    stack_0x20 = *(uint32_t*)0x8016CCAC;
    *(float*)(&stack_0x20 + 0x4) = *(float*)0x8016CCA8;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    if (ret_800B84A4 == 0) goto label_800B8538;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B8538:;
    if (ret_800B8504 == 0) goto label_800B8548;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B8504, &stack_0x10); // [0x8000EC28]
label_800B8548:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x97C);
    r3 = arg0_r3;
    r4 = 24;
    r5 = 13;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x97C) + 0x125);
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 24, 13, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x97C), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x97C) + 0x125)); // [0x800105E8]
    stack_0x20 = *(uint32_t*)0x8016CCAC;
    f0 = *(float*)0x8016CCB0;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    *(float*)(&stack_0x20 + 0x4) = *(float*)0x8016CCB0;
    if (&stack_0x10 == &stack_0x20) goto label_800B859C;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B859C:;
    if (ret_800B8564 == 0) goto label_800B87D0;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B8564, &stack_0x10); // [0x8000EC28]
    goto label_800B87D0;
label_800B85B0:;
    r30 = &stack_0x20;
    r9 = 0;
    r3 = arg0_r3;
    r4 = 24;
    r5 = 12;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 24, 12, 0, 0, 0, 0); // [0x800105E8]
    f0 = *(float*)0x8016CC98;
    stack_0x20 = *(float*)0x8016CC98;
    *(float*)(&stack_0x20 + 0x4) = *(float*)0x8016CC94;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    if (&stack_0x10 == &stack_0x20) goto label_800B8608;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B8608:;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B85D0, &stack_0x10); // [0x8000EC28]
    r9 = 0;
    r3 = arg0_r3;
    r4 = 24;
    r5 = 13;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 24, 13, 0, 0, 0, 0); // [0x800105E8]
    stack_0x20 = *(float*)0x8016CC94;
    f0 = *(float*)0x8016CC9C;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    *(float*)(&stack_0x20 + 0x4) = *(float*)0x8016CC9C;
    if (&stack_0x10 == &stack_0x20) goto label_800B8660;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B8660:;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B862C, &stack_0x10); // [0x8000EC28]
    r9 = 0;
    r3 = arg0_r3;
    r4 = 24;
    r5 = 13;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 24, 13, 0, 0, 0, 0); // [0x800105E8]
    f13 = *(float*)0x8016CCA0;
    f0 = *(float*)0x8016CCA4;
    stack_0x20 = *(float*)0x8016CCA0;
    *(float*)(&stack_0x20 + 0x4) = *(float*)0x8016CCA4;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    if (&stack_0x10 == &stack_0x20) goto label_800B86C0;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B86C0:;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B8684, &stack_0x10); // [0x8000EC28]
    r9 = 0;
    r3 = arg0_r3;
    r4 = 24;
    r5 = 13;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 24, 13, 0, 0, 0, 0); // [0x800105E8]
    r27 = *(uint32_t*)0x8016CCA8;
    stack_0x20 = *(uint32_t*)0x8016CCA8;
    *(float*)(&stack_0x20 + 0x4) = *(float*)0x8016CC94;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    if (&stack_0x10 == &stack_0x20) goto label_800B8718;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B8718:;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B86E4, &stack_0x10); // [0x8000EC28]
    r9 = 0;
    r3 = arg0_r3;
    r4 = 24;
    r5 = 13;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 24, 13, 0, 0, 0, 0); // [0x800105E8]
    r28 = *(uint32_t*)0x8016CCAC;
    stack_0x20 = *(uint32_t*)0x8016CCAC;
    *(uint32_t*)(&stack_0x20 + 0x4) = *(uint32_t*)0x8016CCA8;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    if (&stack_0x10 == &stack_0x20) goto label_800B8770;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B8770:;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B873C, &stack_0x10); // [0x8000EC28]
    r9 = 0;
    r3 = arg0_r3;
    r4 = 24;
    r5 = 13;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 24, 13, 0, 0, 0, 0); // [0x800105E8]
    stack_0x20 = *(uint32_t*)0x8016CCAC;
    f0 = *(float*)0x8016CCB0;
    *(float*)(&stack_0x20 + 0x8) = *(float*)0x8016CC94;
    *(float*)(&stack_0x20 + 0x4) = *(float*)0x8016CCB0;
    if (&stack_0x10 == &stack_0x20) goto label_800B87C8;
    f0 = stack_0x20;
    f13 = stack_0x24;
    stack_0x10 = stack_0x20;
    *(float*)(&stack_0x10 + 0x4) = stack_0x24;
    f0 = stack_0x28;
    *(float*)(&stack_0x10 + 0x8) = stack_0x28;
label_800B87C8:;
    r4 = &stack_0x10;
    r3 = Blt03DirAdd(ret_800B8794, &stack_0x10); // [0x8000EC28]
label_800B87D0:;
    r5 = arg0_r3 + (192);
    r3 = 5;
    r4 = 3;
    r6 = 0;
    r3 = SndSeCall(5, 3, (arg0_r3 + 192), 0); // [0x800CB7DC]
    r0 = stack_0x5C;
    r12 = stack_0x30;
    f30 = stack_0x48;
    f31 = stack_0x50;
    return; // r3 = ret_800B87E0
}

// ============================================================================
// High-Level AST Decompilation: SpecialAtck01(cEm *)
// Unit: player.obj | Address: 0x800B8808 | Size: 0x14C bytes
// ============================================================================
/* [0x800B8808] */ void SpecialAtck01(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B8844;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B8844:;
    r11 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r7 = 0;
    r8 = 0;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r31 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (3768);
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (3144);
    goto label_800B886C;
label_800B8864:;
    r9 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3144) + (12);
    r7 = 0 + (1);
label_800B886C:;
    r0 = *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C);
    if ((0 + 1) > *(uint16_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x85C)) goto label_800B889C;
    r0 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    r10 = *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3144) + 12) + 0x0);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3144) + 12) + 0x0)) goto label_800B8894;
    *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3768) + 0x0) = *(uint32_t*)(((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3144) + 12) + 0x0);
    r8 = 0 + (1);
    r11 = (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 3768) + (4);
label_800B8894:;
    if ((0 + 1) <= 0) goto label_800B8864;
label_800B889C:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B88C8;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125);
    r3 = arg0_r3;
    r4 = 39;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r3 = Blt04Set(arg0_r3, 39, 0, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125)); // [0x80011398]
    goto label_800B88E8;
label_800B88C8:;
    r3 = arg0_r3;
    r4 = 39;
    r5 = 0;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r9 = 0;
    r3 = Blt04Set(arg0_r3, 39, 0, 0, 0, 0, 0); // [0x80011398]
label_800B88E8:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) != 0) goto label_800B8900;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B8920;
label_800B8900:;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125);
    r3 = arg0_r3;
    r4 = 38;
    r5 = 1;
    r6 = 0;
    r7 = 0;
    r3 = Blt04Set(arg0_r3, 38, 1, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125)); // [0x80011398]
    goto label_800B8940;
label_800B8920:;
    r3 = arg0_r3;
    r4 = 38;
    r5 = 1;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r9 = 0;
    r3 = Blt04Set(arg0_r3, 38, 1, 0, 0, 0, 0); // [0x80011398]
label_800B8940:;
    r0 = stack_0x14;
    return; // r3 = ret_800B893C
}

// ============================================================================
// High-Level AST Decompilation: SpecialAtck11(cEm *)
// Unit: player.obj | Address: 0x800B8954 | Size: 0x100 bytes
// ============================================================================
/* [0x800B8954] */ void SpecialAtck11(cEm * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B8990;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B8990:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r11 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r31 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B89C8;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125);
    r3 = arg0_r3;
    r4 = 39;
    r5 = 2;
    r6 = 0;
    r7 = 0;
    r3 = Blt04Set(arg0_r3, 39, 2, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125)); // [0x80011398]
    goto label_800B89E8;
label_800B89C8:;
    r3 = arg0_r3;
    r4 = 39;
    r5 = 2;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r9 = 0;
    r3 = Blt04Set(arg0_r3, 39, 2, 0, 0, 0, 0); // [0x80011398]
label_800B89E8:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) != 0) goto label_800B8A00;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B8A20;
label_800B8A00:;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125);
    r3 = arg0_r3;
    r4 = 38;
    r5 = 3;
    r6 = 0;
    r7 = 0;
    r3 = Blt04Set(arg0_r3, 38, 3, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125)); // [0x80011398]
    goto label_800B8A40;
label_800B8A20:;
    r3 = arg0_r3;
    r4 = 38;
    r5 = 3;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r9 = 0;
    r3 = Blt04Set(arg0_r3, 38, 3, 0, 0, 0, 0); // [0x80011398]
label_800B8A40:;
    r0 = stack_0x14;
    return; // r3 = ret_800B8A3C
}

// ============================================================================
// High-Level AST Decompilation: SpecialAtck02(cEm *)
// Unit: player.obj | Address: 0x800B8A54 | Size: 0x29C bytes
// ============================================================================
/* [0x800B8A54] */ void SpecialAtck02(cEm * arg0_r3) {
    // Stack frame allocated: 64 bytes
    stack_0x38 = f31;
    stack_0x44 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B8A94;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B8A94:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    f31 = *(float*)0x8016CCB4;
    r11 = &stack_0x08;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r31 = &stack_0x08;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    stack_0x08 = *(float*)0x8016CCB4;
    r29 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x8016CCB4;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x8016CCB4;
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 90) goto label_800B8CD8;
    r3 = *(uint32_t*)(arg0_r3 + 0xF0);
    r4 = 1;
    r3 = GetPartsAddr(*(uint32_t*)(arg0_r3 + 0xF0), 1); // [0x800A0BD4]
    f13 = *(float*)(ret_800B8AD0 + 0xCC);
    r3 = ret_800B8AD0 + (204);
    stack_0x08 = *(float*)(ret_800B8AD0 + 0xCC);
    f0 = *(float*)((ret_800B8AD0 + 204) + 0x4);
    *(float*)(&stack_0x08 + 0x4) = *(float*)((ret_800B8AD0 + 204) + 0x4);
    f13 = *(float*)((ret_800B8AD0 + 204) + 0x8);
    *(float*)(&stack_0x08 + 0x8) = *(float*)((ret_800B8AD0 + 204) + 0x8);
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B8B1C;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125);
    r3 = arg0_r3;
    r4 = 1;
    r5 = 14;
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 1, 14, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125)); // [0x800105E8]
    goto label_800B8B84;
label_800B8B1C:;
    r9 = 0;
    r3 = arg0_r3;
    r4 = 1;
    r5 = 14;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 1, 14, 0, 0, 0, 0); // [0x800105E8]
    r11 = &stack_0x18;
    f0 = *(float*)0x8016CCB8;
    stack_0x18 = *(float*)0x8016CCB8;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CCB4;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CCB4;
    if (&stack_0x08 == &stack_0x18) goto label_800B8B74;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    f12 = stack_0x20;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B8B74:;
    if (ret_800B8B38 == 0) goto label_800B8B84;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B8B38, &stack_0x08); // [0x8000EC28]
label_800B8B84:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) == 0) goto label_800B8BB0;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) + 0x125);
    r3 = arg0_r3;
    r4 = 1;
    r5 = 14;
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 1, 14, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) + 0x125)); // [0x800105E8]
    goto label_800B8C20;
label_800B8BB0:;
    r9 = 0;
    r3 = arg0_r3;
    r4 = 1;
    r5 = 14;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 1, 14, 0, 0, 0, 0); // [0x800105E8]
    f13 = *(float*)0x8016CCB4;
    r9 = &stack_0x18;
    f0 = *(float*)0x8016CCBC;
    stack_0x18 = *(float*)0x8016CCB4;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CCBC;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CCB4;
    if (&stack_0x08 == &stack_0x18) goto label_800B8C10;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    f12 = stack_0x20;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B8C10:;
    if (ret_800B8BCC == 0) goto label_800B8C20;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B8BCC, &stack_0x08); // [0x8000EC28]
label_800B8C20:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950) == 0) goto label_800B8C4C;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950) + 0x125);
    r3 = arg0_r3;
    r4 = 1;
    r5 = 14;
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 1, 14, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950) + 0x125)); // [0x800105E8]
    goto label_800B8CC4;
label_800B8C4C:;
    r9 = 0;
    r3 = arg0_r3;
    r4 = 1;
    r5 = 14;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 1, 14, 0, 0, 0, 0); // [0x800105E8]
    f13 = *(float*)0x8016CCC0;
    f12 = *(float*)0x8016CCC4;
    r9 = &stack_0x18;
    f0 = *(float*)0x8016CCB4;
    stack_0x18 = *(float*)0x8016CCC0;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CCC4;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CCB4;
    if (&stack_0x08 == &stack_0x18) goto label_800B8CB4;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    f12 = stack_0x20;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B8CB4:;
    if (ret_800B8C68 == 0) goto label_800B8CC4;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B8C68, &stack_0x08); // [0x8000EC28]
label_800B8CC4:;
    r5 = arg0_r3 + (192);
    r3 = 5;
    r4 = 3;
    r6 = 0;
    r3 = SndSeCall(5, 3, (arg0_r3 + 192), 0); // [0x800CB7DC]
label_800B8CD8:;
    r0 = stack_0x44;
    f31 = stack_0x38;
    return; // r3 = ret_800B8CD4
}

// ============================================================================
// High-Level AST Decompilation: SpecialAtck12(cEm *)
// Unit: player.obj | Address: 0x800B8CF0 | Size: 0x29C bytes
// ============================================================================
/* [0x800B8CF0] */ void SpecialAtck12(cEm * arg0_r3) {
    // Stack frame allocated: 64 bytes
    stack_0x38 = f31;
    stack_0x44 = r0;
    r9 = SDA1::pG;
    r30 = arg0_r3;
    r31 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B8D30;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B8D30:;
    r10 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    f31 = *(float*)0x8016CCC8;
    r11 = &stack_0x08;
    r9 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r31 = &stack_0x08;
    r0 = *(uint16_t*)(arg0_r3 + 0x42C);
    stack_0x08 = *(float*)0x8016CCC8;
    r29 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    *(float*)(&stack_0x08 + 0x4) = *(float*)0x8016CCC8;
    *(float*)(&stack_0x08 + 0x8) = *(float*)0x8016CCC8;
    if (*(uint16_t*)(arg0_r3 + 0x42C) != 90) goto label_800B8F74;
    r3 = *(uint32_t*)(arg0_r3 + 0xF0);
    r4 = 1;
    r3 = GetPartsAddr(*(uint32_t*)(arg0_r3 + 0xF0), 1); // [0x800A0BD4]
    f13 = *(float*)(ret_800B8D6C + 0xCC);
    r3 = ret_800B8D6C + (204);
    stack_0x08 = *(float*)(ret_800B8D6C + 0xCC);
    f0 = *(float*)((ret_800B8D6C + 204) + 0x4);
    *(float*)(&stack_0x08 + 0x4) = *(float*)((ret_800B8D6C + 204) + 0x4);
    f13 = *(float*)((ret_800B8D6C + 204) + 0x8);
    *(float*)(&stack_0x08 + 0x8) = *(float*)((ret_800B8D6C + 204) + 0x8);
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) == 0) goto label_800B8DB8;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125);
    r3 = arg0_r3;
    r4 = 1;
    r5 = 15;
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 1, 15, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x48) + 0x125)); // [0x800105E8]
    goto label_800B8E20;
label_800B8DB8:;
    r9 = 0;
    r3 = arg0_r3;
    r4 = 1;
    r5 = 15;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 1, 15, 0, 0, 0, 0); // [0x800105E8]
    r11 = &stack_0x18;
    f0 = *(float*)0x8016CCCC;
    stack_0x18 = *(float*)0x8016CCCC;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CCC8;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CCC8;
    if (&stack_0x08 == &stack_0x18) goto label_800B8E10;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    f12 = stack_0x20;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B8E10:;
    if (ret_800B8DD4 == 0) goto label_800B8E20;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B8DD4, &stack_0x08); // [0x8000EC28]
label_800B8E20:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) == 0) goto label_800B8E4C;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) + 0x125);
    r3 = arg0_r3;
    r4 = 1;
    r5 = 15;
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 1, 15, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x94C) + 0x125)); // [0x800105E8]
    goto label_800B8EBC;
label_800B8E4C:;
    r9 = 0;
    r3 = arg0_r3;
    r4 = 1;
    r5 = 15;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 1, 15, 0, 0, 0, 0); // [0x800105E8]
    f13 = *(float*)0x8016CCC8;
    r9 = &stack_0x18;
    f0 = *(float*)0x8016CCD0;
    stack_0x18 = *(float*)0x8016CCC8;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CCD0;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CCC8;
    if (&stack_0x08 == &stack_0x18) goto label_800B8EAC;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    f12 = stack_0x20;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B8EAC:;
    if (ret_800B8E68 == 0) goto label_800B8EBC;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B8E68, &stack_0x08); // [0x8000EC28]
label_800B8EBC:;
    r8 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950) == 0) goto label_800B8EE8;
    r9 = *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950) + 0x125);
    r3 = arg0_r3;
    r4 = 1;
    r5 = 15;
    r6 = 0;
    r7 = 0;
    r3 = Blt03Set(arg0_r3, 1, 15, 0, 0, *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950), *(uint8_t*)(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0x950) + 0x125)); // [0x800105E8]
    goto label_800B8F60;
label_800B8EE8:;
    r9 = 0;
    r3 = arg0_r3;
    r4 = 1;
    r5 = 15;
    r6 = 0;
    r7 = 0;
    r8 = 0;
    r3 = Blt03Set(arg0_r3, 1, 15, 0, 0, 0, 0); // [0x800105E8]
    f13 = *(float*)0x8016CCD4;
    f12 = *(float*)0x8016CCD8;
    r9 = &stack_0x18;
    f0 = *(float*)0x8016CCC8;
    stack_0x18 = *(float*)0x8016CCD4;
    *(float*)(&stack_0x18 + 0x4) = *(float*)0x8016CCD8;
    *(float*)(&stack_0x18 + 0x8) = *(float*)0x8016CCC8;
    if (&stack_0x08 == &stack_0x18) goto label_800B8F50;
    f0 = stack_0x18;
    f13 = stack_0x1C;
    f12 = stack_0x20;
    stack_0x08 = stack_0x18;
    *(float*)(&stack_0x08 + 0x4) = stack_0x1C;
    *(float*)(&stack_0x08 + 0x8) = stack_0x20;
label_800B8F50:;
    if (ret_800B8F04 == 0) goto label_800B8F60;
    r4 = &stack_0x08;
    r3 = Blt03DirAdd(ret_800B8F04, &stack_0x08); // [0x8000EC28]
label_800B8F60:;
    r5 = arg0_r3 + (192);
    r3 = 5;
    r4 = 3;
    r6 = 0;
    r3 = SndSeCall(5, 3, (arg0_r3 + 192), 0); // [0x800CB7DC]
label_800B8F74:;
    r0 = stack_0x44;
    f31 = stack_0x38;
    return; // r3 = ret_800B8F70
}

// ============================================================================
// High-Level AST Decompilation: cPlayer::Release(void)
// Unit: player.obj | Address: 0x800B8F8C | Size: 0x84 bytes
// ============================================================================
/* [0x800B8F8C] */ void cPlayer::Release(cPlayer* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r9 = SDA1::pG;
    r31 = this_r3;
    r30 = *(uint32_t*)(SDA1::pG + 0x144);
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4);
    r0 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x4) - *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0));
    if (r0 != 0) goto label_800B8FC8;
    r3 = "vector";
    r3 = _STL::__stl_throw_out_of_range("vector", r4); // [0x8013E678]
label_800B8FC8:;
    r9 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0);
    r3 = 0;
    r4 = 0;
    r5 = this_r3;
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0);
    r30 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + (1388);
    r3 = EspgenDelete(0, 0, this_r3); // [0x8008E8B8]
    r3 = *(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA2C);
    if (*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA2C) == 0) goto label_800B8FF4;
    r3 = PushObj(*(uint32_t*)((*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0x144) + 0x0) + 0x0) + 1388) + 0xA2C)); // [0x800749C8]
label_800B8FF4:;
    r3 = this_r3;
    r3 = PushEm(this_r3); // [0x8007CFDC]
    r0 = stack_0x14;
    return; // r3 = ret_800B8FF8
}

// ============================================================================
// High-Level AST Decompilation: PlGaugeSet(void)
// Unit: player.obj | Address: 0x800B9010 | Size: 0x88 bytes
// ============================================================================
/* [0x800B9010] */ void PlGaugeSet(void) {
    r9 = SDA1::pG;
    r8 = 1000;
    r0 = *(uint8_t*)(SDA1::pG + 0x681B);
    r7 = SDA1::pG;
    if (*(uint8_t*)(SDA1::pG + 0x681B) == 1) goto label_800B9050;
    if (*(uint8_t*)(SDA1::pG + 0x681B) > 1) goto label_800B9038;
    if (*(uint8_t*)(SDA1::pG + 0x681B) == 0) goto label_800B9044;
    goto label_800B9050;
label_800B9038:;
    if (*(uint8_t*)(SDA1::pG + 0x681B) == 2) goto label_800B904C;
    goto label_800B9050;
label_800B9044:;
    r8 = 2000;
    goto label_800B9050;
label_800B904C:;
    r8 = 300;
label_800B9050:;
    r11 = *(uint8_t*)(SDA1::pG + 0x681A);
    *(uint16_t*)(SDA1::pG + 0x6812) = 300;
    r10 = &ed_tbl;
    r8 = *(int16_t*)(SDA1::pG + 0x6814);
    r11 = (SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A));
    r9 = *(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689E);
    r9 = *(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689E) + (-1);
    r9 = ((*(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689E) + -1) + (*(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689E) + -1));
    *(uint16_t*)(SDA1::pG + 0x6816) = ((*(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689E) + -1) + (*(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689E) + -1));
    *(uint16_t*)(SDA1::pG + 0x6814) = ((*(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689E) + -1) + (*(uint8_t*)((SDA1::pG + *(uint8_t*)(SDA1::pG + 0x681A)) + 0x689E) + -1));
    return; // r3 = r3
}

// ============================================================================
// High-Level AST Decompilation: PlVibSet(unsigned long)
// Unit: player.obj | Address: 0x800B9098 | Size: 0x38 bytes
// ============================================================================
/* [0x800B9098] */ void PlVibSet(unsigned long arg0_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r11 = SDA1::pG;
    r4 = arg0_r3;
    r5 = 1;
    r9 = *(uint32_t*)(SDA1::pG + 0xF8);
    r3 = *(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x84);
    r3 = (*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x84) + *(uint32_t*)(SDA1::pG + 0xF8));
    r3 = VibSetData((*(uint32_t*)(*(uint32_t*)(SDA1::pG + 0xF8) + 0x84) + *(uint32_t*)(SDA1::pG + 0xF8)), arg0_r3, 1); // [0x800AD480]
    r0 = stack_0x0C;
    return; // r3 = ret_800B90BC
}

// ============================================================================
// High-Level AST Decompilation: cPlayer::cPlayer(void)
// Unit: player.obj | Address: 0x800B90D0 | Size: 0x3C bytes
// ============================================================================
/* [0x800B90D0] */ void cPlayer::cPlayer(cPlayer* this_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r30 = this_r3;
    r3 = cEm::cEm(this_r3); // [0x80020E98]
    r3 = this_r3;
    r9 = &vtable_cPlayer;
    *(uint32_t*)(this_r3 + 0x4B8) = &vtable_cPlayer;
    r0 = stack_0x14;
    return; // r3 = this_r3
}

// ============================================================================
// High-Level AST Decompilation: cPlayer::~cPlayer(void)
// Unit: player.obj | Address: 0x800B910C | Size: 0x30 bytes
// ============================================================================
/* [0x800B910C] */ void cPlayer::~cPlayer(cPlayer* this_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r11 = this_r3;
    r9 = &vtable_cPlayer;
    *(uint32_t*)(this_r3 + 0x4B8) = &vtable_cPlayer;
    r3 = cEm::~cEm(this_r3); // [0x80020F4C]
    r0 = stack_0x0C;
    return; // r3 = ret_800B9128
}

// ============================================================================
// High-Level AST Decompilation: cPlayer::clip(void) const
// Unit: player.obj | Address: 0x800B913C | Size: 0x18 bytes
// ============================================================================
/* [0x800B913C] */ void cPlayer::clip(void) const(void) {
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x128);
    return; // r3 = r3
}

// ============================================================================
// High-Level AST Decompilation: cPlayer::GetSpecialNo(void) const
// Unit: player.obj | Address: 0x800B9154 | Size: 0x8 bytes
// ============================================================================
/* [0x800B9154] */ void cPlayer::GetSpecialNo(void) const(void) {
    r3 = *(uint32_t*)(r3 + 0xC40);
    return; // r3 = *(uint32_t*)(r3 + 0xC40)
}
