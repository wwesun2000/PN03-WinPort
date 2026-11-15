#include "pn03_runtime.hpp"
#include <algorithm>
#include <cctype>
#include <cstring>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace pn03 {

static const IsoStreamReader* g_active_iso_reader = nullptr;

void IsoStreamReader::set_active_instance(const IsoStreamReader* reader) {
    g_active_iso_reader = reader;
}

const IsoStreamReader* IsoStreamReader::active_instance() {
    return g_active_iso_reader;
}

IsoStreamReader::~IsoStreamReader() {
    if (g_active_iso_reader == this) {
        g_active_iso_reader = nullptr;
    }
}

static uint32_t read_be32(const uint8_t* p) {
    return (static_cast<uint32_t>(p[0]) << 24) |
           (static_cast<uint32_t>(p[1]) << 16) |
           (static_cast<uint32_t>(p[2]) << 8)  |
           static_cast<uint32_t>(p[3]);
}

std::string IsoStreamReader::normalize_gc_path(const std::string& p) {
    std::string out;
    out.reserve(p.size() + 2);
    for (char c : p) {
        if (c == '\\') c = '/';
        out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
    }
    if (out.empty() || out[0] != '/') {
        out.insert(out.begin(), '/');
    }
    return out;
}

bool IsoStreamReader::open(const std::string& iso_or_sys_path, std::string& err_msg) {
    is_open_ = false;
    files_.clear();
    path_index_.clear();

    bool ok = false;
    if (fs::is_directory(iso_or_sys_path)) {
        fs::path boot_p = fs::path(iso_or_sys_path) / "sys" / "boot.bin";
        fs::path fst_p  = fs::path(iso_or_sys_path) / "sys" / "fst.bin";
        if (!fs::exists(boot_p) || !fs::exists(fst_p)) {
            err_msg = "Directory does not contain sys/boot.bin and sys/fst.bin: " + iso_or_sys_path;
            return false;
        }
        std::ifstream bf(boot_p, std::ios::binary);
        std::vector<uint8_t> boot_bytes((std::istreambuf_iterator<char>(bf)), std::istreambuf_iterator<char>());
        std::ifstream ff(fst_p, std::ios::binary);
        std::vector<uint8_t> fst_bytes((std::istreambuf_iterator<char>(ff)), std::istreambuf_iterator<char>());
        is_extracted_dir_ = true;
        base_path_ = iso_or_sys_path;
        ok = parse_headers(boot_bytes, fst_bytes, err_msg);
    } else {
        std::ifstream iso(iso_or_sys_path, std::ios::binary);
        if (!iso.is_open()) {
            err_msg = "Failed to open ISO file: " + iso_or_sys_path;
            return false;
        }
        std::vector<uint8_t> boot_bytes(0x440, 0);
        iso.read(reinterpret_cast<char*>(boot_bytes.data()), static_cast<std::streamsize>(boot_bytes.size()));
        if (iso.gcount() < 0x440) {
            err_msg = "File is too small to be a valid GameCube ISO/GCM header.";
            return false;
        }
        uint32_t fst_off = read_be32(&boot_bytes[0x424]);
        uint32_t fst_sz  = read_be32(&boot_bytes[0x428]);
        if (fst_sz == 0 || fst_sz > 0x1000000u) {
            err_msg = "Invalid FST size in ISO header.";
            return false;
        }
        std::vector<uint8_t> fst_bytes(fst_sz, 0);
        iso.seekg(fst_off, std::ios::beg);
        iso.read(reinterpret_cast<char*>(fst_bytes.data()), static_cast<std::streamsize>(fst_sz));
        is_extracted_dir_ = false;
        base_path_ = iso_or_sys_path;
        ok = parse_headers(boot_bytes, fst_bytes, err_msg);
    }
    if (ok) {
        set_active_instance(this);
    }
    return ok;
}

