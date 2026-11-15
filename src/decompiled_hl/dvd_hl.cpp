// ============================================================================
// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: dvd.obj
// Functions Decompiled: 31
// ============================================================================

// ============================================================================
// High-Level AST Decompilation: trans2mram(unsigned long, unsigned long, unsigned long)
// Unit: dvd.obj | Address: 0x8007AE7C | Size: 0x6C bytes
// ============================================================================
/* [0x8007AE7C] */ void trans2mram(unsigned long arg0_r3, unsigned long arg1_r4, unsigned long arg2_r5) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r28 = arg1_r4;
    r30 = arg2_r5;
    r4 = arg0_r3;
    r29 = *(uint32_t*)0x80188DA4;
    r3 = arg1_r4;
    r3 = memcpy(); // [0x800E88CC]
    r11 = *(uint8_t*)(*(uint32_t*)0x80188DA4 + 0x9C);
    r9 = &ReadStatus;
    r3 = arg1_r4;
    r9 = &ReadStatus + (4);
    r4 = arg2_r5;
    r0 = (r0 + arg2_r5);
    r3 = DCFlushRange(); // [0x800F1970]
    r0 = stack_0x1C;
    return; // r3 = ret_8007AED0
}

// ============================================================================
// High-Level AST Decompilation: trans2aram_cb(unsigned long)
// Unit: dvd.obj | Address: 0x8007AEE8 | Size: 0x3C bytes
// ============================================================================
/* [0x8007AEE8] */ void trans2aram_cb(unsigned long arg0_r3) {
    r10 = *(uint32_t*)0x80188DA4;
    r11 = &ReadStatus;
    r11 = &ReadStatus + (8);
    r9 = *(uint8_t*)(*(uint32_t*)0x80188DA4 + 0x9C);
    r0 = *(uint32_t*)(*(uint32_t*)0x80188DA4 + 0x0);
    *(uint32_t*)(*(uint32_t*)0x80188DA4 + 0x0) = *(uint32_t*)(*(uint32_t*)0x80188DA4 + 0x0);
    r8 = *(uint32_t*)(arg0_r3 + 0x18);
    r0 = (*(uint32_t*)(*(uint32_t*)0x80188DA4 + 0x0) + *(uint32_t*)(arg0_r3 + 0x18));
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: trans2aram(unsigned long, unsigned long, unsigned long)
// Unit: dvd.obj | Address: 0x8007AF24 | Size: 0x8C bytes
// ============================================================================
/* [0x8007AF24] */ void trans2aram(unsigned long arg0_r3, unsigned long arg1_r4, unsigned long arg2_r5) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r29 = arg0_r3;
    r30 = *(uint32_t*)0x80188DA4;
    r28 = arg1_r4;
    r31 = arg2_r5;
    if (r0 == 0) goto label_8007AF58;
    r0 = arg2_r5 + (31);
    goto label_8007AF5C;
label_8007AF58:;
    r4 = 0;
label_8007AF5C:;
    r31 = 0;
    r3 = arg0_r3;
    r3 = DCFlushRange(); // [0x800F1970]
    r7 = arg0_r3;
    r8 = arg1_r4;
    r9 = 0;
    r10 = &trans2aram_cb(unsigned long);
    r3 = *(uint32_t*)0x80188DA4 + (108);
    r4 = 0;
    r5 = 0;
    r6 = 1;
    r3 = ARQPostRequest(); // [0x80113F70]
    r0 = *(uint32_t*)(*(uint32_t*)0x80188DA4 + 0x0);
    *(uint32_t*)(*(uint32_t*)0x80188DA4 + 0x0) = *(uint32_t*)(*(uint32_t*)0x80188DA4 + 0x0);
    r0 = stack_0x1C;
    return; // r3 = ret_8007AF8C
}

// ============================================================================
// High-Level AST Decompilation: dvdread_callback(long, DVDFileInfo *)
// Unit: dvd.obj | Address: 0x8007AFB0 | Size: 0x44 bytes
// ============================================================================
/* [0x8007AFB0] */ void dvdread_callback(long arg0_r3, DVDFileInfo * arg1_r4) {
    r9 = *(uint32_t*)(arg1_r4 + 0x2C);
    r0 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x2C) + 0x0);
    *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x2C) + 0x0) = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x2C) + 0x0);
    if (arg0_r3 != -3) goto label_8007AFD8;
    r0 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x2C) + 0x0);
    *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x2C) + 0x0) = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x2C) + 0x0);
    return; // r3 = arg0_r3
label_8007AFD8:;
    r0 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x2C) + 0x5C);
    r0 = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x2C) + 0x0);
    *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x2C) + 0x0) = *(uint32_t*)(*(uint32_t*)(arg1_r4 + 0x2C) + 0x0);
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: dvdread_init(DVD_WORK *, DVD_QUEUE *)
// Unit: dvd.obj | Address: 0x8007AFF4 | Size: 0x1F0 bytes
// ============================================================================
/* [0x8007AFF4] */ void dvdread_init(DVD_WORK * arg0_r3, DVD_QUEUE * arg1_r4) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r29 = arg0_r3;
    r31 = arg1_r4;
    r0 = *(uint8_t*)(arg0_r3 + 0x1);
    r30 = *(uint8_t*)(arg1_r4 + 0x9D);
    if (r9 == 1) goto label_8007B08C;
    if (r9 > 1) goto label_8007B030;
    if (r9 == 0) goto label_8007B03C;
    goto label_8007B1D0;
label_8007B030:;
    if (r9 == 2) goto label_8007B184;
    goto label_8007B1D0;
label_8007B03C:;
    r3 = *(uint32_t*)(arg1_r4 + 0x4);
    r4 = arg1_r4 + (12);
    r3 = DVDFastOpen(); // [0x80105C3C]
    r0 = *(uint32_t*)(arg1_r4 + 0x54);
    if (*(uint32_t*)(arg1_r4 + 0x54) != 0) goto label_8007B05C;
    r0 = *(uint32_t*)(arg1_r4 + 0x40);
    *(uint32_t*)(arg1_r4 + 0x54) = *(uint32_t*)(arg1_r4 + 0x40);
label_8007B05C:;
    r9 = *(uint32_t*)(arg1_r4 + 0x54);
    *(uint32_t*)(arg1_r4 + 0x38) = arg1_r4;
    if (*(uint32_t*)(arg1_r4 + 0x54) == 0) goto label_8007B078;
    r0 = *(uint32_t*)(arg1_r4 + 0x54) + (31);
    goto label_8007B07C;
label_8007B078:;
    r0 = 0;
label_8007B07C:;
    *(uint32_t*)(arg1_r4 + 0x54) = 0;
    r9 = *(uint8_t*)(arg0_r3 + 0x1);
    r9 = *(uint8_t*)(arg0_r3 + 0x1) + (1);
    *(uint8_t*)(arg0_r3 + 0x1) = (*(uint8_t*)(arg0_r3 + 0x1) + 1);
label_8007B08C:;
    r6 = &header_buff;
    r10 = (r8 + &header_buff);
    r11 = &pFilehead;
    r7 = 0;
    r5 = r8;
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    if (*(uint32_t*)(arg1_r4 + 0x0) < 0) goto label_8007B0C8;
    if (*(uint32_t*)(arg1_r4 + 0x0) == 0) goto label_8007B130;
label_8007B0C8:;
    r10 = arg1_r4 + (140);
    if (*(uint32_t*)(arg1_r4 + 0x0) == 0) goto label_8007B0E8;
    r0 = *(uint8_t*)(arg1_r4 + 0x9D) + (-1);
    r11 = *(uint32_t*)0x8019000C;
    goto label_8007B0EC;
label_8007B0E8:;
label_8007B0EC:;
    r4 = &header_buff;
    r4 = (r8 + &header_buff);
    r7 = &dvdread_callback(long, DVDFileInfo *);
    r3 = arg1_r4 + (12);
    r5 = 1024;
    r8 = 2;
    r3 = DVDReadAsyncPrio(); // [0x801061AC]
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    *(uint32_t*)(arg1_r4 + 0x0) = *(uint32_t*)(arg1_r4 + 0x0);
    r9 = *(uint8_t*)(arg0_r3 + 0x1);
    r9 = *(uint8_t*)(arg0_r3 + 0x1) + (1);
    *(uint8_t*)(arg0_r3 + 0x1) = (*(uint8_t*)(arg0_r3 + 0x1) + 1);
    goto label_8007B168;
