#include "tuskpch.h"

#include "SoLoudAudioEngineAPI.h"

namespace Tusk {
	void SoLoudAudioEngineAPI::init() {
		_soloudEngine->init();
	}

	SoLoudAudioEngineAPI::~SoLoudAudioEngineAPI() {
		_soloudEngine->deinit();
	}
}