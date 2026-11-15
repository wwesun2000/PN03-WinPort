#include "pn03_audio_ax.hpp"
#include "pn03_runtime.hpp"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <objbase.h>
#include <xaudio2.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace pn03 {

namespace {

// Verified P.N.03 (GPNE08) Dolphin SDK SDA1/sbss addresses from meka_symbols_full.json
constexpr uint32_t kSymAISCallback        = 0x8026EB90u;
constexpr uint32_t kSymAIDCallback        = 0x8026EB94u;
constexpr uint32_t kSymAIInitFlag         = 0x8026EBA0u;
constexpr uint32_t kSymAIDActive          = 0x8026EBA4u;
constexpr uint32_t kSymARCallback         = 0x8026EBE0u;
constexpr uint32_t kSymARSize             = 0x8026EBE4u;
constexpr uint32_t kSymARStackPointer     = 0x8026EBF0u;
constexpr uint32_t kSymARInitFlag         = 0x8026EBFCu;
constexpr uint32_t kSymARQInitFlag        = 0x8026EC2Cu;
constexpr uint32_t kSymAXClMode           = 0x8026EE48u;
constexpr uint32_t kSymAXOutFrame         = 0x8026EE50u;
constexpr uint32_t kSymAXOutDspReady      = 0x8026EE54u;
constexpr uint32_t kSymAXUserFrameCb      = 0x8026EE60u;
constexpr uint32_t kSymAXDSPInitFlag      = 0x8026EE64u;
constexpr uint32_t kSymAXDSPDoneFlag      = 0x8026EE68u;
constexpr uint32_t kSymAXNumVoices        = 0x8026EEA8u;
constexpr uint32_t kSymDSPInitFlag        = 0x8026EEF0u;

// Dolphin SDK internal AX init helpers (safe data init without HW DSP spin)
constexpr uint32_t kFnAXAllocInit         = 0x80151594u;
constexpr uint32_t kFnAXVPBInit           = 0x80153DD0u;
constexpr uint32_t kFnAXSPBInit           = 0x801532C8u;
constexpr uint32_t kFnAXAuxInit           = 0x80151B64u;
constexpr uint32_t kFnAXClInit            = 0x80152710u;
constexpr uint32_t kFnAXSyncPBs           = 0x80153B20u;

// Dolphin SDK AXOut AI callback range so we don't confuse AX internal DMA with THP DMA
constexpr uint32_t kAXOutCodeStart        = 0x80152710u;
constexpr uint32_t kAXOutCodeEnd          = 0x80152E50u;

constexpr uint32_t kPGGlobalPtr           = 0x8026E754u;

inline int16_t clamp_s16(int32_t v) {
    if (v > 32767) return 32767;
    if (v < -32768) return -32768;
    return static_cast<int16_t>(v);
}

inline bool is_valid_code_vaddr(uint32_t va) {
    return va >= 0x80003100u && va < 0x80400000u && (va & 3u) == 0u;
}

inline bool is_valid_ram_vaddr(uint32_t va) {
    return va >= 0x80000000u && va < 0x81800000u;
}

RuntimeConfig g_ax_default_cfg{};

} // namespace

struct AudioAXInterface::XAudioImpl {
    static constexpr size_t kRingCount    = 24;
    static constexpr size_t kMaxFramesBuf = 2048;

    IXAudio2*               engine       = nullptr;
    IXAudio2MasteringVoice* mastering    = nullptr;
    IXAudio2SourceVoice*    source       = nullptr;
    bool                    com_inited   = false;
    uint32_t                sample_rate  = AudioAXInterface::kDefaultSampleRate;
    size_t                  ring_cursor  = 0;
    std::array<std::vector<int16_t>, kRingCount> ring_buffers{};

    XAudioImpl() {
        for (auto& buf : ring_buffers) {
            buf.resize(kMaxFramesBuf * 2u, 0);
        }
    }
};

AudioAXInterface& global_audio_ax_interface() {
    static AudioAXInterface instance(g_ax_default_cfg);
    return instance;
}

AudioAXInterface::AudioAXInterface(const RuntimeConfig& cfg)
    : cfg_(cfg), aram_(kAramSizeBytes, 0) {}

AudioAXInterface::~AudioAXInterface() {
    shutdown_audio_device();
}

void AudioAXInterface::set_config(const RuntimeConfig& cfg) {
    std::lock_guard<std::mutex> lock(mtx_);
    cfg_ = cfg;
    if (xaudio_ && xaudio_->source) {
        const float vol = cfg_.audio_muted ? 0.0f : std::clamp(cfg_.audio_volume, 0.0f, 1.0f);
        xaudio_->source->SetVolume(vol);
    }
}

void AudioAXInterface::reset_state() {
    std::lock_guard<std::mutex> lock(mtx_);
    ai_initialized_          = false;
    dma_enabled_             = false;
    ai_dma_addr_             = 0;
    ai_dma_len_              = 0;
    ai_dma_read_off_         = 0;
    ai_dma_callback_         = 0;
    ai_stream_callback_      = 0;
    dsp_sample_rate_         = kDefaultSampleRate;
    stream_sample_rate_      = 48000u;
    stream_play_state_       = 0;
    stream_vol_left_         = 255u;
    stream_vol_right_        = 255u;
    ar_initialized_          = false;
    ar_callback_             = 0;
    ar_stack_ptr_            = 0x00004000u;
    ar_alloc_stack_.clear();
    arq_chunk_size_          = 4096u;
    dsp_initialized_         = false;
    dsp_mail_pending_        = 0;
    dsp_mail_value_          = 0;
    ax_initialized_          = false;
    ax_mode_                 = 0;
    ax_user_callback_        = 0;
    ax_aux_a_callback_       = 0;
    ax_aux_b_callback_       = 0;
    ax_max_dsp_cycles_       = 0;
    ax_sample_accum_         = 0;
    ax_callback_invocations_ = 0;
    total_mixed_frames_      = 0;
    last_active_voices_      = 0;
    dropped_xaudio_buffers_  = 0;
    in_callback_             = false;
    std::fill(aram_.begin(), aram_.end(), 0);
    for (auto& hv : host_voices_) {
        hv = HostVoiceState{};
    }
}