label_8007B130:;
    r9 = *(uint32_t*)(arg1_r4 + 0x68);
    r11 = -1;
    r0 = *(uint32_t*)(arg1_r4 + 0x54);
    *(uint32_t*)((arg1_r4 + 140) + 0x4) = *(uint32_t*)(arg1_r4 + 0x54);
    r9 = *(uint32_t*)(arg1_r4 + 0x50);
    *(uint32_t*)((arg1_r4 + 140) + 0x20) = -1;
    *(uint32_t*)((arg1_r4 + 140) + 0x8) = *(uint32_t*)(arg1_r4 + 0x50);
    *(uint32_t*)((arg1_r4 + 140) + 0xC) = *(uint8_t*)(arg1_r4 + 0x9D);
    *(uint32_t*)((arg1_r4 + 140) + 0x10) = *(uint8_t*)(arg1_r4 + 0x9D);
    *(uint8_t*)(arg0_r3 + 0x1) = *(uint8_t*)(arg1_r4 + 0x9D);
    r9 = *(uint8_t*)(arg0_r3 + 0x0);
    r9 = *(uint8_t*)(arg0_r3 + 0x0) + (1);
    *(uint8_t*)(arg0_r3 + 0x0) = (*(uint8_t*)(arg0_r3 + 0x0) + 1);
label_8007B168:;
    r0 = *(uint8_t*)(arg1_r4 + 0x9C);
    r9 = &ReadStatus;
    r11 = 2;
    goto label_8007B1D0;
label_8007B184:;
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    if (*(uint32_t*)(arg1_r4 + 0x0) != 0) goto label_8007B1D0;
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    if (*(uint32_t*)(arg1_r4 + 0x0) == 0) goto label_8007B1A8;
    *(uint8_t*)(arg0_r3 + 0x1) = 2;
    *(uint8_t*)(arg0_r3 + 0x0) = &ReadStatus;
    goto label_8007B1D0;
label_8007B1A8:;
    r11 = *(uint8_t*)(arg0_r3 + 0x0);
    *(uint8_t*)(arg0_r3 + 0x1) = *(uint32_t*)(arg1_r4 + 0x0);
    r10 = &pFilehead;
    r11 = *(uint8_t*)(arg0_r3 + 0x0) + (1);
    *(uint8_t*)(arg0_r3 + 0x0) = (*(uint8_t*)(arg0_r3 + 0x0) + 1);
    r9 = &ReadStatus + (32);
label_8007B1D0:;
    r0 = stack_0x1C;
    return; // r3 = ret_8007B110
}

// ============================================================================
// High-Level AST Decompilation: dvdread_main(DVD_WORK *, DVD_QUEUE *)
// Unit: dvd.obj | Address: 0x8007B1E4 | Size: 0x2B4 bytes
// ============================================================================
/* [0x8007B1E4] */ void dvdread_main(DVD_WORK * arg0_r3, DVD_QUEUE * arg1_r4) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r30 = arg0_r3;
    r31 = arg1_r4;
    r0 = *(uint8_t*)(arg0_r3 + 0x1);
    r11 = *(uint8_t*)(arg1_r4 + 0x9D);
    if (*(uint8_t*)(arg0_r3 + 0x1) == 1) goto label_8007B348;
    if (*(uint8_t*)(arg0_r3 + 0x1) > 1) goto label_8007B224;
    if (*(uint8_t*)(arg0_r3 + 0x1) == 0) goto label_8007B238;
    goto label_8007B484;
label_8007B224:;
    if (*(uint8_t*)(arg0_r3 + 0x1) == 2) goto label_8007B3AC;
    if (*(uint8_t*)(arg0_r3 + 0x1) == 3) goto label_8007B41C;
    goto label_8007B484;
label_8007B238:;
    r28 = &pFilehead;
    r29 = *(uint8_t*)(arg0_r3 + 0x1);
    r9 = *(uint32_t*)0x80190000;
    if (*(uint32_t*)0x80190000 == 3) goto label_8007B304;
    if (*(uint32_t*)0x80190000 > 0x3u) goto label_8007B26C;
    if (*(uint32_t*)0x80190000 == 0) goto label_8007B304;
    goto label_8007B484;
label_8007B26C:;
    if (*(uint32_t*)0x80190000 == 4) goto label_8007B2BC;
    if (*(uint32_t*)0x80190000 != -1) goto label_8007B484;
    if (r10 != 0) goto label_8007B29C;
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    *(uint32_t*)(arg1_r4 + 0x0) = *(uint32_t*)(arg1_r4 + 0x0);
    *(uint8_t*)(arg0_r3 + 0x1) = r10;
    r9 = *(uint8_t*)(arg0_r3 + 0x0);
    goto label_8007B3CC;
label_8007B29C:;
    r9 = *(uint8_t*)(arg1_r4 + 0x9D) + (-1);
    r0 = r10 + (-1);
    *(uint8_t*)(arg1_r4 + 0x9D) = (*(uint8_t*)(arg1_r4 + 0x9D) + -1);
    r9 = (*(uint8_t*)(arg1_r4 + 0x9D) + -1) + (32);
    goto label_8007B484;
label_8007B2BC:;
    if (r10 != 3) goto label_8007B2E4;
    r3 = 0x8016961Cu;
    r3 = OSReport(); // [0x800F2D80]
    r9 = ((*(uint8_t*)(arg1_r4 + 0x9D) + -1) + 32) + (32);
    goto label_8007B484;
label_8007B2E4:;
    r0 = *(uint8_t*)(arg1_r4 + 0x9D) + (1);
    *(uint8_t*)(arg1_r4 + 0x9D) = (*(uint8_t*)(arg1_r4 + 0x9D) + 1);
    r11 = 1;
    *(uint8_t*)(arg0_r3 + 0x1) = 1;
    r9 = *(uint8_t*)(arg0_r3 + 0x0);
    r9 = *(uint8_t*)(arg0_r3 + 0x0) + (-1);
    *(uint8_t*)(arg0_r3 + 0x0) = (*(uint8_t*)(arg0_r3 + 0x0) + -1);
    goto label_8007B484;
label_8007B304:;
    r8 = arg1_r4 + (140);
    r11 = &pFilehead;
    r0 = *(uint32_t*)((*(uint8_t*)(arg0_r3 + 0x0) + -1) + 0x4);
    *(uint32_t*)(arg1_r4 + 0x58) = *(uint32_t*)((*(uint8_t*)(arg0_r3 + 0x0) + -1) + 0x4);
    r0 = *(uint32_t*)((*(uint8_t*)(arg0_r3 + 0x0) + -1) + 0x8);
    *(uint32_t*)(arg1_r4 + 0x64) = *(uint32_t*)((*(uint8_t*)(arg0_r3 + 0x0) + -1) + 0x8);
    r9 = *(uint32_t*)(r10 + 0xC);
    r0 = (*(uint32_t*)((*(uint8_t*)(arg0_r3 + 0x0) + -1) + 0x8) + *(uint32_t*)(r10 + 0xC));
    *(uint32_t*)(arg1_r4 + 0x60) = (*(uint32_t*)((*(uint8_t*)(arg0_r3 + 0x0) + -1) + 0x8) + *(uint32_t*)(r10 + 0xC));
    r9 = *(uint8_t*)(arg0_r3 + 0x1);
    r9 = *(uint8_t*)(arg0_r3 + 0x1) + (1);
    goto label_8007B480;
label_8007B348:;
    r9 = *(uint32_t*)(arg1_r4 + 0x58);
    if (*(uint32_t*)(arg1_r4 + 0x58) <= 0x00080000u) goto label_8007B35C;
label_8007B35C:;
    *(uint32_t*)(arg1_r4 + 0x5C) = 0x00080000u;
    r3 = arg1_r4 + (12);
    if (0x00080000u == 0) goto label_8007B378;
    r0 = 0x0008001Fu;
    goto label_8007B37C;
