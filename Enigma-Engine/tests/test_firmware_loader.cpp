/**
 * Enigma Engine - Firmware loader (Intel HEX / Motorola S-Record) tests.
 * Covers GUI backlog G4 (GP-7124): the loader must emit one section per
 * contiguous ROM run so Memory Map / Hex views show sparse blocks instead
 * of a single zero-filled span. The dense image (index == address) is
 * preserved for byte reads.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdint>

#include "ghidra/BinaryLoader.h"

int passed = 0, total = 0;
#define TEST(n, x) do { total++; if(x){std::cout<<"[PASS] "<<n<<"\n"<<std::flush;passed++;}else{std::cout<<"[FAIL] "<<n<<"\n"<<std::flush;} } while(0)

using namespace ghidra;

static std::string hx(uint8_t v) {
    std::ostringstream os;
    os << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int)v;
    return os.str();
}

// Intel HEX record: :LLAAAATT[DD...]CC with two's-complement checksum.
static std::string hexRecord(uint16_t addr, uint8_t type, const std::vector<uint8_t>& payload) {
    std::string rec = ":";
    uint32_t sum = payload.size() + (addr >> 8) + (addr & 0xFF) + type;
    rec += hx((uint8_t)payload.size()) + hx(addr >> 8) + hx(addr & 0xFF) + hx(type);
    for (uint8_t b : payload) {
        rec += hx(b);
        sum += b;
    }
    rec += hx((uint8_t)((0x100 - (sum & 0xFF)) & 0xFF));
    rec += "\n";
    return rec;
}

static std::string hexExtSeg(uint16_t seg) {
    return hexRecord(0x0000, 0x02, {(uint8_t)(seg >> 8), (uint8_t)(seg & 0xFF)});
}

// Motorola S-Record: S<t><BB><addr><data><CC>, ones'-complement checksum.
static std::string srec(char type, uint32_t addr, int addrSize, const std::vector<uint8_t>& payload) {
    std::string rec = "S";
    rec += type;
    uint8_t count = (uint8_t)(addrSize + payload.size() + 1);
    uint32_t sum = count;
    rec += hx(count);
    for (int i = addrSize - 1; i >= 0; --i) {
        uint8_t b = (uint8_t)((addr >> (i * 8)) & 0xFF);
        rec += hx(b);
        sum += b;
    }
    for (uint8_t b : payload) {
        rec += hx(b);
        sum += b;
    }
    rec += hx((uint8_t)(0xFF - (sum & 0xFF)));
    rec += "\n";
    return rec;
}

static bool sectionCovers(const std::vector<SectionInfo>& secs, uint64_t va) {
    for (const auto& s : secs) {
        if (va >= s.virtualAddress && va < s.virtualAddress + s.virtualSize) return true;
    }
    return false;
}

int main() {
    std::cout << "\n--- Intel HEX sparse sections ---" << std::endl;
    {
        // Two discontiguous runs: 16B at 0x1000, 16B at 0x8000.
        std::string hex;
        hex += hexRecord(0x1000, 0x00, std::vector<uint8_t>(16, 0x90));
        hex += hexExtSeg(0x0800); // base 0x8000
        hex += hexRecord(0x0000, 0x00, std::vector<uint8_t>(16, 0xCC));
        hex += hexRecord(0x0000, 0x01, {});
        std::string p = "test_fw_sparse.hex";
        std::ofstream out(p, std::ios::binary);
        out.write(hex.data(), (std::streamsize)hex.size());
        out.close();

        auto loader = ghidra::createLoader();
        TEST("hex sparse loads", loader->load(p));
        TEST("hex format", loader->getFormatName() == "Intel HEX");
        auto secs = loader->getSections();
        TEST("hex sparse two sections", secs.size() == 2);
        bool names = secs.size() == 2 && secs[0].name == ".rom0" && secs[1].name == ".rom1";
        TEST("hex sparse names", names);
        bool ranges = secs.size() == 2 && secs[0].virtualAddress == 0x1000 &&
                      secs[0].virtualSize == 16 && secs[1].virtualAddress == 0x8000 &&
                      secs[1].virtualSize == 16;
        TEST("hex sparse ranges", ranges);
        TEST("hex gap not covered", !sectionCovers(secs, 0x5000));
        TEST("hex run0 covered", sectionCovers(secs, 0x1005));
        TEST("hex run1 covered", sectionCovers(secs, 0x800F));
        auto b0 = loader->getBytes(0x1000, 4);
        TEST("hex dense image run0",
             b0.size() == 4 && b0[0] == 0x90 && b0[3] == 0x90);
        auto b1 = loader->getBytes(0x8000, 4);
        TEST("hex dense image run1",
             b1.size() == 4 && b1[0] == 0xCC && b1[3] == 0xCC);
        TEST("hex entry is min addr", loader->getEntryPoint() == 0x1000);
        std::remove(p.c_str());
    }

    std::cout << "\n--- Intel HEX single run + merge ---" << std::endl;
    {
        // Adjacent records merge into the legacy single ".text" section.
        std::string hex;
        hex += hexRecord(0x2000, 0x00, std::vector<uint8_t>(16, 0x90));
        hex += hexRecord(0x2010, 0x00, std::vector<uint8_t>(8, 0x91));
        hex += hexRecord(0x0000, 0x01, {});
        std::string p = "test_fw_single.hex";
        std::ofstream out(p, std::ios::binary);
        out.write(hex.data(), (std::streamsize)hex.size());
        out.close();

        auto loader = ghidra::createLoader();
        TEST("hex single loads", loader->load(p));
        auto secs = loader->getSections();
        TEST("hex single one section", secs.size() == 1);
        TEST("hex single legacy name",
             secs.size() == 1 && secs[0].name == ".text" &&
             secs[0].virtualAddress == 0x2000 && secs[0].virtualSize == 24);
        auto b = loader->getBytes(0x2010, 2);
        TEST("hex single dense image", b.size() == 2 && b[0] == 0x91 && b[1] == 0x91);
        std::remove(p.c_str());
    }

    std::cout << "\n--- Motorola S-Record sparse sections ---" << std::endl;
    {
        std::string srec_;
        srec_ += srec('1', 0x1000, 2, std::vector<uint8_t>(8, 0xAA));
        srec_ += srec('1', 0x9000, 2, std::vector<uint8_t>(8, 0xBB));
        srec_ += srec('9', 0x9000, 2, {});
        std::string p = "test_fw_sparse.srec";
        std::ofstream out(p, std::ios::binary);
        out.write(srec_.data(), (std::streamsize)srec_.size());
        out.close();

        auto loader = ghidra::createLoader();
        TEST("srec sparse loads", loader->load(p));
        TEST("srec format", loader->getFormatName() == "Motorola S-Record");
        auto secs = loader->getSections();
        TEST("srec sparse two sections", secs.size() == 2);
        bool ranges = secs.size() == 2 && secs[0].virtualAddress == 0x1000 &&
                      secs[0].virtualSize == 8 && secs[1].virtualAddress == 0x9000 &&
                      secs[1].virtualSize == 8;
        TEST("srec sparse ranges", ranges);
        TEST("srec gap not covered", !sectionCovers(secs, 0x5000));
        auto b = loader->getBytes(0x9000, 2);
        TEST("srec dense image", b.size() == 2 && b[0] == 0xBB && b[1] == 0xBB);
        TEST("srec S9 entry", loader->getEntryPoint() == 0x9000);
        std::remove(p.c_str());
    }

    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Firmware Loader Tests: " << passed << "/" << total << " passed." << std::endl;
    return (passed == total) ? 0 : 1;
}
