#pragma once

#include <AL/al.h>
#include "Tusk/Audio/AudioClip.h"

namespace Tusk {
	class OpenALAudioClip : public AudioClip {
	public:
		OpenALAudioClip(const std::string& path);

		virtual ~OpenALAudioClip() override;

		virtual void play() override;

	private:
		void loadData(const std::string& path);
		void createSource();

	private:
		ALuint _buffer;
		ALuint _source;
	};
}