label_8007B378:;
    r5 = 0;
label_8007B37C:;
    r6 = *(uint32_t*)(arg1_r4 + 0x60);
    r7 = &dvdread_callback(long, DVDFileInfo *);
    r8 = 2;
    r3 = DVDReadAsyncPrio(); // [0x801061AC]
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    *(uint32_t*)(arg1_r4 + 0x0) = *(uint32_t*)(arg1_r4 + 0x0);
    r9 = *(uint8_t*)(arg0_r3 + 0x1);
    r9 = *(uint8_t*)(arg0_r3 + 0x1) + (1);
    goto label_8007B480;
label_8007B3AC:;
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    if (0x00080000u != 0) goto label_8007B484;
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    if (0x00080000u == 0) goto label_8007B3D8;
    r9 = *(uint8_t*)(arg0_r3 + 0x0);
    *(uint8_t*)(arg0_r3 + 0x1) = &pFilehead;
label_8007B3CC:;
    r9 = *(uint8_t*)(arg0_r3 + 0x0) + (1);
    *(uint8_t*)(arg0_r3 + 0x0) = (*(uint8_t*)(arg0_r3 + 0x0) + 1);
    goto label_8007B484;
label_8007B3D8:;
    r9 = &pFilehead;
    r11 = &trans_proc_tbl.531;
    r5 = *(uint32_t*)(arg1_r4 + 0x5C);
    r0 = *(uint32_t*)(r10 + 0x0);
    r4 = *(uint32_t*)(arg1_r4 + 0x64);
    return; // r3 = 0x80380000u
    r9 = *(uint8_t*)(arg0_r3 + 0x1);
    r9 = *(uint8_t*)(arg0_r3 + 0x1) + (1);
    goto label_8007B480;
label_8007B41C:;
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    if (0x00080000u != 0) goto label_8007B484;
    r11 = *(uint32_t*)(arg1_r4 + 0x5C);
    r0 = *(uint32_t*)(arg1_r4 + 0x60);
    r9 = *(uint32_t*)(arg1_r4 + 0x64);
    r8 = *(uint32_t*)(arg1_r4 + 0x58);
    r0 = (*(uint32_t*)(arg1_r4 + 0x60) + *(uint32_t*)(arg1_r4 + 0x5C));
    r9 = (*(uint32_t*)(arg1_r4 + 0x64) + *(uint32_t*)(arg1_r4 + 0x5C));
    *(uint32_t*)(arg1_r4 + 0x60) = (*(uint32_t*)(arg1_r4 + 0x60) + *(uint32_t*)(arg1_r4 + 0x5C));
    *(uint32_t*)(arg1_r4 + 0x64) = (*(uint32_t*)(arg1_r4 + 0x64) + *(uint32_t*)(arg1_r4 + 0x5C));
    if (*(uint32_t*)(arg1_r4 + 0x58) > *(uint32_t*)(arg1_r4 + 0x5C)) goto label_8007B474;
    *(uint32_t*)(arg1_r4 + 0x58) = &dvdread_callback(long, DVDFileInfo *);
    r9 = &pFilehead;
    r11 = *(uint32_t*)(arg1_r4 + 0x5C) + (32);
    *(uint8_t*)(arg0_r3 + 0x1) = &dvdread_callback(long, DVDFileInfo *);
    goto label_8007B484;
label_8007B474:;
    r0 = (*(uint32_t*)(arg1_r4 + 0x58) - (*(uint32_t*)(arg1_r4 + 0x5C) + 32));
    r9 = 1;
    *(uint32_t*)(arg1_r4 + 0x58) = (*(uint32_t*)(arg1_r4 + 0x58) - (*(uint32_t*)(arg1_r4 + 0x5C) + 32));
label_8007B480:;
    *(uint8_t*)(arg0_r3 + 0x1) = 1;
label_8007B484:;
    r0 = stack_0x1C;
    return; // r3 = 0x80380000u
}

// ============================================================================
// High-Level AST Decompilation: dvdread_exit(DVD_WORK *, DVD_QUEUE *)
// Unit: dvd.obj | Address: 0x8007B498 | Size: 0x7C bytes
// ============================================================================
/* [0x8007B498] */ void dvdread_exit(DVD_WORK * arg0_r3, DVD_QUEUE * arg1_r4) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r31 = arg1_r4;
    r3 = arg1_r4 + (12);
    r3 = DVDClose(); // [0x80105D78]
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    if (r0 == 0) goto label_8007B4D4;
    r0 = *(uint8_t*)(arg1_r4 + 0x9C);
    r9 = &ReadStatus;
    r11 = 128;
    goto label_8007B4F0;
label_8007B4D4:;
    r0 = *(uint32_t*)(arg1_r4 + 0x0);
    if (r0 == 0) goto label_8007B4F8;
    r0 = *(uint8_t*)(arg1_r4 + 0x9C);
    r9 = &ReadStatus;
    r11 = 64;
label_8007B4F0:;
label_8007B4F8:;
    r0 = 1;
    *(uint32_t*)(arg1_r4 + 0xA4) = 1;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_8007B4B0
}

// ============================================================================
// High-Level AST Decompilation: DvdReadProc(void)
// Unit: dvd.obj | Address: 0x8007B514 | Size: 0xC0 bytes
// ============================================================================
/* [0x8007B514] */ void DvdReadProc(void) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    stack_0x0C = r12;
    r11 = 0;
    r30 = &Dvd;
    r31 = *(uint32_t*)(&Dvd + 0x4);
    r29 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x4) + 0xA0);
    Dvd = 0;
    *(uint8_t*)(&Dvd + 0x1) = 0;
    r0 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x4) + 0xA4);
    if (*(uint32_t*)(*(uint32_t*)(&Dvd + 0x4) + 0xA4) != 0) goto label_8007B5A0;
    r28 = &tbl.538;
label_8007B560:;
    r0 = *(uint8_t*)(&Dvd + 0x0);
    r3 = &Dvd;
    r4 = *(uint32_t*)(&Dvd + 0x4);
    return; // r3 = &Dvd
    if (*(uint32_t*)(*(uint32_t*)(&Dvd + 0x4) + 0xA0) != 0) goto label_8007B590;
    r3 = 1;
    r3 = TaskSleep(1); // [0x800A1B5C]
    goto label_8007B594;
label_8007B590:;
    r3 = DvdErrCheck(); // [0x8007BD5C]
label_8007B594:;
    r0 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x4) + 0xA4);
    if (*(uint32_t*)(*(uint32_t*)(&Dvd + 0x4) + 0xA4) == 0) goto label_8007B560;
label_8007B5A0:;
    r0 = 0;
    *(uint32_t*)(*(uint32_t*)(&Dvd + 0x4) + 0x0) = 0;
    *(uint32_t*)(&Dvd + 0x4) = 0;
    if (*(uint32_t*)(*(uint32_t*)(&Dvd + 0x4) + 0xA0) != 0) goto label_8007B5B8;
    r3 = TaskExit(); // [0x800A1C38]
label_8007B5B8:;
    r0 = stack_0x24;
    r12 = stack_0x0C;
    return; // r3 = ret_8007B5B4
}

// ============================================================================
// High-Level AST Decompilation: DvdInit(void)
// Unit: dvd.obj | Address: 0x8007B5D4 | Size: 0x30 bytes
// ============================================================================
/* [0x8007B5D4] */ void DvdInit(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = DVDInit(); // [0x80106A6C]
    r3 = 1;
    r3 = DVDSetAutoInvalidation(); // [0x80109C98]
    r3 = DvdFileTblExistCheck(); // [0x8007B6A0]
    r3 = DvdWorkClear(); // [0x8007B604]
    r0 = stack_0x0C;
    return; // r3 = ret_8007B5F0
}

