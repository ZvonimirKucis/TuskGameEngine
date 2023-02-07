#pragma once

namespace Tusk {
	
	class WAVLoader {
	public:
        static char* loadWAV(const std::string& filename,
            std::uint8_t& channels,
            std::int32_t& sampleRate,
            std::uint8_t& bitsPerSample,
            std::int32_t& size);

    private:
        static void loadWAVFileHeader(std::ifstream& file,
            std::uint8_t& channels,
            std::int32_t& sampleRate,
            std::uint8_t& bitsPerSample,
            std::int32_t& size);

        static std::int32_t convertToInt(char* buffer, std::size_t len);
	};

}