bool AudioAXInterface::initialize_audio_device() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (xaudio_ready_ && xaudio_ && xaudio_->source) {
        return true;
    }

    auto* impl = new XAudioImpl();
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr)) {
        impl->com_inited = true;
    } else if (hr != RPC_E_CHANGED_MODE) {
        // Proceed anyway if COM was already initialized with compatible flags
        impl->com_inited = false;
    }

    hr = XAudio2Create(&impl->engine, 0, XAUDIO2_DEFAULT_PROCESSOR);
    if (FAILED(hr) || !impl->engine) {
        if (impl->com_inited) CoUninitialize();
        delete impl;
        xaudio_ready_ = false;
        return false;
    }

    hr = impl->engine->CreateMasteringVoice(&impl->mastering);
    if (FAILED(hr) || !impl->mastering) {
        impl->engine->Release();
        if (impl->com_inited) CoUninitialize();
        delete impl;
        xaudio_ready_ = false;
        return false;
    }

    WAVEFORMATEX wfx{};
    wfx.wFormatTag      = WAVE_FORMAT_PCM;
    wfx.nChannels       = 2;
    wfx.nSamplesPerSec  = dsp_sample_rate_ ? dsp_sample_rate_ : kDefaultSampleRate;
    wfx.wBitsPerSample  = 16;
    wfx.nBlockAlign     = 4;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
    wfx.cbSize          = 0;
    impl->sample_rate   = wfx.nSamplesPerSec;

    hr = impl->engine->CreateSourceVoice(
        &impl->source,
        &wfx,
        0,
        XAUDIO2_DEFAULT_FREQ_RATIO,
        nullptr,
        nullptr,
        nullptr);
    if (FAILED(hr) || !impl->source) {
        impl->mastering->DestroyVoice();
        impl->engine->Release();
        if (impl->com_inited) CoUninitialize();
        delete impl;
        xaudio_ready_ = false;
        return false;
    }

    const float vol = cfg_.audio_muted ? 0.0f : std::clamp(cfg_.audio_volume, 0.0f, 1.0f);
    impl->source->SetVolume(vol);
    impl->source->Start(0);

    xaudio_       = impl;
    xaudio_ready_ = true;
    return true;
}

void AudioAXInterface::shutdown_audio_device() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!xaudio_) {
        xaudio_ready_ = false;
        return;
    }
    if (xaudio_->source) {
        xaudio_->source->Stop(0);
        xaudio_->source->FlushSourceBuffers();
        xaudio_->source->DestroyVoice();
        xaudio_->source = nullptr;
    }
    if (xaudio_->mastering) {
        xaudio_->mastering->DestroyVoice();
        xaudio_->mastering = nullptr;
    }
    if (xaudio_->engine) {
        xaudio_->engine->Release();
        xaudio_->engine = nullptr;
    }
    if (xaudio_->com_inited) {
        CoUninitialize();
        xaudio_->com_inited = false;
    }
    delete xaudio_;
    xaudio_       = nullptr;
    xaudio_ready_ = false;
}

void AudioAXInterface::decode_dsp_adpcm_frame(
    const uint8_t adpcm_frame[8],
    const int16_t coefs[16],
    int16_t& hist1,
    int16_t& hist2,
    int16_t out_pcm[14]) {
    const uint8_t header = adpcm_frame[0];
    const uint32_t pred  = (header >> 4) & 0x7u;
    const uint32_t scale = 1u << (header & 0xFu);
    const int32_t  c1    = coefs[pred * 2u];
    const int32_t  c2    = coefs[pred * 2u + 1u];

    int32_t h1 = hist1;
    int32_t h2 = hist2;
    for (int i = 0; i < 14; ++i) {
        const uint8_t byte = adpcm_frame[1 + (i >> 1)];
        int32_t nib = (i & 1) ? (byte & 0x0Fu) : ((byte >> 4) & 0x0Fu);
        if (nib >= 8) {
            nib -= 16;
        }
        const int32_t raw    = (nib * static_cast<int32_t>(scale) * 2048) + (c1 * h1) + (c2 * h2) + 1024;
        const int16_t sample = clamp_s16(raw >> 11);
        out_pcm[i] = sample;
        h2 = h1;
        h1 = sample;
    }
    hist1 = static_cast<int16_t>(h1);
    hist2 = static_cast<int16_t>(h2);
}

size_t AudioAXInterface::queued_xaudio_buffers() const {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!xaudio_ready_ || !xaudio_ || !xaudio_->source) {
        return 0u;
    }
    XAUDIO2_VOICE_STATE vs{};
    xaudio_->source->GetState(&vs, XAUDIO2_VOICE_NOSAMPLESPLAYED);
    return static_cast<size_t>(vs.BuffersQueued);
}

void AudioAXInterface::submit_xaudio2_pcm(const int16_t* stereo_pcm, size_t num_frames) {
    if (!xaudio_ready_ || !xaudio_ || !xaudio_->source || !stereo_pcm || num_frames == 0) {
        return;
    }

    if (xaudio_->sample_rate != dsp_sample_rate_ && dsp_sample_rate_ > 0) {
        xaudio_->source->SetFrequencyRatio(static_cast<float>(dsp_sample_rate_) / static_cast<float>(xaudio_->sample_rate));
    }

    XAUDIO2_VOICE_STATE vs{};
    xaudio_->source->GetState(&vs, XAUDIO2_VOICE_NOSAMPLESPLAYED);
    if (vs.BuffersQueued >= XAudioImpl::kRingCount) {
        ++dropped_xaudio_buffers_;
        return;
    }

    const size_t clamped_frames = std::min(num_frames, XAudioImpl::kMaxFramesBuf);
    auto& slot = xaudio_->ring_buffers[xaudio_->ring_cursor];
    xaudio_->ring_cursor = (xaudio_->ring_cursor + 1u) % XAudioImpl::kRingCount;
    std::memcpy(slot.data(), stereo_pcm, clamped_frames * 2u * sizeof(int16_t));

    const float vol = cfg_.audio_muted ? 0.0f : std::clamp(cfg_.audio_volume, 0.0f, 1.0f);
    xaudio_->source->SetVolume(vol);

    XAUDIO2_BUFFER xbuf{};
    xbuf.AudioBytes = static_cast<UINT32>(clamped_frames * 2u * sizeof(int16_t));
    xbuf.pAudioData = reinterpret_cast<const BYTE*>(slot.data());
    xaudio_->source->SubmitSourceBuffer(&xbuf);
}