// ============================================================================
// High-Level AST Decompilation: DvdWorkClear(void)
// Unit: dvd.obj | Address: 0x8007B604 | Size: 0x6C bytes
// ============================================================================
/* [0x8007B604] */ void DvdWorkClear(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r4 = 0;
    r5 = 12;
    r3 = &Dvd;
    r3 = memset(); // [0x800E8A5C]
    r4 = 0;
    r5 = 6400;
    r3 = &DvdQueue;
    r3 = memset(); // [0x800E8A5C]
    r4 = 0;
    r5 = 44;
    r3 = &Aram;
    r3 = memset(); // [0x800E8A5C]
    r4 = 0;
    r3 = &AramQueue;
    r5 = 96;
    r3 = memset(); // [0x800E8A5C]
    r0 = stack_0x0C;
    return; // r3 = ret_8007B65C
}

// ============================================================================
// High-Level AST Decompilation: DvdAllReset(void)
// Unit: dvd.obj | Address: 0x8007B670 | Size: 0x30 bytes
// ============================================================================
/* [0x8007B670] */ void DvdAllReset(void) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r3 = DvdReadCancelAll(); // [0x8007BB98]
    r3 = AramDmaCancelAll(); // [0x8007C210]
    r3 = ARQReset(); // [0x80113F64]
    r3 = ARQInit(); // [0x80113EF4]
    r3 = DvdWorkClear(); // [0x8007B604]
    r0 = stack_0x0C;
    return; // r3 = ret_8007B68C
}

// ============================================================================
// High-Level AST Decompilation: DvdFileTblExistCheck(void)
// Unit: dvd.obj | Address: 0x8007B6A0 | Size: 0x48 bytes
// ============================================================================
/* [0x8007B6A0] */ void DvdFileTblExistCheck(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r31 = &FileTbl;
    r30 = &FileTbl + (824);
label_8007B6BC:;
    r3 = *(uint32_t*)(&FileTbl + 0x0);
    r3 = DVDConvertPathToEntrynum(); // [0x80105948]
    *(uint32_t*)(&FileTbl + 0x4) = ret_8007B6C0;
    r31 = &FileTbl + (8);
    if ((&FileTbl + 8) <= (&FileTbl + 824)) goto label_8007B6BC;
    r0 = stack_0x14;
    return; // r3 = ret_8007B6C0
}

// ============================================================================
// High-Level AST Decompilation: DvdFileExistCheck(char *, unsigned long *)
// Unit: dvd.obj | Address: 0x8007B6E8 | Size: 0x5C bytes
// ============================================================================
/* [0x8007B6E8] */ void DvdFileExistCheck(char * arg0_r3, unsigned long * arg1_r4) {
    // Stack frame allocated: 80 bytes
    stack_0x54 = r0;
    r30 = arg1_r4;
    r3 = DVDConvertPathToEntrynum(); // [0x80105948]
    r31 = ret_8007B6FC;
    if (arg1_r4 == 0) goto label_8007B72C;
    if (ret_8007B6FC == -1) goto label_8007B72C;
    r4 = &stack_0x08;
    r3 = DVDFastOpen(); // [0x80105C3C]
    r0 = stack_0x3C;
    r3 = &stack_0x08;
    *(uint32_t*)(arg1_r4 + 0x0) = stack_0x3C;
    r3 = DVDClose(); // [0x80105D78]
label_8007B72C:;
    r3 = ret_8007B6FC;
    r0 = stack_0x54;
    return; // r3 = ret_8007B6FC
}

// ============================================================================
// High-Level AST Decompilation: DvdReadReqMain(unsigned short, char *, unsigned long, unsigned long, unsigned long, unsigned short, unsigned long, void *)
// Unit: dvd.obj | Address: 0x8007B744 | Size: 0x1D4 bytes
// ============================================================================
/* [0x8007B744] */ void DvdReadReqMain(unsigned short arg0_r3, char * arg1_r4, unsigned long arg2_r5, unsigned long arg3_r6, unsigned long arg4_r7, unsigned short arg5_r8, unsigned long arg6_r9, void * arg7_r10) {
    // Stack frame allocated: 56 bytes
    stack_0x3C = r0;
    r25 = arg0_r3;
    r20 = &Dvd;
    r30 = arg2_r5;
    r22 = arg3_r6;
    r28 = arg4_r7;
    r26 = arg5_r8;
    r27 = arg6_r9;
    r23 = arg7_r10;
    r21 = 0;
    r24 = arg1_r4;
    if (r0 != 0) goto label_8007B79C;
    r9 = &FileTbl;
    r9 = &FileTbl + (4);
    goto label_8007B7A8;
label_8007B79C:;
    r3 = arg1_r4;
    r3 = DVDConvertPathToEntrynum(); // [0x80105948]
    r29 = ret_8007B7A0;
label_8007B7A8:;
    r3 = -1;
    if (ret_8007B7A0 == -1) goto label_8007B904;
    r3 = &Dvd;
    r3 = pull_readqueue(&Dvd); // [0x8007BC44]
    r31 = ret_8007B7B8;
    if (ret_8007B7A0 != -1) goto label_8007B7CC;
    r3 = -2;
    goto label_8007B904;
label_8007B7CC:;
    r0 = arg6_r9 + (-16);
    if ((arg6_r9 + -16) > 0x1u) goto label_8007B844;
    r30 = ret_8007B7B8 + (12);
    r3 = ret_8007B7A0;
    r4 = (ret_8007B7B8 + 12);
    r3 = DVDFastOpen(); // [0x80105C3C]
    r9 = *(uint32_t*)(ret_8007B7B8 + 0x40);
    r3 = (ret_8007B7B8 + 12);
    if (*(uint32_t*)(ret_8007B7B8 + 0x40) == 0) goto label_8007B804;
    r0 = *(uint32_t*)(ret_8007B7B8 + 0x40) + (31);
    goto label_8007B808;
label_8007B804:;
    r28 = 0;
label_8007B808:;
    r3 = DVDClose(); // [0x80105D78]
    if (arg6_r9 != 16) goto label_8007B824;
    r3 = 0;
    r3 = memAlloc(0); // [0x8009CB2C]
    r30 = ret_8007B818;
    goto label_8007B828;
label_8007B824:;
    r30 = 0;
label_8007B828:;
    if (0 != 0) goto label_8007B83C;
    *(uint32_t*)(ret_8007B7B8 + 0x0) = 0;
    r3 = -3;
    goto label_8007B904;
label_8007B83C:;
    *(uint32_t*)(arg7_r10 + 0x0) = 0;
    r27 = 0;
label_8007B844:;
    if (0 == 0) goto label_8007B854;
    r21 = 1;
label_8007B854:;
    r0 = 0;
    *(uint32_t*)(ret_8007B7B8 + 0x4) = ret_8007B7A0;
    r0 = 0 | 0xFFFFu;
    *(uint32_t*)(ret_8007B7B8 + 0x50) = 0;
    *(uint32_t*)(ret_8007B7B8 + 0x60) = arg3_r6;
    *(uint32_t*)(ret_8007B7B8 + 0x54) = 0;
    *(uint16_t*)(ret_8007B7B8 + 0xA) = arg5_r8;
    *(uint32_t*)(ret_8007B7B8 + 0xA0) = 1;
    *(uint16_t*)(ret_8007B7B8 + 0x8) = arg0_r3;
    *(uint32_t*)(ret_8007B7B8 + 0x68) = 0;
    if (arg0_r3 != 0) goto label_8007B8A0;
    r5 = arg1_r4;
    r4 = "%s";
    r3 = ret_8007B7B8 + (168);
    r3 = sprintf(); // [0x800E6E74]
    goto label_8007B8C4;
label_8007B8A0:;
    r9 = &FileTbl;
    r4 = "%s";
    r3 = ret_8007B7B8 + (168);
    r3 = sprintf(); // [0x800E6E74]
label_8007B8C4:;
    if (0 != 0x80000000u) goto label_8007B8DC;
    r0 = *(uint32_t*)(ret_8007B7B8 + 0x0);
    *(uint32_t*)(ret_8007B7B8 + 0x0) = *(uint32_t*)(ret_8007B7B8 + 0x0);
label_8007B8DC:;
    r0 = *(uint32_t*)(ret_8007B7B8 + 0xA0);
    if (*(uint32_t*)(ret_8007B7B8 + 0xA0) != 0) goto label_8007B8F4;
    r3 = ret_8007B7B8;
    r3 = DvdLinkQueue(ret_8007B7B8); // [0x8007B918]
    goto label_8007B904;
label_8007B8F4:;
    r30 = *(uint8_t*)(ret_8007B7B8 + 0x9C);
    *(uint32_t*)(&Dvd + 0x4) = ret_8007B7B8;
    r3 = DvdReadProc(); // [0x8007B514]
    r3 = *(uint8_t*)(ret_8007B7B8 + 0x9C);
label_8007B904:;
    r0 = stack_0x3C;
    return; // r3 = *(uint8_t*)(ret_8007B7B8 + 0x9C)
}

