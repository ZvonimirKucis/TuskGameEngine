#include "tuskpch.h"

#include "SoLoudAudioSource.h"

namespace Tusk {
	SoLoudAudioSource::SoLoudAudioSource() {
	}

	SoLoudAudioSource::~SoLoudAudioSource() {
	}

	void SoLoudAudioSource::clip(const Ref<AudioClip>& clip) {
		_clip = clip;
	}
	void SoLoudAudioSource::play() {

	}

	void SoLoudAudioSource::setVolume(float Volume) {}
	void SoLoudAudioSource::setPitch(float pitch) {}
	void SoLoudAudioSource::setLooping(bool loop) {}
	void SoLoudAudioSource::setPosition(float x, float y, float z) {}
	void SoLoudAudioSource::setMaxDistance(float distance) {}
}