void AudioAXInterface::mix_voices_locked(
    const Memory& mem,
    std::vector<int32_t>& accum_lr,
    size_t num_samples,
    size_t& out_active_count) {
    out_active_count = 0;
    const uint32_t aram_bytes = static_cast<uint32_t>(aram_.size());

    for (uint32_t v = 0; v < kMaxVoices; ++v) {
        const uint32_t vp = kAxVpbBase + v * kAxVpbStride;
        const uint16_t state = mem.read_u16(vp + 326u);
        HostVoiceState& hv = host_voices_[v];

        if (state != 1u) {
            hv.active   = false;
            hv.finished = false;
            continue;
        }
        if (hv.finished) {
            continue;
        }

        const uint16_t loop_flag = mem.read_u16(vp + 422u);
        const uint16_t format    = mem.read_u16(vp + 424u);
        const uint32_t loop_addr = (static_cast<uint32_t>(mem.read_u16(vp + 426u)) << 16) | mem.read_u16(vp + 428u);
        const uint32_t end_addr  = (static_cast<uint32_t>(mem.read_u16(vp + 430u)) << 16) | mem.read_u16(vp + 432u);
        uint32_t       cur_addr  = (static_cast<uint32_t>(mem.read_u16(vp + 434u)) << 16) | mem.read_u16(vp + 436u);

        auto align_adpcm_unit = [](uint32_t u) noexcept -> uint32_t {
            return ((u & 0xFu) < 2u) ? ((u & ~0xFu) + 2u) : u;
        };
        const bool can_loop = (loop_flag != 0u) && (loop_addr < end_addr);

        if (end_addr == 0u) {
            hv.active = false;
            continue;
        }
        bool wrapped_on_entry = false;
        if (cur_addr >= end_addr) {
            if (!can_loop) {
                hv.active = false;
                continue;
            }
            // A looping stream voice (e.g. Capcom SND_STR 8-block ARAM ring) whose guest cursor already sits on /
            // past end_addr must wrap to loop_addr like the real DSP does, never be silenced permanently.
            cur_addr         = (format == 0u) ? align_adpcm_unit(loop_addr) : loop_addr;
            wrapped_on_entry = true;
        }

        if (!hv.active || hv.last_guest_cur_addr != cur_addr || wrapped_on_entry) {
            // Fresh voice start or explicit guest seek
            hv.active              = true;
            hv.finished            = false;
            hv.decoded_valid       = false;
            hv.last_guest_cur_addr = cur_addr;
            hv.last_guest_end_addr = end_addr;
            hv.cur_addr_fp         = static_cast<uint64_t>(cur_addr) << 16;
            hv.hist1               = static_cast<int16_t>(mem.read_u16(vp + 474u));
            hv.hist2               = static_cast<int16_t>(mem.read_u16(vp + 476u));
            hv.prev_sample         = hv.hist2;
            hv.cur_sample          = hv.hist1;
            hv.pred_scale          = static_cast<uint8_t>(mem.read_u16(vp + 472u) & 0xFFu);
            if (wrapped_on_entry && format == 0u) {
                const uint16_t l_pred = mem.read_u16(vp + 492u);
                const int16_t  l_yn1  = static_cast<int16_t>(mem.read_u16(vp + 494u));
                const int16_t  l_yn2  = static_cast<int16_t>(mem.read_u16(vp + 496u));
                if (l_pred != 0u || l_yn1 != 0 || l_yn2 != 0) {
                    hv.pred_scale  = static_cast<uint8_t>(l_pred & 0xFFu);
                    hv.hist1       = l_yn1;
                    hv.hist2       = l_yn2;
                    hv.prev_sample = l_yn2;
                    hv.cur_sample  = l_yn1;
                }
            }
        } else {
            // Allow double-buffered AXSetVoiceEndAddr updates without resetting decoder state
            hv.last_guest_end_addr = end_addr;
        }

        ++out_active_count;

        // Read AXPBVE (currentVolume @ +412) and AXPBMIX (vL @ +330, vR @ +334)
        const uint16_t ve_vol = mem.read_u16(vp + 412u);
        uint16_t mix_vl = mem.read_u16(vp + 330u);
        uint16_t mix_vr = mem.read_u16(vp + 334u);
        if (mix_vl == 0u && mix_vr == 0u) {
            mix_vl = 0x8000u;
            mix_vr = 0x8000u;
        }
        const float env_f  = std::min(1.0f, static_cast<float>(ve_vol ? ve_vol : 0x8000u) / 32768.0f);
        const float gain_l = env_f * (static_cast<float>(mix_vl) / 32768.0f);
        const float gain_r = env_f * (static_cast<float>(mix_vr) / 32768.0f);

        uint32_t src_step_fp = (static_cast<uint32_t>(mem.read_u16(vp + 478u)) << 16) | mem.read_u16(vp + 480u);
        if (src_step_fp < 0x00000400u || src_step_fp > 0x00080000u) {
            src_step_fp = 0x00010000u;
        }

        int16_t coefs[16]{};
        if (format == 0u) {
            for (int c = 0; c < 16; ++c) {
                coefs[c] = static_cast<int16_t>(mem.read_u16(vp + 438u + static_cast<uint32_t>(c) * 2u));
            }
        }

        auto step_adpcm_unit = [](uint32_t u) noexcept -> uint32_t {
            ++u;
            return ((u & 0xFu) == 0u) ? (u + 2u) : u;
        };
        auto wrap_to_loop = [&](uint32_t frac) {
            const uint32_t lu = (format == 0u) ? align_adpcm_unit(loop_addr) : loop_addr;
            hv.cur_addr_fp = (static_cast<uint64_t>(lu) << 16) | frac;
            if (format == 0u) {
                const uint16_t l_pred = mem.read_u16(vp + 492u);
                const int16_t  l_yn1  = static_cast<int16_t>(mem.read_u16(vp + 494u));
                const int16_t  l_yn2  = static_cast<int16_t>(mem.read_u16(vp + 496u));
                if (l_pred != 0u || l_yn1 != 0 || l_yn2 != 0) {
                    hv.pred_scale = static_cast<uint8_t>(l_pred & 0xFFu);
                    hv.hist1      = l_yn1;
                    hv.hist2      = l_yn2;
                }
                hv.decoded_valid = false;
            }
        };
        auto decode_adpcm_unit = [&](uint32_t u) {
            if ((u & 0xFu) == 2u || !hv.decoded_valid) {
                const uint32_t hdr_byte_addr = (u & ~0xFu) >> 1;
                if (hdr_byte_addr < aram_bytes) {
                    hv.pred_scale = aram_[hdr_byte_addr];
                }
            }
            const uint32_t cur_byte_addr = u >> 1;
            int16_t sample = hv.cur_sample;
            if (cur_byte_addr < aram_bytes) {
                const uint8_t  hdr   = hv.pred_scale;
                const uint32_t pred  = (hdr >> 4) & 0x7u;
                const uint32_t scale = 1u << (hdr & 0xFu);
                const uint8_t  b     = aram_[cur_byte_addr];
                int32_t nib = (u & 1u) ? (b & 0x0Fu) : ((b >> 4) & 0x0Fu);
                if (nib >= 8) nib -= 16;
                const int32_t raw = (nib * static_cast<int32_t>(scale) * 2048)
                                  + static_cast<int32_t>(coefs[pred * 2u]) * hv.hist1
                                  + static_cast<int32_t>(coefs[pred * 2u + 1u]) * hv.hist2
                                  + 1024;
                sample = clamp_s16(raw >> 11);
                hv.hist2 = hv.hist1;
                hv.hist1 = sample;
            }
            hv.prev_sample       = hv.cur_sample;
            hv.cur_sample        = sample;
            hv.last_decoded_unit = u;
            hv.decoded_valid     = true;
        };

        for (size_t s = 0; s < num_samples; ++s) {
            uint32_t unit = static_cast<uint32_t>(hv.cur_addr_fp >> 16);
            const uint32_t frac = static_cast<uint32_t>(hv.cur_addr_fp & 0xFFFFu);
            if (format == 0u && (unit & 0xFu) < 2u) {
                unit = align_adpcm_unit(unit);
                hv.cur_addr_fp = (static_cast<uint64_t>(unit) << 16) | frac;
            }

            bool just_looped = false;
            if (unit >= end_addr) {
                if (loop_flag && loop_addr < end_addr) {
                    unit = (format == 0u) ? align_adpcm_unit(loop_addr) : loop_addr;
                    hv.cur_addr_fp = (static_cast<uint64_t>(unit) << 16) | frac;
                    just_looped = true;
                } else {
                    hv.finished = true;
                    hv.active   = false;
                    break;
                }
            }

            int16_t pcm_sample = 0;
            if (format == 0u) {
                if (just_looped) {
                    const uint16_t l_pred = mem.read_u16(vp + 492u);
                    const int16_t  l_yn1  = static_cast<int16_t>(mem.read_u16(vp + 494u));
                    const int16_t  l_yn2  = static_cast<int16_t>(mem.read_u16(vp + 496u));
                    if (l_pred != 0u || l_yn1 != 0 || l_yn2 != 0) {
                        hv.pred_scale = static_cast<uint8_t>(l_pred & 0xFFu);
                        hv.hist1      = l_yn1;
                        hv.hist2      = l_yn2;
                    }
                    decode_adpcm_unit(unit);
                } else if (!hv.decoded_valid) {
                    decode_adpcm_unit(unit);
                } else if (unit != hv.last_decoded_unit) {
                    uint32_t u = hv.last_decoded_unit;
                    if (unit > u && (unit - u) <= 64u) {
                        while (u < unit) {
                            u = step_adpcm_unit(u);
                            if (u >= end_addr) break;
                            decode_adpcm_unit(u);
                        }
                    } else {
                        hv.decoded_valid = false;
                        decode_adpcm_unit(unit);
                    }
                }

                if (frac == 0u) {
                    pcm_sample = hv.prev_sample;
                } else {
                    const int32_t p = hv.prev_sample;
                    const int32_t c = hv.cur_sample;
                    pcm_sample = static_cast<int16_t>(p + (((c - p) * static_cast<int32_t>(frac)) >> 16));
                }

                const uint64_t next_fp  = hv.cur_addr_fp + src_step_fp;
                const uint32_t adv_int  = static_cast<uint32_t>(next_fp >> 16) - unit;
                uint32_t       next_unit = unit;
                for (uint32_t k = 0; k < adv_int; ++k) {
                    next_unit = step_adpcm_unit(next_unit);
                }
                hv.cur_addr_fp = (static_cast<uint64_t>(next_unit) << 16) | (next_fp & 0xFFFFu);
            } else if (format == 10u) {
                // Big-endian PCM16 (addresses are ARAM 16-bit word offsets)
                auto read_pcm16 = [&](uint32_t u) -> int16_t {
                    const uint32_t byte_off = u << 1;
                    if (byte_off + 1u < aram_bytes) {
                        return static_cast<int16_t>((static_cast<uint16_t>(aram_[byte_off]) << 8) | aram_[byte_off + 1u]);
                    }
                    return 0;
                };
                const int16_t s0 = read_pcm16(unit);
                if (frac == 0u) {
                    pcm_sample = s0;
                } else {
                    const uint32_t next_u = (unit + 1u < end_addr) ? (unit + 1u) : ((loop_flag && loop_addr < end_addr) ? loop_addr : unit);
                    const int32_t s1 = read_pcm16(next_u);
                    pcm_sample = static_cast<int16_t>(s0 + (((s1 - s0) * static_cast<int32_t>(frac)) >> 16));
                }
                hv.cur_addr_fp += src_step_fp;
            } else if (format == 25u) {
                // Signed PCM8 (addresses are ARAM byte offsets)
                auto read_pcm8 = [&](uint32_t u) -> int16_t {
                    return (u < aram_bytes) ? static_cast<int16_t>(static_cast<int8_t>(aram_[u]) << 8) : 0;
                };
                const int16_t s0 = read_pcm8(unit);
                if (frac == 0u) {
                    pcm_sample = s0;
                } else {
                    const uint32_t next_u = (unit + 1u < end_addr) ? (unit + 1u) : ((loop_flag && loop_addr < end_addr) ? loop_addr : unit);
                    const int32_t s1 = read_pcm8(next_u);
                    pcm_sample = static_cast<int16_t>(s0 + (((s1 - s0) * static_cast<int32_t>(frac)) >> 16));
                }
                hv.cur_addr_fp += src_step_fp;
            } else {
                hv.cur_addr_fp += src_step_fp;
            }

            accum_lr[s * 2u + 0u] += static_cast<int32_t>(static_cast<float>(pcm_sample) * gain_l);
            accum_lr[s * 2u + 1u] += static_cast<int32_t>(static_cast<float>(pcm_sample) * gain_r);

            // Wrap looping voices (or finish one-shots) the instant the cursor reaches end_addr so the cursor
            // written back to guest (__AXVPB +434/+436) is never >= end_addr.
            if (static_cast<uint32_t>(hv.cur_addr_fp >> 16) >= end_addr) {
                if (can_loop) {
                    wrap_to_loop(static_cast<uint32_t>(hv.cur_addr_fp & 0xFFFFu));
                } else {
                    hv.finished = true;
                    hv.active   = false;
                    break;
                }
            }
        }
    }
}