// ============================================================================
// High-Level AST Decompilation: DvdLinkQueue(DVD_QUEUE *)
// Unit: dvd.obj | Address: 0x8007B918 | Size: 0xA4 bytes
// ============================================================================
/* [0x8007B918] */ void DvdLinkQueue(DVD_QUEUE * arg0_r3) {
    r9 = &Dvd;
    r0 = *(uint32_t*)(&Dvd + 0x8);
    if (*(uint32_t*)(&Dvd + 0x8) != 0) goto label_8007B940;
    *(uint32_t*)(&Dvd + 0x8) = arg0_r3;
    *(uint32_t*)(arg0_r3 + 0x48) = *(uint32_t*)(&Dvd + 0x8);
    goto label_8007B998;
label_8007B938:;
    *(uint32_t*)(&Dvd + 0x8) = arg0_r3;
    goto label_8007B99C;
label_8007B940:;
    r11 = *(uint32_t*)(&Dvd + 0x8);
    r10 = *(uint16_t*)(arg0_r3 + 0xA);
    goto label_8007B950;
label_8007B94C:;
    r11 = *(uint32_t*)(&Dvd + 0x8);
label_8007B950:;
    r0 = *(uint16_t*)(*(uint32_t*)(&Dvd + 0x8) + 0xA);
    if (*(uint16_t*)(arg0_r3 + 0xA) >= *(uint16_t*)(*(uint32_t*)(&Dvd + 0x8) + 0xA)) goto label_8007B984;
    *(uint32_t*)(arg0_r3 + 0x4C) = *(uint32_t*)(&Dvd + 0x8);
    r0 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x48);
    *(uint32_t*)(arg0_r3 + 0x48) = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x48);
    *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x48) = arg0_r3;
    r0 = *(uint32_t*)(&Dvd + 0x8);
    if (*(uint32_t*)(&Dvd + 0x8) == *(uint32_t*)(&Dvd + 0x8)) goto label_8007B938;
    r9 = *(uint32_t*)(arg0_r3 + 0x48);
    *(uint32_t*)(*(uint32_t*)(arg0_r3 + 0x48) + 0x4C) = arg0_r3;
    goto label_8007B99C;
label_8007B984:;
    r0 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C);
    if (*(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C) != 0) goto label_8007B94C;
    *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C) = arg0_r3;
    *(uint32_t*)(arg0_r3 + 0x48) = *(uint32_t*)(&Dvd + 0x8);
label_8007B998:;
    *(uint32_t*)(arg0_r3 + 0x4C) = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C);
label_8007B99C:;
    r0 = *(uint8_t*)(arg0_r3 + 0x9C);
    r9 = &ReadStatus;
    r11 = 1;
    r3 = *(uint8_t*)(arg0_r3 + 0x9C);
    return; // r3 = *(uint8_t*)(arg0_r3 + 0x9C)
}

// ============================================================================
// High-Level AST Decompilation: DvdControl(void)
// Unit: dvd.obj | Address: 0x8007B9BC | Size: 0xD4 bytes
// ============================================================================
/* [0x8007B9BC] */ void DvdControl(void) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r9 = &Dvd;
    r31 = &Aram;
    r0 = *(uint32_t*)(&Dvd + 0x4);
    if (*(uint32_t*)(&Dvd + 0x4) != 0) goto label_8007BA10;
    r11 = *(uint32_t*)(&Dvd + 0x8);
    if (*(uint32_t*)(&Dvd + 0x8) == 0) goto label_8007BA10;
    *(uint32_t*)(&Dvd + 0x4) = *(uint32_t*)(&Dvd + 0x8);
    r4 = &DvdReadProc(void);
    r3 = 3;
    r0 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C);
    *(uint32_t*)(&Dvd + 0x8) = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C);
    r3 = TaskExec(3, &DvdReadProc(void)); // [0x800A1B08]
label_8007BA10:;
    r0 = *(uint32_t*)(&Aram + 0x4);
    if (*(uint32_t*)(&Aram + 0x4) != 0) goto label_8007BA40;
    r9 = *(uint32_t*)(&Aram + 0x8);
    if (*(uint32_t*)(&Aram + 0x8) == 0) goto label_8007BA40;
    *(uint32_t*)(&Aram + 0x4) = *(uint32_t*)(&Aram + 0x8);
    r3 = *(uint32_t*)(&Aram + 0x8);
    r4 = 0;
    r0 = *(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x14);
    *(uint32_t*)(&Aram + 0x8) = *(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x14);
    r3 = AramDmaTrans(*(uint32_t*)(&Aram + 0x8), 0); // [0x8007C120]
label_8007BA40:;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x124);
    if (*(uint32_t*)(&Aram + 0x8) == 0) goto label_8007BA78;
    r3 = 20;
    r9 = "Loading...";
    r4 = 20;
    r5 = 208;
    r6 = 216;
    r7 = 0;
    r8 = 0;
    r3 = eprintf3(20, 20, 208, 216, 0, 0, "Loading...", r10); // [0x80081A94]
label_8007BA78:;
    r3 = DvdErrCheck(); // [0x8007BD5C]
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = ret_8007BA78
}

// ============================================================================
// High-Level AST Decompilation: DvdReadCancel(long)
// Unit: dvd.obj | Address: 0x8007BA90 | Size: 0xF0 bytes
// ============================================================================
/* [0x8007BA90] */ void DvdReadCancel(long arg0_r3) {
    // Stack frame allocated: 8 bytes
    stack_0x0C = r0;
    r10 = arg0_r3;
    r9 = &ReadStatus;
    r11 = &Dvd;
    if (r0 != 1) goto label_8007BB40;
    r3 = *(uint32_t*)(&Dvd + 0x8);
    if (*(uint32_t*)(&Dvd + 0x8) == 0) goto label_8007BB38;
    r5 = &ReadStatus;
    r7 = 0;
    r9 = *(uint32_t*)(&Dvd + 0x8);
    r6 = 64;
label_8007BAE0:;
    r0 = *(uint8_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x9C);
    if (*(uint8_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x9C) != arg0_r3) goto label_8007BB2C;
    if (*(uint32_t*)(&Dvd + 0x8) != *(uint32_t*)(&Dvd + 0x8)) goto label_8007BB00;
    r0 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C);
    *(uint32_t*)(&Dvd + 0x8) = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C);
    goto label_8007BB20;
label_8007BB00:;
    r9 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x48);
    r0 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C);
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x48) + 0x4C) = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C);
    r9 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C);
    if (*(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C) == 0) goto label_8007BB20;
    r0 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x48);
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C) + 0x48) = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x48);
label_8007BB20:;
    *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x0) = 0;
    goto label_8007BB38;
label_8007BB2C:;
    r3 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C);
    if (*(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C) != 0) goto label_8007BAE0;
label_8007BB38:;
    r3 = -2;
    goto label_8007BB70;
label_8007BB40:;
    if (*(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x48) != 2) goto label_8007BB6C;
    r3 = *(uint32_t*)(&Dvd + 0x4);
    r4 = 0;
    r3 = *(uint32_t*)(&Dvd + 0x4) + (12);
    r3 = DVDCancelAsync(); // [0x80109D34]
    r3 = -1;
    if (ret_8007BB54 != 1) goto label_8007BB70;
    r3 = 0;
    goto label_8007BB70;
label_8007BB6C:;
    r3 = -1;
label_8007BB70:;
    r0 = stack_0x0C;
    return; // r3 = -1
}

