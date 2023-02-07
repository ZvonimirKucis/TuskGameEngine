#include "tuskpch.h"

#include "WAVLoader.h"

namespace Tusk {

    char* WAVLoader::loadWAV(const std::string& filename, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, std::int32_t& size) {
        std::ifstream in(filename, std::ios::binary);
        loadWAVFileHeader(in, channels, sampleRate, bitsPerSample, size);

        char* data = new char[size];
        in.read(data, size);
        in.close();

        return data;
    }

    void WAVLoader::loadWAVFileHeader(std::ifstream& file, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, std::int32_t& size) {
        char buffer[4];

        file.read(buffer, 4);
        if (std::strncmp(buffer, "RIFF", 4) != 0)
            Logger::Fatal("ERROR: header doesn't begin with RIFF");
        
        file.read(buffer, 4);
        file.read(buffer, 4);
        if (std::strncmp(buffer, "WAVE", 4) != 0)
            Logger::Fatal("ERROR: header doesn't contain RIFF");

        file.read(buffer, 4);
        file.read(buffer, 4);

        file.read(buffer, 2);
        file.read(buffer, 2);
        channels = convertToInt(buffer, 2);

        file.read(buffer, 4);
        sampleRate = convertToInt(buffer, 4);

        file.read(buffer, 4);
        file.read(buffer, 2);

        file.read(buffer, 2);
        bitsPerSample = convertToInt(buffer, 2);

        file.read(buffer, 4);
        file.read(buffer, 4);

        // size of data
        file.read(buffer, 4);
        size = convertToInt(buffer, 4);
    }

    std::int32_t  WAVLoader::convertToInt(char* buffer, std::size_t len) {
        std::int32_t a = 0;
        std::memcpy(&a, buffer, len);
        return a;
    }

}