bool IsoStreamReader::parse_headers(const std::vector<uint8_t>& boot_bin, const std::vector<uint8_t>& fst_bin, std::string& err_msg) {
    if (boot_bin.size() < 0x440) {
        err_msg = "boot.bin smaller than 0x440 bytes.";
        return false;
    }
    uint32_t magic = read_be32(&boot_bin[0x1C]);
    if (magic != 0xC2339F3Du) {
        err_msg = "Invalid GameCube disc magic word at 0x1C (expected 0xC2339F3D).";
        return false;
    }
    game_id_ = std::string(reinterpret_cast<const char*>(&boot_bin[0]), 6);
    game_title_ = reinterpret_cast<const char*>(&boot_bin[0x20]);
    dol_offset_ = read_be32(&boot_bin[0x420]);
    fst_offset_ = read_be32(&boot_bin[0x424]);
    fst_size_   = read_be32(&boot_bin[0x428]);

    if (fst_bin.size() < 12) {
        err_msg = "fst.bin too short.";
        return false;
    }
    uint32_t num_entries = read_be32(&fst_bin[8]);
    uint32_t str_table_off = num_entries * 12;
    if (str_table_off > fst_bin.size()) {
        err_msg = "Corrupted FST string table offset.";
        return false;
    }

    std::vector<std::pair<uint32_t, std::string>> dir_stack;
    dir_stack.emplace_back(num_entries, "");

    for (uint32_t idx = 1; idx < num_entries; ++idx) {
        while (!dir_stack.empty() && idx >= dir_stack.back().first) {
            dir_stack.pop_back();
        }
        const uint8_t* ent = &fst_bin[idx * 12];
        bool is_dir = (ent[0] != 0);
        uint32_t name_off = (static_cast<uint32_t>(ent[1]) << 16) |
                            (static_cast<uint32_t>(ent[2]) << 8)  |
                            static_cast<uint32_t>(ent[3]);
        uint32_t offset_or_parent = read_be32(&ent[4]);
        uint32_t size_or_next     = read_be32(&ent[8]);

        std::string name;
        for (size_t k = str_table_off + name_off; k < fst_bin.size(); ++k) {
            char c = static_cast<char>(fst_bin[k]);
            if (c == '\0') break;
            name.push_back(c);
        }
        std::string full_path = dir_stack.back().second + "/" + name;
        if (is_dir) {
            dir_stack.emplace_back(size_or_next, full_path);
        } else {
            IsoFileEntry fe;
            fe.path        = full_path;
            fe.disc_offset = offset_or_parent;
            fe.size_bytes  = size_or_next;
            fe.is_dir      = false;
            path_index_[normalize_gc_path(full_path)] = files_.size();
            files_.push_back(std::move(fe));
        }
    }

    is_open_ = true;
    return true;
}

const IsoFileEntry* IsoStreamReader::find_file(const std::string& virtual_path) const {
    auto it = path_index_.find(normalize_gc_path(virtual_path));
    if (it == path_index_.end()) return nullptr;
    return &files_[it->second];
}

int32_t IsoStreamReader::find_entrynum(const std::string& virtual_path) const {
    auto it = path_index_.find(normalize_gc_path(virtual_path));
    if (it == path_index_.end()) return -1;
    return static_cast<int32_t>(it->second);
}

const IsoFileEntry* IsoStreamReader::get_file_by_entrynum(int32_t entrynum) const {
    if (entrynum < 0 || static_cast<size_t>(entrynum) >= files_.size()) return nullptr;
    return &files_[static_cast<size_t>(entrynum)];
}

std::vector<uint8_t> IsoStreamReader::read_slice(uint32_t disc_offset, uint32_t length) const {
    if (!is_open_ || is_extracted_dir_) return {};
    std::ifstream iso(base_path_, std::ios::binary);
    if (!iso.is_open()) return {};
    std::vector<uint8_t> buf(length, 0);
    iso.seekg(disc_offset, std::ios::beg);
    iso.read(reinterpret_cast<char*>(buf.data()), static_cast<std::streamsize>(length));
    return buf;
}