// ============================================================================
// High-Level AST Decompilation: dvdread_cancelall_cb(long, DVDCommandBlock *)
// Unit: dvd.obj | Address: 0x8007BB80 | Size: 0x18 bytes
// ============================================================================
/* [0x8007BB80] */ void dvdread_cancelall_cb(long arg0_r3, DVDCommandBlock * arg1_r4) {
    r9 = &Dvd;
    r0 = *(uint16_t*)(&Dvd + 0x2);
    *(uint16_t*)(&Dvd + 0x2) = *(uint16_t*)(&Dvd + 0x2);
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: DvdReadCancelAll(void)
// Unit: dvd.obj | Address: 0x8007BB98 | Size: 0xAC bytes
// ============================================================================
/* [0x8007BB98] */ void DvdReadCancelAll(void) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r0 = 0;
    r31 = &Dvd;
    r11 = *(uint32_t*)(&Dvd + 0x8);
    *(uint32_t*)(&Dvd + 0x8) = 0;
    if (*(uint32_t*)(&Dvd + 0x8) == 0) goto label_8007BBF0;
    r8 = 0;
    r9 = &ReadStatus;
    r10 = 64;
label_8007BBD4:;
    r0 = *(uint8_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x9C);
    *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x0) = 0;
    r11 = *(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C);
    if (*(uint32_t*)(*(uint32_t*)(&Dvd + 0x8) + 0x4C) != 0) goto label_8007BBD4;
label_8007BBF0:;
    r0 = *(uint32_t*)(&Dvd + 0x4);
    if (*(uint32_t*)(&Dvd + 0x4) == 0) goto label_8007BC08;
    r11 = *(uint32_t*)(&Dvd + 0x4);
    r0 = 0;
    *(uint32_t*)(*(uint32_t*)(&Dvd + 0x4) + 0x0) = 0;
label_8007BC08:;
    r0 = *(uint16_t*)(&Dvd + 0x2);
    r3 = &dvdread_cancelall_cb(long, DVDCommandBlock *);
    r0 = *(uint16_t*)(&Dvd + 0x2) | 0x0001u;
    *(uint16_t*)(&Dvd + 0x2) = *(uint16_t*)(&Dvd + 0x2);
    r3 = DVDCancelAllAsync(); // [0x8010A080]
label_8007BC20:;
    r0 = *(uint16_t*)(&Dvd + 0x2);
    if (*(uint32_t*)(&Dvd + 0x4) != 0) goto label_8007BC20;
    r3 = 1;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = 1
}

