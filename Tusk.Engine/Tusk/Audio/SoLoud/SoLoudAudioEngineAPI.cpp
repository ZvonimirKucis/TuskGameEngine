#include "tuskpch.h"

#include "SoLoudAudioEngineAPI.h"

namespace Tusk {
	void SoLoudAudioEngineAPI::init() {
		_soloudEngine = new SoLoud::Soloud;
		_soloudEngine->init();
	}

	SoLoudAudioEngineAPI::~SoLoudAudioEngineAPI() {
		_soloudEngine->deinit();
		delete _soloudEngine;
	}
}