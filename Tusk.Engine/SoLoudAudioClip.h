#pragma once

#include "Tusk/Audio/AudioClip.h"
#include <soloud.h>
#include <soloud_wav.h>

namespace Tusk {
	class SoLoudAudioClip : public AudioClip {
	public:
		SoLoudAudioClip(const std::string& path);
		virtual ~SoLoudAudioClip() override;

	private:
		SoLoud::Wav* _clip;
	};
}