#include "tuskpch.h"

#include "SoLoudAudioClip.h"

namespace Tusk {
	SoLoudAudioClip::SoLoudAudioClip(const std::string& path) {
		_clip->load(path.c_str());
	}

	SoLoudAudioClip::~SoLoudAudioClip() {
		delete _clip;
	}
}