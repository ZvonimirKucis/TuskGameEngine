#include "tuskpch.h"

#include "OpenALAudioClip.h"
#include "Tusk/Audio/WAVLoader.h"

namespace Tusk {
	OpenALAudioClip::OpenALAudioClip(const std::string& path) {
		loadData(path);
	}

	void OpenALAudioClip::loadData(const std::string& path) {
		std::uint8_t channels;
		std::int32_t sampleRate;
		std::uint8_t bitsPerSample;
		std::int32_t size;
		char* soundData;
		soundData = WAVLoader::loadWAV(path, channels, sampleRate, bitsPerSample, size);

		alGenBuffers(1, &_buffer);

		ALenum format;
		if (channels == 1 && bitsPerSample == 8)
			format = AL_FORMAT_MONO8;
		else if (channels == 1 && bitsPerSample == 16)
			format = AL_FORMAT_MONO16;
		else if (channels == 2 && bitsPerSample == 8)
			format = AL_FORMAT_STEREO8;
		else if (channels == 2 && bitsPerSample == 16)
			format = AL_FORMAT_STEREO16;

		alBufferData(_buffer, format, soundData, size, sampleRate);
		delete soundData;
	}

	OpenALAudioClip::~OpenALAudioClip() {
		alDeleteBuffers(1, &_buffer);
	}
}