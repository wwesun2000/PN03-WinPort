// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: compless.obj
// Functions Decompiled: 21
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: LzsDecode(unsigned char *, unsigned char *)
// Unit: compless.obj | Address: 0x80077680 | Size: 0x1C bytes
// ============================================================================
/* [0x80077680] */ void LzsDecode(unsigned char * arg0_r3, unsigned char * arg1_r4) {
    r10 = *(uint32_t*)(arg1_r4 + 0x4);
    r6 = arg1_r4 + (12);
    r8 = *(uint8_t*)(arg1_r4 + 0xC);
    r3 = arg0_r3 + (-1);
    r5 = ((arg1_r4 + 12) + *(uint32_t*)(arg1_r4 + 0x4));
    r7 = 7;
    r5 = ((arg1_r4 + 12) + *(uint32_t*)(arg1_r4 + 0x4)) + (-1);
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_LOOP_TOP
// Unit: compless.obj | Address: 0x8007769C | Size: 0x40 bytes
// ============================================================================
/* [0x8007769C] */ void LZS_DEC_LOOP_TOP(void) {
    if (r7 != 0) goto label_800776B8;
label_800776A4:;
    r7 = 7;
    if (r7 == 0) { /* tail branch 0x800776DC */ return; }
    goto label_800776C8;
label_800776B8:;
    r7 = 7 + (-1);
    if (r7 == 0) { /* tail branch 0x800776DC */ return; }
label_800776C8:;
    if ((7 + -1) != 0) goto label_800776B8;
    goto label_800776A4;
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_GET_BIT_A_0
// Unit: compless.obj | Address: 0x800776A4 | Size: 0x40 bytes
// ============================================================================
/* [0x800776A4] */ void LZS_DEC_GET_BIT_A_0(void) {
label_800776A4:;
    r7 = 7;
    if (r0 == 0) goto label_800776DC;
    goto label_800776C8;
label_800776B8:;
    r7 = 7 + (-1);
    if (r0 == 0) goto label_800776DC;
label_800776C8:;
    if ((7 + -1) != 0) goto label_800776B8;
    goto label_800776A4;
label_800776DC:;
    if ((7 + -1) != 0) { /* tail branch 0x800776F8 */ return; }
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_GET_BIT_A_1
// Unit: compless.obj | Address: 0x800776B8 | Size: 0x40 bytes
// ============================================================================
/* [0x800776B8] */ void LZS_DEC_GET_BIT_A_1(void) {
label_800776B8:;
    r7 = r7 + (-1);
    if (r0 == 0) goto label_800776DC;
    if ((r7 + -1) != 0) goto label_800776B8;
    LZS_DEC_GET_BIT_A_0(); return;
label_800776DC:;
    if ((r7 + -1) != 0) { /* tail branch 0x800776F8 */ return; }
    r7 = 7;
    if ((r7 + -1) == 0) { /* tail branch 0x80077740 */ return; }
    LZS_DEC_BIT_IDX_01(); return;
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_BIT_IDX_1
// Unit: compless.obj | Address: 0x800776C8 | Size: 0x40 bytes
// ============================================================================
/* [0x800776C8] */ void LZS_DEC_BIT_IDX_1(void) {
    if (r7 != 0) { /* tail branch 0x800776B8 */ return; }
    LZS_DEC_GET_BIT_A_0(); return;
    if (r7 != 0) goto label_800776F8;
    r7 = 7;
    if (r7 == 0) { /* tail branch 0x80077740 */ return; }
    LZS_DEC_BIT_IDX_01(); return;
label_800776F8:;
    r7 = 7 + (-1);
    if (r7 == 0) { /* tail branch 0x80077740 */ return; }
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_BIT_IDX_0
// Unit: compless.obj | Address: 0x800776DC | Size: 0x40 bytes
// ============================================================================
/* [0x800776DC] */ void LZS_DEC_BIT_IDX_0(void) {
    if (r7 != 0) goto label_800776F8;
    r7 = 7;
    if (r7 == 0) { /* tail branch 0x80077740 */ return; }
    goto label_80077708;
label_800776F8:;
    r7 = 7 + (-1);
    if (r7 == 0) { /* tail branch 0x80077740 */ return; }
label_80077708:;
    r10 = *(uint8_t*)(r5 - 0x1);
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_GET_BIT_B_0
// Unit: compless.obj | Address: 0x800776E4 | Size: 0x40 bytes
// ============================================================================
/* [0x800776E4] */ void LZS_DEC_GET_BIT_B_0(void) {
    r7 = 7;
    if (r0 == 0) { /* tail branch 0x80077740 */ return; }
    goto label_80077708;
    r7 = 7 + (-1);
    if (r0 == 0) { /* tail branch 0x80077740 */ return; }
label_80077708:;
    r10 = *(uint8_t*)(r5 - 0x1);
    if (r0 == 0) { /* tail branch 0x8007772C */ return; }
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_GET_BIT_B_1
// Unit: compless.obj | Address: 0x800776F8 | Size: 0x40 bytes
// ============================================================================
/* [0x800776F8] */ void LZS_DEC_GET_BIT_B_1(void) {
    r7 = r7 + (-1);
    if (r0 == 0) { /* tail branch 0x80077740 */ return; }
    r10 = *(uint8_t*)(r5 - 0x1);
    if (r0 == 0) goto label_8007772C;
    r11 = r11 + (2);
    LZS_COPY_DEC_TO_OUT(); return;
label_8007772C:;
    r11 = *(uint8_t*)(r5 - 0x1) + (9);
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_BIT_IDX_01
// Unit: compless.obj | Address: 0x80077708 | Size: 0x40 bytes
// ============================================================================
/* [0x80077708] */ void LZS_DEC_BIT_IDX_01(void) {
    r10 = *(uint8_t*)(r5 - 0x1);
    if (r0 == 0) goto label_8007772C;
    r11 = r11 + (2);
    LZS_COPY_DEC_TO_OUT(); return;
label_8007772C:;
    r11 = *(uint8_t*)(r5 - 0x1) + (9);
    if (r12 == 0) { /* tail branch 0x800777B4 */ return; }
    LZS_COPY_DEC_TO_OUT(); return;
    if (r7 != 0) { /* tail branch 0x80077758 */ return; }
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_BIT_IDX_01_LN_IS_3BIT
// Unit: compless.obj | Address: 0x80077724 | Size: 0x40 bytes
// ============================================================================
/* [0x80077724] */ void LZS_DEC_BIT_IDX_01_LN_IS_3BIT(void) {
    r11 = r11 + (2);
    LZS_COPY_DEC_TO_OUT(); return;
    r11 = r10 + (9);
    if (r12 == 0) { /* tail branch 0x800777B4 */ return; }
    LZS_COPY_DEC_TO_OUT(); return;
    if (r7 != 0) goto label_80077758;
    r7 = 7;
    LZS_DEC_BIT_IDX_00_BIT_0(); return;
label_80077758:;
    r7 = 7 + (-1);
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_BIT_IDX_01_LN_IS_BYTE
// Unit: compless.obj | Address: 0x8007772C | Size: 0x40 bytes
// ============================================================================
/* [0x8007772C] */ void LZS_DEC_BIT_IDX_01_LN_IS_BYTE(void) {
    r11 = r10 + (9);
    if (r12 == 0) { /* tail branch 0x800777B4 */ return; }
    LZS_COPY_DEC_TO_OUT(); return;
    if (r7 != 0) goto label_80077758;
    r7 = 7;
    goto label_80077764;
label_80077758:;
    r7 = 7 + (-1);
label_80077764:;
    if ((7 + -1) != 0) { /* tail branch 0x8007777C */ return; }
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_BIT_IDX_00
// Unit: compless.obj | Address: 0x80077740 | Size: 0x40 bytes
// ============================================================================
/* [0x80077740] */ void LZS_DEC_BIT_IDX_00(void) {
    if (r7 != 0) goto label_80077758;
    r7 = 7;
    goto label_80077764;
label_80077758:;
    r7 = 7 + (-1);
label_80077764:;
    if ((7 + -1) != 0) goto label_8007777C;
    r7 = 7;
    LZS_DEC_BIT_IDX_00_BIT_1(); return;
label_8007777C:;
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_GET_BIT_C_0
// Unit: compless.obj | Address: 0x80077748 | Size: 0x40 bytes
// ============================================================================
/* [0x80077748] */ void LZS_DEC_GET_BIT_C_0(void) {
    r7 = 7;
    goto label_80077764;
    r7 = 7 + (-1);
label_80077764:;
    if ((7 + -1) != 0) goto label_8007777C;
    r7 = 7;
    LZS_DEC_BIT_IDX_00_BIT_1(); return;
label_8007777C:;
    r7 = 7 + (-1);
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_GET_BIT_C_1
// Unit: compless.obj | Address: 0x80077758 | Size: 0x40 bytes
// ============================================================================
/* [0x80077758] */ void LZS_DEC_GET_BIT_C_1(void) {
    r7 = r7 + (-1);
    if ((r7 + -1) != 0) goto label_8007777C;
    r7 = 7;
    goto label_80077788;
label_8007777C:;
    r7 = 7 + (-1);
label_80077788:;
    r10 = (r11 + r10);
    r11 = (r11 + r10) + (2);
    r9 = (r3 - r12);
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_BIT_IDX_00_BIT_0
// Unit: compless.obj | Address: 0x80077764 | Size: 0x40 bytes
// ============================================================================
/* [0x80077764] */ void LZS_DEC_BIT_IDX_00_BIT_0(void) {
    if (r7 != 0) goto label_8007777C;
    r7 = 7;
    goto label_80077788;
label_8007777C:;
    r7 = 7 + (-1);
label_80077788:;
    r10 = (r11 + r10);
    r11 = (r11 + r10) + (2);
    r9 = (r3 - r12);
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_GET_BIT_D_0
// Unit: compless.obj | Address: 0x8007776C | Size: 0x40 bytes
// ============================================================================
/* [0x8007776C] */ void LZS_DEC_GET_BIT_D_0(void) {
    r7 = 7;
    goto label_80077788;
    r7 = 7 + (-1);
label_80077788:;
    r10 = (r11 + r10);
    r11 = (r11 + r10) + (2);
    r9 = (r3 - r12);
label_80077798:;
    if (r0 != 0) goto label_80077798;
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_GET_BIT_D_1
// Unit: compless.obj | Address: 0x8007777C | Size: 0x40 bytes
// ============================================================================
/* [0x8007777C] */ void LZS_DEC_GET_BIT_D_1(void) {
    r7 = r7 + (-1);
    r10 = (r11 + r10);
    r11 = (r11 + r10) + (2);
    r9 = (r3 - r12);
label_80077798:;
    if (r0 != 0) goto label_80077798;
    if ((r7 + -1) != 0) { /* tail branch 0x800776B8 */ return; }
    LZS_DEC_GET_BIT_A_0(); return;
    return; // r3 = r3
    SDA1::pConsRoom = r3;
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_BIT_IDX_00_BIT_1
// Unit: compless.obj | Address: 0x80077788 | Size: 0x40 bytes
// ============================================================================
/* [0x80077788] */ void LZS_DEC_BIT_IDX_00_BIT_1(void) {
    r10 = (r11 + r10);
    r11 = (r11 + r10) + (2);
    r9 = (r3 - r12);
label_80077798:;
    if (r0 != 0) goto label_80077798;
    if (r7 != 0) { /* tail branch 0x800776B8 */ return; }
    LZS_DEC_GET_BIT_A_0(); return;
    return; // r3 = r3
    SDA1::pConsRoom = r3;
    r3 = 1;
    return; // r3 = 1
    SDA1::pConsCore = 1;
}

// ============================================================================
// High-Level AST Decompilation: LZS_COPY_DEC_TO_OUT
// Unit: compless.obj | Address: 0x80077794 | Size: 0x40 bytes
// ============================================================================
/* [0x80077794] */ void LZS_COPY_DEC_TO_OUT(void) {
    r9 = (r3 - r12);
label_80077798:;
    if (r0 != 0) goto label_80077798;
    if (r7 != 0) { /* tail branch 0x800776B8 */ return; }
    LZS_DEC_GET_BIT_A_0(); return;
    return; // r3 = r3
    SDA1::pConsRoom = r3;
    r3 = 1;
    return; // r3 = 1
    SDA1::pConsCore = 1;
    r3 = 1;
    return; // r3 = 1
    return; // r3 = 1
}

// ============================================================================
// High-Level AST Decompilation: LZS_COPY_DEC_TO_OUT_TOP
// Unit: compless.obj | Address: 0x80077798 | Size: 0x40 bytes
// ============================================================================
/* [0x80077798] */ void LZS_COPY_DEC_TO_OUT_TOP(void) {
label_80077798:;
    if (r0 != 0) goto label_80077798;
    if (r7 != 0) { /* tail branch 0x800776B8 */ return; }
    LZS_DEC_GET_BIT_A_0(); return;
    return; // r3 = r3
    SDA1::pConsRoom = r3;
    r3 = 1;
    return; // r3 = 1
    SDA1::pConsCore = 1;
    r3 = 1;
    return; // r3 = 1
    return; // r3 = 1
    r11 = SDA1::pConsRoom;
}

// ============================================================================
// High-Level AST Decompilation: LZS_DEC_LOOP_END
// Unit: compless.obj | Address: 0x800777B4 | Size: 0x40 bytes
// ============================================================================
/* [0x800777B4] */ void LZS_DEC_LOOP_END(void) {
    return; // r3 = r3
    SDA1::pConsRoom = r3;
    r3 = 1;
    return; // r3 = 1
    SDA1::pConsCore = 1;
    r3 = 1;
    return; // r3 = 1
    return; // r3 = 1
    r11 = SDA1::pConsRoom;
    if (SDA1::pConsRoom != 0) { /* tail branch 0x80077830 */ return; }
    r9 = &ConsRoomDefault;
}