std::vector<uint8_t> IsoStreamReader::read_file(const std::string& virtual_path) const {
    const IsoFileEntry* fe = find_file(virtual_path);
    if (fe && !is_extracted_dir_) {
        return read_slice(fe->disc_offset, fe->size_bytes);
    }
    if (is_extracted_dir_) {
        std::string rel = fe ? fe->path : virtual_path;
        if (!rel.empty() && rel[0] == '/') rel.erase(0, 1);
        fs::path local_p = fs::path(base_path_) / rel;
        if (!fs::exists(local_p)) {
            local_p = fs::path(base_path_) / "files" / rel;
        }
        if (fs::exists(local_p)) {
            std::ifstream in(local_p, std::ios::binary);
            return std::vector<uint8_t>((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        }
    }
    return {};
}

std::vector<uint8_t> IsoStreamReader::read_file_slice(int32_t entrynum, uint32_t offset, uint32_t length) const {
    const IsoFileEntry* fe = get_file_by_entrynum(entrynum);
    if (!fe || length == 0) return {};
    if (!is_extracted_dir_) {
        uint32_t avail = (offset < fe->size_bytes) ? (fe->size_bytes - offset) : 0u;
        uint32_t to_read = (std::min)(length, avail);
        std::vector<uint8_t> out(length, 0);
        if (to_read > 0) {
            auto part = read_slice(fe->disc_offset + offset, to_read);
            std::memcpy(out.data(), part.data(), part.size());
        }
        return out;
    } else {
        auto full = read_file(fe->path);
        std::vector<uint8_t> out(length, 0);
        if (offset < full.size()) {
            size_t to_copy = (std::min)(static_cast<size_t>(length), full.size() - static_cast<size_t>(offset));
            std::memcpy(out.data(), full.data() + offset, to_copy);
        }
        return out;
    }
}

bool IsoStreamReader::load_main_dol_into_memory(Memory& mem, uint32_t& out_entry_point) const {
    std::vector<uint8_t> dol_bytes;
    if (is_extracted_dir_) {
        fs::path dp = fs::path(base_path_) / "sys" / "main.dol";
        if (!fs::exists(dp)) return false;
        std::ifstream in(dp, std::ios::binary);
        dol_bytes.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    } else {
        auto hdr = read_slice(dol_offset_, 0x100);
        if (hdr.size() < 0x100) return false;
        uint32_t max_end = 0x100;
        for (int i = 0; i < 18; ++i) {
            uint32_t off = read_be32(&hdr[i * 4]);
            uint32_t sz  = read_be32(&hdr[0x90 + i * 4]);
            if (sz > 0 && off + sz > max_end) max_end = off + sz;
        }
        dol_bytes = read_slice(dol_offset_, max_end);
    }

    if (dol_bytes.size() < 0x100) return false;
    out_entry_point = read_be32(&dol_bytes[0xE0]);

    for (int i = 0; i < 7; ++i) {
        uint32_t off   = read_be32(&dol_bytes[0x00 + i * 4]);
        uint32_t vaddr = read_be32(&dol_bytes[0x48 + i * 4]);
        uint32_t sz    = read_be32(&dol_bytes[0x90 + i * 4]);
        if (sz > 0 && off + sz <= dol_bytes.size()) {
            mem.write_bytes(vaddr, &dol_bytes[off], sz);
        }
    }
    for (int i = 0; i < 11; ++i) {
        uint32_t off   = read_be32(&dol_bytes[0x1C + i * 4]);
        uint32_t vaddr = read_be32(&dol_bytes[0x64 + i * 4]);
        uint32_t sz    = read_be32(&dol_bytes[0xAC + i * 4]);
        if (sz > 0 && off + sz <= dol_bytes.size()) {
            mem.write_bytes(vaddr, &dol_bytes[off], sz);
        }
    }

    // Populate FileTbl entrynums (0x80173284, 34 entries of { const char* path, int32_t entrynum })
    for (uint32_t i = 0; i < 34u; ++i) {
        uint32_t entry_va = 0x80173284u + i * 8u;
        uint32_t str_va = mem.read_u32(entry_va);
        if (str_va >= kGcRamBase && str_va < kGcRamBase + kGcRamSize) {
            std::string path = mem.read_cstring(str_va, 256);
            if (!path.empty()) {
                int32_t enum_id = find_entrynum(path);
                mem.write_u32(entry_va + 4u, static_cast<uint32_t>(enum_id));
            }
        }
    }
    return true;
}

std::vector<uint8_t> IsoStreamReader::lzs_decode(const uint8_t* src, size_t src_len) {
    if (!src || src_len < 13) return {};
    uint32_t decomp_size    = read_be32(&src[0]);
    uint32_t bitstream_size = read_be32(&src[4]);
    if (12u + bitstream_size > src_len || decomp_size > 0x02000000u) return {};

    std::vector<uint8_t> out;
    out.reserve(decomp_size);

    size_t bit_ptr  = 12;
    size_t data_ptr = 12 + bitstream_size;
    uint8_t cur_bits = src[bit_ptr];
    int bit_idx = 7;

    auto get_bit = [&]() -> int {
        int b = 0;
        if (bit_idx == 0) {
            b = cur_bits & 1;
            bit_idx = 7;
            bit_ptr++;
            cur_bits = (bit_ptr < src_len) ? src[bit_ptr] : 0;
        } else {
            b = (cur_bits >> bit_idx) & 1;
            bit_idx--;
        }
        return b;
    };

    while (out.size() < decomp_size && data_ptr < src_len) {
        if (get_bit() == 1) {
            out.push_back(src[data_ptr++]);
        } else {
            int32_t neg_offset = 0;
            uint32_t match_len = 0;
            if (get_bit() == 1) {
                if (data_ptr + 1 >= src_len) break;
                uint8_t b0 = src[data_ptr];
                uint8_t b1 = src[data_ptr + 1];
                data_ptr += 2;
                uint32_t off13 = ((static_cast<uint32_t>(b0) << 5) & 0x1FE0u) | (static_cast<uint32_t>(b1) >> 3);
                neg_offset = static_cast<int32_t>(off13 | 0xFFFFE000u);
                uint32_t len3 = b1 & 7u;
                // Note: in P.N.03 compless.obj (0x80077718), rlwinm. r0, r5, 0, 29, 31 extracts low 3 bits of b1 (r5),
                // while our test encoder placed len3 in b0 & 7 == 0 with b1 == 0. Support both seamlessly:
                if (len3 == 0 && (b0 & 7u) != 0) len3 = b0 & 7u;
                if (len3 != 0) {
                    match_len = len3 + 2;
                } else {
                    if (data_ptr >= src_len) break;
                    uint8_t ext_len = src[data_ptr++];
                    if (ext_len == 0) {
                        break;
                    }
                    match_len = static_cast<uint32_t>(ext_len) + 9u;
                }
            } else {
                int bit_c = get_bit();
                int bit_d = get_bit();
                if (data_ptr >= src_len) break;
                uint8_t off8 = src[data_ptr++];
                neg_offset = static_cast<int32_t>(static_cast<uint32_t>(off8) | 0xFFFFFF00u);
                match_len = static_cast<uint32_t>((bit_c << 1) | bit_d) + 2u;
            }

            int64_t copy_pos = static_cast<int64_t>(out.size()) + neg_offset;
            for (uint32_t k = 0; k < match_len && out.size() < decomp_size; ++k) {
                if (copy_pos >= 0 && static_cast<size_t>(copy_pos) < out.size()) {
                    out.push_back(out[static_cast<size_t>(copy_pos)]);
                } else {
                    out.push_back(0);
                }
                copy_pos++;
            }
        }
    }
    return out;
}

std::vector<uint8_t> IsoStreamReader::lzs_encode_for_test(const uint8_t* raw, size_t raw_len) {
    std::vector<uint8_t> bits_buf;
    std::vector<uint8_t> data_buf;
    uint8_t cur_byte = 0;
    int bit_idx = 7;

    auto put_bit = [&](int b) {
        if (b) cur_byte |= static_cast<uint8_t>(1u << bit_idx);
        if (bit_idx == 0) {
            bits_buf.push_back(cur_byte);
            cur_byte = 0;
            bit_idx = 7;
        } else {
            bit_idx--;
        }
    };

    for (size_t i = 0; i < raw_len; ++i) {
        put_bit(1);
        data_buf.push_back(raw[i]);
    }
    put_bit(0);
    put_bit(1);
    data_buf.push_back(0x00);
    data_buf.push_back(0x00);
    data_buf.push_back(0x00);
    if (bit_idx != 7) {
        bits_buf.push_back(cur_byte);
    }

    uint32_t dec_sz = static_cast<uint32_t>(raw_len);
    uint32_t bit_sz = static_cast<uint32_t>(bits_buf.size());
    std::vector<uint8_t> packet(12 + bits_buf.size() + data_buf.size(), 0);
    packet[0] = static_cast<uint8_t>((dec_sz >> 24) & 0xFF);
    packet[1] = static_cast<uint8_t>((dec_sz >> 16) & 0xFF);
    packet[2] = static_cast<uint8_t>((dec_sz >> 8) & 0xFF);
    packet[3] = static_cast<uint8_t>(dec_sz & 0xFF);
    packet[4] = static_cast<uint8_t>((bit_sz >> 24) & 0xFF);
    packet[5] = static_cast<uint8_t>((bit_sz >> 16) & 0xFF);
    packet[6] = static_cast<uint8_t>((bit_sz >> 8) & 0xFF);
    packet[7] = static_cast<uint8_t>(bit_sz & 0xFF);
    std::memcpy(&packet[12], bits_buf.data(), bits_buf.size());
    std::memcpy(&packet[12 + bits_buf.size()], data_buf.data(), data_buf.size());
    return packet;
}

} // namespace pn03