void AudioAXInterface::mix_ai_dma_locked(
    const Memory& mem,
    std::vector<int32_t>& accum_lr,
    size_t num_samples) {
    if (!dma_enabled_ || ai_dma_len_ < 4u || !is_valid_ram_vaddr(ai_dma_addr_)) {
        return;
    }
    const uint32_t buf_bytes = ai_dma_len_ & ~3u;
    if (buf_bytes == 0u) {
        return;
    }
    // Check if the DMA buffer contains actual audio data (e.g. from THP movie player or game PCM writer)
    bool has_nonzero = false;
    const uint32_t probe_bytes = std::min<uint32_t>(buf_bytes, 64u);
    for (uint32_t p = 0; p < probe_bytes; p += 4u) {
        if (mem.read_u32(ai_dma_addr_ + p) != 0u) {
            has_nonzero = true;
            break;
        }
    }
    for (size_t s = 0; s < num_samples; ++s) {
        const uint32_t addr = ai_dma_addr_ + (ai_dma_read_off_ % buf_bytes);
        if (has_nonzero) {
            const int16_t l = static_cast<int16_t>(mem.read_u16(addr));
            const int16_t r = static_cast<int16_t>(mem.read_u16(addr + 2u));
            accum_lr[s * 2u + 0u] += l;
            accum_lr[s * 2u + 1u] += r;
        }
        ai_dma_read_off_ += 4u;
    }
}

