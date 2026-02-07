#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

struct WavData {
    std::vector<char> data;
    uint32_t sampleRate;
    uint16_t channels;
    uint16_t bitsPerSample;
};

class WavLoader {
public:
    static WavData loadWav(const char* filename);
};
