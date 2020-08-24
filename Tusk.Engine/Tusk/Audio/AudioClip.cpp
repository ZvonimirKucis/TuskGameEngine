#include "tuskpch.h"

#include "AudioClip.h"
#include "OpenAL/OpenALAudioClip.h"

namespace Tusk {
	Ref<AudioClip> AudioClip::load(const std::string& path) {
		return CreateRef<OpenALAudioClip>(path);
	}
}