std::vector<int16_t> AudioAXInterface::mix_stereo_frame(const Memory& mem, size_t num_samples) {
    std::vector<int16_t> out(num_samples * 2u, 0);
    if (num_samples == 0u) {
        return out;
    }

    size_t active_voices = 0;
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::vector<int32_t> accum_lr(num_samples * 2u, 0);
        mix_voices_locked(mem, accum_lr, num_samples, active_voices);
        mix_ai_dma_locked(mem, accum_lr, num_samples);
        last_active_voices_ = active_voices;

        const float master = cfg_.audio_muted ? 0.0f : std::clamp(cfg_.audio_volume, 0.0f, 1.0f);
        for (size_t i = 0; i < out.size(); ++i) {
            const int32_t scaled = static_cast<int32_t>(static_cast<float>(accum_lr[i]) * master);
            out[i] = clamp_s16(scaled);
        }

        total_mixed_frames_ += num_samples;
        submit_xaudio2_pcm(out.data(), num_samples);
    }
    return out;
}

void AudioAXInterface::invoke_ppc_callback(uint32_t cb_vaddr, PPCContext& ctx, Memory& mem) {
    static thread_local int tl_callback_depth = 0;
    if (!is_valid_code_vaddr(cb_vaddr) || tl_callback_depth >= 8) {
        return;
    }
    ++tl_callback_depth;
    const bool prev_in_callback = in_callback_;
    in_callback_ = true;

    const uint32_t saved_r0   = ctx.r[0];
    uint32_t       saved_vol[10]{};
    for (int i = 0; i < 10; ++i) {
        saved_vol[i] = ctx.r[3 + i];
    }
    const uint32_t saved_lr   = ctx.lr;
    const uint32_t saved_ctr  = ctx.ctr;
    const uint32_t saved_xer  = ctx.xer;
    const uint32_t saved_cr   = ctx.pack_cr();

    ctx.lr = 0u;
    ctx.call_indirect(cb_vaddr, mem);

    ctx.r[0] = saved_r0;
    for (int i = 0; i < 10; ++i) {
        ctx.r[3 + i] = saved_vol[i];
    }
    ctx.lr   = saved_lr;
    ctx.ctr  = saved_ctr;
    ctx.xer  = saved_xer;
    ctx.unpack_cr(0xFFu, saved_cr);
    in_callback_ = prev_in_callback;
    --tl_callback_depth;
}

void AudioAXInterface::step_audio_frame(PPCContext& ctx, Memory& mem, size_t num_samples) {
    uint32_t cb_to_call  = 0;
    uint32_t ax_ticks    = 0;
    uint32_t dma_cb      = 0;

    {
        std::lock_guard<std::mutex> lock(mtx_);
        // Pull callback pointers if recompiled code wrote them directly to SDA1 globals
        const uint32_t mem_ax_cb = mem.read_u32(kSymAXUserFrameCb);
        if (is_valid_code_vaddr(mem_ax_cb)) {
            ax_user_callback_ = mem_ax_cb;
        }
        const uint32_t mem_aid_cb = mem.read_u32(kSymAIDCallback);
        if (is_valid_code_vaddr(mem_aid_cb)) {
            ai_dma_callback_ = mem_aid_cb;
        }

        if (ax_initialized_ && is_valid_code_vaddr(ax_user_callback_)) {
            cb_to_call = ax_user_callback_;
            ax_sample_accum_ += static_cast<uint32_t>(num_samples);
            ax_ticks = ax_sample_accum_ / 160u;
            ax_sample_accum_ %= 160u;
        }

        if (dma_enabled_ && is_valid_code_vaddr(ai_dma_callback_)) {
            const bool is_ax_internal = (ai_dma_callback_ >= kAXOutCodeStart && ai_dma_callback_ < kAXOutCodeEnd);
            if (!is_ax_internal && ai_dma_len_ >= 4u && ai_dma_read_off_ >= ai_dma_len_) {
                ai_dma_read_off_ %= ai_dma_len_;
                dma_cb = ai_dma_callback_;
            }
        }
    }

    // Authentic AX cadence: every 5ms DSP subframe (160 samples @ 32kHz) the guest AX callback (Snd_main) runs, the
    // HLE DVD / ARQ completion callbacks it queued are delivered, and the voice cursors advance by exactly one
    // subframe before the next tick. Running all ticks back-to-back with frozen cursors / undelivered DVD+ARAM
    // completions starves Capcom's SND_STR ring-buffer refill (dvd_read_req_cnt >= 6 -> BGM stream error -> silence).
    std::vector<int16_t> pcm_out;
    pcm_out.reserve(num_samples * 2u);
    size_t remaining = num_samples;

    auto mix_chunk_and_sync = [&](size_t n) {
        if (n == 0u) {
            return;
        }
        std::lock_guard<std::mutex> lock(mtx_);
        std::vector<int32_t> accum_lr(n * 2u, 0);
        size_t active_voices = 0;
        mix_voices_locked(mem, accum_lr, n, active_voices);
        mix_ai_dma_locked(mem, accum_lr, n);
        last_active_voices_ = active_voices;
        const float master = cfg_.audio_muted ? 0.0f : std::clamp(cfg_.audio_volume, 0.0f, 1.0f);
        for (size_t i = 0; i < accum_lr.size(); ++i) {
            pcm_out.push_back(clamp_s16(static_cast<int32_t>(static_cast<float>(accum_lr[i]) * master)));
        }
        total_mixed_frames_ += n;

        // Push updated host cursor state / voice-end status back to guest __AXVPB RAM so Snd detects finished
        // SFX/streams and the SND_STR ring-buffer play cursor.
        for (uint32_t v = 0; v < kMaxVoices; ++v) {
            const uint32_t vp = kAxVpbBase + v * kAxVpbStride;
            HostVoiceState& hv = host_voices_[v];
            if (hv.finished && mem.read_u16(vp + 326u) == 1u) {
                mem.write_u16(vp + 326u, 0u);
            } else if (hv.active) {
                const uint32_t cur = static_cast<uint32_t>(hv.cur_addr_fp >> 16);
                hv.last_guest_cur_addr = cur;
                mem.write_u16(vp + 434u, static_cast<uint16_t>((cur >> 16) & 0xFFFFu));
                mem.write_u16(vp + 436u, static_cast<uint16_t>(cur & 0xFFFFu));
                mem.write_u16(vp + 472u, static_cast<uint16_t>(hv.pred_scale));
                mem.write_u16(vp + 474u, static_cast<uint16_t>(hv.hist1));
                mem.write_u16(vp + 476u, static_cast<uint16_t>(hv.hist2));
            }
        }
    };

    for (uint32_t t = 0; t < ax_ticks; ++t) {
        const uint32_t next_frame = (mem.read_u32(kSymAXOutFrame) + 1u) & 1u;
        mem.write_u32(kSymAXOutFrame, next_frame);
        mem.write_u32(kSymAXOutDspReady, 1u);
        mem.write_u32(kSymAXDSPDoneFlag, 1u);
        ++ax_callback_invocations_;
        invoke_ppc_callback(cb_to_call, ctx, mem);
        // Deliver DVDReadAsyncPrio / ARQPostRequest completions (cb_dvd_read_end / cb_aram_dma_end) queued by Snd_str
        // inside this subframe so the next tick sees dvd_busy / aram_busy cleared (flush drains chained callbacks).
        flush_pending_hle_callbacks(ctx, mem);

        const size_t n = std::min<size_t>(160u, remaining);
        mix_chunk_and_sync(n);
        remaining -= n;
    }

    if (dma_cb != 0u) {
        invoke_ppc_callback(dma_cb, ctx, mem);
    }

    mix_chunk_and_sync(remaining);

    if (!pcm_out.empty()) {
        std::lock_guard<std::mutex> lock(mtx_);
        submit_xaudio2_pcm(pcm_out.data(), pcm_out.size() / 2u);
    }
}

