#include "tuskpch.h"

#include "OpenALAudioClip.h"
#include "Tusk/Audio/WAVLoader.h"

namespace Tusk {
	OpenALAudioClip::OpenALAudioClip(const std::string& path) {
		loadData(path);
		createSource();
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

	void OpenALAudioClip::createSource() {
		alGenSources( 1, &_source);
		alSourcef( _source, AL_PITCH, 1);
		alSourcef( _source, AL_GAIN, 1.0f);
		alSource3f( _source, AL_POSITION, 0, 0, 0);
		alSource3f( _source, AL_VELOCITY, 0, 0, 0);
		alSourcei( _source, AL_LOOPING, AL_FALSE);
		alSourcei( _source, AL_BUFFER, _buffer);
	}

	void OpenALAudioClip::play() {
		ALint state;
		alGetSourcei(_source, AL_SOURCE_STATE, &state);
		if (state == AL_PLAYING)
			return;
		alSourcePlay(_source);
	}


	OpenALAudioClip::~OpenALAudioClip() {
		alDeleteSources(1, &_source);
		alDeleteBuffers(1, &_buffer);
	}
}