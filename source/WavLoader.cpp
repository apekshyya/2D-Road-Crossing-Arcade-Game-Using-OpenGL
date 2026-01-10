#include "WavLoader.hpp"
#include <iostream>
#include <cstring>

WavData WavLoader::loadWav(const char* filename) {
    WavData wav;
    std::ifstream file(filename, std::ios::binary);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open WAV file: " << filename << std::endl;
        return wav;
    }
    
    // Read RIFF header
    char chunkId[4];
    uint32_t chunkSize;
    char format[4];
    
    file.read(chunkId, 4);
    file.read(reinterpret_cast<char*>(&chunkSize), 4);
    file.read(format, 4);
    
    if (std::strncmp(chunkId, "RIFF", 4) != 0 || std::strncmp(format, "WAVE", 4) != 0) {
        std::cerr << "Invalid WAV file: " << filename << std::endl;
        return wav;
    }
    
    // Read fmt subchunk
    char subchunk1Id[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    
    file.read(subchunk1Id, 4);
    file.read(reinterpret_cast<char*>(&subchunk1Size), 4);
    file.read(reinterpret_cast<char*>(&audioFormat), 2);
    file.read(reinterpret_cast<char*>(&wav.channels), 2);
    file.read(reinterpret_cast<char*>(&wav.sampleRate), 4);
    
    uint32_t byteRate;
    uint16_t blockAlign;
    file.read(reinterpret_cast<char*>(&byteRate), 4);
    file.read(reinterpret_cast<char*>(&blockAlign), 2);
    file.read(reinterpret_cast<char*>(&wav.bitsPerSample), 2);
    
    // Skip any extra format bytes
    if (subchunk1Size > 16) {
        file.seekg(subchunk1Size - 16, std::ios::cur);
    }
    
    // Find data subchunk
    char subchunk2Id[4];
    uint32_t subchunk2Size;
    
    while (true) {
        file.read(subchunk2Id, 4);
        file.read(reinterpret_cast<char*>(&subchunk2Size), 4);
        
        if (std::strncmp(subchunk2Id, "data", 4) == 0) {
            break;
        }
        
        // Skip this chunk
        file.seekg(subchunk2Size, std::ios::cur);
        
        if (file.eof()) {
            std::cerr << "Data chunk not found in WAV file: " << filename << std::endl;
            return wav;
        }
    }
    
    // Read audio data
    wav.data.resize(subchunk2Size);
    file.read(wav.data.data(), subchunk2Size);
    
    file.close();
    return wav;
}