void AudioAXInterface::aram_dma_transfer(
    uint32_t type,
    uint32_t mmem_addr,
    uint32_t aram_addr,
    uint32_t length,
    Memory& mem) {
    if (length == 0u || !is_valid_ram_vaddr(mmem_addr)) {
        return;
    }
    std::lock_guard<std::mutex> lock(mtx_);
    if (aram_addr >= Memory::kAramBase && aram_addr < Memory::kAramBase + Memory::kAramSize) {
        aram_addr -= Memory::kAramBase;
    }
    if (aram_addr >= aram_.size()) {
        return;
    }
    const uint32_t max_len = std::min<uint32_t>(length, static_cast<uint32_t>(aram_.size()) - aram_addr);
    if (type == 0u) {
        // ARAM_DIR_MRAM_TO_ARAM
        for (uint32_t i = 0; i < max_len; ++i) {
            aram_[aram_addr + i] = mem.read_u8(mmem_addr + i);
        }
    } else {
        // ARAM_DIR_ARAM_TO_MRAM
        for (uint32_t i = 0; i < max_len; ++i) {
            mem.write_u8(mmem_addr + i, aram_[aram_addr + i]);
        }
    }
}

uint32_t AudioAXInterface::aram_alloc(uint32_t size) {
    std::lock_guard<std::mutex> lock(mtx_);
    const uint32_t aligned = (size + 31u) & ~31u;
    if (ar_stack_ptr_ + aligned > kAramSizeBytes) {
        return 0u;
    }
    const uint32_t addr = ar_stack_ptr_;
    ar_alloc_stack_.push_back(aligned);
    ar_stack_ptr_ += aligned;
    return addr;
}

void AudioAXInterface::aram_free(uint32_t* out_size) {
    std::lock_guard<std::mutex> lock(mtx_);
    uint32_t freed = 0u;
    if (!ar_alloc_stack_.empty()) {
        freed = ar_alloc_stack_.back();
        ar_alloc_stack_.pop_back();
        ar_stack_ptr_ = (ar_stack_ptr_ >= freed) ? (ar_stack_ptr_ - freed) : 0x00004000u;
    }
    if (out_size) {
        *out_size = freed;
    }
}

size_t AudioAXInterface::active_voice_count() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return last_active_voices_;
}

