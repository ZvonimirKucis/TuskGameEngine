#pragma once

#include <AL/al.h>
#include "Tusk/Audio/AudioClip.h"

namespace Tusk {
	class OpenALAudioClip : public AudioClip {
	public:
		OpenALAudioClip(const std::string& path);
		virtual ~OpenALAudioClip() override;

		virtual uint32_t getBuffer() override { return _buffer; };

	private:
		void loadData(const std::string& path);

	private:
		ALuint _buffer;
	};
}