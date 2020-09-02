#pragma once

#include "AudioClip.h"

namespace Tusk {
	class AudioSource {
	public:
		virtual ~AudioSource() = default;

		virtual void play(const Ref<AudioClip>& clip) = 0;
		virtual void pause() = 0;
		virtual void continuePlaying() = 0;
		virtual void stop() = 0;
		virtual bool isPlaying() = 0;

		virtual void setVolume(float volume) = 0;
		virtual void setPitch(float pitch) = 0;
		virtual void setLooping(bool loop) = 0;
		virtual void setPosition(float x, float y, float z) = 0;
		virtual void setMaxDistance(float distance) = 0;

		static Ref<AudioSource> create();
	};
}