// ============================================================================
// High-Level AST Decompilation: pull_readqueue(DVD_WORK *)
// Unit: dvd.obj | Address: 0x8007BC44 | Size: 0xB8 bytes
// ============================================================================
/* [0x8007BC44] */ void pull_readqueue(DVD_WORK * arg0_r3) {
    // Stack frame allocated: 40 bytes
    stack_0x2C = r0;
    r28 = &DvdQueue;
    r27 = &ReadStatus;
    r29 = &DvdQueue;
    r25 = &ReadStatus + (4);
    r24 = &ReadStatus + (8);
    r26 = 1;
    r0 = &DvdQueue + (6200);
    r30 = 0;
label_8007BC7C:;
    if (r31 != 0) goto label_8007BCD4;
    r3 = &DvdQueue;
    r4 = 0;
    r5 = 200;
    r3 = memset(); // [0x800E8A5C]
    r0 = SDA1::status_idx.575;
    r9 = SDA1::status_idx.575;
    *(uint8_t*)(&DvdQueue + 0x9C) = SDA1::status_idx.575;
    r11 = SDA1::status_idx.575 + (1);
    r0 = (SDA1::status_idx.575 + 1);
    r0 = ((SDA1::status_idx.575 + 1) - (SDA1::status_idx.575 + 1));
    SDA1::status_idx.575 = ((SDA1::status_idx.575 + 1) - (SDA1::status_idx.575 + 1));
    r3 = &DvdQueue;
    goto label_8007BCE8;
label_8007BCD4:;
    r29 = &DvdQueue + (200);
    r30 = 0 + (200);
    if ((&DvdQueue + 200) <= ((SDA1::status_idx.575 + 1) - (SDA1::status_idx.575 + 1))) goto label_8007BC7C;
    r3 = 0;
label_8007BCE8:;
    r0 = stack_0x2C;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: DvdReadCheck(long, unsigned long *, unsigned long *)
// Unit: dvd.obj | Address: 0x8007BCFC | Size: 0x60 bytes
// ============================================================================
/* [0x8007BCFC] */ void DvdReadCheck(long arg0_r3, unsigned long * arg1_r4, unsigned long * arg2_r5) {
    r11 = &ReadStatus;
    if (r0 == 0) goto label_8007BD48;
    if (arg1_r4 == 0) goto label_8007BD2C;
    r9 = &ReadStatus + (4);
    *(uint32_t*)(arg1_r4 + 0x0) = r0;
label_8007BD2C:;
    if (arg2_r5 == 0) goto label_8007BD40;
    r9 = &ReadStatus + (8);
    *(uint32_t*)(arg2_r5 + 0x0) = r0;
label_8007BD40:;
    r3 = 1;
    return; // r3 = 1
label_8007BD48:;
    r3 = -1;
    r3 = 0;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: DvdErrCheck(void)
// Unit: dvd.obj | Address: 0x8007BD5C | Size: 0x278 bytes
// ============================================================================
/* [0x8007BD5C] */ void DvdErrCheck(void) {
    // Stack frame allocated: 40 bytes
    stack_0x2C = r0;
    stack_0x14 = r12;
    r3 = Snd_se_pause_check(); // [0x801381DC]
    r28 = 1;
    r9 = SDA1::pG;
    r31 = 0;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    if (r0 == 0) goto label_8007BD98;
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
label_8007BD98:;
    r29 = 0;
label_8007BDA8:;
    r3 = DVDGetDriveStatus(); // [0x80109BEC]
    if (ret_8007BDA8 == 3) goto label_8007BE20;
    if (ret_8007BDA8 > 3) goto label_8007BDDC;
    if (ret_8007BDA8 == 0) goto label_8007BE30;
    if (ret_8007BDA8 > 0) goto label_8007BDD0;
    if (ret_8007BDA8 == -1) goto label_8007BE18;
    goto label_8007BE48;
label_8007BDD0:;
    if (ret_8007BDA8 == 1) goto label_8007BE28;
    goto label_8007BE48;
label_8007BDDC:;
    if (ret_8007BDA8 == 5) goto label_8007BE08;
    if (ret_8007BDA8 < 5) goto label_8007BE00;
    if (ret_8007BDA8 == 6) goto label_8007BE10;
    if (ret_8007BDA8 != 11) goto label_8007BE48;
    r31 = 11;
    goto label_8007BE48;
label_8007BE00:;
    r31 = 4;
    goto label_8007BE48;
label_8007BE08:;
    r31 = 5;
    goto label_8007BE48;
label_8007BE10:;
    r31 = 6;
    goto label_8007BE48;
label_8007BE18:;
    r31 = -1;
    goto label_8007BE48;
label_8007BE20:;
    r31 = 3;
    goto label_8007BE48;
label_8007BE28:;
    if (3 != 0) goto label_8007BE48;
label_8007BE30:;
    if (3 == 0) goto label_8007BE44;
    if (3 != 0) goto label_8007BE44;
    if (3 != 0) goto label_8007BE44;
    r3 = Snd_se_pause_off(); // [0x801381C4]
label_8007BE44:;
    r28 = 0;
label_8007BE48:;
    if (3 <= 0x1u) goto label_8007BF9C;
    if (3 != 0x1u) goto label_8007BE8C;
    if (3 != 0x1u) goto label_8007BE5C;
    r3 = Snd_se_pause_on(); // [0x801381A0]
label_8007BE5C:;
    r4 = -1;
    r5 = 8;
    r6 = 0;
    r7 = 0;
    r3 = 1;
    r3 = SndStmReq(1, -1, 8, 0, 0); // [0x800CBC70]
    r3 = 2;
    r4 = -1;
    r5 = 8;
    r6 = 0;
    r7 = 0;
    r3 = SndStmReq(2, -1, 8, 0, 0); // [0x800CBC70]
label_8007BE8C:;
    r0 = SDA1::myBgColor;
    r3 = &stack_0x08;
    r4 = 0x00FFFFFFu;
    stack_0x08 = SDA1::myBgColor;
    r3 = GXSetCopyClear(); // [0x80121674]
    r3 = 0;
    r3 = VISetBlack(); // [0x8010E7E0]
    r3 = VibSetClear(); // [0x800AD4C4]
    r3 = Render_before(); // [0x8009D2B0]
    if (3 == 4) goto label_8007BF14;
    if (3 > 4) goto label_8007BECC;
    if (3 == -1) goto label_8007BF50;
    goto label_8007BF7C;
label_8007BECC:;
    if (3 == 6) goto label_8007BF14;
    if (3 < 6) goto label_8007BF1C;
    if (3 != -1) goto label_8007BF7C;
    r9 = &dvd_err_retry;
    r3 = 20;
    r4 = 20;
    r5 = 32;
    r6 = 196;
    r7 = 0;
    r8 = 0;
    r9 = "%s";
    r3 = eprintf3(20, 20, 32, 196, 0, 0, "%s", r10); // [0x80081A94]
    goto label_8007BF7C;
label_8007BF14:;
    r9 = &dvd_err_no_disc;
    goto label_8007BF20;
label_8007BF1C:;
    r9 = &dvd_err_cover_open;
label_8007BF20:;
    r3 = 20;
    r4 = 20;
    r5 = 32;
    r6 = 196;
    r7 = 0;
    r8 = 0;
    r9 = "%s";
    r3 = eprintf3(20, 20, 32, 196, 0, 0, "%s", r10); // [0x80081A94]
    goto label_8007BF7C;
label_8007BF50:;
    r9 = &dvd_err_fatal;
    r3 = 20;
    r4 = 20;
    r5 = 32;
    r6 = 174;
    r7 = 0;
    r8 = 0;
    r9 = "%s";
    r3 = eprintf3(20, 20, 32, 174, 0, 0, "%s", r10); // [0x80081A94]
label_8007BF7C:;
    r3 = EprintfFlush(); // [0x80081BE0]
    if (3 != -1) goto label_8007BF88;
    r3 = SndWatcher(); // [0x800CBFB8]
label_8007BF88:;
    r3 = Render_done(); // [0x8009D3CC]
    if (3 == -1) goto label_8007BF9C;
    r0 = 0;
    SDA1::Soft_reset_cnt = 0;
    r3 = SystemResetCheck(); // [0x8009D674]
label_8007BF9C:;
    if (0 != 0) goto label_8007BDA8;
    if (0 == 0) goto label_8007BFB8;
    r9 = SDA1::pG;
    r0 = *(uint32_t*)(SDA1::pG + 0x148);
    *(uint32_t*)(SDA1::pG + 0x148) = *(uint32_t*)(SDA1::pG + 0x148);
label_8007BFB8:;
    r0 = stack_0x2C;
    r12 = stack_0x14;
    return; // r3 = ret_8007BF98
}

// ============================================================================
// High-Level AST Decompilation: AramDmaTransReq(unsigned long, unsigned long, unsigned long, unsigned long, unsigned char)
// Unit: dvd.obj | Address: 0x8007BFD4 | Size: 0xD4 bytes
// ============================================================================
/* [0x8007BFD4] */ void AramDmaTransReq(unsigned long arg0_r3, unsigned long arg1_r4, unsigned long arg2_r5, unsigned long arg3_r6, unsigned char arg4_r7) {
    // Stack frame allocated: 40 bytes
    stack_0x2C = r0;
    r30 = arg0_r3;
    r29 = arg1_r4;
    r28 = arg2_r5;
    r27 = arg3_r6;
    r31 = arg4_r7;
    r3 = &stack_0x08;
    r3 = pull_aramqueue(&stack_0x08); // [0x8007C0A8]
    r11 = ret_8007BFFC;
    if (r0 != 0) goto label_8007C020;
    r3 = "No ARAM Queue\n";
    r3 = OSReport(); // [0x800F2D80]
    r3 = -1;
    goto label_8007C094;
label_8007C020:;
    *(uint32_t*)(ret_8007BFFC + 0x4) = arg0_r3;
    *(uint32_t*)(ret_8007BFFC + 0x8) = arg1_r4;
    *(uint32_t*)(ret_8007BFFC + 0xC) = arg2_r5;
    *(uint32_t*)(ret_8007BFFC + 0x10) = arg3_r6;
    if (arg4_r7 == 0) goto label_8007C050;
    r3 = ret_8007BFFC;
    *(uint32_t*)0x80188DB0 = ret_8007BFFC;
    r4 = 1;
    r3 = AramDmaTrans(ret_8007BFFC, 1); // [0x8007C120]
    goto label_8007C090;
label_8007C050:;
    r9 = &Aram;
    r0 = *(uint32_t*)(&Aram + 0x8);
    if (*(uint32_t*)(&Aram + 0x8) != 0) goto label_8007C06C;
    *(uint32_t*)(&Aram + 0x8) = ret_8007BFFC;
    goto label_8007C08C;
label_8007C06C:;
    r9 = *(uint32_t*)(&Aram + 0x8);
    goto label_8007C078;
label_8007C074:;
    r9 = *(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x14);
label_8007C078:;
    r0 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x14) + 0x14);
    if (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x14) + 0x14) != 0) goto label_8007C074;
    *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x14) + 0x14) = ret_8007BFFC;
    r0 = 0;
label_8007C08C:;
    *(uint32_t*)(ret_8007BFFC + 0x14) = 0;
label_8007C090:;
    r3 = stack_0x08;
label_8007C094:;
    r0 = stack_0x2C;
    return; // r3 = stack_0x08
}

