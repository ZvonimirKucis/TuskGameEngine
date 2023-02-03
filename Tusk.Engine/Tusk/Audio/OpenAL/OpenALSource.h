#pragma once

#include <al.h>
#include "Tusk/Audio/AudioSource.h"

namespace Tusk {
	class OpenALSource : public AudioSource {
	public:
		OpenALSource();

		virtual ~OpenALSource() override;

		virtual void play(const Ref<AudioClip>& clip) override;
		virtual void pause() override;
		virtual void continuePlaying() override;
		virtual void stop() override;
		virtual bool isPlaying() override;

		virtual void setVolume(float volume) override;
		virtual void setPitch(float pitch) override;
		virtual void setLooping(bool loop) override;
		virtual void setPosition(float x, float y, float z) override;
		virtual void setMaxDistance(float distance) override;

	private:
		void createSource();

	private:
		ALuint _source;
	};
}