#pragma once
#include "pn03_ppc_context.hpp"
#include <cstddef>
#include <cstdint>

namespace pn03::recomp {

struct SymbolEntry {
    uint32_t    address;
    uint32_t    size;
    const char* unit;
    const char* name;
    bool        is_game_code;
};

extern const SymbolEntry kMasterCodeSymbolTable[];
extern const size_t      kMasterCodeSymbolCount;

// Key Verified P.N.03 (GPNE08) Global Symbol Addresses from MEKA.sym
namespace sym_addr {
    constexpr uint32_t kMain                  = 0x8009C4DCu;
    constexpr uint32_t kSystemStartInit       = 0x8009C5B8u;
    constexpr uint32_t kSystemRestartInit     = 0x8009C65Cu;
    constexpr uint32_t kSystemWorkInit        = 0x8009C778u;
    constexpr uint32_t kRenderInit            = 0x800D9CF0u;
    constexpr uint32_t kRender_init           = 0x8009D098u;
    constexpr uint32_t kRender_before         = 0x8009D2B0u;
    constexpr uint32_t kRender                = 0x800D9D10u;
    constexpr uint32_t kFlipTransBuffer       = 0x8009D00Cu;
    constexpr uint32_t kClearOt               = 0x800DC780u;
    constexpr uint32_t kScheduler             = 0x800A18E4u;
    constexpr uint32_t kTrans                 = 0x800D91CCu;
    constexpr uint32_t kTitleTask             = 0x800D7A58u;

    // Input (pad.obj & Dolphin PAD SDK)
    constexpr uint32_t kPadInit               = 0x800ACBECu;
    constexpr uint32_t kPadRead               = 0x800ACC2Cu;
    constexpr uint32_t kVibControl            = 0x800AD160u;
    constexpr uint32_t kSDK_PADInit           = 0x80110014u;
    constexpr uint32_t kSDK_PADRead           = 0x8011022Cu;
    constexpr uint32_t kSDK_PADClamp          = 0x8010F228u;

    // DVD & LZS Compression (dvd.obj, read.obj, compless.obj)
    constexpr uint32_t kDvdInit               = 0x8007B5D4u;
    constexpr uint32_t kDvdFileExistCheck     = 0x8007B6E8u;
    constexpr uint32_t kDvdReadReqMain        = 0x8007B744u;
    constexpr uint32_t kReadCompressData      = 0x800BFB2Cu;
    constexpr uint32_t kLzsDecode             = 0x80077680u;

    // Localization, Font & Message Engine (mes.obj, cockpit.obj, option.obj)
    constexpr uint32_t kMesInit               = 0x8009F0A4u;
    constexpr uint32_t kMesSetLanguage        = 0x8009F12Cu;
    constexpr uint32_t kMesGetLanguage        = 0x8009F138u;
    constexpr uint32_t kGetFontTexAddr        = 0x8009F274u;
    constexpr uint32_t kGetFontSize           = 0x8009F2BCu;
    constexpr uint32_t kGetMesDataAddr        = 0x8009F340u;
    constexpr uint32_t kCreateFont            = 0x8009F384u;
    constexpr uint32_t kFontDraw              = 0x800A00DCu;
    constexpr uint32_t kCockpitSetLanguage    = 0x80076578u;

    // Relocatable Module Loader (OSLink.o -> module/Tools.rel)
    constexpr uint32_t kSDK_OSLink            = 0x800F56E0u;
    constexpr uint32_t kSDK_OSLinkFixed       = 0x800F5704u;

    // BSS & SDA Global Data Variables
    constexpr uint32_t kGlobalStruct          = 0x801959C0u; // Global
    constexpr uint32_t kJoyStruct             = 0x8019D680u; // Joy
    constexpr uint32_t kKeyStruct             = 0x8019E020u; // Key
    constexpr uint32_t kPadData               = 0x801C4A68u; // Pad_data (PADStatus[4])
    constexpr uint32_t kSda_pG                = 0x8026E754u; // pG (r13 - 29836)
    constexpr uint32_t kSda_pFrameBuff        = 0x8026E758u; // pFrame_buff
    constexpr uint32_t kSda_pCurrentBuff      = 0x8026E760u; // pCurrent_buff
    constexpr uint32_t kSda_ZNEAR             = 0x8026E76Cu; // ZNEAR
    constexpr uint32_t kSda_ZFAR              = 0x8026E770u; // ZFAR
    constexpr uint32_t kSda_ORTHO_T           = 0x8026E774u; // ORTHO_T (0.0f)
    constexpr uint32_t kSda_ORTHO_B           = 0x8026E778u; // ORTHO_B (480.0f)
    constexpr uint32_t kSda_ORTHO_L           = 0x8026E77Cu; // ORTHO_L (0.0f)
    constexpr uint32_t kSda_ORTHO_R           = 0x8026E780u; // ORTHO_R (640.0f)
}

} // namespace pn03::recomp