bool AudioAXInterface::dispatch_audio_call(uint32_t vaddr, PPCContext& ctx, Memory& mem) {
    switch (vaddr) {
        // ---- Dolphin Audio Interface (AI) ----
        case 0x80111860u: { // AIInit(u8* stack)
            std::lock_guard<std::mutex> lock(mtx_);
            ai_initialized_ = true;
            mem.write_u32(kSymAIInitFlag, 1u);
            return true;
        }
        case 0x801119CCu: { // AIReset()
            std::lock_guard<std::mutex> lock(mtx_);
            dma_enabled_        = false;
            ai_dma_callback_    = 0;
            ai_stream_callback_ = 0;
            mem.write_u32(kSymAIInitFlag, 0u);
            mem.write_u32(kSymAIDCallback, 0u);
            mem.write_u32(kSymAISCallback, 0u);
            mem.write_u32(kSymAIDActive, 0u);
            return true;
        }
        case 0x80111328u: { // AIDCallback AIRegisterDMACallback(AIDCallback cb)
            std::lock_guard<std::mutex> lock(mtx_);
            const uint32_t prev = ai_dma_callback_;
            ai_dma_callback_ = ctx.r[3];
            mem.write_u32(kSymAIDCallback, ai_dma_callback_);
            ctx.r[3] = prev;
            return true;
        }
        case 0x8011136Cu: { // AIInitDMA(u32 start_addr, u32 length)
            std::lock_guard<std::mutex> lock(mtx_);
            ai_dma_addr_     = ctx.r[3];
            ai_dma_len_      = ctx.r[4];
            ai_dma_read_off_ = 0;
            return true;
        }
        case 0x801113F4u: { // BOOL AIGetDMAEnableFlag()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = dma_enabled_ ? 1u : 0u;
            return true;
        }
        case 0x80111404u: { // AIStartDMA()
            std::lock_guard<std::mutex> lock(mtx_);
            dma_enabled_ = true;
            mem.write_u32(kSymAIDActive, 1u);
            return true;
        }
        case 0x8011141Cu: { // AIStopDMA()
            std::lock_guard<std::mutex> lock(mtx_);
            dma_enabled_ = false;
            mem.write_u32(kSymAIDActive, 0u);
            return true;
        }
        case 0x80111434u: { // u32 AIGetDMABytesLeft()
            std::lock_guard<std::mutex> lock(mtx_);
            if (!dma_enabled_ || ai_dma_len_ == 0u) {
                ctx.r[3] = 0u;
            } else {
                const uint32_t rem = (ai_dma_read_off_ < ai_dma_len_) ? (ai_dma_len_ - ai_dma_read_off_) : 0u;
                ctx.r[3] = rem;
            }
            return true;
        }
        case 0x80111444u: { // u32 AIGetDMAStartAddr()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = ai_dma_addr_;
            return true;
        }
        case 0x80111460u: { // u32 AIGetDMALength()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = ai_dma_len_;
            return true;
        }
        case 0x80111470u: { // BOOL AICheckInit()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = ai_initialized_ ? 1u : 0u;
            return true;
        }
        case 0x80111478u: { // AISCallback AIRegisterStreamCallback(AISCallback cb)
            std::lock_guard<std::mutex> lock(mtx_);
            const uint32_t prev = ai_stream_callback_;
            ai_stream_callback_ = ctx.r[3];
            mem.write_u32(kSymAISCallback, ai_stream_callback_);
            ctx.r[3] = prev;
            return true;
        }
        case 0x80111500u: { // AISetStreamPlayState(u32 state)
            std::lock_guard<std::mutex> lock(mtx_);
            stream_play_state_ = ctx.r[3];
            return true;
        }
        case 0x801115D8u: { // u32 AIGetStreamPlayState()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = stream_play_state_;
            return true;
        }
        case 0x801115E8u: { // AISetDSPSampleRate(u32 rate)
            std::lock_guard<std::mutex> lock(mtx_);
            dsp_sample_rate_ = (ctx.r[3] == 1u) ? 48000u : 32000u;
            return true;
        }
        case 0x801116C8u: { // u32 AIGetDSPSampleRate()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = (dsp_sample_rate_ == 48000u) ? 1u : 0u;
            return true;
        }
        case 0x801116DCu: { // AISetStreamSampleRate(u32 rate)
            std::lock_guard<std::mutex> lock(mtx_);
            stream_sample_rate_ = (ctx.r[3] == 1u) ? 48000u : 32000u;
            return true;
        }
        case 0x801117F8u: { // u32 AIGetStreamSampleRate()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = (stream_sample_rate_ == 48000u) ? 1u : 0u;
            return true;
        }
        case 0x80111808u: { // AISetStreamVolLeft(u8 vol)
            std::lock_guard<std::mutex> lock(mtx_);
            stream_vol_left_ = ctx.r[3] & 0xFFu;
            return true;
        }
        case 0x80111824u: { // u8 AIGetStreamVolLeft()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = stream_vol_left_;
            return true;
        }
        case 0x80111834u: { // AISetStreamVolRight(u8 vol)
            std::lock_guard<std::mutex> lock(mtx_);
            stream_vol_right_ = ctx.r[3] & 0xFFu;
            return true;
        }
        case 0x80111850u: { // u8 AIGetStreamVolRight()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = stream_vol_right_;
            return true;
        }

        // ---- Dolphin ARAM (AR / ARQ) ----
        case 0x80111D44u: { // ARCallback ARRegisterDMACallback(ARCallback cb)
            std::lock_guard<std::mutex> lock(mtx_);
            const uint32_t prev = ar_callback_;
            ar_callback_ = ctx.r[3];
            mem.write_u32(kSymARCallback, ar_callback_);
            ctx.r[3] = prev;
            return true;
        }
        case 0x80111D88u: { // u32 ARGetDMAStatus()
            ctx.r[3] = 0u; // DMA idle / completed immediately
            return true;
        }
        case 0x80111DC4u: { // ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length)
            aram_dma_transfer(ctx.r[3], ctx.r[4], ctx.r[5], ctx.r[6], mem);
            uint32_t cb = 0;
            {
                std::lock_guard<std::mutex> lock(mtx_);
                cb = ar_callback_;
            }
            if (is_valid_code_vaddr(cb)) {
                invoke_ppc_callback(cb, ctx, mem);
            }
            return true;
        }
        case 0x80111EB4u: { // u32 ARAlloc(u32 length)
            const uint32_t addr = aram_alloc(ctx.r[3]);
            mem.write_u32(kSymARStackPointer, ar_stack_ptr_);
            ctx.r[3] = addr;
            return true;
        }
        case 0x80111F1Cu: { // u32 ARFree(u32* length)
            uint32_t freed = 0;
            aram_free(&freed);
            if (is_valid_ram_vaddr(ctx.r[3])) {
                mem.write_u32(ctx.r[3], freed);
            }
            mem.write_u32(kSymARStackPointer, ar_stack_ptr_);
            ctx.r[3] = ar_stack_ptr_;
            return true;
        }
        case 0x80111F90u: { // BOOL ARCheckInit()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = ar_initialized_ ? 1u : 0u;
            return true;
        }
        case 0x80111F98u: { // u32 ARInit(u32* stack_index_addr, u32 num_entries)
            std::lock_guard<std::mutex> lock(mtx_);
            ar_initialized_ = true;
            ar_stack_ptr_   = 0x00004000u;
            ar_alloc_stack_.clear();
            mem.write_u32(kSymARInitFlag, 1u);
            mem.write_u32(kSymARSize, kAramSizeBytes);
            mem.write_u32(kSymARStackPointer, ar_stack_ptr_);
            ctx.r[3] = ar_stack_ptr_;
            return true;
        }
        case 0x8011205Cu: { // ARReset()
            std::lock_guard<std::mutex> lock(mtx_);
            ar_initialized_ = false;
            mem.write_u32(kSymARInitFlag, 0u);
            return true;
        }
        case 0x8011206Cu: { // u32 ARGetBaseAddress()
            ctx.r[3] = 0x00004000u;
            return true;
        }
        case 0x80112074u: // ARGetSize()
        case 0x8011207Cu: { // ARGetInternalSize()
            ctx.r[3] = kAramSizeBytes;
            return true;
        }
        case 0x80113EF4u: { // ARQInit()
            mem.write_u32(kSymARQInitFlag, 1u);
            return true;
        }
        case 0x80113F64u: { // ARQReset()
            mem.write_u32(kSymARQInitFlag, 0u);
            return true;
        }
        case 0x80113F70u: {
            // ARQPostRequest(ARQRequest* req, u32 owner, u32 type, u32 prio, u32 source, u32 dest, u32 length, ARQCallback cb)
            const uint32_t req_va = ctx.r[3];
            const uint32_t type   = ctx.r[5];
            const uint32_t src    = ctx.r[7];
            const uint32_t dst    = ctx.r[8];
            const uint32_t len    = ctx.r[9];
            const uint32_t cb     = ctx.r[10];
            if (is_valid_ram_vaddr(req_va)) {
                mem.write_u32(req_va + 0u, 0u);
                mem.write_u32(req_va + 4u, ctx.r[4]); // owner
                mem.write_u32(req_va + 8u, type);
                mem.write_u32(req_va + 12u, ctx.r[6]); // priority
                mem.write_u32(req_va + 16u, src);
                mem.write_u32(req_va + 20u, dst);
                mem.write_u32(req_va + 24u, len);
                mem.write_u32(req_va + 28u, cb);
            }
            if (type == 0u) {
                aram_dma_transfer(0u, src, dst, len, mem);
            } else {
                aram_dma_transfer(1u, dst, src, len, mem);
            }
            if (is_valid_code_vaddr(cb)) {
                // AramDmaTrans (0x8007C0FC) & zero_buff_clear (0x8013BDE4) busy-wait inline without HLE polls;
                // trans2aram (0x8007AEE8) & snd_str1 (0x8013AF30) set their pending bit after ARQPostRequest returns.
                if (cb == 0x8007C0FCu || cb == 0x8013BDE4u) {
                    const uint32_t saved_r3 = ctx.r[3];
                    ctx.r[3] = req_va;
                    invoke_ppc_callback(cb, ctx, mem);
                    ctx.r[3] = saved_r3;
                } else {
                    enqueue_pending_hle_callback(cb, req_va, 0u, 0u);
                }
            }
            return true;
        }
        case 0x801142DCu: { // ARQSetChunkSize(u32 size)
            std::lock_guard<std::mutex> lock(mtx_);
            arq_chunk_size_ = ctx.r[3];
            return true;
        }
        case 0x801142FCu: { // u32 ARQGetChunkSize()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = arq_chunk_size_;
            return true;
        }

        // ---- Dolphin DSP mailbox / task layer (exact entry points) ----
        case 0x80160038u: { // u32 DSPCheckMailToDSP()
            ctx.r[3] = 0u; // Always ready to accept mail
            return true;
        }
        case 0x80160048u: { // u32 DSPCheckMailFromDSP()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = dsp_mail_pending_ ? 1u : 0u;
            return true;
        }
        case 0x80160058u: { // u32 DSPReadCPUToDSPMbox()
            ctx.r[3] = 0u;
            return true;
        }
        case 0x8016006Cu: { // u32 DSPReadMailFromDSP()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = dsp_mail_pending_ ? dsp_mail_value_ : 0u;
            dsp_mail_pending_ = 0u;
            return true;
        }
        case 0x80160084u: { // DSPSendMailToDSP(u32 mail)
            std::lock_guard<std::mutex> lock(mtx_);
            dsp_mail_pending_ = 1u;
            dsp_mail_value_   = (ctx.r[3] == 0xBABE0180u) ? 0xDCD10002u : 0xDCD10000u;
            return true;
        }
        case 0x80160098u: { // DSPAssertInt()
            return true;
        }
        case 0x801600D8u: { // DSPInit()
            std::lock_guard<std::mutex> lock(mtx_);
            dsp_initialized_  = true;
            dsp_mail_pending_ = 1u;
            dsp_mail_value_   = 0xDCD10000u;
            mem.write_u32(kSymDSPInitFlag, 1u);
            return true;
        }
        case 0x8016019Cu: { // BOOL DSPCheckInit()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = dsp_initialized_ ? 1u : 0u;
            return true;
        }
        case 0x801601A4u: // DSPReset()
        case 0x801601ECu: // DSPHalt()
        case 0x8016022Cu: { // DSPUnhalt()
            return true;
        }
        case 0x80160268u: { // u32 DSPGetDMAStatus()
            ctx.r[3] = 0u;
            return true;
        }
        case 0x80160278u: { // DSPTaskInfo* DSPAddTask(DSPTaskInfo* task)
            const uint32_t task_va = ctx.r[3];
            if (is_valid_ram_vaddr(task_va)) {
                mem.write_u32(task_va + 0u, 3u); // state = DSP_TASK_STATE_DONE
                const uint32_t done_cb = mem.read_u32(task_va + 20u);
                if (is_valid_code_vaddr(done_cb)) {
                    invoke_ppc_callback(done_cb, ctx, mem);
                }
            }
            ctx.r[3] = task_va;
            return true;
        }
        case 0x801602E8u: // DSPCancelTask(DSPTaskInfo* task)
        case 0x80160328u: { // DSPTaskInfo* DSPAssertTask(DSPTaskInfo* task)
            return true;
        }

        // ---- Dolphin AX Core Lifecycle (let AXAlloc / AXVPB / AXSetVoice* execute recompiled code on real guest __AXVPB RAM!) ----
        case 0x80151260u: { // AXInit()
            // Save caller volatile PPC registers / LR while initializing guest AX RAM tables
            const uint32_t saved_r0  = ctx.r[0];
            uint32_t       saved_vol[10]{};
            for (int i = 0; i < 10; ++i) saved_vol[i] = ctx.r[3 + i];
            const uint32_t saved_lr  = ctx.lr;
            const uint32_t saved_ctr = ctx.ctr;
            const uint32_t saved_xer = ctx.xer;
            const uint32_t saved_cr  = ctx.pack_cr();

            ctx.call_indirect(kFnAXAllocInit, mem);
            ctx.call_indirect(kFnAXVPBInit, mem);
            ctx.call_indirect(kFnAXSPBInit, mem);
            ctx.call_indirect(kFnAXAuxInit, mem);
            ctx.call_indirect(kFnAXClInit, mem);

            ctx.r[0] = saved_r0;
            for (int i = 0; i < 10; ++i) ctx.r[3 + i] = saved_vol[i];
            ctx.lr  = saved_lr;
            ctx.ctr = saved_ctr;
            ctx.xer = saved_xer;
            ctx.unpack_cr(0xFFu, saved_cr);

            std::lock_guard<std::mutex> lock(mtx_);
            ax_initialized_ = true;
            mem.write_u32(kSymAXDSPInitFlag, 1u);
            mem.write_u32(kSymAXDSPDoneFlag, 1u);
            mem.write_u32(kSymAXOutDspReady, 1u);
            mem.write_u32(kSymAXOutFrame, 0u);
            mem.write_u32(kSymDSPInitFlag, 1u);
            mem.write_u32(kSymAIInitFlag, 1u);
            return true;
        }
        case 0x8015129Cu: { // AXQuit()
            std::lock_guard<std::mutex> lock(mtx_);
            ax_initialized_   = false;
            ax_user_callback_ = 0;
            mem.write_u32(kSymAXUserFrameCb, 0u);
            mem.write_u32(kSymAXDSPInitFlag, 0u);
            mem.write_u32(kSymAXOutDspReady, 0u);
            return true;
        }
        case 0x80152E48u: { // AXOutCallback AXRegisterCallback(AXOutCallback cb)
            std::lock_guard<std::mutex> lock(mtx_);
            const uint32_t prev = mem.read_u32(kSymAXUserFrameCb);
            ax_user_callback_ = ctx.r[3];
            mem.write_u32(kSymAXUserFrameCb, ax_user_callback_);
            ctx.r[3] = prev;
            return true;
        }
        case 0x80151FECu: { // AXRegisterAuxACallback(AXAuxCallback cb, void* context)
            std::lock_guard<std::mutex> lock(mtx_);
            ax_aux_a_callback_ = ctx.r[3];
            return false; // Let guest struct write also proceed cleanly
        }
        case 0x80151FF8u: { // AXRegisterAuxBCallback(AXAuxCallback cb, void* context)
            std::lock_guard<std::mutex> lock(mtx_);
            ax_aux_b_callback_ = ctx.r[3];
            return false;
        }
        case 0x80152738u: { // AXSetMode(u32 mode)
            std::lock_guard<std::mutex> lock(mtx_);
            ax_mode_ = ctx.r[3];
            mem.write_u32(kSymAXClMode, ax_mode_);
            return true;
        }
        case 0x8015274Cu: { // u32 AXGetMode()
            std::lock_guard<std::mutex> lock(mtx_);
            ctx.r[3] = mem.read_u32(kSymAXClMode);
            return true;
        }
        case 0x8015275Cu: { // __AXOutNewFrame(u32 lessDspCycles)
            uint32_t cb = 0;
            {
                std::lock_guard<std::mutex> lock(mtx_);
                cb = mem.read_u32(kSymAXUserFrameCb);
                if (!cb) cb = ax_user_callback_;
            }
            invoke_ppc_callback(kFnAXSyncPBs, ctx, mem);
            if (is_valid_code_vaddr(cb)) {
                invoke_ppc_callback(cb, ctx, mem);
            }
            const uint32_t next_frame = (mem.read_u32(kSymAXOutFrame) + 1u) & 1u;
            mem.write_u32(kSymAXOutFrame, next_frame);
            mem.write_u32(kSymAXOutDspReady, 1u);
            return true;
        }

        default:
            // All AXAlloc/AXAcquireVoice/AXFreeVoice/AXSetVoice* and Capcom Snd_* routines
            // run directly via recompiled C++ code against guest RAM & __AXVPB[64].
            return false;
    }
}

} // namespace pn03
