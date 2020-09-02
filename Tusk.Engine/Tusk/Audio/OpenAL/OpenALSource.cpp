#include "tuskpch.h"

#include "OpenALSource.h"

namespace Tusk {

	OpenALSource::OpenALSource() {
		createSource();
	}

	void OpenALSource::play(const Ref<AudioClip>& clip) {
		stop();
		alSourcei(_source, AL_BUFFER, clip->getBuffer());
		continuePlaying();
	}

	void OpenALSource::pause() {
		alSourcePause(_source);
	}

	void OpenALSource::continuePlaying() {
		alSourcePlay(_source);
	}

	void OpenALSource::stop() {
		alSourceStop(_source);
	}

	bool OpenALSource::isPlaying() {
		ALint state;
		alGetSourcei(_source, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}

	void OpenALSource::setVolume(float volume) {
		alSourcef(_source, AL_GAIN, volume);
	}

	void OpenALSource::setPitch(float pitch) {
		alSourcef(_source, AL_PITCH, pitch);
	}

	void OpenALSource::setLooping(bool loop) {
		alSourcei(_source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	}

	void OpenALSource::setPosition(float x, float y, float z) {
		alSource3f(_source, AL_POSITION, x, y, z);
	}

	void OpenALSource::setMaxDistance(float distance) {
		alSourcef(_source, AL_MAX_DISTANCE, distance);
	}

	void OpenALSource::createSource() {
		alGenSources(1, &_source);
		alSourcef(_source, AL_PITCH, 1);
		alSourcef(_source, AL_GAIN, 1.0f);
		alSource3f(_source, AL_POSITION, 0, 0, 0);
		alSource3f(_source, AL_VELOCITY, 0, 0, 0);
		alSourcei(_source, AL_LOOPING, AL_FALSE);

		alSourcef(_source, AL_ROLLOFF_FACTOR, 1);
		alSourcef(_source, AL_REFERENCE_DISTANCE, 0);
		alSourcef(_source, AL_MAX_DISTANCE, 100);
	}

	OpenALSource::~OpenALSource() {
		alDeleteSources(1, &_source);
	}
}