// ============================================================================
// High-Level AST Decompilation: pull_aramqueue(unsigned long *)
// Unit: dvd.obj | Address: 0x8007C0A8 | Size: 0x54 bytes
// ============================================================================
/* [0x8007C0A8] */ void pull_aramqueue(unsigned long * arg0_r3) {
    r0 = 4;
    r8 = arg0_r3;
    r9 = &AramQueue;
    r10 = 0;
    r7 = 1;
    r3 = &AramQueue;
    r11 = 0;
label_8007C0CC:;
    if (4 != 0) goto label_8007C0E4;
    *(uint32_t*)(arg0_r3 + 0x0) = 0;
    return; // r3 = &AramQueue
label_8007C0E4:;
    r3 = &AramQueue + (24);
    r11 = 0 + (24);
    r10 = 0 + (1);
    if (4 >= 0) goto label_8007C0CC;
    r3 = 0;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: aram_cb(unsigned long)
// Unit: dvd.obj | Address: 0x8007C0FC | Size: 0x24 bytes
// ============================================================================
/* [0x8007C0FC] */ void aram_cb(unsigned long arg0_r3) {
    r10 = 0;
    r9 = &Aram;
    r11 = *(uint32_t*)(&Aram + 0x4);
    r0 = *(uint32_t*)(*(uint32_t*)(&Aram + 0x4) + 0x0);
    r0 = *(uint32_t*)(*(uint32_t*)(&Aram + 0x4) + 0x0) | 0x0002u;
    *(uint32_t*)(*(uint32_t*)(&Aram + 0x4) + 0x0) = *(uint32_t*)(*(uint32_t*)(&Aram + 0x4) + 0x0);
    *(uint32_t*)(&Aram + 0x4) = 0;
    return; // r3 = arg0_r3
}

// ============================================================================
// High-Level AST Decompilation: AramDmaTrans(ARAM_QUEUE *, unsigned char)
// Unit: dvd.obj | Address: 0x8007C120 | Size: 0xB8 bytes
// ============================================================================
/* [0x8007C120] */ void AramDmaTrans(ARAM_QUEUE * arg0_r3, unsigned char arg1_r4) {
    // Stack frame allocated: 24 bytes
    stack_0x1C = r0;
    r31 = arg0_r3;
    r11 = *(uint32_t*)(arg0_r3 + 0x10);
    r29 = &Aram;
    r30 = arg1_r4;
    if (*(uint32_t*)(arg0_r3 + 0x10) == 0) goto label_8007C158;
    r0 = *(uint32_t*)(arg0_r3 + 0x10) + (31);
    goto label_8007C15C;
label_8007C158:;
    r9 = 0;
label_8007C15C:;
    r0 = *(uint32_t*)(arg0_r3 + 0x4);
    *(uint32_t*)(arg0_r3 + 0x10) = 0;
    if (*(uint32_t*)(arg0_r3 + 0x4) != 0) goto label_8007C174;
    r3 = *(uint32_t*)(arg0_r3 + 0x8);
    goto label_8007C178;
label_8007C174:;
    r3 = *(uint32_t*)(arg0_r3 + 0xC);
label_8007C178:;
    r4 = *(uint32_t*)(arg0_r3 + 0x10);
    r3 = DCFlushRange(); // [0x800F1970]
    r5 = *(uint32_t*)(arg0_r3 + 0x4);
    r7 = *(uint32_t*)(arg0_r3 + 0x8);
    r3 = &Aram + (12);
    r8 = *(uint32_t*)(arg0_r3 + 0xC);
    r10 = &aram_cb(unsigned long);
    r9 = *(uint32_t*)(arg0_r3 + 0x10);
    r4 = 0;
    r6 = 1;
    r3 = ARQPostRequest(); // [0x80113F70]
    if (*(uint32_t*)(arg0_r3 + 0x4) == 0) goto label_8007C1C4;
    r9 = 0;
label_8007C1B4:;
    r0 = *(uint32_t*)(arg0_r3 + 0x0);
    if (*(uint32_t*)(arg0_r3 + 0x4) == 0) goto label_8007C1B4;
    *(uint32_t*)(arg0_r3 + 0x0) = 0;
label_8007C1C4:;
    r0 = stack_0x1C;
    return; // r3 = ret_8007C1A4
}

// ============================================================================
// High-Level AST Decompilation: AramTransCheck(long)
// Unit: dvd.obj | Address: 0x8007C1D8 | Size: 0x38 bytes
// ============================================================================
/* [0x8007C1D8] */ void AramTransCheck(long arg0_r3) {
    r9 = &AramQueue;
    if (r0 == 0) goto label_8007C1F8;
    if (r0 == 0) goto label_8007C208;
label_8007C1F8:;
    r0 = 0;
    r3 = 1;
    return; // r3 = 1
label_8007C208:;
    r3 = 0;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: AramDmaCancelAll(void)
// Unit: dvd.obj | Address: 0x8007C210 | Size: 0xB0 bytes
// ============================================================================
/* [0x8007C210] */ void AramDmaCancelAll(void) {
    // Stack frame allocated: 16 bytes
    stack_0x14 = r0;
    r31 = 0;
    r30 = &Aram;
    r0 = *(uint32_t*)(&Aram + 0x4);
    if (*(uint32_t*)(&Aram + 0x4) == 0) goto label_8007C270;
    r9 = &AramQueue;
label_8007C240:;
    if (*(uint32_t*)(&Aram + 0x4) != &AramQueue) goto label_8007C25C;
label_8007C248:;
    r3 = 0;
    r3 = AramTransCheck(0); // [0x8007C1D8]
    if (ret_8007C24C == 0) goto label_8007C248;
    goto label_8007C26C;
label_8007C25C:;
    r31 = 0 + (1);
    r9 = &AramQueue + (24);
    if ((0 + 1) <= 3) goto label_8007C240;
label_8007C26C:;
    r31 = 1;
label_8007C270:;
    r9 = *(uint32_t*)(&Aram + 0x8);
    if (*(uint32_t*)(&Aram + 0x8) == 0) goto label_8007C2A4;
    r0 = *(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x14);
    if (*(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x14) == 0) goto label_8007C2A0;
    r11 = 0;
label_8007C28C:;
    *(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x0) = 0;
    r9 = *(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x14);
    r0 = *(uint32_t*)(*(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x14) + 0x14);
    if (*(uint32_t*)(*(uint32_t*)(*(uint32_t*)(&Aram + 0x8) + 0x14) + 0x14) != 0) goto label_8007C28C;
label_8007C2A0:;
    r31 = 1;
label_8007C2A4:;
    r3 = ARQFlushQueue(); // [0x801142A4]
    r3 = 1;
    r0 = stack_0x14;
    return; // r3 = 1
}

// ============================================================================
// High-Level AST Decompilation: MemorySwap(void *, void *, unsigned long)
// Unit: dvd.obj | Address: 0x8007C2C0 | Size: 0xB4 bytes
// ============================================================================
/* [0x8007C2C0] */ void MemorySwap(void * arg0_r3, void * arg1_r4, unsigned long arg2_r5) {
    // Stack frame allocated: 32 bytes
    stack_0x24 = r0;
    r5 = arg2_r5 + (31);
    r28 = arg0_r3;
    r29 = arg1_r4;
    if (r0 == 0) goto label_8007C35C;
label_8007C2E8:;
    r31 = r30;
    if (r30 <= 0x00040000u) goto label_8007C2F8;
label_8007C2F8:;
    r4 = arg0_r3;
    r5 = 0x00040000u;
    r30 = (r30 - 0x00040000u);
    r3 = memcpy(); // [0x800E88CC]
    r4 = arg1_r4;
    r6 = 0x00040000u;
    r7 = 1;
    r3 = 1;
    r3 = AramDmaTransReq(1, arg1_r4, 0x803C0000u, 0x00040000u, 1); // [0x8007BFD4]
    r3 = arg0_r3;
    r5 = 0x00040000u;
    r28 = (arg0_r3 + 0x00040000u);
    r3 = memcpy(); // [0x800E88CC]
    r5 = arg1_r4;
    r3 = 0;
    r6 = 0x00040000u;
    r7 = 1;
    r29 = (arg1_r4 + 0x00040000u);
    r3 = AramDmaTransReq(0, 0x80380000u, arg1_r4, 0x00040000u, 1); // [0x8007BFD4]
    if ((r30 - 0x00040000u) != 0) goto label_8007C2E8;
label_8007C35C:;
    r3 = 1;
    r0 = stack_0x24;
    return; // r3 = 1
}

// ============================================================================
// High-Level AST Decompilation: DvdFindFirst(char *, DVDFindFile *)
// Unit: dvd.obj | Address: 0x8007C374 | Size: 0x5C bytes
// ============================================================================
/* [0x8007C374] */ void DvdFindFirst(char * arg0_r3, DVDFindFile * arg1_r4) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r31 = arg1_r4;
    r3 = DVDOpenDir(); // [0x801065F8]
    r3 = 0;
    if (ret_8007C388 == 0) goto label_8007C3BC;
    r3 = arg1_r4;
    r4 = arg1_r4 + (12);
    r3 = DVDReadDir(); // [0x801066B8]
    r3 = 1;
    if (ret_8007C3A0 != 0) goto label_8007C3BC;
    r3 = arg1_r4;
    r3 = DVDCloseDir(); // [0x8010675C]
    r3 = 0;
label_8007C3BC:;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = 0
}

// ============================================================================
// High-Level AST Decompilation: DvdFindNext(DVDFindFile *)
// Unit: dvd.obj | Address: 0x8007C3D0 | Size: 0x48 bytes
// ============================================================================
/* [0x8007C3D0] */ void DvdFindNext(DVDFindFile * arg0_r3) {
    // Stack frame allocated: 16 bytes
    stack_0x0C = r31;
    stack_0x14 = r0;
    r31 = arg0_r3;
    r4 = arg0_r3 + (12);
    r3 = DVDReadDir(); // [0x801066B8]
    r3 = 1;
    if (ret_8007C3E8 != 0) goto label_8007C404;
    r3 = arg0_r3;
    r3 = DVDCloseDir(); // [0x8010675C]
    r3 = 0;
label_8007C404:;
    r0 = stack_0x14;
    r31 = stack_0x0C;
    return; // r3 = 0
}
