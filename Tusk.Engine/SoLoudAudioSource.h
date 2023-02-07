#pragma once

#include "Tusk/Audio/AudioSource.h"

namespace Tusk {
	class SoLoudAudioSource : public AudioSource {
	public:
		SoLoudAudioSource();
		virtual ~SoLoudAudioSource() override;

		virtual void clip(const Ref<AudioClip>& clip) override;
		virtual void play() override;

		virtual void setVolume(float Volume) override;
		virtual void setPitch(float pitch) override;
		virtual void setLooping(bool loop) override;
		virtual void setPosition(float x, float y, float z) override;
		virtual void setMaxDistance(float distance) override;

	private:
		Ref<AudioClip> _clip;
	};
}