#pragma once

#include "pn03_config.hpp"
#include "pn03_ppc_context.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <vector>

namespace pn03 {

// Dolphin SDK Audio Interface (AI), Auxiliary DSP (AX), ARAM (AR/ARQ), and DSP
// Host Mixer + XAudio2 Stereo Output Engine for P.N.03 (GPNE08).
class AudioAXInterface {
public:
    static constexpr uint32_t kAramSizeBytes      = 16u * 1024u * 1024u;
    static constexpr uint32_t kMaxVoices          = 64u;
    static constexpr uint32_t kAxVpbBase          = 0x802614E0u;
    static constexpr uint32_t kAxVpbStride        = 548u;
    static constexpr uint32_t kDefaultSampleRate  = 32000u;

    explicit AudioAXInterface(const RuntimeConfig& cfg);
    ~AudioAXInterface();

    AudioAXInterface(const AudioAXInterface&) = delete;
    AudioAXInterface& operator=(const AudioAXInterface&) = delete;

    // Host audio device lifecycle & configuration
    bool initialize_audio_device();
    void shutdown_audio_device();
    void reset_state();
    void set_config(const RuntimeConfig& cfg);
    const RuntimeConfig& config() const { return cfg_; }

    // Dolphin DSP 4-bit ADPCM frame decoder (8 bytes -> 14 PCM16 samples)
    static void decode_dsp_adpcm_frame(
        const uint8_t adpcm_frame[8],
        const int16_t coefs[16],
        int16_t& hist1,
        int16_t& hist2,
        int16_t out_pcm[14]);

    // Step guest AX/AI callbacks and mix & submit one audio frame (~16.6ms @ 60Hz)
    void step_audio_frame(PPCContext& ctx, Memory& mem, size_t num_samples = 540);

    // Mix active AXVPB voices + AI DMA PCM into stereo interleaved int16 (L,R) and queue to XAudio2
    std::vector<int16_t> mix_stereo_frame(const Memory& mem, size_t num_samples = 540);

    // ARAM DMA transfer helper (type 0: MainRAM -> ARAM, type 1: ARAM -> MainRAM)
    void aram_dma_transfer(uint32_t type, uint32_t mmem_addr, uint32_t aram_addr, uint32_t length, Memory& mem);
    uint32_t aram_alloc(uint32_t size);
    void aram_free(uint32_t* out_size = nullptr);

    // HLE dispatch for AI, AR, ARQ, AX, and DSP calls in dolphin_sdk_hle.cpp
    bool dispatch_audio_call(uint32_t vaddr, PPCContext& ctx, Memory& mem);

    // Diagnostics & unit-test state queries
    size_t   active_voice_count() const;
    bool     is_dma_enabled() const { return dma_enabled_; }
    uint32_t ai_dma_addr() const { return ai_dma_addr_; }
    uint32_t ai_dma_len() const { return ai_dma_len_; }
    uint32_t ax_user_callback() const { return ax_user_callback_; }
    uint32_t ai_dma_callback() const { return ai_dma_callback_; }
    uint32_t dsp_sample_rate() const { return dsp_sample_rate_; }
    uint32_t ax_callback_invocations() const { return ax_callback_invocations_; }
    uint64_t total_mixed_frames() const { return total_mixed_frames_; }
    bool     has_xaudio_output() const { return xaudio_ready_; }
    size_t   queued_xaudio_buffers() const;
    uint64_t dropped_xaudio_buffers() const { return dropped_xaudio_buffers_; }
    const std::vector<uint8_t>& aram_bytes() const { return aram_; }

private:
    struct HostVoiceState {
        bool     active = false;
        bool     finished = false;
        bool     decoded_valid = false;
        uint32_t last_guest_cur_addr = 0;
        uint32_t last_guest_end_addr = 0;
        uint32_t last_decoded_unit = 0;
        uint64_t cur_addr_fp = 0; // 48.16 fixed-point ARAM address (nibbles for ADPCM, words for PCM16, bytes for PCM8)
        int16_t  prev_sample = 0;
        int16_t  cur_sample = 0;
        int16_t  hist1 = 0;
        int16_t  hist2 = 0;
        uint8_t  pred_scale = 0;
    };

    void submit_xaudio2_pcm(const int16_t* stereo_pcm, size_t num_frames);
    void mix_voices_locked(const Memory& mem, std::vector<int32_t>& accum_lr, size_t num_samples, size_t& out_active_count);
    void mix_ai_dma_locked(const Memory& mem, std::vector<int32_t>& accum_lr, size_t num_samples);
    void invoke_ppc_callback(uint32_t cb_vaddr, PPCContext& ctx, Memory& mem);

    RuntimeConfig cfg_;
    mutable std::mutex mtx_;

    // Dolphin AI state
    bool     ai_initialized_     = false;
    bool     dma_enabled_        = false;
    uint32_t ai_dma_addr_        = 0;
    uint32_t ai_dma_len_         = 0;
    uint32_t ai_dma_read_off_    = 0;
    uint32_t ai_dma_callback_    = 0;
    uint32_t ai_stream_callback_ = 0;
    uint32_t dsp_sample_rate_    = kDefaultSampleRate;
    uint32_t stream_sample_rate_ = 48000u;
    uint32_t stream_play_state_  = 0;
    uint32_t stream_vol_left_    = 255u;
    uint32_t stream_vol_right_   = 255u;

    // Dolphin AR / DSP / AX state
    bool     ar_initialized_          = false;
    uint32_t ar_callback_             = 0;
    uint32_t ar_stack_ptr_            = 0x00004000u;
    std::vector<uint32_t> ar_alloc_stack_;
    uint32_t arq_chunk_size_          = 4096u;
    bool     dsp_initialized_         = false;
    uint32_t dsp_mail_pending_        = 0;
    uint32_t dsp_mail_value_          = 0;
    bool     ax_initialized_          = false;
    uint32_t ax_mode_                 = 0;
    uint32_t ax_user_callback_        = 0;
    uint32_t ax_aux_a_callback_       = 0;
    uint32_t ax_aux_b_callback_       = 0;
    uint32_t ax_max_dsp_cycles_       = 0;
    uint32_t ax_sample_accum_         = 0;
    uint32_t ax_callback_invocations_ = 0;
    uint64_t total_mixed_frames_      = 0;
    size_t   last_active_voices_      = 0;
    bool     in_callback_             = false;

    // 16 MB emulated GameCube ARAM + per-voice playback state
    std::vector<uint8_t> aram_;
    std::array<HostVoiceState, kMaxVoices> host_voices_{};

    // XAudio2 COM handles & pre-allocated ring buffers (pimpl pointers to avoid Windows header leak)
    struct XAudioImpl;
    XAudioImpl* xaudio_                 = nullptr;
    bool        xaudio_ready_           = false;
    uint64_t    dropped_xaudio_buffers_ = 0;
};

using AudioAXHLE = AudioAXInterface;

AudioAXInterface& global_audio_ax_interface();

} // namespace pn03
