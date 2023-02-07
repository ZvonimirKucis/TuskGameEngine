#include "tuskpch.h"

#include "AudioEngine.h"

namespace Tusk {
	Scope<AudioEngineAPI> AudioEngine::_audioEngineAPI = AudioEngineAPI::create();

	void AudioEngine::init() {
		_audioEngineAPI->init();
	}

}